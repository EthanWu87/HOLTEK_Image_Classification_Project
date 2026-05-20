/*************************************************************************************************************
 * @file    app_cgm_cp.c
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
#include "hw_gpio.h"
#include "hw_pmu.h"
#include "hw_sys_ctrl.h"

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "app_timer.h"
#include "linkqueue.h"
#include "uart.h"
#include "ota.h"
#include "rand.h"
#include "calendar.h"
#include "rtc.h"
#include "mmu.h"
#include "ipc.h"

#include "ble_init.h"
#include "ble_peripheral.h"
#include "ble_event.h"
#include "ble_cb_event_def.h"
#include "ble_dis.h"
#include "ble_bas.h"
#include "tt_service.h"
#include "ota_service.h"
#include "ble_cts.h"
#include "cgm_service.h"
#include "cgms_racp.h"
#include "cgms_racp_process.h"
#include "cgms_db.h"
#include "cgms_utility.h"

#include "gap_api.h"
#include "gatt_client_api.h"


#if SPI_CMD_SUPPORT

#include "spi_master.h"

#define SPI_CMD_BEGIN           (0x5A)
#define SPI_EVT_BEGIN           (0xA5)
#define SPI_CMD_EVT_END         (0xFF)
#define SPI_CMD_MIN_SIZE        (1 + 1 + 1)     /* Begin + length + end */
#define SPI_EVT_MIN_SIZE        (1 + 1 + 1)     /* Begin + length + end */
#define SHARE_DATA_SIZE         (256)

typedef enum
{
    EN_SPI_CMD_READ_3_BYTES     = 0x01,
    EN_SPI_CMD_READ_256_BYTES   = 0x02,
}EN_SPI_CMD_T;

static uint8_t gpu8SharedData[SHARE_DATA_SIZE];

static inline bool is_valid_spi_cmd(uint8_t *pu8Data,uint16_t u16DataLen)
{
    if (NULL == pu8Data || SPI_CMD_MIN_SIZE > u16DataLen)
        return false;

    if (SPI_CMD_BEGIN != pu8Data[0] || SPI_CMD_EVT_END != pu8Data[u16DataLen -1])
        return false;
        
    return true;
}

static inline bool is_valid_spi_event_data(uint8_t *pu8Data,uint16_t u16DataLen)
{
    uint16_t u16Len = 0;
    
    if (NULL == pu8Data || SPI_EVT_MIN_SIZE > u16DataLen)
        return false;
    
    u16Len = SPI_EVT_MIN_SIZE + pu8Data[1] + 1;
    
    if (u16DataLen != u16Len)
        return false;

    if (SPI_EVT_BEGIN != pu8Data[0] || SPI_CMD_EVT_END != pu8Data[u16DataLen -1])
        return false;
        
    return true;
}

#endif

#define APP_MSG_NUM                 (5)

typedef enum
{
    EN_MSG_MODULE_BLE  = 0x00,
    EN_MSG_MODULE_CGMS,
    EN_MSG_MODULE_OTA,
    
#if SPI_CMD_SUPPORT
    EN_MSG_MODULE_SPI,
#endif
    
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

/* CGMS Variables */
static stCgmsHandle_t gstCgmsHandle;
static stAppTimerNode_t gstCgmsMeasTimer;
//static uint16_t gu16TimeOffsetMin;
static stCalendar_t gstCalendar;
static stCtsInit_t gstCtsInit;
static bool gbKeyDown = false;
static bool gbUpgrading = false;

/* Link Queue for OTA Data */
static stLinkQueue_t gpstOtaQueue = NULL;
static stAppTimerNode_t gstConnIntvTimer;


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

static EN_ERR_STA_T cgms_send_meas_by_float(float fGlucoseConcentration)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    sfloat_t sfloatData;
    uint16_t u16Data;
    
    INFO("Glucose Concentration : %f mg/dL\n",fGlucoseConcentration);
    sfloatData = float_to_sfloat(fGlucoseConcentration);
    u16Data = sfloat_to_u16(sfloatData);
    stCgmsMeasRec_t stRecord;
    stRecord.u8Flags = 0;
    stRecord.u16GlucoseConcentration = u16Data;
    stRecord.u16TimeOffset = gstCgmsHandle.stStatus.u16TimeOffset++;

    enRet = cgms_meas_send(&gstCgmsHandle,&stRecord);
    if(ERR_STA_OK != enRet)
    {
        INFO("CGMS Send Measurement Failed\r\n");
        return enRet;
    }
    
    enRet = cgms_db_record_add(&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("CGMS Database is Full\r\n");
        return enRet;
    }
    
    INFO("CGMS Record Add to Database Successful\r\n");
    INFO("CGMS Database Number of Stored Record : %u\r\n",cgms_db_get_record_num());
    
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Calendar transform to Session Start Time.
 * @param  pstCalendar: Calendar Handle.
 * @param  pstSst: Session Start Time Parameters.
 *
 * @return None.
 *********************************************************************************************************************/
static void calendar_to_sst(const pstCalendar_t pstCalendar,stCgmsSessionStartTime_t *pstSst)
{
    pstSst->u16Year = pstCalendar->u16Year;
    pstSst->u8Month = pstCalendar->u8Mon;
    pstSst->u8Day = pstCalendar->u8Day;
    pstSst->u8Hour = pstCalendar->u8Hour;
    pstSst->u8Minute = pstCalendar->u8Min;
    pstSst->u8Second = pstCalendar->u8Sec;
}

/**********************************************************************************************************************
 * @brief  Session Start Time transform to Calendar.
 * @param  pstSst: Session Start Time Parameters.
 * @param  pstCalendar: Calendar Handle.
 *
 * @return None.
 *********************************************************************************************************************/
static void sst_to_calendar(const stCgmsSessionStartTime_t *pstSst,pstCalendar_t pstCalendar)
{
    pstCalendar->u16Year  = pstSst->u16Year;
    pstCalendar->u8Mon    = pstSst->u8Month;
    pstCalendar->u8Day    = pstSst->u8Day;
    pstCalendar->u8Hour   = pstSst->u8Hour;
    pstCalendar->u8Min    = pstSst->u8Minute;
    pstCalendar->u8Sec    = pstSst->u8Second;
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
        .name = "App CGMS Msg Queue",
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
 * @brief  Send Message of CGM Service(LL Task Context).
 * @param  u8Event: Module Event.
 * @param  pu8Data: Event Data.
 * @param  u16DataLen: the Length of Event Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void cgms_event_callback(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen)
{
    if(!send_msg_app_task(EN_MSG_MODULE_CGMS, u8Event, pu8Data, u16DataLen))
    {
        INFO("Send CGM Message Failed\r\n");
    }
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
//  EN_ERR_STA_T enRet = ERR_STA_OK;
    float fGlucoseConcentration;

    if (true == gstCgmsHandle.isRacpRunning)
    {
        INFO("Racp is Running,Please Try Again Later\r\n");
        return;
    }
    
    if (false == gstCgmsHandle.isSessionStart)
    {
        INFO("Please Start Session and Try Again\r\n");
        return;
    }
    
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
    if (false == str_to_float((const char *)pu8Data,&fGlucoseConcentration))
    {
        INFO("String To Float Failed\n");
        return;
    }
    
    cgms_send_meas_by_float(fGlucoseConcentration);
}

/**********************************************************************************************************************
 * @brief  Data Receive Callback of OTA Service(LL Task Context).
 * @param  pu8Data: Receive Data.
 * @param  u16DataLen: the Length of Receive Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void ota_recv_callback(uint8_t* pu8Data, uint16_t u16DataLen)
{
    uint8_t u8Ret = link_queue_put(gpstOtaQueue,pu8Data,u16DataLen);
    if (0 != u8Ret)
    {
        INFO("Link Queue Put Failed\n");
        return;
    }
    if(!send_msg_app_task(EN_MSG_MODULE_OTA, 0, NULL, 0))
    {
        INFO("Send OTA Message Failed\r\n");
    }
}

/**********************************************************************************************************************
 * @brief  Data Receive Callback of Transparent Transmission Service(LL Task Context).
 * @param  pu8Data: Receive Data.
 * @param  u16DataLen: the Length of Receive Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void tt_recv_callback(uint8_t *pu8Data,uint16_t u16DataLen)
{
    INFO("TT Receive : ");
    for (int i=0;i<u16DataLen;i++)
        PRINTF("0x%02X ",pu8Data[i]);
    PRINTF("\r\n");
    
    u16DataLen -= 1;
    
    switch(pu8Data[0])
    {
        case TT_CMD_WRITE_DEV_NAME:
        {
            uint8_t u8Idx;
            uint8_t u8DevName[TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN+1] = {0};

            if (TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN < u16DataLen || 1 > u16DataLen)
                return;

            for(u8Idx = 1;u8Idx < u16DataLen;u8Idx++)
            {
                if (' ' > pu8Data[u8Idx])
                    break;
            }
            
            if (1 == u8Idx)
            {
                INFO("Invaild Dev Name\n");
                return;
            }
            INFO("u8Idx : %u\r\n",u8Idx);
            memcpy(u8DevName,&pu8Data[1],u8Idx);
            
            if (ERR_STA_OK != mmu_write(EN_MMU_BLE_ADV_DEV_NAME,0,u8DevName,TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN,true))   
            {
                INFO("MMU Write Failed\n");
                return;
            }

            INFO("MMU Write Dev Name : %s\n",(const char *)u8DevName);
            
            ble_set_dev_name((const char *)u8DevName);

            break;
        }
        case TT_CMD_READ_DEV_NAME:
        {
            EN_ERR_STA_T enRet;
            uint8_t u8DevName[TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN + 1] = {0};

            if (0 < u16DataLen)
                return;

            if (ERR_STA_OK != mmu_read(EN_MMU_BLE_ADV_DEV_NAME,0,u8DevName,TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN))
            {
                INFO("Ble Dev Name Not Found in flash\n");
                return;
            }
            
            enRet = tt_serivce_send(get_ble_conn_handle(),u8DevName,strlen((const char *)u8DevName));
            if (ERR_STA_OK != enRet)
            {
                INFO("TT Service Send Failed\n");
                return;
            }

            INFO("MMU Read Dev Name : %s\n",(const char *)u8DevName);

            break;
        }
        case TT_CMD_WRITE_ADV_INTERVAL:
        {
            uint16_t u16AdvInterval;

            if (TT_CMD_WRITE_ADV_INTERVAL_PARAM_LEN != u16DataLen)
                return;

            u16AdvInterval = BUILD_UINT16(pu8Data[1],pu8Data[2]);
            if (0x20 > u16AdvInterval || 0x4000 < u16AdvInterval)
            {
                INFO("Invaild Adv Interval\n");
                return;
            }

            if (ERR_STA_OK != mmu_write(EN_MMU_BLE_ADV_INTERVAL,0,&pu8Data[1],u16DataLen,true))   
            {
                INFO("MMU Write Failed\n");
                return;
            }

            INFO("MMU Write Adv Interval : %.3f ms\n",u16AdvInterval * 0.625);

            ble_set_adv_interval(u16AdvInterval);

            break;
        }
        case TT_CMD_READ_ADV_INTERVAL:
        {
            EN_ERR_STA_T enRet;
            uint16_t u16AdvInterval;
            if (0 < u16DataLen)
                return;

            if (ERR_STA_OK != mmu_read(EN_MMU_BLE_ADV_INTERVAL,0,(uint8_t *)&u16AdvInterval,2))
            {
                INFO("Ble Adv Interval Not Found in flash\n");
                return;
            }

            enRet = tt_serivce_send(get_ble_conn_handle(),(uint8_t *)&u16AdvInterval,TT_CMD_WRITE_ADV_INTERVAL_PARAM_LEN);
            if (ERR_STA_OK != enRet)
            {
                INFO("TT Service Send Failed\n");
                return;
            }

            INFO("MMU Read Adv Interval : %.3f ms\n",u16AdvInterval * 0.625);

            break;
        }
        default:break;
    }
}

/**********************************************************************************************************************
 * @brief  OTA Event Handle.
 * @param  enEvt: OTA Event.
 *
 * @return None.
 *********************************************************************************************************************/
static void ota_event_handler(EN_OTA_EVT_T enEvt)
{
    switch(enEvt)
    {
        case EN_OTA_EVT_GET_FIRMWARE_INFO:
            gbUpgrading = true;
            INFO("[EN_OTA_EVT_GET_FIRMWARE_INFO]\n");
            break;
        case EN_OTA_EVT_HANDSHAKE:
            INFO("[EN_OTA_EVT_HANDSHAKE]\n");
            break;
        case EN_OTA_EVT_UPGRADE_REQUEST:
            INFO("[EN_OTA_EVT_UPGRADE_REQUEST]\n");
            break;
        case EN_OTA_EVT_UPGRADE_CODE:
            //INFO("[EN_OTA_EVT_UPGRADE_CODE]\n");
            break;
        case EN_OTA_EVT_UPGRADE_FINISH:
            INFO("[EN_OTA_EVT_UPGRADE_FINISH]\n");
            break;
        case EN_OTA_EVT_CHIP_RESTART:
            INFO("[EN_OTA_EVT_CHIP_RESTART]\n");
            ota_rsp_restart(true,500);
            gbUpgrading = false;
            break;
        default:
            break;
    }
}

/**********************************************************************************************************************
 * @brief  App Timer Timeout Callback(Interrupt Context).
 * @param  pContext: Private Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void cgms_meas_timer_timeout(void *pContext)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    gstCgmsHandle.stStatus.u16TimeOffset++;

    INFO("Time Offset Minutes : %u\r\n",gstCgmsHandle.stStatus.u16TimeOffset);

    if (0 != (gstCgmsHandle.stStatus.u16TimeOffset % gstCgmsHandle.u8CommIntv))
        return;

    stCgmsMeasRec_t stRecord;
    stRecord.u8Flags = 0;
    stRecord.u16GlucoseConcentration = (uint16_t )rom_get_rand();
    stRecord.u16TimeOffset = gstCgmsHandle.stStatus.u16TimeOffset;
    stRecord.stStatus.u8CalTemp = 0;
    stRecord.stStatus.u8Status = 0;
    stRecord.stStatus.u8Warning = 0;
    enRet = cgms_meas_send(&gstCgmsHandle,&stRecord);
    if(ERR_STA_OK != enRet)
    {
        INFO("CGMS Send Measurement Failed\r\n");
        return;
    }

    enRet = cgms_db_record_add(&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("CGMS Database is Full\r\n");
        return;
    }

    INFO("Glucose Concentration : %f mg/dL\n",sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)));
    INFO("CGMS Record Add to Database Successful\r\n");
    INFO("CGMS Database Number of Stored Record : %u\r\n",cgms_db_get_record_num());
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
            gstCgmsHandle.u16ConnHandle = u16ConnHandle;
            app_timer_start(&gstConnIntvTimer,1000,NULL);
            break;
        }
        case MSG_BLE_DISCONNECTED_IND:
        {   
            gstCgmsHandle.u16ConnHandle = 0;
            start_pair_adv();
            break;
        }
        default:break;
    }
}

/**********************************************************************************************************************
 * @brief  CGMS SOCP Event Handle Process(App Task).
 * @param  u8Event: Module Event.
 * @param  pstHandle: CGMS Global Handle.
 *
 * @return None.
 *********************************************************************************************************************/
static void cgms_socp_event_process(uint8_t u8Event,stCgmsHandle_t *pstHandle)
{
    switch(u8Event)
    {
        case EN_CGMS_EVT_SOCP_START_SESSION:
        {
            if (0 != pstHandle->u8CommIntv)
            {
                uint32_t u32Sec;

                calendar_period_get_time(&gstCalendar);
                calendar_to_sst(&gstCalendar,&pstHandle->stSst);
                calendar_utc_to_second(&gstCalendar,&u32Sec);
                if (ERR_STA_OK != mmu_write(EN_MMU_CGMS_SOCP_SST,0,(uint8_t *)&u32Sec,sizeof(uint32_t),true))
                {
                    INFO("MMU Write CGMS SOCP Session Start Time Failed\n");
                }

                cgms_db_record_delete_all();

                app_timer_start(&gstCgmsMeasTimer,1 * 60 *1000,NULL);
                INFO("CGMS SOCP Start Session\n");
                INFO("CGM Device Session Start Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
                    gstCgmsHandle.stSst.u16Year,gstCgmsHandle.stSst.u8Month,gstCgmsHandle.stSst.u8Day,gstCgmsHandle.stSst.u8Hour,
                    gstCgmsHandle.stSst.u8Minute,gstCgmsHandle.stSst.u8Second);
                INFO("SOCP Session Timer Start,Communication Interval : %u Minutes\n",pstHandle->u8CommIntv);
            }
            else
                INFO("[ERROR] Communication Interval is Zero\n");
            break;
        }
        case EN_CGMS_EVT_SOCP_STOP_SESSION:
        {
            INFO("CGMS SOCP Stop Session\n");
            pstHandle->stStatus.u16TimeOffset = 0;
            app_timer_stop(&gstCgmsMeasTimer);
            INFO("SOCP Session Timer Stop\r\n");
            break;
        }
        case EN_CGMS_EVT_SOCP_SET_COMM_INTV:
        {
            INFO("CGMS SOCP Communication Interval Changed,Communication Interval : %u Minutes\n",pstHandle->u8CommIntv);
            
            if (false == gstCgmsHandle.isSessionStart)
                return;

            app_timer_stop(&gstCgmsMeasTimer);
            app_timer_start(&gstCgmsMeasTimer,1 * 60 *1000,NULL);

            break;
        }
        default:break;
    }
}

/**********************************************************************************************************************
 * @brief  CGMS RACP Event Handle Process(App Task).
 * @param  u8Event: Module Event.
 * @param  pstHandle: CGMS Global Handle.
 *
 * @return None.
 *********************************************************************************************************************/
static void cgms_racp_event_process(uint8_t u8Event,stCgmsHandle_t *pstHandle)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    switch(u8Event)
    {
        case EN_CGMS_EVT_RACP_REPORT_RECORDS:
        {
            stCgmsRacpVal_t stCmdInfo = pstHandle->stRacpCmdInfo;
            if (CGMS_RACP_OPERATOR_ALL == stCmdInfo.u8Operator)
            {
                INFO("CGMS Report All Stored Resords\n");
                enRet = cgms_racp_record_all_report(pstHandle);
            }
            else if (CGMS_RACP_OPERATOR_LESS_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MaxVal;
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("CGMS Report <= 0x%04X Stored Resords\n",u16MaxVal);
                enRet = cgms_racp_record_less_or_equal_report(pstHandle,u16MaxVal);
            }
            else if (CGMS_RACP_OPERATOR_GREATER_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("CGMS Report >= 0x%04X Stored Resords\n",u16MinVal);
                enRet = cgms_racp_record_greater_or_equal_report(pstHandle,u16MinVal);
            }
            else if (CGMS_RACP_OPERATOR_WITHIN_RANGE_OF == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal,u16MaxVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],2);
                INFO("CGMS Report >= 0x%04X && <= 0x%04X Stored Resords\n",u16MinVal,u16MaxVal);
                enRet = cgms_racp_record_range_of_report(pstHandle,u16MinVal,u16MaxVal);
            }
            else if (CGMS_RACP_OPERATOR_FIRST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("CGMS Report First Stored Resord\n");
                enRet = cgms_racp_record_first_report(pstHandle);
            }
            else if (CGMS_RACP_OPERATOR_LAST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("CGMS Report Last Stored Resord\n");
                enRet = cgms_racp_record_last_report(pstHandle);
            }
            else
            {
                INFO("Unknown RACP Operator\n");
            }
            
            if (ERR_DATA_NOT_FOUND == enRet)
                enRet = cgms_racp_rsp_code_send(pstHandle,CGMS_RACP_OPCODE_RESPONSE_CODE,stCmdInfo.u8Opcode,CGMS_RACP_RESPONSE_NO_RECORDS_FOUND);
            else if (ERR_STA_OK == enRet)
                enRet = cgms_racp_rsp_code_send(pstHandle,CGMS_RACP_OPCODE_RESPONSE_CODE,stCmdInfo.u8Opcode,CGMS_RACP_RESPONSE_SUCCESS);
            else if (ERR_STA_BREAK == enRet)
                break;
            else
            {
                INFO("CGMS RACP Error : %d\r\n",enRet);
                break;
            }
            
            if (ERR_STA_OK != enRet)
            {
                INFO("CGMS RACP Respond Failed\r\n");
                break;
            }
            
            break;
        }
        case EN_CGMS_EVT_RACP_REPORT_NUM_OF_RECORDS:
        {
            stCgmsRacpVal_t stCmdInfo = pstHandle->stRacpCmdInfo;
            uint16_t u16NumOfRecords = 0;
            if (CGMS_RACP_OPERATOR_ALL == stCmdInfo.u8Operator)
            {
                INFO("CGMS Report Number of All Stored Resords\n");
                enRet = cgms_racp_record_number_of_all_get(pstHandle,&u16NumOfRecords);
            }
            else if (CGMS_RACP_OPERATOR_LESS_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MaxVal;
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("CGMS Report Number of Stored Resords <= 0x%04X\n",u16MaxVal);
                enRet = cgms_racp_record_number_of_less_or_equal_get(pstHandle,u16MaxVal,&u16NumOfRecords);
            }
            else if (CGMS_RACP_OPERATOR_GREATER_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("CGMS Report Number of Stored Resords >= 0x%04X\n",u16MinVal);
                enRet = cgms_racp_record_number_of_greater_or_equal_get(pstHandle,u16MinVal,&u16NumOfRecords);
            }
            else if (CGMS_RACP_OPERATOR_WITHIN_RANGE_OF == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal,u16MaxVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],2);
                INFO("CGMS Report Number of Stored Resords >= 0x%04X && <= 0x%04X\n",u16MinVal,u16MaxVal);
                enRet = cgms_racp_record_number_of_range_get(pstHandle,u16MinVal,u16MaxVal,&u16NumOfRecords);
            }
            else if (CGMS_RACP_OPERATOR_FIRST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("CGMS Report Number of First Stored Resord\n");
                enRet = cgms_racp_record_number_of_first_get(pstHandle,&u16NumOfRecords);
            }
            else if (CGMS_RACP_OPERATOR_LAST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("CGMS Report Number of Last Stored Resord\n");
                enRet = cgms_racp_record_number_of_last_get(pstHandle,&u16NumOfRecords);
            }
            else
            {
                INFO("Unknown RACP Operator\n");
                break;
            }
            
            if (enRet == ERR_STA_BREAK)
                break;
            
            INFO("CGMS Report Number of Records : %u\r\n",u16NumOfRecords);
            enRet = cgms_racp_rsp_code_send(pstHandle,CGMS_RACP_OPCODE_RESPONSE_NUM_OF_STROED_RECORDS,u16NumOfRecords&0xFF,u16NumOfRecords>>8);
            if (ERR_STA_OK != enRet)
            {
                INFO("CGMS RACP Respond Failed\r\n");
                break;
            }
            
            break;
        }
        case EN_CGMS_EVT_RACP_DELETE_STORED_RECORDS:
        {
            stCgmsRacpVal_t stCmdInfo = pstHandle->stRacpCmdInfo;
//          uint16_t u16NumOfRecords = 0;
            if (CGMS_RACP_OPERATOR_ALL == stCmdInfo.u8Operator)
            {
                INFO("CGMS Delete All Stored Resords\n");
                enRet = cgms_racp_record_all_delete(pstHandle);
            }
            else if (CGMS_RACP_OPERATOR_LESS_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MaxVal;
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("CGMS Delete Stored Resords <= 0x%04X\n",u16MaxVal);
                enRet = cgms_racp_record_less_or_equal_delete(pstHandle,u16MaxVal);
            }
            else if (CGMS_RACP_OPERATOR_GREATER_OR_EQUAL == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                INFO("CGMS Delete Stored Resords >= 0x%04X\n",u16MinVal);
                enRet = cgms_racp_record_greater_or_equal_delete(pstHandle,u16MinVal);
            }
            else if (CGMS_RACP_OPERATOR_WITHIN_RANGE_OF == stCmdInfo.u8Operator)
            {
                uint16_t u16MinVal,u16MaxVal;
                u16MinVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],0);
                u16MaxVal = rom_little_endian_read_16(&pstHandle->stRacpCmdInfo.u8Operand[CGMS_RACP_OPERAND_FILTER_PARAM_IDX],2);
                INFO("CGMS Delete Stored Resords >= 0x%04X && <= 0x%04X\n",u16MinVal,u16MaxVal);
                enRet = cgms_racp_record_range_of_delete(pstHandle,u16MinVal,u16MaxVal);
            }
            else if (CGMS_RACP_OPERATOR_FIRST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("CGMS Delete First Stored Resord\n");
                enRet = cgms_racp_record_first_delete(pstHandle);
            }
            else if (CGMS_RACP_OPERATOR_LAST_RECORD == stCmdInfo.u8Operator)
            {
                INFO("CGMS Delete Last Stored Resord\n");
                enRet = cgms_racp_record_last_delete(pstHandle);
            }
            else
            {
                INFO("Unknown RACP Operator\n");
                break;
            }
            
            if (enRet == ERR_STA_BREAK)
                break;
            else if (enRet == ERR_DATA_NOT_FOUND)
                enRet = cgms_racp_rsp_code_send(pstHandle,CGMS_RACP_OPCODE_RESPONSE_CODE,stCmdInfo.u8Opcode,CGMS_RACP_RESPONSE_NO_RECORDS_FOUND);
            else if (enRet == ERR_STA_OK)
                enRet = cgms_racp_rsp_code_send(pstHandle,CGMS_RACP_OPCODE_RESPONSE_CODE,stCmdInfo.u8Opcode,CGMS_RACP_RESPONSE_SUCCESS);
            else
            {
                INFO("CGMS RACP Error : %d\r\n",enRet);
                break;
            }
            if (ERR_STA_OK != enRet)
            {
                INFO("CGMS RACP Respond Failed\r\n");
                break;
            }
            break;
        }
        default:break;
    }
    pstHandle->isRacpRunning = false;
}

/**********************************************************************************************************************
 * @brief  CGMS Event Handle Process(App Task).
 * @param  pstAppMsg: Module Message.
 *
 * @return None.
 *********************************************************************************************************************/
static void cgms_event_process(stAppMsg_t *pstAppMsg)
{
    uint8_t u8Event = pstAppMsg->u8Event;
    stCgmsHandle_t *pstHandle = (stCgmsHandle_t *)pstAppMsg->p;
    
    switch(u8Event)
    {
        case EN_CGMS_EVT_SOCP_START_SESSION:
        case EN_CGMS_EVT_SOCP_STOP_SESSION:
        case EN_CGMS_EVT_SOCP_SET_COMM_INTV:
        {
            cgms_socp_event_process(u8Event,pstHandle);
            break;
        }
        case EN_CGMS_EVT_RACP_REPORT_RECORDS:
        case EN_CGMS_EVT_RACP_REPORT_NUM_OF_RECORDS:
        case EN_CGMS_EVT_RACP_DELETE_STORED_RECORDS:
        {
            cgms_racp_event_process(u8Event,pstHandle);
            break;
        }
        case EN_CGMS_EVT_SST_SESSION_START_TIME_UPDATE:
        {
            stCalendar_t stCalendar;
            uint32_t u32Sec = 0;
            
            sst_to_calendar(&pstHandle->stSst,&stCalendar);
            calendar_utc_to_second(&stCalendar,&u32Sec);
            
            if ( ERR_STA_OK != mmu_write(EN_MMU_CGMS_SOCP_SST,0,(uint8_t *)&u32Sec,sizeof(uint32_t),true))
            {
                INFO("MMU Write CGMS SOCP Session Start Time Failed\r\n");
            }
            
            INFO("CGMS Session Start Time Update\r\n");
            INFO("CGM Device Session Start Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
                gstCgmsHandle.stSst.u16Year,gstCgmsHandle.stSst.u8Month,gstCgmsHandle.stSst.u8Day,gstCgmsHandle.stSst.u8Hour,
                gstCgmsHandle.stSst.u8Minute,gstCgmsHandle.stSst.u8Second);
            
            break;
        }
        default:
            INFO("CGMS Unknown Event\n");
    }
}

/**********************************************************************************************************************
 * @brief  OTA Event Handle Process(App Task).
 *
 * @return None.
 *********************************************************************************************************************/
static void ota_event_process(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint8_t pu8Data[OTA_PACKAGE_MAX_LEN];
    uint32_t u32PriMask;
    uint16_t u16DataLen;

    u32PriMask = __get_PRIMASK();
    __disable_irq();

    u16DataLen = link_queue_get_front_data_size(gpstOtaQueue);

    link_queue_get(gpstOtaQueue,pu8Data,u16DataLen);

    __set_PRIMASK(u32PriMask);

    enRet = ota_protocol_parse(get_ble_conn_handle(),pu8Data,u16DataLen,ota_event_handler);
    if (ERR_STA_OK != enRet)
        INFO("OTA Protocol Parse Failed\n");
}

#if SPI_CMD_SUPPORT

/**********************************************************************************************************************
 * @brief  SPI Read 3 Bytes CGM Data from SPI Slave.
 *
 * @return None.
 *********************************************************************************************************************/
static void spi_read_3_bytes_process(void)
{
    EN_ERR_STA_T enRet;
    char cTmpBuf[4] = {0};
    uint8_t u8SendData[] = {0x5A,0x02,0xFF};
    uint8_t u8RecvData[SPI_EVT_MIN_SIZE + 0x02 + 1];
    stCgmsMeasRec_t stRecord;
    float fGlucoseConcentration;
    sfloat_t sfGlucoseConcentration;
    uint16_t u16GlucoseConcentration;
    
    // Read Data
    enRet = spi_master_transmit_bytes(u8SendData,sizeof(u8SendData));
    if (ERR_STA_OK != enRet)
    {
        INFO("SPI Send Command Failed\n");
        return;
    }
    rom_delay_us(200);
    enRet = spi_master_receive_bytes(u8RecvData,sizeof(u8RecvData));
    if (ERR_STA_OK != enRet)
    {
        INFO("SPI Receive 3 Bytes Failed\n");
        return;
    }
    
    INFO("Recv Data : ");
    for(uint16_t i=0;i<sizeof(u8RecvData);i++)
        PRINTF("0x%02X ",u8RecvData[i]);
    PRINTF("\n");
    
    // Parse Data
    if (false == is_valid_spi_event_data(u8RecvData,sizeof(u8RecvData)))
    {
        INFO("Invalid SPI Event Data\n");
        return;
    }
    
    memcpy(cTmpBuf,&u8RecvData[2],3);
    
    if (false == str_to_float(cTmpBuf,&fGlucoseConcentration))
    {
        INFO("String To Float Failed\n");
        return;
    }
    
    cgms_send_meas_by_float(fGlucoseConcentration);
}

/**********************************************************************************************************************
 * @brief  SPI Read 256 Bytes CGM Data from SPI Slave.
 *
 * @return None.
 *********************************************************************************************************************/
static void spi_read_256_bytes_process(void)
{
    EN_ERR_STA_T enRet;
    uint8_t u8SendData[] = {0x5A,0xFF,0xFF};
    uint8_t u8RecvData[SPI_EVT_MIN_SIZE + 0xFF + 1];

    // Read Data
    enRet = spi_master_transmit_bytes(u8SendData,sizeof(u8SendData));
    if (ERR_STA_OK != enRet)
    {
        INFO("SPI Send Command Failed\n");
        return;
    }
    
    rom_delay_us(200);
    enRet = spi_master_receive_bytes(u8RecvData,sizeof(u8RecvData));
    if (ERR_STA_OK != enRet)
    {
        INFO("SPI Receive 256 Bytes Failed\n");
        return;
    }
    
    INFO("Recv Data : ");
    for(uint16_t i=0;i<sizeof(u8RecvData);i++)
        PRINTF("0x%02X ",u8RecvData[i]);
    PRINTF("\n");
    
    // Parse Data
    if (false == is_valid_spi_event_data(u8RecvData,sizeof(u8RecvData)))
    {
        INFO("Invalid SPI Event Data\n");
        return;
    }
    
    memcpy(gpu8SharedData,&u8RecvData[2],u8RecvData[1]+1);
    
    INFO("Valid SPI Event Data\n");
    
    // ipc cmd
    uint32_t u32SharedDataAddr = (uint32_t)&gpu8SharedData;
    ipc_send(EN_IPC_CMD_CAL_SUM,&u32SharedDataAddr,4);
}

/**********************************************************************************************************************
 * @brief  SPI Event Process.
 * @param  pstAppMsg: App Message.
 *
 * @return None.
 *********************************************************************************************************************/
static void spi_event_process(const stAppMsg_t *pstAppMsg)
{
    EN_ERR_STA_T enRet;
    
    switch(pstAppMsg->u8Event)
    {
        case EN_SPI_CMD_READ_3_BYTES:
        {
            spi_read_3_bytes_process();
            break;
        }
        case EN_SPI_CMD_READ_256_BYTES:
        {
            spi_read_256_bytes_process();
            break;
        }
        default:break;
    }
}

#endif

/**********************************************************************************************************************
 * @brief  CGM Device Time Init.
 *
 * @return None.
 *********************************************************************************************************************/
static void cgms_time_init(void)
{
//  EN_ERR_STA_T enRet = ERR_STA_OK;
    uint32_t u32Sec = 0;
//  uint16_t u16SstFlag;
    
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

    // Set CGMS Session Run Time Default Value(Unit:hour)
    gstCgmsHandle.u16Srt = 10;

    // Set CGMS Time Offset Initial Value (Represent the number of minutes the user-facing time differs from the Session Start Time)
    gstCgmsHandle.stStatus.u16TimeOffset = 0;

    // Read Old Session Start Time from Flash
    // Set Session Start Time by Collector(Clinet) or yourself(CGM Device)
    // Represent the time of the initial CGM measurement
    if (ERR_STA_OK == mmu_read(EN_MMU_CGMS_SOCP_SST,0,(uint8_t *)&u32Sec,sizeof(uint32_t)))
    {
        INFO("Use Session Start Time From Flash\n");
        stCalendar_t stCalendar;
        calendar_second_to_utc(u32Sec,&stCalendar);

        calendar_to_sst(&stCalendar,&gstCgmsHandle.stSst);
    }
    else
    {
        INFO("Use Default Session Start Time\n");
        calendar_to_sst(&gstCalendar,&gstCgmsHandle.stSst);

        calendar_utc_to_second(&gstCalendar,&u32Sec);

        if (ERR_STA_OK != mmu_write(EN_MMU_CGMS_SOCP_SST,0,(uint8_t *)&u32Sec,sizeof(uint32_t),true))
        {
            INFO("MMU Write CGMS SOCP Session Start Time Failed\r\n");
        }
    }
    // -128 Represent for Time Zone Unknown
    gstCgmsHandle.stSst.i8TimeZone = -128;
    // 255 Represent for Daylight Saving Time Unknown
    gstCgmsHandle.stSst.u8Dst = 255;

    INFO("CGM Device System Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
        gstCalendar.u16Year,gstCalendar.u8Mon,gstCalendar.u8Day,gstCalendar.u8Hour,gstCalendar.u8Min,gstCalendar.u8Sec);
    INFO("CGM Device Session Start Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
        gstCgmsHandle.stSst.u16Year,gstCgmsHandle.stSst.u8Month,gstCgmsHandle.stSst.u8Day,gstCgmsHandle.stSst.u8Hour,
        gstCgmsHandle.stSst.u8Minute,gstCgmsHandle.stSst.u8Second);
}

/**********************************************************************************************************************
 * @brief  Current Time Service Get Time Callback.
 * @param  stCtsDateTime : Current Time Service Data Time
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T ble_cts_get_time_callback(stCtsDateTime_t *stCtsDateTime)
{
//  EN_ERR_STA_T enRet = ERR_STA_OK;

    calendar_period_get_time(&gstCalendar);

    stCtsDateTime->u16Year  = gstCalendar.u16Year;
    stCtsDateTime->u8Mon    = gstCalendar.u8Mon;
    stCtsDateTime->u8Day    = gstCalendar.u8Day;
    stCtsDateTime->u8Hour   = gstCalendar.u8Hour;
    stCtsDateTime->u8Min    = gstCalendar.u8Min;
    stCtsDateTime->u8Sec    = gstCalendar.u8Sec;
    stCtsDateTime->u8Wday   = gstCalendar.u8Wday;
    stCtsDateTime->u8F256   = 0;

    INFO("CGM CTS Get System Time\r\n");
    INFO("CGM Device System Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
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

    INFO("CGM CTS Set System Time\r\n");
    INFO("CGM Device System Time : %04u-%02u-%02u %02u:%02u:%02u\r\n",
        gstCalendar.u16Year,gstCalendar.u8Mon,gstCalendar.u8Day,gstCalendar.u8Hour,gstCalendar.u8Min,gstCalendar.u8Sec);

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Determine whether have Completed All Works and Enter Sleep Mode.
 *
 * @return true : goto sleep  false : can not goto sleep.
 *********************************************************************************************************************/
bool is_app_can_goto_sleep(void)
{
    if (true == gbKeyDown)
        return false;

    if (true == gbUpgrading)
        return false;

    // Check ble.
    if (!ble_init_is_system_sleep_allowed())
        return false;

    return true;
}

/**********************************************************************************************************************
 * @brief  GPIO IRQ2 Handle.
 *
 * @return None.
 *********************************************************************************************************************/
void GPIO_IRQ2_Handler(void)
{
    uint32_t u32IntMask = 0;
    uint32_t u32Level = 0;

    rom_hw_gpio_get_pin_interrupt_flag(GPIO_PORT_KEY,GPIO_PIN_KEY,&u32IntMask);
    rom_hw_gpio_clear_pin_interrupt_flag(GPIO_PORT_KEY,GPIO_PIN_KEY);

    if (u32IntMask & GPIO_PIN_KEY)
    {
        rom_hw_gpio_get_pin_input_level(GPIO_PORT_KEY,GPIO_PIN_KEY,&u32Level);
        if (u32Level)
            gbKeyDown = false;
        else
            gbKeyDown = true;
    }
}

/**********************************************************************************************************************
 * @brief  Update connect interval timer.
 *
 * @return None.
 *********************************************************************************************************************/
static void UpdateConnIntvTimer(void *pContext)
{
    uint16_t u16ConnHandle = get_ble_conn_handle();
    // update connect interval .
    stGapConnectionUpdate_t stConnPara = {
        .u16ConnIntervalMin1250us  = MSEC_TO_UNITS(1000, UNIT_1_25_MS),
        .u16ConnIntervalMax1250us  = MSEC_TO_UNITS(1000, UNIT_1_25_MS),
        .u16ConnLatency            = 0,
        .u16SupervisionTimeout10ms = MSEC_TO_UNITS(6000, UNIT_10_MS),
    };
    rom_gap_api_connection_parameters_update(u16ConnHandle, &stConnPara);
    PRINTF("updataConnIntv Timer running\n");
}

/**********************************************************************************************************************
 * @brief  Update BLE param from flash.
 *
 * @return None.
 *********************************************************************************************************************/
static void ble_set_param_from_flash(void)
{
//  EN_ERR_STA_T enRet;
    uint16_t u16AdvInterval;
    uint8_t u8DevName[TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN + 1] = {0};

    if (ERR_STA_OK != mmu_read(EN_MMU_BLE_ADV_DEV_NAME,0,u8DevName,TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN))
    {
        INFO("Ble Dev Name Not Found in flash\n");
    }
    else
    {
        INFO("MMU Read Dev Name : %s\n",(const char *)u8DevName);
        ble_set_dev_name((const char *)u8DevName);
    }
    
    if (ERR_STA_OK != mmu_read(EN_MMU_BLE_ADV_INTERVAL,0,(uint8_t *)&u16AdvInterval,2))
    {
        INFO("Ble Adv Interval Not Found in flash\n");
        return;
    }
    else
    {
        INFO("MMU Read Adv Interval : %.3f ms\n",u16AdvInterval * 0.625);
        ble_set_adv_interval(u16AdvInterval);
    }
}

/**********************************************************************************************************************
 * @brief  CGM Device Application Main.
 * 
 * @return None
 *********************************************************************************************************************/
void app_cgm_cp(void)
{
    osStatus_t status = osOK;
    stAppMsg_t stAppMsg;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    INFO("---------------CGM Profile Example----------------\n");
    
    // 1. Component init
    msg_queue_init();    
    gpstOtaQueue = link_queue_create();
    if (NULL == gpstOtaQueue)
        INFO("OTA Link Queue Create Failed\n");
    
    cgms_time_init();
    cgms_db_init();

    // 2. Init Ble
    ble_init();
    ble_event_init(ble_event_callback);
    ble_set_param_from_flash();
    ble_peripheral_init();

    // 3. Add Service
    ble_dis_init();
    ble_bas_init(get_battery_level); 
    tt_service_init(tt_recv_callback);
    ota_service_init(ota_recv_callback);

    gstCtsInit.cts_get_time_handler = ble_cts_get_time_callback;
    gstCtsInit.cts_set_time_handler = ble_cts_set_time_callback; 
    ble_cts_init(&gstCtsInit);

    // Add Cgm Sensor Feature
    // Refer to CGM_FEATURE_SUPPORT_* in "cgm_service.h"
    gstCgmsHandle.stFeature.u32Feature = 0;
    enRet = cgm_service_init(&gstCgmsHandle,cgms_event_callback);
    if (ERR_STA_OK != enRet)
    {
        PRINTF("CGMS Init Failed\n");
        return;
    }

    // 4. Init Uart
    enRet = uart_init(uart_recv_callback);
    if (enRet != ERR_STA_OK)
    {
        INFO("Uart Init Failed\r\n");
    }
    uart_send_bytes((uint8_t *)"Uart Init Successful\r\n",strlen("Uart Init Successful\r\n"));

#if SPI_CMD_SUPPORT
    enRet = spi_master_init();
    if (enRet != ERR_STA_OK)
    {
        INFO("SPI Master Init Failed\r\n");
    }
    INFO("SPI Master Init OK\n");
#endif
    
    // 5. Start Ble Pair Advertising
    start_pair_adv();
    
    // 6. Create Send CGMS Measurement App Timer 
    app_timer_create(&gstCgmsMeasTimer,APP_TIMER_MODE_REPEAT,cgms_meas_timer_timeout);
    // 7. Create Update Connect Interval App Timer
    app_timer_create(&gstConnIntvTimer, APP_TIMER_MODE_ONCE, UpdateConnIntvTimer);
    // 7. Add Wakeup Source (Wakeup by Key Down)
    app_set_wakeup_source();

    while(1)
    {
        // 8. Wait for Event
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
            case EN_MSG_MODULE_CGMS:
            {
                cgms_event_process(&stAppMsg);
                break;
            }
            case EN_MSG_MODULE_OTA:
            {
                ota_event_process();
                break;
            }
            
#if SPI_CMD_SUPPORT
            case EN_MSG_MODULE_SPI:
            {
                spi_event_process(&stAppMsg);
                break;
            }
#endif
            default:break;
        }
    }
}

