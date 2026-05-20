/*************************************************************************************************************
 * @file    hal_rf.h
 * @version V1.0
 * @date    2021-02-18
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


#ifndef __HAL_RF_H__
#define __HAL_RF_H__


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define MAX_CHANNEL_NUM         ( 40 )


//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum
{
    TX_NEG20_DBM    = 0,
    TX_NEG5_DBM     = 1,
    TX_0_DBM        = 2,
    TX_5_DBM        = 3,
    TX_7_DBM        = 4,
    TX_10_DBM       = 5,
    TX_CUSTOM_POWER = 6,

} EN_TX_POWER_T;

typedef enum
{
    DC_CAL_DATA_RATE_1M_S2_S8 = 0,
    DC_CAL_DATA_RATE_2M       = 1,

} EN_DC_CAL_DATA_RATE_T;


//=====================================================================================================================
// TYPEDEF CALLBACK
//=====================================================================================================================
typedef void (*callback_rf_cali_init)(void);
typedef void (*callback_rf_tx_cali)(void);
typedef EN_ERR_STA_T (*callback_rf_rx_cali)(void);
typedef bool (*callback_rf_rx_dc_cal)(uint32_t* pu32);


extern void rom_hal_rf_cali_init_callback_register(callback_rf_cali_init callback);
extern void rom_hal_rf_tx_cali_callback_register(callback_rf_tx_cali callback);
extern void rom_hal_rf_rx_cali_callback_register(callback_rf_rx_cali callback);
extern void rom_hal_rf_rx_dc_cal_callback_register(callback_rf_rx_dc_cal callback);


extern uint8_t const g_pu8TxGainDefaultTable[6];

/**
 * @brief  RF function initialization.
 */
extern void rom_hal_rf_init(void);


/**
 * @brief  RF calibration parameter initialization.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_rf_cali_init(void);


/**
 * @brief  RF calibration correction parameter update.
 * @param  isTxPhy2m: true - 2M PHY, false - 1M/S2/S8.
 */
extern void rom_hal_rf_set_modgain_cail_correction(bool isTxPhy2m);


/**
 * @brief  Start single-tone Tx transmitting.
 * @param  enTxPoweSel: Tx power select, @ref EN_TX_POWER_T.
 * @param  u8PaAcw: Tx gain PA ACW configration, range is 0 ~ 255.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_rf_set_tx_gain_acw(EN_TX_POWER_T enTxPowerdBm, uint8_t u8PaAcw);


/**
 * @brief  modgain calibration.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_rf_tx_cali(void);


/**
 * @brief  FD calibration and DCOC calibration.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_rf_rx_cali(void);


/**
 * @brief  Rx dc cal handle.
 * @param  is2mPhy: true - 2M PHY, false - 1M/S2/S8.
 * @return u32Offset, DC CAL Offset value.
 */
extern uint32_t rom_hal_rf_rx_dc_cal(bool is2mPhy);


/**
 * @brief  Rx 1M/2M datarate dc cal sweep all channel.
 */
extern void rom_hal_rf_rx_dc_cal_sweep(void);


/**
 * @brief Update dc cal offset value with channel.
 * @param is2mPhy: true - 2M PHY, false - 1M/S2/S8.
 * @param u8Channel: Rx channel num, range is 0~39.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_rf_rx_dc_cal_offset_update(bool is2mPhy, uint8_t u8Channel);


/**
 * @brief RF Tx power amplifier control word table parameter initialization.
 * @param pu8Tab: table point.
 */
extern void rom_hal_rf_tx_power_table_init(uint8_t *pu8Tab);


/**
 * @brief  Get current tx PA gain.
 * @return PA Gain.
 */
extern uint8_t rom_hal_rf_get_tx_gain(void);


/**
 * @brief  RF Tx power configuration.
 * @param  enTxPowerdBm: power parameter @ref EN_TX_POWER_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_rf_tx_power_set(EN_TX_POWER_T enTxPower);


/**
 * @brief  Start single-tone Tx transmitting.
 * @param  u8FreqChannelNum: channel num, range: 0~39, Frequency(MHz) = u8FreqChannelNum*2 + 2402.
 * @param  enTxPoweSel: Tx power select, @ref EN_TX_POWER_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_rf_single_tone_start(uint8_t u8FreqChannelNum, EN_TX_POWER_T enTxPoweSel);


/**
 * @brief Stop single-tone Tx transmitting.
 */
extern void rom_hal_rf_single_tone_stop(void);


#endif /* __HAL_RF_H__ */


