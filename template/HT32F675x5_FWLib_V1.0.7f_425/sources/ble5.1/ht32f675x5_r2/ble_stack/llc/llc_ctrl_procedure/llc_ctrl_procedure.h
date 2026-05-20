/*************************************************************************************************************
 * @file    llc_ctrl_procedure.h
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
#ifndef LLC_CTRL_PROCEDURE_H
#define LLC_CTRL_PROCEDURE_H

////forward declaration
struct stLlcConnectionRoleNode;
////

typedef enum
{
    LLC_CTRL_PROCEDURE_STATE_UNKNOWN,
    LLC_CTRL_PROCEDURE_STATE_INITIATED,
    LLC_CTRL_PROCEDURE_STATE_WAITING_COLLISION_REJECT,
    LLC_CTRL_PROCEDURE_STATE_PROCESSING,
}
EN_LLC_CTRL_PROCEDURE_STATE_T;

typedef enum
{
    LLC_CTRL_PROCEDURE_ERR_NONE = 0,
    LLC_CTRL_PROCEDURE_ERR_NOT_PROCEDURE_RELATED_PDU,
    LLC_CTRL_PROCEDURE_ERR_BUSY,
    LLC_CTRL_PROCEDURE_ERR_DISCONNECTED,
}
EN_LLC_CTRL_PROCEDURE_ERR_T;


typedef enum
{
    LLC_CTRL_PROCEDURE_ON_EVENT_CLOSED_RESULT_NORMAL = 0,
    LLC_CTRL_PROCEDURE_ON_EVENT_CLOSED_RESULT_CONN_CHANGED,
}
EN_LLC_CTRL_PROCEDURE_ON_EVENT_CLOSED_RESULT_T;


typedef enum
{
    LLC_CTRL_PROCEDURE_TYPE_CONNECTION_UPDATE = 0,
    LLC_CTRL_PROCEDURE_TYPE_CHANNEL_MAP_UPDATE,
    LLC_CTRL_PROCEDURE_TYPE_ENCRYPTION,
    LLC_CTRL_PROCEDURE_TYPE_FEATURE_EXCHANGE,
    LLC_CTRL_PROCEDURE_TYPE_VERSION_EXCHANGE,
    LLC_CTRL_PROCEDURE_TYPE_TERMINATION,
    LLC_CTRL_PROCEDURE_TYPE_CONNECTION_PARAMETERS_REQUEST,
    LLC_CTRL_PROCEDURE_TYPE_LE_PING,
    LLC_CTRL_PROCEDURE_TYPE_DATA_LENGTH_UPDATE,
    LLC_CTRL_PROCEDURE_TYPE_PHY_UPDATE,
    LLC_CTRL_PROCEDURE_TYPE_MINIMUN_NUMBER_OF_USED_CHANNELS,
    LLC_CTRL_PROCEDURE_TYPE_CONSTANT_TONE_EXTENSION_REQUEST,
    LLC_CTRL_PROCEDURE_TYPE_PERIODIC_ADVERTISING_SYNC_TRANSFER,
    LLC_CTRL_PROCEDURE_TYPE_SLEEP_CLOCK_ACCURACY_UPDATE,
}
EN_LLC_CTRL_PROCEDURE_TYPE_T;


typedef EN_LLC_CTRL_PROCEDURE_ON_EVENT_CLOSED_RESULT_T (*llc_ctrl_procedure_on_conn_event_closed_callback) (struct stLlcConnectionRoleNode* pstRole, struct stLlcCtrlProcedureNode* pstProcedure);
typedef EN_LLC_CTRL_PROCEDURE_ERR_T (*llc_ctrl_procedure_on_recv_ctrl_pdu_callback) (struct stLlcConnectionRoleNode *pstRole,struct stLlcCtrlProcedureNode* pstProcedure, stLlcDataChannelPdu_t* pstCtrlPdu);
typedef void (*llc_ctrl_procedure_on_procedure_rejected_callback) (struct stLlcConnectionRoleNode* pstRole, struct stLlcCtrlProcedureNode* pstProcedure, uint8_t u8ErrorCode);

typedef struct stLlcCtrlProcedureNode
{
    uint64_t u64ProcedureResponseTimeoutTimeStartUs;
    EN_LLC_CTRL_PROCEDURE_TYPE_T enumProcedureType;
    EN_LLC_CTRL_PROCEDURE_STATE_T enumState;
    bool bActive;
    bool bHasInstant;
    bool bHasTimeout;
    bool bSelfInitiated;
    bool bBlockOtherProcedure;
    bool bPending;
    uint8_t u8SubState;
    uint8_t u8ExtraInfo;
    stLlcDataChannelPdu_t* pstBlockedTxPdu;
    stLlcDataChannelPdu_t* pstTxPduSendAfterExistingPdu;
    //nullable
    llc_ctrl_procedure_on_conn_event_closed_callback onConnEventClosedCallback;
    //nullable
    llc_ctrl_procedure_on_procedure_rejected_callback onProcedureRejectedCallback;
    //nonnull
    llc_ctrl_procedure_on_recv_ctrl_pdu_callback onRecvCtrlPduCallback;
    
    uint32_t u32Reserved;//for future use
} __attribute__((aligned(8)))
stLlcCtrlProcedure_t;


////for extern module
void rom_llc_ctrl_procedure_init(struct stLlcConnectionRoleNode *pstRole);
EN_LLC_DATA_PDU_PROCESS_RESULT_T rom_llc_ctrl_procedure_on_recv_ctrl_pdu(struct stLlcConnectionRoleNode* pstRole, stLlcDataChannelPdu_t* pstCtrlPdu);
EN_LLC_CTRL_PROCEDURE_ON_EVENT_CLOSED_RESULT_T rom_llc_ctrl_procedure_on_conn_event_closed(struct stLlcConnectionRoleNode* pstRole);


bool rom_llc_ctrl_procedure_is_instant_take_effect_at_next_conn_event(struct stLlcConnectionRoleNode *pstRole);


bool rom_llc_ctrl_procedure_is_procedures_running(struct stLlcConnectionRoleNode *pstRole);
////


////for procedures
stLlcDataChannelPdu_t* rom_llc_ctrl_procedure_alloc_tx_ctrl_pdu(struct stLlcConnectionRoleNode* pstRole);
void rom_llc_ctrl_procedure_free_tx_ctrl_pdu(struct stLlcConnectionRoleNode* pstRole, stLlcDataChannelPdu_t* pstPdu);
void rom_llc_ctrl_procedure_send_ctrl_pdu(struct stLlcConnectionRoleNode* pstRole, stLlcCtrlProcedure_t* pstRelateProcedure, stLlcDataChannelPdu_t* pstPdu);
void rom_llc_ctrl_procedure_send_ctrl_pdu_after_existing_pdu_send_over(struct stLlcConnectionRoleNode *pstRole, stLlcCtrlProcedure_t* pstRelateProcedure, stLlcDataChannelPdu_t* pstPdu);
void rom_llc_ctrl_procedure_enable_tx_data_pdu_process(struct stLlcConnectionRoleNode *pstRole, bool bEnable);
void rom_llc_ctrl_procedure_rsp_unknown_with_acked_callback(struct stLlcConnectionRoleNode *pstRole, stLlcCtrlProcedure_t* pstRelateProcedure, uint8_t u8UnknownType, 
    llc_data_channel_pdu_acked_callback ackedCallback, uint32_t u32AckedParameter);
void rom_llc_ctrl_procedure_rsp_unknown(struct stLlcConnectionRoleNode* pstRole, stLlcCtrlProcedure_t* pstRelateProcedure, uint8_t u8UnknownType);
void rom_llc_ctrl_procedure_rsp_reject_with_acked_callback(struct stLlcConnectionRoleNode *pstRole, stLlcCtrlProcedure_t* pstRelateProcedure, uint8_t u8RejectOpcode, uint8_t u8ErrCode,
    llc_data_channel_pdu_acked_callback ackedCallback, uint32_t u32AckedParameter);
void rom_llc_ctrl_procedure_rsp_reject(struct stLlcConnectionRoleNode* pstRole, stLlcCtrlProcedure_t* pstRelateProcedure, uint8_t u8RejectOpcode, uint8_t u8ErrCode);
uint16_t rom_llc_ctrl_procedure_get_self_initial_procedure_target_instant(struct stLlcConnectionRoleNode *pstRole);
////


////procedures interface
uint8_t rom_llc_ctrl_procedure_disconnect(uint16_t u16ConnHandle, uint8_t u8Reason);

uint8_t rom_llc_ctrl_procedure_start_encryption(uint16_t u16ConnHandle, uint8_t pu8RandomNumber[8], uint16_t u16EncryptedDiversifier, uint8_t pu8LongTermKey[16]);

uint8_t rom_llc_ctrl_procedure_long_term_key_reply(uint16_t u16ConnHandle, uint8_t pu8LongTermKey[16]);

uint8_t rom_llc_ctrl_procedure_long_term_key_negative_reply(uint16_t u16ConnHandle);

uint8_t rom_llc_ctrl_procedure_connection_update(uint16_t u16ConnHandle, uint16_t u16ConnIntervalMin1250us, uint16_t u16ConnIntervalMax1250us, 
    uint16_t u16ConnLatency, uint16_t u16SupervisionTimeout10ms);

uint8_t rom_llc_ctrl_procedure_channel_map_update(uint16_t u16ConnHandle, uint8_t pu8ChannelMap[5]);

uint8_t rom_llc_ctrl_procedure_data_length_update(uint16_t u16ConnHandle, uint16_t u16TxOctets, uint16_t u16TxTime);

uint8_t rom_llc_ctrl_procedure_set_default_phy(uint8_t u8AllPhys, uint8_t u8TxPhys, uint8_t u8RxPhys);

uint8_t rom_llc_ctrl_procedure_phy_update(uint16_t u16ConnHandle, uint8_t u8AllPhys, uint8_t u8TxPhys, uint8_t u8RxPhys, uint16_t u16PhyOptions, bool bIsInitialtedByHost);

//status report inner API
void rom_llc_ctrl_procedure_read_remote_version_information(uint16_t u16ConnHandle);

//status report inner API
void rom_llc_ctrl_procedure_read_remote_features(uint16_t u16ConnHandle);

////

#endif
