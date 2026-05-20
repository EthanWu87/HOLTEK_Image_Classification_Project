/*************************************************************************************************************
 * @file    lpwr_ctrl.h
 * @version V1.0
 * @date    2021-02-18
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


#ifndef __LPWR_CTRL_H__
#define __LPWR_CTRL_H__

/**
 * @brief  PMU LUT Configuration.
 */
#define LUT_INDEX_CP_SWD (0)
#define LUT_INDEX_MP_SWD (1)

#define LUT_CP_SWD_ACT   (LUT_ACT_PD_SYS_ON | LUT_ACT_CP_IRQ_EN)
#define LUT_MP_SWD_ACT   (LUT_ACT_PD_SYS_ON | LUT_ACT_MP_IRQ_EN)

/**
 * @brief  Low power control callback functions definition.
 */
typedef bool (*lpwr_ctrl_before_sleep_cb)(void);
typedef void (*lpwr_ctrl_after_wakeuup_cb)(void);

typedef enum
{
    LPWR_MODE_ACTIVE      = 0x00,
    LPWR_MODE_IDLE        = 0x01,
    LPWR_MODE_SLEEP       = 0x02, /* SRAM keep retention, system clock will power down. */
    LPWR_MODE_DEEPSLEEP   = 0x03, /* SRAM will power down, LCLK clock will keep working(shutdown with 32K). */
    LPWR_MODE_HIBERNATION = 0x04, /* SRAM will power down, LCLK clock will turn off(shutdown without 32K). */

} EN_LPWR_MODE_SEL_T;

#define IS_VALID_LPWR_MODE_SEL(SEL) ((SEL) <= LPWR_MODE_HIBERNATION)

/**
 * @brief  Get ble reamin sleep time.
 * @return Reamin sleep time, us.
 */
extern uint32_t lpwr_ctrl_get_ble_remain_sleep_time_us(void);

/**
 * @brief  Configure system low power mode
 * @param  enMode: System work mode, @ref EN_LPWR_MODE_SEL_T.
 * @return
 */
extern EN_ERR_STA_T lpwr_ctrl_set_low_power_mode(EN_LPWR_MODE_SEL_T enMode);

/**
 * @brief  Low Power Application Initialize
 *         Configure System Sleep Mode to PMU_SLEEP;
 *         Configure SWD Power Domain Controller(Look-Up Table)
 * @param  enMode: System work mode, @ref EN_LPWR_MODE_SEL_T.
 * @param  pfnBeforeSleepCb: Before sleep callback function.
 * @param  pfnAfterWakeupCb: After wakeup callback function.
 */
extern void lpwr_ctrl_init(EN_LPWR_MODE_SEL_T enMode, lpwr_ctrl_before_sleep_cb pfnBeforeSleepCb,
                           lpwr_ctrl_after_wakeuup_cb pfnAfterWakeupCb);

/**
 * @brief  System goto sleep function.
 */
extern void lpwr_ctrl_goto_sleep(void);

#endif /* __LPWR_CTRL_H__ */
