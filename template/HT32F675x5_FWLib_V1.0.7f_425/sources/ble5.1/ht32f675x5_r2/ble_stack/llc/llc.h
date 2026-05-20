/*************************************************************************************************************
 * @file    llc.h
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
#ifndef LLC_H
#define LLC_H


typedef void (*llc_task_msg_callback) (void* pParam);

typedef struct
{
    llc_task_msg_callback msgCallback;
    void* pParam;
}
stLlcTaskMsg_t;

typedef bool (*llc_send_msg_to_llc_task_callback)(stLlcTaskMsg_t stLlcTaskMsg);

//interfaces for APP
void rom_llc_init(void);

void rom_llc_set_send_msg_to_llc_task_callback(llc_send_msg_to_llc_task_callback callback);
void rom_llc_on_llc_task_received_msg(stLlcTaskMsg_t stLlcTaskMsg);

void rom_llc_set_timer_enable_callback(api_llp_timer_enable callback);
void rom_llc_set_timer_get_count_callback(api_llp_timer_get_count callback);
void rom_llc_set_llp_clock_accuracy_callback(api_llp_get_clock_accuracy_ppm callback);
void rom_llc_set_start_adv_fragment_callback(api_llp_start_adv_fragment callback);
void rom_llc_set_start_scan_fragment_callback(api_llp_start_scan_fragment callback);
void rom_llc_set_start_init_fragment_callback(api_llp_start_init_fragment callback);
void rom_llc_set_start_slave_fragment_callback(api_llp_start_slave_fragment callback);
void rom_llc_set_start_master_fragment_callback(api_llp_start_master_fragment callback);
void rom_llc_set_stop_fragment_callback(api_llp_stop_fragment callback);
void rom_llc_set_update_tx_pdu_callback(api_llp_update_tx_pdu callback);
void rom_llc_set_update_rx_pdu_callback(api_llp_update_rx_pdu callback);
void rom_llc_set_trig_schedule_report_callback(api_llp_trig_schedule_report callback);
void rom_llc_set_get_rssi_callback(api_llp_get_rssi callback);

//interfaces for llc
bool rom_llc_send_msg_to_llc_task(llc_task_msg_callback callback, void* pParam);
void rom_llc_timer_enable(bool bEnable);
uint64_t rom_llc_timer_get_count(bool bHighAccuracy);
uint16_t rom_llc_get_llp_clock_accuracy_ppm(void);
EN_LLP_ERR_T rom_llc_start_adv_fragment(stLlpAdvFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llc_start_scan_fragment(stLlpScanFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llc_start_init_fragment(stLlpInitFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llc_start_slave_fragment(stLlpSlaveFragmentParam_t *pstParam);
EN_LLP_ERR_T rom_llc_start_master_fragment(stLlpMasterFragmentParam_t *pstParam);

//considering llp is asynchronous with llc, this API must be used carefully
//otherwise you may stop a fragment which is not your expected one
EN_LLP_ERR_T rom_llc_stop_fragment(void);
EN_LLP_ERR_T rom_llc_update_tx_pdu(stLlpPduPointer_t* pstLlpTxPduPtr);
EN_LLP_ERR_T rom_llc_update_rx_pdu(stLlpPduPointer_t* pstLlpRxPduPtr, uint16_t u16RxPayloadSizeLimit);
void rom_llc_trig_schedule(void);
int8_t rom_llc_get_rssi(uint32_t u32RssiRelatedValue);


//interfaces for llp
void rom_llc_on_schedule(void);
void rom_llc_on_llp_fragment_start(void);
void rom_llc_on_llp_fragment_stop(void);
EN_LLP_STATE_CMD_T rom_llc_on_llp_tx_end(stLlpTxEndReport_t* pstReport);
EN_LLP_STATE_CMD_T rom_llc_on_llp_rx_end(stLlpRxEndReport_t* pstReport);


#endif
