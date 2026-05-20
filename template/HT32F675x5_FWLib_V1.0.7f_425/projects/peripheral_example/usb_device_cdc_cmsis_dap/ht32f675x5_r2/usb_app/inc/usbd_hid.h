/*************************************************************************************************************
 * @file    usbd_hid.h
 * @version V1.0
 * @date    2022-12-20
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


#ifndef __USBD_HID_H__
#define __USBD_HID_H__

/**
 * @brief  USB device endpiont reset.
 */
extern void usb_device_reset_endpoint(void);

/**
 * @brief  USB device hid recive data.
 * @param  pu8Buf: Pointer to save received data.
 * @param  pu32Len: Pointer to received data length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE usb_device_recive_hid_data(uint8_t *pu8Buf, uint32_t *pu32Len);

/**
 * @brief  USB device hid send data.
 * @param  pu8Buf: Pointer to send buffer.
 * @param  u32Len: Send data buffer length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE usb_device_send_hid_data(uint8_t *pu8Buf, uint32_t u32Len);

#endif /*__USBD_HID_H__*/
