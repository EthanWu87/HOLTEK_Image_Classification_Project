/*************************************************************************************************************
 * @file    ble_wss.c
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

#include "ble_wss.h"

static stWssHandle_t *gpstHandle;
static uint8_t u8MeasCfg = 0x02;

static uint16_t wss_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle);
static uint16_t wss_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);
static uint32_t wss_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);

static gatt_serviceCBs_t gWssCb =
{
    wss_get_attr_cb,        /* Get Attribute Callback */
    wss_read_attr_cb,       /* Read Attribute Callback */
    wss_write_attr_cb,      /* Write Attribute Callback */
};

static EN_ERR_STA_T wss_meas_send_indicate(stWssHandle_t *pstHandle,const stWssMeasRec_t *pstRecord)
{
    uint8_t u8Data[sizeof(stWssMeasRec_t)];
    uint8_t u8Flags = pstRecord->u8Flags;
    uint16_t u16Len = 0;
    
    u8Data[u16Len++] = pstRecord->u8Flags;
    
    rom_little_endian_store_16(u8Data,u16Len,pstRecord->u16Weight);
    u16Len += 2;
    
    if (u8Flags & WSS_MEAS_FLAGS_TIME_STAMP_PRESENT)
        u16Len += wss_date_time_encode(&pstRecord->stTimeStamp,&u8Data[u16Len]);

    if (u8Flags & WSS_MEAS_FLAGS_USER_ID_PRESENT)
        u8Data[u16Len++] = pstRecord->u8UserId;
    
    if (u8Flags & WSS_MEAS_FLAGS_BMI_AND_HEIGHT_PRESENT)
    {
        rom_little_endian_store_16(u8Data,u16Len,pstRecord->u16BMI);
        u16Len += 2;
        rom_little_endian_store_16(u8Data,u16Len,pstRecord->u16Height);
        u16Len += 2;
    }
    
    uint32_t u32Ret = rom_gatts_api_send_indicate(pstHandle->u16ConnHandle,pstHandle->u16MeasHandle,u8Data,u16Len);
    if (0 != u32Ret)
        return ERR_STA_ERROR;

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Initialize Weight Scale Service.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T wss_init(void)
{
    uint16_t u16Hdl = 0;
    
    /* WSS Service Start */
    u16Hdl = patch_gatts_api_add_service_start(0,WS_SERV_UUID,NULL,&gWssCb);
    gpstHandle->u16SrvHandle = u16Hdl;
    
    /* WSS Measurement */
    u16Hdl = patch_gatts_api_add_char(0, WS_MEAS_UUID, NULL,
                                    ATT_PROPERTY_INDICATE | ATT_PROPERTY_DYNAMIC | ATT_PROPERTY_AUTHENTICATION_REQUIRED, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    gpstHandle->u16MeasHandle = u16Hdl;
    
    /* WSS Measurement Client Characteristic Configuration Descriptor */
    u16Hdl = rom_gatts_api_add_char_descrip_client_config();
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    gpstHandle->u16MeasCfgHandle = u16Hdl;
    
    /* WSS Feature */
    u16Hdl = patch_gatts_api_add_char(0, WS_FEATURE_UUID, NULL,
                                    ATT_PROPERTY_READ, 
                                    (uint8_t *)&gpstHandle->u32Feature,sizeof(gpstHandle->u32Feature));
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    gpstHandle->u16FeatureHandle = u16Hdl;
    
    /* WSS Service End */
    patch_gatts_api_add_service_end();
    
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Initialize Weight Scale Service.
 * @param  pstHandle: WSS Global Handle.
 * @param  eventCb: WSS Event Callback Function.WSS Event @ref EN_WSS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ble_wss_init(stWssHandle_t *pstHandle)
{
    if (NULL == pstHandle)
        return ERR_STA_ERROR;
    
    gpstHandle = pstHandle;

    return wss_init();
}

/**********************************************************************************************************************
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: WSS Global Handle.
 * @param  pstRecord: WSS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T wss_meas_send(stWssHandle_t *pstHandle,const stWssMeasRec_t *pstRecord)
{
	if (0x00 == u8MeasCfg)
		return ERR_STA_OK;
	return wss_meas_send_indicate(pstHandle,pstRecord);
}

/**********************************************************************************************************************
 * @brief  Characteristic Get Function Callback.
 * @param  u16ConnHandle: Ble Connected Handle.
 * @param  u16AttrHandle: Characteristic Handle.
 *
 * @return Length of Data.
 *********************************************************************************************************************/
static uint16_t wss_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
{
    if (u16AttrHandle == gpstHandle->u16MeasCfgHandle)
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
static uint16_t wss_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    if (u16AttrHandle == gpstHandle->u16MeasCfgHandle)
    {
        pu8Buf[0] = u8MeasCfg;
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
static uint32_t wss_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    EN_ERR_STA_T enRet;

    if (u16AttrHandle == gpstHandle->u16MeasCfgHandle)
        u8MeasCfg = pu8Buf[0];

    return 0;
}

