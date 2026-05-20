/*************************************************************************************************************
 * @file    llc_tool.h
 * @version V1.0
 * @date    2021-02-06
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
#ifndef LLC_TOOL_H
#define LLC_TOOL_H

#define LLC_TOOL_MIN(x,y) ((x>=y)?(y):(x))
#define LLC_TOOL_MAX(x,y) ((x>=y)?(x):(y))

bool rom_llc_tool_is_buf_4_byte_aligned(void* pBuf);

bool rom_llc_tool_is_buf_8_byte_aligned(void* pBuf);

uint16_t rom_llc_tool_read_little_endian_uint16(uint8_t *pu8Buf);

void rom_llc_tool_write_little_endian_uint16(uint8_t *pu8Buf, uint16_t u16Value);

uint32_t rom_llc_tool_read_little_endian_uint32(uint8_t *pu8Buf);

void rom_llc_tool_write_little_endian_uint32(uint8_t *pu8Buf, uint32_t u32Value);

uint64_t rom_llc_tool_read_little_endian_uint64(uint8_t *pu8Buf);;

void rom_llc_tool_write_little_endian_uint64(uint8_t *pu8Buf, uint64_t u64Value);

uint8_t rom_llc_tool_byte_bit_reverse(uint8_t u8Input);

bool rom_llc_tool_is_phy_coded(uint8_t enumLlpPhy);

uint32_t rom_llc_tool_calculate_trx_time_us_by_pdu_size(uint16_t u16PduSize, EN_LL_PHY_T enumLlpPhy);

uint16_t rom_llc_tool_calculate_pdu_payload_max_octets_by_tx_time_without_cte(uint16_t u16MaxTxTimeUs, EN_LL_PHY_T enumLlpPhy);

bool rom_llc_tool_is_array_all_zero ( uint8_t *pu8Array, uint16_t u16Len);

#endif
