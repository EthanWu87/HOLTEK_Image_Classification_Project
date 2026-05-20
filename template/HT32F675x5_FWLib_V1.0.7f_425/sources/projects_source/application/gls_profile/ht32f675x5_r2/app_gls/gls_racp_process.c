/*************************************************************************************************************
 * @file    gls_racp_process.c
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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "err_def.h"
#include "app_cfg.h"
#include "utility.h"

#include "ble_gls.h"
#include "gls_db.h"
#include "gls_utility.h"

#include "gls_racp_process.h"
#include "gls_utility.h"
static EN_ERR_STA_T gls_racp_record_less_or_equal_get(uint16_t u16MaxSequenceNumber,uint16_t *u16BeginEndNum,stGlsMeasRec_t *stRecord)
{
    uint16_t u16DbNum;
    u16DbNum = gls_db_get_record_num();
    
    for (uint16_t u16Idx = *u16BeginEndNum;u16Idx < u16DbNum;u16Idx++)
    {
        if (ERR_STA_OK == gls_db_record_get(u16Idx,stRecord))
        {
            if (stRecord->u16SequenceNumber <= u16MaxSequenceNumber)
            {
                *u16BeginEndNum = u16Idx;
                return ERR_STA_OK;
            }
        }
    }
    
    stRecord = NULL;
    
    return ERR_DATA_NOT_FOUND;
}

static EN_ERR_STA_T gls_racp_record_greater_or_equal_get(uint16_t u16MinSequenceNumber,uint16_t *u16BeginEndNum,stGlsMeasRec_t *stRecord)
{
    uint16_t u16DbNum;
    u16DbNum = gls_db_get_record_num();
    
    for (uint16_t u16Idx = *u16BeginEndNum;u16Idx < u16DbNum;u16Idx++)
    {
        if (ERR_STA_OK == gls_db_record_get(u16Idx,stRecord))
        {
            if (stRecord->u16SequenceNumber >= u16MinSequenceNumber)
            {
                *u16BeginEndNum = u16Idx;
                return ERR_STA_OK;
            }
        }
    }
    
    stRecord = NULL;
    
    return ERR_DATA_NOT_FOUND;
}

static EN_ERR_STA_T gls_racp_record_range_of_get(uint16_t u16MinSequenceNumber,uint16_t u16MaxSequenceNumber,uint16_t *u16BeginEndNum,stGlsMeasRec_t *stRecord)
{
    uint16_t u16DbNum;
    
    u16DbNum = gls_db_get_record_num();
    
    for (uint16_t u16Idx = *u16BeginEndNum;u16Idx < u16DbNum;u16Idx++)
    {
        if (ERR_STA_OK == gls_db_record_get(u16Idx,stRecord))
        {
            if (stRecord->u16SequenceNumber >= u16MinSequenceNumber && stRecord->u16SequenceNumber <= u16MaxSequenceNumber)
            {
                *u16BeginEndNum = u16Idx;
                return ERR_STA_OK;
            }
        }
    }
    
    stRecord = NULL;
    
    return ERR_DATA_NOT_FOUND;
}

EN_ERR_STA_T gls_racp_record_all_report(stGlsHandle_t *pstHandle)
{
    uint16_t u16DbNum,u16ReportCnt = 0;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_STA_OK;
    
    u16DbNum = gls_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }

    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }   

        enRet = gls_db_record_get(u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;

        enRet = gls_meas_send(pstHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("GLS Send Measurement Failed\r\n");
            return ERR_STA_ERROR;
        }
        
        u16ReportCnt++;
        INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            u16ReportCnt,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16SequenceNumber);
        rom_delay_ms(10);
    }
    
    if (0 == u16ReportCnt)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_less_or_equal_report(stGlsHandle_t *pstHandle,uint16_t u16MaxSequenceNumber)
{
    uint16_t u16DbNum,u16ReportCnt = 0;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = gls_racp_record_less_or_equal_get(u16MaxSequenceNumber,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = gls_meas_send(pstHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("GLS Send Measurement Failed\r\n");
            return ERR_STA_ERROR;
        }
        
        u16ReportCnt++;
        INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            u16ReportCnt,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16SequenceNumber);
        rom_delay_ms(1);
    }
    
    if (0 == u16ReportCnt)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_greater_or_equal_report(stGlsHandle_t *pstHandle,uint16_t u16MinSequenceNumber)
{
    uint16_t u16DbNum,u16ReportCnt = 0;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = gls_racp_record_greater_or_equal_get(u16MinSequenceNumber,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = gls_meas_send(pstHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("GLS Send Measurement Failed\r\n");
            return ERR_STA_ERROR;
        }
        
        u16ReportCnt++;
        INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            u16ReportCnt,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16SequenceNumber);
        rom_delay_ms(1);
    }
    
    if (0 == u16ReportCnt)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_range_of_report(stGlsHandle_t *pstHandle,uint16_t u16MinSequenceNumber,uint16_t u16MaxSequenceNumber)
{
    uint16_t u16DbNum,u16ReportCnt = 0;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = gls_racp_record_range_of_get(u16MinSequenceNumber,u16MaxSequenceNumber,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = gls_meas_send(pstHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("GLS Send Measurement Failed\r\n");
            return ERR_STA_ERROR;
        }
        
        u16ReportCnt++;
        INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            u16ReportCnt,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16SequenceNumber);
        rom_delay_ms(1);
    }
    
    if (0 == u16ReportCnt)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_first_report(stGlsHandle_t *pstHandle)
{
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("GLS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = gls_db_record_get(0,&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("GLS Database Record Not Found\r\n");
        return enRet;
    }
    
    enRet = gls_meas_send(pstHandle,&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("GLS Send Measurement Failed\r\n");
        return ERR_STA_ERROR;
    }
    
    INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            1,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16SequenceNumber);
    
    return enRet;
}

EN_ERR_STA_T gls_racp_record_last_report(stGlsHandle_t *pstHandle)
{
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("GLS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = gls_db_record_get(gls_db_get_record_num()-1,&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("GLS Database Record Not Found\r\n");
        return enRet;
    }
    
    enRet = gls_meas_send(pstHandle,&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("GLS Send Measurement Failed\r\n");
        return ERR_STA_ERROR;
    }
    
    INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            1,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16SequenceNumber);
    
    return enRet;
}

EN_ERR_STA_T gls_racp_record_number_of_all_get(stGlsHandle_t *pstHandle,uint16_t *u16Num)
{
    *u16Num = 0;

    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;

    if (false == pstHandle->isRacpRunning)
    {
        INFO("GLS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    *u16Num = gls_db_get_record_num();

    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_number_of_less_or_equal_get(stGlsHandle_t *pstHandle,uint16_t u16MaxSequenceNumber,uint16_t *u16Num)
{
    uint16_t u16DbNum;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = gls_racp_record_less_or_equal_get(u16MaxSequenceNumber,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        (*u16Num)++;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_number_of_greater_or_equal_get(stGlsHandle_t *pstHandle,uint16_t u16MinSequenceNumber,uint16_t *u16Num)
{
    uint16_t u16DbNum;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = gls_racp_record_greater_or_equal_get(u16MinSequenceNumber,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        (*u16Num)++;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_number_of_range_get(stGlsHandle_t *pstHandle,uint16_t u16MinSequenceNumber,uint16_t u16MaxSequenceNumber,uint16_t *u16Num)
{
    uint16_t u16DbNum;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = gls_racp_record_range_of_get(u16MinSequenceNumber,u16MaxSequenceNumber,&u16Idx,&stRecord);  
        if (ERR_STA_OK != enRet)
            break;
        
        (*u16Num)++;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_number_of_first_get(stGlsHandle_t *pstHandle,uint16_t *u16Num)
{
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("GLS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = gls_db_record_get(0,&stRecord);
    if (ERR_STA_OK != enRet)
        return ERR_STA_OK;

    *u16Num = 1;
    
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_number_of_last_get(stGlsHandle_t *pstHandle,uint16_t *u16Num)
{
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("GLS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = gls_db_record_get(gls_db_get_record_num()-1,&stRecord);
    if (ERR_STA_OK != enRet)
        return ERR_STA_OK;

    *u16Num = 1;
    
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_all_delete(stGlsHandle_t *pstHandle)
{
    uint16_t u16DbNum;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16Idx;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("GLS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = gls_db_record_delete_all();
    
    if (ERR_STA_OK != enRet)
        return enRet;
    
    INFO("GLS Delete All Stored Records Successful : %u\r\n",u16DbNum);
    
    return ERR_STA_OK;
}

EN_ERR_STA_T gls_racp_record_less_or_equal_delete(stGlsHandle_t *pstHandle,uint16_t u16MaxSequenceNumber)
{
    uint16_t u16DbNum;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16DeleteCnt = 0;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = gls_racp_record_less_or_equal_get(u16MaxSequenceNumber,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = gls_db_record_delete(u16Idx);
        if (ERR_STA_OK != enRet)
            break;
        
        u16DeleteCnt++;
    }
    
    if (0 != u16DeleteCnt)
    {
        INFO("GLS Deleted %u Stored Records Successful\r\n",u16DeleteCnt);
        return ERR_STA_OK;
    }
    
    INFO("GLS Database Record Not Found\r\n");
    
    return enRet;
}

EN_ERR_STA_T gls_racp_record_greater_or_equal_delete(stGlsHandle_t *pstHandle,uint16_t u16MinSequenceNumber)
{
    uint16_t u16DbNum;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16DeleteCnt = 0;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = gls_racp_record_greater_or_equal_get(u16MinSequenceNumber,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = gls_db_record_delete(u16Idx);
        if (ERR_STA_OK != enRet)
            break;
        
        u16DeleteCnt++;
    }
    
    if (0 != u16DeleteCnt)
    {
        INFO("GLS Deleted %u Stored Records Successful\r\n",u16DeleteCnt);
        return ERR_STA_OK;
    }
    
    INFO("GLS Database Record Not Found\r\n");
    
    return enRet;
}

EN_ERR_STA_T gls_racp_record_range_of_delete(stGlsHandle_t *pstHandle,uint16_t u16MinSequenceNumber,uint16_t u16MaxSequenceNumber)
{
    uint16_t u16DbNum;
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16DeleteCnt = 0;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = gls_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("GLS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("GLS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = gls_racp_record_range_of_get(u16MinSequenceNumber,u16MaxSequenceNumber,&u16Idx,&stRecord);
        if (enRet != ERR_STA_OK)
            break;
        
        enRet = gls_db_record_delete(u16Idx);
        if (ERR_STA_OK != enRet)
            break;
        
        u16DeleteCnt++;
    }
    
    if (0 != u16DeleteCnt)
    {
        INFO("GLS Deleted %u Stored Records Successful\r\n",u16DeleteCnt);
        return ERR_STA_OK;
    }
    
    INFO("GLS Database Record Not Found\r\n");
    
    return enRet;
}

EN_ERR_STA_T gls_racp_record_first_delete(stGlsHandle_t *pstHandle)
{
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("GLS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = gls_db_record_delete(0);
    if (ERR_STA_OK != enRet)
    {
        INFO("GLS Database Record Not Found\r\n");
        return enRet;
    }
    
    INFO("GLS Deleted First Stored Records Successful\r\n");
    
    return enRet;
}

EN_ERR_STA_T gls_racp_record_last_delete(stGlsHandle_t *pstHandle)
{
    stGlsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("GLS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = gls_db_record_delete(gls_db_get_record_num()-1);
    if (ERR_STA_OK != enRet)
    {
        INFO("GLS Database Record Not Found\r\n");
        return enRet;
    }
    
    INFO("GLS Deleted Last Stored Records Successful\r\n");
    
    return enRet;
}

