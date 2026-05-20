/*************************************************************************************************************
 * @file    ble_gls.c
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
#include "utility.h"

#include "gatt_uuid_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"

#include "ble_gls.h"
#include "gls_meas.h"
#include "gls_racp.h"

#define GLS_SESSION_START_TIME_DATA_SIZE           (9)

static stGlsHandle_t *gpstHandle;
static gls_event_callback_t gGlsEventCb = NULL;

static uint16_t gls_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle);
static uint16_t gls_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);
static uint32_t gls_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);

static gatt_serviceCBs_t gGlsCb =
{
    gls_get_attr_cb,        /* Get Attribute Callback */
    gls_read_attr_cb,       /* Read Attribute Callback */
    gls_write_attr_cb,      /* Write Attribute Callback */
};


/**********************************************************************************************************************
 * @brief  Initialize Glucose Service.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T gls_init(void)
{
    uint16_t u16Hdl = 0;
    stGlsChrsHandle_t *stChrsHdl = &gpstHandle->stChrsHandle;

    /* GLS Service Start */
    u16Hdl = patch_gatts_api_add_service_start(0,GLUCOSE_SERV_UUID,NULL,&gGlsCb);
    gpstHandle->u16SrvHandle = u16Hdl;

    /* GLS Measurement */
    u16Hdl = patch_gatts_api_add_char(0, GLUCOSE_MEAS_UUID, NULL,
                                    ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16Measurement = u16Hdl;
    
    /* GLS Measurement Client Characteristic Configuration Descriptor */
    u16Hdl = rom_gatts_api_add_char_descrip_client_config();
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16MeasurementCfg = u16Hdl;
    
    /* GLS Feature */
    u16Hdl = patch_gatts_api_add_char(0, GLUCOSE_FEATURE_UUID, NULL,
                                    ATT_PROPERTY_READ, 
                                    (uint8_t *)&gpstHandle->u16Feature,sizeof(gpstHandle->u16Feature));
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    stChrsHdl->u16Feature = u16Hdl;

    /* GLS Record Access Control Point */
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

    /* GLS Service End */
    patch_gatts_api_add_service_end();

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Report GLS Event.
 * @param  enEvent: GLS Event @ref EN_GLS_EVT_T.
 *
 * @return None.
 *********************************************************************************************************************/
void gls_report_event(EN_GLS_EVT_T enEvent)
{
    if (NULL == gGlsEventCb)
        return;
    
    gGlsEventCb(enEvent,(uint8_t *)gpstHandle,sizeof(*gpstHandle));
}

/**********************************************************************************************************************
 * @brief  Initialize Glucose Service.
 * @param  pstHandle: GLS Global Handle.
 * @param  eventCb: GLS Event Callback Function.GLS Event @ref EN_GLS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ble_gls_init(stGlsHandle_t *pstHandle,gls_event_callback_t cb)
{
    if (NULL == pstHandle)
        return ERR_STA_ERROR;

    gpstHandle = pstHandle;

    gGlsEventCb = cb;
    gpstHandle->event_handler = gls_report_event;

    return gls_init();
}

/**********************************************************************************************************************
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: GLS Global Handle.
 * @param  pstRecord: GLS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T gls_meas_send(stGlsHandle_t *pstHandle,const stGlsMeasRec_t *pstRecord)
{
    if (0x00 == gls_meas_get_cfg())
        return ERR_STA_OK;
    return gls_meas_send_notify(pstHandle,pstRecord);
}

/**********************************************************************************************************************
 * @brief  Characteristic Get Function Callback.
 * @param  u16ConnHandle: Ble Connected Handle.
 * @param  u16AttrHandle: Characteristic Handle.
 *
 * @return Length of Data.
 *********************************************************************************************************************/
static uint16_t gls_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
{
    if (u16AttrHandle == gpstHandle->stChrsHandle.u16MeasurementCfg)
        return 2;
    else if(u16AttrHandle == gpstHandle->stChrsHandle.u16RacpCfg)
        return 2;
    return 0;
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
static uint16_t gls_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    if (u16AttrHandle == gpstHandle->stChrsHandle.u16MeasurementCfg)
    {
        pu8Buf[0] = gls_meas_get_cfg();
        pu8Buf[1] = 0;
        return 2;
    }
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16RacpCfg)
    {
        pu8Buf[0] = gls_racp_get_cfg();
        pu8Buf[1] = 0;
        return 2;
    }
    return 0;
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
static uint32_t gls_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    EN_ERR_STA_T enRet;

    if (u16AttrHandle == gpstHandle->stChrsHandle.u16MeasurementCfg)
        gls_meas_set_cfg(pu8Buf[0]);
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16RacpCfg)
        gls_racp_set_cfg(pu8Buf[0]);
    else if (u16AttrHandle == gpstHandle->stChrsHandle.u16Racp)
    {
        if (NULL == pu8Buf || 0 == u16BufSize)
            return 0;

        gls_racp_cmd_parse(gpstHandle,pu8Buf,u16BufSize);
    }

    return 0;
}

