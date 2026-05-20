/*************************************************************************************************************
 * @file    calendar.h
 * @version V1.0.2
 * @date    2019-01-28
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

#ifndef __CALENDAR_H__
#define __CALENDAR_H__


/*********************************************************************
 * MACROS
 */
#ifndef CAL_SUCCESS
#define CAL_SUCCESS 0
#endif

#ifndef CAL_FAILURE
#define CAL_FAILURE 1
#endif


/*********************************************************************
 * TYPEDEF
 */
typedef struct
{
    uint16_t u16Year; //1970~
    uint8_t  u8Mon;   //1~12
    uint8_t  u8Day;   //1~31
    uint8_t  u8Hour;  //0~23
    uint8_t  u8Min;   //0~59
    uint8_t  u8Sec;   //0~59
    uint8_t  u8Wday;  //0~6: Sunday~Saturday
    
} stCalendar_t, *pstCalendar_t;


/**********************************************************************************************************************
 * @brief  Calendar init
 * @param  pstCalendar: Init calendar time.
 * @output 
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
extern EN_ERR_STA_T calendar_init ( pstCalendar_t pstCalendar );


/**********************************************************************************************************************
 * @brief  Enable or disable calendar stopwatch.
 * @param  enable: 0: turn off, others: turn on.
 * @output 
 * @return None.
 *********************************************************************************************************************/
extern void calendar_enable_stopwatch ( uint8_t enable );


/**********************************************************************************************************************
 * @brief  Get stopwatch time.
 * @param  None.
 * @output 
 * @return time: Stopwatch time, ms.
 *********************************************************************************************************************/
extern uint32_t calendar_get_stopwatch_time ( void );


/**********************************************************************************************************************
 * @brief  Transform calendar time form, from second to utc
 * @param  u32Sec: Calendar time, second.
 * @output pstCalendar: Calendar utc time.
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
extern EN_ERR_STA_T calendar_second_to_utc ( uint32_t u32Sec, pstCalendar_t pstCalendar );


/**********************************************************************************************************************
 * @brief  Transform calendar time form, from utc to second 
 * @param  pstCalendar: Calendar utc time.
 * @output p32Seconds: Calendar time, second.
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
extern EN_ERR_STA_T calendar_utc_to_second ( pstCalendar_t pstCalendar, uint32_t *p32Seconds );


/**********************************************************************************************************************
 * @brief  Set calendar time by utc form. 
 * @param  pstCalendar: Calendar utc time.
 * @output 
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
extern EN_ERR_STA_T calendar_set_utc ( pstCalendar_t pstCalendar );


/**********************************************************************************************************************
 * @brief  Get calendar time by utc form. 
 * @param  None.
 * @output pstCalendar: Calendar utc time.
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
extern EN_ERR_STA_T calendar_get_utc ( pstCalendar_t pstCalendar );


/**********************************************************************************************************************
 * @brief  Set calendar time by second form. 
 * @param  u32Seconds: Calendar seconds time.
 * @output None.
 * @return None.
 *********************************************************************************************************************/
extern void calendar_set_seconds ( uint32_t u32Seconds );


/**********************************************************************************************************************
 * @brief  Get calendar time by second form. 
 * @param  None.
 * @output 
 * @return Calendar second time.
 *********************************************************************************************************************/
extern uint32_t calendar_get_seconds ( void );


/**********************************************************************************************************************
 * @brief  Get RTC dcxo count periodically.
 * @param  None.
 * @output 
 * @return None.
 *********************************************************************************************************************/
extern void calendar_period_get_rtc_counter_dcxo ( void );


/**********************************************************************************************************************
 * @brief  Get current time periodically.
 * @param  None.
 * @output pstCalendar: Current time by utc form.
 *         If pstCalendar is null, it just update current time to golbal variables 
 *         g_u32CurrentSeconds and g_stCalendar.
 * @return None.
 *********************************************************************************************************************/
extern void calendar_period_get_time ( pstCalendar_t pstCalendar );



#endif


