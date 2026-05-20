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


#ifndef __USBD_CDC_H__
#define __USBD_CDC_H__

/**
 * @brief  DEFINE
 */
#define HID_GET_REPORT   0x01
#define HID_GET_IDLE     0x02
#define HID_GET_PROTOCOL 0x03
#define HID_SET_REPORT   0x09
#define HID_SET_IDLE     0x0A
#define HID_SET_PROTOCOL 0x0B


/**
 * @brief  USB device endpiont reset.
 */
extern void usb_device_reset_endpoint(void);

/**
 * @brief  USB device hid class request.
 * @param  pu8Setup: Pointer to setup buffer.
 */
extern void usb_device_hid_class_request(uint8_t *pu8Setup);


/**
 * @brief  USB device hid recive data.
 * @param  pu8Buf: Pointer to save received data.
 * @param  pu32Len: Pointer to received data length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE usb_device_hid_data_recive ( uint8_t *pu8ReceiveBuf, uint32_t *pu32Len );


/**
 * @brief  USB device hid send keyboard data.
 * @param  pu8Buf: Pointer to send buffer.
 * @param  u32Len: Send data buffer length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE usb_device_hid_keyboard_data_report ( uint8_t *pu8SendBuf, uint32_t u32Len );

/**
 * @brief  USB device hid send consumer data.
 * @param  pu8Buf: Pointer to send buffer.
 * @param  u32Len: Send data buffer length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE usb_device_hid_consumer_data_report ( uint8_t *pu8SendBuf, uint32_t u32Len );

#endif /*__USBD_HID_H__*/
