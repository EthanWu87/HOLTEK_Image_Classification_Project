/*************************************************************************************************************
 * @file    cgms_socp.c
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
#include <stdbool.h>
#include <string.h>

#include "err_def.h"
#include "app_cfg.h"

#include "gatt_service_api.h"
#include "utility.h"
#include "cgm_service.h"

#include "cgms_socp.h"


#define CGMS_SOCP_RSP_VAL_MAX_LEN                           (18)
#define CGMS_SOCP_OPERAND_MAX_LEN                           (18)

/* CGMS SOCP Opecode */
#define CGMS_SOCP_OPCODE_NULL                               (0x00)
#define CGMS_SOCP_OPCODE_SET_CGM_COMMUNICATION_INTERVAL     (0x01)
#define CGMS_SOCP_OPCODE_GET_CGM_COMMUNICATION_INTERVAL     (0x02)
#define CGMS_SOCP_RESPONSE_GET_CGM_COMMUNICATION_INTERVAL   (0x03)
#define CGMS_SOCP_OPCODE_SET_GLUCOSE_CALIBRATION_VALUE      (0x04)
#define CGMS_SOCP_OPCODE_GET_GLUCOSE_CALIBRATION_VALUE      (0x05)
#define CGMS_SOCP_RESPONSE_GET_GLUCOSE_CALIBRATION_VALUE    (0x06)
#define CGMS_SOCP_OPCODE_SET_PATIENT_HIGH_ALERT_LEVEL       (0x07)
#define CGMS_SOCP_OPCODE_GET_PATIENT_HIGH_ALERT_LEVEL       (0x08)
#define CGMS_SOCP_RESPONSE_GET_PATIENT_HIGH_ALERT_LEVEL     (0x09)
#define CGMS_SOCP_OPCODE_SET_PATIENT_LOW_ALERT_LEVEL        (0x0A)
#define CGMS_SOCP_OPCODE_GET_PATIENT_LOW_ALERT_LEVEL        (0x0B)
#define CGMS_SOCP_RESPONSE_GET_PATIENT_LOW_ALERT_LEVEL      (0x0C)
#define CGMS_SOCP_OPCODE_SET_HYPO_ALERT_LEVEL               (0x0D)
#define CGMS_SOCP_OPCODE_GET_HYPO_ALERT_LEVEL               (0x0E)
#define CGMS_SOCP_RESPONSE_GET_HYPO_ALERT_LEVEL             (0x0F)
#define CGMS_SOCP_OPCODE_SET_HYPER_ALERT_LEVEL              (0x10)
#define CGMS_SOCP_OPCODE_GET_HYPER_ALERT_LEVEL              (0x11)
#define CGMS_SOCP_RESPONSE_GET_HYPER_ALERT_LEVEL            (0x12)
#define CGMS_SOCP_OPCODE_SET_RATE_OF_DECREASE_ALERT_LEVEL   (0x13)
#define CGMS_SOCP_OPCODE_GET_RATE_OF_DECREASE_ALERT_LEVEL   (0x14)
#define CGMS_SOCP_RESPONSE_GET_RATE_OF_DECREASE_ALERT_LEVEL (0x15)
#define CGMS_SOCP_OPCODE_SET_RATE_OF_INCREASE_ALERT_LEVEL   (0x16)
#define CGMS_SOCP_OPCODE_GET_RATE_OF_INCREASE_ALERT_LEVEL   (0x17)
#define CGMS_SOCP_RESPONSE_GET_RATE_OF_INCREASE_ALERT_LEVEL (0x18)
#define CGMS_SOCP_OPCODE_RESET_DEVICE_SPECIFIC_ALERT        (0x19)

#define CGMS_SOCP_OPCODE_START_SESSION                      (0x1A)
#define CGMS_SOCP_OPCODE_STOP_SESSION                       (0x1B)
#define CGMS_SOCP_RESPONSE_CODE                             (0x1C)

/* CGMS SOCP Response Code */
#define CGMS_SOCP_RESPONSE_SUCCESS                          (0x01)
#define CGMS_SOCP_RESPONSE_OP_CODE_NOT_SUPPORTED            (0x02)
#define CGMS_SOCP_RESPONSE_INVALID_OPERAND                  (0x03)
#define CGMS_SOCP_RESPONSE_PROCEDURE_NOT_COMPLETED          (0x04)
#define CGMS_SOCP_RESPONSE_OUT_OF_RANGE                     (0x05)

/* CGMS SOCP Command Type */
typedef struct
{
    uint8_t u8Opcode;
    uint8_t u8Operand[CGMS_SOCP_OPERAND_MAX_LEN];
    uint16_t u16OperandLen;
}stCgmsSocpCmd_t;

/* CGMS SOCP Response Type */
typedef struct
{
    uint8_t u8Opcode;
    uint8_t u8ReqOpcode;
    uint8_t u8RspCode;
    uint8_t u8RspVal[CGMS_SOCP_RSP_VAL_MAX_LEN];
    uint8_t u8RspValLen;
}stCgmsSocpRsp_t;

static uint8_t gu8IsIndicateEnable = 0x02;

/**********************************************************************************************************************
 * @brief  Get CGMS SOCP Client Characteristic Configuration Descriptor.
 *
 * @return Client Characteristic Configuration Descriptor.
 *********************************************************************************************************************/
uint8_t cgms_socp_get_cfg(void)
{
    return gu8IsIndicateEnable;
}

/**********************************************************************************************************************
 * @brief  Set CGMS SOCP Client Characteristic Configuration Descriptor.
 * @param  u8Cfg: Client Characteristic Configuration Descriptor.
 *                  0x00 : Disable
 *                  0x02 : Enable
 * @return None.
 *********************************************************************************************************************/
void cgms_socp_set_cfg(uint8_t u8Cfg)
{
    gu8IsIndicateEnable = (u8Cfg & 0x03);
}

/**********************************************************************************************************************
 * @brief  Send SOCP Response Code by GATT Indicate.
 * @param  pstHandle: CGMS Global Handle.
 * @param  stRspInfo: CGMS SOCP Response Code Information.
 *
 * @return None.
 *********************************************************************************************************************/
static void cgms_socp_send(stCgmsHandle_t *pstHandle,const stCgmsSocpRsp_t *stRspInfo)
{
    uint8_t u8SendBuf[sizeof(stCgmsSocpCmd_t)];
    uint8_t u8DataLen = 0;

    if (0x00 == cgms_socp_get_cfg())
        return;

    if (NULL == pstHandle || NULL == stRspInfo)
        return;

    u8SendBuf[u8DataLen++] = stRspInfo->u8Opcode;

    if ((stRspInfo->u8Opcode != CGMS_SOCP_RESPONSE_GET_CGM_COMMUNICATION_INTERVAL) &&
        (stRspInfo->u8Opcode != CGMS_SOCP_RESPONSE_GET_GLUCOSE_CALIBRATION_VALUE) &&
        (stRspInfo->u8Opcode != CGMS_SOCP_RESPONSE_GET_HYPER_ALERT_LEVEL) &&
        (stRspInfo->u8Opcode != CGMS_SOCP_RESPONSE_GET_HYPO_ALERT_LEVEL) &&
        (stRspInfo->u8Opcode != CGMS_SOCP_RESPONSE_GET_PATIENT_HIGH_ALERT_LEVEL) &&
        (stRspInfo->u8Opcode != CGMS_SOCP_RESPONSE_GET_PATIENT_LOW_ALERT_LEVEL) &&
        (stRspInfo->u8Opcode != CGMS_SOCP_RESPONSE_GET_RATE_OF_DECREASE_ALERT_LEVEL) &&
        (stRspInfo->u8Opcode != CGMS_SOCP_RESPONSE_GET_RATE_OF_INCREASE_ALERT_LEVEL))
    {
        u8SendBuf[u8DataLen++] = stRspInfo->u8ReqOpcode;
        u8SendBuf[u8DataLen++] = stRspInfo->u8RspCode;
    }
    
    for (int i=0;i<stRspInfo->u8RspValLen;i++)
        u8SendBuf[u8DataLen++] = stRspInfo->u8RspVal[i];

    rom_gatts_api_send_indicate(pstHandle->u16ConnHandle,pstHandle->stChrsHandle.u16Socp,u8SendBuf,u8DataLen);

    INFO("SOCP Response : ");
    for (int i=0;i<u8DataLen;i++)
        PRINTF("0x%02X ",u8SendBuf[i]);
    PRINTF("\n");
    
    return;
}

/**********************************************************************************************************************
 * @brief  Parse SOCP Command.
 * @param  pstHandle: CGMS Global Handle.
 * @param  pu8Buf: Source Data Buffer.
 * @param  u16BufSize: Source Data Buffer Size.
 *
 * @return None.
 *********************************************************************************************************************/
void cgms_socp_cmd_parse(stCgmsHandle_t *pstHandle,uint8_t *pu8Buf,uint16_t u16BufSize)
{
    stCgmsSocpCmd_t stCmdInfo = {0};
    stCgmsSocpRsp_t stRspInfo = {0};

    stCmdInfo.u8Opcode = pu8Buf[0];

    if (1 < u16BufSize)
    {
        stCmdInfo.u16OperandLen = (u16BufSize - 1) > CGMS_SOCP_OPERAND_MAX_LEN ? CGMS_SOCP_OPERAND_MAX_LEN : (u16BufSize - 1);
        memcpy(stCmdInfo.u8Operand,&pu8Buf[1],stCmdInfo.u16OperandLen);
    }

    INFO("CGM SOCP Opcode : 0x%02X  Operand : ",stCmdInfo.u8Opcode);
    for (int i=0;i<stCmdInfo.u16OperandLen;i++)
        PRINTF("0x%02X ",stCmdInfo.u8Operand[i]);
    PRINTF("\r\n");


    stRspInfo.u8Opcode = CGMS_SOCP_RESPONSE_CODE;
    stRspInfo.u8ReqOpcode = stCmdInfo.u8Opcode;
    stRspInfo.u8RspCode = CGMS_SOCP_RESPONSE_OP_CODE_NOT_SUPPORTED;
    stRspInfo.u8RspValLen = 0;

    switch(stCmdInfo.u8Opcode)
    {
        case CGMS_SOCP_OPCODE_SET_CGM_COMMUNICATION_INTERVAL:
        {
            stRspInfo.u8RspCode = CGMS_SOCP_RESPONSE_SUCCESS;
            if (stCmdInfo.u16OperandLen != 0 && 0 != stCmdInfo.u8Operand[0])
            {
                pstHandle->u8CommIntv = stCmdInfo.u8Operand[0];
                pstHandle->event_handler(EN_CGMS_EVT_SOCP_SET_COMM_INTV);
            }
            else
                stRspInfo.u8RspCode = CGMS_SOCP_RESPONSE_INVALID_OPERAND;
            break;
        }
        case CGMS_SOCP_OPCODE_GET_CGM_COMMUNICATION_INTERVAL:
        {
            stRspInfo.u8Opcode = CGMS_SOCP_RESPONSE_GET_CGM_COMMUNICATION_INTERVAL;
            stRspInfo.u8RspVal[0] = pstHandle->u8CommIntv;
            stRspInfo.u8RspValLen++;
            break;
        }
        case CGMS_SOCP_OPCODE_START_SESSION:
        {
            if (pstHandle->isSessionStart)
                stRspInfo.u8RspCode = CGMS_SOCP_RESPONSE_PROCEDURE_NOT_COMPLETED;
            else
            {
                memset(&pstHandle->stSst,0,sizeof(stCgmsSessionStartTime_t));
                pstHandle->stStatus.u16TimeOffset = 0;
                pstHandle->stStatus.stStatus.u8Status &= ~CGMS_STATUS_STATUS_SESSION_STOPPED;

                pstHandle->event_handler(EN_CGMS_EVT_SOCP_START_SESSION);

                stRspInfo.u8RspCode = CGMS_SOCP_RESPONSE_SUCCESS;
                pstHandle->isSessionStart = true;
            }
            break;
        }
        case CGMS_SOCP_OPCODE_STOP_SESSION:
        {
            if (false == pstHandle->isSessionStart)
                stRspInfo.u8RspCode = CGMS_SOCP_RESPONSE_SUCCESS;
            else
            {
                stRspInfo.u8RspCode = CGMS_SOCP_RESPONSE_SUCCESS;
                pstHandle->isSessionStart = false;

                pstHandle->stStatus.stStatus.u8Status |= CGMS_STATUS_STATUS_SESSION_STOPPED;

                pstHandle->event_handler(EN_CGMS_EVT_SOCP_STOP_SESSION);
            }
            break;
        }
        default:
            break;
    }

    // Response
    cgms_socp_send(pstHandle,&stRspInfo);
}

