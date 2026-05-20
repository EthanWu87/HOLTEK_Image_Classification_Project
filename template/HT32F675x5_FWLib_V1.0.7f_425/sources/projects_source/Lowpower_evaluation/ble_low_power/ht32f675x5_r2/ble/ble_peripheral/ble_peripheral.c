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
#include "hw_efuse.h"
#include "hal_rf.h"

#include "llc_llp_interface.h"
#include "llp_hw.h"
#include "llp.h"
#include "bluetooth.h"

#include "gap_def.h"
#include "gap_api.h"

#include "app_cfg.h"
#include "utility.h"
#include "type_def.h"

/**
 * @brief  Read efuse product information as mac.
 * @param  pu8Buf: Pointer to save mac.
 * @return status, @ref EN_ERR_STA_T.
 */
static uint8_t ble_peripheral_set_device_addr(uint8_t *pu8Buf)
{
    uint8_t       u8efuse[6];
    const uint8_t au8Mac[] = BLE_DEVICE_MAC;

    if (NULL == pu8Buf)
    {
        return ERR_PARA_ERR;
    }

    rom_hw_efuse_read_bytes(EFUSE_PRODUCTION_DATE_YEAR_ADDR, u8efuse, sizeof(u8efuse));

    if ((u8efuse[0] == 0) && (u8efuse[1] == 0))
    {
        memcpy(pu8Buf, au8Mac, 6);
    }
    else
    {
        pu8Buf[5] = u8efuse[5];                                                        // Host and Socket ID
        pu8Buf[4] = (LO_UINT8(u8efuse[0]) << HALF_BYTE_BITS) | (HI_UINT8(u8efuse[0])); // Year and Month
        pu8Buf[3] = u8efuse[1];                                                        // Day
        pu8Buf[2] = u8efuse[2];                                                        // Hour
        pu8Buf[1] = u8efuse[3] & EFUSE_PRODUCTION_TIME_MINUTE_MSK;                     // Minute
        pu8Buf[0] = u8efuse[4] & EFUSE_PRODUCTION_TIME_SECOND_MSK;                     // Second
    }

    return ERR_STA_OK;
}

/**
 * @brief  ble peripheral init.
 */
void ble_peripheral_init(void)
{
    uint8_t au8DeviceAddr[6];

    // 2. Set Device Address
    ble_peripheral_set_device_addr(au8DeviceAddr);
    rom_gap_api_set_public_device_address(au8DeviceAddr);

    // 3. Set ble advertising parameters.
    stGapSetAdvertisingParameters_t stAdvParam = {
#if (LOW_POWER_DCDC_BLE_ADV_ITV_100MS||LOW_POWER_LDO_BLE_ADV_ITV_100MS)
        .u16AdvertisingIntervalMin625us = BLE_ADV_INTERVAL_100MS,
        .u16AdvertisingIntervalMax625us = BLE_ADV_INTERVAL_100MS,
        
#elif (LOW_POWER_DCDC_BLE_ADV_ITV_1000MS||LOW_POWER_LDO_BLE_ADV_ITV_1000MS)
        .u16AdvertisingIntervalMin625us = BLE_ADV_INTERVAL_1000MS,
        .u16AdvertisingIntervalMax625us = BLE_ADV_INTERVAL_1000MS,
        
#elif (LOW_POWER_DCDC_BLE_ADV_ITV_10000MS||LOW_POWER_LDO_BLE_ADV_ITV_10000MS)
        .u16AdvertisingIntervalMin625us = BLE_ADV_INTERVAL_10000MS,
        .u16AdvertisingIntervalMax625us = BLE_ADV_INTERVAL_10000MS,
        
#else
        .u16AdvertisingIntervalMin625us = BLE_ADV_INTERVAL_100MS,
        .u16AdvertisingIntervalMax625us = BLE_ADV_INTERVAL_100MS,
        
#endif
        .enumAdvertisingType            = GAP_ADVERTISING_TYPE_ADV_IND,
        .enumOwnAddressType             = GAP_OWN_ADDRESS_TYPE_RESOLVABLE_OR_PUBLIC,
        .u8AdvertisingChannelMap        = (GAP_ADV_CHANNEL_MAP_37 | GAP_ADV_CHANNEL_MAP_38 | GAP_ADV_CHANNEL_MAP_39),
        .enumAdvertisingFilterPolicy    = GAP_ADV_FILTER_POLICY_CONN_ALL_SCAN_ALL,
    };
    rom_gap_api_set_advertising_parameters(0, &stAdvParam);

    // 4. Set ble advertising data.
    uint8_t u8AdvData[BLE_ADV_DATA_MAX_LENTH] = {
        // flags
        2, // length of this data
        GAP_ADTYPE_FLAGS,
        GAP_ADTYPE_FLAGS_GENERAL | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,
        strlen(BLE_ADV_NAME_STRING) + 1,
        GAP_ADTYPE_LOCAL_NAME_COMPLETE,
    };
    memcpy(&u8AdvData[5], BLE_ADV_NAME_STRING, strlen(BLE_ADV_NAME_STRING));
    rom_gap_api_set_advertising_data(0, u8AdvData, sizeof(u8AdvData));

    // 5. Set ble scan response data.
    uint8_t u8ScanResponseData[strlen(BLE_ADV_NAME_STRING) + 2];
    u8ScanResponseData[0] = strlen(BLE_ADV_NAME_STRING) + 1;
    u8ScanResponseData[1] = GAP_ADTYPE_LOCAL_NAME_COMPLETE;

    memcpy(&u8ScanResponseData[2], BLE_ADV_NAME_STRING, strlen(BLE_ADV_NAME_STRING));

    rom_gap_api_set_scan_response_data(0, u8ScanResponseData, sizeof(u8ScanResponseData));

    // 6. SM init.
    rom_gap_api_sm_bond_info_save_by_app_config_only_for_legacy_pair(0);
    rom_gap_api_update_pair_para(IO_CAPABILITY_NO_INPUT_NO_OUTPUT, SM_AUTHREQ_BONDING | SM_AUTHREQ_MITM_PROTECTION, 16);

    // 7. Enable ble advertising.
    rom_gap_api_set_advertising_enable(0, true);
}
