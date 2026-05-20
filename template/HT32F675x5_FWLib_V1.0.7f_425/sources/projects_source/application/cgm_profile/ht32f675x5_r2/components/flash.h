/*************************************************************************************************************
 * @file    flash.h
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
#ifndef FLASH_H
#define FLASH_H

#include <stdbool.h>
#include "err_def.h"

#define FLASH_PAGE_SIZE                     ( 256 )
#define FLASH_SECTOR_SIZE                   ( 4096 )

/* Must be PAGE_SIZE or SECTOR_SIZE */
#define FLASH_CACHE_SIZE                    (FLASH_SECTOR_SIZE)

#define FLASH_WRITE_TIME_US                 (3000)
#define FLASH_ERASE_TIME_US                 (20000)

/***************************************************************************** 
 * @brief  Read the latest data from main flash memory or flash cache
 * @param  u32Addr: Start Address of SIP FLASH MEMORY 
 * @param  pu8Buf: Pointer to a buffer which used to save the readed data 
 * @param  u32Len: Length of read data 
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ****************************************************************************/  
EN_ERR_STA_T flash_read(uint32_t u32Addr,uint8_t *pBuf,uint32_t u32Len);

/**************************************************************************** 
 * @brief  Write the buffer data to sip flash memory or flash cache from indicated start address. 
 * @param  u32Addr: Start Address of SIP FLASH MEMORY. 
 * @param  pu8Buf: Pointer to a buffer which will be written to flash memory.
 * @param  u32Len: Length of write data, maximum length is 64 * 1024 Bytes. 
 * @param  bSyncNow: Whether to synchronize immediately.
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ***************************************************************************/  
EN_ERR_STA_T flash_write(uint32_t u32Addr,uint8_t *pBuf,uint32_t u32Len,bool bSyncNow);

/**************************************************************************** 
 * @brief  Synchronize data from flash cache to main flash memory.  
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ***************************************************************************/  
EN_ERR_STA_T flash_sync(void);

/**************************************************************************** 
 * @brief  Set the mode for operating the flash. 
 * @param  enMode: Access mode as below, @ref EN_FLASH_BUS_MODE_T  
 * @note   enMode default value is BUS_MODE_QPI
 ***************************************************************************/ 
void set_flash_bus_mode(EN_FLASH_BUS_MODE_T enMode);

#endif