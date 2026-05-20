/*************************************************************************************************************
 * @file    llc_legacy_initiator.h
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
#ifndef LLC_LEGACY_INITIATOR_H
#define LLC_LEGACY_INITIATOR_H

typedef enum
{
    LLC_LEGACY_INITIATOR_SUB_STATE_IDLE = 0,
    LLC_LEGACY_INITIATOR_SUB_STATE_RX_ADV,
    LLC_LEGACY_INITIATOR_SUB_STATE_TX_IND,
}
EN_LLC_LEGACY_INITIATOR_SUB_STATE_T;


typedef struct
{
    stLlcSchedulerEvent_t stSchedulerEvent;
    stLlpPduPointer_t stTxPduPtr;
    stLlpPduPointer_t stRxPduPtr;
    
    uint32_t u32ConnectIndHeader;
    uint16_t u16ConnectIndPduPayloadLen;
    uint8_t pu8ConnectIndPduPayload[40]__attribute__((aligned(4)));
    
    uint32_t u32RxHeader;
    uint16_t u16RxPduPayloadLen;
    uint8_t pu8RxPduPayload[40]__attribute__((aligned(4)));
    
    
    ////create connection parameters
    uint16_t u16ScanInterval625us;
    uint16_t u16ScanWindow625us;
    
    uint16_t u16ConnInterval1250us;
    uint16_t u16ConnLatency;
    uint16_t u16SupervisionTimeout10ms;
    uint8_t u8InitiatorFilterPolicy;
    bool bOwnAddrTypeRPA;
    bool bPeerRPA_Resolved; // 
    uint8_t u8PeerIdentifyAddrType; //from RPA resolve 
    uint8_t pu8PeerIdentifyAddr[6]; //from RPA resolve 
    bool bOwnTxAdd;
    uint8_t u8OwnAddressType;
    uint8_t pu8OwnAddress[6];
    bool bPeerTxAdd;
    uint8_t u8PeerAddressType;
    uint8_t pu8PeerAddress[6];
    
    uint8_t u8ChannelFlags;
    uint8_t u8CurChannelIdx;
    
    EN_LLC_LEGACY_INITIATOR_SUB_STATE_T enumSubState;
    stLlcConnectionRole_t *pstConnectionRole;
    bool bEnabled;
    
    bool bCreateMasterAfterFragmentStopped;
    uint64_t u64PacketEndTime;
    uint64_t u64TimeOfLastSync;
    uint32_t u32RssiRelatedValue;
    uint64_t u64RPAStartTimeUs;
    
    uint32_t u32Reserved;
} __attribute__((aligned(8)))
stLlcLegacyInitiator_t;

bool rom_llc_legacy_initiator_mem_init(stLlcLegacyInitiator_t* pstLlcLegacyInitiatorMemBuffer);
stLlcLegacyInitiator_t* rom_llc_legacy_initiator_get_instance(void);

void rom_llc_legacy_initiator_init(void);

bool rom_llc_legacy_initiator_is_enabled(void);

bool rom_llc_legacy_initiator_is_white_list_in_use(void);

uint8_t rom_llc_legacy_initiator_create_connection(uint16_t LE_Scan_Interval, uint16_t LE_Scan_Window, uint8_t Initiator_Filter_Policy, uint8_t Peer_Address_Type,
    uint8_t Peer_Address[6], uint8_t Own_Address_Type, uint16_t Conn_Interval_Min, uint16_t Conn_Interval_Max, uint16_t Conn_Latency,
    uint16_t Supervision_Timeout, uint16_t Minimum_CE_Length, uint16_t Maximum_CE_Length, uint8_t Scan_Channel_Map);

uint8_t rom_llc_legacy_initiator_create_connection_cancel(void);

uint32_t rom_llc_legacy_initiator_on_event_blocked(void* pstRoleInstance);
EN_LLP_ERR_T rom_llc_legacy_initiator_config_llp (void* pstRoleInstance, uint32_t u32MaxWorkWindowTimeUs);
void rom_llc_legacy_initiator_on_llp_fragment_start(void* pstRoleInstance);
bool rom_llc_legacy_initiator_on_llp_fragment_stop(void* pstRoleInstance);
EN_LLP_STATE_CMD_T rom_llc_legacy_initiator_on_llp_tx_end(void* pstRoleInstance, stLlpTxEndReport_t *pstReport);
EN_LLP_STATE_CMD_T rom_llc_legacy_initiator_on_llp_rx_end(void* pstRoleInstance, stLlpRxEndReport_t *pstReport);
void rom_llc_legacy_initiator_on_event_removed(void* pstRoleInstance);



#endif
