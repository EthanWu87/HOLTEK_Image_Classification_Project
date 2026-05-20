/*************************************************************************************************************
 * @file    llc_ext_scan_primary_scanning.h
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
#ifndef LLC_EXT_SCAN_PRIMARY_SCANNING_H
#define LLC_EXT_SCAN_PRIMARY_SCANNING_H


#define LLC_EXT_SCAN_PRIMARY_SCANNING_MIN_WINDOW_US (2500)


#define LLC_EXT_SCAN_PRIMARY_SCANNING_WINDOW_ADJUSTABLE (1)


void rom_llc_ext_scan_primary_scanning_clear_phy(stLlcExtScan_t* pstScan);

uint8_t rom_llc_ext_scan_primary_scanning_get_phy_num(stLlcExtScan_t* pstScan);

bool rom_llc_ext_scan_primary_scanning_add_phy(stLlcExtScan_t* pstScan, EN_LL_PHY_T enumPhy, uint8_t Scan_Type, uint16_t Scan_Interval, uint16_t Scan_Window, uint8_t Channel_Map);

void rom_llc_ext_scan_primary_scanning_on_enable(stLlcExtScan_t* pstScan);

void rom_llc_ext_scan_primary_scanning_on_disable(stLlcExtScan_t* pstScan);

void rom_llc_ext_scan_primary_scanning_prepare_timing(stLlcExtScan_t* pstScan, bool bStart);

bool rom_llc_ext_scan_primary_scanning_get_timing(stLlcExtScan_t* pstScan, stLlcExtScanTiming_t* pstTiming);

void rom_llc_ext_scan_primary_scanning_on_scheduled(stLlcExtScan_t* pstScan);

uint32_t rom_llc_ext_scan_primary_scanning_on_event_blocked (stLlcExtScan_t* pstScan);

EN_LLP_ERR_T rom_llc_ext_scan_primary_scanning_config_llp(stLlcExtScan_t* pstScan, uint32_t u32MaxWorkWindowTimeUs);

void rom_llc_ext_scan_primary_scanning_on_llp_fragment_start(stLlcExtScan_t* pstScan);

bool rom_llc_ext_scan_primary_scanning_on_llp_fragment_stop(stLlcExtScan_t* pstScan);

EN_LLP_STATE_CMD_T rom_llc_ext_scan_primary_scanning_on_llp_tx_end(stLlcExtScan_t* pstScan, stLlpTxEndReport_t *pstReport);

EN_LLP_STATE_CMD_T rom_llc_ext_scan_primary_scanning_on_llp_rx_end(stLlcExtScan_t* pstScan, stLlpRxEndReport_t *pstReport);

#endif
