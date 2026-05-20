/*************************************************************************************************************
 * @file    ble_wss.h
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
#ifndef WSS_SERVICE_H
#define WSS_SERVICE_H

/* WSS Feature Characteristic Definition */
#define WSS_FEATURE_SUPPORT_TIME_STAMP              (1 << 0)
#define WSS_FEATURE_SUPPORT_MULTIPLE_USER           (1 << 1)
#define WSS_FEATURE_SUPPORT_BMI                     (1 << 2)
#define WSS_FEATURE_SUPPORT_WEIGHT_MEAS_RES_TYPE_1  (1 << 3)
#define WSS_FEATURE_SUPPORT_WEIGHT_MEAS_RES_TYPE_2  (2 << 3)
#define WSS_FEATURE_SUPPORT_WEIGHT_MEAS_RES_TYPE_3  (3 << 3)
#define WSS_FEATURE_SUPPORT_WEIGHT_MEAS_RES_TYPE_4  (4 << 3)
#define WSS_FEATURE_SUPPORT_WEIGHT_MEAS_RES_TYPE_5  (5 << 3)
#define WSS_FEATURE_SUPPORT_WEIGHT_MEAS_RES_TYPE_6  (6 << 3)
#define WSS_FEATURE_SUPPORT_WEIGHT_MEAS_RES_TYPE_7  (7 << 3)
#define WSS_FEATURE_SUPPORT_HEIGHT_MEAS_RES_TYPE_1  (1 << 7)
#define WSS_FEATURE_SUPPORT_HEIGHT_MEAS_RES_TYPE_2  (2 << 7)
#define WSS_FEATURE_SUPPORT_HEIGHT_MEAS_RES_TYPE_3  (3 << 7)

/* WSS Measurement Characteristic Record Flags Definition */
#define WSS_MEAS_FLAGS_MEAS_UNIT                (0x01 << 0)
#define WSS_MEAS_FLAGS_TIME_STAMP_PRESENT       (0x01 << 1)
#define WSS_MEAS_FLAGS_USER_ID_PRESENT          (0x01 << 2)
#define WSS_MEAS_FLAGS_BMI_AND_HEIGHT_PRESENT   (0x01 << 3)

typedef struct
{
    uint16_t u16Year;
    uint8_t u8Month;
    uint8_t u8Day;
    uint8_t u8Hour;
    uint8_t u8Minute;
    uint8_t u8Second;
}stWssDateTime_t;

typedef struct
{
    uint8_t u8Flags;                /* Flags */
    uint16_t u16Weight;             /* Weight - if flags bit 0 = 0 : kilograms(resolution = 0.005) or 1 : pounds(resolution = 0.01) */
    stWssDateTime_t stTimeStamp;    /* Time Stamp */
    uint8_t u8UserId;               /* User ID (0xFF = unknown user) */
    uint16_t u16BMI;                /* Unit : 0.1kg/m2 */
    uint16_t u16Height;             /* Height - if flags bit 3 = 0 : meters(resolution = 0.001) or 1 : inches(resolution = 0.1) */
}stWssMeasRec_t;

/* WSS Global Handler */
typedef struct
{
    uint16_t u16ConnHandle;                         /* Ble Connected Handle */
    uint16_t u16SrvHandle;                          /* WSS Service Handle */
    uint16_t u16FeatureHandle;                      /* WSS Feature Handle */
    uint16_t u16MeasHandle;                         /* WSS Measurement Handle */
    uint16_t u16MeasCfgHandle;                      /* WSS Measurement Configuration Handle */
    uint32_t u32Feature;                            /* WSS Device Feature */
    void *pData;                                    /* User Data */
}stWssHandle_t __attribute__((aligned(4)));

static inline uint8_t wss_date_time_encode(const stWssDateTime_t *stWssDateTime,uint8_t *pu8Data)
{
    uint8_t u8Len = 0;
    
    if (NULL == stWssDateTime || NULL == pu8Data)
        return 0;
    
    pu8Data[u8Len++] = stWssDateTime->u16Year;
    pu8Data[u8Len++] = stWssDateTime->u16Year >> 8;
    pu8Data[u8Len++] = stWssDateTime->u8Month;
    pu8Data[u8Len++] = stWssDateTime->u8Day;
    pu8Data[u8Len++] = stWssDateTime->u8Hour;
    pu8Data[u8Len++] = stWssDateTime->u8Minute;
    pu8Data[u8Len++] = stWssDateTime->u8Second;
    
    return u8Len;
}

/**
 * @brief  Initialize Weight Scale Service.
 * @param  pstHandle: WSS Global Handle.
 * @param  eventCb: WSS Event Callback Function.WSS Event @ref EN_WSS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ble_wss_init(stWssHandle_t *pstHandle);

/**
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: WSS Global Handle.
 * @param  pstRecord: WSS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T wss_meas_send(stWssHandle_t *pstHandle,const stWssMeasRec_t *pstRecord);

#endif
