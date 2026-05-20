/*************************************************************************************************************
 * @file    llc_ext_initiator_state_machine.h
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
#ifndef LLC_EXT_INITIATOR_STATE_MACHINE_H
#define LLC_EXT_INITIATOR_STATE_MACHINE_H

void rom_llc_ext_initiator_state_machine_init(stLlcExtInitiator_t* pstInitiator);

void rom_llc_ext_initiator_state_machine_clear_connection_parameters(stLlcExtInitiator_t* pstInitiator);

bool rom_llc_ext_initiator_state_machine_add_connection_parameters(stLlcExtInitiator_t* pstInitiator,
    EN_LLC_SPEC_5_1_HCI_PHY_T PHY,
    uint16_t Conn_Interval_Min,
    uint16_t Conn_Interval_Max,
    uint16_t Conn_Latency,
    uint16_t Supervision_Timeout);

void rom_llc_ext_initiator_state_machine_set_connection_req_pdu_by_phy(stLlcExtInitiator_t* pstInitiator, EN_LLC_SPEC_5_1_HCI_PHY_T PHY);

void rom_llc_ext_initiator_state_machine_update_connection_req_pdu_AdvA(stLlcExtInitiator_t* pstInitiator, uint8_t AdvA[6], bool RxAdd, bool bChSel);

void rom_llc_ext_initiator_state_machine_update_connection_req_pdu_InitA(stLlcExtInitiator_t* pstInitiator, uint8_t InitA[6], bool TxAdd);

uint8_t rom_llc_ext_initiator_state_machine_enable(stLlcExtInitiator_t* pstInitiator, bool bEnable);

void rom_llc_ext_initiator_state_machine_schedule_next_scanning(stLlcExtInitiator_t* pstInitiator);

#endif
