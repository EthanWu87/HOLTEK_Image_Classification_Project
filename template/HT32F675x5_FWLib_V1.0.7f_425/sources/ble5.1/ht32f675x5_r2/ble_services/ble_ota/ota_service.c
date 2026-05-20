/*************************************************************************************************************
 * @file    ota_service.c
 * @version V1.0
 * @date    2022-11-07
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


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "err_def.h"
#include "stack_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"

#include "utility.h"
#include "gap_api.h"
#include "ble_gap_service.h"

#include "app_cfg.h"
#include "ota_service.h"


static ota_recv_callback_t gpRecvCb = NULL;
static stOtaService_t stOtaSrvInfo;

static uint16_t ble_ota_read_attrCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);
static uint32_t ble_ota_write_attrCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16TransMode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);
static uint16_t ble_ota_get_attrlenCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle);

gatt_serviceCBs_t gstBleotaCBs =
{
        ble_ota_get_attrlenCB,
        ble_ota_read_attrCB,  
        ble_ota_write_attrCB,
};

/**
 * @brief  To create ble ota profile.
 */
EN_ERR_STA_T ota_service_init(ota_recv_callback_t pRecvCb)
{
    if (NULL == pRecvCb)
        return ERR_PARA_ERR;
    
    gpRecvCb = pRecvCb;
    
    // 1. Add Profile
    uint16_t HT32_OTA_SERVICE_UUID = 0xFD10;
    patch_gatts_api_add_service_start(0, HT32_OTA_SERVICE_UUID, NULL, &gstBleotaCBs);

    // 2. Data Characteristic
    uint16_t HT32_OTA_DATA_UUID = 0xFD11;
    stOtaSrvInfo.u16DataHandle = patch_gatts_api_add_char(0, HT32_OTA_DATA_UUID, NULL,
                                                            (ATT_PROPERTY_WRITE_WITHOUT_RESPONSE | ATT_PROPERTY_DYNAMIC), NULL, 0);
    if (0 == stOtaSrvInfo.u16DataHandle)
        return ERR_STA_ERROR;

    // 3. Control Characteristic
    uint16_t HT32_OTA_CTRL_UUID = 0xFD12;
    stOtaSrvInfo.u16CtrlHandle = patch_gatts_api_add_char(0, HT32_OTA_CTRL_UUID, NULL,
                                                            (ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC), NULL, 0);
    if (0 == stOtaSrvInfo.u16CtrlHandle)
        return ERR_STA_ERROR;
    
    rom_gatts_api_add_char_descrip_client_config();
    patch_gatts_api_add_service_end();
    
    return ERR_STA_OK;
}

/**
 * @brief  Read an attribute.
 * @return Error Status.
 */
static uint16_t ble_ota_read_attrCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    return 0;
}

/**
 * @brief  Get the length of attribute.
 * @return Error Status.
 */
static uint16_t ble_ota_get_attrlenCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
{
    if (u16AttrHandle == stOtaSrvInfo.u16CtrlHandle)
    {
        return 2;
    }
    return 0;
}

/**
 * @brief  Write an attribute.
 * @return Error Status.
 */
static uint32_t ble_ota_write_attrCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16TransMode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    if (u16AttrHandle == stOtaSrvInfo.u16DataHandle)
    {
        if (NULL == pu8Buf)
            return 0;

        gpRecvCb(pu8Buf,u16BufSize);;
    }
    return 0;
}

EN_ERR_STA_T ota_send_notify(uint16_t u16ConnHandle,uint8_t *pu8Buf,uint16_t u16BufSize)
{
    uint32_t u32Ret = 0;

    u32Ret = rom_gatts_api_send_notify(u16ConnHandle,stOtaSrvInfo.u16CtrlHandle,pu8Buf,u16BufSize);
    if (0 != u32Ret)
        return ERR_STA_ERROR;
    return ERR_STA_OK;
}

