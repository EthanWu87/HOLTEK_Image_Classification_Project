/*************************************************************************************************************
 * @file    patch_hal_pmu.h
 * @version V1.1
 * @date    2023-07-01
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


#ifndef __PATCH_HAL_PMU_H__
#define __PATCH_HAL_PMU_H__

/**
 * @brief  Set part of RAM_SIZE_KBYTE_MAX KB ram or all of them to retention.
 * @param  u16RamSize: Size of ram which will keep retention, unit: KB.
 *         u16RamSize >= 0 && u16RamSize <= 256.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hal_pmu_set_sram_ret(uint16_t u16RamSizeKB);

/**
 * @brief  Select System Clock(SYS_HCLK) Source.
 * @param  enSrc: System clock source selection, @ref EN_SYS_CLK_SRC_SEL_T.
 * @param  enFreq: The crystal frequency, @ref EN_DCXO_HCLK_FREQ_T.
 * @param  u16TimeUs: It means the stabilization time of crystal. Unit: us.
 *                    If system clock is @EN_SYS_CLK_RC16M, it means no impact.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hal_pmu_set_sys_clk_src(EN_SYS_CLK_SRC_SEL_T enSrc, EN_DCXO_HCLK_FREQ_T enFreq,
                                                  uint16_t u16TimeUs);

#endif /* __PATCH_HAL_PMU_H__ */
