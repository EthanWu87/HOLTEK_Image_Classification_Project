/*************************************************************************************************************
 * @file    llc_ext_initiator_secondary_scanning.h
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
#ifndef LLC_EXT_INITIATOR_SECONDARY_SCANNING_H
#define LLC_EXT_INITIATOR_SECONDARY_SCANNING_H


void rom_llc_ext_initiator_secondary_scanning_on_enable(stLlcExtInitiator_t* pstInitiator);

void rom_llc_ext_initiator_secondary_scanning_on_disable(stLlcExtInitiator_t* pstInitiator);

void rom_llc_ext_initiator_secondary_scanning_prepare_timing(stLlcExtInitiator_t* pstInitiator);

bool rom_llc_ext_initiator_secondary_scanning_get_timing(stLlcExtInitiator_t* pstInitiator, stLlcExtInitiatorTiming_t* pstTiming);

void rom_llc_ext_initiator_secondary_scanning_on_received_extended_pdu_when_primary_scanning(stLlcExtInitiator_t* pstInitiator, stLlcAdvChannelPdu_t* pstPdu);

void rom_llc_ext_initiator_secondary_scanning_on_scheduled(stLlcExtInitiator_t* pstInitiator);

uint32_t rom_llc_ext_initiator_secondary_scanning_on_event_blocked (stLlcExtInitiator_t* pstInitiator);

EN_LLP_ERR_T rom_llc_ext_initiator_secondary_scanning_config_llp(stLlcExtInitiator_t* pstInitiator, uint32_t u32MaxWorkWindowTimeUs);

void rom_llc_ext_initiator_secondary_scanning_on_llp_fragment_start(stLlcExtInitiator_t* pstInitiator);

bool rom_llc_ext_initiator_secondary_scanning_on_llp_fragment_stop(stLlcExtInitiator_t* pstInitiator);

EN_LLP_STATE_CMD_T rom_llc_ext_initiator_secondary_scanning_on_llp_tx_end(stLlcExtInitiator_t* pstInitiator, stLlpTxEndReport_t *pstReport);

EN_LLP_STATE_CMD_T rom_llc_ext_initiator_secondary_scanning_on_llp_rx_end(stLlcExtInitiator_t* pstInitiator, stLlpRxEndReport_t *pstReport);

#endif
