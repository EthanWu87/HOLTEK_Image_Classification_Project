/*************************************************************************************************************
 * @file    ht32f67595_evb.h
 * @version V1.1
 * @date    2025-08-20
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
#define GPIO_PORT_KEY                      (GPIOA)
#define GPIO_PIN_KEY                       (GPIO_PIN_27)  //P27, PA27
#define GPIO_PORT_KEY1                      (GPIOA)
#define GPIO_PIN_KEY1                       (GPIO_PIN_27)  //P27, PA27
#define GPIO_PORT_KEY2                      (GPIOA)
#define GPIO_PIN_KEY2                       (GPIO_PIN_27)  //P24, PA24
#define GPIO_PORT_KEY3                      (GPIOB)
#define GPIO_PIN_KEY3                       (GPIO_PIN_53)  //P53, PB21


// LED pin
#define GPIO_PORT_LED1                      (GPIOB)
#define GPIO_PIN_LED1                       (GPIO_PIN_7)  //P39, PB07
#define GPIO_PORT_LED2                      (GPIOB)
#define GPIO_PIN_LED2                       (GPIO_PIN_9)  //P41, PB09
#define GPIO_PORT_LED3                      (GPIOB)
#define GPIO_PIN_LED3                       (GPIO_PIN_10)  //P42, PB10

// UART Pins
// UART0
#define GPIO_PORT_UART0_TX                 (GPIOA)
#define GPIO_PIN_UART0_TX                  (GPIO_PIN_29) 	//P29, PA29
#define GPIO_PORT_UART0_RX                 (GPIOA)
#define GPIO_PIN_UART0_RX                  (GPIO_PIN_0) 	//P00, PA0

// UART1
#define GPIO_PORT_UART1_TX                 (GPIOB)
#define GPIO_PIN_UART1_TX                  (GPIO_PIN_12) 	//P44, PB12
#define GPIO_PORT_UART1_RX                 (GPIOB)
#define GPIO_PIN_UART1_RX                  (GPIO_PIN_11) 	//P43, PB11

// UART2
#define GPIO_PORT_UART2_TX                 (GPIOA)
#define GPIO_PIN_UART2_TX                  (GPIO_PIN_9) 	//P09, PA9
#define GPIO_PORT_UART2_RX                 (GPIOA)
#define GPIO_PIN_UART2_RX                  (GPIO_PIN_21) 	//P21, PA21

#endif /* __HT32F67595_EVB__H__ */

