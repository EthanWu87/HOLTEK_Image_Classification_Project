/*************************************************************************************************************
 * @file    reg_adc_ana.h
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


#ifndef __REG_ADC_ANA_H__
#define __REG_ADC_ANA_H__

#ifdef __cplusplus
 extern "C"
{
#endif


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IOM uint32_t ADC_ANALOG_CFG_0;       /* [0x00](RW) */
    __IOM uint32_t ADC_ANALOG_CFG_1;       /* [0x04](RW) */
    __IOM uint32_t ADC_ANALOG_CFG_2;       /* [0x08](RW) */
    __IOM uint32_t ADC_ANALOG_PGA_CFG_0;   /* [0x0C](RW) */
    __IOM uint32_t ADC_ANALOG_PGA_CFG_1;   /* [0x10](RW) */
    __IOM uint32_t ADC_ANALOG_PGA_CFG_2;   /* [0x14](RW) */

} stADC_Analog_Handle_t, *pstADC_Analog_Handle_t;


//=====================================================================================================================
// [0x00](RW) ADC_ANALOG_CFG_0
//=====================================================================================================================
//=============================================================================
// ADC_ANALOG_CFG_0[5:3] AUDIO_MIC_BIAS_CTRL. Set audio mic bias voltage, only for Audio.
#define AUDIO_MIC_BIAS_CTRL_SHIFT          (3)
#define AUDIO_MIC_BIAS_CTRL_MSK            ((0x01 << 3) - 1)
#define AUDIO_MIC_BIAS_CTRL_CLEAR          (0)

typedef enum
{
    EN_AUDIO_MIC_BIAS_DISABLE  = 0x00,
    EN_AUDIO_MIC_BIAS_1_5V     = 0x01,
    EN_AUDIO_MIC_BIAS_1_8V     = 0x02,
    EN_AUDIO_MIC_BIAS_2_2V     = 0x03,
    EN_AUDIO_MIC_BIAS_2_5V     = 0x04,
    EN_AUDIO_MIC_BIAS_VDDR     = 0x05,

} EN_AUDIO_MIC_BIAS_VOLT_T;

#define IS_VALID_AUDIO_MIC_BIAS_VOLT(VOLT)   (((VOLT) == EN_AUDIO_MIC_BIAS_DISABLE) || \
                                              ((VOLT) == EN_AUDIO_MIC_BIAS_1_5V)    || \
                                              ((VOLT) == EN_AUDIO_MIC_BIAS_1_8V)    || \
                                              ((VOLT) == EN_AUDIO_MIC_BIAS_2_2V)    || \
                                              ((VOLT) == EN_AUDIO_MIC_BIAS_2_5V)    || \
                                              ((VOLT) == EN_AUDIO_MIC_BIAS_VDDR))

//=============================================================================
// ADC_ANALOG_CFG_0[2] ADC_ANA_EN. Enable analog adc.
#define ADC_ANA_EN_SHIFT                   (2)
#define ADC_ANA_EN_MSK                     ((0x01 << 1) - 1)

//=============================================================================
// ADC_ANALOG_CFG_0[1:0] AUDIO_MIC_BIAS_CURR_CFG. Configure audio adc mic bias current.
#define AUDIO_MIC_BIAS_CURR_CFG_SHIFT      (0)
#define AUDIO_MIC_BIAS_CURR_CFG_MSK        ((0x01 << 2) - 1)
#define AUDIO_MIC_BIAS_CURR_CFG_CLEAR      (0)


//=====================================================================================================================
// [0x04](RW) ADC_ANALOG_CFG_1
//=====================================================================================================================
//=============================================================================
// ADC_ANALOG_CFG_1 [6:7] AUDIO_MIC_BIAS_EXT_REF
// Audio Adc mic bias external reference enable, only for audio Debug
#define AUDIO_MIC_BIAS_EXT_REF_SHIFT       (6)
#define AUDIO_MIC_BIAS_EXT_REF_MSK         ((0x01 << 2) - 1)
#define AUDIO_MIC_BIAS_EXT_REF_CLEAR       (0)

//=============================================================================
// ADC_ANALOG_CFG_1[5] AUDIO_MIC_BIAS_INT_REF
// Audio adc mic bias internal reference enable, only for audio Debug
#define AUDIO_MIC_BIAS_INT_REF_SHIFT       (5)
#define AUDIO_MIC_BIAS_INT_REF_MSK         ((0x01 << 1) - 1)
#define AUDIO_MIC_BIAS_INT_REF_CLEAR       (0)

typedef enum
{
    AUDIO_MICBIAS_INTREF_DIS    = 0x00,
    AUDIO_MICBIAS_INTREF_EN     = 0x01,

} EN_AUDIO_MICBIAS_INTREF_T;

//=============================================================================
// ADC_ANALOG_CFG_1[4] ADC_ANA_PATH_EN
// ADC module for audio enable. Gpadc set 0, Audio set 1.
#define ADC_ANA_PATH_EN_SHIFT              (4)
#define ADC_ANA_PATH_EN_MSK                ((0x01 << 1) - 1)
#define ADC_ANA_PATH_EN_CLEAR              (0)

typedef enum
{
    ADC_ANA_PATH_DIS  = 0x00,
    ADC_ANA_PATH_EN   = 0x01,

} EN_AUDIO_PATH_CTRL_T;

//=============================================================================
// ADC_ANALOG_CFG_1[3] ADC_ANA_PGA_SHORT_INPUT
// Audio adc speed up start enable, use to gpio Discharge
#define ADC_ANA_PGA_SHORT_INPUT_SHIFT      (3)
#define ADC_ANA_PGA_SHORT_INPUT_MSK        ((0x01 << 1) - 1)
#define ADC_ANA_PGA_SHORT_INPUT_CLEAR      (0)

//=============================================================================
// ADC_ANALOG_CFG_1[2] ADC_ANA_INPUT_MODE
// audio input mode, single or difference, only audio mode, gpadc ignore
#define ADC_ANA_INPUT_MODE_SHIFT           (2)
#define ADC_ANA_INPUT_MODE_MSK             ((0x01 << 1) - 1)

typedef enum
{
    ADC_ANA_DIFF_INPUT_MODE     = 0x00,
    ADC_ANA_SINGLE_INPUT_MODE   = 0x01,

} EN_AUDIO_ADC_INPUT_MODE_T;

#define IS_VALID_ADC_INPUT_MODE(MODE)  (((MODE) == ADC_ANA_DIFF_INPUT_MODE) || ((MODE) == ADC_ANA_SINGLE_INPUT_MODE))

//=============================================================================
// ADC_ANALOG_CFG_1[1:0] ADC_VCM_VOLT, VCM Voltage
#define ADC_VCM_VOLT_SHIFT                 (0)
#define ADC_VCM_VOLT_MSK                   ((0x01 << 2) - 1)

typedef enum
{
    EN_ADC_VCM_VOLT_0_4_5V = 0x00, /* VCM Voltage = 0.45V */
    EN_ADC_VCM_VOLT_0_5_0V = 0x01, /* VCM Voltage = 0.50V */
    EN_ADC_VCM_VOLT_0_5_5V = 0x03, /* VCM Voltage = 0.55V */

} EN_ADC_VCM_VOLT_T;

#define IS_VALID_ADC_VCM_VOLT(VALUE) (((VALUE) == EN_ADC_VCM_VOLT_0_4_5V)  || \
                                      ((VALUE) == EN_ADC_VCM_VOLT_0_5_0V)  || \
                                      ((VALUE) == EN_ADC_VCM_VOLT_0_5_5V))


//=====================================================================================================================
// [0x08](RW) ADC_ANALOG_CFG_2
//=====================================================================================================================
//=============================================================================
// ADC_ANALOG_CFG_2[10] ADC_CONVERSION_MODE, gpadc coversion mode. Audio ignore
#define ADC_CONVERSION_MODE_SHIFT          (10)
#define ADC_CONVERSION_MODE_MSK            ((0x01 << 1) - 1)

typedef enum
{
    ADC_CONVERSION_SCAN   = 0x00,
    ADC_CONVERSION_SINGLE = 0x01,

} EN_ADC_CONVERSION_MODE_T;

#define IS_VALID_ADC_CONVERSION_MODE(MODE) (((MODE) == ADC_CONVERSION_SCAN) ||\
                                            ((MODE) == ADC_CONVERSION_SINGLE))

//=============================================================================
// ADC_ANALOG_CFG_2[9:8] buf gain, for debug, reserved.

//=============================================================================
// ADC_ANALOG_CFG_2[7] ADC_BUF_CFG, gpadc must be enable, audio must be disable
#define ADC_BUF_CFG_SHIFT                  (7)
#define ADC_BUF_CFG_MSK                    ((0x01 << 1) - 1)

typedef enum
{
    ADC_BUF_DISABLE = 0x00,
    ADC_BUF_ENABLE  = 0x01,

} EN_ADC_BUF_CFG_T;


//=====================================================================================================================
// [0x0C](RW) ADC_ANALOG_PGA_CFG_0 (CH0 ~ CH3 channel pga configure)
//=====================================================================================================================
//=============================================================================
// ADC_ANALOG_PGA_CFG_0[3:0] ADC_ANA_CH0_PGA_CFG
#define ADC_ANA_CH0_PGA_CFG_SHIFT          (0)
#define ADC_ANA_CH0_PGA_CFG_MSK            ((0x01 << 4) - 1)
#define ADC_ANA_CH0_PGA_CFG_CLEAR          (0)

typedef enum
{
    EN_AUDIO_ADC_PGA_0DB   = 0,
    EN_AUDIO_ADC_PGA_3DB   = 1,
    EN_AUDIO_ADC_PGA_6DB   = 2,
    EN_AUDIO_ADC_PGA_9DB   = 3,
    EN_AUDIO_ADC_PGA_12DB  = 4,
    EN_AUDIO_ADC_PGA_15DB  = 5,
    EN_AUDIO_ADC_PGA_18DB  = 6,
    EN_AUDIO_ADC_PGA_21DB  = 7,
    EN_AUDIO_ADC_PGA_24DB  = 8,
    EN_AUDIO_ADC_PGA_27DB  = 9,
    EN_AUDIO_ADC_PGA_30DB  = 10,
    EN_AUDIO_ADC_PGA_MAX   = 11

} EN_AUDIO_ADC_PGA_GAIN_T;

#define IS_VALID_AUDIO_ADC_PGA_GAIN(GAIN) ((GAIN) < EN_AUDIO_ADC_PGA_MAX)


//=====================================================================================================================
// [0x10](RW) ADC_ANALOG_PGA_CFG_1
//=====================================================================================================================


//=====================================================================================================================
// [0x14](RW) ADC_ANALOG_PGA_CFG_2
//=====================================================================================================================
//=============================================================================
// ADC_ANALOG_PGA_CFG_2[8] ADC_ANA_PGA_SEL
#define ADC_ANA_PGA_SEL_SHIFT              (8)
#define ADC_ANA_PGA_SEL_MSK                ((0x01 << 1) - 1)

typedef enum
{
    AUDIO_PGA_DIS        = 0x00,
    AUDIO_PGA_EN         = 0x01,

} EN_AUIDO_PGA_EN_T;

#define IS_VALID_AUIDO_PGA_MODE(MODE)  ((MODE) == AUDIO_PGA_DIS || (MODE) == AUDIO_PGA_EN)


#ifdef __cplusplus
}
#endif

#endif /* __REG_ADC_ANA_H__ */

