/*************************************************************************************************************
 * @file    app_cfg.h
 * @version V1.0
 * @date    2021-02-06
 * @brief   boot2 project app configuration.
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


#ifndef __APP_CFG_H__
#define __APP_CFG_H__


// HT32F675x5 Memory Map
#include "..\..\..\..\..\sources\mem_cfg\ht32f675x5_mem_cfg_r2.h"


//=====================================================================================================================
// MEMOARY MAP DEFINE
//=====================================================================================================================
//=============================================================================
// Flash
//=============================================================================
#define FLASH_RESET_HANDLER_ADDR           (FLASH_BASE_ADDR + FLASH_BOOT_RESERVED_SIZE_MAX + 4)


//=====================================================================================================================
// PERIPHERAL DEFINE
//=====================================================================================================================
//=============================================================================
// GPIO
//=============================================================================
// mp app_debug
#define GPIO_PORT_LOG_TX                   (GPIOA)
#define GPIO_PIN_LOG_TX                    (GPIO_PIN_29) // P29

//=============================================================================
// UART
//=============================================================================
// app_debug
#define UART_HANDLE_LOG                    (UART0)
#define UART_BPS_LOG                       (460800)


//=====================================================================================================================
// LOG DEFINE
//=====================================================================================================================
#define APP_DEBUG_ENABLED                  (0)

#if APP_DEBUG_ENABLED
    #define PRINTF(fmt, args...)           printf(fmt, ##args)
#else
    #define PRINTF(fmt, args...)
#endif


//=====================================================================================================================
// Boot2 Configuration
//=====================================================================================================================
#define BOOT2_FLASH_MODE                   (BUS_MODE_SPI)


#endif /* __APP_CFG_H__ */

