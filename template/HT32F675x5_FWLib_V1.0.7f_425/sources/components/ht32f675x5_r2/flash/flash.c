/*************************************************************************************************************
 * @file    flash.c
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

#include "hw_flash.h"
#include "flash.h"

#if (FLASH_CACHE_SIZE == FLASH_PAGE_SIZE)
    #define FLASH_ERASE_TYPE                (ERASE_PAGE)
    #elif (FLASH_CACHE_SIZE == FLASH_SECTOR_SIZE)
    #define FLASH_ERASE_TYPE                   (ERASE_SECTOR)
#else
    #error "The value of FLASH_CACHE_SIZE must be FLASH_PAGE_SIZE or FLASH_SECTOR_SIZE!"
#endif


static bool gbIsNeedSync = false;
static bool gbIsCacheDataValid = false;
static uint16_t gu16CurrentRegionNum;
static EN_FLASH_BUS_MODE_T genMode = BUS_MODE_QPI;
static uint8_t gu8FlashCache[FLASH_CACHE_SIZE] __attribute__ ((section(".flash.cache"))) __attribute__ ((aligned(4)));

/***************************************************************************** 
 * @brief  get address belongs to which region 
 * @param  u32Addr: User data base address
 * @output 
 * @return Region num
 ****************************************************************************/  
static uint16_t get_region_num(uint32_t u32Addr)
{
    return u32Addr/FLASH_CACHE_SIZE;
}

/***************************************************************************** 
 * @brief  Write data into flash cache
 * @param  u16BeginIdx: Index value of the written address
 * @param  pu8Buf: Pointer to a buffer which will be written to flash cache
 * @param  u32Len: Length of write data 
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ****************************************************************************/  
static EN_ERR_STA_T flash_cache_write(uint16_t u16BeginIdx,const uint8_t *pu8Buf,uint16_t u16Len)
{
    /* parameters check */
    if (NULL == pu8Buf || 0 == u16Len)
        return ERR_STA_ERROR;
    if (FLASH_CACHE_SIZE < (u16BeginIdx + u16Len))
        return ERR_STA_ERROR;
    
    /* write into cache */
    memcpy(&gu8FlashCache[u16BeginIdx],pu8Buf,u16Len);
    
    /* set flag */
    gbIsNeedSync = true;
    
    return ERR_STA_OK;
}


/***************************************************************************** 
 * @brief  Read data from main flash memory
 * @param  u32Addr: Start Address of SIP FLASH MEMORY 
 * @param  pu8Buf: Pointer to a buffer which used to save the readed data 
 * @param  u32Len: Length of read data 
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ****************************************************************************/ 
static EN_ERR_STA_T _flash_read(uint32_t u32Addr,uint8_t *pu8Buf,uint32_t u32Len)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    enRet = rom_hw_flash_read_bytes ( FLASH, u32Addr, pu8Buf, u32Len, genMode );    

    return enRet;
}

/**************************************************************************** 
 * @brief  Write the buffer data to sip flash memory. 
 * @param  u32Addr: Start Address of SIP FLASH MEMORY 
 * @param  pu8Buf: Pointer to a buffer which will be written to flash memory 
 * @param  u32Len: Length of write data, maximum length is 64 * 1024 Bytes; 
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ***************************************************************************/ 
static EN_ERR_STA_T _flash_write(uint32_t u32Addr,uint8_t *pu8Buf,uint32_t u32Len)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    enRet = rom_hw_flash_write_bytes ( FLASH, u32Addr, pu8Buf, u32Len, genMode ,FLASH_WRITE_TIME_US);    

    return enRet;
}

/*************************************************************************** 
 * @brief  Erase sip flash memory with indicated @ref EN_SFLASH_ERASE_SIZE_T number. 
 * @param  enSize: The range of Erase, @ref EN_SFLASH_ERASE_SIZE_T. 
 * @param  u16Num: Number of Erase. 
 * @output 
 * @return HW status: @ref EN_ERR_STA_T 
 **************************************************************************/  
static EN_ERR_STA_T _flash_erase(EN_SFLASH_ERASE_SIZE_T enSize,uint16_t u16Num)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    enRet = rom_hw_flash_erase ( FLASH, enSize, u16Num ,FLASH_ERASE_TIME_US);  

    return enRet;
}

/**************************************************************************** 
 * @brief  Write the buffer data to sip flash memory from indicated start address. 
 * @param  u32Addr: Start Address of SIP FLASH MEMORY
 * @note   u32Addr must be a multiple of FLASH_PAGE_SIZE or FLASH_SECTOR_SIZE
 * @param  pu8Buf: Pointer to a buffer which will be written to flash memory 
 * @param  u32Len: Length of write data, maximum length is 64 * 1024 Bytes; 
 * @param  u16RemainLen: Length of no written data; 
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ***************************************************************************/  
static EN_ERR_STA_T flash_write_region_no_cache(uint32_t u32Addr,uint8_t *pu8Buf,uint32_t u32Len,uint16_t *u16RemainLen)
{    
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint32_t u32BeginAddr = u32Addr;
    int iRelen = u32Len;
    
    if (0 != (u32Addr % FLASH_PAGE_SIZE) || (NULL == u16RemainLen))
        return ERR_STA_ERROR;

    do
    {
        if ((0 == (u32BeginAddr % FLASH_SECTOR_SIZE)) && (iRelen >= FLASH_SECTOR_SIZE))
        {
            enRet = _flash_erase(ERASE_SECTOR,u32BeginAddr/FLASH_SECTOR_SIZE);
            if (ERR_STA_OK != enRet)
                return enRet;
            
            iRelen -= FLASH_SECTOR_SIZE;
            u32BeginAddr += FLASH_SECTOR_SIZE;
        }
        else if ((0 == (u32BeginAddr % FLASH_PAGE_SIZE)) && (iRelen >= FLASH_PAGE_SIZE))
        {
            if (FLASH_CACHE_SIZE == FLASH_SECTOR_SIZE)
                break;
            
            enRet = _flash_erase(ERASE_PAGE,u32BeginAddr/FLASH_PAGE_SIZE);
            if (ERR_STA_OK != enRet)
                return enRet;

            iRelen -= FLASH_PAGE_SIZE;
            u32BeginAddr += FLASH_PAGE_SIZE;
        }
    }while(iRelen >= FLASH_PAGE_SIZE);
    
    *u16RemainLen = iRelen;
    
    if (*u16RemainLen == u32Len)
        return enRet;
    
    enRet = _flash_write(u32Addr,pu8Buf,u32Len - iRelen);
    if (ERR_STA_OK != enRet)
        return enRet;

    gbIsCacheDataValid = false;
    
    return enRet;
}

/***************************************************************************** 
 * @brief  Read the latest data from main flash memory or flash cache
 * @param  u32Addr: Start Address of SIP FLASH MEMORY 
 * @param  pu8Buf: Pointer to a buffer which used to save the readed data 
 * @param  u32Len: Length of read data 
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ****************************************************************************/  
EN_ERR_STA_T flash_read(uint32_t u32Addr,uint8_t *pu8Buf,uint32_t u32Len)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;  
    uint32_t u32BeginAddr = u32Addr;
    uint32_t u32EndAddr = u32Addr + u32Len - 1;
    uint16_t u16HeadRegionNum = get_region_num(u32BeginAddr);
    uint16_t u16TailRegionNum = get_region_num(u32EndAddr);
    uint16_t u16RegionHeadAddrOffset;
    uint16_t u16ReLen;
    uint16_t i = u16HeadRegionNum;

    do
    {
        u16RegionHeadAddrOffset = u32BeginAddr - i * FLASH_CACHE_SIZE;    
        u16ReLen = (u16HeadRegionNum == u16TailRegionNum)?u32Len:(FLASH_CACHE_SIZE - u16RegionHeadAddrOffset);
        
        /* read exist data from flash cache */
        if ((i == gu16CurrentRegionNum) && gbIsCacheDataValid)
            memcpy(pu8Buf,&gu8FlashCache[u16RegionHeadAddrOffset],u16ReLen);
        else /* read data that not exist in flash cache from main flash memory to pu8Buf */
        {
            enRet = _flash_read(u32BeginAddr,pu8Buf,u16ReLen);
            if (ERR_STA_OK != enRet)
                return enRet;
        }
        
        pu8Buf += u16ReLen;
        u32BeginAddr += u16ReLen;
        u32Len -= u16ReLen;
    }while( ++i < u16TailRegionNum );
    
    if ( i == u16TailRegionNum)
    {
        /* read exist data from flash cache */
        if ((u16TailRegionNum == gu16CurrentRegionNum) && gbIsCacheDataValid)
            memcpy(pu8Buf,&gu8FlashCache[0],u32Len);
        else /* read tail data that not exist in flash cache from main flash memory to pu8Buf */
        {
            enRet = _flash_read(u32BeginAddr,pu8Buf,u32Len);
            if (ERR_STA_OK != enRet)
                return enRet;
        }    
    }

    return enRet;
}

/**************************************************************************** 
 * @brief  Write the buffer data to sip flash memory or flash cache from indicated start address. 
 * @param  u32Addr: Start Address of SIP FLASH MEMORY. 
 * @param  pu8Buf: Pointer to a buffer which will be written to flash memory.
 * @param  u32Len: Length of write data, maximum length is 64 * 1024 Bytes. 
 * @param  bSyncNow: Whether to synchronize immediately.
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ***************************************************************************/  
EN_ERR_STA_T flash_write(uint32_t u32Addr,uint8_t *pu8Buf,uint32_t u32Len,bool bSyncNow)
{
    EN_ERR_STA_T enRet = ERR_STA_OK; 
    uint32_t u32BeginAddr = u32Addr;
    uint32_t u32EndAddr = u32Addr + u32Len - 1;
    uint16_t u16RegionHeadAddrOffset;
    uint16_t u16RegionTailAddrOffset;
    uint16_t u16Relen;
    
    uint16_t u16HeadRegionNum = get_region_num(u32BeginAddr);
    uint16_t u16TailRegionNum = get_region_num(u32EndAddr);

    /* u32Addr region is not the same as current flash cache region */
    if ((u16HeadRegionNum != gu16CurrentRegionNum) && gbIsCacheDataValid)
    {

        /* Synchronize current flash cache into main flash memory */
        enRet = flash_sync();
        if (ERR_STA_OK != enRet)
            return enRet;
        gbIsCacheDataValid = false;
    }

    u16RegionHeadAddrOffset = u32BeginAddr - u16HeadRegionNum * FLASH_CACHE_SIZE;
    u16RegionTailAddrOffset = u32EndAddr - u16TailRegionNum * FLASH_CACHE_SIZE;

    /* read head data from main flash memory to flash cache */
    if (!gbIsCacheDataValid)
    {
        u16Relen = u16RegionHeadAddrOffset;
        if (0 != u16Relen)
        {
            enRet = _flash_read(u16HeadRegionNum * FLASH_CACHE_SIZE,gu8FlashCache,u16Relen);
            if (ERR_STA_OK != enRet)
                return enRet;
            gbIsNeedSync = true;
        }
        /* update flag */
        gu16CurrentRegionNum = u16HeadRegionNum;
    }

    /* Head and Tail in same region */
    if (u16HeadRegionNum == u16TailRegionNum)
    {
        /* write user data into flash cache */
        enRet = flash_cache_write(u16RegionHeadAddrOffset,pu8Buf,u32Len);
        if (ERR_STA_OK != enRet)
            return enRet;

        u16Relen = FLASH_CACHE_SIZE - u16RegionTailAddrOffset - 1;
        if (!gbIsCacheDataValid && (0 != u16Relen))
        {
            /* update tail data from main flash memory to flash cache */
            enRet = _flash_read(u32EndAddr + 1,&gu8FlashCache[u16RegionTailAddrOffset+1],u16Relen);
            if (ERR_STA_OK != enRet)
                return enRet;
            gbIsNeedSync = true;
        }
    }
    else /* Head and Tail in different region */
    {
        if (0 != u16RegionHeadAddrOffset)
        {
            u16Relen = FLASH_CACHE_SIZE - u16RegionHeadAddrOffset;
            enRet = flash_cache_write(u16RegionHeadAddrOffset,pu8Buf,u16Relen);
            if (ERR_STA_OK != enRet)
                return enRet;

            /* update flag */
            gbIsCacheDataValid = true;
            enRet = flash_sync();
            if (ERR_STA_OK != enRet)
                return enRet;

            pu8Buf += u16Relen;
            u32Len -= u16Relen;
        }

        enRet = flash_write_region_no_cache((gu16CurrentRegionNum + 1) * FLASH_CACHE_SIZE,pu8Buf,u32Len,&u16Relen);
        if (ERR_STA_OK != enRet)
            return enRet;

        if (0 == u16Relen)
            return enRet;

        gu16CurrentRegionNum = u16TailRegionNum;

        pu8Buf += (u32Len - u16Relen);
        u32Len = u16Relen;
        enRet = flash_cache_write(0,pu8Buf,u16Relen);
        if (ERR_STA_OK != enRet)
            return enRet;

        u16Relen = FLASH_CACHE_SIZE - u32Len;
        enRet = _flash_read(u32EndAddr + 1,&gu8FlashCache[u32Len],u16Relen);
        if (ERR_STA_OK != enRet)
            return enRet;
        gbIsNeedSync = true;

    }
    
    /* update flag */
    gbIsCacheDataValid = true;
    
    if (bSyncNow)
        enRet = flash_sync();

    return enRet;
}

/**************************************************************************** 
 * @brief  Synchronize data from flash cache to main flash memory.  
 * @output 
 * @return status: @ref EN_ERR_STA_T 
 ***************************************************************************/  
EN_ERR_STA_T flash_sync(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;  
    uint32_t u32CurrentRegionAddrBase = gu16CurrentRegionNum * FLASH_CACHE_SIZE;

    if (!gbIsCacheDataValid || !gbIsNeedSync)
        return enRet;

    /* 1.erase */
    enRet = _flash_erase(FLASH_ERASE_TYPE,gu16CurrentRegionNum);
    if (ERR_STA_OK != enRet)
        return enRet;

    /* 2.write */
    enRet = _flash_write(u32CurrentRegionAddrBase,gu8FlashCache,FLASH_CACHE_SIZE);
    /* 3.update flag */
    if (ERR_STA_OK == enRet)
        gbIsNeedSync = false;

    return enRet;
}

/**************************************************************************** 
 * @brief  Set the mode for operating the flash. 
 * @param  enMode: Access mode as below, @ref EN_FLASH_BUS_MODE_T  
 * @note   enMode default value is BUS_MODE_QPI
 ***************************************************************************/  
void set_flash_bus_mode(EN_FLASH_BUS_MODE_T enMode)
{
    genMode = enMode;
}

