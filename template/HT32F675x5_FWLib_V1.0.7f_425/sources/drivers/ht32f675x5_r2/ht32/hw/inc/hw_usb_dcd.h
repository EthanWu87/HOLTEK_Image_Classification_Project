/*************************************************************************************************************
 * @file    hw_usb_dcd.h
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


#ifndef __HW_USB_DCD_H__
#define __HW_USB_DCD_H__

#ifdef __cplusplus
 extern "C" {
#endif /*__cplusplus*/


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
// Max packet size. Fixed, user should not modify.
#define DEVICE_FS_CONTROL_MPS              ( 64 )
#define DEVICE_FS_INT_IN_MPS               ( 64 )
#define DEVICE_FS_INT_OUT_MPS              ( 64 )
#define DEVICE_FS_BULK_IN_MPS              ( 64 )
#define DEVICE_FS_BULK_OUT_MPS             ( 64 )
#define DEVICE_FS_ISO_IN_MPS               ( 64 )
#define DEVICE_FS_ISO_OUT_MPS              ( 64 )

#define USB_DEVICE_DEFAULT_ADDR            ( 0x00 )


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef enum _DEVICE_TRANSFER_TYPE
{
    EN_TYPE_SETUP        = 0xFF,
    EN_TYPE_CONTROL_IN   = 0xFE,
    EN_TYPE_CONTROL_OUT  = 0xFD,
    EN_TYPE_ISO_IN       = 0x81,
    EN_TYPE_ISO_OUT      = 0x01,
    EN_TYPE_BULK_IN      = 0x82,
    EN_TYPE_BULK_OUT     = 0x02,
    EN_TYPE_INT_IN       = 0x83,
    EN_TYPE_INT_OUT      = 0x03,

} EN_DEVICE_TRANSFER_TYPE;

typedef enum
{
    EN_USB_INT_EP_RX = 0,
    EN_USB_INT_EP_TX = 1,

} EN_USB_EP_INT_TPYE_T;


typedef enum _EN_USB_DEVICE_ERR_CODE
{
    EN_DEVICE_NONE_ERR = 0,
    EN_DEVICE_UNLINK_ERR,

    EN_CONTROL_SEND_ERR,
    EN_CONTROL_RCV_ERR,
    EN_CONTROL_SETUP_ERR,

    EN_BULK_SEND_ERR,
    EN_BULK_RCV_ERR0,
    EN_BULK_RCV_ERR1,
    EN_BULK_RCV_ERR2,

    EN_INT_SEND_ERR,
    EN_INT_RCV_ERR0,
    EN_INT_RCV_ERR1,
    EN_INT_RCV_ERR2,

} EN_USB_DEVICE_ERR_CODE;




/**
 * @brief  usb ctrl device initial.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_ctrl_device_init(void);


/**
 * @brief  Return STALL response.
 * @param  u8EndPointNum: EndPointNum endpoint.
 */
extern void rom_hw_usb_ctrl_device_stall_send_response(uint8_t u8EndPointNum);


/**
 * @brief  Reset the endpoint.
 * @param  u8EndPointNum: EndPointNum endpoint.
 * @param  enEndPointType: EndPointNum type, @ref EN_DEVICE_TRANSFER_TYPE.
 */
extern void rom_hw_usb_ctrl_device_end_point_reset(uint8_t u8EndPointNum, EN_DEVICE_TRANSFER_TYPE enEndPointType);


/**
 * @brief  Set the device address. After the bus is reset, set the device address to 0.
 * @brief  Then set the specified device address according to the setAddress command sent from the host terminal.
 * @param  u8Address: Device addr.
 */
extern void rom_hw_usb_ctrl_device_addr_set(uint8_t u8Address);


/**
 * @brief  Gets events on the USB bus.
 * @return uint8_t: USB bus event coding.
 */
extern uint8_t rom_hw_usb_ctrl_device_bus_event_get(void);


/**
 * @brief  Sends data from the control endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32Len: buf data length.
 * @param  u32TimeOut: timeout.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
EN_USB_DEVICE_ERR_CODE rom_hw_usb_ctrl_device_control_send(uint8_t* pu8Buf, uint32_t u32Len, uint32_t u32TimeOut);


/**
 * @brief  Receive OUT data from the control endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32MaxLen: Buf data receive max length.
 * @param  u32TimeOut: Timeout.
 * @param  p32TransferLen : The actual length of data received.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE rom_hw_usb_ctrl_device_control_receive(uint8_t* pu8Buf, uint32_t u32MaxLen,
                                                                     uint32_t* pu32TransferLen, uint32_t u32TimeOut);


/**
 * @brief  Receive SETUP data from the control endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32MaxLen: Buf data receive max length,usually 8 octet.
 * @param  p32TransferLen: The actual length of data received.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE rom_hw_usb_ctrl_device_setup_receive(uint8_t* pu8Buf, uint32_t u32MaxLen,
                                                                   uint32_t* pu32TransferLen);


/**
 * @brief  Sends data from the Bulk In endpoint.
 * @param  u8EpNum: Endpoint number.
 * @param  pu8Buf: Point to the send buffer.
 * @param  u32Len: Send buffer length.
 * @param  u32TimeOut: Send timeout.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE rom_hw_usb_ctrl_device_bulk_send(uint8_t u8EpNum, uint8_t *pu8Buf, uint32_t u32Len,
                                                               uint32_t u32TimeOut);


/**
 * @brief  Receive data from BULK OUT endpoint.
 * @param  u8EpNum: EpNum endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32MaxLen: Buf data receive max length.
 * @param  u32TimeOut: Timeout.
 * @param  p32TransferLen : The actual length of data received.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE rom_hw_usb_ctrl_device_bulk_receive(uint8_t u8EpNum, uint8_t* pu8Buf, uint16_t u32MaxLen,
                                                                  uint32_t* pu32TransferLen, uint32_t u32TimeOut);


/**
 * @brief  Sends data from the ISO In endpoint.
 * @param  u8EpNum: EpNum endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32Len: Buf data length.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE rom_hw_usb_ctrl_device_iso_send(uint8_t u8EpNum, uint8_t* pu8Buf, uint32_t u32Len);


/**
 * @brief  Receive data from the IOS OUT endpoint.
 * @param  u8EpNum: EpNum endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32MaxLen: Buf data receive max length.
 * @param  p32TransferLen: The actual length of data received.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE rom_hw_usb_ctrl_device_iso_receive(uint8_t u8EpNum, uint8_t* pu8Buf, uint32_t u32MaxLen,
                                                                 uint32_t* pu32TransferLen);


/**
 * @brief  Sends data from the INT IN endpoint.
 * @param  u8EpNum: EpNum endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32Len: Buf data length,it cannot be greater than DEVICE_FS_BULK_IN_MPS.
 * @param  u32TimeOut: Timeout.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE rom_hw_usb_ctrl_device_interrupt_send(uint8_t u8EpNum, uint8_t* pu8Buf, uint32_t u32Len,
                                                                    uint32_t u32TimeOut);


/**
 * @brief  Receive data from the INT OUT endpoint.
 * @param  u8EpNum: EpNum endpoint.
 * @param  pu8Buf: Point to data buf.
 * @param  u32MaxLen: Buf data receive max length.
 * @param  u32TimeOut: Timeout.
 * @param  p32TransferLen: The actual length of data received.
 * @return Error code, @ref USB_DEVICE_ERR_CODE.
 */
extern EN_USB_DEVICE_ERR_CODE rom_hw_usb_ctrl_device_interrupt_receive(uint8_t u8EpNum, uint8_t* pu8Buf, uint16_t u32MaxLen,
                                                                       uint32_t* p32TransferLen, uint32_t u32TimeOut);



#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__HW_USB_DCD_H__*/
/**
 * @}
 * @}
 */


