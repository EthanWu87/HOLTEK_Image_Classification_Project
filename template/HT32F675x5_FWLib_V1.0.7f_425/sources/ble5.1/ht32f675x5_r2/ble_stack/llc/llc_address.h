/*************************************************************************************************************
 * @file    llc_address.h
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
#ifndef LLC_ADDRESS_H
#define LLC_ADDRESS_H


void rom_llc_address_init(void);

void rom_llc_address_get_own_public_address(uint8_t pu8Addr[6]);

bool rom_llc_address_get_own_random_address(uint8_t pu8Addr[6]);

bool rom_llc_address_get_own_resolvable_private_address(uint8_t pu8Addr[6]);
bool rom_llc_address_get_own_resolvable_private_address_with_peer_addr(uint8_t pu8LocalRPA[6],uint8_t u8PeerIdentifyAddrType, uint8_t pu8PeerIdentifyAddr[6]);

uint8_t rom_llc_address_set_random_address(uint8_t pu8RandomAddr[6]);

uint8_t rom_llc_address_set_public_address(uint8_t pu8PublicAddr[6]);


#endif
