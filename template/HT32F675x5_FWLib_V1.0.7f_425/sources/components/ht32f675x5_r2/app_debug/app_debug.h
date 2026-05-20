/*************************************************************************************************************
 * @file    app_debug.h
 * @version V1.0
 * @date    2020-05-07
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


#ifndef __APP_DEBUG_H__
#define __APP_DEBUG_H__

/**
 * @brief  TYPEDEF STRUCT
 */
typedef struct
{
    uint8_t *pu8buf;
    uint16_t u16MaxLen;

} stDebugBuf_t;

/**
 * @brief  App debug init.
 * @param  pstGPIO: GPIO handle, Should be GPIOA/GPIOB.
 * @param  enPin: The pin which would be set tx function.
 * @param  pstUART: UART handle, Should be PERI_UART0/PERI_UART1/PERI_UART2.
 * @param  u32BaudRate: Uart baudrate.
 * @param  pststDebugBuf: Point to app debug buf struct.
 * @return retuen status, @ref EN_HAL_STA_T.
 */
extern EN_ERR_STA_T app_debug_init(stGPIO_Handle_t *pstGPIO, uint32_t u32Pin, stUART_Handle_t *pstUART,
                                   uint32_t u32BaudRate, stDebugBuf_t *pststDebugBuf);

/**
 * @brief  Set app debug io high impedance
 */
extern void app_debug_deinit(void);

/**
 * @brief  App debug reinit
 * @return retuen status, @ref EN_HAL_STA_T
 */
extern EN_ERR_STA_T app_debug_reinit(void);

/**
 * @brief  Check app debug is print done
 * @return status: false(0) - app debug is working.
 *                 true(1)  - app debug is idle.
 */
extern bool app_debug_print_complete(void);

/**
 * @brief  Print all data by uart.
 */
extern void app_debug_printf(void);

/**
 * @brief  Print hex string.
 * @param  pPreStr: Preamble string.
 * @param  pu8Buf: Data buffer.
 * @param  u16BufLen: Buffer length.
 */
extern void app_debug_printf_hex_string(char *pPreStr, const uint8_t *pu8Buf, uint16_t u16BufLen);

#endif /* __APP_DEBUG_H__ */
