/*************************************************************************************************************
 * @file    main.c
 * @version V1.1
 * @date    2022-02-10
 * @brief   ble hrs mp app main file
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
#include "hw_efuse.h"
#include "hw_crg.h"
#include "hw_gpio.h"
#include "hw_pmu.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hal_pmu.h"
#include "patch_hal_pmu.h"

#include "app_cfg.h"
#include "boards.h"
#include "lpwr_ctrl.h"
#include "utility.h"

#include "app_debug.h"
#include "err_debug.h"

/**
 * @brief  System power manage.
 * @param  enSel: Select DCDC or LDO, @ref EN_PMU_POWER_SEL_T.
 */
static void system_power_init(EN_PMU_PWR_SEL_T enSel)
{
    if (enSel == PWR_SEL_LDO)
    {
        rom_hw_pmu_set_ldo_act_voltage(EN_LDO_ACT_1200mV);
        rom_hw_pmu_set_ldo_dig_voltage(EN_LDO_DIG_1100mV);
        rom_hw_pmu_set_ldo_ret_sleep_voltage(EN_LDO_RET_1100mV);
    }
    else
    {
        rom_hw_pmu_dcdc_init();
        rom_hw_pmu_set_dcdc_act_voltage(EN_DCDC_ACT_VOLT_1200mV);
        rom_hw_pmu_set_ldo_dig_voltage(EN_LDO_DIG_1100mV);
        rom_hw_pmu_set_dcdc_ret_voltage(EN_DCDC_LPWR_VOLT_1050mV);
        rom_hw_pmu_set_dcdc_ret_clk_divisor(EN_DCDC_LPWR_CLK_1K);
        rom_hw_pmu_enable_dcdc_ret_output();
    }
    // Power Selection
    rom_hal_pmu_sel_power_act_out_mode(enSel);
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
    app_debug_init(GPIO_PORT_MP_APP_DEBUG_TX, GPIO_PIN_MP_APP_DEBUG_TX, UART_HANDLE_MP_APP_DEBUG, UART_BPS_MP_APP_DEBUG,
                   NULL);
    PRINTF("[%s T %s]ble peripheral project(mp) start to work.\n", __DATE__, __TIME__);
#endif

    err_debug_init();
}

/**
 * @brief  Enable CM0P. Remap cm0p, release cm0p reset signal.
 */
static void system_enable_cp(void)
{
    rom_hw_crg_keep_reset(CRG_CP_SW_RST);

    if (ERR_STA_OK == rom_hw_sys_ctrl_enable_cp_remap(ROM_CP_STARTUP_CODE_ADDR, ROM_CP_STARTUP_CODE_SIZE_MAX))
    {
        rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_REMAP_ADDR, (*(volatile uint32_t *)((RAM_CP_ADDR + 4))));

        rom_hw_crg_enable_clk_gate(CRG_CP_CLK_GATE);
        rom_hw_crg_enable_clk_gate(CRG_CP_DAP_CLK_GATE);
        rom_hw_crg_release_reset(CRG_CP_SW_RST);
    }
}

/**
 * @brief  Check if the system can enter sleep
 * @return false(0) - System can not goto sleep.
 * @return true(1)  - System can goto sleep.
 */
static bool lpwr_before_sleep(void)
{
    return true;
}

/**
 * @brief  CPU after wakeup from sleep func.
 */
static void lpwr_after_wakeup(void)
{
// System clock need configure to pll64m
#if SYSTEM_CLOCK_PLL64M_ENABLED
    uint32_t u32Value = 0;
    uint32_t u32Time  = 0;
    do
    {
        u32Time = lpwr_ctrl_get_ble_remain_sleep_time_us();
        rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_CP_WFI_FLAG, &u32Value);
    } while ((u32Time <= DCXO_HCLK_STABLE_TIME) || (0 == u32Value));

    rom_hal_pmu_set_sys_clk_src(EN_SYS_CLK_PLL64M, DCXO_HCLK_STABLE_TIME_2500US);
#endif

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
    patch_hal_pmu_set_sram_ret(RAM_APP_SIZE_KBYTE_MAX);
    lpwr_ctrl_init(enMode, lpwr_before_sleep, lpwr_after_wakeup);
}


/**
 * @brief  main function.
 * @return 0.
 */
int main(void)
{
    // Disable watchdog timer.
    rom_hw_wdt_disable(WDT0);

    rom_delay_ms(100);

    system_power_init(PWR_SEL_LDO);
    system_clock_init(EN_SYS_CLK_DCXO16M);
    peripheral_init();
    
    system_lpwr_init(LPWR_MODE_SLEEP);
    system_enable_cp();
    
    for (;;)
    {
        lpwr_ctrl_goto_sleep();
    }

    return 0;
}
