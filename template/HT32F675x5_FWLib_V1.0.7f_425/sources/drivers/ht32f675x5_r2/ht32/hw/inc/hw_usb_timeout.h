/*************************************************************************************************************
 * @file    hw_usb_timeout.h
 * @version V1.0
 * @date    2021-02-07
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


#ifndef __HW_USB_TIMEOUT_H__
#define __HW_USB_TIMEOUT_H__

#ifdef __cplusplus
 extern "C" {
#endif /*__cplusplus*/


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    uint32_t    TimeOutVal;      // time out value
    uint32_t    TickValCache;    // soft timer setting value
    uint8_t     IsTimeOut;       // time out flag
    uint8_t     reserved1;
    uint8_t     reserved2;
    uint8_t     reserved3;

} stUSB_TIMER_t;




/**
 * @brief  Set time out value of softtimer.
 * @param  stUSB_TIMER_t*: timer.
 */
extern void rom_usb_set_timeout(stUSB_TIMER_t* pTimer, uint32_t timeout);


/**
 * @brief  Check whether time out.
 * @param  stUSB_TIMER_t* timer.
 * @return uint8_t: timeout return 1,
 *                  not timeout return 0.
 */
extern uint8_t rom_usb_is_timeout(stUSB_TIMER_t* pTimer);


/**
 * @brief  Wait us.
 * @param  uint32_t:u32Us.
 */
extern void rom_usb_wait_us(uint32_t u32Us);


/**
 * @brief  Wait ms.
 * @param  uint32_t:u32Ms.
 */
extern void rom_usb_wait_ms(uint32_t u32Ms);


/**
 * @brief  Get indicate timer past time.
 * @param  stUSB_TIMER_t* timer.
 * @return uint32_t: Past time.
 */
extern uint32_t rom_usb_get_past_time(stUSB_TIMER_t* pTimer);



#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__HW_USB_TIMEOUT_H__*/

