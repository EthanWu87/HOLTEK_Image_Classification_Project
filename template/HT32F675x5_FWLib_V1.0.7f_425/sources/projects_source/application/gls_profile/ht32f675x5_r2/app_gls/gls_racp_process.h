/*************************************************************************************************************
 * @file    gls_racp_process.h
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
#ifndef GLS_RACP_PROCESS_H
#define GLS_RACP_PROCESS_H


EN_ERR_STA_T gls_racp_record_all_report(stGlsHandle_t *pstHandle);
EN_ERR_STA_T gls_racp_record_less_or_equal_report(stGlsHandle_t *pstHandle,uint16_t u16MaxTimeOffset);
EN_ERR_STA_T gls_racp_record_greater_or_equal_report(stGlsHandle_t *pstHandle,uint16_t u16MinTimeOffset);
EN_ERR_STA_T gls_racp_record_range_of_report(stGlsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset);
EN_ERR_STA_T gls_racp_record_first_report(stGlsHandle_t *pstHandle);
EN_ERR_STA_T gls_racp_record_last_report(stGlsHandle_t *pstHandle);
EN_ERR_STA_T gls_racp_record_number_of_all_get(stGlsHandle_t *pstHandle,uint16_t *u16Num);
EN_ERR_STA_T gls_racp_record_number_of_less_or_equal_get(stGlsHandle_t *pstHandle,uint16_t u16MaxTimeOffset,uint16_t *u16Num);
EN_ERR_STA_T gls_racp_record_number_of_greater_or_equal_get(stGlsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t *u16Num);
EN_ERR_STA_T gls_racp_record_number_of_range_get(stGlsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset,uint16_t *u16Num);
EN_ERR_STA_T gls_racp_record_number_of_first_get(stGlsHandle_t *pstHandle,uint16_t *u16Num);
EN_ERR_STA_T gls_racp_record_number_of_last_get(stGlsHandle_t *pstHandle,uint16_t *u16Num);
EN_ERR_STA_T gls_racp_record_all_delete(stGlsHandle_t *pstHandle);
EN_ERR_STA_T gls_racp_record_less_or_equal_delete(stGlsHandle_t *pstHandle,uint16_t u16MaxTimeOffset);
EN_ERR_STA_T gls_racp_record_greater_or_equal_delete(stGlsHandle_t *pstHandle,uint16_t u16MinTimeOffset);
EN_ERR_STA_T gls_racp_record_range_of_delete(stGlsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset);
EN_ERR_STA_T gls_racp_record_first_delete(stGlsHandle_t *pstHandle);
EN_ERR_STA_T gls_racp_record_last_delete(stGlsHandle_t *pstHandle);

#endif