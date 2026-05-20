/*************************************************************************************************************
 * @file    host_stack_conn_hdl.h
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

typedef struct stack_timer_source {
    void*  timer_handle; 
    uint32_t timer_active;
    uint32_t u32TimeMs;
    // will be called when timer fired
    void  (*pfnProcess)(void* param); 
    void * pContext;
} stack_timer_source_t;

typedef enum
{
    P_READY,
    P_W2_SEND_SERVICE_QUERY,/*1*/
    P_W4_SERVICE_QUERY_RESULT,
    P_W2_SEND_SERVICE_WITH_UUID_QUERY,
    P_W4_SERVICE_WITH_UUID_RESULT,
    P_W2_SEND_MTU_EXCHG,
    P_W4_MTU_EXCHG_RESULT,

    P_W2_SEND_ALL_CHARACTERISTICS_OF_SERVICE_QUERY,/*5*/
    P_W4_ALL_CHARACTERISTICS_OF_SERVICE_QUERY_RESULT,
    P_W2_SEND_CHARACTERISTIC_WITH_UUID_QUERY,
    P_W4_CHARACTERISTIC_WITH_UUID_QUERY_RESULT,

    P_W2_SEND_ALL_CHARACTERISTIC_DESCRIPTORS_QUERY,
    P_W4_ALL_CHARACTERISTIC_DESCRIPTORS_QUERY_RESULT,

    P_W2_SEND_INCLUDED_SERVICE_QUERY,/*0xB*/
    P_W4_INCLUDED_SERVICE_QUERY_RESULT,
    P_W2_SEND_INCLUDED_SERVICE_WITH_UUID_QUERY,
    P_W4_INCLUDED_SERVICE_UUID_WITH_QUERY_RESULT,

    P_W2_SEND_READ_CHARACTERISTIC_VALUE_QUERY,
    P_W4_READ_CHARACTERISTIC_VALUE_RESULT,

    P_W2_SEND_READ_BLOB_QUERY,/*0x11*/
    P_W4_READ_BLOB_RESULT,

    P_W2_SEND_READ_BY_TYPE_REQUEST,
    P_W4_READ_BY_TYPE_RESPONSE,

    P_W2_SEND_READ_MULTIPLE_REQUEST,
    P_W4_READ_MULTIPLE_RESPONSE,

    P_W2_SEND_WRITE_CHARACTERISTIC_VALUE,/*0x17*/
    P_W4_WRITE_CHARACTERISTIC_VALUE_RESULT,

    P_W2_PREPARE_WRITE,
    P_W4_PREPARE_WRITE_RESULT,
    P_W2_PREPARE_RELIABLE_WRITE,
    P_W4_PREPARE_RELIABLE_WRITE_RESULT,

    P_W2_EXECUTE_PREPARED_WRITE,/*0x1D*/
    P_W4_EXECUTE_PREPARED_WRITE_RESULT,
    P_W2_CANCEL_PREPARED_WRITE,
    P_W4_CANCEL_PREPARED_WRITE_RESULT,
    P_W2_CANCEL_PREPARED_WRITE_DATA_MISMATCH,
    P_W4_CANCEL_PREPARED_WRITE_DATA_MISMATCH_RESULT,

    P_W2_SEND_READ_CLIENT_CHARACTERISTIC_CONFIGURATION_QUERY,/*0x23*/
    P_W4_READ_CLIENT_CHARACTERISTIC_CONFIGURATION_QUERY_RESULT,
    P_W2_WRITE_CLIENT_CHARACTERISTIC_CONFIGURATION,
    P_W4_CLIENT_CHARACTERISTIC_CONFIGURATION_RESULT,

    P_W2_SEND_READ_CHARACTERISTIC_DESCRIPTOR_QUERY,
    P_W4_READ_CHARACTERISTIC_DESCRIPTOR_RESULT,

    P_W2_SEND_READ_BLOB_CHARACTERISTIC_DESCRIPTOR_QUERY,
    P_W4_READ_BLOB_CHARACTERISTIC_DESCRIPTOR_RESULT,/*0x2A*/

    P_W2_SEND_WRITE_CHARACTERISTIC_DESCRIPTOR,
    P_W4_WRITE_CHARACTERISTIC_DESCRIPTOR_RESULT,

    // all long writes use this
    P_W2_PREPARE_WRITE_CHARACTERISTIC_DESCRIPTOR,
    P_W4_PREPARE_WRITE_CHARACTERISTIC_DESCRIPTOR_RESULT,
    P_W2_EXECUTE_PREPARED_WRITE_CHARACTERISTIC_DESCRIPTOR,
    P_W4_EXECUTE_PREPARED_WRITE_CHARACTERISTIC_DESCRIPTOR_RESULT,/*0x30*/

    // gatt reliable write API use this (manual version of the above)
    P_W2_PREPARE_WRITE_SINGLE,
    P_W4_PREPARE_WRITE_SINGLE_RESULT,

    P_W4_CMAC_READY,
    P_W4_CMAC_RESULT,
    P_W2_SEND_SIGNED_WRITE,
    P_W4_SEND_SINGED_WRITE_DONE,
} gatt_client_state_t;




typedef enum
{
    CENTRAL_IDLE,
    CENTRAL_W4_NAME_QUERY_COMPLETE,
    CENTRAL_W4_NAME_VALUE,
    CENTRAL_W4_MTU_EXCHG,
    CENTRAL_W4_RECONNECTION_ADDRESS_QUERY_COMPLETE,
    CENTRAL_W4_PERIPHERAL_PRIVACY_FLAG_QUERY_COMPLETE,
    CENTRAL_W4_SIGNED_WRITE_QUERY_COMPLETE,
    CENTRAL_W4_PRIMARY_SERVICES_ALL,
    CENTRAL_W4_PRIMARY_SERVICES_ONE_BY_UUID,
    CENTRAL_W4_INCLUDED_SERVICE_QUERY,
    CENTRAL_ENTER_SERVICE_UUID_4_DISCOVER_CHARACTERISTICS,
    CENTRAL_ENTER_START_HANDLE_4_DISCOVER_CHARACTERISTICS,
    CENTRAL_ENTER_END_HANDLE_4_DISCOVER_CHARACTERISTICS,
    CENTRAL_W4_DISCOVER_CHARACTERISTICS_ALL_FOR_A_SERVICE,
    CENTRAL_W4_DISCOVER_CHARACTERISTICS_ONE_BY_UUID,
    CENTRAL_W4_CHARACTERISTICS,
    CENTRAL_W4_DISCOVER_CHARACTERISTIC_DESCRIPTORS,
    CENTRAL_W4_READ_CHARACTERISTIC_VALUE_BY_HANDLE,
    CENTRAL_ENTER_HANDLE_4_READ_CHARACTERISTIC_VALUE_BY_UUID,
    CENTRAL_W4_READ_CHARACTERISTIC_VALUE_BY_UUID,
    CENTRAL_ENTER_OFFSET_4_READ_LONG_CHARACTERISTIC_VALUE_BY_HANDLE,
    CENTRAL_W4_READ_LONG_CHARACTERISTIC_VALUE_BY_HANDLE,
    CENTRAL_W4_READ_CHARACTERISTIC_DESCRIPTOR_BY_HANDLE,
    CENTRAL_ENTER_OFFSET_4_READ_LONG_CHARACTERISTIC_DESCRIPTOR_BY_HANDLE,
    CENTRAL_W4_READ_LONG_CHARACTERISTIC_DESCRIPTOR_BY_HANDLE,
    CENTRAL_W4_READ_MULTIPLE_CHARACTERISTIC_VALUES,
    CENTRAL_W4_WRITE_WITHOUT_RESPONSE,
    CENTRAL_W4_WRITE_CHARACTERICISTIC_VALUE,
    CENTRAL_ENTER_HANDLE_4_WRITE_LONG_CHARACTERISTIC_VALUE,
    CENTRAL_W4_WRITE_LONG_CHARACTERISTIC_VALUE,
    CENTRAL_W4_RELIABLE_WRITE_LONG_CHARACTERISTIC_VALUE,
    CENTRAL_W4_WRITE_CHARACTERISTIC_DESCRIPTOR,
    CENTRAL_ENTER_HANDLE_4_WRITE_LONG_CHARACTERISTIC_DESCRIPTOR,
    CENTRAL_W4_WRITE_LONG_CHARACTERISTIC_DESCRIPTOR,
    CENTRAL_W4_INCLUDED_SERVICES,
    CENTRAL_W4_SIGNED_WRITE,
    CENTRAL_W4_WRITE_CLIENT_CHARACTERISTIC_CONFIGURATION,
    CENTRAL_W4_PREPARE_WRITE_CHAR_VALUE,
    CENTRAL_W4_PREPARE_WRITE_EXCUTE_CHAR_VALUE,
    CENTRAL_W4_PREPARE_WRITE_CANCEL_CHAR_VALUE,

    CENTRAL_W4_ENTER_HANDLE_4_PREPARE_WRITE,
    CENTRAL_W4_ENTER_OFFSET_4_PREPARE_WRITE,

    CENTRAL_GPA_ENTER_UUID,
    CENTRAL_GPA_ENTER_START_HANDLE,
    CENTRAL_GPA_ENTER_END_HANDLE,
    CENTRAL_GPA_W4_RESPONSE,
    CENTRAL_GPA_W4_RESPONSE2,
    CENTRAL_GPA_W4_RESPONSE3,
    CENTRAL_GPA_W4_RESPONSE4,
} central_state_t;

typedef enum
{
    MTU_IS_NOT_EXCHANGED,
    MTU_IS_EXCHANGING,
    MTU_IS_EXCHANGED,
}MTU_EXCHANGE_STATE_E;

typedef struct
{
    //stAppTimerNode_t att_transacton_timer;
    uint16_t mtu;       // initialized to ATT_DEFAULT_MTU (23), negotiated during MTU exchange
    uint16_t max_mtu;   // local maximal L2CAP_MTU, set to l2cap_max_le_mtu()
    uint16_t conn_handle;
    uint8_t mtu_exchange_state;   //see @MTU_EXCHANGE_STATE_E
    uint8_t connection_state;
    uint16_t att_handle_value_indication_handle; //for indication
    uint16_t att_prepare_write_handle; //for indication

    uint8_t encryption_key_size;
    uint8_t authenticated;
    uint8_t authorized;
}  att_connection_t;

typedef enum
{
    SM_PAIR_IDLE=0,
    SM_PAIR_WAITTING_TO_START,
    SM_PAIR_CACHE_RECV_AND_WAITTING,
    SM_PAIR_CACHE_SEND_AND_WAITTING,
    SM_PAIR_INIT,
    SM_PAIR_ACTIVE,
    SM_PAIR_TIMEOUT,
    SM_PAIR_OVER,
} sm_pair_state ;

typedef enum
{
    SM_TIMER_IDLE=0,
    SM_TIMER_ACTIVE,
    SM_TIMER_RUN_BACKGROUD,
} sm_timer_sta;

typedef enum
{
    AUTHORIZATION_UNKNOWN,
    AUTHORIZATION_PENDING,
    AUTHORIZATION_DECLINED,
    AUTHORIZATION_GRANTED
} authorization_state_t;



typedef struct le_device_memory_db
{

    // Identification
    uint8_t  addr_type;
    uint8_t  key_size;
    uint8_t  authenticated;
    uint8_t  authorized;
    bd_addr_t addr;
    uint16_t ediv;
    uint8_t  rand[8];
    // Stored pairing information allows to re-establish an enncrypted connection
    // with a peripheral that doesn't have any persistent memory
    sm_key_t ltk;
    sm_key_t irk;

    // Signed Writes by remote
    sm_key_t remote_csrk;
    uint32_t remote_counter;

    // Signed Writes by us
    sm_key_t local_csrk;
    uint32_t local_counter;

} le_device_memory_db_t;
typedef struct
{
    uint16_t conn_handle;
    uint8_t   pair_state;
    uint8_t   conn_state;
    uint8_t   sm_role; 
    uint8_t   sm_local_addr_type;
    uint8_t   sm_local_address[6];
    uint8_t   sm_timer_active;
    uint8_t   sm_peer_addr_type;
    uint8_t   sm_peer_address[6];    
    uint8_t   packet_cache[8];
    
    
    uint32_t goto_conn_index;
    uint32_t timeLo_for_rtc_cnt;
    uint8_t sm_connection_encrypted;
    uint8_t sm_connection_authenticated;   // [0..1]
    uint8_t sm_actual_encryption_key_size;
    uint8_t encryption_key_size;
    uint8_t authenticated;
    uint8_t authorized;
    uint8_t bonding_status;
    uint8_t connection_state;
    authorization_state_t sm_connection_authorization_state;
    uint8_t   null[3];
    uint8_t  confirm_sucess;
    uint32_t passkey;
    le_device_memory_db_t le_device_db;
    stack_timer_source_t st_timer;
} sm_pair_state_t;


typedef struct
{
    uint16_t conn_handle;
    uint16_t connection_state;
    gatt_client_state_t gatt_client_state;
    central_state_t central_state;
    
    uint16_t uuid16;
    uint8_t  uuid128[16];

    uint16_t start_group_handle;
    uint16_t end_group_handle;

    uint16_t query_start_handle;
    uint16_t query_end_handle;

    uint8_t  characteristic_properties;
    uint16_t characteristic_start_handle;

    uint16_t attribute_handle;
    uint16_t attribute_offset;
    uint16_t attribute_length;
    uint8_t* attribute_value;

    // read multiple characteristic values
    uint16_t    read_multiple_handle_count;
    uint16_t*   read_multiple_handles;

    uint16_t client_characteristic_configuration_handle;
    uint8_t  client_characteristic_configuration_value[2];

    uint8_t  filter_with_uuid;
    uint8_t  send_confirmation;
    stack_timer_source_t st_timer;

    // int      le_device_index;
    // uint8_t  cmac[8];

} t_gatt_client;

typedef struct st_stack_acl_data_mngr_list
{ 
    void * acl_data_list_for_conn_head ;
    void * acl_data_list_for_conn_tail ;
    // st_stack_acl_data_t * acl_data_list_for_conn_tail ;
}st_stack_acl_data_mngr_list_t;

typedef struct {    
    
    // module handle
    uint16_t conn_handle;
    uint16_t Conn_Interval;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;

    // remote side
    uint8_t peer_address[6];
    uint8_t peer_address_type;

    // role: 0 - master, 1 - slave
    uint8_t role;

    // connection state  0 - discon, 1 - connected
    uint8_t conn_state;
    uint8_t rx_cached_num;
    uint8_t   null[2];

    uint16_t le_max_rx_octets;
    uint16_t le_max_tx_octets;

    st_stack_acl_data_mngr_list_t st_acl_data_mngr_list;

    
    // LE Security Manager
    sm_pair_state_t st_sm_state;

    // ATT Connection
    att_connection_t st_att_state;

    // ATT CLIENT
    t_gatt_client    st_gatt_client_state;


} host_connection_t;

extern host_connection_t* gp_host_conn;
host_connection_t * rom_host_connection_for_handle(uint16_t conn_handle);
void  rom_host_connection_on_conn_event(uint8_t *evt);
void  rom_host_connection_on_disconn_event(uint16_t conn_handle);
att_connection_t * rom_att_connection_for_handle(uint16_t conn_handle);
t_gatt_client* rom_gatt_client_for_handle(uint16_t conn_handle);
sm_pair_state_t * rom_sm_pair_state_for_handle(uint16_t conn_handle);
uint8_t rom_host_connection_is_slave_role ( uint16_t conn_handle );
