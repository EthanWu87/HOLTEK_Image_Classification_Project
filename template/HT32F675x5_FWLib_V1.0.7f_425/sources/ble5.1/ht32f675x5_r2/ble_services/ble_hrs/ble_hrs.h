/*************************************************************************************************************
 * @file    ble_hrs.h
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
#ifndef BLE_HRS_H
#define BLE_HRS_H

#define HRS_MEASUREMENT_FLAGS_HEART_RATE_VAL_FORMAT             (1 << 0)
#define HRS_MEASUREMENT_FLAGS_CONTACT_DETECT                    (1 << 1)
#define HRS_MEASUREMENT_FLAGS_CONTACT_SUPPORT                   (1 << 2)
#define HRS_MEASUREMENT_FLAGS_ENERGY_EXPENDED                   (1 << 3)
#define HRS_MEASUREMENT_FLAGS_RR_INTERVAL                       (1 << 4)

/* HRS Event */
typedef enum
{
    EN_HRS_EVT_NONE = 0x00,
}EN_HRS_EVT_T;

typedef struct
{
    uint8_t  u8Flags;                /* Heart Rate Measurement Flags Field */
    uint8_t  u8MeasVal;              /* Heart Rate Measurement Value (8 bit resolution)*/
    uint16_t u16MeasVal;             /* Heart Rate Measurement Value (16 bit resolution)*/
    uint16_t u16EnerExpend;          /* Energy Expended  */
    uint16_t u16RRInterval;          /* RR-interval */
}stHrsMeasRec_t;

/* HRS Global Handler */
typedef struct
{
    void (*event_handler)(EN_HRS_EVT_T u8Event);        /* HRS Event Callback Handler */
    uint16_t u16ConnHandle;                             /* Ble Connected Handle */
    uint16_t u16SrvHandle;                              /* Heart Rate Service Handle */
    uint16_t u16HrsMeasHandle;                          /* Heart Rate Measurement Characteristic Handle */
    uint16_t u16HrsMeasCfgHandle;                       /* Heart Rate Measurement Characteristic Configuration Handle */
    void *pData;                                        /* User Data */
}stHrsHandle_t __attribute__((aligned(4)));

/* HRS Event Callback Function Declaration */
typedef void (*hrs_event_callback_t)(uint8_t u8Event, uint8_t* pu8Data, uint16_t u16DataLen);

/**
 * @brief  Initialize Heart Rate Service.
 * @param  pstHandle: HRS Global Handle.
 * @param  eventCb: HRS Event Callback Function. @ref EN_HRS_EVT_T.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ble_hrs_init(stHrsHandle_t *pstHandle,hrs_event_callback_t eventCb);

/**
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: HRS Global Handle.
 * @param  pstRecord: HRS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T hrs_meas_send(stHrsHandle_t *pstHandle,const stHrsMeasRec_t *pstRecord);

#endif
