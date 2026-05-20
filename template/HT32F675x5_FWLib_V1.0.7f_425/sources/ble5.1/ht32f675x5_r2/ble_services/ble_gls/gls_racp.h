/*************************************************************************************************************
 * @file    gls_racp.h
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
#ifndef GLS_RACP_H
#define GLS_RACP_H



#define GLS_RACP_RSP_BUF_LEN                            (25)
#define GLS_RACP_OPERAND_FILTER_TYPE_IDX                (0)
#define GLS_RACP_OPERAND_FILTER_PARAM_IDX               (1)
        
#define GLS_RACP_OPERAND_FILTER_TYPE_LEN                (1)
#define GLS_RACP_OPERAND_FILTER_PARAM_LEN               (2)
#define GLS_RACP_GREATER_OR_LESS_OPERAND_LEN            (GLS_RACP_OPERAND_FILTER_TYPE_LEN + GLS_RACP_OPERAND_FILTER_PARAM_LEN)
#define GLS_RACP_WITHIN_RANGE_OF_OPERAND_LEN            (GLS_RACP_OPERAND_FILTER_TYPE_LEN + 2 * GLS_RACP_OPERAND_FILTER_PARAM_LEN)

/* RACP Opcode */
#define GLS_RACP_OPCODE_RESERVED                        (0x00)
#define GLS_RACP_OPCODE_REPORT_STORED_RECORDS           (0x01)
#define GLS_RACP_OPCODE_DELETE_STORED_RECORDS           (0x02)
#define GLS_RACP_OPCODE_ABORT_OPERATION                 (0x03)
#define GLS_RACP_OPCODE_REPORT_NUM_OF_STORED_RECORDS    (0x04)
#define GLS_RACP_OPCODE_RESPONSE_NUM_OF_STROED_RECORDS  (0x05)
#define GLS_RACP_OPCODE_RESPONSE_CODE                   (0x06)

/* RACP Operator */
#define GLS_RACP_OPERATOR_NULL                          (0x00)
#define GLS_RACP_OPERATOR_ALL                           (0x01)
#define GLS_RACP_OPERATOR_LESS_OR_EQUAL                 (0x02)
#define GLS_RACP_OPERATOR_GREATER_OR_EQUAL              (0x03)
#define GLS_RACP_OPERATOR_WITHIN_RANGE_OF               (0x04)
#define GLS_RACP_OPERATOR_FIRST_RECORD                  (0x05)
#define GLS_RACP_OPERATOR_LAST_RECORD                   (0x06)
#define GLS_RACP_OPERATOR_RESERVED                      (0x07)
    
/* RACP Operand Filter Type */  
#define GLS_RACP_OPERAND_FILTER_TYPE_RESERVED           (0x00)
#define GLS_RACP_OPERAND_FILTER_TYPE_SEQUENCE_NUMBER    (0x01)
#define GLS_RACP_OPERAND_FILTER_TYPE_FACING_TIME        (0x02)  /* Within GLS Service Not Allowed */
    
/* RACP Response Code */    
#define GLS_RACP_RESPONSE_RESERVED                      (0x00)
#define GLS_RACP_RESPONSE_SUCCESS                       (0x01)
#define GLS_RACP_RESPONSE_OPCODE_UNSUPPORTED            (0x02)
#define GLS_RACP_RESPONSE_INVALID_OPERATOR              (0x03)
#define GLS_RACP_RESPONSE_OPERATOR_UNSUPPORTED          (0x04)
#define GLS_RACP_RESPONSE_INVALID_OPERAND               (0x05)
#define GLS_RACP_RESPONSE_NO_RECORDS_FOUND              (0x06)
#define GLS_RACP_RESPONSE_ABORT_FAILED                  (0x07)
#define GLS_RACP_RESPONSE_PROCEDURE_NOT_DONE            (0x08)
#define GLS_RACP_RESPONSE_OPERAND_UNSUPPORTED           (0x09)

/**
 * @brief  Get GLS RACP Client Characteristic Configuration Descriptor.
 *
 * @return Client Characteristic Configuration Descriptor.
 */
uint8_t gls_racp_get_cfg(void);

/**
 * @brief  Set GLS RACP Client Characteristic Configuration Descriptor.
 * @param  u8Cfg: Client Characteristic Configuration Descriptor.
 *                0x00 : Disable
 *                0x02 : Enable
 * @return None.
 */
void gls_racp_set_cfg(uint8_t u8Cfg);

/**
 * @brief  Parse RACP Command.
 * @param  pstHandle: GLS Global Handle.
 * @param  pu8Buf: Source Data Buffer.
 * @param  u16BufSize: Source Data Buffer Size.
 *
 * @return None.
 */
void gls_racp_cmd_parse(stGlsHandle_t *pstHandle,uint8_t *pu8Buf,uint16_t u16BufSize);

/**
 * @brief  Send RACP Response Code by GATT Indicate.
 * @param  pstHandle: GLS Global Handle.
 * @param  u8Opcode: GLS RACP Response Opcode.Must be GLS_RACP_OPCODE_RESPONSE_NUM_OF_STROED_RECORDS or GLS_RACP_OPCODE_RESPONSE_CODE
 *                   Operand is Requset Code and Response Code When u8Opcode is GLS_RACP_OPCODE_RESPONSE_CODE.
 *                   Operand is Number of GLS Measurement Records When u8Opcode is GLS_RACP_OPCODE_RESPONSE_NUM_OF_STROED_RECORDS.
 * @param  u8Operand1: GLS RACP Response Operand.
 * @param  u8Operand2: GLS RACP Response Operand.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T gls_racp_rsp_code_send(stGlsHandle_t *pstHandle,uint8_t u8Opcode,uint8_t u8Operand1,uint8_t u8Operand2);

#endif
