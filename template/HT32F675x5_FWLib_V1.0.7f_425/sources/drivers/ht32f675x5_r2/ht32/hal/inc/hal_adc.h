/*************************************************************************************************************
 * @file    hal_adc.h
 * @version V1.0
 * @date    2021-09-07
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


#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__

/**
 * @brief  DEFINE.
 */
#define HT32_ADC_SAMPLE_ERROR_COUNT             (16)
#define HT32_ADC_SAMPLE_CHANNEL_COUNT(chCnt)    (chCnt * 2)
#define HT32_ADC_SAMPLE_NUMBER_FOR_DMA(sampNum) (sampNum / 2 + HT32_ADC_SAMPLE_ERROR_COUNT)
#define HT32_ADC_SAMPLE_BUF_SIZE(chCnt, sampNum) \
    (HT32_ADC_SAMPLE_CHANNEL_COUNT(chCnt) * HT32_ADC_SAMPLE_NUMBER_FOR_DMA(sampNum))

// ADC Resolution Define
#define ADC_RESOLUTION_10BIT               (10) /*!< ADC resolution 10 bits */
#define ADC_RESOLUTION_12BIT               (12) /*!< ADC resolution 12 bits */
#define ADC_MAX_DR_BIT                     (16)
#define ADC_FIFO_DEPTH                     (4)

// ADC Voltage
#define ADC_IO_STANDARD_200MV_VAL          (200)  /** @brief define 200mV */
#define ADC_IO_STANDARD_900MV_VAL          (900)  /** @brief define 900mV */
#define ADC_IO_DELTA_VAL                   (ADC_IO_STANDARD_900MV_VAL - ADC_IO_STANDARD_200MV_VAL)

#define ADC_VDDR_STANDARD_2000MV_VAL       (2000) /** @brief define 2000mV */
#define ADC_VDDR_STANDARD_3500MV_VAL       (3500) /** @brief define 3500mV */
#define ADC_VDDR_DELTA_VAL                 (ADC_VDDR_STANDARD_3500MV_VAL - ADC_VDDR_STANDARD_2000MV_VAL)

// ADC Temperature
#define ADC_TEMPERATURE_STANDARD_NEG40_VAL (-40) /** @brief define -40 degree centigrade */
#define ADC_TEMPERATURE_STANDARD_116_VAL   (116) /** @brief define 116 degree centigrade */
#define ADC_TEMPERATURE_TRIM1              (351) /** @brief define trim value of -40 degree centigrade */
#define ADC_TEMPERATURE_TRIM2              (249) /** @brief define trim value of 116 degree centigrade */

/**
 * @brief  TYPEDEF.
 */
typedef struct
{
    stADC_Handle_t *pstADCHandle;
    uint8_t         u8Resolution;
    EN_ADC_CH_T     enCh;

    EN_ADC_SAMP_MODE_SEL_T    enSampMode;
    EN_ADC_SAMP_SRC_SEL_T     enSampSrc;
    EN_ADC_PWM_SAMP_SRC_SEL_T enPwmSampSrc;

} stADCInitHandle_t;

typedef struct
{
    uint16_t u16ADC0IOLoVolt;   /* ADC io tune value @200mV */
    uint16_t u16ADC0IOHiVolt;   /* ADC io tune value @900mV */
    uint16_t u16ADC1IOLoVolt;   /* ADC io tune value @200mV */
    uint16_t u16ADC1IOHiVolt;   /* ADC io tune value @900mV */
    uint16_t u16ADC0VddrLoVolt; /* ADC vddr tune value @2.0V */
    uint16_t u16ADC0VddrHiVolt; /* ADC vddr tune value @3.5V */

} stADCTuneValue_t;

/**
 * @brief  cfg adc downsp and dgc for resolution.
 * @param  u8Resolution : 11 / 12 / 13 / 14.
 * @param  pu16DownspValue:
 * @param  pu8Dgc
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_adc_resolution_to_downsp_dgc(uint8_t u8Resolution, uint16_t *pu16DownspValue,
                                                         uint8_t *pu8Dgc);

/**
 * @brief  ADC FIFO raw value converted to adc value（Code/LSB).
 * @param  pstADCInitHandle: Pointer to adc init struct, @ref stADCInitHandle_t.
 * @param  u32ADCDataIn: FIFO Reg data.
 * @param  pu16ADCDataOut: output adc value (Code/Lsb).
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_adc_fifo_reg_to_lsb(stADCInitHandle_t *pstADCInitHandle, uint32_t u32ADCDataIn,
                                                uint16_t *pu16ADCDataOut);

/**
 * @brief  Get adc trim value.
 * @param  pstADC: ADC handle, Should be ADC0 / ADC1.
 * @param  pStAdcTrimValue: , @ref stAdcTuneValue_t.
 * @param  u8Resolution: 10Bit(ADC_RESOLUTION_10B) & 12bit(ADC_RESOLUTION_12B).
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_adc_get_trim(stADC_Handle_t *pstADC, stADCTuneValue_t *pstADCTrimValue,
                                         uint8_t u8Resolution);

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
extern EN_ERR_STA_T rom_hal_adc_init(stADCInitHandle_t *pstADCInitHandle, uint16_t u16SampNum);

/**
 * @brief  Get adc value for one channel.
 * @param  pstADCInitHandle: ADC init handle, @ref stADCInitHandle_t.
 * @param  enCh: ADC channel.
 * @output pu16Value: Pointer to adc sample data.
 * @return status: @ref EN_ERR_STA_T.
 */
// extern EN_ERR_STA_T rom_hal_adc_get_data(stADCInitHandle_t *pstADC, EN_ADC_CH_T enCh, uint16_t *pu16Value);

/**
 * @brief  Read adc value by dma mode.
 * @param  pstADCInitHandle: ADC init handle, @ref stADCInitHandle_t.
 * @param  u8ChCnt: ADC channel count.
 * @param  u16SampCnt: ADC sample count.
 * @param  pu32SampleTmpBuf: Pointer to save adc dma sample buffer.
 * @param  pu16SampleBuf: Pointer to adc sample buffer.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_adc_read_dma_data(stADCInitHandle_t *pstADCInitHandle, uint8_t u8ChCnt, uint16_t u16SampCnt,
                                              uint32_t *pu32SampleTmpBuf, uint16_t *pu16SampleBuf);

#endif /* __HAL_ADC_H__ */
