/*************************************************************************************************************
 * @file    type_def.h
 * @version V1.0
 * @date    2023-06-20
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


#ifndef __TYPE_DEF_H__
#define __TYPE_DEF_H__

/**
 * @brief  ENABLE/DISABLE DEFINE
 */
#ifndef DISABLE
    #define DISABLE (0)
#endif

#ifndef ENABLE
    #define ENABLE (1)
#endif

/**
 * @brief  BIT/BYTE/WORD DEFINE
 */
#define LOW_HALF_BYTE_MASK     (0x0F)
#define HIGH_HALF_BYTE_MASK    (0xF0)

#define BYTE_MSK               (0xFF)
#define HALF_WORD_MSK          (0xFFFF)
#define WORD_MSK               (0xFFFFFFFF)
#define DWORD_MSK              (0xFFFFFFFFFFFFFFFF)

#define UINT8_BYTES            (1)
#define UINT16_BYTES           (2)
#define UINT24_BYTES           (3)
#define UINT32_BYTES           (4)
#define UINT128_BYTES          (16)
#define UINT128_WORDS          (4)

#define HALF_BYTE_BITS         (4)
#define BYTE_BITS              (8)
#define HALF_WORD_BITS         (16)
#define WORD_BITS              (32)

#define BYTE_INVALIDE          (0xFF)
#define HALF_WORD_INVALIDE     (0xFFFF)
#define WORD_INVALIDE          (0xFFFFFFFF)

/**
 * @brief  SYSTEM CLOCK DEFINE
 */
#define SYS_CLOCK_16M_HZ       (16000000U)
#define SYS_CLOCK_16M_KHZ      (16000)
#define SYS_CLOCK_16M_MHZ      (16)

#define SYS_CLOCK_32M_HZ       (32000000U)
#define SYS_CLOCK_32M_KHZ      (32000)
#define SYS_CLOCK_32M_MHZ      (32)

#define SYS_CLOCK_48M_HZ       (48000000U)
#define SYS_CLOCK_48M_KHZ      (48000)
#define SYS_CLOCK_48M_MHZ      (48)

#define SYS_CLOCK_64M_HZ       (64000000U)
#define SYS_CLOCK_64M_KHZ      (64000)
#define SYS_CLOCK_64M_MHZ      (64)

#define SYS_CLOCK_128M_HZ      (128000000U)
#define SYS_CLOCK_128M_KHZ     (128000)
#define SYS_CLOCK_128M_MHZ     (128)

/**
 * @brief  Low Power Clock(32KHz) Define
 */
#define LPWR_CLOCK_32K_HZ      (32768U)

#define TIME_US_TO_32K_CNT(us) ((us) * (LPWR_CLOCK_32K_HZ) / 1000000)
#define TIME_MS_TO_32K_CNT(ms) ((ms) * (LPWR_CLOCK_32K_HZ) / 1000)

#endif /* __TYPE_DEF_H__ */
