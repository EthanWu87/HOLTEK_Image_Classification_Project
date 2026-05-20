/*************************************************************************************************************
 * @file    hw_uart.h
 * @version V1.1
 * @date    2022-01-13
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


#ifndef __HW_UART_H__
#define __HW_UART_H__

#include "err_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */




typedef enum
{
    UART_BAUDRATE_MIN     = ( 0x00 ),
    UART_BAUDRATE_2400    = ( 2400 ),
    UART_BAUDRATE_9600    = ( 9600 ),
    UART_BAUDRATE_14400   = ( 14400 ),
    UART_BAUDRATE_19200   = ( 19200 ),
    UART_BAUDRATE_38400   = ( 38400 ),
    UART_BAUDRATE_57600   = ( 57600 ),
    UART_BAUDRATE_115200  = ( 115200 ),
    UART_BAUDRATE_256000  = ( 256000 ),
    UART_BAUDRATE_921600  = ( 921600 ),
    UART_BAUDRATE_1000000 = ( 1000000 ),
    UART_BAUDRATE_1500000 = ( 1500000 ),
    UART_BAUDRATE_1600000 = ( 1600000 ),
    UART_BAUDRATE_2000000 = ( 2000000 ),
    UART_BAUDRATE_MAX     = ( UART_BAUDRATE_2000000 )

} EN_UART_BARDRATE_T;


typedef enum
{
    UART_DIVISOR_2400    = ( 0x03B81A09 ),
    UART_DIVISOR_9600    = ( 0x00EE0681 ),
    UART_DIVISOR_14400   = ( 0x009E0456 ),
    UART_DIVISOR_19200   = ( 0x00770340 ),
    UART_DIVISOR_38400   = ( 0x003B019F ),
    UART_DIVISOR_57600   = ( 0x00270114 ),
    UART_DIVISOR_115200  = ( 0x00130089 ),
    UART_DIVISOR_256000  = ( 0x0008003D ),
    UART_DIVISOR_921600  = ( 0x00020010 ),
    UART_DIVISOR_1000000 = ( 0x0002000F ),
    UART_DIVISOR_1500000 = ( 0x00010009 ),
    UART_DIVISOR_1600000 = ( 0x00010009 ),
    UART_DIVISOR_2000000 = ( 0x00010007 ),

} EN_UART_DIVISOR_T;

/* This macro checks if BAUDRATE is a valid UART baudrate */
#define IS_UART_BAUDRATE_VALID(BAUDRATE) ((( BAUDRATE) > UART_BAUDRATE_MIN ) && ((BAUDRATE) <= UART_BAUDRATE_MAX))



/**
  * @brief HAL UART State structures definition
  */
typedef enum
{
    UART_STATE_RESET             = 0x00,    /*!< Peripheral is not initialized                      */
    UART_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use           */
    UART_STATE_BUSY              = 0x02,    /*!< an internal process is ongoing                     */
    UART_STATE_BUSY_TX           = 0x12,    /*!< Data Transmission process is ongoing               */
    UART_STATE_BUSY_RX           = 0x22,    /*!< Data Reception process is ongoing                  */
    UART_STATE_BUSY_TX_RX        = 0x32,    /*!< Data Transmission and Reception process is ongoing */
    UART_STATE_TIMEOUT           = 0x03,    /*!< Timeout state                                      */
    UART_STATE_ERROR             = 0x04     /*!< Error                                              */
} EM_UART_STATE_T;


typedef union
{
    uint32_t u32UartCfg;
    struct
    {
        uint32_t u8TxFifoThld    : 5;    /**<  */
        uint32_t u8RxFifoThld    : 5;    /**<  */
        uint32_t u8StopBits      : 2;    /**< Specifies the number of stop bits transmitted */
        uint32_t u8DataBits      : 2;    /**< Specifies the number of data bits transmitted in a frame
                                                         This parameter can be a value of @ref UART_Word_Length **/
        uint32_t u8ParityBits    : 3;    /**< Specifies the parity mode,This parameter can be a value of @ref UART_Parity */
        uint32_t u8EndianMode    : 1;    /**<  */
        uint32_t u8LineBreakEn   : 1;    /**< Specifies whether the hardware flow control mode is enabled or disabled */
        uint32_t u8FlowCtrlEn    : 1;
        uint32_t u8RtsThld       : 5;
        uint32_t u8ErrDiscard    : 1;
    } stUartCfg;
    struct
    {
        uint32_t u8TxFifoThld    : 4;    /**<  */
        uint32_t u8RxFifoThld    : 4;    /**<  */
        uint32_t u8RxToThld      : 8;    /**<   */
        uint32_t u8StopBits      : 2;    /**< Specifies the number of stop bits transmitted */
        uint32_t u8DataBits      : 2;    /**< Specifies the number of data bits transmitted in a frame
                                                         This parameter can be a value of @ref UART_Word_Length **/
        uint32_t u8ParityBits    : 3;    /**< Specifies the parity mode,This parameter can be a value of @ref UART_Parity */
        uint32_t u8EndianMode    : 1;    /**<  */
        uint32_t u8LineBreakEn   : 1;    /**< Specifies whether the hardware flow control mode is enabled or disabled */
        uint32_t u8FlowCtrlEn    : 1;
        uint32_t u8RtsThld       : 4;
        uint32_t u8ErrDiscard    : 1;
        uint32_t u8UartSccSel    : 1;
    } stUart2Cfg;
} unUartCfg_t;

/**
  * @brief Structure definition of UART initialization
  * @{
  */
typedef struct
{
    uint32_t    u32UartBaudRate;           /*!< This member configures the UART communication baud rate. */
    unUartCfg_t unUartCfg;

} stUartInit_t, *pstUartInit_t;


#define UART_TXFIFO_DEFAULT_THLD          ( 0x06 )
#define UART_RXFIFO_DEFAULT_THLD          ( 0x06 )


#define UART_DMA_FIFO_DEFAULT_THLD        ( 0x01 )
#define UART_FLOW_CONTROL_DEFAULT_THLD    ( 0x05 )
#define UART_RTS_DEFAULT_THLD             ( 0x06 )

#define UART_RX_TIMEOUT_DEFAULT           ( 0xFF ) //32 us




/**
 * @brief  DeInitializes the UART peripheral.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_deinit(stUART_Handle_t* pstUART);


/**
 * @brief  Initializes the UART mode according to the specified parameters in
 *         the stUartInit_t and create the associated handle.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  stUartInit_t: Pointer to a stUartInit_t structure that contains the initial structure.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_init(stUART_Handle_t* pstUART, stUartInit_t* pstInitType);


/**
 * @brief  Set uart baudrate.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  u32BaudRate: baudrate.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_set_baudrate(stUART_Handle_t* pstUART, uint32_t u32BaudRate);


/**
 * @brief  Set UART DATA BITS.
 *         Databit is upward compatible, high data bits can correctly receive data with low data bits,
 *         databit5 maximum is 31, databit6 maximum is 63,
 *         databit7 maximum is 127, databit8 maximum is 255.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  enSize: UART data size, @ref EN_UART_DATA_SIZE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_set_data_sizes(stUART_Handle_t* pstUART, EN_UART_DATA_SIZE_T enSize);


/**
 * @brief  Set UART stop bit.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  enStopbits: UART stop bit, @ref EN_UART_STOP_SIZE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_set_stop_sizes(stUART_Handle_t* pstUART, EN_UART_STOP_SIZE_T enStopbits);


/**
 * @brief  Set UART parity.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  enParity: UART parity, @ref EN_UART_PARITY_BITS_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_set_parity(stUART_Handle_t* pstUART, EN_UART_PARITY_BITS_T enParity);


/**
 * @brief  Set UART endian mode.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  enMode: UART endian mode, @ref EN_UART_ENDIAN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_set_mode(stUART_Handle_t* pstUART, EN_UART_ENDIAN_T enMode);


/**
 * @brief  Set Tx FIFO under threshold level, When TX Fifo is under this threshold, it trigger a interrupt.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  u8Thld: Threshold for UART TX FIFO.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_set_txfifo_thld(stUART_Handle_t* pstUART, uint8_t u8Thld);


/**
 * @brief  Set rx FIFO over threshold level, When RX Fifo is over the threshold, it trigger a interrupt.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  u8Thld: Threshold for UART RX FIFO.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_set_rxfifo_thld(stUART_Handle_t* pstUART, uint8_t u8Thld);


/**
 * @brief  Uart config the send line break function.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  enEn: Enalbe or disable RX line break function.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_line_break_enable(stUART_Handle_t* pstUART, EN_UART_LB_EN_T enEn);


/**
 * @brief  Set uart rx timeout.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  u8SymbolNum: Time out value, unit: ms.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_set_rx_timeout(stUART_Handle_t* pstUART, uint8_t u8SymbolNum);


/**
 * @brief  Uart config flow function.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  enEn: Enalbe or disable flow function, @ref EN_UART_FLOW_EN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_flow_enable(stUART_Handle_t* pstUART, EN_UART_FLOW_EN_T enEn);


/**
 * @brief  Set rts threshold.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  u8Thld: Threshold for UART RTS.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_set_rts_thld(stUART_Handle_t* pstUART, uint8_t u8Thld);


/**
 * @brief  uart configur clear fifo function.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_clear_rxfifo(stUART_Handle_t* pstUART);


/**
 * @brief  Get uart tx fifo count.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  pu8Cnt: Tx fifo count values.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_get_txfifo_cnt(stUART_Handle_t* pstUART, uint8_t* pu8Cnt);


/**
 * @brief  Get uart rx fifo count.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  pu8Cnt: Rx fifo count values.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_get_rxfifo_cnt(stUART_Handle_t* pstUART, uint8_t* pu8Cnt);


/**
 * @brief  Get uart interrupt flag(status).
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  pu16Falg: Indicate which interrupt flag will be read, @ref EN_UART_INT_FLAG_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_get_interrupt_flag(stUART_Handle_t* pstUART, uint16_t* pu16Falg);


/**
 * @brief  Set uart interrupt enable.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  u16Msk: Indicate which interrupt will be enable, @ref EN_UART_INT_FLAG_T.
 *                 bit-1 means enable
 *                 bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_enable_interrupt(stUART_Handle_t* pstUART, uint16_t u16Msk);


/**
 * @brief  set uart interrupt enable.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  u16Msk: indicate which interrupt will be disable, @ref EN_UART_INT_FLAG_T.
 *                 bit-1 means disable
 *                 bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_disable_interrupt(stUART_Handle_t* pstUART, uint16_t u16Msk);


/**
 * @brief  Clear uart indicated interrupt flag.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  u16Msk: Indicate which flag will be clear, @ref EN_UART_INT_FLAG_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_clear_interrupt_flag(stUART_Handle_t* pstUART, uint16_t u16Msk);


/**
 * @brief  Get a byte data in non blocking mode.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  pu8Data: Pointer to data buffer.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_get_byte(stUART_Handle_t* pstUART, uint8_t* pu8Data);


/**
 * @brief  Receives an amount of data in non blocking mode.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  pu8Data: Pointer to data buffer.
 * @param  u8BufSize: Amount of data to be received.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_receive(stUART_Handle_t* pstUART, uint8_t* pu8Buf, uint8_t u8BufSize);


/**
 * @brief  Transmits single data through the UART when TX FIFO is not fulled, blocking while sending.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  u8Data: The data to transmit.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_send_byte(stUART_Handle_t* pstUART, uint8_t u8Data);


/**
 * @brief  Transmit an amount of data in blocking mode.
 * @param  pstUART: UART handle, Should be UART0 / UART1 / UART2.
 * @param  pu8Data: Pointer to data buffer.
 * @param  u16Len: Amount of data to be sent.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_uart_transmit(stUART_Handle_t* pstUART, uint8_t* pu8Buf, uint16_t u16Len);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HW_UART_H__ */


