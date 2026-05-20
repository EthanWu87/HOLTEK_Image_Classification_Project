/*************************************************************************************************************
 * @file    hw_cache.h
 * @version V1.0
 * @date    2020-06-16
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


#ifndef __HW_CACHE_H__
#define __HW_CACHE_H__

#ifdef __cplusplus
extern "C"{
#endif


/**
 * @brief  Initialize cache.
 * @param  enEn: Enable cache or bypass, @ref EN_CACHE_ENABLE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_cache_init(EN_CACHE_ENABLE_T enEn);


/**
 * @brief  Configure cache read mode.
 * @param  EN_FLASH_BUS_MODE_T: Read mode, @ref EN_FLASH_BUS_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_cache_set_mode(EN_FLASH_BUS_MODE_T enMode);



#ifdef __cplusplus
}
#endif

#endif /* __HW_CACHE_H__ */

