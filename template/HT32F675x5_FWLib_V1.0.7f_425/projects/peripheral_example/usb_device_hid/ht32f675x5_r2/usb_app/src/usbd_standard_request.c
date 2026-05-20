/*************************************************************************************************************
 * @file    usbd_standard_request.c
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


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_usb_phy.h"
#include "hw_usb_ctrl.h"
#include "hw_usb_timeout.h"
#include "hw_usb_dcd.h"
#include "hw_usb_hcd.h"
#include "hal_usb.h"
#include "patch_hw_usb_ctrl.h"

#include "app_cfg.h"
#include "type_def.h"
#include "utility.h"
#include "app_debug.h"

#include "usbd_utility.h"
#include "usbd_hid.h"
#include "usbd_hid_descriptor.h"
#include "usbd_standard_request.h"
#include "usbd_init.h"

/**
 * @brief  LOCAL VARIABLE.
 */
static stUsbDescriptor_t m_stUsbDescriptor = {
    .stDeviceDescriptor             = {.pu8Buf = NULL, .u16BufLen = 0},
    .stConfigurationDescriptor      = {.pu8Buf = NULL, .u16BufLen = 0},
    .stInterfaceDescriptor          = {.pu8Buf = NULL, .u16BufLen = 0},
    .stEndpointDescriptor           = {.pu8Buf = NULL, .u16BufLen = 0},
    .stStringDescriptorLangeID      = {.pu8Buf = NULL, .u16BufLen = 0},
    .stStringDescriptorManuf        = {.pu8Buf = NULL, .u16BufLen = 0},
    .stStringDescriptorProduct      = {.pu8Buf = NULL, .u16BufLen = 0},
    .stStringDescriptorSerialNumber = {.pu8Buf = NULL, .u16BufLen = 0},
    .stDeviceQualifierDescriptor    = {.pu8Buf = NULL, .u16BufLen = 0},
};

static uint8_t m_au8StringDescriptorBuf[128];

static uint8_t m_pu8EpStates[7] = {0};
static uint16_t m_u16UsbConfig = 0;
static uint8_t m_u8ReqInterface = 0;

/**
 * @brief  Init USB descriptor.
 */
void usb_device_standard_descriptor_init(void)
{
    // 1. Device Descriptor
    m_stUsbDescriptor.stDeviceDescriptor.pu8Buf    = (uint8_t *)g_au8UsbDeviceDescriptor;
    m_stUsbDescriptor.stDeviceDescriptor.u16BufLen = g_au8UsbDeviceDescriptor[0];

    // 2. Configuration Descriptor
    m_stUsbDescriptor.stConfigurationDescriptor.pu8Buf    = (uint8_t *)g_au8UsbConfigurationDescriptor;
    m_stUsbDescriptor.stConfigurationDescriptor.u16BufLen = g_au8UsbConfigurationDescriptor[2];

    // 3. String Descriptor
    // LangeID
    m_stUsbDescriptor.stStringDescriptorLangeID.pu8Buf    = (uint8_t *)g_au8UsbStringDescriptorLangID;
    m_stUsbDescriptor.stStringDescriptorLangeID.u16BufLen = g_au8UsbStringDescriptorLangID[0];

    // 4. Device Qualifier Descriptor
    m_stUsbDescriptor.stDeviceQualifierDescriptor.pu8Buf    = (uint8_t *)g_au8DeviceQualifierDescriptor;
    m_stUsbDescriptor.stDeviceQualifierDescriptor.u16BufLen = g_au8DeviceQualifierDescriptor[0];
    
}

/**
 * @brief  return the string length.
 * @param  pu8Buf : pointer to the ascii string buffer.
 * @retval string length.
 */
static uint8_t usb_device_get_Len(uint8_t *pu8Buf)
{
    uint8_t len = 0U;

    while (*pu8Buf != '\0')
    {
        len++;
        pu8Buf++;
    }

    return len;
}

/**
 * @brief  Convert Ascii string into unicode one.
 * @param  desc : descriptor buffer.
 * @param  unicode : Formatted string buffer (unicode).
 * @param  len : descriptor length.
 */
void usb_device_get_string(uint8_t *pu8Desc, uint8_t *pu8Unicode, uint16_t *pu16Len)
{
    uint8_t idx = 0U;

    if (pu8Desc != NULL)
    {
        *pu16Len          = (uint16_t)usb_device_get_Len(pu8Desc) * 2U + 2U;
        pu8Unicode[idx++] = *(uint8_t *)(void *)pu16Len;
        pu8Unicode[idx++] = USB_DT_STRING;

        while (*pu8Desc != '\0')
        {
            pu8Unicode[idx++] = *pu8Desc++;
            pu8Unicode[idx++] = 0U;
        }
    }
}

/**
 * @brief  Process the get descriptor command.
 */
static void usb_device_get_descriptor(uint8_t *pu8Setup)
{
    uint16_t      u16MaxLen;
    stUsbBuffer_t stUsbBuf = {.pu8Buf = NULL, .u16BufLen = 0};

    switch (pu8Setup[3])
    {
        case USB_DT_DEVICE:
        {
            stUsbBuf.pu8Buf    = m_stUsbDescriptor.stDeviceDescriptor.pu8Buf;
            stUsbBuf.u16BufLen = m_stUsbDescriptor.stDeviceDescriptor.u16BufLen;
            break;
        }
        case USB_DT_CONFIG:
        {
            stUsbBuf.pu8Buf    = m_stUsbDescriptor.stConfigurationDescriptor.pu8Buf;
            stUsbBuf.u16BufLen = m_stUsbDescriptor.stConfigurationDescriptor.u16BufLen;
            break;
        }
        case USB_DT_STRING:
        {
            if (pu8Setup[2] == USBD_IDX_LANGID_STR)
            {
                stUsbBuf.pu8Buf    = m_stUsbDescriptor.stStringDescriptorLangeID.pu8Buf;
                stUsbBuf.u16BufLen = m_stUsbDescriptor.stStringDescriptorLangeID.u16BufLen;
            }
            else if (pu8Setup[2] == USBD_IDX_MFC_STR)
            {
                usb_device_get_string((uint8_t *)USB_STRING_DESCRIPTOR_MANUFACTURER, m_au8StringDescriptorBuf,
                                      &stUsbBuf.u16BufLen);
                stUsbBuf.pu8Buf = m_au8StringDescriptorBuf;
            }
            else if (pu8Setup[2] == USBD_IDX_PRODUCT_STR)
            {
                usb_device_get_string((uint8_t *)USB_STRING_DESCRIPTOR_PRODUCT, m_au8StringDescriptorBuf,
                                      &stUsbBuf.u16BufLen);
                stUsbBuf.pu8Buf = m_au8StringDescriptorBuf;
            }
            else if (pu8Setup[2] == USBD_IDX_CONFIG_STR)
            {
                
            }
            else
            {
                usb_device_get_string((uint8_t *)USB_STRING_DESCRIPTOR_SERIAL_NUMBER, m_au8StringDescriptorBuf,
                                      &stUsbBuf.u16BufLen);
                stUsbBuf.pu8Buf = m_au8StringDescriptorBuf;
            }
            break;
        }
        case USB_DT_INTERFACE:
        {
            // The PC will not send this instruction by default
            break;
        }
        case USB_DT_ENDPOINT:
        {
            // The PC will not send this instruction by default
            break;
        }
        case USB_DT_DEVICE_QUALIFIER:
        {
            stUsbBuf.pu8Buf    = m_stUsbDescriptor.stDeviceQualifierDescriptor.pu8Buf;
            stUsbBuf.u16BufLen = m_stUsbDescriptor.stDeviceQualifierDescriptor.u16BufLen;
            break;
        }
        
        case USB_DT_HID_REPORT:
            stUsbBuf.pu8Buf = g_au8HidDataReportDescriptor;
            stUsbBuf.u16BufLen = sizeof(g_au8HidDataReportDescriptor);
            break;
        
        case USB_DT_BOS:
            patch_hw_usb_ctrl_device_stall_send_response ( EP_ADDR_CONTROL );
            break;
        
        case USB_DT_HID:
            stUsbBuf.pu8Buf = &g_au8UsbConfigurationDescriptor[18];
            stUsbBuf.u16BufLen = 9;
            break;
        
        default:
        {
            patch_hw_usb_ctrl_device_stall_send_response ( EP_ADDR_CONTROL );
            return;
        }
    }

    u16MaxLen = BUILD_UINT16(pu8Setup[6], pu8Setup[7]);
    if (stUsbBuf.u16BufLen > u16MaxLen)
    {
        stUsbBuf.u16BufLen = u16MaxLen;
    }

    EN_USB_DEVICE_ERR_CODE enUsbRet = EN_DEVICE_NONE_ERR;
    enUsbRet = rom_hw_usb_ctrl_device_control_send(stUsbBuf.pu8Buf, stUsbBuf.u16BufLen, 10);
    if( enUsbRet != EN_DEVICE_NONE_ERR )
    {
        PRINTF("ctrl send error:%d\r\n", enUsbRet);
    }
}

/**
 * @brief  USB device standard request.
 * @param  pu8Setup: Pointer to setup buffer.
 */
static void usb_device_standard_request(uint8_t *pu8Setup)
{
    uint8_t u8Resp[8];

    switch (pu8Setup[1])
    {
        case USB_REQ_GET_STATUS:
        {
            u8Resp[0] = 0x00;
            u8Resp[1] = 0x00;
            if( (pu8Setup[0]&SETUP_BIT_MASK) == 0x00 )//get status of device
            {
                PRINTF ( "Get status of device\r\n" );
            }
            else if( (pu8Setup[0]&SETUP_BIT_MASK) == 0x02 )//get status of endpoints
            {
                //if ep is stall, u8Resp[0] = 0x01;
                if(m_pu8EpStates[(pu8Setup[4]&0x1f)] == 1)
                {
                    u8Resp[0] = 0x01;
                }
            }
            
            rom_hw_usb_ctrl_device_control_send ( ( uint8_t* ) &u8Resp, 2, 10 );
            break;
        }
        case USB_REQ_CLEAR_FEATURE:
        {
            if( (pu8Setup[0]&SETUP_BIT_MASK) == 0x02 )//Clear End-point Feature
            {
                uint16_t u16UsbSetupReqValue = ((uint16_t)pu8Setup[2] | (pu8Setup[3] << 8));
                if( 0 == u16UsbSetupReqValue )
                {
                    m_pu8EpStates[(pu8Setup[4]&SETUP_BIT_MASK)] = 0;
                }
            }
            break;
        }
        case USB_REQ_SET_FEATURE:
        {
            if( (pu8Setup[0] & SETUP_BIT_MASK) == 0x02 )//Set End-point Feature
            {
                uint16_t u16UsbSetupReqValue = ((uint16_t)pu8Setup[2] | (pu8Setup[3] << 8));
                if( 0 == u16UsbSetupReqValue )
                {
                    patch_hw_usb_ctrl_device_stall_send_response ( pu8Setup[4] );
                    m_pu8EpStates[(pu8Setup[4] & SETUP_BIT_MASK)] = 1;
                }
            }
            break;
        }
        case USB_REQ_SET_ADDRESS:
        {
            rom_hw_usb_ctrl_device_addr_set(pu8Setup[2] & 0x7F);
            break;
        }
        case USB_REQ_GET_DESCRIPTOR:
        {
            usb_device_get_descriptor(pu8Setup);
            break;
        }
        case USB_REQ_SET_DESCRIPTOR:
        {
            break;
        }
        case USB_REQ_GET_CONFIGURATION:
        {
            u8Resp[0] = m_u16UsbConfig&0xff;
            u8Resp[1] = m_u16UsbConfig>>8;
            rom_hw_usb_ctrl_device_control_send ( ( uint8_t* ) &u8Resp, 1, 5 );
            break;
        }
        case USB_REQ_SET_CONFIGURATION:
        {
            m_u16UsbConfig = ((uint16_t)pu8Setup[3]<<8)+pu8Setup[2];
            usb_device_reset_endpoint();
            break;
        }
        case USB_REQ_GET_INTERFACE:
        {
            u8Resp[0] = m_u8ReqInterface;
            rom_hw_usb_ctrl_device_control_send ( ( uint8_t* ) &u8Resp, 1, 5 );
            break;
        }
        case USB_REQ_SET_INTERFACE:
        {
            m_u8ReqInterface = pu8Setup[2];
            break;
        }
        case USB_REQ_SYNCH_FRAME:
        {
            break;
        }
        default:
        {
            patch_hw_usb_ctrl_device_stall_send_response ( EP_ADDR_CONTROL );
            break;
        }
    }
}

/**
 * @brief  USB device class request.
 */
static void usb_device_class_request(uint8_t *pu8Setup)
{
    usb_device_hid_class_request (pu8Setup);
}

/**
 * @brief  USB device manufacturer request.
 */
static void usb_device_manufactur_request(void) {}

/**
 * @brief  USB device unkown request.
 * @param  None.
 * @output
 * @return None.
 */
static void usb_device_other_request(void)
{
    patch_hw_usb_ctrl_device_stall_send_response(EP_ADDR_CONTROL);
}

/**
 * @brief  Process control commands from Host.
 */
void usb_device_request_process(void)
{
    uint8_t  u8BusEvent;
    uint32_t u32DataLen;
    uint8_t  u8ReqType;
    uint8_t  au8Setup[8];

    u8BusEvent = rom_hw_usb_ctrl_device_bus_event_get();

    if (u8BusEvent & 0x04)
    {
        rom_hw_usb_ctrl_device_addr_set(0);
    }

    if (rom_hw_usb_ctrl_device_setup_receive(au8Setup, 8, &u32DataLen) != EN_DEVICE_NONE_ERR)
    {
        return;
    }

    u8ReqType = (au8Setup[0] & 0x60) >> 5;
    switch (u8ReqType)
    {
        case USB_REQ_TYPE_STANDARD:
        {
            usb_device_standard_request(au8Setup);
            break;
        }
        case USB_REQ_TYPE_CLASS:
        {
            usb_device_class_request(au8Setup);
            break;
        }
        case USB_REQ_TYPE_VENDOR:
        {
            usb_device_manufactur_request();
            break;
        }
        default:
        {
            usb_device_other_request();
            break;
        }
    }
}
