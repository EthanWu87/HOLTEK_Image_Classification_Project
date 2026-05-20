/*************************************************************************************************************
 * @file    hal_timer.h
 * @version V1.0
 * @date    2021-02-18
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



#ifndef __HAL_TIMER_H__
#define __HAL_TIMER_H__


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define PWM_FREQUENCY_HZ_MAX         ( 8000000 )
#define BIT16_PWM_FREQUENCY_HZ_MIN   ( 16 )


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    uint8_t  u8Prescale;       /*Divide TIM clock, the range of Prescaler value is 0 to 0xF.*/
    uint32_t u32Compare;       /*Compare value
                                 16-bit timer: the range of compare value is 0 to 0xFFFF.
                                 32-bit timer: the range of compare value is 0 to 0xFFFFFFFF.*/
    uint8_t  u8CounterMode;    /*Counter mode, @ref EN_TIMER_CNT_MODE_T.*/

} stTimerInit_t;

typedef struct
{
    uint8_t u8Prescale;
    uint8_t u8Signal;
    uint8_t u8Mode;
    uint8_t u8Trig;
    uint8_t u8CntFormat;
    uint8_t u8LoopModeEn;

} stCapInit_t;

typedef struct
{
    uint16_t u16CompVal;
    uint8_t  u8Prescale;
    uint8_t  u8Mode;
    uint8_t  u8Pol;
    uint8_t  u8Interval;
    uint8_t  u8Signal;

} stDecodeInit_t;




/**
 * @brief  Enable timer clk.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_enable_clk(stTIMER_Handle_t* pstTIMER);


/**
 * @brief  Disable timer clk.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_disable_clk(stTIMER_Handle_t* pstTIMER);


/**
 * @brief  Init an indicated timer.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel will be enable, @ref EN_TIMER_CH_T.
 * @param  pstTimerInit: Init parameters of timer, @ref stTimerInit_t.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_init(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, stTimerInit_t* pstTimerInit);


/**
 * @brief  Configure an indicated timer compare value.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel will be config compare value.
 * @param  u32Value: Compare value.
 *         16-bit timer: the range of compare value is 0 to 0xFFFF.
 *         32-bit timer: the range of compare value is 0 to 0xFFFFFFFF.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_set_compare(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, uint32_t u32Value);


/**
 * @brief  Config an indicated pwm frequency and duty.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which pwm config frequency and duty, @ref EN_PWM_CH_T.
 * @param  u32Frequency: pwm output frequency, unit: Hz.
 * @param  u16Duty: pwm duty, 0 ~ 10000 -> (0% ~ 100.00%), accuracy: Timer CLK / PWM Frequency.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_pwm_init(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,
                                           uint32_t u32Frequency, uint16_t u16Duty);


/**
 * @brief  Config a indicated pwm compare value and high, low counter.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which pwm config, @ref EN_PWM_CH_T.
 * @param  u32HiCount: PWM high counter.
 * @param  u32LoCount: PWM low counter.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_set_pwm_hi_lo_cnt(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,
                                                    uint32_t u32HiCount, uint32_t u32LoCount);


/**
 * @brief  Enable PWM module.
 * @param  pstTIMER: PWM handle, Should be PWM0 / PWM1 / PWM2 / PWM3.
 * @param  enCh: Indicate which pwm enable, @ref EN_PWM_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_enable_pwm(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Enable PWM module.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which pwm enable, @ref EN_PWM_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_disable_pwm(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Init an indicated timer function of capture.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel will be config, @ref EN_TIMER_CH_T.
 * @param  pstCapInit: Capture init struct, @ref stCapInit_t.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_capture_init(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh, stCapInit_t* pstCapInit);


/**
 * @brief  Enable timer capture function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel enable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_enable_capture(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Disable timer capture function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which channel disable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_disable_capture(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Init a indicated timer, config decode.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be config, @ref EN_TIMER_CH_T.
 * @param  pstDecodeInit: Decode init struct type.
 *         .u8Prescale: The divider for the input clock.
 *          16-bit timer: the range of u8Prescale is [0:16).
 *          32-bit timer: the range of u8Prescale is [0:256).
 *         .u8Mode: Decode mode, @ref EN_DECODE_MODE_T.
 *         .u8Pol: Decode polarity, @ref EN_DECODE_POL_T.
 *         .u8Value: The value of decode interval.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_decode_init(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh,
                                              stDecodeInit_t* pstDecodeInit);


/**
 * @brief  Enable timer decode function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be enable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_enable_decode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);


/**
 * @brief  Disable timer decode function.
 * @param  pstTIMER: TIMER handle, Should be TIMER0 / TIMER1 / TIMER2 / TIMER3.
 * @param  enCh: Indicate which timer will be disable, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_timer_disable_decode(stTIMER_Handle_t* pstTIMER, EN_TIMER_CH_T enCh);




#endif /* __HAL_TIMER_H__ */


