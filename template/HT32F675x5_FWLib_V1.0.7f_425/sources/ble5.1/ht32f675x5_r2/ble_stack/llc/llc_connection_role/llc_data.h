/*************************************************************************************************************
 * @file    llc_data.h
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
#ifndef LLC_DATA_H
#define LLC_DATA_H


////forward declaration
struct stLlcConnectionRoleNode;
struct stLlcCtrlProcedureNode;
////


typedef enum
{
    LLC_DATA_PDU_PROCESS_RESULT_REMOVE = 0,
    LLC_DATA_PDU_PROCESS_RESULT_KEEP,
    LLC_DATA_PDU_PROCESS_RESULT_DISCONNECTED,
}
EN_LLC_DATA_PDU_PROCESS_RESULT_T;

void rom_llc_data_connection_role_init(struct stLlcConnectionRoleNode* pstRole);
void rom_llc_data_process_main( struct stLlcConnectionRoleNode *pstRole );
void rom_llc_data_process_on_connection_event_closed( struct stLlcConnectionRoleNode *pstRole );
void rom_llc_data_disconnect_when_rx_data_pdu(struct stLlcConnectionRoleNode* pstRole, bool bDisconnectWhenRecvDataPdu);
void rom_llc_data_enable_tx_data_pdu_process_async( struct stLlcConnectionRoleNode *pstRole, bool bEnable);
bool rom_llc_data_is_tx_data_pdu_process_enabled( struct stLlcConnectionRoleNode *pstRole );

bool rom_llc_data_is_queued_tx_acl_data_list_empty( struct stLlcConnectionRoleNode *pstRole );
bool rom_llc_data_is_prepared_tx_pdu_list_empty( struct stLlcConnectionRoleNode *pstRole );
bool rom_llc_data_is_queued_tx_ctrl_pdu_list_empty( struct stLlcConnectionRoleNode *pstRole );
bool rom_llc_data_is_queued_tx_data_pdu_list_empty( struct stLlcConnectionRoleNode *pstRole );
bool rom_llc_data_is_transmiting_pdu_empty( struct stLlcConnectionRoleNode *pstRole );

#endif

