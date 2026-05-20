/*************************************************************************************************************
 * @file    llc_phy_update_procedure.h
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
#ifndef LLC_PHY_UPDATE_PROCEDURE_H
#define LLC_PHY_UPDATE_PROCEDURE_H

void rom_llc_phy_update_procedure_init(stLlcConnectionRole_t *pstRole);

bool rom_llc_phy_update_procedure_peer_initiated_init(stLlcConnectionRole_t *pstRole, stLlcCtrlProcedure_t* pstProcedure, stLlcDataChannelPdu_t* pstFirstPdu);

uint8_t rom_llc_phy_update_procedure_self_initiated_init(stLlcConnectionRole_t *pstRole, stLlcCtrlProcedure_t* pstProcedure, bool bPending,
    uint8_t u8AllPhys, uint8_t u8TxPhys, uint8_t u8RxPhys, uint16_t u16PhyOptions, bool bIsInitialtedByHost);

EN_LLC_CTRL_PROCEDURE_ERR_T rom_llc_phy_update_procedure_on_recv_ctrl_pdu(stLlcConnectionRole_t *pstRole, stLlcCtrlProcedure_t* pstProcedure, stLlcDataChannelPdu_t* pstCtrlPdu);


EN_LLC_CTRL_PROCEDURE_ON_EVENT_CLOSED_RESULT_T rom_llc_phy_update_procedure_on_conn_event_closed(stLlcConnectionRole_t *pstRole, stLlcCtrlProcedure_t* pstProcedure);

void rom_llc_phy_update_procedure_on_procedure_rejected(stLlcConnectionRole_t *pstRole, stLlcCtrlProcedure_t* pstProcedure, uint8_t u8ErrorCode);

uint8_t rom_llc_phy_update_procedure_set_default_phy(uint8_t u8AllPhys, uint8_t u8TxPhys, uint8_t u8RxPhys);

#endif
