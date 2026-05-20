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
 * @brief  USB device endpiont reset.
 */
void usb_device_reset_endpoint(void)
{
    rom_hw_usb_ctrl_device_end_point_reset(EP_ADDR_HID_INT_IN, EN_TYPE_INT_IN);
    rom_hw_usb_ctrl_device_end_point_reset(EP_ADDR_HID_INT_OUT, EN_TYPE_INT_OUT);
    rom_hw_usb_ctrl_device_interrupt_send(EP_ADDR_HID_INT_IN, NULL, 0, 5);
    rom_hw_usb_ctrl_endpoint_interrupt_enable(EP_ADDR_HID_INT_OUT);
}

/**
 * @brief  USB device hid receive data.
 * @param  pu8Buf: Pointer to save received data.
 * @param  pu32Len: Pointer to received data length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
EN_USB_DEVICE_ERR_CODE usb_device_recive_hid_data(uint8_t *pu8Buf, uint32_t *pu32Len)
{
    return rom_hw_usb_ctrl_device_interrupt_receive(EP_ADDR_HID_INT_OUT, pu8Buf, HID_USB_DATA_PACKET_SIZE, pu32Len, 5);
}

/**
 * @brief  USB device hid send data.
 * @param  pu8Buf: Pointer to send buffer.
 * @param  u32Len: Send data buffer length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
EN_USB_DEVICE_ERR_CODE usb_device_send_hid_data(uint8_t *pu8Buf, uint32_t u32Len)
{
    return rom_hw_usb_ctrl_device_interrupt_send(EP_ADDR_HID_INT_IN, pu8Buf, u32Len, 5);
}
