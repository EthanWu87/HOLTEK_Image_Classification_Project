/*************************************************************************************************************
 * @file    ble_bas.h
 * @version V1.0
 * @date    2022-11-11
 * @brief   ble battery service
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


 
#ifndef BLE_BAS_H
#define BLE_BAS_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef uint8_t (*ble_bas_get_battery_level_t)(void);

EN_ERR_STA_T ble_bas_init(ble_bas_get_battery_level_t getLevel);
EN_ERR_STA_T ble_bas_send_battery_level(uint16_t u16ConnHandle, uint8_t u8BatteryLevel);


#ifdef __cplusplus
}
#endif

#endif /* BATTSERVICE_H */
