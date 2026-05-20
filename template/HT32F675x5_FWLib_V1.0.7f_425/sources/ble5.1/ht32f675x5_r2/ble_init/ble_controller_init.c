/*************************************************************************************************************
 * @file    ble_controller_init.c
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

#include "ble_config.h"
#include "app_cfg.h"
#include "err_def.h"

#include "llc_llp_interface.h"
#include "llc_spec_5_1.h"
#include "llc_adv_channel_pdu.h"
#include "llc_data_channel_pdu.h"
#include "llc_acl_data.h"
#include "llc_acl_data.h"
#include "llc_hci_command.h"
#include "llc_scheduler.h"
#include "llc_schedule_algorithm.h"
#include "llc_data.h"
#include "llc_ctrl_procedure.h"
#include "llc_connection_role.h"
#include "llc_master.h"
#include "llc_slave.h"
#include "llc_legacy_adv.h"
#include "llc_legacy_scan.h"
#include "llc_legacy_initiator.h"
#include "llc_ext_adv.h"
#include "llc_ext_scan.h"
#include "llc_ext_scan_duplicate_filter.h"
#include "llc_ext_initiator.h"
#include "llc_white_list.h"
#include "llc_privacy.h"
#include "llc.h"

#include "llp_hw.h"
#include "llp.h"
#include "llp_sleep.h"

#include "controller_interface.h"

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "ble_init.h"

////Check User Configuration
//=================
#if (WHITE_LIST_NUM > 6)
    #error "White List Capacity Error"
#endif

#if (RESOLVING_LIST_NUM > 2)
    #error "Resolving List Capacity Error"
#endif

#if (0 != (SHORT_ADV_CHANNEL_PDU_SIZE % 4)) || (0 != (LONG_ADV_CHANNEL_PDU_SIZE % 4)) \
    || (0 != (SHORT_DATA_CHANNEL_PDU_SIZE % 4)) || (0 != (LONG_DATA_CHANNEL_PDU_SIZE % 4))
    #error "PDU Size Error"
#endif

#if ((SHORT_ADV_CHANNEL_PDU_SIZE) > (LONG_ADV_CHANNEL_PDU_SIZE))
    #error "Advertising Channel PDU Payload Size Error"
#endif

#if ((SHORT_DATA_CHANNEL_PDU_SIZE) > (LONG_DATA_CHANNEL_PDU_SIZE))
    #error "Data Channel PDU Payload Size Error"
#endif
//=================

#define MAX_SCHEDULE_EVENT_NUM                                                                               \
    ((LEGACY_ADV_NUM) + (LEGACY_SCAN_ENABLE) + (LEGACY_INITIATOR_ENABLE) + (EXT_ADV_NUM) + (EXT_SCAN_ENABLE) \
     + (EXT_INITIATOR_ENABLE) + (CONNECTION_ROLE_NUM))

stLlcLegacyAdv_t g_pstLegacyAdvMemBuffer[LEGACY_ADV_NUM];

#if LEGACY_SCAN_ENABLE
stLlcLegacyScan_t g_pstLlcLegacyScanMemBuffer[1];
#endif

#if LEGACY_INITIATOR_ENABLE
stLlcLegacyInitiator_t g_pstLegacyInitiatorMemBuffer[1];
#endif

#if (EXT_ADV_NUM > 0)
stLlcExtAdv_t             g_pstExtAdvMemBuffer[EXT_ADV_NUM];
stLlcExtAdvPduExtraInfo_t g_pstExtAdvPduExtraInfoMemBuffer[SHORT_ADV_CHANNEL_PDU_NUM + LONG_ADV_CHANNEL_PDU_NUM];
#endif

#if EXT_SCAN_ENABLE
stLlcExtScan_t               g_pstExtScanMemBuffer[1];
stLlcExtScanPduExtraInfo_t   g_pstExtScanPduExtraInfoMemBuffer[SHORT_ADV_CHANNEL_PDU_NUM + LONG_ADV_CHANNEL_PDU_NUM];
stLlcExtScanAdvertisingSet_t g_pstExtScanAdvertisingSetMemBuffer[EXT_SCAN_ADVERTISING_SET_NUM];
stLlcExtScanDuplicateFilterReport_t g_pstExtScanDuplicateFilterReportMemBuffer[EXT_SCAN_DUPLICATE_REPORT_NUM];
#endif

#if EXT_INITIATOR_ENABLE
stLlcExtInitiator_t g_pstExtInitiatorMemBuffer[1];
stLlcExtInitiatorPduExtraInfo_t
    g_pstExtInitiatorPduExtraInfoMemBuffer[SHORT_ADV_CHANNEL_PDU_NUM + LONG_ADV_CHANNEL_PDU_NUM];
stLlcExtInitiatorAdvertisingSet_t g_pstExtInitiatorAdvertisingSetMemBuffer[EXT_INITIATOR_ADVERTISING_SET_NUM];
#endif

#if (CONNECTION_ROLE_NUM) > 0
stLlcConnectionRole_t g_pstConnectionRoleMem[CONNECTION_ROLE_NUM];
#endif

pstLlcSchedulerEvent_t g_pstSchedulerEventArrayBuffer[MAX_SCHEDULE_EVENT_NUM];
pstLlcSchedulerEvent_t g_pstSchedulerEventTempArrayBuffer[MAX_SCHEDULE_EVENT_NUM];

stLlcWhiteListDevice_t     g_pstWhiteListBuffer[WHITE_LIST_NUM];
stLlcResolvingListDevice_t g_pstResolvingListBuffer[RESOLVING_LIST_NUM];

#if (LEGACY_SCAN_ENABLE > 0) || (LEGACY_INITIATOR_ENABLE) || (EXT_ADV_NUM > 0) || (EXT_SCAN_ENABLE) \
    || (EXT_INITIATOR_ENABLE)
stLlcAdvChannelPdu_t g_pstLongAdvChannelPduMem[LONG_ADV_CHANNEL_PDU_NUM];
uint8_t              g_pu8LongAdvChannelPduPayloadMem[LONG_ADV_CHANNEL_PDU_NUM][LONG_ADV_CHANNEL_PDU_SIZE]
    __attribute__((aligned(4)));
stLlcAdvChannelPdu_t g_pstShortAdvChannelPduMem[SHORT_ADV_CHANNEL_PDU_NUM];
uint8_t              g_pu8ShortAdvChannelPduPayloadMem[SHORT_ADV_CHANNEL_PDU_NUM][SHORT_ADV_CHANNEL_PDU_SIZE]
    __attribute__((aligned(4)));
#endif

#if (CONNECTION_ROLE_NUM) > 0
stLlcDataChannelPdu_t g_pstLongTxDataChannelPduMem[LONG_TX_DATA_CHANNEL_PDU_NUM];
uint8_t g_pu8LongTxDataChannelPduPayloadMem[LONG_TX_DATA_CHANNEL_PDU_NUM][LONG_TX_DATA_CHANNEL_PDU_SIZE + 4]
    __attribute__((aligned(4))); //+4 for hw MIC
stLlcDataChannelPdu_t g_pstShortTxDataChannelPduMem[SHORT_TX_DATA_CHANNEL_PDU_NUM];
uint8_t g_pu8ShortTxDataChannelPduPayloadMem[SHORT_TX_DATA_CHANNEL_PDU_NUM][SHORT_TX_DATA_CHANNEL_PDU_SIZE + 4]
    __attribute__((aligned(4))); //+4 for hw MIC

stLlcDataChannelPdu_t g_pstLongRxDataChannelPduMem[LONG_RX_DATA_CHANNEL_PDU_NUM];
uint8_t g_pu8LongRxDataChannelPduPayloadMem[LONG_RX_DATA_CHANNEL_PDU_NUM][LONG_RX_DATA_CHANNEL_PDU_SIZE + 4]
    __attribute__((aligned(4))); //+4 for hw MIC
stLlcDataChannelPdu_t g_pstShortRxDataChannelPduMem[SHORT_RX_DATA_CHANNEL_PDU_NUM];
uint8_t g_pu8ShortRxDataChannelPduPayloadMem[SHORT_RX_DATA_CHANNEL_PDU_NUM][SHORT_RX_DATA_CHANNEL_PDU_SIZE + 4]
    __attribute__((aligned(4))); //+4 for hw MIC

stLlcAclData_t g_pstAclDataMem[ACL_DATA_NUM];
uint8_t        g_pu8AclDataPayloadMem[ACL_DATA_NUM][ACL_DATA_SIZE] __attribute__((aligned(4)));
#endif

stLlcHciCommand_t g_pstHciCommandMemBuffer[HCI_COMMAND_NUM];
uint8_t g_pu8HciCommandParametersBuffer[HCI_COMMAND_NUM][HCI_COMMAND_PARAMETERS_SIZE] __attribute__((aligned(4)));

static uint32_t llcTaskCb[osRtxThreadCbSize / 4U] __attribute__((aligned(4)));
static uint64_t llcTaskStack[(LLC_TASK_STACK_SIZE) / 8U];
osThreadId_t    llcTaskId;

osMessageQueueId_t llcTaskMsgQueueId;
static uint32_t    llcTaskMsgQueueCb[osRtxMessageQueueCbSize / 4U];
static uint32_t    llcTaskMsgQueueMem[osRtxMessageQueueMemSize(LLC_TASK_MSG_COUNT, sizeof(stLlcTaskMsg_t)) / 4U];

static bool controller_mem_init(void)
{
    uint32_t i;

//// legacy adv mem init
#if (LEGACY_ADV_NUM) > 0
    if (!rom_llc_legacy_adv_mem_init(g_pstLegacyAdvMemBuffer, LEGACY_ADV_NUM))
    {
        return false;
    }
#endif
////

//// legacy scan mem init
#if (LEGACY_SCAN_ENABLE)
    if (!rom_llc_legacy_scan_mem_init(g_pstLlcLegacyScanMemBuffer))
    {
        return false;
    }
#endif
////

//// legacy initiator mem init
#if (LEGACY_INITIATOR_ENABLE)
    if (!rom_llc_legacy_initiator_mem_init(g_pstLegacyInitiatorMemBuffer))
    {
        return false;
    }
#endif
////

//// ext adv mem init
#if (EXT_ADV_NUM) > 0
    if (!rom_llc_ext_adv_mem_init(g_pstExtAdvMemBuffer, sizeof(g_pstExtAdvMemBuffer) / sizeof(stLlcExtAdv_t),
                                  g_pstExtAdvPduExtraInfoMemBuffer,
                                  sizeof(g_pstExtAdvPduExtraInfoMemBuffer) / sizeof(stLlcExtAdvPduExtraInfo_t)))
    {
        return false;
    }
#endif
////

//// ext scan mem init
#if (EXT_SCAN_ENABLE)
    rom_llc_ext_scan_duplicate_filter_init(g_pstExtScanDuplicateFilterReportMemBuffer,
                                           sizeof(g_pstExtScanDuplicateFilterReportMemBuffer)
                                               / sizeof(stLlcExtScanDuplicateFilterReport_t));
    if (!rom_llc_ext_scan_mem_init(g_pstExtScanMemBuffer, g_pstExtScanPduExtraInfoMemBuffer,
                                   sizeof(g_pstExtScanPduExtraInfoMemBuffer) / sizeof(stLlcExtScanPduExtraInfo_t),
                                   g_pstExtScanAdvertisingSetMemBuffer,
                                   sizeof(g_pstExtScanAdvertisingSetMemBuffer) / sizeof(stLlcExtScanAdvertisingSet_t)))
    {
        return false;
    }
#endif
////

//// ext initiator mem init
#if (EXT_INITIATOR_ENABLE)
    if (!rom_llc_ext_initiator_mem_init(
            g_pstExtInitiatorMemBuffer, g_pstExtInitiatorPduExtraInfoMemBuffer,
            sizeof(g_pstExtInitiatorPduExtraInfoMemBuffer) / sizeof(stLlcExtInitiatorPduExtraInfo_t),
            g_pstExtInitiatorAdvertisingSetMemBuffer,
            sizeof(g_pstExtInitiatorAdvertisingSetMemBuffer) / sizeof(stLlcExtInitiatorAdvertisingSet_t)))
    {
        return false;
    }
#endif
////

//// connection role mem init
#if (CONNECTION_ROLE_NUM) > 0
    if (!rom_llc_connection_role_mem_init(g_pstConnectionRoleMem, CONNECTION_ROLE_NUM))
    {
        return false;
    }
#endif
    ////

    //// scheduler mem init
    if (!rom_llc_scheduler_mem_init(g_pstSchedulerEventArrayBuffer, sizeof(g_pstSchedulerEventArrayBuffer),
                                    g_pstSchedulerEventTempArrayBuffer, sizeof(g_pstSchedulerEventTempArrayBuffer),
                                    MAX_SCHEDULE_EVENT_NUM))
    {
        return false;
    }
    ////

    //// white list mem init
    if (!rom_llc_white_list_init(g_pstWhiteListBuffer, WHITE_LIST_NUM))
    {
        return false;
    }
    ////

    //// privacy mem init
    if (!rom_llc_privacy_init(g_pstResolvingListBuffer, RESOLVING_LIST_NUM))
    {
        return false;
    }
////

//// adv channel pdu mem init
#if (LEGACY_SCAN_ENABLE > 0) || (LEGACY_INITIATOR_ENABLE) || (EXT_ADV_NUM > 0) || (EXT_SCAN_ENABLE) \
    || (EXT_INITIATOR_ENABLE)
    for (i = 0; i < LONG_ADV_CHANNEL_PDU_NUM; i++)
    {
        g_pstLongAdvChannelPduMem[i].u16PayloadBufSize = LONG_ADV_CHANNEL_PDU_SIZE;
        g_pstLongAdvChannelPduMem[i].pu8Payload        = g_pu8LongAdvChannelPduPayloadMem[i];
    }
    for (i = 0; i < SHORT_ADV_CHANNEL_PDU_NUM; i++)
    {
        g_pstShortAdvChannelPduMem[i].u16PayloadBufSize = SHORT_ADV_CHANNEL_PDU_SIZE;
        g_pstShortAdvChannelPduMem[i].pu8Payload        = g_pu8ShortAdvChannelPduPayloadMem[i];
    }
    stLlcAdvChannelPduMemCfg_t stLlcAdvChannelPduMemCfg = {
        .pstLongAdvChannelPduMemBuffer   = g_pstLongAdvChannelPduMem,
        .u8LongAdvChannelPduNum          = LONG_ADV_CHANNEL_PDU_NUM,
        .u16LongAdvChannelPduPayloadSize = LONG_ADV_CHANNEL_PDU_SIZE,

        .pstShortAdvChannelPduMemBuffer   = g_pstShortAdvChannelPduMem,
        .u8ShortAdvChannelPduNum          = SHORT_ADV_CHANNEL_PDU_NUM,
        .u16ShortAdvChannelPduPayloadSize = SHORT_ADV_CHANNEL_PDU_SIZE,
    };
    if (!rom_llc_adv_channel_pdu_mem_init(&stLlcAdvChannelPduMemCfg))
    {
        return false;
    }
#endif
    ////

#if (CONNECTION_ROLE_NUM) > 0
    //// data channel pdu mem init
    for (i = 0; i < LONG_TX_DATA_CHANNEL_PDU_NUM; i++)
    {
        g_pstLongTxDataChannelPduMem[i].u16PayloadBufSize = LONG_TX_DATA_CHANNEL_PDU_SIZE;
        g_pstLongTxDataChannelPduMem[i].pu8Payload        = g_pu8LongTxDataChannelPduPayloadMem[i];
    }
    for (i = 0; i < SHORT_TX_DATA_CHANNEL_PDU_NUM; i++)
    {
        g_pstShortTxDataChannelPduMem[i].u16PayloadBufSize = SHORT_TX_DATA_CHANNEL_PDU_SIZE;
        g_pstShortTxDataChannelPduMem[i].pu8Payload        = g_pu8ShortTxDataChannelPduPayloadMem[i];
    }
    for (i = 0; i < LONG_RX_DATA_CHANNEL_PDU_NUM; i++)
    {
        g_pstLongRxDataChannelPduMem[i].u16PayloadBufSize = LONG_RX_DATA_CHANNEL_PDU_SIZE;
        g_pstLongRxDataChannelPduMem[i].pu8Payload        = g_pu8LongRxDataChannelPduPayloadMem[i];
    }
    for (i = 0; i < SHORT_RX_DATA_CHANNEL_PDU_NUM; i++)
    {
        g_pstShortRxDataChannelPduMem[i].u16PayloadBufSize = SHORT_RX_DATA_CHANNEL_PDU_SIZE;
        g_pstShortRxDataChannelPduMem[i].pu8Payload        = g_pu8ShortRxDataChannelPduPayloadMem[i];
    }

    stLlcDataChannelPduMemCfg_t stLlcDataChannelPduMemCfg = {
        .pstLongTxDataChannelPduMemBuffer   = g_pstLongTxDataChannelPduMem,
        .u8LongTxDataChannelPduNum          = LONG_TX_DATA_CHANNEL_PDU_NUM,
        .u16LongTxDataChannelPduPayloadSize = LONG_TX_DATA_CHANNEL_PDU_SIZE,

        .pstShortTxDataChannelPduMemBuffer   = g_pstShortTxDataChannelPduMem,
        .u8ShortTxDataChannelPduNum          = SHORT_TX_DATA_CHANNEL_PDU_NUM,
        .u16ShortTxDataChannelPduPayloadSize = SHORT_TX_DATA_CHANNEL_PDU_SIZE,

        .pstLongRxDataChannelPduMemBuffer   = g_pstLongRxDataChannelPduMem,
        .u8LongRxDataChannelPduNum          = LONG_RX_DATA_CHANNEL_PDU_NUM,
        .u16LongRxDataChannelPduPayloadSize = LONG_RX_DATA_CHANNEL_PDU_SIZE,

        .pstShortRxDataChannelPduMemBuffer   = g_pstShortRxDataChannelPduMem,
        .u8ShortRxDataChannelPduNum          = SHORT_RX_DATA_CHANNEL_PDU_NUM,
        .u16ShortRxDataChannelPduPayloadSize = SHORT_RX_DATA_CHANNEL_PDU_SIZE,
    };

    if (!rom_llc_data_channel_pdu_mem_init(&stLlcDataChannelPduMemCfg))
    {
        return false;
    }
    ////

    //// acl data mem init
    for (i = 0; i < ACL_DATA_NUM; i++)
    {
        g_pstAclDataMem[i].pu8Payload        = g_pu8AclDataPayloadMem[i];
        g_pstAclDataMem[i].u16PayloadBufSize = ACL_DATA_SIZE;
    }

    if (!rom_llc_acl_data_mem_init(g_pstAclDataMem, ACL_DATA_SIZE, ACL_DATA_NUM))
    {
        return false;
    }
////
#endif

    //// hci command mem init
    for (i = 0; i < HCI_COMMAND_NUM; i++)
    {
        g_pstHciCommandMemBuffer[i].pu8ParametersBuffer     = g_pu8HciCommandParametersBuffer[i];
        g_pstHciCommandMemBuffer[i].u16ParametersBufferSize = HCI_COMMAND_PARAMETERS_SIZE;
    }

    if (!rom_llc_hci_command_mem_init(g_pstHciCommandMemBuffer, HCI_COMMAND_PARAMETERS_SIZE, HCI_COMMAND_NUM))
    {
        return false;
    }
    ////

    return true;
}

/**
 * @brief  llc task
 * @param  None.
 * @return None.
 */
static void llc_task(void *argument)
{
    stLlcTaskMsg_t stLlcTaskMsg;
    osStatus_t     status;

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
static bool send_msg_to_llc_task(stLlcTaskMsg_t stLlcTaskMsg)
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
 * @brief  controller task init.
 */
bool controller_task_init(void)
{
    const osMessageQueueAttr_t llc_task_msg_queue_attr = {
        .name      = "llc_task_msg_queue",
        .attr_bits = 0,
        .cb_mem    = llcTaskMsgQueueCb,
        .cb_size   = sizeof(llcTaskMsgQueueCb),
        .mq_mem    = llcTaskMsgQueueMem,
        .mq_size   = sizeof(llcTaskMsgQueueMem),
    };

    llcTaskMsgQueueId = osMessageQueueNew(LLC_TASK_MSG_COUNT, sizeof(stLlcTaskMsg_t), &llc_task_msg_queue_attr);

    if (NULL == llcTaskMsgQueueId)
    {
        PRINTF("llcTaskMsgQueueId NULL\n");
        return false;
    }

    const osThreadAttr_t llc_task_attr = {
        .name       = "llc_task",
        .attr_bits  = osThreadJoinable,
        .cb_mem     = &llcTaskCb,
        .cb_size    = sizeof(llcTaskCb),
        .stack_mem  = llcTaskStack,
        .stack_size = sizeof(llcTaskStack),
        .priority   = osPriorityAboveNormal,
    };

    llcTaskId = osThreadNew(llc_task, NULL, &llc_task_attr);

    if (NULL == llcTaskId)
    {
        PRINTF("llcTaskId NULL\n");
        return false;
    }

    rom_llc_set_send_msg_to_llc_task_callback(send_msg_to_llc_task);

    return true;
}

bool ble_controller_init(void)
{
    if (!controller_mem_init())
    {
        return false;
    }

    if (!controller_task_init())
    {
        return false;
    }

    rom_llp_init();
    rom_llp_set_clock_accuracy_ppm(CLOCK_ACCURACY);
    rom_llp_sleep_set_time(SLEEP_THRESHOLD_TIME_US, PRE_WAKEUP_TIME_US);
    rom_llc_init();

    return true;
}
