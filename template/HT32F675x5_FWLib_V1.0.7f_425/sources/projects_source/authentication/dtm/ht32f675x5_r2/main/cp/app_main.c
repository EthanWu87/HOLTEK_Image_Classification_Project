/*************************************************************************************************************
 * @file    app_main.c
 * @version V1.0
 * @date    2022-07-11
 * @brief   dtm cm0p main function.
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


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_sys_ctrl.h"
#include "hw_trng.h"
#include "hal_rf.h"

#include "app_cfg.h"
#include "type_def.h"
#include "boards.h"

#include "rand.h"
#include "utility.h"
#include "err_debug.h"
#include "app_debug.h"

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "hci_peripheral.h"
#include "dtm_init.h"

/**
 * @brief  Extern functions.
 */
extern void idle_task_init(void);

/**
 * @brief  System clock init, Control clock gate.
 */
static void system_clock_init(void)
{
    rom_hw_crg_enable_clk_gate(CRG_AHB4_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_FD_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_LO_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_SDM_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_MDM_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_LLC_HCLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_LLC_LCLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_CPTO0_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_CPTO1_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_CALI_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_TRNG_CLK_GATE);
}

/**
 * @brief  All peripheral init.
 */
static void peripheral_init(void)
{
    /* Disable CP all Peripheral interrupt. */
    rom_hw_sys_ctrl_peri_int_ctrl(SYS_CTRL_CP, 0, 0);

    // Rand init
    rom_rand_init(rom_hw_trng_gen_32bit());

#if APP_DEBUG_ENABLED
    app_debug_init(GPIO_PORT_CP_LOG_TX, GPIO_PIN_CP_LOG_TX, UART_HANDLE_CP_LOG, UART_BPS_CP_LOG, NULL);
    PRINTF("[%s T %s]dtm project(cp) start to work.\n", __DATE__, __TIME__);
#endif

    err_debug_init();

    hci_app_init();
}

/**
 * @brief  cm0p app main function.
 * @param  argument:
 */
void app_main(void *argument)
{
    system_clock_init();
    peripheral_init();

    idle_task_init();

    if (ERR_STA_OK == dtm_init())
    {
        PRINTF("DTM init successful.\n");
    }
    else
    {
        PRINTF("DTM init failed.\n");
    }

    osThreadTerminate(osThreadGetId());
}
