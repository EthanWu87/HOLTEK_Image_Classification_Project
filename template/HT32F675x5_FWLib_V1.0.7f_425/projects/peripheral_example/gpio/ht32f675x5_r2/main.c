/*************************************************************************************************************
 * @file    main.c
 * @version V1.1
 * @date    2025-08-20
 * @brief   GPIO module example code.
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
#include "hw_pmu.h"
#include "hw_efuse.h"
#include "hw_gpio.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hal_pmu.h"

#include "app_cfg.h"
#include "boards.h"
#include "utility.h"
#include "app_debug.h"

/**
 * @brief  example case.
 */
typedef enum
{
    GPIO_EXAMPLE_INPUT     = 0x01,
    GPIO_EXAMPLE_OUTPUT    = 0x02,
    GPIO_EXAMPLE_INTERRUPT = 0x03,
    GPIO_EXAMPLE_SW_INPUT  = 0x04,
    GPIO_EXAMPLE_SW_OUTPUT = 0x05,

} enExampleCase_t;

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
    PRINTF("[%s T %s]GPIO example code start to work.\n", __DATE__, __TIME__);
#endif
}

/**
 * @brief  GPIO input example code. Read io status:
 *         Each bit of the return value represents the state of an IO,
 *         0: low level, 1: high level.
 * @param  enPullMode: Pin pull mode, @ref EN_GPIO_PULL_MODE_T.
 */
static void gpio_example_input(EN_GPIO_PULL_MODE_T enPullMode)
{
    uint32_t i;
    uint32_t u32Level = 0;

    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO, enPullMode);
    rom_hw_gpio_set_pin_input_output(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO, GPIO_MODE_INPUT);

    for (i = 0; i < 16; i++)
    {
        rom_hw_gpio_get_pin_input_level(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO, &u32Level);
        PRINTF("GPIO input level: %08X\n", u32Level);

        rom_delay_ms(1000);
    }
}

/**
 * @brief  GPIO output example code.
 *         Set and get indicated pin output level.
 * @param  enStrength: Pin drive strength, @ref EN_GPIO_DRIVE_STRENGTH_T.
 */
static void gpio_example_output(EN_GPIO_DRV_STRENGTH_T enStrength)
{
    uint32_t u32Level;

    rom_hw_gpio_set_pin_input_output(GPIO_PORT_LED2, GPIO_PIN_LED2, GPIO_MODE_OUTPUT);
    rom_hw_gpio_set_pin_drive_strength(GPIO_PORT_LED2, GPIO_PIN_LED2, enStrength);

    while(1)
       {
       	rom_hw_gpio_set_pin_output_level(GPIO_PORT_LED2, GPIO_PIN_LED2, 1);
       	rom_hw_gpio_get_pin_output_level(GPIO_PORT_LED2, GPIO_PIN_LED2, &u32Level);
       	PRINTF("(1) GPIO output level: %08X\n", u32Level);
       	rom_delay_ms(500);

       	rom_hw_gpio_set_pin_output_level(GPIO_PORT_LED2, GPIO_PIN_LED2, 0);
       	rom_hw_gpio_get_pin_output_level(GPIO_PORT_LED2, GPIO_PIN_LED2, &u32Level);
       	PRINTF("(2) GPIO output level: %08X\n", u32Level);
       	rom_delay_ms(500);
       }
}

/**
 * @brief  GPIO interrupt handler.
 */
__RAM_FUNC void GPIO_IRQ0_Handler(void)
{
    uint32_t u32Flag, u32Level;

    /* Get interrupt status */
    rom_hw_gpio_get_pin_interrupt_flag(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO, &u32Flag);
    rom_hw_gpio_clear_pin_interrupt_flag(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO);
    PRINTF("io int flag: %08X\n", u32Flag);

    rom_hw_gpio_get_pin_input_level(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO, &u32Level);
    PRINTF("io int level: %08X\n", u32Level);
}

/**
 * @brief  GPIO interrupt init.
 */
static void gpio_example_int_init(void)
{
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, GPIO_IRQ0);
    NVIC_ClearPendingIRQ(GPIO_IRQ0);
    NVIC_SetPriority(GPIO_IRQ0, 0x3);
    NVIC_EnableIRQ(GPIO_IRQ0);
}

/**
 * @brief  GPIO interrupt example code.
 * @param  enType: Interrupt type, @ref EN_GPIO_INT_TYPE_T.
 */
static void gpio_example_interrupt(EN_GPIO_INT_TYPE_T enType)
{
    rom_hw_gpio_set_pin_input_output(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO, GPIO_MODE_INPUT);

    if (GPIO_INT_HIGH_LEVEL == enType)
    {
        rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO, GPIO_PULL_DOWN);
    }
    else
    {
        rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO, GPIO_PULL_UP);
    }

    /* Configure for gpio interrupt */
    gpio_example_int_init();

    /* Initialize io to interrupt mode. */
    rom_hw_gpio_set_pin_interrupt_type(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO, GPIO_INT_CH0, enType);

    // Clear gpio interrupt flag.
    rom_hw_gpio_clear_pin_interrupt_flag(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO);

    /* Enable gpio interrupt */
    rom_hw_gpio_enable_pin_interrupt(GPIO_PORT_INPUT_IO, GPIO_PIN_INPUT_IO);
}

/**
 * @brief  GPIO SWD input example code.
 *
 * @details Read io status: Each bit of the return value represents the state of an IO,
 *          0: low level, 1: high level.
 */
static void gpio_example_swd_input(void)
{
    uint8_t i;
    uint8_t u8Level = 0;

    rom_hw_gpio_disable_swd(GPIO_SWD_CP);
    rom_hw_gpio_disable_swd(GPIO_SWD_MP);

    rom_hw_gpio_set_sw_input_output(GPIO_SWD_CP, GPIO_PIN_SWD_PINS, GPIO_MODE_INPUT);
    rom_hw_gpio_set_sw_input_output(GPIO_SWD_MP, GPIO_PIN_SWD_PINS, GPIO_MODE_INPUT);

    rom_hw_gpio_set_sw_pull_mode(GPIO_SWD_CP, GPIO_PIN_SWD_PINS, GPIO_PULL_DOWN);
    rom_hw_gpio_set_sw_pull_mode(GPIO_SWD_MP, GPIO_PIN_SWD_PINS, GPIO_PULL_DOWN);

    for (i = 0; i < 5; i++)
    {
        rom_hw_gpio_get_sw_input_level(GPIO_SWD_CP, GPIO_PIN_SWD_PINS, &u8Level);
        PRINTF("GPIO level(GPIO_SWD_CP): 0x%02X\n", u8Level);

        rom_hw_gpio_get_sw_input_level(GPIO_SWD_MP, GPIO_PIN_SWD_PINS, &u8Level);
        PRINTF("GPIO level(GPIO_SWD_MP): 0x%02X\n", u8Level);
        rom_delay_ms(1000);
    }

    rom_hw_gpio_enable_swd(GPIO_SWD_CP);
    rom_hw_gpio_enable_swd(GPIO_SWD_MP);
}

/**
 * @brief  GPIO SWD output example code.
 */
static void gpio_example_swd_output(void)
{
    uint8_t i;

    rom_hw_gpio_disable_swd(GPIO_SWD_CP);
    rom_hw_gpio_disable_swd(GPIO_SWD_MP);

    rom_hw_gpio_set_sw_input_output(GPIO_SWD_CP, GPIO_PIN_SWD_PINS, GPIO_MODE_OUTPUT);
    rom_hw_gpio_set_sw_input_output(GPIO_SWD_MP, GPIO_PIN_SWD_PINS, GPIO_MODE_OUTPUT);
    rom_hw_gpio_set_sw_drive_strength(GPIO_SWD_CP, GPIO_PIN_SWD_PINS, GPIO_DRV_STRENGTH_LEVEL1);
    rom_hw_gpio_set_sw_drive_strength(GPIO_SWD_MP, GPIO_PIN_SWD_PINS, GPIO_DRV_STRENGTH_LEVEL1);

    for (i = 0; i < 5; i++)
    {
        rom_hw_gpio_set_sw_output_level(GPIO_SWD_CP, GPIO_PIN_SWD_PINS, 0);
        rom_hw_gpio_set_sw_output_level(GPIO_SWD_MP, GPIO_PIN_SWD_PINS, 0);
        rom_delay_ms(1000);

        rom_hw_gpio_set_sw_output_level(GPIO_SWD_CP, GPIO_PIN_SWD_PINS, 1);
        rom_hw_gpio_set_sw_output_level(GPIO_SWD_MP, GPIO_PIN_SWD_PINS, 1);
        rom_delay_ms(1000);
    }
    rom_hw_gpio_set_sw_output_level(GPIO_SWD_CP, GPIO_PIN_SWD_PINS, 0);
    rom_hw_gpio_set_sw_output_level(GPIO_SWD_MP, GPIO_PIN_SWD_PINS, 0);

    rom_hw_gpio_enable_swd(GPIO_SWD_CP);
    rom_hw_gpio_enable_swd(GPIO_SWD_MP);
}

/**
 * @brief  GPIO module example code.
 */
static void gpio_example(void)
{
    switch (GPIO_EXAMPLE_OUTPUT)
    {
        case GPIO_EXAMPLE_INPUT:
        {
            // Pin pull mode, @ref EN_GPIO_PULL_MODE_T.
            gpio_example_input(GPIO_PULL_UP);
            break;
        }
        case GPIO_EXAMPLE_OUTPUT:
        {
            // Pin drive strength, @ref EN_GPIO_DRIVE_STRENGTH_T.
            gpio_example_output(GPIO_DRV_STRENGTH_LEVEL0);
            break;
        }
        case GPIO_EXAMPLE_INTERRUPT:
        {
            // Interrupt type, @ref EN_GPIO_INT_TYPE_T.
            gpio_example_interrupt(GPIO_INT_FALLING_EDGE);
            break;
        }
        case GPIO_EXAMPLE_SW_INPUT:
        {
            gpio_example_swd_input();
            break;
        }
        case GPIO_EXAMPLE_SW_OUTPUT:
        {
            gpio_example_swd_output();
            break;
        }
        default:
            break;
    }
}

/**
 * @brief  GPIO example code main function.
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

    gpio_example();

    for (;;);

    return 0;
}
