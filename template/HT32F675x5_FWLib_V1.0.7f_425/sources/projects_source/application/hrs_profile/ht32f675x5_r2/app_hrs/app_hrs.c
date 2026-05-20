/*************************************************************************************************************
 * @file    app_hrs.c
 * @version V1.1
 * @date    2025-08-26
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

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "app_timer.h"
#include "rand.h"

#include "ble_init.h"
#include "ble_peripheral.h"
#include "ble_event.h"
#include "ble_cb_event_def.h"
#include "ble_dis.h"
#include "ble_hrs.h"
#include "ble_bas.h"
#include "uart.h"
#include "dev_info.h"
#include "gap_api.h"
#define APP_MSG_NUM                        (5)

typedef enum
{
    EN_MSG_MODULE_BLE   = 0x00,
    EN_MSG_MODULE_HRS   = 0x01,
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

/* HRS Variables */
static stHrsHandle_t gstHrsHandle;
static stAppTimerNode_t gstHrsExampleTimer;


bool str_to_float(const char *str,float *f)
{
    char *pEnd = NULL;
    const char *pBegin = str;

    *f = strtof(pBegin,&pEnd);
    if (pEnd == pBegin)
        return false;
    
    return true;
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
/**********************************************************************************************************************
 * @brief  OS Message Queue Init.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T msg_queue_init(void)
{
    const osMessageQueueAttr_t appMsgAueueAttr =
    {
        .name = "App HRS Msg Queue",
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
static void hrs_event_callback(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen)
{
    if(!send_msg_app_task(EN_MSG_MODULE_HRS, u8Event, pu8Data, u16DataLen))
    {
        INFO("Send Hrs Message Failed\r\n");
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
            gstHrsHandle.u16ConnHandle = u16ConnHandle;
            break;
        }
        case MSG_BLE_DISCONNECTED_IND:
        {    
            gstHrsHandle.u16ConnHandle = 0;
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
 * @brief  Heart Rate Service Event Handle Process(App Task).
 * @param  pstAppMsg: Module Message.
 *
 * @return None.
 *********************************************************************************************************************/
static void hrs_event_process(const stAppMsg_t *pstAppMsg)
{
    switch(pstAppMsg->u8Event)
    {
        case EN_HRS_EVT_NONE:
            break;
        default:break;
    }
}
static void hrs_example_timer_timeout_UART(float ValueMeasurement)
{
    if (false == is_ble_connected())
        return;

    stHrsMeasRec_t stRecord = {0};

    stRecord.u8Flags       = HRS_MEASUREMENT_FLAGS_HEART_RATE_VAL_FORMAT | HRS_MEASUREMENT_FLAGS_CONTACT_DETECT |
                             HRS_MEASUREMENT_FLAGS_CONTACT_SUPPORT | HRS_MEASUREMENT_FLAGS_ENERGY_EXPENDED | HRS_MEASUREMENT_FLAGS_RR_INTERVAL;
		
		
//INFO("HRS_MEASUREMENT_FLAGS_HEART_RATE_VAL_FORMAT:%d\n",stRecord.u8Flags&0x01);
//INFO("HRS_MEASUREMENT_FLAGS_CONTACT_DETECT:%d\n",stRecord.u8Flags&0x02);
//INFO("HRS_MEASUREMENT_FLAGS_CONTACT_SUPPORT:%d\n",stRecord.u8Flags&0x04);
//INFO("HRS_MEASUREMENT_FLAGS_ENERGY_EXPENDED:%d\n",stRecord.u8Flags&0x08);
//INFO("HRS_MEASUREMENT_FLAGS_RR_INTERVAL:%d\n",stRecord.u8Flags&0x10);
	
		

		//setting parameter
		stRecord.u8MeasVal     = (uint8_t)ValueMeasurement;
    stRecord.u16MeasVal    = (uint16_t)ValueMeasurement;
    stRecord.u16EnerExpend = (uint16_t)ValueMeasurement;
    stRecord.u16RRInterval = (uint16_t)ValueMeasurement;

		
		//print 8bit Heart Rate Measurement Value
		if(HRS_MEASUREMENT_FLAGS_HEART_RATE_VAL_FORMAT==0)
{ 
	INFO("Heart Rate Measurement 8bit: %.0f bpm\n",(float)stRecord.u8MeasVal);
	INFO("Energy Expended: %.0f kj\n",(float)stRecord.u16EnerExpend);
	INFO("RR-Interval: %.2f ms\n",0.976563*(float)stRecord.u16RRInterval);
}
		//print 16bit Heart Rate Measurement Value
		if(HRS_MEASUREMENT_FLAGS_HEART_RATE_VAL_FORMAT==1)
{
	INFO("Heart Rate Measurement Value 16bit: %.0f bpm\n",(float)stRecord.u16MeasVal);
	INFO("Energy Expended: %.0f kj\n",(float)stRecord.u16MeasVal);
	INFO("RR-Interval: %.2f ms\n",0.976563*(float)stRecord.u16RRInterval);

}
		
		
    hrs_meas_send(&gstHrsHandle,&stRecord);
}
static void hrs_example_timer_timeout(void *pContext)
{
    if (false == is_ble_connected())
        return;

    stHrsMeasRec_t stRecord = {0};
    stRecord.u8Flags       = HRS_MEASUREMENT_FLAGS_HEART_RATE_VAL_FORMAT | HRS_MEASUREMENT_FLAGS_CONTACT_DETECT |
                             HRS_MEASUREMENT_FLAGS_CONTACT_SUPPORT | HRS_MEASUREMENT_FLAGS_ENERGY_EXPENDED | HRS_MEASUREMENT_FLAGS_RR_INTERVAL;
    stRecord.u8MeasVal     = (uint8_t)rom_get_rand();
    stRecord.u16MeasVal    = (uint16_t)rom_get_rand();
    stRecord.u16EnerExpend = (uint16_t)rom_get_rand();
    stRecord.u16RRInterval = (uint16_t)rom_get_rand();

		
		//print 8bit Heart Rate Measurement Value
		if(HRS_MEASUREMENT_FLAGS_HEART_RATE_VAL_FORMAT==0)
{ 
	INFO("Heart Rate Measurement 16bit: %.0f bpm\n",(float)stRecord.u8MeasVal);
	INFO("Energy Expended: %.0f kj\n",(float)stRecord.u16EnerExpend);
	INFO("RR-Interval: %.2f ms\n",(float)stRecord.u16RRInterval);
}
		//print 16bit Heart Rate Measurement Value
		if(HRS_MEASUREMENT_FLAGS_HEART_RATE_VAL_FORMAT==1)
{
	INFO("Heart Rate Measurement Value 8bit: %.0f bpm\n",(float)stRecord.u16MeasVal);
	INFO("Energy Expended: %.0f kj\n",(float)stRecord.u16MeasVal);
	INFO("RR-Interval: %.2f ms\n",(float)stRecord.u16RRInterval);

}
		
    hrs_meas_send(&gstHrsHandle,&stRecord);
}

/**********************************************************************************************************************
 * @brief  Data Receive Callback of Uart(Interrupt Context).
 * @param  pu8Data: Receive Data.
 * @param  u16DataLen: the Length of Receive Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void uart_recv_callback(uint8_t* pu8Data, uint16_t u16DataLen)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
  
 //INFO("pu8Data=%s\n",pu8Data);
	  float ValueMeasurement;
	
//    if (true == gstCgmsHandle.isRacpRunning)
//    {
//        INFO("Racp is Running,Please Try Again Later\r\n");
//        return;
//    }
//    
//    if (false == gstCgmsHandle.isSessionStart)
//    {
//        INFO("Please Start Session and Try Again\r\n");
//        return;
//    }
    
#if SPI_CMD_SUPPORT

    /* Note : SPI command don't end with '\r' or '\n' */
    if (true == is_valid_spi_cmd(pu8Data,u16DataLen))
    {
        if (pu8Data[1] == 0x02)
        {
            if (false == send_msg_app_task(EN_MSG_MODULE_SPI,EN_SPI_CMD_READ_3_BYTES,NULL,0))
                INFO("Send App Message Failed\n");
            return;
        }
        else if(pu8Data[1] == 0xFF)
        {
            if (false == send_msg_app_task(EN_MSG_MODULE_SPI,EN_SPI_CMD_READ_256_BYTES,NULL,0))
                INFO("Send App Message Failed\n");
            return;
        }
    }

#endif

    /* Parse Data */
    if (false == str_to_float((const char *)pu8Data,&ValueMeasurement))
    {
        INFO("Input data Failed\n");
        return;
    }
     //INFO("Heart Rate Measurement Value UART=%f\n",ValueMeasurement);
		INFO("Heart Rate Measurement UART input\n");
    hrs_example_timer_timeout_UART(ValueMeasurement);
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
void app_hrs(void)
{
    osStatus_t status = osOK;
    stAppMsg_t stAppMsg;
    EN_ERR_STA_T enRet = ERR_STA_OK;

    INFO("---------------Heart Rate Profile Example----------------\n");

    // 1. Component init
    msg_queue_init();

    // 2. Init Ble
    ble_init();
    ble_event_init(ble_event_callback);
    ble_peripheral_init();
    //read_dev_info();        
    // 3. Add Service
    ble_dis_init();
	  ble_bas_init(get_battery_level); 
    ble_hrs_init(&gstHrsHandle,hrs_event_callback);

					enRet = uart_init(uart_recv_callback);
    if (enRet != ERR_STA_OK)
    {
        INFO("Uart Init Failed\r\n");
    }
    uart_send_bytes((uint8_t *)"Uart Init Successful\r\n",strlen("Uart Init Successful\r\n"));
		

		
	
    // 4. Start Ble Pair Advertising
    start_pair_adv();

    // 5. Create and Start Example Timer
    app_timer_create(&gstHrsExampleTimer,APP_TIMER_MODE_REPEAT,hrs_example_timer_timeout);
    app_timer_start(&gstHrsExampleTimer,5*1000,NULL);

    while(1)
    {
        // 6. Wait for Event
        status = osMessageQueueGet(gosMsgId, &stAppMsg, NULL, osWaitForever);
        if (osOK != status)
        {
            INFO("HRS Message Queue Get Failed \n");
            continue;
        }
        switch(stAppMsg.u8MsgModule)
        {
            case EN_MSG_MODULE_BLE:
            {
                ble_event_process(&stAppMsg);
                break;
            }
            case EN_MSG_MODULE_HRS:
            {
                hrs_event_process(&stAppMsg);
                break;
            }
            default:break;
        }
    }
}
