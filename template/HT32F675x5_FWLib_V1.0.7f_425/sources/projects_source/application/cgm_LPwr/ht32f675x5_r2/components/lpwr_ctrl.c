/*************************************************************************************************************
 * @file    lpwr_ctrl.c
 * @version V1.0
 * @date    2021-02-18
 * @brief   Low Power Control
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
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_cache.h"
#include "hw_crg.h"
#include "hw_efuse.h"
#include "hw_gpio.h"
#include "hw_flash.h"
#include "patch_hw_flash.h"
#include "hw_pmu.h"
#include "hw_sys_ctrl.h"
#include "hal_pmu.h"

#include "type_def.h"
#include "app_cfg.h"

#include "utility.h"
#include "lpwr_ctrl.h"
#include "app_debug.h"

/**
 * @brief  Local variables.
 */
static lpwr_ctrl_before_sleep_cb  pfnLpwrCtrlBeforeSleep = NULL;
static lpwr_ctrl_after_wakeuup_cb pfnLpwrCtrlAfterWakeup = NULL;

static EN_LPWR_MODE_SEL_T m_enLpwrMode = LPWR_MODE_ACTIVE;

#if defined(__MAIN_PROCESSOR)
/**
 * @brief  Configure flash io pull mode.
 */
static void lpwr_ctrl_cfg_flash_io(void)
{
    uint8_t u8ChipDef;
    EN_CHIP_DEF_MEM_TYPE_T enMemType;

    rom_hw_efuse_read_bytes(EFUSE_CHIP_DEFINE_ADDR, &u8ChipDef, sizeof(u8ChipDef));

    enMemType = (u8ChipDef >> EFUSE_CHIP_DEF_MEM_TYPE_SHIFT) & EFUSE_CHIP_DEF_MEM_TYPE_MSK;

    if (EX_MEM_XIP_FLASH_FIXED_IO == enMemType)
    {
        // SPI_CLK - PA12, SPI_CS - PA13, SPI_SI   - PA14
        // SPI_SO  - PA15, SPI_WP - PA16, SPI_HOLD - PA17
        rom_hw_gpio_set_pin_pull_mode(GPIOA, GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PULL_DOWN);
        rom_hw_gpio_set_pin_pull_mode(GPIOA, GPIO_PIN_13 | GPIO_PIN_16 | GPIO_PIN_17, GPIO_PULL_UP);
    }
    else if (EX_MEM_XIP_FLASH_ANY_IO == enMemType)
    {
        uint8_t io[6];
        uint8_t ioMask = EFUSE_FLASH_RESELECT_IO_MSK;
        rom_hw_efuse_read_bytes(EFUSE_FLASH_RESELECT_IO_ADDR, io, sizeof(io));

        // SPI_CLK - u8IoReuse[0], SPI_CS - u8IoReuse[1], SPI_SI   - u8IoReuse[2]
        // SPI_SO  - u8IoReuse[3], SPI_WP - u8IoReuse[4], SPI_HOLD - u8IoReuse[5]
        rom_hw_gpio_set_pin_pull_mode(GPION((io[0] & ioMask)), GPIO_PIN_N((io[0] & ioMask)), GPIO_PULL_DOWN); // SPI_CLK
        rom_hw_gpio_set_pin_pull_mode(GPION((io[1] & ioMask)), GPIO_PIN_N((io[1] & ioMask)), GPIO_PULL_UP);   // SPI_CS
        rom_hw_gpio_set_pin_pull_mode(GPION((io[2] & ioMask)), GPIO_PIN_N((io[2] & ioMask)), GPIO_PULL_DOWN); // SPI_SI
        rom_hw_gpio_set_pin_pull_mode(GPION((io[3] & ioMask)), GPIO_PIN_N((io[3] & ioMask)), GPIO_PULL_DOWN); // SPI_SO
        rom_hw_gpio_set_pin_pull_mode(GPION((io[4] & ioMask)), GPIO_PIN_N((io[4] & ioMask)), GPIO_PULL_UP);   // SPI_WP
        rom_hw_gpio_set_pin_pull_mode(GPION((io[5] & ioMask)), GPIO_PIN_N((io[5] & ioMask)), GPIO_PULL_UP); // SPI_HOLD
    }
}
#endif

/**
 * @brief  Get ble reamin sleep time.
 * @return Reamin sleep time, us.
 */
uint32_t lpwr_ctrl_get_ble_remain_sleep_time_us(void)
{
    if ((reg_ltc_slp_ind & 0x01) == 0)
    {
        return 0;
    }

    return (uint32_t)(((reg_ltc_ret_pd_slp_len - reg_ltc_slp_cnt) * (reg_crg_cali_32k_prd & 0xFFFF)) >> 10);
}

/**
 * @brief  Configure system low power mode
 * @param  enMode: System work mode, @ref EN_LPWR_MODE_SEL_T.
 * @return HW status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T lpwr_ctrl_set_low_power_mode(EN_LPWR_MODE_SEL_T enMode)
{
    if (!IS_VALID_LPWR_MODE_SEL(enMode))
    {
        return ERR_PARA_ERR;
    }

    if (LPWR_MODE_DEEPSLEEP == enMode)
    {
        rom_hw_pmu_set_low_power_mode(PWR_MODE_DEEPSLEEP);
    }
    else if (LPWR_MODE_HIBERNATION == enMode)
    {
        rom_hw_pmu_set_low_power_mode(PWR_MODE_HIBERNATION);
    }
    else
    {
        rom_hw_pmu_set_low_power_mode(PWR_MODE_SLEEP);
    }

    return ERR_STA_OK;
}

/**
 * @brief  Low Power Application Initialize
 *         Configure System Sleep Mode to PMU_SLEEP;
 *         Configure SWD Power Domain Controller(Look-Up Table)
 * @param  enMode: System work mode, @ref EN_LPWR_MODE_SEL_T.
 * @param  pfnBeforeSleepCb: Before sleep callback function.
 * @param  pfnAfterWakeupCb: After wakeup callback function.
 */
void lpwr_ctrl_init(EN_LPWR_MODE_SEL_T enMode, lpwr_ctrl_before_sleep_cb pfnBeforeSleepCb,
                    lpwr_ctrl_after_wakeuup_cb pfnAfterWakeupCb)
{
    m_enLpwrMode = enMode;

    pfnLpwrCtrlBeforeSleep = pfnBeforeSleepCb;
    pfnLpwrCtrlAfterWakeup = pfnAfterWakeupCb;

#if defined(__MAIN_PROCESSOR)
    lpwr_ctrl_cfg_flash_io();

    lpwr_ctrl_set_low_power_mode(enMode);

    rom_hw_pmu_set_wakeup_source(LUT_INDEX_MP_SWD, LUT_TRIG_ID_OTHER, LUT_TRIG_ID_MP_SWD, LUT_MP_SWD_ACT);
#else
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_CP_WFI_FLAG, 0);
    rom_hw_pmu_set_wakeup_source(LUT_INDEX_CP_SWD, LUT_TRIG_ID_OTHER, LUT_TRIG_ID_CP_SWD, LUT_CP_SWD_ACT);
#endif
}

/**
 * @brief  System goto sleep function.
 */
__RAM_FUNC void lpwr_ctrl_goto_sleep(void)
{
    uint32_t u32Primask   = 0;
#if defined(__MAIN_PROCESSOR)
    uint32_t u32SysClkSrc = 0;
    uint32_t u32Value = 0;
    uint32_t u32CPEnabled;
#endif

    if (LPWR_MODE_ACTIVE == m_enLpwrMode)
    {
        return;
    }

    u32Primask = __get_PRIMASK();
    __disable_irq();

    if (NULL != pfnLpwrCtrlBeforeSleep)
    {
        // false(0) - System can not goto sleep.
        // true(1)  - System can goto sleep.
        if (pfnLpwrCtrlBeforeSleep() != true)
        {
            __set_PRIMASK(u32Primask);
            return;
        }
    }

    switch (m_enLpwrMode)
    {
        case LPWR_MODE_IDLE:
        {
            SCB->SCR &= ~(SCB_SCR_SLEEPDEEP_Msk);
            __WFI();
            break;
        }
        case LPWR_MODE_SLEEP:
        case LPWR_MODE_DEEPSLEEP:
        case LPWR_MODE_HIBERNATION:
        {
            // If system clock is PLL64M, need wait until cp is in WFI state.
            // And then set system clock to DCXO16M.
            #if defined(__MAIN_PROCESSOR)
                rom_hw_crg_get_sys_clk_src(&u32SysClkSrc);
                rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_REMAP_ADDR, &u32CPEnabled);

                if (SYS_CLK_SRC_PLL_CLK == u32SysClkSrc)
                {
                    uint32_t u32Time  = 0;

                    if (u32CPEnabled != 0)
                    {
                        u32Time = lpwr_ctrl_get_ble_remain_sleep_time_us();
                        rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_CP_WFI_FLAG, &u32Value);

                        if ((u32Time <= DCXO_HCLK_STABLE_TIME) || (0 == u32Value))
                            break;
                    }

                    rom_hal_pmu_set_sys_clk_src(EN_SYS_CLK_DCXO16M, 2000);
                }

                if (u32CPEnabled != 0)
                {
                    rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_CP_WFI_FLAG, &u32Value);
                    if (u32Value == 0)
                        break;
                }
            #elif defined(__CO_PROCESSOR)
                rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_CP_WFI_FLAG, 1);
                patch_hw_flash_enter_deep_power_down(FLASH);
            #endif
                // CPU gets into WFI mode.
                SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
                __WFI();
            /* After wakeup, flash release from DEEP POWER DOWN state */
            #if defined(__MAIN_PROCESSOR)
                patch_hw_flash_release_deep_power_down(FLASH);

                // Reinit cache to set all cache memory miss
                rom_hw_cache_init(CACHE_ENABLE);
            #elif defined(__CO_PROCESSOR)
                patch_hw_flash_release_deep_power_down(FLASH);
                rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_CP_WFI_FLAG, 0);
            #endif
        }
        default:
            break;
    }

    if ((NULL != pfnLpwrCtrlAfterWakeup) && (LPWR_MODE_SLEEP == m_enLpwrMode))
    {
        pfnLpwrCtrlAfterWakeup();
    }

    __set_PRIMASK(u32Primask);
}
