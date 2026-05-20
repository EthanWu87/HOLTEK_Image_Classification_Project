/*************************************************************************************************************
 * @file    reg_usb_ctrl.h
 * @version V1.0
 * @date    2020-11-24
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


#ifndef __REG_USB_CTRL_H__
#define __REG_USB_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IOM uint32_t USB_CTRL_1;                  /* [0x00](RW) */
    __IOM uint32_t USB_CTRL_2;                  /* [0x04](RW) */
    __IOM uint32_t USB_CTRL_3;                  /* [0x08](RW) */
    __IOM uint32_t USB_CTRL_4;                  /* [0x0C](RW) */
    __IOM uint32_t USB_CTRL_5;                  /* [0x10](RW) */
    __IOM uint32_t USB_CTRL_6;                  /* [0x14](RW) */
    __IOM uint32_t USB_CTRL_7;                  /* [0x18](RW) */
    __IOM uint32_t USB_CTRL_8;                  /* [0x1C](RW) */

} stUSBCtrl_Handle_t, *pstUSBCtrl_Handle_t;



// usb common register
#define reg_usb_common_faddr                    ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x00))
#define reg_usb_common_power                    ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x01))
#define reg_usb_common_intrtx1                  ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x02))
#define reg_usb_common_intrtx2                  ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x03))
#define reg_usb_common_intrrx1                  ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x04))
#define reg_usb_common_intrrx2                  ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x05))
#define reg_usb_common_intrusb                  ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x06))
#define reg_usb_common_intrtxen                 ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x07))
#define reg_usb_common_intrrxen                 ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x09))
#define reg_usb_common_intrusbe                 ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x0B))
#define reg_usb_common_frame                    ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x0C))
#define reg_usb_common_frame2                   ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x0D))
#define reg_usb_common_index                    ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x0E))
#define reg_usb_common_devctl                   ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x0F))//update by elvis

// usb indexed register
#define reg_usb_indexed_csr_txmaxp              ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x10))
#define reg_usb_indexed_csr_csr0                ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x11))
#define reg_usb_indexed_csr_csr02               ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x12))
#define reg_usb_indexed_csr_txcsr1              ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x11))
#define reg_usb_indexed_csr_txcsr2              ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x12))
#define reg_usb_indexed_csr_rxmaxp              ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x13))
#define reg_usb_indexed_csr_rxcsr1              ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x14))
#define reg_usb_indexed_csr_rxcsr2              ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x15))
#define reg_usb_indexed_csr_count0              ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x16))
#define reg_usb_indexed_csr_rxcount1            ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x16))
#define reg_usb_indexed_csr_rxcount2            ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x17))
#define reg_usb_indexed_csr_host_txtype         ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x18))
#define reg_usb_indexed_csr_host_nak_limit0     ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x19))
#define reg_usb_indexed_csr_host_tx_interval    ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x19))
#define reg_usb_indexed_csr_host_rxtype         ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x1A))
#define reg_usb_indexed_csr_host_rx_interval    ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x1B))
#define reg_usb_indexed_csr_dev_config_data     ((volatile uint8_t*)(ADDR_USB_CTRL_BASE + 0x1F))


// usb endpoint fifo register
#define reg_usb_endpoint_fifo_addr              (ADDR_USB_CTRL_BASE + 0x20)
#define reg_usb_endpoint_fifo                   ((volatile uint32_t*)(reg_usb_endpoint_fifo_addr))


// reg_usb_common_power

//0x01
#define faddr_devctrl                           (1<<7)
#define faddr_addr                              (0x7F<<0)

//0x02
#define power_prw_iso_update                    (1 << 7)
#define power_prw_soft_conn                     (1 << 6)
#define power_prw_hs_enab                       (1 << 5)
#define power_prw_hs_mode                       (1 << 4)
#define power_pr_reset                          (1 << 3)
#define power_prw_resume                        (1 << 2)
#define power_prw_en_suspend_mode               (1 << 1)
#define Power_prw_EnSuspendMode                 (1 << 0)

#define Power_hrw_HSEnab                        (1 << 5)
#define Power_hr_HSMode                         (1 << 4)
#define Power_hrw_Reset                         (1 << 3)
#define Power_hrw_Resume                        (1 << 2)
#define Power_hs_SuspendMode                    (1 << 1)
#define Power_hrw_EnSuspendMode                 (1 << 0)


// reg_usb_common_intrusb
//0x06
#define IntUSB_VBusErr                          (1 << 7)
#define IntUSB_SessReq                          (1 << 6)
#define IntUSB_DisCon                           (1 << 5)
#define IntUSB_Conn                             (1 << 4)
#define IntUSB_SOF                              (1 << 3)
#define IntUSB_p_Reset                          (1 << 2)
#define IntUSB_h_Babble                         (1 << 2)
#define IntUSB_Resume                           (1 << 1)
#define IntUSB_Suspend                          (1 << 0)

//0x0B
#define IntUSBE_VBusErr                         (1 << 7)
#define IntUSBE_SessReq                         (1 << 6)
#define IntUSBE_DisCon                          (1 << 5)
#define IntUSBE_Conn                            (1 << 4)
#define IntUSBE_SOF                             (1 << 3)
#define IntUSBE_p_Reset                         (1 << 2)
#define IntUSBE_h_Babble                        (1 << 2)
#define IntUSBE_Resume                          (1 << 1)
#define IntUSBE_Suspend                         (1 << 0)


//
#define TestMode_rw_ForceHost                   (1 << 7)
#define TestMode_rw_FIFOAccess                  (1 << 6)
#define TestMode_rw_ForceFS                     (1 << 5)
#define TestMode_rw_ForceHS                     (1 << 4)
#define TestMode_rw_Packet                      (1 << 3)
#define TestMode_rw_K                           (1 << 2)
#define TestMode_rw_J                           (1 << 1)
#define TestMode_rw_SE0_NAK                     (1 << 0)

// reg_usb_common_devctl  //0x0F
#define DevCtl_r_B_Device                       (1 << 7)
#define DevCtl_r_FSDev                          (1 << 6)
#define DevCtl_r_LSDev                          (1 << 5)
#define DevCtl_r_VBus                           (3 << 3)
#define DevCtl_VBus_bSE                         (0 << 3)
#define DevCtl_VBus_aSE_bAV                     (1 << 3)
#define DevCtl_VBus_aAV_bVBus                   (2 << 3)
#define DevCtl_VBus_aVBus                       (3 << 3)
#define DevCtl_r_HostMode                       (1 << 2)
#define DevCtl_rw_HostReq                       (1 << 1)
#define DevCtl_rw_Session                       (1 << 0)



/*************************Ep0*******************/
// reg_usb_indexed_csr_csr0  0x11
#define CSR0_ps_ServicedSetupEnd                (1 << 7)
#define CSR0_ps_ServicedRxPktRdy                (1 << 6)
#define CSR0_ps_SendStall                       (1 << 5)
#define CSR0_pr_SetupEnd                        (1 << 4)
#define CSR0_ps_DataEnd                         (1 << 3)
#define CSR0_prc_SentStall                      (1 << 2)
#define CSR0_prs_TxPktRdy                       (1 << 1)
#define CSR0_pr_RxPktRdy                        (1 << 0)

#define CSR0_hrc_NAKTimeout                     (1 << 7)
#define CSR0_hrw_StatusPkt                      (1 << 6)
#define CSR0_hrw_ReqPkt                         (1 << 5)
#define CSR0_hrc_Error                          (1 << 4)
#define CSR0_hrw_SetupPkt                       (1 << 3)
#define CSR0_hrc_RxStall                        (1 << 2)
#define CSR0_hrs_TxPktRdy                       (1 << 1)
#define CSR0_hrc_RxPktRdy                       (1 << 0)

//0x12 FlushFIFO

//0x13
#define CSR0_ps_FlushFIFO                       (1 << 0)

#define CSR02_hrw_DisPing                       (1 << 3)
#define CSR02_hs_FlushFIFO                      (1 << 0)


/********************EP1-EP6***************************/
// reg_usb_indexed_csr_txcsr1  0x11
//#define   TxCSR_prc_IncompTx                  (1 << 7)
#define TxCSR_prc_Unused                        (1 << 7)
#define TxCSR_ps_ClrDataTog                     (1 << 6)
#define TxCSR_prc_SentStall                     (1 << 5)
#define TxCSR_prw_SendStall                     (1 << 4)
#define TxCSR_ps_FlushFIFO                      (1 << 3)
#define TxCSR_prc_UnderRun                      (1 << 2)
#define TxCSR_prc_FIFONotEmpty                  (1 << 1)
#define TxCSR_prs_TxPktRdy                      (1 << 0)

#define TxCSR_hrc_NAKTimeout_IncompTx           (1 << 7)
#define TxCSR_hs_ClrDataTog                     (1 << 6)
#define TxCSR_hrc_RxStall                       (1 << 5)
#define TxCSR_hs_FlushFIFO                      (1 << 3)
#define TxCSR_hrc_Error                         (1 << 2)
#define TxCSR_hrc_FIFONotEmpty                  (1 << 1)
#define TxCSR_hrs_TxPktRdy                      (1 << 0)

// reg_usb_indexed_csr_txcsr2  0x12
#define TxCSR_prw_AutoSet                       (1 << 7)
#define TxCSR_prw_ISO                           (1 << 6)
#define TxCSR_prw_Mode                          (1 << 5)
#define TxCSR_prw_DMAReqEnab                    (1 << 4)
#define TxCSR_prw_FrcDataTog                    (1 << 3)
#define TxCSR_prw_DMAReqMode                    (1 << 2)

#define TxCSR_hrw_AutoSet                       (1 << 7)
#define TxCSR_hrw_Mode                          (1 << 5)
#define TxCSR_hrw_DMAReqEnab                    (1 << 4)
#define TxCSR_hrw_FrcDataTog                    (1 << 3)
#define TxCSR_hrw_DMAReqMode                    (1 << 2)



// reg_usb_indexed_csr_rxcsr1 0x14
#define RxCSR_ps_ClrDataTog                     (1 << 7)
#define RxCSR_prc_SentStall                     (1 << 6)
#define RxCSR_prw_SendStall                     (1 << 5)
#define RxCSR_ps_FlushFIFO                      (1 << 4)
#define RxCSR_pr_DataError                      (1 << 3)
#define RxCSR_prc_OverRun                       (1 << 2)
#define RxCSR_pr_FIFOFull                       (1 << 1)
#define RxCSR_prc_RxPktRdy                      (1 << 0)

#define RxCSR_hs_ClrDataTog                     (1 << 7)
#define RxCSR_hrc_RxStall                       (1 << 6)
#define RxCSR_hrw_ReqPkt                        (1 << 5)
#define RxCSR_hs_FlushFIFO                      (1 << 4)
#define RxCSR_hrc_DataError_NAKTimeout          (1 << 3)
#define RxCSR_hrc_Error                         (1 << 2)
#define RxCSR_hr_FIFOFull                       (1 << 1)
#define RxCSR_hrc_RxPktRdy                      (1 << 0)


// reg_usb_indexed_csr_rxcsr2 0x15
#define RxCSR_prw_AutoClear                     (1 << 7)
#define RxCSR_prw_ISO                           (1 << 6)
#define RxCSR_prw_DMAReqEnab                    (1 << 5)
#define RxCSR_prw_DisNyet_pr_PIDError           (1 << 4)
#define RxCSR_prw_DMAReqMode                    (1 << 3)
#define RxCSR_prc_IncompRx                      (1 << 0)

#define RxCSR_hrw_AutoClear                     (1 << 7)
#define RxCSR_hrw_AutoReq                       (1 << 6)
#define RxCSR_hrw_DMAReqEnab                    (1 << 5)
#define RxCSR_hr_PIDError                       (1 << 4)
#define RxCSR_hrw_DMAReqMode                    (1 << 3)
#define RxCSR_hrc_IncompRx                      (1 << 0)


// reg_usb_indexed_csr_host_txtype 0x18
#define TxType_rw_Protocol                      (3 << 4)
#define TxType_Protocol_Illegal                 (0 << 4)
#define TxType_Protocol_Isochronous             (1 << 4)
#define TxType_Protocol_Bulk                    (2 << 4)
#define TxType_Protocol_Interrupt               (3 << 4)
#define TxType_rw_TargetEndpointNumber          (15 << 0)


// reg_usb_indexed_csr_host_rxtype 0x1A
#define RxType_rw_Protocol                      (3 << 4)
#define RxType_Protocol_Illegal                 (0 << 4)
#define RxType_Protocol_Isochronous             (1 << 4)
#define RxType_Protocol_Bulk                    (2 << 4)
#define RxType_Protocol_Interrupt               (3 << 4)
#define RxType_rw_TargetEndpointNumber          (15 << 0)


#define ReadUSBReg8(Addr)                       (*((volatile uint8_t*)(Addr)))
#define WriteUSBReg8(Addr, Val)                 (*((volatile uint8_t*)(Addr)) = (Val))
#define SetBitUSBReg8(Addr, mask)               ((*((volatile uint8_t*)(Addr)) |= (uint8_t)(mask)))
#define ClrBitUSBReg8(Addr, mask)               ((*((volatile uint8_t*)(Addr)) &= (uint8_t)(~mask)))



#ifdef __cplusplus
}
#endif

#endif /*__REG_USB_CTRL_H__*/



