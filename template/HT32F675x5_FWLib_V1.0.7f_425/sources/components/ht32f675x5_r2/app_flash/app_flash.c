/*************************************************************************************************************
 * @file    app_flash.c
 * @version V1.0
 * @date    2022-04-09
 * @brief   Application code of flash module.
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

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "sflash.h"
#include "hw_flash.h"
#include "patch_hw_flash.h"

/**
 * @brief  Read sip flash memory from indicated start address with indicated access mode.
 * @param  u32Addr: Start Address of SIP FLASH MEMORY.
 * @param  pu8Buf: Pointer to a buffer which used to save the readed data.
 * @param  u32Len: Length of read data.
 * @param  enMode: Access mode as below, @ref EN_FLASH_BUS_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T app_flash_read(uint32_t u32Addr, uint8_t *pu8Buf, uint32_t u32Len, EN_FLASH_BUS_MODE_T enMode)
{
    EN_ERR_STA_T enRet      = ERR_STA_OK;
    uint32_t     u32Primask = __get_PRIMASK();

    __disable_irq();

    enRet = patch_hw_flash_read_bytes(FLASH, u32Addr, pu8Buf, u32Len, enMode);

    __set_PRIMASK(u32Primask);

    return enRet;
}

/**
 * @brief  Write the buffer data to  sip flash memory from indicated start address with indicated access mode.
 * @param  u32Addr: Start Address of SIP FLASH MEMORY.
 * @param  pu8Buf: Pointer to a buffer which will be written to flash memory.
 * @param  u32Len: Length of write data, maximum length is 64 * 1024 Bytes;
 * @param  enMode: Access mode as below, @ref EN_FLASH_BUS_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T app_flash_write(uint32_t u32Addr, uint8_t *pu8Buf, uint32_t u32Len, EN_FLASH_BUS_MODE_T enMode)
{
    EN_ERR_STA_T enRet      = ERR_STA_OK;
    uint32_t     u32Primask = __get_PRIMASK();

    __disable_irq();

    enRet = patch_hw_flash_write_bytes(FLASH, u32Addr, pu8Buf, u32Len, enMode, FLASH_PROGRAM_TIMEOUT_US);

    __set_PRIMASK(u32Primask);

    return enRet;
}

/**
 * @brief  Erase sip flash memory with indicated @ref EN_SFLASH_ERASE_SIZE_T number.
 * @param  enSize: The range of Erase, @ref EN_SFLASH_ERASE_SIZE_T.
 * @param  u16Num: Number of Erase.
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T app_flash_erase(EN_SFLASH_ERASE_SIZE_T enSize, uint16_t u16Num)
{
    EN_ERR_STA_T enRet      = ERR_STA_OK;
    uint32_t     u32Primask = __get_PRIMASK();

    __disable_irq();

    enRet = patch_hw_flash_erase(FLASH, enSize, u16Num, FLASH_PAGE_ERASE_TIMEOUT_US);

    __set_PRIMASK(u32Primask);

    return enRet;
}
