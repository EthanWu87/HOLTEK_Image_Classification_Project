/*************************************************************************************************************
 * @file    utility.c
 * @version V1.0
 * @date    2020-01-03
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
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"

#include "version.h"
#include "utility.h"

/**
 * @brief  typedef
 */
typedef void (*loadCodeFunc)(void);

/**
 * @brief  System delay.
 * @param  u32Time: Time which will delay, unit: us.
 */
void rom_delay_us(uint32_t u32Time)
{
    uint32_t cycles;

    cycles = SystemCoreClock / 1000000U * u32Time;

    rom_delay_cycles(cycles);
}

/**
 * @brief  System delay.
 * @param  u32Time: Time which will delay, unit: ms.
 */
void rom_delay_ms(uint32_t u32Time)
{
    rom_delay_us(u32Time * 1000);
}

/**
 * @brief  Transform data of uint8_t to data of uint16_t by little endian.
 * @param  pu8Buf: Point to data buf.
 * @param  pos: Position of data which transform.
 * @return uint16_t
 */
uint16_t rom_little_endian_read_16(const uint8_t *pu8Buf, int32_t pos)
{
    return (((uint16_t)pu8Buf[pos]) | (((uint16_t)pu8Buf[pos + 1]) << 8));
}

/**
 * @brief  Transform data of uint8_t to data of uint24_t by little endian.
 * @param  pu8Buf: Point to data buf.
 * @param  pos: Position of data which transform.
 * @return uint24_t
 */
uint32_t rom_little_endian_read_24(const uint8_t *pu8Buf, int32_t pos)
{
    return (((uint32_t)pu8Buf[pos])            |
            (((uint32_t)pu8Buf[pos + 1]) << 8) |
            (((uint32_t)pu8Buf[pos + 2]) << 16));
}

/**
 * @brief  Transform data of uint8_t to data of uint32_t by little endian.
 * @param  pu8Buf: Point to data buf.
 * @param  pos: Position of data which transform.
 * @return uint32_t
 */
uint32_t rom_little_endian_read_32(const uint8_t *pu8Buf, int32_t pos)
{
    return (((uint32_t)pu8Buf[pos])             |
            (((uint32_t)pu8Buf[pos + 1]) << 8)  |
            (((uint32_t)pu8Buf[pos + 2]) << 16) |
            (((uint32_t)pu8Buf[pos + 3]) << 24));
}

/**
 * @brief  Transform data of uint16_t to data of uint8_t by little endian.
 * @param  pu8Buf: Point to data buf of uint8_t.
 * @param  pos: Position of data which transform.
 * @param  value: The data of uint16_t.
 */
void rom_little_endian_store_16(uint8_t *pu8Buf, int32_t pos, uint16_t value)
{
    pu8Buf[pos++] = value;
    pu8Buf[pos++] = value >> 8;
}

/**
 * @brief  Transform data of uint32_t to data of uint8_t by little endian.
 * @param  pu8Buf: Point to data buf of uint8_t.
 * @param  pos: Position of data which transform.
 * @param  value: The data of uint32_t.
 */
void rom_little_endian_store_32(uint8_t *pu8Buf, int32_t pos, uint32_t value)
{
    pu8Buf[pos++] = value;
    pu8Buf[pos++] = value >> 8;
    pu8Buf[pos++] = value >> 16;
    pu8Buf[pos++] = value >> 24;
}

/**
 * @brief  Load code.
 *         Code will jump to specific address.
 * @param  u32Addr:
 */
void rom_load_code_func(uint32_t u32Addr)
{
    loadCodeFunc func = (loadCodeFunc)(u32Addr | 1);

    func();

    for (;;);
}

/**
 * @brief  Get rom version.
 * @return uint32_t: Rom version 1~15.
 */
uint32_t rom_get_rom_version(void)
{
    return (ROM_VERSION);
}



