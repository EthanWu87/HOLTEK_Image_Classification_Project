/*
 * Copyright (c) 2013-2020 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "sflash.h"
#include "hw_flash.h"

#include "Driver_Storage.h"


#define ARM_STORAGE_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */


/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion =
{
    ARM_STORAGE_API_VERSION,
    ARM_STORAGE_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_STORAGE_CAPABILITIES DriverCapabilities =
{
    0, /* Asynchronous Mode */
    0, /* Supports EraseAll operation */
    0  /* Reserved */
};


//
// Functions
//
static int32_t ARM_Storage_ReturnCheck(EN_ERR_STA_T enRet)
{
    int32_t s32Ret = ARM_DRIVER_OK;

    switch (enRet)
    {
        case ERR_STA_OK:
        {
            s32Ret = ARM_DRIVER_OK;
            break;
        }
        case ERR_STA_BUSY:
        {
            s32Ret = ARM_DRIVER_ERROR_BUSY;
            break;
        }
        case ERR_STA_TIMEOUT:
        {
            s32Ret = ARM_DRIVER_ERROR_TIMEOUT;
            break;
        }
        case ERR_PARA_ERR:
        {
            s32Ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        }
        default:
        {
            s32Ret = ARM_DRIVER_ERROR;
            break;
        }
    }

    return s32Ret;
}

static ARM_DRIVER_VERSION ARM_Storage_GetVersion(void)
{
    return DriverVersion;
}

static ARM_STORAGE_CAPABILITIES ARM_Storage_GetCapabilities(void)
{
    return DriverCapabilities;
}

static int32_t ARM_Storage_Initialize(ARM_Storage_Callback_t callback)
{
    return ARM_DRIVER_OK;
}

static int32_t ARM_Storage_Uninitialize(void)
{
    return ARM_DRIVER_OK;
}

static int32_t ARM_Storage_PowerControl(ARM_POWER_STATE state)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    switch (state)
    {
        case ARM_POWER_OFF:
        {
            break;
        }
        case ARM_POWER_LOW:
        {
            enRet = rom_hw_flash_enter_deep_power_down(FLASH, BUS_MODE_QPI);
            break;
        }
        case ARM_POWER_FULL:
        {
            enRet = rom_hw_flash_release_deep_power_down(FLASH);
            break;
        }
    }

    return ARM_Storage_ReturnCheck(enRet);
}

static int32_t ARM_Storage_ReadData(uint64_t addr, void *data, uint32_t size)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_flash_read_bytes(FLASH, addr, (uint8_t *)data, size, BUS_MODE_SPI);

    return ARM_Storage_ReturnCheck(enRet);
}

static int32_t ARM_Storage_ProgramData(uint64_t addr, const void *data, uint32_t size)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_flash_write_bytes(FLASH, addr, (uint8_t *)data, size, BUS_MODE_SPI, FLASH_PROGRAM_TIMEOUT_US);

    return ARM_Storage_ReturnCheck(enRet);
}

static int32_t ARM_Storage_Erase(uint64_t addr, uint32_t size)
{
    EN_ERR_STA_T enRet;
    uint32_t eraseSize;
    uint32_t u32Addr = addr;
    uint32_t u32Size = size;

    if ((addr % SFLASH_PAGE_BYTE_SIZE) || (size % SFLASH_PAGE_BYTE_SIZE))
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    do
    {
        if ((u32Size >= SFLASH_BLOCK_64KB_BYTE_SIZE) && (u32Addr % SFLASH_BLOCK_64KB_BYTE_SIZE == 0))
        {
            enRet = rom_hw_flash_erase(FLASH, ERASE_BLOCK_64KB, u32Addr >> SFLASH_BLOCK_64KB_SHIFT_BITS,
                                         FLASH_PAGE_ERASE_TIMEOUT_US);
            eraseSize = SFLASH_BLOCK_64KB_BYTE_SIZE;
        }
        else if ((u32Size >= SFLASH_BLOCK_32KB_BYTE_SIZE) && (u32Addr % SFLASH_BLOCK_32KB_BYTE_SIZE == 0))
        {
            enRet = rom_hw_flash_erase(FLASH, ERASE_BLOCK_32KB, u32Addr >> SFLASH_BLOCK_32KB_SHIFT_BITS,
                                         FLASH_PAGE_ERASE_TIMEOUT_US);
            eraseSize = SFLASH_BLOCK_32KB_BYTE_SIZE;
        }
        else if ((u32Size >= SFLASH_SECTOR_BYTE_SIZE) && (u32Addr % SFLASH_SECTOR_BYTE_SIZE == 0))
        {
            enRet = rom_hw_flash_erase(FLASH, ERASE_SECTOR, u32Addr >> SFLASH_SECTOR_SHIFT_BITS,
                                         FLASH_PAGE_ERASE_TIMEOUT_US);
            eraseSize = SFLASH_SECTOR_BYTE_SIZE;
        }
        else
        {
            enRet = rom_hw_flash_erase(FLASH, ERASE_PAGE, u32Addr >> SFLASH_PAGE_SHIFT_BITS,
                                         FLASH_PAGE_ERASE_TIMEOUT_US);
            eraseSize = SFLASH_PAGE_BYTE_SIZE;
        }

        if (ERR_STA_OK != enRet)
        {
            return ARM_Storage_ReturnCheck(enRet);
        }

        u32Size -= eraseSize;
        u32Addr += eraseSize;

    } while (u32Addr < (addr + size));

    return ARM_Storage_ReturnCheck(enRet);
}

static int32_t ARM_Storage_EraseAll(void)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_flash_chip_erase(FLASH, FLASH_CHIP_ERASE_TIMEOUT_US);

    return ARM_Storage_ReturnCheck(enRet);
}

static ARM_STORAGE_STATUS ARM_Storage_GetStatus(void)
{
    ARM_STORAGE_STATUS enStatus = 
    {
        .busy = 0,
        .error = 0,
        .reserved = 0,
    };

    return enStatus;
}

static int32_t ARM_Storage_GetInfo(ARM_STORAGE_INFO *info)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static uint32_t ARM_Storage_ResolveAddress(uint64_t addr)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_Storage_GetNextBlock(const ARM_STORAGE_BLOCK *prev_block, ARM_STORAGE_BLOCK *next_block)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_Storage_GetBlock(uint64_t addr, ARM_STORAGE_BLOCK *block)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

// End Storage Interface
extern ARM_DRIVER_STORAGE Driver_Storage0;
ARM_DRIVER_STORAGE Driver_Storage0 =
{
    ARM_Storage_GetVersion,
    ARM_Storage_GetCapabilities,
    ARM_Storage_Initialize,
    ARM_Storage_Uninitialize,
    ARM_Storage_PowerControl,
    ARM_Storage_ReadData,
    ARM_Storage_ProgramData,
    ARM_Storage_Erase,
    ARM_Storage_EraseAll,
    ARM_Storage_GetStatus,
    ARM_Storage_GetInfo,
    ARM_Storage_ResolveAddress,
    ARM_Storage_GetNextBlock,
    ARM_Storage_GetBlock
};


