/*************************************************************************************************************
 * @file    boot2.c
 * @version V1.0
 * @date    2020-06-24
 * @brief   check and update the new code into the specify area
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
#include <stdlib.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "sflash.h"
#include "hw_cache.h"
#include "hw_crg.h"
#include "hw_gpio.h"
#include "hw_flash.h"

#include "utility.h"
#include "crc.h"
#include "version.h"
#include "app_cfg.h"
#include "type_def.h"
#include "app_debug.h"

#include "boot2.h"

/**
 * @brief  MACROS
 */
#define SYS_RESET_AND_RETURN_IF_FALSE(ret) \
    {                                      \
        if (ERR_STA_OK != ret)             \
        {                                  \
            rom_hw_crg_system_reset();     \
            rom_delay_ms(1000);            \
            return ERR_STA_ERROR;          \
        }                                  \
    }

/**
 * @brief  LOCAL VARIABLES.
 */
static uint8_t m_u8DataBuf[SFLASH_PAGE_BYTE_SIZE + 1] __attribute__((aligned(4)));

/**
 * @brief  Calculate crc32.
 * @param  u32SrcAddr: Srouce address.
 * @param  u32Size: Size of data to read.
 * @param  u32InitCrc: The initialized crc32.
 * @return uint32: crc32.
 */
static uint32_t boot2_cal_crc32(uint32_t u32SrcAddr, uint32_t u32Size, uint32_t u32InitCrc)
{
    uint32_t tempSrcAddr = u32SrcAddr;
    uint32_t totalSize   = u32Size;
    uint32_t u32crc      = u32InitCrc;
    uint32_t tempSize    = 0;

    while (totalSize)
    {
        tempSize = (totalSize > SFLASH_PAGE_BYTE_SIZE) ? SFLASH_PAGE_BYTE_SIZE : totalSize;

        if (ERR_STA_OK != rom_hw_flash_read_bytes(FLASH, tempSrcAddr, m_u8DataBuf, tempSize, BOOT2_FLASH_MODE))
        {
            PRINTF("E1");
            return ERR_STA_ERROR;
        }

        u32crc = rom_get_crc32(m_u8DataBuf, tempSize, u32crc);

        tempSrcAddr += tempSize;
        totalSize -= tempSize;
    }

    return u32crc;
}

/**
 * @brief  Copy flash code in ota area to flash.
 * @param  u32SrcAddrOffset: bytes of copy data&code.
 * @param  u32DstAddrOffset:
 * @param  u32Size:
 * @return uint8_t: @ref EN_ERR_STA_T
 */
static uint8_t boot2_flash_to_flash(uint32_t u32SrcAddrOffset, uint32_t u32DstAddrOffset, uint32_t u32Size)
{
    uint32_t tempSrcAddr = u32SrcAddrOffset;
    uint32_t tempDstAddr = u32DstAddrOffset;
    uint32_t totalSize   = u32Size;
    uint32_t tempSize    = 0;

    while (totalSize)
    {
        tempSize = (totalSize > SFLASH_PAGE_BYTE_SIZE) ? SFLASH_PAGE_BYTE_SIZE : totalSize;

        if (ERR_STA_OK != rom_hw_flash_read_bytes(FLASH, tempSrcAddr, m_u8DataBuf, tempSize, BOOT2_FLASH_MODE))
        {
            PRINTF("E2");
            return ERR_STA_ERROR;
        }

        /* Update data into target flash addr */
        if (ERR_STA_OK
            != rom_hw_flash_write_bytes(FLASH, tempDstAddr, m_u8DataBuf, tempSize, BOOT2_FLASH_MODE,
                                        FLASH_PROGRAM_TIMEOUT_US))
        {
            PRINTF("E3");
            return ERR_STA_ERROR;
        }

        tempSrcAddr += tempSize;
        tempDstAddr += tempSize;
        totalSize -= tempSize;
    }

    return ERR_STA_OK;
}

/**
 * @brief  Check if app code need update.
 * @param  pstCodeInfo: Pointer which fw upgrade code information
 * @return If update success or no update need return TRUE, otherwise return FALSE
 */
static uint8_t boot2_check_fw_upgrade_info(stFwUpgradeCodeInfo_t *pstCodeInfo)
{
    uint8_t  i;
    uint8_t *pData  = NULL;
    uint8_t  u8Ret  = 0;
    uint8_t  u8Len  = 0;
    uint32_t u32Crc = 0;

    /* Step 1.1. Get fw upgrade information. */
    PRINTF("=>1.1\n");
    u8Ret = rom_hw_flash_read_bytes(FLASH, FLASH_FW_UPGRADE_CODE_INFO_ADDR_OFFSET, (uint8_t *)pstCodeInfo,
                                    sizeof(stFwUpgradeCodeInfo_t), BOOT2_FLASH_MODE);
    if (ERR_STA_OK != u8Ret)
    {
        return ERR_STA_ERROR;
    }

    /* Step 1.2. Check fw upgrade information struct crc32. */
    PRINTF("=>1.2\n");
    pData  = (uint8_t *)pstCodeInfo;
    u8Len  = sizeof(stFwUpgradeCodeInfo_t) - sizeof(pstCodeInfo->u32StructCrc);
    u32Crc = rom_get_crc32(pData, u8Len, CRC32_DEFAULT);
    if (pstCodeInfo->u32StructCrc != u32Crc)
    {
        return ERR_STA_ERROR;
    }

    /* Step 1.3. Check fw upgrade parameter validity. */
    PRINTF("=>1.3\n");
    if ((pstCodeInfo->u8Boot2Ver != BOOT2_VERSION) || (pstCodeInfo->u8RomVer != ROM_VERSION)
        || (pstCodeInfo->u32BinCodeSize > FLASH_SIZE_MAX) || (pstCodeInfo->u32NeedFwUpgradeFlag != FW_UPGRADE_FLAG))
    {
        return ERR_STA_ERROR;
    }

    /* Step 4. Check crc of code in fw upgrade area. */
    PRINTF("=>1.4\n");
    u32Crc = boot2_cal_crc32(pstCodeInfo->u32BinFlashAddrOffset, pstCodeInfo->u32BinCodeSize, CRC32_DEFAULT);
    if (u32Crc != pstCodeInfo->u32BinCodeCrc)
    {
        return ERR_STA_ERROR;
    }

    PRINTF("=>1.5\n");

    return ERR_STA_OK;
}

/**
 * @brief  Erase code.
 * @param  u32Addr: The address which app or fw upgrade code.
 * @param  u32Size: Code size, unit: byte.
 * @return
 */
static uint8_t boot2_erase_flash(uint32_t u32Addr, uint32_t u32Size)
{
    uint32_t addr = u32Addr;
    uint32_t size = u32Size;
    uint32_t eraseSize;
    uint8_t  retCode = 0;

    do
    {
        if ((size >= SFLASH_BLOCK_64KB_BYTE_SIZE) && (addr % SFLASH_BLOCK_64KB_BYTE_SIZE == 0))
        {
            retCode   = rom_hw_flash_erase(FLASH, ERASE_BLOCK_64KB, addr >> SFLASH_BLOCK_64KB_SHIFT_BITS,
                                           FLASH_PAGE_ERASE_TIMEOUT_US);
            eraseSize = SFLASH_BLOCK_64KB_BYTE_SIZE;
        }
        else if ((size >= SFLASH_BLOCK_32KB_BYTE_SIZE) && (addr % SFLASH_BLOCK_32KB_BYTE_SIZE == 0))
        {
            retCode   = rom_hw_flash_erase(FLASH, ERASE_BLOCK_32KB, addr >> SFLASH_BLOCK_32KB_SHIFT_BITS,
                                           FLASH_PAGE_ERASE_TIMEOUT_US);
            eraseSize = SFLASH_BLOCK_32KB_BYTE_SIZE;
        }
        else if ((size >= SFLASH_SECTOR_BYTE_SIZE) && (addr % SFLASH_SECTOR_BYTE_SIZE == 0))
        {
            retCode =
                rom_hw_flash_erase(FLASH, ERASE_SECTOR, addr >> SFLASH_SECTOR_SHIFT_BITS, FLASH_PAGE_ERASE_TIMEOUT_US);
            eraseSize = SFLASH_SECTOR_BYTE_SIZE;
        }
        else
        {
            retCode =
                rom_hw_flash_erase(FLASH, ERASE_PAGE, addr >> SFLASH_PAGE_SHIFT_BITS, FLASH_PAGE_ERASE_TIMEOUT_US);
            eraseSize = SFLASH_PAGE_BYTE_SIZE;
        }

        SYS_RESET_AND_RETURN_IF_FALSE(retCode);
        size -= eraseSize;
        addr += eraseSize;

    } while (addr < (u32Addr + u32Size));

    return ERR_STA_OK;
}

/**
 * @brief  Check if app code need update.
 * @return status: @ref EN_ERR_STA_T.
 *         ERR_STA_OK: Update success or no update need;
 *         otherwise return ERR_STA_ERROR.
 */
uint8_t boot2_update_flash(void)
{
    uint8_t               retCode = 0;
    uint32_t              crc32   = CRC32_DEFAULT;
    stFwUpgradeCodeInfo_t stCodeInfo;

    /* Setp 1. Check fw upgrade sector information. If no need for updating, return ERR_STA_ERROR. */
    PRINTF("\n=>1\n");
    if (boot2_check_fw_upgrade_info(&stCodeInfo))
    {
        return ERR_STA_ERROR;
    }

    /* Step 2. Erase app code, code size max is u32FwUpgradeCodeSize. */
    PRINTF("=>2\n");
    retCode = boot2_erase_flash(stCodeInfo.u32RunningCodeAddrOffset, stCodeInfo.u32RunningCodeSize);
    SYS_RESET_AND_RETURN_IF_FALSE(retCode);

    /* Setp 3. Copy fw upgrade code from fw upgrade sector to app sector. */
    PRINTF("=>3\n");
    retCode = boot2_flash_to_flash(stCodeInfo.u32BinFlashAddrOffset, stCodeInfo.u32RunningCodeAddrOffset,
                                   stCodeInfo.u32BinCodeSize);
    SYS_RESET_AND_RETURN_IF_FALSE(retCode);

    /* Step 4. Check crc of app code in app code area. */
    PRINTF("=>4\n");
    crc32 = boot2_cal_crc32(stCodeInfo.u32RunningCodeAddrOffset, stCodeInfo.u32BinCodeSize, CRC32_DEFAULT);
    if (crc32 != stCodeInfo.u32BinCodeCrc)
    {
        SYS_RESET_AND_RETURN_IF_FALSE(ERR_STA_ERROR);
    }

    /* Step 5. Erase fw upgrade information */
    PRINTF("=>5\n");
    retCode = rom_hw_flash_erase(FLASH, ERASE_PAGE, FLASH_FW_UPGRADE_CODE_INFO_ADDR_OFFSET >> SFLASH_PAGE_SHIFT_BITS,
                                 FLASH_PAGE_ERASE_TIMEOUT_US);
    SYS_RESET_AND_RETURN_IF_FALSE(retCode);

    /* Step 6. Erase fw upgrade code */
    PRINTF("=>6\n");
    // boot2_erase_flash(stCodeInfo.u32BinFlashAddrOffset, stCodeInfo.u32BinCodeSize);
    rom_hw_crg_system_reset();

    return ERR_STA_OK;
}

/**
 * @brief  Cache init.
 * @return status: @ref EN_ERR_STA_T.
 */
uint8_t boot2_cache_init(void)
{
    uint8_t retCode = 0;

    PRINTF("=>7");

#if 1 /* Cache QSPI */
    PRINTF("=>7.1\n");
    retCode = rom_hw_flash_set_quad_enable(FLASH, ENABLE);
    SYS_RESET_AND_RETURN_IF_FALSE(retCode);

    // default use QPI mode
    retCode = rom_hw_cache_set_mode(BUS_MODE_QPI);
    SYS_RESET_AND_RETURN_IF_FALSE(retCode);
#else /* Cache SPI */
    PRINTF("=>7.2\n");
    retCode = rom_hw_flash_set_quad_enable(FLASH, DISABLE);
    SYS_RESET_AND_RETURN_IF_FALSE(retCode);

    retCode = rom_hw_cache_set_mode(BUS_MODE_SPI);
    SYS_RESET_AND_RETURN_IF_FALSE(retCode);
#endif

    retCode = rom_hw_cache_init(CACHE_ENABLE);
    SYS_RESET_AND_RETURN_IF_FALSE(retCode);

    PRINTF("=>8\n");

#if APP_DEBUG_ENABLED
    uint32_t codeData = 0;

    codeData = (*(volatile uint32_t *)0x10002000);
    PRINTF("[0x10002000]: %08X\n", codeData);
    codeData = (*(volatile uint32_t *)0x10002004);
    PRINTF("[0x10002004]: %08X\n", codeData);
#endif

    return ERR_STA_OK;
}

/**
 * @brief  Load sdk code.
 */
void boot2_load_code(void)
{
    uint32_t addr = 0;

    addr = (*(volatile uint32_t *)(FLASH_RESET_HANDLER_ADDR));
    PRINTF("=>9: %08X\n", addr);

    /* Update success and goto main code */
    rom_load_code_func(addr);
}
