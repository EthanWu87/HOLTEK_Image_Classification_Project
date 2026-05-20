/*************************************************************************************************************
 * @file    hw_crg.h
 * @version V1.1
 * @date    2022-01-11
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



#ifndef __HW_CRG_H__
#define __HW_CRG_H__

#ifdef __cplusplus
extern "C"{
#endif




/**********************************************************************************************************************
 *                                             CRG Clock Source
 *********************************************************************************************************************/

/**
 * @brief  Select Low Power Clock(LPWR_CLK, 32K Clock) Source.
 * @param  enSrc: LPWR_CLK source selection. @ref EN_LPWR_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_lpwr_clk_src(EN_LPWR_CLK_SRC_T enSrc);


/**
 * @brief  Get Low Power Clock(LPWR_CLK, 32K Clock) Source.
 * @param  pu32Src: Point to LPWR_CLK source. @ref EN_LPWR_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_get_lpwr_clk_src(uint32_t* pu32Src);


/**
 * @brief  Check System Clock(SYS_CLK) Source is RC_HCLK or not.
 * @return status: false(0) - SYS_CLK source is not RC_HCLK.
 *                 true(1)  - SYS_CLK source is RC_HCLK.
 */
extern bool rom_hw_crg_sys_clk_src_is_rc_hclk(void);


/**
 * @brief  Select DCXO_HCLK Clock Frequency.
 * @param  enFreq: DCXO high clock source frequency. 16MHz or 32MHz crystal oscillator. @ref EN_DCXO_HCLK_FREQ_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_dcxo_hclk_freq(EN_DCXO_HCLK_FREQ_T enFreq);


/**
 * @brief  Select System Clock(SYS_CLK) Source.
 * @param  enSrc: System clock source selection. @ref EN_SYS_CLK_SEL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_sys_clk_src(EN_SYS_CLK_SEL_T enSrc);


/**
 * @brief  Get System Clock(SYS_CLK) Source.
 * @param  pu32Src: Point to system clock source. @ref EN_SYS_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_get_sys_clk_src(uint32_t* pu32Src);


/**
 * @brief  Select Audio ADC Clock(ADC_CLK) Source Clock.
 * @param  enADC: ADC channel, @ref EN_CRG_ADC_T.
 * @param  enSrc: The source clock of ADC_CLK, @ref EN_ADC_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_adc_clk_src(EN_CRG_ADC_T enADC, EN_ADC_CLK_SRC_T enSrc);


/**
 * @brief  Select GTIM Clock(GTIMn_CLK) Source.
 * @param  enGTIM: GTIM channel, @ref EN_CRG_GTIM_T.
 * @param  enSrc: The source of GTIM clock, @ref EN_GTIM_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_gtim_clk_src(EN_CRG_GTIM_T enGTIM, EN_GTIM_CLK_SRC_T enSrc);


/**
 * @brief  Get GPTimer Clock(GTIMn_CLK) Source.
 * @param  enGTIM: GTIM channel, @ref EN_CRG_GTIM_T.
 * @param  pu32Src: Point to GPTimer source, @ref EN_GTIM_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_get_gtim_clk_src(EN_CRG_GTIM_T enGTIM, uint32_t* pu32Src);


/**
 * @brief  Select QSPI Clock(QSPIn_CLK) Source.
 * @param  enQSPI: QSPI channel, @ref EN_CRG_QSPI_T.
 * @param  enSrc: The source of QSPI clock, @ref EN_QSPI_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_qspi_clk_src(EN_CRG_QSPI_T enQSPI, EN_QSPI_CLK_SRC_T enSrc);


/**
 * @brief  Configure Analog Peripheral Outout Clock(ANA_OUT_CLK) output from gpio PB15.
 *         Need set pid of PB15 to PID_TEST_CLK_OUT.
 *         ==> rom_hw_gpio_set_pin_pid( GPIOB, GPIO_PIN_15, PID_DEBUG_MODE);
 * @param  enClk: The clock which would be output, @ref EN_ANA_OUT_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_ana_output_clk_src(EN_ANA_OUT_CLK_SRC_T enClk);





/**********************************************************************************************************************
 *                                             CRG Clock Division
 *********************************************************************************************************************/

/**
 * @brief  Enable RC High Clock(RC_HCLK) or DCXO High Clock(DCXO_HCLK) Division to LPWR_CLK.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_enable_hclk_div_lclk(void);


/**
 * @brief  Disable RC High Clock(RC_HCLK) or DCXO High Clock(DCXO_HCLK) Division to LPWR_CLK.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_disable_hclk_div_lclk(void);


/**
 * @brief  Select GTIM System Clock (GTIM_SCLK) division with SYS_CLK.
 * @param  enDiv: The divisor of system clock, @ref EN_GTIM_SYS_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
**/
// extern EN_ERR_STA_T rom_hw_crg_set_gtim_sys_clk_divisor(EN_GTIM_SYS_CLK_DIV_T enDiv);


/**
 * @brief  Select System PMU Clock(PMU_HCLK) division with SYS_CLK.
 * @param  enDiv: The divisor of apb clock, @ref EN_PMU_HCLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_pmu_hclk_divisor(EN_PMU_HCLK_DIV_T enDiv);


/**
 * @brief  Select MP APB Clock(MP_APB_CLK) division with AHB_CLK.
 * @param  enDiv: The divisor of apb clock, @ref EN_APB_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_apb_clk_divisor(EN_APB_CLK_DIV_T enDiv);


/**
 * @brief  Select CP AHB Clock(CP_AHB_CLK, CM0P) Divison With MP_AHB_CLK. (CP_AHB_CLK must >= 16MHz).
 * @param  enDiv: The divisor of ahb clock, @ref EN_AHB_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_cp_ahb_clk_divisor(EN_AHB_CLK_DIV_T enDiv);


/**
 * @brief  Configure RC_HCLK frequency to 16MHz or 48MHz.
 *         16MHz: Enable rc_hclk division by 3.
 * @param  enFreq: RC_HCLK frequency, @ref EN_RC_HCLK_FREQ_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_rc_hclk_frequency(EN_RC_HCLK_FREQ_T enFreq);


/**
 * @brief  Configure MP AHB Clock(MP_AHB_CLK, CM33) Divison With SYS_CLK. (MP_AHB_CLK must >= 16MHz).
 * @param  enDiv: The divisor of ahb clock, @ref EN_AHB_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_mp_ahb_clk_divisor(EN_AHB_CLK_DIV_T enDiv);


/**
 * @brief  Select pll128m clock (PLL128M_CLK) Division.
 * @param  enDiv: The divisor of PLL128M_CLK, @ref EN_PLL128M_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_pll128m_clk_divisor(EN_PLL128M_CLK_DIV_T enDiv);


/**
 * @brief  Configure Audio ADC Clock(ADC_CLK) division with SYS_CLK.
 * @param  enADC: Audio ADC channel, @ref EN_CRG_ADC_T.
 * @param  u8Div: The divisor of ADC_CLK. From 0 to 255, Step by 1.
 *                0-->Division by 2;
 *                1-->Division by 4;
 *                2-->Division by 6;
 *                ......
 *                255-->Division by 512;
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_adc_clk_divisor(EN_CRG_ADC_T enADC, uint8_t u8Div);


/**
 * @brief  Configure I2S BClock (I2S_BCLK) division with PERI_CLK.
 * @param  u8Div: The divisor of I2S_BCLK, @ref EN_I2S_BCLK_DIV_T.
 *                1-->Division by 1;
 *                2-->Division by 2;
 *                4-->Division by 8;
 *                ......
 *                31-->Division by 62;
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_i2s_bclk_divisor(EN_I2S_BCLK_DIV_T enDiv);


/**
 * @brief  Select CPTO Clock(CPTOn_CLK) division with CP_AHB_CLK.
 * @param  enCPTO: CPTO channel, @ref EN_CRG_CPTO_T.
 * @param  enDiv: The divisor of CPTO clock, @ref EN_CPTO_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_cpto_clk_divisor(EN_CRG_CPTO_T enCPTO, EN_CPTO_CLK_DIV_T enDiv);


/**
 * @brief  Select LLC Clock(LLC_CLK) division with CP_AHB_CLK.
 * @param  enDiv: The divisor of llc clock, @ref EN_LLC_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_llc_clk_divisor(EN_LLC_CLK_DIV_T enDiv);


/**
 * @brief  Select QSPI Clock(QSPIn_CLK) division with QSPIn_CLK.
 * @param  enQSPI: QSPI channel, @ref EN_CRG_QSPI_T.
 * @param  enDiv: The divisor of QSPI clock, @ref EN_QSPI_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_qspi_clk_divisor(EN_CRG_QSPI_T enQSPI, EN_QSPI_CLK_DIV_T enDiv);


/**
 * @brief  Select System Out Clock (OUTPUT_CLK) division with SYS_CLK.
 * @param  u8Div: The divisor of OUTPUT_CLK, @ref EN_SYS_OUT_CLK_DIV_T.
 *                0-->Division by 1;
 *                1-->Division by 2;
 *                2-->Division by 4;
 *                ......
 *                15-->Division by 30;
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_set_sys_clk_out_divisor(EN_SYS_OUT_CLK_DIV_T enDiv);




/**********************************************************************************************************************
 *                                             CRG Clock Source
 *********************************************************************************************************************/

/**
 * @brief  Turn xx_CLK clock gating on.
 * @param  u8En: Indicate which clock gate will be turned on. @ref EN_CRG_CLK_GATE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_enable_clk_gate(uint8_t u8En);


/**
 * @brief  Turn xx_CLK clock gating off.
 * @param  u8Dis: Indicate which clock gate will be turned off. @ref EN_CRG_CLK_GATE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_disable_clk_gate(uint8_t u8Dis);


/**
 * @brief  Turn xx_CLK clock gating on or off. Each bit corresponding a module.
 *         0: Turn xx_CLK clock gating off.
 *         1: Turn xx_CLK clock gating on.
 * @param  u32Reg0: Clock gate control register 0.
 * @param  u32Reg1: Clock gate control register 1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_clk_gate_ctrl(uint32_t u32Reg0, uint32_t u32Reg1);





/**********************************************************************************************************************
 *                                             CRG Reset Control
 *********************************************************************************************************************/

/**
 * @brief  Keeping xx Module Software Reseting.
 * @param  enReset: xx module software reset.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_keep_reset(EN_CRG_SW_RST_T enReset);


/**
 * @brief  Release xx Module Software Reset.
 * @param  enReset: xx module software release reset.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_release_reset(EN_CRG_SW_RST_T enReset);


/**
 * @brief  Control xx Module Software Reset. Each bit corresponding a module.
 *         0: Release xx Module Software Reset.
 *         1: Keeping xx Module Software Reseting.
 * @param  u32Reg0: Software reset control register 0
 * @param  u32Reg1: Software reset control register 1
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_reset_ctrl(uint32_t u32Reg0, uint32_t u32Reg1);


/**
 * @brief  Main-Processor(mp)(cm33) Software Reset.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_mp_reset(void);


/**
 * @brief  CO-Processor(cp)(cm0p) Software Reset.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_cp_reset(void);


/**
 * @brief  System Software Reset.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_system_reset(void);


/**
 * @brief  Get reset flag(status).
 * @param  pu16RstFlag: Indicate which reset flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_get_reset_flag(uint16_t* pu16RstFlag);


/**
 * @brief  Clear reset flag(status).
 * @param  u16Flag: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_clear_reset_flag(uint16_t u16Flag);


/**
 * @brief  Enable WDT1 reset system.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_enable_wdt1_reset_sys(void);


/**
 * @brief  Disable WDT1 reset system.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_disable_wdt1_reset_sys(void);




/**********************************************************************************************************************
 *                                             CRG Calibration
 *********************************************************************************************************************/

/**
 * @brief  Configure Calibrate RC Clock.
 * @param  enSel: RC clock source selection, @ref EN_CRG_CALIB_CLK_SEL_T.
 * @param  u8Speed: The speed of calibration. The smaller the value, the faster the speed of calibration.
 *                  The range if [0,15].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_cfg_cali_rc_clk(EN_CRG_CALIB_CLK_SEL_T enSel, uint8_t u8Speed);


/**
 * @brief  Enable pmu calibration.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_enable_pmu_cali(void);


/**
 * @brief  Disable pmu calibration.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_disable_pmu_cali(void);


/**
 * @brief  Enable calibration.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_enable_cali(void);


/**
 * @brief  Disable calibration.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_crg_disable_cali(void);


/**
 * @brief  Get cycles of DCXO16M or DCXO32M in every RC32K cycle.
 * @return uint16_t: Cycles of DCXO16M or DCXO32M in every RC32K cycle.
 */
extern uint16_t rom_hw_crg_get_32k_cycles_of_dcxo_hclk(void);




#ifdef __cplusplus
}
#endif

#endif /* __HW_CRG_H__ */


