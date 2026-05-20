/*************************************************************************************************************
 * @file    spi_master.h
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
#ifndef SPI_MASTER_H
#define SPI_MASTER_H

/**
 * @brief  SPI Master Init.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T spi_master_init(void);

/**
 * @brief  SPI Master Reinit.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T spi_master_reinit(void);

/**
 * @brief  SPI Master Deinit.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T spi_master_deinit(void);

/**
 * @brief  SPI Master Transmit Bytes to Slave and Receive Bytes From Slave.
 * @param  u8TxBuf: Send Data Buffer.
 * @param  u8RxBuf: Receive Data Buffer.
 * @param  u16TrxLen: The length of Send and Receive Data Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T spi_master_transmit_receive_bytes(uint8_t *u8TxBuf,uint8_t *u8RxBuf,uint16_t u16TrxLen);

/**
 * @brief  SPI Master Transmit Bytes to Slave.
 * @param  u8TxBuf: Send Data Buffer.
 * @param  u16TxLen: The length of Send Data Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T spi_master_transmit_bytes(uint8_t *u8TxBuf,uint16_t u16TxLen);

/**
 * @brief  SPI Master Receive Bytes From Slave.
 * @param  u8RxBuf: Receive Data Buffer.
 * @param  u16RxLen: The length of Receive Data Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T spi_master_receive_bytes(uint8_t *u8RxBuf,uint16_t u16RxLen);

#endif
