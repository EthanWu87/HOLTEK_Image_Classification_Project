/*************************************************************************************************************
 * @file    cgms_racp_process.h
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
#ifndef CGMS_RACP_PROCESS_H
#define CGMS_RACP_PROCESS_H


EN_ERR_STA_T cgms_racp_record_all_report(stCgmsHandle_t *pstHandle);
EN_ERR_STA_T cgms_racp_record_less_or_equal_report(stCgmsHandle_t *pstHandle,uint16_t u16MaxTimeOffset);
EN_ERR_STA_T cgms_racp_record_greater_or_equal_report(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset);
EN_ERR_STA_T cgms_racp_record_range_of_report(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset);
EN_ERR_STA_T cgms_racp_record_first_report(stCgmsHandle_t *pstHandle);
EN_ERR_STA_T cgms_racp_record_last_report(stCgmsHandle_t *pstHandle);
EN_ERR_STA_T cgms_racp_record_number_of_all_get(stCgmsHandle_t *pstHandle,uint16_t *u16Num);
EN_ERR_STA_T cgms_racp_record_number_of_less_or_equal_get(stCgmsHandle_t *pstHandle,uint16_t u16MaxTimeOffset,uint16_t *u16Num);
EN_ERR_STA_T cgms_racp_record_number_of_greater_or_equal_get(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t *u16Num);
EN_ERR_STA_T cgms_racp_record_number_of_range_get(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset,uint16_t *u16Num);
EN_ERR_STA_T cgms_racp_record_number_of_first_get(stCgmsHandle_t *pstHandle,uint16_t *u16Num);
EN_ERR_STA_T cgms_racp_record_number_of_last_get(stCgmsHandle_t *pstHandle,uint16_t *u16Num);
EN_ERR_STA_T cgms_racp_record_all_delete(stCgmsHandle_t *pstHandle);
EN_ERR_STA_T cgms_racp_record_less_or_equal_delete(stCgmsHandle_t *pstHandle,uint16_t u16MaxTimeOffset);
EN_ERR_STA_T cgms_racp_record_greater_or_equal_delete(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset);
EN_ERR_STA_T cgms_racp_record_range_of_delete(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset);
EN_ERR_STA_T cgms_racp_record_first_delete(stCgmsHandle_t *pstHandle);
EN_ERR_STA_T cgms_racp_record_last_delete(stCgmsHandle_t *pstHandle);

#endif