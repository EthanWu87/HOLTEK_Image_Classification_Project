/*************************************************************************************************************
 * @file    rom_callback.c
 * @version V1.0
 * @date    2021-05-27
 * @brief   
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

#include "rom_callback.h"

/**
 * @brief  Local function callback.
 */
func_lib_assert g_libAssertCallback = NULL;
func_lib_idle_task g_libIdleTaskCallback = NULL;
func_lib_os_error g_libOsErrorCallback = NULL;
func_lib_system_error g_libSystemErrorCallback = NULL;

void system_assert(uint16_t u16Addr, bool bCondition, uint32_t u32Info)
{
    if ((NULL != g_libAssertCallback) && !bCondition)
    {
        g_libAssertCallback(u16Addr, u32Info);
    }
}

void system_error(uint16_t u16ErrModule, uint16_t u16ErrLine, uint32_t u32ErrInfo1, uint32_t u32ErrInfo2)
{
    if (NULL != g_libSystemErrorCallback)
    {
        g_libSystemErrorCallback(u16ErrModule, u16ErrLine, u32ErrInfo1, u32ErrInfo2);
    }
}

/**
 * @brief  Idle task processor callback for cp and mp.
 */
void idle_task_processor(void)
{
    if (NULL != g_libIdleTaskCallback)
    {
        g_libIdleTaskCallback();
    }
}

/**
 * @brief  os error processor callback for cp and mp.
 */
uint8_t os_error_processor(uint32_t u32Code, void* pObjectId)
{
    if (NULL != g_libOsErrorCallback)
    {
        g_libOsErrorCallback(u32Code, pObjectId);
    }
    else
    {
        return 0;
    }

    return 1;
}

