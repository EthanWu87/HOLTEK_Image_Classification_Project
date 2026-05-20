/*************************************************************************************************************
 * @file    utility.h
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


#ifndef __UTILITY_H__
#define __UTILITY_H__

/**
 * @brief  Define
 */
#ifndef BV
    #define BV(n)                      (1 << (n))
#endif

#ifndef BF
    #define BF(x, b, s)                (((x) & (b)) >> (s))
#endif

#ifndef MIN
    #define MIN(n, m)                  (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
    #define MAX(n, m)                  (((n) < (m)) ? (m) : (n))
#endif

#ifndef ABS
    #define ABS(n)                     (((n) < 0) ? -(n) : (n))
#endif

#define HI_UINT64(a)                   (((a) >> 32) & 0xFFFFFFFF);
#define LO_UINT64(a)                   ((a) & 0xFFFFFFFF)

/* takes a byte out of a uint32 : var - uint32,  ByteNum - byte to take out (0 - 3) */
#define BREAK_UINT32(var, ByteNum)     (uint8_t)((uint32_t)(((var) >> ((ByteNum)*8)) & 0x00FF))

#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3)     \
                                       ((uint32_t)((uint32_t)((Byte0)&0x00FF)        + \
                                                  ((uint32_t)((Byte1)&0x00FF) << 8)  + \
                                                  ((uint32_t)((Byte2)&0x00FF) << 16) + \
                                                  ((uint32_t)((Byte3)&0x00FF) << 24)))

#define BUILD_UINT16(loByte, hiByte)   ((uint16_t)(((loByte)&0x00FF) + (((hiByte)&0x00FF) << 8)))

#define HI_UINT16(a)                   (((a) >> 8) & 0xFF)
#define LO_UINT16(a)                   ((a)&0xFF)

#define BUILD_UINT8(hiByte, loByte)    ((uint8_t)(((loByte)&0x0F) + (((hiByte)&0x0F) << 4)))

#define HI_UINT8(a)                    (((a) >> 4) & 0x0F)
#define LO_UINT8(a)                    ((a)&0x0F)


enum
{
    UNIT_0_625_MS = 625,        /**< Number of microseconds in 0.625 milliseconds. */
    UNIT_1_25_MS  = 1250,       /**< Number of microseconds in 1.25 milliseconds. */
    UNIT_10_MS    = 10000       /**< Number of microseconds in 10 milliseconds. */
};



/**@brief Macro for converting milliseconds to ticks.
 *
 * @param[in] TIME          Number of milliseconds to convert.
 * @param[in] RESOLUTION    Unit to be converted to in [us/ticks].
 */
#define MSEC_TO_UNITS(TIME, RESOLUTION) (((TIME) * 1000) / (RESOLUTION))


// ram code attribute
#define __RAM_FUNC    __attribute__ ((section(".ram.function")))




/**
 * @brief  Delay cycles.
 * @param  u32Cycles.
 */
extern void rom_delay_cycles(uint32_t u32Cycles);

/**
 * @brief  System delay.
 * @param  u32Time: Time which will delay, unit: us.
 */
extern void rom_delay_us(uint32_t u32Time);

/**
 * @brief  System delay.
 * @param  u32Time: Time which will delay, unit: ms.
 */
extern void rom_delay_ms(uint32_t u32Time);

/**
 * @brief  Transform data of uint8_t to data of uint16_t by little endian.
 * @param  pu8Buf: Point to data buf.
 * @param  pos: Position of data which transform.
 * @return uint16_t.
 */
extern uint16_t rom_little_endian_read_16(const uint8_t *pu8Buf, int32_t pos);

/**
 * @brief  Transform data of uint8_t to data of uint24_t by little endian.
 * @param  pu8Buf: Point to data buf.
 * @param  pos: Position of data which transform.
 * @return uint24_t.
 */
extern uint32_t rom_little_endian_read_24(const uint8_t *pu8Buf, int32_t pos);

/**
 * @brief  Transform data of uint8_t to data of uint32_t by little endian.
 * @param  pu8Buf: Point to data buf.
 * @param  pos: Position of data which transform.
 * @return uint32_t.
 */
extern uint32_t rom_little_endian_read_32(const uint8_t *pu8Buf, int32_t pos);

/**
 * @brief  Transform data of uint16_t to data of uint8_t by little endian.
 * @param  pu8Buf: Point to data buf of uint8_t.
 * @param  pos: Position of data which transform.
 * @param  value: The data of uint16_t.
 * @return None.
 */
extern void rom_little_endian_store_16(uint8_t *pu8Buf, int32_t pos, uint16_t value);

/**
 * @brief  Transform data of uint32_t to data of uint8_t by little endian.
 * @param  pu8Buf: Point to data buf of uint8_t.
 * @param  pos: Position of data which transform.
 * @param  value: The data of uint32_t.
 * @return None.
 */
extern void rom_little_endian_store_32(uint8_t *pu8Buf, int32_t pos, uint32_t value);


/**
 * @brief  Load code.
 *         Code will jump to specific address.
 * @param  u32Addr:
 */
extern void rom_load_code_func(uint32_t u32Addr);

/**
 * @brief  Get rom version.
 * @return uint32_t: Rom version 1~15.
 */
extern uint32_t rom_get_rom_version(void);

#endif /* __UTILITY_H__ */
