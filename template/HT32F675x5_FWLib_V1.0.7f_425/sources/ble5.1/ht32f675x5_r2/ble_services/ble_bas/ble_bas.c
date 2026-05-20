/*************************************************************************************************************
 * @file    ble_bas.c
 * @version V1.0
 * @date    2022-11-11
 * @brief   ble battery service
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

#include "gatt_uuid_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"
#include "stack_utility.h"
#include "ble_cb_event_def.h"

#include "app_cfg.h"
#include "ble_bas.h"

typedef struct
{
    uint16_t u16SrvHandle;
    uint16_t u16ReadNotifyHandle;
    uint16_t u16NotifyCfgHandle;
    uint16_t u16ReportRefHandle;
    uint8_t u8NotifyCfg;
}stBleBasHandle_t;

static stBleBasHandle_t gstBleBasHandle;
static ble_bas_get_battery_level_t greadLevel;


static uint16_t ble_bas_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle);
static uint16_t ble_bas_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);
static uint32_t ble_bas_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);

// Battery Service Callbacks
gatt_serviceCBs_t batteryCBs =
{
    ble_bas_get_attr_cb,
    ble_bas_read_attr_cb,  
    ble_bas_write_attr_cb, 
};


EN_ERR_STA_T ble_bas_init(ble_bas_get_battery_level_t readLevel)
{   
    if(readLevel == NULL)
        return ERR_PARA_ERR;
    
    greadLevel = readLevel;
    
    gstBleBasHandle.u16SrvHandle = patch_gatts_api_add_service_start(0, BATT_SERV_UUID, NULL, &batteryCBs);
    if (0 == gstBleBasHandle.u16SrvHandle)
        return ERR_STA_ERROR;

    gstBleBasHandle.u16ReadNotifyHandle = patch_gatts_api_add_char(0, BATT_LEVEL_UUID, NULL, ATT_PROPERTY_READ | ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC, NULL, 0);
    if (0 ==gstBleBasHandle.u16ReadNotifyHandle)
        return ERR_STA_ERROR;

    gstBleBasHandle.u16NotifyCfgHandle = rom_gatts_api_add_char_descrip_client_config();
    if (0 ==gstBleBasHandle.u16NotifyCfgHandle)
        return ERR_STA_ERROR;

    gstBleBasHandle.u16ReportRefHandle = rom_gatts_api_add_char_descrip(GATT_REPORT_REF_UUID, ATT_PROPERTY_READ, NULL, 0);
    if (0 ==gstBleBasHandle.u16ReportRefHandle)
        return ERR_STA_ERROR;
    
    patch_gatts_api_add_service_end();
    
    gstBleBasHandle.u8NotifyCfg = 1;
    
    return  0;
}

static uint16_t ble_bas_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
{
    if (gstBleBasHandle.u16ReadNotifyHandle == u16AttrHandle)
        return 1;
    else if (gstBleBasHandle.u16NotifyCfgHandle == u16AttrHandle)
        return 2;

    return 0;
}

static uint16_t ble_bas_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    if (gstBleBasHandle.u16ReadNotifyHandle == u16AttrHandle)
    {
        if (pu8Buf)
        {
            uint8_t u8Level = greadLevel();
            pu8Buf[0] = (u8Level > 100) ? (100) : (u8Level);
        }
        return 1;
    }
    else if (gstBleBasHandle.u16NotifyCfgHandle == u16AttrHandle)
    {
        if (pu8Buf)
        {
            pu8Buf[0] = gstBleBasHandle.u8NotifyCfg;
            pu8Buf[1] = 0;
        }
        return 2;
    }
    return 0;
}

static uint32_t ble_bas_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    if (gstBleBasHandle.u16NotifyCfgHandle == u16AttrHandle)
        gstBleBasHandle.u8NotifyCfg = pu8Buf[0];

    return 0;
}

EN_ERR_STA_T ble_bas_send_battery_level(uint16_t u16ConnHandle, uint8_t u8BatteryLevel)
{
    if (gstBleBasHandle.u8NotifyCfg)
    {
        uint32_t u32Ret = rom_gatts_api_send_notify(u16ConnHandle,gstBleBasHandle.u16ReadNotifyHandle,&u8BatteryLevel,1);
        if (0 != u32Ret)
            return ERR_STA_ERROR;
    }
    return ERR_STA_OK;
}

