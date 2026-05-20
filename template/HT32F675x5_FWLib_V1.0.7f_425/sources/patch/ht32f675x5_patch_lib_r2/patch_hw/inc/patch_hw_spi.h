/*************************************************************************************************************
 * @file    patch_hw_spi.h
 * @version V1.2
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


#ifndef __PATCH_HW_SPI_H__
#define __PATCH_HW_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************************************************
 * @brief  Send a data buffer to SPI bus with indicated length, and receive the same length of data
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1
 * @param  pu8TxBuf: Point to tx buffer This arguments can set to NULL, when SPI work at RX_ONLY mode.
 * @param  pu8RxBuf: Point to rx buffer. This arguments can set to NULL, when SPI work at TX_ONLY mode.
 * @param  u16TxLen: The Length which will be send out
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
extern EN_ERR_STA_T patch_hw_spi_transmit_bytes(stSPI_Handle_t *pstSPI, uint8_t *pu8TxBuf, uint8_t *pu8RxBuf,
                                                    uint16_t u16TrxLen);

#ifdef __cplusplus
}
#endif

#endif