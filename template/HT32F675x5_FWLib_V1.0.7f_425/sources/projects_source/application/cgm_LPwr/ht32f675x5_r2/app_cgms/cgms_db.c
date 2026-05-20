/*************************************************************************************************************
 * @file    cgms_db.c
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
#include "mmu.h"

#include "cgm_service.h"
#include "cgms_db.h"

typedef struct {
    bool bIsUsed;
    stCgmsMeasRec_t stRec;
}stCgmsDbData_t __attribute__((aligned(4)));

static stCgmsDbData_t gpstRecData[CGMS_DB_RECORDS_MAX_NUM] __attribute__((aligned(4)));
static uint8_t gpu8RecordOrder[CGMS_DB_RECORDS_MAX_NUM];
static uint16_t gu16RecordNum;

/**********************************************************************************************************************
 * @brief  CGMS Database Init.
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T cgms_db_init(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16DatabaseSize = sizeof(gpstRecData);
    // 1. Read From Flash
    do
    {      
        enRet = mmu_read(EN_MMU_CGMS_DATABASE,0,(uint8_t *)gpstRecData,u16DatabaseSize);
        if (ERR_STA_OK != enRet)
        {
            INFO("CGMS Database Not Found in Flash\r\n");
            break;
        }

        enRet = mmu_read(EN_MMU_CGMS_DB_RECORDS_NUMBER,0,(uint8_t *)&gu16RecordNum,sizeof(uint16_t));
        if (ERR_STA_OK != enRet)
        {
            INFO("CGMS Database Not Found in Flash\r\n");
            break;
        }

        enRet = mmu_read(EN_MMU_CGMS_DB_RECORDS_ORDER,0,gpu8RecordOrder,CGMS_DB_RECORDS_MAX_NUM);
        if (ERR_STA_OK != enRet)
        {
            INFO("CGMS Database Not Found in Flash\r\n");
            break;
        }
        
        INFO("CGMS Database Read From Flash Successful\r\n");
        INFO("CGMS Database Number of Records : %u\r\n",gu16RecordNum);
        
        return ERR_STA_OK;
    }while(0);
    
    INFO("CGMS Create a New Database\r\n");

    // 2. Not Existance in Flash
    gu16RecordNum = 0;
    memset(gpstRecData,0,sizeof(gpstRecData));
    memset(gpu8RecordOrder,0xFF,sizeof(gpu8RecordOrder));
    
    do
    {
        enRet = mmu_write(EN_MMU_CGMS_DATABASE,0,(uint8_t *)gpstRecData,u16DatabaseSize,false);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = mmu_write(EN_MMU_CGMS_DB_RECORDS_NUMBER,0,(uint8_t *)&gu16RecordNum,sizeof(uint16_t),false);
        if (ERR_STA_OK != enRet)
            break;
    
        enRet = mmu_write(EN_MMU_CGMS_DB_RECORDS_ORDER,0,gpu8RecordOrder,CGMS_DB_RECORDS_MAX_NUM,true);
        if (ERR_STA_OK != enRet)
            break;

        return ERR_STA_OK;
    }while(0);
    
    INFO("CGMS Database Create Failed\r\n");
    
    return ERR_STA_ERROR;
}

/**********************************************************************************************************************
 * @brief  Get Number of CGMS Record in Database.
 * 
 * @return The Number of CGMS Record.
 *********************************************************************************************************************/
uint16_t cgms_db_get_record_num(void)
{
    return gu16RecordNum;
}

/**********************************************************************************************************************
 * @brief  Get CGMS Record from Database.
 * @param  u16RecNum: Record Number
 * @param  stRecord: CGMS Record.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T cgms_db_record_get(uint16_t u16RecNum,stCgmsMeasRec_t *stRecord)
{
    if (0 == gu16RecordNum || u16RecNum >= gu16RecordNum)
        return ERR_DATA_NOT_FOUND;
    
    if (false == gpstRecData[gpu8RecordOrder[u16RecNum]].bIsUsed)
        return ERR_DATA_NOT_FOUND;
    
    *stRecord = gpstRecData[gpu8RecordOrder[u16RecNum]].stRec;
    
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Get Idle Index.
 * @output
 * @return Idle Index
 *********************************************************************************************************************/
static uint16_t cgms_db_idle_index_get(void)
{
    uint16_t u16Idx;
    for (u16Idx = 0;u16Idx < CGMS_DB_RECORDS_MAX_NUM;u16Idx++)
    {
        if (false == gpstRecData[u16Idx].bIsUsed)
            return u16Idx;
    }
    return 0xFFFF;
}

/**********************************************************************************************************************
 * @brief  Add a New Record into Database.
 * @param  stRecord: CGMS Record
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T cgms_db_record_add(const stCgmsMeasRec_t *stRecord)
{
    uint16_t u16Idx;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    u16Idx = cgms_db_idle_index_get();
    if (0xFFFF == u16Idx)
        return ERR_STA_ERROR;
    
    do
    {
        gpstRecData[u16Idx].bIsUsed = true;
        gpstRecData[u16Idx].stRec = *stRecord;
        enRet = mmu_write(EN_MMU_CGMS_DATABASE,sizeof(stCgmsDbData_t)*u16Idx,(uint8_t *)&gpstRecData[u16Idx],sizeof(stCgmsDbData_t),false);
        if (ERR_STA_OK != enRet)
            break;
        
        gpu8RecordOrder[gu16RecordNum] = u16Idx;
        mmu_write(EN_MMU_CGMS_DB_RECORDS_ORDER,gu16RecordNum*sizeof(uint8_t),(uint8_t *)&gpu8RecordOrder[gu16RecordNum],sizeof(uint8_t),false);
        if (ERR_STA_OK != enRet)
            break;
        
        gu16RecordNum++;
        mmu_write(EN_MMU_CGMS_DB_RECORDS_NUMBER,0,(uint8_t *)&gu16RecordNum,sizeof(uint16_t),true);
        if (ERR_STA_OK != enRet)
            break;
        
        return ERR_STA_OK;
    }while(0);
    
    INFO("CGMS Database Record Add Failed\r\n");
    return ERR_STA_ERROR;
}

/**********************************************************************************************************************
 * @brief  Delete a Record by Number.
 * @param  u16RecNum: CGMS Record Number
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T cgms_db_record_delete(uint16_t u16RecNum)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16DelIdx;
    uint16_t u16RecOrderOffset;
    uint16_t u16ReviseSize;
    
    if (u16RecNum >= gu16RecordNum)
        return ERR_DATA_NOT_FOUND;
    
    u16DelIdx = gpu8RecordOrder[u16RecNum];
    
    do
    {
        gpstRecData[u16DelIdx].bIsUsed = false;
        enRet = mmu_write(EN_MMU_CGMS_DATABASE,sizeof(stCgmsDbData_t)*u16DelIdx,(uint8_t *)&gpstRecData[u16DelIdx],sizeof(stCgmsDbData_t),false);
        if (ERR_STA_OK != enRet)
            break;
        
        gu16RecordNum--;
        
        u16ReviseSize = (gu16RecordNum - u16RecNum) * sizeof(uint8_t);
        if (0 != u16ReviseSize)
        {
            u16RecOrderOffset = u16RecNum * sizeof(uint8_t);
            for (uint16_t u16Idx = u16RecNum;u16Idx < gu16RecordNum;u16Idx++)
                gpu8RecordOrder[u16Idx] = gpu8RecordOrder[u16Idx+1];
            
            enRet = mmu_write(EN_MMU_CGMS_DB_RECORDS_ORDER,u16RecOrderOffset,(uint8_t *)&gpu8RecordOrder[u16RecNum],u16ReviseSize,false);
            if (ERR_STA_OK != enRet)
                break;
        }
        
        enRet = mmu_write(EN_MMU_CGMS_DB_RECORDS_NUMBER,0,(uint8_t *)&gu16RecordNum,sizeof(uint16_t),true);
        if (ERR_STA_OK != enRet)
            break;
        
        return ERR_STA_OK;
    }while(0);
    
    INFO("CGMS Database Delete Failed\r\n");
    
    return ERR_STA_ERROR;
}

/**********************************************************************************************************************
 * @brief  Delete All Records.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T cgms_db_record_delete_all(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16DatabaseSize = sizeof(gpstRecData);
    
    gu16RecordNum = 0;
    memset(gpstRecData,0,sizeof(gpstRecData));
    memset(gpu8RecordOrder,0xFF,sizeof(gpu8RecordOrder));
    
    do
    {
        enRet = mmu_write(EN_MMU_CGMS_DATABASE,0,(uint8_t *)gpstRecData,u16DatabaseSize,false);
        if (ERR_STA_OK != enRet)
            break;
        
        enRet = mmu_write(EN_MMU_CGMS_DB_RECORDS_NUMBER,0,(uint8_t *)&gu16RecordNum,sizeof(uint16_t),false);
        if (ERR_STA_OK != enRet)
            break;
    
        enRet = mmu_write(EN_MMU_CGMS_DB_RECORDS_ORDER,0,gpu8RecordOrder,CGMS_DB_RECORDS_MAX_NUM,true);
        if (ERR_STA_OK != enRet)
            break;
        
        return ERR_STA_OK;
    }while(0);
    
    return ERR_STA_ERROR;
}

