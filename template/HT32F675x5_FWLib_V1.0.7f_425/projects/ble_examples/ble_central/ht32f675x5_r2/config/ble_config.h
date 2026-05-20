/*************************************************************************************************************
 * @file    ble_config.h
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
#ifndef BLE_CONFIG_H
#define BLE_CONFIG_H

//================= User Configuration Start =================

// <<< Use Configuration Wizard in Context Menu >>>


// <o>Profile Buffer Size
// <i> buffer size of GATT profile
// <i> default: 1024
#define PROFILE_BUF_SIZE 1024


// <h>Role Configuration
// =======================

// <o>Max Legacy Advitiser <0-255>
// <i> defines maximum number of legacy advitisers [0~255]
// <i> default: 1
#define LEGACY_ADV_NUM 0

// <q>Legacy Scanner Switch
// <i>Enable/Disable Legacy Scanner
#define LEGACY_SCAN_ENABLE 1

// <q>Legacy Initiator Switch
// <i>Enable/Disable Legacy Initiator
#define LEGACY_INITIATOR_ENABLE 1

// <o>Max Extended Advitiser <0-255>
// <i> defines maximum number of extended advitisers [0~255]
// <i> default: 1
#define EXT_ADV_NUM 0

// <e>Extended Scanner Switch
// <i>Enable/Disable Extended Scanner
#define EXT_SCAN_ENABLE 0

// <o>Max Extended Advertisng Sets Num <1-255>
// <i> defines maximum number of extended advertising sets that Scanner can trace at the same time[1~255]
// <i> default: 6
#define EXT_SCAN_ADVERTISING_SET_NUM 2

// <o>Max Duplicate Report Num <1-255>
// <i> defines maximum number of advertising reports that duplicate list could hold[0~255]
// <i> default: 6
#define EXT_SCAN_DUPLICATE_REPORT_NUM 64

// </e>

// <e>Extended Initiator Switch
// <i>Enable/Disable Extended Initiator
#define EXT_INITIATOR_ENABLE 0

// <o>Max Extended Advertisng Sets Num <1-255>
// <i> defines maximum number of extended advertising sets that Initiator can trace at the same time[1~255]
// <i> default: 6
#define EXT_INITIATOR_ADVERTISING_SET_NUM 1

// </e>

// <o>Max Connection <0-255>
// <i> defines maximum number of connections [0~255]
// <i> default: 1
#define CONNECTION_ROLE_NUM 1

// =======================
// </h>


// <h>Filter Configuration
// =======================

// <o>White List Max Num <0-6>
// <i> defines maximum number of devices could be added to white list [0~6]
// <i> default: 6
#define WHITE_LIST_NUM 6

// <o>Resovling List Max Num <0-6>
// <i> defines maximum number of records could be added to resoving list [0~2]
// <i> default: 2
#define RESOLVING_LIST_NUM 2

// =======================
// </h>


// <h>Advertising Channel PDU Configuration
// =======================

// <o>Short Advertising Channel PDU Max Num <0-256>
// <i> defines maximum number of short advertising channel pdus [0~256]
// <i> default: 8
#define SHORT_ADV_CHANNEL_PDU_NUM 4

// <o>Short Advertising Channel PDU Payload Size <40-256>
// <i> defines short advertising channel pdu payload size [40~256, should be an integral multiple of 4]
// <i> default: 40
#define SHORT_ADV_CHANNEL_PDU_SIZE 40

// <o>Long Advertising Channel PDU Max Num <0-256>
// <i> defines maximum number of long advertising channel pdus [0~256]
// <i> default: 0
#define LONG_ADV_CHANNEL_PDU_NUM 4

// <o>Long Advertising Channel PDU Payload Size <40-256>
// <i> defines long advertising channel pdu payload size [40~256, should be an integral multiple of 4]
// <i> default: 256
#define LONG_ADV_CHANNEL_PDU_SIZE 256

// =======================
// </h>


// <h>Data Channel PDU Configuration
// =======================

// <o>Short Tx Data Channel PDU Max Num <0-256>
// <i> defines maximum number of short data channel pdus [0~256]
// <i> default: 8
#define SHORT_TX_DATA_CHANNEL_PDU_NUM 4

// <o>Short Tx Data Channel PDU Payload Size <40-256>
// <i> defines short data channel pdu payload size [40~256, should be an integral multiple of 4]
// <i> default: 40
#define SHORT_TX_DATA_CHANNEL_PDU_SIZE 40

// <o>Long Tx Data Channel PDU Max Num <0-256>
// <i> defines maximum number of long data channel pdus [0~256]
// <i> default: 8
#define LONG_TX_DATA_CHANNEL_PDU_NUM 2

// <o>Long Tx Data Channel PDU Payload Size <40-256>
// <i> defines long data channel pdu payload size [40~256, should be an integral multiple of 4]
// <i> default: 256
#define LONG_TX_DATA_CHANNEL_PDU_SIZE 256

// <o>Short Rx Data Channel PDU Max Num <0-256>
// <i> defines maximum number of short data channel pdus [0~256]
// <i> default: 8
#define SHORT_RX_DATA_CHANNEL_PDU_NUM 4

// <o>Short Rx Data Channel PDU Payload Size <40-256>
// <i> defines short data channel pdu payload size [40~256, should be an integral multiple of 4]
// <i> default: 40
#define SHORT_RX_DATA_CHANNEL_PDU_SIZE 40

// <o>Long Rx Data Channel PDU Max Num <0-256>
// <i> defines maximum number of long data channel pdus [0~256]
// <i> default: 8
#define LONG_RX_DATA_CHANNEL_PDU_NUM 2

// <o>Long Rx Data Channel PDU Payload Size <40-256>
// <i> defines long data channel pdu payload size [40~256, should be an integral multiple of 4]
// <i> default: 256
#define LONG_RX_DATA_CHANNEL_PDU_SIZE 256

// =======================
// </h>


// <h>Task Configuration
// =======================

// <o>Controller Task Stack Size
// <i> defines task stack size of BLE controller [should be an integral multiple of 8]
// <i> default: 1024
#define LLC_TASK_STACK_SIZE 2048


// <o>Host Task Stack Size
// <i> defines task stack size of BLE host [should be an integral multiple of 8]
// <i> default: 1024
#define HOST_TASK_STACK_SIZE 2048

// =======================
// </h>


// <h>Sleep Configuration
// =======================

// <o>Pre-wakeup Time(us)
// <i> defines the point of time that system wakeup before BLE event, affected by XO
// <i> default: 3500
#define PRE_WAKEUP_TIME_US 3500


// <o>Sleep Threshold Time(us)
// <i> defines the time period during which the system does not allow sleep before BLE event
// <i> default: 4000
#define SLEEP_THRESHOLD_TIME_US 4000

// =======================
// </h>


// <<< end of configuration section >>>

//================= User Configuration End =================

#define CLOCK_ACCURACY 500

#define LLC_TASK_MSG_COUNT   (64)

#define ACL_DATA_SIZE   (256)
#define ACL_DATA_NUM    (2)


#define HCI_COMMAND_NUM (2)
#define HCI_COMMAND_PARAMETERS_SIZE (256)

#endif
