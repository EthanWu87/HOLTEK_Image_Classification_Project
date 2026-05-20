/*************************************************************************************************************
 * @file    ble_mus.c
 * @version V1.0
 * @date    2021-01-21
 * @brief   ble mus service
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
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"

#include "ble_mus.h"

/**
 * @brief  DEFINE.
 */
#define BLE_SERVICE_RETURN_IF_ERROR(handle) \
    do                                      \
    {                                       \
        if (handle == 0)                    \
        {                                   \
            return ERR_STA_ERROR;           \
        }                                   \
    } while (0)

// UUID
#define BLE_UUID_MUS_SERVICE           0xFFF0
#define BLE_UUID_MUS_TX_CHARACTERISTIC 0xFFF1
#define BLE_UUID_MUS_RX_CHARACTERISTIC 0xFFF2

/**
 * @brief  TYPEDEF.
 */
typedef enum
{
    BLE_MUS_HANDLE_TX_WRITE,
    BLE_MUS_HANDLE_RX_NOTIFY,
    BLE_MUS_HANDLE_RX_NOTIFY_CFG,
    BLE_MUS_HANDLE_MAX

} enBleMusHandle_t;

/**
 * @brief  LOCAL VARIABLES.
 */
static uint16_t               m_u16BleMusServiceHandle[BLE_MUS_HANDLE_MAX];
static uint8_t                m_u8BleMusRxNotifyCfg = 0;
static ble_mus_data_handler_t m_pfnDataHandlerCB    = NULL;

/**
 * @brief  ble mus gatt services callbacks.
 */
static uint16_t ble_mus_get_attr_len_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle);
static uint16_t ble_mus_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset,
                                     uint8_t *pu8Data, uint16_t u16DataLen);
static uint32_t ble_mus_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16TransactionMode,
                                      uint16_t u16Offset, uint8_t *pu8Data, uint16_t u16DataLen);
static const gatt_serviceCBs_t m_stGattCBs = {
    ble_mus_get_attr_len_cb,
    ble_mus_read_attr_cb,
    ble_mus_write_attr_cb,
};

/**
 * @brief  Initializing the Holtek UART Service.
 * @param  pfnDataHandler: Pointer to function for handling received data.
 * @return uint32_t: Return status.
 */
uint32_t ble_mus_init(ble_mus_data_handler_t pfnDataHandler)
{
    uint16_t u16Handle = 0;

    m_u8BleMusRxNotifyCfg = 0;
    m_pfnDataHandlerCB    = pfnDataHandler;

    // Add the service.
    u16Handle = patch_gatts_api_add_service_start(false, BLE_UUID_MUS_SERVICE, NULL, (gatt_serviceCBs_t *)&m_stGattCBs);
    BLE_SERVICE_RETURN_IF_ERROR(u16Handle);

    // Add the TX Characteristic.
    u16Handle = patch_gatts_api_add_char(0, BLE_UUID_MUS_TX_CHARACTERISTIC, NULL,
                                         (ATT_PROPERTY_WRITE_WITHOUT_RESPONSE | ATT_PROPERTY_DYNAMIC), NULL, 0);
    BLE_SERVICE_RETURN_IF_ERROR(u16Handle);
    m_u16BleMusServiceHandle[BLE_MUS_HANDLE_TX_WRITE] = u16Handle;

    // Add the RX Characteristic.
    u16Handle = patch_gatts_api_add_char(0, BLE_UUID_MUS_RX_CHARACTERISTIC, NULL,
                                         (ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC), NULL, 0);
    BLE_SERVICE_RETURN_IF_ERROR(u16Handle);
    m_u16BleMusServiceHandle[BLE_MUS_HANDLE_RX_NOTIFY] = u16Handle;

    // Add the RX Characteristic Description.
    u16Handle = rom_gatts_api_add_char_descrip_client_config();
    BLE_SERVICE_RETURN_IF_ERROR(u16Handle);
    m_u16BleMusServiceHandle[BLE_MUS_HANDLE_RX_NOTIFY_CFG] = u16Handle;

    patch_gatts_api_add_service_end();

    return ERR_STA_OK;
}

static uint16_t ble_mus_get_attr_len_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
{
    if (m_u16BleMusServiceHandle[BLE_MUS_HANDLE_RX_NOTIFY_CFG] == u16AttrHandle)
    {
        return 2;
    }

    return 0;
}

static uint16_t ble_mus_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset,
                                     uint8_t *pu8Data, uint16_t u16DataLen)
{
    if (m_u16BleMusServiceHandle[BLE_MUS_HANDLE_RX_NOTIFY_CFG] == u16AttrHandle)
    {
        if (pu8Data)
        {
            pu8Data[0] = m_u8BleMusRxNotifyCfg;
            pu8Data[1] = 0;
        }

        return 2;
    }

    return 0;
}

static uint32_t ble_mus_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16TransactionMode,
                                      uint16_t u16Offset, uint8_t *pu8Data, uint16_t u16DataLen)
{
    if ((m_u16BleMusServiceHandle[BLE_MUS_HANDLE_TX_WRITE] == u16AttrHandle)
        && (ATT_TRANSACTION_MODE_NONE == u16TransactionMode))
    {
        if (m_pfnDataHandlerCB != NULL)
        {
            m_pfnDataHandlerCB(u16ConnHandle, pu8Data, u16DataLen);
        }
    }
    else if (m_u16BleMusServiceHandle[BLE_MUS_HANDLE_RX_NOTIFY_CFG] == u16AttrHandle)
    {
        m_u8BleMusRxNotifyCfg = pu8Data[0];
    }

    return 0;
}

uint16_t ble_mus_transfer(uint16_t u16ConnHandle, uint8_t *pu8Data, uint16_t u16DataLen)
{
    return rom_gatts_api_send_notify(u16ConnHandle, m_u16BleMusServiceHandle[BLE_MUS_HANDLE_RX_NOTIFY], pu8Data,
                                     u16DataLen);
}
