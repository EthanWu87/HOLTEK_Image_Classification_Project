/*************************************************************************************************************
 * @file    usbd_hid_descriptor.c
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


#include <stdint.h>

#include "utility.h"

#include "usbd_standard_request.h"
#include "usbd_hid_descriptor.h"

/**
 * @brief  GLOBAL VARIABLE.
 */
/* USB Device Descriptor */
const uint8_t g_au8UsbDeviceDescriptor[] = {
    0x12, /* bLength */
    0x01, /* bDescriptorType */
    0x10,
    0x01, /* bcdUSB */
    0x00, /* bDeviceClass */
    0x00, /* bDeviceSubClass */
    0x00, /* bDeviceProtocol */
    0x40, /* bMaxPacketSize0 */
    LO_UINT16(HOLTEK_VID),
    HI_UINT16(HOLTEK_VID), /* idVendor */
    LO_UINT16(HID_KEYBOARD_PID),
    HI_UINT16(HID_KEYBOARD_PID), /* idProduct */
    0x00,
    0x01, /* bcdDevice */
    0x01, /* iManufacturer */
    0x02, /* iProduct */
    0x03, /* iSerialNumber */
    0x01, /* bNumConfigurations */
};

/* USB Configuration Descriptor */
const uint8_t g_au8UsbConfigurationDescriptor[] = {
    /* Configuration Descriptor */
    0x09,                              /* bLength: Configuration Descriptor size */
    USB_DESCRIPTOR_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
    9 + 9 + 9 + 7 + 7,                 /* wTotalLength:no of returned bytes */
    0x00, 0x01,                        /* bNumInterfaces:1 interface */
    0x01,                              /* bConfigurationValue: Configuration value */
    0x04,                              /* iConfiguration: Index of string descriptor describing the configuration */
    0x80,                              /* bmAttributes: usb Vbus powered */
    0x32,                              /* MaxPower: x*2mA */

    /* Interface Descriptor */
    0x09,                          /* bLength */
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType */
    HID_DATA_INTERFACE_NUM,        /* bInterfaceNumber */
    0x00,                          /* bAlternateSetting */
    0x02,                          /* bEndpoints: 1 endpoint for input, 1 endpoint for output */
    0x03,                          /* bInterfaceClass: HID class */
    0x00,                          /* bInterfaceSubClass: 0x01 support BIOS boot */
    0x00,                          /* bInterfaceProtocol: keyboard boot 0x01, mouse boot 0x02 */
    0x05,                          /* iConfiguration */

    /* Device Class Descriptor */
    0x09,              /* bLength */
    USB_DT_HID,        /* bDescriptorType:HID 0x21 */
    0x00, 0x01,        /* bcdHID */
    0x00,              /* bCountyCode: United States 0x21 */
    0x01,              /* bNumDescriptors: 1 HID report */
    USB_DT_HID_REPORT, /* bDescriptorType */
    LO_UINT16(sizeof(g_au8HidDataReportDescriptor)), HI_UINT16(sizeof(g_au8HidDataReportDescriptor)),
    /* bDescriptorLength */ // 21 00

    /* Endpoint Descriptor */
    0x07,                           /* bLength: Endpoint Descriptor size */
    USB_DESCRIPTOR_TYPE_ENDPOINT,   /* bDescriptorType: Endpoint */
    EP_ADDR_HID_INT_OUT,            /* bEndpointAddress */
    EP_ATTR_HID_OUT,                /* bmAttributes: Interrupt */
    HID_USB_DATA_PACKET_SIZE, 0x00, /* wMaxPacketSize */
    0x01,                           /* bInterval: 1 ms*/

    0x07,                           /* bLength: Endpoint Descriptor size */
    USB_DESCRIPTOR_TYPE_ENDPOINT,   /* bDescriptorType: Endpoint */
    EP_ADDR_HID_INT_IN,             /* bEndpointAddress */
    EP_ATTR_HID_IN,                 /* bmAttributes: Interrupt */
    HID_USB_DATA_PACKET_SIZE, 0x00, /* wMaxPacketSize */
    0x01,                           /* bInterval: 1 ms*/
};

/* USB String Descriptor - LangID */
const uint8_t g_au8UsbStringDescriptorLangID[] = {
    0x04,
    0x03,
    0x09,
    0x04,
};

/* USB Device Qualifier Descriptor */
const uint8_t g_au8DeviceQualifierDescriptor[] = {
    10, 6, 0x10, 0x01, 0, 0, 0, 64, 1, 0,
};

/** Usb HID report descriptor. */
uint8_t g_au8HidDataReportDescriptor[32] = {
    /* USER CODE BEGIN 0 */
    0x06, 0x00, 0xFF, /*  Usage Page (vendor defined) ($FF00) global */
    0x09, 0x01,       /*  Usage (vendor defined) ($01) local */
    0xA1, 0x01,       /*  Collection (Application) */
    0x15, 0x00,       /*   LOGICAL_MINIMUM (0) */
    0x25, 0xFF,       /*   LOGICAL_MAXIMUM (255) */
    0x75, 0x08,       /*   REPORT_SIZE (8bit) */

    // Input Report
    0x95, 64,   /*   Report Length (64 REPORT_SIZE) */
    0x09, 0x01, /*   USAGE (Vendor Usage 1) */
    0x81, 0x02, /*   Input(data,var,absolute) */

    // Output Report
    0x95, 64,   /*   Report Length (64 REPORT_SIZE) */
    0x09, 0x01, /*   USAGE (Vendor Usage 1) */
    0x91, 0x02, /*   Output(data,var,absolute) */

    // Feature Report
    0x95, 64,   /*   Report Length (64 REPORT_SIZE) */
    0x09, 0x01, /*   USAGE (Vendor Usage 1) */
    0xB1, 0x02, /*   Feature(data,var,absolute) */

    /* USER CODE END 0 */
    0xC0, /*  END_COLLECTION              */
};
