/*************************************************************************************************************
 * @file    llc_connection_role.h
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
#ifndef LLC_CONNECTION_ROLE_H
#define LLC_CONNECTION_ROLE_H



typedef enum
{
    LLC_CONNECTION_ROLE_STATE_DISCONNECTED  = 0,
    LLC_CONNECTION_ROLE_STATE_CREATED       = 1,//connecting
    LLC_CONNECTION_ROLE_STATE_ESTABLISHED   = 2,//connected
    LLC_CONNECTION_ROLE_STATE_DISCONNECTING = 3,
    
}
EN_LLC_CONNECTION_ROLE_STATE_T;

typedef enum
{
    LLC_CONNECTION_ROLE_SUB_STATE_IDLE = 0,
    LLC_CONNECTION_ROLE_SUB_STATE_RX,
    LLC_CONNECTION_ROLE_SUB_STATE_TX,
    
}
EN_LLC_CONNECTION_ROLE_SUB_STATE_T;


typedef enum
{
    LLC_CONNECTION_ROLE_LATENCY_NOT_USED = 0,
    LLC_CONNECTION_ROLE_LATENCY_USED = 1,
    LLC_CONNECTION_ROLE_LATENCY_WAKING = 2,
}
EN_LLC_CONNECTION_ROLE_LATENCY_STATE_T;


#define LLC_CONNECTION_ROLE_TX_CTRL_PDU_NUM (4)


//msg to avoid duplicated msg send
typedef enum
{
    LLC_CONNECTION_ROLE_MSG_FLAG_CONNECTION_EVENT_CLOSED = (1U<<0),
    LLC_CONNECTION_ROLE_MSG_FLAG_DATA_PROCESS            = (1U<<1),
    
}
EN_LLC_CONNECTION_ROLE_MSG_FLAG_T;


typedef struct stLlcConnectionRoleNode
{
    ////todo : make all struct natural alignmnet after devolop
    
    
////for scheduler    
    stLlcSchedulerEvent_t stSchedulerEvent;
////
    
////for host
    uint16_t u16ConnHandle;//max 0xEFF
////
    
////for llp
    stLlpPduPointer_t stTxPduPtr;
    stLlpPduPointer_t stRxPduPtr;
////
    
////ACL Data
    stLlcAclData_t* pstHostToControllerAclDataHead;
    stLlcAclData_t* pstHostToControllerAclDataTail;
////
    
////TX, pstQueuedTxPduList(origin) -> pstPreparedTxPduList(encrypted) -> 
////pstConnEventTxPduList(waiting send) -> pstTranmittingPdu(sending)
    stLlcDataChannelPdu_t* pstQueuedTxCtrlPduListHead;
    stLlcDataChannelPdu_t* pstQueuedTxCtrlPduListTail;
    stLlcDataChannelPdu_t* pstQueuedTxDataPduListHead;
    stLlcDataChannelPdu_t* pstQueuedTxDataPduListTail;
    
    stLlcDataChannelPdu_t* pstPreparedTxPduListHead;
    stLlcDataChannelPdu_t* pstPreparedTxPduListTail;
    
    stLlcDataChannelPdu_t* pstConnEventTxPduListHead;
    stLlcDataChannelPdu_t* pstConnEventTxPduListTail;
    
    stLlcDataChannelPdu_t* pstTranmittingPdu;
////
    
    
//// RX, pstReceivingPdu -> pstConnEventRxPduAndAckedPduList -> pstRxPduList
    stLlcDataChannelPdu_t* pstReceivingPdu;
    
    stLlcDataChannelPdu_t* pstConnEventRxPduAndAckedPduListHead;
    stLlcDataChannelPdu_t* pstConnEventRxPduAndAckedPduListTail;
    
    stLlcDataChannelPdu_t* pstRxPduListHead;
    stLlcDataChannelPdu_t* pstRxPduListTail;
////
    
    
    //for empty tx
    stLlcDataChannelPdu_t stTxEmptyPdu;
    //for low resource rx
    stLlcDataChannelPdu_t stRxEmptyPdu;
    
    //for ctrl pdu send
    stLlcDataChannelPdu_t stTxCtrlPdu[LLC_CONNECTION_ROLE_TX_CTRL_PDU_NUM];
    uint8_t pu8TxCtrlPduPayload[LLC_CONNECTION_ROLE_TX_CTRL_PDU_NUM][(LLC_SPEC_5_1_CTRL_PDU_PAYLOAD_MAX_SIZE + 4 + 3)/4*4] __attribute__((aligned(4)));//+4 for MIC
    
    //reserved for terminate_ind
    stLlcDataChannelPdu_t stTerminateIndPdu;
    uint8_t pu8TerminateIndPduPayload[(LLC_SPEC_5_1_LL_TERMINATE_IND_PAYLOAD_SIZE  + 4 + 3)/4*4] __attribute__((aligned(4)));//+4 for MIC
    
    uint8_t u8PeerAddrType;
    uint8_t pu8PeerAddr[6];
    uint8_t u8SelfAddrType;
    uint8_t pu8SelfAddr[6];

////conn param
    uint16_t u16PresetConnEventCounter;
    uint64_t u64PresetConnEventAnchorPoint;
    uint64_t u64PresetConnEventStartTime;//expected trx time(with clock accuracy)
    uint64_t u32PresetConnEventStartRxWindowUs;
    uint8_t u8PresetLastUnmappedChannel;
    uint8_t u8PresetChannelIdx;
    
    uint16_t u16ConnEventCounter;
    uint64_t u64ConnEventAnchorPoint;
    uint64_t u64LastSyncTime;
    uint32_t u32RssiRelatedValue;
    
    
    EN_LLC_CONNECTION_ROLE_LATENCY_STATE_T enumLatencyState;
    
    uint16_t u16ConnItv1250us;
    uint16_t u16ConnSlaveLatency;
    uint16_t u16ConsecutiveConnEventsWithRxEmptyPdu;
    bool bRxNonemptyWithinConnEvent;
    uint16_t u16ConnSupervisionTimeout10ms;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint8_t u8Sca;
    
    uint16_t u16ProcedureInstant;
    //connection update procedure
    uint8_t u8WinSizeNew;
    uint16_t u16WinOffsetNew;
    uint16_t u16ConnItv1250usNew;
    uint16_t u16ConnSlaveLatencyNew;
    uint16_t u16ConnSupervisionTimeout10msNew;
////

////Channel classification
    bool bChSel;
    uint8_t pu8ChM[5];
    uint8_t u8Hop;
    uint8_t u8CurChannelIdx;
    uint8_t u8LastUnmappedChannel;
    
    //channel map update procedure
    uint8_t pu8ChMNew[5];
////

    
////Data PDU Length Management
    //BLUETOOTH CORE SPECIFICATION Version 5.1 | Vol 6, Part B, Page2792
    
    //the maximum number of octets in the Payload that the local device will send to the remote device
    uint16_t connMaxTxOctets;
    
    //the maximum number of octets in the Payload that the local device is able to receive from the remote device
    uint16_t connMaxRxOctets;
    
    //the maximum number of octets in the Payload that the remote device will send to the local device
    uint16_t connRemoteMaxTxOctets;
    
    //the maximum number of octets in the Payload that the remote device is able to receive from the local device
    uint16_t connRemoteMaxRxOctets;
    
    //the maximum number of microseconds that the local device will take to transmit a packet to the remote device
    uint16_t connMaxTxTime;
    
    //the maximum number of microseconds that the local device can take to receive a packet from the remote device
    uint16_t connMaxRxTime;
    
    //the maximum number of microseconds that the remote device will take to transmit a packet to the local device
    uint16_t connRemoteMaxTxTime;
    
    //the maximum number of microseconds that the remote device can take to receive a packet from the local device
    uint16_t connRemoteMaxRxTime;
    
////
    
////Acknowledgement and Flow Control
    bool bTransmitSeqNum;//self property
    bool bNextExpectedSeqNum;//self property
    bool bMoreData;//self and remote
////
    
    
    EN_LL_PHY_T enumTxPhy;
    EN_LL_PHY_T enumRxPhy;
    EN_LL_PHY_T enumTxPhyNew;
    EN_LL_PHY_T enumRxPhyNew;
    uint8_t u8PreferredTxPhys;
    uint8_t u8PreferredRxPhys;
    uint16_t u16PhyOptions;//prefer S2 or S8
    
    uint16_t u16ConsecutiveCrcErrCountWithinConnEvent;
    uint16_t u16RxCountWithinConnEvent;
    
    uint64_t u64ConnSupervisionTimeStartUs;
    
    uint8_t u8DisconnectReason;
    
    
    bool bIsSelfMaster;//true:master false:slave
    EN_LLC_CONNECTION_ROLE_STATE_T enumState;
    EN_LLC_CONNECTION_ROLE_SUB_STATE_T enumSubState;
    stLlcCtrlProcedure_t stSelfInitiatedProcedure;
    stLlcCtrlProcedure_t stPeerInitiatedProcedure;
    
    ////for task process to avoid duplicated msg send
    uint32_t u32MsgFlags;

////for ble_mem
    bool bMemUsed;
////

////for encryption procedure
    bool bDisconnectWhenRxDataPdu;
    bool bTxEncrypted;
    bool bRxEncrypted;
    
    uint8_t pu8Rand[8] __attribute__((aligned(4)));
    uint8_t pu8EDIV[2] __attribute__((aligned(4)));
    uint8_t pu8SKD[16] __attribute__((aligned(4)));
    uint8_t pu8IV[8] __attribute__((aligned(4)));
    uint8_t pu8LTK[16] __attribute__((aligned(4)));
    uint8_t pu8SessionKey[16] __attribute__((aligned(4)));//SK = Encrypt(LTK, SKD)
    uint64_t u64TxEncryptPacketCounter39bit; //39 bits
    uint64_t u64RxEncryptPacketCounter39bit; //39 bits
    
    //store rand, ediv and ltk before encryption pause
    uint8_t pu8RandNewAsMaster[8] __attribute__((aligned(4)));
    uint8_t pu8EDIVNewAsMaster[2] __attribute__((aligned(4)));
    uint8_t pu8LTKNewAsMaster[16] __attribute__((aligned(4)));
////

////for rom_llc_data
    bool bTxAclDataFragmentProcessing;
    bool bTxDataPduProcessDisableFlag;
    bool bTxDataPduProcessing;
    bool bTxDataPduProcessDisabled;
////


////for version exchange procedure
    bool bSelfVersionIndSent;
    bool bPeerVersionIndReceived;
    uint8_t u8PeerVersNr;
    uint16_t u16PeerCompId;
    uint16_t u16PeerSubVersNr;
////
    uint8_t Peer_RPA_Resoluted; //only  Peer_RPA_Resoluted,Peer_Identify_Address exists
    uint8_t Peer_Identify_Address_Type;
    uint8_t Peer_Identify_Address[6];
    uint8_t Own_Address_Be_RPA;

////for feature exchange procedure
    bool bPeerFeatureSetCached;
    uint64_t u64PeerFeatureSet;
////
    
    
    uint16_t u16TransmitWindowSizeUs;
    bool bTerminateWhenConnectionEventClosed;
    bool bPeerRequestRetransmitWhileSelfIsSlave;
    uint64_t u64ConnTerminateTimerStartUs;
    
    uint32_t u32Reserved;//reserved for future use
} __attribute__((aligned(8)))
stLlcConnectionRole_t;


typedef struct
{
    //the lesser of  connMaxTxOctets and connRemoteMaxRxOctets 
    uint16_t connEffectiveMaxTxOctets;
    
    //the lesser of  connMaxRxOctets and connRemoteMaxTxOctets
    uint16_t connEffectiveMaxRxOctets;
    
    //the lesser of  connMaxTxTime and connRemoteMaxRxTime 
    uint16_t connEffectiveMaxTxTimeUncoded;
    
    //the value (2*T_IFS) + min( connEffectiveMaxRxTime , (( connEffectiveMaxRxOctets * 64) + 976))
    uint16_t connIntervalRequired;
    
    //connIntervalRequired + 2704
    uint16_t connIntervalCodedMin;
    
    //the current  connInterval for the connection minus  connIntervalRequired 
    uint16_t connIntervalPortionAvailable;
    
    //the lesser of connEffectiveMaxTxTimeUncoded and  connIntervalPortionAvailable 
    uint16_t connEffectiveMaxTxTimeAvailable;
    
    //the greater of 2704 and connEffectiveMaxTxTimeAvailable 
    uint16_t connEffectiveMaxTxTimeCoded;
    
    // equal to  connEffectiveMaxTxTimeUncoded
    //while the connection is on an LE Uncoded PHY and equal to
    //connEffectiveMaxTxTimeCoded while the connection is on the LE Coded PHY
    uint16_t connEffectiveMaxTxTime;
    
    //the lesser of  connMaxRxTime and connRemoteMaxTxTime
    uint16_t connEffectiveMaxRxTimeUncoded;
    
    //the greater of 2704 and connEffectiveMaxRxTimeUncoded
    uint16_t connEffectiveMaxRxTimeCoded;
    
    //equal to  connEffectiveMaxRxTimeUncoded
    //while the connection is on an LE Uncoded PHY and equal to
    //connEffectiveMaxRxTimeCoded while the connection is on the LE Coded PHY
    uint16_t connEffectiveMaxRxTime;
}
stLlcConnectionRoleEffectiveParams_t;

bool rom_llc_connection_role_mem_init(stLlcConnectionRole_t* pstConnectionRoleMemBuffer, uint8_t u8ConnectionRoleNum);
stLlcConnectionRole_t* rom_llc_connection_role_alloc_instance(void);
stLlcConnectionRole_t* rom_llc_connection_role_get_allocated_instance_by_conn_handle(uint16_t u16ConnHandle);
void rom_llc_connection_role_free_instance( stLlcConnectionRole_t* pstRole );


void rom_llc_connection_role_connection_init(stLlcConnectionRole_t* pstRole, EN_LL_PHY_T enumPhy, uint32_t u32RssiRelatedValue);
void rom_llc_connection_role_deinit(stLlcConnectionRole_t* pstRole);

stLlcDataChannelPdu_t* rom_llc_connection_role_alloc_rx_pdu(stLlcConnectionRole_t* pstRole);
void rom_llc_connection_role_free_rx_pdu(stLlcConnectionRole_t* pstRole, stLlcDataChannelPdu_t* pstPdu);

bool rom_llc_connection_role_schedule_start(stLlcConnectionRole_t* pstRole);
void rom_llc_connection_role_schedule_stop(stLlcConnectionRole_t* pstRole);

void rom_llc_connection_role_add_tx_data_pdu(stLlcConnectionRole_t* pstRole ,stLlcDataChannelPdu_t* pstPdu);
void rom_llc_connection_role_add_tx_ctrl_pdu(stLlcConnectionRole_t* pstRole ,stLlcDataChannelPdu_t* pstPdu);
void rom_llc_connection_role_add_host_to_controller_acl_data(stLlcConnectionRole_t* pstRole, stLlcAclData_t* pstAclData);

uint32_t rom_llc_connection_role_get_event_counts_to_timeout(stLlcConnectionRole_t* pstRole);

void rom_llc_connection_role_on_connection_event_closed(stLlcConnectionRole_t* pstRole);
void rom_llc_connection_role_on_scheduler_event_added(void* pstRoleInstance);
void rom_llc_connection_role_on_scheduler_event_removed(void* pstRoleInstance);
void rom_llc_connection_role_get_conn_effective_params(stLlcConnectionRole_t* pstRole, stLlcConnectionRoleEffectiveParams_t* pstParams);

bool rom_llc_connection_role_is_access_address_in_use(uint32_t u32AccessAddress);

void rom_llc_connection_role_preset_connection_event(stLlcConnectionRole_t* pstRole, uint16_t u16IncreasedEventCount);


uint8_t rom_llc_connection_role_read_rssi( uint16_t u16ConnHandle, int8_t* ps8Rssi);

uint8_t rom_llc_connection_role_read_channel_map( uint16_t u16ConnHandle, uint8_t pu8ChannelMap[5]);

uint8_t rom_llc_connection_role_write_suggested_default_data_length(uint16_t u16SuggestedMaxTxOctets, uint16_t u16SuggestedMaxTxTime);

void rom_llc_connection_role_read_suggested_default_data_length(uint16_t* pu16SuggestedMaxTxOctets, uint16_t* pu16SuggestedMaxTxTime);

void rom_llc_connection_terminate_when_connection_event_closed(stLlcConnectionRole_t* pstRole);

void rom_llc_connection_role_update_channel_map_for_all_master(uint8_t pu8ChannelMap[5]);

bool rom_llc_connection_role_is_device_connnected(bool bPublic, uint8_t pu8Address[6]);

#endif
