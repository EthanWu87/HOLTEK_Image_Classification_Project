/*************************************************************************************************************
 * @file    ipc_general_blocking.h
 * @version V1.0
 * @date    2022-12-27
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


#ifndef __IPC_GENERAL_BLOCKING_H__
#define __IPC_GENERAL_BLOCKING_H__

/**
 * @brief  TYPEDEF
 */
typedef uint32_t (*ipc_rx_msg_cb_func)(uint8_t *pu8DataBuffer, uint32_t u32DataLen);

/**
 * @brief  General ipc Initialization.
 * @param  pu8DataBuf: the buffer to save data.
 * @param  u32BufMaxLen: the buffersize to save data.
 * @param  pfnCallback: Callback functions.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T ipc_general_init(uint8_t *pu8DataBuf, uint32_t u32BufMaxLen, ipc_rx_msg_cb_func pfnCallback);

/**
 * @brief  Send ipc message by blocking. This API can be called from Interrupt Service Routines (ISR).
 * @param  pu8Data: Pointer to the data buffer which will be sent.
 * @param  u32DataLen: Data length.
 * @return status: @ref EN_ERR_STA_T.
 */
extern uint32_t ipc_general_send_msg_blocking(uint8_t *pu8Data, uint32_t u32DataLen);

#endif /* __IPC_GENERAL_BLOCKING_H__ */
