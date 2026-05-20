/*************************************************************************************************************
 * @file    ble_cts.h
 * @version V1.0
 * @date    2021-02-06
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
#ifndef BLE_CTS_H
#define BLE_CTS_H

#include "utility.h"

typedef struct
{
    uint8_t u8ManualTimeUpdate              : 1;
    uint8_t u8ExternalReferenceTimeUpdate   : 1;
    uint8_t u8ChangeOfTimeZone              : 1;
    uint8_t u8ChangeOfDaylightSavingTime    : 1;
}stCtsAdjustReason_t;

typedef struct
{
    uint16_t u16Year;   // 1970~
    uint8_t u8Mon;      // 1~12
    uint8_t u8Day;      // 1~31
    uint8_t u8Hour;     // 0~23
    uint8_t u8Min;      // 0~59
    uint8_t u8Sec;      // 0~59
    uint8_t u8Wday;     // 0~6: Sunday~Saturday
    uint8_t u8F256;     // 1/256 of a Second
    stCtsAdjustReason_t stAdjustReson;
}stCtsDateTime_t;

typedef struct
{
    EN_ERR_STA_T (*cts_get_time_handler)(stCtsDateTime_t *stCtsDateTime);
    EN_ERR_STA_T (*cts_set_time_handler)(const stCtsDateTime_t *stCtsDateTime);
}stCtsInit_t;


static inline uint8_t ble_cts_date_time_encode(const stCtsDateTime_t *stCtsDateTime,uint8_t *pu8Data)
{
    uint8_t u8AdjustReason = 0;
    uint16_t u16DataLen = 0;
    
    u8AdjustReason |= stCtsDateTime->stAdjustReson.u8ChangeOfDaylightSavingTime;
    u8AdjustReason |= stCtsDateTime->stAdjustReson.u8ChangeOfTimeZone;
    u8AdjustReason |= stCtsDateTime->stAdjustReson.u8ExternalReferenceTimeUpdate;
    u8AdjustReason |= stCtsDateTime->stAdjustReson.u8ManualTimeUpdate;
    
    rom_little_endian_store_16(pu8Data,0,stCtsDateTime->u16Year);
    u16DataLen += 2;
    
    pu8Data[u16DataLen++] = stCtsDateTime->u8Mon;
    pu8Data[u16DataLen++] = stCtsDateTime->u8Day;
    pu8Data[u16DataLen++] = stCtsDateTime->u8Hour;
    pu8Data[u16DataLen++] = stCtsDateTime->u8Min;
    pu8Data[u16DataLen++] = stCtsDateTime->u8Sec;
    pu8Data[u16DataLen++] = stCtsDateTime->u8Wday;
    pu8Data[u16DataLen++] = stCtsDateTime->u8F256;
    pu8Data[u16DataLen++] = u8AdjustReason;
    
    return u16DataLen;
}

static inline uint8_t ble_cts_date_time_decode(stCtsDateTime_t *stCtsDateTime,const uint8_t *pu8Data)
{
    uint16_t u16DataLen = 0;
    
    stCtsDateTime->u16Year = rom_little_endian_read_16(pu8Data,0);
    u16DataLen += 2;
    
    stCtsDateTime->u8Mon = pu8Data[u16DataLen++];
    stCtsDateTime->u8Day = pu8Data[u16DataLen++];
    stCtsDateTime->u8Hour = pu8Data[u16DataLen++];
    stCtsDateTime->u8Min = pu8Data[u16DataLen++];
    stCtsDateTime->u8Sec = pu8Data[u16DataLen++];
    stCtsDateTime->u8Wday = pu8Data[u16DataLen++];
    stCtsDateTime->u8F256 = pu8Data[u16DataLen++];
    stCtsDateTime->stAdjustReson.u8ManualTimeUpdate              = (pu8Data[u16DataLen] >> 0) & 0x01;
    stCtsDateTime->stAdjustReson.u8ExternalReferenceTimeUpdate   = (pu8Data[u16DataLen] >> 1) & 0x01;
    stCtsDateTime->stAdjustReson.u8ChangeOfTimeZone              = (pu8Data[u16DataLen] >> 2) & 0x01;
    stCtsDateTime->stAdjustReson.u8ChangeOfDaylightSavingTime    = (pu8Data[u16DataLen] >> 3) & 0x01;
    
    return ++u16DataLen;
}

/**********************************************************************************************************************
 * @brief  Current Time Service Init.
 * @param  stCtsInit: Configuration of CTS
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ble_cts_init(const stCtsInit_t *stCtsInit);

/**********************************************************************************************************************
 * @brief  Send Current Time to Client.
 * @param  u16ConnHandle: Connection Handle of Ble
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ble_cts_send_time(uint16_t u16ConnHandle);

#endif