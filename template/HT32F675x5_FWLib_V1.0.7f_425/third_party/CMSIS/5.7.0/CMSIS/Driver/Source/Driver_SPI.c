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

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_spi.h"

#include "Driver_SPI.h"


#define ARM_SPI_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */


/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion =
{
    ARM_SPI_API_VERSION,
    ARM_SPI_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_SPI_CAPABILITIES DriverCapabilities =
{
    0, /* Reserved (must be zero) */
    0, /* TI Synchronous Serial Interface */
    0, /* Microwire Interface */
    0, /* Signal Mode Fault event: \ref ARM_SPI_EVENT_MODE_FAULT */
    0  /* Reserved (must be zero) */
};

ARM_SPI_SignalEvent_t m_pfnSpi0Event;




//
//  Functions
//
static int32_t ARM_SPI_ReturnCheck(EN_ERR_STA_T enRet)
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

static ARM_DRIVER_VERSION ARM_SPI_GetVersion(void)
{
    return DriverVersion;
}

static ARM_SPI_CAPABILITIES ARM_SPI_GetCapabilities(void)
{
    return DriverCapabilities;
}

void SPI0_IRQ_Handler(void)
{
    uint16_t u16Falg;
    uint16_t u16SpiFalg = 0;

    rom_hw_spi_get_interrupt_flag(SPI0, &u16Falg);
    rom_hw_spi_clear_interrupt_flag(SPI0, u16Falg);

    if (u16Falg & SPI_INT_TX_FINISHED)
    {
        u16SpiFalg |= ARM_SPI_EVENT_TRANSFER_COMPLETE;
    }
    else if (u16Falg & SPI_INT_RX_FINISHED)
    {
        u16SpiFalg |= ARM_SPI_EVENT_TRANSFER_COMPLETE;
    }
    else if (u16Falg & SPI_INT_RXFIFO_OVER_FLOW)
    {
        u16SpiFalg |= ARM_SPI_EVENT_DATA_LOST;
    }
    else if (u16Falg & SPI_INT_TXFIFO_UNDER_FLOW)
    {
        u16SpiFalg |= ARM_SPI_EVENT_DATA_LOST;
    }

    if (m_pfnSpi0Event != NULL)
    {
        m_pfnSpi0Event(u16SpiFalg);
    }
}

static int32_t ARM_SPI_Initialize(ARM_SPI_SignalEvent_t cb_event)
{
    EN_ERR_STA_T enRet;
    stSpiInit_t stSpiInit;

    m_pfnSpi0Event = cb_event;

    stSpiInit.u32ClkDiv = EN_SPI_CLK_DIV_16M_1M;
    stSpiInit.unSpiCfg.u32SpiCfg = SPI_INIT_DEFAULT(SPI_MODE_MASTER, SPI_CPHA_0_0, SPI_MODE_FULL_TXRX);
    enRet = rom_hw_spi_init(SPI0, &stSpiInit);

    return ARM_SPI_ReturnCheck(enRet);
}

static int32_t ARM_SPI_Uninitialize(void)
{
    return ARM_DRIVER_OK;
}

static int32_t ARM_SPI_PowerControl(ARM_POWER_STATE state)
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

static int32_t ARM_SPI_Send(const void *data, uint32_t num)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_spi_transmit_bytes(SPI0, (uint8_t *)data, NULL, num);

    return ARM_SPI_ReturnCheck(enRet);
}

static int32_t ARM_SPI_Receive(void *data, uint32_t num)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_spi_transmit_bytes(SPI0, NULL, (uint8_t *)data, num);

    return ARM_SPI_ReturnCheck(enRet);
}

static int32_t ARM_SPI_Transfer(const void *data_out, void *data_in, uint32_t num)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_spi_transmit_bytes(SPI0, (uint8_t *)data_in, (uint8_t *)data_out, num);

    return ARM_SPI_ReturnCheck(enRet);
}

static uint32_t ARM_SPI_GetDataCount(void)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_SPI_Control(uint32_t control, uint32_t arg)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    switch (control & ARM_SPI_CONTROL_Msk)
    {
        case 0:
        {
            enRet = rom_hw_spi_disable(SPI0);
            enRet = rom_hw_spi_set_cpha_cpol_mode(SPI0, SPI_CPHA_0_0);
            enRet = rom_hw_spi_set_cs_mode(SPI0, SPI_HW_CS);
            break;
        }
        case ARM_SPI_MODE_MASTER:
        {
            enRet = rom_hw_spi_set_work_mode(SPI0, SPI_MODE_MASTER);
            // enRet = rom_hw_spi_set_speed(SPI0, 16000000, arg);
            break;
        }
        case ARM_SPI_MODE_SLAVE:
        {
            enRet = rom_hw_spi_set_work_mode(SPI0, SPI_MODE_SLAVE);
            break;
        }
        case ARM_SPI_CPOL0_CPHA1:
        {
            enRet = rom_hw_spi_set_cpha_cpol_mode(SPI0, SPI_CPHA_0_1);
            break;
        }
        case ARM_SPI_CPOL1_CPHA0:
        {
            enRet = rom_hw_spi_set_cpha_cpol_mode(SPI0, SPI_CPHA_1_0);
            break;
        }
        case ARM_SPI_CPOL1_CPHA1:
        {
            enRet = rom_hw_spi_set_cpha_cpol_mode(SPI0, SPI_CPHA_1_1);
            break;
        }
        case ARM_SPI_DATA_BITS(7):
        {
            enRet = rom_hw_spi_set_data_bits(SPI0, SPI_DATA_BITS_8);
            break;
        }
        case ARM_SPI_DATA_BITS(15):
        {
            enRet = rom_hw_spi_set_data_bits(SPI0, SPI_DATA_BITS_16);
            break;
        }
        case ARM_SPI_DATA_BITS(31):
        {
            enRet = rom_hw_spi_set_data_bits(SPI0, SPI_DATA_BITS_32);
            break;
        }
        case ARM_SPI_DATA_BITS(63):
        {
            enRet = rom_hw_spi_set_data_bits(SPI0, SPI_DATA_BITS_64);
            break;
        }
        case ARM_SPI_SS_MASTER_SW:
        case ARM_SPI_SS_SLAVE_SW:
        {
            enRet = rom_hw_spi_set_cs_mode(SPI0, SPI_SW_CS);
            break;
        }
        case ARM_SPI_SS_MASTER_HW_OUTPUT:
        {
            enRet = rom_hw_spi_set_cs_mode(SPI0, SPI_HW_CS);
            break;
        }
        case ARM_SPI_SET_BUS_SPEED:
        {
            // enRet = rom_hw_spi_set_speed(SPI0, 16000000, arg);
            break;
        }
        case ARM_SPI_SET_DEFAULT_TX_VALUE:
        {
            enRet = rom_hw_spi_set_idle_data(SPI0, arg);
            break;
        }
        default:
        {
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
    }

    return ARM_SPI_ReturnCheck(enRet);
}

static ARM_SPI_STATUS ARM_SPI_GetStatus(void)
{
    ARM_SPI_STATUS stStatus =
    {
        .busy       = 0,
        .data_lost  = 0,
        .mode_fault = 0,
        .reserved   = 0,
    };

    return stStatus;
}

static void ARM_SPI_SignalEvent(uint32_t event)
{
    uint16_t u16SpiFalg = 0;

    if (event & ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        u16SpiFalg |= SPI_INT_TX_FINISHED | SPI_INT_RX_FINISHED;
    }
    else if (event & ARM_SPI_EVENT_DATA_LOST)
    {
        u16SpiFalg |= SPI_INT_RXFIFO_OVER_FLOW | SPI_INT_TXFIFO_UNDER_FLOW;
    }

    rom_hw_spi_disable_interrupt(SPI0, SPI_INT_MASK);
    rom_hw_spi_enable_interrupt(SPI0, u16SpiFalg);
}

// End SPI Interface
extern ARM_DRIVER_SPI Driver_SPI0;
ARM_DRIVER_SPI Driver_SPI0 =
{
    ARM_SPI_GetVersion,
    ARM_SPI_GetCapabilities,
    ARM_SPI_Initialize,
    ARM_SPI_Uninitialize,
    ARM_SPI_PowerControl,
    ARM_SPI_Send,
    ARM_SPI_Receive,
    ARM_SPI_Transfer,
    ARM_SPI_GetDataCount,
    ARM_SPI_Control,
    ARM_SPI_GetStatus
};


