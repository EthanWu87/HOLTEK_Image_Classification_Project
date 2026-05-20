/*************************************************************************************************************
 * @file    mmu.h
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
#ifndef MMU_H
#define MMU_H

#include "..\..\..\..\..\sources\mem_cfg\ht32f675x5_mem_cfg_r2.h"

#define MMU_BASE_ADDR           (FLASH_MMU_BASE_ADDR_OFFSET)

/* Data Type */
typedef enum
{
    EN_MMU_HEADER                   = 0x00,
    EN_MMU_CGMS_DATABASE            = 0x01,
    EN_MMU_CGMS_DB_RECORDS_NUMBER   = 0x02,
    EN_MMU_CGMS_DB_RECORDS_ORDER    = 0x03,
    EN_MMU_CGMS_SOCP_SST            = 0x04,
    EN_MMU_BLE_ADV_DEV_NAME         = 0x05,
    EN_MMU_BLE_ADV_INTERVAL         = 0x06,
    
    EN_MMU_RESERVED        /* End of Enum Type */
}EN_MMU_ADDR_T;

/**********************************************************************************************************************
 * @brief  Clear Data of Type in MMU.
 * @param  enType: Data Type.
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T mmu_clear(EN_MMU_ADDR_T enType);

/**********************************************************************************************************************
 * @brief  Clear All Data in MMU.
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T mmu_clear_all(void);

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
EN_ERR_STA_T mmu_write(EN_MMU_ADDR_T enType,uint16_t u16Offset,uint8_t *pu8Data,uint16_t u16DataLen,bool bIsSyncNow);

/**********************************************************************************************************************
 * @brief  Read Data from Flash.
 * @param  enType: Data Type.
 * @param  u16Offset: Address Offset.
 * @param  pu8Data: Data Buffer.
 * @param  u16DataLen: The Length of Data Buffer.
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T mmu_read(EN_MMU_ADDR_T enType,uint16_t u16Offset,uint8_t *pu8Data,uint16_t u16DataLen);

#endif
