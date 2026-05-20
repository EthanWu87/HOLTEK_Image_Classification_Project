/*************************************************************************************************************
 * @file    hw_pmu.h
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



#ifndef __HW_PMU_H__
#define __HW_PMU_H__

#ifdef __cplusplus
extern "C" {
#endif




/**********************************************************************************************************************
 *                                             PMU Interrupt Driver
 *********************************************************************************************************************/

/**
 * @brief  Get pmu interrupt flag(status) by read the PMU_LUT_INT_FLAG register.
 * @param  pu32IntMsk: Indicate which interrupt flag will be read
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_get_interrupt_flag(uint32_t* pu32IntMsk);


/**
 * @brief  Clear pmu interrupt flag(status) by write the PMU_LUT_INT_CLR register.
 * @param  u32IntMsk: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_clear_interrupt_flag(uint32_t u32IntMsk);


/**
 * @brief  PMU wakeup source selection.
 * @param  u8LutIdx: lut index, need < 16.
 * @param  enTrigSel: Lut trigger selection, @ref PUM_LUT_TRIG_SEL_T.
 * @param  enLutTrigId: Lut trigger id selection, @ref EN_LUT_TRIG_ID_T.
 * @param  enLutAction: Lut action selection, @ref EN_LUT_ACT_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_wakeup_source(uint8_t u8LutIdx, PUM_LUT_TRIG_SEL_T enTrigSel,
                                                 EN_LUT_TRIG_ID_T enLutTrigId, EN_LUT_ACT_T enLutAction);


/**
 * @brief  PMU gpio without debounce wakeup source selection.
 * @param  u8LutIdx: lut index, need < 16.
 * @param  enTrigSel: Lut trigger config, must select
 *                    LUT_TRIG_ID_GPIOA,
 *                    LUT_TRIG_ID_GPIOB,
 *                    LUT_TRIG_ID_GPIOC
 * @param  u32Pin: Which pin need to be configure, Only one pin can be configured at the same time, @ref EN_GPIO_PIN_T.
 * @param  u8LutAction: Lut action config, @ref EN_LUT_ACT_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_gpio_wakeup_source(uint8_t u8LutIdx, PUM_LUT_TRIG_SEL_T enTrigSel,
                                                      uint32_t u32Pin, EN_LUT_ACT_T enLutAction);


/**********************************************************************************************************************
                                             PMU Sram Power Driver
 *********************************************************************************************************************/

/**
 * @brief  Set part of sram or all of them to retention.
 * @param  u32SramBlock: Blocks of ram which will keep retention.
 *         Each bit correspoding a SRAM block.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_sram_block_ret(uint32_t u32SramBlock);


/**
 * @brief  Set part of sram or all of them to no retention(shutdown).
 * @param  u32SramBlock: Blocks of ram which will shut down.
 *         Each bit correspoding a SRAM block.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_clr_sram_block_ret(uint32_t u32SramBlock);





/**********************************************************************************************************************
                                                PMU Power Driver
 *********************************************************************************************************************/

/**
 * @brief  Enable LDO_ACT Output When LDO in Active Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_enable_ldo_act_output(void);


/**
 * @brief  Disable LDO_ACT Output When LDO in Active Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_disable_ldo_act_output(void);


/**
 * @brief  Configure LDO Output Voltage which for RF Module.
 * @param  enVolt: Configure LDO_ACT output voltage by active mode, @ref EN_LDO_ACT_VOLT_T
 *                 Step is 50, unit: mV, range is 950mV to 1300mV.
 *         The voltage of LDO_ACT should be at lease 50mV higher than the voltage of LDO_DIG.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_ldo_act_voltage(EN_LDO_ACT_VOLT_T enVolt);


/**
 * @brief  Enable LDO_1V8 Output When DCDC MISO 1.8V output in Active Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_enable_ldo_1v8_output(void);


/**
 * @brief  Disable LDO_1V8 Output When DCDC MISO 1.8V output in Active Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_disable_ldo_1v8_output(void);


/**
 * @brief  Enable LDO_DIG Output When LDO in Active Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_enable_ldo_dig_output(void);


/**
 * @brief  Disable LDO_DIG Output When LDO in Active Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_disable_ldo_dig_output(void);


/**
 * @brief  Configure LDO Output Voltage which for digital module and LDO_RET_ACT Output Voltage in Active Mode.
 * @param  enVolt: Configure LDO Output Voltage, Step is 50, unit: mV, range is 900mV to 1100mV.
 *         When SYS_CLK is 16MHz, LDO_DIG can configure to 900mV;
 *         When SYS_CLK is 128MHz, LDO_DIG should configure to 1100mV.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_ldo_dig_voltage(EN_LDO_DIG_VOLT_T enVolt);


/**
 * @brief  Get LDO output voltage which for digital module.
 * @param  pu8Volt: Pointer to the buffer to get LDO Output Voltage, @ref EN_LDO_DIG_VOLT_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_get_ldo_dig_voltage(uint8_t* pu8Volt);


/**
 * @brief  Configure LDO_RET_ACT Output Voltage in Active Mode.
 * @param  enSleepVolt: Configure LDO_RET output voltage by sleep mode, @ref EN_LDO_RET_VOLT_T.
 *                      Step is 50, unit: mV, range is 750mV to 1100mV.
 *         When SYS_CLK is 16MHz, LDO_RET_ACT can configure to 900mV;
 *         When SYS_CLK is 128MHz, LDO_RET_ACT should configure to 1100mV.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_ldo_ret_act_voltage(EN_LDO_RET_VOLT_T enVolt);


/**
 * @brief  Configure LDO_RET_SLEEP Output Voltage in Sleep Mode.
 * @param  enSleepVolt: Configure LDO_RET output voltage by sleep mode, @ref EN_LDO_RET_VOLT_T.
 *                      Step is 50, unit: mV, range is 750mV to 1100mV.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_ldo_ret_sleep_voltage(EN_LDO_RET_VOLT_T enSleepVolt);


/**
 * @brief  Configure DCDC(include SISO, SIDO) parameter.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_dcdc_init(void);


/**
 * @brief  Enable DCDC Output When DC-DC in Active Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_enable_dcdc_act_output(void);


/**
 * @brief  Disable DCDC Output When DC-DC in Active Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_disable_dcdc_act_output(void);


/**
 * @brief  Configure DCDC Output Voltage which for RF Module.
 * @param  enVolt: Configure DCDC_ACT output voltage by active mode, @ref EN_DCDC_ACT_VOLT_T.
 *                 Unit: mV, range is 950mV to 1300mV.
 *         The voltage of DCDC_ACT should be at lease 50mV higher than the voltage of LDO_DIG.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_dcdc_act_voltage(EN_DCDC_ACT_VOLT_T enVolt);


/**
 * @brief  Enable DCDC Output When DC-DC in sleep Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_enable_dcdc_ret_output(void);


/**
 * @brief  Disable DCDC Output When DC-DC in Low Power Mode.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_disable_dcdc_ret_output(void);


/**
 * @brief  Configure DCDC_LPWR Output Voltage in Sleep Mode.
 * @param  enLpwrVolt: Configure DCDC_LPWR output voltage by sleep mode, @ref EN_DCDC_LPWR_VOLT_T.
 *                     Unit: mV, range is 650mV to 1050mV.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_dcdc_ret_voltage(EN_DCDC_LPWR_VOLT_T enLpwrVolt);


/**
 * @brief  Select DCDC Low Power Clock(DCDC_LPWR_CLK) Division With RC_LCLK.
 * @param  enDiv: The divisor of DCDC_LPWR_CLK, @ref EN_DCDC_LPWR_CLK_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_dcdc_ret_clk_divisor(EN_DCDC_LPWR_CLK_T enDiv);


/**
 * @brief  PMU sleep mode select.
 * @param  enMode: pmu sleep mode, @ref EN_PWR_MODE_T.
 *         PWR_MODE_DEEPSLEEP: RC_LCLK clock is keep working (shutdown with 32K);
 *         PWR_MODE_HIBERNATION: RC_LCLK clock will turn off (shutdown without 32K);
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_low_power_mode(EN_PWR_MODE_T enMode);





/**********************************************************************************************************************
 *                                              PMU Clock Driver
 *********************************************************************************************************************/

/**
 * @brief  Check RC Low Clock(RC_LCLK) is Enable or not.
 * @return status: false(0) - RC_LCLK is Disabled.
 *                 true(1)  - RC_LCLK is Enabled.
 */
extern bool rom_hw_pmu_rc_lclk_is_enable(void);


/**
 * @brief  Check DCXO Low Clock(DCXO_LCLK) is power on or off.
 * @return status: false(0) - DCXO_LCLK is powered off.
 *                 true(1)  - DCXO_LCLK is powered on.
 */
extern bool rom_hw_pmu_dcxo_lclk_is_power_on(void);


/**
 * @brief  Check DCXO Low Clock(DCXO_LCLK) is output.
 * @return status: false(0) - DCXO_LCLK output is disabled.
 *                 true(1)  - DCXO_LCLK output is enabled.
 */
extern bool rom_hw_pmu_dcxo_lclk_is_clk_out(void);


/**
 * @brief  Check RC High Clock(RC_HCLK) is Power On or Off.
 * @return status: false(0) - RC_HCLK is Powered Off.
 *                 true(1)  - RC_HCLK is Powered On.
 */
extern bool rom_hw_pmu_rc_hclk_is_power_on(void);


/**
 * @brief  Check DCXO High Clock(DCXO_HCLK) is Output.
 * @return status: false(0) - DCXO_HCLK output is disabled.
 *                 true(1)  - DCXO_HCLK output is enabled.
 */
extern bool rom_hw_pmu_dcxo_hclk_is_clk_out(void);


/**
 * @brief  Check DCXO High Clock(DCXO_HCLK) is Power On or Off.
 * @return status: false(0) - DCXO_HCLK is Powered Off.
 *                 true(1)  - DCXO_HCLK is Powered On.
 */
extern bool rom_hw_pmu_dcxo_hclk_is_power_on(void);


/**
 * @brief  Check RC High Clock(RC_HCLK) is Output.
 * @return status: false(0) - RC_HCLK output is disabled.
 *                 true(1)  - RC_HCLK output is enabled.
 */
extern bool rom_hw_pmu_rc_hclk_is_clk_out(void);


/**
 * @brief  Check PLL Clock(PLL_CLK) is Power On or Off.
 * @return status: false(0) - PLL_CLK is Powered Off.
 *                 true(1)  - PLL_CLK is Powered On.
 */
extern bool rom_hw_pmu_pll_clk_is_power_on(void);


/**
 * @brief  Check PLL Clock(PLL96M_CLK or PLL128M_CLK) is Output.
 * @return status: false(0) - PLL96M_CLK or PLL128M_CLK output is disabled.
 *                 true(1)  - PLL96M_CLK and PLL128M_CLK output is enabled.
 */
extern bool rom_hw_pmu_pll_clk_is_clk_out(void);


/**
 * @brief  Turn Clock Power On.
 * @param  enCLK: Indicate which clock will be powered on, @ref EN_CLK_POWER_CTRL_T.
 * @param  u32TimeUs: The setup time of clock. Unit: us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_turn_clk_power_on(EN_CLK_POWER_CTRL_T enCLK, uint32_t u32TimeUs);


/**
 * @brief  Turn Clock Power Off.
 * @param  enCLK: Indicate which clock will be powered off, @ref EN_CLK_POWER_CTRL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_turn_clk_power_off(EN_CLK_POWER_CTRL_T enCLK);


/**
 * @brief  Enable Clock Output.
 * @param  enCLK: Indicate which clock will be output, @ref EN_CLK_OUT_CTRL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_enable_clk_output(EN_CLK_OUT_CTRL_T enCLK);


/**
 * @brief  Disable Clock Output.
 * @param  enCLK: Indicate which clock will be closed, @ref EN_CLK_OUT_CTRL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_disable_clk_output(EN_CLK_OUT_CTRL_T enCLK);


/**
 * @brief  Check DCXO Low Clock(DCXO_LCLK) configuration is valid.
 * @param  pstBuf: Pointer to a stDCXOBuf_t structure that contains.
 * @param  pstPara: Pointer to a stDCXOParam_t structure that contains.
 * @return status: false(0) - DCXO_LCLK configuration is invalid.
 *                 true(1)  - DCXO_LCLK configuration is valid.
 */
extern bool rom_hw_pmu_dcxo_lclk_cfg_is_valid(stDCXOBuf_t* pstBuf, stDCXOParam_t* pstParam);


/**
 * @brief  Configure DCXO Low Clock(DCXO_LCLK, 32KHz) inverter, current and Load Capacitance.
 * @param  pstBuf: Pointer to a stDCXOBuf_t structure that contains,
 *                  u8PosBuf, u8NegBuf: Number of inverters. The range of value is [0:7].
 * @param  pstPara: Pointer to a stDCXOParam_t structure that contains,
 *                  u8Ib: dcxo current. The range of value is [0:7].
 *                  u8Ngm: The number of inverters in parallel with the active part of the oscillator.
 *                         The range of value is [0:7]. Suggest cfg to 2~4.
 *                  u8Cap: dcxo load capacitance. Unit: 0.1pF, the range is [0:255] which means 3.0pF~28.5pF.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_dcxo_lclk_param(stDCXOBuf_t* pstBuf, stDCXOParam_t* pstParam);


/**
 * @brief  Configure RC32K_CLK calibration value to calibrate RC32K_CLK.
 * @param  u8Val: RC_LCLK tune value, the range is [0:255].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_rc_lclk_tune(uint8_t u8Val);


/**
 * @brief  Configure RC_HCLK calibration value to calibrate RC16M_CLK or RC48M_CLK.
 * @param  u8Val: RC_HCLK tune value, the range is [0:127].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_rc_hclk_tune(uint8_t u8Val);


/**
 * @brief  Enable or disable output RC_HCLK clock while turning on RC_HCLK.
 * @param  enMode: RC_HCLK clock output mode.
 *                 b0 - Delay 0.5 to 1.5 32K clock cycles to output RC_HCLK after turn on RC_HCLK.
 *                 b1 - Output RC_HCLK while turning on RC_HCLK immediately.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_rc_hclk_sync_out(EN_RC_HCLK_SYNC_OUT_MODE_T enMode);


/**
 * @brief  Configure DCXO High Clock(DCXO_HCLK) Power to DCDC_ACT or VDDR.
 * @param  enPwr: DCXO_HCLK power selection, @ref EN_DCXO_HCLK_PWR_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_sel_dcxo_hclk_pwr(EN_DCXO_HCLK_PWR_T enPwr);


/**
 * @brief  Configure DCXO High Clock(DCXO_HCLK) Stable Time after wakeup, unit: 31.25us.
 * @param  u8Time: the stable time, Rang is [0:255], unit is 31.25us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_dcxo_hclk_stable_time(uint8_t u8Time);


/**
 * @brief  Configure DCXO High Clock(DCXO_HCLK) Current and Load Capacitance.
 * @param  pstPara: Pointer to a stDCXOParam_t structure that contains,
 *                  u8Ib: dcxo current. The range of value is [0:7].
 *                  u8Ngm: The number of inverters in parallel with the active part of the oscillator.
 *                         The range of value is [0:7]. Suggest cfg to 2~4.
 *                  u8Cap: dcxo load capacitance. Unit: 0.1pF, the range is [0:255] which means 3.0pF~28.5pF.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_set_dcxo_hclk_param(stDCXOParam_t* pstParam);


/**
 * @brief  Configure USB phy iso sel.
 * @param  enIso: USB phy iso, @ref EN_USB_PHY_RX_ISO_CFG_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_pmu_sel_usb_phy_iso(EN_USB_PHY_RX_ISO_CFG_T enIso);


#ifdef __cplusplus
}
#endif

#endif /* __HW_PMU_H__ */

