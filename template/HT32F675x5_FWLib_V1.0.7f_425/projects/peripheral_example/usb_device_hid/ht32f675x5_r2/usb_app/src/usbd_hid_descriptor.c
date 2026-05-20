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
 * @brief  USB Device Descriptor.
 */
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
    LO_UINT16(HID_PID),
    HI_UINT16(HID_PID), /* idProduct */
    0x00,
    0x01, /* bcdDevice */
    0x01, /* iManufacturer */
    0x02, /* iProduct */
    0x03, /* iSerialNumber */
    0x01, /* bNumConfigurations */
};

/* USB Configuration Descriptor */
uint8_t g_au8UsbConfigurationDescriptor[] = {
    /*Configuration Descriptor*/
    0x09,                                 /* bLength: Configuration Descriptor size */
    USB_DT_CONFIG,                        /* bDescriptorType: Configuration */
    9+9+9+7+7,                            /* wTotalLength:no of returned bytes */
    0x00,
    0x01,                                 /* bNumInterfaces:3 interface */
    0x01,                                 /* bConfigurationValue: Configuration value */
    0x00,                                 /* iConfiguration: Index of string descriptor describing the configuration */
    0x80,                                 /* bmAttributes: usb Vbus powered */
    0xFA,                                 /* MaxPower: x*2mA: 500mA */
    
    /*Interface Descriptor */
    0x09,                        /* bLength */
    USB_DT_INTERFACE,            /* bDescriptorType */
    HID_DATA_INTERFACE_NUM,      /* bInterfaceNumber */
    0x00,                        /* bAlternateSetting */
    0x02,                        /* bEndpoints: 1 endpoint for input, 1 endpoint for output */
    0x03,                        /* bInterfaceClass: HID class */
    0x00,                        /* bInterfaceSubClass: 0x01 support BIOS boot */
    0x00,                        /* bInterfaceProtocol: keyboard boot 0x01, mouse boot 0x02 */
    0x00,                        /* iConfiguration */

    /*Device Class Descriptor */
    0x09,                        /* bLength */
    USB_DT_HID,                  /* bDescriptorType:HID 0x21 */
    0x01, 0x02,                  /* bcdHID */
    0x00,                        /* bCountyCode: United States 0x21 */
    0x01,                        /* bNumDescriptors: 1 HID report */
    USB_DT_HID_REPORT,           /* bDescriptorType */
    sizeof ( g_au8HidDataReportDescriptor ) & 0xff,  /* bDescriptorLength */
    ( sizeof ( g_au8HidDataReportDescriptor ) >> 8 ) & 0xff,

    /*Endpoint Descriptor*/
    0x07,                           /* bL0ength: Endpoint Descriptor size */
    USB_DT_ENDPOINT,                /* bDescriptorType: Endpoint */
    EP_ADDR_HID_INT_OUT,            /* bEndpointAddress */
    EP_ATTR_HID_OUT,                /* bmAttributes: Interrupt */
    HID_USB_PACKET_SIZE, 0x00,      /* wMaxPacketSize */
    0x01,                           /* bInterval: 1 ms*/

    0x07,                           /* bLength: Endpoint Descriptor size */
    USB_DT_ENDPOINT,                /* bDescriptorType: Endpoint */
    EP_ADDR_HID_INT_IN,             /* bEndpointAddress */
    EP_ATTR_HID_IN,                 /* bmAttributes: Interrupt */
    HID_USB_PACKET_SIZE, 0x00,      /* wMaxPacketSize */
    0x01,                           /* bInterval: 1 ms*/
};

/*USB HID report descriptor*/
uint8_t g_au8HidDataReportDescriptor[169] =
{
    0x05, 0x01,                 /* Usage Page (Generic Desktop) */
    0x09, 0x02,                 /* Usage (Mouse) */
    0xA1, 0x01,                 /* Collection (Application) */
    0x09, 0x01,                 /* Usage (Pointer) */
    0xA1, 0x00,                 /* Collection (Physical) */
    0x85, HID_MOUSE_REPORT_ID,  /* Report Id (1) */
    0x05, 0x09,                 /* Usage Page (Buttons) */
    0x19, 0x01,                 /* Usage Minimum (01) - Button 1 */
    0x29, 0x03,                 /* Usage Maximum (03) - Button 3 */
    0x15, 0x00,                 /* Logical Minimum (0) */
    0x25, 0x01,                 /* Logical Maximum (1) */
    0x75, 0x01,                 /* Report Size (1) */
    0x95, 0x03,                 /* Report Count (3) */
    0x81, 0x02,                 /* Input (Data, Variable, Absolute) - Button states */
    0x75, 0x05,                 /* Report Size (5) */
    0x95, 0x01,                 /* Report Count (1) */
    0x81, 0x01,                 /* Input (Constant) - Padding or Reserved bits */
    0x05, 0x01,                 /* Usage Page (Generic Desktop) */
    0x09, 0x30,                 /* Usage (X) */
    0x09, 0x31,                 /* Usage (Y) */
    0x09, 0x38,                 /* Usage (Wheel) */
    0x15, 0x81,                 /* Logical Minimum (-127) */
    0x25, 0x7F,                 /* Logical Maximum (127) */
    0x75, 0x08,                 /* Report Size (8) */
    0x95, 0x03,                 /* Report Count (3) */
    0x81, 0x06,                 /* Input (Data, Variable, Relative) - X & Y coordinate */
    0xC0,                       /* End Collection */
    0xC0,                       /* End Collection */
    
    0x05, 0x01,                     /* Usage Page (Generic Desktop Ctrls) */
    0x09, 0x06,                     /* Usage (Keyboard) */
    0xA1, 0x01,                     /* Collection (Application) */
    0x85, HID_KEYBOARD_REPORT_ID,   /* Report ID (1) */
    0x05, 0x07,         /*   Usage Page (Kbrd/Keypad) */
    0x19, 0xE0,         /*   Usage Minimum (0xE0) */
    0x29, 0xE7,         /*   Usage Maximum (0xE7) */
    0x15, 0x00,         /*   Logical Minimum (0) */
    0x25, 0x01,         /*   Logical Maximum (1) */
    0x75, 0x01,         /*   Report Size (1) */
    0x95, 0x08,         /*   Report Count (8) */
    0x81, 0x02,         /*   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position) */
    0x75, 0x08,         /*   Report Size (8) */
    0x95, 0x01,         /*   Report Count (1) */
    0x81, 0x01,         /*   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position) */
    0x05, 0x07,         /*   Usage Page (Kbrd/Keypad) */
    0x19, 0x04,         /*   Usage Minimum (0x04) */
    0x29, 0x94,         /*   Usage Maximum (0x94) */
    0x15, 0x00,         /*   Logical Minimum (0) */
    0x25, 0x01,         /*   Logical Maximum (1) */
    0x75, 0x01,         /*   Report Size (1) */
    0x95, 0x90,         /*   Report Count (144) */
    0x81, 0x02,         /*   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position) */
    0x85, 0x08,         /*   Report ID (8) */
    0x05, 0x08,         /*   Usage Page (LEDs) */
    0x19, 0x01,         /*   Usage Minimum (Num Lock) */
    0x29, 0x05,         /*   Usage Maximum (Kana) */
    0x15, 0x00,         /*   Logical Minimum (0) */
    0x25, 0x01,         /*   Logical Maximum (1) */
    0x95, 0x05,         /*   Report Count (5) */
    0x75, 0x01,         /*   Report Size (1) */
    0x91, 0x02,         /*   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile) */
    0x95, 0x01,         /*   Report Count (1) */
    0x75, 0x03,         /*   Report Size (3) */
    0x91, 0x01,         /*   Output (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile) */
    0x85, 0x09,         /*   Report ID (9) */
    0x06, 0x00, 0xFF,   /*   Usage Page (Vendor Defined 0xFF00) */
    0x0A, 0x01, 0xFF,   /*   Usage (0xFF01) */
    0x15, 0x00,         /*   Logical Minimum (0) */
    0x26, 0xFF, 0x00,   /*   Logical Maximum (255) */
    0x75, 0x08,         /*   Report Size (8) */
    0x95, 0x1D,         /*   Report Count (29) */
    0xB1, 0x02,         /*   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile) */
    0xC0,               /* End Collection */

    0x05, 0x0C,                     /* Usage Page(Consumer) */
    0x09, 0x01,                     /* Usage(Consumer Control) */
    0xA1, 0x01,                     /* Collection(Application) */
    0x85, HID_CONSUMER_REPORT_ID,   /* Report ID (3)   */
    0x19, 0x00,                     /* Usage Min (0x00) */
    0x2a, 0x9c, 0x02,               /* Usage Max (0x029c) */
    0x15, 0x00,                     /* Logical Min (0x00) */
    0x26, 0x9c, 0x02,               /* Logical Max (0x029c) */
    0x75, 0x10,                     /* Report Size (0x10) */
    0x95, 0x08,                     /* Report Count (0x08) */
    0x81, 0x00,                     /* Input (Data,Ary,Abs) */
    0xC0,                           /* End Collection(Application) */
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



