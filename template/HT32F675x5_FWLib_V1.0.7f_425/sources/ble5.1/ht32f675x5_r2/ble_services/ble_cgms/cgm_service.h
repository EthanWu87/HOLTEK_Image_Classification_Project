/*************************************************************************************************************
 * @file    cgm_service.h
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
#ifndef CGM_SERVICE_H
#define CGM_SERVICE_H

#define CGMS_MEAS_COMMUNICATION_INTERAL_DEFAULT     (0x01)  /* 1 Minute */

/* CGMS Event */
typedef enum
{
    EN_CGMS_EVT_SOCP_SET_COMM_INTV              = 0x01,
    EN_CGMS_EVT_SOCP_START_SESSION              = 0x02,
    EN_CGMS_EVT_SOCP_STOP_SESSION               = 0x03,
    EN_CGMS_EVT_RACP_REPORT_RECORDS             = 0x04,
    EN_CGMS_EVT_RACP_REPORT_NUM_OF_RECORDS      = 0x05,
    EN_CGMS_EVT_RACP_DELETE_STORED_RECORDS      = 0x06,
    EN_CGMS_EVT_SST_SESSION_START_TIME_UPDATE   = 0x07,
}EN_CGMS_EVT_T;

/* CGMS Measurement Characteristic Record Flags Definition */
#define CGMS_MEAS_FLAGS_TREND_INFO              (0x01 << 0)
#define CGMS_MEAS_FLAGS_QUALITY                 (0x01 << 1)
#define CGMS_MEAS_FLAGS_STATUS_STATUS           (0x01 << 5)
#define CGMS_MEAS_FLAGS_STATUS_CALTEMP          (0x01 << 6)
#define CGMS_MEAS_FLAGS_STATUS_WARNING          (0x01 << 7)

/* CGM Feature Characteristic Definition */
#define CGM_FEATURE_SUPPORT_CALIBRATION                             (0x01 << 0)
#define CGM_FEATURE_SUPPORT_HIGH_LOW_ALERT                          (0x01 << 1)
#define CGM_FEATURE_SUPPORT_HYPO_ALERT                              (0x01 << 2)
#define CGM_FEATURE_SUPPORT_HYPER_ALERT                             (0x01 << 3)
#define CGM_FEATURE_SUPPORT_RATE_OF_INCREASE_DECREASE_ALERT         (0x01 << 4)
#define CGM_FEATURE_SUPPORT_DEVICE_SPECIFIC_ALERT                   (0x01 << 5)
#define CGM_FEATURE_SUPPORT_SENSOR_MALFUNCTION_DETECTION            (0x01 << 6)
#define CGM_FEATURE_SUPPORT_SENSOR_TEMPERATURE_HIGH_LOW_DETECTION   (0x01 << 7)
#define CGM_FEATURE_SUPPORT_SENSOR_RESULT_HIGH_LOW_DETECTION        (0x01 << 8)
#define CGM_FEATURE_SUPPORT_LOW_BATTERY_DETECTION                   (0x01 << 9)
#define CGM_FEATURE_SUPPORT_SENSOR_TYPE_ERROR_DETECTION             (0x01 << 10)
#define CGM_FEATURE_SUPPORT_GENERAL_DEVICE_FAULT                    (0x01 << 11)
#define CGM_FEATURE_SUPPORT_E2E_CRC                                 (0x01 << 12)
#define CGM_FEATURE_SUPPORT_MULTIPLE_BOND                           (0x01 << 13)
#define CGM_FEATURE_SUPPORT_MULTIPLE_SESSIONS                       (0x01 << 14)
#define CGM_FEATURE_SUPPORT_TREND_INFO                              (0x01 << 15)
#define CGM_FEATURE_SUPPORT_QUALITY                                 (0x01 << 16)

/* CGMS Sensor Status */
#define CGMS_STATUS_STATUS_SESSION_STOPPED                          (0x01 << 0)     /* Session Stoped */
#define CGMS_STATUS_STATUS_DEVICE_BATTERY_LOW                       (0x01 << 1)     /* Device Battert Low */
#define CGMS_STATUS_STATUS_SENSOR_TYPE_INCORRECT_FOR_DEVICE         (0x01 << 2)     /* Sensor Type Incorrect for Device */
#define CGMS_STATUS_STATUS_SENSOR_MALFUNCTION                       (0x01 << 3)     /* Sensor Malfunction */
#define CGMS_STATUS_STATUS_DEVICE_SPECIFIC_ALERT                    (0x01 << 4)     /* Device Specific Alert */
#define CGMS_STATUS_STATUS_GENERAL_DEVICE_FAULT                     (0x01 << 5)     /* General Device Fault */

typedef struct
{
    uint8_t u8Status;       /* Status Annunciation */
    uint8_t u8CalTemp;      /* Calibration and Temperature Annunciation */	
    uint8_t u8Warning;      /* Warning Annunciation */
}stCgmsMeasSensorStatus_t;

typedef struct
{
    uint16_t u16TimeOffset;             /* Relative Time Difference to The Session Start Time */
    stCgmsMeasSensorStatus_t stStatus;  /* Indicate The Status of The CGM Device */
}stCgmsStatus_t;

typedef struct
{
    uint8_t u8Size;                     /* Not Used */
    uint8_t u8Flags;                    /* Indicat The Optional Fields and The Sensor Status Annunciation Field */
    uint16_t u16GlucoseConcentration;   /* Glucose Concentration(SFLOAT) */
    uint16_t u16TimeOffset;             /* Relative Time Difference to The Session Start Time */
    stCgmsMeasSensorStatus_t stStatus;  /* Variable Length Between 1 and 3 Octets */
    uint16_t u16TrendInfo;              /* Optional Field that Can Include Trend Information(SFLOAT) */
    uint16_t u16Quality;                /* Optional Field that Includes The Quality of The Measurement */
}stCgmsMeasRec_t;


typedef struct
{
    uint32_t u32Feature;        /* Function Support by CGMS Device */
    uint8_t  u8Type;            /* Sample Type */
    uint8_t  u8SampLocation;    /* Sample Location */
}stCgmsFeature_t;

/* CGMS Session Start Time */
typedef struct
{
    uint16_t u16Year;
    uint8_t u8Month;
    uint8_t u8Day;
    uint8_t u8Hour;
    uint8_t u8Minute;
    uint8_t u8Second;
    int8_t i8TimeZone;
    uint8_t u8Dst;
}stCgmsSessionStartTime_t;

/* CGMS Record Access Control Point Command and Response Info */
#define CGMS_RACP_OPERAND_MAX_LEN               (20)
typedef struct
{
    uint8_t u8Opcode;                               /* Opcode Reference "cgms_racp.h" */
    uint8_t u8Operator;                             /* Operator Reference "cgms_racp.h" */
    uint8_t u8Operand[CGMS_RACP_OPERAND_MAX_LEN];   /* Operand */
    uint8_t u8OperandLen;                           /* Operand Length */
}stCgmsRacpVal_t;

/* CGMS Characteristic Handler */
typedef struct
{
    uint16_t u16Measurement;    /* CGM Measurement */
    uint16_t u16MeasurementCfg; /* CGM Measurement Client Characteristic Configuration Descriptor */
    uint16_t u16Feature;        /* CGM Feature */
    uint16_t u16Status;         /* CGM Status */
    uint16_t u16StartTime;      /* CGM Session Start Time */
    uint16_t u16RunTime;        /* CGM Session Run Time */
    uint16_t u16Racp;           /* Record Access Control Point */
    uint16_t u16RacpCfg;        /* Record Access Control Point Client Characteristic Configuration Descriptor */
    uint16_t u16Socp;           /* CGM Specofic Ops Control Point */
    uint16_t u16SocpCfg;        /* CGM Specofic Ops Control Point Client Characteristic Configuration Descriptor */
}stCgmsChrsHandle_t;

/* CGMS Global Handler */
typedef struct
{
    void (*event_handler)(EN_CGMS_EVT_T u8Event);   /* CGMS Event Callback Handler */
    uint16_t u16ConnHandle;                         /* Ble Connected Handle */
    uint16_t u16SrvHandle;                          /* CGM Service Handle */
    stCgmsChrsHandle_t stChrsHandle;                /* CGMS Characteristic Handle */
    bool isSessionStart;                            /* Session Status */
    bool isRacpRunning;                             /* RACP Command Execution Status */
    stCgmsFeature_t stFeature;                      /* CGM Device Feature */
    stCgmsStatus_t stStatus;                        /* CGM Device Status */
    stCgmsSessionStartTime_t stSst;                 /* Session Start Time */
    uint16_t u16Srt;                                /* Session Run Time (Uint:Hour) */
    uint8_t u8CommIntv;                             /* Communication Inteval */
    stCgmsRacpVal_t stRacpCmdInfo;                  /* Current RACP Command */
}stCgmsHandle_t __attribute__((aligned(4)));

/* CGMS Event Callback Function Declaration */
typedef void (*cgms_event_callback_t)(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen);

/**
 * @brief  Encode Feature Data.
 * @param  stFeature: CGMS Feature Handle.
 * @param  pu8OutDataBuf: Output Data Buffer.
 * @param  u8DataBufLen: The Length of Output Data Buffer
 *
 * @return The Length of Output Data.
 */
static inline uint8_t cgms_encode_feature(const stCgmsFeature_t *stFeature,uint8_t *pu8OutDataBuf,uint8_t u8DataBufLen)
{
    uint8_t u8Len = 0;
    
    if (NULL == pu8OutDataBuf || 0 == u8DataBufLen)
        return 0;
    
    pu8OutDataBuf[u8Len++] = (uint8_t) ((stFeature->u32Feature & 0x000000FF) >> 0);
    pu8OutDataBuf[u8Len++] = (uint8_t) ((stFeature->u32Feature & 0x0000FF00) >> 8);
    pu8OutDataBuf[u8Len++] = (uint8_t) ((stFeature->u32Feature & 0x00FF0000) >> 16);
    pu8OutDataBuf[u8Len++] = (uint8_t) ((stFeature->u8SampLocation << 4) | (stFeature->u8Type & 0x0F));
    pu8OutDataBuf[u8Len++] = 0xFF;
    pu8OutDataBuf[u8Len++] = 0xFF;

    return u8Len;
}

/**
 * @brief  Initialize Continuous Glucose Monitoring Service.
 * @param  pstHandle: CGMS Global Handle.
 * @param  eventCb: CGMS Event Callback Function.CGMS Event @ref EN_CGMS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T cgm_service_init(stCgmsHandle_t *pstHandle,cgms_event_callback_t eventCb);

/**
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: CGMS Global Handle.
 * @param  pstRecord: CGMS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T cgms_meas_send(stCgmsHandle_t *pstHandle,const stCgmsMeasRec_t *pstRecord);

#endif
