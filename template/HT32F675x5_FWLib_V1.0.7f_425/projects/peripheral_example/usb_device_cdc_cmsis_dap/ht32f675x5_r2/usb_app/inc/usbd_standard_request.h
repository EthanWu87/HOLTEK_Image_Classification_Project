/*************************************************************************************************************
 * @file    usbd_standard_request.h
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


#ifndef __USBD_STANDARD_REQUEST_H__
#define __USBD_STANDARD_REQUEST_H__

/**
 * @brief  DEFINE.
 */
#define USB_DT_DEVICE                                 1
#define USB_DT_CONFIG                                 2
#define USB_DT_STRING                                 3
#define USB_DT_INTERFACE                              4
#define USB_DT_ENDPOINT                               5
#define USB_DT_DEVICE_QUALIFIER                       6
#define USB_DT_HID                                    0x21
#define USB_DT_HID_REPORT                             0x22

#define USB_REQ_GET_STATUS                            0
#define USB_REQ_CLEAR_FEATURE                         1
#define USB_REQ_SET_FEATURE                           3
#define USB_REQ_SET_ADDRESS                           5
#define USB_REQ_GET_DESCRIPTOR                        6
#define USB_REQ_SET_DESCRIPTOR                        7
#define USB_REQ_GET_CONFIGURATION                     8
#define USB_REQ_SET_CONFIGURATION                     9
#define USB_REQ_GET_INTERFACE                         10
#define USB_REQ_SET_INTERFACE                         11
#define USB_REQ_SYNCH_FRAME                           12

// Configuration Descriptor Type
#define USB_DESCRIPTOR_TYPE_DEVICE                    0x01U
#define USB_DESCRIPTOR_TYPE_CONFIGURATION             0x02U
#define USB_DESCRIPTOR_TYPE_STRING                    0x03U
#define USB_DESCRIPTOR_TYPE_INTERFACE                 0x04U
#define USB_DESCRIPTOR_TYPE_ENDPOINT                  0x05U
#define USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER          0x06U
#define USB_DESCRIPTOR_TYPE_OTHER_SPEED_CONFIGURATION 0x07U
#define USB_DESCRIPTOR_TYPE_BOS                       0x0FU

// Endpoint Descriptor Attributes(USB2.0 SPEC Table 9-13. Standard Endpoint Descriptor)
// Transfer Type
#define MASK_TRANS_TYPE_CTRL                          0x00
#define MASK_TRANS_TYPE_ISO                           0x01
#define MASK_TRANS_TYPE_BULK                          0x02
#define MASK_TRANS_TYPE_INT                           0x03

// Synchronization Type
#define MASK_SYNC_TYPE_NO_SYNCHRONIZATION             0x00
#define MASK_SYNC_TYPE_ASYNCHRONIZATION               0x04
#define MASK_SYNC_TYPE_ADAPTIVE                       0x08
#define MASK_SYNC_TYPE_SYNCHRONOUS                    0x0C

// Usage Type
#define MASK_USAGE_TYPE_DATA_EP                       0x00
#define MASK_USAGE_TYPE_FB_EP                         0x10
#define MASK_USAGE_TYPE_FB_DATA_EP                    0x20

// USER Endpoint Attributes
#define EP_ATTR_CTRL                                  (MASK_TRANS_TYPE_CTRL)
#define EP_ATTR_AUDIO_IN                              (MASK_TRANS_TYPE_ISO | MASK_SYNC_TYPE_ADAPTIVE | MASK_USAGE_TYPE_DATA_EP)
#define EP_ATTR_AUDIO_OUT                             (MASK_TRANS_TYPE_ISO | MASK_SYNC_TYPE_ADAPTIVE | MASK_USAGE_TYPE_DATA_EP)
#define EP_ATTR_HID_IN                                (MASK_TRANS_TYPE_INT | MASK_SYNC_TYPE_NO_SYNCHRONIZATION | MASK_USAGE_TYPE_DATA_EP)
#define EP_ATTR_HID_OUT                               (MASK_TRANS_TYPE_INT | MASK_SYNC_TYPE_NO_SYNCHRONIZATION | MASK_USAGE_TYPE_DATA_EP)
#define EP_ATTR_CDC_IN                                (MASK_TRANS_TYPE_BULK | MASK_SYNC_TYPE_NO_SYNCHRONIZATION | MASK_USAGE_TYPE_DATA_EP)
#define EP_ATTR_CDC_OUT                               (MASK_TRANS_TYPE_BULK | MASK_SYNC_TYPE_NO_SYNCHRONIZATION | MASK_USAGE_TYPE_DATA_EP)

// Endpoint Descriptor Address(USB2.0 SPEC Table 9-13. Standard Endpoint Descriptor)
// Endpoint Address(Support 6 endpoint)
#define MASK_EP_ADDR_CTRL                             0
#define MASK_EP_ADDR_1                                1
#define MASK_EP_ADDR_2                                2
#define MASK_EP_ADDR_3                                3
#define MASK_EP_ADDR_4                                4
#define MASK_EP_ADDR_5                                5
#define MASK_EP_ADDR_6                                6

// Endpoint Direction
#define MASK_EP_DIR_OUT                               0x00
#define MASK_EP_DIR_IN                                0x80

// USER Endpoint Address
#define EP_ADDR_CONTROL                               (MASK_EP_ADDR_CTRL)
#define EP_ADDR_CDC_BULK_IN                           (MASK_EP_DIR_IN | MASK_EP_ADDR_1)
#define EP_ADDR_CDC_BULK_OUT                          (MASK_EP_DIR_OUT | MASK_EP_ADDR_2)
#define EP_ADDR_HID_INT_OUT                           (MASK_EP_DIR_OUT | MASK_EP_ADDR_3)
#define EP_ADDR_HID_INT_IN                            (MASK_EP_DIR_IN | MASK_EP_ADDR_4)
#define EP_ADDR_AUDIO_ISO_IN                          (MASK_EP_DIR_IN | MASK_EP_ADDR_5)
#define EP_ADDR_AUDIO_ISO_OUT                         (MASK_EP_DIR_OUT | MASK_EP_ADDR_6)

// VID and PID
#define HOLTEK_VID                                    0x04D9
//#define HOLTEK_DFU_PID                                0x8675
#define HID_KEYBOARD_PID                              0x8675
//#define HID_MOUSE_PID                                 0x8675
//#define HID_KEYBORD_MOUSE_PID                         0x8675
//#define CDC_PID                                       0x8675
//#define AUDIO_MIC_PID                                 0x8675
//#define AUDIO_SPEEAKER_PID                            0x8675
//#define AUDIO_MIC_SPEEAKER_PID                        0x8675
//#define HID_AUDIO_CDC_PID                             0x8675

/**
 * @brief  TYPEDEF
 */
typedef struct
{
    uint8_t *pu8Buf;
    uint16_t u16BufLen;

} stUsbBuffer_t;

typedef struct
{
    stUsbBuffer_t stDeviceDescriptor;
    stUsbBuffer_t stConfigurationDescriptor;
    stUsbBuffer_t stInterfaceDescriptor;
    stUsbBuffer_t stEndpointDescriptor;
    stUsbBuffer_t stStringDescriptorLangeID;
    stUsbBuffer_t stStringDescriptorManuf;
    stUsbBuffer_t stStringDescriptorProduct;
    stUsbBuffer_t stStringDescriptorSerialNumber;
    stUsbBuffer_t stDeviceQualifierDescriptor;

} stUsbDescriptor_t;

/**
 * @brief  Init USB descriptor.
 */
extern void usb_device_standard_descriptor_init(void);

/**
 * @brief  Process control commands from Host.
 */
extern void usb_device_request_process(void);

#endif /*__USBD_STANDARD_REQUEST_H__*/
