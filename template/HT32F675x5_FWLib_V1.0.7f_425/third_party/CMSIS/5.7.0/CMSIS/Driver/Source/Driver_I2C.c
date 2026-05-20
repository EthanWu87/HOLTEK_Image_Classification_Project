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

#include <string.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_i2c.h"

#include "Driver_I2C.h"


#define ARM_I2C_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion =
{
    ARM_I2C_API_VERSION,
    ARM_I2C_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_I2C_CAPABILITIES DriverCapabilities =
{
    1 /* supports 10-bit addressing */
};

static ARM_I2C_SignalEvent_t m_pfnI2c0Event;




//
//  Functions
//
static int32_t ARM_I2C_ReturnCheck(EN_ERR_STA_T enRet)
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

static ARM_DRIVER_VERSION ARM_I2C_GetVersion(void)
{
    return DriverVersion;
}

static ARM_I2C_CAPABILITIES ARM_I2C_GetCapabilities(void)
{
    return DriverCapabilities;
}

void I2C0_IRQ_Handler(void)
{
    uint16_t u16Falg;
    uint16_t u16I2cFalg = 0;

    rom_hw_i2c_get_interrupt_flag(I2C0, &u16Falg);
    rom_hw_i2c_clear_interrupt_flag(I2C0, u16Falg);

    if (u16Falg & I2C_INT_TX_FINISHED)
    {
        u16I2cFalg |= ARM_I2C_EVENT_TRANSFER_DONE;
    }
    else if (u16Falg & I2C_INT_RXFIFO_NOT_EMPTY)
    {
        u16I2cFalg |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
    }
    else if (u16Falg & I2C_INT_MASTER_ARBITRATE_LOST)
    {
        u16I2cFalg |= ARM_I2C_EVENT_ARBITRATION_LOST;
    }
    else if (u16Falg & I2C_INT_SLAVE_BUS_ERROR)
    {
        u16I2cFalg |= ARM_I2C_EVENT_BUS_ERROR;
    }

    if (m_pfnI2c0Event != NULL)
    {
        m_pfnI2c0Event(u16I2cFalg);
    }
}

static int32_t ARM_I2C_Initialize(ARM_I2C_SignalEvent_t cb_event)
{
    EN_ERR_STA_T enRet;
    stI2cMasterInit_t stI2cMasterInit;

    m_pfnI2c0Event = cb_event;

    stI2cMasterInit.u32BaudRate = I2C_BAUDRATE_400K;
    stI2cMasterInit.u16SlaveAddr = 0x50;
    stI2cMasterInit.unCfg.stCfg.u8AddrMode = I2C_ADDR_MODE_7_BITS;
    stI2cMasterInit.unCfg.stCfg.u8Enable = I2C_ENABLE;
    stI2cMasterInit.unCfg.stCfg.u8StretchEn = I2C_STRETCH_ENABLE;
    stI2cMasterInit.unCfg.stCfg.u8TrxMode = I2C_MASTER_MODE_WRITE;
    enRet = rom_hw_i2c_master_init(I2C0, &stI2cMasterInit);

    return ARM_I2C_ReturnCheck(enRet);
}

static int32_t ARM_I2C_Uninitialize(void)
{
    return ARM_DRIVER_OK;
}

static int32_t ARM_I2C_PowerControl(ARM_POWER_STATE state)
{
    switch (state)
    {
        case ARM_POWER_OFF:
        {
            break;
        }
        case ARM_POWER_LOW:
        {
            break;
        }
        case ARM_POWER_FULL:
        {
            break;
        }
    }
    return ARM_DRIVER_OK;
}

static int32_t ARM_I2C_MasterTransmit(uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_i2c_set_addr(I2C0, addr);
    enRet = rom_hw_i2c_master_write(I2C0, (uint8_t *)data, num);

    return ARM_I2C_ReturnCheck(enRet);
}

static int32_t ARM_I2C_MasterReceive(uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_i2c_set_addr(I2C0, addr);
    enRet = rom_hw_i2c_master_read(I2C0, (uint8_t *)data, num);

    return ARM_I2C_ReturnCheck(enRet);
}

static int32_t ARM_I2C_SlaveTransmit(const uint8_t *data, uint32_t num)
{
    EN_ERR_STA_T enRet;

    enRet = patch_hw_i2c_slave_write(I2C0, (uint8_t *)data, num);

    return ARM_I2C_ReturnCheck(enRet);
}

static int32_t ARM_I2C_SlaveReceive(uint8_t *data, uint32_t num)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_I2C_GetDataCount(void)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_I2C_Control(uint32_t control, uint32_t arg)
{
    EN_ERR_STA_T enRet;

    switch (control)
    {
        case ARM_I2C_OWN_ADDRESS:
        {
            rom_hw_i2c_set_addr(I2C0, arg);
            break;
        }
        case ARM_I2C_BUS_SPEED:
        {
            switch (arg)
            {
                case ARM_I2C_BUS_SPEED_STANDARD:
                {
                    enRet = rom_hw_i2c_master_set_speed(I2C0, I2C_BAUDRATE_100K);
                    break;
                }
                case ARM_I2C_BUS_SPEED_FAST:
                {
                    enRet = rom_hw_i2c_master_set_speed(I2C0, I2C_BAUDRATE_400K);
                    break;
                }
                default:
                {
                    return ARM_DRIVER_ERROR_UNSUPPORTED;
                }
            }
            break;
        }
        case ARM_I2C_ABORT_TRANSFER:
        {
            enRet = rom_hw_i2c_master_disable(I2C0);
            enRet = rom_hw_i2c_slave_disable(I2C0);
            break;
        }
        default:
        {
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
    }

    return ARM_I2C_ReturnCheck(enRet);
}

static ARM_I2C_STATUS ARM_I2C_GetStatus(void)
{
    ARM_I2C_STATUS stStatus =
    {
        .busy             = 0,
        .mode             = 0,
        .direction        = 0,
        .general_call     = 0,
        .arbitration_lost = 0,
        .bus_error        = 0,
        .reserved         = 0,
    };

    return stStatus;
}

static void ARM_I2C_SignalEvent(uint32_t event)
{
    uint16_t u16I2cFalg = 0;

    if (event & ARM_I2C_EVENT_TRANSFER_DONE)
    {
        u16I2cFalg |= I2C_INT_TX_FINISHED;
    }
    else if (event & ARM_I2C_EVENT_TRANSFER_INCOMPLETE)
    {
        u16I2cFalg |= I2C_INT_RXFIFO_NOT_EMPTY;
    }
    else if (event & ARM_I2C_EVENT_ARBITRATION_LOST)
    {
        u16I2cFalg |= I2C_INT_MASTER_ARBITRATE_LOST;
    }
    else if (event & ARM_I2C_EVENT_BUS_ERROR)
    {
        u16I2cFalg |= I2C_INT_SLAVE_BUS_ERROR;
    }

    rom_hw_i2c_disable_interrupt(I2C0, I2C_INT_MASK);
    rom_hw_i2c_enable_interrupt(I2C0, u16I2cFalg);
}


// End I2C Interface
extern ARM_DRIVER_I2C Driver_I2C0;
ARM_DRIVER_I2C Driver_I2C0 =
{
    ARM_I2C_GetVersion,
    ARM_I2C_GetCapabilities,
    ARM_I2C_Initialize,
    ARM_I2C_Uninitialize,
    ARM_I2C_PowerControl,
    ARM_I2C_MasterTransmit,
    ARM_I2C_MasterReceive,
    ARM_I2C_SlaveTransmit,
    ARM_I2C_SlaveReceive,
    ARM_I2C_GetDataCount,
    ARM_I2C_Control,
    ARM_I2C_GetStatus
};


