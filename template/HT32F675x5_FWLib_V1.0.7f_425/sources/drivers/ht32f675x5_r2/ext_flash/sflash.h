/*************************************************************************************************************
 * @file    sflash.h
 * @version V1.0
 * @date    2021-06-18
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


#ifndef __SFLASH_H__
#define __SFLASH_H__

#include ".\puya\sflash_p25q40u.h"
#include ".\puya\sflash_p25q40su.h" // 512KB
#include ".\puya\sflash_p25q80su.h" // 1MB
#include ".\puya\sflash_p25q16su.h" // 2MB

#define SFLASH_CHIP_ID              (P25Q80SU_CHIP_ID)
#define SFLASH_PROGRAM_TIME_US      (P25Q80SU_PROGRAM_TIME_US)
#define SFLASH_PAGE_ERASE_TIME_US   (P25Q80SU_PAGE_ERASE_TIME_US)
#define SFLASH_SECTOR_ERASE_TIME_US (P25Q80SU_PAGE_ERASE_TIME_US)
#define SFLASH_CHIP_ERASE_TIME_US   (P25Q80SU_CHIP_ERASE_TIME_US)

#endif /* __SFLASH_H__ */
