/*************************************************************************************************************
 * @file    llp.h
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
#ifndef LLP_H
#define LLP_H


typedef enum
{
    LLP_FRAGMENT_CONTINUE = 0,
    LLP_FRAGMENT_STOP,
}
EN_LLP_FRAGMENT_RET;


typedef EN_LLP_FRAGMENT_RET (*callback_llp_fragment_on_start)(void);
typedef void (*callback_llp_fragment_on_stop)(void);
typedef EN_LLP_FRAGMENT_RET (*callback_llp_fragment_on_interrupt) (uint32_t u32IntState);

typedef struct
{
    
    EN_LLP_FRAGMENT_TYPE_T enumFragmentType;
    callback_llp_fragment_on_start fragment_start_callback;
    callback_llp_fragment_on_stop fragment_stop_callback;
    callback_llp_fragment_on_interrupt fragment_interrupt_callback;
}
stLlpFragment_t;




//interfaces for llc
void rom_llp_trig_schedule (void);
void rom_llp_timer_enable (bool bEnable);
uint64_t rom_llp_timer_get_count(bool bHighAccuracy);
uint16_t rom_llp_get_clock_accuracy_ppm( void );

EN_LLP_ERR_T rom_llp_start_adv_fragment(stLlpAdvFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llp_start_scan_fragment(stLlpScanFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llp_start_init_fragment(stLlpInitFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llp_start_slave_fragment(stLlpSlaveFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llp_start_master_fragment(stLlpMasterFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llp_start_ext_adv_fragment(stLlpExtAdvFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llp_start_ext_scan_fragment(stLlpExtScanFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llp_start_ext_init_fragment(stLlpExtInitFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llp_stop_fragment(void);
EN_LLP_ERR_T rom_llp_update_tx_pdu(stLlpPduPointer_t* pstLlpTxPduPtr);
EN_LLP_ERR_T rom_llp_update_rx_pdu(stLlpPduPointer_t* pstLlpRxPduPtr, uint16_t u16RxPayloadSizeLimit);
int8_t rom_llp_get_rssi(uint32_t u32RssiRelatedValue);


//interfaces for APP
void rom_llp_init(void);
void rom_llp_set_clock_accuracy_ppm(uint16_t u16Ppm);
void rom_llp_set_schedule_report_callback(callback_on_schedule callback);
void rom_llp_set_fragment_start_report_callback(callback_on_llp_fragment_start callback);
void rom_llp_set_fragment_stop_report_callback(callback_on_llp_fragment_stop callback);
void rom_llp_set_tx_end_report_callback(callback_on_llp_tx_end callback);
void rom_llp_set_rx_end_report_callback(callback_on_llp_rx_end callback);
bool rom_llp_is_system_sleep_allowed(void);


//interfaces for llp
EN_LLP_STATE_CMD_T rom_llp_report_tx_end(stLlpTxEndReport_t* pstReport);
EN_LLP_STATE_CMD_T rom_llp_report_rx_end(stLlpRxEndReport_t* pstReport);
uint32_t rom_llp_get_rssi_related_value(void);

bool rom_llp_is_idle(void);

#endif
