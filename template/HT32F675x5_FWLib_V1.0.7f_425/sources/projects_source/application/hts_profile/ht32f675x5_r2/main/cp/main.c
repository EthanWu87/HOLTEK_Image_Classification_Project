/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2020-07-15
 * @brief   ble hts cp main file
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

#include "cmsis_os2.h"
#include "rtx_lib.h"

/**
 * @brief  Local variables
 */
static osRtxThread_t m_appMainCB __attribute__((aligned(4), section(".bss.os.thread.cb")));
static uint64_t      m_u64AppMainStack[256];

/**
 * @brief  Extern functions
 * @param  argument
 */
extern void app_main(void *argument);

/**
 * @brief  main function
 * @return
 */
int main(void)
{
    const osThreadAttr_t attr = {
        "app_main",
        osThreadJoinable,
        &m_appMainCB,
        sizeof(m_appMainCB),
        &m_u64AppMainStack[0],
        sizeof(m_u64AppMainStack),
        osPriorityNormal,
        0,
    };

    osKernelInitialize();               // Initialize CMSIS-RTOS
    osThreadNew(app_main, NULL, &attr); // Create application main thread
    osKernelStart();                    // Start thread execution

    for (;;);

    return 0;
}
