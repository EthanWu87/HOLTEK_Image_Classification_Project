/*************************************************************************************************************
 * @file    ble_dis.h
 * @version V1.0
 * @date    2021-01-21
 * @brief   Device information service
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


#ifndef __BLE_DIS_H__
#define __BLE_DIS_H__

/**< Device Information Service Parameters */
#define DEVINFO_SYSTEM_ID           0
#define DEVINFO_MODEL_NUMBER        1
#define DEVINFO_SERIAL_NUMBER       2
#define DEVINFO_FIRMWARE_REV        3
#define DEVINFO_HARDWARE_REV        4
#define DEVINFO_SOFTWARE_REV        5
#define DEVINFO_MANUFACTURER_NAME   6
#define DEVINFO_11073_CERT_DATA     7
#define DEVINFO_PNP_ID              8

/**< IEEE 11073 authoritative body values */
#define DEVINFO_11073_BODY_EMPTY    0
#define DEVINFO_11073_BODY_IEEE     1
#define DEVINFO_11073_BODY_CONTINUA 2
#define DEVINFO_11073_BODY_EXP      254

/**< System ID length */
#define DEVINFO_SYSTEM_ID_LEN       8

/**< PnP ID length */
#define DEVINFO_PNP_ID_LEN          7

/**
 * @brief  Initializes the Device Information service by registering GATT
 *          attributes with the GATT server.
 * @return Error Status.
 */
extern uint8_t ble_dis_init(void);

/**
 * @brief  Set a Device Information parameter.
 * @param  param: Profile parameter ID
 * @param  u8Len: length of data to write
 * @param  pValue: pointer to data to write. This is dependent on the parameter
 *                 ID and WILL be cast to the appropriate data type (example: data
 *                 type of uint16_t will be cast to uint16_t pointer).
 * @return Error Status.
 */
extern uint8_t ble_dis_set_parameter(uint8_t u8Param, uint8_t u8Len, void *pValue);

/**
 * @brief   Get a Device Information parameter.
 * @param   u8Param: Profile parameter ID
 * @param   pValue: pointer to data to get.  This is dependent on the parameter
 *          ID and WILL be cast to the appropriate data type (example: data type
 *          of uint16_t will be cast to uint16_t pointer).
 * @return Error Status.
 */
extern uint8_t ble_dis_get_parameter(uint8_t u8Param, void *pValue);

#endif /* __BLE_DIS_H__ */
