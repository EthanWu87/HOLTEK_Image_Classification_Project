/*************************************************************************************************************
 * @file    hw_audio.h
 * @version V1.1
 * @date    2022-01-21
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


#ifndef __HW_AUDIO_H__
#define __HW_AUDIO_H__

#ifdef __cplusplus
extern "C"{
#endif




//=====================================================================================================================
// DEFINE
//=====================================================================================================================
/* total audio sample rate support number for adc & pdm */
#define AUDIO_SUPPORT_SAMPLE_RATE_NUM      ( 6 )

/* audio sample rate support list,for adc & pdm */
#define AUDIO_SAMPLE_DIV_8K                ( 8000U )
#define AUDIO_SAMPLE_DIV_16K               ( 16000U )
#define AUDIO_SAMPLE_DIV_22K               ( 22000U )
#define AUDIO_SAMPLE_DIV_32K               ( 32000U )
#define AUDIO_SAMPLE_DIV_44K               ( 44000U )
#define AUDIO_SAMPLE_DIV_64K               ( 64000U )

/* only audio adc mode */
#define AUDIO_INPUT_CLOCK_FIX_16MHZ        ( 16000000U )

/* only audio pdm mode */
#define AUDIO_INPUT_CLOCK_FIX_4MHZ         ( 4000000U )
#define AUDIO_INPUT_CLOCK_FIX_2MHZ         ( 2000000U )

#define AUDIO_PDM_CLOCK_2M_DIV             ( 8U )
#define AUDIO_PDM_CLOCK_1M_DIV             ( 16U )


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef union
{
    uint32_t u32Cfg;

    struct
    {
        uint32_t u8GainMult             : 5; /* @ ref PDM_GAIN_MULT                  */
        uint32_t u8DebugOutEn           : 1; /* invalid set 0                        */
        uint32_t u8AdcDataFormat        : 1; /* @ ref EN_CIC_ADC_CODE_MODE_T         */
        uint32_t u8SlpfFlgEn            : 1; /* @ ref Slpf begin data flg ,Set 1     */
        uint32_t u8SlpfEn               : 1; /* @ ref EN_AUDIO_LPF_BYPASS_EN_T       */
        uint32_t u8CompEn               : 1; /* @ ref EN_AUDIO_COMP_BYPASS_EN_T      */
        uint32_t u8SourceEn             : 1; /* @ ref EN_AUDIO_SOURCE_DATA_EN_T      */
        uint32_t reserved               : 1; /* invalid set 0                        */
        uint32_t u8AdcClockPol          : 1; /* @ ref EN_CIC_ADC_POL_T               */
        uint32_t u8CicSourceSel         : 1; /* @ ref EN_CIC_PDM_POL_T               */
        uint32_t u8CicEnable            : 1; /* if audio module on set 1,else set 0  */
        uint32_t u8Adc_zero_move_en     : 1; /* if cic on ,should set 1              */
    } stCfg;
    
} unAudioCfg_t;

/* For audio adc  */
typedef struct
{
    unAudioCfg_t                         unCfg;              /* CIC cfg */
    EN_AUDIO_ADC_INPUT_MODE_T            enAudioInputMode;   /* input mode: single-end input/difference input*/
    EN_AUDIO_SAMPLE_RATE_T               enAudioSampleRate;  /* sample rate */

} stAudio_Adc_Init_t;


/* For audio pdm */
typedef struct
{
    unAudioCfg_t                        unCfg;               /* CIC cfg */
    EN_AUDIO_SAMPLE_RATE_T              enAudioSampleRate;   /* sample rate */
    EN_PDM_CLOCK_T                      enPdmClockRate;      /* pdm clock rate */

} stAudio_Pdm_Init_t;




/**********************************************************************************************************************
 *                                             Audio Interrupt Cfg function
 *********************************************************************************************************************/

/**
 * @brief  Get indicated audio interrupt flag(status).
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  pu32Flag: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_get_interrupt_flag(stAUDIO_Handle_t *pstAUDIO, uint32_t *pu32Flag);


/**
 * @brief  Clear audio interrupt flag(status).
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  u32Flag: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_clear_interrupt_flag(stAUDIO_Handle_t *pstAUDIO, uint32_t u32Flag);


/**
 * @brief  enable audio interrupt flag(status).
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  u32IntEn: Indicate which interrupt will be enable,
 *                   bit-0 means enable
 *                   bit-1 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_enable_interrupt(stAUDIO_Handle_t *pstAUDIO, uint32_t u32IntEn);


/**
 * @brief  disable audio interrupt flag(status).
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  u32IntDis: Indicate which interrupt will be disable,
 *                    bit-1 means disable
 *                    bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_disable_interrupt(stAUDIO_Handle_t *pstAUDIO, uint32_t u32IntDis);




/**********************************************************************************************************************
 *                                             Audio public module Cfg function
 *********************************************************************************************************************/

/**
 * @brief  Configure audio cic moduel.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enAudioCicStatus: cic on or off, Recommend to open. @ref EN_AUDIO_CIC_CTRL_T.
 * @note   Configure before the audio module is enabled.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_cfg_cic(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_CIC_CTRL_T enAudioCicStatus);


/**
 * @brief  Select audio fifo data source.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enAudioSource: audio data source from cic or （adc&pdm） @ref EN_AUDIO_SOURCE_DATA_EN_T
 * @note   Set before the audio module is enabled.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_select_fifo_data(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_SOURCE_DATA_EN_T enAudioSource);


/**
 * @brief  Set audio compensation filter.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enCompFilter: Enable or disable compensation filter, @ref EN_AUDIO_COMP_FILTER_EN_T.
 * @note   Set before the Audio module is enabled.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_set_compensation_filter(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_COMP_FILTER_EN_T enCompFilter);


/**
 * @brief  Select audio cic moduel data source.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enSource: Audio cic data source, @ref EN_AUDIO_CIC_SOURCE_T.
 * @note   Set before the audio module is enabled.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_select_cic_soure(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_CIC_SOURCE_T enSource);


/**
 * @brief  Set audio Strong Low Pass Filter(SLPF).
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enSlpf: Enable or disable SLPF, @ref EN_AUDIO_SLPF_EN_T.
 * @note   Set before the audio module is enabled.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_set_slpf(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_SLPF_EN_T enSlpf);


/**
 * @brief  Read audio fifo data. Audio fifo deepth is 4 * 32Byte.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  pu32AudioPdmData: Pinter to save audio fifo data.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_read_fifo(stAUDIO_Handle_t *pstAUDIO, uint32_t *pu32AudioPdmData);




/**********************************************************************************************************************
 *                                             Audio Adc Mode Cfg function
 *********************************************************************************************************************/

/**
 * @brief  Set audio adc sample rate.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enSlpf: Enable or disable Slpf, @ref EN_AUDIO_SLPF_EN_T.
 * @param  enSampleRate audio Sample rate @ref EN_AUDIO_SAMPLE_RATE_T,
 *         If slpf on: 8KHz <= sample rate <= 32KHz,
 *         if slpf off: 32KHz<= sample rate <= 64KHz.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_adc_set_sample_rate(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_SLPF_EN_T enSlpf,
                                                     EN_AUDIO_SAMPLE_RATE_T enSampleRate);


/**
 * @brief  Set audio adc input mode.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enInputMode: Audio adc input mode, @EN_AUDIO_ADC_INPUT_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_adc_set_input_mode(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_ADC_INPUT_MODE_T enInputMode);


/**
 * @brief  Audio adc deinit.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_adc_deinit(stAUDIO_Handle_t *pstAUDIO);


/**
 * @brief  Audio adc init.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  pstCfg: Pointer to audio adc configuration, input mode and sampleRate.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_adc_init(stAUDIO_Handle_t *pstAUDIO, stAudio_Adc_Init_t *pstCfg);


/**
 * @brief  Set audio adc pga gain.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enAudioGain: Audio ADC PGA gain(0 ~ 30dB, step by 3dB), @ref EN_AUDIO_ADC_PGA_GAIN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_adc_set_pga_gain(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_ADC_PGA_GAIN_T enAudioGain);


/**
 * @brief  Set audio adc common mode voltage.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enVcmVolt: Audio adc vcm voltage, @ref EN_AUDIO_VCM_CFG_T.
 * @note   vcm voltage must be equal to (ldo dig volt / 2).
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_adc_set_vcm_volt(stAUDIO_Handle_t *pstAUDIO, EN_ADC_VCM_VOLT_T enVcmVolt);


/**
 * @brief  Enable audio adc module.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enMicBiasVolt: Mic bias voltage, @ref EN_AUDIO_MIC_BIAS_VOL_T.
 * @param  u32PgaTimeUs: Audio ADC stable time, unit is us.
 * @param  u32TimeUs: Wait for release times, unit is us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_adc_enable(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_MIC_BIAS_VOLT_T enMicBiasVolt,
                                            uint32_t u32PgaTimeUs, uint32_t u32TimeUs);


/**
 * @brief  Disable audio adc module.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_adc_disable(stAUDIO_Handle_t *pstAUDIO);




/**********************************************************************************************************************
 *                                             Audio Pdm Mode Cfg function
 *********************************************************************************************************************/

/**
 * @brief  Set audio pdm sample rate, pdm input clock fixed to 2MHz.
 *         pdm slpf on: 8KHz ~ 32KHz,
 *         pdm slpf off: 32KHz ~ 64KHz.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enSlpf: Enable or disable slpf, @ref EN_AUDIO_SLPF_EN_T.
 * @param  enSampleRate: Audio pdm sample rate, @ref EN_AUDIO_SAMPLE_RATE_T.

 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_pdm_set_sample_rate(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_SLPF_EN_T enSlpf,
                                                     EN_AUDIO_SAMPLE_RATE_T enSampleRate);


/**
 * @brief  Set audio pdm pga gain.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enPdmGainMult: pdm digital gain mult control, @ref EN_PDM_GAIN_MULT.
 * @note   used before pdm mode enable, @ref rom_hw_audio_pdm_enable.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_pdm_set_digital_gain(stAUDIO_Handle_t *pstAUDIO, EN_PDM_GAIN_MULT enPdmGainMult);


/**
 * @brief  Set audio pdm clock, recommend set to 2M.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  enAudioPdmClock: 1M & 2M, @ref EN_PDM_CLOCK_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_pdm_cfg_clk(stAUDIO_Handle_t *pstAUDIO, EN_PDM_CLOCK_T enAudioPdmClock);


/**
 * @brief  Audio pdm deinit.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_pdm_deinit(stAUDIO_Handle_t *pstAUDIO);


/**
 * @brief  Audio pdm init.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @param  pstCfg: Pointer to pdm configuration, @ref stAudio_Pdm_Init_t
 * @note   1. 675x5 pdm module Audio0 Only supports rising edge sample data
 *         2. 675x5 pdm module Audio1 Only supports rising edge sample data
 *         3. Stereo sample data need audio0 + Audio1

 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_pdm_init(stAUDIO_Handle_t *pstAUDIO, stAudio_Pdm_Init_t *pstCfg);


/**
 * @brief  Enable audio pdm.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_pdm_enable(stAUDIO_Handle_t *pstAUDIO);


/**
 * @brief  Disable audio pdm.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0 / AUDIO1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_audio_pdm_disable(stAUDIO_Handle_t *pstAUDIO);


#ifdef __cplusplus
}
#endif

#endif /* __HW_AUDIO_H__ */


