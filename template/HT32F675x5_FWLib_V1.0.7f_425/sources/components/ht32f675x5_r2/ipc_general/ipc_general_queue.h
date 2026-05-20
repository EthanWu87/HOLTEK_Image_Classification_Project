/*************************************************************************************************************
 * @file    ipc_general_queue.h
 * @version V1.0
 * @date    2022-12-28
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


#ifndef __IPC_GENERAL_QUEUE_H__
#define __IPC_GENERAL_QUEUE_H__


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define IPC_MSG_COUNT                      ( 2 )
#define IPC_MSG_DATA_SIZE                  ( 512 )

#define IpcMessageBufferMemSize(msgCount, msgSize)  (4*(msgCount)*(3+(((msgSize)+3)/4)))


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef struct __attribute__((aligned(4)))
{
    uint32_t  u32DataLen;
    uint8_t  *pu8Data;

} stIpcMsg_t;


// Receive message callback function.
typedef uint32_t (*ipc_rx_msg_cb_func)(uint8_t *pu8Data, uint32_t u32DataLen);


typedef struct __attribute__((aligned(4)))
{
    uint8_t  *pu8Buf;
    uint32_t  u32BufSize;
    uint32_t  u32MsgCount;
    uint32_t  u32MsgSize;

    EN_QUEUE_MODE_T enMode;
    ipc_rx_msg_cb_func pfnCallback;

} stIpcInit_t;




/**
 * @brief  General ipc Initialization.
 * @param  pstIpcInit: Pointer to ipc init struct.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T ipc_general_init(stIpcInit_t *pstIpcInit);


/**
 * @brief  Send ipc message by blocking. This API can not be called from Interrupt Service Routines (ISR).
 * @param  pu8Data: Pointer to the data buffer which will be sent.
 * @param  u32DataLen: Data length.
 * @return status: @ref EN_ERR_STA_T.
 */
extern uint32_t ipc_general_send_msg_blocking(uint8_t *pu8Data, uint32_t u32DataLen);


/**
 * @brief  IPC Send Message by Non-Blocking. This API Can Call in IRQ Handler.
 * @param  pu8Data: Data of Message.
 * @param  u32DataLen: Data Length of Message.
 * @return HW status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T ipc_general_send_msg_nonblocking(uint8_t *pu8Data, uint32_t u32DataLen);




#endif /* __IPC_GENERAL_QUEUE_H__ */

