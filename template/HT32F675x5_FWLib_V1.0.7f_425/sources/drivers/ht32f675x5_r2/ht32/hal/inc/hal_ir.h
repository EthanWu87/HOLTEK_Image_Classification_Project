/*************************************************************************************************************
 * @file    hal_ir.h
 * @version V1.1
 * @date    2022-01-25
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


#ifndef __HAL_IR_H__
#define __HAL_IR_H__


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef union
{
    struct
    {
        uint32_t FristDurTimerUs     : 16;
        uint32_t SecendDurTimerUs    : 16;

    } stDurTimerUs_t;

    struct
    {
        uint32_t b15FristDurTimerUs  : 15;
        uint32_t b1FristLevel        : 1;

        uint32_t b15SecendDurTimerUs : 15;
        uint32_t b1SecendLevel       : 1;

    } stFromatDurTimerUs;

} unIR_SendSignalData_t, *punIR_SendSignalData_t;




/**
 * @brief  Initialize a indicated ir timer clock.
 * @param  pstIR: IR handle, should be IR0 / IR1 / IR2 / IR3.
 * @param  u32Frequency: pwm output frequency of carrier, unit: Hz.
 * @param  u8Duty: pwm duty of carrier.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_ir_send_init(stTIMER_Handle_t* pstIR, uint32_t u32Freq, uint16_t u16Duty,
                                         EN_IR_SEND_PATH_T enPath);


/**
 * @brief  IR send start.
 * @param  pstIR: IR handle, should be IR0 / IR1 / IR2 / IR3.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_ir_start_send(stTIMER_Handle_t* pstIR);


/**
 * @brief  IR send stop.
 * @param  pstIR: IR handle, should be IR0 / IR1 / IR2 / IR3.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_ir_stop_send(stTIMER_Handle_t* pstIR);


/**
 * @brief  Config a indicated channel prescale.
 * @param  pstIR: IR handle, should be IR0 / IR1 / IR2 / IR3.
 * @param  enCh: IR channel.
 * @param  u8Prescale: The divider for the input clock, the range of u8Prescale is 0~15.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_ir_config_clock(stTIMER_Handle_t* pstIR, EN_IR_CH_T enCh, uint8_t u8Prescale);


/**
 * @brief  Config IR next peroid compare value.
 * @param  pstIR: IR handle, should be IR0 / IR1 / IR2 / IR3.
 * @param  punIrData: Config data @ref unIR_SendSignalData_t.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_ir_send_next_signal_level(stTIMER_Handle_t* pstIR, unIR_SendSignalData_t* punIrData);


/**
 * @brief  IR study init.
 * @param  pstIR: IR handle, should be IR0 / IR1 / IR2 / IR3.
 * @param  pstDecodeInit: Decode init struct type.
 *         .u8Prescale: The divider for the input clock, the range of u8Prescale is 0~15.
 *         .u8Mode: Decode mode, @ref EN_DECODE_MODE_T.
 *         .u8Pol: Decode polarity, @ref EN_DECODE_POL_T.
 *         .u8Value: The value of decode interval.
 * @param  pstCapInit: Capture init struct type.
 *         .u8Prescale: The divider for the input clock, the range of u8Prescale is 0~15.
 *         .u8Signal: Capture signal, @ref EN_CAP_SIGNAL_T.
 *         .u8Mode: Capture mode, @ref EN_CAP_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_ir_study_init(stTIMER_Handle_t* pstIR, stDecodeInit_t* pstDecodeInit,
                                          stCapInit_t* pstCapInit);


/**
 * @brief  Start IR study.
 * @param  pstIR: IR handle should be IR0 / IR1 / IR2 / IR3.
 * @param  u8Rtune: Set resistance of R in RC filter, R = 50K*2^(u8Rtune).
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_ir_start_study(stTIMER_Handle_t* pstIR, uint8_t u8Rtune);


/**
 * @brief  IR study stop.
 * @param  pstIR: IR handle should be IR0 / IR1 / IR2 / IR3.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_ir_stop_study(stTIMER_Handle_t* pstIR);



#endif /* __HAL_IR_H__ */

