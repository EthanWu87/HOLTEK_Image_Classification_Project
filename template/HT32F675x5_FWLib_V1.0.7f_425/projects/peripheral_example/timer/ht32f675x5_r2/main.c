/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2022-03-26
 * @brief   timer example code.
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
#include "hw_sys_ctrl.h"
#include "hw_timer.h"
#include "hw_wdt.h"
#include "hal_timer.h"
#include "patch_hal_timer.h"
#include "hal_pmu.h"

#include "app_cfg.h"
#include "type_def.h"
#include "boards.h"

#include "utility.h"
#include "app_debug.h"


//=====================================================================================================================
// TYPEDEFS
//=====================================================================================================================
typedef enum
{
    TIMER_EXAMPLE_TIMER         = 0x01,
    TIMER_EXAMPLE_PWM           = 0x02,
    TIMER_EXAMPLE_CLK_BY_GPIO   = 0x03,

} enTimerExampleCase_t;

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

    PRINTF("Timer example code start to work.\n");
#endif
}

/**
 * @brief  TIMER0 irq handler.
 */
__RAM_FUNC void TIMER0_IRQ_Handler(void)
{
    uint32_t u32IntFlag = 0;

    rom_hw_gpio_toggle_pin_output_level(GPIO_PORT_TIMER, GPIO_PIN_TIMER);

    rom_hw_timer_get_interrupt_flag(TIMER0, TIMER_CHA, &u32IntFlag );
    rom_hw_timer_clear_interrupt_flag(TIMER0, TIMER_CHA, u32IntFlag );

    rom_hw_timer_clear_counter(TIMER0, TIMER_CHA);
}

/**
 * @brief  Timer example code - gptimer.
 */
static void timer_example_gptimer(void)
{
    // GPIO Init.
    rom_hw_gpio_set_pin_input_output(GPIO_PORT_TIMER, GPIO_PIN_TIMER, GPIO_MODE_OUTPUT);
    rom_hw_gpio_set_pin_output_level(GPIO_PORT_TIMER, GPIO_PIN_TIMER, GPIO_LEVEL_LO);

    stTimerInit_t stTimerInit =
    {
        .u8Prescale = 15,
        .u32Compare = 1000, // 1ms
        .u8CounterMode = TIMER_CNT_MODE_CONTINU,
    };

    NVIC_ClearPendingIRQ(TIMER0_IRQ);
    NVIC_SetPriority(TIMER0_IRQ, 0x3);
    NVIC_EnableIRQ(TIMER0_IRQ);
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, TIMER0_IRQ);

    rom_hal_timer_init(TIMER0, TIMER_CHA, &stTimerInit);
    rom_hw_timer_enable_interrupt(TIMER0, TIMER_CHA, TIMER_INT_MATCH);
    rom_hw_timer_start(TIMER0, TIMER_CHA);
}

/**
 * @brief  Timer example code - pwm.
 */
static void timer_example_pwm(uint32_t u32Freq,uint16_t u16Duty)
{
    // GPIO Init.
    rom_hw_gpio_set_pin_pid(GPIO_PORT_PWM, GPIO_PIN_PWM, PID_GTIM_PWM1_CHA);

    patch_hal_timer_pwm_init(TIMER1, TIMER_CHA, u32Freq, u16Duty);
    rom_hal_timer_enable_pwm(TIMER1, TIMER_CHA);
    rom_hw_timer_start(TIMER1, TIMER_CHA);
}


/**
 * @brief  Timer example code - by gpio.
 */
static void timer_example_by_gpio(void)
{
    //EN_ERR_STA_T enRet; // GNU Warning Issue
    rom_hw_gpio_set_pin_input_output(GPIO_PORT_TIMER, GPIO_PIN_TIMER, GPIO_MODE_OUTPUT);
    rom_hw_gpio_set_pin_output_level(GPIO_PORT_TIMER, GPIO_PIN_TIMER, GPIO_LEVEL_LO);
    
    NVIC_ClearPendingIRQ(TIMER0_IRQ);
    NVIC_SetPriority(TIMER0_IRQ, 0x3);
    NVIC_EnableIRQ(TIMER0_IRQ);
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, TIMER0_IRQ);
    
    rom_hw_gpio_set_pin_input_output(GPIO_PORT_TIMER_CLK_IN,GPIO_PIN_TIMER_CLK_IN,GPIO_MODE_INPUT);
    rom_hw_gpio_set_pin_pid(GPIO_PORT_TIMER_CLK_IN,GPIO_PIN_TIMER_CLK_IN,PID_GTIM0_CLK_IN);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_TIMER_CLK_IN,GPIO_PIN_TIMER_CLK_IN,GPIO_PULL_NONE);

    stTimerInit_t stTimerInit = {
        .u8Prescale = 15,
        .u32Compare = 1000,
        .u8CounterMode = TIMER_CNT_MODE_CONTINU
    };

    rom_hal_timer_init(TIMER0,TIMER_CHAB,&stTimerInit);

    // Must change gtim clk src after timer init
    rom_hw_crg_set_gtim_clk_src(CRG_GTIM0,GTIM_CLK_SRC_GPIO_INPUT);
    
    rom_hw_timer_enable_interrupt(TIMER0, TIMER_CHAB, TIMER_INT_MATCH);

    rom_hw_timer_start(TIMER0, TIMER_CHAB);
}

/**
 * @brief  Timer example code.
 */
static void timer_example(void)
{
    switch (TIMER_EXAMPLE_PWM)
    {
        case TIMER_EXAMPLE_TIMER:
        {
            timer_example_gptimer();
            break;
        }
        case TIMER_EXAMPLE_PWM:
        {
            // 2KHz Duty : %34.56
            timer_example_pwm(2000,3456);
            break;
        }
        case TIMER_EXAMPLE_CLK_BY_GPIO:
        {
            // Set gpio clk src output
            rom_hw_gpio_set_pin_pull_mode(GPIOA, GPIO_PIN_29, GPIO_PULL_NONE);
            rom_hw_gpio_set_pin_pid(GPIOA, GPIO_PIN_29, PID_ANA_OUT_CLK);
            rom_hw_crg_enable_clk_gate(CRG_ANA_OUT_CLK_GATE);
            rom_hw_crg_set_ana_output_clk_src(ANA_OUT_CLK_SYS_CLK);

            timer_example_by_gpio();
            break;
        }
        default: break;
    }
}

/**
 * @brief  Timer example code main function
 */
int main(void)
{
    // Disable watchdog timer.
    rom_hw_wdt_disable(WDT0);

    rom_delay_ms(100);

    system_power_init();
    // EN_SYS_CLK_DCXO16M EN_SYS_CLK_PLL64M
    system_clock_init(EN_SYS_CLK_PLL64M);
    peripheral_init();

    timer_example();

    for (;;);

    return 0;
}


