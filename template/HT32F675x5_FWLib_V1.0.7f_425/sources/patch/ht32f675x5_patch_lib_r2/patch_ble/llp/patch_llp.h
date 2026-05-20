/*************************************************************************************************************
 * @file    patch_llp.h
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
#ifndef PATCH_LLP_H
#define PATCH_LLP_H

void patch_llp(void);

EN_LLP_ERR_T patch_llp_start_adv_fragment(stLlpAdvFragmentParam_t *pstParam);

EN_LLP_ERR_T patch_llp_start_scan_fragment(stLlpScanFragmentParam_t *pstParam);

EN_LLP_ERR_T patch_llp_start_init_fragment(stLlpInitFragmentParam_t *pstParam);

EN_LLP_ERR_T patch_llp_start_slave_fragment(stLlpSlaveFragmentParam_t *pstParam);

EN_LLP_ERR_T patch_llp_start_master_fragment(stLlpMasterFragmentParam_t *pstParam);

EN_LLP_ERR_T patch_llp_start_ext_adv_fragment(stLlpExtAdvFragmentParam_t *pstParam);

EN_LLP_ERR_T patch_llp_start_ext_scan_fragment(stLlpExtScanFragmentParam_t *pstParam);

EN_LLP_ERR_T patch_llp_start_ext_init_fragment(stLlpExtInitFragmentParam_t *pstParam);

#endif
