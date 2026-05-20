/*************************************************************************************************************
 * @file    llp_hw.h
 * @version V1.0
 * @date    2021-02-06
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
#ifndef LLP_HW_H
#define LLP_HW_H


#define LLP_HW_INT_MASK_ITV_TX_PRE  (1)
#define LLP_HW_INT_MASK_ITV_RX_PRE  (1<<1)
#define LLP_HW_INT_MASK_SLEEP_DONE  (1<<6)
#define LLP_HW_INT_MASK_TX_END      (1<<9)
#define LLP_HW_INT_MASK_CRC_OK      (1<<10)
#define LLP_HW_INT_MASK_CRC_ERR     (1<<11)
#define LLP_HW_INT_MASK_RX_LOST     (1<<12)
#define LLP_HW_INT_MASK_RX_END      (1<<14)
#define LLP_HW_INT_MASK_TX_FAILED   (1<<15)
#define LLP_HW_INT_MASK_SYNC        (1<<22)
#define LLP_HW_INT_MASK_WAKEUP      (1<<23)


typedef enum
{
    LLP_FRAGMENT_TYPE_DTM_TX = 0,
    LLP_FRAGMENT_TYPE_DTM_RX = 1,
    LLP_FRAGMENT_TYPE_ADV = 2,
    LLP_FRAGMENT_TYPE_SCAN = 3,
    LLP_FRAGMENT_TYPE_INIT = 4,
    LLP_FRAGMENT_TYPE_SLAVE = 5,
    LLP_FRAGMENT_TYPE_MASTER = 6,
    LLP_FRAGMENT_TYPE_EXT_ADV = 7,
    LLP_FRAGMENT_TYPE_EXT_SCAN = 8,
    LLP_FRAGMENT_TYPE_EXT_INIT = 9,
}
EN_LLP_FRAGMENT_TYPE_T;



typedef void (*llp_hw_interrupt_callback) (uint32_t u32IntState);
typedef uint8_t (*llp_rf_rx_calib_callback) ( bool is2mPhy, uint8_t u8RfChannel );
typedef void (*llp_rf_tx_calib_callback) ( bool is2mPhy);

void rom_llp_hw_init(llp_hw_interrupt_callback callback);

void rom_llp_set_rf_rx_calib_callback(llp_rf_rx_calib_callback callback);

void rom_llp_set_rf_tx_calib_callback(llp_rf_tx_calib_callback callback);

void rom_llp_hw_trig_schedule(void);

void rom_llp_hw_int_irq_handler(void);

void rom_llp_hw_sch_timer_enable (bool bEnable);

uint64_t rom_llp_hw_read_sch_timer_count(void);

void rom_llp_hw_set_idle_mode(void);

void rom_llp_hw_set_dtm_tx_mode(uint32_t u32TxIntervalUs);

void rom_llp_hw_set_dtm_rx_mode(void);

void rom_llp_hw_set_adv_mode(void);

void rom_llp_hw_set_scan_mode(void);

void rom_llp_hw_set_init_mode(void);

void rom_llp_hw_set_slave_mode(void);

void rom_llp_hw_set_master_mode(void);

EN_LLP_ERR_T rom_llp_hw_set_work_time_us(EN_LLP_FRAGMENT_TYPE_T enumFragmentType, uint32_t u32WorkTimeUs);

EN_LLP_ERR_T rom_llp_hw_set_slave_rx_window(uint32_t u32RxWindowUs, EN_LL_PHY_T enumRxPhy);

bool rom_llp_hw_is_work_time_reached(void);

EN_LLP_ERR_T rom_llp_hw_set_trx_param(bool bIsSecondaryChannel, uint8_t u8ChannelIdx, uint32_t u32AccessAddress, uint32_t u32CrcInit,
                               bool bWhiteningEn, EN_LL_PHY_T txPhy, EN_LL_PHY_T rxPhy );

EN_LLP_ERR_T rom_llp_hw_set_tx_pdu(stLlpPduPointer_t* pstLlpTxPduPtr);

EN_LLP_ERR_T rom_llp_hw_set_rx_pdu(stLlpPduPointer_t* pstLlpRxPduPtr, uint16_t u16RxPayloadSizeLimit);

void rom_llp_hw_get_rx_packet_start_end_time(uint64_t* pu64StartTime, uint64_t* pu64EndTime);

uint32_t rom_llp_hw_get_rx_header(void);

uint32_t rom_llp_hw_get_tx_header(void);

EN_LLP_ERR_T rom_llp_hw_set_ifs(EN_LL_PHY_T enumTxPhy, EN_LL_PHY_T enumRxPhy, uint16_t u16IfsUs, uint16_t u16IfsWindowUs);

EN_LLP_ERR_T rom_llp_hw_set_trt_mode_start_time(uint64_t u64StartTimeUs, EN_LL_PHY_T enumTxPhy);

EN_LLP_ERR_T rom_llp_hw_set_rtr_mode_start_time(uint64_t u64StartTimeUs, EN_LL_PHY_T enumRxPhy);

void rom_llp_hw_set_scan_init_anchor_window_us(uint32_t u32WindowUs);

void rom_llp_hw_cancel_tx(void);

EN_LL_PHY_T rom_llp_hw_get_peer_tx_phy(void);


bool rom_llp_hw_sleep_cycles_of_low_clk(uint32_t u32Cycles);

void rom_llp_hw_wakeup(void);

uint32_t rom_llp_hw_convert_us_to_cycles_of_low_clk(uint32_t u16Us);

uint32_t rom_llp_hw_convert_cycles_of_low_clk_to_us(uint32_t u32CyclesOfLowClk);

void rom_llp_hw_set_rssi_trim(uint8_t u8RssiAgc0, uint8_t u8RssiAgc1, uint8_t u8RssiAgc2);

uint32_t rom_llp_hw_read_rssi_reg(void);


#endif

