/*************************************************************************************************************
 * @file    hw_talos.h
 * @version V1.0 
 * @date    2020-01-03
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


#ifdef _HW_TALOS_H_
#define _HW_TALOS_H_

//=====================================================================================================================

typedef enum
{
    MAIN_FREQ_1MHZ  = 0x00,
    MAIN_FREQ_2MHZ  = 0x01,
    MAIN_FREQ_4MHZ  = 0x02,
    MAIN_FREQ_8MHZ  = 0x03,
    MAIN_FREQ_16MHZ = 0x04,
    MAIN_FREQ_32MHZ = 0x05,
    MAIN_FREQ_48MHZ = 0x06,
    MAIN_FREQ_NUM   = 0x07,
} EN_MAIN_FREQ_T;


/**********************************************************************************************************************
* @brief  This function configures the source of the time base. 
*         The time source is configured  to have 1ms time base with a dedicated Tick interrupt priority.
* @note   This function is called  automatically at the beginning of program after
*         reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig(). 
* @note   In the default implementation, SysTick timer is the source of time base. 
*         It is used to generate interrupts at regular time intervals. 
*         Care must be taken if HAL_Delay() is called from a peripheral ISR process, 
*         The the SysTick interrupt must have higher priority (numerically lower) 
*          than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
*          The function is declared as __Weak   to be overwritten  in case of other
*          implementation user file.
* @input param
*
* @param  - u32TickPriority : 
* @output 
* @return   @ref EN_HAL_STA_T
/**********************************************************************************************************************/
extern EN_HW_STA_T hw_init_tick( uint32_t u32Priority );


/**********************************************************************************************************
* @brief  This function configures the Flash prefetch, 
*        Configures time base source, NVIC and Low level hardware
* @note   This function is called  automatically at the beginning of program after
*         reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig(). 
* @note   This function is called at the beginning of program after reset and before 
*         the clock configuration
* @note   The time base configuration is based on MSI clock when exiting from Reset.
*         Once done, time base tick start incrementing.
*        In the default implementation,Systick is used as source of time base.
*        the tick variable is incremented each 1ms in its ISR.
* @input param
*
* @output 
* @return   @ref EN_HAL_STA_T
*********************************************************************************************************/
extern EN_HW_STA_T hw_sys_config_clock( void );


/**********************************************************************************************************
* @brief  This function configures the Flash prefetch, 
*        Configures time base source, NVIC and Low level hardware
* @note   This function is called  automatically at the beginning of program after
*         reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig(). 
* @note   This function is called at the beginning of program after reset and before 
*         the clock configuration
* @note   The time base configuration is based on MSI clock when exiting from Reset.
*         Once done, time base tick start incrementing.
*        In the default implementation,Systick is used as source of time base.
*        the tick variable is incremented each 1ms in its ISR.
* @input param
*
* @output 
* @return   @ref EN_HAL_STA_T
*********************************************************************************************************/
extern EN_HW_STA_T hw_switch_main_freq( EN_MAIN_FREQ_T enFreq );


/**********************************************************************************************************
* @brief  This function configures the Flash prefetch, 
*        Configures time base source, NVIC and Low level hardware
* @note   This function is called  automatically at the beginning of program after
*         reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig(). 
* @note   This function is called at the beginning of program after reset and before 
*         the clock configuration
* @note   The time base configuration is based on MSI clock when exiting from Reset.
*         Once done, time base tick start incrementing.
*        In the default implementation,Systick is used as source of time base.
*        the tick variable is incremented each 1ms in its ISR.
* @input param
*
* @output 
* @return   @ref EN_HAL_STA_T
*********************************************************************************************************/
extern EN_HW_STA_T hw_init( void );


/**********************************************************************************************************
* @brief This function de-Initializes common part of the HAL and stops the source
*        of time base.
* @note This function is optional.
* @retval HAL status
***********************************************************************************************************/
extern EN_HW_STA_T hw_deinit( void );

/**********************************************************************************************************
* @brief This function is called to increment  a global variable "uwTick"
*        used as application time base.
* @note In the default implementation, this variable is incremented each 1ms
*       in Systick ISR.
* @note This function is declared as __weak to be overwritten in case of other 
*      implementations in user file.
* @retval None
***********************************************************************************************************/
extern void hw_inc_tick( void );



/**********************************************************************************************************
* @brief Provides a tick value in millisecond.
* @note This function is declared as __weak to be overwritten in case of other 
*       implementations in user file.
* @retval tick value
* @retval None
***********************************************************************************************************/
extern uint32_t hw_get_current_freq_hz( void );


/**********************************************************************************************************
* @brief Provides a tick value in millisecond.
* @note This function is declared as __weak to be overwritten in case of other 
*       implementations in user file.
* @retval tick value
* @retval None
***********************************************************************************************************/
extern uint32_t hw_get_current_freq_khz( void );


/**********************************************************************************************************
* @brief Provides a tick value in millisecond.
* @note This function is declared as __weak to be overwritten in case of other 
*       implementations in user file.
* @retval tick value
* @retval None
***********************************************************************************************************/
extern uint32_t hw_get_current_freq_mhz( void );


/**********************************************************************************************************
* @brief Provides a tick value in millisecond.
* @note This function is declared as __weak to be overwritten in case of other 
*       implementations in user file.
* @retval tick value
* @retval None
***********************************************************************************************************/
extern uint32_t hw_get_tick( void );


/**********************************************************************************************************
* @brief This function provides accurate delay (in milliseconds) based 
*        on variable incremented.
* @note In the default implementation , SysTick timer is the source of time base.
*       It is used to generate interrupts at regular time intervals where uwTick
*       is incremented.
* @note ThiS function is declared as __weak to be overwritten in case of other
*       implementations in user file.
* @param Delay: specifies the delay time length, in milliseconds.
* @retval None
***********************************************************************************************************/
extern void hw_tick_delay( uint32_t u32Delay );


/**********************************************************************************************************
* @brief Suspend Tick increment.
* @note In the default implementation , SysTick timer is the source of time base. It is
*       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
*       is called, the the SysTick interrupt will be disabled and so Tick increment 
*       is suspended.
* @note This function is declared as __weak to be overwritten in case of other
*       implementations in user file.
* @retval None
***********************************************************************************************************/
extern void hw_suspend_tick( void );


/**********************************************************************************************************
* @brief Resume Tick increment.
* @note In the default implementation , SysTick timer is the source of time base. It is
*       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
*       is called, the the SysTick interrupt will be enabled and so Tick increment 
*       is resumed.
* @note This function is declared as __weak to be overwritten in case of other
*       implementations in user file.
* @retval None
***********************************************************************************************************/
extern void hw_resume_tick( void );


/**********************************************************************************************************
* @brief Returns the hw revision
* @retval version: 0xXYZR (8bits for each decimal, R for RC)
***********************************************************************************************************/
extern uint32_t hw_get_hw_version( void );


/**********************************************************************************************************
* @brief Returns the device revision identifier.
* @retval Device revision identifier
***********************************************************************************************************/
extern uint32_t hw_get_revision_id( void );

/**********************************************************************************************************
* @brief Returns the device revision identifier.
* @retval Device revision identifier
***********************************************************************************************************/
extern uint32_t hw_get_device_id( void );

