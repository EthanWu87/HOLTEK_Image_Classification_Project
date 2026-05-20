/*************************************************************************************************************
 * @file    gls_meas.h
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
#ifndef GLS_MEAS_H
#define GLS_MEAS_H

/**
 * @brief  Get GLS Measurement Client Characteristic Configuration Descriptor.
 *
 * @return Client Characteristic Configuration Descriptor.
 */
uint8_t gls_meas_get_cfg(void);

/**
 * @brief  Set GLS Measurement Client Characteristic Configuration Descriptor.
 * @param  u8Cfg: Client Characteristic Configuration Descriptor.
 *                  0x00 : Disable
 *                  0x01 : Enable
 * @return None.
 */
void gls_meas_set_cfg(uint8_t u8Cfg);

/**
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: GLS Global Handle.
 * @param  pstRecord: GLS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T gls_meas_send_notify(stGlsHandle_t *pstGlsHandle,const stGlsMeasRec_t *pstRecord);

#endif