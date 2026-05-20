/*************************************************************************************************************
 * @file    usbd_init.c
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
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_sys_ctrl.h"
#include "hal_pmu.h"
#include "hw_usb_phy.h"
#include "hw_usb_ctrl.h"
#include "hw_usb_dcd.h"
#include "hal_usb.h"

#include "app_cfg.h"
#include "utility.h"
#include "app_debug.h"

#include "usbd_cdc.h"
#include "usbd_standard_request.h"
#include "usbd_cdc_descriptor.h"
#include "usbd_init.h"

/**
 * @brief  Local variables.
 */
const static uint16_t m_au16UsbEpNumMask[] = {
    0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
    0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000,
};

struct usb_fp_callback_t m_pfnUsbFpCb[7] = {
    {0, NULL}, {1, NULL}, {2, NULL}, {3, NULL}, {4, NULL}, {5, NULL}, {6, NULL},
};

/**
 * @brief  USB module interrupt entry function, where the specific endpoint interrupt is judged,
 *         and then the callback function is executed.
 */
__RAM_FUNC void USB_IRQ_Handler(void)
{
    uint8_t  u8EpIndex, u8EpNum, u8IntrUSB;
    uint16_t u16Intrx;

    const struct usb_fp_callback_t *pstUsbFpCb = USB_INVAILD_EPCB;

    rom_hw_usb_ctrl_get_interrupt_flag(&u8EpIndex, &u16Intrx, &u8IntrUSB);

    u16Intrx &= USB_MASK_EP_INVAILD_INT; // holtek usb endpoint num max is 7(include EP0)
    for (u8EpNum = 0; (u8EpNum < (USB_REG_FIELD_BIT << 1)) && (u16Intrx >> u8EpNum); u8EpNum++)
    {
        if (u16Intrx & m_au16UsbEpNumMask[u8EpNum])
        {
            pstUsbFpCb = &m_pfnUsbFpCb[(u8EpNum % USB_REG_FIELD_BIT)];
            if (__builtin_expect(!!(pstUsbFpCb == USB_INVAILD_EPCB), 0))
            {
                continue;
            }
            else if (__builtin_expect(!!(pstUsbFpCb->fpcb == NULL), 0))
            {
                continue;
            }
            (*pstUsbFpCb->fpcb)(u8EpNum >= USB_REG_FIELD_BIT, pstUsbFpCb->u8EpNum);
        }
    }
}

/**
 * @brief USB phy interrupt.
 */
__RAM_FUNC void USB_PHY_IRQ_Handler(void)
{
    uint32_t u32Mask   = 0;

    rom_hw_sys_ctrl_get_usb_phy_int_flag(&u32Mask);
    rom_hw_sys_ctrl_clear_usb_phy_int_flag(u32Mask);

    rom_hw_sys_ctrl_get_usb_phy_por_event_int_flag(&u32Mask);
}

/**
 * @brief  USB device register endpoint callback function.
 * @param  epZero: ctrl endpoint cb,epTrx:other endpoint cb.
 */
static void usb_device_register_endpoint_callback(FPCALLBACK epZero, FPCALLBACK epTrx)
{
    m_pfnUsbFpCb[0].fpcb = epZero;
    m_pfnUsbFpCb[1].fpcb = epTrx;
    m_pfnUsbFpCb[2].fpcb = epTrx;
    m_pfnUsbFpCb[3].fpcb = epTrx;
    m_pfnUsbFpCb[4].fpcb = epTrx;
    m_pfnUsbFpCb[5].fpcb = epTrx;
    m_pfnUsbFpCb[6].fpcb = epTrx;
}

/**
 * @brief  USB device trx endpoint handler.
 * @param  u8Type: USB endpoint type, @ref EN_USB_EP_INT_TPYE_T.
 * @param  u8EpNum: Endpoint number.
 */
static void usb_device_trx_endpoint_handle(uint8_t u8Type, uint8_t u8EpNum)
{
    uint32_t u32RcvLen = 0;
    uint8_t  u8RcvData[64];

    PRINTF("[TRX]Type: %d, EpNum: %d\n", u8Type, u8EpNum);

    if (EN_USB_INT_EP_RX == u8Type)
    {
        if (EP_ADDR_CDC_BULK_OUT == u8EpNum)
        {
            usb_device_recive_cdc_data(u8RcvData, &u32RcvLen);
            app_debug_printf_hex_string("CDC Rcv", u8RcvData, u32RcvLen);
            usb_device_send_cdc_data(u8RcvData, u32RcvLen);
        }
    }
    else if (EN_USB_INT_EP_TX == u8Type)
    {
        u8EpNum = u8EpNum | 0x80;
        if (EP_ADDR_CDC_BULK_IN == u8EpNum)
        {
        }
    }
}

/**
 * @brief  USB device ctrl endpoint handler.
 * @param  u8Type: USB endpoint type, @ref EN_USB_EP_INT_TPYE_T.
 * @param  u8EpNum: Endpoint number.
 */
static void usb_device_ctrl_endpoint_handle(uint8_t u8Type, uint8_t u8EpNum)
{
    // PRINTF("[CTRL]Type: %d, EpNum: %d\n", u8Type, u8EpNum);

    /*EP0,rx and tx share*/
    if (EN_USB_INT_EP_RX == u8Type || EN_USB_INT_EP_TX == u8Type)
    {
        usb_device_request_process();
    }
}

/**
 * @brief  USB Device Init.
 */
void usb_device_init(void)
{
    // 1. Enable PLL48M clock and enable usb clock gate.
    // Enable PLL48M clock to make sure output 48MHz clock for USB.
    rom_hal_pmu_enable_pll_clk(EN_DCXO_HCLK_FREQ_16M, 2000);
    rom_hal_usb_clock_enable(true);

    // 2. Enable usb irq.
    // 2.1 Enable USB_CTRL irq.
    NVIC_ClearPendingIRQ(USB_CTRL_IRQ);
    NVIC_SetPriority(USB_CTRL_IRQ, 0x3);
    NVIC_EnableIRQ(USB_CTRL_IRQ);
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, USB_CTRL_IRQ);

    // 2.2 Enable USB_PHY irq.
    NVIC_ClearPendingIRQ(USB_PHY_IRQ);
    NVIC_SetPriority(USB_PHY_IRQ, 0x3);
    NVIC_EnableIRQ(USB_PHY_IRQ);
    rom_hw_sys_ctrl_enable_usb_phy_pd_int(); // Enable USB phy interrupt
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, USB_PHY_IRQ);

    // 3. Register usb endpoint transmit handle.
    usb_device_register_endpoint_callback(usb_device_ctrl_endpoint_handle, usb_device_trx_endpoint_handle);

    // 4. Initialize USB to device mode.
    rom_hal_usb_device_init();
    usb_device_standard_descriptor_init();
    usb_device_reset_endpoint();

    // 5. Resume enum.
    rom_hal_usb_device_software_disconnect();
    rom_delay_ms(15); // Must >= 10ms.
    rom_hal_usb_device_software_connect();
}
