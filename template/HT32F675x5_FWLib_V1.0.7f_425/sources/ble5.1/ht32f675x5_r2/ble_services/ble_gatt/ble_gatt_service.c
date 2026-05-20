/*************************************************************************************************************
 * @file    ble_gatt_service.c
 * @version V1.0
 * @date    2021-12-05
 * @brief   ble gatt service.
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

#include "err_def.h"
#include "stack_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"

#include "gatt_client_api.h"

#include "gatt_uuid_def.h"

#include "gap_api.h"

#include "gatt_service_api.h"
#include "gatt_uuid_def.h"

#include "utility.h"

/**
 * @brief  DEFINE
 */
#define BLE_SERVICE_RETURN_IF_ERROR(handle) \
    do                                      \
    {                                       \
        if (handle == 0)                    \
        {                                   \
            return ERR_STA_ERROR;           \
        }                                   \
    } while (0)

/**
 * @brief  BLE Handle
 */
typedef enum
{
    BLE_SERVICE_CHANGED_IDX               = 0,
    BLE_SERVICE_CHANGED_NOTIFY_CONFIG_IDX = 1,

} enBleGattsHandle_t;

/**
 * @brief  LOCAL VARIABLES
 */
static uint16_t m_au16BleGattServerHdl[3] = {0}; // service and characteristic
static uint8_t  m_u8RxClientCharCfg       = 0;

// ble gatt services callbacks.
static uint16_t ble_gatt_get_attrlenCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle);

static uint16_t ble_gatt_read_attrCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset,
                                     uint8_t *pu8Data, uint16_t u16DataLen);
static uint32_t ble_gatt_write_attrCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16TransactionMode,
                                      uint16_t u16Offset, uint8_t *pu8Data, uint16_t u16DataLen);

static const gatt_serviceCBs_t g_gattCBs = {
    ble_gatt_get_attrlenCB,
    ble_gatt_read_attrCB,  // Read callback function pointer
    ble_gatt_write_attrCB, // Write callback function pointer
};

/**
 * @brief  Initializing the ble gatt service.
 * @return uint32_t: Return status.
 */
uint32_t ble_gatt_service_init(void)
{
    uint16_t u16Handle = 0;

    u16Handle = patch_gatts_api_add_service_start(0, GATT_SERVICE_UUID, NULL, (gatt_serviceCBs_t *)&g_gattCBs);
    BLE_SERVICE_RETURN_IF_ERROR(u16Handle);

    // ibeacon uuid
    u16Handle =
        patch_gatts_api_add_char(0, SERVICE_CHANGED_UUID, NULL, (ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC), NULL, 0);
    BLE_SERVICE_RETURN_IF_ERROR(u16Handle);
    m_au16BleGattServerHdl[BLE_SERVICE_CHANGED_IDX] = u16Handle;

    u16Handle = rom_gatts_api_add_char_descrip_client_config();
    BLE_SERVICE_RETURN_IF_ERROR(u16Handle);
    m_au16BleGattServerHdl[BLE_SERVICE_CHANGED_NOTIFY_CONFIG_IDX] = u16Handle;

    patch_gatts_api_add_service_end();
    return 0;
}

uint16_t ble_gatt_get_attrlenCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
{
    if (m_au16BleGattServerHdl[BLE_SERVICE_CHANGED_NOTIFY_CONFIG_IDX] == u16AttrHandle)
    {
        return 2;
    }
    return 0;
}

uint16_t ble_gatt_read_attrCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Data,
                              uint16_t u16DataLen)
{
    // Make sure it's not a blob operation (no attributes in the profile are long)
    if (m_au16BleGattServerHdl[BLE_SERVICE_CHANGED_NOTIFY_CONFIG_IDX] == u16ConnHandle)
    {
        if (pu8Data)
        {
            pu8Data[0] = m_u8RxClientCharCfg;
            pu8Data[1] = 0;
        }
        return 2;
    }

    return 0;
}

uint32_t ble_gatt_write_attrCB(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16TransactionMode,
                               uint16_t u16Offset, uint8_t *pu8Data, uint16_t u16DataLen)
{
    if (m_au16BleGattServerHdl[BLE_SERVICE_CHANGED_NOTIFY_CONFIG_IDX] == u16AttrHandle)
    {
        m_u8RxClientCharCfg = pu8Data[0];
    }

    return 0;
}
