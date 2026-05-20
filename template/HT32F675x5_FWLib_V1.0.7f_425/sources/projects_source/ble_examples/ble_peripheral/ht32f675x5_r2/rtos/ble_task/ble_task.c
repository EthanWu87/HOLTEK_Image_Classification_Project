/*************************************************************************************************************
 * @file    ble_task.c
 * @version V1.0
 * @date    2022-02-13
 * @brief   ble_peripheral ble task
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

#include "RegHT32F675x5.h"
#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "llc_llp_interface.h"
#include "llc_spec_5_1.h"
#include "llc_scheduler.h"
#include "llc_acl_data.h"
#include "llc_data_channel_pdu.h"
#include "llc.h"
#include "llc_data.h"
#include "llc_ctrl_procedure.h"
#include "llc_connection_role.h"

#include "bluetooth.h"
#include "host_stack_conn_hdl.h"
#include "host_interface.h"
#include "encrypt.h"
#include "ble_task.h"
#include "ble_callback.h"
#include "hci.h"

#include "app_cfg.h"
#include "mlog.h"


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define LLC_TASK_MSG_COUNT                 ( 64 )
#define BLE_STACK_MSG_COUNT                ( 64 )

#define STACK_MSG_BUFFER_SIZE_SHORT        ( 36 )
#define STACK_MSG_BUFFER_SIZE_LONG         ( 128 )
#define STACK_MSG_BUFFER_SHORT_NUM         ( 16 )
#define STACK_MSG_BUFFER_LONG_NUM          ( 8 )


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef struct
{
    uint8_t u8Buf[STACK_MSG_BUFFER_SIZE_SHORT];

} stStackMsgShortBuf_t;

typedef struct
{
    uint8_t u8Buf[STACK_MSG_BUFFER_SIZE_LONG];

} stStackMsgLongBuf_t;


//=====================================================================================================================
// LOCAL VARIABLES
//=====================================================================================================================
static uint32_t llcTaskCb[osRtxThreadCbSize / 4U] __attribute__((aligned(4)));
static uint64_t llcTaskStack[1024 / 8U];
osThreadId_t llcTaskId;

osMessageQueueId_t llcTaskMsgQueueId;
static uint32_t llcTaskMsgQueueCb[osRtxMessageQueueCbSize / 4U];
static uint32_t llcTaskMsgQueueMem[osRtxMessageQueueMemSize(LLC_TASK_MSG_COUNT, sizeof(stLlcTaskMsg_t)) / 4U];

osMemoryPoolId_t stack_msg_buffer_short_MemPool; // memory pool id
osMemoryPoolId_t stack_msg_buffer_long_MemPool;  // memory pool id

static uint32_t bleStackTask_PoolCbMem_short[osRtxMemoryPoolCbSize / sizeof(uint32_t)] __attribute__((section(".bss.os.mempool.cb")));
static uint32_t bleStackTask_PoolMem_short[osRtxMemoryPoolMemSize(STACK_MSG_BUFFER_SHORT_NUM, sizeof(stStackMsgShortBuf_t)) / sizeof(uint32_t)];
static uint32_t bleStackTask_PoolCbMem_long[osRtxMemoryPoolCbSize / sizeof(uint32_t)] __attribute__((section(".bss.os.mempool.cb")));
static uint32_t bleStackTask_PoolMem_long[osRtxMemoryPoolMemSize(STACK_MSG_BUFFER_LONG_NUM, sizeof(stStackMsgLongBuf_t)) / sizeof(uint32_t)];

const osMemoryPoolAttr_t bleStackTask_MemPool_short_attr =
{
    .name = "bleStackTask_MemPool_short",
    .attr_bits = 0,
    .cb_mem = &bleStackTask_PoolCbMem_short,
    .cb_size = sizeof(bleStackTask_PoolCbMem_short),
    .mp_mem = &bleStackTask_PoolMem_short,
    .mp_size = sizeof(bleStackTask_PoolMem_short),
};

const osMemoryPoolAttr_t bleStackTask_MemPool_long_attr =
{
    .name = "bleStackTask_MemPool_long",
    .attr_bits = 0,
    .cb_mem = &bleStackTask_PoolCbMem_long,
    .cb_size = sizeof(bleStackTask_PoolCbMem_long),
    .mp_mem = &bleStackTask_PoolMem_long,
    .mp_size = sizeof(bleStackTask_PoolMem_long),
};

static uint32_t bleStackTaskCb[osRtxThreadCbSize / 4U] __attribute__((aligned(4)));
static uint64_t bleStackTaskStack[1024 / 8U];
osThreadId_t bleStackTaskId;

osMessageQueueId_t bleStackTaskMsgQueueId;
static uint32_t bleStackTaskMsgQueueCb[osRtxMessageQueueCbSize / 4U];
static uint32_t bleStackTaskMsgQueueMem[osRtxMessageQueueMemSize(BLE_STACK_MSG_COUNT, sizeof(stack_msg_st)) / 4U];

//=====================================================================================================================
// LOCAL VARIABLES
//=====================================================================================================================
extern void rom_st_ctrl_task_handler(stack_msg_st *pmsg);




/**
 * @brief  llc task
 * @param  None.
 * @return None.
 */
static void llc_task(void *argument)
{
    stLlcTaskMsg_t stLlcTaskMsg;
    osStatus_t status;

    for (;;)
    {
        status = osMessageQueueGet(llcTaskMsgQueueId, &stLlcTaskMsg, NULL, osWaitForever);

        if (osOK == status)
        {
            rom_llc_on_llc_task_received_msg(stLlcTaskMsg);
        }
        else
        {
            PRINTF("llc_task get msg failed:%u\n", status);
        }
    }
}

/**
 * @brief
 * @param  None.
 * @return None.
 */
static bool ble_task_send_msg_to_llc_task(stLlcTaskMsg_t stLlcTaskMsg)
{
    uint32_t u32Timeout = osWaitForever;

    if (__get_IPSR())
    {
        // in interrupt
        u32Timeout = 0;
    }

    osStatus_t status = osMessageQueuePut(llcTaskMsgQueueId, &stLlcTaskMsg, 0, u32Timeout);

    if (osOK == status)
    {
        return true;
    }
    else
    {
        PRINTF("ble_task_send_msg_to_llc_task failed:%u\n", status);

        return false;
    }
}

/**
 * @brief  ble task init.
 */
void ble_task_init(void)
{
    const osMessageQueueAttr_t llc_task_msg_queue_attr =
    {
        .name = "llc_task_msg_queue",
        .attr_bits = 0,
        .cb_mem = llcTaskMsgQueueCb,
        .cb_size = sizeof(llcTaskMsgQueueCb),
        .mq_mem = llcTaskMsgQueueMem,
        .mq_size = sizeof(llcTaskMsgQueueMem),
    };

    llcTaskMsgQueueId = osMessageQueueNew(LLC_TASK_MSG_COUNT, sizeof(stLlcTaskMsg_t), &llc_task_msg_queue_attr);

    if (NULL == llcTaskMsgQueueId)
    {
        PRINTF("llcTaskMsgQueueId NULL\n");
        return;
    }

    const osThreadAttr_t llc_task_attr =
    {
        .name = "llc_task",
        .attr_bits = osThreadJoinable,
        .cb_mem = &llcTaskCb,
        .cb_size = sizeof(llcTaskCb),
        .stack_mem = llcTaskStack,
        .stack_size = sizeof(llcTaskStack),
        .priority = osPriorityAboveNormal,
    };

    llcTaskId = osThreadNew(llc_task, NULL, &llc_task_attr);

    if (NULL == llcTaskId)
    {
        PRINTF("llcTaskId NULL\n");
        return;
    }

    rom_llc_set_send_msg_to_llc_task_callback(ble_task_send_msg_to_llc_task);
}

/**
 * @brief
 */
static void bleStack_task_init_MemPool(void)
{
    stack_msg_buffer_short_MemPool = osMemoryPoolNew(STACK_MSG_BUFFER_SHORT_NUM, sizeof(stStackMsgShortBuf_t), &bleStackTask_MemPool_short_attr);
    if (stack_msg_buffer_short_MemPool == NULL)
    {
        MLOG0E(0x6000, "stack_msg_buffer_short_MemPool alloc fail"); // MemPool object not created, handle failure
    }

    stack_msg_buffer_long_MemPool = osMemoryPoolNew(STACK_MSG_BUFFER_LONG_NUM, sizeof(stStackMsgLongBuf_t), &bleStackTask_MemPool_long_attr);
    if (stack_msg_buffer_long_MemPool == NULL)
    {
        MLOG0E(0x6001, "stack_msg_buffer_short_MemPool alloc fail"); // MemPool object not created, handle failure
    }
}

/**
 * @brief  ble task init
 * @param  None.
 */
static void bleStack_task(void *argument)
{
    stack_msg_st st_msg;
    osStatus_t status;

    for (;;)
    {
        status = osMessageQueueGet(bleStackTaskMsgQueueId, &st_msg, NULL, osWaitForever);

        if (osOK == status)
        {
            // MLOGD(0x6206,"bleStack_task u16Msg=0x%x",u16Msg);
            rom_st_ctrl_task_handler(&st_msg);

            if (st_msg.p_ext_info)
            {
                osMemoryPoolId_t pdataPoolId = (osMemoryPoolId_t)st_msg.dataPoolId;
                if (NULL != pdataPoolId)
                {
                    osMemoryPoolFree(pdataPoolId, st_msg.p_ext_info);
                }
                else
                {
                    MLOG0E(0x6002, "osMemoryPoolFree error st_msg.dataPoolId==NULL ");
                }
            }
        }
        else
        {
            MLOGE(0x6003, "bleStack_task get msg failed:%u\n", status);
        }
    }
}

/**
 * @brief  ble task init
 * @param  None.
 * @return None.
 */
static bool send_msg_to_bleStackTask(uint8_t module_type, uint16_t conn_handle, uint8_t len, uint8_t *pdata)
{
    uint32_t u32Timeout = osWaitForever;
    stack_msg_st st_msg;

    if (__get_IPSR())
    {
        // in interrupt
        u32Timeout = 0;
    }

    st_msg.conn_handle = conn_handle;
    st_msg.module_type = module_type;
    st_msg.p_ext_info = NULL;
    st_msg.len_of_ext_info = len;

    if (len == 0)
    {
    }
    else if (len <= STACK_MSG_BUFFER_SIZE_SHORT)
    {
        st_msg.p_ext_info = (stStackMsgShortBuf_t *)osMemoryPoolAlloc(stack_msg_buffer_short_MemPool, 0U); // get Mem Block

        if (st_msg.p_ext_info == NULL)
        {
            st_msg.p_ext_info = (stStackMsgLongBuf_t *)osMemoryPoolAlloc(stack_msg_buffer_long_MemPool, 0U); // get Mem Block
            if (st_msg.p_ext_info == NULL)
            {
                MLOG0E(0x6004, "stack_msg_buffer_short_MemPool and stack_msg_buffer_long_MemPool alloc failed ");
                return false;
            }
            st_msg.dataPoolId = stack_msg_buffer_long_MemPool;
        }
        else
        {

            st_msg.dataPoolId = stack_msg_buffer_short_MemPool;
        }
        memcpy(st_msg.p_ext_info, pdata, len);
    }
    else if (len <= STACK_MSG_BUFFER_SIZE_LONG)
    {
        st_msg.p_ext_info = (stStackMsgLongBuf_t *)osMemoryPoolAlloc(stack_msg_buffer_long_MemPool, 0U); // get Mem Block

        if (st_msg.p_ext_info == NULL)
        {
            MLOG0E(0x6005, "stack_msg_buffer_long_MemPool alloc failed ");
            return false;
        }
        st_msg.dataPoolId = stack_msg_buffer_long_MemPool;
        memcpy(st_msg.p_ext_info, pdata, len);
    }
    else
    {
        MLOGE(0x6006, " ext info too long alloc failed len=%d", len);
        return false;
    }

    MLOGD(0x6007, "send_msg_to_bleStackTask module_type=0x%x", module_type);
    osStatus_t status = osMessageQueuePut(bleStackTaskMsgQueueId, &st_msg, 0, u32Timeout);
    if (osOK == status)
    {
        return true;
    }
    else
    {
        MLOGE(0x6008, "bleStackTaskMsgQueueId failed:%u\n", status);
        return false;
    }
}

/**
 * @brief  ble task init
 */
static void bleStackTask_init(void)
{
    const osMessageQueueAttr_t bleStackTask_msg_queue_attr =
    {
        .name = "bleStack_msg_queue",
        .attr_bits = 0,
        .cb_mem = bleStackTaskMsgQueueCb,
        .cb_size = sizeof(bleStackTaskMsgQueueCb),
        .mq_mem = bleStackTaskMsgQueueMem,
        .mq_size = sizeof(bleStackTaskMsgQueueMem),
    };

    bleStack_task_init_MemPool();
    bleStackTaskMsgQueueId = osMessageQueueNew(BLE_STACK_MSG_COUNT, sizeof(stack_msg_st), &bleStackTask_msg_queue_attr);

    if (NULL == bleStackTaskMsgQueueId)
    {
        PRINTF("bleStackTask bleStackTaskMsgQueueIdNULL\n");
        return;
    }

    const osThreadAttr_t bleStackTask_task_attr =
    {
        .name = "bleStackTask",
        .attr_bits = osThreadJoinable,
        .cb_mem = &bleStackTaskCb,
        .cb_size = sizeof(bleStackTaskCb),
        .stack_mem = bleStackTaskStack,
        .stack_size = sizeof(bleStackTaskStack),
        .priority = osPriorityNormal,
    };

    bleStackTaskId = osThreadNew(bleStack_task, NULL, &bleStackTask_task_attr);
    if (NULL == bleStackTaskId)
    {
        MLOG0E(0x6009, "bleStackTask NULL\n");
        return;
    }

    rom_host_interface_set_hci_event_parameter_max_length(STACK_MSG_BUFFER_SIZE_LONG);
    ble_callback_set_send_msg_to_stack_task_callback(send_msg_to_bleStackTask);
}

#if 0
//======================
osThreadId_t encryptTaskId;
uint32_t encryptTaskCb[osRtxThreadCbSize / 4U] __attribute__ ( ( aligned ( 4 ), section ( ".bss.os.thread.cb" ) ) );
uint64_t      encryptTaskStack[1024 / 8U];

#define ENCRYPT_MSG_COUNT (16)
osMessageQueueId_t encryptTaskMsgQueueId;
uint32_t encryptTaskMsgQueueCb[osRtxMessageQueueCbSize / 4U];
uint32_t encryptTaskMsgQueueMem[osRtxMessageQueueMemSize ( ENCRYPT_MSG_COUNT, sizeof ( aes128_msg_st ) ) / 4U];


void encrypt_task ( void *argument )
{
    aes128_msg_st msg;
    osStatus_t status;
    for ( ;; )
    {
        status = osMessageQueueGet ( encryptTaskMsgQueueId, &msg, NULL, osWaitForever );
        if ( osOK == status )
        {
            encrypt_task_handler ( &msg );
        }
        else
        {
            MLOGE ( 0x600a, "encrypt_task get msg failed:%u\n", status );
        }
    }
}

bool send_msg_to_encryptTask ( uint8_t module_type, uint8_t idx, uint8_t *key, uint8_t *plaintext )
{
    uint32_t u32Timeout = osWaitForever;
    aes128_msg_st msg;
    msg.role_idx = idx;
    msg.module_type = module_type;
    memcpy ( msg.plaintext, plaintext, 16 );
    memcpy ( msg.key, key, 16 );
    if ( __get_IPSR() )
    {
        //in interrupt
        u32Timeout = 0;
    }

    osStatus_t status = osMessageQueuePut ( encryptTaskMsgQueueId, &msg, 0, u32Timeout );
    if ( osOK == status )
    {
        return true;
    }
    else
    {
        MLOGE ( 0x600b, "send_msg_to_encryptTask failed:%u\n", status );
        return false;
    }
}


void encryptTask_init ( void )
{
    const osMessageQueueAttr_t encryptTask_msg_queue_attr =
    {
        .name = "encrypt_msg_queue",
        .attr_bits = 0,
        .cb_mem = encryptTaskMsgQueueCb,
        .cb_size = sizeof ( encryptTaskMsgQueueCb ),
        .mq_mem = encryptTaskMsgQueueMem,
        .mq_size = sizeof ( encryptTaskMsgQueueMem ),
    };

    encryptTaskMsgQueueId = osMessageQueueNew ( ENCRYPT_MSG_COUNT, sizeof ( aes128_msg_st ), &encryptTask_msg_queue_attr );
    if ( NULL == encryptTaskMsgQueueId )
    {
        MLOG0E ( 0x600c, "encryptTask encryptTaskMsgQueueIdNULL\n" );
        return;
    }

    const osThreadAttr_t encryptTask_task_attr =
    {
        .name = "encryptTask",
        .attr_bits = osThreadJoinable,
        .cb_mem = &encryptTaskCb,
        .cb_size = sizeof ( encryptTaskCb ),
        .stack_mem = encryptTaskStack,
        .stack_size = sizeof ( encryptTaskStack ),
        .priority = osPriorityNormal,
    };
    encryptTaskId = osThreadNew ( encrypt_task, NULL, &encryptTask_task_attr );
    if ( NULL == encryptTaskId )
    {
        MLOG0E ( 0x600d, "encryptTask NULL\n" );
        return;
    }

    ble_callback_set_send_msg_to_encrypt_task_callback ( send_msg_to_encryptTask );

}
#endif

/**
 * @brief  Creat ble_llc & ble_stack & encrypt task.
 * @return int, ref@int
 */
int ble_stack_task_init(void)
{
    bleStackTask_init();

    // encryptTask_init ();

    return 0;
}


