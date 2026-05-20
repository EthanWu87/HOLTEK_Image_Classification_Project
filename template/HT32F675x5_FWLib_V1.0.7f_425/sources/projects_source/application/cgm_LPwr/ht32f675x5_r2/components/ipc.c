/*************************************************************************************************************
 * @file    ipc.c
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
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "err_def.h"
#include "app_cfg.h"
#include "utility.h"
#include "msg_queue.h"
#include "ipc_general_queue.h"
#include "ipc.h"

static ipc_callback_t ipc_callback = NULL;
static uint8_t gu8IpcBuffer[IpcMessageBufferMemSize(IPC_MSG_COUNT,IPC_MSG_DATA_SIZE + 1)] __attribute__((aligned(4)));

/**********************************************************************************************************************
 * @brief  IPC Receive Message from Other Core Callback.
 * @param  pu8Data: Received Data.
 * @param  u32DataLen: The length of Received Data
 *********************************************************************************************************************/
static uint32_t ipc_receive_msg_callback(uint8_t *pu8Data, uint32_t u32DataLen)
{
    if(ipc_callback != NULL)
    {
        uint8_t *pu8Ptr = &pu8Data[1];
        if (u32DataLen == 1)
            pu8Ptr = NULL;
        ipc_callback(pu8Data[0],pu8Ptr,u32DataLen-1);
    }
    return 0;
}

/**********************************************************************************************************************
 * @brief  IPC Module Init.
 * @param  cb: IPC Callback for Receiving Data.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ipc_init(ipc_callback_t cb)
{
    if (NULL == cb)
        return ERR_PARA_ERR;
    
    ipc_callback = cb;
    
    stIpcInit_t stIpcInit;
    
    stIpcInit.pu8Buf = gu8IpcBuffer;
    stIpcInit.u32BufSize = sizeof(gu8IpcBuffer);
    stIpcInit.u32MsgCount = IPC_MSG_COUNT;
    stIpcInit.u32MsgSize = IPC_MSG_DATA_SIZE;
    stIpcInit.enMode = QUEUE_MODE_NO_OVERFLOW;
    stIpcInit.pfnCallback = ipc_receive_msg_callback;

    return ipc_general_init(&stIpcInit);
}

/**********************************************************************************************************************
 * @brief  IPC Send Command and Data to Other Core.
 * @param  u8Cmd: IPC Callback for Receiving Data.
 * @param  pData: The Ready to Send Data.
 * @param  u16DataLen: The Length of Data.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ipc_send(uint8_t u8Cmd,void *pData,uint16_t u16DataLen)
{
    uint8_t *pu8Data = pData;
    
    if ((NULL == pu8Data && 0 != u16DataLen) || (NULL != pu8Data && 0 == u16DataLen) || u16DataLen > IPC_MSG_DATA_SIZE)
        return ERR_PARA_ERR;
    
    uint8_t pu8TmpData[IPC_MSG_DATA_SIZE + 1];
    
    pu8TmpData[0] = u8Cmd;
    memcpy(&pu8TmpData[1],pu8Data,u16DataLen);
    
    return ipc_general_send_msg_nonblocking(pu8TmpData,u16DataLen+1);
}
