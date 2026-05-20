/*************************************************************************************************************
 * @file    patch_llc_feature_exchange_procedure.h
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
#ifndef __PATCH_LLC_FEATURE_EXCHANGE_PROCEDURE_H__
#define __PATCH_LLC_FEATURE_EXCHANGE_PROCEDURE_H__

extern uint64_t gu64BleImplFeatureSet;

extern bool patch_llc_feature_exchange_procedure_peer_initiated_init(stLlcConnectionRole_t *pstRole, stLlcCtrlProcedure_t* pstProcedure, stLlcDataChannelPdu_t* pstFirstPdu);

#endif