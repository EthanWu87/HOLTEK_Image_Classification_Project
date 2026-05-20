/*************************************************************************************************************
 * @file    ht32f67595_evb.h
 * @version V1.0
 * @date    2022-09-22
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


#ifndef __HT32F67595_EVB__H__
#define __HT32F67595_EVB__H__

// Key pin
#define GPIO_PORT_KEY                      (GPIOB)
#define GPIO_PIN_KEY                       (GPIO_PIN_3)  //P35, PB3

// UART Pins
// UART0
#define GPIO_PORT_UART0_TX                 (GPIOB)
#define GPIO_PIN_UART0_TX                  (GPIO_PIN_2)  //P34, PB2
#define GPIO_PORT_UART0_RX                 (GPIOB)
#define GPIO_PIN_UART0_RX                  (GPIO_PIN_13) //P45, PB13

// UART1
#define GPIO_PORT_UART1_TX                 (GPIOA)
#define GPIO_PIN_UART1_TX                  (GPIO_PIN_30) //P30, PA30
#define GPIO_PORT_UART1_RX                 (GPIOA)
#define GPIO_PIN_UART1_RX                  (GPIO_PIN_29) //P29, PA29

// UART2
#define GPIO_PORT_UART2_TX                 (GPIOA)
#define GPIO_PIN_UART2_TX                  (GPIO_PIN_20) //P20, PA20
#define GPIO_PORT_UART2_RX                 (GPIOA)
#define GPIO_PIN_UART2_RX                  (GPIO_PIN_18) //P18, PA18

#endif /* __HT32F67595_EVB__H__ */

