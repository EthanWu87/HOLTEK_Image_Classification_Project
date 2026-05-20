/*************************************************************************************************************
 * @file    sflash_p25q16su.h
 * @version V1.0
 * @date    2023-08-11
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


#ifndef __SFLASH_P25Q16SU_H__
#define __SFLASH_P25Q16SU_H__

#define P25Q16SU_CHIP_ID                (0x156085)

#define P25Q16SU_PROGRAM_TIME_US        (3000)   // 1.5ms ~ 3ms
#define P25Q16SU_PAGE_ERASE_TIME_US     (30000)  // 16ms ~ 30ms
#define P25Q16SU_SECTOR_ERASE_TIME_US   (30000)  // 16ms ~ 30ms
#define P25Q16SU_BLOCK32K_ERASE_TIME_US (30000)  // 16ms ~ 30ms
#define P25Q16SU_BLOCK64K_ERASE_TIME_US (30000)  // 16ms ~ 30ms
#define P25Q16SU_CHIP_ERASE_TIME_US     (180000) // 130ms ~ 180ms

#define P25Q16SU_MEM_SIZE_BYTE          (0x200000) // 2MBytes
#define P25Q16SU_ADDR_BITS              (0x18)

#endif /* __SFLASH_P25Q16SU_H__ */
