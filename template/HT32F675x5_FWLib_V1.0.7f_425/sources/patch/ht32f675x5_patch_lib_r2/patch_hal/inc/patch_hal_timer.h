/*************************************************************************************************************
 * @file    patch_hal_timer.h
 * @version V1.0
 * @date    2024-05-06
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


#ifndef __PATCH_HAL_TIMER_H__
#define __PATCH_HAL_TIMER_H__

/**
 * @brief  Config an indicated pwm frequency and duty.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which pwm config frequency and duty, @ref EN_PWM_CH_T.
 * @param  u32Frequency: pwm output frequency, unit: Hz.
 * @param  u16Duty: pwm duty, 0 ~ 10000 -> (0% ~ 100.00%), accuracy: Timer CLK / PWM Frequency.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hal_timer_pwm_init(stTIMER_Handle_t *pstTIMER, EN_TIMER_CH_T enCh,
                                             uint32_t u32Frequency, uint16_t u16Duty);

#endif