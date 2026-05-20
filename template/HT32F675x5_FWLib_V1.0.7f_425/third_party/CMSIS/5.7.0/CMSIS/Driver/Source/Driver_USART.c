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
#include "hw_uart.h"

#include "Driver_USART.h"


#define ARM_USART_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */


/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion =
{
    ARM_USART_API_VERSION,
    ARM_USART_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_USART_CAPABILITIES DriverCapabilities =
{
    1, /* supports UART (Asynchronous) mode */
    0, /* supports Synchronous Master mode */
    0, /* supports Synchronous Slave mode */
    0, /* supports UART Single-wire mode */
    0, /* supports UART IrDA mode */
    0, /* supports UART Smart Card mode */
    0, /* Smart Card Clock generator available */
    1, /* RTS Flow Control available */
    1, /* CTS Flow Control available */
    1, /* Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE */
    1, /* Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT */
    1, /* RTS Line: 0=not available, 1=available */
    1, /* CTS Line: 0=not available, 1=available */
    0, /* DTR Line: 0=not available, 1=available */
    0, /* DSR Line: 0=not available, 1=available */
    0, /* DCD Line: 0=not available, 1=available */
    0, /* RI Line: 0=not available, 1=available */
    0, /* Signal CTS change event: \ref ARM_USART_EVENT_CTS */
    0, /* Signal DSR change event: \ref ARM_USART_EVENT_DSR */
    0, /* Signal DCD change event: \ref ARM_USART_EVENT_DCD */
    0, /* Signal RI change event: \ref ARM_USART_EVENT_RI */
    0  /* Reserved (must be zero) */
};

static ARM_USART_SignalEvent_t m_pfnUart0Event;




//
//   Functions
//
static int32_t ARM_USART_ReturnCheck(EN_ERR_STA_T enRet)
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

static ARM_DRIVER_VERSION ARM_USART_GetVersion(void)
{
    return DriverVersion;
}

static ARM_USART_CAPABILITIES ARM_USART_GetCapabilities(void)
{
    return DriverCapabilities;
}

void UART0_IRQ_Handler(void)
{
    uint16_t u16Falg;
    uint16_t u16UartFalg = 0;

    rom_hw_uart_get_interrupt_flag(UART0, &u16Falg);
    rom_hw_uart_clear_interrupt_flag(UART0, u16Falg);

    if (u16Falg & UART_INT_TX_FINISHED)
    {
        u16UartFalg |= ARM_USART_EVENT_TX_COMPLETE;
    }
    else if (u16Falg & UART_INT_RXFIFO_OVER_FLOW)
    {
        u16UartFalg |= ARM_USART_EVENT_RX_OVERFLOW;
    }
    else if (u16Falg & UART_INT_RX_TIMEOUT)
    {
        u16UartFalg |= ARM_USART_EVENT_RX_TIMEOUT;
    }
    else if (u16Falg & UART_INT_LINE_BREAK)
    {
        u16UartFalg |= ARM_USART_EVENT_RX_BREAK;
    }
    else if (u16Falg & UART_INT_PARITY_ERR)
    {
        u16UartFalg |= ARM_USART_EVENT_RX_PARITY_ERROR;
    }

    if (m_pfnUart0Event != NULL)
    {
        m_pfnUart0Event(u16UartFalg);
    }
}

static int32_t ARM_USART_Initialize(ARM_USART_SignalEvent_t cb_event)
{
    stUartInit_t stUartInit;
    EN_ERR_STA_T enRet;

    m_pfnUart0Event = cb_event;

    stUartInit.u32UartBaudRate = 115200;
    stUartInit.unUartCfg.u32UartCfg = UART_INIT_DEFAULT(UART_PARITY_NONE);

    enRet = rom_hw_uart_init(UART0, &stUartInit);

    return ARM_USART_ReturnCheck(enRet);
}

static int32_t ARM_USART_Uninitialize(void)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_uart_deinit(UART0);

    return ARM_USART_ReturnCheck(enRet);
}

static int32_t ARM_USART_PowerControl(ARM_POWER_STATE state)
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

    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_USART_Send(const void *data, uint32_t num)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_uart_transmit(UART0, (uint8_t *)data, num);

    return ARM_USART_ReturnCheck(enRet);
}

static int32_t ARM_USART_Receive(void *data, uint32_t num)
{
    EN_ERR_STA_T enRet;

    enRet = rom_hw_uart_receive(UART0, (uint8_t *)data, num);

    return ARM_USART_ReturnCheck(enRet);
}

static int32_t ARM_USART_Transfer(const void *data_out, void *data_in, uint32_t num)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static uint32_t ARM_USART_GetTxCount(void)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static uint32_t ARM_USART_GetRxCount(void)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_USART_Control(uint32_t control, uint32_t arg)
{
    EN_ERR_STA_T enRet;

    switch (control)
    {
        case 0: // Default
        {
            enRet = rom_hw_uart_set_data_sizes(UART0, UART_DATA_BITS_8);
            enRet = rom_hw_uart_set_parity(UART0, UART_PARITY_NONE);
            enRet = rom_hw_uart_set_stop_sizes(UART0, UART_STOP_SIZE_1BIT);
            enRet = rom_hw_uart_flow_enable(UART0, UART_FLOW_DISABLE);
            break;
        }
        case ARM_USART_MODE_ASYNCHRONOUS:
        {
            enRet = rom_hw_uart_set_baudrate(UART0, arg);
            break;
        }
        case ARM_USART_DATA_BITS_5:
        {
            enRet = rom_hw_uart_set_data_sizes(UART0, UART_DATA_BITS_5);
            break;
        }
        case ARM_USART_DATA_BITS_6:
        {
            enRet = rom_hw_uart_set_data_sizes(UART0, UART_DATA_BITS_6);
            break;
        }
        case ARM_USART_DATA_BITS_7:
        {
            enRet = rom_hw_uart_set_data_sizes(UART0, UART_DATA_BITS_7);
            break;
        }
        case ARM_USART_PARITY_EVEN:
        {
            enRet = rom_hw_uart_set_parity(UART0, UART_PARITY_EVEN);
            break;
        }
        case ARM_USART_PARITY_ODD:
        {
            enRet = rom_hw_uart_set_parity(UART0, UART_PARITY_ODD);
            break;
        }
        case ARM_USART_STOP_BITS_2:
        {
            enRet = rom_hw_uart_set_stop_sizes(UART0, UART_STOP_SIZE_2BIT);
            break;
        }
        case ARM_USART_STOP_BITS_1_5:
        {
            enRet = rom_hw_uart_set_stop_sizes(UART0, UART_STOP_SIZE_1P5BIT);
            break;
        }
        case ARM_USART_STOP_BITS_0_5:
        {
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
        case ARM_USART_FLOW_CONTROL_RTS_CTS:
        {
            enRet = rom_hw_uart_flow_enable(UART0, UART_FLOW_ENABLE);
            break;
        }
        default:
        {
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
    }

    return ARM_USART_ReturnCheck(enRet);
}

static ARM_USART_STATUS ARM_USART_GetStatus(void)
{
    ARM_USART_STATUS stStatus =
    {
        .tx_busy          = 0,
        .rx_busy          = 0,
        .tx_underflow     = 0,
        .rx_overflow      = 0,
        .rx_break         = 0,
        .rx_framing_error = 0,
        .rx_parity_error  = 0,
        .reserved         = 0
    };

    return stStatus;
}

static int32_t ARM_USART_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static ARM_USART_MODEM_STATUS ARM_USART_GetModemStatus(void)
{
    ARM_USART_MODEM_STATUS stStatus =
    {
        .cts = 0,
        .dsr = 0,
        .dcd = 0,
        .ri  = 0,
        .reserved = 0
    };

    return stStatus;
}

static void __attribute__((unused)) ARM_USART_SignalEvent(uint32_t event)
{
    uint16_t u16UartFalg = 0;

    if (event & ARM_USART_EVENT_TX_COMPLETE)
    {
        u16UartFalg |= UART_INT_TX_FINISHED;
    }
    else if (event & ARM_USART_EVENT_RX_OVERFLOW)
    {
        u16UartFalg |= UART_INT_RXFIFO_OVER_FLOW;
    }
    else if (event & ARM_USART_EVENT_RX_TIMEOUT)
    {
        u16UartFalg |= UART_INT_RX_TIMEOUT;
    }
    else if (event & ARM_USART_EVENT_RX_BREAK)
    {
        u16UartFalg |= UART_INT_LINE_BREAK;
    }
    else if (event & ARM_USART_EVENT_RX_PARITY_ERROR)
    {
        u16UartFalg |= UART_INT_PARITY_ERR;
    }

    rom_hw_uart_disable_interrupt(UART0, UART_INT_MASK);
    rom_hw_uart_enable_interrupt(UART0, u16UartFalg);
}

// End USART Interface
extern ARM_DRIVER_USART Driver_USART0;
ARM_DRIVER_USART Driver_USART0 =
{
    ARM_USART_GetVersion,
    ARM_USART_GetCapabilities,
    ARM_USART_Initialize,
    ARM_USART_Uninitialize,
    ARM_USART_PowerControl,
    ARM_USART_Send,
    ARM_USART_Receive,
    ARM_USART_Transfer,
    ARM_USART_GetTxCount,
    ARM_USART_GetRxCount,
    ARM_USART_Control,
    ARM_USART_GetStatus,
    ARM_USART_SetModemControl,
    ARM_USART_GetModemStatus
};


