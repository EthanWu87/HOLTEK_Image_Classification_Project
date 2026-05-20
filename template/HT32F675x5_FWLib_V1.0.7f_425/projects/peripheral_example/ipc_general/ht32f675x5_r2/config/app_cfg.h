/*************************************************************************************************************
 * @file    app_cfg.h
 * @version V1.1
 * @date    2025-08-21
 * @brief   ipc_general app configuration.
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
// RAM(0x2000_3000 ~ 0x0003_FFFF)
//=============================================================================
// CP RAM Code & Data In SDK
#define RAM_CP_ADDR                        (RAM_2ND_BOOT_ADDR) // 0x2000_3000, 12KB
#define RAM_CP_SIZE_MAX                    (52 * KBYTE)

// CP STACK and HEAP in SDK
#define RAM_CP_STACK_SIZE_MAX              (4 * KBYTE) // @ref startup_ARMCM0Plus.s
#define RAM_CP_HEAP_SIZE_MAX               (0 * KBYTE) // @ref startup_ARMCM0Plus.s
#define RAM_CP_STACK_HEAP_SIZE_MAX         (RAM_CP_STACK_SIZE_MAX + RAM_CP_HEAP_SIZE_MAX)
#define RAM_CP_STACK_HEAP_ADDR             (RAM_CP_ADDR + RAM_CP_SIZE_MAX - RAM_CP_STACK_HEAP_SIZE_MAX)

// MP NEW_VECTOR In SDK
#define RAM_MP_VECTOR_ADDR                 (RAM_CP_ADDR + RAM_CP_SIZE_MAX)
#define RAM_MP_VECTOR_SIZE_MAX             (512)

// MP RAM Code In SDK
#define RAM_MP_CODE_ADDR                   (RAM_MP_VECTOR_ADDR + RAM_MP_VECTOR_SIZE_MAX)
#define RAM_MP_CODE_SIZE_MAX               (32 * KBYTE - RAM_MP_VECTOR_SIZE_MAX)

// MP RAM Data In SDK
#define RAM_MP_DATA_ADDR                   (RAM_MP_CODE_ADDR + RAM_MP_CODE_SIZE_MAX)
#define RAM_MP_DATA_SIZE_MAX               (32 * KBYTE)

// MP STACK and HEAP in SDK
#define RAM_MP_STACK_SIZE_MAX              (4 * KBYTE) // @ref startup_ARMCM33.s
#define RAM_MP_HEAP_SIZE_MAX               (0 * KBYTE) // @ref startup_ARMCM33.s
#define RAM_MP_STACK_HEAP_SIZE_MAX         (RAM_MP_STACK_SIZE_MAX + RAM_MP_HEAP_SIZE_MAX)
#define RAM_MP_STACK_HEAP_ADDR             (RAM_MP_DATA_ADDR + RAM_MP_DATA_SIZE_MAX - RAM_MP_STACK_HEAP_SIZE_MAX)


//=============================================================================
// Flash(0x1000_0000 ~ 0x11FF_FFFF)
//=============================================================================
#define FLASH_MP_APP_CODE_ADDR             (FLASH_BASE_ADDR + FLASH_BOOT_RESERVED_SIZE_MAX)
#define FLASH_MP_APP_CODE_SIZE_MAX         (FLASH_SIZE_MAX - FLASH_BOOT_RESERVED_SIZE_MAX)


//=====================================================================================================================
// PERIPHERAL DEFINE
//=====================================================================================================================
//=============================================================================
// GPIO
//=============================================================================
// mp app_debug
#define GPIO_PORT_MP_APP_DEBUG_TX          (GPIO_PORT_UART0_TX)
#define GPIO_PIN_MP_APP_DEBUG_TX           (GPIO_PIN_UART0_TX)

// cp app_debug
#define GPIO_PORT_CP_APP_DEBUG_TX          (GPIO_PORT_UART1_TX)
#define GPIO_PIN_CP_APP_DEBUG_TX           (GPIO_PIN_UART1_TX)

//=============================================================================
// UART
//=============================================================================
// mp app_debug
#define UART_HANDLE_MP_APP_DEBUG           (UART0)
#define UART_BPS_MP_APP_DEBUG              (460800)

// cp app_debug
#define UART_HANDLE_CP_APP_DEBUG           (UART1)
#define UART_BPS_CP_APP_DEBUG              (460800)

//=====================================================================================================================
// APP Configuration
//=====================================================================================================================
//=============================================================================
// DEFAULT CFG
//=============================================================================
#define RC_HCLK_TUNE_DEFAUT_VAL            (0x56)
#define RC_LCLK_TUNE_DEFAUT_VAL            (0xA9)

//=============================================================================
// SYSTEM CLOCK
//=============================================================================
#define DCXO_HCLK_STABLE_TIME_2500US       (2500)
#define DCXO_HCLK_STABLE_TIME_2000US       (2000)
#define SYSTEM_CLOCK_PLL64M_ENABLED        (0)

//=============================================================================
// LOG CFG
//=============================================================================
#if defined(__MAIN_PROCESSOR)
    #define APP_DEBUG_ENABLED              (1)
    #define MLOG_DEBUG_ENABLED             (0)
#else
    #define APP_DEBUG_ENABLED              (1)
    #define MLOG_DEBUG_ENABLED             (0)
#endif

#if APP_DEBUG_ENABLED
    #define PRINTF(fmt, args...)           printf(fmt, ##args)
#else
    #define PRINTF(fmt, args...)
#endif


#endif /* __APP_CFG_H__ */


