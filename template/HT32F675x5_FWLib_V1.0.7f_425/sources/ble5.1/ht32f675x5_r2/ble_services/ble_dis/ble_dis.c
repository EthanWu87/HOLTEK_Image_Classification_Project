/*************************************************************************************************************
 * @file    ble_dis.c
 * @version V1.0
 * @date    2021-01-21
 * @brief   Device information service
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
#include "ble_dis.h"

#include "app_cfg.h"

/**
 * @brief  DEFINE.
 */
#define BLE_SERVICE_RETURN_IF_ERROR(ret)            \
    if (ret == 0)                                   \
    {                                               \
        PRINTF("Dev info service init failure.\n"); \
        return ERR_STA_ERROR;                       \
    }

/**
 * @brief  LOCAL VARIABLES.
 */
/* System ID characteristic */
static uint8_t m_u8SystemId[DEVINFO_SYSTEM_ID_LEN] = {0, 0, 0, 0, 0, 0, 0, 0};

/* Model Number String characteristic */
static const uint8_t m_u8ModelNumber[] = "Model Number";

/* Serial Number String characteristic */
static const uint8_t m_u8SerialNumber[] = "Serial Number";

/* Firmware Revision String characteristic */
static const uint8_t m_u8FirmwareRev[] = "Firmware Revision";

/* Hardware Revision String characteristic */
static const uint8_t m_u8HardwareRev[] = "Hardware Revision";

/* Software Revision String characteristic */
static const uint8_t m_u8SoftwareRev[] = "Software Revision";

/* Manufacturer Name String characteristic */
static const uint8_t m_u8MfrName[] = "Manufacturer Name";

/* IEEE 11073-20601 Regulatory Certification Data List characteristic */
static const uint8_t m_u811073Cert[] = {
    DEVINFO_11073_BODY_EXP, /* authoritative body type */
    0x00,                   /* authoritative body structure type */
                            /* authoritative body data follows below: */
    'e',
    'x',
    'p',
    'e',
    'r',
    'i',
    'm',
    'e',
    'n',
    't',
    'a',
    'l',
};

static uint8_t m_u8PnpId[DEVINFO_PNP_ID_LEN] = {
    1,            /* Vendor ID source (1=Bluetooth SIG) */
    0,    0,      /* Vendor ID  */
    0,    0,      /* Product ID (vendor-specific) */
    0x10, (0x01), /* Product version (JJ.M.N) */
};

static uint16_t m_u16ServiceHandle;
static uint16_t m_u16ServiceEndHandle;

// ble gap services callbacks.
static uint16_t ble_dis_get_attr_len_cb(uint16_t u8ConnHdl, uint16_t u16Handle);
static uint16_t ble_dis_read_attr_cb(uint16_t u8ConnHdl, uint16_t u16Handle, uint16_t u16Offset, uint8_t *pu8Buf,
                                     uint16_t u16Len);

static const gatt_serviceCBs_t devInfoServiceCBs = {
    ble_dis_get_attr_len_cb,
    ble_dis_read_attr_cb,
    NULL,
};

/**
 * @brief  Initializes the Device Information service by registering GATT
 *          attributes with the GATT server.
 * @return Error Status.
 */
uint8_t ble_dis_init(void)
{
    uint16_t u16handle = 0;

    u16handle = patch_gatts_api_add_service_start(0, DEVINFO_SERV_UUID, NULL, (gatt_serviceCBs_t *)&devInfoServiceCBs);
    BLE_SERVICE_RETURN_IF_ERROR(u16handle);

    /* System ID */
    u16handle = patch_gatts_api_add_char(0, SYSTEM_ID_UUID, NULL, (ATT_PROPERTY_READ | ATT_PROPERTY_DYNAMIC), NULL, 0);
    BLE_SERVICE_RETURN_IF_ERROR(u16handle);
    m_u16ServiceHandle = u16handle;

    /* Model Number String */
    u16handle = patch_gatts_api_add_char(0, MODEL_NUMBER_UUID, NULL, ATT_PROPERTY_READ, (uint8_t *)m_u8ModelNumber,
                                         sizeof(m_u8ModelNumber));
    BLE_SERVICE_RETURN_IF_ERROR(u16handle);

    /* Serial Number String */
    u16handle = patch_gatts_api_add_char(0, SERIAL_NUMBER_UUID, NULL, ATT_PROPERTY_READ, (uint8_t *)m_u8SerialNumber,
                                         sizeof(m_u8SerialNumber));
    BLE_SERVICE_RETURN_IF_ERROR(u16handle);

    /* Firmware Revision String */
    u16handle = patch_gatts_api_add_char(0, FIRMWARE_REV_UUID, NULL, ATT_PROPERTY_READ, (uint8_t *)m_u8FirmwareRev,
                                         sizeof(m_u8FirmwareRev));

    /* Hardware Revision String */
    u16handle = patch_gatts_api_add_char(0, HARDWARE_REV_UUID, NULL, ATT_PROPERTY_READ, (uint8_t *)m_u8HardwareRev,
                                         sizeof(m_u8HardwareRev));

    /* Software Revision String */
    u16handle = patch_gatts_api_add_char(0, SOFTWARE_REV_UUID, NULL, ATT_PROPERTY_READ, (uint8_t *)m_u8SoftwareRev,
                                         sizeof(m_u8SoftwareRev));

    /* Manufacturer Name String */
    u16handle = patch_gatts_api_add_char(0, MANUFACTURER_NAME_UUID, NULL, ATT_PROPERTY_READ, (uint8_t *)m_u8MfrName,
                                         sizeof(m_u8MfrName));

    /* IEEE 11073-20601 Regulatory Certification Data List */
    u16handle = patch_gatts_api_add_char(0, IEEE_11073_CERT_DATA_UUID, NULL, ATT_PROPERTY_READ,
                                         (uint8_t *)m_u811073Cert, sizeof(m_u811073Cert));

    /* PnP ID */
    u16handle = patch_gatts_api_add_char(0, PNP_ID_UUID, NULL, ATT_PROPERTY_READ, m_u8PnpId, sizeof(m_u8PnpId));

    patch_gatts_api_add_service_end();
    m_u16ServiceEndHandle = rom_gatts_api_get_last_attribute_handle();

    return ERR_STA_OK;
}

/**
 * @brief  Set a Device Information parameter.
 * @param  param: Profile parameter ID
 * @param  u8Len: length of data to write
 * @param  pValue: pointer to data to write. This is dependent on the parameter
 *                 ID and WILL be cast to the appropriate data type (example: data
 *                 type of uint16_t will be cast to uint16_t pointer).
 * @return Error Status.
 */
uint8_t ble_dis_set_parameter(uint8_t u8Param, uint8_t u8Len, void *pValue)
{
    uint8_t ret = ERR_STA_OK;

    switch (u8Param)
    {
        case DEVINFO_SYSTEM_ID:
        {
            memcpy(m_u8SystemId, pValue, u8Len);
            break;
        }
        default:
        {
            ret = ERR_STA_ERROR;
            break;
        }
    }

    return (ret);
}

/**
 * @brief   Get a Device Information parameter.
 * @param   u8Param: Profile parameter ID
 * @param   pValue: pointer to data to get.  This is dependent on the parameter
 *          ID and WILL be cast to the appropriate data type (example: data type
 *          of uint16_t will be cast to uint16_t pointer).
 * @return Error Status.
 */
uint8_t ble_dis_get_parameter(uint8_t u8Param, void *pValue)
{
    uint8_t ret = ERR_STA_OK;

    switch (u8Param)
    {
        case DEVINFO_SYSTEM_ID:
        {
            memcpy(pValue, m_u8SystemId, sizeof(m_u8SystemId));
            break;
        }
        case DEVINFO_MODEL_NUMBER:
        {
            memcpy(pValue, m_u8ModelNumber, sizeof(m_u8ModelNumber));
            break;
        }
        case DEVINFO_SERIAL_NUMBER:
        {
            memcpy(pValue, m_u8SerialNumber, sizeof(m_u8SerialNumber));
            break;
        }
        case DEVINFO_FIRMWARE_REV:
        {
            memcpy(pValue, m_u8FirmwareRev, sizeof(m_u8FirmwareRev));
            break;
        }
        case DEVINFO_HARDWARE_REV:
        {
            memcpy(pValue, m_u8HardwareRev, sizeof(m_u8HardwareRev));
            break;
        }
        case DEVINFO_SOFTWARE_REV:
        {
            memcpy(pValue, m_u8SoftwareRev, sizeof(m_u8SoftwareRev));
            break;
        }
        case DEVINFO_MANUFACTURER_NAME:
        {
            memcpy(pValue, m_u8MfrName, sizeof(m_u8MfrName));
            break;
        }
        case DEVINFO_11073_CERT_DATA:
        {
            memcpy(pValue, m_u811073Cert, sizeof(m_u811073Cert));
            break;
        }
        case DEVINFO_PNP_ID:
        {
            memcpy(pValue, m_u8PnpId, sizeof(m_u8PnpId));
            break;
        }
        default:
        {
            ret = ERR_STA_ERROR;
            break;
        }
    }

    return (ret);
}

/**
 * @brief
 * @param  None.
 * @return Error Status.
 */
static uint16_t ble_dis_get_attr_len_cb(uint16_t u8ConnHdl, uint16_t u16Handle)
{
    if (u16Handle == m_u16ServiceHandle)
    {
        return (sizeof(m_u8SystemId));
    }

    return 0;
}

/**
 * @brief  Read an attribute.
 * @param  None.
 * @return Error Status.
 */
static uint16_t ble_dis_read_attr_cb(uint16_t u8ConnHdl, uint16_t u16Handle, uint16_t u16Offset, uint8_t *pu8Buf,
                                     uint16_t u16Len)
{
    if (u16Handle == m_u16ServiceHandle)
    {
        if (pu8Buf)
        {
            memcpy(pu8Buf, m_u8SystemId, sizeof(m_u8SystemId));
        }

        return (sizeof(m_u8SystemId));
    }

    return (0);
}
