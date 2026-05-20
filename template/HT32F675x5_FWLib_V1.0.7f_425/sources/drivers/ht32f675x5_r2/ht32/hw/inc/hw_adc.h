/*************************************************************************************************************
 * @file    hw_adc.h
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


#ifndef __HW_ADC_H__
#define __HW_ADC_H__

#ifdef __cplusplus
extern "C"{
#endif




//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef union
{
    uint32_t u32Cfg;

    struct
    {
        uint32_t u8DGC          : 5; /**< [4:0] ADC_CIC_DOWNSP_DGC */
        uint32_t reserved       : 1; /**< [5] reserved */
        uint32_t u8DataFormat   : 1; /**< [6] ADC_DATA_FORMAT */
        uint32_t u8CicEn        : 1; /**< [7] ADC_CIC_EN */
        uint32_t u8SampMode     : 1; /**< [8] ADC_SAMP_MODE **/
        uint32_t u8FifoThld     : 2; /**< [10:9] ADC_FIFO_THLD */
        uint32_t u8ClkEn        : 1; /**< [11] ADC_CLK_EN_MODE */
        uint32_t u8DataProcess  : 1; /**< [12] ADC_DATA_PROCESS_MODE */
        uint32_t u8BypassCopmst : 1; /**< [13] ADC_COMPST_FLITER_EN */
        uint32_t u8DownspThld   : 3; /**< [16:14] ADC_DOWNSP_OUT_THLD */

    } stCfg;

} unADCCfg_t;

typedef struct
{
    unADCCfg_t unCfg;
    uint16_t u16StableTimeUs;
    uint16_t u16DownSampValue;
    uint16_t u16SampNum;

} stAdcInit_t;




/**********************************************************************************************************************
 *                                             ADC Interrupt Cfg
 *********************************************************************************************************************/

/**
 * @brief  Get indicated ADC interrupt flag(status).
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  pu32Flag: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_get_interrupt_flag(stADC_Handle_t *pstADC, uint32_t *pu32Flag);


/**
 * @brief  Clear indicated ADC interrupt flag(status).
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  u32Flag: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_clear_interrupt_flag(stADC_Handle_t *pstADC, uint32_t u32Flag);


/**
 * @brief  Enable indicated ADC interrupt.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  u32IntEn: Indicate which interrupt will be enable,
 *                   bit-0 means enable
 *                   bit-1 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_enable_interrupt(stADC_Handle_t *pstADC, uint32_t u32IntEn);


/**
 * @brief  Disable indicated ADC interrupt.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  u32IntDis: Indicate which interrupt will be disable,
 *                    bit-1 means disable
 *                    bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_disable_interrupt(stADC_Handle_t *pstADC, uint32_t u32IntDis);




/**********************************************************************************************************************
 *                                             Configure ADC Parameter
 *********************************************************************************************************************/

/**
 * @brief  Deinitializes the ADC module and reset the registers.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_deinit(stADC_Handle_t *pstADC);


/**
 * @brief  Initializes ADC. Configure ADC Source Data, Data Format.
 *         Configure Sample Stable Time, Down Sample Rate, Sample Number.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  pstInit: Pointer to adc work clock config.
 * @param  u16SampleCnt: Pointer to a stAdcInit_t structure that contains ADC configuation.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_init(stADC_Handle_t *pstADC, stAdcInit_t *pstInit);


/**
 * @brief  Enable the ADC module.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_enable(stADC_Handle_t *pstADC);


/**
 * @brief  Disable ADC module.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @note   If disabled adc, the whole adc module will be shutdown.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_disable(stADC_Handle_t *pstADC);


/**
 * @brief  Set adc channel selection.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  enCh: ADC channel, include io, vddr and tempreture, @ref EN_ADC_CH_T.
 *         For single adc channel: ADC_CH_0/.../ADC_CH_TEMP;
 *         For multiple adc channel: ADC_CH_0|ADC_CH_1|ADC_CH_2...;
 * @note   1) Turn off the ADC module before configuring the channel.
 *         2) The last channel status will not be saved.
 *         3) If the corresponding bit write 0, the channel will be closed.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_set_channel_sel(stADC_Handle_t *pstADC, EN_ADC_CH_T enCh);


/**
 * @brief  Get adc channel selection.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  pu16Status: Point to adc channel selection, @ref EN_ADC_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_get_channel_sel(stADC_Handle_t *pstADC, uint16_t *pu16Status);


/**
 * @brief  Set adc sample mode. Must after Trigger ADC Stop.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1
 * @param  enSampMode:
 *         - ADC_SAMP_BY_SW_TRIG: Software trigger by @ref rom_hw_adc_start_sample.
 *         - ADC_SAMP_BY_AUTO_TRIG: CPU auto trigger.
 *         - ADC_SAMP_BY_GPIO_PWM_TRIG: gpio & pwm trigger, must be configuration EN_ADC_SAMP_SRC_SEL_T and
 *           EN_ADC_PWM_SAMP_SRC_SEL_T.
 * @param  enSampSrc:
 *         - If use GPIO trigger, please configure the trigger level.
 *         - If use pwm triger, please configure the pwm trigger level.
 * @param  enPwmSampSrc: pwm triger source.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_set_sample_mode(stADC_Handle_t *pstADC, EN_ADC_SAMP_MODE_SEL_T enSampMode,
                                               EN_ADC_SAMP_SRC_SEL_T enSampSrc, EN_ADC_PWM_SAMP_SRC_SEL_T enPwmSampSrc);


/**
 * @brief  Configure ADC data format.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  enFormat: ADC data format, @ref EN_ADC_DATA_FORMAT_T.
 * @note   The ADC data format is complement code if enable cic, otherwise is original code.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_set_data_format(stADC_Handle_t *pstADC, EN_ADC_DATA_FORMAT_T enFormat);


/**
 * @brief  Enable ADC CIC function.
 *         The ADC data format is complement code if enable cic, otherwise is original code.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  u8DGC: CIC downsample filter DGC (digital gain control) coefficient, coefficient = 2^u8DGC, range is 0 ~ 31.
 * @param  u16Downsp: CIC filter down sample rate, must be multiple of 4, range is 0 ~ 4095.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_cfg_cic(stADC_Handle_t *pstADC, uint8_t u8DGC, uint16_t u16Downsp);


/**
 * @brief  Enable ADC CIC Function.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_enable_cic(stADC_Handle_t *pstADC);


/**
 * @brief  Disable ADC CIC Function.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_disable_cic(stADC_Handle_t *pstADC);


/**
 * @brief  Trigger ADC Start to Sample.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @note   Only used when triggered by software ADC_SAMP_BY_SW_TRIG.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_start_sample(stADC_Handle_t *pstADC);


/**
 * @brief  Trigger ADC Stop to Sample.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @note   Effective in all trigger modes @ref EN_ADC_SAMP_MODE_SEL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_stop_sample(stADC_Handle_t *pstADC);


/**
 * @brief  Enable adc analog buf configuration. Enable adc buffer first before enabling adc.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_enable_buf(stADC_Handle_t *pstADC);


/**
 * @brief  Disable adc analog buf configuration.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_disable_buf(stADC_Handle_t *pstADC);


/**
 * @brief  Set adc vcm voltage.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  enVcmVoltage: VCM voltage, @ref EN_ADC_VCM_VOLT_T. The VCM voltage must be equal to LDO_DIG / 2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_set_vcm_voltage(stADC_Handle_t *pstADC, EN_ADC_VCM_VOLT_T enVcmVoltage);


/**
 * @brief  Set adc conversion mode.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  enConversionMode: single channel or scan channel @ref EN_ADC_CONVERSION_MODE_T.
 * @note   default scan channel mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_set_conversion_mode(stADC_Handle_t *pstADC, EN_ADC_CONVERSION_MODE_T enConversionMode);




/**********************************************************************************************************************
 *                                             ADC Value Read Cfg
 *********************************************************************************************************************/

/**
 * @brief  Get the original data of adc, Do not use FIFO mode.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  pu16RawData: ADC value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_get_adc_rawdata(stADC_Handle_t *pstADC, uint16_t *pu16RawData);


/**
 * @brief  Get adc fifo count.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  pu8FifoCount: Pointer to adc fifo count.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_get_fifo_count(stADC_Handle_t *pstADC, uint8_t *pu8FifoCount);


/**
 * @brief  Read adc fifo value.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  pu32Value: ADC reg value.
 *         If the number of sampling bits is 10, then read ADC values at a time and store them in the FIFO.
 *         The high 6 bits are filled with 0, and the low 10 bits are the actual data.
 *         If the number of sampling bits is 12, Then read ADC values at a time and store them in the FIFO,
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_read_fifo(stADC_Handle_t *pstADC, uint16_t *pu16Value);


/**
 * @brief  Set adc fifo threshold.
 *         When the FIFO data reaches the threshold, an interrupt(@ADC_INT_FLAG [14]) and DMA request are generated.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  enFifoThWord: 1 word ~ 4 word, @ref EN_ADC_FIFO_THLD_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_set_fifo_threshold(stADC_Handle_t *pstADC, EN_ADC_FIFO_THLD_T enFifoThWord);


/**
 * @brief  Trigger Clear ADC Sample Counter.
 *         Must After Trigger ADC Stop.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_clear_sample_cnt(stADC_Handle_t *pstADC);


/**
 * @brief  Get the sample counter of adc. For debugging.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  pu16RawData: ADC value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_adc_get_adc_sample_cnt(stADC_Handle_t *pstADC, uint16_t *pu16SampCnt);




#ifdef __cplusplus
}
#endif

#endif /* __HW_ADC_H__ */

