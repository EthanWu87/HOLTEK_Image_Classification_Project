/*************************************************************************************************************
 * @file    hw_rf.h
 * @version V1.0
 * @date    2022-01-20
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


#ifndef __HW_RF_H__
#define __HW_RF_H__

#define BYTE_MSK (0xFF)
#define HALF_WORD_MSK (0xFFFF)
#define WORD_MSK (0xFFFFFFFF)

typedef enum
{
    EN_LDO_RF_850mV = 0,
    EN_LDO_RF_900mV = 1,
    EN_LDO_RF_950mV = 2,
    EN_LDO_RF_1000mV = 3,
    EN_LDO_RF_1050mV = 4,
    EN_LDO_RF_1100mV = 5,
    EN_LDO_RF_1150mV = 6,
    EN_LDO_RF_1200mV = 7,

} EN_LDO_RF_VOLT_T;

typedef enum
{
    T1_OV_40US = 0,
    T1_OV_60US = 1,
    T1_OV_90US = 2,
    T1_OV_120US = 3,
    T1_OV_150US = 4,
    T1_OV_180US = 5,
    T1_OV_210US = 6,
    T1_OV_255US = 7,

} EN_T1_OV_SET_T;

typedef enum
{
    T3_TIME_1US = 0,
    T3_TIME_2US = 1,
    T3_TIME_4US = 2,
    T3_TIME_8US = 3,

} EN_T3_TIME_SET_T;

typedef enum
{
    PA_VMD_MODE = 1,
    PA_DIFF_MODE = 2,
    PA_LP_MODE = 3,

} EN_PA_MODE_T;

typedef enum
{
    OTW_FREQ_SEL_32_96 = 0,
    OTW_FREQ_SEL_0_128 = 1,

} EN_OTW_SEL_T;

typedef enum
{
    RXIF_VCM_VOL_0V35 = 0,
    RXIF_VCM_VOL_0V40 = 1,
    RXIF_VCM_VOL_0V45 = 2,
    RXIF_VCM_VOL_0V50 = 3,

} EN_IF_VCM_CFG_T;

typedef enum
{
    I_MIXER_TIA_4UA = 0,
    I_MIXER_TIA_5UA = 1,
    I_MIXER_TIA_6UA = 2,
    I_MIXER_TIA_7UA = 3,

} EN_TIA_CUR_CFG_T;

typedef enum
{
    DCOC_IDLE_MODE = 0x00,
    DCOC_HOST_MODE = 0x01,
    DCOC_RX_MODE = 0x10,

} EN_DCOC_MODE_T;

typedef enum
{
    AGC_POWER_TH_1M = 0x40,
    AGC_POWER_TH_2M = 0x50,

} EN_PHY_PWR_TH_CFG_T;

typedef enum
{
    HOST_RX = 0,
    HOST_TX = 1,

} EN_HOST_TRX_MODE_T;

typedef enum
{
    DCOC_RESET = 0x1,
    FD_RESET = 0x2,
    RFMUX_RESET = 0x4,
    TXP_RESET = 0x8,
    MDM_RESET = 0x10,
    DTM_RESET = 0x20,
    LO16_RESET = 0x40,
    TRXS_RESET = 0x80,
    SDM_RESET = 0x100,

} EN_RF_SOFT_RESET_MODULE_T;

typedef enum
{
    DCOC_CALI_STA = 0,
    PAC_CALI_STA = 1,
    FD_CALI_STA = 2,

} EN_CALI_STATUS_T;

typedef enum
{
    RF_LLC_DATA_RATE_125K = 0,
    RF_LLC_DATA_RATE_500K = 1,
    RF_LLC_DATA_RATE_1M = 2,
    RF_LLC_DATA_RATE_2M = 3,

} EN_RF_LLC_DATA_RATE_T;

typedef enum
{
    MODE_LLC = 0,
    MODE_RADIO = 1,
    MODE_HOST1 = 2,
    MODE_HOST2 = 3,

} EN_RF_MODE_TRX_EN_T;

typedef enum
{
    HOST_TRX_DISABLE = 0,
    HOST_TX_EN = 1,
    HOST_RX_EN = 2,

} EN_RF_HOST_TRX_EN_T;

typedef enum
{
    TX_GAIN_0 = 0,
    TX_GAIN_1 = 1,
    TX_GAIN_2 = 2,
    TX_GAIN_3 = 3,
    TX_GAIN_4 = 4,
    TX_GAIN_5 = 5,

} EN_RF_TX_GAIN_SEL_T;

typedef struct
{
    uint8_t IF_RX_PGA_GAIN;
    uint8_t IF_RX_FD_OFFSET_ID;
    uint8_t RF_GM2_C;
    uint8_t RF_GM1_C;
    uint8_t RF_LNA_C;
    uint8_t RF_MIXER_IF_G;
    uint8_t RF_LNA_GAIN;

} stRF_AGC_CLASS_T;

typedef struct
{
    uint32_t Fvco;
    uint32_t VcoTune;
    uint32_t VcoLock;
    uint32_t VcoIb;
    uint32_t Modgain;
    uint32_t TxSel;

} stLO_STATUS_t;

typedef struct
{
    EN_RF_LLC_DATA_RATE_T txDataRate;
    EN_RF_LLC_DATA_RATE_T rxDataRate;

} stRF_TRX_DATA_RATE_T;




/**
 * @brief  Configuration rf TRx timing parameter.
 * @param  enT1OvSet: 0:40us; 1:60us; 2: 90us ; 3:120us; 4:150 ; 5:180us; 6: 210us; 7:255us @ref EN_T1OVSET_T.
 * @param  u8T2TimeUs: TX_EN_RF to ramp-up start time, unit:us, range: 0 ~ 255.
 * @param  enT3Time: Wait Tx ramp_up time 0:1us,1:2us;2:4us;3:8us @ref EN_T1OVSET_T.
 * @param  u8T4TimeUs: TX_EN to TX_EN_MDM time, unit:us, range: 0 ~ 63.
 * @param  u8T5TimeUs: TX_EN_MDM to TX_EN_RF time, unit:us, range: 0 ~ 15.
 * @param  u8T8TimeUs:RX mode, RX_EN_RF from bb to RX_EN_MDM delay time, unit:us, range: 0 ~ 255.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_trx_timing_config(EN_T1_OV_SET_T enT1OvSet, uint8_t u8T2TimeUs, EN_T3_TIME_SET_T enT3Time,
                                                uint8_t u8T4TimeUs, uint8_t u8T5TimeUs, uint8_t u8T8TimeUs);


/**
 * @brief  Configuration PA acw ramp up and down step parameter.
 * @param  u8Step: ramp step, range: 0 ~ 15.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_acw_ramp_step_config(uint8_t u8Step);


/**
 * @brief  Radio DTM mode,tx_en before tx_data time parameter configure.
 * @param  u16TimeUs: unit is us, range is 0 ~ 511.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_tx_en_before_tx_data_time_config(uint16_t u16TimeUs);


/**
 * @brief  Configuration Rx AGC0 parameter.
 * @param  stpAgcConfig: @ref stRF_AGC_CLASS_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_rx_gain0_config(stRF_AGC_CLASS_T *stpAgcConfig);


/**
 * @brief  Configuration Rx AGC1 parameter.
 * @param  stpAgcConfig: @ref stRF_AGC_CLASS_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_rx_gain1_config(stRF_AGC_CLASS_T *stpAgcConfig);


/**
 * @brief  Configuration Rx AGC2 parameter.
 * @param  stpAgcConfig: @ref stRF_AGC_CLASS_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_rx_gain2_config(stRF_AGC_CLASS_T *stpAgcConfig);


/**
 * @brief  Configuration PGA bandwidth parameter.
 * @param  u81mBw: 1M bandwidth configure parameter.
 * @param  u82mBw: 2M bandwidth configure parameter.
 */
extern void rom_hw_rf_rx_pga_bandwidth_config(uint8_t u81mBw, uint8_t u82mBw);


/**
 * @brief  Configuration PGA IF tuning parameter.
 * @param  u8Reg: IF tuning parameter, range: 0 ~ 15.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_pga_if_tuning_config(uint8_t u8Reg);


/**
 * @brief  Configuration PA second harmonic tuning parameter.
 * @param  u8PaH2Val: range is 0 ~ 15.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_tx_pa_h2_config(uint8_t u8PaH2Val);


/**
 * @brief  PA mode Configuration.
 * @param  enModeSel: @ref EN_PA_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_tx_pa_mode_config(EN_PA_MODE_T enModeSel);


/**
 * @brief  Internal RFIO matching capacitance for Tx mode.
 * @param  u8_10dBmCap1: Cap1 for RFIO in TX(10dBm) mode, 100fF/step.
 * @param  u8_0dBmCap1: Cap1 for RFIO in TX(0dBm) mode, 100fF/step.
 * @param  u8_0dBmCap2: Cap2 for RFIO in TX(0dBm) mode, 30fF/step.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_tx_rfio_cap_config(uint8_t u8_10dBmCap1, uint8_t u8_0dBmCap1, uint8_t u8_0dBmCap2);


/**
 * @brief  Internal RFIO matching capacitance for Rx mode.
 * @param  u8Cap1: Cap1 for RFIO in RX mode, 100fF/step.
 * @param  u8LowGainCap2: Cap2 for RFIO in RX(Low Gain) mode, 30fF/step.
 * @param  u8HighGainCap2: cap2 for RFIO in RX(High Gain) mode, 30fF/step.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_rx_rfio_cap_config(uint8_t u8Cap1, uint8_t u8LowGainCap2, uint8_t u8HighGainCap2);


/**
 * @brief  syn_loop registers Configuration.
 * @param  u32LdosReg: syn loop filter TRx parameter.
 * @param  u32SynCfg1Reg: syn vco/clock/otw parameter.
 * @param  u32SynCfg2Reg: syn current control.
 */
extern void rom_hw_rf_syn_loop_config(uint32_t u32LdosReg, uint32_t u32SynCfg1Reg, uint32_t u32SynCfg2Reg);


/**
 * @brief  VCO handle wait time Configuration.
 * @param  u8WaitLockTimeCnt: lock wait time config, 128*(2+wait) number clk_xo.
 * @param  u8WaitVcoCalTimeCnt: VCO calibration step config, 128*(1+wait) number clk_xo.
 * @param  u8WaitVcoStarupTimeCnt: vco startup wait time, 64*(2+wait) number clk_xo.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_vco_wait_config(uint8_t u8WaitLockTimeCnt, uint8_t u8WaitVcoCalTimeCnt, uint8_t u8WaitVcoStarupTimeCnt);


/**
 * @brief  Modgain scale Configuration.
 * @param  enOtwSel: modGain calibration freqency difference value select, @ref EN_OTW_SEL_T.
 * @param  u8ModgainCoeff: modGain calibration coefficient set, ( u8ModgainCoeff + 240 ) / 25.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_modgain_scale_config(EN_OTW_SEL_T enOtwSel, uint8_t u8ModgainCoeff);


/**
 * @brief  Radio reset control.
 * @param  u8RadioIdleResetEn: 1 - Radio reset enable, 0 - Radio reset disable.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_radio_reset_ctrl(uint8_t u8RadioIdleResetEn);


/**
 * @brief  VCM Configuration.
 * @param  enVcmSel: @ref EN_IF_VCM_CFG_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_vcm_config(EN_IF_VCM_CFG_T enVcmSel);


/**
 * @brief  RF Frequency Detector enable/disable control.
 * @param  u8EnSel: 1 - FD enable, 0 - FD disable.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_fd_enable(uint8_t u8EnSel);


/**
 * @brief  RF mixer Configuration.
 * @param  u8LoVolNum: 250mV + 50mV * u8LoVolNum.
 * @param  enTiaCurSel: 0:4uA, 1:5uA, 2:5uA, 3:7uA, @ref EN_TIA_CUR_CFG_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_mixer_config(uint8_t u8LoVolNum, EN_TIA_CUR_CFG_T enTiaCurSel);


/**
 * @brief  RF DC Offset Calibration parameter initial.
 * @return status: @ref EN_ERR_STA_T.
 */
extern void rom_hw_rf_dcoc_path_init(void);


/**
 * @brief  RF rx_en duration time Config for test.
 * @param  u16TimeUs, Internal RX_EN duration time, uint is us, each duration time have a posedge.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_test_rx_en_dur_time_config(uint16_t u16TimeUs);


/**
 * @brief  AGC RSSI threshold value Configuration.
 * @param  u16MaxThReg: max rssi threshold register value.
 * @param  u8MinThReg: min rssi threshold register value.
 * @param  u16ScaleValReg: rssi threshold scale register value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_agc_rssi_threshold_config(uint16_t u16MaxThReg, uint8_t u8MinThReg, uint16_t u16ScaleValReg);


/**
 * @brief  AGC Configuration.
 * @param  u8AgcWaitTimeNum: unit is us.
 * @param  u8AciWaitTimeNum: unit is 0.5us.
 * @param  u8IB_sel: inband power coefficient.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_agc_config(uint8_t u8AgcWaitTimeNum, uint8_t u8AciWaitTimeNum, uint8_t u8IB_sel);


/**
 * @brief  AGC power threshold Configuration.
 * @param  enPhySel @ref EN_PHY_PWR_TH_CFG_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_agc_power_threshold(EN_PHY_PWR_TH_CFG_T enPhySel);


/**
 * @brief  AGC DC Offset threshold value config.
 * @param  u8Val: register value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_agc_dc_offset_threshold(uint8_t u8Val);


/**
 * @brief  AGC hold time out configuration.
 * @param  u8TimeNum: unit is 16us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_agc_hold_time_out_config(uint8_t u8TimeNum);


/**
 * @brief  AGC RSSI Configuration.
 * @param  u8Agc0: unit is dB.
 * @param  u8Agc1: unit is dB.
 * @param  u8Agc2: unit is dB.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_agc_rssi_config(uint8_t u8Agc0, uint8_t u8Agc1, uint8_t u8Agc2);


/**
 * @brief  select modgain bypass.
 * @param  u8EnableSel, 1: modgain bypass enable, 0: modgain bypass disable.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_modgain_bypass_enable(uint8_t u8EnableSel);


/**
 * @brief  modgain calibration value configuration.
 * @param  u16caliVal: calibration value, range is 0 ~ 4095.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_modgain_cali_value_config(uint16_t u16caliVal);


/**
 * @brief  set local oscillator.
 * @param  u32FreqMHz: LO frequence, unit is MHz, range 2300 ~ 2500.
 * @param  u8TRxMode:  0 - Rx mode , 1 = Tx mode.
 * @return vco calibrtion value, uint32_t.
 */
extern uint32_t rom_hw_rf_set_lo(uint32_t u32FreqMHz, uint8_t u8TRxMode);


/**
 * @brief Clear LO state machine.
 */
extern void rom_hw_rf_clear_lo(void);


/**
 * @brief  Modgain calibration coefficient configuration.
 * @param  u32Kpara, modgain K coefficient, range: 0 ~ 255.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_modgain_k_coefficient_config(uint32_t u32Kpara);


/**
 * @brief  Get local oscillator status.
 * @param  pstLoStu: @ref stLO_STATUS_t.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_lo_status_get(stLO_STATUS_t *pstLoStu);


/**
 * @brief  RF host mode enable.
 * @param  u8EnSel: 1 - enable host mode, 0 - disable host mode.
 * @param  enTRxMode: host Tx/Rx mode select, @ref EN_HOST_TRX_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_host_mode_enable(uint8_t u8EnSel, EN_HOST_TRX_MODE_T enTRxMode);


/**
 * @brief  RF frequency detector clock enable.
 * @param  u8EnSel: 0 - disable FD clock, 1 - enable FD clock.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_fd_clock_enable(uint8_t u8EnSel);


/**
 * @brief  RF DCOC clock enable.
 * @param  u8EnSel: 0 - disable DCOC clock, 1 - enable DCOC clock.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_dcoc_clock_enable(uint8_t u8EnSel);


/**
 * @brief  RF modules soft reset.
 * @param  enModuleSel: @ref EN_RF_SOFT_RESET_MODULE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_module_soft_reset(EN_RF_SOFT_RESET_MODULE_T enModuleSel);


/**
 * @brief  FD tuning calibration control.
 * @param  u8EnSel: 0 - tuning disable, 1 - tuning enable.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_fd_tune_enable(uint8_t u8EnSel);


/**
 * @brief  Get calibration states.
 * @param  enStaSel, Select the statu to read  @ref EN_CALI_STATUS_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_get_cali_status(EN_CALI_STATUS_T enStaSel);


/**
 * @brief  Dynamic DCOC configuration.
 * @param  u8DynDly2Us: dynamic delay time, unit is 2us, range is 0 ~ 15(0 ~ 30us).
 * @param  u8DynRng: ADC data dynmaic range is 0 ~ 63.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_dynamic_dcoc_config(uint8_t u8DynDly2Us, uint8_t u8DynRng);


/**
 * @brief  Dynamic DCOC disable.
 * @param  u8disSel: 0 - tuning disable, 1 - tuning enable.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_dynamic_dcoc_disable(uint8_t u8disSel);


/**
 * @brief  DCOC TIA slope K configuration.
 * @param  u8Kpara: range is 0 ~ 15.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_dcoc_tia_k_set(uint8_t u8Kpara);


/**
 * @brief  DCOC calibration TIA search begin channel.
 * @param  u8ChVal: begin channel value, range is 0 ~ 39.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_dcoc_tia_search_begin_channel(uint8_t u8ChVal);


/**
 * @brief  DCOC calibration trigger.
 * @param  u8EnTrig: 1 - dcoc trig start, 0 - dcoc trig stop.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_dcoc_trigger(uint8_t u8EnTrig);


/**
 * @brief  Get LLC TRx data rate.
 * @param  stpDataRate: LLC data rate parameter point, @ref stRF_TRX_DATA_RATE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_get_llc_trx_data_rate(stRF_TRX_DATA_RATE_T *stpDataRate);


/**
 * @brief  Set LLC TRx data rate.
 * @param  stpDataRate: LLC data rate parameter point, @ref stRF_TRX_DATA_RATE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_set_llc_trx_data_rate(stRF_TRX_DATA_RATE_T *stpDataRate);


/**
 * @brief  Set LLC Control bit for dc cal.
 * @param  u32EnMask:
 *         0x01 - ltc_en
 *         0x02 - dtm_en
 *         0x04 - byp_en
 *         0x08 - close_whiten
 *         0x10 - trxs_host_mode
 *         0x20 - trxs_host_rx_en
 *         0x40 - trxs_host_tx_en
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_set_llc_control(uint32_t u32EnMask);


/**
 * @brief  Get LLC Control config for dc cal.
 * @param  pu32EnMask: LLC Control config parameter point.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_get_llc_control(uint32_t *pu32EnMask);


/**
 * @brief  Clear LLC Control bit for dc cal.
 * @param  u32EnMask:
 *         0x01 - ltc_en
 *         0x02 - dtm_en
 *         0x04 - byp_en
 *         0x08 - close_whiten
 *         0x10 - trxs_host_mode
 *         0x20 - trxs_host_rx_en
 *         0x40 - trxs_host_tx_en
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_clr_llc_control(uint32_t u32EnMask);


/**
 * @brief  TRx mode data enable select,
 * @param  enModeTrxSel: @ref EN_RF_MODE_TRX_EN_T
 *         0 - data from LLC mode
 *         1 - data from radio dtm mode
 *         2,3 - data from host mode
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_mode_trx_en_sel(EN_RF_MODE_TRX_EN_T enModeTrxSel);


/**
 * @brief  Get DC CAL offset between I/Q.
 * @return offset value, uint32_t.
 */
extern EN_ERR_STA_T rom_hw_rf_rx_dc_cal_get_offset_between_iq(uint32_t *u32Offset);


/**
 * @brief  host mode control.
 * @param  enHostTrxSel: @ref EN_RF_HOST_TRX_EN_T.
 *         0 - disable host mode
 *         1 - host tx mode enable
 *         2 - host rx mode enable
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_host_trx_en_sel(EN_RF_HOST_TRX_EN_T enHostTrxSel);


/**
 * @brief  Set bit, the rf module clock enable, The clock is turned on by the state machine.
 * @param  u32ClockEnMask, RF module clock gate bit mask.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_clock_en_set(uint32_t u32ClockEnMask);


/**
 * @brief  Clear bit, the rf module clock always on.
 * @param  u32ClockAlwaysOnMask, RF module clock gate bit mask.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_clock_en_clr(uint32_t u32ClockAlwaysOnMask);


/**
 * @brief  Select TX GAIN table.
 * @param  u8TxGainTableIndex: Select PA_GAIN from TX GAIN Table, range: 0 ~ 5 @ref EN_RF_TX_GAIN_SEL_T.
 *         PA_GAIN:
 *         0: select tx_gain_table0,table 0 is the min gain
 *         1: select tx_gain_table1
 *         2: select tx_gain_table2
 *         3: select tx_gain_table3
 *         4: select tx_gain_table4
 *         5: select tx_gain_table5, table5 is the max gain
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_tx_gain_sel(EN_RF_TX_GAIN_SEL_T u8TxGainTableIndex);


/**
 * @brief  Get GFSK Scl value, tx_table_gain = acw_mod * (gfsk_scl/16).
 * @return gfsk_scl: uint32_t.
 */
extern uint32_t rom_hw_rf_gfsk_scal_get(void);


/**
 * @brief  Tx gain configuration.
 * @param  enTxGainSel: gain table sel, range:0 ~ 5, @ref EN_RF_TX_GAIN_SEL_T.
 * @param  u32TxGainVal: table PA gain value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_tx_gain_table_config(EN_RF_TX_GAIN_SEL_T enTxGainSel, uint32_t u32TxGainVal);


/**
 * @brief  Get ACW from tx gain table.
 * @param  enTxGainSel: range is 0 ~ 5, @ref EN_RF_TX_GAIN_SEL_T.
 * @param  u8PaAcw: range is 0 ~ 255.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_get_tx_gain_acw(EN_RF_TX_GAIN_SEL_T enTxGainSel, uint8_t *pu8PaAcw);


/**
 * @brief  Tx gain single tone configuration.
 * @param  u8SingleToneEnSel: single tone config, 1: enable, u8TxPowerAcw is valid, 0: disable single tone mode.
 * @param  u8TxPowerAcw: PA ACW value, Control Tx power.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_tx_single_tone_config(uint8_t u8SingleToneEnSel, uint8_t u8TxPowerAcw);


/**
 * @brief  DC CAL offset configuration.
 * @param  u32Offset: dci and dcq offset value, Offset = (dci_offset << 8) + dcq_offset , range is 0 ~ 65535.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_rx_dc_cal_offset_config(uint32_t u32Offset);


/**
 * @brief  RF LDO configuration.
 * @param  enVolSel: RF LDO output voltage = 850mV+enVolSel*50mV, range is 0 ~ 7, @ref EN_LDO_RF_VOLT_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_rf_ldo_voltage(EN_LDO_RF_VOLT_T enSel);


#endif /* __HW_RF_H__ */

