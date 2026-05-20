/*************************************************************************************************************
 * @file    hw_usb_ctrl.h
 * @version V1.1
 * @date    2022-01-14
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


#ifndef __HW_USB_CTRL_H__
#define __HW_USB_CTRL_H__

#ifdef __cplusplus
 extern "C" {
#endif /*__cplusplus*/


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define USB_MASK_EP_INVAILD_INT            (0x7F7F)
#define USB_REG_FIELD_BIT                  (8)
#define USB_ENDPOINT_MAX                   (7)
#define USB_INVAILD_EPCB                   ((struct usb_fp_callback_t *)(0xFFFFFFFF))

//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef enum
{
    EN_USB_HOOK_UNKNOWN         = 0,
    EN_USB_HOOK_DEV_PHY         = 1,
    EN_USB_HOOK_HOST_PHY        = 2,
    EN_USB_HOOK_DEV_CTRL        = 3,
    EN_USB_HOOK_HOST_CTRL       = 4,
    EN_USB_HOOK_UNFIFO          = 5,
    EN_USB_HOOK_FIFO            = 6,
    EN_USB_HOOK_MAX,

} EN_USB_CALLBACK_HOOK_T;

typedef void (*FPCALLBACK)(uint8_t u8Type, uint8_t u8EpNum);

struct usb_fp_callback_t
{
    uint8_t u8EpNum;
    FPCALLBACK fpcb;
};

typedef int (*USBCallBackHook_t)(int, void*, void*);


//=====================================================================================================================
// EXTERN VARIABLES
//=====================================================================================================================
extern USBCallBackHook_t USBCallBackHook[EN_USB_HOOK_MAX];





/**
 * @brief  A send buffer that load data from a buffer into an endpoint.
 * @param  u32EndPointNum: EpNum endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32Len: buf data lenght.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_load_fifo_data(uint32_t u32EndPointNum, uint8_t* pu8Buf, uint32_t u32Len);


/**
 * @brief  A send buffer that unload data from a buffer into an endpoint.
 * @param  u32EndPointNum: EpNum endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32Len: buf data lenght.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_unload_fifo_data(uint32_t u32EndPointNum, uint8_t* pu8Buf, uint32_t u32Len);


/**
 * @brief  Usb get endpoint interrupt flag.
 * @param  pu8EpIndex: Endpoint that generates the interrupt.
 * @param  pu16Intrx: Endpoint interrupt flag.
 * @param  pu8IntrUSB: Bus abnormal interrupt flag.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_ctrl_get_interrupt_flag(uint8_t* pu8EpIndex, uint16_t* pu16Intrx, uint8_t* pu8IntrUSB);


/**
 * @brief  The Device modeler enable an endpoint to interrupt.
 * @param  u8EpNum: EpNum endpoint.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_ctrl_endpoint_interrupt_enable(uint8_t u8EpNum);


/**
 * @brief  The Device modeler disable an endpoint to interrupt.
 * @param  u8EpNum: EpNum endpoint.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_ctrl_endpoint_interrupt_disable(uint8_t u8EpNum);


/**
 * @brief  The Device modeler init an endpoint to interrupt.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_ctrl_endpoint_interrupt_init(void);




#ifdef  __cplusplus
}
#endif /*__cplusplus*/

#endif /*__HW_USB_CTRL_H__*/


