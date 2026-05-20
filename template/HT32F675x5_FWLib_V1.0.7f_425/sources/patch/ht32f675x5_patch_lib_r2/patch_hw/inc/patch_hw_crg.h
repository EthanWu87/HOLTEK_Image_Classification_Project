/*************************************************************************************************************
 * @file    patch_hw_crg.h
 * @version V1.1
 * @date    2024-05-06
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


#ifndef __PATCH_HW_CRG_H__
#define __PATCH_HW_CRG_H__

/**
 * @brief  Select GTIM System Clock (GTIM_SCLK) division with SYS_CLK.
 * @param  enDiv: The divisor of system clock, @ref EN_GTIM_SYS_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hw_crg_set_gtim_sys_clk_divisor(EN_GTIM_SYS_CLK_DIV_T enDiv);

/**
 * @brief  Take time(us) transform to cycles of RC32K.
 * @param  u32Time: Time, unit: us
 * @return cycles of RC32K.
 */
extern uint32_t patch_hw_crg_time_to_32k_cycles(uint32_t u32TimeUs);

/**
 * @brief  Select GTIM Clock(GTIMn_CLK) Source.
 * @param  enGTIM: GTIM channel, @ref EN_CRG_GTIM_T.
 * @param  enSrc: The source of GTIM clock, @ref EN_GTIM_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hw_crg_get_gtim_clk_src(EN_CRG_GTIM_T enGTIM, uint32_t *pu32Src);

#endif /* __PATCH_HW_CRG_H__ */
