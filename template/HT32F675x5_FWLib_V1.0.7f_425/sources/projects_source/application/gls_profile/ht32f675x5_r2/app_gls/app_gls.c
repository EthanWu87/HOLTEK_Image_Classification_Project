/*************************************************************************************************************
 * @file    app_gls.c
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
#include "ble_bas.h"
#include "ble_gls.h"
#include "gls_racp.h"
#include "gls_racp_process.h"
#include "gls_db.h"
#include "gls_utility.h"
#include "uart.h"
#include "dev_info.h"
#include "gap_api.h"
#define APP_MSG_NUM             (5)

typedef enum
{
    EN_MSG_MODULE_BLE  = 0x00,
    EN_MSG_MODULE_GLS = 0x01,
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

/* GLS Variables */
static stGlsHandle_t gstGlsHandle;
static stAppTimerNode_t gstGlsMeasTimer;
static uint16_t gu16TimeOffsetMin;
static stAppTimerNode_t gstGlsExampleTimer;
static stCalendar_t gstCalendar;
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
        .name = "App GLS Msg Queue",
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
 * @brief  Send Message of GLS Service(LL Task Context).
 * @param  u8Event: Module Event.
 * @param  pu8Data: Event Data.
 * @param  u16DataLen: the Length of Event Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void gls_event_callback(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen)
{
    if(!send_msg_app_task(EN_MSG_MODULE_GLS, u8Event, pu8Data, u16DataLen))
    {
        INFO("Send GLS Message Failed\r\n");
    }
}

/**********************************************************************************************************************
 * @brief  App Timer Timeout Callback(Interrupt Context).
 * @param  pContext: Private Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void gls_meas_timer_timeout(void *pContext)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    stGlsMeasRec_t stRecord;
    stRecord.u8Flags = 0;
    stRecord.u16GlucoseConcentration = (uint16_t )rom_get_rand();
    stRecord.u16TimeOffset = 0;
    enRet = gls_meas_send(&gstGlsHandle,&stRecord);
    if(ERR_STA_OK != enRet)
    {
        INFO("GLS Send Measurement Failed\r\n");
        return;
    }
    
    enRet = gls_db_record_add(&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("GLS Database is Full\r\n");
        return;
    }
    
    INFO("Glucose Concentration : %f Kg/L\n",sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)));
    INFO("GLS Record Add to Database Successful\r\n");
    INFO("GLS Database Number of Stored Record : %u\r\n",gls_db_get_record_num());
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
            gstGlsHandle.u16ConnHandle = u16ConnHandle;
            break;
        }
        case MSG_BLE_DISCONNECTED_IND:
        {
            gstGlsHandle.u16ConnHandle = 0;
            start_pair_adv();
            break;
        }
        default:break;
    }
}

/**********************************************************************************************************************
 * @brief  GLS RACP Event Handle Process(App Task).
 * @param  u8Event: Module Event.
 * @param  pstHandle: GLS Global Handle.
 *
 * @return None.
 *********************************************************************************************************************/
static void gls_racp_event_process(uint8_t u8Event,stGlsHandle_t *pstHandle)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    switch(u8Event)
    {
        case EN_GLS_EVT_RACP_REPORT_RECORDS:
        {
            stGlsRacpVal_t stCmdInfo = pstHandle->stRacpCmdInfo;
            if (GLS_RACP_OPERATOR_ALL == stCmdInfo.u8Operator)
            {
                INFO("GLS Report All Stored Resords\n");
                enRet = gls_racp_record_all_report(pstHandle);
            }
            else if (GLS_RACP_OPERATOR_LESS_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MaxVal;
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("GLS Report <= 0x%04X Stored Resords\n",u16MaxVal);
                enRet = gls_racp_record_less_or_equal_report(pstHandle,u16MaxVal);
            }
            else if (GLS_RACP_OPERATOR_GREATER_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("GLS Report >= 0x%04X Stored Resords\n",u16MinVal);
                enRet = gls_racp_record_greater_or_equal_report(pstHandle,u16MinVal);
            }
            else if (GLS_RACP_OPERATOR_WITHIN_RANGE_OF == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal,u16MaxVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],2);
                INFO("GLS Report >= 0x%04X && <= 0x%04X Stored Resords\n",u16MinVal,u16MaxVal);
                enRet = gls_racp_record_range_of_report(pstHandle,u16MinVal,u16MaxVal);
            }
            else if (GLS_RACP_OPERATOR_FIRST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("GLS Report First Stored Resord\n");
                enRet = gls_racp_record_first_report(pstHandle);
            }
            else if (GLS_RACP_OPERATOR_LAST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("GLS Report Last Stored Resord\n");
                enRet = gls_racp_record_last_report(pstHandle);
            }
            else
            {
                INFO("Unknown RACP Operator\n");
            }
            
            if (ERR_DATA_NOT_FOUND == enRet)
                enRet = gls_racp_rsp_code_send(pstHandle,GLS_RACP_OPCODE_RESPONSE_CODE,stCmdInfo.u8Opcode,GLS_RACP_RESPONSE_NO_RECORDS_FOUND);
            else if (ERR_STA_OK == enRet)
                enRet = gls_racp_rsp_code_send(pstHandle,GLS_RACP_OPCODE_RESPONSE_CODE,stCmdInfo.u8Opcode,GLS_RACP_RESPONSE_SUCCESS);
            else if (ERR_STA_BREAK == enRet)
                break;
            else
            {
                INFO("GLS RACP Error : %d\r\n",enRet);
                break;
            }
            
            if (ERR_STA_OK != enRet)
            {
                INFO("GLS RACP Respond Failed\r\n");
                break;
            }
            
            break;
        }
        case EN_GLS_EVT_RACP_REPORT_NUM_OF_RECORDS:
        {
            stGlsRacpVal_t stCmdInfo = pstHandle->stRacpCmdInfo;
            uint16_t u16NumOfRecords = 0;
            if (GLS_RACP_OPERATOR_ALL == stCmdInfo.u8Operator)
            {
                INFO("GLS Report Number of All Stored Resords\n");
                enRet = gls_racp_record_number_of_all_get(pstHandle,&u16NumOfRecords);
            }
            else if (GLS_RACP_OPERATOR_LESS_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MaxVal;
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("GLS Report Number of Stored Resords <= 0x%04X\n",u16MaxVal);
                enRet = gls_racp_record_number_of_less_or_equal_get(pstHandle,u16MaxVal,&u16NumOfRecords);
            }
            else if (GLS_RACP_OPERATOR_GREATER_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("GLS Report Number of Stored Resords >= 0x%04X\n",u16MinVal);
                enRet = gls_racp_record_number_of_greater_or_equal_get(pstHandle,u16MinVal,&u16NumOfRecords);
            }
            else if (GLS_RACP_OPERATOR_WITHIN_RANGE_OF == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal,u16MaxVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],2);
                INFO("GLS Report Number of Stored Resords >= 0x%04X && <= 0x%04X\n",u16MinVal,u16MaxVal);
                enRet = gls_racp_record_number_of_range_get(pstHandle,u16MinVal,u16MaxVal,&u16NumOfRecords);
            }
            else if (GLS_RACP_OPERATOR_FIRST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("GLS Report Number of First Stored Resord\n");
                enRet = gls_racp_record_number_of_first_get(pstHandle,&u16NumOfRecords);
            }
            else if (GLS_RACP_OPERATOR_LAST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("GLS Report Number of Last Stored Resord\n");
                enRet = gls_racp_record_number_of_last_get(pstHandle,&u16NumOfRecords);
            }
            else
            {
                INFO("Unknown RACP Operator\n");
                break;
            }
            
            if (enRet == ERR_STA_BREAK)
                break;
            
            INFO("GLS Report Number of Records : %u\r\n",u16NumOfRecords);
            enRet = gls_racp_rsp_code_send(pstHandle,GLS_RACP_OPCODE_RESPONSE_NUM_OF_STROED_RECORDS,u16NumOfRecords&0xFF,u16NumOfRecords>>8);
            if (ERR_STA_OK != enRet)
            {
                INFO("GLS RACP Respond Failed\r\n");
                break;
            }
            
            break;
        }
        case EN_GLS_EVT_RACP_DELETE_STORED_RECORDS:
        {
            stGlsRacpVal_t stCmdInfo = pstHandle->stRacpCmdInfo;
            uint16_t u16NumOfRecords = 0;
            if (GLS_RACP_OPERATOR_ALL == stCmdInfo.u8Operator)
            {
                INFO("GLS Delete All Stored Resords\n");
                enRet = gls_racp_record_all_delete(pstHandle);
            }
            else if (GLS_RACP_OPERATOR_LESS_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MaxVal;
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("GLS Delete Stored Resords <= 0x%04X\n",u16MaxVal);
                enRet = gls_racp_record_less_or_equal_delete(pstHandle,u16MaxVal);
            }
            else if (GLS_RACP_OPERATOR_GREATER_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("GLS Delete Stored Resords >= 0x%04X\n",u16MinVal);
                enRet = gls_racp_record_greater_or_equal_delete(pstHandle,u16MinVal);
            }
            else if (GLS_RACP_OPERATOR_WITHIN_RANGE_OF == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal,u16MaxVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[GLS_RACP_OPERAND_FILTER_PARAM_IDX],2);
                INFO("GLS Delete Stored Resords >= 0x%04X && <= 0x%04X\n",u16MinVal,u16MaxVal);
                enRet = gls_racp_record_range_of_delete(pstHandle,u16MinVal,u16MaxVal);
            }
            else if (GLS_RACP_OPERATOR_FIRST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("GLS Delete First Stored Resord\n");
                enRet = gls_racp_record_first_delete(pstHandle);
            }
            else if (GLS_RACP_OPERATOR_LAST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("GLS Delete Last Stored Resord\n");
                enRet = gls_racp_record_last_delete(pstHandle);
            }
            else
            {
                INFO("Unknown RACP Operator\n");
                break;
            }
            
            if (enRet == ERR_STA_BREAK)
                break;
            else if (enRet == ERR_DATA_NOT_FOUND)
                enRet = gls_racp_rsp_code_send(pstHandle,GLS_RACP_OPCODE_RESPONSE_CODE,stCmdInfo.u8Opcode,GLS_RACP_RESPONSE_NO_RECORDS_FOUND);
            else if (enRet == ERR_STA_OK)
                enRet = gls_racp_rsp_code_send(pstHandle,GLS_RACP_OPCODE_RESPONSE_CODE,stCmdInfo.u8Opcode,GLS_RACP_RESPONSE_SUCCESS);
            else
            {
                INFO("GLS RACP Error : %d\r\n",enRet);
                break;
            }
            if (ERR_STA_OK != enRet)
            {
                INFO("GLS RACP Respond Failed\r\n");
                break;
            }
            break;
        }
        default:break;
    }
    pstHandle->isRacpRunning = false;
}

/**********************************************************************************************************************
 * @brief  GLS Event Handle Process(App Task).
 * @param  pstAppMsg: Module Message.
 *
 * @return None.
 *********************************************************************************************************************/
static void gls_event_process(stAppMsg_t *pstAppMsg)
{
    uint8_t u8Event = pstAppMsg->u8Event;
    stGlsHandle_t *pstHandle = (stGlsHandle_t *)pstAppMsg->p;
    
    switch(u8Event)
    {
        case EN_GLS_EVT_RACP_REPORT_RECORDS:
        case EN_GLS_EVT_RACP_REPORT_NUM_OF_RECORDS:
        case EN_GLS_EVT_RACP_DELETE_STORED_RECORDS:
        {
            gls_racp_event_process(u8Event,pstHandle);
            break;
        }
        default:
            INFO("GLS Unknown Event\n");
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
 * @brief  GLS Device Time Init.
 *
 * @return None.
 *********************************************************************************************************************/
static void gls_time_init(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint32_t u32Sec = 0;
    uint16_t u16SstFlag;
    
    // Calendar Default Time
    gstCalendar.u16Year = 2024;
    gstCalendar.u8Mon = 1;
    gstCalendar.u8Day = 5;
    gstCalendar.u8Hour = 16;
    gstCalendar.u8Min = 35;
    gstCalendar.u8Sec = 9;
    gstCalendar.u8Wday = 4;
    
    // RTC Init&Start
    rtc_start();
    // Calendar Init
    calendar_init(&gstCalendar);
    
    INFO("GLS Device System Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
        gstCalendar.u16Year,gstCalendar.u8Mon,gstCalendar.u8Day,gstCalendar.u8Hour,gstCalendar.u8Min,gstCalendar.u8Sec);
}
/**********************************************************************************************************************
 * @brief  Set Wakeup Source.
 *
 * @return None.
 *********************************************************************************************************************/
static void app_set_wakeup_source(void)
{
    // 1. set gpio mode
    rom_hw_gpio_set_pin_input_output(GPIO_PORT_KEY,GPIO_PIN_KEY,GPIO_MODE_INPUT);

    // 2. set input pin pull mode
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_KEY,GPIO_PIN_KEY,GPIO_PULL_UP);

    // 3. set input pin both edges interrupt
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_CP,GPIO_IRQ2);
    rom_hw_gpio_set_pin_interrupt_type(GPIO_PORT_KEY,GPIO_PIN_KEY,GPIO_INT_CH2,GPIO_INT_BOTH_EDGE);

    // 4. set input pin wake up source
    rom_hw_gpio_set_pin_wakeup_debounce(2,GPIO_WAKEUP_DEB_UNIT_1MS);
    rom_hw_gpio_enable_pin_wakeup(GPIO_PORT_KEY,GPIO_PIN_KEY,GPIO_WAKEUP_LOW_LEVEL);
    rom_hw_pmu_set_gpio_wakeup_source(LUT_INDEX_KEY,LUT_TRIG_ID_GPIOB,GPIO_PIN_KEY,
                                          LUT_ACT_PD_SYS_ON|LUT_ACT_DCXO_HCLK_ON|LUT_ACT_CP_IRQ_EN);

    // 5. enable input interrupt
    rom_hw_gpio_clear_pin_interrupt_flag(GPIO_PORT_KEY,GPIO_PIN_KEY);
    rom_hw_gpio_enable_pin_interrupt(GPIO_PORT_KEY,GPIO_PIN_KEY);

    NVIC_ClearPendingIRQ(GPIO_IRQ2);
    NVIC_SetPriority(GPIO_IRQ2,0x3);
    NVIC_EnableIRQ(GPIO_IRQ2);
}
static void gls_example_add_data(void *pContext)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    static uint16_t u16SeqNum = 0;

    calendar_period_get_time(&gstCalendar);
    
    stGlsMeasRec_t stRecord;
    
    stRecord.u8Flags = 0;
    stRecord.u8Flags |= GLS_MEAS_FLAGS_GLUCOSE_CONCENTRATION_AND_TYPE_SAMPLE_LOCATION;
    stRecord.u8Flags |= GLS_MEAS_FLAGS_TIME_OFFSET;
		//stRecord.u8Flags |= GLS_MEAS_FLAGS_GLUCOSE_UNITS;//kg/l->mol/l
    stRecord.u16GlucoseConcentration = (uint16_t )(rom_get_rand()%2047);

    stRecord.stTypeSampleLocation.u8Type = GLS_MEAS_TYPE_ARTERIAL_PLASMA;
    stRecord.stTypeSampleLocation.u8SampleLocation = GLS_MEAS_SAMP_LOCATION_FINGER;
    stRecord.u16SequenceNumber = u16SeqNum++;
    
    stRecord.stBaseTime.u16Year     = gstCalendar.u16Year;
    stRecord.stBaseTime.u8Month     = gstCalendar.u8Mon;
    stRecord.stBaseTime.u8Day       = gstCalendar.u8Day;
    stRecord.stBaseTime.u8Hour      = gstCalendar.u8Hour;
    stRecord.stBaseTime.u8Minute    = gstCalendar.u8Min;
    stRecord.stBaseTime.u8Second    = gstCalendar.u8Sec;
    
    if (true == is_ble_connected())
    {
        enRet = gls_meas_send(&gstGlsHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("GLS Send Failed\n");
            return;
        }
    }

    enRet = gls_db_record_add(&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("GLS Database is Full\r\n");
        return;
    }

    INFO("Glucose Concentration : %f Kg/L\n",sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)));
    INFO("GLS Record Add to Database Successful\r\n");
    INFO("GLS Database Number of Stored Record : %u\r\n",gls_db_get_record_num());
}
static void gls_example_add_data_uart(float fGlucoseConcentration)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    static uint16_t u16SeqNum = 0;

    calendar_period_get_time(&gstCalendar);
    
    stGlsMeasRec_t stRecord;
    
    stRecord.u8Flags = 0;
    stRecord.u8Flags |= GLS_MEAS_FLAGS_GLUCOSE_CONCENTRATION_AND_TYPE_SAMPLE_LOCATION;
    stRecord.u8Flags |= GLS_MEAS_FLAGS_TIME_OFFSET;
		//stRecord.u8Flags |= GLS_MEAS_FLAGS_GLUCOSE_UNITS;//kg/l->mol/l
    //stRecord.u16GlucoseConcentration = (uint16_t )(rom_get_rand()%2047);
		stRecord.u16GlucoseConcentration = (uint16_t )fGlucoseConcentration;
    stRecord.stTypeSampleLocation.u8Type = GLS_MEAS_TYPE_ARTERIAL_PLASMA;
    stRecord.stTypeSampleLocation.u8SampleLocation = GLS_MEAS_SAMP_LOCATION_FINGER;
    stRecord.u16SequenceNumber = u16SeqNum++;
    
    stRecord.stBaseTime.u16Year     = gstCalendar.u16Year;
    stRecord.stBaseTime.u8Month     = gstCalendar.u8Mon;
    stRecord.stBaseTime.u8Day       = gstCalendar.u8Day;
    stRecord.stBaseTime.u8Hour      = gstCalendar.u8Hour;
    stRecord.stBaseTime.u8Minute    = gstCalendar.u8Min;
    stRecord.stBaseTime.u8Second    = gstCalendar.u8Sec;
    
    if (true == is_ble_connected())
    {
        enRet = gls_meas_send(&gstGlsHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("GLS Send Failed\n");
            return;
        }
    }

    enRet = gls_db_record_add(&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("GLS Database is Full\r\n");
        return;
    }

    INFO("Glucose Concentration UART: %f Kg/L\n",sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)));
    INFO("GLS Record Add to Database Successful\r\n");
    INFO("GLS Database Number of Stored Record : %u\r\n",gls_db_get_record_num());
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
    float fGlucoseConcentration;
 //INFO("pu8Data=%s\n",pu8Data);
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
 INFO("fGlucoseConcentration1=%f\n",fGlucoseConcentration);
    /* Parse Data */
    if (false == str_to_float((const char *)pu8Data,&fGlucoseConcentration))
    {
        INFO("String To Float Failed\n");
        return;
    }
     INFO("fGlucoseConcentration2=%f\n",fGlucoseConcentration);
    gls_example_add_data_uart(fGlucoseConcentration);
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
 * @brief  GLS Device Application Main.
 * 
 * @return None
 *********************************************************************************************************************/
void app_gls(void)
{
    osStatus_t status = osOK;
    stAppMsg_t stAppMsg;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    INFO("---------------GLS Profile Example----------------\n");
    
    // 1. Component init
    msg_queue_init();
    gls_time_init();
    gls_db_init();

    // 2. Init Ble
    ble_init();
    ble_event_init(ble_event_callback);
    ble_peripheral_init();
    //read_dev_info();
    // 3. Add Service
    ble_dis_init();
    ble_bas_init(get_battery_level); 
    // Add GLS Sensor Feature
    // Refer to GLS_FEATURE_SUPPORT_* in "ble_gls.h"
    gstGlsHandle.u16Feature = 0;
    enRet = ble_gls_init(&gstGlsHandle,gls_event_callback);
    if (ERR_STA_OK != enRet)
    {
        PRINTF("GLS Init Failed\n");
        return;
    }
//    
		enRet = uart_init(uart_recv_callback);
    if (enRet != ERR_STA_OK)
    {
        INFO("Uart Init Failed\r\n");
    }
    uart_send_bytes((uint8_t *)"Uart Init Successful\r\n",strlen("Uart Init Successful\r\n"));
		
		
		
		
    // 4. Start Ble Pair Advertising
    start_pair_adv();

    // 5. Create Send GLS Measurement App Timer 
    app_timer_create(&gstGlsMeasTimer,APP_TIMER_MODE_REPEAT,gls_meas_timer_timeout);

    // 6. Create and Start Example Timer
    app_timer_create(&gstGlsExampleTimer,APP_TIMER_MODE_REPEAT,gls_example_add_data);
    app_timer_start(&gstGlsExampleTimer,5 * 1000,NULL);
        //app_set_wakeup_source();
				
				
				
    while(1)
    {
        // 7. Wait for Event
        status = osMessageQueueGet(gosMsgId, &stAppMsg, NULL, osWaitForever);
        if (osOK != status)
        {
            INFO("GLS Message Queue Get Failed \n");
            continue;
        }
        switch(stAppMsg.u8MsgModule)
        {
            case EN_MSG_MODULE_BLE:
            {
                ble_event_process(&stAppMsg);
                break;
            }
            case EN_MSG_MODULE_GLS:
            {
                gls_event_process(&stAppMsg);
                break;
            }
            default:break;
        }
    }
}
  