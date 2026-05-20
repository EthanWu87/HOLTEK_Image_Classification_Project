/*************************************************************************************************************
 * @file    ble_peripheral.c
 * @version V1.0
 * @date    2022-02-13
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
#include <string.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hal_rf.h"

#include "llc_llp_interface.h"
#include "llp_hw.h"
#include "llp.h"
#include "bluetooth.h"

#include "gap_def.h"
#include "gap_api.h"

#include "app_cfg.h"
#include "utility.h"
#include "gatt_uuid_def.h"

#include "ble_peripheral.h"
#include "ble_gatt_service.h"
#include "ble_gap_service.h"

//=====================================================================================================================
// LOCAL VARIABLES
//=====================================================================================================================
const static uint8_t m_au8DeviceAddr[] = BLE_DEVICE_MAC;

/**
 * @brief  ble peripheral init.
 */
void ble_peripheral_init(void)
{
    // 1. Set rf tx power.
    rom_hal_rf_tx_power_set(TX_0_DBM);

    // 2. Set Device Address
    rom_gap_api_set_public_device_address((uint8_t *)m_au8DeviceAddr);

    ble_gatt_service_init();
    ble_gap_service_init((uint8_t *)BLE_ADV_NAME_STRING,strlen(BLE_ADV_NAME_STRING),GAP_APPEARE_GENERIC_PULSE_OXIMETER);
}

void start_pair_adv(void)
{
    stGapSetAdvertisingParameters_t stAdvParam =
    {
        .u16AdvertisingIntervalMin625us = BLE_ADV_INTERVAL_MS,
        .u16AdvertisingIntervalMax625us = BLE_ADV_INTERVAL_MS,
        .enumAdvertisingType = GAP_ADVERTISING_TYPE_ADV_IND,
        .enumOwnAddressType = GAP_OWN_ADDRESS_TYPE_PUBLIC,
        .u8AdvertisingChannelMap = (GAP_ADV_CHANNEL_MAP_37 | GAP_ADV_CHANNEL_MAP_38 | GAP_ADV_CHANNEL_MAP_39),
        .enumAdvertisingFilterPolicy = GAP_ADV_FILTER_POLICY_CONN_ALL_SCAN_ALL,
    };
    rom_gap_api_set_advertising_parameters(0, &stAdvParam);

    uint8_t u8AdvData[] =
    {
        /* flags */
        0x02,
        GAP_ADTYPE_FLAGS,
        GAP_ADTYPE_FLAGS_GENERAL | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,

        /* service UUID */
        0x03,
        GAP_ADTYPE_16BIT_MORE,
        LO_UINT16(PLX_SERV_UUID),
        HI_UINT16(PLX_SERV_UUID),

        /* apperence */
        0x03,
        GAP_ADTYPE_APPEARANCE,
        LO_UINT16(GAP_APPEARE_GENERIC_PULSE_OXIMETER),
        HI_UINT16(GAP_APPEARE_GENERIC_PULSE_OXIMETER),
    };
    rom_gap_api_set_advertising_data(0, u8AdvData, sizeof(u8AdvData));

    uint8_t u8ScanResponseData[strlen(BLE_ADV_NAME_STRING) + 2];
    u8ScanResponseData[0] = strlen(BLE_ADV_NAME_STRING) + 1;
    u8ScanResponseData[1] = GAP_ADTYPE_LOCAL_NAME_COMPLETE;

    memcpy(&u8ScanResponseData[2], BLE_ADV_NAME_STRING, strlen(BLE_ADV_NAME_STRING));

    rom_gap_api_set_scan_response_data(0, u8ScanResponseData, sizeof(u8ScanResponseData));

    rom_gap_api_set_advertising_enable(0, true);

}

