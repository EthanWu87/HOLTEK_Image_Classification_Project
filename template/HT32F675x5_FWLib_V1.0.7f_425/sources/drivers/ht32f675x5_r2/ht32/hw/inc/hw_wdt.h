/*************************************************************************************************************
 * @file    hw_wdt.h
 * @version V1.0
 * @date    2021-06-08
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


#ifndef __HW_WDT_H__
#define __HW_WDT_H__

#ifdef __cplusplus
    extern "C" {
#endif 




/**
 * @brief  Trigger timer configuration valid.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @param  enCh: Indicate which timer will be cfg, @ref EN_TIMER_CH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_trig_cfg_valid(stWDT_Handle_t* pstWDT, uint32_t u32Cfg);


/**
 * @brief  Deinitializes the WDT Module and reset the registers.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_deinit(stWDT_Handle_t *pstWDT);


/**
 * @brief  Enable watchdog timer.
 *         This function needs 3 cycles of 32KHz to be valid.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_enable(stWDT_Handle_t* pstWDT);


/**
 * @brief  Disable watchdog timer.
 *         This function needs 3 cycles of 32KHz to be valid.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_disable(stWDT_Handle_t* pstWDT);


/**
 * @brief  Configure watchdog compare value(monitor time).
 *         This function needs 3 cycles of 32KHz to be valid.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @param  u32Compare: WDT compare counter, the unit is a cycle of 32KHz.
 * @return status: @ref EN_ERR_STA_T.
 **/
extern EN_ERR_STA_T rom_hw_wdt_set_compare(stWDT_Handle_t *pstWDT, uint32_t u32Compare);


/**
 * @brief  Get watchdog timer counter.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_get_counter(stWDT_Handle_t* pstWDT, uint32_t *pu32Counter);


/**
 * @brief  Enable watchdog reset system after wdt counter reach compare counter. (default)
 *         This function needs 3 cycles of 32KHz to be valid.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_enable_reset(stWDT_Handle_t* pstWDT);


/**
 * @brief  Disable watchdog reset system after wdt counter reach compare counter.
 *         This function needs 3 cycles of 32KHz to be valid.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_disable_reset(stWDT_Handle_t* pstWDT);


/**
 * @brief  Configure delay reset time.
 *         This function needs 3 cycles of 32KHz to be valid.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @param  u16Time: Time of delay reset, the unit is a cycle of 32KHz.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_set_delay_reset(stWDT_Handle_t* pstWDT, uint16_t u16Time);


/**
 * @brief  Clear watchdog timer counter.
 *         This function needs 3 cycles of 32KHz to be valid.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_feed(stWDT_Handle_t* pstWDT);


/**
 * @brief  Get indicated WDT interrupt flag(status) by read the WDT_INT_FLAG register.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @param  pu8IntMsk: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_get_interrupt_flag(stWDT_Handle_t* pstWDT, uint8_t* pu8IntMsk);


/**
 * @brief  Clear indicated WDT interrupt flag(status) by write the WDT_INT_CLR register.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @param  u8Msk: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_clear_interrupt_flag(stWDT_Handle_t* pstWDT, uint8_t u8Msk);


/**
 * @brief  Enable indicated WDT interrupt byt write WDT_INT_EN register with indicated bits.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @param  u8IntEn: Indicate which interrupt will be enable, 
 *                  bit-1 means enable
 *                  bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_enable_interrupt(stWDT_Handle_t* pstWDT, uint8_t u8IntEn);


/**
 * @brief  Disable indicated WDT interrupt byt write WDT_INT_EN register with indicated bits.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @param  u8IntDis: Indicate which interrupt will be disable, 
 *                   bit-1 means disable.
 *                   bit-0 means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_wdt_disable_interrupt(stWDT_Handle_t* pstWDT, uint8_t u8IntDis);


#ifdef __cplusplus
}
#endif

#endif /* _HW_WDT_H_ */


