/*************************************************************************************************************
 * @file    llc_ext_scan_state_machine.h
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
#ifndef LLC_EXT_SCAN_STATE_MACHINE_H
#define LLC_EXT_SCAN_STATE_MACHINE_H

void rom_llc_ext_scan_state_machine_init(stLlcExtScan_t* pstScan);

void rom_llc_ext_scan_state_machine_update_scan_req_pdu_AdvA(stLlcExtScan_t* pstScan, uint8_t AdvA[6], bool RxAdd);

void rom_llc_ext_scan_state_machine_update_scan_req_pdu_ScanA(stLlcExtScan_t* pstScan, uint8_t ScanA[6], bool TxAdd);

void rom_llc_ext_scan_state_machine_enable(stLlcExtScan_t* pstScan, bool bEnable);

void rom_llc_ext_scan_state_machine_schedule_next_scanning(stLlcExtScan_t* pstScan);

void rom_llc_ext_scan_state_machine_backoff_scan_result(stLlcExtScan_t* pstScan, bool bSuccess);

bool rom_llc_ext_scan_state_machine_backoff_is_scan_canceled(stLlcExtScan_t* pstScan);

#endif
