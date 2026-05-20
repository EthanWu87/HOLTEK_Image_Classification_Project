/*************************************************************************************************************
 * @file    ble_hts.c
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

#include "bluetooth.h"
#include "err_def.h"
#include "app_cfg.h"
#include "gatt_uuid_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"

#include "utility.h"

#include "ble_hts.h"

static stHtsHandle_t *gpstHandle;
static hts_event_callback_t gEventCb = NULL;
static uint8_t gu8IsIndicateEnabled = 0x02;
static uint16_t hts_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle);
static uint16_t hts_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);
static uint32_t hts_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);

static gatt_serviceCBs_t gHtsCb =
{
    hts_get_attr_cb,        /* Get Attribute Callback */
    hts_read_attr_cb,       /* Read Attribute Callback */
    hts_write_attr_cb,      /* Write Attribute Callback */
};

/**********************************************************************************************************************
 * @brief  Get HTS Measurement Client Characteristic Configuration Descriptor.
 *
 * @return Client Characteristic Configuration Descriptor.
 *********************************************************************************************************************/
static uint8_t hts_meas_get_cfg(void)
{
    return gu8IsIndicateEnabled;
}

/**********************************************************************************************************************
 * @brief  Set HTS Measurement Client Characteristic Configuration Descriptor.
 * @param  u8Cfg: Client Characteristic Configuration Descriptor.
 *                  0x00 : Disable
 *                  0x02 : Enable
 * @return None.
 *********************************************************************************************************************/
void hts_meas_set_cfg(uint8_t u8Cfg)
{
    gu8IsIndicateEnabled = (u8Cfg & 0x03);
}

/**********************************************************************************************************************
 * @brief  Initialize Health Thermometer Service.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T hts_init(void)
{
    uint16_t u16Hdl = 0;

    /* Health Thermometer Service Start */
    u16Hdl = patch_gatts_api_add_service_start(0,THERMOMETER_SERV_UUID,NULL,&gHtsCb);
    gpstHandle->u16SrvHandle = u16Hdl;

    /* HTS Temperature Measurement */
    u16Hdl = patch_gatts_api_add_char(0, TEMP_MEAS_UUID, NULL,
                                    ATT_PROPERTY_INDICATE | ATT_PROPERTY_DYNAMIC, 
                                    NULL, 0);
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    gpstHandle->u16HtsMeasHandle = u16Hdl;

    /* HTS Measurement Client Characteristic Configuration Descriptor */
    u16Hdl = rom_gatts_api_add_char_descrip_client_config();
    if (0 == u16Hdl)
        return ERR_STA_ERROR;
    gpstHandle->u16HtsMeasCfgHandle = u16Hdl;

    /* Health Thermometer Service End */
    patch_gatts_api_add_service_end();

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Report HTS Event.
 * @param  enEvent: HTS Event @ref EN_HTS_EVT_T.
 *
 * @return None.
 *********************************************************************************************************************/
void hts_report_event(EN_HTS_EVT_T enEvent)
{
    if (NULL == gEventCb)
        return;

    gEventCb(enEvent,(uint8_t *)gpstHandle,sizeof(*gpstHandle));
}

/**********************************************************************************************************************
 * @brief  Initialize Health Thermometer Service.
 * @param  pstHandle: HTS Global Handle.
 * @param  eventCb: HTS Event Callback Function.HTS Event @ref EN_HTS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ble_hts_init(stHtsHandle_t *pstHandle,hts_event_callback_t cb)
{
    if (NULL == pstHandle)
        return ERR_STA_ERROR;

    gpstHandle = pstHandle;
    gEventCb = cb;
    gpstHandle->event_handler = hts_report_event;

    return hts_init();
}

/**********************************************************************************************************************
 * @brief  Packed Measurement Record.
 * @param  pstHandle: HTS Global Handle.
 * @param  pstRecord: HTS Measurement Record.
 * @param  pu8Pkg: Package Buffer.
 *
 * @return Length of Package.
 *********************************************************************************************************************/
static uint8_t hts_record_pack(stHtsHandle_t *pstHandle,const stHtsMeasRec_t *pstRecord,uint8_t *pu8Pkg)
{
    uint8_t u8Len = 0;
    uint8_t u8Flags = pstRecord->u8Flags;

    pu8Pkg[u8Len++] = u8Flags;

    rom_little_endian_store_32(pu8Pkg,u8Len,pstRecord->u32TempMeasVal);
    u8Len += 4;

    if (u8Flags & HTS_MEASUREMENT_FLAGS_TIME_STAMP)
    {
        u8Len += hts_date_time_encode(&pstRecord->stHtsDateTime,&pu8Pkg[u8Len]);
    }

    if (u8Flags & HTS_MEASUREMENT_FLAGS_TEMP_TYPE)
    {
        pu8Pkg[u8Len++] = pstRecord->u8TempType;
    }

    return u8Len;
}

/**********************************************************************************************************************
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: HTS Global Handle.
 * @param  pstRecord: HTS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T hts_meas_send(stHtsHandle_t *pstHandle,const stHtsMeasRec_t *pstRecord)
{
    uint32_t u32Ret = 0;
    uint8_t u8Pkg[sizeof(stHtsMeasRec_t)] = {0};
    uint8_t u8Len = 0;

    if (0x00 == hts_meas_get_cfg())
    {
        return ERR_STA_OK;
    }
    u8Len = hts_record_pack(pstHandle,pstRecord,u8Pkg);

    if (0 == pstHandle->u16ConnHandle)
    {
        PRINTF("HTS Ble Connected Handle Error");
        return ERR_STA_ERROR;
    }

    u32Ret = rom_gatts_api_send_indicate(pstHandle->u16ConnHandle,gpstHandle->u16HtsMeasHandle,u8Pkg,u8Len);
    if (0 != u32Ret)
    {
        PRINTF("HTS indicate Error=%d\n",u32Ret);
        return ERR_STA_ERROR;
    }

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Characteristic Get Function Callback.
 * @param  u16ConnHandle: Ble Connected Handle.
 * @param  u16AttrHandle: Characteristic Handle.
 *
 * @return Length of Data.
 *********************************************************************************************************************/
static uint16_t hts_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
{
    if (u16AttrHandle == gpstHandle->u16HtsMeasCfgHandle)
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
static uint16_t hts_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    if (u16AttrHandle == gpstHandle->u16HtsMeasCfgHandle)
    {
        pu8Buf[0] = hts_meas_get_cfg();
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
static uint32_t hts_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    if (u16AttrHandle == gpstHandle->u16HtsMeasCfgHandle){
        hts_meas_set_cfg(pu8Buf[0]);
    }

    return 0;
}

