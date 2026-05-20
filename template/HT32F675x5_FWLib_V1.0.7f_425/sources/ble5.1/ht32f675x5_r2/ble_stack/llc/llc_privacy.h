/*************************************************************************************************************
 * @file    llc_privacy.h
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
#ifndef LLC_PRIVACY_H
#define LLC_PRIVACY_H

typedef enum
{
    PRIVACY_NETWORK_MODE     = 0,
    PRIVACY_DEVICE_MODE      = 1,
}
Privacy_Mode_type;

typedef struct
{
    uint8_t u8PeerIdentifyAddrType;
    bool bMemUsed;    
    uint8_t pu8PeerIdentifyAddr[6];
    uint8_t u8Privacy_mode;
    uint8_t rfu;
    uint8_t pu8CurrentPeerRPA[6]; //current RPA
    uint8_t pu8PeerIRK[16];
    uint8_t pu8LocalIRK[16];
} __attribute__((aligned(8)))
stLlcResolvingListDevice_t;

bool rom_llc_privacy_is_addr_RPA ( uint8_t pu8Addr[6]);
bool rom_llc_privacy_is_addr_NON_RPA ( uint8_t pu8Addr[6]);
bool rom_llc_privacy_is_addr_static_random_addr ( uint8_t pu8Addr[6]);

bool rom_llc_privacy_is_has_local_irk(uint8_t* pu8Idx);
bool rom_llc_privacy_resolve_RPA(uint8_t pu8IRK[16],uint8_t pu8RPA_in[6]);
bool rom_llc_privacy_gen_RPA(uint8_t pu8IRK[16],uint8_t pu8RPA_out[6]);
bool rom_llc_privacy_init(stLlcResolvingListDevice_t* pstResolvingListBuf, uint8_t u8ResolvingListMaxNum);

bool rom_llc_privacy_is_device_in_resolving_list(uint8_t u8PeerIdentifyAddrType, uint8_t pu8PeerIdentifyAddr[6],uint8_t *privacy_mode,uint8_t *irk_is_all_zero);

uint8_t rom_llc_privacy_Add_Device_To_Resolving_List(uint8_t Peer_Identity_Address_Type,
    uint8_t Peer_Identity_Address[6],
    uint8_t Peer_IRK[16],
    uint8_t Local_IRK[16]);

uint8_t rom_llc_privacy_Remove_Device_From_Resolving_List (uint8_t Peer_Identity_Address_Type, uint8_t Peer_Identity_Address[6]);
uint8_t rom_llc_privacy_Clear_Resolving_List(void);
uint8_t rom_llc_privacy_Read_Resolving_List_Size(void);
uint8_t rom_llc_privacy_Set_Address_Resolution_Enable(uint8_t Address_Resolution_Enable);
uint8_t rom_llc_privacy_Set_Resolvable_Private_Address_Timeout(uint16_t RPA_Timeout);
uint8_t rom_llc_privacy_Set_Privacy_Mode(uint8_t Peer_Identity_Address_Type, uint8_t Peer_Identity_Address[6], uint8_t Privacy_Mode);
bool rom_llc_privacy_resolve_local_RPA ( uint8_t pu8RPA_local[6] );
bool rom_llc_privacy_get_own_resolvable_private_address_with_peer_addr(uint8_t pu8LocalRPA[6],uint8_t u8PeerIdentifyAddrType, uint8_t pu8PeerIdentifyAddr[6]);

bool rom_llc_privacy_gen_RPA_for_local(uint8_t u8Idx);
void rom_llc_privacy_get_local_RPA(uint8_t pu8Addr[6]);
bool rom_llc_privacy_resolve_peer_RPA(uint8_t pu8RPA_peer[6],uint8_t pu8PeerIdentifyAddr[6],uint8_t* pu8PeerIdentifyAddrType);
bool rom_llc_privacy_is_device_in_resolving_list(uint8_t u8PeerIdentifyAddrType, uint8_t pu8PeerIdentifyAddr[6],uint8_t *privacy_mode,uint8_t *irk_is_all_zero);
bool rom_llc_privacy_is_resolving_enabled(void);
bool rom_llc_privacy_gen_and_get_peer_RPA_with_peer_addr(uint8_t pu8PeerRPA[6],uint8_t u8PeerIdentifyAddrType, uint8_t pu8PeerIdentifyAddr[6]);
bool rom_llc_privacy_is_RPA_timeout ( uint64_t* u64StartUs );
#endif
