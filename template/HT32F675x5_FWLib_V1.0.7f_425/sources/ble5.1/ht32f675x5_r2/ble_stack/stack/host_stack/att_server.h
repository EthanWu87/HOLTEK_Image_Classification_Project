/*************************************************************************************************************
 * @file    att_server.h
 * @version V1.0.0
 * @date    2016-11-18
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


#ifndef __ATT_SERVER_H
#define __ATT_SERVER_H



// MARK: Attribute PDU Opcodes
#define ATT_ERROR_RESPONSE              0x01

#define ATT_EXCHANGE_MTU_REQUEST        0x02
#define ATT_EXCHANGE_MTU_RESPONSE       0x03

#define ATT_FIND_INFORMATION_REQUEST    0x04
#define ATT_FIND_INFORMATION_REPLY      0x05
#define ATT_FIND_BY_TYPE_VALUE_REQUEST  0x06
#define ATT_FIND_BY_TYPE_VALUE_RESPONSE 0x07

#define ATT_READ_BY_TYPE_REQUEST        0x08
#define ATT_READ_BY_TYPE_RESPONSE       0x09
#define ATT_READ_REQUEST                0x0a
#define ATT_READ_RESPONSE               0x0b
#define ATT_READ_BLOB_REQUEST           0x0c
#define ATT_READ_BLOB_RESPONSE          0x0d
#define ATT_READ_MULTIPLE_REQUEST       0x0e
#define ATT_READ_MULTIPLE_RESPONSE      0x0f
#define ATT_READ_BY_GROUP_TYPE_REQUEST  0x10
#define ATT_READ_BY_GROUP_TYPE_RESPONSE 0x11

#define ATT_WRITE_REQUEST               0x12
#define ATT_WRITE_RESPONSE              0x13

#define ATT_PREPARE_WRITE_REQUEST       0x16
#define ATT_PREPARE_WRITE_RESPONSE      0x17
#define ATT_EXECUTE_WRITE_REQUEST       0x18
#define ATT_EXECUTE_WRITE_RESPONSE      0x19

#define ATT_HANDLE_VALUE_NOTIFICATION   0x1b
#define ATT_HANDLE_VALUE_INDICATION     0x1d
#define ATT_HANDLE_VALUE_CONFIRMATION   0x1e


#define ATT_WRITE_COMMAND                0x52
#define ATT_SIGNED_WRITE_COMMAND         0xD2

// typedef enum
// {
//     MTU_IS_NOT_EXCHANGED,
//     MTU_IS_EXCHANGING,
//     MTU_IS_EXCHANGED,
// }MTU_EXCHANGE_STATE_E;

// typedef struct
// {
//     //stAppTimerNode_t att_transacton_timer;
//     uint32_t att_transacton_timer_param;
//     uint16_t mtu;       // initialized to ATT_DEFAULT_MTU (23), negotiated during MTU exchange
//     uint16_t max_mtu;   // local maximal L2CAP_MTU, set to l2cap_max_le_mtu()
//     uint8_t mtu_exchange_state;   //see @MTU_EXCHANGE_STATE_E
//     uint8_t connection_state;
// }__attribute__((aligned(4))) att_cfg_t;


extern int rom_gatt_client_run ( t_gatt_client * p_gatt_state );
extern void rom_gatt_client_handle_value_notification ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_exchange_mtu_response ( uint16_t conn_handle,   uint16_t mtu );
extern void rom_gatt_client_handle_read_by_group_type_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_value_indication ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_read_by_type_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_read_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_find_by_type_value_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_find_information_reply ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_write_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_read_blob_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_prepare_write_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_execute_write_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_read_multiple_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );
extern void rom_gatt_client_handle_error_response ( t_gatt_client * p_gatt_state, uint8_t* packet, uint16_t size );

extern void gatt_timeout_handler ( void* idx_ptr );


extern uint8_t rom_att_server_notify( uint16_t con_handle, uint16_t attribute_handle, uint8_t *value, uint16_t value_len );


extern uint8_t rom_att_server_indicate( uint16_t con_handle, uint16_t attribute_handle, uint8_t *value, uint16_t value_len);

//extern void rom_att_packet_handler(uint16_t conn_handle, uint8_t *packet, uint16_t size);

extern uint8_t att_exchange_mtu_request(uint16_t con_handle );

extern void rom_att_signed_write_handle_cmac_result(uint8_t hash[16]);
// extern void att_indication_timeout_stop(uint8_t idx); //Previously modified.
extern void att_auto_exchange_mtu_onoff(int onoff);
extern uint8_t rom_att_exchange_mtu_request_api(uint16_t con_handle ,uint16_t mtu);
extern void att_wakeup_during_latency_onoff(int onoff);
  
extern void rom_att_event_encrypt_change ( uint16_t u16ConnHandle,uint8_t authenticated ,uint8_t encryption_key_size ,uint8_t authorized ); 
extern void rom_att_event_conn_commpelete(att_connection_t * p_att_state);
extern void rom_att_event_disconn_commpelete(att_connection_t * p_att_state);
bool rom_att_tx_buffer_commit ( uint16_t con_handle, uint8_t *p_data, uint16_t data_size );
uint16_t rom_att_get_mtu ( uint16_t con_handle );

//extern int32_t g_att_suppress_mtu_exchange_auto  ;
#endif // __ATT_SERVER_H
