/*************************************************************************************************************
 * @file    llc_ext_scan.h
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
#ifndef LLC_EXT_SCAN_H
#define LLC_EXT_SCAN_H


#define LLC_EXT_SCAN_MAX_PRIMARY_SCANNING_PHYS  (2)// 1M and Coded


typedef struct
{
    bool bScanningPhyEnabled;
    
    EN_LL_PHY_T enumPhy;
    
    ////Setting Parameters
    uint8_t Scan_Type;
    uint16_t Scan_Interval;
    uint16_t Scan_Window;
    
    uint8_t Channel_Map;
    ////
    
    uint32_t u32ChannelScanWindowUs;
    
    uint8_t u8CurrentChannelIdx;
    
    uint64_t u64OriginalStartTimeUs;
    uint32_t u32EventStartTimeOffsetUs;
} __attribute__((aligned(8)))
stLlcExtScanPrimaryScanningPhy_t;


typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint32_t u32MinWorkTimeUs;
} __attribute__((aligned(8)))
stLlcExtScanTiming_t;


typedef enum
{
    LLC_EXT_SCAN_STATE_IDLE = 0,
    LLC_EXT_SCAN_STATE_RX_ADV,
    LLC_EXT_SCAN_STATE_TX_REQ,
    LLC_EXT_SCAN_STATE_RX_RSP,
}
EN_LLC_EXT_SCAN_STATE_T;


typedef enum
{
    LLC_EXT_SCAN_ADVERTISING_SET_STATE_IDLE = 0,
    LLC_EXT_SCAN_ADVERTISING_SET_STATE_AUX,
    LLC_EXT_SCAN_ADVERTISING_SET_STATE_CHAIN,
}
EN_LLC_EXT_SCAN_ADVERTISING_SET_STATE_T;

typedef struct stLlcExtScanAdvertisingSetNode
{
    EN_LLC_EXT_SCAN_ADVERTISING_SET_STATE_T enumSetState;
    
    uint64_t u64StartTimeUs;
    uint32_t u32AnchorWindowUs;
    uint32_t u32WorkTimeUs;
    
    EN_LL_PHY_T enumPrimaryPhy;
    EN_LL_PHY_T enumSecondaryPhy;
    uint8_t u8ChannelIdx;
    
    bool bScannable;
    bool bConnectable;
    bool bDirected;
    EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T enumAddressType;
    uint8_t pu8Address[6];
    EN_LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_T enumDirectAddressType;
    uint8_t pu8DirectAddress[6];
    uint16_t u16DID;
    uint8_t u8SID;
    
    int8_t s8LastTxPower;
    uint32_t u32RssiRelatedValueForSetWithoutAuxiliaryPacket;
    stLlcAdvChannelPdu_t* pstAdvPdu;
    stLlcAdvChannelPdu_t* pstRspPdu;
    stLlcAdvChannelPdu_t* pstChainPduListHead;
    stLlcAdvChannelPdu_t* pstChainPduListTail;
    
    struct stLlcExtScanAdvertisingSetNode* prev;
    struct stLlcExtScanAdvertisingSetNode* next;
    
    bool bMemUsed;
} __attribute__((aligned(8)))
stLlcExtScanAdvertisingSet_t;

typedef struct
{
    stLlcSchedulerEvent_t stSchedulerEvent;
    stLlpPduPointer_t stTxPduPtr;
    stLlpPduPointer_t stRxPduPtr;
    
    stLlcAdvChannelPdu_t stRxEmptyPdu;
    stLlcAdvChannelPdu_t* pstRecevingPdu;
    
    uint32_t u32ScanReqHeader;
    uint16_t u16ScanReqPduPayloadLen;
    uint8_t pu8ScanReqPduPayload[LLC_SPEC_5_1_SCAN_REQ_PAYLOAD_SIZE]__attribute__((aligned(4)));
    
    
    ////Setting Parameters
    uint8_t Own_Address_Type;
    uint8_t Scanning_Filter_Policy;
    uint8_t Filter_Duplicates;
    uint16_t Duration;
    uint16_t Period;
    ////
    
    
    stLlcExtScanPrimaryScanningPhy_t stPrimaryScanningPhys[LLC_EXT_SCAN_MAX_PRIMARY_SCANNING_PHYS];
    
    bool bOwnAddressTxAdd;
    bool bOwnAddressResolvable;
    uint8_t pu8OwnAddress[6];
    uint64_t u64OwnResolvableAddressUpdatedTime;
    
    uint64_t u64PeriodUs;
    uint32_t u32DurationUs;
    
    
    bool bEnabled;
    bool bDisabledByHost;
    bool bUpdateEnabledParameters;
    bool bIsScanningPhyPrimary;
    uint32_t u32ScanningPhyMaxWorkTimeUs;
    EN_LLC_EXT_SCAN_STATE_T enumState;
    
    
    ////primary scanning
    uint32_t u32PrimaryScanIntervalUs;
    uint64_t u64IntervalStartTimeUs;
    uint64_t u64DurationStartTimeUs;
    stLlcExtScanPrimaryScanningPhy_t* pstCurrentPrimaryScanningPhy;
    stLlcAdvChannelPdu_t* pstReceivedExtendedPduWhenPrimaryScanning;
    
    uint8_t u8BackOffConsecutiveSuccessCount;
    uint8_t u8BackOffConsecutiveFailureCount;
    uint16_t u16BackoffCount;
    uint16_t u16UpperLimit;
    
    stLlcAdvChannelPdu_t* pstPrimaryScanningReportPduListHead;
    stLlcAdvChannelPdu_t* pstPrimaryScanningReportPduListTail;
    bool bPrimaryReporting;
    ////
    
    ////secondary scanning
    stLlcExtScanAdvertisingSet_t* pstSecondaryScanningSetScheduleListHead;
    stLlcExtScanAdvertisingSet_t* pstSecondaryScanningSetScheduleListTail;
    stLlcExtScanAdvertisingSet_t* pstCurrentSecondaryScanningSet;
    
    stLlcExtScanAdvertisingSet_t* pstSecondaryScanningSetReportListHead;
    stLlcExtScanAdvertisingSet_t* pstSecondaryScanningSetReportListTail;
    
    bool bSecondaryFragmentTruncated;
    bool bSecondaryReporting;
    ////
    
    ////priority
    bool bIsPrimaryScanningBlocked;
    uint8_t u8PriorityForPrimaryScannning;
    uint8_t u8PriorityForSecondaryScannning;
    ////
} __attribute__((aligned(8)))
stLlcExtScan_t;

typedef struct
{
    uint64_t u64PduStartTimeUs;
    EN_LL_PHY_T enumPhy;
    
    EN_LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_LEGACY_EVENT_TYPE_T enumEventTypeForPrimaryScanning;
    EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T enumAddressTypeForPrimaryScanning;
    uint8_t pu8AddressForPrimaryScanning[6];
    EN_LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_T enumDirectAddressTypeForPrimaryScanning;
    uint8_t pu8DirectAddressForPrimaryScanning[6];
    
    bool bMemUsed;
} __attribute__((aligned(8)))
stLlcExtScanPduExtraInfo_t;


typedef struct
{
    uint8_t Own_Address_Type;
    uint8_t Scanning_Filter_Policy;
    
    bool Scan_PHY_Enabled_1M;
    uint8_t Scan_Type_1M;
    uint16_t Scan_Interval_1M;
    uint16_t Scan_Window_1M;
    uint8_t Scan_Map_1M;
    
    bool Scan_PHY_Enabled_Coded;
    uint8_t Scan_Type_Coded;
    uint16_t Scan_Interval_Coded;
    uint16_t Scan_Window_Coded;
    uint8_t Scan_Map_Coded;
} __attribute__((aligned(4)))
stLlcExtScanSetParameters_t;


bool rom_llc_ext_scan_mem_init(stLlcExtScan_t* pstLlcExtScanMemBuffer,
    stLlcExtScanPduExtraInfo_t* pstLlcExtScanPduExtraInfoMem, uint8_t u8LlcExtScanPduExtraInfoNum,
    stLlcExtScanAdvertisingSet_t* pstLlcExtScanAdvertisingSetMemBuffer, uint8_t u8LlcExtScanAdvertisingSetNum);


stLlcAdvChannelPdu_t* rom_llc_ext_scan_alloc_pdu(stLlcExtScan_t* pstScan);
bool rom_llc_ext_scan_is_pdu_empty(stLlcExtScan_t* pstScan, stLlcAdvChannelPdu_t* pstPdu);
void rom_llc_ext_scan_free_pdu(stLlcExtScan_t* pstScan, stLlcAdvChannelPdu_t* pstPdu);

stLlcExtScanPduExtraInfo_t* rom_llc_ext_scan_get_pdu_extra_info(stLlcAdvChannelPdu_t* pstPdu);

stLlcExtScanAdvertisingSet_t* rom_llc_ext_scan_alloc_advertising_set(void);

void rom_llc_ext_scan_free_advertising_set(stLlcExtScanAdvertisingSet_t* pstAdvertisingSet);

void rom_llc_ext_scan_init(void);

bool rom_llc_ext_scan_is_enabled(void);

bool rom_llc_ext_scan_is_white_list_in_use(void);

uint8_t rom_llc_ext_scan_set_parameters(stLlcExtScanSetParameters_t* pstParameters);

void rom_llc_ext_scan_set_enable(uint8_t Enable, uint8_t Filter_Duplicates, uint16_t Duration, uint16_t Period);

bool rom_llc_ext_scan_check_RPA_and_white_list_disallowed(stLlcExtScan_t* pstScan, 
    bool bPeerTxAdd, uint8_t pu8PeerAdvA[6], 
    bool bPeerRxAdd, uint8_t pu8PeerTargetA[6],
    EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T* Peer_Address_Type, uint8_t Peer_Address[6],
    EN_LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_T* Direct_Address_Type, uint8_t Direct_Address[6]);

#endif
