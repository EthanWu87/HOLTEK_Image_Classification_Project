/*************************************************************************************************************
 * @file    hci_cmd.h
 * @version V1.0
 * @date    2022-07-11
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


#ifndef __HCI_CMD_H__
#define __HCI_CMD_H__

/*
 *  Opcode Group Fields for the HCI Command Groups
 */
#define LINK_CONTROL_OGF                 0x01
#define LINK_POLICY_OGF                  0x02
#define HOST_CONTROL_OGF                 0x03
#define LOCAL_INFO_OGF                   0x04
#define LOCAL_STATUS_OGF                 0x05
#define TEST_COMMANDS_OGF                0x06
#define LE_CONTROLLER_OGF                0x08
#define EXTENDED_OGF                     0x3F

/***********************************************
 * Host Controller and Baseband command opcode
 *  - Opcode group subfield = 0x03
 ***********************************************/

#define HC_G                             (HOST_CONTROL_OGF << 10)

#define HCI_RESET                        (0x0003 + HC_G) // 0x0c03

/***********************************************
 * LE Controller commands opcode
 *  - Opcode group subfield = 0x08
 ***********************************************/
#define LE_G                             (LE_CONTROLLER_OGF << 10)

#define HCI_LE_RECEIVER_TEST             (0x001D + LE_G) // 0x201d
#define HCI_LE_TRANSMITTER_TEST          (0x001E + LE_G) // 0x201e
#define HCI_LE_TEST_END                  (0x001F + LE_G) // 0x201f
#define HCI_LE_ENHANCED_RECEIVER_TEST    (0x0033 + LE_G) // 0x2033
#define HCI_LE_ENHANCED_TRANSMITTER_TEST (0x0034 + LE_G) // 0x2034
#define HCI_LE_SINGLE_TONE_TEST          (0x0035 + LE_G) // 0x2035

#define HCI_LE_TX_USER_DATA_IN_DTM       (0x0380 + LE_G) // 0x2380
#define HCI_LE_RX_USER_DATA_IN_DTM       (0x0381 + LE_G) // 0x2381

/**
 ***********************************************
 * HCI Status parameters command opcode
 *  - Opcode group subfield = 0x3F
 ***********************************************/
#define E_G                              (EXTENDED_OGF << 10)

// scan
#define HCI_WRITE_SCAN_PARAMS_EXT        (0x0000 + E_G)
#define HCI_WRITE_SCAN_ENABLE_EXT        (0x0001 + E_G)
#define HCI_RESET_EXT                    (0x0002 + E_G)
#define HCI_READ_BUFF_NUM                (0x0003 + E_G)
#define HCI_SET_DEV_NAME_ADDR            (0x0004 + E_G)

// adv
#define HCI_SET_ADV_PARAM_EXT            (0x0010 + E_G)
#define HCI_SET_ADV_STOP_EXT             (0x0011 + E_G)
#define HCI_SET_ADV_DATA                 (0x0012 + E_G)
#define HCI_SET_SCAN_RSP                 (0x0013 + E_G)
#define HCI_SET_ADV_START                (0x0014 + E_G)
#define HCI_SET_ADV_ADDR                 (0x0015 + E_G)
#define HCI_SET_GAP_DEVICE_NAME          (0x0017 + E_G)

// CONNECTION
#define HCI_CREATE_CONNCT_EXT            (0x0030 + E_G)
#define HCI_DISCONNECT_EXT               (0x0031 + E_G)
#define HCI_CONNCT_CANCEL_EXT            (0x0032 + E_G)
#define HCI_CONNCT_UPDATE_EXT            (0x0033 + E_G)
#define HCI_CONNCT_GET_MTU_EXT           (0x0034 + E_G)
#define HCI_PHY_UPDATE                   (0x0035 + E_G)

// SM
#define HCI_SM_PARA_SET                  (0x0040 + E_G)
#define HCI_SM_SECURITY_REQUEST          (0x0041 + E_G)
#define HCI_SM_SEND_PASSKEY              (0x0042 + E_G)

// TRX
#define HCI_DATA_SEND                    (0x00B0 + E_G)
#define HCI_GET_BLE_STATUS               (0x00C5 + E_G)
#define HCI_BOND_DEVICE_INIT             (0x00C8 + E_G)

#define HCI_HT32_READ_REG                 (0x00c2 + E_G)
#define HCI_HT32_WRITE_REG                (0x00c3 + E_G)

#define HCI_EXT_SM_TEST                  (0x00CC + E_G) // 0xFCCC

/**<USER CMD*/
#define HCI_CMD_USER_DEFINE              (0x00F0 + E_G)
#define HCI_TX_POWER_TEST                (0xBABA0000)

/**<CENTRAL*/
#define HCI_CENTRAL_EXCHG_MTU            (0x0050 + E_G)
#define HCI_CENTRAL_DISCOVERY_ALL        (0x0051 + E_G)
#define HCI_CENTRAL_CONN_BY_NAME         (0x0052 + E_G)
#define HCI_CENTRAL_CONN_BY_ADR          (0x0053 + E_G)

#define HCI_CENTRAL_READ_CHAR_BY_HANDLE  (0x0060 + E_G)
#define HCI_CENTRAL_READ_CHAR_BY_UUID    (0x0061 + E_G)
#define HCI_CENTRAL_READ_LONG_CHAR       (0x0062 + E_G)

#define HCI_CENTRAL_WRITE_CHAR           (0x0063 + E_G)
#define HCI_CENTRAL_WRITE_CHAR_NORESP    (0x0064 + E_G)
#define HCI_CENTRAL_WRITE_LONG_CHAR      (0x0065 + E_G)

#define HCI_CENTRAL_AUTOTEST_D2H         (0x0070 + E_G)
#define HCI_CENTRAL_AUTOTEST_H2D         (0x0071 + E_G)

/**
 * @brief  Hci cmd dispatch
 * @param  u16Opcode: op code.
 * @param  pu8Buf: payload data buffer
 * @param  u16PayloadLen: payload data buffer length
 * @param  pstEvent: event struct point
 */
extern void hci_cmd_dispatch(uint16_t u16Opcode, uint8_t *pu8Buf, uint16_t u16PayloadLen, stEvent_t *pstEvent);

#endif /* __HCI_CMD_H__ */
