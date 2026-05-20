/*************************************************************************************************************
 * @file    llc_legacy_adv.h
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
#ifndef LLC_LEGACY_ADV_H
#define LLC_LEGACY_ADV_H

typedef enum
{
    LLC_LEGACY_ADV_SUB_STATE_IDLE = 0,
    LLC_LEGACY_ADV_SUB_STATE_TX1,
    LLC_LEGACY_ADV_SUB_STATE_RX,
    LLC_LEGACY_ADV_SUB_STATE_TX2,
}
EN_LLC_LEGACY_ADV_SUB_STATE_T;


typedef struct
{
    stLlcSchedulerEvent_t stSchedulerEvent;
    stLlpPduPointer_t stTxPduPtr;
    stLlpPduPointer_t stRxPduPtr;
    uint16_t u16AdvItv625us;
    
    uint32_t u32AdvPduHeader;
    uint32_t u32ScanRspPduHeader;
    
    uint32_t u32RxHeader;
    //rx need 34, set 36 for HW design
    //rx addr must be 4 byte aligned, limit by HW design
    //for better HW compability, set all buffer 4 byte aligned
    uint8_t pu8RxPduPayload[36]__attribute__((aligned(4)));
    uint8_t pu8AdvPduPayload[40]__attribute__((aligned(4)));
    uint8_t pu8ScanRspPduPayload[40]__attribute__((aligned(4)));
    
    uint16_t u16AdvPduPayloadLen;
    uint16_t u16ScanRspPduPayloadLen;
    uint16_t u16RxPduPayloadLen;
    uint8_t u8AdvIdx;
    uint8_t u8ChannelFlags;
    uint8_t u8CurChannelIdx;
    bool bChSel;
    bool bTxAdd;
    bool bOwnAddrTypeRPA;
    uint8_t u8OwnAddrType;
    uint8_t pu8OwnAddr[6];
    uint8_t u8PeerAddrType;
    uint8_t pu8PeerAddr[6]; //for direct adv ,maybe change to RPA
    uint8_t bPeerRPA_Resolved; // 
    uint8_t u8PeerIdentifyAddrType; //from RPA resolve; for direct adv ,from the adv param  Peer_Address_Type
    uint8_t pu8PeerIdentifyAddr[6]; //from RPA resolve; for direct adv ,from the adv param  Peer_Address 
    uint8_t u8AdvertisingDataLength;
    uint8_t pu8AdvertisingData[32];
    uint8_t u8ScanResponseDataLength;
    uint8_t pu8ScanResponseData[32];
    
    uint8_t u8AdvType;
    uint8_t u8FilterPolicy;
    EN_LLC_LEGACY_ADV_SUB_STATE_T enumSubState;
    
    bool bCreateSlaveAfterFragmentStopped;
    uint64_t u64PacketEndTime;
    uint64_t u64TimeOfLastSync;
    uint32_t u32RssiRelatedValue;
    
    bool bEnabled;
    uint64_t u64AdvEventStartTime;
    uint64_t u64AdvStartTime;//for high duty cycle adv only
    uint64_t u64RPAStartTimeUs;
    
    uint32_t u32Reserved;
} __attribute__((aligned(8)))
stLlcLegacyAdv_t;

bool rom_llc_legacy_adv_mem_init(stLlcLegacyAdv_t* pstLlcLegacyAdvMemBuffer, uint8_t u8LlcLegacyAdvNum);
uint8_t rom_llc_legacy_adv_get_num(void);
stLlcLegacyAdv_t* rom_llc_legacy_adv_get_instance(uint8_t u8AdvIdx);

void rom_llc_legacy_adv_init(void);
//must be invoked after rom_llc_address_init
void rom_llc_legacy_adv_default_paramters_init(stLlcLegacyAdv_t* pstLegacyAdv);
uint8_t rom_llc_legacy_adv_set_parameters(uint8_t u8AdvIdx, uint16_t u16AdvertisingIntervalMin625us, uint16_t u16AdvertisingIntervalMax625us, uint8_t u8AdvertisingType,
    uint8_t u8OwnAddressType, uint8_t u8PeerAddressType, uint8_t pu8PeerAddress[6], uint8_t u8AdvertisingChannelMap, uint8_t u8AdvertisingFilterPolicy);
uint8_t rom_llc_legacy_adv_set_advertising_data(uint8_t u8AdvIdx, uint8_t u8AdvertisingDataLength, uint8_t* pu8AdvertisingData);
uint8_t rom_llc_legacy_adv_set_scan_response_data(uint8_t u8AdvIdx, uint8_t u8ScanResponseDataLength, uint8_t* pu8ScanResponseData);
uint8_t rom_llc_legacy_adv_set_advertising_enable(uint8_t u8AdvIdx, uint8_t u8AdvertisingEnable);

bool rom_llc_legacy_adv_is_any_adv_enabled(void);
bool rom_llc_legacy_adv_is_white_list_in_use(void);

//bool rom_llc_legacy_adv_is_white_list_disallowed_peer_scan(uint8_t u8FilterPlicy, bool bIsPeerRandomOrPublic, uint8_t pu8PeerAddr[6]);
//bool rom_llc_legacy_adv_is_white_list_disallowed_peer_connect(uint8_t u8FilterPlicy, bool bIsPeerRandomOrPublic, uint8_t pu8PeerAddr[6]);
bool rom_llc_legacy_adv_is_active(void);
bool rom_llc_legacy_adv_check_RPA_and_white_list_disallowed_peer_connect(stLlcLegacyAdv_t* pstLegacyAdv, bool bIsPeerRandomOrPublic, uint8_t pu8PeerAddr[6]);
bool rom_llc_legacy_adv_check_RPA_and_white_list_disallowed_peer_scan(stLlcLegacyAdv_t* pstLegacyAdv, bool bIsPeerRandomOrPublic, uint8_t pu8PeerAddr[6]);


uint32_t rom_llc_legacy_adv_on_event_blocked(void* pstRoleInstance);
EN_LLP_ERR_T rom_llc_legacy_adv_config_llp (void* pstRoleInstance, uint32_t u32MaxWorkWindowTimeUs);
void rom_llc_legacy_adv_on_llp_fragment_start(void* pstRoleInstance);
bool rom_llc_legacy_adv_on_llp_fragment_stop(void* pstRoleInstance);
EN_LLP_STATE_CMD_T rom_llc_legacy_adv_on_llp_tx_end(void* pstRoleInstance, stLlpTxEndReport_t *pstReport);
EN_LLP_STATE_CMD_T rom_llc_legacy_adv_on_llp_rx_end(void* pstRoleInstance, stLlpRxEndReport_t *pstReport);


uint8_t rom_llc_legacy_adv_get_next_adv_channel_idx(uint8_t u8CurChannelIdx, uint8_t u8ChannelFlags);
void rom_llc_legacy_adv_set_tx_ptr_to_advertising_data(stLlcLegacyAdv_t* pstLegacyAdv);
void rom_llc_legacy_adv_set_tx_ptr_to_scan_response_data(stLlcLegacyAdv_t* pstLegacyAdv);

void rom_llc_legacy_adv_create_slave_after_fragment_stopped(stLlcLegacyAdv_t* pstLegacyAdv, uint64_t u64PacketEndTime,
    uint64_t u64TimeOfLastSync, uint32_t u32RssiRelatedValue);

void rom_llc_legacy_adv_on_event_removed(void* pstRoleInstance);
#endif
