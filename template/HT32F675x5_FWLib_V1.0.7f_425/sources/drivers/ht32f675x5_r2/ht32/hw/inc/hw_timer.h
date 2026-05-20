/*************************************************************************************************************
 * @file    hw_timer.h
 * @version V1.1
 * @date    2022-01-18
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


#ifndef __HW_TIMER_H__
#define __HW_TIMER_H__


#ifdef __cplusplus
extern "C" {
#endif





/**********************************************************************************************************************
 *                                                   Timer Function
 *********************************************************************************************************************/

/**
 * @brief  Trigger timer configuration valid.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel will be cfg, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_trig_cfg_valid(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Select timer work mode by write TIMER_MODE register with indicated bits
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_work_mode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Get timer mode configuration.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  pu32Mode: Point to timer mode configuration.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_get_mode(stTIMER_Handle_t* pstTIMER,  uint32_t* pu32Mode);


/**
 * @brief  Configure a indicated timer clock prescale.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer init clock, @ref EN_TIMER_CH_T.
 * @param  u8Prescale: The divider for the input clock, the range of u8Prescale is 0 to 0x0F.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_clock_prescale(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint8_t u8Prescale);


/**
 * @brief  Configure a indicated timer counter mode.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @param  enMode: Timer counter mode control, @ref EN_TIMER_CNT_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_counter_mode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,
                                                    EN_TIMER_CNT_MODE_T enMode);


/**
 * @brief  Get timer configuration.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  pu32Cfg: Point to timer configuration.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_get_cfg(stTIMER_Handle_t* pstTIMER, uint32_t* pu32Cfg);


/**
 * @brief  Start a indicated timer.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be start, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_start(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Stop a indicated timer.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be stop, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_stop(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Get a indicated timer current counter.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate get which timer counter, @ref EN_TIMER_CH_T.
 * @param  pu32Cnt: Current timer counter.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_get_counter(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t* pu32Cnt);


/**
 * @brief  Clear a indicated timer counter.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be clear, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_clear_counter(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Configure a indicated timer compare value
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config compare value, @ref EN_TIMER_CH_T.
 * @param  u32Value: Compare value.
 *         16-bit timer: the range of compare value is 0 to 0xFFFF.
 *         32-bit timer: the range of compare value is 0 to 0xFFFFFFFF.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_compare(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t u32Value);


/**
 * @brief  Get a indicated timer compare value.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate get which timer compare value, @ref EN_TIMER_CH_T.
 * @param  pu32Value: Point to compare value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_get_compare(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t* pu32Value);


/**
 * @brief  Get indicated timer interrupt flag(status) by read the TIMER_INT_FLAG register.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer, @ref EN_TIMER_CH_T.
 * @param  pu32Msk: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_get_interrupt_flag(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t* pu32Msk);


/**
 * @brief  Clear indicated TIMER interrupt flag(status) by write the TIMER_INT_CLR register.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer, @ref EN_TIMER_CH_T.
 * @param  u32Msk: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_clear_interrupt_flag(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t u32Msk);


/**
 * @brief  Enable indicated TIMER interrupt byt write TIMER_INT_EN register with indicated bits.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer, @ref EN_TIMER_CH_T.
 * @param  u32IntEn: Indicate which interrupt will be enable,
 *                   bit-1 means enable
 *                   bit-0 means no impact
 *                   @ref EN_TIMER_INT_FLAG_T
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_enable_interrupt(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t u32IntEn);


/**
 * @brief  Disable indicated TIMER interrupt byt write TIMER_INT_EN register with indicated bits.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer, @ref EN_TIMER_CH_T
 * @param  u32IntDis: Indicate which interrupt will be disable,
 *                    bit-1 means disable
 *                    bit-0 means no impact
 *                    @ref EN_TIMER_INT_FLAG_T
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_disable_interrupt(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t u32IntDis);


/**
 * @brief  Enable timer wakeup function.
 * @param  pstTIMER: TIMER handle, Should be TIMER2/TIMER3.
 * @param  enCh: Indicate which timer, @ref EN_TIMER_CH_T.
 * @param  u32En: Indicate which wakeup source will be enable, @ref EN_TIMER_WAKEUP_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_enable_wakeup(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,  uint32_t u32En);


/**
 * @brief  Disable timer wakeup function.
 * @param  pstTIMER: TIMER handle, Should be TIMER2/TIMER3.
 * @param  enCh: Indicate which timer, @ref EN_TIMER_CH_T.
 * @param  u32Dis: Indicate which wakeup source will be disable, @ref EN_TIMER_WAKEUP_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_disable_wakeup(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t u32Dis);


/**
 * @brief  Enable a indicated timer start to work synchronously function.
 *         Multiple timer can start to work synchronously.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_enable_sync_start(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  disable a indicated timer start to work synchronously function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_disable_sync_start(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Enable a indicated timer stop work synchronously function.
 *         Multiple timer can stop work synchronously.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_enable_sync_stop(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Disable a indicated timer stop work synchronously function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_disable_sync_stop(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Configure a indicated timer compare value valid for the next compare period.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_enable_compare_volid_delay(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Configure a indicated timer compare value valid immediately.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_disable_compare_volid_delay(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Get a indicated timer work status.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer, @ref EN_TIMER_CH_T.
 * @param  pu8Status: Timer work status, @ref EN_TIMER_STATUS_T.
 *         TIMER_STATUS_RUNNING: Timer is running;
 *         TIMER_STATUS_STOP: Timer is disable or stop.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_get_work_status(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint8_t* pu8Status);


/**
 * @brief  Get a indicated timer counter mode.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer, @ref EN_TIMER_CH_T.
 * @param  pu8Mode: Timer counter mode, @ref EN_TIMER_COUNTER_MODE_T.
 *         TIMER_COUNTER_MODE_DECREASE: Timer is working at decrease mode;
 *         TIMER_COUNTER_MODE_INCREASE: Timer is working at increase mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_get_counter_mode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint8_t* pu8Mode);


/**
 * @brief  Get timer wakeup source work status.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  pu8Status: Point to save timer wakeup source work status.
 * @return status: @ref EN_ERR_STA_T.
 **/
extern EN_ERR_STA_T rom_hw_timer_get_wakeup_status(stTIMER_Handle_t* pstTIMER, uint8_t* pu8State);




/**********************************************************************************************************************
 *                                              Timer PWM Function
 *********************************************************************************************************************/

/**
 * @brief  Enable PWM module.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer's pwm enable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_enable_pwm(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Disable PWM module.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer's pwm disable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_disable_pwm(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Configure a indicated timer compare high and low counter.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel will be config, @ref EN_TIMER_CH_T.
 * @param  u32HiCount: Compare high counter.
 * @param  u32LoCount: Compare low counter.
 *         16-bit timer: the range of counter value is 0 to 0xFFFF.
 *         32-bit timer: the range of counter value is 0 to 0xFFFFFFFF.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_pwm_hi_low_cnt(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,
                                                      uint32_t u32HiCount, uint32_t u32LoCount);


/**
 * @brief  Get a specified pwm channel of high and low counter.
 * @param  pstTIMER: Timer handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel, @ref EN_TIMER_CH_T.
 * @param  pu32HiCount: Point to PWM high counter.
 * @param  pu32LoCount: Point to PWM low counter.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_get_pwm_hi_low_cnt(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,
                                                      uint32_t* pu32HiCount, uint32_t* pu32LoCount);


/**
 * @brief  Set pwm polarity.
 * @param  pstTIMER: Timer handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate config which channel, @ref EN_TIMER_CH_T.
 * @param  enPol: Pwm polarity, @ref EN_PWM_POLARITY_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_pwm_polarity(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, EN_PWM_POL_T enPol);




/**********************************************************************************************************************
 *                                              Timer Capture Function
 *********************************************************************************************************************/

/**
 * @brief  Enable timer capture function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel enable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_enable_capture(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Disable timer capture function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel disable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_disable_capture(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Configure capture and decode signal source.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel, @ref EN_TIMER_CH_T.
 * @param  enSignal: Capture signal, @ref EN_CAP_DECODE_SIGNAL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_capture_and_decode_src(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,
                                                            EN_CAP_DECODE_SIGNAL_T enSignal);


/**
 * @brief  Set a indicated timer capture channel B signal source.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enSrc: Capture channel B signal source, @ref EN_CAP_CHB_SRC_T,
 *         TIMER_CAP_CHB_SRC_GPIO_IR: Capture channel B signal source is GPIO or IR,
 *         TIMER_CAP_CHB_SRC_DECODE: Capture channel B signal source is channel A decode signal.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_capture_chb_src(stTIMER_Handle_t* pstTIMER, EN_CAP_CHB_SRC_T enSrc);


/**
 * @brief  Configure capture mode.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @param  enMode: Capture mode, @ref EN_CAP_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_capture_mode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, EN_CAP_MODE_T enMode);


/**
 * @brief  Get a indicated timer capture counter.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel, @ref EN_TIMER_CH_T.
 * @param  pu32CapCnt: Point to capture counter.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_get_capture_counter(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t* pu32CapCnt);


/**
 * @brief  Configure capture trigger mode.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel, @ref EN_TIMER_CH_T.
 * @param  enMode: Capture trigger mode, @ref EN_CAP_TRIG_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_capture_trig_mode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,
                                                       EN_CAP_TRIG_MODE_T enMode);


/**
 * @brief  Configure capture counter format.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel, @ref EN_TIMER_CH_T.
 * @param  enFornmat: Capture counter format, @ref EN_CAP_CNT_FORMAT_T.
 *         CAP_CNT_FORMAT_UNSIGNED: Capture counter is unsigned.
 *         CAP_CNT_FORMAT_SIGNED: Capture counter is signed.
 *                                When capture work at 16-bit, counter[15] = 0, means input signal is low level;
 *                                counter[15] = 1, means input signal is high level.
 *                                When capture work at 32-bit, counter[31] = 0, means input signal is low level;
 *                                counter[31] = 1, means input signal is high level.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_capture_counter_format(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,
                                                            EN_CAP_CNT_FORMAT_T enFornmat);





/**********************************************************************************************************************
 *                                              Timer Decode Function
 *********************************************************************************************************************/

/**
 * @brief  Enable timer decode function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be enable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_enable_decode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Disable decode function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be disable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_disable_decode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Configure Decode Polarity.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @param  enMode: Decode polarity, @ref EN_DECODE_POL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_decode_pol(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, EN_DECODE_POL_T enPol);


/**
 * @brief  Configure Decode Mode.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @param  enMode: Decode mode, @ref EN_DECODE_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_decode_mode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, EN_DECODE_MODE_T enMode);


/**
 * @brief  Set a indicated timer decode interval.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel will be config, @ref EN_TIMER_CH_T.
 * @param  u8Val: The value of decode interval.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_timer_set_decode_interval(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint8_t u8Val);




#ifdef __cplusplus
}
#endif



#endif /* __HW_TIMER_H__ */


