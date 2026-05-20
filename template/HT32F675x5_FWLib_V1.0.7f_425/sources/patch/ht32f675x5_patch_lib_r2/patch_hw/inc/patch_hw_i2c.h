/*************************************************************************************************************
 * @file    patch_hw_i2c.h
 * @version V1.0
 * @date    2024-05-21
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


#ifndef __PATCH_HW_I2C_H__
#define __PATCH_HW_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    EN_I2C_MASTER_STAT_OK,
    EN_I2C_MASTER_STAT_PARA_ERR,
    EN_I2C_MASTER_STAT_NACK_ON_TRANSMIT_ADDR,
    EN_I2C_MASTER_STAT_NACK_ON_TRANSMIT_DATA,
    EN_I2C_MASTER_STAT_TIMEOUT,
}EN_I2C_MASTER_STAT_T;

/**
 * @brief  I2C master send stop bit
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @return status: @ref EN_ERR_STA_T
 */
extern EN_ERR_STA_T patch_hw_i2c_master_send_stop(stI2C_Handle_t *pstI2C);

/**
 * @brief  Read multiple bytes from I2C slave, no reg addr.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  pu8RxBuf: Pointer to a buffer which used to save the read data.
 * @param  u16Len: Length of read data
 * @param  u8SendStop: Decide whether to send stop bit
 * @return status: @ref EN_I2C_MASTER_STAT_T.
 */
extern EN_I2C_MASTER_STAT_T patch_hw_i2c_master_read(stI2C_Handle_t *pstI2C, uint8_t *pu8RxBuf, uint16_t u16Len,uint8_t u8SendStop);

/**
 * @brief  Write multiple bytes to I2C slave.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  pu8TxBuf: Pointer to a buffer which used to write.
 * @param  u16Len: Length of write data
 * @param  u8SendStop: Decide whether to send stop bit
 * @return status: @ref EN_I2C_MASTER_STAT_T.
 */
extern EN_I2C_MASTER_STAT_T patch_hw_i2c_master_write(stI2C_Handle_t *pstI2C, uint8_t *pu8TxBuf, uint16_t u16Len,uint8_t u8SendStop);

/**
 * @brief  Write multiple bytes to I2C master.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  pu8TxBuf: Pointer to a buffer which used to write.
 * @param  u16Len: Length of write data
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T patch_hw_i2c_slave_write(stI2C_Handle_t *pstI2C, uint8_t *pu8TxBuf, uint16_t u16Len);

#ifdef __cplusplus
}
#endif

#endif