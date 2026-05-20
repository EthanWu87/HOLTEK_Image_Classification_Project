/*************************************************************************************************************
 * @file    err_debug.h
 * @version V1.0
 * @date    2020-12-25
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


#ifndef __ERR_DEBUG_H__
#define __ERR_DEBUG_H__

/**
 * @brief  os_error_handler
 * @param  u32Code
 * @param  pObjectId: pointer to the object
 * @return uint32_t
 */
extern uint32_t os_error_handler(uint32_t u32Code, void *pObjectId);

/**
 * @brief  system_assert_debug
 *         Show the error of system assert
 * @param  adr - it defines in mem.h
 */
extern void system_assert_debug(uint16_t adr, uint32_t info);

extern void system_error_handler(uint16_t u16ErrModule, uint16_t u16ErrLine, uint32_t u32ErrInfo1,
                                 uint32_t u32ErrInfo2);

extern void err_debug_init(void);

#endif /* __ERR_DEBUG_H__ */
