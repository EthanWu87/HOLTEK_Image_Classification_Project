/*************************************************************************************************************
 * @file    ble_mus.h
 * @version V1.0
 * @date    2022-06-09
 * @brief   Holtek UART Service
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


#ifndef __BLE_MUS_H__
#define __BLE_MUS_H__

/**
 * @brief  TYPEDEF.
 */
/**@brief Holtek UART Service event handler type. */
typedef void (*ble_mus_data_handler_t)(uint16_t u16ConnHandle, uint8_t *pu8Data, uint16_t u16DataLen);

/**
 * @brief  Initializing the Holtek UART Service.
 * @param  pfnDataHandler: Pointer to function for handling received data.
 * @return uint32_t: Return status.
 */
extern uint32_t ble_mus_init(ble_mus_data_handler_t pfnDataHandler);

uint16_t ble_mus_transfer(uint16_t u16ConnHandle, uint8_t *pu8Data, uint16_t u16DataLen);

#endif /* __BLE_MUS_H__ */
