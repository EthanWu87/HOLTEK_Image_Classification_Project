/*************************************************************************************************************
 * @file    uart.h
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
#ifndef UART_H
#define UART_H

typedef void (*uart_recv_callback_t)(uint8_t* pu8Data, uint16_t u16DataLen);

/**
 * @brief  UART Init.
 * @param  recvCb: Received Callback Function.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T uart_init(uart_recv_callback_t recvCb);

/**
 * @brief  UART Deinit.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T uart_deinit(void);
/**
 * @brief  UART Reinit.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T uart_reinit(void);

/**
 * @brief  UART Send Bytes.
 * @param  pu8Buf: Send Data Buffer
 * @param  u16Len: The length of Send Data
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T uart_send_bytes(uint8_t *pu8Buf,uint16_t u16Len);


#endif
