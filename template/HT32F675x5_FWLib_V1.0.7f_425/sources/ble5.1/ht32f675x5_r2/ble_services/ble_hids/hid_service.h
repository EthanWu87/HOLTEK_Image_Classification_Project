/*************************************************************************************************************
 * @file    hid_service.h
 * @version V1.0
 * @date    2021-09-04
 * @brief   Human Interface Device Service
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


#ifndef __HID_SERVICE_H__
#define __HID_SERVICE_H__

#define KBD_REPORT_NUM        8
#define CONSUMER_REPORT_NUM   8
#define AUDIO_SBC_REPORT_NUM  120

void hid_service_init(void);

bool hid_kbd_report(uint16_t u16ConnHandle, uint8_t *pReport, uint8_t u8DateLen);
bool hid_consumer_report(uint16_t u16ConnHandle, uint16_t *pReport, uint8_t u8DateLen);

#endif





