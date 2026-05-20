/*************************************************************************************************************
 * @file    reg_usb_phy.h
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


#ifndef __REG_USB_PHY_H__
#define __REG_USB_PHY_H__

#define __OP     volatile                  /**< defines 'write pulse only' permissions   */
#define __IOP    volatile                  /**< defines 'read / write pulse' permissions */

#ifndef __IO
    #define __I     volatile const         /**< defines 'read only' permissions          */
    #define __O     volatile               /**< defines 'write only' permissions         */
    #define __IO    volatile               /**< defines 'read / write' permissions       */
    #define __ATTRIBUTE__(keyword)  keyword
    #define BITBAND
    #define AT(address)
    #define WEAK
    #define __NO_INIT__
#endif  // __IO

//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
          uint32_t RESERVED[2];

    __IOM uint32_t USB_PHY_CTRL1;          /* [0x08](RW) */
    __IOM uint32_t USB_PHY_ANA_CTRL;       /* [0x0C](RW) */
    __IOM uint32_t USB_PHY_LINE_STATUS;    /* [0x10](RW) */
    __IOM uint32_t USB_PHY_DLY_CTRL;       /* [0x14](RW) */
    
} stUSBPHY_Handle_t, *pstUSBPHY_Handle_t;


//=====================================================================================================================
// [0x08](RW) USB_PHY_CTRL1 
//=====================================================================================================================
//=============================================================================
// USB_PHY_CTRL1[0] USB_PHY_VBUS_VALID Define 
#define USB_PHY_VBUS_VALID_SHIFT           ( 0 )
#define USB_PHY_VBUS_VALID_MSK             ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_CTRL1[1] USB_PHY_VBUS_SES Define 
#define USB_PHY_VBUS_SES_SHIFT             ( 1 )
#define USB_PHY_VBUS_SES_MSK               ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_CTRL1[2] USB_PHY11_VBUS_LO Define 
#define USB_PHY11_VBUS_LO_SHIFT            ( 2 )
#define USB_PHY11_VBUS_LO_MSK              ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_CTRL1[3] USB_PHY11_CID Define 
#define USB_PHY11_CID_SHIFT                ( 3 )
#define USB_PHY11_CID_MSK                  ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_CTRL1[4] USB_PHY_TEST_MODE Define 
#define USB_PHY_TEST_MODE_SHIFT            ( 4 )
#define USB_PHY_TEST_MODE_MSK              ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_CTRL1[5] USB_USB_TEST_MODE Define 
#define USB_USB_TEST_MODE_SHIFT            ( 5 )
#define USB_USB_TEST_MODE_MSK              ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_CTRL1[6] USB_PHY11_SUSPEND_INV Define 
#define USB_PHY11_SUSPEND_INV_SHIFT        ( 6 )
#define USB_PHY11_SUSPEND_INV_MSK          ( (0x01 << 1) - 1 )


//=====================================================================================================================
// [0x0C](RW) REG_USB_ANA_PHY_CTRL 
//=====================================================================================================================
//=============================================================================
// REG_USB_ANA_PHY_CTRL[1:0] USB_PHY_DP_PULLUP Define 
#define USB_PHY_DP_PULLUP_SHIFT            ( 0 )
#define USB_PHY_DP_PULLUP_MSK              ( (0x01 << 2) - 1 )

typedef enum
{
    USB_PHY_DP_PULLUP_NONE  = 0x00,
    USB_PHY_DP_PULLUP_1_5K  = 0x01,
    USB_PHY_DP_PULLUP_2_2K  = 0x02,
    USB_PHY_DP_PULLUP_1_2K  = 0x03,

}USB_PHY_DP_PULLUP_T;

//=============================================================================
// REG_USB_ANA_PHY_CTRL[5] USB_PHY_PULLDOWN15K_DM Define 
#define USB_PHY_PULLDOWN15K_DM_SHIFT       ( 5 )
#define USB_PHY_PULLDOWN15K_DM_MSK         ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[6] USB_PHY_PULLDOWN15K_DP Define 
#define USB_PHY_PULLDOWN15K_DP_SHIFT       ( 6 )
#define USB_PHY_PULLDOWN15K_DP_MSK         ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[7] USB_PHY_SPEED Define 
#define USB_PHY_SPEED_SHIFT                ( 7 )
#define USB_PHY_SPEED_MSK                  ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[8] USB_PHY_PULLUP500K_DM Define 
#define USB_PHY_PULLUP500K_DM_SHIFT        ( 8 )
#define USB_PHY_PULLUP500K_DM_MSK          ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[9] USB_PHY_PULLUP500K_DP Define 
#define USB_PHY_PULLUP500K_DP_SHIFT        ( 9 )
#define USB_PHY_PULLUP500K_DP_MSK          ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[10] USB_PHY_EN_IDRES Define 
#define USB_PHY_EN_IDRES_SHIFT             ( 10 )
#define USB_PHY_EN_IDRES_MSK               ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[11] USB_PHY_DM27 Define 
#define USB_PHY_DM27_SHIFT                 ( 11 )
#define USB_PHY_DM27_MSK                   ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[12] USB_PHY_DP27 Define 
#define USB_PHY_DP27_SHIFT                 ( 12 )
#define USB_PHY_DP27_MSK                   ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[13] USB_PHY_PWRDN Define 
#define USB_PHY_PWRDN_SHIFT                ( 13 )
#define USB_PHY_PWRDN_MSK                  ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[14] USB_PHY_LSPD_DM Define 
#define USB_PHY_LSPD_DM_SHIFT              ( 14 )
#define USB_PHY_LSPD_DM_MSK                ( (0x01 << 1) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[17:15] SLC_SEL Define 
#define USB_PHY_SLC_SEL_SHIFT              ( 15 )
#define USB_PHY_SLC_SEL_MSK                ( (0x01 << 3) - 1 )

//=============================================================================
// REG_USB_ANA_PHY_CTRL[19:18] USB_PHY_BYP_SWC Define 
#define USB_PHY_BYP_SWC_SHIFT              ( 18 )
#define USB_PHY_BYP_SWC_MSK                ( (0x01 << 2) - 1 )
typedef enum
{
    USB_PHY_BYP_SWC_NONE  = 0x00,
    USB_PHY_BYP_SWC_0     = 0x01,
    USB_PHY_BYP_SWC_1     = 0x02,
    USB_PHY_BYP_SWC_ALL   = 0x03,
    
}USB_PHY_BYP_SWC_T;

//=============================================================================
// REG_USB_ANA_PHY_CTRL[21:20] USB_PHY_SWC Define 
#define USB_PHY_SWC_SHIFT                  ( 20 )
#define USB_PHY_SWC_MSK                    ( (0x01 << 2) - 1 )
typedef enum
{
    USB_PHY_BRANCH_SWC_NONE  = 0x00,
    USB_PHY_BRANCH_SWC_0     = 0x01,
    USB_PHY_BRANCH_SWC_1     = 0x02,
    USB_PHY_BRANCH_SWC_ALL   = 0x03,
    
}USB_PHY_BRANCH_SWC_T;

//=============================================================================
// REG_USB_ANA_PHY_CTRL[24:22] USB_PHY_RECV_IB Define 
#define USB_PHY_RECV_IB_SHIFT              ( 22 )
#define USB_PHY_RECV_IB_MSK                ( (0x01 << 2) - 1 )


//=====================================================================================================================
// [0x10](RW) USB_PHY_LINE_STATUS 
//=====================================================================================================================
//=============================================================================
// USB_PHY_LINE_STATUS[0] USB_PHY_RCV Define 
#define USB_PHY_RCV_SHIFT                  ( 0 )
#define USB_PHY_RCV_MSK                    ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_LINE_STATUS[1] USB_PHY_VM Define 
#define USB_PHY_VM_SHIFT                   ( 1 )
#define USB_PHY_VM_MSK                     ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_LINE_STATUS[1] USB_PHY_VP Define 
#define USB_PHY_VP_SHIFT                   ( 2 )
#define USB_PHY_VP_MSK                     ( (0x01 << 1) - 1 )


//=====================================================================================================================
// [0x14](RW) USB_PHY_DLY_CTRL 
//=====================================================================================================================
//=============================================================================
// USB_PHY_LINE_STATUS[3:0] USB_PHY_VPIN_DLY Define 
#define USB_PHY_VPIN_DLY_SHIFT             ( 0 )
#define USB_PHY_VPIN_DLY_MSK               ( (0x01 << 4) - 1 )

//=============================================================================
// USB_PHY_LINE_STATUS[7:4] USB_PHY_VPOUT_DLY Define 
#define USB_PHY_VPOUT_DLY_SHIFT            ( 4 )
#define USB_PHY_VPOUT_DLY_MSK              ( (0x01 << 4) - 1 )

//=============================================================================
// USB_PHY_LINE_STATUS[11:8] USB_PHY_VMIN_DLY Define 
#define USB_PHY_VMIN_DLY_SHIFT             ( 8 )
#define USB_PHY_VMIN_DLY_MSK               ( (0x01 << 4) - 1 )

//=============================================================================
// USB_PHY_LINE_STATUS[15:12] USB_PHY_VMAX_DLY Define 
#define USB_PHY_VMAX_DLY_SHIFT             ( 12 )
#define USB_PHY_VMAX_DLY_MSK               ( (0x01 << 4) - 1 )

//=============================================================================
// USB_PHY_LINE_STATUS[16] USB_PHY_VPIN_LST_MUX Define 
#define USB_PHY_VPIN_LST_MUX_SHIFT         ( 16 )
#define USB_PHY_VPIN_LST_MUX_MSK           ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_LINE_STATUS[17] USB_PHY_VPOUT_LST_MUX Define 
#define USB_PHY_VPOUT_LST_MUX_SHIFT        ( 17 )
#define USB_PHY_VPOUT_LST_MUX_MSK          ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_LINE_STATUS[18] USB_PHY_VMIN_LST_MUX Define 
#define USB_PHY_VMIN_LST_MUX_SHIFT         ( 18 )
#define USB_PHY_VMIN_LST_MUX_MSK           ( (0x01 << 1) - 1 )

//=============================================================================
// USB_PHY_LINE_STATUS[19] USB_PHY_VMAX_LST_MUX Define 
#define USB_PHY_VMAX_LST_MUX_SHIFT         ( 19 )
#define USB_PHY_VMAX_LST_MUX_MSK           ( (0x01 << 1) - 1 )




#define REG_USB_ANA_PHY_CTRL               ( *(volatile unsigned long *)(ADDR_USB_PHY_BASE+0xc) )
#define ADR_USB_ANA_PHY_CTRL                                            (ADDR_USB_PHY_BASE+0xc)
#define MASK_PHY_DP_1_5K_PULLUP            ( 0x1 )
#define MASK_PHY_DP_2_2K_PULLUP            ( 0x2 )
#define MASK_PHY_DP_1_2K_PULLUP            ( 0x3 )
#define MASK_PHY_DP_PULLUP                 ( 0x3 )
#define MASK_PHY_PULLDOWN15K_DM            ( 0x20 )
#define MASK_PHY_PULLDOWN15K_DP            ( 0x40 )
#define MASK_PHY_SPEED                     ( 0x80 )
#define MASK_PHY_PULLUP500K_DM             ( 0x100 )
#define MASK_PHY_PULLUP500K_DP             ( 0x200 )
#define MASK_PHY_EN_IDRES                  ( 0x400 )
#define MASK_PHY_DM27                      ( 0x800 )
#define MASK_PHY_DP27                      ( 0x1000 )
#define MASK_USB_PHY_PWRDN                 ( 0x2000 )
#define MASK_USB_PHY_LSPD_DM               ( 0x4000 )
#define MASK_USB_PHY_FULL_STRENGTH         ( 0x38000 )
#define BIAS_PHY_DP_PULLUP                 ( 0 )
#define BIAS_PHY_PULLDOWN15K_DM            ( 5 )
#define BIAS_PHY_PULLDOWN15K_DP            ( 6 )
#define BIAS_PHY_SPEED                     ( 7 )
#define BIAS_PHY_PULLUP500K_DM             ( 8 )
#define BIAS_PHY_PULLUP500K_DP             ( 9 )
#define BIAS_PHY_EN_IDRES                  ( 10 )
#define BIAS_PHY_DM27                      ( 11 )
#define BIAS_PHY_DP27                      ( 12 )
#define BIAS_USB_PHY_PWRDN                 ( 13 )
#define BIAS_USB_PHY_LSPD_DM               ( 14 )
#define BIAS_USB_PHY_FULL_STRENGTH         ( 15 )


#define REG_USB_CTRL1                      ( *(volatile unsigned long *)(ADDR_USB_PHY_BASE+0x8) )
#define ADR_USB_CTRL1                                                   (ADDR_USB_PHY_BASE+0x8)
#define MASK_USB_VBUS_VALID                ( 0x1 )
#define MASK_USB_VBUS_SES                  ( 0x2 )
#define MASK_USB_PHY11_VBUS_LO             ( 0x4 )
#define MASK_USB_PHY11_CID                 ( 0x8 )
#define MASK_USB_PHY_TEST_MODE             ( 0x10 )
#define MASK_USB_USB_TEST_MODE             ( 0x20 )
#define MASK_USB_PHY11_SUSPEND_INV         ( 0x40 )
#define BIAS_USB_VBUS_VALID                ( 0 )
#define BIAS_USB_VBUS_SES                  ( 1 )
#define BIAS_USB_PHY11_VBUS_LO             ( 2 )
#define BIAS_USB_PHY11_CID                 ( 3 )
#define BIAS_USB_PHY_TEST_MODE             ( 4 )
#define BIAS_USB_USB_TEST_MODE             ( 5 )
#define BIAS_USB_PHY11_SUSPEND_INV         ( 6 )

#define REG_PHY_LINE_STATUS                ( *(volatile unsigned long *)(ADDR_USB_PHY_BASE+0x10))
#define ADR_PHY_LINE_STATUS                                             (ADDR_USB_PHY_BASE+0x10)
#define MASK_USB_PHY_RCV                   ( 0x1 )
#define MASK_USB_PHY_VM                    ( 0x2 )
#define MASK_USB_PHY_VP                    ( 0x4 )
#define MASK_EXT_PHY_VM                    ( 0x8 )
#define MASK_EXT_PHY_VP                    ( 0x10 )
#define BIAS_USB_PHY_RCV                   ( 0 )
#define BIAS_USB_PHY_VM                    ( 1 )
#define BIAS_USB_PHY_VP                    ( 2 )
#define BIAS_EXT_PHY_VM                    ( 3 )
#define BIAS_EXT_PHY_VP                    ( 4 )

#define REG_USB_DLY_CTRL                   ( *(volatile unsigned long * )(ADDR_USB_PHY_BASE+0x14) )
#define ADR_USB_DLY_CTRL                                                 (ADDR_USB_PHY_BASE+0x14)
#define MASK_USB_VPIN_DLY_CFG              ( 0xF )
#define MASK_USB_VPOUT_DLY_CFG             ( 0xF0 )
#define MASK_USB_VMIN_DLY_CFG              ( 0xF00 )
#define MASK_USB_VMOUT_DLY_CFG             ( 0xF000 )
#define MASK_USB_VPIN_LST_MUX_CFG          ( 0x10000 )
#define MASK_USB_VPOUT_LST_MUX_CFG         ( 0x20000 )
#define MASK_USB_VMIN_LST_MUX_CFG          ( 0x40000 )
#define MASK_USB_VMOUT_LST_MUX_CFG         ( 0x80000 )
#define BIAS_USB_VPIN_DLY_CFG              ( 0 )
#define BIAS_USB_VPOUT_DLY_CFG             ( 4 )
#define BIAS_USB_VMIN_DLY_CFG              ( 8 )
#define BIAS_USB_VMOUT_DLY_CFG             ( 12 )
#define BIAS_USB_VPIN_LST_MUX_CFG          ( 16 )
#define BIAS_USB_VPOUT_LST_MUX_CFG         ( 17 )
#define BIAS_USB_VMIN_LST_MUX_CFG          ( 18 )
#define BIAS_USB_VMOUT_LST_MUX_CFG         ( 19 )




typedef struct _ST_USB_ANA_PHY_CTRL
{
    __IO  unsigned long PHY_DP_PULLUP      : 2; /**< 2'b11: 1.2K resistance pull up for DP
                                                     2'b10: 2.2K resistance pull up for DP */
          unsigned long                    : 3; /**< reserved */
    __IO  unsigned long PHY_PULLDOWN15K_DM : 1; /**< 1: connect DM to ground with 15K resistance  */
    __IO  unsigned long PHY_PULLDOWN15K_DP : 1; /**< 1: connect DP to ground with 15K resistance  */
    __IO  unsigned long PHY_SPEED          : 1; /**< PHY Speed, 1: full speed, 0: low speed, default "1"  */
    __IO  unsigned long PHY_PULLUP500K_DM  : 1; /**< 1: 500K resistance pull up for DM  */
    __IO  unsigned long PHY_PULLUP500K_DP  : 1; /**< 1: 500K resistance pull up for DP  */
    __IO  unsigned long PHY_EN_IDRES       : 1; /**< Enable the ID Resistors for iPhone Charging  */
    __IO  unsigned long PHY_DM27           : 1; /**< "1": Set DM27 to 2.7V
                                                     "0": Set DM27 to 2.0V */
    __IO  unsigned long PHY_DP27           : 1; /**< "1": Set DM27 to 2.7V
                                                     "0": Set DM27 to 2.0V */
    __IO  unsigned long USB_PHY_PWRDN      : 1; /**< OSC lowpower and power control
                                                     phy power down (suspend)
                                                     the default value should be "1" to guarantee the reused GPIO can be used as dig
                                                     0: PHY's suspend is controlled by USB logic controller
                                                     1: PHY's suspend is forced to be 1'b1 */
} ST_USB_ANA_PHY_CTRL;

#define SREG_USB_ANA_PHY_CTRL              (*(volatile ST_USB_ANA_PHY_CTRL *) ADR_USB_ANA_PHY_CTRL)


// USB setting, host: 7'bxxx_0111, slave: 7'bxxx_1010
typedef struct _ST_USB_CTRL1
{
    __IO  unsigned long VBUS_VALID         : 1; /**< Vbus compared to selected Vbus Valid threshold (required to be >4.4V).
                                                     1 = above the Vbus Valid threshold,
                                                     0 = below the Vbus Valid threshold. */
    __IO  unsigned long VBUS_SES           : 1; /**< Vbus compared to Session Valid threshold for a B device (required to be betwee
                                                     1 = above the Session Valid threshold,
                                                     0 = below the Session Valid threshold. */
    __IO  unsigned long PHY11_VBUS_LO      : 1; /**< Vbus compared to Session End threshold (required to be between 0.2V and 0.8V).
                                                     1 = above the Session End threshold,
                                                     0 = below the Session End threshold. */
    __IO  unsigned long PHY11_CID          : 1; /**< Connect ID, deduce by sampling the devide ID line, 1: B-byte, 0: A-byte  */
    __IO  unsigned long PHY_TEST_MODE      : 1; /**< 1: test inernal PHY  */
    __IO  unsigned long USB_TEST_MODE      : 1; /**< 1: test USB1.1 (USB IP) by external PHY  */
    __IO  unsigned long PHY11_SUSPEND_INV  : 1; /**< 1: inverter for usb output  */

} ST_USB_CTRL1;

#define SREG_USB_CTRL1                      (*(volatile ST_USB_CTRL1 *) ADR_USB_CTRL1)



// USB input line status from PHY
typedef struct _ST_PHY_LINE_STATUS
{
    __I   unsigned long USB_PHY_RCV        : 1; /**< phy_rcv may be ext_phy_rcv, phy1_rcv or phy2_rcv
                                                     controlled by gpio_usb_ex_phy11_sel, gpio_usb_sel_phy2_n_phy1 */
    __I   unsigned long USB_PHY_VM         : 1; /**< internal PHY VM status  */
    __I   unsigned long USB_PHY_VP         : 1; /**< internal PHY VP status  */
    __I   unsigned long EXT_PHY_VM         : 1; /**< external PHY VM status  */
    __I   unsigned long EXT_PHY_VP         : 1; /**< external PHY VP status  */

} ST_PHY_LINE_STATUS;

#define SREG_PHY_LINE_STATUS               (*(volatile ST_PHY_LINE_STATUS *) ADR_PHY_LINE_STATUS)


typedef struct _ST_USB_DLY_CTRL
{
    __IO  unsigned long VPIN_DLY_CFG       : 4; /**< VP input delay chain configuration  */
    __IO  unsigned long VPOUT_DLY_CFG      : 4; /**< VP output delay chain configuration  */
    __IO  unsigned long VMIN_DLY_CFG       : 4; /**< VM input delay chain configuration  */
    __IO  unsigned long VMOUT_DLY_CFG      : 4; /**< VM output delay chain configuration  */
    __IO  unsigned long VPIN_LST_MUX_CFG   : 1; /**< VP input delay mux configuration
                                                     0: vp in not through delay chain,only through last mux
                                                     1: vp in not only through delay chain,but also through last mux */
    __IO  unsigned long VPOUT_LST_MUX_CFG  : 1; /**< VP output delay mux configuration
                                                     0: vp out not through delay chain,only through last mux
                                                     1: vp out not only through delay chain,but also through last mux */
    __IO  unsigned long VMIN_LST_MUX_CFG   : 1; /**< VM input delay mux configuration
                                                     0: vm in not through delay chain,only through last mux
                                                     1: vm in not only through delay chain,but also through last mux */
    __IO  unsigned long VMOUT_LST_MUX_CFG  : 1; /**< VM output delay mux configuration
                                                     0: vm out not through delay chain,only through last mux
                                                     1: vm out not only through delay chain,but also through last mux */
} ST_USB_DLY_CTRL;

#define SREG_USB_DLY_CTRL                  (*(volatile ST_USB_DLY_CTRL *) ADR_USB_DLY_CTRL)


#endif

