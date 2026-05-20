/*************************************************************************************************************
 * @file    idle_task.c
 * @version V1.1
 * @date    2022-02-10
 * @brief   idle task.
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

#include "app_cfg.h"
#include "utility.h"
#include "lpwr_ctrl.h"
#include "rom_callback.h"

#if APP_DEBUG_ENABLED
    #include "app_debug.h"
#endif

#if MLOG_DEBUG_ENABLED
    #include "mlog_transport_uart.h"
#endif

/**
 * @brief  System idle process function
 */
static void idle_task_sys_idle_process(void)
{
#if APP_DEBUG_ENABLED
    app_debug_printf();
    rom_delay_us(500);
#endif

#if MLOG_DEBUG_ENABLED
    mlog_transport_uart_print();
    rom_delay_us(150);
#endif

    lpwr_ctrl_goto_sleep();
}

/**
 * @brief  idle task init.
 */
void idle_task_init(void)
{
    g_libIdleTaskCallback = idle_task_sys_idle_process;
}
