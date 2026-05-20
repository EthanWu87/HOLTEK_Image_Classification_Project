/*************************************************************************************************************
 * @file    hw_trng.h
 * @version V1.1
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


#ifndef __HW_TRNG_H__
#define __HW_TRNG_H__

#ifdef __cplusplus
extern "C" {
#endif

//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    uint32_t            u32SampleCnt; /* Set the number of rng_clk cycles between two consecutive ring oscillator samples.
                                         Note: If the von-neuman is bypassed, the minimum value for sample count must not be less then 17.*/
    bool                bDmaEn;       /* Enable or disable dma request trng data. */
    uint8_t             u8BypassCtrl; /* Bypass control, default is 0. */
    uint8_t             u8Level;      /* Trng data generate level, range is 0 ~ 3 */
    EN_TRNG_SRC_CH_EN_T enSrcEn;      /* Trng source channel selection, @ref EN_TRNG_SRC_CH_EN_T */

} stTrngInit_t, *pstTrngInit_t;

/**
 * @brief  Get trng interrupt flag(status).
 * @param  pu16Flag: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_get_interrupt_flag(uint16_t *pu16Flag);

/**
 * @brief  Clear trng interrupt flag(status).
 * @param  u16Flag: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_clear_interrupt_flag(uint16_t u16Flag);

/**
 * @brief  Enable trng interrupt.
 * @param  u16IntEn: Indicate which interrupt will be enable,
 *                   bit-1 means enable
 *                   bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_enable_interrupt(uint16_t u16IntEn);

/**
 * @brief  Disable trng interrupt.
 * @param  u16IntDis: Indicate which interrupt will be disable
 *                    bit-1 means disable
 *                    bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_disable_interrupt(uint16_t u16IntDis);

/**
 * @brief  Set trng bypass configuration.
 * @param  u8BypassCtrl: bypass cfg:
 *         bit4: Set 1 to bypass the LFSR in the trng data-path;
 *         bit3: Set 1 to bypass the autocorrelation test in the trng module;
 *         bit2: Set 1 to bypass the trng test in the trng;
 *         bit1: Set 1 to bypass the von-neuman balancer(including the 32 consecutive bits test).
 *         bit0: Must set 0, trng data will all be 0 when this bit set 1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_set_bypass(uint8_t u8BypassCtrl);

/**
 * @brief  Set trng sample count.
 * @param  u32SampleCnt: Sample count. Sets the number of rng_clk cycles between two consecutive ring oscillator
 * samples. If the von-neuman is bypassed, the minimum value for sample counter must not be less then 17.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_set_sample_cnt(uint32_t u32SampleCnt);

/**
 * @brief  Enable trng analog random source.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_enable_analog_source(void);

/**
 * @brief  Disable trng analog random source.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_disable_analog_source(void);

/**
 * @brief  Set trng digital source level.
 * @param  u8Level: The trng level, the range is 0~3.
 *                  Selects the number of inverters in the ring oscillator, 0~3 for 1~4.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_set_source_level(uint8_t u8Level);

/**
 * @brief  Enable trng digital and(or) analog channel.
 * @param  u8Ch: Random channel, @ref EN_TRNG_SRC_CH_EN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_enable_channel(uint8_t u8Ch);

/**
 * @brief  Disable trng digital and(or) analog channel.
 * @param  u8Ch: Random channel, @ref EN_TRNG_SRC_CH_EN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_disable_channel(uint8_t u8Ch);

/**
 * @brief  Enable dma get random data.
 *         - Set output serial data from lfsr.
 *         - Enable trng in continue mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_enable_dma(void);

/**
 * @brief  Disable dma get random data.
 *         - Set output parallel data from correlation.
 *         - Disable trng in continue mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_disable_dma(void);

/**
 * @brief  Get 192bit data valid flag(status).
 * @return bool: true - Indicate flag, means 192bit random data is ready.
 */
extern bool rom_hw_trng_get_data_valid_flag(void);

/**
 * @brief  Disable dma get random data.
 * @param  pstInit: Pointer to a stTrngInit_t structure.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_init(stTrngInit_t *pstInit);

/**
 * @brief  Get random data by reading entropy data register.
 * @param  pu8Buf: Pointer to a buffer which used to save the read data.
 * @param  u8BufLen: Maximum length of pu8Buf, it should not be bigger than 6.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_get_192bit_random(uint8_t *pu8Buf, uint8_t u8BufLen);

/**
 * @brief  Get random data.
 * @param  pu8Buf: Point buffer to receive random data.
 * @param  u32BufLen: Buffer length.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_get_random(uint8_t *pu8Buf, uint32_t u32BufLen);


/**
 * @brief  Get random data by reading entropy data register.
 * @param  pu8Buf: Pointer to a buffer which used to save the read data.
 * @param  u8BufLen: Maximum length of pu8Buf, it should not be bigger than 24.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_trng_gen_192bit(uint8_t* pu8Buf, uint8_t u8BufLen);


/**
 * @brief  Get random data.
 * @return 32bit random data.
 */
extern uint32_t rom_hw_trng_gen_32bit(void);


#ifdef __cplusplus
}
#endif

#endif /* __HW_TRNG_H__ */
