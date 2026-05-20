/*************************************************************************************************************
 * @file    ble_init.h
 * @version V1.0
 * @date    2023-05-26
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


#ifndef __BLE_INIT_H__
#define __BLE_INIT_H__

/**
 * @brief  ble init.
 */
extern EN_ERR_STA_T ble_init(void);

/**
 * @brief  check if system can go to sleep
 * @return false(0) - system can not goto sleep.
 * @return true(1)  - system can goto sleep.
 */
bool ble_init_is_system_sleep_allowed(void);

/**
 * @brief when system wakeup by llc, invoke this func
 */
void ble_init_on_system_wakeup_by_llc(void);

#endif /* __BLE_INIT_H__ */
