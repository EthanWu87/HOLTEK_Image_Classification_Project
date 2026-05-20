/*************************************************************************************************************
 * @file    rtc.c
 * @version V1.1
 * @date    2026-02-24
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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "app_cfg.h"
#include "boards.h"

#include "hw_rtc.h"
#include "hw_crg.h"
#include "hw_sys_ctrl.h"
#include "hw_pmu.h"
#include "patch_hw_rtc.h"
#include "rtc.h"

static bool gbIsRtcStart = false;

/**********************************************************************************************************************
 * @brief  Start RTC.
 * @note   Need Select LPWR_CLK_DCXO_LCLK as Low Power Clock Source
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rtc_start(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint32_t u32ClkSrc;
    
    // Note:Select RTC clock source based on low power clock source
    rom_hw_crg_get_lpwr_clk_src(&u32ClkSrc);
    if(LPWR_CLK_DCXO_LCLK != u32ClkSrc)
	 {
		patch_hw_rtc_set_rtc_clk_src(EN_RTC_CLK_SRC_RC_LCLK);
	 }
	 else
	 {
		patch_hw_rtc_set_rtc_clk_src(EN_RTC_CLK_SRC_DCXO_LCLK);
	 }
	 rom_hw_rtc_set_ldo_ret_output_voltage(EN_RTC_LDO_RET_950mV);

    rom_hw_rtc_clear_count();    
    enRet = rom_hw_rtc_start();
    if (ERR_STA_OK != enRet)	return enRet;
    
    gbIsRtcStart = true;
	 // Note:This can reduce power consumption in sleep mode.
    if(LPWR_CLK_DCXO_LCLK == u32ClkSrc) rom_hw_pmu_disable_clk_output(EN_RC_LCLK_OUT_CTRL);
    
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Stop RTC.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rtc_stop(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    enRet = rom_hw_rtc_stop();
    if (ERR_STA_OK != enRet)
        return enRet;
    
    gbIsRtcStart = false;
    
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Restart RTC.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rtc_restart(void)
{
    if (gbIsRtcStart)
    {
        rom_hw_rtc_clear_count();
        return ERR_STA_OK;
    }
    
    return rtc_start();    
}

