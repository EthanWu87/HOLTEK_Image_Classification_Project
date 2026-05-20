/*************************************************************************************************************
 * @file    hal_crg.h
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



#ifndef __HAL_CRG_H__
#define __HAL_CRG_H__

#ifdef __cplusplus
extern "C"{
#endif




/**
 * @brief  Take time(us) transform to cycles of RC32K.
 * @param  u32Time: Time, unit: us.
 * @return cycles of RC32K.
 */
// extern uint32_t rom_hal_crg_time_to_32k_cycles(uint32_t u32Time);


/**
 * @brief  Take cycles of RC32K transform to time(us).
 * @param  u32Cycles: Cycles of RC32K.
 * @return Time, unit: us.
 */
extern uint32_t rom_hal_crg_32k_cycles_to_time(uint32_t u32Cycles);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_CRG_H__ */

