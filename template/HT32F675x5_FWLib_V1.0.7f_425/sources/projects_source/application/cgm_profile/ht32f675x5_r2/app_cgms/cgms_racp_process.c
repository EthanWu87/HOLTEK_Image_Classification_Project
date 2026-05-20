/*************************************************************************************************************
 * @file    cgms_racp_process.c
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

#include "cgm_service.h"
#include "cgms_db.h"
#include "cgms_utility.h"

#include "cgms_racp_process.h"

static EN_ERR_STA_T cgms_racp_record_less_or_equal_get(uint16_t u16MaxTimeOffset,uint16_t *u16BeginEndNum,stCgmsMeasRec_t *stRecord)
{
    uint16_t u16DbNum;
    u16DbNum = cgms_db_get_record_num();
    
    for (uint16_t u16Idx = *u16BeginEndNum;u16Idx < u16DbNum;u16Idx++)
    {
        if (ERR_STA_OK == cgms_db_record_get(u16Idx,stRecord))
        {
            if (stRecord->u16TimeOffset <= u16MaxTimeOffset)
            {
                *u16BeginEndNum = u16Idx;
                return ERR_STA_OK;
            }
        }
    }
    
    stRecord = NULL;
    
    return ERR_DATA_NOT_FOUND;
}

static EN_ERR_STA_T cgms_racp_record_greater_or_equal_get(uint16_t u16MinTimeOffset,uint16_t *u16BeginEndNum,stCgmsMeasRec_t *stRecord)
{
    uint16_t u16DbNum;
    u16DbNum = cgms_db_get_record_num();
    
    for (uint16_t u16Idx = *u16BeginEndNum;u16Idx < u16DbNum;u16Idx++)
    {
        if (ERR_STA_OK == cgms_db_record_get(u16Idx,stRecord))
        {
            if (stRecord->u16TimeOffset >= u16MinTimeOffset)
            {
                *u16BeginEndNum = u16Idx;
                return ERR_STA_OK;
            }
        }
    }
    
    stRecord = NULL;
    
    return ERR_DATA_NOT_FOUND;
}

static EN_ERR_STA_T cgms_racp_record_range_of_get(uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset,uint16_t *u16BeginEndNum,stCgmsMeasRec_t *stRecord)
{
    uint16_t u16DbNum;
    
    u16DbNum = cgms_db_get_record_num();
    
    for (uint16_t u16Idx = *u16BeginEndNum;u16Idx < u16DbNum;u16Idx++)
    {
        if (ERR_STA_OK == cgms_db_record_get(u16Idx,stRecord))
        {
            if (stRecord->u16TimeOffset >= u16MinTimeOffset && stRecord->u16TimeOffset <= u16MaxTimeOffset)
            {
                *u16BeginEndNum = u16Idx;
                return ERR_STA_OK;
            }
        }
    }
    
    stRecord = NULL;
    
    return ERR_DATA_NOT_FOUND;
}

EN_ERR_STA_T cgms_racp_record_all_report(stCgmsHandle_t *pstHandle)
{
    uint16_t u16DbNum,u16ReportCnt = 0;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_STA_OK;
    
    u16DbNum = cgms_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }   
        
        enRet = cgms_db_record_get(u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = cgms_meas_send(pstHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("CGMS Send Measurement Failed\r\n");
            return ERR_STA_ERROR;
        }
        
        u16ReportCnt++;
        INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            u16ReportCnt,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16TimeOffset);
        rom_delay_ms(1);
    }
    
    if (0 == u16ReportCnt)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_less_or_equal_report(stCgmsHandle_t *pstHandle,uint16_t u16MaxTimeOffset)
{
    uint16_t u16DbNum,u16ReportCnt = 0;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = cgms_racp_record_less_or_equal_get(u16MaxTimeOffset,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = cgms_meas_send(pstHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("CGMS Send Measurement Failed\r\n");
            return ERR_STA_ERROR;
        }
        
        u16ReportCnt++;
        INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            u16ReportCnt,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16TimeOffset);
        rom_delay_ms(1);
    }
    
    if (0 == u16ReportCnt)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_greater_or_equal_report(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset)
{
    uint16_t u16DbNum,u16ReportCnt = 0;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = cgms_racp_record_greater_or_equal_get(u16MinTimeOffset,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = cgms_meas_send(pstHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("CGMS Send Measurement Failed\r\n");
            return ERR_STA_ERROR;
        }
        
        u16ReportCnt++;
        INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            u16ReportCnt,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16TimeOffset);
        rom_delay_ms(1);
    }
    
    if (0 == u16ReportCnt)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_range_of_report(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset)
{
    uint16_t u16DbNum,u16ReportCnt = 0;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = cgms_racp_record_range_of_get(u16MinTimeOffset,u16MaxTimeOffset,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = cgms_meas_send(pstHandle,&stRecord);
        if (ERR_STA_OK != enRet)
        {
            INFO("CGMS Send Measurement Failed\r\n");
            return ERR_STA_ERROR;
        }
        
        u16ReportCnt++;
        INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            u16ReportCnt,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16TimeOffset);
        rom_delay_ms(1);
    }
    
    if (0 == u16ReportCnt)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_first_report(stCgmsHandle_t *pstHandle)
{
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("CGMS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = cgms_db_record_get(0,&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return enRet;
    }
    
    enRet = cgms_meas_send(pstHandle,&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("CGMS Send Measurement Failed\r\n");
        return ERR_STA_ERROR;
    }
    
    INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            1,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16TimeOffset);
    
    return enRet;
}

EN_ERR_STA_T cgms_racp_record_last_report(stCgmsHandle_t *pstHandle)
{
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("CGMS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = cgms_db_record_get(cgms_db_get_record_num()-1,&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return enRet;
    }
    
    enRet = cgms_meas_send(pstHandle,&stRecord);
    if (ERR_STA_OK != enRet)
    {
        INFO("CGMS Send Measurement Failed\r\n");
        return ERR_STA_ERROR;
    }
    
    INFO("[%u] Glucose Concentration : %f mg/dL\t Time Offset : %u mins\r\n",
            1,sfloat_to_float(u16_to_sfloat(stRecord.u16GlucoseConcentration)),stRecord.u16TimeOffset);
    
    return enRet;
}

EN_ERR_STA_T cgms_racp_record_number_of_all_get(stCgmsHandle_t *pstHandle,uint16_t *u16Num)
{
    *u16Num = 0;

    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;

    if (false == pstHandle->isRacpRunning)
    {
        INFO("CGMS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    *u16Num = cgms_db_get_record_num();

    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_number_of_less_or_equal_get(stCgmsHandle_t *pstHandle,uint16_t u16MaxTimeOffset,uint16_t *u16Num)
{
    uint16_t u16DbNum;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = cgms_racp_record_less_or_equal_get(u16MaxTimeOffset,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        (*u16Num)++;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_number_of_greater_or_equal_get(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t *u16Num)
{
    uint16_t u16DbNum;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = cgms_racp_record_greater_or_equal_get(u16MinTimeOffset,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        (*u16Num)++;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_number_of_range_get(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset,uint16_t *u16Num)
{
    uint16_t u16DbNum;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;u16Idx++)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = cgms_racp_record_range_of_get(u16MinTimeOffset,u16MaxTimeOffset,&u16Idx,&stRecord);  
        if (ERR_STA_OK != enRet)
            break;
        
        (*u16Num)++;
    }
    
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_number_of_first_get(stCgmsHandle_t *pstHandle,uint16_t *u16Num)
{
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("CGMS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = cgms_db_record_get(0,&stRecord);
    if (ERR_STA_OK != enRet)
        return ERR_STA_OK;

    *u16Num = 1;
    
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_number_of_last_get(stCgmsHandle_t *pstHandle,uint16_t *u16Num)
{
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    *u16Num = 0;
    
    if (NULL == u16Num || NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("CGMS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = cgms_db_record_get(cgms_db_get_record_num()-1,&stRecord);
    if (ERR_STA_OK != enRet)
        return ERR_STA_OK;

    *u16Num = 1;
    
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_all_delete(stCgmsHandle_t *pstHandle)
{
    uint16_t u16DbNum;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16Idx;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("CGMS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = cgms_db_record_delete_all();
    
    if (ERR_STA_OK != enRet)
        return enRet;
    
    INFO("CGMS Delete All Stored Records Successful : %u\r\n",u16DbNum);
    
    return ERR_STA_OK;
}

EN_ERR_STA_T cgms_racp_record_less_or_equal_delete(stCgmsHandle_t *pstHandle,uint16_t u16MaxTimeOffset)
{
    uint16_t u16DbNum;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16DeleteCnt = 0;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = cgms_racp_record_less_or_equal_get(u16MaxTimeOffset,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = cgms_db_record_delete(u16Idx);
        if (ERR_STA_OK != enRet)
            break;
        
        u16DeleteCnt++;
    }
    
    if (0 != u16DeleteCnt)
    {
        INFO("CGMS Deleted %u Stored Records Successful\r\n",u16DeleteCnt);
        return ERR_STA_OK;
    }
    
    INFO("CGMS Database Record Not Found\r\n");
    
    return enRet;
}

EN_ERR_STA_T cgms_racp_record_greater_or_equal_delete(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset)
{
    uint16_t u16DbNum;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16DeleteCnt = 0;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = cgms_racp_record_greater_or_equal_get(u16MinTimeOffset,&u16Idx,&stRecord);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = cgms_db_record_delete(u16Idx);
        if (ERR_STA_OK != enRet)
            break;
        
        u16DeleteCnt++;
    }
    
    if (0 != u16DeleteCnt)
    {
        INFO("CGMS Deleted %u Stored Records Successful\r\n",u16DeleteCnt);
        return ERR_STA_OK;
    }
    
    INFO("CGMS Database Record Not Found\r\n");
    
    return enRet;
}

EN_ERR_STA_T cgms_racp_record_range_of_delete(stCgmsHandle_t *pstHandle,uint16_t u16MinTimeOffset,uint16_t u16MaxTimeOffset)
{
    uint16_t u16DbNum;
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16DeleteCnt = 0;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    u16DbNum = cgms_db_get_record_num();
    if (0 == u16DbNum)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return ERR_DATA_NOT_FOUND;
    }
    
    for (uint16_t u16Idx = 0;u16Idx < u16DbNum;)
    {
        if (false == pstHandle->isRacpRunning)
        {
            INFO("CGMS RACP Process Aborted\r\n");
            return ERR_STA_BREAK;
        }
        
        enRet = cgms_racp_record_range_of_get(u16MinTimeOffset,u16MaxTimeOffset,&u16Idx,&stRecord);
        if (enRet != ERR_STA_OK)
            break;
        
        enRet = cgms_db_record_delete(u16Idx);
        if (ERR_STA_OK != enRet)
            break;
        
        u16DeleteCnt++;
    }
    
    if (0 != u16DeleteCnt)
    {
        INFO("CGMS Deleted %u Stored Records Successful\r\n",u16DeleteCnt);
        return ERR_STA_OK;
    }
    
    INFO("CGMS Database Record Not Found\r\n");
    
    return enRet;
}

EN_ERR_STA_T cgms_racp_record_first_delete(stCgmsHandle_t *pstHandle)
{
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("CGMS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = cgms_db_record_delete(0);
    if (ERR_STA_OK != enRet)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return enRet;
    }
    
    INFO("CGMS Deleted First Stored Records Successful\r\n");
    
    return enRet;
}

EN_ERR_STA_T cgms_racp_record_last_delete(stCgmsHandle_t *pstHandle)
{
    stCgmsMeasRec_t stRecord;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == pstHandle)
        return ERR_PARA_ERR;
    
    if (false == pstHandle->isRacpRunning)
    {
        INFO("CGMS RACP Process Aborted\r\n");
        return ERR_STA_BREAK;
    }
    
    enRet = cgms_db_record_delete(cgms_db_get_record_num()-1);
    if (ERR_STA_OK != enRet)
    {
        INFO("CGMS Database Record Not Found\r\n");
        return enRet;
    }
    
    INFO("CGMS Deleted Last Stored Records Successful\r\n");
    
    return enRet;
}

