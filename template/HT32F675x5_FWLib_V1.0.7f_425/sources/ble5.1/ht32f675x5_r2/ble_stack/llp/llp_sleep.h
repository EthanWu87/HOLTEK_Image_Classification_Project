/*************************************************************************************************************
 * @file    llp_sleep.h
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
#ifndef LLP_SLEEP_H
#define LLP_SLEEP_H

void rom_llp_sleep_init(void);

void rom_llp_sleep_set_time(uint16_t u16SleepThresholdTimeUs, uint16_t u16WakeupTimeUs);

void rom_llp_sleep_wakeup(void);

void rom_llp_sleep_on_fragment_config_succeed(uint64_t u64FragmentStartTime);

void rom_llp_sleep_on_wakeup_interrupt(void);

void rom_llp_sleep_on_system_wakeup_by_llc(void);

bool rom_llp_sleep_is_system_sleep_allowed(void);


#endif
