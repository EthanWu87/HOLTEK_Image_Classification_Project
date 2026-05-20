/*************************************************************************************************************
 * @file    ipc.h
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
#ifndef IPC_H
#define IPC_H

typedef enum
{
    EN_IPC_CMD_CAL_SUM      = 0x00,
    EN_IPC_CMD_CAL_SUM_OK   = 0x01,
    EN_IPC_CMD_CAL_FFT      = 0x02,
    EN_IPC_CMD_CAL_FFT_OK   = 0x03,
    // ...
}EN_IPC_CMD_T;

typedef void (*ipc_callback_t)(uint8_t u8Cmd,void *pData,uint16_t u16DataLen);

/**
 * @brief  IPC Module Init.
 * @param  cb: IPC Callback for Receiving Data.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ipc_init(ipc_callback_t cb);

/**
 * @brief  IPC Send Command and Data to Other Core.
 * @param  u8Cmd: IPC Callback for Receiving Data.
 * @param  pData: The Ready to Send Data.
 * @param  u16DataLen: The Length of Data.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ipc_send(uint8_t u8Cmd,void *pData,uint16_t u16DataLen);

#endif