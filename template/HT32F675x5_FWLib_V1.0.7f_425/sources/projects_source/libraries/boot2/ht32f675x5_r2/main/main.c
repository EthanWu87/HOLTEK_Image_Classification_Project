/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2020-06-24
 * @brief   boot2 main function
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

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_pmu.h"
#include "hw_sys_ctrl.h"

#include "version.h"
#include "app_cfg.h"
#include "utility.h"
#include "app_debug.h"

#include "boot2.h"

/**
 * @brief  Local variables.
 */
const stBoot2Header_t g_stBoot2Header __attribute__((section(".boot2.code.header"))) = {
    .u16HT32Flag    = HT32_BLE_SOC_FLAG,
    .u8Boot2Ver     = BOOT2_VERSION,
    .u8RomVer       = ROM_VERSION,
    .u8EncryptFlag  = 0,
    .u8Reserved     = 0,
    .u16UserKey     = 0,
    .u32CodeSize    = 0,
    .u32Crc32       = 0,
    .u32HeaderCrc32 = 0,
};

/**
 * @brief  Local functions.
 */
void system_init(void) __attribute__((section(".boot2.code")));

/**
 * @brief  ht32f675x5 system bug fix solutions.
 */
static void system_bug_fix(void)
{
    // BUG01
    // Fixed the bug which gpio can not wake up the system in hibernation mode.
    reg_pmu_test_en &= ~mask_pmu_test_en_wakeup_deb_en;

    // BUG02
    // Disable the function which if there is no interrupt after system wakeup,
    // then send pmu timeout interrupt to cp and mp.
    reg_pmu_test_en &= ~mask_pmu_test_en_pdon_timeout_en;

    // BUG03
    // Fixed the bug which P00 can not wakeup the system.
    for (uint8_t i = 2; i < PMU_LUT_MAX; i++)
    {
        PMU->PMU_LUT_ROW[i] = ((LUT_TRIG_SEL_MSK << LUT_TRIG_SEL_SHIFT) | (LUT_TRIG_ID_MSK << LUT_TRIG_ID_SHIFT));
    }
}

/**
 * @brief  boot2 entry
 */
void system_init(void)
{
#if APP_DEBUG_ENABLED
    rom_hw_pmu_set_rc_hclk_tune(0x56);
    app_debug_init(GPIO_PORT_LOG_TX, GPIO_PIN_LOG_TX, UART_HANDLE_LOG, UART_BPS_LOG, NULL);
#endif

    /* System bug fix solutions. */
    system_bug_fix();

    /* Release software reset signal of cp, cp will goto sleep. */
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_REMAP_ADDR, 0);
    rom_hw_crg_enable_clk_gate(CRG_CP_CLK_GATE);
    rom_hw_crg_release_reset(CRG_CP_SW_RST);

    /* Check firmware upgrade. */
    boot2_update_flash();

    /* Init cache. */
    boot2_cache_init();

    /* Jump to sdk main. */
    boot2_load_code();
}
