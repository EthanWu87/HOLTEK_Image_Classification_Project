/*************************************************************************************************************
 * @file    llc_ext_scan_duplicate_filter.h
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
#ifndef LLC_EXT_SCAN_DUPLICATE_FILTER_H
#define LLC_EXT_SCAN_DUPLICATE_FILTER_H

typedef struct
{
    uint64_t u64VersionNumer;
    
    EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T enumAddressType;
    uint8_t pu8Address[6];
    uint8_t u8SID;
    
    bool bMemUsed;
} __attribute__((aligned(8)))
stLlcExtScanDuplicateFilterReport_t;

void rom_llc_ext_scan_duplicate_filter_init(stLlcExtScanDuplicateFilterReport_t* pstLlcExtScanDuplicateFilterReportMem, uint8_t u8LlcExtScanDuplicateFilterReportNum);

void rom_llc_ext_scan_duplicate_filter_reset(void);

void rom_llc_ext_scan_duplicate_filter_add_report(EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T enumAddressType, uint8_t pu8Address[6], uint8_t u8SID);

bool rom_llc_ext_scan_duplicate_filter_is_report_duplicated(EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T enumAddressType, uint8_t pu8Address[6], uint8_t u8SID);

#endif
