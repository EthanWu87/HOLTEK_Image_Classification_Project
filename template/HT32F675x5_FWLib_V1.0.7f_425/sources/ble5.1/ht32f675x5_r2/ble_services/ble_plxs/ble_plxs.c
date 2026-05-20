/*************************************************************************************************************
 * @file    ble_plxs.c
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

#include "utility.h"

#include "ble_plxs.h"

static stPlxsHandle_t *gpstHandle;
static uint8_t u8MeasCfg = 0x02;

static uint16_t plxs_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle);
static uint16_t plxs_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);
static uint32_t plxs_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);

static gatt_serviceCBs_t gPlxsCb =
{
    plxs_get_attr_cb,        /* Get Attribute Callback */
    plxs_read_attr_cb,       /* Read Attribute Callback */
    plxs_write_attr_cb,      /* Write Attribute Callback */
};

static EN_ERR_STA_T plxs_meas_send_indicate(stPlxsHandle_t *pstHandle,const stPlxsMeasRec_t *pstRecord)
{
    uint8_t u8Data[sizeof(stPlxsMeasRec_t)];
    uint8_t u8Flags = pstRecord->u8Flags;
    uint16_t u16Len = 0;
    
    u8Data[u16Len++] = pstRecord->u8Flags;
    
    rom_little_endian_store_16(u8Data,u16Len,pstRecord->u16SpO2);
    u16Len += 2;
    
    rom_little_endian_store_16(u8Data,u16Len,pstRecord->u16Pr);
    u16Len += 2;
    
    if (PLXS_MEAS_FLAGS_TIME_STAMP_PRESENT & u8Flags)
        u16Len += plxs_date_time_encode(&pstRecord->stTimeStamp,&u8Data[u16Len]);
    else
    {        
        if (1 == (PLXS_FEATURE_SUPPORT_TIMESTAMP_FOR_SPOT_CHECK_MEAS & pstHandle->stFeatures.u16Features))
        {
            PRINTF("Missing Timestamp\n");
            return ERR_PARA_ERR;
        }
    }
    
    if (PLXS_FEATURE_SUPPORT_MEAS_STATUS_PRESENT & pstHandle->stFeatures.u16Features)
    {
        if (PLXS_MEAS_FLAGS_MEAS_STATUS_PRESENT & u8Flags)
        {
            rom_little_endian_store_16(u8Data,u16Len,pstRecord->u16MeasStatus);
            u16Len += 2;
        }
    }
    
    if (PLXS_FEATURE_SUPPORT_DEV_AND_SEN_STATUS_PRESENT & pstHandle->stFeatures.u16Features)
    {
        if (PLXS_MEAS_FLAGS_DEV_SENSOR_STATUS_PRESENT & u8Flags)
        {
            rom_little_endian_store_32(u8Data,u16Len,pstRecord->u32DevAndSensorStatus);
            u16Len += 3;
        }
    }
    
    if (PLXS_MEAS_FLAGS_PLUSE_AMPLITUDE_INDEX_PRESENT & u8Flags)
    {
        rom_little_endian_store_16(u8Data,u16Len,pstRecord->u16PluseAmplitudeIndex);
        u16Len += 2;
    }
    
    uint32_t u32Ret = rom_gatts_api_send_indicate(pstHandle->u16ConnHandle,pstHandle->u16MeasHandle,u8Data,u16Len);
    if (0 != u32Ret)
    {
        PRINTF("BLS indicate Error=%d\n",u32Ret);
        return ERR_STA_ERROR;
    }

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Initialize PLX Serivce Service.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T plxs_init(void)
{
    uint16_t u16Hdl = 0;
    uint8_t u8FeatureData[sizeof(stPlxsFeature_t)];
    uint8_t u8FeatureDataLen = 0;
    
    rom_little_endian_store_16(u8FeatureData,u8FeatureDataLen,gpstHandle->stFeatures.u16Features);
    u8FeatureDataLen += 2;
    
    if (PLXS_FEATURE_SUPPORT_MEAS_STATUS_PRESENT & gpstHandle->stFeatures.u16Features)
    {
        rom_little_endian_store_16(u8FeatureData,u8FeatureDataLen,gpstHandle->stFeatures.u16MeasFeatures);
        u8FeatureDataLen += 2;
    }
    
    if (PLXS_FEATURE_SUPPORT_DEV_AND_SEN_STATUS_PRESENT & gpstHandle->stFeatures.u16Features)
    {
        rom_little_endian_store_32(u8FeatureData,u8FeatureDataLen,gpstHandle->stFeatures.u32DevSensorStatusFeatures);
        u8FeatureDataLen += 3;
    }
    
    /* PLXS Service Start */
    u16Hdl = patch_gatts_api_add_service_start(0,PLX_SERV_UUID,NULL,&gPlxsCb);
    gpstHandle->u16SrvHandle = u16Hdl;
    
    /* PLXS Measurement */
    u16Hdl = patch_gatts_api_add_char(0, PLX_SPOT_CHECK_MEAS_UUID, NULL,
                                    ATT_PROPERTY_INDICATE | ATT_PROPERTY_DYNAMIC, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    gpstHandle->u16MeasHandle = u16Hdl;
    
    /* PLXS Measurement Client Characteristic Configuration Descriptor */
    u16Hdl = rom_gatts_api_add_char_descrip_client_config();
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    gpstHandle->u16MeasCfgHandle = u16Hdl;
    
    /* PLXS Feature */
    u16Hdl = patch_gatts_api_add_char(0, PLX_FEATURES_UUID, NULL,
                                    ATT_PROPERTY_READ, 
                                    u8FeatureData,u8FeatureDataLen);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    gpstHandle->u16FeatureHandle = u16Hdl;
    
    /* PLXS Service End */
    patch_gatts_api_add_service_end();
    
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Initialize PLX Service.
 * @param  pstHandle: PLXS Global Handle.
 * @param  eventCb: PLXS Event Callback Function.PLXS Event @ref EN_PLXS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ble_plxs_init(stPlxsHandle_t *pstHandle)
{
    if (NULL == pstHandle)
        return ERR_STA_ERROR;
    
    gpstHandle = pstHandle;

    return plxs_init();
}

/**********************************************************************************************************************
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: PLXS Global Handle.
 * @param  pstRecord: PLXS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T plxs_meas_send(stPlxsHandle_t *pstHandle,const stPlxsMeasRec_t *pstRecord)
{
    if (0x00 == u8MeasCfg)
    {
        return ERR_STA_OK;
    }
    
    if (0 == pstHandle->u16ConnHandle)
    {
        PRINTF("PLXS Ble Connected Handle Error");
        return ERR_STA_ERROR;
    }

    return plxs_meas_send_indicate(pstHandle,pstRecord);
}

/**********************************************************************************************************************
 * @brief  Characteristic Get Function Callback.
 * @param  u16ConnHandle: Ble Connected Handle.
 * @param  u16AttrHandle: Characteristic Handle.
 *
 * @return Length of Data.
 *********************************************************************************************************************/
static uint16_t plxs_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
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
static uint16_t plxs_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
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
static uint32_t plxs_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    EN_ERR_STA_T enRet;
    if (u16AttrHandle == gpstHandle->u16MeasCfgHandle)
    {
        u8MeasCfg = pu8Buf[0];
    }
    return 0;
}

