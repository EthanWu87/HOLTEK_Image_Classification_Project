/*************************************************************************************************************
 * @file    hw_rtc.h
 * @version V1.1
 * @date    2022-01-14
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


#ifndef __HW_RTC_H__
#define __HW_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif




/**
 * @brief  Get indicated timer interrupt flag(status) by read the RTC_INT_FLAG register.
 * @param  pu16Flag: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_get_interrupt_flag(uint16_t* pu16Flag);


/**
 * @brief  Clear indicated RTC interrupt flag(status) by write the RTC_INT_CLR register.
 * @param  u16Flag: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_clear_interrupt_flag(uint16_t u16Flag);


/**
 * @brief  Enable indicated RTC interrupt byt write RTC_INT_EN register with indicated bits.
 * @param  u8IntEn: Indicate which interrupt will be enable,
 *                  bit-1 means enable
 *                  bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_enable_interrupt(uint16_t u16IntEn);


/**
 * @brief  Disable indicated RTC interrupt byt write RTC_INT_EN register with indicated bits.
 * @param  u8IntDis: Indicate which interrupt will be disable,
 *                   bit-1 means disable
 *                   bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_disable_interrupt(uint16_t u16IntDis);


/**
 * @brief  Enable indicated RTC tick and overflow interrupt.
 * @param  u16IntEn: Indicate which interrupt will be enable, @ref EN_RTC_INT_T.
 *                   bit-1 means enable
 *                   bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_enable_tick_overflow_interrupt(uint16_t u16IntEn);


/**
 * @brief  Disable indicated RTC tick and overflow interrupt.
 * @param  u16IntEn: Indicate which interrupt will be enable, @ref EN_RTC_INT_T.
 *                   bit-1 means enable
 *                   bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_disable_tick_overflow_interrupt(uint16_t u16IntDis);


/**
 * @brief  Enable indicated RTC wakeup interrupt.
 * @param  u16WakeupEn: Indicate which wakeup interrupt will be enable, @ref EN_RTC_INT_WAKEUP_EN_T.
 *                      bit-1 means enable
 *                      bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_enable_wakeup(uint16_t u16WakeupEn);


/**
 * @brief  Disable indicated RTC wakeup interrupt.
 * @param  u16WakeupDis: Indicate which wakeup interrupt will be disable, @ref EN_RTC_INT_WAKEUP_EN_T
 *                       bit-1 means disable
 *                       bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_disable_wakeup(uint16_t u16WakeupDis);


/**
 * @brief  Start RTC counter.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_start(void);


/**
 * @brief  Stop RTC counter.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_stop(void);


/**
 * @brief  Get rtc current counter value.
 * @param  pu8Hi: Point to save rtc current counter value[39:32].
 * @param  pu32Lo: Point to save rtc current counter value[31:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_get_count(uint8_t* pu8Hi, uint32_t* pu32Lo);


/**
 * @brief  Get rtc current counter value.
 * @param  pu64Count: Point to save rtc current counter value[39:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_get_count64(uint64_t* pu64Count);


/**
 * @brief  Clear rtc counter.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_clear_count(void);


/**
 * @brief  Set RTC counter to 0xFFFFFFFFF0 to trigger overflow interrupt quickly.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_set_count_overflow(void);


/**
 * @brief  Set rtc prescale value.
 * @param  u16Prescale: prescale value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_set_prescale(uint16_t u16Prescale);


/**
 * @brief  Set rtc compare counter value.
 * @param  enCh: RTC compare channel, @ref EN_RTC_CH_T.
 * @param  u8Hi: RTC compare counter value[39:32].
 * @param  u32Lo: RTC compare counter value[31:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_set_compare(EN_RTC_CH_T enCh, uint8_t u8Hi, uint32_t u32Lo);


/**
 * @brief  Set rtc compare counter value.
 * @param  enCh: RTC compare channel, @ref EN_RTC_CH_T.
 * @param  u64Compare: RTC compare counter value[39:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_set_compare64(EN_RTC_CH_T enCh, uint64_t u64Compare);


/**
 * @brief  Get rtc compare counter value.
 * @param  enCh: RTC compare channel, @ref EN_RTC_CH_T.
 * @param  pu8Hi: Point to save rtc compare counter value[39:32].
 * @param  pu32Lo: Point to save rtc compare counter value[31:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_get_compare(EN_RTC_CH_T enCh, uint8_t* pu8Hi, uint32_t* pu32Lo);


/**
 * @brief  Get rtc compare counter value.
 * @param  enCh: RTC compare channel, @ref EN_RTC_CH_T.
 * @param  pu64Compare: Point to save rtc compare counter value[39:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_get_compare64(EN_RTC_CH_T enCh, uint64_t* pu64Compare);


/**
 * @brief  Get rtc work status.
 * @param  pu8Status: Point to save rtc work status.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_get_work_status(uint8_t* pu8Status);


/**
 * @brief  Get rtc wakeup source work status, the PMU enters low power consumption only when it is in stop state.
 * @param  pu8Status: Point to save stim wakeup source work status, @ref EN_RTC_WAKEUP_STATUS_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_get_wakeup_status(uint8_t* pu8Status);


/**
 * @brief  Reset rtc_pdw module.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_pdw_reset(void);


/**
 * @brief  Select RTC_CLK Clock Source.
 * @param  enSrc: rtc clock source selection. @ref EN_RTC_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_set_rtc_clk_src(EN_RTC_CLK_SRC_T enSrc);


/**
 * @brief  Configure LDO_RET(VDDRTC) output voltage.
 * @param  enVolt: Configure LDO_RET(VDDRTC) output voltage, @ref EN_RTC_LDO_RET_VOLT_T
 *                 Step is 50, unit: mV, range is 750mV to 1100mV.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_set_ldo_ret_output_voltage(EN_RTC_LDO_RET_VOLT_T enVolt);


/**
 * @brief  Configure software flag. Check if rtc module initialized or not.
 *         When VDDR powered down, this flag will be retained.
 * @param  u32SwFlag: Software flag.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rtc_set_sw_flag(uint32_t u32SwFlag);


#ifdef __cplusplus
}
#endif

#endif /* __HW_RTC_H__ */


