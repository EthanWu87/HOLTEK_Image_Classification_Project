/*************************************************************************************************************
 * @file    hw_qdec.h
 * @version V1.0
 * @date    2020-09-22
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



#ifndef __HW_QDEC_H__
#define __HW_QDEC_H__

#ifdef __cplusplus
extern "C" {
#endif




/**
 * @brief  Set QDEC positive direction.
 * @param  enPol: Positive direction, @ref EN_QDEC_DIR_POL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_set_pos_direction(EN_QDEC_DIR_POL_T enPol);


/**
 * @brief  Enable QDEC input signal debounce.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_enable_debounce(void);


/**
 * @brief  Disable QDEC input signal debounce.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_disable_debounce(void);


/**
 * @brief  Initialize QDEC LED pin controller.
 * @param  enPol: LED output polarity, @ref EN_QDEC_LED_POL_T.
 * @param  u32Period: Led pin should setup before detect point, unit 62.5ns(1/16M).
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_cfg_led(EN_QDEC_LED_POL_T enPol, uint32_t u32Period);


/**
 * @brief  Set qdec sample period.
 * @param  enPeriod: Qdec sample period, @ref EN_QDEC_SAMPLE_PERIOD_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_set_sample_period(EN_QDEC_SAMPLE_PERIOD_T enPeriod);


/**
 * @brief  Set qdec acc threshold.
 *         When counter equal u8Val, will generate acc overflow interrupt.
 * @param  u8Val: Acc period.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_set_acc_thld(uint8_t u8Val);


/**
 * @brief  Set qdec acc double transition threshold.
 *         When counter equal u8Val, will generate double transition overflow interrupt.
 * @param  u8Val: Acc dbl period.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_set_acc_dbl_thld(uint8_t u8Val);


/**
 * @brief  Set qdec acc no change threshold.
 *         When counter equal u8Val, will generate go to sleep interrupt.
 * @param  u8Val: Acc no change period.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_set_acc_no_change_thld(uint8_t u8Val);


/**
 * @brief  Get qdec sample result.
 * @param  pu8Val: Point to sample result value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_get_sample_result(uint8_t* pu8Val);


/**
 * @brief  Clear qdec counter.
 * @param  u8Msk: Indicate which register will be clear, @ref EN_QDEC_CLR_CNT_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_clear_cnt(uint8_t u8Msk);


/**
 * @brief  Get qdec acc counter.
 * @param  ps16Val: Point to acc counter value.
 *                  bit8: 0 - positive direction, 1 - negative.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_get_acc_cnt(int16_t* ps16Val);


/**
 * @brief  Get qdec acc double transition counter.
 * @param  pu8Val: Point to acc double transition counter value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_get_acc_dbl_cnt(uint8_t* pu8Val);


/**
 * @brief  Get qdec acc no change counter.
 * @param  pu8Val: Point to acc no change counter value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_get_acc_no_change_cnt(uint8_t* pu8Val);


/**
 * @brief  Enable QDEC module.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_enable(void);


/**
 * @brief  Disable QDEC module.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_disable(void);


/**
 * @brief  Get indicated QDEC interrupt flag(status) by read the QDEC_INT_FLAG register.
 * @param  pu8IntFlag: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_get_interrupt_flag(uint8_t* pu8IntFlag);


/**
 * @brief  Clear indicated QDEC interrupt flag(status) by write the QDEC_INT_CLR register.
 * @param  u8Flag: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_clear_interrupt_flag(uint8_t u8Flag);


/**
 * @brief  Enable indicated QDEC interrupt by write QDEC_INT_EN register with indicated bits.
 * @param  u8IntEn: Indicate which interrupt will be enable,
 *                  bit-1 means enable
 *                  bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_enable_interrupt(uint8_t u8IntEn);


/**
 * @brief  Disable indicated QDEC interrupt by write QDEC_INT_EN register with indicated bits.
 * @param  u8IntDis: Indicate which interrupt will be enable,
 *                   bit-1 means disable
 *                   bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_qdec_disable_interrupt(uint8_t u8IntDis);


#ifdef __cplusplus
}
#endif

#endif /* __HW_QDEC_H__ */


