/*************************************************************************************************************
 * @file    hw_usb_hcd.h
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


#ifndef __HW_USB_HCD_H__
#define __HW_USB_HCD_H__

#ifdef __cplusplus
 extern "C" {
#endif  /*__cplusplus*/


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define HOST_CONTROL_EP         ( 0 )
#define HOST_BULK_IN_EP         ( 1 )
#define HOST_BULK_OUT_EP        ( 1 )
#define HOST_INT_IN_EP          ( 2 )
#define HOST_ISO_OUT_EP         ( 2 )
#define HOST_ISO_IN_EP          ( 2 )

#define HOST_FS_CONTROL_MPS     ( 64 )
#define HOST_FS_INT_IN_MPS      ( 64 )
#define HOST_FS_BULK_IN_MPS     ( 64 )
#define HOST_FS_BULK_OUT_MPS    ( 64 )
#define HOST_FS_ISO_OUT_MPS     ( 64 )
#define HOST_FS_ISO_IN_MPS      ( 64 )

#define ENDPOINT_TYPE_CONTROL   ( 0x00 )
#define ENDPOINT_TYPE_ISO       ( 0x01 )
#define ENDPOINT_TYPE_BULK      ( 0x02 )
#define ENDPOINT_TYPE_INT       ( 0x03 )


//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum _EN_USB_HOST_ERR_CODE
{
    EN_HOST_NONE_ERR = 0,
    EN_HOST_UNLINK_ERR,

    EN_CONTROL_WRITE_SETUP_ERR,
    EN_CONTROL_WRITE_OUT_ERR,
    EN_CONTROL_WRITE_IN_ERR,

    EN_CONTROL_READ_SETUP_ERR,
    EN_CONTROL_READ_OUT_ERR,
    EN_CONTROL_READ_IN_ERR,

    EN_BULK_READ_ERR,
    EN_BULK_WRITE_ERR,

    EN_INT_READ_ERR,
    EN_INT_WRITE_ERR,

    EN_ISO_READ_ERR,
    EN_ISO_WRITE_ERR,

} EN_USB_HOST_ERR_CODE;

typedef enum _HOST_TRANSFER_TYPE
{
    EN_HOST_CONTROL_SETUP,
    EN_HOST_CONTROL_IN,
    EN_HOST_CONTROL_OUT,
    EN_HOST_INT_IN,
    EN_HOST_INT_OUT,
    EN_HOST_BULK_IN,
    EN_HOST_BULK_OUT,
    EN_HOST_ISO_IN,
    EN_HOST_ISO_OUT

} EN_HOST_TRANSFER_TYPE;


typedef enum _USB_LINK_STATE
{
    EN_HOST_LINK,
    EN_HOST_LINK_JITTER,
    EN_HOST_DETECT,

    EN_DEVICE_DETECT,                //device detect state, pull-up & pull-down disable,DP == 1
    EN_DEVICE_LINK_JITTER,           //device link to PC in jitter state
    EN_DEVICE_UNLINK_JITTER,         //device unlink in jitter state
    EN_DEVICE_LINK,                  //device link state, pull-up & pull-down disable,DP == 0
    EN_DEVICE_ACTIVE,                //device active state,pull-down disable,pull-up ebable,SOF
    EN_DEVICE_SOF_TIMEOUT            //SOF timeout state,pull-up & pull-down disable,DP == 0

} EN_USB_LINK_STATE_T;


typedef struct _USB_CTRL_SETUP_REQUEST
{
    // D7(0:H->D;1:D->H);
    // D6~D5(0:standard ,1:cvlass,2:manufactor,3:rsv)
    // D4~D0(0:devide,1:interfacr,2:endpoint,3:other,4_31:RSV)
    uint8_t  bmRequest;
    uint8_t  bRequest;       //request code
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;

} USB_CTRL_SETUP_REQUEST, *PUSB_CTRL_SETUP_REQUEST;


typedef struct _PIPE_INFO
{
    uint8_t  EpNum;             //endpoint number
    uint8_t  EpType;            //endpoint type
    uint16_t MaxPacketSize;     //max packet size

} PIPE_INFO;




/**
 * @brief  usb host port set link state.
 * @param  u8State: Set link state.
 */
extern void rom_hw_usb_ctrl_host_port_set_link_state(uint8_t u8State);


/**
 * @brief  usb host port is link.
 * @return True: usb host port is linked.
 */
extern bool rom_hw_usb_ctrl_host_port_is_link(void);


/**
 * @brief  usb ctrl host init.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_ctrl_host_init(void);


/**
 * @brief  usb host port reset.
 */
extern  void rom_hw_usb_ctrl_host_port_reset(void);


/**
 * @brief  usb host set device addr.
 * @param  u8Address:need set device addr.
 */
extern void rom_hw_usb_ctrl_host_set_device_addr(uint8_t u8Address);


/**
 * @brief  usb host halt clear.
 */
extern void rom_hw_usb_ctrl_host_halt_clear(void);


/**
 * @brief  usb host wait trans end.
 * @param  TransferType: trans type.
 * @param  u16TimeOut: timeout, unit: ms.
 * @return 1: sucess, 0: fail.
 */
extern bool rom_hw_usb_ctrl_host_wait_transfer_end(uint8_t u8TransferType, uint16_t u16TimeOut);


/**
 * @brief  usb host control ep compalete SETUP trans.
 * @param  SetupPacket: SETUP request.
 * @param  u32TimeOut: timeout, unit: ms.
 * @return 1: sucess, 0: fail.
 */
extern bool rom_hw_usb_ctrl_host_setup_packet(USB_CTRL_SETUP_REQUEST stSetupPacket, uint32_t u32TimeOut);


/**
 * @brief  usb host perform a control write transfer or a no-data write transfer from the control endpoint,
           SETUP OUTDATA INDATA or SETUP IN.
 * @param  SetupPacket: SETUP request cmd.
 * @param  pu8Buf: Buf OUT pointer.
 * @param  u32Len: Buf OUT length.
 * @param  u32TimeOut: timeout, unit: ms.
 * @return Error code @ref EN_USB_HOST_ERR_CODE.
 */
extern EN_USB_HOST_ERR_CODE rom_hw_usb_ctrl_host_control_write(USB_CTRL_SETUP_REQUEST stSetupPacket, uint8_t* pu8Buf,
                                                               uint32_t u32Len, uint32_t u32TimeOut);


/**
 * @brief  usb host perform a control read transfer or a no-data write transfer from the control endpoint,
           SETUP OUTDATA INDATA or SETUP IN.
 * @param  SetupPacket: SETUP request cmd.
 * @param  pu8Buf: Buf OUT pointer.
 * @param  u32Len: Buf OUT length.
 * @param  u32TimeOut: timeout, unit: ms.
 * @return Error code @ref EN_USB_HOST_ERR_CODE.
 */
extern EN_USB_HOST_ERR_CODE rom_hw_usb_ctrl_host_control_read(USB_CTRL_SETUP_REQUEST SetupPacket, uint8_t* pu8Buf,
                                                              uint32_t u32Len, uint32_t u32TimeOut);


/**
 * @brief  The Host receives a packet in BULK transport.
 * @param  pstPipe: Pipe pipe pointer.
 * @param  pu8Buf: Buf OUT pointer.
 * @param  u32Len: Buf OUT length.
 * @param  u32TimeOut: timeout, unit: ms.
 * @return Error code @ref EN_USB_HOST_ERR_CODE.
 */
extern EN_USB_HOST_ERR_CODE rom_hw_usb_ctrl_host_bulk_read(PIPE_INFO* pstPipe, uint8_t* pu8Buf, uint32_t u32Len,
                                                           uint32_t* pu32TransferLen, uint16_t u32TimeOut);


/**
 * @brief  The Host send a packet in BULK transport.
 * @param  pstPipe: Pipe pipe pointer.
 * @param  pu8Buf: Buf OUT pointer.
 * @param  u32Len: Buf OUT length.
 * @param  u32TimeOut: timeout, unit: ms.
 * @return Error code @ref EN_USB_HOST_ERR_CODE.
 */
extern EN_USB_HOST_ERR_CODE rom_hw_usb_ctrl_host_bulk_write(PIPE_INFO* pstPipe, uint8_t* pu8Buf, uint32_t u32Len,
                                                            uint32_t u32TimeOut);


/**
 * @brief  The Host send a packet in interrupt transport.
 * @param  pstpstPipe: Pipe pipe pointer.
 * @param  pu8Buf: Buf OUT pointer.
 * @param  u32Len: Buf OUT length.
 * @param  u32TimeOut: timeout, unit: ms.
 * @return Error code @ref EN_USB_HOST_ERR_CODE.
 */
extern EN_USB_HOST_ERR_CODE rom_hw_usb_ctrl_host_interrupt_write(PIPE_INFO* pstPipe, uint8_t* pu8Buf, uint32_t u32Len,
                                                                 uint32_t u32TimeOut);


/**
 * @brief  The Host receives a packet in int interrupt.
 * @param  pstPipe: Pipe pipe pointer.
 * @param  pu8Buf: Buf OUT pointer.
 * @param  u32Len: Buf OUT length.
 * @param  pu32TransferLen: Transfered data length.
 * @param  u32TimeOut: timeout, unit:ms.
 * @return Error code @ref EN_USB_HOST_ERR_CODE.
 */
extern EN_USB_HOST_ERR_CODE rom_hw_usb_ctrl_host_interrupt_read(PIPE_INFO* pstPipe, uint8_t* pu8Buf, uint32_t u32Len,
                                                                uint32_t* pu32TransferLen, uint32_t u32TimeOut);


/**
 * @brief  The Host send a packet in int iso.
 * @param  pstPipe: Pipe pipe pointer.
 * @param  pu8Buf: Buf OUT pointer.
 * @param  u32Len: Buf OUT length.
 * @param  u32TimeOut: timeout, unit: ms.
 * @return Error code @ref EN_USB_HOST_ERR_CODE.
 */
extern EN_USB_HOST_ERR_CODE rom_hw_usb_ctrl_host_iso_write(PIPE_INFO* pstPipe, uint8_t* pu8Buf, uint32_t u32Len,
                                                           uint32_t u32TimeOut);


/**
 * @brief  The Host receives a packet in iso iso.
 * @param  pstPipe: Pipe pipe pointer.
 * @param  pu8Buf: Buf OUT pointer.
 * @param  u32Len: Buf OUT length.
 * @param  u32TimeOut: timeout, unit:ms.
 * @return Error code @ref EN_USB_HOST_ERR_CODE.
 */
extern EN_USB_HOST_ERR_CODE rom_hw_usb_ctrl_host_iso_read(PIPE_INFO* pstPipe, uint8_t* pu8Buf, uint32_t u32Len,
                                                          uint32_t u32TimeOut);

#ifdef __cplusplus
}
#endif

#endif /*__HW_USB_HCD_H__*/
/**
 * @}
 * @}
 */
