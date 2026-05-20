/*************************************************************************************************************
 * @file    version.h
 * @version V1.0
 * @date    2021-05-25
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


#ifndef __VERSION_H__
#define __VERSION_H__

/**
 * @brief  Version Define.
 */
#define HT32_BLE_SOC_FLAG       (0x2A4B)
#define ROM_VERSION             (0x02) // ROM Version
#define BOOT2_VERSION           (0x11)

#define BOOT2_CODE_ENCRYPT_FLAG (0x45)
#define FW_UPGRADE_FLAG         (0x476A6778)

typedef enum 
{
    HT32F675x5       = 0x04,
} EN_CHIP_TYPE;

#endif /* __VERSION_H__ */
