/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2023-06-19
 * @brief   TRNG module example code.
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
#include "hw_dma.h"
#include "hw_efuse.h"
#include "hw_gpio.h"
#include "hw_sys_ctrl.h"
#include "hw_trng.h"
#include "hw_uart.h"
#include "hw_wdt.h"
#include "hal_pmu.h"

#include "app_cfg.h"
#include "type_def.h"
#include "boards.h"

#include "utility.h"
#include "app_debug.h"

/**
 * @brief  Macro definition.
 */
#define TRNG_BUF_SIZE                     (32 * 1024)

// ./assess.exe 1000000
// bitstreams 100
#define TRNG_NIST_SP800_22_TEST_DATA_SIZE (12 * 1024 * 1024) // 12MBytes

/**
 * @brief  Enumeration.
 */
typedef enum
{
    TRNG_EXAMPLE_SAMPLE        = 0x00,
    TRNG_EXAMPLE_NIST_SP800_22 = 0x01,

} enTrngExampleCase_t;

/**
 * @brief  Local variables.
 */
static uint8_t  m_u8TrngBuf[TRNG_BUF_SIZE] __ALIGNED(4);
static uint32_t m_u32NistTestDataCnt = 0;

/**
 * @brief  System power manage.
 */
static void system_power_init(void)
{
    rom_hw_pmu_set_ldo_act_voltage(EN_LDO_ACT_1200mV);
    rom_hw_pmu_set_ldo_dig_voltage(EN_LDO_DIG_1100mV);
    rom_hw_pmu_set_ldo_ret_sleep_voltage(EN_LDO_RET_1100mV);

    // Power selection
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
    PRINTF("[%s T %s]TRNG example code start to work.\n", __DATE__, __TIME__);
#endif
}

/**
 * @brief  trng sample example.
 */
static void trng_example_sample(void)
{
    uint8_t  u8TrngBuf[TRNG_8BIT_DATA_LEN];
    uint32_t u32Trng = 0;

    // Enable clock gate.
    rom_hw_crg_enable_clk_gate(CRG_AHB4_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_TRNG_CLK_GATE);

    // Trng init.
    stTrngInit_t stTrngInit = {
        .u32SampleCnt = TRNG_SAMPLE_CNT_CFG,
        .bDmaEn       = DISABLE,
        .u8BypassCtrl = TRNG_BYPASS_CTRL_CFG,
        .u8Level      = TRNG_LEVEL_CFG,
        .enSrcEn      = EN_TRNG_SRC_ALL_CH,
    };
    rom_hw_trng_init(&stTrngInit);

    while (1)
    {
        // Get 32bit trng data.
        rom_hw_trng_get_random((uint8_t *)&u32Trng, sizeof(u32Trng));
        PRINTF("TRNG: %08X\n", u32Trng);

        // Get 24Bytes trng data.
        rom_hw_trng_get_random(u8TrngBuf, sizeof(u8TrngBuf));
        PRINTF("TRNG: ");
        for (uint8_t i = 0; i < sizeof(u8TrngBuf); i++)
        {
            PRINTF("%02X ", u8TrngBuf[i]);
        }
        PRINTF("\n");

        rom_delay_ms(1000);
    }
}

/**
 * @brief  DMA IRQ7 Handler.
 */
__RAM_FUNC void DMA_IRQ7_Handler(void)
{
    uint8_t u8IntFlag = 0;

    // Disable dma first.
    rom_hw_dma_disable(DMA7);

    // Read and clear dma interrupt flag.
    rom_hw_dma_get_interrupt_flag(DMA7, &u8IntFlag);
    rom_hw_dma_clear_interrupt_flag(DMA7, u8IntFlag);

    // Start to send trng data through uart module.
    rom_hw_uart_transmit(UART_HANDLE_TRNG_TEST, m_u8TrngBuf, sizeof(m_u8TrngBuf));

    m_u32NistTestDataCnt += sizeof(m_u8TrngBuf);

    if (m_u32NistTestDataCnt <= TRNG_NIST_SP800_22_TEST_DATA_SIZE)
    {
        rom_hw_dma_enable(DMA7);
    }

    PRINTF("TRNG NIST SP800-22 test progress: %02d%%\n",
           m_u32NistTestDataCnt * 100 / TRNG_NIST_SP800_22_TEST_DATA_SIZE);
}

/**
 * @brief  trng NIST SP800-22 randomness test.
 */
static void trng_example_nist_sp800_22(void)
{
    m_u32NistTestDataCnt = 0;

    // trng
    // 1. Turn trng clock gating on.
    rom_hw_crg_enable_clk_gate(CRG_AHB4_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_TRNG_CLK_GATE);

    // 2. Trng init.
    stTrngInit_t stTrngInit = {
        .u32SampleCnt = TRNG_SAMPLE_CNT_CFG,
        .bDmaEn       = ENABLE,
        .u8BypassCtrl = TRNG_BYPASS_CTRL_CFG,
        .u8Level      = TRNG_LEVEL_CFG,
        .enSrcEn      = EN_TRNG_SRC_ALL_CH,
    };
    rom_hw_trng_init(&stTrngInit);

    // uart
    // 3. Turn uart clock gating on.
    rom_hw_crg_enable_clk_gate(CRG_UART1_CLK_GATE);

    // 4. Configure uart gpio
    rom_hw_gpio_set_pin_pid(GPIO_PORT_TRNG_TEST_TX, GPIO_PIN_TRNG_TEST_TX, PID_UART1_TXD);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_TRNG_TEST_TX, GPIO_PIN_TRNG_TEST_TX, GPIO_PULL_UP);

    // 5. uart init
    stUartInit_t stUartInit = {
        .u32UartBaudRate = UART_BPS_TRNG_TEST,
        .unUartCfg.u32UartCfg = UART_INIT_DEFAULT(UART_PARITY_NONE),
    };
    rom_hw_uart_init(UART_HANDLE_TRNG_TEST, &stUartInit);

    // dma
    // 6. Turn DMA clock gating on.
    rom_hw_crg_enable_clk_gate(CRG_DMA_CLK_GATE);

    // 7. Trng dma int init
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, DMA_IRQ7);
    NVIC_ClearPendingIRQ(DMA_IRQ7);
    NVIC_SetPriority(DMA_IRQ7, 0x3);
    NVIC_EnableIRQ(DMA_IRQ7);

    // 8. Trng dma configuration
    stDmaInit_t stDmaInit = {
        .u32SrcAddr                   = (uint32_t)&TRNG->TRNG_RX_FIFO,
        .u32DstAddr                   = (uint32_t)m_u8TrngBuf,
        .u32TimeOut                   = 1000,
        .unPeriSel.stPeriSel.enPeriID = DMA_PERI_TRNG_RX,
        .unCfg.u32DMACfg              = DMA_INIT_PERI_TO_MEM_DEFAULT_CFG(TRNG_BUF_SIZE / 4, DMA_DATA_4BYTES),
    };
    stDmaInit.unCfg.stDmaCfg.u8StopCfg = true;

    rom_hw_dma_init(DMA7, &stDmaInit);
    // rom_hw_dma_set_circ_total_len(DMA7, TRNG_BUF_SIZE);
    rom_hw_dma_set_interrupt_channel(DMA7, DMA_INT7);
    rom_hw_dma_enable_interrupt(DMA7, DMA_INT_4_4_DONE);

    // 9. Start to transmit trng data.
    rom_hw_dma_enable(DMA7);
}

/**
 * @brief  trng example.
 */
static void trng_example(void)
{
    uint8_t u8Case = TRNG_EXAMPLE_SAMPLE;

    switch (u8Case)
    {
        case TRNG_EXAMPLE_SAMPLE:
        {
            trng_example_sample();
            break;
        }
        // It takes about 12 minutes.
        case TRNG_EXAMPLE_NIST_SP800_22:
        {
            trng_example_nist_sp800_22();
            break;
        }
    }
}

/**
 * @brief  trng example code main function.
 */
int main(void)
{
    // Disable watchdog timer.
    rom_hw_wdt_disable(WDT0);

    rom_delay_ms(100);

    system_power_init();
    system_clock_init(EN_SYS_CLK_DCXO16M);
    peripheral_init();

    trng_example();

    for (;;);

    return 0;
}
