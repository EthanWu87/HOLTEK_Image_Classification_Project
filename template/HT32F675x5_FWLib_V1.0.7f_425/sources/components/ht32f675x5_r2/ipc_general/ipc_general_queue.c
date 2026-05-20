/*************************************************************************************************************
 * @file    ipc_general_queue.c
 * @version V1.0
 * @date    2022-12-28
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

#include "app_cfg.h"
#include "utility.h"

#include "msg_queue.h"
#include "ipc_general_queue.h"


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#if defined(__MAIN_PROCESSOR)
    #define SYS_CTRL_HANDLE                ( SYS_CTRL_MP )
    #define IPC_SW_INT_CH                  ( SW_IRQ1 )
    #define IPC_SW_IRQ_HANDLER             SW_IRQ1_Handler
#elif defined(__CO_PROCESSOR)
    #define SYS_CTRL_HANDLE                ( SYS_CTRL_CP )
    #define IPC_SW_INT_CH                  ( SW_IRQ0 )
    #define IPC_SW_IRQ_HANDLER             SW_IRQ0_Handler
#else
    #error "core unset"
#endif

#define IPC_SEND_TIMEOUT_MS                ( 100 )


//=====================================================================================================================
// LOCAL VARIATE
//=====================================================================================================================
static pMsgQueueId_t m_pIpcTxMsgQueueId;
static stIpcInit_t m_stIpcInit;
static ipc_rx_msg_cb_func m_pfnIpcRxCbFunc;
static stQueueDef_t m_stQueue;

static uint8_t m_au8TxTempBuf[IPC_MSG_DATA_SIZE + 4] __attribute__((aligned(4)));
static uint8_t m_au8RxTempBuf[IPC_MSG_DATA_SIZE + 4] __attribute__((aligned(4)));



/**
 * @brief  Trigger a software interrupt.
 */
static void ipc_general_trig_int(void)
{
#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_trigger_sw_int(SYS_CTRL_CP, SYS_CTRL_SW_INT_BIT0);
#else
    rom_hw_sys_ctrl_trigger_sw_int(SYS_CTRL_MP, SYS_CTRL_SW_INT_BIT1);
#endif
}

/**
 * @brief  Check IPC Receive Buffer ID.
 */
static stQueueDef_t* ipc_general_get_rx_data_buffer_id(void)
{
    uint32_t u32Id;

#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_IPC_ID_SLAVE, &u32Id);
#else
    rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_IPC_ID_MASTER, &u32Id);
#endif

    return (stQueueDef_t *)u32Id;
}

/**
 * @brief  IPC Receive Data.
 */
static void ipc_general_receive_handler(void)
{
    uint8_t  u8LockId;
    uint8_t  u8LockRcvStatus;
    uint32_t u32RcvStatus;
    uint8_t  u8WriteComRegStatus;
    stQueueDef_t *pRxQueueId;
    stIpcMsg_t stIpcRxMsg;
    EN_QUEUE_ERR_STA_T enStatus = QUEUE_STA_OK;


#if defined(__MAIN_PROCESSOR)
    u8LockId = SYS_CTRL_LOCK_ID_IPC_SLAVE;
    u8LockRcvStatus = SYS_CTRL_LOCK_ID_RECEIVE_STATUS_SLAVE;
#else
    u8LockId = SYS_CTRL_LOCK_ID_IPC_MASTER;
    u8LockRcvStatus = SYS_CTRL_LOCK_ID_RECEIVE_STATUS_MASTER;
#endif

    while (1)
    {
        pRxQueueId = ipc_general_get_rx_data_buffer_id();

        if (NULL == pRxQueueId)
        {
            PRINTF("The rx queue id is NULL\n");
            break;
        }

        if (ERR_STA_OK == rom_hw_sys_ctrl_lock_device(u8LockId))
        {
            if (msg_queue_is_empty(pRxQueueId))
            {
                rom_hw_sys_ctrl_release_device(u8LockId);
                break;
            }

            //m_stIpcRxMsg.pu8Data = m_au8RxTempBuf;
            enStatus = msg_queue_pop(pRxQueueId, (void *)m_au8RxTempBuf);
            stIpcRxMsg.pu8Data = &m_au8RxTempBuf[4];
            stIpcRxMsg.u32DataLen = BUILD_UINT32(m_au8RxTempBuf[0], m_au8RxTempBuf[1], m_au8RxTempBuf[2], m_au8RxTempBuf[3]);

            if (QUEUE_STA_OK == enStatus)
            {
                if (NULL != m_pfnIpcRxCbFunc)
                {
                    u32RcvStatus = m_pfnIpcRxCbFunc(stIpcRxMsg.pu8Data, stIpcRxMsg.u32DataLen);

                    while (1)
                    {
                        if (ERR_STA_OK == rom_hw_sys_ctrl_lock_device(u8LockRcvStatus))
                        {
                            #if defined(__MAIN_PROCESSOR)
                                rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_SLAVE,
                                                              (uint32_t)u32RcvStatus);
                            #else
                                rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_MASTER,
                                                              (uint32_t)u32RcvStatus);
                            #endif
                            rom_hw_sys_ctrl_release_device(u8LockRcvStatus);
                            break;
                        }

                        // This delay is necessary. If no delay is added here, it will result in an error.
                        rom_delay_us(1); 
                    };
                }
                rom_hw_sys_ctrl_release_device(u8LockId);
            }
        }

        /* After proc a msg, yield */
        rom_delay_us(1); // This delay is necessary. If no delay is added here, it will result in an error.

    }; /* Loop until no msg exist */
}

/**
 * @brief  IPC SW interrupt IRQ handler.
 */
void IPC_SW_IRQ_HANDLER(void)
{
    uint8_t intFlag;

    rom_hw_sys_ctrl_get_sw_int_flag(SYS_CTRL_HANDLE, &intFlag);
    rom_hw_sys_ctrl_clear_sw_int_flag(SYS_CTRL_HANDLE, intFlag);

    if (intFlag)
    {
        ipc_general_receive_handler();
    }
}

/**
 * @brief  General ipc Initialization.
 * @param  pstIpcInit: Pointer to ipc init struct.
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ipc_general_init(stIpcInit_t *pstIpcInit)
{
    // Creat message queue.
    m_pIpcTxMsgQueueId = msg_queue_create(&m_stQueue, pstIpcInit->pu8Buf, pstIpcInit->u32BufSize, 
                                          pstIpcInit->u32MsgCount, pstIpcInit->u32MsgSize, pstIpcInit->enMode);

    memcpy(&m_stIpcInit, pstIpcInit, sizeof(stIpcInit_t));
    m_pfnIpcRxCbFunc = pstIpcInit->pfnCallback;

#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_release_device(SYS_CTRL_LOCK_ID_IPC_MASTER);
    rom_hw_sys_ctrl_release_device(SYS_CTRL_LOCK_ID_RECEIVE_STATUS_MASTER);
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_ID_MASTER, (uint32_t)m_pIpcTxMsgQueueId);
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_MASTER, 0xFFFFFFFF);
#else
    rom_hw_sys_ctrl_release_device(SYS_CTRL_LOCK_ID_IPC_SLAVE);
    rom_hw_sys_ctrl_release_device(SYS_CTRL_LOCK_ID_RECEIVE_STATUS_SLAVE);
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_ID_SLAVE, (uint32_t)m_pIpcTxMsgQueueId);
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_SLAVE, 0xFFFFFFFF);
#endif

    // SW int initialization.
    NVIC_ClearPendingIRQ(IPC_SW_INT_CH);
    NVIC_SetPriority(IPC_SW_INT_CH, 3);
    NVIC_EnableIRQ(IPC_SW_INT_CH);
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_HANDLE, IPC_SW_INT_CH);

    return ERR_STA_OK;
}

/**
 * @brief  Send ipc message by blocking. This API can not be called from Interrupt Service Routines (ISR).
 * @param  pu8Data: Pointer to the data buffer which will be sent.
 * @param  u32DataLen: Data length.
 * @return status: @ref EN_ERR_STA_T.
 */
uint32_t ipc_general_send_msg_blocking(uint8_t *pu8Data, uint32_t u32DataLen)
{
    uint8_t  u8Timeout = 0;
    uint8_t  u8IntFlag;
    uint8_t  u8LockId;
    uint8_t  u8LockRcvStatus;
    uint32_t u32MsgRcvStatus;
    stIpcMsg_t stMsg;

    if (NULL == m_pIpcTxMsgQueueId)
    {
        return ERR_PARA_ERR;
    }

    if ((NULL == pu8Data) && (0 != u32DataLen))
    {
        return ERR_PARA_ERR;
    }

    if (u32DataLen > m_stIpcInit.u32MsgSize)
    {
        return ERR_PARA_ERR;
    }

#if defined(__MAIN_PROCESSOR)
    u8LockId = SYS_CTRL_LOCK_ID_IPC_MASTER;
    u8LockRcvStatus = SYS_CTRL_LOCK_ID_RECEIVE_STATUS_MASTER;
#else
    u8LockId = SYS_CTRL_LOCK_ID_IPC_SLAVE;
    u8LockRcvStatus = SYS_CTRL_LOCK_ID_RECEIVE_STATUS_SLAVE;
#endif

    if (rom_hw_sys_ctrl_lock_device(u8LockId))
    {
        return ERR_STA_BUSY;
    }

    // IPC data
    memcpy(m_au8TxTempBuf, &u32DataLen, sizeof(uint32_t));
    memcpy(&m_au8TxTempBuf[sizeof(uint32_t)], pu8Data, u32DataLen);
    if (QUEUE_STA_OK != msg_queue_push(m_pIpcTxMsgQueueId, m_au8TxTempBuf))
    {
        rom_hw_sys_ctrl_release_device(u8LockId);
        return ERR_STA_BUSY;
    }

    rom_hw_sys_ctrl_release_device(u8LockId);
    ipc_general_trig_int();

    while (1)
    {
        if (ERR_STA_OK == rom_hw_sys_ctrl_lock_device(u8LockRcvStatus))
        {
            #if defined(__MAIN_PROCESSOR)
                rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_MASTER, &u32MsgRcvStatus);
            #else
                rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_SLAVE, &u32MsgRcvStatus);
            #endif
            if ((u32MsgRcvStatus == 0xFFFFEEEE) || (u32MsgRcvStatus == 0xFFFFFFFF))
            {
                rom_hw_sys_ctrl_release_device(u8LockRcvStatus);
            }
            else
            {
                break;
            }
        }

        // This delay is necessary. If no delay is added here, it will result in an error.
        rom_delay_ms(1); 

        u8Timeout++;
        if (u8Timeout > IPC_SEND_TIMEOUT_MS)
        {
            #if defined(__MAIN_PROCESSOR)
                rom_hw_sys_ctrl_get_sw_int_flag(SYS_CTRL_CP, &u8IntFlag);
                rom_hw_sys_ctrl_clear_sw_int_flag(SYS_CTRL_CP, u8IntFlag);
            #else
                rom_hw_sys_ctrl_get_sw_int_flag(SYS_CTRL_MP, &u8IntFlag);
                rom_hw_sys_ctrl_clear_sw_int_flag(SYS_CTRL_MP, u8IntFlag);
            #endif

            PRINTF("The operation timed out!\n");
            return ERR_STA_BUSY;
        }
    }

#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_MASTER, 0xFFFFEEEE);
#else
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_SLAVE, 0xFFFFEEEE);
#endif

    rom_hw_sys_ctrl_release_device(u8LockRcvStatus);

    return u32MsgRcvStatus;
}

/**
 * @brief  IPC Send Message by Non-Blocking. This API Can Call in IRQ Handler.
 * @param  pu8Data: Data of Message.
 * @param  u32DataLen: Data Length of Message.
 * @return HW status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ipc_general_send_msg_nonblocking(uint8_t *pu8Data, uint32_t u32DataLen)
{
    uint8_t u8LockId;
    stIpcMsg_t stMsg;

    if (NULL == m_pIpcTxMsgQueueId)
    {
        return ERR_PARA_ERR;
    }

    if ((NULL == pu8Data) && (0 != u32DataLen))
    {
        return ERR_PARA_ERR;
    }

    if (u32DataLen > m_stIpcInit.u32MsgSize)
    {
        return ERR_PARA_ERR;
    }

#if defined(__MAIN_PROCESSOR)
    u8LockId = SYS_CTRL_LOCK_ID_IPC_MASTER;
#else
    u8LockId = SYS_CTRL_LOCK_ID_IPC_SLAVE;
#endif

    if (rom_hw_sys_ctrl_lock_device(u8LockId))
    {
        return ERR_STA_BUSY;
    }

    memcpy(m_au8TxTempBuf, &u32DataLen, sizeof(uint32_t));
    memcpy(&m_au8TxTempBuf[sizeof(uint32_t)], pu8Data, u32DataLen);
    if (QUEUE_STA_OK != msg_queue_push(m_pIpcTxMsgQueueId, m_au8TxTempBuf))
    {
        rom_hw_sys_ctrl_release_device(u8LockId);
        return ERR_STA_BUSY;
    }
    rom_hw_sys_ctrl_release_device(u8LockId);

    ipc_general_trig_int();

    return ERR_STA_OK;
}

