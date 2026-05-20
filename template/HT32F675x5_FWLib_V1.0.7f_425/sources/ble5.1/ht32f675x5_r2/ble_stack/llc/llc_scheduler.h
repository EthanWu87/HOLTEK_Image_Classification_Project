/*************************************************************************************************************
 * @file    llc_scheduler.h
 * @version V1.0
 * @date    2021-02-06
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
#ifndef LLC_SCHEDULER_H
#define LLC_SCHEDULER_H


typedef enum
{
    LLC_SCHEDULER_STATE_IDLE = 0,
    LLC_SCHEDULER_STATE_EVENT_PREPARE,
    LLC_SCHEDULER_STATE_EVENT_SCHEDULE,
    LLC_SCHEDULER_STATE_EVENT_WAIT,
    LLC_SCHEDULER_STATE_EVENT_RUN,
    LLC_SCHEDULER_STATE_EVENT_STOP,
}
EN_LLC_SCHEDULER_STATE_T;


typedef enum
{
    LLC_SCHEDULER_ROLE_ADV = 0,
    LLC_SCHEDULER_ROLE_SCAN,
    LLC_SCHEDULER_ROLE_INIT,
    LLC_SCHEDULER_ROLE_SLAVE,
    LLC_SCHEDULER_ROLE_MASTER,
    LLC_SCHEDULER_ROLE_EXT_ADV,
    LLC_SCHEDULER_ROLE_EXT_SCAN,
    LLC_SCHEDULER_ROLE_EXT_INIT,
}
EN_LLC_SCHEDULER_ROLE_T;


typedef enum
{
    LLC_SCHEDULER_EVENT_STATE_IDLE = 0,
    LLC_SCHEDULER_EVENT_STATE_LLP_CONFIGED,
    LLC_SCHEDULER_EVENT_STATE_RUN,
}
EN_LLC_SCHEDULER_EVENT_STATE_T;



//return blocked count
typedef uint32_t (*scheduler_callback_on_event_blocked) (void* pstRoleInstance);
typedef EN_LLP_ERR_T (*scheduler_callback_config_llp) (void* pstRoleInstance, uint32_t u32MaxWorkWindowTimeUs);
typedef void (*scheduler_callback_on_llp_start) (void* pstRoleInstance);

//return true to skip prepare and schedule state and go to wait state(this event will get another run time) : for future use
typedef bool (*scheduler_callback_on_llp_stop) (void* pstRoleInstance);
typedef EN_LLP_STATE_CMD_T (*scheduler_callback_on_llp_tx_end) (void* pstRoleInstance, stLlpTxEndReport_t *pstReport);
typedef EN_LLP_STATE_CMD_T (*scheduler_callback_on_llp_rx_end) (void* pstRoleInstance, stLlpRxEndReport_t *pstReport);
typedef void (*scheduler_callback_on_event_added) (void* pstRoleInstance);
typedef void (*scheduler_callback_on_event_removed) (void* pstRoleInstance);
typedef void (*scheduler_callback_on_event_prepare) (void* pstRoleInstance);


typedef struct llcSchdulerEventNode
{
    uint64_t u64NextEventTimePointUs;//begining of TRX
    
    uint32_t u32NextEventMinWorkTimeUs;
    uint32_t u32CompensationTimeUs;
    EN_LLC_SCHEDULER_ROLE_T enumRole;
    EN_LLC_SCHEDULER_EVENT_STATE_T enumEventState;
    uint8_t u8Priority;
    
    scheduler_callback_on_event_blocked blockCallback;
    scheduler_callback_config_llp configCallback;
    scheduler_callback_on_llp_start startCallback;
    scheduler_callback_on_llp_stop stopCallback;
    scheduler_callback_on_llp_tx_end txEndCallback;
    scheduler_callback_on_llp_rx_end rxEndCallback;
    scheduler_callback_on_event_added eventAddedCallback;
    scheduler_callback_on_event_removed eventRemovedCallback;
    scheduler_callback_on_event_prepare eventPrepareCallback;//can not add/remove event in eventPrepareCallback
    
    void *pstRoleInstance;
    bool bRemoveAfterStop;
    
    struct llcSchdulerEventNode *next;
    struct llcSchdulerEventNode *prev;
    uint32_t u32Reserved;
} __attribute__((aligned(8)))
stLlcSchedulerEvent_t, *pstLlcSchedulerEvent_t;

extern volatile EN_LLC_SCHEDULER_STATE_T g_enumLlcSchedulerState;

bool rom_llc_scheduler_mem_init(pstLlcSchedulerEvent_t* pstEventsArrayBuffer, uint32_t u32EventsArrayBufferSize,
    pstLlcSchedulerEvent_t* pstEventsTempArrayBuffer, uint32_t u32EventsTempArrayBufferSize, uint32_t u32MaxEventsNum);

bool rom_llc_scheduler_add_event(stLlcSchedulerEvent_t* pstEvent);
bool rom_llc_scheduler_is_event_added(stLlcSchedulerEvent_t* pstEvent);
bool rom_llc_scheduler_remove_event(stLlcSchedulerEvent_t* pstEvent);
void rom_llc_scheduler_request_reschedule(stLlcSchedulerEvent_t* pstEvent);

void rom_llc_scheduler_on_schedule(void);
void rom_llc_scheduler_on_llp_fragment_start(void);
void rom_llc_scheduler_on_llp_fragment_stop(void);
EN_LLP_STATE_CMD_T rom_llc_scheduler_on_llp_tx_end(stLlpTxEndReport_t *pstReport);
EN_LLP_STATE_CMD_T rom_llc_scheduler_on_llp_rx_end(stLlpRxEndReport_t *pstReport);

bool rom_llc_scheduler_is_event_block_another(stLlcSchedulerEvent_t* pstEvent1, stLlcSchedulerEvent_t* pstEvent2);

#endif
