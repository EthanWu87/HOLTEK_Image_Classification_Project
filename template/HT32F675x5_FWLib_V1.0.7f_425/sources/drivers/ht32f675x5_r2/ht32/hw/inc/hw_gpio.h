/*************************************************************************************************************
 * @file    hw_gpio.h
 * @version V1.1
 * @date    2022-01-11
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



#ifndef __HW_GPIO_H__
#define __HW_GPIO_H__


#ifdef __cplusplus
extern "C" {
#endif




/**********************************************************************************************************************
 *                                             GPIO Function
 *********************************************************************************************************************/

/**
 * @brief  Configure gpio pins.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: Which pins need to be configure.
 * @param  u32Cfg: Pin configuration.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_pin_cfg(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin, uint32_t u32Cfg);


/**
 * @brief  Initialize a GPIO.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: Which pins need to be config.
 * @param  u32Cfg: The GPIO Pin config.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_pin_init(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin, uint32_t u32Cfg);


/**
 * @brief  Config gpio input and output mode.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be config, @ref EN_GPIO_PIN_T.
 * @param  enMode: Pin input or output mode, @ref EN_GPIO_PIN_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_pin_input_output(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin,
                                                     EN_GPIO_PIN_MODE_T enMode);


/**
 * @brief  Sets or clears indicated pins output level.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be set or clear, @ref EN_GPIO_PIN_T.
 * @param  enLevel: Output level status, @ref EN_GPIO_LEVEL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_pin_output_level(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin,
                                                     EN_GPIO_LEVEL_T enLevel);


/**
 * @brief  Toggle indicated pins output level.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be toggle, @ref EN_GPIO_PIN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_toggle_pin_output_level(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin);


/**
 * @brief  Get indicated pins output status.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be get status, @ref EN_GPIO_PIN_T.
 * @param  pu32Level: Pins status, @ref EN_GPIO_LEVEL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_get_pin_output_level(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin, uint32_t* pu32Level);


/**
 * @brief  Get indicated pins input status.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be get status, @ref EN_GPIO_PIN_T.
 * @param  pu32Level: Pins status, @ref EN_GPIO_LEVEL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_get_pin_input_level(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin, uint32_t* pu32Level);


/**
 * @brief  Set indicated pin peripheral function.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be set, @ref EN_GPIO_PIN_T.
 * @param  enPID: Pin peripheral function choice, @ref EN_GPIO_PID_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_pin_pid(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin, EN_GPIO_PID_T enPID);


/**
 * @brief  Enable specific io for qspi function.
 * @param  enCh: QSPI channel, @ref EN_QSPI_FIXED_GPIO_EN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_enable_qspi_pid(EN_QSPI_FIXED_GPIO_EN_T enCh);


/**
 * @brief  Disable specific io for qspi function.
 * @param  enCh: QSPI channel, @ref EN_QSPI_FIXED_GPIO_EN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_disable_qspi_pid(EN_QSPI_FIXED_GPIO_EN_T enCh);


/**
 * @brief  Config indicated pins pull up or pull down.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be config, @ref EN_GPIO_PIN_T.
 * @param  enMode: Pin pull mode, @ref EN_GPIO_PULL_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_pin_pull_mode(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin, EN_GPIO_PULL_MODE_T enMode);


/**
 * @brief  Config indicated pins drive strength.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be config, @ref EN_GPIO_PIN_T.
 * @param  enStrength: Pin drive strength, @ref EN_GPIO_DRIVE_STRENGTH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_pin_drive_strength(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin,
                                                       EN_GPIO_DRV_STRENGTH_T enStrength);


/**
 * @brief  Set indicated pin interrupt type.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be set, @ref EN_GPIO_PIN_T.
 * @param  enCh: Interrupt handle sel, @ref EN_GPIO_INT_CH_T.
 * @param  enType: Interrupt type, @ref EN_GPIO_INT_TYPE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_pin_interrupt_type(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin,
                                                       EN_GPIO_INT_CH_T enCh, EN_GPIO_INT_TYPE_T enType);


/**
 * @brief  Get indicated pins interrupt flag(status).
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: Get indicate pins interrupt flag, @ref EN_GPIO_PIN_T.
 * @param  pu32Msk: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_get_pin_interrupt_flag(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin, uint32_t* pu32Msk);


/**
 * @brief  Clear indicated pins interrupt flag(status).
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: Indicate pins interrupt flag will be cleared, @ref EN_GPIO_PIN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_clear_pin_interrupt_flag(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin);


/**
 * @brief  Enable indicated pins interrupt.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: Which pins need to be config, @ref EN_GPIO_PIN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_enable_pin_interrupt(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin);


/**
 * @brief  Disable indicated pins interrupt.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: Which pins need to be config, @ref EN_GPIO_PIN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_disable_pin_interrupt(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin);


/**
 * @brief  Set all pins wakeup debounce.
 *         All pins share one wakeup debounce time.
 * @param  u8Time: Debounce time, 0~63.
 * @param  enUnit: Debounce unit, @ref EN_GPIO_WAKEUP_DEBOUNCE_UNIT_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_pin_wakeup_debounce(uint8_t u8Time, EN_GPIO_WAKEUP_DEBOUNCE_UNIT_T enUnit);


/**
 * @brief  Enable indicated pins wakeup function.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be enable, @ref EN_GPIO_PIN_T.
 * @param  enPol: Wakeup polarity, @ref EN_GPIO_WAKEUP_POL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_enable_pin_wakeup(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin, EN_GPIO_WAKEUP_POL_T enPol);


/**
 * @brief  Disable indicated pins wakeup function.
 * @param  pstGPIO: GPIO peripheral handle, Should be GPIOA / GPIOB.
 * @param  u32Pin: The pins which would be disable, @ref EN_GPIO_PIN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_disable_pin_wakeup(stGPIO_Handle_t* pstGPIO, uint32_t u32Pin);


/**
 * @brief  Clear all pins wakeup flag.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_clear_wakeup_flag(void);





/**********************************************************************************************************************
 *                                             GPIO SWD Function
 *********************************************************************************************************************/

/**
 * @brief  Enable m0plus or m33 swd port. If config swd port to general io, need disable swd port first.
 * @param  pstGPIO: GPIO peripheral handle, Should be SWD_M0P / SWD_M33.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_enable_swd(stGPIO_SWD_Handle_t* pstGPIO);


/**
 * @brief  Disable m0plus or m33 swd port. If config swd port to general io, need disable swd port first.
 * @param  pstGPIO: GPIO peripheral handle, Should be SWD_M0P / SWD_M33.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_disable_swd(stGPIO_SWD_Handle_t* pstGPIO);


/**
 * @brief  Config indicated pin(swdio or swclk) input or output mode.
 * @param  pstGPIO: GPIO peripheral handle, Should be SWD_M0P / SWD_M33.
 * @param  u8Pin: The pins which would be config, @ref EN_GPIO_SW_NUM_T.
 * @param  enMode: Pin input or output mode, @ref EN_GPIO_PIN_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_sw_input_output(stGPIO_SWD_Handle_t* pstGPIO, uint8_t u8Pin,
                                                    EN_GPIO_PIN_MODE_T enMode);


/**
 * @brief  Set indicated pin(swdio or swclk) output status.
 * @param  pstGPIO: GPIO peripheral handle, Should be SWD_M0P / SWD_M33.
 * @param  u8Pin: The pins which would be set or clear, @ref EN_GPIO_SW_NUM_T.
 * @param  enLevel: Output level status, @ref EN_GPIO_LEVEL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_sw_output_level(stGPIO_SWD_Handle_t* pstGPIO, uint8_t u8Pin, EN_GPIO_LEVEL_T enLevel);


/**
 * @brief  Get indicated pin(swdio or swclk) input status.
 * @param  pstGPIO: GPIO peripheral handle, Should be SWD_M0P / SWD_M33.
 * @param  u8Pin: The pins which would be get, @ref EN_GPIO_SW_NUM_T.
 * @param  pu8Level: Pin level, @ref EN_GPIO_LEVEL_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_get_sw_input_level(stGPIO_SWD_Handle_t* pstGPIO, uint8_t u8Pin, uint8_t* pu8Level);


/**
 * @brief  Config indicated pin(swdio or swclk) pull up or pull down.
 * @param  pstGPIO: GPIO peripheral handle, Should be SWD_M0P / SWD_M33.
 * @param  u8Pin: The pins which would be config, @ref EN_GPIO_SW_NUM_T.
 * @param  enMode: Pin pull mode, @ref EN_GPIO_PULL_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_sw_pull_mode(stGPIO_SWD_Handle_t* pstGPIO, uint8_t u8Pin, EN_GPIO_PULL_MODE_T enMode);


/**
 * @brief  Config indicated pin(swdio or swclk) drive strength.
 * @param  pstGPIO: GPIO peripheral handle, Should be SWD_M0P / SWD_M33.
 * @param  enPin: The pins which would be config, @ref EN_GPIO_SW_NUM_T.
 * @param  enStrength: Pin drive strength, @ref EN_GPIO_DRV_STRENGTH_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_sw_drive_strength(stGPIO_SWD_Handle_t* pstGPIO, uint8_t u8Pin,
                                                      EN_GPIO_DRV_STRENGTH_T enStrength);




/**********************************************************************************************************************
 *                                             GPIO IR Function
 *********************************************************************************************************************/

/**
 * @brief  Enable ir tx output.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_enable_ir_tx_out(void);


/**
 * @brief  Disable ir tx output.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_disable_ir_tx_out(void);


/**
 * @brief  Enable ir rx amp.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_enable_ir_rx_amp(void);


/**
 * @brief  Disable ir rx amp.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_disable_ir_rx_amp(void);


/**
 * @brief  Set resistance of R in RC filter.
 * @param  u8Rtune: R = 50K*2^(u8Rtune).
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_set_ir_rx_rtune(uint8_t u8Rtune);


/**
 * @brief  Get ir control register vlaue.
 * @param  pu32IrCtrlValue: Pointer to ir ctrl reg vlaue.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_get_ir_ctrl_value(uint32_t* pu32IrCtrlValue);




/**********************************************************************************************************************
 *                                             GPIO Others Function
 *********************************************************************************************************************/
 
/**
 * @brief  Enable ddcxo32k clock output from PB07 or(and) PB10.
 * @param  u8Io: output io, @ref EN_DCXO32K_OUT_CFG_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_enable_dcxo32k_output(uint8_t u8Io);


/**
 * @brief  Disable ddcxo32k clock output from PB07 or(and) PB10.
 * @param  u8Io: output io, @ref EN_DCXO32K_OUT_CFG_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_gpio_disable_dcxo32k_output(uint8_t u8Io);


#ifdef __cplusplus
}
#endif

#endif /* __HW_GPIO_H__ */


