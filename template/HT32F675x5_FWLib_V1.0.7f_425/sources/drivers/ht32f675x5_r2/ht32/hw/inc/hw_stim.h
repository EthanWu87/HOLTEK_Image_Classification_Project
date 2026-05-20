/*************************************************************************************************************
 * @file    hw_stim.h
 * @version V1.1
 * @date    2022-01-12
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


#ifndef __HW_STIM_H__
#define __HW_STIM_H__

#ifdef __cplusplus
extern "C" {
#endif




/**
 * @brief  Get indicated timer interrupt flag(status) by read the STIM_INT_FLAG register.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  pu16Flag: Indicate which interrupt flag will be read
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_get_interrupt_flag(stSTIM_Handle_t* pstSTIM, uint16_t* pu16Flag);


/**
 * @brief  Clear indicated STIM interrupt flag(status) by write the STIM_INT_CLR register.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  u16Flag: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_clear_interrupt_flag(stSTIM_Handle_t* pstSTIM, uint16_t u16Flag);


/**
 * @brief  Enable indicated STIM interrupt by write STIM_INT_EN register with indicated bits.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  u16IntEn: Indicate which interrupt will be enable, @ref EN_STIM_INT_T
 *                   bit-1 means enable
 *                   bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_enable_interrupt(stSTIM_Handle_t* pstSTIM, uint16_t u16IntEn);


/**
 * @brief  Disable indicated STIM interrupt by write STIM_INT_EN register with indicated bits.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  u16IntDis: Indicate which interrupt will be disable, @ref EN_STIM_INT_T
 *                    bit-1 means disable
 *                    bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_disable_interrupt(stSTIM_Handle_t* pstSTIM, uint16_t u16IntDis);


/**
 * @brief  Enable indicated STIM tick and overflow interrupt.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  u16IntEn: Indicate which interrupt will be enable, @ref EN_STIM_INT_TICK_OVFLW_T
 *                   bit-1 means enable
 *                   bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_enable_tick_overflow_interrupt(stSTIM_Handle_t* pstSTIM, uint16_t u16IntEn);


/**
 * @brief  Disable indicated STIM tick and overflow interrupt.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  u16IntEn: Indicate which interrupt will be enable, @ref EN_STIM_INT_TICK_OVFLW_T
 *                   bit-1 means enable
 *                   bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_disable_tick_overflow_interrupt(stSTIM_Handle_t* pstSTIM, uint16_t u16IntDis);


/**
 * @brief  Enable indicated STIM wakeup interrupt.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  u16WakeupEn: Indicate which wakeup interrupt will be enable, @ref EN_STIM_INT_WAKEUP_EN_T
 *                      bit-1 means enable
 *                      bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_enable_wakeup(stSTIM_Handle_t* pstSTIM, uint16_t u16WakeupEn);


/**
 * @brief  Disable indicated STIM wakeup interrupt.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  u16WakeupDis: Indicate which wakeup interrupt will be disable, @ref EN_STIM_INT_WAKEUP_EN_T
 *                       bit-1 means disable
 *                       bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_disable_wakeup(stSTIM_Handle_t* pstSTIM, uint16_t u16WakeupDis);


/**
 * @brief  Start STIM counter.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_start(stSTIM_Handle_t* pstSTIM);


/**
 * @brief  Stop STIM counter.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_stop(stSTIM_Handle_t* pstSTIM);


/**
 * @brief  Clear stim counter.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_clear_count(stSTIM_Handle_t* pstSTIM);


/**
 * @brief  Set STIM counter to 0xFFFFFFF0 to trigger overflow interrupt quickly.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_set_count_overflow(stSTIM_Handle_t* pstSTIM);


/**
 * @brief  Get stim current counter value.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  pu32Count: Point to save stim current counter value[31:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_get_count(stSTIM_Handle_t* pstSTIM, uint32_t* pu32Count);


/**
 * @brief  Set stim prescale value.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  u16Prescale: prescale value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_set_prescale(stSTIM_Handle_t* pstSTIM, uint16_t u16Prescale);


/**
 * @brief  Set stim compare counter value.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  enCh: STIM compare channel, @ref EN_STIM_CH_T.
 * @param  u32Comp: STIM compare counter value[31:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_set_compare(stSTIM_Handle_t* pstSTIM, EN_STIM_CH_T enCh, uint32_t u32Comp);


/**
 * @brief  Get stim compare counter value.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  enCh: STIM compare channel, @ref EN_STIM_CH_T.
 * @param  pu32Comp: Point to save stim compare counter value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_get_compare(stSTIM_Handle_t* pstSTIM, EN_STIM_CH_T enCh, uint32_t* pu32Comp);


/**
 * @brief  Get stim work status.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  pu8Status: Point to save stim work status.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_get_work_status(stSTIM_Handle_t* pstSTIM, uint8_t* pu8Status);


/**
 * @brief  Get stim wakeup source work status,the PMU enters low power consumption only when it is in stop state.
 * @param  pstSTIM: STIM handle, Should be STIM0 / STIM1.
 * @param  pu8Status: Point to save stim wakeup source work status,@ref EN_STIM_WAKEUP_STATUS_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_stim_get_wakeup_status(stSTIM_Handle_t* pstSTIM, uint8_t* pu8State);


#ifdef __cplusplus
}
#endif


#endif /* __HW_STIM_H__ */


