/*************************************************************************************************************
 * @file    crc.h
 * @version V1.0
 * @date    2020-01-06
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


#ifndef __CRC_H__
#define __CRC_H__

/**
 * @brief  crc32 default value
 */
#define CRC32_DEFAULT (0xFFFFFFFF)

/**
 * @brief  Get crc8 maxim.
 * @param  pu8Buf: The source data.
 * @param  u32Len: The length of data.
 * @param  u8OldCRC8: The last crc value.
 * @return uint8: crc8.
 */
extern uint8_t rom_crc8_maxim(const uint8_t *pu8Data, uint32_t u32Len, uint8_t u8OldCRC8);

/**
 * @brief  Get crc16 ccitt.
 * @param  pu8Buf: The source data.
 * @param  u32Len: The length of data.
 * @param  u16OldCRC16: The last crc value.
 * @return uint16: crc16.
 */
extern uint16_t rom_get_crc16_ccitt(const uint8_t *pu8Data, uint32_t u32Len, uint16_t u16OldCRC16);

/**
 * @brief  Get crc32.
 * @param  pu8Buf: The source data.
 * @param  u32Len: The length of data.
 * @param  u32OldCRC32: The last crc value.
 * @return uint32: crc32.
 */
extern uint32_t rom_get_crc32(const uint8_t *pu8Buf, uint32_t u32Len, uint32_t u32OldCRC32);

#endif /* __CRC_H__ */
