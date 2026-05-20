/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2022-10-31
 * @brief   usb device hid example code.
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
#include "hw_crg.h"
#include "hw_pmu.h"
#include "hw_efuse.h"
#include "hw_gpio.h"
#include "hw_stim.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hal_pmu.h"
#include "patch_hal_pmu.h"

#include "app_cfg.h"
#include "type_def.h"
#include "boards.h"

#include "rand.h"
#include "utility.h"
#include "lpwr_ctrl.h"

#include "app_debug.h"

#include "usbd_init.h"

/**
 * @brief  System power manage.
 * @param  enSel: Select DCDC or LDO, @ref EN_PMU_POWER_SEL_T.
 */
static void system_power_init(EN_PMU_PWR_SEL_T enSel)
{
    // Set ldo_act voltage.
    rom_hw_pmu_set_ldo_act_voltage(EN_LDO_ACT_1200mV);

    // Init dcdc configuration and set dcdc_act voltage.
    rom_hw_pmu_dcdc_init();
    rom_hw_pmu_set_dcdc_act_voltage(EN_DCDC_ACT_VOLT_1200mV);

    // Set ldo_dig and ldo_ret voltage.
    rom_hw_pmu_set_ldo_dig_voltage(EN_LDO_DIG_1100mV);
    rom_hw_pmu_set_ldo_ret_sleep_voltage(EN_LDO_RET_1100mV);

    // Power selection. It will be valid after the system gets into sleep, default is ldo mode.
    rom_hal_pmu_sel_power_act_out_mode(enSel);
}

/**
 * @brief  System clock init.
 * @param  enSrc: System clock source selection, @ref EN_SYS_CLK_SRC_SEL_T.
 * @param  enSrc: LPWR_CLK source sel, @ref EN_LPWR_CLK_SRC_T.
 */
static void system_clock_init(EN_SYS_CLK_SRC_SEL_T enSysClkSrc, EN_LPWR_CLK_SRC_T enLpwrClkSrc)
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

    /* Low power clock */
    rom_hw_crg_enable_clk_gate(CRG_RTC_APB_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_RTC_RC_LCLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_AHB4_CLK_GATE);
    
    rom_hal_pmu_cfg_dcxo_lclk_param(DCXO_LCLK_BUF_3, DCXO_LCLK_IB_3, DCXO_LCLK_NGM_3, DCXO_LCLK_CAP_6PF);
    
    rom_hal_pmu_set_lpwr_clk_src(enLpwrClkSrc, DCXO_LCLK_STABLE_TIME_1000MS);
    
    rom_hw_crg_enable_clk_gate(CRG_USB_CLK_GATE);
}

/**
 * @brief  All peripheral init.
 */
static void peripheral_init(void)
{
    rom_rand_init(33);

    /* Disable MP all Peripheral interrupt. */
    rom_hw_sys_ctrl_peri_int_ctrl(SYS_CTRL_MP, 0, 0);

#if APP_DEBUG_ENABLED
    app_debug_init(GPIO_PORT_APP_DEBUG_TX, GPIO_PIN_APP_DEBUG_TX, UART_HANDLE_APP_DEBUG, UART_BPS_APP_DEBUG, NULL);
    PRINTF("[%s T %s]System usb hid example code start to work.\n", __DATE__, __TIME__);
#endif

    // System wakeup pin init
    rom_hw_gpio_set_pin_input_output(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP, GPIO_MODE_INPUT);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP, GPIO_PULL_UP);
}

/**
 * @brief  PMU IRQ Handler.
 */
void PMU_IRQ_Handler(void)
{
    uint32_t u32IntFlag;

    rom_hw_pmu_get_interrupt_flag(&u32IntFlag);
    rom_hw_pmu_clear_interrupt_flag(u32IntFlag);

    PRINTF("PMU INT: %04X\n", u32IntFlag);
}

/**
 * @brief  Check if the system can enter sleep.
 * @return false(0) - System can not goto sleep.
 * @return true(1)  - System can goto sleep.
 */
static bool lpwr_before_sleep(void)
{
    uint32_t u32Level;

    rom_hw_gpio_get_pin_input_level(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP, &u32Level);

    // If wakeup pin is low level, system can not goto sleep
    if (0 == (GPIO_PIN_WAKEUP & u32Level))
    {
        return false;
    }

    rom_delay_us(20);

    return true;
}

/**
 * @brief  CPU after wakeup from sleep functoin.
 */
static void lpwr_after_wakeup(void)
{
#if APP_DEBUG_ENABLED
    app_debug_reinit();

#endif
}

/**
 * @brief  Low power init.
 * @param  enMode: System work mode, @ref EN_LPWR_MODE_SEL_T.
 */
static void system_lpwr_init(EN_LPWR_MODE_SEL_T enMode)
{
    lpwr_ctrl_init(enMode, lpwr_before_sleep, lpwr_after_wakeup);
    patch_hal_pmu_set_sram_ret(RAM_APP_SIZE_KBYTE_MAX);
}

/**
 * @brief  stim0 channel 0 irq handler.
 */
__RAM_FUNC void STIM0_IRQ0_Handler(void)
{
    //uint32_t u32Count; // GNU Warning Issue
    uint16_t u16Flag;

    /* Get stim0 channel 0 interrupt flag and clear it. */
    rom_hw_stim_get_interrupt_flag(STIM0, &u16Flag);
    rom_hw_stim_clear_interrupt_flag(STIM0, u16Flag);
    
    rom_hw_stim_stop(STIM0);
}

/**
 * @brief  stim wakeup init.
 */
static void wakeup_stim_init()
{
    // Enable stim0 module clock gate.
    rom_hw_crg_enable_clk_gate(CRG_STIM0_CLK_GATE);

    // Set stim prescale to 0(default).
    rom_hw_stim_set_prescale(STIM0, 0);

    // Configuration stim0 ch0 peripheral int
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, STIM0_IRQ0);
    NVIC_ClearPendingIRQ(STIM0_IRQ0);
    NVIC_SetPriority(STIM0_IRQ0, 3);
    NVIC_EnableIRQ(STIM0_IRQ0);

    // Configure stim0 ch0 interrupt and compare value.
    rom_hw_stim_disable_wakeup(STIM0, STIM_INT_WAKEUP_EN_MASK);
    rom_hw_stim_disable_interrupt(STIM0, STIM_INT_MASK);
    rom_hw_stim_enable_interrupt(STIM0, STIM_CH0_INT_MATCH);
    rom_hw_stim_enable_wakeup(STIM0, STIM_CH0_INT_MATCH_WAKEUP);
    rom_hw_stim_set_compare(STIM0, STIM_CH0, TIME_MS_TO_32K_CNT(100));

    // Configure pmu wakeup source
    rom_hw_pmu_set_wakeup_source(LUT_INDEX_STIM_WAKEUP, LUT_TRIG_ID_OTHER, LUT_TRIG_ID_STIM0_CH0, LUT_ACT_WAKEUP);

    // Start stim0 counter.
    rom_hw_stim_start(STIM0);
}

/**
 * @brief  gpio irq handler.
 */
__RAM_FUNC void GPIO_IRQ0_Handler(void)
{
    uint32_t u32Flag;
    uint32_t u32Level;

    /* Get interrupt status */
    rom_hw_gpio_get_pin_interrupt_flag(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP, &u32Flag);
    rom_hw_gpio_clear_pin_interrupt_flag(GPIO_PORT_WAKEUP, u32Flag);
    rom_hw_gpio_clear_wakeup_flag();

    rom_delay_us(100);

    rom_hw_gpio_get_pin_input_level(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP, &u32Level);
    PRINTF("io int: %08X, %08X\n", u32Flag, u32Level);
}

/**
 * @brief  gpio wakeup init.
 */
static void key_gpio_init(void)
{
    // Config gpio irq0 peripheral int
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, GPIO_IRQ0);
    NVIC_ClearPendingIRQ(GPIO_IRQ0);
    NVIC_SetPriority(GPIO_IRQ0, 3);
    NVIC_EnableIRQ(GPIO_IRQ0);

    // Configure gpio input and interrupt
    rom_hw_gpio_set_pin_input_output(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP, GPIO_MODE_INPUT);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP, GPIO_PULL_UP);
    rom_hw_gpio_set_pin_interrupt_type(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP, GPIO_INT_CH0, GPIO_INT_FALLING_EDGE);
    rom_hw_gpio_clear_pin_interrupt_flag(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP);
    rom_hw_gpio_enable_pin_interrupt(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP);

    rom_hw_gpio_set_pin_wakeup_debounce(1, GPIO_WAKEUP_DEB_UNIT_30US);
    rom_hw_gpio_enable_pin_wakeup(GPIO_PORT_WAKEUP, GPIO_PIN_WAKEUP, GPIO_WAKEUP_LOW_LEVEL);

    // GPIO wakeup with debounce
    rom_hw_pmu_set_wakeup_source(LUT_INDEX_GPIO_WAKEUP, LUT_TRIG_ID_OTHER, LUT_TRIG_ID_GPIO, LUT_ACT_WAKEUP);
}


/**
 * @brief  Main Function.
 * @return 0.
 */
int main(void)
{
    // Disable watchdog timer.
    rom_hw_wdt_disable(WDT0);

    rom_delay_ms(1000);

    system_power_init(PWR_SEL_DCDC);
    system_clock_init(EN_SYS_CLK_DCXO16M, LPWR_CLK_RC_LCLK);
    peripheral_init();
    system_lpwr_init(LPWR_MODE_SLEEP);

    wakeup_stim_init();
    key_gpio_init();
    lpwr_ctrl_goto_sleep();
    
    usb_device_init();

    for (;;)
    {
        
    }

    return 0;
}
