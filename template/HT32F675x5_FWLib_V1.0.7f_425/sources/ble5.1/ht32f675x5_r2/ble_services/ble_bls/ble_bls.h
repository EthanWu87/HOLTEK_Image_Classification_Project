/*************************************************************************************************************
 * @file    ble_bls.h
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
#ifndef BLE_BLS_H
#define BLE_BLS_H

#define BLS_FEATURE_SUPPORTED_BODY_MOVEMENT_DETECTION           (1 << 0)
#define BLS_FEATURE_SUPPORTED_CUFF_FIT_DETECTION                (1 << 1)
#define BLS_FEATURE_SUPPORTED_IRREGULAR_PLUSE_DETECTION         (1 << 2)
#define BLS_FEATURE_SUPPORTED_PLUSE_RATE_RANGE_DETECTION        (1 << 3)
#define BLS_FEATURE_SUPPORTED_MEASUREMENT_POSITION_DETECTION    (1 << 4)
#define BLS_FEATURE_SUPPORTED_MULTIPLE_BOND                     (1 << 5)
#define BLS_FEATURE_SUPPORTED_E2E_CRC                           (1 << 6)
#define BLS_FEATURE_SUPPORTED_USER_DATA_SERVICE                 (1 << 7)
#define BLS_FEATURE_SUPPORTED_USER_FACING_TIME                  (1 << 8)

#define BLS_MEASUREMENT_FLAGS_BLOOD_PRESSURE_UINTS              (1 << 0)
#define BLS_MEASUREMENT_FLAGS_TIME_STAMP                        (1 << 1)
#define BLS_MEASUREMENT_FLAGS_PLUSE_RATE                        (1 << 2)
#define BLS_MEASUREMENT_FLAGS_USER_ID                           (1 << 3)
#define BLS_MEASUREMENT_FLAGS_MEASUREMENT_STATUS                (1 << 4)

/* BLS Event */
typedef enum
{
    EN_BLS_EVT_NONE         = 0x00,
}EN_BLS_EVT_T;

typedef struct
{
    uint16_t u16Year;
    uint8_t u8Month;
    uint8_t u8Day;
    uint8_t u8Hour;
    uint8_t u8Minute;
    uint8_t u8Second;
}stBlsDateTime_t;

typedef struct
{
    uint8_t u8Flags;                /* Blood Pressure Measurement Flags Field */
    uint16_t u16MeasSystolic;       /* Blood Pressure Measurement Compound Value - Systolic */
    uint16_t u16MeasDiastolic;      /* Blood Pressure Measurement Compound Value - Diastolic */
    uint16_t u16MeasMAP;            /* Blood Pressure Measurement Compound Value - Mean Arterial Pressure */
    stBlsDateTime_t stBlsDateTime;  /* Time Stamp */
    uint16_t u16PluseRate;          /* Pulse Rate */
    uint8_t u8UserId;               /* User ID */
    uint16_t u16MeasStatus;         /* Measurement Status */
}stBlsMeasRec_t;

/* BLS Global Handler */
typedef struct
{
    void (*event_handler)(EN_BLS_EVT_T u8Event);    /* BLS Event Callback Handler */
    uint16_t u16ConnHandle;                         /* Ble Connected Handle */
    uint16_t u16SrvHandle;                          /* Blood Pressure Service Handle */
    uint16_t u16BlsFeatureHandle;                   /* Blood Pressure Feature Characteristic Handle */
    uint16_t u16BlsMeasHandle;                      /* Blood Pressure Measurement Characteristic Handle */
    uint16_t u16BlsMeasCfgHandle;                   /* Blood Pressure Measurement Characteristic Configuration Handle */
    uint16_t u16BlsFeature;                         /* Blood Pressure Device Supported Feature */
    void *pData;                                    /* User Data */
}stBlsHandle_t __attribute__((aligned(4)));

/* BLS Event Callback Function Declaration */
typedef void (*bls_event_callback_t)(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen);

static inline uint8_t bls_date_time_encode(const stBlsDateTime_t *stBlsDateTime,uint8_t *pu8Data)
{
    uint8_t u8Len = 0;
    
    if (NULL == stBlsDateTime || NULL == pu8Data)
        return 0;
    
    pu8Data[u8Len++] = stBlsDateTime->u16Year;
    pu8Data[u8Len++] = stBlsDateTime->u16Year >> 8;
    pu8Data[u8Len++] = stBlsDateTime->u8Month;
    pu8Data[u8Len++] = stBlsDateTime->u8Day;
    pu8Data[u8Len++] = stBlsDateTime->u8Hour;
    pu8Data[u8Len++] = stBlsDateTime->u8Minute;
    pu8Data[u8Len++] = stBlsDateTime->u8Second;
    
    return u8Len;
}

/**
 * @brief  Initialize Blood Pressure Service.
 * @param  pstHandle: BLS Global Handle.
 * @param  eventCb: BLS Event Callback Function. @ref EN_BLS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ble_bls_init(stBlsHandle_t *pstHandle,bls_event_callback_t eventCb);

/**
 * @brief  Send Measurement Record by GATT Indicate.
 * @param  pstHandle: BLS Global Handle.
 * @param  pstRecord: BLS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T bls_meas_send(stBlsHandle_t *pstHandle,const stBlsMeasRec_t *pstRecord);

#endif
