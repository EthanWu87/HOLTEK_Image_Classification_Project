/*************************************************************************************************************
 * @file    mlog_transport_uart.c
 * @version V1.0
 * @date    2023-07-11
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

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_gpio.h"
#include "hw_uart.h"
#include "hw_crg.h"

#include "mlog_protocol.h"
#include "mlog_transport_uart.h"

static void mlog_transport_uart_protocol_print_impl(uint8_t *pu8Buffer, uint16_t u16Length);

static EN_GPIO_PIN_T    m_enumLogIoTx;
static uint32_t         m_u32LogUartBps;
static stUART_Handle_t *m_pstLogUartHandle;
static stGPIO_Handle_t *m_pstLogGpioHandle;

bool mlog_transport_uart_init(stUART_Handle_t *pstUART, stGPIO_Handle_t *pstGPIO, EN_GPIO_PIN_T enumPin,
                              uint32_t u32BaudRate)
{
    if ((!(IS_VALID_UART_HANDLE(pstUART))))
    {
        return false;
    }

    m_enumLogIoTx      = enumPin;
    m_u32LogUartBps    = (uint32_t)u32BaudRate;
    m_pstLogUartHandle = pstUART;
    m_pstLogGpioHandle = pstGPIO;

    return mlog_transport_uart_reinit();
}

void mlog_transport_uart_deinit(void)
{
    mlog_protocol_print_callback_register(NULL);

    rom_hw_gpio_set_pin_input_output(m_pstLogGpioHandle, m_enumLogIoTx, GPIO_MODE_IMPEDANCE);

    if (UART0 == m_pstLogUartHandle)
    {
        rom_hw_crg_disable_clk_gate(CRG_UART0_CLK_GATE);
    }
    else
    {
        rom_hw_crg_disable_clk_gate(CRG_UART1_CLK_GATE);
    }
}

bool mlog_transport_uart_reinit(void)
{
    EN_ERR_STA_T enRet;
    stUartInit_t stUartInit;

    if (UART0 == m_pstLogUartHandle)
    {
        rom_hw_crg_enable_clk_gate(CRG_UART0_CLK_GATE);
        enRet = rom_hw_gpio_set_pin_pid(m_pstLogGpioHandle, m_enumLogIoTx, PID_UART0_TXD);
    }
    else
    {
        rom_hw_crg_enable_clk_gate(CRG_UART1_CLK_GATE);
        enRet = rom_hw_gpio_set_pin_pid(m_pstLogGpioHandle, m_enumLogIoTx, PID_UART1_TXD);
    }
    ERR_RETURN_IF_ERROR(enRet);

    enRet = rom_hw_gpio_set_pin_pull_mode(m_pstLogGpioHandle, m_enumLogIoTx, GPIO_PULL_UP);
    ERR_RETURN_IF_ERROR(enRet);

    stUartInit.u32UartBaudRate = m_u32LogUartBps;

    // TxFifoThld and RxFifoThld is 8, StopBit is 1, 8bit, no parity, little-ending
    stUartInit.unUartCfg.u32UartCfg = UART_INIT_DEFAULT(UART_PARITY_NONE);

    enRet = rom_hw_uart_init(m_pstLogUartHandle, &stUartInit);
    if (ERR_STA_OK == enRet)
    {
        mlog_protocol_print_callback_register(mlog_transport_uart_protocol_print_impl);
        return true;
    }
    else
    {
        return false;
    }
}

void mlog_transport_uart_print(void)
{
    mlog_protocol_print();
}

static void mlog_transport_uart_protocol_print_impl(uint8_t *pu8Buffer, uint16_t u16Length)
{
    rom_hw_uart_transmit(m_pstLogUartHandle, pu8Buffer, u16Length);
}
