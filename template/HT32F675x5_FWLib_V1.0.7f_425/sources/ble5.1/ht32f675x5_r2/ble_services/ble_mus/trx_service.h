/*************************************************************************************************************
 * @file    trx_service.h
 * @version Initial Draft
 * @date    2016-11-15
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

/** @defgroup  profile  serverTxRx
* @{
*/
#ifndef __HT32TXRXSERVICE_H__
#define __HT32TXRXSERVICE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

    
#define HT32_TX_RX_SERVICE_UUID              0xFFF0  //
#define RX_CUS_UUID                         0xFFF2  //
#define TX_CUS_UUID                         0xFFF1  //
#define HT32_TRX_CMD_UUID                    0xFFF3  //
#define HT32_TRX_READ_FOR_ENCPT_UUID                 0xFFF4  //
#define HT32_TRX_BLOBREAD_PREPWRITE_TEST_UUID        0xFFF6  //
#define HT32_TRX_BLOBREAD_PREPWRITE_TEST_UUID2        0xFFFA  //
#define HT32_TRX_INDICATE_UUID                       0xFFF7  //
#define HT32_TRX_NOTIFY_TEST_UUID            0xFFF8
#define HT32_TRX_W_TEST_UUID                 0xFFF9

extern uint16_t txrx_server_receive( uint16_t conn_handle, uint8_t *data, uint16_t length);
extern uint32_t txrx_server_transfer( uint16_t conn_handle, uint8_t *data, uint32_t length);
extern uint16_t  trx_get_attrLenCB( uint16_t conn_handle, uint16_t attribute_handle);
extern uint16_t  trx_read_attrCB( uint16_t conn_handle, uint16_t attribute_handle, uint16_t offset, uint8_t  * buffer, uint16_t  buffer_size);
extern uint32_t trx_write_attrCB( uint16_t conn_handle, uint16_t attribute_handle, uint16_t  transaction_mode, uint16_t offset, uint8_t  *buffer, uint16_t buffer_size);
extern uint32_t trx_init_service( void );
extern uint16_t txrx_cmd_receive( uint16_t conn_handle, uint8_t *data, uint16_t length);

typedef enum TXRX_SRV_HANDLE
{
    TX_WRITE            = 0,
    RX_NOTIFY           = 1,
    RX_NOTIFY_CONFIG    = 2,
    TXRX_CMD            = 3,
    TXRX_CMD_CONFIG        = 4,
    TXRX_READ_FOR_ENCPT    = 5,

} TXRX_SRV_HANDLE_ENUM;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HT32TXRXSERVICE_H__ */
/** @} */ // 模块结尾,自行拷贝到末尾


