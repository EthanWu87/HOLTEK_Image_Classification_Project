/*************************************************************************************************************
 * @file    ble_gap_service.h
 * @version V1.0
 * @date    2021-12-05
 * @brief   ble gap service
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


#ifndef __BLE_GAP_SERVICE_H__
#define __BLE_GAP_SERVICE_H__

/**
 * @brief  Initializing the ble gap service.
 * @param  u16Apperance: Pointer to function for handling received data.
 * @param  pu8DevName: Pointer to device name.
 * @param  u8DevNameLen: Device name length.
 * @return uint32_t: Return status.
 */
extern uint32_t ble_gap_service_init(uint8_t *pu8DevName, uint8_t u8DevNameLen, uint16_t u16Apperance);

/**
 * @brief  Set the Holtek UART Service.
 * @param  pu8DevName: Pointer to device name.
 * @param  u8DevNameLen: Device name length.
 */
extern void ble_gap_service_set_device_name(uint8_t *pu8DevName, uint16_t u8DevNameLen);

#endif /* __BLE_GAP_SERVICE_H__ */
