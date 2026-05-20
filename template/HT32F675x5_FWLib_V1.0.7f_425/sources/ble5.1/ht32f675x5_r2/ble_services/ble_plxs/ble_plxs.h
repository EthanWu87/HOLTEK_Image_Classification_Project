/*************************************************************************************************************
 * @file    ble_plxs.h
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
#ifndef PLXS_SERVICE_H
#define PLXS_SERVICE_H

/* PLXS Feature Characteristic Definition */
#define PLXS_FEATURE_SUPPORT_MEAS_STATUS_PRESENT                (1 << 0)
#define PLXS_FEATURE_SUPPORT_DEV_AND_SEN_STATUS_PRESENT         (1 << 1)
#define PLXS_FEATURE_SUPPORT_MEAS_STORAGE_FOR_SPOT_CHECK_MEAS   (1 << 2)
#define PLXS_FEATURE_SUPPORT_TIMESTAMP_FOR_SPOT_CHECK_MEAS      (1 << 3)
#define PLXS_FEATURE_SUPPORT_SPO2PR_FAST_METRIC                 (1 << 4)
#define PLXS_FEATURE_SUPPORT_SPO2PR_SLOW_METRIC                 (1 << 5)
#define PLXS_FEATURE_SUPPORT_PLUSE_AMPLITUDE                    (1 << 6)
#define PLXS_FEATURE_SUPPORT_MULTIPLE_BONDS                     (1 << 7)

/* PLXS Measurement Characteristic Record Flags Definition */
#define PLXS_MEAS_FLAGS_TIME_STAMP_PRESENT              (1 << 0)
#define PLXS_MEAS_FLAGS_MEAS_STATUS_PRESENT             (1 << 1)
#define PLXS_MEAS_FLAGS_DEV_SENSOR_STATUS_PRESENT       (1 << 2)
#define PLXS_MEAS_FLAGS_PLUSE_AMPLITUDE_INDEX_PRESENT   (1 << 3)
#define PLXS_MEAS_FLAGS_DEV_CLOCK_IS_NOT_SET            (1 << 4)

/* PLXS Measurement Characteristic Record Status Definition */
#define PLXS_MEAS_STATUS_MEAS_ONGOING                   (1 << 5)    /* Measurement Ongoing */
#define PLXS_MEAS_STATUS_EARLY_ESTIMATED_DATA           (1 << 6)    /* Early Estimated Data */
#define PLXS_MEAS_STATUS_VALIDATED_DATA                 (1 << 7)    /* Validated Data */
#define PLXS_MEAS_STATUS_FULLY_QUALIFIED_DATA           (1 << 8)    /* Fully Qualified Data */
#define PLXS_MEAS_STATUS_DATA_FROM_MEAS_STORAGE         (1 << 9)    /* Data from Measurement Storage */
#define PLXS_MEAS_STATUS_DATA_FOR_DEMONSTRATION         (1 << 10)   /* Data for Demonstration */
#define PLXS_MEAS_STATUS_DATA_FOR_TESTING               (1 << 11)   /* Data for Testing */
#define PLXS_MEAS_STATUS_CALIBRATION_ONGOINT            (1 << 12)   /* Calibration Ongoing */
#define PLXS_MEAS_STATUS_MEAS_UNAVALIABLE               (1 << 13)   /* Measurement Unavaliable */
#define PLXS_MEAS_STATUS_QUESTIONABLE_MEAS_DETECTED     (1 << 14)   /* Questionable Measurement Detected */
#define PLXS_MEAS_STATUS_INVALID_MEAS_DETECTED          (1 << 15)   /* Invalid Measurement Detected */

/* PLXS Device and Sensor Status Definition */
#define PLXS_DEV_SEN_STATUS_EXT_DISPLAY_UPDATE_ONGOING     (1 << 0)    /* Extended Display Update Ongoing */
#define PLXS_DEV_SEN_STATUS_EQP_MALFUNCTION_DETECTED       (1 << 1)    /* Equipment Malfunction Detected */
#define PLXS_DEV_SEN_STATUS_SIGNAL_PROCESSING_IRR_DETECTED (1 << 2)    /* Signal Processing Irregularity Detected */
#define PLXS_DEV_SEN_STATUS_INADEQUATE_SIGNAL_DETECTED     (1 << 3)    /* Inadequate Singal Detected */
#define PLXS_DEV_SEN_STATUS_POOR_SIGNAL_DETECTED           (1 << 4)    /* Poor Signal Detected */
#define PLXS_DEV_SEN_STATUS_LOW_PERFUSION_DETECTED         (1 << 5)    /* Low Perfusion Detected */
#define PLXS_DEV_SEN_STATUS_ERRATIC_SIGNAL_DETECTED        (1 << 6)    /* Erratic Signal Detected */
#define PLXS_DEV_SEN_STATUS_NON_PULSATILE_SIGNAL_DETECTED  (1 << 7)    /* Non-Pulsatile Signal Detected */
#define PLXS_DEV_SEN_STATUS_QUESTIONABLE_PULSE_DETECTED    (1 << 8)    /* Questionable Pulse Detected */
#define PLXS_DEV_SEN_STATUS_SIGNAL_ANALYSIS_ONGOING        (1 << 9)    /* Signal Analysis Ongoing */
#define PLXS_DEV_SEN_STATUS_SENSOR_INTERFERENCE_DETECTED   (1 << 10)   /* Sensor Interference Detected */
#define PLXS_DEV_SEN_STATUS_SENSOR_UNCONNECTED_TO_USER     (1 << 11)   /* Sensor Unconnected to User */
#define PLXS_DEV_SEN_STATUS_UNKNOWN_SENSOR_CONNECTED       (1 << 12)   /* Unknown Sensor Connected */
#define PLXS_DEV_SEN_STATUS_SENSOR_DISPLACED               (1 << 13)   /* Sensor Displaced */
#define PLXS_DEV_SEN_STATUS_SENSOR_MALFUNCTIONING          (1 << 14)   /* Sensor Malfunctioning */
#define PLXS_DEV_SEN_STATUS_SENSOR_DISCONNECTED            (1 << 15)   /* Sensor Disconnected */

typedef struct
{
    uint16_t u16Year;
    uint8_t u8Month;
    uint8_t u8Day;
    uint8_t u8Hour;
    uint8_t u8Minute;
    uint8_t u8Second;
}stPlxsDateTime_t;

typedef struct
{
    uint8_t u8Flags;                    /* Flags */
    uint16_t u16SpO2;                   /* Percent oxygen saturation of hemoglobin */
    uint16_t u16Pr;                     /* pulse rate */
    stPlxsDateTime_t stTimeStamp;       /* Time Stamp */
    uint16_t u16MeasStatus;             /* Measurement Status */
    uint32_t u32DevAndSensorStatus;     /* Device And Sensor Status (24-Bit)*/
    uint16_t u16PluseAmplitudeIndex;    /* Pulse Amplitude Index */
}stPlxsMeasRec_t;

typedef struct
{
    uint16_t u16Features;                   /* Supported Features */
    uint16_t u16MeasFeatures;               /* Measurement Features Support */
    uint32_t u32DevSensorStatusFeatures;    /* Device and Sensor Status Support (24-bit) */
}stPlxsFeature_t;

/* PLXS Global Handler */
typedef struct
{
    uint16_t u16ConnHandle;                         /* Ble Connected Handle */
    uint16_t u16SrvHandle;                          /* PLXS Service Handle */
    uint16_t u16FeatureHandle;                      /* PLXS Feature Handle */
    uint16_t u16MeasHandle;                         /* PLXS Measurement Handle */
    uint16_t u16MeasCfgHandle;                      /* PLXS Measurement Configuration Handle */
    stPlxsFeature_t stFeatures;                     /* PLXS Device Feature */
    void *pData;                                    /* User Data */
}stPlxsHandle_t __attribute__((aligned(4)));

static inline uint8_t plxs_date_time_encode(const stPlxsDateTime_t *stPlxsDateTime,uint8_t *pu8Data)
{
    uint8_t u8Len = 0;
    
    if (NULL == stPlxsDateTime || NULL == pu8Data)
        return 0;
    
    pu8Data[u8Len++] = stPlxsDateTime->u16Year;
    pu8Data[u8Len++] = stPlxsDateTime->u16Year >> 8;
    pu8Data[u8Len++] = stPlxsDateTime->u8Month;
    pu8Data[u8Len++] = stPlxsDateTime->u8Day;
    pu8Data[u8Len++] = stPlxsDateTime->u8Hour;
    pu8Data[u8Len++] = stPlxsDateTime->u8Minute;
    pu8Data[u8Len++] = stPlxsDateTime->u8Second;
    
    return u8Len;
}

/**
 * @brief  Initialize PLX Serivce Service.
 * @param  pstHandle: PLXS Global Handle.
 * @param  eventCb: PLXS Event Callback Function.PLXS Event @ref EN_PLXS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ble_plxs_init(stPlxsHandle_t *pstHandle);

/**
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: PLXS Global Handle.
 * @param  pstRecord: PLXS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T plxs_meas_send(stPlxsHandle_t *pstHandle,const stPlxsMeasRec_t *pstRecord);

#endif
