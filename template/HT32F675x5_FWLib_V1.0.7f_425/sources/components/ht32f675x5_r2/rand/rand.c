/*************************************************************************************************************
 * @file    rand.c
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


#include <stdint.h>
#include <stdio.h>

#include "utility.h"
#include "rand.h"

/**
 * @brief  rand seed
 */
static uint32_t m_u32RandSeed;

/**
 * @brief  Get rand
 * @param  pu32Seed.
 */
static uint32_t get_rand_r(uint32_t *pu32Seed)
{
    uint32_t u32Result;
    uint32_t u32NextSeed = *pu32Seed;

    u32NextSeed = (u32NextSeed * 1103515245) + 12345; /* permutate seed */
    u32Result   = u32NextSeed & 0xfffc0000;           /* use only top 14 bits */

    u32NextSeed = (u32NextSeed * 1103515245) + 12345;             /* permutate seed */
    u32Result   = u32Result + ((u32NextSeed & 0xffe00000) >> 14); /* top 11 bits */

    u32NextSeed = (u32NextSeed * 1103515245) + 12345;               /* permutate seed */
    u32Result   = u32Result + ((u32NextSeed & 0xfe000000) >> (25)); /* use only top 7 bits */

    *pu32Seed = u32NextSeed;

    return (u32Result & SYS_RAND_MAX);
}

/**
 * @brief  Rand init.
 * @param  u32Seed: Rand seed.
 */
void rom_rand_init(uint32_t u32Seed)
{
    m_u32RandSeed = u32Seed;
}

/**
 * @brief  Get rand data of 32bit.
 * @return uint32_t: Rand data.
 */
uint32_t rom_get_rand(void)
{
    return (get_rand_r(&m_u32RandSeed));
}

/**
 * @brief  Get rand data of 128bit
 * @param  pu8Buf: Point to data buffer which saved.
 */
void rom_get_rand_128(uint8_t *pu8Buf)
{
    uint8_t  i;
    uint32_t u32Result;

    for (i = 0; i < 4; i++)
    {
        u32Result               = rom_get_rand();
        *(pu8Buf + (4 * i) + 0) = BREAK_UINT32(u32Result, 0);
        *(pu8Buf + (4 * i) + 1) = BREAK_UINT32(u32Result, 1);
        *(pu8Buf + (4 * i) + 2) = BREAK_UINT32(u32Result, 2);
        *(pu8Buf + (4 * i) + 3) = BREAK_UINT32(u32Result, 3);
    }
}
