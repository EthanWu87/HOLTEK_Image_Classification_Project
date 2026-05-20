/*************************************************************************************************************
 * @file    ble_client.c
 * @version V1.0
 * @date    2022-11-13
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

#include "llc_spec_5_1.h"
#include "hci.h"
#include "gatt_uuid_def.h"
#include "gatt_client_api.h"
#include "gatt_service_api.h"

#include "ble_cb_event_def.h"
#include "ble_callback.h"

#include "app_cfg.h"
#include "err_def.h"
#include "utility.h"

/**
 * @brief  LOCAL VARIABLES
 */
static gatt_client_service_t                   m_stMusService;
static gatt_client_characteristic_t            m_stMusTxChar;
static gatt_client_characteristic_t            m_stMusRxChar;
static gatt_client_characteristic_descriptor_t m_stMusCharDes;

/**
 * @brief  Parse ble primary service.
 * @param  u16ConnHandle: BLE connect handle.
 * @param  u16OpCode: Operate code.
 * @param  u16ErrCode: Error code.
 * @param  pu8Buf: Pointer to buffer.
 * @param  u16Len: Buffer length.
 */
static void ble_client_parse_service(uint16_t u16ConnHandle, uint16_t u16OpCode, uint16_t u16ErrCode, uint8_t *pu8Buf,
                                     uint16_t u16Len)
{
    if ((u16ErrCode & 0x8000) == 0 && (u16ErrCode & 0x00FF) == 0 && (pu8Buf != NULL))
    {
        gatt_client_service_t *pstGattService = (gatt_client_service_t *)pu8Buf;

        if (0xFFF0 == pstGattService->uuid16)
        {
            PRINTF("Find service: 0xFFF0\n");
            memcpy(&m_stMusService, pstGattService, sizeof(m_stMusService));
        }
    }
    else if ((u16ErrCode & 0x8000) != 0)
    {
        rom_gatt_client_api_discover_characteristics_for_service(u16ConnHandle, &m_stMusService);
    }
}

/**
 * @brief  Parse ble characteristic.
 * @param  u16ConnHandle: BLE connect handle.
 * @param  u16OpCode: Operate code.
 * @param  u16ErrCode: Error code.
 * @param  pu8Buf: Pointer to buffer.
 * @param  u16Len: Buffer length.
 */
static void ble_client_parse_characteristic(uint16_t u16ConnHandle, uint16_t u16OpCode, uint16_t u16ErrCode,
                                            uint8_t *pu8Buf, uint16_t u16Len)
{
    if ((u16ErrCode & 0x8000) == 0 && (u16ErrCode & 0x00FF) == 0 && (pu8Buf != NULL))
    {
        gatt_client_characteristic_t *pstGattChar = (gatt_client_characteristic_t *)pu8Buf;

        switch (pstGattChar->uuid16)
        {
            case 0xFFF1:
            {
                PRINTF("Find characteristic: 0xFFF1\n");
                memcpy(&m_stMusRxChar, pstGattChar, sizeof(gatt_client_characteristic_t));
                break;
            }
            case 0xFFF2:
            {
                PRINTF("Find characteristic: 0xFFF2\n");
                memcpy(&m_stMusTxChar, pstGattChar, sizeof(gatt_client_characteristic_t));
                break;
            }
            default:
                break;
        }
    }
    else if ((u16ErrCode & 0x8000) != 0)
    {
        rom_gatt_client_api_discover_characteristic_descriptors(u16ConnHandle, &m_stMusTxChar);
    }
}

/**
 * @brief  unpack characteristic descriptor
 * @param  u16ConnHandle: BLE connect handle.
 * @param  u16OpCode: Operate code.
 * @param  u16ErrCode: Error code.
 * @param  pu8Buf: Pointer to buffer.
 * @param  u16Len: Buffer length.
 */
static void ble_client_unpack_char_des(uint16_t u16ConnHandle, uint16_t u16OpCode, uint16_t u16ErrCode, uint8_t *pu8Buf,
                                       uint16_t u16Len)
{
    if ((u16ErrCode & 0x8000) == 0 && (u16ErrCode & 0x00FF) == 0 && (pu8Buf != NULL))
    {
        gatt_client_characteristic_descriptor_t *pCharDes = (gatt_client_characteristic_descriptor_t *)pu8Buf;

        if ((pCharDes->uuid16 == GATT_CLIENT_CHAR_CFG_UUID) && (pCharDes->handle >= m_stMusTxChar.start_handle)
            && (pCharDes->handle <= m_stMusTxChar.end_handle))
        {
            memcpy(&m_stMusCharDes, pCharDes, sizeof(gatt_client_characteristic_descriptor_t));
        }
    }
    else if ((u16ErrCode & 0x8000) != 0)
    {
        uint16_t handle = m_stMusCharDes.handle;
        uint8_t  notify[2];

        notify[0] = LO_UINT16(GATT_CLIENT_CFG_NOTIFY);
        notify[1] = HI_UINT16(GATT_CLIENT_CFG_NOTIFY);

        PRINTF("Enable notify.\n");
        rom_gatt_client_api_write_characteristic_descriptor_using_descriptor_handle(u16ConnHandle, handle,
                                                                                    sizeof(notify), notify);
    }
}

/**
 * @brief   ble client callback, unpack
 */
static void ble_client_unpack_char_des_w_result(uint16_t u16ConnHandle, uint16_t u16OpCode, uint16_t u16ErrCode,
                                                uint8_t *pu8Buf, uint16_t u16Len)
{
    PRINTF("[%d]BLE client done.\n", u16Len);

    uint8_t data[] = {0x12, 0x34, 0x56, 0x78, 0x90};
    rom_gatt_client_api_write_value_of_characteristic_without_response(u16ConnHandle, m_stMusRxChar.value_handle,
                                                                       sizeof(data), data);
}

/**
 * @brief  ble client callback, unpack
 * @param  pu8Buf: format:1b[notify u16OpCode] hdl[2byte] data[len-3]
 */
static void ble_client_unpack_notify(uint16_t u16ConnHandle, uint16_t u16OpCode, uint16_t u16ErrCode, uint8_t *pu8Buf,
                                     uint16_t u16Len)
{
    uint16_t handle = BUILD_UINT16(pu8Buf[0], pu8Buf[1]);

    if (handle == m_stMusTxChar.value_handle)
    {
        uint16_t i;

        PRINTF("[BLE_RX][%d]: ", u16Len);
        for (i = 2; i < u16Len; i++)
        {
            PRINTF("%02X ", pu8Buf[i]);
        }
        PRINTF("\n");
    }
}

/**
 * @brief  ble gatt client callback handler.
 * @param  u16ConnHandle: BLE connect handle.
 * @param  u16OpCode: Operate code.
 * @param  u16ErrCode: Error code.
 * @param  pu8Buf: Pointer to buffer.
 * @param  u16Len: Buffer length.
 * @return 0.
 */
static uint32_t ble_client_callback_handler(uint16_t u16ConnHandle, uint16_t u16OpCode, uint16_t u16ErrCode,
                                            uint8_t *pu8Buf, uint16_t u16Len)
{
    PRINTF("[Client][%d]connHandle: %d, opCode: %d, errCode: %04X\n", u16Len, u16ConnHandle, u16OpCode, u16ErrCode);

    switch (u16OpCode)
    {
        case GATTC_USER_PRIMARY_SERVICES_QUERY_ALL: // Find out all primary services uuid.
        {
            ble_client_parse_service(u16ConnHandle, u16OpCode, u16ErrCode, pu8Buf, u16Len);
            break;
        }
        case GATTC_USER_CHARACTERISTICS_QUERY_ALL: // Get the characteristic uuid of the indicate service.
        {
            ble_client_parse_characteristic(u16ConnHandle, u16OpCode, u16ErrCode, pu8Buf, u16Len);
            break;
        }
        case GATTC_USER_CHARACTERISTICS_DESCRIPTOR_QUERY: // 8
        {
            ble_client_unpack_char_des(u16ConnHandle, u16OpCode, u16ErrCode, pu8Buf, u16Len);
            break;
        }
        case GATTC_USER_CHARACTERISTICS_DESCRIP_WRITE_RESULT: // 19
        {
            ble_client_unpack_char_des_w_result(u16ConnHandle, u16OpCode, u16ErrCode, pu8Buf, u16Len);
            break;
        }
        case GATTC_USER_WRITE_CLIENT_CHARACTERISTIC_CONFIGURATION:
        {
            break;
        }
        case GATTC_USER_NOTIFICATION: // 0
        {
            ble_client_unpack_notify(u16ConnHandle, u16OpCode, u16ErrCode, pu8Buf, u16Len);
            break;
        }
        // format:1d[indication opcode] hdl[2byte] data[u16Len-3]
        case GATTC_USER_INDICATION: // 1
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

/**
 * @brief  ble client init.
 */
void ble_client_init(void)
{
    rom_gatt_client_api_init(ble_client_callback_handler);
}
