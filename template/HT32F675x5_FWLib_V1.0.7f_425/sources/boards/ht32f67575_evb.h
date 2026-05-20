/*************************************************************************************************************
 * @file    ht32f67575_evb.h
 * @version V1.0
 * @date    2023-08-28
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


#ifndef __HT32F67575_EVB__H__
#define __HT32F67575_EVB__H__

// Key pin
#define GPIO_PORT_KEY                      (GPIOB)
#define GPIO_PIN_KEY                       (GPIO_PIN_17) //P49, PB17

// UART Pins
// UART0
#define GPIO_PORT_UART0_TX                 (GPIOB)
#define GPIO_PIN_UART0_TX                  (GPIO_PIN_7)  //P39, PB7
#define GPIO_PORT_UART0_RX                 (GPIOA)
#define GPIO_PIN_UART0_RX                  (GPIO_PIN_28) //P28, PA28

// UART1
#define GPIO_PORT_UART1_TX                 (GPIOB)
#define GPIO_PIN_UART1_TX                  (GPIO_PIN_12) //P44, PB12
#define GPIO_PORT_UART1_RX                 (GPIOB)
#define GPIO_PIN_UART1_RX                  (GPIO_PIN_10) //P42, PB10

// UART2
#define GPIO_PORT_UART2_TX                 (GPIOA)
#define GPIO_PIN_UART2_TX                  (GPIO_PIN_2)  //P02, PA2
#define GPIO_PORT_UART2_RX                 (GPIOA)
#define GPIO_PIN_UART2_RX                  (GPIO_PIN_1)  //P01, PA1

// Flash Pins
#define GPIO_PORT_FLASH_CLK                (GPIOA)
#define GPIO_PIN_FLASH_CLK                 (GPIO_PIN_23) //P23, PA23
#define GPIO_PORT_FLASH_CS                 (GPIOA)
#define GPIO_PIN_FLASH_CS                  (GPIO_PIN_24) //P24, PA24
#define GPIO_PORT_FLASH_SI                 (GPIOA)
#define GPIO_PIN_FLASH_SI                  (GPIO_PIN_25) //P25, PA25
#define GPIO_PORT_FLASH_SO                 (GPIOA)
#define GPIO_PIN_FLASH_SO                  (GPIO_PIN_26) //P26, PA26
#define GPIO_PORT_FLASH_WP                 (GPIOA)
#define GPIO_PIN_FLASH_WP                  (GPIO_PIN_27) //P27, PA27
#define GPIO_PORT_FLASH_HLD                (GPIOA)
#define GPIO_PIN_FLASH_HLD                 (GPIO_PIN_28) //P28, PA28


#endif /* __HT32F67575_EVB__H__ */


