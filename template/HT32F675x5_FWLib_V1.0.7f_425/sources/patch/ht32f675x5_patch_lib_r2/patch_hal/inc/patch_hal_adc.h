/*************************************************************************************************************
 * @file    patch_hal_adc.h
 * @version V1.0
 * @date    2023-08-19
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


#ifndef __PATCH_HAL_ADC_H__
#define __PATCH_HAL_ADC_H__

/**
 * @brief  ADC init function.
 * @param  pstADCInitHandle: ADC init handle, @ref stADCInitHandle_t.
 *         .pstADCHandle: ADC handle, should be ADC0 / ADC1;
 *         .u8Resolution: ADC resolution, should be 10Bit / 12Bit;
 *         .enCh: ADC sample channel(s), @ref EN_ADC_CH_T;
 *         .enSampMode: ADC sample mode, @ref EN_ADC_SAMP_MODE_SEL_T;
 *         .enSampSrc: ADC sample source, @ref EN_ADC_SAMP_SRC_SEL_T;
 *         .enPwmSampSrc: @ref EN_ADC_PWM_SAMP_SRC_SEL_T;
 * @param  u16SampNum: Each adc channel sample number when sample mode is ADC_SAMP_BY_AUTO_TRIG,
 *                     can not set to 0 when sample mode is others.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hal_adc_init(stADCInitHandle_t *pstADCInitHandle, uint16_t u16SampNum);

/**
 * @brief  Transform adc sample data to voltage.
 * @param  pstADCInitHandle: ADC init handle, @ref stADCInitHandle_t.
 * @param  enCh: ADC Channel, @ref EN_ADC_CH_T.
 * @param  u16ADCSampData: ADC sample data.
 * @param  pu16Volt: ADC voltage, unit is mV.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hal_adc_trans_voltage(stADCInitHandle_t *pstADCInitHandle, EN_ADC_CH_T enCh, uint16_t u16ADCSampData,
                                                uint16_t *pu16Volt);

/**
 * @brief  Get adc value for one channel.
 * @param  pstADCInitHandle: ADC init handle, @ref stADCInitHandle_t.
 * @param  enCh: ADC channel.
 * @param  pu16Volt: Pointer to adc sample voltage, unit is mV.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hal_adc_get_voltage(stADCInitHandle_t *pstADCInitHandle, EN_ADC_CH_T enCh, uint16_t *pu16Volt);

/**
 * @brief  Get adc value for one channel.
 * @param  pstADCInitHandle: ADC init handle, @ref stADCInitHandle_t.
 * @param  enCh: ADC channel.
 * @output pu16Value: Pointer to adc sample data.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hal_adc_get_data(stADCInitHandle_t *pstADCInitHandle, EN_ADC_CH_T enCh, uint16_t *pu16Value);

#endif /* __PATCH_HAL_ADC_H__ */
