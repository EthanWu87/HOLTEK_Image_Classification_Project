/*************************************************************************************************************
 * @file    hw_i2s.h
 * @version V1.1
 * @date    2023-06-10
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


#ifndef __HW_I2S_H__
#define __HW_I2S_H__

//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef union
{
    uint32_t u32Cfg;

    struct
    {
        uint32_t u8BLCKEdge : 1;     /* @ref EN_I2S_BCLK_CPOL_T       */
        uint32_t u8InvertWCLK : 1;   /* @ref EN_I2S_INVERT_WCLK_T     */
        uint32_t u8Standard : 2;     /* @ref EN_I2S_STANDARD_T        */
        uint32_t u8dataFormat : 2;   /* @ref EN_I2S_DATA_FROMAT_T     */
        uint32_t u8ChSel : 2;        /* @ref EN_I2S_CH_SEL_T          */
        uint32_t u8Mclkoutput : 2;   /* @ref EN_I2S_MCLK_SEL_T        */
        uint32_t u8Mode : 1;         /* @ref EN_I2S_WORK_MODE_T       */
        uint32_t Reserved0 : 2;      /* Reserved                      */
        uint32_t Reserved1 : 1;      /* Reserved                      */
        uint32_t u8Mclk_en : 1;      /* @ref EN_I2S_MCLK_EN_T         */
        uint32_t Reserved2 : 3;      /* invalid                       */
        uint32_t u8rxDataStrgEx : 1; /* @ref EN_I2S_RX_DATA_STRG_EX_T */

    } stCfg;

} unI2SCfg_t;

/**********************************************************************************************************************
 *                                             I2S Interrupt Cfg
 *********************************************************************************************************************/

/**
 * @brief  Get indicated i2s interrupt flag(status).
 * @param  pu32Flag: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_get_interrupt_flag(uint32_t *pu32Flag);

/**
 * @brief  Clear indicated I2S interrupt flag(status).
 * @param  u32Flag: Indicate which flag will be cleared
 *                  bit-1 means clear
 *                  bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_clear_interrupt_flag(uint32_t u32Flag);

/**
 * @brief  Enable indicated i2s interrupt.
 * @param  u32IntEn: Indicate which interrupt will be enable,
 *                   bit-1 means enable
 *                   bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_enable_interrupt(uint32_t u32IntEn);

/**
 * @brief  disable indicated i2s interrupt.
 * @param  u32IntDis: Indicate which interrupt will be disable,
 *                    bit-1 means disable
 *                    bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_disable_interrupt(uint32_t u32IntDis);

/**********************************************************************************************************************
 *                                             I2S Module Cfg
 *********************************************************************************************************************/

/**
 * @brief  I2S module deinit.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_deinit(void);

/**
 * @brief  Configure I2S.
 * @param  u32Cfg: I2C configuation.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_init(uint32_t u32Cfg);

/**
 * @brief  Set i2s work mode.
 * @param  enWorkmode: Config work mode, @ref EN_I2S_WORK_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_set_work_mode(EN_I2S_WORK_MODE_T enWorkmode);

/**
 * @brief  Set i2s wclk width which determine the sampling rate. fWCLK = fBCLK / wclkWidth / 2.
 * @note   fWCLK must great than or equal to 21KHz!!!
 * @param  enWclkWidth: wclk width or data Frame length.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_set_wclk_freq(uint8_t enWclkWidth);

/**
 * @brief  Enable i2s tx mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_enable_tx(void);

/**
 * @brief  Disable i2s tx mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2s_disable_tx(void);

#endif /* __HW_I2S_H__ */
