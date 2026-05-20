/*************************************************************************************************************
 * @file    ble_hts.h
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
#ifndef BLE_HTS_H
#define BLE_HTS_H

#define HTS_MEASUREMENT_FLAGS_TEMP_UINTS                (1 << 0)
#define HTS_MEASUREMENT_FLAGS_TIME_STAMP                (1 << 1)
#define HTS_MEASUREMENT_FLAGS_TEMP_TYPE                 (1 << 2)

/* HTS Event */
typedef enum
{
    EN_HTS_EVT_NONE         = 0x00,

}EN_HTS_EVT_T;

typedef struct
{
    uint16_t u16Year;
    uint8_t u8Month;
    uint8_t u8Day;
    uint8_t u8Hour;
    uint8_t u8Minute;
    uint8_t u8Second;
}stHtsDateTime_t;

typedef struct
{
    uint8_t u8Flags;                    /* Health Thermometer Measurement Flags Field */
    uint32_t u32TempMeasVal;            /* Health Thermometer Temperature Measurement Value(Unit : Celsius or Fahrenheit) */
    stHtsDateTime_t stHtsDateTime;      /* Time Stamp */
    uint8_t u8TempType;                 /* Temperature Type */
}stHtsMeasRec_t;

/* HTS Global Handler */
typedef struct
{
    void (*event_handler)(EN_HTS_EVT_T u8Event);    /* HTS Event Callback Handler */
    uint16_t u16ConnHandle;                         /* Ble Connected Handle */
    uint16_t u16SrvHandle;                          /* Health Thermometer Service Handle */
    uint16_t u16HtsMeasHandle;                      /* Health Thermometer Measurement Characteristic Handle */
    uint16_t u16HtsMeasCfgHandle;                   /* Health Thermometer Measurement Characteristic Configuration Handle */
    void *pData;                                    /* User Data */
}stHtsHandle_t __attribute__((aligned(4)));

/* HTS Event Callback Function Declaration */
typedef void (*hts_event_callback_t)(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen);

static inline uint8_t hts_date_time_encode(const stHtsDateTime_t *stHtsDateTime,uint8_t *pu8Data)
{
    uint8_t u8Len = 0;
    
    if (NULL == stHtsDateTime || NULL == pu8Data)
        return 0;
    
    pu8Data[u8Len++] = stHtsDateTime->u16Year;
    pu8Data[u8Len++] = stHtsDateTime->u16Year >> 8;
    pu8Data[u8Len++] = stHtsDateTime->u8Month;
    pu8Data[u8Len++] = stHtsDateTime->u8Day;
    pu8Data[u8Len++] = stHtsDateTime->u8Hour;
    pu8Data[u8Len++] = stHtsDateTime->u8Minute;
    pu8Data[u8Len++] = stHtsDateTime->u8Second;
    
    return u8Len;
}

/**
 * @brief  Initialize Health Thermometer Service.
 * @param  pstHandle: HTS Global Handle.
 * @param  eventCb: HTS Event Callback Function. @ref EN_HTS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ble_hts_init(stHtsHandle_t *pstHandle,hts_event_callback_t eventCb);

/**
 * @brief  Send Measurement Record by GATT Indicate.
 * @param  pstHandle: HTS Global Handle.
 * @param  pstRecord: HTS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T hts_meas_send(stHtsHandle_t *pstHandle,const stHtsMeasRec_t *pstRecord);

#endif
