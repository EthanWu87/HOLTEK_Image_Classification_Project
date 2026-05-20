/*************************************************************************************************************
 * @file    ble_host_init.c
 * @version V1.0
 * @date    2023-05-26
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


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "app_cfg.h"
#include "ble_config.h"

#include "mlog.h"

#include "err_def.h"
#include "app_timer.h"

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "bluetooth.h"
#include "host_stack_conn_hdl.h"
#include "host_interface.h"
#include "host_stack_mem.h"

#include "gatt_client_api.h"
#include "ble_gatt_service.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"

#include "gap_api.h"
#include "ble_gap_service.h"

#include "ble_callback.h"

/**
 * @brief  DEFINE.
 */
#undef PRINTF
#define PRINTF(fmt, args...)

#define CTRL_POOL_SIZE          (360 * (CONNECTION_ROLE_NUM))

#define STACK_SHORT_BUFFER_SIZE (40)
#define STACK_SHORT_BUFFER_NUM  (16)
#define STACK_LONG_BUFFER_SIZE  (256)
#define STACK_LONG_BUFFER_NUM   (8)
#define STACK_DATA_POOL_SIZE                                   \
    (((STACK_SHORT_BUFFER_SIZE + 24) * STACK_SHORT_BUFFER_NUM) \
     + ((STACK_LONG_BUFFER_SIZE + 24) * STACK_LONG_BUFFER_NUM))

#define GATTS_SERV_SUPPORT_MAX_IN_STACK (16)
#define BLE_STACK_MSG_COUNT             (64)
#define STACK_MSG_BUFFER_SIZE_SHORT     (36)
#define STACK_MSG_BUFFER_SIZE_LONG      (128)
#define STACK_MSG_BUFFER_SHORT_NUM      (16)
#define STACK_MSG_BUFFER_LONG_NUM       (8)

/**
 * @brief  TYPEDEF.
 */
typedef struct
{
    uint8_t u8Buf[STACK_MSG_BUFFER_SIZE_SHORT];

} stStackMsgShortBuf_t;

typedef struct
{
    uint8_t u8Buf[STACK_MSG_BUFFER_SIZE_LONG];

} stStackMsgLongBuf_t;

/**
 * @brief  Local variables.
 */
static uint8_t m_u8CtrlPool[CTRL_POOL_SIZE] __attribute__((aligned(8)))            = {0};
static uint8_t m_u8StackDataPool[STACK_DATA_POOL_SIZE] __attribute__((aligned(8))) = {0};
static uint8_t m_u8ProfileBuf[PROFILE_BUF_SIZE] __attribute__((aligned(4)))        = {0};

static gatts_serv_info_st m_stGattsServInfo[GATTS_SERV_SUPPORT_MAX_IN_STACK] __attribute__((aligned(4))) = {0};

static stAppTimerNode_t g_appTimerNode[(CONNECTION_ROLE_NUM)*2];

static osMemoryPoolId_t m_pMemPoolShort; // memory pool id
static osMemoryPoolId_t m_pMemPoolLong;  // memory pool id

static uint32_t m_au32PoolCbMemShort[osRtxMemoryPoolCbSize / sizeof(uint32_t)]
    __attribute__((section(".bss.os.mempool.cb")));

static uint32_t m_au32PoolMemShort[osRtxMemoryPoolMemSize(STACK_MSG_BUFFER_SHORT_NUM, sizeof(stStackMsgShortBuf_t))
                                   / sizeof(uint32_t)];

static uint32_t m_au32PoolCbMemLong[osRtxMemoryPoolCbSize / sizeof(uint32_t)]
    __attribute__((section(".bss.os.mempool.cb")));

static uint32_t m_au32PoolMemLong[osRtxMemoryPoolMemSize(STACK_MSG_BUFFER_LONG_NUM, sizeof(stStackMsgLongBuf_t))
                                  / sizeof(uint32_t)];

static uint32_t bleStackTaskCb[osRtxThreadCbSize / 4U] __attribute__((aligned(4)));
static uint64_t bleStackTaskStack[(HOST_TASK_STACK_SIZE) / 8U];
osThreadId_t    bleStackTaskId;

osMessageQueueId_t bleStackTaskMsgQueueId;
static uint32_t    bleStackTaskMsgQueueCb[osRtxMessageQueueCbSize / 4U];
static uint32_t    bleStackTaskMsgQueueMem[osRtxMessageQueueMemSize(BLE_STACK_MSG_COUNT, sizeof(stack_msg_st)) / 4U];

/**
 * @brief  Extern functions.
 */
extern void rom_st_ctrl_task_handler(stack_msg_st *pmsg);

/**
 * @brief
 */
static bool bleStack_task_init_MemPool(void)
{
    const osMemoryPoolAttr_t MemPoolShortAttr = {
        .name      = "bleStackTask_MemPool_short",
        .attr_bits = 0,
        .cb_mem    = &m_au32PoolCbMemShort,
        .cb_size   = sizeof(m_au32PoolCbMemShort),
        .mp_mem    = &m_au32PoolMemShort,
        .mp_size   = sizeof(m_au32PoolMemShort),
    };

    m_pMemPoolShort = osMemoryPoolNew(STACK_MSG_BUFFER_SHORT_NUM, sizeof(stStackMsgShortBuf_t), &MemPoolShortAttr);
    if (m_pMemPoolShort == NULL)
    {
        MLOG0E(0x6000, "m_pMemPoolShort alloc fail"); // MemPool object not created, handle failure
        PRINTF("m_pMemPoolShort alloc fail\n");
        return false;
    }

    const osMemoryPoolAttr_t MemPoolLongAttr = {
        .name      = "bleStackTask_MemPool_long",
        .attr_bits = 0,
        .cb_mem    = &m_au32PoolCbMemLong,
        .cb_size   = sizeof(m_au32PoolCbMemLong),
        .mp_mem    = &m_au32PoolMemLong,
        .mp_size   = sizeof(m_au32PoolMemLong),
    };

    m_pMemPoolLong = osMemoryPoolNew(STACK_MSG_BUFFER_LONG_NUM, sizeof(stStackMsgLongBuf_t), &MemPoolLongAttr);
    if (m_pMemPoolLong == NULL)
    {
        MLOG0E(0x6001, "m_pMemPoolShort alloc fail"); // MemPool object not created, handle failure
        PRINTF("m_pMemPoolShort alloc fail\n");
        return false;
    }

    return true;
}

/**
 * @brief  ble task init
 * @param  None.
 */
static void bleStack_task(void *argument)
{
    stack_msg_st stMsg;
    osStatus_t   status;

    for (;;)
    {
        status = osMessageQueueGet(bleStackTaskMsgQueueId, &stMsg, NULL, osWaitForever);

        if (osOK == status)
        {
            // MLOGD(0x6206,"bleStack_task u16Msg=0x%x",u16Msg);
            rom_st_ctrl_task_handler(&stMsg);

            if (stMsg.p_ext_info)
            {
                osMemoryPoolId_t pdataPoolId = (osMemoryPoolId_t)stMsg.dataPoolId;
                if (NULL != pdataPoolId)
                {
                    osMemoryPoolFree(pdataPoolId, stMsg.p_ext_info);
                }
                else
                {
                    MLOG0E(0x6002, "osMemoryPoolFree error stMsg.dataPoolId==NULL ");
                    PRINTF("osMemoryPoolFree error stMsg.dataPoolId==NULL\n");
                }
            }
        }
        else
        {
            MLOGE(0x6003, "bleStack_task get msg failed:%u\n", status);
            PRINTF("bleStack_task get msg failed: %u\n", status);
        }
    }
}

/**
 * @brief
 * @param  module_type
 * @param  conn_handle
 * @param  len
 * @param  pdata
 * @return
 * @return
 */
static bool send_msg_to_bleStackTask(uint8_t module_type, uint16_t conn_handle, uint8_t len, uint8_t *pdata)
{
    uint32_t     u32Timeout = osWaitForever;
    stack_msg_st stMsg;

    if (__get_IPSR())
    {
        // in interrupt
        u32Timeout = 0;
    }

    stMsg.conn_handle     = conn_handle;
    stMsg.module_type     = module_type;
    stMsg.p_ext_info      = NULL;
    stMsg.len_of_ext_info = len;

    if (len == 0)
    {
    }
    else if (len <= STACK_MSG_BUFFER_SIZE_SHORT)
    {
        stMsg.p_ext_info = (stStackMsgShortBuf_t *)osMemoryPoolAlloc(m_pMemPoolShort, 0U); // get Mem Block

        if (stMsg.p_ext_info == NULL)
        {
            stMsg.p_ext_info = (stStackMsgLongBuf_t *)osMemoryPoolAlloc(m_pMemPoolLong, 0U); // get Mem Block
            if (stMsg.p_ext_info == NULL)
            {
                MLOG0E(0x6004, "m_pMemPoolShort and m_pMemPoolLong alloc failed ");
                PRINTF("m_pMemPoolShort and m_pMemPoolLong alloc failed\n");
                return false;
            }
            stMsg.dataPoolId = m_pMemPoolLong;
        }
        else
        {

            stMsg.dataPoolId = m_pMemPoolShort;
        }
        memcpy(stMsg.p_ext_info, pdata, len);
    }
    else if (len <= STACK_MSG_BUFFER_SIZE_LONG)
    {
        stMsg.p_ext_info = (stStackMsgLongBuf_t *)osMemoryPoolAlloc(m_pMemPoolLong, 0U); // get Mem Block

        if (stMsg.p_ext_info == NULL)
        {
            MLOG0E(0x6005, "m_pMemPoolLong alloc failed ");
            PRINTF("m_pMemPoolLong alloc failed\n");
            return false;
        }
        stMsg.dataPoolId = m_pMemPoolLong;
        memcpy(stMsg.p_ext_info, pdata, len);
    }
    else
    {
        MLOGE(0x6006, " ext info too long alloc failed len=%d", len);
        PRINTF(" ext info too long alloc failed len=%d\n", len);
        return false;
    }

    MLOGD(0x6007, "send_msg_to_bleStackTask module_type=0x%x", module_type);
    osStatus_t status = osMessageQueuePut(bleStackTaskMsgQueueId, &stMsg, 0, u32Timeout);
    if (osOK == status)
    {
        return true;
    }
    else
    {
        MLOGE(0x6008, "bleStackTaskMsgQueueId failed:%u\n", status);
        PRINTF("bleStackTaskMsgQueueId failed: %u\n", status);
        return false;
    }
}

/**
 * @brief  ble task init
 */
static bool bleStackTask_init(void)
{
    const osMessageQueueAttr_t bleStackTask_msg_queue_attr = {
        .name      = "bleStack_msg_queue",
        .attr_bits = 0,
        .cb_mem    = bleStackTaskMsgQueueCb,
        .cb_size   = sizeof(bleStackTaskMsgQueueCb),
        .mq_mem    = bleStackTaskMsgQueueMem,
        .mq_size   = sizeof(bleStackTaskMsgQueueMem),
    };

    bleStack_task_init_MemPool();
    bleStackTaskMsgQueueId = osMessageQueueNew(BLE_STACK_MSG_COUNT, sizeof(stack_msg_st), &bleStackTask_msg_queue_attr);

    if (NULL == bleStackTaskMsgQueueId)
    {
        PRINTF("bleStackTask bleStackTaskMsgQueueIdNULL\n");
        return false;
    }

    const osThreadAttr_t bleStackTask_task_attr = {
        .name       = "bleStackTask",
        .attr_bits  = osThreadJoinable,
        .cb_mem     = &bleStackTaskCb,
        .cb_size    = sizeof(bleStackTaskCb),
        .stack_mem  = bleStackTaskStack,
        .stack_size = sizeof(bleStackTaskStack),
        .priority   = osPriorityAboveNormal,
    };

    bleStackTaskId = osThreadNew(bleStack_task, NULL, &bleStackTask_task_attr);
    if (NULL == bleStackTaskId)
    {
        MLOG0E(0x6009, "bleStackTask NULL\n");
        return false;
    }

    rom_host_interface_set_hci_event_parameter_max_length(STACK_MSG_BUFFER_SIZE_LONG);
    ble_callback_set_send_msg_to_stack_task_callback(send_msg_to_bleStackTask);

    return true;
}

/**
 * @brief  Create a timer.
 * @param  pstTimer: If create the timer successed, this point will save the new timer id.
 * @param  enMode: Work mode, @ref EN_APP_TIMER_MODE_T.
 * @param  pfnHandler: Function to be executed when the timer expires.
 * @return Status: true - success, false - fail.
 */
static bool ble_app_timer_create(void *pTimerHandle, void *pTimeOutHandler)
{
    return (ERR_STA_OK == app_timer_create((stAppTimerNode_t *)pTimerHandle, APP_TIMER_MODE_ONCE, pTimeOutHandler));
}

/**
 * @brief  Start the timer.
 * @param  pstTimer: Point that the timer should be initialized.
 * @param  u32Time: timer out value unit ms, 0~131072000ms   140737488.
 * @param  pContext: point to the parameter when the timerout happened will send to the timerout handler.
 * @return Status: true - success, false - fail.
 */
static bool ble_app_timer_start(void *pTimerHandle, uint32_t u32TimeOutMs, void *pContext)
{
    return (ERR_STA_OK == app_timer_start((stAppTimerNode_t *)pTimerHandle, u32TimeOutMs, pContext));
}

/**
 * @brief  Stop a specified timer.
 * @param  pstTimer: point to the timer will be stop.
 * @return Status: true - success, false - fail.
 */
static bool ble_app_timer_stop(void *pTimerHandle)
{
    return (ERR_STA_OK == app_timer_stop((stAppTimerNode_t *)pTimerHandle));
}

/**
 * @brief  Stop one timer. after this, the timer can be restart
 * @param  pstTimer: point to the timer will be stop.
 * @return Status: true - success, false - fail.
 */
static bool ble_app_timer_delete(void *pTimerHandle)
{
    return (ERR_STA_OK == app_timer_delete((stAppTimerNode_t *)pTimerHandle));
}

bool ble_host_init(void)
{
    patch_gatts_api_init(m_u8ProfileBuf, PROFILE_BUF_SIZE, m_stGattsServInfo, GATTS_SERV_SUPPORT_MAX_IN_STACK);

    if (!bleStackTask_init())
    {
        PRINTF("bleStackTask_init error.\n");
        return false;
    }

    rom_ble_host_stack_mem_init((CONNECTION_ROLE_NUM), STACK_SHORT_BUFFER_NUM, STACK_SHORT_BUFFER_SIZE,
                                STACK_LONG_BUFFER_NUM, STACK_LONG_BUFFER_SIZE);
    rom_host_stack_mem_ctrl_init(m_u8CtrlPool, CTRL_POOL_SIZE);
    rom_host_stack_mem_acl_data_mem_init(m_u8StackDataPool, STACK_DATA_POOL_SIZE);

    rom_ble_host_stack_timer_init((void *)&g_appTimerNode[0], (CONNECTION_ROLE_NUM)*2, sizeof(stAppTimerNode_t));
    rom_gap_api_sm_init();
    ble_callback_set_timer_create_callback(ble_app_timer_create);
    ble_callback_set_timer_start_callback(ble_app_timer_start);
    ble_callback_set_send_timer_stop_callback(ble_app_timer_stop);
    ble_callback_set_send_timer_delete_callback(ble_app_timer_delete);

    return true;
}