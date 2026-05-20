/*************************************************************************************************************
 * @file    cgms_socp.h
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
#ifndef CGMS_SOCP_H
#define CGMS_SOCP_H

/**
 * @brief  Get CGMS SOCP Client Characteristic Configuration Descriptor.
 *
 * @return Client Characteristic Configuration Descriptor.
 */
uint8_t cgms_socp_get_cfg(void);

/**
 * @brief  Set CGMS SOCP Client Characteristic Configuration Descriptor.
 * @param  u8Cfg: Client Characteristic Configuration Descriptor.
 *                0x00 : Disable
 *                0x02 : Enable
 * @return None.
 */
void cgms_socp_set_cfg(uint8_t u8Cfg);

/**
 * @brief  Parse SOCP Command.
 * @param  pstHandle: CGMS Global Handle.
 * @param  pu8Buf: Source Data Buffer.
 * @param  u16BufSize: Source Data Buffer Size.
 *
 * @return None.
 */
void cgms_socp_cmd_parse(stCgmsHandle_t *stHandle,uint8_t *pu8Buf,uint16_t u16BufSize);




#endif
