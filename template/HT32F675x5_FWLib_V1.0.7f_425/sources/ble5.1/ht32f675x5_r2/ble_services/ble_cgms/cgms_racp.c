/*************************************************************************************************************
 * @file    cgms_racp.c
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
#include "cgm_service.h"
#include "utility.h"

#include "cgms_racp.h"


static uint8_t gu8IsIndicateEnable = 0x02;

/**********************************************************************************************************************
 * @brief  Get CGMS RACP Client Characteristic Configuration Descriptor.
 *
 * @return Client Characteristic Configuration Descriptor.
 *********************************************************************************************************************/
uint8_t cgms_racp_get_cfg(void)
{
    return gu8IsIndicateEnable;
}

/**********************************************************************************************************************
 * @brief  Set CGMS RACP Client Characteristic Configuration Descriptor.
 * @param  u8Cfg: Client Characteristic Configuration Descriptor.
 *                  0x00 : Disable
 *                  0x02 : Enable
 * @return None.
 *********************************************************************************************************************/
void cgms_racp_set_cfg(uint8_t u8Cfg)
{
    gu8IsIndicateEnable = (u8Cfg & 0x03);
}

/**********************************************************************************************************************
 * @brief  Send RACP Response Code by GATT Indicate.
 * @param  pstHandle: CGMS Global Handle.
 * @param  stRspInfo: CGMS RACP Response Code Information.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T cgms_racp_send(stCgmsHandle_t *pstHandle,const stCgmsRacpVal_t *stRspInfo)
{
    uint8_t u8RspBuf[CGMS_RACP_RSP_BUF_LEN];
    uint16_t u16Len = 0;
    uint32_t u32Ret;

    if (NULL == pstHandle || NULL == stRspInfo)
        return ERR_STA_ERROR;

    if (0x00 == cgms_racp_get_cfg())
        return ERR_STA_OK;

    u8RspBuf[u16Len++] = stRspInfo->u8Opcode;
    u8RspBuf[u16Len++] = stRspInfo->u8Operator;

    for (int i=0;i<stRspInfo->u8OperandLen;i++)
        u8RspBuf[u16Len++] = stRspInfo->u8Operand[i];

    u32Ret = rom_gatts_api_send_indicate(pstHandle->u16ConnHandle,pstHandle->stChrsHandle.u16Racp,u8RspBuf,u16Len);
    if (0 != u32Ret)
        return ERR_STA_ERROR;
    return ERR_STA_OK;
}


/**********************************************************************************************************************
 * @brief  Send RACP Response Code by GATT Indicate.
 * @param  pstHandle: CGMS Global Handle.
 * @param  u8Opcode: CGMS RACP Response Opcode.Must be CGMS_RACP_OPCODE_RESPONSE_NUM_OF_STROED_RECORDS or CGMS_RACP_OPCODE_RESPONSE_CODE
 *                   Operand is Requset Code and Response Code When u8Opcode is CGMS_RACP_OPCODE_RESPONSE_CODE.
 *                   Operand is Number of CGMS Measurement Records When u8Opcode is CGMS_RACP_OPCODE_RESPONSE_NUM_OF_STROED_RECORDS.
 * @param  u8Operand1: CGMS RACP Response Operand.
 * @param  u8Operand2: CGMS RACP Response Operand.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T cgms_racp_rsp_code_send(stCgmsHandle_t *pstHandle,uint8_t u8Opcode,uint8_t u8Operand1,uint8_t u8Operand2)
{
    stCgmsRacpVal_t stRspInfo = {0};

    stRspInfo.u8Opcode = u8Opcode;
    stRspInfo.u8Operator = CGMS_RACP_OPERATOR_NULL;
    stRspInfo.u8Operand[stRspInfo.u8OperandLen++] = u8Operand1;
    stRspInfo.u8Operand[stRspInfo.u8OperandLen++] = u8Operand2;

    return cgms_racp_send(pstHandle,&stRspInfo);
}

/**********************************************************************************************************************
 * @brief  Check RACP Command.
 * @param  stCmdInfo: CGMS RACP Command Information.
 * @param  bRacpState: CGMS RACP Running State.
 * @param  u8RspCode: CGMS RACP Command Response Code.
 *
 * @return Result of Check.
 *********************************************************************************************************************/
static bool cgms_racp_cmd_check(const stCgmsRacpVal_t *stCmdInfo,bool bRacpState,uint8_t *u8RspCode)
{
    /* CGMS RACP Running State */
    if (bRacpState)
    {
        if (CGMS_RACP_OPCODE_ABORT_OPERATION != stCmdInfo->u8Opcode )
            return false;

        if (CGMS_RACP_OPERATOR_NULL != stCmdInfo->u8Operator)
            *u8RspCode = CGMS_RACP_RESPONSE_INVALID_OPERATOR;
        else if (0 != stCmdInfo->u8OperandLen)
            *u8RspCode = CGMS_RACP_RESPONSE_OPERAND_UNSUPPORTED;
        else
            *u8RspCode = CGMS_RACP_RESPONSE_SUCCESS;
    }
    /* CGMS RACP Not Running State */
    else
    {
        if (CGMS_RACP_OPCODE_ABORT_OPERATION == stCmdInfo->u8Opcode)
            *u8RspCode = CGMS_RACP_RESPONSE_ABORT_FAILED;
        else if ((CGMS_RACP_OPCODE_REPORT_STORED_RECORDS == stCmdInfo->u8Opcode) ||
                (CGMS_RACP_OPCODE_REPORT_NUM_OF_STORED_RECORDS == stCmdInfo->u8Opcode))
        {
            switch(stCmdInfo->u8Operator)
            {
                case CGMS_RACP_OPERATOR_ALL:
                case CGMS_RACP_OPERATOR_FIRST_RECORD:
                case CGMS_RACP_OPERATOR_LAST_RECORD:
                {
                    if (0 != stCmdInfo->u8OperandLen)
                        *u8RspCode = CGMS_RACP_RESPONSE_INVALID_OPERAND;
                    break;
                }

                case CGMS_RACP_OPERATOR_LESS_OR_EQUAL:
                case CGMS_RACP_OPERATOR_GREATER_OR_EQUAL:
                {
                    /* Operand Len or Operand Filter Type Error */
                    if (CGMS_RACP_GREATER_OR_LESS_OPERAND_LEN != stCmdInfo->u8OperandLen)
                        *u8RspCode = CGMS_RACP_RESPONSE_INVALID_OPERAND;
                    else if (CGMS_RACP_OPERAND_FILTER_TYPE_FACING_TIME == stCmdInfo->u8Operand[0])
                        *u8RspCode = CGMS_RACP_RESPONSE_OPERAND_UNSUPPORTED;
                    else if (CGMS_RACP_OPERAND_FILTER_TYPE_RESERVED == stCmdInfo->u8Operand[0])
                        *u8RspCode = CGMS_RACP_RESPONSE_PROCEDURE_NOT_DONE;
                    break;
                }
                case CGMS_RACP_OPERATOR_WITHIN_RANGE_OF:
                {
                    /* Operand Len or Operand Filter Type Error */
                    if (CGMS_RACP_WITHIN_RANGE_OF_OPERAND_LEN != stCmdInfo->u8OperandLen)
                        *u8RspCode = CGMS_RACP_RESPONSE_INVALID_OPERAND;
                    else if (CGMS_RACP_OPERAND_FILTER_TYPE_FACING_TIME == stCmdInfo->u8Operand[0])
                        *u8RspCode = CGMS_RACP_RESPONSE_OPERAND_UNSUPPORTED;
                    else if (CGMS_RACP_OPERAND_FILTER_TYPE_RESERVED == stCmdInfo->u8Operand[0])
                        *u8RspCode = CGMS_RACP_RESPONSE_PROCEDURE_NOT_DONE;
                    break;
                }
                case CGMS_RACP_OPERATOR_NULL:
                    *u8RspCode = CGMS_RACP_RESPONSE_INVALID_OPERATOR;
                    break;
                default:
                    *u8RspCode = CGMS_RACP_RESPONSE_OPERATOR_UNSUPPORTED;
                    break;
            }
        }
        else if (CGMS_RACP_OPCODE_DELETE_STORED_RECORDS == stCmdInfo->u8Opcode)
        {
            switch(stCmdInfo->u8Operator)
            {
                case CGMS_RACP_OPERATOR_ALL:
                case CGMS_RACP_OPERATOR_FIRST_RECORD:
                case CGMS_RACP_OPERATOR_LAST_RECORD:
                {
                    if (0 != stCmdInfo->u8OperandLen)
                        *u8RspCode = CGMS_RACP_RESPONSE_INVALID_OPERAND;
                    break;
                }
                case CGMS_RACP_OPERATOR_LESS_OR_EQUAL:
                case CGMS_RACP_OPERATOR_GREATER_OR_EQUAL:
                {
                    /* Operand Len or Operand Filter Type Error */
                    if (CGMS_RACP_GREATER_OR_LESS_OPERAND_LEN != stCmdInfo->u8OperandLen)
                        *u8RspCode = CGMS_RACP_RESPONSE_INVALID_OPERAND;
                    else if (CGMS_RACP_OPERAND_FILTER_TYPE_FACING_TIME == stCmdInfo->u8Operand[0])
                        *u8RspCode = CGMS_RACP_RESPONSE_OPERAND_UNSUPPORTED;
                    else if (CGMS_RACP_OPERAND_FILTER_TYPE_RESERVED == stCmdInfo->u8Operand[0])
                        *u8RspCode = CGMS_RACP_RESPONSE_PROCEDURE_NOT_DONE;
                    break;
                }
                case CGMS_RACP_OPERATOR_WITHIN_RANGE_OF:
                {
                    /* Operand Len or Operand Filter Type Error */
                    if (CGMS_RACP_WITHIN_RANGE_OF_OPERAND_LEN != stCmdInfo->u8OperandLen)
                        *u8RspCode = CGMS_RACP_RESPONSE_INVALID_OPERAND;
                    else if (CGMS_RACP_OPERAND_FILTER_TYPE_FACING_TIME == stCmdInfo->u8Operand[0])
                        *u8RspCode = CGMS_RACP_RESPONSE_OPERAND_UNSUPPORTED;
                    else if (CGMS_RACP_OPERAND_FILTER_TYPE_RESERVED == stCmdInfo->u8Operand[0])
                        *u8RspCode = CGMS_RACP_RESPONSE_PROCEDURE_NOT_DONE;
                    break;
                }
                case CGMS_RACP_OPERATOR_NULL:
                    *u8RspCode = CGMS_RACP_RESPONSE_INVALID_OPERATOR;
                    break;
                default:
                    *u8RspCode = CGMS_RACP_RESPONSE_OPERATOR_UNSUPPORTED;
                    break;
            }
        }
        else
            *u8RspCode = CGMS_RACP_RESPONSE_OPCODE_UNSUPPORTED;
    }
    return (*u8RspCode == CGMS_RACP_RESPONSE_RESERVED);
}

/**********************************************************************************************************************
 * @brief  Parse RACP Command.
 * @param  pstHandle: CGMS Global Handle.
 * @param  pu8Buf: Source Data Buffer.
 * @param  u16BufSize: Source Data Buffer Size.
 *
 * @return None.
 *********************************************************************************************************************/
void cgms_racp_cmd_parse(stCgmsHandle_t *pstHandle,uint8_t *pu8Buf,uint16_t u16BufSize)
{
    uint8_t u8RspCode = CGMS_RACP_RESPONSE_RESERVED;
    stCgmsRacpVal_t *stCmdInfo = &pstHandle->stRacpCmdInfo;
    
    memset(stCmdInfo,0,sizeof(stCgmsRacpVal_t));
    
    stCmdInfo->u8Opcode = pu8Buf[0];
    
    if (1 < u16BufSize)
        stCmdInfo->u8Operator = pu8Buf[1];
    if (2 < u16BufSize)
    {
        stCmdInfo->u8OperandLen = (u16BufSize - 2) > CGMS_RACP_OPERAND_MAX_LEN ? CGMS_RACP_OPERAND_MAX_LEN : (u16BufSize - 2);
        memcpy(stCmdInfo->u8Operand,&pu8Buf[2],stCmdInfo->u8OperandLen);
    }
    
    INFO("CGMS RACP Opcode : 0x%02X  Operator : 0x%02X Operand : ",stCmdInfo->u8Opcode,stCmdInfo->u8Operator);
    for (int i=0;i<stCmdInfo->u8OperandLen;i++)
        PRINTF("0x%02X ",stCmdInfo->u8Operand[i]);
    PRINTF("\r\n");
    
    if (cgms_racp_cmd_check(stCmdInfo,pstHandle->isRacpRunning,&u8RspCode))
    {
        pstHandle->isRacpRunning = true;
        if (CGMS_RACP_OPCODE_REPORT_STORED_RECORDS == stCmdInfo->u8Opcode)
            pstHandle->event_handler(EN_CGMS_EVT_RACP_REPORT_RECORDS);
        else if (CGMS_RACP_OPCODE_REPORT_NUM_OF_STORED_RECORDS == stCmdInfo->u8Opcode)
            pstHandle->event_handler(EN_CGMS_EVT_RACP_REPORT_NUM_OF_RECORDS);
        else if (CGMS_RACP_OPCODE_DELETE_STORED_RECORDS == stCmdInfo->u8Opcode)
            pstHandle->event_handler(EN_CGMS_EVT_RACP_DELETE_STORED_RECORDS);
        else
        {
            // Unknown Status
            INFO("CGMS RACP ERROR : Unknown Status\n");
            pstHandle->isRacpRunning = false;
            return;
        }
    }
    else if (CGMS_RACP_RESPONSE_RESERVED != u8RspCode)
    {
        pstHandle->isRacpRunning = false;
        cgms_racp_rsp_code_send(pstHandle,CGMS_RACP_OPCODE_RESPONSE_CODE,stCmdInfo->u8Opcode,u8RspCode);
        INFO("CGMS RACP Invalid Command\n");
    }
    else
    {
        // Ignore
        INFO("CGMS RACP Ignore Command\n");
    }
}

