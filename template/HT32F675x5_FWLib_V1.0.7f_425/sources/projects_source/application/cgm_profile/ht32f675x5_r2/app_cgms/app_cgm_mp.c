/*************************************************************************************************************
 * @file    app_cgm_mp.c
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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "app_cfg.h"
#include "boards.h"
#include "utility.h"

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "lpwr_ctrl.h"
#include "ipc.h"

#define APP_MSG_NUM                 (5)

typedef struct
{
    uint8_t  u8MsgModule;
    uint8_t  u8Event;
    uint32_t u32Length;
    void *p;
    uint16_t u16Reserve;
}stAppMsg_t;

typedef enum
{
    EN_MSG_MODULE_CAL_UNIT = 0x00,
}EN_MSG_MODULE_T;

typedef enum
{
    EN_EVT_CAL_SUM      = 0x00,
    EN_EVT_CAL_FFT      = 0x01,
    // ...
}EN_EVT_CAL_UNIT_T;

/* Message Queue Variables */
static osMessageQueueId_t gosMsgId = NULL;
static uint32_t gu32TaskMsgQueueCb[osRtxMessageQueueCbSize / 4U];
static uint32_t gu32TaskMsgQueueMem[osRtxMessageQueueMemSize(10, sizeof(stAppMsg_t)) / 4U];
static uint32_t gu32SharedSum = 0;

/**********************************************************************************************************************
 * @brief  OS Message Queue Init.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T msg_queue_init(void)
{
    const osMessageQueueAttr_t appMsgAueueAttr =
    {
        .name = "App CGMS Msg Queue",
        .attr_bits = 0,
        .cb_mem = gu32TaskMsgQueueCb,
        .cb_size = sizeof(gu32TaskMsgQueueCb),
        .mq_mem = gu32TaskMsgQueueMem,
        .mq_size = sizeof(gu32TaskMsgQueueMem),
    };

    gosMsgId = osMessageQueueNew(APP_MSG_NUM, sizeof(stAppMsg_t), &appMsgAueueAttr);
    if(NULL == gosMsgId)
    {
        PRINTF("create AppMsgId failed\n");
        return ERR_STA_ERROR;
    }
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Send App Message.
 * @param  enMsgModlue: App Module.
 * @param  u8Event: Module Event.
 * @param  pu8Data: Event Data.
 * @param  u32Len: the length of Event Data.
 *
 * @return Result of Send Message.
 *********************************************************************************************************************/
static bool send_msg_app_task(EN_MSG_MODULE_T enMsgModlue, uint8_t u8Event, void *pu8Data, uint32_t u32Len)
{
    uint32_t u32Timeout = osWaitForever;
    stAppMsg_t stAppMsg;

    if (__get_IPSR())
    {
        // in interrupt
        u32Timeout = 0;
    }
    
    stAppMsg.u8MsgModule = enMsgModlue;
    stAppMsg.u8Event = u8Event;
    stAppMsg.p = pu8Data;
    stAppMsg.u32Length = u32Len;

    osStatus_t Status = osMessageQueuePut(gosMsgId, &stAppMsg, 0, u32Timeout);
    if (osOK == Status)
        return true;
    else
    {
        INFO("Send Message Failed: %d\n", Status);
        return false;
    }
}

/**********************************************************************************************************************
 * @brief  IPC Receice Callback(ISR).
 * @param  u8Cmd: IPC Cmd.
 * @param  pData: Data from Other Core.
 * @param  u16DataLen: The Length of Data.
 *
 * @return None.
 *********************************************************************************************************************/
static void ipc_recv_callback(uint8_t u8Cmd,void *pData,uint16_t u16DataLen)
{
    uint8_t *pu8Data = pData;
    switch(u8Cmd)
    {
        case EN_IPC_CMD_CAL_SUM:
        {
            uint32_t u32SharedMemoryAddr = BUILD_UINT32(pu8Data[0],pu8Data[1],pu8Data[2],pu8Data[3]);
            send_msg_app_task(EN_MSG_MODULE_CAL_UNIT,EN_EVT_CAL_SUM,(void *)u32SharedMemoryAddr,4);
            break;
        }
        
        // ... Other Cmd
        
        default:break;
    }
}

/**********************************************************************************************************************
 * @brief  Calculate Module Process.
 * @param  pstAppMsg: App Message.
 *
 * @return None.
 *********************************************************************************************************************/
static void cal_unit_process(const stAppMsg_t *pstAppMsg)
{
    uint8_t *pu8SharedData = (uint8_t *)pstAppMsg->p;
    
    switch(pstAppMsg->u8Event)
    {
        case EN_EVT_CAL_SUM:
        {
            // sum process
            INFO("Received Shared Data : ");
            for(uint16_t i=0;i<256;i++)
            {
                PRINTF("0x%02X ",pu8SharedData[i]);
                gu32SharedSum += pu8SharedData[i];
            }
            PRINTF("\n");
            
            INFO("Sum of Shared Data: 0x%08X\n",gu32SharedSum);
            
            uint32_t u32SharedSumAddr = (uint32_t)&gu32SharedSum;
            ipc_send(EN_IPC_CMD_CAL_SUM_OK,&u32SharedSumAddr,4);
            
            break;
        }
        case EN_EVT_CAL_FFT:
        {
            // fft process
            break;
        }
        default:break;
    }
}

/**********************************************************************************************************************
 * @brief  CGM Device Application Main.
 * 
 * @return None
 *********************************************************************************************************************/
void app_cgm_mp(void)
{
    osStatus_t status = osOK;
    stAppMsg_t stAppMsg;
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    // Message Queue for Module
    msg_queue_init();
    
    // Initializes Inter-Processor Communication
    enRet = ipc_init(ipc_recv_callback);
    if (ERR_STA_OK != enRet)
        INFO("IPC Init Failed\n");
    
    while(1)
    {
        // Wait Module Message
        status = osMessageQueueGet(gosMsgId, &stAppMsg, NULL, osWaitForever);
        if (osOK != status)
        {
            INFO("CGM Message Queue Get Failed \n");
            continue;
        }
        switch(stAppMsg.u8MsgModule)
        {
            case EN_MSG_MODULE_CAL_UNIT:
            {   
                cal_unit_process(&stAppMsg);
                break;
            }
            default:break;
        }
    }
}
