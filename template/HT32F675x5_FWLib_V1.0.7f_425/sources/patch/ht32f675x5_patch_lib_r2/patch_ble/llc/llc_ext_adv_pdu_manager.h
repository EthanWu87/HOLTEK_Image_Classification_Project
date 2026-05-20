/*************************************************************************************************************
 * @file    llc_ext_adv_pdu_manager.h
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
#ifndef LLC_EXT_ADV_PDU_MANAGER_H
#define LLC_EXT_ADV_PDU_MANAGER_H

void rom_llc_ext_adv_pdu_manager_accept_updating_pdu(stLlcExtAdv_t* pstAdv);

void rom_llc_ext_adv_pdu_manager_update_accepted_pdus_AdvA(stLlcExtAdv_t* pstAdv);

void rom_llc_ext_adv_pdu_manager_update_accepted_pdus_TargetA(stLlcExtAdv_t* pstAdv);

void rom_llc_ext_adv_pdu_manager_update_accepted_connect_response_pdu_TargetA(stLlcExtAdv_t* pstAdv, bool bRxAdd, uint8_t pu8TargetA[6]);

void rom_llc_ext_adv_pdu_manager_update_accepted_pdus_ADI(stLlcExtAdv_t* pstAdv);

void rom_llc_ext_adv_pdu_manager_update_accepted_primary_pdus_AuxPtr(stLlcExtAdv_t* pstAdv, uint32_t u32AuxPtrOffset30Us);

void rom_llc_ext_adv_pdu_manager_update_accepted_secondary_pdus_AuxPtr(stLlcExtAdv_t* pstAdv);

uint8_t rom_llc_ext_adv_pdu_manager_set_advertising_data(stLlcExtAdv_t* pstAdv, EN_LLC_SPEC_5_1_HCI_ADV_DATA_OPERATION_T enumOperation, bool bFragmentPreferred, uint8_t *pu8Data, uint8_t u8DataLength);

uint8_t rom_llc_ext_adv_pdu_manager_set_scan_response_data(stLlcExtAdv_t* pstAdv, EN_LLC_SPEC_5_1_HCI_SCAN_RESPONSE_DATA_OPERATION_T enumOperation, bool bFragmentPreferred, uint8_t *pu8Data, uint8_t u8DataLength);

void rom_llc_ext_adv_pdu_manager_clear(stLlcExtAdv_t* pstAdv);

#endif
