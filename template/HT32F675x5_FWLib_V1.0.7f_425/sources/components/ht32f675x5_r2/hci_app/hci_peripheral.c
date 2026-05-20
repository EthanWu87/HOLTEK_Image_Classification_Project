/*************************************************************************************************************
 * @file    hci_peripheral.c
 * @version V1.0
 * @date    2023-07-11
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
#include <stdbool.h>

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_dma.h"
#include "hw_gpio.h"
#include "hw_uart.h"
#include "hw_sys_ctrl.h"

#include "type_def.h"
#include "boards.h"
#include "app_cfg.h"

#include "hci_struct.h"
#include "hci_cmd.h"
#include "hci_event.h"
#include "hci_peripheral.h"
#include "mlog.h"

/**
 * @brief  Define
 */
#if defined(__MAIN_PROCESSOR)
    #define HCI_SYS_CTRL_INT (SYS_CTRL_MP)
#else
    #define HCI_SYS_CTRL_INT (SYS_CTRL_CP)
#endif

/**
 * @brief  Local variables
 */
static osRtxThread_t hciAppEventCB;
static uint64_t      hciAppEventStack[HCI_EVENT_TASK_STACK_SIZE / sizeof(uint64_t)];
osThreadId_t         hciAppEventTaskId;

static osRtxThread_t hciAppCmdCB;
static uint64_t      hciAppCmdStack[HCI_CMD_TASK_STACK_SIZE / sizeof(uint64_t)];
osThreadId_t         hciAppCmdTaskId;

static uint8_t m_u8CmdBuf[HCI_CMD_BUF_SIZE] __attribute__((aligned(4)));     /* hci app cmd buffer */
static uint8_t m_u8EventBuf[HCI_EVENT_BUF_SIZE] __attribute__((aligned(4))); /* hci app event buffer */

static uint8_t          m_u8State;  /* parse hci app cmd state */
static stHciBuf_t       m_stCmdBuf; /* hci app cmd parse buffer */
static stHciCmdHeader_t m_stCmdHeader;

static uint8_t m_u8CopyBuf[256] __attribute__((aligned(4))); /* copy cmd data from m_u8CmdBuf to this buf */
static uint8_t m_u8CopyBufIdx;

static stEvent_t  m_stEvent;    /* hci app event struct */
static stHciBuf_t m_stEventBuf; /* hci app event packet buffer */

/**
 * @brief
 * @param
 * @return
 */
void hci_send_event(uint8_t *pu8SendData, uint16_t u16Len)
{
    uint8_t *pu8Evt = NULL;
    uint8_t *pu8Buf = NULL;
    uint16_t u16Tx;
    uint16_t u16Rx;
    //    uint16_t u16Len;
    uint16_t    u16UnuseBufLen;
    stHciBuf_t *pstEventBuf = &m_stEventBuf;

    u16Tx  = pstEventBuf->u16Tx;
    u16Rx  = pstEventBuf->u16Rx;
    pu8Buf = pstEventBuf->pu8Buf;

    if (u16Tx <= u16Rx)
    {
        u16UnuseBufLen = u16Tx + HCI_EVENT_BUF_SIZE - u16Rx;
    }
    else
    {
        u16UnuseBufLen = u16Tx - u16Rx;
    }

    MLOG1688D(0xa240, "Event u16Tx,u16Rx,u16Len: %d,%d,%d", u16Tx, u16Rx, u16Len);
    if (u16Len <= u16UnuseBufLen)
    {
        if (u16Rx + u16Len <= HCI_EVENT_BUF_SIZE)
        {
            memcpy(&pu8Buf[u16Rx], (uint8_t *)pu8SendData, u16Len);
        }
        else
        {
            pu8Evt = (uint8_t *)pu8SendData;
            memcpy(&pu8Buf[u16Rx], pu8Evt, HCI_EVENT_BUF_SIZE - u16Rx);
            memcpy(&pu8Buf[0], &pu8Evt[HCI_EVENT_BUF_SIZE - u16Rx], u16Len + u16Rx - HCI_EVENT_BUF_SIZE);
        }
        pstEventBuf->u16Rx = ((u16Rx + u16Len) & (HCI_EVENT_BUF_SIZE - 1));

        osThreadFlagsSet(hciAppEventTaskId, 0x01U);
    }
    else
    {
        MLOG1616E(0xa241, "Event fifo not enough.u16Len,u16UnuseBufLen: %d %d", u16Len, u16UnuseBufLen);
        // need return ???
    }
}

/**
 * @brief  Copy hci app cmd data to m_u8CmdBuf buf.
 * @param  u16Idx: Hci app cmd payload data index.
 * @return
 */
static uint8_t hci_app_cmd_copy_data(uint16_t u16Idx)
{
    m_u8CopyBuf[m_u8CopyBufIdx] = m_u8CmdBuf[u16Idx];
    m_u8CopyBufIdx++;

    if (m_u8CopyBufIdx >= m_stCmdHeader.u8Len)
    {
        m_u8CopyBufIdx                         = 0;
        m_stEvent.u8Len                        = 0x09;
        m_stEvent.u8EvtCode                    = HT32_SPECIFIED_EVENT_CODE;
        m_stEvent.unPar.stCmdSta.u8Status      = 0;
        m_stEvent.unPar.stCmdSta.u8NumCmdPckts = 1;
        m_stEvent.unPar.stCmdSta.u16Opcode     = m_stCmdHeader.u16OpCode;
        memset(&m_stEvent.unPar.stCmdSta.u8Para, 0, 4);

        return ERR_STA_OK;
    }

    return ERR_DATA_BUSY;
}

/**
 * @brief  Hci app cmd data analysis
 * @param  u16Tx: Hci app cmd data index.
 * @param  u16Len: Hci app cmd data length.
 * @return
 */
static uint16_t hci_app_cmd_analysis(uint16_t u16Tx, uint16_t u16Len)
{
    uint8_t  u8Status = 0;
    uint8_t *pu8Buf   = NULL;
    uint16_t i        = 0;
    uint16_t idx      = 0;

    pu8Buf = m_u8CmdBuf;

    while (i < u16Len)
    {
        idx = CHECK_HCI_CMD_INDEX(u16Tx + i);
        // PRINTF ( "%02X ", pu8Buf[idx] );

        switch (m_u8State)
        {
            case HCI_STATE_TYPE:
            {
                if (HCI_TYPE_COMMAND == pu8Buf[idx])
                {
                    m_u8CopyBufIdx       = 0;
                    m_u8State            = HCI_STATE_CMD_OPCODE_LO;
                    m_stCmdHeader.u8Type = HCI_TYPE_COMMAND;
                }
                else
                {
                    MLOGE(0xa242, "Err type=%x\n", pu8Buf[idx]);
                }
                break;
            }
            case HCI_STATE_CMD_OPCODE_LO:
            {
                m_stCmdHeader.u16OpCode = pu8Buf[idx];
                m_u8State               = HCI_STATE_CMD_OPCODE_HI;
                break;
            }
            case HCI_STATE_CMD_OPCODE_HI:
            {
                m_stCmdHeader.u16OpCode |= (pu8Buf[idx] << 8);
                m_u8State = HCI_STATE_CMD_LENGTH;
                break;
            }
            case HCI_STATE_CMD_LENGTH:
            {
                m_stCmdHeader.u8Len = pu8Buf[idx];
                m_u8State           = HCI_STATE_DATA_START;

                if (0 == m_stCmdHeader.u8Len)
                {
                    if (HCI_TYPE_COMMAND == m_stCmdHeader.u8Type)
                    {
                        hci_cmd_dispatch(m_stCmdHeader.u16OpCode, m_u8CopyBuf, m_stCmdHeader.u8Len, &m_stEvent);
                        hci_event_generate(&m_stEventBuf, &m_stEvent);
                        m_u8State = HCI_STATE_TYPE;
                    }
                }
                break;
            }
            case HCI_STATE_DATA_START:
            case HCI_STATE_DATA_CONT:
            {
                m_u8State = HCI_STATE_DATA_CONT;

                if (HCI_TYPE_COMMAND == m_stCmdHeader.u8Type)
                {
                    if (hci_app_cmd_copy_data(idx) == ERR_STA_OK)
                    {
                        hci_cmd_dispatch(m_stCmdHeader.u16OpCode, m_u8CopyBuf, m_stCmdHeader.u8Len, &m_stEvent);
                        hci_event_generate(&m_stEventBuf, &m_stEvent);
                        m_u8State = HCI_STATE_TYPE;
                    }
                }
                break;
            }
            default:
                break;
        }
        i++;
    }

    return 0; // data_length;
}

/**
 * @brief  Hci app cmd task receive data buffer
 */
static void hci_app_cmd_buffer(void)
{
    uint16_t u16Tx;
    uint16_t u16Rx;
    uint16_t u16Len;
    uint16_t u16TailLen;

    u16Tx = m_stCmdBuf.u16Tx;
    u16Rx = m_stCmdBuf.u16Rx;

    while (u16Rx != u16Tx)
    {
        u16Len = (u16Rx + HCI_CMD_BUF_SIZE - u16Tx) & (HCI_CMD_BUF_SIZE - 1);
        // PRINTF ( "CMD Len: %d\n", u16Len );

        /* Hci dispatch function. */
        hci_app_cmd_analysis(u16Tx, u16Len);

        u16Tx = u16Rx;
    }

    m_stCmdBuf.u16Tx = u16Tx;
}

/**
 * @brief  Hci app event task handler
 * @param  argument:
 */
static void hci_app_event_task(void *argument)
{
    uint32_t flag;

    while (1)
    {
        flag = osThreadFlagsWait(0x7FFFFFFF, osFlagsWaitAny, osWaitForever);
        if (0 == (flag & osFlagsError))
        {
            rom_hw_dma_set_interval_tx_index(DMA_HANDLE_HCI_UART_TX, m_stEventBuf.u16Rx);
        }
    }
}

/**
 * @brief  Hci app cmd task handler
 * @param  argument:
 */
static void hci_app_cmd_task(void *argument)
{
    uint32_t flag;

    while (1)
    {
        flag = osThreadFlagsWait(0x7FFFFFFFU, osFlagsWaitAny, osWaitForever);
        if (0 == (flag & osFlagsError))
        {
            hci_app_cmd_buffer();
        }
    }
}

/**
 * @brief  Hci app dma interrupt handler
 */
void DMA_IRQ7_Handler(void)
{
    uint8_t u8IntMsk;

    rom_hw_dma_get_interrupt_flag(DMA_HANDLE_HCI_UART_RX, &u8IntMsk);
    rom_hw_dma_clear_interrupt_flag(DMA_HANDLE_HCI_UART_RX, u8IntMsk);

    if (u8IntMsk & DMA_INT_MSK)
    {
        rom_hw_dma_get_trx_pointer(DMA_HANDLE_HCI_UART_RX, &m_stCmdBuf.u16Rx);
        MLOG1616D(0xa243, "DMA RX INT: %02X, %d\n", u8IntMsk, m_stCmdBuf.u16Rx);
        osThreadFlagsSet(hciAppCmdTaskId, 0x01U);
    }

    rom_hw_dma_get_interrupt_flag(DMA_HANDLE_HCI_UART_TX, &u8IntMsk);
    rom_hw_dma_clear_interrupt_flag(DMA_HANDLE_HCI_UART_TX, u8IntMsk);

    if (u8IntMsk & DMA_INT_MSK)
    {
        rom_hw_dma_get_trx_pointer(DMA_HANDLE_HCI_UART_TX, &m_stEventBuf.u16Tx);
        MLOG1616D(0xa244, "DMA TX INT: %02X, %d\n", u8IntMsk, m_stEventBuf.u16Tx);
    }
}

/**
 * @brief  Hci app uart io init
 */
static void hci_gpio_init(void)
{
    stUartInit_t stUartInit;

    // Init uart io
    rom_hw_gpio_set_pin_pid(GPIO_PORT_HCI_TX, GPIO_PIN_HCI_TX, GPIO_PID_HCI_UART_TX);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_HCI_TX, GPIO_PIN_HCI_TX, GPIO_PULL_UP);

    rom_hw_gpio_set_pin_pid(GPIO_PORT_HCI_RX, GPIO_PIN_HCI_RX, GPIO_PID_HCI_UART_RX);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_HCI_RX, GPIO_PIN_HCI_RX, GPIO_PULL_UP);

    // Enable uart clock gate
    rom_hw_crg_enable_clk_gate(CRG_CLK_GATE_HCI_UART);

    // Init uart
    stUartInit.u32UartBaudRate      = UART_BAUDRATE_HCI;
    stUartInit.unUartCfg.u32UartCfg = UART_INIT_DEFAULT(UART_PARITY_NONE);
    rom_hw_uart_init(UART_HANDLE_HCI, &stUartInit);

    // For test...
    rom_hw_uart_send_byte(UART_HANDLE_HCI, 0x55);
}

/**
 * @brief  Hci app uart dma init
 */
static void hci_dma_init(void)
{
    stDmaInit_t stDmaInit = {
        .u32SrcAddr                   = UART_RXFIFO_ADDR_HCI,
        .u32DstAddr                   = (uint32_t)m_stCmdBuf.pu8Buf,
        .u32TimeOut                   = 1000,
        .unCfg.u32DMACfg              = DMA_INIT_PERI_TO_MEM_DEFAULT_CFG(HCI_CMD_BUF_SIZE, DMA_DATA_1BYTE),
        .unPeriSel.stPeriSel.enPeriID = DMA_PERI_HCI_UART_RX,
    };

    // Enable dma clock gate
    rom_hw_crg_enable_clk_gate(CRG_DMA_CLK_GATE);

    // Enable hci dma interrupt
    rom_hw_sys_ctrl_enable_peri_int(HCI_SYS_CTRL_INT, DMA_IRQ_HCI);
    NVIC_ClearPendingIRQ(DMA_IRQ_HCI);
    NVIC_SetPriority(DMA_IRQ_HCI, 0x3);
    NVIC_EnableIRQ(DMA_IRQ_HCI);

    // Configure dma uart rx
    rom_hw_dma_init(DMA_HANDLE_HCI_UART_RX, &stDmaInit);
    rom_hw_dma_set_interrupt_channel(DMA_HANDLE_HCI_UART_RX, DMA_INT_HCI);
    rom_hw_dma_enable_interrupt(DMA_HANDLE_HCI_UART_RX, DMA_INT_MSK);
    rom_hw_dma_enable(DMA_HANDLE_HCI_UART_RX);

    stDmaInit.u32SrcAddr = (uint32_t)m_stEventBuf.pu8Buf;
    stDmaInit.u32DstAddr = UART_TXFIFO_ADDR_HCI;
    stDmaInit.unPeriSel.stPeriSel.enPeriID = DMA_PERI_HCI_UART_TX,
    stDmaInit.unCfg.u32DMACfg              = DMA_INIT_MEM_TO_PERI_DEFAULT_CFG(HCI_EVENT_BUF_SIZE, DMA_DATA_1BYTE);

    // Configure dma uart tx
    rom_hw_dma_init(DMA_HANDLE_HCI_UART_TX, &stDmaInit);
    rom_hw_dma_set_interrupt_channel(DMA_HANDLE_HCI_UART_TX, DMA_INT_HCI);
    rom_hw_dma_enable_interrupt(DMA_HANDLE_HCI_UART_TX, DMA_INT_TIMEOUT);
    rom_hw_dma_interval_tx_mode_enable(DMA_HANDLE_HCI_UART_TX);
    rom_hw_dma_enable(DMA_HANDLE_HCI_UART_TX);
}

/**
 * @brief  Hci app data buf init
 */
static void hci_buffer_init(void)
{
    m_stCmdBuf.u16Rx  = 0;
    m_stCmdBuf.u16Tx  = 0;
    m_stCmdBuf.pu8Buf = m_u8CmdBuf;

    m_stEventBuf.u16Rx  = 0;
    m_stEventBuf.u16Tx  = 0;
    m_stEventBuf.pu8Buf = m_u8EventBuf;

    m_u8State = HCI_STATE_TYPE;

    m_stEvent.u8Type = HCI_TYPE_EVENT;

    memset(&m_stCmdHeader, 0, sizeof(stHciCmdHeader_t));
}

/**
 * @brief  Creat hci app task
 * @return Status: @ref EN_ERR_STA_T.
 */
static EN_ERR_STA_T hci_task_init(void)
{
    const osThreadAttr_t eventAttr = {
        "hci_app_event",
        osThreadJoinable,
        &hciAppEventCB,
        sizeof(hciAppEventCB),
        &hciAppEventStack[0],
        sizeof(hciAppEventStack),
        osPriorityNormal,
        0,
    };

    const osThreadAttr_t cmdAttr = {
        "hci_app_cmd",
        osThreadJoinable,
        &hciAppCmdCB,
        sizeof(hciAppCmdCB),
        &hciAppCmdStack[0],
        sizeof(hciAppCmdStack),
        osPriorityNormal,
        0,
    };

    hciAppEventTaskId = osThreadNew(hci_app_event_task, NULL, &eventAttr);
    if (NULL == hciAppEventTaskId)
    {
        PRINTF("hci app event task creat fail.\n");
        return ERR_STA_ERROR;
    }

    hciAppCmdTaskId = osThreadNew(hci_app_cmd_task, NULL, &cmdAttr);
    if (NULL == hciAppCmdTaskId)
    {
        PRINTF("hci app cmd task creat fail.\n");
        return ERR_STA_ERROR;
    }

    PRINTF("hci_task_init done.\n");

    return ERR_STA_OK;
}

/**
 * @brief  Hci app init
 */
void hci_app_init(void)
{
    hci_gpio_init();
    hci_buffer_init();
    hci_dma_init();
    hci_task_init();
}
