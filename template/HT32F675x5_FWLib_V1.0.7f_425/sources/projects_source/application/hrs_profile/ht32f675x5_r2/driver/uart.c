/*************************************************************************************************************
 * @file    uart.c
 * @version V1.0
 * @date    2021-02-06
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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_gpio.h"
#include "app_cfg.h"
#include "boards.h"

#include "hw_uart.h"
#include "hw_crg.h"
#include "hw_dma.h"
#include "hw_sys_ctrl.h"
#include "uart.h"


static uint8_t gu8UartRxBuf[HRS_UART_BUF_SIZE] = {0};
static uart_recv_callback_t gRecvCallback = NULL;

/**********************************************************************************************************************
 * @brief  UART DMA Init.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T uart_dma_init(void)
{
    stDmaInit_t stDmaInit;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    // 1. Turn DMA clock gating on.
    enRet = rom_hw_crg_enable_clk_gate(CRG_DMA_CLK_GATE);
    if (ERR_STA_OK != enRet)
        return enRet;
    
    rom_hw_uart_set_rxfifo_thld(HRS_UART_HANDLE, 1);
																
    // 2. UART RX DMA configuration
    stDmaInit.u32SrcAddr = (uint32_t)&UART1->UART_RX_FIFO;
    stDmaInit.u32DstAddr = (uint32_t)gu8UartRxBuf;
    stDmaInit.u32TimeOut = 1000;
    stDmaInit.unPeriSel.stPeriSel.enPeriID = DMA_PERI_UART1_RX;
    stDmaInit.unCfg.u32DMACfg = DMA_INIT_PERI_TO_MEM_DEFAULT_CFG(HRS_UART_BUF_SIZE, DMA_DATA_1BYTE);
    enRet = rom_hw_dma_init(DMA7, &stDmaInit);
    
    // 3. DMA interrupt init
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_CP, DMA_IRQ7);
    NVIC_ClearPendingIRQ(DMA_IRQ7);
    NVIC_SetPriority(DMA_IRQ7, 0x3);
    NVIC_EnableIRQ(DMA_IRQ7);
    
    rom_hw_dma_set_interrupt_channel(DMA7, DMA_INT7);
    rom_hw_dma_enable_interrupt(DMA7, DMA_INT_TIMEOUT);
    rom_hw_dma_enable(DMA7);
    
    return enRet;
}

/**********************************************************************************************************************
 * @brief  UART Init.
 * @param  recvCb: Received Callback Function.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T uart_init(uart_recv_callback_t recvCb)
{
    stUartInit_t stUartInit;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (NULL == recvCb)
        return ERR_PARA_ERR;
    
    gRecvCallback = recvCb;
    
    // 1. Init UART IO.
    rom_hw_gpio_set_pin_pid(HRS_UART_PORT_TX, HRS_UART_PIN_TX, PID_UART1_TXD);
    rom_hw_gpio_set_pin_pid(HRS_UART_PORT_RX, HRS_UART_PIN_RX, PID_UART1_RXD);
    rom_hw_gpio_set_pin_pull_mode(HRS_UART_PORT_TX, HRS_UART_PIN_TX, GPIO_PULL_UP);
    rom_hw_gpio_set_pin_pull_mode(HRS_UART_PORT_RX, HRS_UART_PIN_RX, GPIO_PULL_UP);
    
    // 2. Turn UART clock gating on.
    enRet = rom_hw_crg_enable_clk_gate(CRG_UART1_CLK_GATE);
    if (ERR_STA_OK != enRet)
        return enRet;
    
    // 3. UART Init.
    stUartInit.u32UartBaudRate = HRS_UART_BPS;
    stUartInit.unUartCfg.u32UartCfg = UART_INIT_DEFAULT(UART_PARITY_NONE);
    
    enRet = rom_hw_uart_init(HRS_UART_HANDLE, &stUartInit);
    if (ERR_STA_OK != enRet)
        return enRet;
    
    enRet = uart_dma_init();
    
    return enRet;
}

/**********************************************************************************************************************
 * @brief  UART Send Bytes.
 * @param  pu8Buf: Send Data Buffer
 * @param  u16Len: The length of Send Data
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T uart_send_bytes(uint8_t *pu8Buf,uint16_t u16Len)
{
    return rom_hw_uart_transmit(HRS_UART_HANDLE,pu8Buf,u16Len);
}															


void DMA_IRQ7_Handler()
{
    rom_hw_dma_disable(DMA7);
    uint8_t u8IntMsk;
    uint16_t u16Count;
    rom_hw_dma_get_interrupt_flag(DMA7, &u8IntMsk);
    rom_hw_dma_clear_interrupt_flag(DMA7, u8IntMsk);
    
    if (u8IntMsk & DMA_INT_MSK)
    {
        rom_hw_dma_get_trx_pointer(DMA7, &u16Count);
        gRecvCallback(gu8UartRxBuf,u16Count);
        memset(gu8UartRxBuf,0,u16Count);
        rom_hw_dma_enable(DMA7);
    }
}

/**********************************************************************************************************************
 * @brief  UART Deinit.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T uart_deinit(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    rom_hw_gpio_set_pin_input_output(HRS_UART_PORT_TX, HRS_UART_PIN_TX, GPIO_MODE_IMPEDANCE);
    rom_hw_gpio_set_pin_input_output(HRS_UART_PORT_RX, HRS_UART_PIN_RX, GPIO_MODE_IMPEDANCE);

    enRet = rom_hw_crg_disable_clk_gate(CRG_UART1_CLK_GATE);

    return enRet;
}

/**********************************************************************************************************************
 * @brief  UART Reinit.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T uart_reinit(void)
{
    return uart_init(gRecvCallback);
}
