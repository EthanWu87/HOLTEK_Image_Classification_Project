/*************************************************************************************************************
 * @file    llc_legacy_scan.h
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
#ifndef LLC_LEGACY_SCAN_H
#define LLC_LEGACY_SCAN_H

typedef enum
{
    LLC_LEGACY_SCAN_SUB_STATE_IDLE = 0,
    LLC_LEGACY_SCAN_SUB_STATE_RX_ADV,
    LLC_LEGACY_SCAN_SUB_STATE_TX_REQ,
    LLC_LEGACY_SCAN_SUB_STATE_RX_RSP,
}
EN_LLC_LEGACY_SCAN_SUB_STATE_T;


typedef struct
{
    ////event-related variable
    stLlcSchedulerEvent_t stSchedulerEvent;
    stLlpPduPointer_t stTxPduPtr;
    stLlpPduPointer_t stRxPduPtr;
    stLlcAdvChannelPdu_t stRxEmptyPdu;
    stLlcAdvChannelPdu_t* pstRecevingPdu;
    stLlcAdvChannelPdu_t* pstRxPduListHead;
    stLlcAdvChannelPdu_t* pstRxPduListTail;
    uint32_t u32ScanReqHeader;
    uint16_t u16ScanReqPduPayloadLen;
    uint8_t pu8ScanReqPduPayload[12]__attribute__((aligned(4)));
    
    ////scan parameters
    uint8_t u8ScanType;
    uint16_t u16ScanItv625us;
    uint16_t u16ScanWindow625us;
    uint8_t u8OwnAddrType;
    bool bOwnAddrTypeRPA;
    uint8_t u8ScanFilterPolicy;
    uint8_t u8ChannelFlags;
    
    ////variable
    bool bOwnTxAdd;
    uint8_t pu8OwnAddr[6];
    
    
    ////status
    uint8_t u8CurChannelIdx;
    EN_LLC_LEGACY_SCAN_SUB_STATE_T enumSubState;
    bool bEnabled;
    bool bGenerateDisabledEvent;
    bool bDuplicateFilterEnabled;
    bool bLastDeviceAdvDuplicated;
    bool bLastDeviceRspDuplicated;
    bool bLastDeviceTxAdd;
    uint8_t pu8LastDeviceAddr[6];
    uint16_t u16BackoffCount;
    uint16_t u16UpperLimit;
    uint8_t u8BackOffConsecutiveSuccessCount;
    uint8_t u8BackOffConsecutiveFailureCount;
    bool bReportMsgSent;
    uint64_t u64RPAStartTimeUs;
    
    uint32_t u32Reserved;
} __attribute__((aligned(8)))
stLlcLegacyScan_t;

bool rom_llc_legacy_scan_mem_init(stLlcLegacyScan_t* pstLlcLegacyScanMemBuffer);
stLlcLegacyScan_t* rom_llc_legacy_scan_get_instance(void);

void rom_llc_legacy_scan_init(void);
uint8_t rom_llc_legacy_scan_set_scan_parameters(uint8_t u8ScanType, uint16_t u16ScanInterval625us, uint16_t u16ScanWindow625us, 
    uint8_t u8OwnAddrType, uint8_t u8ScanFilterPolicy, uint8_t u8ChannelMap);
void rom_llc_legacy_scan_set_scan_enable(uint8_t u8LEScanEnable, uint8_t u8FilterDuplicates);

bool rom_llc_legacy_scan_is_enabled(void);

bool rom_llc_legacy_scan_is_white_list_in_use(void);

uint32_t rom_llc_legacy_scan_on_event_blocked(void* pstRoleInstance);
EN_LLP_ERR_T rom_llc_legacy_scan_config_llp (void* pstRoleInstance, uint32_t u32MaxWorkWindowTimeUs);
void rom_llc_legacy_scan_on_llp_fragment_start(void* pstRoleInstance);
bool rom_llc_legacy_scan_on_llp_fragment_stop(void* pstRoleInstance);
EN_LLP_STATE_CMD_T rom_llc_legacy_scan_on_llp_tx_end(void* pstRoleInstance, stLlpTxEndReport_t *pstReport);
EN_LLP_STATE_CMD_T rom_llc_legacy_scan_on_llp_rx_end(void* pstRoleInstance, stLlpRxEndReport_t *pstReport);
void rom_llc_legacy_scan_on_event_removed(void* pstRoleInstance);




#endif
