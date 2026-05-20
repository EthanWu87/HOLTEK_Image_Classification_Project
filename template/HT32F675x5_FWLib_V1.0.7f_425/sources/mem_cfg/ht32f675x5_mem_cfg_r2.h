/*************************************************************************************************************
 * @file    ht32f675x5_mem_cfg_r2.h
 * @version V1.0
 * @date    2023-03-03
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



#ifndef __HT32F675X5_MEM_CFG_R2_H__
#define __HT32F675X5_MEM_CFG_R2_H__


//=====================================================================================================================
// MEMOARY MAP DEFINE
//=====================================================================================================================
#define KBYTE                              (1024)

#define FLASH_BYTES_PER_BLOCK_64K          (64 * KBYTE)
#define FLASH_BYTES_PER_BLOCK_64K_SHIFT    (16)//64KB

#define FLASH_BYTES_PER_BLOCK_32K          (32 * KBYTE)
#define FLASH_BYTES_PER_BLOCK_32K_SHIFT    (15)//32KB

#define FLASH_BYTES_PER_SECTOR             (4 * KBYTE)
#define FLASH_BYTES_PER_SECTOR_SHIFT       (12)//4KB

#define FLASH_BYTES_PER_PAGE               (256)
#define FLASH_BYTES_PER_PAGE_SHIFT         (8)//256B


//=============================================================================
// ROM(0x00000000 ~ 0x0001FFFF)
//=============================================================================
// ROM base address
#define ROM_BYTES_PER_BLOCK                (64 * KBYTE)

#define ROM_BASE_ADDR                      (0x00000000)
#define ROM_SIZE_MAX                       (256 * KBYTE) // 256KB

#define ROM_BLOCK0_ADDR                    (ROM_BASE_ADDR + (ROM_BYTES_PER_BLOCK * 0)) // 0x0000_0000
#define ROM_BLOCK0_SIZE_MAX                (ROM_BYTES_PER_BLOCK) // 64K
#if (ROM_BLOCK0_ADDR != 0x00000000)
    #error "ROM_BLOCK0_ADDR error!"
#endif

#define ROM_BLOCK1_ADDR                    (ROM_BASE_ADDR + (ROM_BYTES_PER_BLOCK * 1)) // 0x0001_0000
#define ROM_BLOCK1_SIZE_MAX                (ROM_BYTES_PER_BLOCK) // 64K
#if (ROM_BLOCK1_ADDR != 0x00010000)
    #error "ROM_BLOCK1_ADDR error!"
#endif

#define ROM_BLOCK2_ADDR                    (ROM_BASE_ADDR + (ROM_BYTES_PER_BLOCK * 2)) // 0x0002_0000
#define ROM_BLOCK2_SIZE_MAX                (ROM_BYTES_PER_BLOCK) // 64K
#if (ROM_BLOCK2_ADDR != 0x00020000)
    #error "ROM_BLOCK2_ADDR error!"
#endif

#define ROM_BLOCK3_ADDR                    (ROM_BASE_ADDR + (ROM_BYTES_PER_BLOCK * 3)) // 0x0003_0000
#define ROM_BLOCK3_SIZE_MAX                (ROM_BYTES_PER_BLOCK  - 4) // 65532B, reserve 4 byte for rombist crc
#if (ROM_BLOCK3_ADDR != 0x00030000)
    #error "ROM_BLOCK3_ADDR error!"
#endif

// cp startup
#define ROM_CP_STARTUP_CODE_ADDR           (ROM_BLOCK1_ADDR) // 0x0001_0000
#define ROM_CP_STARTUP_CODE_SIZE_MAX       (1 * KBYTE) // Limited by HW design, DO NOT MODIFY!!!
#if (ROM_CP_STARTUP_CODE_ADDR != 0x00010000)
    #error "ROM_CP_STARTUP_CODE_ADDR error!"
#endif


//=============================================================================
// RAM(0x20000000 ~ 0x2007FFFF)
//=============================================================================
// RAM base address
#define RAM_BASE_ADDR                      (0x20000000)     // S_AHB
#define RAM_SIZE_MAX                       (64 * KBYTE * 4) // 0x4_0000, 256KB
#define RAM_SIZE_KBYTE_MAX                 (64 * 4)         // 0x4_0000, 256KB

// MP RAM In ROM
#define RAM_MP_ROM_DATA_ADDR               (RAM_BASE_ADDR) // 0x2000_0000
#define RAM_MP_ROM_DATA_SIZE_MAX           (2 * KBYTE)
#if (RAM_MP_ROM_DATA_ADDR != 0x20000000)
    #error "RAM_MP_ROM_DATA_ADDR error!"
#endif

// CP RAM In ROM
#define RAM_CP_ROM_DATA_ADDR               (RAM_MP_ROM_DATA_ADDR + RAM_MP_ROM_DATA_SIZE_MAX)
#define RAM_CP_ROM_DATA_SIZE_MAX           (6 * KBYTE)
#if (RAM_CP_ROM_DATA_ADDR != 0x20000800)
    #error "RAM_CP_ROM_DATA_ADDR error!"
#endif

// CP STACK and HEAP
#define RAM_CP_ROM_STACK_SIZE_MAX          (1 * KBYTE) // @ref startup_ARMCM0plus.s
#define RAM_CP_ROM_HEAP_SIZE_MAX           (0 * KBYTE) // @ref startup_ARMCM0plus.s
#define RAM_CP_ROM_STACK_HEAP_SIZE_MAX     (RAM_CP_ROM_STACK_SIZE_MAX + RAM_CP_ROM_HEAP_SIZE_MAX)
#define RAM_CP_ROM_STACK_HEAP_ADDR         (RAM_CP_ROM_DATA_ADDR + RAM_CP_ROM_DATA_SIZE_MAX - RAM_CP_ROM_STACK_HEAP_SIZE_MAX)
#if (RAM_CP_ROM_STACK_HEAP_ADDR != 0x20001C00)
    #error "RAM_CP_ROM_STACK_HEAP_ADDR error!"
#endif

// RAM In ROM
#define RAM_ROM_DATA_ADDR                  (RAM_CP_ROM_DATA_ADDR + RAM_CP_ROM_DATA_SIZE_MAX)
#define RAM_ROM_DATA_SIZE_MAX              (RAM_MP_ROM_DATA_SIZE_MAX + RAM_CP_ROM_DATA_SIZE_MAX)
#if (RAM_ROM_DATA_ADDR != 0x20002000)
    #error "RAM_ROM_DATA_ADDR error!"
#endif

// RAM STACK and HEAP in ROM
// MP STACK and HEAP
#define RAM_MP_ROM_STACK_SIZE_MAX          (4 * KBYTE) // @ref startup_ARMCMP.s
#define RAM_MP_ROM_HEAP_SIZE_MAX           (0 * KBYTE) // @ref startup_ARMCMP.s
#define RAM_MP_ROM_STACK_HEAP_SIZE_MAX     (RAM_MP_ROM_STACK_SIZE_MAX + RAM_MP_ROM_HEAP_SIZE_MAX)
#define RAM_MP_ROM_STACK_HEAP_ADDR         (RAM_ROM_DATA_ADDR)
#if (RAM_MP_ROM_STACK_HEAP_ADDR != 0x20002000)
    #error "RAM_MP_ROM_STACK_HEAP_ADDR error!"
#endif

// MP RAM In 2nd Boot
#define RAM_2ND_BOOT_ADDR                  (RAM_MP_ROM_STACK_HEAP_ADDR + RAM_MP_ROM_STACK_HEAP_SIZE_MAX)
#define RAM_2ND_BOOT_SIZE_MAX              (4 * KBYTE)
#if (RAM_2ND_BOOT_ADDR != 0x20003000)
    #error "RAM_2ND_BOOT_ADDR error!"
#endif


//=============================================================================
// Flash(0x10000000 ~ x)
//=============================================================================
// Flash information
#define FLASH_BASE_ADDR                        (0x10000000) // FLASH0
#define FLASH_BASE_ADDR_OFFSET                 (0x00000000)
#define FLASH_SIZE_MAX                         (512 * KBYTE)

// 2nd boot
#define FLASH_2ND_BOOT_OFFSET                  (FLASH_BASE_ADDR_OFFSET)
#define FLASH_2ND_BOOT_SIZE_MAX                (RAM_2ND_BOOT_SIZE_MAX)

// Firmware upgrade code information
#define FLASH_FW_UPGRADE_CODE_INFO_ADDR        (FLASH_BASE_ADDR + FLASH_2ND_BOOT_SIZE_MAX)
#define FLASH_FW_UPGRADE_CODE_INFO_ADDR_OFFSET (FLASH_2ND_BOOT_OFFSET + FLASH_2ND_BOOT_SIZE_MAX)
#define FLASH_FW_UPGRADE_CODE_INFO_SIZE_MAX    (4 * KBYTE)

#define FLASH_BOOT_RESERVED_SIZE_MAX           (FLASH_2ND_BOOT_SIZE_MAX + FLASH_FW_UPGRADE_CODE_INFO_SIZE_MAX)


#endif /* __HT32F675X5_MEM_CFG_R2_H__ */


