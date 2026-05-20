/*************************************************************************************************************
 * @file    hal_audio.h
 * @version V1.0
 * @date    2022-01-23
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

#ifndef __HAL_AUDIO_H__
#define __HAL_AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef enum
{
    AUDIO_PDM_SAMP_EDGE_RISE = 0x00,  /* _|- */
    AUDIO_PDM_SAMP_EDGE_FALL = 0x01,  /* -|_*/
    AUDIO_PDM_SAMP_EDGE_BOTH = 0x02,  /* _|--|_ */

} EN_AUDIO_PDM_SAMP_EDGE_T;

#define IS_AUDIO_PDM_SAMP_EDGE_VALID(_EDGE_)    (((_EDGE_) == AUDIO_PDM_SAMP_EDGE_FALL) || \
                                                 ((_EDGE_) == AUDIO_PDM_SAMP_EDGE_RISE) || \
                                                 ((_EDGE_) == AUDIO_PDM_SAMP_EDGE_BOTH))




/**
 * @brief  software dcr handler.
 * @param  p32PdmDcrBuf: status value.
 * @param  p32PdmDcrValue: dcr value.
 * @param  p16buf: audio data buffer, and the target data will save the same position.
 * @param  u16len: buf length.
 * @return status: @ref EN_ERR_STA_T.
 */
extern void rom_hal_audio_software_dcr_handler(int32_t *p32PdmDcrBuf, int32_t *p32PdmDcrValue,
                                               int16_t *p16buf, uint16_t u16len);


/**
 * @brief  audio software CIC algorithm, this function will convert audio data to 16K x 16bit PCM data.
 * @param  pu32DataIn: audio data buffer.
 * @param  pu16DataOut: after convert the resault save buffer.
 * @param  u16start: first data pos.
 * @param  u32len: min len is 256 / 2 = 128 WORD.
 * @return valid output data length.
 */
extern uint16_t rom_hal_audio_sw_cic_handler(uint32_t *pu32DataIn, uint16_t *pu16DataOut, uint16_t u16start, uint32_t u32len);


/**
 * @brief  udio adc mode deinit.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0/AUDIO1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_audio_adc_deinit(stAUDIO_Handle_t *pstAUDIO);


/**
 * @brief  audio adc mode init.
 * @param  pstAUDIO: Audio handle, Should be AUDIO0/AUDIO1.
 * @param  enAudioSampleRate :range: 8k - 32K  @ref EN_AUDIO_SAMPLE_RATE_T , SLPF is enabled by default.
 * @note   if slpf on: 8K <= Sample rate <= 32K.
           if slpf off: 32K<= Sample rate <= 64K.
 * @param  enAudioInputMode: single or diff @ref EN_AUDIO_ADC_INPUT_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_audio_adc_init(stAUDIO_Handle_t *pstAUDIO, EN_AUDIO_SAMPLE_RATE_T enAudioSampleRate,
                                           EN_AUDIO_ADC_INPUT_MODE_T enAudioInputMode);


/**
 * @brief  audio pdm mode init.
 * @param  enAudioSampleRate :range: 8k - 32K  @ref EN_AUDIO_SAMPLE_RATE_T , SLPF is enabled by default.
 * @note   if slpf on: 8K <= Sample rate <= 32K.
           if slpf off: 32K<= Sample rate <= 64K.
 * @param  enPdmClockRate: 2Mhz or 1Mhz @ref EN_PDM_CLOCK_T.
 * @param  enPdmSampleEdge: rise or fall or both, pdm0 only support rise sample, pdm1 only support rise sample.
                            @ref EN_AUDIO_PDM_SAMP_EDGE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_audio_pdm_init(EN_AUDIO_SAMPLE_RATE_T enAudioSampleRate, EN_PDM_CLOCK_T enPdmClockRate,
                                           EN_AUDIO_PDM_SAMP_EDGE_T enPdmSampleEdge);


/**
 * @brief  Enable audio pdm.
 * @param  enPdmSampleEdge: rise or fall or both, pdm0 only support rise sample, pdm1 only support rise sample.
                            @ref EN_AUDIO_PDM_SAMP_EDGE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_audio_pdm_enable(EN_AUDIO_PDM_SAMP_EDGE_T enPdmSampleEdge);


/**
 * @brief  Disable audio pdm.
 * @param  enPdmSampleEdge: rise or fall or both, pdm0 only support rise sample, pdm1 only support rise sample.
                            @ref EN_AUDIO_PDM_SAMP_EDGE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_audio_pdm_disable(EN_AUDIO_PDM_SAMP_EDGE_T enPdmSampleEdge);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_AUDIO_H__ */

