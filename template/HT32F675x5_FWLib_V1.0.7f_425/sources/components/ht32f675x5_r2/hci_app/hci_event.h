/*************************************************************************************************************
 * @file    hci_event.h
 * @version V1.0
 * @date    2023-07-11
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


#ifndef __HCI_EVENT_H__
#define __HCI_EVENT_H__

// event code
#define CMD_CMPLT_EVT_CODE              (0x0E)

#define HT32_CMD_STATUS_CODE            (0x01)
#define HT32_CNNCT_CMPLT_CODE           (0x02)
#define HT32_DISCNNCT_CMPLT_CODE        (0x03)
#define HT32_ADV_RPT_RESLT_CODE         (0x04)
#define HT32_ENCRYPTION_STATUS_CHG_CODE (0x05)
#define HT32_CNNCT_UPDATE_CODE          (0x06)
#define HT32_MTU_RPT_CODE               (0x08)
#define HT32_NUM_OF_CMPLT_PKTS_CODE     (0x09)
#define HT32_DATA_RPT_CODE              (0x0A)
#define HT32_READY_TO_WORK              (0x0B)
#define HT32_PASSKEY_INPUT_IND          (0x0C)
#define HT32_PASSKEY_DISPLAY_IND        (0x0D)
#define HT32_PASSKEY_DISPLAY_CANCEL_IND (0x0E)
#define HT32_KEYPRESS_NOTIFICATION      (0x0F)
#define HT32_PERI_TIMER_NOTIFY          (0x10)
#define HT32_BOND_DEVICE_RPT            (0x20)
#define HT32_BOND_DEVICE_CMPLT          (0x21)
#define HT32_SPECIFIED_EVENT_CODE       (0x3F)
#define HT32_UNKNOW_PACKET              (0xFF)

/**
 * @brief  Hci app event packet
 * @param  pstEventBuf: Data point which hci event buffer
 * @param  pstEvent: Data point which hci event
 */
extern void hci_event_generate(stHciBuf_t *pstEventBuf, stEvent_t *pstEvent);

#endif /* __HCI_EVENT_H__ */
