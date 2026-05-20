/*************************************************************************************************************
 * @file    rand.h
 * @version V1.0
 * @date    2023-07-11
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


#ifndef __RAND_H__
#define __RAND_H__

/**
 * @brief  Define
 */
#define SYS_RAND_MAX 0xFFFFFFFF

/**
 * @brief  Rand init.
 * @param  u32Seed: Rand seed.
 */
extern void rom_rand_init(uint32_t u32Seed);

/**
 * @brief  Get rand data of 32bit.
 * @return uint32_t: Rand data.
 */
extern uint32_t rom_get_rand(void);

/**
 * @brief  Get rand data of 128bit
 * @param  pu8Buf: Point to data buffer which saved.
 */
extern void rom_get_rand_128(uint8_t *pu8Buf);

#endif /* __RAND_H__ */
