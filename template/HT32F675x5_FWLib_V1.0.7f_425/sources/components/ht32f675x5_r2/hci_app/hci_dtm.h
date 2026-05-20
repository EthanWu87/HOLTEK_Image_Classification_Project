/*************************************************************************************************************
 * @file    hci_dtm.h
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


#ifndef __HCI_DTM_H__
#define __HCI_DTM_H__

/**
 * @brief  Hci dtm cmd handler
 * @param  u16Opcode: op code.
 * @param  pu8Buf: payload data buffer
 * @param  u16Len: payload data buffer length
 * @param  pstEvent: event struct point
 */
extern void hci_dtm_cmd_handler(uint16_t u16Opcode, uint8_t *pu8Buf, uint16_t u16Len, stEvent_t *pstEvent);

#endif /* __HCI_DTM_H__ */
