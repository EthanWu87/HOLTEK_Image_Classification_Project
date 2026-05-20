/*************************************************************************************************************
 * @file    ota_service.h
 * @version V1.0
 * @date    2022-11-07
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


#ifndef __BLE_OTA_PROFILE_H__
#define __BLE_OTA_PROFILE_H__

typedef struct
{
    uint16_t u16SrvHandle;
    uint16_t u16DataHandle;
    uint16_t u16CtrlHandle;
}stOtaService_t;

typedef void (*ota_recv_callback_t)(uint8_t* pu8Data, uint16_t u16DataLen);

/**
 * @brief  To creat ble ota profile.
 */
EN_ERR_STA_T ota_service_init(ota_recv_callback_t eventCb);
EN_ERR_STA_T ota_send_notify(uint16_t u16ConnHandle,uint8_t *pu8Buf,uint16_t u16BufSize);

#endif /* __BLE_OTA_PROFILE_H__ */
