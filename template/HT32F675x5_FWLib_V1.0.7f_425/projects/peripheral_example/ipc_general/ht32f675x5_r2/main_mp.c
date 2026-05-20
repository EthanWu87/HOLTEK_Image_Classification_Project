/*************************************************************************************************************
 * @file    main_mp.c
 * @version V1.0
 * @date    2022-12-26
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


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_pmu.h"
#include "hw_efuse.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hw_stim.h"
#include "hw_timer.h"
#include "hal_pmu.h"
#include "hal_timer.h"

#include "app_cfg.h"
#include "boards.h"
#include "type_def.h"

#include "utility.h"
#include "rand.h"
#include "app_debug.h"

#include "ipc_general_blocking.h"

/**
 * @brief  DEFINE
 */
#define IPC_MSG_DATA_LEN (10)

/**
 * @brief  LOCAL VARIABLES
 */
static uint8_t gu8IpcTxBuf[IPC_MSG_DATA_LEN] __attribute__((aligned(4)))     = {0};
static uint8_t gu8IpcRxBuf[IPC_MSG_DATA_LEN + 4] __attribute__((aligned(4))) = {0};

static uint32_t gu32PassCount = 0;
static uint32_t gu32FailCount = 0;

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
    rom_rand_init(1);

    /* Disable MP all Peripheral interrupt. */
    rom_hw_sys_ctrl_peri_int_ctrl(SYS_CTRL_MP, 0, 0);

#if APP_DEBUG_ENABLED
    app_debug_init(GPIO_PORT_MP_APP_DEBUG_TX, GPIO_PIN_MP_APP_DEBUG_TX, UART_HANDLE_MP_APP_DEBUG, UART_BPS_MP_APP_DEBUG,
                   NULL);
    PRINTF("[%s T %s]ipc_general mp example code start to work.\n", __DATE__, __TIME__);
#endif
}

/**
 * @brief  Enable cotrex-m0plus. Release cm0p reset signal.
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

    rom_delay_ms(200);
}

/**
 * @brief  stim0 channel0 irq handler.
 */
__RAM_FUNC void STIM0_IRQ0_Handler(void)
{
    uint16_t u16Flag;
    uint32_t u32Count;

    /* Get stim0 channel 0 interrupt flag and clear it. */
    rom_hw_stim_get_interrupt_flag(STIM0, &u16Flag);
    rom_hw_stim_clear_interrupt_flag(STIM0, u16Flag);

    __disable_irq();
    rom_hw_stim_get_count(STIM0, &u32Count);
    rom_hw_stim_set_compare(STIM0, STIM_CH0, u32Count + TIME_MS_TO_32K_CNT(1000));
    __enable_irq();

    PRINTF("[STIM0]PASS: %d, Fail: %d\n", gu32PassCount, gu32FailCount);
}

/**
 * @brief  stim init.
 */
static void ipc_example_stim_init(void)
{
    // Enable stim0 module clock gate.
    rom_hw_crg_enable_clk_gate(CRG_STIM0_CLK_GATE);

    // Set stim prescale to 0(default).
    rom_hw_stim_set_prescale(STIM0, 0);

    // Config stim0 ch0 peripheral int
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, STIM0_IRQ0);
    NVIC_ClearPendingIRQ(STIM0_IRQ0);
    NVIC_SetPriority(STIM0_IRQ0, 0);
    NVIC_EnableIRQ(STIM0_IRQ0);

    // Configure stim0 ch0 interrupt and compare value.
    rom_hw_stim_enable_interrupt(STIM0, STIM_CH0_INT_MATCH);
    rom_hw_stim_set_compare(STIM0, STIM_CH0, TIME_MS_TO_32K_CNT(1000));

    // Start stim0 counter.
    rom_hw_stim_start(STIM0);
}

/**
 * @brief  IPC receive message callback function.
 * @param  pu8Data: Point to receive data buffer.
 * @param  u32DataLen: Data buffer length.
 */
static uint32_t ipc_receive_msg_callback(uint8_t *pu8Data, uint32_t u32DataLen)
{
    uint8_t u8CheckSum = 0;
    PRINTF("IPC MP Recv : ");
    for(int i=0; i<u32DataLen;i++)
    {
        PRINTF("0x%02X ",pu8Data[i]);
    }
    PRINTF("\r\n");
    
    for (int i=0; i < u32DataLen - 1; i++)
        u8CheckSum += pu8Data[i];
    
    if (u8CheckSum == pu8Data[u32DataLen-1])
        gu32PassCount++;
    else
        gu32FailCount++;

    return 0;
}

/**
 * @brief  IPC example.
 */
static void ipc_example(void)
{
    uint16_t i;
    uint8_t  u8CheckSum = 0;

    // stim init.
    ipc_example_stim_init();

    // ipc init.
    ipc_general_init(gu8IpcRxBuf, sizeof(gu8IpcRxBuf), ipc_receive_msg_callback);

    rom_delay_ms(100);
    
    for (;;)
    {
        u8CheckSum = 0;
        for (i = 0; i < sizeof(gu8IpcTxBuf) - 1; i++)
        {
            gu8IpcTxBuf[i] = rom_get_rand();
            u8CheckSum += gu8IpcTxBuf[i];
        }
        gu8IpcTxBuf[i] = u8CheckSum;

        PRINTF("IPC MP Send : ");
        for(int i=0; i<sizeof(gu8IpcTxBuf);i++)
        {
            PRINTF("0x%02X ",gu8IpcTxBuf[i]);
        }
        PRINTF("\r\n");
        ipc_general_send_msg_blocking(gu8IpcTxBuf, sizeof(gu8IpcTxBuf));
        
        rom_delay_ms(1000);
    }
}

/**
 * @brief  Main Function.
 * @return 0.
 */
int main(void)
{
    rom_hw_wdt_disable(WDT0);

    rom_delay_ms(100);

    system_power_init();
    system_clock_init(EN_SYS_CLK_DCXO16M);
    peripheral_init();

    system_enable_cp();

    ipc_example();

    for (;;);

    return 0;
}
