/*************************************************************************************************************
 * @file    dev_info.h
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
#ifndef DEV_INFO_H
#define DEV_INFO_H

#define DEV_INFO_DEFAULT_BLE_DEV_ADDR_BYTE      (0x09)
#define DEV_INFO_DEVICE_ID_BYTE                 (0x31)
#define DEV_INFO_CUSTOM_BLE_DEV_ADDR_BYTE       (0x34)

#define DEV_INFO_DEFAULT_BLE_DEV_ADDR_LENGTH    (6)
#define DEV_INFO_DEVICE_ID_LENGTH               (3)
#define DEV_INFO_CUSTOM_BLE_DEV_ADDR_LENGTH     (6)

/**
 * @brief  Get Device ID in efuse.
 * @param  u32Did: Buffer for Receiving Device ID.
 * @param  u8DidLen: Length of Receive Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T dev_info_device_id(uint8_t *u32Did,uint8_t u8DidLen);

/**
 * @brief  Get Default BLE Device Address in efuse.
 * @param  pu8AddrBuf: Buffer for Receiving Default BLE Device Address.
 * @param  u8BufLen: Length of Receive Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T dev_info_default_ble_addr(uint8_t *pu8AddrBuf,uint8_t u8BufLen);

/**
 * @brief  Get Custom BLE Device Address in efuse.
 * @param  pu8AddrBuf: Buffer for Receiving Custom BLE Device Address.
 * @param  u8BufLen: Length of Receive Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T dev_info_custom_ble_addr(uint8_t *pu8AddrBuf,uint8_t u8BufLen);

#endif