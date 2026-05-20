/*************************************************************************************************************
 * @file    mlog_transport_uart.h
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


#ifndef __MLOG_TRANSPORT_UART_H__
#define __MLOG_TRANSPORT_UART_H__

extern bool mlog_transport_uart_init(stUART_Handle_t *pstUART, stGPIO_Handle_t *pstGPIO, EN_GPIO_PIN_T enumPin,
                                     uint32_t u32BaudRate);

extern bool mlog_transport_uart_reinit(void);

extern void mlog_transport_uart_deinit(void);

extern bool mlog_transport_uart_reinit(void);

extern void mlog_transport_uart_print(void);

#endif /* __MLOG_TRANSPORT_UART_H__ */
