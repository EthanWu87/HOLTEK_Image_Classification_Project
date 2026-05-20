/*************************************************************************************************************
 * @file    app_plxs.c
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
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "app_cfg.h"
#include "boards.h"
#include "utility.h"
#include "hw_gpio.h"
#include "hw_pmu.h"
#include "hw_sys_ctrl.h"

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "app_timer.h"
#include "rand.h"
#include "rtc.h"
#include "calendar.h"

#include "ble_init.h"
#include "ble_peripheral.h"
#include "ble_event.h"
#include "ble_cb_event_def.h"
#include "ble_dis.h"
#include "ble_cts.h"
#include "ble_bas.h"
#include "ble_plxs.h"
#include "dev_info.h"
#include "gap_api.h"
#define APP_MSG_NUM                     (5)

typedef enum
{
    EN_MSG_MODULE_BLE  = 0x00,
}EN_MSG_MODULE_T;

typedef struct
{
    uint8_t  u8MsgModule;
    uint8_t  u8Event;
    uint32_t u32Length;
    void *p;
    uint16_t u16Reserve;
    
}stAppMsg_t;

/* Message Queue Variables */
static osMessageQueueId_t gosMsgId = NULL;
static uint32_t gu32TaskMsgQueueCb[osRtxMessageQueueCbSize / 4U];
static uint32_t gu32TaskMsgQueueMem[osRtxMessageQueueMemSize(10, sizeof(stAppMsg_t)) / 4U];

/* PLXS Variables */
static stPlxsHandle_t gstPlxsHandle;
static stAppTimerNode_t gstPlxsMeasTimer;
static stAppTimerNode_t gstPlxsExampleTimer;
static stCalendar_t gstCalendar;
static uint8_t ble_bas_get_battery_level(void)
{
    return 99;
}

/**********************************************************************************************************************
 * @brief  OS Message Queue Init.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T msg_queue_init(void)
{
    const osMessageQueueAttr_t appMsgAueueAttr =
    {
        .name = "App PLXS Msg Queue",
        .attr_bits = 0,
        .cb_mem = gu32TaskMsgQueueCb,
        .cb_size = sizeof(gu32TaskMsgQueueCb),
        .mq_mem = gu32TaskMsgQueueMem,
        .mq_size = sizeof(gu32TaskMsgQueueMem),
    };

    gosMsgId = osMessageQueueNew(APP_MSG_NUM, sizeof(stAppMsg_t), &appMsgAueueAttr);
    if(NULL == gosMsgId)
    {
        PRINTF("create AppMsgId failed\n");
        return ERR_STA_ERROR;
    }
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Send App Message.
 * @param  enMsgModlue: App Module.
 * @param  u8Event: Module Event.
 * @param  pu8Data: Event Data.
 * @param  u32Len: the length of Event Data.
 *
 * @return Result of Send Message.
 *********************************************************************************************************************/
static bool send_msg_app_task(EN_MSG_MODULE_T enMsgModlue, uint8_t u8Event, uint8_t *pu8Data, uint32_t u32Len)
{
    uint32_t u32Timeout = osWaitForever;
    stAppMsg_t stAppMsg;

    if (__get_IPSR())
    {
        // in interrupt
        u32Timeout = 0;
    }
    
    stAppMsg.u8MsgModule = enMsgModlue;
    stAppMsg.u8Event = u8Event;
    stAppMsg.p = pu8Data;
    stAppMsg.u32Length = u32Len;

    osStatus_t Status = osMessageQueuePut(gosMsgId, &stAppMsg, 0, u32Timeout);
    if (osOK == Status)
        return true;
    else
    {
        INFO("Send Message Failed: %d\n", Status);
        return false;
    }
}

/**********************************************************************************************************************
 * @brief  Send Message of Ble Event(Ble Task Context).
 * @param  u8Event: Module Event.
 * @param  pu8Data: Event Data.
 * @param  u16DataLen: the Length of Event Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void ble_event_callback(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen)
{
    if(!send_msg_app_task(EN_MSG_MODULE_BLE, u8Event, pu8Data, u16DataLen))
    {
        INFO("Send Ble Message Failed\r\n");
    }
}

/**********************************************************************************************************************
 * @brief  Ble Event Handle Process(App Task).
 * @param  pstAppMsg: Module Message.
 *
 * @return None.
 *********************************************************************************************************************/
static void ble_event_process(const stAppMsg_t *pstAppMsg)
{
    uint16_t u16ConnHandle;
    switch(pstAppMsg->u8Event)
    {
        case MSG_BLE_CONNECTED_IND:
        {
            u16ConnHandle = get_ble_conn_handle();
            gstPlxsHandle.u16ConnHandle = u16ConnHandle;
            break;
        }
        case MSG_BLE_DISCONNECTED_IND:
        {
            gstPlxsHandle.u16ConnHandle = 0;
            start_pair_adv();
            break;
        }
        default:break;
    }
}

/**********************************************************************************************************************
 * @brief  Determine whether have Completed All Works and Enter Sleep Mode.
 *
 * @return true : goto sleep  false : can not goto sleep.
 *********************************************************************************************************************/
bool is_app_can_goto_sleep(void)
{
    // Check ble.
    if (!ble_init_is_system_sleep_allowed())
        return false;

    return true;
}

/**********************************************************************************************************************
 * @brief  PLXS Time Init.
 *
 * @return None.
 *********************************************************************************************************************/
static void plxs_time_init(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    // Calendar Default Time
    gstCalendar.u16Year = 2023;
    gstCalendar.u8Mon = 9;
    gstCalendar.u8Day = 25;
    gstCalendar.u8Hour = 16;
    gstCalendar.u8Min = 35;
    gstCalendar.u8Sec = 9;
    gstCalendar.u8Wday = 4;

    // RTC Init&Start
    rtc_start();
    // Calendar Init
    calendar_init(&gstCalendar);

    INFO("Device System Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
        gstCalendar.u16Year,gstCalendar.u8Mon,gstCalendar.u8Day,gstCalendar.u8Hour,gstCalendar.u8Min,gstCalendar.u8Sec);
}

/**********************************************************************************************************************
 * @brief  Current Time Service Get Time Callback.
 * @param  stCtsDateTime : Current Time Service Data Time
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T ble_cts_get_time_callback(stCtsDateTime_t *stCtsDateTime)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    calendar_period_get_time(&gstCalendar);

    stCtsDateTime->u16Year  = gstCalendar.u16Year;
    stCtsDateTime->u8Mon    = gstCalendar.u8Mon;
    stCtsDateTime->u8Day    = gstCalendar.u8Day;
    stCtsDateTime->u8Hour   = gstCalendar.u8Hour;
    stCtsDateTime->u8Min    = gstCalendar.u8Min;
    stCtsDateTime->u8Sec    = gstCalendar.u8Sec;
    stCtsDateTime->u8Wday   = gstCalendar.u8Wday;
    stCtsDateTime->u8F256   = 0;

    INFO("CTS Get System Time\r\n");
    INFO("System Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
        gstCalendar.u16Year,gstCalendar.u8Mon,gstCalendar.u8Day,gstCalendar.u8Hour,gstCalendar.u8Min,gstCalendar.u8Sec);

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Current Time Service Set Time Callback.
 * @param  stCtsDateTime : Current Time Service Data Time
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T ble_cts_set_time_callback(const stCtsDateTime_t *stCtsDateTime)
{
    gstCalendar.u16Year = stCtsDateTime->u16Year;
    gstCalendar.u8Mon   = stCtsDateTime->u8Mon;
    gstCalendar.u8Day   = stCtsDateTime->u8Day;
    gstCalendar.u8Hour  = stCtsDateTime->u8Hour;
    gstCalendar.u8Min   = stCtsDateTime->u8Min;
    gstCalendar.u8Sec   = stCtsDateTime->u8Sec;
    gstCalendar.u8Wday  = stCtsDateTime->u8Wday;

    calendar_set_utc(&gstCalendar);

    INFO("CTS Set System Time\r\n");
    INFO("Device System Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
        gstCalendar.u16Year,gstCalendar.u8Mon,gstCalendar.u8Day,gstCalendar.u8Hour,gstCalendar.u8Min,gstCalendar.u8Sec);

    return ERR_STA_OK;
}

static void plxs_example_timer_timeout(void *pContext)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (false == is_ble_connected())
        return;
    
    stPlxsMeasRec_t stRecord;
    stRecord.u8Flags = 0;
    stRecord.u16SpO2 = (uint16_t )rom_get_rand()&0xff;
    stRecord.u16Pr = (uint16_t )rom_get_rand()&0xff;

    enRet = plxs_meas_send(&gstPlxsHandle,&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("PLXS Send Failed\n");
        return;
    }
}





static void read_dev_info(void)
{
    EN_ERR_STA_T enRet;
    uint8_t u8Addr[6];
    uint8_t u8Did[3];

    enRet = dev_info_device_id(u8Did,3);
    if (ERR_STA_OK != enRet)
    {
        INFO("Read Device ID Failed\n");
        return;
    }

    INFO("Device ID : ");
    for (int i=0;i<3;i++)
        PRINTF("0x%02X ",u8Did[i]);
    PRINTF("\n");
        
    enRet = dev_info_default_ble_addr(u8Addr,6);
    if (ERR_STA_OK != enRet)
    {
        INFO("Read Default Ble Dev Addr Failed\n");
        return;
    }

    INFO("Defaule Ble Addr : ");
    for (int i=0;i<6;i++)
        PRINTF("0x%02X ",u8Addr[i]);
    PRINTF("\n");
    rom_gap_api_set_public_device_address((uint8_t *)u8Addr);
        
    // use Custom ble mac if address not zero
    enRet = dev_info_custom_ble_addr(u8Addr,6);
    if (ERR_STA_OK != enRet)
    {
        INFO("Read Custom Ble Dev Addr Failed\n");
        return;
    }
    else if(ERR_STA_OK == enRet)
    {
        if(u8Addr[0] == 0x0 && u8Addr[1] == 0x0 && u8Addr[2] == 0x0 &&
           u8Addr[3] == 0x0 && u8Addr[4] == 0x0 && u8Addr[5] == 0x0)
        {
            //all value is 0(default)
        }
        else
        {
            INFO("custom Ble Addr : ");
            for (int i=0;i<6;i++)
                PRINTF("0x%02X ",u8Addr[i]);
            PRINTF("\n");
            rom_gap_api_set_public_device_address((uint8_t *)u8Addr);
        }
    }
}


/**********************************************************************************************************************
 * @brief  PLXS Device Application Main.
 * 
 * @return None
 *********************************************************************************************************************/
void app_plxs(void)
{
    osStatus_t status = osOK;
    stAppMsg_t stAppMsg;
    EN_ERR_STA_T enRet = ERR_STA_OK;

    INFO("---------------PLXS Profile Example----------------\n");

    // 1. Component init
    msg_queue_init();
    plxs_time_init();

    // 2. Init Ble
    ble_init();
    ble_event_init(ble_event_callback);
    ble_peripheral_init();
    read_dev_info();
    // 3. Add Service
    ble_dis_init();
    ble_bas_init(ble_bas_get_battery_level);
    
    stCtsInit_t stCtsInit;
    stCtsInit.cts_get_time_handler = ble_cts_get_time_callback;
    stCtsInit.cts_set_time_handler = ble_cts_set_time_callback;
    
    ble_cts_init(&stCtsInit);

    // Add PLXS Sensor Feature
    // Refer to PLXS_FEATURE_SUPPORT_* in "ble_plxs.h"
    gstPlxsHandle.stFeatures.u16Features = PLXS_FEATURE_SUPPORT_MEAS_STATUS_PRESENT |
                                           PLXS_FEATURE_SUPPORT_DEV_AND_SEN_STATUS_PRESENT |
                                           PLXS_FEATURE_SUPPORT_TIMESTAMP_FOR_SPOT_CHECK_MEAS |
                                           PLXS_FEATURE_SUPPORT_PLUSE_AMPLITUDE;
    
    enRet = ble_plxs_init(&gstPlxsHandle);
    if (ERR_STA_OK != enRet)
    {
        PRINTF("PLXS Init Failed\n");
        return;
    }


    // 4. Start Ble Pair Advertising
    start_pair_adv();
    // 5. Create and Start Example Timer
    app_timer_create(&gstPlxsExampleTimer,APP_TIMER_MODE_REPEAT,plxs_example_timer_timeout);
    app_timer_start(&gstPlxsExampleTimer,5*1000,NULL);
    while(1)
    {
        // 6. Wait for Event
        status = osMessageQueueGet(gosMsgId, &stAppMsg, NULL, osWaitForever);
        if (osOK != status)
        {
            INFO("PLXS Message Queue Get Failed \n");
            continue;
        }
        switch(stAppMsg.u8MsgModule)
        {
            case EN_MSG_MODULE_BLE:
            {
                ble_event_process(&stAppMsg);
                break;
            }
            default:break;
        }
    }
}
