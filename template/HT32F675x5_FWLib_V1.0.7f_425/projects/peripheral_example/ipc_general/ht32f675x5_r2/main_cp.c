/*************************************************************************************************************
 * @file    main_cp.c
 * @version V1.0
 * @date    2022-12-27
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
#include <stdio.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_rtc.h"
#include "hw_stim.h"
#include "hw_sys_ctrl.h"
#include "hw_timer.h"
#include "hal_timer.h"

#include "app_cfg.h"
#include "type_def.h"
#include "boards.h"
#include "utility.h"
#include "rand.h"
#include "app_debug.h"

#include "ipc_general_blocking.h"

/**
 * @brief  DEFINE
 */
#define IPC_MSG_DATA_LEN (10)

/**
 * @brief  LOCAL VARIATE
 */
static uint8_t gu8IpcTxBuf[IPC_MSG_DATA_LEN] __attribute__((aligned(4)))     = {0};
static uint8_t gu8IpcRxBuf[IPC_MSG_DATA_LEN + 4] __attribute__((aligned(4))) = {0};

static uint32_t gu32PassCount = 0;
static uint32_t gu32FailCount = 0;

/**
 * @brief  All peripheral init.
 */
static void peripheral_init(void)
{
    /* Disable MP all Peripheral interrupt. */
    rom_hw_sys_ctrl_peri_int_ctrl(SYS_CTRL_CP, 0, 0);

#if APP_DEBUG_ENABLED
    app_debug_init(GPIO_PORT_CP_APP_DEBUG_TX, GPIO_PIN_CP_APP_DEBUG_TX, UART_HANDLE_CP_APP_DEBUG, UART_BPS_CP_APP_DEBUG,
                   NULL);
    PRINTF("[%s T %s]ipc_general cp example code start to work.\n", __DATE__, __TIME__);
#endif

    rom_rand_init(1);
}

/**
 * @brief  stim1 channel0 irq handler.
 */
void STIM1_IRQ0_Handler(void)
{
    uint16_t u16Flag;
    uint32_t u32Count;
    /* Get stim1 channel 0 interrupt flag and clear it. */
    rom_hw_stim_get_interrupt_flag(STIM1, &u16Flag);
    rom_hw_stim_clear_interrupt_flag(STIM1, u16Flag);

    __disable_irq();
    rom_hw_stim_get_count(STIM1, &u32Count);
    rom_hw_stim_set_compare(STIM1, STIM_CH0, u32Count + TIME_MS_TO_32K_CNT(1000));
    __enable_irq();

    PRINTF("[STIM1]PASS: %d, Fail: %d\n", gu32PassCount, gu32FailCount);
}

/**
 * @brief  stim init.
 */
static void ipc_example_stim_init(void)
{
    // Enable stim1 module clock gate.
    rom_hw_crg_enable_clk_gate(CRG_STIM1_CLK_GATE);

    // Set stim prescale to 0(default).
    rom_hw_stim_set_prescale(STIM1, 0);

    // Config stim1 ch0 peripheral int
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_CP, STIM1_IRQ0);
    NVIC_ClearPendingIRQ(STIM1_IRQ0);
    NVIC_SetPriority(STIM1_IRQ0, 0x3);
    NVIC_EnableIRQ(STIM1_IRQ0);

    // Configure stim1 ch0 interrupt and compare value.
    rom_hw_stim_enable_interrupt(STIM1, STIM_CH0_INT_MATCH);
    rom_hw_stim_set_compare(STIM1, STIM_CH0, TIME_MS_TO_32K_CNT(1000));

    // Start stim1 counter.
    rom_hw_stim_start(STIM1);
}

/**
 * @brief  IPC receive message callback function.
 * @param  pu8Data: Point to receive data buffer.
 * @param  u32DataLen: Data buffer length.
 */
static uint32_t ipc_receive_msg_callback(uint8_t *pu8Data, uint32_t u32DataLen)
{
    uint8_t u8CheckSum = 0;
    
    PRINTF("IPC CP Recv : ");
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

        PRINTF("IPC CP Send : ");
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
    peripheral_init();

    ipc_example();

    for (;;);

    return 0;
}
