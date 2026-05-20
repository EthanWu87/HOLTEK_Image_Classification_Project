/*************************************************************************************************************
 * @file    ipc_rtos.h
 * @version V1.0
 * @date    2021-03-17
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


#ifndef __IPC_RTOS_H__
#define __IPC_RTOS_H__


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define IPC_MSG_COUNT                      ( 16 )
#define IPC_MSG_DATA_LEN                   ( 32 )

#if __MAIN_PROCESSOR
    #define IPC_MSG_EXTRA_DATA_COUNT       ( 8 )
    #define IPC_MSG_EXTRA_DATA_LEN         ( 144 )

    #define IPC_RX_TASK_PRIORITY           ( osPriorityNormal )
    #define IPC_RX_TASK_STACK_SIZE         ( 1024 )
#else
    #define IPC_MSG_EXTRA_DATA_COUNT       ( 4 )
    #define IPC_MSG_EXTRA_DATA_LEN         ( 144 )

    #define IPC_RX_TASK_PRIORITY           ( osPriorityNormal )
    #define IPC_RX_TASK_STACK_SIZE         ( 1024 )
#endif


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef struct
{
    uint32_t  u32Cmd;
    uint8_t  *pu8Data;
    uint32_t  u32DataLen;
    uint8_t  *pu8ExtraData;
    uint32_t  u32ExtraDataLen;

} stIpcMsg_t __attribute__((aligned(4)));


typedef void (*ipc_rx_msg_cb_func)(stIpcMsg_t *pstIpcMsg);




/**
 * @brief  IPC Send Message by Non-Blocking
 *         This API Can Call in IRQ Handler.
 * @param  u32Cmd: Command of Message
 * @param  pu8Data: Data of Message
 * @param  u32DataLen: Data Length of Message
 * @param  pu8ExtraData: Extra Data of Message
 * @param  u32ExtraDataLen: Extra Data Length of Message
 * @return HW status: @ref EN_ERR_STA_T 
 */
extern EN_ERR_STA_T ipc_rtos_send_msg_nonblocking(uint32_t u32Cmd, uint8_t* pu8Data, uint32_t u32DataLen, 
                                             uint8_t* pu8ExtraData, uint32_t u32ExtraDataLen);


/**
 * @brief  IPC Send Message by Blocking
 *         This API Can Not Call in IRQ Handler.
 * @param  u32Cmd: Command of Message
 * @param  pu8Data: Data of Message
 * @param  u32DataLen: Data Length of Message
 * @param  pu8ExtraData: Extra Data of Message
 * @param  u32ExtraDataLen: Extra Data Length of Message
 * @return HW status: @ref EN_ERR_STA_T
 */
extern EN_ERR_STA_T ipc_rtos_send_msg_blocking(uint32_t u32Cmd, uint8_t* pu8Data, uint32_t u32DataLen, 
                                          uint8_t* pu8ExtraData, uint32_t u32ExtraDataLen);


/**
 * @brief  Inter-Processor Communication(IPC) Initialization.
 * @param  pfnCallback: IPC receive callback function.
 * @return HW status: @ref EN_ERR_STA_T
 */
extern EN_ERR_STA_T ipc_rtos_init(ipc_rx_msg_cb_func pfnCallback);


#endif /* __IPC_RTOS_H__ */


