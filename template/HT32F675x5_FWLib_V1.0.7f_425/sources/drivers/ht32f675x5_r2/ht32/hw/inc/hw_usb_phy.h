/*************************************************************************************************************
 * @file    hw_usb_phy.h
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


#ifndef __HW_USB_PHY_H__
#define __HW_USB_PHY_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */




/**
 * @brief  Get DP level.
 * @return uint8_t: 1:DP higt level,0:DP low level.
 */
extern uint8_t rom_hw_usb_phy_get_dp(void);


/**
 * @brief  Get DM level.
 * @return uint8_t: 1-DM high level-DM low level.
 */
extern uint8_t rom_hw_usb_phy_get_dm(void);


/**
 * @brief  phy_rcv may be ext_phy_rcv, phy1_rcv or phy2_rcv.
 * @return  0: gpio_usb_ex_phy11_sel, 1: gpio_usb_sel_phy2_n_phy1.
 */
extern uint8_t rom_hw_usb_phy_phy_rcv(void);


/**
 * @brief  enable Port DP pullup resistor.
 * @param  dp Pull-up resistance value. @ref USB_PHY_DP_PULLUP_T.
 * @return HW status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_phy_enable_dp_pullup(USB_PHY_DP_PULLUP_T enRes);


/**
 * @brief  disable Port DP pullup resistor.
 */
extern void rom_hw_usb_phy_disable_dp_pullup(void);


/**
 * @brief  Enable Port DM 15K pull-down resistor.
 */
extern void rom_hw_usb_phy_enable_pulldown_dm_15K(void);


/**
 * @brief  Disable Port DM 15K pull-down resistor.
 */
extern void rom_hw_usb_phy_disable_pulldown_dm_15K(void);


/**
 * @brief  Get Port DP 15K pull-down resistor.
 * @return uint8_t: 1-enable, 0-disable.
 */
extern uint8_t rom_hw_usb_phy_get_pulldown_dp_15k_state(void);


/**
 * @brief  Enable Port DM 15K pull-down resistor.
 */
extern void rom_hw_usb_phy_enable_pulldown_dp_15K(void);


/**
 * @brief  Disable Port DP 15K pull-down resistor.
 */
extern void rom_hw_usb_phy_disable_pulldown_dp_15K(void);


/**
 * @brief  enable Port DM 500K pull-up resistor.
 */
extern void rom_hw_usb_phy_enable_pullup_dm_500K(void);


/**
 * @brief  disable Port DM 500K pull-up resistor.
 */
extern void rom_hw_usb_phy_disable_pullup_dm_500K(void);


/**
 * @brief  enable Port DP 500K pull-up resistor.
 */
extern void rom_hw_usb_phy_enable_pullup_dp_500K(void);


/**
 * @brief  disable Port DP 500K pull-up resistor.
 */
extern void rom_hw_usb_phy_disable_pullup_dp_500K(void);


/**
 * @brief  Set port full speed.
 */
extern void rom_hw_usb_phy_set_full_speed(void);


/**
 * @brief  Set Port low speed.
 */
extern void rom_hw_usb_phy_set_low_speed(void);


/**
 * @brief  Set Port dp27.
 * @param  u8Enable: 1 - Set DP27 to 2.7V, 0 - Set DP27 to 2.0V.
 */
extern void rom_hw_usb_phy_dp27_enable(uint8_t u8Enable);


/**
 * @brief  Set Port dm27.
 * @param  u8Enable: 1 - Set DM27 to 2.7V, 0 - Set DM27 to 2.0V.
 */
extern void rom_hw_usb_phy_dm27_enable(uint8_t u8Enable);


/**
 * @brief  OSC lowpower and power control, phy power down (suspend) the default value should be "1" to
 *         guarantee the reused GPIO can be used as digital pad by default.
 * @param  u8Vaild: 0: PHY's suspend is controlled by USB logic controller.
 *                  1: PHY's suspend is forced to be 1'b1.
 */
extern void rom_hw_usb_phy_pwrdn_set(uint8_t u8Vaild);


/**
 * @brief  Vbus get compared to Session End threshold (required to be between 0.2V and 0.8V).
 * @return 0:PHY's suspend is controlled by USB logic controller. 1: PHY's suspend is forced to be 1'b1.
 */
extern uint8_t rom_hw_usb_phy_pwrdn_get(void);


/**
 * @brief  Set Port lspd.
 * @param  u8Enable: 1: set DM27 to 2.7V, 0: Set DM27 to 2.0V
 */
extern void rom_hw_usb_phy_lspd_dm_enable(uint8_t u8Enable);


/**
 * @brief  usb speed full drives strength.
 * @param  u8Stength: 0 - 7, The higher the value, the greater the driving power.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_phy_speed_full_drive_strength(uint8_t u8Strength);


/**
 * @brief  usb bypass slew rate controlling of each branch.
 * @param  enBypSwc：bypass slew rate controlling of each branch.@ref USB_PHY_BYP_SWC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_phy_set_bypass_swicth(USB_PHY_BYP_SWC_T enBypSwc);


/**
 * @brief  usb drive branch select in each slice,drv branch select = 1+SWC.
 * @param  enSel: drive branch select in each slice.drv branch select = 1+SWC. @ref USB_PHY_BRANCH_SWC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_phy_drv_branch_swicth(USB_PHY_BRANCH_SWC_T enSel);


/**
 * @brief  usb receiver bias current select.
 * @param  u8Sel: receiver bias current select.range[0-3].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_phy_recv_bias_current_selet(uint8_t u8Sel);


/**
 * @brief  Vbus compared to selected Vbus Valid threshold (required to be >4.4V).
 * @param  boolValid: 1 - above the Vbus Valid threshold, 0 - below the Vbus Valid threshold.
 */
extern void rom_hw_usb_phy_set_ctrl_vbus_vaild(bool bValid);


/**
 * @brief  Vbus compared to Session Valid threshold for a B device (required to be between 0.8V and 4V).
 * @param  boolValid: 1 - above the Session Valid threshold, 0 - below the Session Valid threshold.
 */
extern void rom_hw_usb_phy_set_ctrl_vbus_ses(bool bValid);


/**
 * @brief  Vbus compared to Session End threshold (required to be between 0.2V and 0.8V).
 * @param  boolValid: 1 - above the Session End threshold, 0 - below the Session End threshold.
 */
extern void rom_hw_usb_phy_set_ctrl_phy11_vbus_lo(bool bThr);


/**
 * @brief  Connect ID, deduce by sampling the devide ID line.
 * @param  bType: 1: B-byte, 0: A-byte.
 */
extern void rom_hw_usb_phy_ctrl_phy11_cid(bool bType);


/**
 * @brief  Set phy test mode set.
 * @param  u8Enable: 1: enable phy test mode, 0: disable phy test mode.
 */
extern void rom_hw_usb_phy_test_mode_set_enable(uint8_t u8Enable);


/**
 * @brief  Set usb test mode set.
 * @param  u8Enable: 1: enable usb test mode, 0: disable usb test mode.
 */
extern void rom_hw_usb_phy_test_mode_set(uint8_t u8Enable);


/**
 * @brief  inverter for otg output.
 * @param  u8Enable: 1:enable inverter for otg output,0:disable inverter for otg output.
 */
extern void rom_hw_usb_phy11_set_suspend_inverter(uint8_t u8Enable);


/**
 * @brief  phy vm out delay.
 * @param  u8Delay:u8Delay:Differential signal controller to physical layer VM out delay time,range [0-15],default is 0.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_phy_vmout_dly_cfg(uint8_t u8Delay);


/**
 * @brief  phy vm out delay enable.
 * @param  u8Delay: 0 ~ 15.
 */
extern void rom_hw_usb_phy_vmout_mux_cfg_enable(void);


/**
 * @brief  phy vm out delay disable.
 */
extern void rom_hw_usb_phy_vmout_mux_cfg_disable(void);


/**
 * @brief  phy vp out delay.
 * @param  u8Delay:Differential signal controller to physical layer VP out delay time,range [0-15],default is 0.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_phy_vpout_dly_cfg(uint8_t u8Delay);


/**
 * @brief phy vp out delay enable.
 */
extern void rom_hw_usb_phy_vpout_mux_cfg_enable(void);


/**
 * @brief  phy vp out delay disable.
 */
extern void rom_hw_usb_phy_vpout_mux_cfg_disable(void);


/**
 * @brief  phy vp out delay config.
 * @param  u8Delay:Differential signal controller to physical layer VM in delay time,range [0-15],default is 0.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_phy_vmin_dly_cfg(uint8_t u8Delay);


/**
 * @brief  phy vp out delay enable.
 */
extern void rom_hw_usb_phy_vmin_mux_cfg_enable(void);


/**
 * @brief  phy vp out delay disable.
 */
extern void rom_hw_usb_phy_vmin_mux_cfg_disable(void);


/**
 * @brief  phy vp in delay config.
 * @param  u8Delay:Differential signal controller to physical layer VP in delay time,range [0-15],default is 0.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_usb_phy_vpin_dly_cfg(uint8_t u8Delay);


/**
 * @brief phy vp in delay config enable.
 */
extern void rom_hw_usb_phy_vpin_mux_cfg_enable(void);


/**
 * @brief phy vp in delay config disable.
 */
extern void rom_hw_usb_phy_vpin_mux_cfg_disable(void);


/**
 * @brief usb phy register reset.
 */
extern void rom_hw_usb_phy_reset_register(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__HW_USB_PHY_H__*/

/**
 * @}
 * @}
 */
