/*************************************************************************************************************
 * @file    usbd_hid.c
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
#include "hw_usb_ctrl.h"
#include "hw_usb_dcd.h"

#include "app_cfg.h"
#include "utility.h"
#include "app_debug.h"

#include "usbd_standard_request.h"
#include "usbd_hid_descriptor.h"
#include "usbd_hid.h"

/**
 * @brief  LOCAL VARIABLE.
 */
static uint8_t m_u8UsbHidIdleState = 0;

/**
 * @brief  Reset USB device endpiont.
 */
void usb_device_reset_endpoint(void)
{
    rom_hw_usb_ctrl_device_end_point_reset ( EP_ADDR_HID_INT_IN, EN_TYPE_INT_IN );
    rom_hw_usb_ctrl_device_end_point_reset ( EP_ADDR_HID_INT_OUT, EN_TYPE_INT_OUT );
    rom_hw_usb_ctrl_device_interrupt_send ( EP_ADDR_HID_INT_IN, NULL, 0, 5 );
    rom_hw_usb_ctrl_endpoint_interrupt_enable ( EP_ADDR_HID_INT_OUT );
}

/**
 * @brief  USB device hid class request.
 * @param  pu8Setup: Pointer to setup buffer.
 */
void usb_device_hid_class_request (uint8_t *pu8Setup)
{
    uint8_t pu8Resp[8] = {0};
    uint8_t u8RespLen = 0; 
    uint16_t u16SetupReqIndex = 0;

    if (HID_DATA_INTERFACE_NUM == pu8Setup[4])
    {
        u16SetupReqIndex = pu8Setup[4]|(uint16_t)(pu8Setup[5])<<8;
        switch (pu8Setup[1])
        {
            case HID_SET_IDLE:
                if( 0 == u16SetupReqIndex )
                {
                    m_u8UsbHidIdleState = pu8Setup[3];
                }
                break;

            case HID_GET_IDLE:
                if( 0 == u16SetupReqIndex )
                {
                    pu8Resp[0] = m_u8UsbHidIdleState;
                    u8RespLen = 1;
                }
                break;
            
            case HID_GET_REPORT:
                break;

            case HID_SET_REPORT:
                break;
            
            case HID_SET_PROTOCOL:
                break;
            
            case HID_GET_PROTOCOL:
                break;
            
            default:
                break;
        }
        rom_hw_usb_ctrl_device_control_send ( pu8Resp, u8RespLen, 5 );
    }
}


/**
 * @brief  USB device hid recive data.
 * @param  pu8Buf: Pointer to save received data.
 * @param  pu32Len: Pointer to received data length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
EN_USB_DEVICE_ERR_CODE usb_device_hid_data_recive ( uint8_t *pu8ReceiveBuf, uint32_t *pu32Len )
{
    uint8_t ret = 0;
    ret = rom_hw_usb_ctrl_device_interrupt_receive ( EP_ADDR_HID_INT_OUT, pu8ReceiveBuf, HID_USB_PACKET_SIZE, pu32Len, 5 );
    return ret;
}


/**
 * @brief  USB device hid send keyboard data.
 * @param  pu8Buf: Pointer to send buffer.
 * @param  u32Len: Send data buffer length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
EN_USB_DEVICE_ERR_CODE usb_device_hid_keyboard_data_report ( uint8_t *pu8SendBuf, uint32_t u32Len )
{
    EN_USB_DEVICE_ERR_CODE enRet = 0;
    uint8_t pu8HidReportBuf[9] = {};
    pu8HidReportBuf[0] = HID_KEYBOARD_REPORT_ID;
    memcpy(&pu8HidReportBuf[1],pu8SendBuf,u32Len);
    enRet = rom_hw_usb_ctrl_device_interrupt_send ( EP_ADDR_HID_INT_IN, pu8HidReportBuf, 9, 5 );
    return enRet;
}

/**
 * @brief  USB device hid send consumer data.
 * @param  pu8Buf: Pointer to send buffer.
 * @param  u32Len: Send data buffer length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
EN_USB_DEVICE_ERR_CODE usb_device_hid_consumer_data_report ( uint8_t *pu8SendBuf, uint32_t u32Len )
{
    EN_USB_DEVICE_ERR_CODE enRet = 0;
    uint8_t pu8HidReportBuf[17] = {};
    pu8HidReportBuf[0] = HID_CONSUMER_REPORT_ID;
    memcpy(&pu8HidReportBuf[1],pu8SendBuf,u32Len);
    enRet = rom_hw_usb_ctrl_device_interrupt_send ( EP_ADDR_HID_INT_IN, pu8HidReportBuf, 17, 5 );
    return enRet;
}
