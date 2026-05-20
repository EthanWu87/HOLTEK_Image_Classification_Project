/*************************************************************************************************************
 * @file    ble_gls.h
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
#ifndef GLS_SERVICE_H
#define GLS_SERVICE_H

#define GLS_MEAS_COMMUNICATION_INTERAL_DEFAULT          (0x01)  /* 1 Minute */

/* GLS Event */
typedef enum
{
    EN_GLS_EVT_RACP_REPORT_RECORDS              = 0x00,
    EN_GLS_EVT_RACP_REPORT_NUM_OF_RECORDS       = 0x01,
    EN_GLS_EVT_RACP_DELETE_STORED_RECORDS       = 0x02,
}EN_GLS_EVT_T;

/* GLS Feature Characteristic Definition */
#define GLS_FEATURE_SUPPORT_LOW_BATTERY_DETECTION                   (0x01 << 0)
#define GLS_FEATURE_SUPPORT_SENSOR_MALFUNCTION_DETECTION            (0x01 << 1)
#define GLS_FEATURE_SUPPORT_SENSOR_SAMPLE_SIZE                      (0x01 << 2)
#define GLS_FEATURE_SUPPORT_SENSOR_STRIP_INSERTION_ERROR_DETECTION  (0x01 << 3)
#define GLS_FEATURE_SUPPORT_SENSOR_STRIP_TYPE_ERROR_DETECTION       (0x01 << 4)
#define GLS_FEATURE_SUPPORT_SENSOR_RESULT_HIGH_LOW_DETECTION        (0x01 << 5)
#define GLS_FEATURE_SUPPORT_SENSOR_TEMPERATURE_HIGH_LOW_DETECTION   (0x01 << 6)
#define GLS_FEATURE_SUPPORT_SENSOR_READ_INTERRUPT_DETECTION         (0x01 << 7)
#define GLS_FEATURE_SUPPORT_GENERAL_DEVICE_FAULT                    (0x01 << 8)
#define GLS_FEATURE_SUPPORT_TIME_FAULT                              (0x01 << 9)
#define GLS_FEATURE_SUPPORT_MULTIPLE_BOND                           (0x01 << 10)

/* GLS Measurement Characteristic Record Flags Definition */
#define GLS_MEAS_FLAGS_TIME_OFFSET                                      (0x01 << 0)
#define GLS_MEAS_FLAGS_GLUCOSE_CONCENTRATION_AND_TYPE_SAMPLE_LOCATION   (0x01 << 1)
#define GLS_MEAS_FLAGS_GLUCOSE_UNITS                                    (0x01 << 2)
#define GLS_MEAS_FLAGS_SENSOR_STATUS_ANNUNCAITION                       (0x01 << 3)
#define GLS_MEAS_FLAGS_CONTEXT_INFORMATION                              (0x01 << 4)

/* GLS Measurement Type Filed*/
#define GLS_MEAS_TYPE_RESERVED                  (0x0)
#define GLS_MEAS_TYPE_CAPILLARY_WHOLE_BLOOD     (0x1)
#define GLS_MEAS_TYPE_CAPILLARY_PLASMA          (0x2)
#define GLS_MEAS_TYPE_VENOUS_WHOLE_BLOOD        (0x3)
#define GLS_MEAS_TYPE_VENOUS_PLASMA             (0x4)
#define GLS_MEAS_TYPE_ARTERIAL_WHOLE_BLOOD      (0x5)
#define GLS_MEAS_TYPE_ARTERIAL_PLASMA           (0x6)
#define GLS_MEAS_TYPE_UNDETERMINED_WHOLE_BLOOD  (0x7)
#define GLS_MEAS_TYPE_UNDETERMINED_PLASMA       (0x8)
#define GLS_MEAS_TYPE_INTERSTITIAL_FLUID_ISF    (0x9)
#define GLS_MEAS_TYPE_CONTROL_SOLUTION          (0xA)

/* GLS Measurement Sample Location Filed*/
#define GLS_MEAS_SAMP_LOCATION_RESERVED                 (0x0)
#define GLS_MEAS_SAMP_LOCATION_FINGER                   (0x1)
#define GLS_MEAS_SAMP_LOCATION_ALTERNATE_SITE_TEST_AST  (0x2)
#define GLS_MEAS_SAMP_LOCATION_EARLOBE                  (0x3)
#define GLS_MEAS_SAMP_LOCATION_CONTROL_SOLUTION         (0x4)
#define GLS_MEAS_SAMP_LOCATION_VALUE_NOT_AVAILABLE      (0xF)

/* GLS Measurement Sensor Status */
#define GLS_MEAS_STATUS_DEVICE_BATTERY_LOW              (1 << 0)
#define GLS_MEAS_STATUS_SENSOR_MALFUNCTION              (1 << 1)
#define GLS_MEAS_STATUS_SAMPLE_SIZE_INSUFFICIENT        (1 << 2)
#define GLS_MEAS_STATUS_STRIP_INSERTION_ERROR           (1 << 3)
#define GLS_MEAS_STATUS_STRIP_TYPE_INCORRECT            (1 << 4)
#define GLS_MEAS_STATUS_SENSOR_RESULT_TOO_HIGH          (1 << 5)
#define GLS_MEAS_STATUS_SENSOR_RESULT_TOO_LOW           (1 << 6)
#define GLS_MEAS_STATUS_SENSOR_TEMPERATURE_TOO_HIGH     (1 << 7)
#define GLS_MEAS_STATUS_SENSOR_TEMPERATURE_TOO_LOW      (1 << 8)
#define GLS_MEAS_STATUS_SENSOR_READ_INTERRUPTED         (1 << 9)
#define GLS_MEAS_STATUS_GENERAL_DEVICE_FAULT            (1 << 10)
#define GLS_MEAS_STATUS_TIME_FAULT                      (1 << 11)

typedef struct
{
    uint16_t u16Year;
    uint8_t u8Month;
    uint8_t u8Day;
    uint8_t u8Hour;
    uint8_t u8Minute;
    uint8_t u8Second;
}stGlsDateTime_t;

typedef struct
{
    uint8_t u8Type : 4;
    uint8_t u8SampleLocation : 4;
}stGlsTypeSampleLocation_t;

typedef struct
{
    uint8_t u8Flags;                                /* Indicat The Optional Fields and The Sensor Status Annunciation Field */
    uint16_t u16SequenceNumber;                     /* Sequence Number */
    stGlsDateTime_t stBaseTime;                     /* Base Time */
    uint16_t u16TimeOffset;                         /* Time Offset */
    uint16_t u16GlucoseConcentration;               /* Glucose Concentration(SFLOAT) */
    stGlsTypeSampleLocation_t stTypeSampleLocation; /* Type-Sample Location */
    uint16_t u16Status;                             /* Sensor Status Annunciation */
}stGlsMeasRec_t;

/* GLS Record Access Control Point Command and Response Info */
#define GLS_RACP_OPERAND_MAX_LEN                (20)
typedef struct
{
    uint8_t u8Opcode;                               /* Opcode Reference "gls_racp.h" */
    uint8_t u8Operator;                             /* Operator Reference "gls_racp.h" */
    uint8_t u8Operand[GLS_RACP_OPERAND_MAX_LEN];    /* Operand */
    uint8_t u8OperandLen;                           /* Operand Length */
}stGlsRacpVal_t;

/* GLS Characteristic Handler */
typedef struct
{
    uint16_t u16Measurement;    /* GLS Measurement */
    uint16_t u16MeasurementCfg; /* GLS Measurement Client Characteristic Configuration Descriptor */
    uint16_t u16Feature;        /* GLS Feature */
    uint16_t u16Racp;           /* Record Access Control Point */
    uint16_t u16RacpCfg;        /* Record Access Control Point Client Characteristic Configuration Descriptor */
}stGlsChrsHandle_t;

/* GLS Global Handler */
typedef struct
{
    void (*event_handler)(EN_GLS_EVT_T u8Event);    /* GLS Event Callback Handler */
    uint16_t u16ConnHandle;                         /* Ble Connected Handle */
    uint16_t u16SrvHandle;                          /* GLS Service Handle */
    stGlsChrsHandle_t stChrsHandle;                 /* GLS Characteristic Handle */
    bool isRacpRunning;                             /* RACP Command Execution Status */
    uint16_t u16Feature;                            /* GLS Device Feature */
    stGlsRacpVal_t stRacpCmdInfo;                   /* Current RACP Command */
    void *pData;                                    /* User Data */
}stGlsHandle_t __attribute__((aligned(4)));

/* GLS Event Callback Function Declaration */
typedef void (*gls_event_callback_t)(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen);

static inline uint8_t gls_date_time_encode(const stGlsDateTime_t *stGlsDateTime,uint8_t *pu8Data)
{
    uint8_t u8Len = 0;
    
    if (NULL == stGlsDateTime || NULL == pu8Data)
        return 0;
    
    pu8Data[u8Len++] = stGlsDateTime->u16Year;
    pu8Data[u8Len++] = stGlsDateTime->u16Year >> 8;
    pu8Data[u8Len++] = stGlsDateTime->u8Month;
    pu8Data[u8Len++] = stGlsDateTime->u8Day;
    pu8Data[u8Len++] = stGlsDateTime->u8Hour;
    pu8Data[u8Len++] = stGlsDateTime->u8Minute;
    pu8Data[u8Len++] = stGlsDateTime->u8Second;
    
    return u8Len;
}

/**
 * @brief  Initialize Glucose Service.
 * @param  pstHandle: GLS Global Handle.
 * @param  eventCb: GLS Event Callback Function.GLS Event @ref EN_GLS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ble_gls_init(stGlsHandle_t *pstHandle,gls_event_callback_t eventCb);

/**
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: GLS Global Handle.
 * @param  pstRecord: GLS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T gls_meas_send(stGlsHandle_t *pstHandle,const stGlsMeasRec_t *pstRecord);

#endif
