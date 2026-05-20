/*************************************************************************************************************
 * @file    mmu.c
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
#include <string.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "app_cfg.h"
#include "boards.h"

#include "flash.h"

#include "mmu.h"

#define MMU_DATA_VALID_FLAG                         (0x5A5A)
#define MMU_DATA_INVALID_FLAG                       (0xA5A5)

#define MMU_HEADER_MAX_SIZE                         (2)
#define MMU_CGMS_DATABASE_MAX_SIZE                  (3 * 1024)
#define MMU_CGMS_DB_RECORDS_NUMBER_MAX_SIZE         (2)
#define MMU_CGMS_DB_RECORDS_ORDER_MAX_SIZE          (CGMS_DB_RECORDS_MAX_NUM)
#define MMU_CGMS_SOCP_SESSION_START_TIME_MAX_SIZE   (4)
#define MMU_BLE_ADV_DEV_NAME_MAX_SIZE               (TT_CMD_WRITE_DEV_NAME_PARAM_MAX_LEN)
#define MMU_BLE_ADV_INTERVAL_MAX_SIZE               (TT_CMD_WRITE_ADV_INTERVAL_PARAM_LEN)

typedef struct
{
    EN_MMU_ADDR_T enType;
    uint16_t u16InfoSize;
}stMmuInfo_t;

static const stMmuInfo_t stMmuInfo[EN_MMU_RESERVED] = {
    { EN_MMU_HEADER                 ,MMU_HEADER_MAX_SIZE },
    { EN_MMU_CGMS_DATABASE          ,MMU_CGMS_DATABASE_MAX_SIZE },
    { EN_MMU_CGMS_DB_RECORDS_NUMBER ,MMU_CGMS_DB_RECORDS_NUMBER_MAX_SIZE},
    { EN_MMU_CGMS_DB_RECORDS_ORDER  ,MMU_CGMS_DB_RECORDS_ORDER_MAX_SIZE},
    { EN_MMU_CGMS_SOCP_SST          ,MMU_CGMS_SOCP_SESSION_START_TIME_MAX_SIZE},
    { EN_MMU_BLE_ADV_DEV_NAME       ,MMU_BLE_ADV_DEV_NAME_MAX_SIZE},
    { EN_MMU_BLE_ADV_INTERVAL       ,MMU_BLE_ADV_INTERVAL_MAX_SIZE},
};


static uint32_t mmu_get_addr(EN_MMU_ADDR_T enType)
{
    uint32_t u32Addr = MMU_BASE_ADDR;

    if (EN_MMU_HEADER == enType)
        return u32Addr;

    u32Addr += MMU_HEADER_MAX_SIZE;

    for (int i=1;i<EN_MMU_RESERVED;i++)
    {
        if (enType != stMmuInfo[i].enType)
            u32Addr += (2 + stMmuInfo[i].u16InfoSize);
        else 
            return u32Addr;
    }
    return 0xFFFFFFFF;
}

static bool is_mmu_data_valid(void)
{
    uint16_t u16Flag;
    EN_ERR_STA_T enRet;
    uint32_t u32Addr;

    u32Addr = mmu_get_addr(EN_MMU_HEADER);
    if (0xFFFFFFFF == u32Addr)
    {
        INFO("MMU Type Not Found\n");
        return ERR_STA_ERROR;
    }
    
    enRet = flash_read(u32Addr,(uint8_t *)&u16Flag,stMmuInfo[EN_MMU_HEADER].u16InfoSize);
    if (ERR_STA_OK != enRet)
    {
        INFO("MMU Read Header Failed\n");
        return false;
    }

    if (MMU_DATA_VALID_FLAG == u16Flag)
        return true;

    return false;
}

static EN_ERR_STA_T __mmu_write(EN_MMU_ADDR_T enType,uint16_t u16Offset,uint8_t *pu8Data,uint16_t u16DataLen,bool bIsSyncNow)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint32_t u32StartAddr,u32EndAddr;
    uint16_t u16Tmp = MMU_DATA_VALID_FLAG;

    u32StartAddr = mmu_get_addr(enType);
    if (0xFFFFFFFF == u32StartAddr)
    {
        INFO("MMU Type Not Found\n");
        return ERR_STA_ERROR;
    }
    
    u32EndAddr = u32StartAddr + stMmuInfo[enType].u16InfoSize + 2;
    if (u32EndAddr < u32StartAddr + u16Offset + u16DataLen + 2)
    {
        INFO("MMU Write Data Beyond End Address\n");
        return ERR_STA_ERROR;
    }

    enRet = flash_write(u32StartAddr + u16Offset + 2,pu8Data,u16DataLen,false);
    if (ERR_STA_OK != enRet)
    {
        INFO("MMU Write Data Failed\n");
        return enRet;
    }

    return flash_write(u32StartAddr,(uint8_t *)&u16Tmp,2,bIsSyncNow);
}

EN_ERR_STA_T mmu_clear(EN_MMU_ADDR_T enType)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    bool isDataValid = false;
    uint32_t u32StartAddr;
    uint16_t u16Tmp;

    isDataValid = is_mmu_data_valid();
    if (false == isDataValid)
        return ERR_STA_OK;

    u32StartAddr = mmu_get_addr(enType);
    if (0xFFFFFFFF == u32StartAddr)
    {
        INFO("MMU Type Not Found\n");
        return ERR_STA_ERROR;
    }

    enRet = flash_read(u32StartAddr,(uint8_t *)&u16Tmp,2);
    if (ERR_STA_OK != enRet)
    {
        INFO("MMU Clear Failed\n");
        return enRet;
    }

    if (u16Tmp == MMU_DATA_VALID_FLAG)
    {
        u16Tmp = MMU_DATA_INVALID_FLAG;
        enRet = flash_write(u32StartAddr,(uint8_t *)&u16Tmp,2,true);
        if (ERR_STA_OK != enRet)
        {
            INFO("MMU Clear Failed\n");
            return enRet;
        }
    }

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Clear All Data in MMU.
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T mmu_clear_all(void)
{
    uint16_t u16Flag = MMU_DATA_INVALID_FLAG;
    EN_ERR_STA_T enRet;
    bool isDataValid = false;

    isDataValid = is_mmu_data_valid();
    if (false == isDataValid)
        return ERR_STA_OK;

    enRet = __mmu_write(EN_MMU_HEADER,0,(uint8_t *)&u16Flag,stMmuInfo[EN_MMU_HEADER].u16InfoSize,true);
    if (ERR_STA_OK != enRet)
        INFO("MMU Clear All Failed\n");

    return enRet;
}

/**********************************************************************************************************************
 * @brief  Write Data to Flash.
 * @param  enType: Data Type.
 * @param  u16Offset: Address Offset.
 * @param  pu8Data: Data Buffer.
 * @param  u16DataLen: The Length of Data Buffer.
 * @param  bIsSyncNow: Write into flash right now.
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T mmu_write(EN_MMU_ADDR_T enType,uint16_t u16Offset,uint8_t *pu8Data,uint16_t u16DataLen,bool bIsSyncNow)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    bool isDataValid = false;

    if (NULL == pu8Data || 0 == u16DataLen)
        return ERR_PARA_ERR;

    isDataValid = is_mmu_data_valid();
    if (false == isDataValid)
    {
        uint16_t u16Tmp = MMU_DATA_VALID_FLAG;
        enRet = __mmu_write(EN_MMU_HEADER,0,(uint8_t *)&u16Tmp,stMmuInfo[EN_MMU_HEADER].u16InfoSize,false);
        if (ERR_STA_OK != enRet)
        {
            INFO("MMU Write Header Failed\n");
            return ERR_STA_ERROR;
        }
        bIsSyncNow = true;
    }

    enRet = __mmu_write(enType,u16Offset,pu8Data,u16DataLen,bIsSyncNow);
    if (ERR_STA_OK != enRet)
    {
        INFO("MMU Write Failed\n");
        return ERR_STA_ERROR;
    }

    return enRet;
}

/**********************************************************************************************************************
 * @brief  Read Data from Flash.
 * @param  enType: Data Type.
 * @param  u16Offset: Address Offset.
 * @param  pu8Data: Data Buffer.
 * @param  u16DataLen: The Length of Data Buffer.
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T mmu_read(EN_MMU_ADDR_T enType,uint16_t u16Offset,uint8_t *pu8Data,uint16_t u16DataLen)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    bool isDataValid = false;
    uint32_t u32StartAddr,u32EndAddr;
    uint16_t u16Tmp;

    if (NULL == pu8Data || 0 == u16DataLen)
        return ERR_PARA_ERR;

    isDataValid = is_mmu_data_valid();
    if (false == isDataValid)
    {
        INFO("MMU Data Invalid\r\n");
        return ERR_STA_ERROR;
    }
    
    u32StartAddr = mmu_get_addr(enType);
    if (0xFFFFFFFF == u32StartAddr)
    {
        INFO("MMU Type Not Found\n");
        return ERR_STA_ERROR;
    }
    
    u32EndAddr = u32StartAddr + stMmuInfo[enType].u16InfoSize + 2;
    
    if (u32EndAddr < u32StartAddr + u16Offset + u16DataLen + 2)
    {
        INFO("MMU Read Data Beyond End Address\n");
        return ERR_STA_ERROR;
    }
    
    enRet = flash_read(u32StartAddr,(uint8_t *)&u16Tmp,2);
    if (ERR_STA_OK != enRet)
    {
        INFO("MMU Read Failed\n");
        return enRet;
    }
    
    if (u16Tmp != MMU_DATA_VALID_FLAG)
        return ERR_DATA_NOT_FOUND;
    
    return flash_read(u32StartAddr+u16Offset+2,pu8Data,u16DataLen);
}

