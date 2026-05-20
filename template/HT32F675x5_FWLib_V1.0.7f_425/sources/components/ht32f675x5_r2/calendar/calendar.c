/*************************************************************************************************************
 * @file    calendar.c
 * @version V1.2
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


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_rtc.h"
#include "type_def.h"

#include "calendar.h"

//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define LEAP_YEAR(YEAR)            ( (!((YEAR) % 400) || (((YEAR) % 100) && !((YEAR) % 4))) ? 1 : 0 )

#define CALENDAR_START_YEAR        ( 1970 )
#define CALENDAR_START_WEEK        ( 4 ) // 1970.1.1 is Thursday

#define SECONDS_PER_MINNUTE        ( 60 )
#define SECONDS_PER_HOUR           ( SECONDS_PER_MINNUTE * 60 )
#define SECONDS_PER_DAY            ( SECONDS_PER_HOUR * 24 )
#define MINNUTES_PER_HOUR          ( 60 )
#define HOURS_PER_DAY              ( 24 )
#define DAYS_PER_WEEK              ( 7 )
#define MONS_PER_YEAR              ( 12 )

#define HI_DCXO_FREQ_HZ            ( 16000000 )
#define HI_DCXO_FREQ_KHZ           ( 16000 )


//=====================================================================================================================
// LOCAL VARIABLES
//=====================================================================================================================
const static uint16_t m_u16DaysOfYear[] = { 365, 366 };
const static uint8_t  m_u8DaysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// offset @app update.
// Seconds from 1970.1.1 0:0:0 to the last update.
static uint32_t m_u32UpdateSecondsOffset = 0;

// Last time
static uint32_t m_u32LastSeconds = 0;

// The seconds from 1970.1.1 0:0:0 to now
static uint32_t m_u32CurrentSeconds = 0;

// UTC time, from 1970.1.1 0:0:0 to now, year/month/day/weekday hour:minute:second
static stCalendar_t m_stCalendar;

// Cycles of RC32K, Cycles of XO16M
static uint64_t m_u64Count32k = 0;
static uint64_t m_u64CountDcxo = 0;
static uint16_t m_u16LastFi = 0;

// Stopwatch
static uint8_t  m_u8StopwatchFlag;
static uint64_t m_u64StopwatchCount;




/**********************************************************************************************************************
 * @brief  Get cycles of high dcxo in every RC32K cycle.
 *         Need read twice to ensure the value of cycles is stable.
 * @param  None.
 * @output
 * @return u16Cycles: Cycles of high dcxo in every RC32K cycle.
 *********************************************************************************************************************/
static uint16_t calendar_get_cycles_of_dcxo ( void )
{
	 if(RTC_PDW->RTC_CLK_SRC_STA & RTC_CLK_SRC_STA_MSK)	return((HI_DCXO_FREQ_HZ * 64) / LPWR_CLOCK_32K_HZ);
	 else return rom_hw_crg_get_32k_cycles_of_dcxo_hclk();
}

/**********************************************************************************************************************
 * @brief  Get current rtc count.
 *         Read RTC count 4 times until there are two continuous counts equal.
 * @param  None.
 * @output
 * @return u64RtcCount: Rtc count.
 *********************************************************************************************************************/
static uint64_t calendar_get_rtc_count ( void )
{
    uint64_t u64RtcCount = 0;

    rom_hw_rtc_get_count64 ( &u64RtcCount );

    return u64RtcCount;
}

/**********************************************************************************************************************
 * @brief  Calculate seconds by RTC dcxo count.
 * @param  None.
 * @output
 * @return second: Current seconds from 1970.1.1 0:0:0 to now.
 *********************************************************************************************************************/
static uint32_t calendar_add_seconds_by_count ( void )
{
    uint32_t second = 0;

    second = m_u32UpdateSecondsOffset + m_u64CountDcxo / HI_DCXO_FREQ_HZ;

    return second;
}

/**********************************************************************************************************************
 * @brief  Calendar init
 * @param  pstCalendar: Init calendar time.
 * @output
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T calendar_init ( pstCalendar_t pstCalendar )
{
    if ( NULL == pstCalendar )
    {
        return ERR_PARA_ERR;
    }

    m_u32LastSeconds = 0;
    m_u32CurrentSeconds = 0;
    m_u32UpdateSecondsOffset = 0;
    m_u8StopwatchFlag = 0;

    memset ( &m_stCalendar, 0, sizeof ( stCalendar_t ) );

    calendar_period_get_time ( &m_stCalendar );
    calendar_set_utc ( pstCalendar );

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Enable or disable calendar stopwatch.
 * @param  enable: 0: turn off, others: turn on.
 * @output
 * @return None.
 *********************************************************************************************************************/
void calendar_enable_stopwatch ( uint8_t enable )
{
    m_u8StopwatchFlag = enable;
    m_u64StopwatchCount = 0;

    if ( m_u8StopwatchFlag )
    {
        calendar_period_get_rtc_counter_dcxo();
    }
}

/**********************************************************************************************************************
 * @brief  Get stopwatch time.
 * @param  None.
 * @output
 * @return time: Stopwatch time, ms.
 *********************************************************************************************************************/
uint32_t calendar_get_stopwatch_time ( void )
{
    uint32_t time;

    calendar_period_get_rtc_counter_dcxo();

    time = ( m_u64StopwatchCount / HI_DCXO_FREQ_KHZ );

    return time;
}

/**********************************************************************************************************************
 * @brief  Transform calendar time form, from second to utc
 * @param  u32Sec: Calendar time, second.
 * @output pstCalendar: Calendar utc time.
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T calendar_second_to_utc ( uint32_t u32Sec, pstCalendar_t pstCalendar )
{
    uint8_t  i = 0;
    uint32_t days;
    uint32_t seconds;

    if ( NULL == pstCalendar )
    {
        return ERR_PARA_ERR;
    }

    seconds = u32Sec + ( 8 * SECONDS_PER_HOUR );
    days = ( seconds / SECONDS_PER_DAY );

    pstCalendar->u8Hour  = ( seconds / SECONDS_PER_HOUR ) % HOURS_PER_DAY;
    pstCalendar->u8Min   = ( seconds / SECONDS_PER_MINNUTE ) % SECONDS_PER_MINNUTE;
    pstCalendar->u8Sec   = ( seconds % SECONDS_PER_MINNUTE );

    pstCalendar->u16Year = CALENDAR_START_YEAR,
                 pstCalendar->u8Mon   = 1;
    pstCalendar->u8Wday  = ( ( days + CALENDAR_START_WEEK ) % DAYS_PER_WEEK );

    while ( days >= m_u16DaysOfYear[LEAP_YEAR ( pstCalendar->u16Year )] )
    {
        days -= m_u16DaysOfYear[LEAP_YEAR ( pstCalendar->u16Year )];
        pstCalendar->u16Year ++;
    }

    while ( days >= ( m_u8DaysOfMonth[i] + ((i == 1) ? LEAP_YEAR ( pstCalendar->u16Year ) : 0) ) )
    {
        days -= ( m_u8DaysOfMonth[i] + ((i == 1) ? LEAP_YEAR ( pstCalendar->u16Year ) : 0) );
        i++;
        pstCalendar->u8Mon++;
    }

    pstCalendar->u8Day = days + 1;

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Transform calendar time form, from utc to second
 * @param  pstCalendar: Calendar utc time.
 * @output p32Seconds: Calendar time, second.
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T calendar_utc_to_second ( pstCalendar_t pstCalendar, uint32_t* p32Seconds )
{
    uint32_t seconds = 0;
    uint16_t days = 0;
    uint8_t  mounth;
    uint16_t year;

    if ( ( NULL == pstCalendar ) || ( NULL == p32Seconds ) )
    {
        return ERR_PARA_ERR;
    }

    mounth = pstCalendar->u8Mon;
    year = pstCalendar->u16Year;

    while ( mounth > 1 )
    {
        days += ( m_u8DaysOfMonth[mounth - 2] + LEAP_YEAR ( year ) );

        mounth --;
    }

    while ( year > CALENDAR_START_YEAR )
    {
        days += m_u16DaysOfYear[LEAP_YEAR ( year - 1 )];

        year --;
    }

    days += pstCalendar->u8Day - 1;

    pstCalendar->u8Wday  = ( ( days + CALENDAR_START_WEEK ) % DAYS_PER_WEEK );

    seconds += days * SECONDS_PER_DAY;
    seconds += pstCalendar->u8Hour * SECONDS_PER_HOUR;
    seconds += pstCalendar->u8Min * SECONDS_PER_MINNUTE;
    seconds += pstCalendar->u8Sec;

    seconds -= ( 8 * SECONDS_PER_HOUR );

    *p32Seconds = seconds;

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Set calendar time by utc form.
 * @param  pstCalendar: Calendar utc time.
 * @output
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T calendar_set_utc ( pstCalendar_t pstCalendar )
{
    if ( NULL == pstCalendar )
    {
        return ERR_PARA_ERR;
    }

    memcpy ( &m_stCalendar, pstCalendar, sizeof ( stCalendar_t ) );

    calendar_utc_to_second ( &m_stCalendar, &m_u32UpdateSecondsOffset );

    m_u64Count32k = calendar_get_rtc_count();
    m_u64CountDcxo = 0;

    m_u32LastSeconds = m_u32UpdateSecondsOffset;
    m_u32CurrentSeconds = m_u32UpdateSecondsOffset;

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Get calendar time by utc form.
 * @param  None.
 * @output pstCalendar: Calendar utc time.
 * @return Err status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T calendar_get_utc ( pstCalendar_t pstCalendar )
{
    if ( NULL == pstCalendar )
    {
        return ERR_PARA_ERR;
    }

    memcpy ( pstCalendar, &m_stCalendar, sizeof ( stCalendar_t ) );

    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Set calendar time by second form.
 * @param  u32Seconds: Calendar seconds time.
 * @output None.
 * @return None.
 *********************************************************************************************************************/
void calendar_set_seconds ( uint32_t u32Seconds )
{
    m_u64Count32k = calendar_get_rtc_count();
    m_u64CountDcxo = 0;

    m_u32UpdateSecondsOffset = u32Seconds;

    m_u32LastSeconds = m_u32UpdateSecondsOffset;
    m_u32CurrentSeconds = m_u32UpdateSecondsOffset;

    calendar_second_to_utc ( m_u32UpdateSecondsOffset, &m_stCalendar );
}

/**********************************************************************************************************************
 * @brief  Get calendar time by second form.
 * @param  None.
 * @output
 * @return Calendar second time.
 *********************************************************************************************************************/
uint32_t calendar_get_seconds ( void )
{
    return m_u32CurrentSeconds;
}

/**********************************************************************************************************************
 * @brief  Get RTC dcxo count periodically.
 * @param  None.
 * @output
 * @return None.
 *********************************************************************************************************************/
void calendar_period_get_rtc_counter_dcxo ( void )
{
    uint16_t u16Fi;
    uint16_t u16CurrentFi = 0;
    uint64_t u64DeltaCount32k = 0;
    uint64_t u64TempCount32k  = 0;

    u16CurrentFi = calendar_get_cycles_of_dcxo();

    if ( m_u16LastFi )
    {
        u16Fi = ( u16CurrentFi + m_u16LastFi ) / 2;
    }

    m_u16LastFi = u16CurrentFi;

    u64TempCount32k = calendar_get_rtc_count();

    if ( u64TempCount32k >= m_u64Count32k )
    {
        u64DeltaCount32k = u64TempCount32k - m_u64Count32k;
    }
    else // RTC count overflow
    {
        u64DeltaCount32k = u64TempCount32k + 0xFFFFFFFFFF - m_u64Count32k;
    }

    m_u64Count32k  = u64TempCount32k;
    m_u64CountDcxo += ( ( u64DeltaCount32k * u16Fi ) >> 6 );

    if ( m_u8StopwatchFlag )
    {
        m_u64StopwatchCount += ( ( u64DeltaCount32k * u16Fi ) >> 6 );
    }
}

/**********************************************************************************************************************
 * @brief  Get current time periodically.
 * @param  None.
 * @output pstCalendar: Current time by utc form.
 *         If pstCalendar is null, it just update current time to golbal variables
 *         m_u32CurrentSeconds and m_stCalendar.
 * @return None.
 *********************************************************************************************************************/
void calendar_period_get_time ( pstCalendar_t pstCalendar )
{
    stCalendar_t t;
    uint16_t second = 0;

    calendar_period_get_rtc_counter_dcxo();
    m_u32CurrentSeconds = calendar_add_seconds_by_count();

    memcpy ( &t, &m_stCalendar, sizeof ( stCalendar_t ) );

    if ( m_u32CurrentSeconds > m_u32LastSeconds )
    {
        second += t.u8Sec;
        second += ( m_u32CurrentSeconds - m_u32LastSeconds );

        if ( second >= SECONDS_PER_MINNUTE )
        {
            t.u8Min += second / SECONDS_PER_MINNUTE;
            t.u8Sec  = second % SECONDS_PER_MINNUTE;
            if ( t.u8Min >= MINNUTES_PER_HOUR )
            {
                t.u8Hour += t.u8Min / MINNUTES_PER_HOUR;
                t.u8Min   = t.u8Min % MINNUTES_PER_HOUR;
                if ( t.u8Hour >= HOURS_PER_DAY )
                {
                    t.u8Wday += t.u8Hour / HOURS_PER_DAY;
                    t.u8Day  += t.u8Hour / HOURS_PER_DAY;
                    t.u8Hour  = t.u8Hour % HOURS_PER_DAY;
                    if ( t.u8Day > ( m_u8DaysOfMonth[t.u8Mon - 1] + LEAP_YEAR ( t.u16Year ) ) )
                    {
                        t.u8Day = t.u8Day % ( m_u8DaysOfMonth[t.u8Mon - 1] + LEAP_YEAR ( t.u16Year ) );
                        t.u8Mon++;
                        if ( t.u8Mon > MONS_PER_YEAR )
                        {
                            t.u8Mon = 1;
                            t.u16Year++;
                        }
                    }

                    t.u8Wday %= DAYS_PER_WEEK;
                }
            }
        }
        else
        {
            t.u8Sec = second;
        }

        m_u32LastSeconds = m_u32CurrentSeconds;
        memcpy ( &m_stCalendar, &t, sizeof ( stCalendar_t ) );
    }

    if ( pstCalendar )
    {
        memcpy ( pstCalendar, &t, sizeof ( stCalendar_t ) );
    }
}


