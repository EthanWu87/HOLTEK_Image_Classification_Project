/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2023-01-16
 * @brief   ADC module example code.
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

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "type_def.h"
#include "hw_crg.h"
#include "hw_pmu.h"
#include "hw_gpio.h"
#include "hw_adc.h"
#include "hw_audio.h"
#include "hw_dma.h"
#include "hw_efuse.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hal_adc.h"
#include "patch_hal_adc.h"
#include "hal_pmu.h"

#include "app_cfg.h"
#include "boards.h"
#include "type_def.h"

#include "utility.h"
#include "app_debug.h"

/**
 * @brief  DEFINE.
 */
#define ADC_SAMPLE_CHANNEL        (ADC_CH_2 | ADC_CH_3 | ADC_CH_5 | ADC_CH_VDDR)
#define ADC_SAMPLE_CHANNEL_COUNT  (4)   // 4 channels
#define ADC_SAMPLE_NUMBER_FOR_DMA (100) // 100 sample count each channel
#define ADC_SAMPLE_BUF_SIZE       (ADC_SAMPLE_CHANNEL_COUNT * ADC_SAMPLE_NUMBER_FOR_DMA)

/**
 * @brief  example case.
 */
typedef enum
{
    ADC_SAMPLE_BY_SW_TRIG  = 0x01,
    ADC_SAMPLE_BY_DMA_MODE = 0x02,

} enExampleCase_t;

/**
 * @brief  LOCAL VARIABLES.
 */
static uint32_t m_au32ADCSampleTmpBuf[HT32_ADC_SAMPLE_BUF_SIZE(ADC_SAMPLE_CHANNEL_COUNT, ADC_SAMPLE_NUMBER_FOR_DMA)];
static uint16_t m_au16ADCSampleDataBuf[ADC_SAMPLE_BUF_SIZE];

// ADC Init Handle
static stADCInitHandle_t m_stADCInitHandle;

/**
 * @brief  LOCAL FUNCTION.
 */
static void adc_example_dma_init(void);

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
    PRINTF("[%s T %s]ADC example code start to work.\n", __DATE__, __TIME__);
#endif
}

/**
 * @brief  adc init.
 * @param  enMode: adc sample mode, @ref EN_ADC_SAMP_MODE_SEL_T.
 */
static void adc_example_init(EN_ADC_SAMP_MODE_SEL_T enSampleMode)
{
    // PA21 - ADC0_CH2, PA22 - ADC0_CH3, PB1 - ADC0_CH5
    rom_hw_gpio_set_pin_pull_mode(GPIOA, GPIO_PIN_21 | GPIO_PIN_22, GPIO_PULL_NONE);
    rom_hw_gpio_set_pin_pull_mode(GPIOB, GPIO_PIN_1, GPIO_PULL_NONE);

    // 1. Parameter Init.
    m_stADCInitHandle.pstADCHandle = ADC0;
    m_stADCInitHandle.u8Resolution = ADC_RESOLUTION_10BIT;
    m_stADCInitHandle.enCh         = ADC_SAMPLE_CHANNEL;
    m_stADCInitHandle.enSampMode   = enSampleMode;
    m_stADCInitHandle.enSampSrc    = 0;
    m_stADCInitHandle.enPwmSampSrc = 0;

    // 2. Init ADC in DMA mode if needed.
    if (m_stADCInitHandle.enSampMode == ADC_SAMP_BY_AUTO_TRIG)
    {
        adc_example_dma_init();
    }

    // 3. Init ADC and enable adc sample.
    patch_hal_adc_init(&m_stADCInitHandle, HT32_ADC_SAMPLE_NUMBER_FOR_DMA(ADC_SAMPLE_NUMBER_FOR_DMA));
}

/**
 * @brief  ADC example code - sample by software trigger.
 */
static void adc_example_read_by_sw_trig(void)
{
    uint16_t u16Voltage = 0;

    PRINTF("\n");

    if (ERR_STA_OK == patch_hal_adc_get_voltage(&m_stADCInitHandle, ADC_CH_2, &u16Voltage))
    {
        PRINTF("ADC0 CH2 Volt   : %dmV\n", u16Voltage);
    }

    if (ERR_STA_OK == patch_hal_adc_get_voltage(&m_stADCInitHandle, ADC_CH_3, &u16Voltage))
    {
        PRINTF("ADC0 CH3 Volt   : %dmV\n", u16Voltage);
    }

    if (ERR_STA_OK == patch_hal_adc_get_voltage(&m_stADCInitHandle, ADC_CH_5, &u16Voltage))
    {
        PRINTF("ADC0 CH5 Volt   : %dmV\n", u16Voltage);
    }

    if (ERR_STA_OK == patch_hal_adc_get_voltage(&m_stADCInitHandle, ADC_CH_VDDR, &u16Voltage))
    {
        PRINTF("ADC0 CHVDDR Volt: %dmV\n", u16Voltage);
    }
}

/**
 * @brief  DMA irq handler.
 */
__RAM_FUNC void DMA_IRQ0_Handler(void)
{
    uint8_t u8IntFlag;

    rom_hw_dma_get_interrupt_flag(DMA0, &u8IntFlag);
    rom_hw_dma_clear_interrupt_flag(DMA0, u8IntFlag);

    if (u8IntFlag & DMA_INT_4_4_DONE)
    {
        rom_hal_adc_read_dma_data(&m_stADCInitHandle, ADC_SAMPLE_CHANNEL_COUNT, ADC_SAMPLE_NUMBER_FOR_DMA,
                                  m_au32ADCSampleTmpBuf, m_au16ADCSampleDataBuf);
    }

    // print adc data
    {
        uint16_t i;
        for (i = 0; i < sizeof(m_au16ADCSampleDataBuf) / UINT16_BYTES; i++)
        {
            PRINTF("%d ", m_au16ADCSampleDataBuf[i]);
        }
		PRINTF("\r\n");
    }
}

/**
 * @brief  DMA init for ADC.
 */
static void adc_example_dma_init(void)
{
    // 1. Turn DMA clock gating on.
    rom_hw_crg_enable_clk_gate(CRG_DMA_CLK_GATE);

    // 2. Enable DMA Interrupt.
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, DMA_IRQ0);
    NVIC_ClearPendingIRQ(DMA_IRQ0);
    NVIC_SetPriority(DMA_IRQ0, 0x03);
    NVIC_EnableIRQ(DMA_IRQ0);

    // 3. ADC RX DMA configuration.
    stDmaInit_t stDmaInit = {
        .u32SrcAddr                   = (uint32_t) & (ADC0->ADC_RX_FIFO),
        .u32DstAddr                   = (uint32_t)m_au32ADCSampleTmpBuf,
        .u32TimeOut                   = 1000,
        .unPeriSel.stPeriSel.enPeriID = DMA_PERI_ADC0_RX,
        .unCfg.u32DMACfg =
            DMA_INIT_PERI_TO_MEM_DEFAULT_CFG(sizeof(m_au32ADCSampleTmpBuf) / UINT32_BYTES, DMA_DATA_4BYTES),
    };

    rom_hw_dma_init(DMA0, &stDmaInit);
    rom_hw_dma_set_interrupt_channel(DMA0, DMA_INT0);
    rom_hw_dma_enable_interrupt(DMA0, DMA_INT_4_4_DONE);
    rom_hw_dma_enable(DMA0);
}

/**
 * @brief  ADC module example code.
 */
static void adc_example(void)
{
    uint8_t u8Case = ADC_SAMPLE_BY_SW_TRIG;

    switch (u8Case)
    {
        case ADC_SAMPLE_BY_SW_TRIG:
        {
            adc_example_init(ADC_SAMP_BY_SW_TRIG);

            for (;;)
            {
                adc_example_read_by_sw_trig();
                rom_delay_ms(1000);
            }
            break;
        }
        case ADC_SAMPLE_BY_DMA_MODE:
        {
            adc_example_init(ADC_SAMP_BY_AUTO_TRIG);
            break;
        }
        default:
            break;
    }
}


/**
 * @brief  ADC example code main function.
 * @return 0.
 */
int main(void)
{
    // Disable watchdog timer.
    rom_hw_wdt_disable(WDT0);

    rom_delay_ms(100);

    system_power_init();
    system_clock_init(EN_SYS_CLK_DCXO16M);
    peripheral_init();
	
    adc_example();

    for (;;)
        ;

    return 0;
}
