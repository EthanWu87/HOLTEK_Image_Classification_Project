/*************************************************************************************************************
 * @file    llc_white_list.h
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
#ifndef LLC_WHITE_LIST_H
#define LLC_WHITE_LIST_H

typedef struct
{
    uint8_t u8AddrType;
    bool bMemUsed;
    uint8_t pu8Addr[6];
} __attribute__((aligned(8)))
stLlcWhiteListDevice_t;


bool rom_llc_white_list_init(stLlcWhiteListDevice_t* pstWhiteListBuf, uint8_t u8WhiteListMaxNum);

bool rom_llc_white_list_is_device_in_list(uint8_t u8AddrType, uint8_t pu8Addr[6]);

uint8_t rom_llc_white_list_read_size(uint8_t* pu8Size);

uint8_t rom_llc_white_list_clear(void);

uint8_t rom_llc_white_list_add_device(uint8_t u8AddressType, uint8_t pu8Address[6]);

uint8_t rom_llc_white_list_remove_device(uint8_t u8AddressType, uint8_t pu8Address[6]);

#endif
