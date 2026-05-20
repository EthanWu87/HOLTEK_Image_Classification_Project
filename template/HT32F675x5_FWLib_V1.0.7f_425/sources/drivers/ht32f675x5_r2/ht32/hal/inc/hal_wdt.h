/*************************************************************************************************************
 * @file    hal_wdt.h
 * @version V1.0
 * @date    2021-06-08
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



#ifndef __HAL_WDT_H__
#define __HAL_WDT_H__


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define WDT_MAX_TIME_MS                    ( 131082000 )
#define WDT_DELAY_RESET_MAX_TIME_MS        ( 2147 )




/**
 * @brief  Configure watchdog monitor time, delay time of reset and enable wdt.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @param  u32TimeMs: Monitor time, unit: ms. Max time 131082S.
 * @param  u16DelayResetTimeMs: Time of delay reset, unit: ms.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_wdt_init(stWDT_Handle_t *pstWDT, uint32_t u32TimeMs, uint16_t u16DelayResetTimeMs);


/**
 * @brief  Deinitializes the WDT Module and reset the registers.
 * @param  pstWDT: WDT handle, Should be WDT0 / WDT1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hal_wdt_deinit(stWDT_Handle_t* pstWDT);




#endif /* __HAL_WDT_H__ */


