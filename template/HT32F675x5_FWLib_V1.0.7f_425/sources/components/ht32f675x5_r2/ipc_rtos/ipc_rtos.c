/*************************************************************************************************************
 * @file    ipc_rtos.c
 * @version V1.0
 * @date    2021-03-17
 * @brief   
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/



#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_sys_ctrl.h"

#include "cmsis_os2.h"
#include "rtx_os.h"

#include "app_cfg.h"
#include "utility.h"
#include "ipc_rtos.h"


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define CHECK_OS_RETURN( id, entity)             \
    do                                           \
    {                                            \
        if(NULL == id)                           \
        {                                        \
            PRINTF("%s new fail.\n", entity);    \
            return ERR_STA_ERROR;                \
        }                                        \
    }while(0)


#if defined(__MAIN_PROCESSOR)
    #define IPC_SW_INT_CH             (SW_IRQ1)
#elif defined(__CO_PROCESSOR)
    #define IPC_SW_INT_CH             (SW_IRQ0)
#else
    #error "core unset"
#endif

#define IPC_RECEIVE_MSG_THREAD_FLAG   (0x0001U)




//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef struct
{
    uint8_t  u8Data[IPC_MSG_EXTRA_DATA_LEN];
    uint32_t u32DataLen;
    osMemoryPoolId_t dataPoolId;

} stIPCExtraData_t __attribute__((aligned(4)));

typedef struct
{
    uint32_t u32Cmd;
    uint8_t  u8Data[IPC_MSG_DATA_LEN];
    uint32_t u32DataLen;
    stIPCExtraData_t* pstExtraData;

} stIPCData_t __attribute__((aligned(4)));


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
/* Task Receive */
static uint32_t ipcRecvTaskCbMem[osRtxThreadCbSize / sizeof(uint32_t)] __attribute__ ((section(".bss.os.thread.cb")));
static uint64_t ipcRecvTaskStackMem[(IPC_RX_TASK_STACK_SIZE) / sizeof(uint64_t)];

/* Message Queue */
static uint32_t ipcQueueCbMem[osRtxMessageQueueCbSize / sizeof(uint32_t)] __attribute__ ((section(".bss.os.msgqueue.cb")));
static uint32_t ipcQueueMqMem[osRtxMessageQueueMemSize(IPC_MSG_COUNT, sizeof(stIPCData_t)) / sizeof(uint32_t)];

/* Extra Message Queue */
static uint32_t ipcPoolCbMem[osRtxMemoryPoolCbSize / sizeof(uint32_t)] __attribute__ ((section(".bss.os.mempool.cb")));
static uint32_t ipcPoolMem[osRtxMemoryPoolMemSize(IPC_MSG_EXTRA_DATA_COUNT, sizeof(stIPCExtraData_t)) / sizeof(uint32_t)];

/* Mutex For Local Threads, hw_lock For Inter-Processor */
static uint32_t ipcMutexCbMem[osRtxMutexCbSize / sizeof(uint32_t)] __attribute__ ((section (".bss.os.mutex.cb")));

/* Task, Queue, Memory Pool, Mutex ID */
static osThreadId_t       ipcRxTaskId;
static osMessageQueueId_t ipcTxQueueId;
static osMemoryPoolId_t   ipcTxPoolId;
static osMutexId_t        ipcMutexId;

static stIpcMsg_t         stIpcMsg;
static stIPCData_t        g_stRxTmpData; // Tmp variable

/* Receive Task Callback Function */
static ipc_rx_msg_cb_func ipcRxCbFunc;




/**
 * @brief  Check IPC Receive Queue ID.
 * @param  pRxQueueId.
 */
static void ipc_rtos_check_rx_queue_id(osMessageQueueId_t *pRxQueueId)
{
    uint32_t u32Id;

    if( NULL == *pRxQueueId)
    {
        #if defined(__MAIN_PROCESSOR)
            rom_hw_sys_ctrl_read_com_reg( SYS_CTRL_COM_REG_IPC_ID_SLAVE, &u32Id);
        #else
            rom_hw_sys_ctrl_read_com_reg( SYS_CTRL_COM_REG_IPC_ID_MASTER, &u32Id);
        #endif

        *pRxQueueId = (osMessageQueueId_t)u32Id;
        PRINTF("Rx queue id(reg): %08X\n", u32Id);
    }
}

/**
 * @brief  Trigger a Software Interrupt.
 */
static void ipc_rtos_trig_int(void)
{
#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_trigger_sw_int(SYS_CTRL_CP, SYS_CTRL_SW_INT_BIT0);
#else
    rom_hw_sys_ctrl_trigger_sw_int(SYS_CTRL_MP, SYS_CTRL_SW_INT_BIT1);
#endif
}

/**
 * @brief  IPC Interrupt IRQ Handler.
 */
#if defined(__MAIN_PROCESSOR)
void SW_IRQ1_Handler(void)
#else
void SW_IRQ0_Handler(void)
#endif
{
    uint8_t intFlag;

#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_get_sw_int_flag(SYS_CTRL_MP, &intFlag);
    rom_hw_sys_ctrl_clear_sw_int_flag(SYS_CTRL_MP, intFlag);
#else
    rom_hw_sys_ctrl_get_sw_int_flag(SYS_CTRL_CP, &intFlag);
    rom_hw_sys_ctrl_clear_sw_int_flag(SYS_CTRL_CP, intFlag);
#endif

    if(NULL != ipcRxTaskId)
    {
        osThreadFlagsSet(ipcRxTaskId, IPC_RECEIVE_MSG_THREAD_FLAG);
    }
}

/**
 * @brief  IPC Receive Data Task.
 * @param  argument.
 */
static void ipc_rtos_rx_task(void* argument)
{
    uint8_t lockId;
    osStatus_t osStatus = osOK;
    osMessageQueueId_t rxQueueId = NULL;

#if defined(__MAIN_PROCESSOR)
    lockId = SYS_CTRL_LOCK_ID_IPC_SLAVE;;
#else
    lockId = SYS_CTRL_LOCK_ID_IPC_MASTER;
#endif

    for(; ;)
    {
        do
        {
            ipc_rtos_check_rx_queue_id( &rxQueueId);

            if(NULL == rxQueueId)
            {
                PRINTF("Rx queue id: %08X\n", (uint32_t)rxQueueId);
                break;
            }

            if(ERR_STA_OK == rom_hw_sys_ctrl_lock_device(lockId))
            {
                osStatus = osMessageQueueGet(rxQueueId, &g_stRxTmpData, NULL, 0);

                if(osOK == osStatus)
                {
                    stIpcMsg.u32Cmd = g_stRxTmpData.u32Cmd;
                    stIpcMsg.pu8Data = g_stRxTmpData.u8Data;
                    stIpcMsg.u32DataLen = g_stRxTmpData.u32DataLen;
                    stIpcMsg.pu8ExtraData = NULL;
                    stIpcMsg.u32ExtraDataLen = 0;

                    stIPCExtraData_t *pstExtraData = g_stRxTmpData.pstExtraData;
                    if(NULL != pstExtraData)
                    {
                        stIpcMsg.pu8ExtraData = pstExtraData->u8Data;
                        stIpcMsg.u32ExtraDataLen = pstExtraData->u32DataLen;
                    }

                    if (NULL != ipcRxCbFunc)
                    {
                        ipcRxCbFunc( &stIpcMsg);
                    }

                    /* Free extra data */
                    if (NULL != pstExtraData)
                    {
                        osMemoryPoolFree( pstExtraData->dataPoolId, pstExtraData);
                    }
                }

                rom_hw_sys_ctrl_release_device( lockId);
            }

            /* After proc a msg, yield */
            osThreadYield();

        }while(osOK == osStatus); /* Loop until no msg exist */

        /* Wait for next msg */
        osThreadFlagsWait(IPC_RECEIVE_MSG_THREAD_FLAG, osFlagsWaitAny, osWaitForever);
    }
}

/**
 * @brief  IPC Task Initialization.
 *         Creat IPC Task, For IPC Receive.
 *         Creat IPC Message Queue, For IPC Send message(few of data).
 *         Creat IPC Memory Pool, For IPC Send Mass of data.
 *         Creat IPC Mutex, For Multiple Send Requirement.
 * @return HW status: @ref EN_ERR_STA_T
 */
static uint8_t ipc_rtos_task_init(void)
{
    const osThreadAttr_t taskAttr =
    {
        .name = "ipc_rx_task",
        .cb_mem = ipcRecvTaskCbMem,
        .cb_size = sizeof(ipcRecvTaskCbMem),
        .stack_mem = ipcRecvTaskStackMem,
        .stack_size = sizeof(ipcRecvTaskStackMem),
        .priority = IPC_RX_TASK_PRIORITY
    };

    const osMessageQueueAttr_t queueAttr =
    {
        .name = "ipc_queue",
        .cb_mem = &ipcQueueCbMem,
        .cb_size = sizeof(ipcQueueCbMem),
        .mq_mem = ipcQueueMqMem,
        .mq_size = sizeof(ipcQueueMqMem)
    };

    const osMemoryPoolAttr_t poolAttr =
    {
        .name = "ipc_pool",
        .cb_mem = &ipcPoolCbMem,
        .cb_size = sizeof(ipcPoolCbMem),
        .mp_mem = &ipcPoolMem,
        .mp_size = sizeof(ipcPoolMem)
    };

    const osMutexAttr_t ipcMutexAttr = 
    {
        .name = "ipc_mutex",
        .attr_bits = osMutexRecursive | osMutexPrioInherit | osMutexRobust,
        .cb_mem = ipcMutexCbMem,
        .cb_size = sizeof(ipcMutexCbMem)
    };

    ipcRxTaskId = osThreadNew(ipc_rtos_rx_task, NULL, &taskAttr);
    CHECK_OS_RETURN(ipcRxTaskId, "ipc_rx_task");
    PRINTF( "ipcRxTaskId: %08X\n", (uint32_t)ipcRxTaskId);

    ipcTxQueueId = osMessageQueueNew(IPC_MSG_COUNT, sizeof(stIPCData_t), &queueAttr);
    CHECK_OS_RETURN(ipcTxQueueId, "ipc_queue");
    PRINTF( "ipcTxQueueId: %08X\n", (uint32_t)ipcTxQueueId);

    ipcTxPoolId = osMemoryPoolNew(IPC_MSG_EXTRA_DATA_COUNT, sizeof(stIPCExtraData_t), &poolAttr);
    CHECK_OS_RETURN(ipcTxPoolId, "ipc_pool");
    PRINTF( "ipcTxPoolId: %08X\n", (uint32_t)ipcTxPoolId);

    ipcMutexId = osMutexNew(&ipcMutexAttr);
    CHECK_OS_RETURN(ipcMutexId, "ipc_mutex");
    PRINTF( "ipcMutexId: %08X\n", (uint32_t)ipcMutexId);

    return ERR_STA_OK;
}

/**
 * @brief  IPC Data Initialization.
 */
static void ipc_rtos_data_init( void)
{
    ipcRxTaskId  = NULL;
    ipcTxQueueId = NULL;
    ipcTxPoolId  = NULL;
    ipcMutexId   = NULL;

    ipcRxCbFunc  = NULL;

    memset( &stIpcMsg, 0, sizeof(stIpcMsg));

    #if defined(__MAIN_PROCESSOR)
        rom_hw_sys_ctrl_release_device( SYS_CTRL_LOCK_ID_IPC_MASTER);
        rom_hw_sys_ctrl_write_com_reg( SYS_CTRL_COM_REG_IPC_ID_MASTER, 0);
    #else
        rom_hw_sys_ctrl_release_device( SYS_CTRL_LOCK_ID_IPC_SLAVE);
        rom_hw_sys_ctrl_write_com_reg( SYS_CTRL_COM_REG_IPC_ID_SLAVE, 0);
    #endif
}

/**
 * @brief  IPC Send Message by Non-Blocking. This API Can Call in IRQ Handler.
 * @param  u32Cmd: Command of Message.
 * @param  pu8Data: Data of Message.
 * @param  u32DataLen: Data Length of Message.
 * @param  pu8ExtraData: Extra Data of Message.
 * @param  u32ExtraDataLen: Extra Data Length of Message.
 * @return HW status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ipc_rtos_send_msg_nonblocking(uint32_t u32Cmd, uint8_t* pu8Data, uint32_t u32DataLen, 
                                        uint8_t* pu8ExtraData, uint32_t u32ExtraDataLen)
{
    uint8_t lockId;
    stIPCData_t stData;
    stIPCExtraData_t *pstExtraData = NULL;

    if((NULL == ipcTxQueueId) || (NULL == ipcTxPoolId) || (NULL == ipcMutexId))
    {
        return ERR_PARA_ERR;
    }

    if((NULL == pu8Data) && (0 != u32DataLen))
    {
        return ERR_PARA_ERR;
    }

    if((NULL == pu8ExtraData) && (0 != u32ExtraDataLen))
    {
        return ERR_PARA_ERR;
    }

    if((u32DataLen > IPC_MSG_DATA_LEN) || (u32ExtraDataLen > IPC_MSG_EXTRA_DATA_LEN))
    {
        return ERR_PARA_ERR;
    }

    if(0U == __get_IPSR())
    {
        if(osOK != osMutexAcquire(ipcMutexId,0))
        {
            return ERR_STA_BUSY+0x10;
        }
    }

#if defined(__MAIN_PROCESSOR)
    lockId = SYS_CTRL_LOCK_ID_IPC_MASTER;
#else
    lockId = SYS_CTRL_LOCK_ID_IPC_SLAVE;
#endif

    if( rom_hw_sys_ctrl_lock_device(lockId))
    {
        if(0U == __get_IPSR())
        {
            osMutexRelease( ipcMutexId);
        }
        return ERR_STA_BUSY+0x11;
    }

    stData.u32Cmd = u32Cmd;
    stData.u32DataLen = u32DataLen;
    memcpy(stData.u8Data, pu8Data, u32DataLen);

    if(NULL == pu8ExtraData || 0 == u32ExtraDataLen)
    {
        stData.pstExtraData = NULL;
    }
    else
    {
        //osWaitForever is NOT allowed since locked, peer has no access to it
        pstExtraData = osMemoryPoolAlloc(ipcTxPoolId, 0);
        if(NULL == pstExtraData)
        {
            rom_hw_sys_ctrl_release_device( lockId);
            if(0U == __get_IPSR())
            {
                osMutexRelease( ipcMutexId);
            }
            return ERR_DATA_BUSY;
        }

        memcpy(pstExtraData->u8Data, pu8ExtraData, u32ExtraDataLen);
        pstExtraData->u32DataLen = u32ExtraDataLen;
        pstExtraData->dataPoolId = ipcTxPoolId;

        stData.pstExtraData = pstExtraData;
    }

    if(osOK != osMessageQueuePut(ipcTxQueueId, &stData, NULL, 0))
    {
        /* If failed, free extra data if needed */
        if( NULL != pstExtraData)
        {
            osMemoryPoolFree( ipcTxPoolId, pstExtraData);
        }

        rom_hw_sys_ctrl_release_device( lockId);
        if(0U == __get_IPSR())
        {
            osMutexRelease( ipcMutexId);
        }
        return ERR_STA_BUSY+0x12;
    }

    rom_hw_sys_ctrl_release_device( lockId);

    if( 0U == __get_IPSR())
    {
        osMutexRelease( ipcMutexId);
    }

    ipc_rtos_trig_int();

    return ERR_STA_OK;
}

/**
 * @brief  IPC Send Message by Blocking. This API Can Not Call in IRQ Handler.
 * @param  u32Cmd: Command of Message.
 * @param  pu8Data: Data of Message.
 * @param  u32DataLen: Data Length of Message.
 * @param  pu8ExtraData: Extra Data of Message.
 * @param  u32ExtraDataLen: Extra Data Length of Message.
 * @return HW status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ipc_rtos_send_msg_blocking(uint32_t u32Cmd, uint8_t* pu8Data, uint32_t u32DataLen, 
                                     uint8_t* pu8ExtraData, uint32_t u32ExtraDataLen)
{
    uint8_t lockId;
    stIPCData_t stData;
    stIPCExtraData_t *pstExtraData = NULL;
    osStatus_t osStatus;

    if((NULL == ipcTxQueueId) || (NULL == ipcTxPoolId) || (NULL == ipcMutexId))
    {
        return ERR_PARA_ERR;
    }

    if((NULL == pu8Data) && (0 != u32DataLen))
    {
        return ERR_PARA_ERR;
    }

    if((NULL == pu8ExtraData) && (0 != u32ExtraDataLen))
    {
        return ERR_PARA_ERR;
    }

    if((u32DataLen > IPC_MSG_DATA_LEN) || (u32ExtraDataLen > IPC_MSG_EXTRA_DATA_LEN))
    {
        return ERR_PARA_ERR;
    }

    /* Can Not Call in IRQ Handler. */
    if(__get_IPSR())
    {
        return ERR_NOT_ALLOWED;
    }

    if(osOK != osMutexAcquire(ipcMutexId,osWaitForever))
    {
        return ERR_STA_BUSY;
    }

#if defined(__MAIN_PROCESSOR)
    lockId = SYS_CTRL_LOCK_ID_IPC_MASTER;
#else
    lockId = SYS_CTRL_LOCK_ID_IPC_SLAVE;
#endif
    
    stData.u32Cmd = u32Cmd;
    stData.u32DataLen = u32DataLen;
    memcpy(stData.u8Data, pu8Data, u32DataLen);

    if(NULL == pu8ExtraData || 0 == u32ExtraDataLen)
    {
        stData.pstExtraData = NULL;
    }
    else
    {
        do
        {
            while(rom_hw_sys_ctrl_lock_device(lockId))
            {
                /* Blocking for getting lock */
                osThreadYield();
            }

            /* osWaitForever is NOT allowed since locked, peer has no access to it */
            pstExtraData = osMemoryPoolAlloc(ipcTxPoolId, 0);
            rom_hw_sys_ctrl_release_device( lockId);

            if(NULL == pstExtraData)
            {
                /* If get pool failed, try again */
                osThreadYield();
            }
        }while( NULL == pstExtraData);

        pstExtraData->dataPoolId = ipcTxPoolId;
        pstExtraData->u32DataLen = u32ExtraDataLen;
        memcpy(pstExtraData->u8Data, pu8ExtraData, u32ExtraDataLen);

        stData.pstExtraData = pstExtraData;
    }

    /* Send Message to Message Queue */
    do
    {
        while(rom_hw_sys_ctrl_lock_device( lockId))
        {
            /* Blocking for getting lock */
            osThreadYield();
        }

        osStatus = osMessageQueuePut(ipcTxQueueId, &stData, NULL, 0);
        rom_hw_sys_ctrl_release_device(lockId);

        if(osOK != osStatus)
        {
            osThreadYield();
        }
    }while( osOK != osStatus);

    ipc_rtos_trig_int();

    osMutexRelease( ipcMutexId);

    return ERR_STA_OK;
}

/**
 * @brief  Inter-Processor Communication(IPC) Initialization.
 * @param  pfnCallback: IPC receive callback function.
 * @return HW status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ipc_rtos_init( ipc_rx_msg_cb_func pfnCallback)
{
    ipc_rtos_data_init();

    // IPC Interrupt Initialization.
    NVIC_ClearPendingIRQ(IPC_SW_INT_CH);
    NVIC_SetPriority(IPC_SW_INT_CH, 3);
    NVIC_EnableIRQ(IPC_SW_INT_CH);

    ipcRxCbFunc = pfnCallback;

    if(ipc_rtos_task_init())
    {
        return ERR_STA_ERROR;
    }

    #if defined(__MAIN_PROCESSOR)
        rom_hw_sys_ctrl_write_com_reg( SYS_CTRL_COM_REG_IPC_ID_MASTER, (uint32_t)ipcTxQueueId);
        rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, IPC_SW_INT_CH);
    #else
        rom_hw_sys_ctrl_write_com_reg( SYS_CTRL_COM_REG_IPC_ID_SLAVE, (uint32_t)ipcTxQueueId);
        rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_CP, IPC_SW_INT_CH);
    #endif

    return ERR_STA_OK;
}


