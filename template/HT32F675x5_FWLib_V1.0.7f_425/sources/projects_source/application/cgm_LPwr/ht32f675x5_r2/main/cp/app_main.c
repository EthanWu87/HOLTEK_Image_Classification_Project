/*************************************************************************************************************
 * @file    app_main.c
 * @version V1.0
 * @date    2022-02-13
 * @brief   cgm cp app main file
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
#include <string.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_pmu.h"
#include "hw_uart.h"
#include "hw_sys_ctrl.h"
#include "hw_trng.h"
#include "hw_efuse.h"
#include "hal_pmu.h"

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "app_cfg.h"
#include "boards.h"

#include "rand.h"
#include "utility.h"
#include "lpwr_ctrl.h"
#include "app_timer.h"
#include "rom_callback.h"
#include "err_debug.h"
#include "app_debug.h"
#include "mlog.h"
#include "mlog_transport_uart.h"
#include "ble_init.h"
#include "uart.h"
#include "spi_master.h"
#include "dev_info.h"

/**
 * @brief  LOCAL VARIABLES
 */
#if APP_DEBUG_ENABLED
static uint8_t gu8DebugBuf[4096] __attribute__((aligned(4)));
static stDebugBuf_t gstDebugBuf __attribute__((aligned(4)));
#endif

/**
 * @brief  Extern functions.
 */
extern void idle_task_init(void);
extern void app_cgm_cp(void);
extern bool is_app_can_goto_sleep(void);

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
 * @brief  All peripheral related please init here
 */
static void peripheral_init(void)
{
    /* Disable CP all Peripheral interrupt. */
    rom_hw_sys_ctrl_peri_int_ctrl(SYS_CTRL_CP, 0, 0);

    // Rand init
    rom_rand_init(rom_hw_trng_gen_32bit());

    // App timer init
    app_timer_init();

#if APP_DEBUG_ENABLED
    gstDebugBuf.pu8buf    = gu8DebugBuf;
    gstDebugBuf.u16MaxLen = sizeof(gu8DebugBuf);
//    app_debug_init(GPIO_PORT_CP_APP_DEBUG_TX, GPIO_PIN_CP_APP_DEBUG_TX, UART_HANDLE_CP_APP_DEBUG, UART_BPS_CP_APP_DEBUG,
//                   &m_stDebugBuf);
    app_debug_init(GPIO_PORT_CP_APP_DEBUG_TX, GPIO_PIN_CP_APP_DEBUG_TX, UART_HANDLE_CP_APP_DEBUG, UART_BPS_CP_APP_DEBUG,
                   NULL);
    PRINTF("[%s T %s]ble peripheral project(cp) start to work.\n", __DATE__, __TIME__);
#endif

#if MLOG_DEBUG_ENABLED
    mlog_transport_uart_init(UART_HANDLE_CP_MLOG, GPIO_PORT_CP_MLOG_TX, GPIO_PIN_CP_MLOG_TX, UART_BPS_CP_MLOG);

    MLOG0D(0x80c0, "MLOG0D test");
    MLOGI(0x80c1, "MLOGI test : 0x%04x", 0x1234);
    MLOG32I(0x80c2, "MLOG32I test : 0x%08x", 0x12345678);
    MLOG88W(0x80c3, "MLOG88W test : 0x%02x : 0x%02x", 0x12, 0x34);
    MLOG1616W(0x80c4, "MLOG1616W test : 0x%04x : 0x%04x", 0x1234, 0x5678);
    MLOG3216W(0x80c5, "MLOG3216W test : 0x%08x : 0x%04x", 0x12345678, 0x4321);
    MLOG3232W(0x80c6, "MLOG3232W test : 0x%08x : 0x%08x", 0x12345678, 0x87654321);
    MLOG1688E(0x80c7, "MLOG1688E test : 0x%04x : 0x%02x : 0x%02x", 0x1234, 0x56, 0x78);
    MLOG161616E(0x80c8, "MLOG161616E test : 0x%04x : 0x%04x : 0x%04x", 0x1234, 0x5678, 0xabcd);
    MLOG3288E(0x80c9, "MLOG3288E test : 0x%08x : 0x%02x : 0x%02x", 0x12345678, 0xab, 0xcd);
    MLOG321616E(0x80ca, "MLOG321616E test : 0x%08x : 0x%04x : 0x%04x", 0x12345678, 0xaabb, 0xccdd);

    uint8_t pu8Data[] = {0x12, 0x34, 0x56, 0x78, 0x90};
    MLOGXD(0x80cb, "MLOGXD test:", pu8Data, sizeof(pu8Data));
#endif

    err_debug_init();
}

/**
 * @brief  Check if the system can get into sleep
 * @return false(0) - System can not get into sleep.
 * @return true(1)  - System can get into sleep.
 */
static bool lpwr_before_sleep(void)
{
    if (false == is_app_can_goto_sleep())
        return false;

// Check app debug(uart).
#if APP_DEBUG_ENABLED
    if (!app_debug_print_complete())
    {
        return false;
    }

    // Set uart pin to impedance
    app_debug_deinit();
#endif

// Check mlog(uart).
#if MLOG_DEBUG_ENABLED
    /* Set uart pin to impedance */
    mlog_transport_uart_deinit();
#endif

    // CGM UART Deinit
    uart_deinit();

#if SPI_CMD_SUPPORT
    spi_master_deinit();
#endif

    OS_Tick_Disable();

    return true;
}

/**
 * @brief  CPU after wakeup from sleep func
 */
static void lpwr_after_wakeup(void)
{
    // CGM Uart Reinit
    uart_reinit();

#if APP_DEBUG_ENABLED
    app_debug_reinit();
#endif

#if MLOG_DEBUG_ENABLED
    // Re-init mlog
    mlog_transport_uart_reinit();
#endif

    OS_Tick_Enable();
}

/**
 * @brief  PMU IRQ Handler.
 */
void PMU_IRQ_Handler(void)
{
    uint32_t u32IntFlag;

    rom_hw_pmu_get_interrupt_flag(&u32IntFlag);
    rom_hw_pmu_clear_interrupt_flag(u32IntFlag);

    if (u32IntFlag & (1 << LUT_INDEX_CP_LLC))
    {
        ble_init_on_system_wakeup_by_llc();
    }
    if (u32IntFlag & (1 << LUT_INDEX_KEY))
    {
        MLOG0D(0x80cc, "Wakeup by Key");
    }
}

/**
 * @brief  Low power init
 * @param  enMode: System work mode, @ref EN_LPWR_MODE_SEL_T.
 */
static void system_lpwr_init(EN_LPWR_MODE_SEL_T enMode)
{
    // Enable pmu interrupt. 
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_CP, PMU_IRQ);
    NVIC_ClearPendingIRQ(PMU_IRQ);
    NVIC_SetPriority(PMU_IRQ, 0);
    NVIC_EnableIRQ(PMU_IRQ);

    // Low power init.
    lpwr_ctrl_init(enMode, lpwr_before_sleep, lpwr_after_wakeup);
}

static void show_dev_info(void)
{
    EN_ERR_STA_T enRet;
    uint8_t u8Addr[6];
    uint8_t u8Did[3];

    enRet = dev_info_device_id(u8Did,3);
    if (ERR_STA_OK != enRet)
    {
        INFO("Read Device ID Failed\n");
        return;
    }

    INFO("Device ID : ");
    for (int i=0;i<3;i++)
        PRINTF("0x%02X ",u8Did[i]);
    PRINTF("\n");

    enRet = dev_info_default_ble_addr(u8Addr,6);
    if (ERR_STA_OK != enRet)
    {
        INFO("Read Default Ble Dev Addr Failed\n");
        return;
    }

    INFO("Defaule Ble Addr : ");
    for (int i=0;i<6;i++)
        PRINTF("0x%02X ",u8Addr[i]);
    PRINTF("\n");

    enRet = dev_info_custom_ble_addr(u8Addr,6);
    if (ERR_STA_OK != enRet)
    {
        INFO("Read Custom Ble Dev Addr Failed\n");
        return;
    }

    INFO("Custom Ble Addr : ");
    for (int i=0;i<6;i++)
        PRINTF("0x%02X ",u8Addr[i]);
    PRINTF("\n");
}

static void write_dev_info(void)
{
//  EN_ERR_STA_T enRet;
//  uint8_t u8CustomAddr[] = {0x11,0x22,0x33,0x44,0xAC,0x04};
//  uint8_t u8DeviceID[] = {0x75,0x75,0x06};

    PRINTF("--------Before Device Info Write--------\n");
    show_dev_info();

    /* Uncomment if you want to write device information into efuse */
    /* efuse can only write 0 to 1 */

//    enRet = rom_hw_efuse_write_bytes(DEV_INFO_CUSTOM_BLE_DEV_ADDR_BYTE,u8CustomAddr,DEV_INFO_CUSTOM_BLE_DEV_ADDR_LENGTH);
//    if (ERR_STA_OK != enRet)
//    {
//        INFO("Write Custom Ble Dev Addr Failed\n");
//        return;
//    }
//    
//    enRet = rom_hw_efuse_write_bytes(DEV_INFO_DEVICE_ID_BYTE,u8DeviceID,DEV_INFO_DEVICE_ID_LENGTH);
//    if (ERR_STA_OK != enRet)
//    {
//        INFO("Write Device ID Failed\n");
//        return;
//    }
//    
//    PRINTF("--------After Device Info Write--------\n");
//    show_dev_info();
}

/**
 * @brief  cp app main task.
 * @param  argument
 */
void app_main(void *argument)
{
    system_clock_init();
    peripheral_init();

    idle_task_init();
    system_lpwr_init(LPWR_MODE_SLEEP);

    PRINTF("------------App1 v0.1------------\n");
    
    write_dev_info();
    
    app_cgm_cp();
    
    osThreadTerminate(osThreadGetId());
}
