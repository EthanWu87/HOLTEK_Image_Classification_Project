/*************************************************************************************************************
 * @file    dev_info.c
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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_efuse.h"

#include "dev_info.h"

/**********************************************************************************************************************
 * @brief  Get Device ID in efuse.
 * @param  u32Did: Buffer for Receiving Device ID.
 * @param  u8DidLen: Length of Receive Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T dev_info_device_id(uint8_t *u32Did,uint8_t u8DidLen)
{
    if (NULL == u32Did || u8DidLen < DEV_INFO_DEVICE_ID_LENGTH)
        return ERR_PARA_ERR;
    
    return rom_hw_efuse_read_bytes(DEV_INFO_DEVICE_ID_BYTE,u32Did,DEV_INFO_DEVICE_ID_LENGTH);
}

/**********************************************************************************************************************
 * @brief  Get Default BLE Device Address in efuse.
 * @param  pu8AddrBuf: Buffer for Receiving Default BLE Device Address.
 * @param  u8BufLen: Length of Receive Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T dev_info_default_ble_addr(uint8_t *pu8AddrBuf,uint8_t u8BufLen)
{
    if (NULL == pu8AddrBuf || u8BufLen < DEV_INFO_DEFAULT_BLE_DEV_ADDR_LENGTH)
        return ERR_PARA_ERR;
    
    return rom_hw_efuse_read_bytes(DEV_INFO_DEFAULT_BLE_DEV_ADDR_BYTE,pu8AddrBuf,DEV_INFO_DEFAULT_BLE_DEV_ADDR_LENGTH);
}

/**********************************************************************************************************************
 * @brief  Get Custom BLE Device Address in efuse.
 * @param  pu8AddrBuf: Buffer for Receiving Custom BLE Device Address.
 * @param  u8BufLen: Length of Receive Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T dev_info_custom_ble_addr(uint8_t *pu8AddrBuf,uint8_t u8BufLen)
{
    if (NULL == pu8AddrBuf || u8BufLen < DEV_INFO_CUSTOM_BLE_DEV_ADDR_LENGTH)
        return ERR_PARA_ERR;
    
    return rom_hw_efuse_read_bytes(DEV_INFO_CUSTOM_BLE_DEV_ADDR_BYTE,pu8AddrBuf,DEV_INFO_CUSTOM_BLE_DEV_ADDR_LENGTH);
}
