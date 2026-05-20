/*************************************************************************************************************
 * @file    hal_pmu.h
 * @version V1.1
 * @date    2022-01-10
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



#ifndef __HAL_PMU_H__
#define __HAL_PMU_H__


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef enum
{
    PWR_SEL_LDO  = 0x00,
    PWR_SEL_DCDC = 0x01,

} EN_PMU_PWR_SEL_T;

#define IS_VALID_PMU_PWR_SEL( SEL ) ( ((SEL) == PWR_SEL_LDO) || ((SEL) == PWR_SEL_DCDC) )


typedef enum
{
    EN_SYS_CLK_RC16M    = 0x00, /* No Crystal, Use RC16M, System Clock is 16MHz */
    EN_SYS_CLK_DCXO16M  = 0x01, /* Crystal is 16MHz, System Clock is 16MHz. */
    EN_SYS_CLK_PLL64M   = 0x02, /* Crystal is 16MHz, System Clock is 64MHz. */

} EN_SYS_CLK_SRC_SEL_T;

#define IS_VALID_SYS_CLK_SRC_SEL( SRC ) ( (SRC) <= EN_SYS_CLK_PLL64M )




/**********************************************************************************************************************
                                             PMU Sram Power Driver
**********************************************************************************************************************/

/**
 * @brief  Set part of RAM_SIZE_KBYTE_MAX KB ram or all of them to retention.
 * @param  u16RamSize: Size of ram which will keep retention. Must in multiples of 64. unit: KB.
 *         u16RamSize >= 0 && u16RamSize <= 256.
 * @return status: @ref EN_ERR_STA_T.
 */
// extern EN_ERR_STA_T rom_hal_pmu_set_sram_ret(uint16_t u16RamSize);





/**********************************************************************************************************************
                                                PMU Power Driver
**********************************************************************************************************************/

/**
 * @brief  Set PMU power out by LDO or DCDC.
 * @param  enSel: Select DCDC or LDO, @ref EN_PMU_PWR_SEL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_sel_power_act_out_mode(EN_PMU_PWR_SEL_T enSel);





/**********************************************************************************************************************
                                                PMU Clock Driver
**********************************************************************************************************************/

/**
 * @brief  Configure DCXO Low Clock(DCXO_LCLK) inverter, Current and Load Capacitance.
 * @param  u8buf: Number of inverters. The range of value is [0:7].
 * @param  u8Ib: dcxo current. The range of value is [0:7].
 * @param  u8Ngm: The number of inverters in parallel with the active part of the oscillator.
 *                The range of value is [0:7]. Suggest cfg to 2~4.
 * @param  u16Cap: dcxo load capacitance. Unit: 0.1pF, the range is [30:285].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_cfg_dcxo_lclk_param(uint8_t u8buf, uint8_t u8Ib, uint8_t u8Ngm, uint16_t u16Cap);


/**
 * @brief  Enable DCXO Low Clock(DCXO_LCLK).
 * @param  u16TimeMs: The stabilization time of crystal. Unit: ms.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_enable_dcxo_lclk(uint16_t u16TimeMs);


/**
 * @brief  Disable DCXO Low Clock(DCXO_LCLK).
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_disable_dcxo_lclk(void);


/**
 * @brief  Select Low Power Clock (LPWR_CLK) Source.
 * @param  enSrc: LPWR_CLK source sel, @ref EN_LPWR_CLK_SRC_T
 * @param  u16TimeMs: If system clock is @EN_LPWR_CLK_DCXO_LCLK,
 *                    it means the stabilization time of crystal. Unit: ms.
 *                    If system clock is @EN_LPWR_CLK_RC_LCLK, it means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_set_lpwr_clk_src(EN_LPWR_CLK_SRC_T enSrc, uint16_t u16TimeMs);


/**
 * @brief  Enable RC_HCLK(RC16M) Clock Output.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_enable_rc_hclk(void);


/**
 * @brief  Disable RC_HCLK(RC16M) Clock Output.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_disable_rc_hclk(void);


/**
 * @brief  Configure DCXO High Clock(DCXO_HCLK) Current and Load Capacitance.
 * @param  u8Ib: dcxo current. The range of value is [0:7].
 * @param  u8Ngm: The number of inverters in parallel with the active part of the oscillator.
 *                The range of value is [0:7]. Suggest cfg to 2~4.
 * @param  u16Cap: dcxo load capacitance. Unit: 0.1pF, the range is [30:285].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_cfg_dcxo_hclk_param(uint8_t u8Ib, uint8_t u8Ngm, uint16_t u16Cap);


/**
 * @brief  Configure DCXO High Clock(DCXO_HCLK) Stable Time, the unit is us.
 * @param  u16Time: dcxo stable time. The range of value is 0 to 7968us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_set_dcxo_hclk_stable_time(uint16_t u16TimeUs);


/**
 * @brief  Enable DCXO High Clock(DCXO_HCLK).
 * @param  enFreq: DCXO high clock source selection. 16MHz or 32MHz crystal. @ref EN_DCXO_HCLK_FREQ_T.
 * @param  u16TimeUs: The stabilization time of crystal. Unit: us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_enable_dcxo_hclk(EN_DCXO_HCLK_FREQ_T enFreq, uint16_t u16TimeUs);


/**
 * @brief  Disable DCXO High Clock(DCXO_HCLK).
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_disable_dcxo_hclk(void);


/**
 * @brief  Enable PLL_CLK(96MHz and 128MHz).
 * @param  enDCXOFreq: DCXO high clock source selection. 16MHz or 32MHz crystal, @ref EN_DCXO_HCLK_FREQ_T.
 * @param  u16TimeUs: The stabilization time of crystal. Unit: us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_enable_pll_clk(EN_DCXO_HCLK_FREQ_T enDCXOFreq, uint16_t u16TimeUs);


/**
 * @brief  Disable PLL_CLK(96MHz and 128MHz).
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_disable_pll_clk(void);


/**
 * @brief  Select System Clock(SYS_HCLK) Source.
 * @param  enSrc: System clock source selection, @ref EN_SYS_CLK_SRC_SEL_T.
 * @param  u16TimeUs: It means the stabilization time of crystal. Unit: us.
 *                    If system clock is @EN_SYS_CLK_RC16M, it means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_pmu_set_sys_clk_src(EN_SYS_CLK_SRC_SEL_T enSrc, uint16_t u16TimeUs);




#endif /* __HAL_PMU_H__ */


