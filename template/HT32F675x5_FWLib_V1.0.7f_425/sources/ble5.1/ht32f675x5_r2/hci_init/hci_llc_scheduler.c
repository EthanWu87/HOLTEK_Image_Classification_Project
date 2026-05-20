/*************************************************************************************************************
 * @file    hci_llc_scheduler.c
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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "RegHT32F675x5.h"

#include "llc_llp_interface.h"

#include "llc.h"

#include "llc_scheduler.h"

#include "llc_tool.h"

#include "llc_schedule_algorithm.h"

#include "llc_priority.h"

#include "mlog.h"

#include "llc_hook.h"
#include "rom_callback.h"

#include "hci_llc_scheduler.h"


//performance optimize scheduler, only 1 event can run


extern void rom_llc_scheduler_request_schedule(void);


extern volatile EN_LLC_SCHEDULER_STATE_T g_llcSchedulerCurrentState;
extern volatile EN_LLC_SCHEDULER_STATE_T g_llcSchedulerNextState;
extern stLlcSchedulerEvent_t* g_pstLlcScheduledEvent;
extern volatile bool g_bLlcScheduleRequested;
extern uint32_t g_u32ScheduledEventMaxWorkTimeUs;

stLlcSchedulerEvent_t* g_pstHciLlcConnectionEvent = NULL;
stLlcSchedulerEvent_t* g_pstHciLlcOtherEvent = NULL;


bool hci_llc_scheduler_add_event(bool* pbIsDone, void* pEvent)
{
    *pbIsDone = true;
    stLlcSchedulerEvent_t* pstEvent = pEvent;
    
    if (LLC_SCHEDULER_STATE_EVENT_PREPARE == g_llcSchedulerCurrentState)
    {
        ////can not add/remove event in prepare state
        return false;
    }
    
    if ((LLC_SCHEDULER_ROLE_SLAVE == pstEvent->enumRole) 
        || (LLC_SCHEDULER_ROLE_MASTER == pstEvent->enumRole))
    {
        if (NULL != g_pstHciLlcConnectionEvent)
        {
            return false;
        }
        g_pstHciLlcConnectionEvent = pstEvent;
    }
    else
    {
        if (NULL != g_pstHciLlcOtherEvent)
        {
            return false;
        }
        g_pstHciLlcOtherEvent = pstEvent;
    }
    
    pstEvent->bRemoveAfterStop = false;
    pstEvent->enumEventState = LLC_SCHEDULER_EVENT_STATE_IDLE;
    
    if (NULL != pstEvent->eventAddedCallback)
    {
        pstEvent->eventAddedCallback(pstEvent->pstRoleInstance);
    }
    
    if (LLC_SCHEDULER_STATE_IDLE == g_llcSchedulerCurrentState)
    {
        rom_llc_scheduler_request_schedule();
    }
    else
    {
        if (NULL != g_pstLlcScheduledEvent)
        {
            
            //stop current fragment to re-schedule
            rom_llc_stop_fragment();
        }
    }
    return true;
}


bool hci_llc_scheduler_is_event_added (bool* pbIsDone, void* pEvent)
{
    *pbIsDone = true;
    
    if (pEvent == g_pstHciLlcConnectionEvent || pEvent == g_pstHciLlcOtherEvent)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool hci_llc_scheduler_remove_event(bool* pbIsDone, void* pEvent)
{
    *pbIsDone = true;
    stLlcSchedulerEvent_t* pstEvent = pEvent;
    
    if ((NULL == pstEvent) || ((NULL == g_pstHciLlcConnectionEvent)&&(NULL == g_pstHciLlcOtherEvent)))
    {
        //already removed
        return true;
    }
    
    uint32_t u32Primask = __get_PRIMASK();
    __disable_irq();
    
    if (pstEvent == g_pstLlcScheduledEvent)
    {
        pstEvent->bRemoveAfterStop = true;
        rom_llc_stop_fragment();
        
        __set_PRIMASK(u32Primask);
        return true;
    }
    
    
    if (pstEvent == g_pstHciLlcConnectionEvent)
    {
        g_pstHciLlcConnectionEvent = NULL;
        
        if (NULL != pstEvent->eventRemovedCallback)
        {
            pstEvent->eventRemovedCallback(pstEvent->pstRoleInstance);
        }
    }
    else if (pstEvent == g_pstHciLlcOtherEvent)
    {
        g_pstHciLlcOtherEvent = NULL;
        
        if (NULL != pstEvent->eventRemovedCallback)
        {
            pstEvent->eventRemovedCallback(pstEvent->pstRoleInstance);
        }
    }
    __set_PRIMASK(u32Primask);
    
    ////already removed
    return true;
}


void hci_llc_scheduler_request_reschedule (bool* pbIsDone, void* pEvent)
{
    *pbIsDone = true;
    stLlcSchedulerEvent_t* pstEvent = pEvent;
    
    uint32_t u32Primask = __get_PRIMASK();
    __disable_irq();
    
    if ((LLC_SCHEDULER_STATE_IDLE == g_llcSchedulerCurrentState)||(NULL == g_pstLlcScheduledEvent))
    {
        rom_llc_scheduler_request_schedule();
        __set_PRIMASK(u32Primask);
        return;
    }
    else
    {
        //stop current fragment to re-schedule
        rom_llc_stop_fragment();
    }
    __set_PRIMASK(u32Primask);
}


void hci_llc_scheduler_goto_prepare_state(void)
{
    g_bLlcScheduleRequested = false;
    g_llcSchedulerCurrentState = LLC_SCHEDULER_STATE_EVENT_PREPARE;
    g_pstLlcScheduledEvent = NULL;
    
    if ((NULL == g_pstHciLlcConnectionEvent)&&(NULL == g_pstHciLlcOtherEvent))
    {
        g_llcSchedulerNextState = LLC_SCHEDULER_STATE_IDLE;
        return;
    }
    
    if ((NULL != g_pstHciLlcConnectionEvent))
    {
        if (NULL != g_pstHciLlcConnectionEvent->eventPrepareCallback)
        {
            g_pstHciLlcConnectionEvent->eventPrepareCallback(g_pstHciLlcConnectionEvent->pstRoleInstance);
        }
    }
    
    //others no need to invoke eventPrepareCallback
    
    
    g_llcSchedulerNextState = LLC_SCHEDULER_STATE_EVENT_SCHEDULE;
}


void hci_llc_scheduler_goto_schedule_state(void)
{
    g_llcSchedulerCurrentState = LLC_SCHEDULER_STATE_EVENT_SCHEDULE;
    
    if (NULL != g_pstHciLlcConnectionEvent)
    {
        g_pstLlcScheduledEvent = g_pstHciLlcConnectionEvent;
    }
    else
    {
        g_pstLlcScheduledEvent = g_pstHciLlcOtherEvent;
    }
    
    g_u32ScheduledEventMaxWorkTimeUs = 0xFFFFFFFF;
    
    if (g_bLlcScheduleRequested)
    {
        g_llcSchedulerCurrentState = LLC_SCHEDULER_STATE_EVENT_PREPARE;
        return;
    }
    
    g_llcSchedulerNextState = LLC_SCHEDULER_STATE_EVENT_WAIT;
    
}

void hci_llc_scheduler_goto_stop_state(void)
{
    
    g_llcSchedulerCurrentState = LLC_SCHEDULER_STATE_EVENT_STOP;
    stLlcSchedulerEvent_t *pstStoppedEvent = g_pstLlcScheduledEvent;
    //set NULL at first
    g_pstLlcScheduledEvent = NULL;
    
    
    bool bStoppedAfterStart = (LLC_SCHEDULER_EVENT_STATE_RUN == pstStoppedEvent->enumEventState);
    pstStoppedEvent->enumEventState = LLC_SCHEDULER_EVENT_STATE_IDLE;
    
    bool bSkipPrepareAndScheduleState = false;
    if (bStoppedAfterStart)
    {
        if (NULL != pstStoppedEvent->stopCallback)
        {
            bSkipPrepareAndScheduleState = pstStoppedEvent->stopCallback(pstStoppedEvent->pstRoleInstance);
        }
    }
    
    
    if (pstStoppedEvent->bRemoveAfterStop)
    {
        bSkipPrepareAndScheduleState = false;
        rom_llc_scheduler_remove_event(pstStoppedEvent);
    }
    
    if (bSkipPrepareAndScheduleState)
    {
        g_pstLlcScheduledEvent = pstStoppedEvent;
        g_u32ScheduledEventMaxWorkTimeUs = 0xFFFFFFFF;
        g_llcSchedulerNextState = LLC_SCHEDULER_STATE_EVENT_WAIT;
    }
    else
    {
        g_llcSchedulerNextState = LLC_SCHEDULER_STATE_EVENT_PREPARE;
    }
}


void hci_llc_scheduler_main(bool* pbIsDone)
{
    *pbIsDone = true;
    
    while(g_llcSchedulerCurrentState != g_llcSchedulerNextState)
    {
        switch(g_llcSchedulerNextState)
        {
            case LLC_SCHEDULER_STATE_IDLE:
            {
                extern void rom_llc_scheduler_goto_idle_state(void);
                rom_llc_scheduler_goto_idle_state();
            }
                break;
            
            case LLC_SCHEDULER_STATE_EVENT_PREPARE:
                hci_llc_scheduler_goto_prepare_state();
                break;
            
            case LLC_SCHEDULER_STATE_EVENT_SCHEDULE:
                hci_llc_scheduler_goto_schedule_state();
                break;
            
            case LLC_SCHEDULER_STATE_EVENT_WAIT:
            {
                extern void rom_llc_scheduler_goto_wait_state(void);
                rom_llc_scheduler_goto_wait_state();
            }
                break;
            
            case LLC_SCHEDULER_STATE_EVENT_RUN:
            {
                extern void rom_llc_scheduler_goto_run_state(void);
                rom_llc_scheduler_goto_run_state();
            }
                break;
            
            case LLC_SCHEDULER_STATE_EVENT_STOP:
                hci_llc_scheduler_goto_stop_state();
                break;
            
            default:
                //unexpected situation
                system_error(SYS_ERR_MODULE_LLC_SCHEDULER, __LINE__+10000, g_llcSchedulerNextState, g_llcSchedulerCurrentState);
                break;
        }
    }
}



void hci_llc_scheduler_init(void)
{
    g_llcHookPrefixTable[LLC_HOOK_PREFIX_scheduler_add_event] = hci_llc_scheduler_add_event;
    g_llcHookPrefixTable[LLC_HOOK_PREFIX_scheduler_is_event_added] = hci_llc_scheduler_is_event_added;
    g_llcHookPrefixTable[LLC_HOOK_PREFIX_scheduler_remove_event] = hci_llc_scheduler_remove_event;
    g_llcHookPrefixTable[LLC_HOOK_PREFIX_scheduler_request_reschedule] = hci_llc_scheduler_request_reschedule;
    g_llcHookPrefixTable[LLC_HOOK_PREFIX_scheduler_main] = hci_llc_scheduler_main;
}
