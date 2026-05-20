/*************************************************************************************************************
 * @file    hal_usb.h
 * @version V1.0
 * @date    2021-02-25
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


#ifndef __HAL_USB_H__
#define __HAL_USB_H__

#ifdef __cplusplus
extern "C"{
#endif




/**
 * @brief  Enable or disable usb clock gate.
 * @param  u8Enable: 0 - disable, others - enable.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_usb_clock_enable(uint8_t u8Enable);


/**
 * @brief  Reset usb module by software reset.
 */
extern void rom_hal_usb_clock_reset(void);


/**
 * @brief  Device software connect.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_usb_device_software_connect(void);


/**
 * @brief  Device software disconnect.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_usb_device_software_disconnect(void);


/**
 * @brief  usb phy device init.
 * @param  Initialization process of usb Device PHY.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_usb_phy_device_init(void);


/**
 * @brief  usb phy host init.
 * @param  Initialization process of usb Host PHY.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_usb_phy_host_init(void);


/**
 * @brief  usb device init.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_usb_device_init(void);


/**
 * @brief  usb phy init.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_usb_host_init(void);


/**
 * @brief  usb phy test init.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_usb_phy_test_mode_init(void);




#ifdef __cplusplus
}
#endif

#endif /*__HAL_USB_H__*/

