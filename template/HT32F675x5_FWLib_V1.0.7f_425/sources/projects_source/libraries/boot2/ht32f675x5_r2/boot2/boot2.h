/*************************************************************************************************************
 * @file    boot2.h
 * @version V1.0
 * @date    2020-06-24
 * @brief   Check and update the new code into the specify area
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


#ifndef __BOOT2_H__
#define __BOOT2_H__

/**
 * @brief  Length of Code Header.
 */
#define CODE_HEADER_SIZE_MAX (sizeof(stBoot2Header_t))

/**
 * @brief  typedef
 */
typedef struct __attribute__((aligned(4)))
{
    uint16_t u16HT32Flag;   // HT32 Flag: 2A4B, customer can not change.
    uint8_t  u8Boot2Ver;    // Secondary boot version.
    uint8_t  u8RomVer;      // Rom version.
    uint8_t  u8EncryptFlag; // 0x45: Secondary boot code need encrypte.
    uint8_t  u8Reserved;
    uint16_t u16UserKey;     // If Secondary boot code need encrypte, need this key.
    uint32_t u32CodeSize;    // Secondary boot code size.
    uint32_t u32Crc32;       // Secondary boot code CRC32, not include code header.
    uint32_t u32HeaderCrc32; // Secondary boot code header CRC32.

} stBoot2Header_t;

// Firmware upgrade code information.
typedef struct __attribute__((aligned(4)))
{
    // Information
    uint16_t u16HT32Flag;          // HT32 Flag: 2A4B, customer can not change.
    uint8_t  u8RomVer;             // Rom version.
    uint8_t  u8Boot2Ver;           // Secondary boot version.
    uint32_t u32NeedFwUpgradeFlag; // Need upgrade or not.

    // Firmware upgrade saved information
    uint32_t u32BinFlashAddrOffset; // The offset address of bin code saved in flash.
    uint32_t u32BinCodeSize;        // Bin code size
    uint32_t u32BinCodeCrc;         // Bin code crc32

    // Current running code region.
    uint32_t u32RunningCodeAddrOffset; // Current running code offset address.
    uint32_t u32RunningCodeSize;       // Current running code size.

    uint32_t u32StructCrc; // Struct information crc32.

} stFwUpgradeCodeInfo_t;

/**
 * @brief  Check if app code need update.
 * @return status: @ref EN_ERR_STA_T.
 *         ERR_STA_OK: Update success or no update need;
 *         otherwise return ERR_STA_ERROR.
 */
extern uint8_t boot2_update_flash(void);

/**
 * @brief  Cache init.
 * @return status: @ref EN_ERR_STA_T.
 */
extern uint8_t boot2_cache_init(void);

/**
 * @brief  Load sdk code.
 */
extern void boot2_load_code(void);

#endif /* __BOOT2_H__ */
