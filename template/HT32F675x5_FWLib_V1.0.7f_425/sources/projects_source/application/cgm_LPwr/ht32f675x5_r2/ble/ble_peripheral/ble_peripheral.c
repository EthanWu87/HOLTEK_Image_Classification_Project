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
#include "ble_gatt_service.h"
#include "ble_gap_service.h"
#include "dev_info.h"
#include "mmu.h"
#include "ble_peripheral.h"

static char gcDevName[TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN + 1] = BLE_ADV_NAME_STRING;
static uint16_t gu16AdvInterval = BLE_ADV_INTERVAL_MS;

static void ble_get_dev_addr(uint8_t *pu8Addr)
{
    uint16_t u16CheckSum = 0;
    uint8_t u8Addr[6] = {0};

    dev_info_default_ble_addr(u8Addr,6);

    for(uint8_t u8Idx=0;u8Idx<6;u8Idx++)
        u16CheckSum += u8Addr[u8Idx];

    if (0 == u16CheckSum)
        return;

    memcpy(pu8Addr,u8Addr,6);
    return;
}

EN_ERR_STA_T ble_set_dev_name(const char *pDevName)
{
    if (NULL == pDevName || strlen(pDevName) > TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN)
        return ERR_PARA_ERR;

    memset(gcDevName,0,sizeof(gcDevName));
    memcpy(gcDevName,pDevName,strlen(pDevName));

    return ERR_STA_OK;
}

EN_ERR_STA_T ble_set_adv_interval(uint16_t u16AdvInterval)
{
    if (0x20 > u16AdvInterval || 0x4000 < u16AdvInterval)
        return ERR_PARA_ERR;

    gu16AdvInterval = u16AdvInterval;

    return ERR_STA_OK;
}

/**
 * @brief  ble peripheral init.
 */
void ble_peripheral_init(void)
{
    uint8_t u8DeviceAddr[] = BLE_DEVICE_MAC;

    // 1. Get Device Address
    ble_get_dev_addr(u8DeviceAddr);

    // 2. Set Device Address
    rom_gap_api_set_public_device_address((uint8_t *)u8DeviceAddr);

    ble_gap_service_init((uint8_t *)gcDevName, strlen(gcDevName),GAP_APPEARE_CONTINUOUS_GLUCOSE_MONITOR);
    ble_gatt_service_init();
}

void start_pair_adv(void)
{
    uint16_t u16ScanRspDataLen = 0;
    uint8_t u8ScanResponseData[25];

    stGapSetAdvertisingParameters_t stAdvParam =
    {
        .u16AdvertisingIntervalMin625us = gu16AdvInterval,
        .u16AdvertisingIntervalMax625us = gu16AdvInterval,
        .enumAdvertisingType = GAP_ADVERTISING_TYPE_ADV_IND,
        .enumOwnAddressType = GAP_OWN_ADDRESS_TYPE_PUBLIC,
#if (BLE_ADV_CHANNEL_NUM == 1)
        .u8AdvertisingChannelMap = (GAP_ADV_CHANNEL_MAP_37),
#elif (BLE_ADV_CHANNEL_NUM == 2)
        .u8AdvertisingChannelMap = (GAP_ADV_CHANNEL_MAP_37 | GAP_ADV_CHANNEL_MAP_39),
#else
        .u8AdvertisingChannelMap = (GAP_ADV_CHANNEL_MAP_37 | GAP_ADV_CHANNEL_MAP_38 | GAP_ADV_CHANNEL_MAP_39),
#endif
        .enumAdvertisingFilterPolicy = GAP_ADV_FILTER_POLICY_CONN_ALL_SCAN_ALL,
    };
    rom_gap_api_set_advertising_parameters(0, &stAdvParam);

    uint8_t u8AdvData[] =
    {
        /* flags */
        0x02,
        GAP_ADTYPE_FLAGS,
        GAP_ADTYPE_FLAGS_GENERAL | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,

        /* appearance */
        0x03,
        GAP_ADTYPE_APPEARANCE,
        LO_UINT16(GAP_APPEARE_CONTINUOUS_GLUCOSE_MONITOR),
        HI_UINT16(GAP_APPEARE_CONTINUOUS_GLUCOSE_MONITOR),

        /* service UUID */
        0x03,
        GAP_ADTYPE_16BIT_MORE,
        LO_UINT16(CGM_SERV_UUID),
        HI_UINT16(CGM_SERV_UUID)
    };
    rom_gap_api_set_advertising_data(0, u8AdvData, sizeof(u8AdvData));

    u8ScanResponseData[u16ScanRspDataLen++] = strlen(gcDevName) + 1;
    u8ScanResponseData[u16ScanRspDataLen++] = GAP_ADTYPE_LOCAL_NAME_COMPLETE;

    memcpy(&u8ScanResponseData[2],gcDevName,strlen(gcDevName));
    u16ScanRspDataLen += (strlen(gcDevName));

    rom_gap_api_set_scan_response_data(0,u8ScanResponseData,u16ScanRspDataLen);

    rom_gap_api_set_advertising_enable(0,true);
}

