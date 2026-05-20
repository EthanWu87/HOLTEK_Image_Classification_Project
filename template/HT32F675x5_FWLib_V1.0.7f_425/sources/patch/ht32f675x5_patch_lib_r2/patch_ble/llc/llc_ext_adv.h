/*************************************************************************************************************
 * @file    llc_ext_adv.h
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
#ifndef LLC_EXT_ADV_H
#define LLC_EXT_ADV_H

////forward declaration
struct stLlcExtAdvNode;
////


#define ADVERTISING_EVENT_PROPERTIES_ADV_IND    (LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_USE_LEGACY_PDUS|\
                                                    LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_CONNECTABLE|\
                                                        LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_SCANNABLE)

#define ADVERTISING_EVENT_PROPERTIES_ADV_DIRECT_IND_LOW_DUTY_CYCLE  (LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_USE_LEGACY_PDUS|\
                                                                        LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_CONNECTABLE|\
                                                                            LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_DIRECTED)
                                                        

#define ADVERTISING_EVENT_PROPERTIES_ADV_DIRECT_IND_HIGH_DUTY_CYCLE  (LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_USE_LEGACY_PDUS|\
                                                                        LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_CONNECTABLE|\
                                                                            LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_DIRECTED|\
                                                                                LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_HIGH_DUTY_CYCLE_DIRECTED_CONNECTABLE)
                                                                                
#define ADVERTISING_EVENT_PROPERTIES_ADV_SCAN_IND    (LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_USE_LEGACY_PDUS|\
                                                        LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_SCANNABLE)
                                                        
#define ADVERTISING_EVENT_PROPERTIES_ADV_NONCONN_IND    (LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_USE_LEGACY_PDUS)


#define LLC_EXT_ADV_IS_CONNECTABLE(Advertising_Event_Properties)        ((Advertising_Event_Properties) & LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_CONNECTABLE)
#define LLC_EXT_ADV_IS_SCANNABLE(Advertising_Event_Properties)          ((Advertising_Event_Properties) & LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_SCANNABLE)
#define LLC_EXT_ADV_IS_DIRECTED(Advertising_Event_Properties)           ((Advertising_Event_Properties) & LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_DIRECTED)
#define LLC_EXT_ADV_IS_HIGH_DUTY_CYCLE(Advertising_Event_Properties)    ((Advertising_Event_Properties) & LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_HIGH_DUTY_CYCLE_DIRECTED_CONNECTABLE)
#define LLC_EXT_ADV_IS_LEGACY(Advertising_Event_Properties)             ((Advertising_Event_Properties) & LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_USE_LEGACY_PDUS)
#define LLC_EXT_ADV_IS_ANONYMOUS(Advertising_Event_Properties)          ((Advertising_Event_Properties) & LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_OMIT_ADDRESS)
#define LLC_EXT_ADV_IS_INCLUDE_TX_POWER(Advertising_Event_Properties)   ((Advertising_Event_Properties) & LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_INCLUDE_TX_POWER)



typedef enum
{
    LLC_EXT_ADV_STATE_IDLE = 0,
    LLC_EXT_ADV_STATE_PRIMARY_TX_ADV,
    LLC_EXT_ADV_STATE_PRIMARY_RX_REQ,
    LLC_EXT_ADV_STATE_PRIMARY_TX_RSP,
    
    LLC_EXT_ADV_STATE_SECONDARY_TX_ADV,
    LLC_EXT_ADV_STATE_SECONDARY_RX_REQ,
    LLC_EXT_ADV_STATE_SECONDARY_TX_RSP,
    
    LLC_EXT_ADV_STATE_SECONDARY_TX_CHAIN,
}
EN_LLC_EXT_ADV_STATE_T;

typedef enum
{
    LLC_EXT_ADV_STATE_MACHINE_IDLE = 0,
    LLC_EXT_ADV_STATE_MACHINE_PRIMARY_ADV,//lagacy PDUs or ADV_EXT_IND
    LLC_EXT_ADV_STATE_MACHINE_SECONDARY_ADV,//AUX_ADV_IND with req and rsp
    LLC_EXT_ADV_STATE_MACHINE_SECONDARY_CHAIN_TX,//ADV_CHAIN_IND
}
EN_LLC_EXT_ADV_STATE_MACHINE_T;


typedef struct stLlcExtAdvNode
{
    stLlcSchedulerEvent_t stSchedulerEvent;
    stLlpPduPointer_t stTxPduPtr;
    stLlpPduPointer_t stRxPduPtr;
    
    
////setting parameters
    uint8_t Advertising_Random_Address[6];
    
    uint8_t Advertising_Handle;
    uint16_t Advertising_Event_Properties;
    uint32_t Primary_Advertising_Interval_Min;
    uint32_t Primary_Advertising_Interval_Max;
    uint8_t Primary_Advertising_Channel_Map;
    uint8_t Own_Address_Type;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint8_t Advertising_Filter_Policy;
    int8_t Advertising_Tx_Power;
    uint8_t Primary_Advertising_PHY;
    uint8_t Secondary_Advertising_Max_Skip;
    uint8_t Secondary_Advertising_PHY;
    uint8_t Advertising_SID;
    uint8_t Scan_Request_Notification_Enable;
    
    uint8_t Secondary_Advertising_Channel_Map[5];
////
    
    
////status
    bool bCreated;
    bool bEnabled;
    bool bAdvertisingRandomAddressSet;
    bool bAcceptUpdatingPdus;
    bool bUpdateAcceptedPdusAddress;
    bool bUpdateAcceptedPdusADI;
    
    uint16_t u16ClockAccuracyPpm;
    
    uint8_t u8ApplySecondaryAdvertisingSkip;
    uint8_t u8CurrentSecondaryAdvertisingSkip;
    
    uint32_t u32DurationUs;
    uint64_t u64AdvStartTimeUs;
    
    uint8_t u8MaxExtendedAdvertisingEvents;
    uint8_t u8CurrentExtendedAdvertisingEvents;
    
    uint64_t u64PrimaryAdvertisingEventStartTime;
    uint64_t u64SecondaryAdvertisingEventStartTime;
    uint8_t u8CurPrimaryChannelIdx;
    uint8_t u8CurSecondaryChannelIdx;
    stLlcAdvChannelPdu_t* pstCurrentChainPdu;
    bool bNeedChainTx;
    
    bool bOwnAddressTxAdd;
    bool bOwnAddressResolvable;
    uint8_t pu8OwnAddress[6];
    uint64_t u64OwnResolvableAddressUpdatedTime;
    uint8_t pu8PeerAddress[6];
    bool bPeerAddressRxAdd;
    
    
    EN_LL_PHY_T enumPrimaryPhy;
    EN_LL_PHY_T enumSecondaryPhy;
    
    uint16_t u16CurrentDID;
    
    EN_LLC_EXT_ADV_STATE_T enumState;
    EN_LLC_EXT_ADV_STATE_MACHINE_T enumStateMachine;
    
    uint8_t u8PrimaryAdvertisingPduNum;
    uint8_t u8PrimaryAdvertisingPduIdx;
    
    
////

    uint32_t u32RxPduHeader;
    uint16_t u16RxPduPaylength;
    uint8_t pu8RxPduPayload[40]__attribute__((aligned(4)));


////accepted PDUs
    uint16_t u16AdvertisingDataLength;
    uint16_t u16ScanResponseDataLength;
    
    stLlcAdvChannelPdu_t* pstPrimaryAdvertisingPdu;
    stLlcAdvChannelPdu_t* pstSecondaryAdvertisingPdu;
    stLlcAdvChannelPdu_t* pstResponsePdu;
    stLlcAdvChannelPdu_t* pstChainPdusHead;
    stLlcAdvChannelPdu_t* pstChainPdusTail;
    
    uint32_t u32PrimaryAdvertisingPduOffsetToEachOther30us;//start to start
    uint32_t u32PrimaryAdvEventOffsetToSecondaryAdvEvent30us;//start to start
    uint32_t u32SecondaryAdvEventOffsetToChainTxUs;//start to start
    
    uint32_t u32PrimaryAdvertisingInterval30us;
////

////updating PDUs
    uint16_t u16UpdatingAdvertisingDataLength;
    uint16_t u16UpdatingScanResponseDataLength;
    stLlcAdvChannelPdu_t* pstUpdatingPrimaryAdvertisingPdu;
    stLlcAdvChannelPdu_t* pstUpdatingSecondaryAdvertisingPdu;
    stLlcAdvChannelPdu_t* pstUpdatingResponsePdu;
    stLlcAdvChannelPdu_t* pstUpdatingChainPdusHead;
    stLlcAdvChannelPdu_t* pstUpdatingChainPdusTail;
    
    uint32_t u32UpdatingPrimaryAdvertisingPduOffsetToEachOther30us;//start to start
    uint32_t u32UpdatingPrimaryAdvEventOffsetToSecondaryAdvEvent30us;//start to start
    uint32_t u32UpdatingSecondaryAdvEventOffsetToChainTxUs;//start to start
    
    uint32_t u32UpdatingPrimaryAdvertisingInterval30us;
////


//// parameters for slave
    bool bCreateSlaveAfterFragmentStopped;
    uint64_t u64PacketEndTime;
    uint64_t u64TimeOfLastSync;
    uint32_t u32RssiRelatedValue;
////

//// parameters for priority
    uint8_t u8PrimaryChannelPriority;
    uint8_t u8SecondaryChannelPriority;
////


////parameters for RPA
    bool bPeerRPA_Resolved;
    uint8_t u8PeerAddrType;
    uint8_t pu8PeerIdentifyAddr[6];
    uint8_t u8PeerIdentifyAddrType;
////

////parameters for Scan Request Notification
    bool bSendScanRequestNotificationAfterFragmentStopped;
    uint8_t Scanner_Address_Type;
    uint8_t Scanner_Address[6];
////

} __attribute__((aligned(8)))
stLlcExtAdv_t;


typedef struct
{
    uint32_t u32AuxPduOffset30us;
    
    bool bMemUsed;
} __attribute__((aligned(8)))
stLlcExtAdvPduExtraInfo_t;




bool rom_llc_ext_adv_mem_init(stLlcExtAdv_t* pstLlcExtAdvMem, uint8_t u8LlcExtAdvNum,
    stLlcExtAdvPduExtraInfo_t* pstLlcExtAdvPduExtraInfoMem, uint8_t u8LlcExtAdvPduExtraInfoNum);

uint8_t rom_llc_ext_adv_get_num(void);

stLlcExtAdv_t* rom_llc_ext_adv_get_instance_by_index(uint8_t u8AdvIdx);

stLlcExtAdv_t* rom_llc_ext_adv_create_instance_by_handle(uint8_t Advertising_Handle);

stLlcExtAdv_t* rom_llc_ext_adv_get_created_instance_by_handle(uint8_t Advertising_Handle);


stLlcAdvChannelPdu_t* rom_llc_ext_adv_alloc_adv_channel_pdu(  uint16_t  u16RequestPayloadSize, bool bWithExtraInfo );
void rom_llc_ext_adv_free_adv_channel_pdu(  stLlcAdvChannelPdu_t* pstPdu );
stLlcExtAdvPduExtraInfo_t* rom_llc_ext_adv_get_pdu_extra_info(stLlcAdvChannelPdu_t* pstPdu);

void rom_llc_ext_adv_init(void);

uint8_t rom_llc_ext_adv_get_next_primary_adv_channel_idx(uint8_t u8CurChannelIdx, uint8_t u8ChannelFlags);
uint8_t rom_llc_ext_adv_get_next_secondary_adv_channel_idx(stLlcExtAdv_t* pstAdv, uint8_t u8CurChannelIdx);
bool rom_llc_ext_adv_check_RPA_and_white_list_disallowed_peer_scan(stLlcExtAdv_t* pstAdv, bool bIsPeerRandomOrPublic, uint8_t pu8PeerAddr[6],
    uint8_t* Scanner_Address_Type, uint8_t Scanner_Address[6]);
bool rom_llc_ext_adv_check_RPA_and_white_list_disallowed_peer_connect(stLlcExtAdv_t* pstAdv, bool bIsPeerRandomOrPublic, uint8_t pu8PeerAddr[6]);

void rom_llc_ext_adv_default_paramters_init(stLlcExtAdv_t* pstAdv);


uint8_t rom_llc_ext_adv_set_advertising_set_random_address(uint8_t Advertising_Handle, uint8_t Advertising_Random_Address[6]); 

uint8_t rom_llc_ext_adv_set_parameters(uint8_t Advertising_Handle,
    uint16_t Advertising_Event_Properties,
    uint32_t Primary_Advertising_Interval_Min,
    uint32_t Primary_Advertising_Interval_Max,
    uint8_t Primary_Advertising_Channel_Map,
    uint8_t Secondary_Advertising_Channel_Map[5],
    uint8_t Own_Address_Type,
    uint8_t Peer_Address_Type,
    uint8_t Peer_Address[6],
    uint8_t Advertising_Filter_Policy,
    int8_t Advertising_Tx_Power,
    uint8_t Primary_Advertising_PHY,
    uint8_t Secondary_Advertising_Max_Skip,
    uint8_t Secondary_Advertising_PHY,
    uint16_t PHY_options,
    uint8_t Advertising_SID,
    uint8_t Scan_Request_Notification_Enable,
    int8_t *ps8SelectedTxPower);
    
uint8_t rom_llc_ext_adv_set_advertising_data(uint8_t Advertising_Handle,
    uint8_t Operation,
    uint8_t Fragment_Preference,
    uint8_t Advertising_Data_Length,
    uint8_t *Advertising_Data);

uint8_t rom_llc_ext_adv_set_scan_response_data(uint8_t Advertising_Handle,
    uint8_t Operation,
    uint8_t Fragment_Preference,
    uint8_t Scan_Response_Data_Length,
    uint8_t *Scan_Response_Data);
    
uint8_t rom_llc_ext_adv_set_enable(uint8_t Parameter_Total_Length, uint8_t* Parameters);

uint8_t rom_llc_ext_adv_read_maximum_advertising_data_length(uint16_t *pu16MaximumAdvertisingDataLength);

uint8_t rom_llc_ext_adv_read_number_of_supported_advertising_sets(uint8_t *pu8NumSupportedAdvertisingSets);

uint8_t rom_llc_ext_adv_remove_advertising_set(uint8_t Advertising_Handle);

uint8_t rom_llc_ext_adv_clear_advertising_sets(void);

bool rom_llc_ext_adv_is_any_advertising_set_enabled(void);

bool rom_llc_ext_adv_is_white_list_in_use(void);

void rom_llc_ext_adv_update_secondary_advertising_channel_map_for_all_extended_adv(uint8_t Secondary_Advertising_Channel_Map[5]);

#endif
