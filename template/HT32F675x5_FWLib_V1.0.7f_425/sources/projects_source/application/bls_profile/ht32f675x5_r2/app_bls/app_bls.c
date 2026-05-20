/*************************************************************************************************************
 * @file    app_bls.c
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
#include "app_timer.h"
#include "rand.h"
#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "ble_init.h"
#include "ble_peripheral.h"
#include "ble_event.h"
#include "ble_cb_event_def.h"
#include "ble_dis.h"
#include "ble_bls.h"
#include "ble_bas.h"
#include "dev_info.h"
#include "gap_api.h"
#define APP_MSG_NUM                 (5)

typedef enum
{
    EN_MSG_MODULE_BLE   = 0x00,
    EN_MSG_MODULE_BLS   = 0x01,
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

/* BLS Variables */
static stBlsHandle_t gstBlsHandle;
static stAppTimerNode_t gstExampleTimer;

/**********************************************************************************************************************
 * @brief  OS Message Queue Init.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T msg_queue_init(void)
{
    const osMessageQueueAttr_t appMsgAueueAttr =
    {
        .name = "App BLS Msg Queue",
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
 * @brief  Send Message of Blood Pressure Service Event(Ble Task Context).
 * @param  u8Event: Module Event.
 * @param  pu8Data: Event Data.
 * @param  u16DataLen: the Length of Event Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void bls_event_callback(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen)
{
    if(!send_msg_app_task(EN_MSG_MODULE_BLS, u8Event, pu8Data, u16DataLen))
    {
        INFO("Send Bls Message Failed\r\n");
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
            gstBlsHandle.u16ConnHandle = u16ConnHandle;
            break;
        }
        case MSG_BLE_DISCONNECTED_IND:
        {
            gstBlsHandle.u16ConnHandle = 0;
            start_pair_adv();
            break;
        }
        default:break;
    }
}

/**********************************************************************************************************************
 * @brief  Blood Pressure Service Event Handle Process(App Task).
 * @param  pstAppMsg: Module Message.
 *
 * @return None.
 *********************************************************************************************************************/
static void bls_event_process(const stAppMsg_t *pstAppMsg)
{
    switch(pstAppMsg->u8Event)
    {
        case EN_BLS_EVT_NONE:
            break;
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

static void example_timer_timeout(void *pContext)
{
    if (false == is_ble_connected())
        return;

    stBlsMeasRec_t stRecord = {0};
        stRecord.u8Flags =	BLS_MEASUREMENT_FLAGS_TIME_STAMP |
                            BLS_MEASUREMENT_FLAGS_PLUSE_RATE |
                            BLS_MEASUREMENT_FLAGS_MEASUREMENT_STATUS;
	
    stRecord.u16MeasSystolic = (uint16_t)rom_get_rand()&0xff;
    stRecord.u16MeasDiastolic = (uint16_t)rom_get_rand()&0xff;
    stRecord.u16MeasMAP = (uint16_t)rom_get_rand()&0xff;

    stRecord.stBlsDateTime.u16Year=0x07E7;
    stRecord.stBlsDateTime.u8Month = 12;
    stRecord.stBlsDateTime.u8Day = 14;
    stRecord.stBlsDateTime.u8Hour = 11;
    stRecord.stBlsDateTime.u8Minute = 40;
    stRecord.stBlsDateTime.u8Second = 59;
    stRecord.u16PluseRate= 0xF258;
    stRecord.u16MeasStatus = 1;
    bls_meas_send(&gstBlsHandle,&stRecord);
}

/**********************************************************************************************************************
 * @brief  Get Battery Level.
 *
 * @return Battery Level
 *********************************************************************************************************************/
static uint8_t get_battery_level(void)
{
    uint8_t u8BatteryLevel = 66;
    INFO("Current Battery Level : %u%%\r\n",u8BatteryLevel);
    return u8BatteryLevel;
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
 * @brief  Blood Pressure Device Application Main.
 * 
 * @return None
 *********************************************************************************************************************/
void app_bls(void)
{
    osStatus_t status = osOK;
    stAppMsg_t stAppMsg;
    EN_ERR_STA_T enRet = ERR_STA_OK;

    INFO("---------------Blood Pressure Profile Example----------------\n");

    // 1. Component init
    msg_queue_init();

    // 2. Init Ble
    ble_init();
    ble_event_init(ble_event_callback);
    ble_peripheral_init();
    read_dev_info();        
    // 3. Add Service
    ble_dis_init();
    ble_bas_init(get_battery_level); 
    //BLS
    gstBlsHandle.u16BlsFeature = BLS_FEATURE_SUPPORTED_BODY_MOVEMENT_DETECTION;
    ble_bls_init(&gstBlsHandle,bls_event_callback);
            

    // 4. Start Ble Pair Advertising
    start_pair_adv();
    // 5. Create and Start Example Timer
    app_timer_create(&gstExampleTimer,APP_TIMER_MODE_REPEAT,example_timer_timeout);
    app_timer_start(&gstExampleTimer,5 * 1000,NULL);

    while(1)
    {
        // 5. Wait for Event
        status = osMessageQueueGet(gosMsgId, &stAppMsg, NULL, osWaitForever);
        if (osOK != status)
        {
            INFO("CGM Message Queue Get Failed \n");
            continue;
        }
        switch(stAppMsg.u8MsgModule)
        {
            case EN_MSG_MODULE_BLE:
            {
                ble_event_process(&stAppMsg);
                break;
            }
            case EN_MSG_MODULE_BLS:
            {
                bls_event_process(&stAppMsg);
                break;
            }
            default:break;
        }
    }
}
