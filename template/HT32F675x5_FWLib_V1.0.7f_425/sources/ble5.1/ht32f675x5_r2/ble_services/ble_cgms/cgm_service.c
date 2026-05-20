/*************************************************************************************************************
 * @file    cgm_service.c
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
#include <time.h>

#include "bluetooth.h"
#include "err_def.h"
#include "app_cfg.h"
#include "gatt_uuid_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"

#include "stack_utility.h"
#include "utility.h"

#include "cgm_service.h"
#include "cgms_meas.h"
#include "cgms_socp.h"
#include "cgms_racp.h"

#define CGMS_SESSION_START_TIME_DATA_SIZE           (9)

static stCgmsHandle_t *gpstHandle;
static cgms_event_callback_t gCgmsEventCb = NULL;

static uint16_t cgms_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle);
static uint16_t cgms_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);
static uint32_t cgms_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);

static gatt_serviceCBs_t gCgmCb =
{
    cgms_get_attr_cb,       /* Get Attribute Callback */
    cgms_read_attr_cb,      /* Read Attribute Callback */
    cgms_write_attr_cb,     /* Write Attribute Callback */
};


/**********************************************************************************************************************
 * @brief  Get CGMS Status.
 * @param  pu8Buf: Destination Data Buffer.
 * @param  u16BufSize: Destination Data Buffer Size.
 *
 * @return Length of Data.
 *********************************************************************************************************************/
static uint16_t cgms_get_status(uint8_t *pu8Buf,uint16_t u16BufSize)
{
    uint16_t u16Len = 0;

    if (NULL == pu8Buf || 0 == u16BufSize || sizeof(gpstHandle->stStatus) > u16BufSize)
        return 0;

    rom_little_endian_store_16(pu8Buf,u16Len,gpstHandle->stStatus.u16TimeOffset);
    u16Len += 2;

    pu8Buf[u16Len++] = gpstHandle->stStatus.stStatus.u8Status;
    pu8Buf[u16Len++] = gpstHandle->stStatus.stStatus.u8CalTemp;
    pu8Buf[u16Len++] = gpstHandle->stStatus.stStatus.u8Warning;

    return u16Len;
}

/**********************************************************************************************************************
 * @brief  Get Session Start Time.
 * @param  pu8Buf: Destination Data Buffer.
 * @param  u16BufSize: Destination Data Buffer Size.
 *
 * @return Length of Data.
 *********************************************************************************************************************/
static uint16_t cgms_get_sst(uint8_t *pu8Buf,uint16_t u16BufSize)
{
    uint16_t u16Len = 0;
    if (NULL == pu8Buf || 0 == u16BufSize || CGMS_SESSION_START_TIME_DATA_SIZE > u16BufSize)
        return 0;

    rom_little_endian_store_16(pu8Buf,0,gpstHandle->stSst.u16Year);
    u16Len += 2;

    pu8Buf[u16Len++] = gpstHandle->stSst.u8Month;
    pu8Buf[u16Len++] = gpstHandle->stSst.u8Day;
    pu8Buf[u16Len++] = gpstHandle->stSst.u8Hour;
    pu8Buf[u16Len++] = gpstHandle->stSst.u8Minute;
    pu8Buf[u16Len++] = gpstHandle->stSst.u8Second;
    pu8Buf[u16Len++] = gpstHandle->stSst.i8TimeZone;
    pu8Buf[u16Len++] = gpstHandle->stSst.u8Dst;

    return u16Len;
}

/**********************************************************************************************************************
 * @brief  Set Session Start Time.
 * @param  pu8Buf: Source Data Buffer.
 * @param  u16BufSize: Source Data Buffer Size.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T cgms_set_sst(uint8_t *pu8Buf,uint16_t u16BufSize)
{
    if (NULL == pu8Buf || 0 == u16BufSize)
        return ERR_STA_ERROR;

    struct tm stTime = {0};
    time_t stTimeInSec;

    stTime.tm_year = rom_little_endian_read_16(pu8Buf,0);
    stTime.tm_year -= 1900;
    stTime.tm_mon = pu8Buf[2];
    stTime.tm_mday = pu8Buf[3];
    stTime.tm_hour = pu8Buf[4];
    stTime.tm_min = pu8Buf[5];
    stTime.tm_sec = pu8Buf[6];

    stTime.tm_isdst = 0;

    stTimeInSec = mktime(&stTime);

    stTimeInSec = stTimeInSec - (gpstHandle->stStatus.u16TimeOffset * 60);

    stTime = *(localtime(&stTimeInSec));

    if (stTime.tm_isdst == 1)
    {
        stTime.tm_hour = stTime.tm_hour - 1;
        stTime.tm_isdst = 0;
    }

    rom_little_endian_store_16((uint8_t *)&gpstHandle->stSst.u16Year,0,stTime.tm_year + 1900);

    gpstHandle->stSst.u8Month = (uint8_t)stTime.tm_mon; 
    gpstHandle->stSst.u8Day = (uint8_t)stTime.tm_mday;
    gpstHandle->stSst.u8Hour = (uint8_t)stTime.tm_hour;
    gpstHandle->stSst.u8Minute = (uint8_t)stTime.tm_min;
    gpstHandle->stSst.u8Second = (uint8_t)stTime.tm_sec;
    gpstHandle->stSst.i8TimeZone = pu8Buf[7];
    gpstHandle->stSst.u8Dst = pu8Buf[8];

    gpstHandle->event_handler(EN_CGMS_EVT_SST_SESSION_START_TIME_UPDATE);

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Get Session Run Time.
 * @param  pu8Buf: Destination Data Buffer.
 * @param  u16BufSize: Destination Data Buffer Size.
 *
 * @return Length of Data.
 *********************************************************************************************************************/
static uint16_t cgms_get_srt(uint8_t *pu8Buf,uint16_t u16BufSize)
{
    uint16_t u16Len = 0;

    if (NULL == pu8Buf || 0 == u16BufSize || sizeof(gpstHandle->u16Srt) > u16BufSize)
        return 0;

    rom_little_endian_store_16(pu8Buf,u16Len,gpstHandle->u16Srt);
    u16Len += 2;

    return u16Len;
}


/**********************************************************************************************************************
 * @brief  Initialize Continuous Glucose Monitoring Service.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T cgms_init(void)
{
    uint16_t u16Hdl = 0;
    uint8_t u8FeatureDataLen = 0;
    uint8_t pu8FeatureBuf[6] = {0};
    stCgmsChrsHandle_t *stChrsHdl = &gpstHandle->stChrsHandle;

    /* CGM Service Start */
    u16Hdl = patch_gatts_api_add_service_start(0,CGM_SERV_UUID,NULL,&gCgmCb);
    gpstHandle->u16SrvHandle = u16Hdl;

    /* CGM Measurement */
    u16Hdl = patch_gatts_api_add_char(0, CGM_MEASUREMENT_UUID, NULL,
                                    ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC | ATT_PROPERTY_AUTHENTICATION_REQUIRED, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16Measurement = u16Hdl;

    /* CGM Measurement Client Characteristic Configuration Descriptor */
    u16Hdl = rom_gatts_api_add_char_descrip_client_config();
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16MeasurementCfg = u16Hdl;

    /* CGM Feature */
    u8FeatureDataLen = cgms_encode_feature(&gpstHandle->stFeature,pu8FeatureBuf,6);
    u16Hdl = patch_gatts_api_add_char(0, CGM_FEATURE_UUID, NULL,
                                    ATT_PROPERTY_READ | ATT_PROPERTY_AUTHENTICATION_REQUIRED, 
                                    pu8FeatureBuf,u8FeatureDataLen);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16Feature = u16Hdl;

    /* CGM Status */
    u16Hdl = patch_gatts_api_add_char(0, CGM_STATUS_UUID, NULL,
                                    ATT_PROPERTY_READ | ATT_PROPERTY_DYNAMIC | ATT_PROPERTY_AUTHENTICATION_REQUIRED, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16Status = u16Hdl;

    /* CGM Session Start Time */
    u16Hdl = patch_gatts_api_add_char(0, CGM_SESSION_START_TIME_UUID, NULL,
                                    ATT_PROPERTY_READ | ATT_PROPERTY_WRITE | ATT_PROPERTY_DYNAMIC | ATT_PROPERTY_AUTHENTICATION_REQUIRED, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16StartTime = u16Hdl;

    /* CGM Session Run Time */
    u16Hdl = patch_gatts_api_add_char(0, CGM_SESSION_RUN_TIME_UUID, NULL,
                                    ATT_PROPERTY_READ | ATT_PROPERTY_DYNAMIC | ATT_PROPERTY_AUTHENTICATION_REQUIRED, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16RunTime = u16Hdl;

    /* CGM Record Access Control Point */
    u16Hdl = patch_gatts_api_add_char(0, RECORD_CTRL_PT_UUID, NULL,
                                    ATT_PROPERTY_INDICATE | ATT_PROPERTY_WRITE | ATT_PROPERTY_DYNAMIC | ATT_PROPERTY_AUTHENTICATION_REQUIRED, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16Racp = u16Hdl;

    /* Record Access Control Point Client Characteristic Configuration Descriptor */
    u16Hdl = rom_gatts_api_add_char_descrip_client_config();
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16RacpCfg = u16Hdl;

    /* CGM Specofic Ops Control Point */
    u16Hdl = patch_gatts_api_add_char(0, CGM_SPEC_OPS_CTRL_PT_UUID, NULL,
                                    ATT_PROPERTY_INDICATE | ATT_PROPERTY_WRITE | ATT_PROPERTY_DYNAMIC | ATT_PROPERTY_AUTHENTICATION_REQUIRED, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16Socp = u16Hdl;

    /* CGM Specofic Ops Control Point Client Characteristic Configuration Descriptor */
    u16Hdl = rom_gatts_api_add_char_descrip_client_config();
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16SocpCfg = u16Hdl;

    /* CGM Service End */
    patch_gatts_api_add_service_end();

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Report CGMS Event.
 * @param  enEvent: CGMS Event @ref EN_CGMS_EVT_T.
 *
 * @return None.
 *********************************************************************************************************************/
void cgms_report_event(EN_CGMS_EVT_T enEvent)
{
    if (NULL == gCgmsEventCb)
        return;

    gCgmsEventCb(enEvent,(uint8_t *)gpstHandle,sizeof(*gpstHandle));
}

/**********************************************************************************************************************
 * @brief  Initialize Continuous Glucose Monitoring Service.
 * @param  pstHandle: CGMS Global Handle.
 * @param  eventCb: CGMS Event Callback Function.CGMS Event @ref EN_CGMS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T cgm_service_init(stCgmsHandle_t *pstHandle,cgms_event_callback_t cb)
{
    if (NULL == pstHandle)
        return ERR_STA_ERROR;

    gpstHandle = pstHandle;
    gpstHandle->isSessionStart = false;
    gpstHandle->stStatus.stStatus.u8Status = 0;
    gpstHandle->stStatus.stStatus.u8Status |= CGMS_STATUS_STATUS_SESSION_STOPPED;
    gCgmsEventCb = cb;
    gpstHandle->event_handler = cgms_report_event;

    if (0 == gpstHandle->u8CommIntv)
        gpstHandle->u8CommIntv = CGMS_MEAS_COMMUNICATION_INTERAL_DEFAULT;

    return cgms_init();
}

/**********************************************************************************************************************
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: CGMS Global Handle.
 * @param  pstRecord: CGMS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T cgms_meas_send(stCgmsHandle_t *pstHandle,const stCgmsMeasRec_t *pstRecord)
{
    if (0x00 == cgms_meas_get_cfg())
        return ERR_STA_OK;
    return cgms_meas_send_notify(pstHandle,pstRecord);
}

/**********************************************************************************************************************
 * @brief  Characteristic Get Function Callback.
 * @param  u16ConnHandle: Ble Connected Handle.
 * @param  u16AttrHandle: Characteristic Handle.
 *
 * @return Length of Data.
 *********************************************************************************************************************/
static uint16_t cgms_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
{
    if (u16AttrHandle == gpstHandle->stChrsHandle.u16MeasurementCfg)
        return 2;
    else if(u16AttrHandle == gpstHandle->stChrsHandle.u16SocpCfg)
        return 2;
    else if(u16AttrHandle == gpstHandle->stChrsHandle.u16RacpCfg)
        return 2;
    else if(u16AttrHandle == gpstHandle->stChrsHandle.u16Status)
        return sizeof(gpstHandle->stStatus);
    else if(u16AttrHandle == gpstHandle->stChrsHandle.u16StartTime)
        return CGMS_SESSION_START_TIME_DATA_SIZE;
    else if(u16AttrHandle == gpstHandle->stChrsHandle.u16RunTime)
        return sizeof(gpstHandle->u16Srt);
    return 2;
}

/**********************************************************************************************************************
 * @brief  Characteristic Read Function Callback.
 * @param  u16ConnHandle: Ble Connected Handle.
 * @param  u16AttrHandle: Characteristic Handle.
 * @param  u16Offset: Read Offset Position.
 * @param  pu8Buf: Destination Data Buffer.
 * @param  u16BufSize: Destination Data Buffer Size.
 *
 * @return Length of Data.
 *********************************************************************************************************************/
static uint16_t cgms_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    if (u16AttrHandle == gpstHandle->stChrsHandle.u16MeasurementCfg)
    {
        pu8Buf[0] = cgms_meas_get_cfg();
        pu8Buf[1] = 0;
        return 2;
    }
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16SocpCfg)
    {
        pu8Buf[0] = cgms_socp_get_cfg();
        pu8Buf[1] = 0;
        return 2;
    }
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16RacpCfg)
    {
        pu8Buf[0] = cgms_racp_get_cfg();
        pu8Buf[1] = 0;
        return 2;
    }
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16Status)      
        return cgms_get_status(pu8Buf,u16BufSize);    
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16StartTime)      
        return cgms_get_sst(pu8Buf,u16BufSize);     
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16RunTime)
        return cgms_get_srt(pu8Buf,u16BufSize);


    return 2;
}

/**********************************************************************************************************************
 * @brief  Characteristic Write Function Callback.
 * @param  u16ConnHandle: Ble Connected Handle.
 * @param  u16AttrHandle: Characteristic Handle.
 * @param  u16Offset: Write Offset Position.
 * @param  pu8Buf: Source Data Buffer.
 * @param  u16BufSize: Source Data Buffer Size.
 *
 * @return Status.
 *********************************************************************************************************************/
static uint32_t cgms_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    EN_ERR_STA_T enRet;

    if (u16AttrHandle == gpstHandle->stChrsHandle.u16MeasurementCfg)
        cgms_meas_set_cfg(pu8Buf[0]);
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16SocpCfg)
        cgms_socp_set_cfg(pu8Buf[0]);
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16RacpCfg)
        cgms_racp_set_cfg(pu8Buf[0]);
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16Racp)
    {
        if (NULL == pu8Buf || 0 == u16BufSize)
            return 0;
        cgms_racp_cmd_parse(gpstHandle,pu8Buf,u16BufSize);
    }
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16Socp)
    {
        if (NULL == pu8Buf || 0 == u16BufSize)
            return 0;
        cgms_socp_cmd_parse(gpstHandle,pu8Buf,u16BufSize);
    }
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16StartTime)
    {
        enRet = cgms_set_sst(pu8Buf,u16BufSize);
        if (ERR_STA_OK != enRet)
            PRINTF("Session Start Time Format Error\n");
    }

    return 0;
}

