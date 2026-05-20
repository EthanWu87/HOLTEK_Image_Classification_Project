/*************************************************************************************************************
 * @file    llc_ext_initiator.h
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
#ifndef LLC_EXT_INITIATOR_H
#define LLC_EXT_INITIATOR_H


#define LLC_EXT_INITIATOR_MAX_PRIMARY_SCANNING_PHYS  (2)// 1M and Coded
#define LLC_EXT_INITIATOR_MAX_CONNECTION_PARAMETERS  (3)// 1M, 2M and Coded


typedef struct
{
    bool bScanningPhyEnabled;
    
    EN_LL_PHY_T enumPhy;
    
    ////Setting Parameters
    uint16_t Scan_Interval;
    uint16_t Scan_Window;
    uint8_t Channel_Map;
    ////
    
    uint32_t u32ChannelScanWindowUs;
    
    uint8_t u8CurrentChannelIdx;
    
    uint64_t u64OriginalStartTimeUs;
    uint32_t u32EventStartTimeOffsetUs;
} __attribute__((aligned(8)))
stLlcExtInitiatorPrimaryScanningPhy_t;

typedef struct
{
    bool bConnectionParametersProvided;
    EN_LLC_SPEC_5_1_HCI_PHY_T PHY;
    uint16_t Conn_Interval_Min;
    uint16_t Conn_Interval_Max;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    
    uint32_t u32ConnectReqHeader;
    uint16_t u16ConnectReqPduPayloadLen;
    uint8_t pu8ConnectReqPduPayload[LLC_SPEC_5_1_CONNECT_IND_PAYLOAD_SIZE]__attribute__((aligned(4)));
}
__attribute__((aligned(4)))
stLlcExtInitiatorConnectionParameters_t;

typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint32_t u32MinWorkTimeUs;
} __attribute__((aligned(8)))
stLlcExtInitiatorTiming_t;


typedef enum
{
    LLC_EXT_INITIATOR_STATE_IDLE = 0,
    LLC_EXT_INITIATOR_STATE_RX_ADV,
    LLC_EXT_INITIATOR_STATE_TX_REQ,
    LLC_EXT_INITIATOR_STATE_RX_RSP,
}
EN_LLC_EXT_INITIATOR_STATE_T;


typedef struct stLlcExtInitiatorAdvertisingSetNode
{
    uint64_t u64StartTimeUs;
    uint32_t u32AnchorWindowUs;
    uint32_t u32WorkTimeUs;
    
    EN_LL_PHY_T enumPrimaryPhy;
    EN_LL_PHY_T enumSecondaryPhy;
    uint8_t u8ChannelIdx;
    
    bool bDirected;
    EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T enumAddressType;
    uint8_t pu8Address[6];
    EN_LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_T enumDirectAddressType;
    uint8_t pu8DirectAddress[6];
    uint16_t u16DID;
    uint8_t u8SID;
    
    stLlcAdvChannelPdu_t* pstAdvPdu;
    stLlcAdvChannelPdu_t* pstRspPdu;
    
    struct stLlcExtInitiatorAdvertisingSetNode* prev;
    struct stLlcExtInitiatorAdvertisingSetNode* next;
    
    bool bMemUsed;
} __attribute__((aligned(8)))
stLlcExtInitiatorAdvertisingSet_t;

typedef struct
{
    stLlcSchedulerEvent_t stSchedulerEvent;
    stLlpPduPointer_t stTxPduPtr;
    stLlpPduPointer_t stRxPduPtr;
    
    stLlcAdvChannelPdu_t stRxEmptyPdu;
    stLlcAdvChannelPdu_t* pstRecevingPdu;
    
    ////Setting Parameters
    uint8_t Own_Address_Type;
    uint8_t Initiator_Filter_Policy;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    ////
    
    
    stLlcExtInitiatorPrimaryScanningPhy_t stPrimaryScanningPhys[LLC_EXT_INITIATOR_MAX_PRIMARY_SCANNING_PHYS];
    stLlcExtInitiatorConnectionParameters_t stConnectionParameters[LLC_EXT_INITIATOR_MAX_CONNECTION_PARAMETERS];
    
    bool bOwnAddressTxAdd;
    bool bOwnAddressResolvable;
    uint8_t pu8OwnAddress[6];
    uint64_t u64OwnResolvableAddressUpdatedTime;
    
    bool bEnabled;
    bool bIsScanningPhyPrimary;
    uint32_t u32ScanningPhyMaxWorkTimeUs;
    EN_LLC_EXT_INITIATOR_STATE_T enumState;
    
    
    ////primary scanning
    uint32_t u32PrimaryScanIntervalUs;
    uint64_t u64IntervalStartTimeUs;
    stLlcExtInitiatorPrimaryScanningPhy_t* pstCurrentPrimaryScanningPhy;
    stLlcAdvChannelPdu_t* pstReceivedExtendedPduWhenPrimaryScanning;
    bool bConnectIndSentWhenPrimaryScanning;
    ////
    
    ////secondary scanning
    stLlcExtInitiatorAdvertisingSet_t* pstSecondaryScanningSetScheduleListHead;
    stLlcExtInitiatorAdvertisingSet_t* pstSecondaryScanningSetScheduleListTail;
    stLlcExtInitiatorAdvertisingSet_t* pstCurrentSecondaryScanningSet;
    
    bool bSecondaryFragmentTruncated;
    ////
    
    ////connection
    stLlcConnectionRole_t* pstConnectionRole;
    stLlcExtInitiatorConnectionParameters_t* pstChosenConnectionParameters;
    bool bCreateConnection;
    stLlcMasterInitParam_t stMasterInitParam;
    ////
} __attribute__((aligned(8)))
stLlcExtInitiator_t;

typedef struct
{
    uint64_t u64PduStartTimeUs;
    uint64_t u64PduEndTimeUs;
    EN_LL_PHY_T enumPhy;
    
    EN_LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_LEGACY_EVENT_TYPE_T enumEventTypeForPrimaryScanning;
    EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T enumAddressTypeForPrimaryScanning;
    uint8_t pu8AddressForPrimaryScanning[6];
    EN_LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_T enumDirectAddressTypeForPrimaryScanning;
    uint8_t pu8DirectAddressForPrimaryScanning[6];
    
    bool bMemUsed;
} __attribute__((aligned(8)))
stLlcExtInitiatorPduExtraInfo_t;


typedef struct
{
    uint8_t Initiator_Filter_Policy;
    uint8_t Own_Address_Type;
    
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    
    bool Scan_PHY_Enabled_1M;
    uint16_t Scan_Interval_1M;
    uint16_t Scan_Window_1M;
    uint8_t Scan_Map_1M;
    
    bool Scan_PHY_Enabled_Coded;
    uint16_t Scan_Interval_Coded;
    uint16_t Scan_Window_Coded;
    uint8_t Scan_Map_Coded;
    
    
    bool Connection_Parameters_Provided_1M;
    uint16_t Conn_Interval_Min_1M;
    uint16_t Conn_Interval_Max_1M;
    uint16_t Conn_Latency_1M;
    uint16_t Supervision_Timeout_1M;
    
    bool Connection_Parameters_Provided_2M;
    uint16_t Conn_Interval_Min_2M;
    uint16_t Conn_Interval_Max_2M;
    uint16_t Conn_Latency_2M;
    uint16_t Supervision_Timeout_2M;
    
    bool Connection_Parameters_Provided_Coded;
    uint16_t Conn_Interval_Min_Coded;
    uint16_t Conn_Interval_Max_Coded;
    uint16_t Conn_Latency_Coded;
    uint16_t Supervision_Timeout_Coded;
} __attribute__((aligned(4)))
stLlcExtInitiatorSetParameters_t;


bool rom_llc_ext_initiator_mem_init(stLlcExtInitiator_t* pstLlcExtInitiatorMemBuffer,
    stLlcExtInitiatorPduExtraInfo_t* pstLlcExtInitiatorPduExtraInfoMem, uint8_t u8LlcExtInitiatorPduExtraInfoNum,
    stLlcExtInitiatorAdvertisingSet_t* pstLlcExtInitiatorAdvertisingSetMemBuffer, uint8_t u8LlcExtInitiatorAdvertisingSetNum);


stLlcAdvChannelPdu_t* rom_llc_ext_initiator_alloc_pdu(stLlcExtInitiator_t* pstInitiator);
bool rom_llc_ext_initiator_is_pdu_empty(stLlcExtInitiator_t* pstInitiator, stLlcAdvChannelPdu_t* pstPdu);
void rom_llc_ext_initiator_free_pdu(stLlcExtInitiator_t* pstInitiator, stLlcAdvChannelPdu_t* pstPdu);

stLlcExtInitiatorPduExtraInfo_t* rom_llc_ext_initiator_get_pdu_extra_info(stLlcAdvChannelPdu_t* pstPdu);

stLlcExtInitiatorAdvertisingSet_t* rom_llc_ext_initiator_alloc_advertising_set(void);

void rom_llc_ext_initiator_free_advertising_set(stLlcExtInitiatorAdvertisingSet_t* pstAdvertisingSet);

void rom_llc_ext_initiator_init(void);

bool rom_llc_ext_initiator_is_enabled(void);

bool rom_llc_ext_initiator_is_white_list_in_use(void);

uint8_t rom_llc_ext_initiator_create_connection(stLlcExtInitiatorSetParameters_t* pstParameters);

uint8_t rom_llc_ext_initiator_create_connection_cancel(void);

bool rom_llc_ext_initiator_check_RPA_and_white_list_disallowed(stLlcExtInitiator_t* pstInitiator, 
    bool bPeerTxAdd, uint8_t pu8PeerAdvA[6], 
    bool bPeerRxAdd, uint8_t pu8PeerTargetA[6],
    EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T* Peer_Address_Type, uint8_t Peer_Address[6],
    EN_LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_T* Direct_Address_Type, uint8_t Direct_Address[6]);

#endif
