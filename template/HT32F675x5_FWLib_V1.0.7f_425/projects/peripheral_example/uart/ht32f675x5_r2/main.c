/*************************************************************************************************************
 * @file    main.c
 * @version V1.1
 * @date    2025-08-21
 * @brief   UART module example code.
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


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_pmu.h"
#include "hw_efuse.h"
#include "hw_dma.h"
#include "hw_gpio.h"
#include "hw_uart.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hal_pmu.h"

#include "app_cfg.h"
#include "type_def.h"
#include "boards.h"

#include "utility.h"
#include "app_debug.h"


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define UART_BUF_SIZE                      ( 256 )


//=====================================================================================================================
// TYPEDEFS
//=====================================================================================================================
typedef enum
{
    UART_EXAMPLE_TX           = 0x00,
    UART_EXAMPLE_INTERRUPT_RX = 0x01,
    UART_EXAMPLE_DMA_TX       = 0x02,
    UART_EXAMPLE_DMA_RX       = 0x03,

} enUartExampleCase_t;


//=====================================================================================================================
// LOCAL VARIABLES
//=====================================================================================================================
static uint8_t m_u8TxBuf[UART_BUF_SIZE] __attribute__((aligned(4))) = {0};
static uint8_t m_u8RxBuf[UART_BUF_SIZE] __attribute__((aligned(4))) = {0};




/**
 * @brief  System power manage.
 */
static void system_power_init(void)
{
    rom_hw_pmu_set_ldo_act_voltage(EN_LDO_ACT_1200mV);
    rom_hw_pmu_set_ldo_dig_voltage(EN_LDO_DIG_1100mV);
    rom_hw_pmu_set_ldo_ret_sleep_voltage(EN_LDO_RET_1100mV);

    // Power Selection
    rom_hal_pmu_sel_power_act_out_mode(PWR_SEL_LDO);
}

/**
 * @brief  System clock init.
 * @param  enSrc: System clock source selection, @ref EN_SYS_CLK_SRC_SEL_T.
 */
static void system_clock_init(EN_SYS_CLK_SRC_SEL_T enSysClkSrc)
{
    uint8_t u8Tune = 0;

    /* Set rc_hclk tune value */
    rom_hw_efuse_read_bytes(EFUSE_RC_HCLK_TUNE_ADDR, &u8Tune, sizeof(u8Tune));
    if (0 == u8Tune)
    {
        rom_hw_pmu_set_rc_hclk_tune(RC_HCLK_TUNE_DEFAUT_VAL);
    }

    /* Set rc32k tune value */
    rom_hw_efuse_read_bytes(EFUSE_RC_LCLK_TUNE_ADDR, &u8Tune, sizeof(u8Tune));
    if (u8Tune)
    {
        rom_hw_pmu_set_rc_lclk_tune(u8Tune);
    }
    else
    {
        rom_hw_pmu_set_rc_lclk_tune(RC_LCLK_TUNE_DEFAUT_VAL);
    }

    /* System clock */
    rom_hw_pmu_sel_dcxo_hclk_pwr(EN_DCXO_HCLK_PWR_VDDR);
    rom_hal_pmu_cfg_dcxo_hclk_param(DCXO_HCLK_IB_3, DCXO_HCLK_NGM_3, DCXO_HCLK_CAP_10PF);
    rom_hal_pmu_set_sys_clk_src(enSysClkSrc, DCXO_HCLK_STABLE_TIME_2500US);
}

/**
 * @brief  All peripheral init.
 */
static void peripheral_init(void)
{
    /* Disable MP all Peripheral interrupt. */
    rom_hw_sys_ctrl_peri_int_ctrl(SYS_CTRL_MP, 0, 0);

#if APP_DEBUG_ENABLED
    app_debug_init(GPIO_PORT_APP_DEBUG_TX, GPIO_PIN_APP_DEBUG_TX, UART_HANDLE_APP_DEBUG, UART_BPS_APP_DEBUG, NULL);

    PRINTF("UART example code start to work.\n");
#endif
}

/**
 * @brief  uart init.
 */
static void uart_example_init(void)
{
    stUartInit_t stUartInit;

    // 1. Turn UART clock gating on.
    rom_hw_crg_enable_clk_gate(CRG_UART0_CLK_GATE);

    // 2. Init UART IO.
    rom_hw_gpio_set_pin_pid(GPIO_PORT_UART_TX, GPIO_PIN_UART_TX, PID_UART0_TXD);
    rom_hw_gpio_set_pin_pid(GPIO_PORT_UART_RX, GPIO_PIN_UART_RX, PID_UART0_RXD);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_UART_TX, GPIO_PIN_UART_TX, GPIO_PULL_UP);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_UART_RX, GPIO_PIN_UART_RX, GPIO_PULL_UP);

    // 3. UART Init.
    stUartInit.u32UartBaudRate = UART_BPS_EXAMPLE;
    stUartInit.unUartCfg.u32UartCfg = UART_INIT_DEFAULT(UART_PARITY_NONE);

    rom_hw_uart_init(UART_HANDLE_EXAMPLE, &stUartInit);
}

/**
 * @brief  uart irq handler.
 */
void UART2_IRQ_Handler(void)
{
    uint8_t i;
    uint8_t u8Cnt = 0;
    uint16_t u16Falg = 0;

    rom_hw_uart_get_interrupt_flag(UART_HANDLE_EXAMPLE, &u16Falg);
    rom_hw_uart_clear_interrupt_flag(UART_HANDLE_EXAMPLE, u16Falg);

    rom_hw_uart_get_rxfifo_cnt(UART_HANDLE_EXAMPLE, &u8Cnt);
    rom_hw_uart_receive(UART_HANDLE_EXAMPLE, m_u8RxBuf, u8Cnt);

    for (i = 0; i < u8Cnt; i++)
    {
        PRINTF("%02X ", m_u8RxBuf[i]);
    }
    PRINTF("\n");
}

/**
 * @brief  uart interrupt init.
 */
static void uart_example_int_init(void)
{
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, UART2_IRQ);
    NVIC_ClearPendingIRQ(UART2_IRQ);
    NVIC_SetPriority(UART2_IRQ, 0x3);
    NVIC_EnableIRQ(UART2_IRQ);

    rom_hw_uart_set_rx_timeout(UART_HANDLE_EXAMPLE, 2);
    rom_hw_uart_set_rxfifo_thld(UART_HANDLE_EXAMPLE, 8);
    rom_hw_uart_enable_interrupt(UART_HANDLE_EXAMPLE, UART_INT_RX_TIMEOUT | UART_INT_RXFIFO_OVER_THLD);
}

/**
 * @brief  uart dma irq handler.
 */
void DMA_IRQ7_Handler(void)
{
    uint8_t u8IntMsk;
    uint16_t u16Count;

    rom_hw_dma_get_interrupt_flag(DMA6, &u8IntMsk);
    rom_hw_dma_clear_interrupt_flag(DMA6, u8IntMsk);

    if (u8IntMsk & DMA_INT_MSK)
    {
        rom_hw_dma_get_trx_pointer(DMA6, &u16Count);
        PRINTF("DMA6 INT: %02X, %d\n", u8IntMsk, u16Count);
    }

    rom_hw_dma_get_interrupt_flag(DMA7, &u8IntMsk);
    rom_hw_dma_clear_interrupt_flag(DMA7, u8IntMsk);

    if (u8IntMsk & DMA_INT_MSK)
    {
        PRINTF("DMA7 INT: %02X\n", u8IntMsk);
    }
}

/**
 * @brief  uart dma init.
 */
static void uart_example_dma_init(void)
{
    stDmaInit_t stDmaInit;

    // 1. Turn DMA clock gating on.
    rom_hw_crg_enable_clk_gate(CRG_DMA_CLK_GATE);

    // 2. UART RX DMA configuration
    stDmaInit.u32SrcAddr = (uint32_t)&UART2->UART_RX_FIFO;
    stDmaInit.u32DstAddr = (uint32_t)m_u8RxBuf;
    stDmaInit.u32TimeOut = 1000;
    stDmaInit.unPeriSel.stPeriSel.enPeriID = DMA_PERI_UART2_RX;
    stDmaInit.unCfg.u32DMACfg = DMA_INIT_PERI_TO_MEM_DEFAULT_CFG(UART_BUF_SIZE, DMA_DATA_1BYTE);

    rom_hw_dma_init(DMA6, &stDmaInit);
    rom_hw_dma_set_interrupt_channel(DMA6, DMA_INT7);
    rom_hw_dma_enable_interrupt(DMA6, DMA_INT_MSK);
    rom_hw_dma_enable(DMA6);

    // 3. UART TX DMA configuration
    stDmaInit.u32SrcAddr = (uint32_t)m_u8TxBuf;
    stDmaInit.u32DstAddr = (uint32_t)&UART2->UART_TX_FIFO;
    stDmaInit.unPeriSel.stPeriSel.enPeriID = DMA_PERI_UART2_TX,
    stDmaInit.unCfg.u32DMACfg = DMA_INIT_MEM_TO_PERI_DEFAULT_CFG(UART_BUF_SIZE, DMA_DATA_1BYTE);

    rom_hw_dma_init(DMA7, &stDmaInit);
    rom_hw_dma_interval_tx_mode_enable(DMA7);
    rom_hw_dma_set_interrupt_channel(DMA7, DMA_INT7);
    rom_hw_dma_enable_interrupt(DMA7, DMA_INT_MSK);
    rom_hw_dma_enable(DMA7);

    // 4. DMA int init
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, DMA_IRQ7);
    NVIC_ClearPendingIRQ(DMA_IRQ7);
    NVIC_SetPriority(DMA_IRQ7, 0x3);
    NVIC_EnableIRQ(DMA_IRQ7);
}

/**
 * @brief  UART transmit.
 */
static void uart_example_tx(void)
{
    uint8_t u8TxBuf[] = {"123456789"};

    uart_example_init();

    rom_hw_uart_send_byte(UART_HANDLE_EXAMPLE, '0');

    rom_hw_uart_transmit(UART_HANDLE_EXAMPLE, u8TxBuf, sizeof(u8TxBuf));
}

/**
 * @brief  UART receive by uart interrupt.
 */
static void uart_example_int_rx(void)
{
    uart_example_init();

    uart_example_int_init();
}

/**
 * @brief  UART transmit by dma.
 */
static void uart_example_dma_tx(void)
{
    uint16_t i;

    uart_example_init();

    uart_example_dma_init();

    for (i = 0; i < sizeof(m_u8TxBuf); i++)
    {
        m_u8TxBuf[i] = i & 0xFF;
    }

    i = 0;
    for (;;)
    {
        i += 16;
        rom_hw_dma_set_interval_tx_index(DMA7, (i % sizeof(m_u8TxBuf)));

        rom_delay_ms(1000);
    }
}

/**
 * @brief  UART receive by dma.
 */
static void uart_example_dma_rx(void)
{
    uart_example_init();

    uart_example_dma_init();
}

/**
 * @brief  UART module example code.
 */
static void uart_example(void)
{
    enUartExampleCase_t enCase = UART_EXAMPLE_TX;

    switch (enCase)
    {
        case UART_EXAMPLE_TX:
        {
            uart_example_tx();
            break;
        }
        case UART_EXAMPLE_INTERRUPT_RX:
        {
            uart_example_int_rx();
            break;
        }
        case UART_EXAMPLE_DMA_TX:
        {
            uart_example_dma_tx();
            break;
        }
        case UART_EXAMPLE_DMA_RX:
        {
            uart_example_dma_rx();
            break;
        }
        default: break;
    }
}

/**
 * @brief  UART example code main function.
 */
int main(void)
{
    // Disable watchdog timer.
    rom_hw_wdt_disable(WDT0);

    rom_delay_ms(100);

    system_power_init();
    system_clock_init(EN_SYS_CLK_DCXO16M);
    peripheral_init();

    uart_example();

    for (;;);

    return 0;
}


