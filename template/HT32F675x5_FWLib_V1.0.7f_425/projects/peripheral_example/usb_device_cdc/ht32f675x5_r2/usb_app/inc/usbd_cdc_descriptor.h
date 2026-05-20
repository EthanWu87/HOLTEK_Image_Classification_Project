/*************************************************************************************************************
 * @file    usbd_cdc_descriptor.h
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


#ifndef __USBD_CDC_DESCRIPTOR_H__
#define __USBD_CDC_DESCRIPTOR_H__

/**
 * @brief  DEFINE
 */
// Endpoint transfer packet size
#define CDC_USB_DATA_PACKET_SIZE            64
#define CDC_USB_CTRL_PACKET_SIZE            16

// CDC interface serial number define
#define CDC_CTRL_INTERFACE_NUM              0
#define CDC_DATA_INTERFACE_NUM              1

/* USB String Descriptor - Manufacturer */
#define USB_STRING_DESCRIPTOR_MANUFACTURER  "Holtek"

/* USB String Descriptor - Product */
#define USB_STRING_DESCRIPTOR_PRODUCT       "Holtek CDC"

/* USB String Descriptor - Serial Number */
#define USB_STRING_DESCRIPTOR_SERIAL_NUMBER "20221221"

/**
 * @brief  GLOBAL VARIABLE
 */
/* USB Device Descriptor */
extern const uint8_t g_au8UsbDeviceDescriptor[];

/* USB Configuration Descriptor */
extern const uint8_t g_au8UsbConfigurationDescriptor[];

/* USB String Descriptor - LangID */
extern const uint8_t g_au8UsbStringDescriptorLangID[];

/* USB Device Qualifier Descriptor */
extern const uint8_t g_au8DeviceQualifierDescriptor[];

#endif /*__USBD_CDC_DESCRIPTOR_H__*/
