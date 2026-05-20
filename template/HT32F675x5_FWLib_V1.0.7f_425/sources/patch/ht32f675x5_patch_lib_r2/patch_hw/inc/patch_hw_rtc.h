/*************************************************************************************************************
 * @file    patch_hw_rtc.h
 * @version V1.0
 * @date    2023-05-24
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


#ifndef __PATCH_HW_RTC_H__
#define __PATCH_HW_RTC_H__

/**
 * @brief  Select RTC_CLK Clock Source.
 * @param  enSrc: rtc clock source selection. @ref EN_RTC_CLK_SRC_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hw_rtc_set_rtc_clk_src(EN_RTC_CLK_SRC_T enSrc);

#endif /* __PATCH_HW_CRG_H__ */
