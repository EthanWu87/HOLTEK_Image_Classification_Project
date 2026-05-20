/*************************************************************************************************************
 * @file    llp_dtm_tx.h
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

#ifndef LLP_DTM_TX_H
#define LLP_DTM_TX_H

extern const stLlpDtmFragment_t g_stLlpDtmTxFragment;

EN_LLP_ERR_T rom_llp_dtm_tx_fragment_start(stLlpDtmTxFragmentParam_t* pstParam);

EN_LLP_DTM_FRAGMENT_RET rom_llp_dtm_tx_on_fragment_start(void);

void rom_llp_dtm_tx_on_fragment_stop(void);

EN_LLP_DTM_FRAGMENT_RET rom_llp_dtm_tx_on_interrupt(uint32_t u32IntState);

#endif
