/*************************************************************************************************************
 * @file    sm.h
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



#ifndef __SM_H__
#define __SM_H__


#if defined __cplusplus
extern "C" {
#endif

#define ENABLE_LE_SECURE_CONNECTIONS
#define DEFINE_CMAC_AND_SIGNED_WRITE

//#define ENABLE_LE_SECURE_CONNECTIONS
//#define DEFINE_CMAC_AND_SIGNED_WRITE
//#define ENABLE_DERIVATE_KEY

typedef uint8_t sm_pairing_packet_t[7];

typedef enum
{
    DKG_W4_WORKING,
    DKG_CALC_IRK,
    DKG_W4_IRK,
    DKG_CALC_DHK,
    DKG_W4_DHK,
    DKG_READY
} derived_key_generation_t;

typedef enum
{
    RAU_W4_WORKING,
    RAU_IDLE,
    RAU_GET_RANDOM,
    RAU_W4_RANDOM,
    RAU_GET_ENC,
    RAU_W4_ENC,
    RAU_SET_ADDRESS,
} random_address_update_t;

typedef enum
{
    CMAC_IDLE,
    CMAC_CALC_SUBKEYS,
    CMAC_W4_SUBKEYS,
    CMAC_CALC_MI,
    CMAC_W4_MI,
    CMAC_CALC_MLAST,
    CMAC_W4_MLAST
} cmac_state_t;

typedef enum
{
    JUST_WORKS,
    PK_RESP_INPUT,  // Initiator displays PK, responder inputs PK
    PK_INIT_INPUT,  // Responder displays PK, initiator inputs PK
    PK_BOTH_INPUT,  // Only input on both, both input PK
    NUMERIC_COMPARISON,  // Only numerical compparison (yes/no) on on both sides
    OOB             // OOB available on both sides
} stk_generation_method_t;

typedef enum
{
    SM_USER_RESPONSE_IDLE,
    SM_USER_RESPONSE_PENDING,
    SM_USER_RESPONSE_CONFIRM,
    SM_USER_RESPONSE_PASSKEY,
    SM_USER_RESPONSE_DECLINE
} sm_user_response_t;

typedef enum
{
    SM_AES128_IDLE,
    SM_AES128_ACTIVE
} sm_aes128_state_t;

typedef enum
{
    SM_DKG,
    SM_RAU,
    SM_CMAC,
    SM_CSRK,
    SM_LINK,
}sm_encrypt_type;

typedef enum
{
    ADDRESS_RESOLUTION_IDLE,
    ADDRESS_RESOLUTION_GENERAL,
    ADDRESS_RESOLUTION_FOR_CONNECTION,
} address_resolution_mode_t;

typedef enum
{
    ADDRESS_RESOLUTION_SUCEEDED,
    ADDRESS_RESOLUTION_FAILED,
} address_resolution_event_t;

typedef enum
{
    EC_KEY_GENERATION_IDLE,
    EC_KEY_GENERATION_ACTIVE,
    EC_KEY_GENERATION_DONE,
} ec_key_generation_state_t;

typedef enum
{
    SM_STATE_VAR_DHKEY_COMMAND_RECEIVED = 1 << 0
} sm_state_var_t;

//
// SM internal types and globals
//

typedef enum
{

    // general states
    // state = 0
    SM_GENERAL_IDLE,// = 0
    SM_GENERAL_SEND_PAIRING_FAILED,// = 1
    SM_GENERAL_TIMEOUT, // = 2, // no other security messages are exchanged

    // Phase 1: Pairing Feature Exchange
    SM_PH1_W4_USER_RESPONSE,// = 3,

    // Phase 2: Authenticating and Encrypting

    // get random number for use as TK Passkey if we show it
    SM_PH2_GET_RANDOM_TK,// = 4,
    SM_PH2_W4_RANDOM_TK,// = 5,

    // get local random number for confirm c1
    SM_PH2_C1_GET_RANDOM_A,// = 6,
    SM_PH2_C1_W4_RANDOM_A,// = 7,
    SM_PH2_C1_GET_RANDOM_B,// = 8,
    SM_PH2_C1_W4_RANDOM_B,// = 9,

    // calculate confirm value for local side
    // state = 10
    SM_PH2_C1_GET_ENC_A,// = 0xA,
    SM_PH2_C1_W4_ENC_A,// = 0xB,
    SM_PH2_C1_GET_ENC_B,// = 0xC,
    SM_PH2_C1_W4_ENC_B,// = 0xD,

    // calculate confirm value for remote side
    SM_PH2_C1_GET_ENC_C,// = 0xE,
    SM_PH2_C1_W4_ENC_C,// = 0xF,
    SM_PH2_C1_GET_ENC_D,// = 0x10,
    SM_PH2_C1_W4_ENC_D,// = 0x11,

    SM_PH2_C1_SEND_PAIRING_CONFIRM, // 0x12
    SM_PH2_SEND_PAIRING_RANDOM, //0x13

    // calc STK
    // state = 20
    SM_PH2_CALC_STK,//0x14
    SM_PH2_W4_STK,//0x15

    SM_PH2_W4_CONNECTION_ENCRYPTED,//0x16

    // Phase 3: Transport Specific Key Distribution
    // calculate DHK, Y, EDIV, and LTK
    SM_PH3_GET_RANDOM,//0x17
    SM_PH3_W4_RANDOM,//0x18
    SM_PH3_GET_DIV,//0x19
    SM_PH3_W4_DIV,//0x1A
    SM_PH3_Y_GET_ENC,//0x1B
    SM_PH3_Y_W4_ENC,//0x1C
    SM_PH3_LTK_GET_ENC,//0x1D
    // state = 30
    SM_PH3_LTK_W4_ENC,//0x1E
    SM_PH3_CSRK_GET_ENC,//0x1F
    SM_PH3_CSRK_W4_ENC,//0x20

    // exchange keys
    SM_PH3_DISTRIBUTE_KEYS,//0x21
    SM_PH3_RECEIVE_KEYS,//0x22

    // RESPONDER ROLE
    // state = 35
    SM_RESPONDER_IDLE,//0x23
    SM_RESPONDER_SEND_SECURITY_REQUEST,//0x24
    SM_RESPONDER_PH0_RECEIVED_LTK_REQUEST,//0x25
    SM_RESPONDER_PH0_SEND_LTK_REQUESTED_NEGATIVE_REPLY,//0x26
    SM_RESPONDER_PH1_W4_PAIRING_REQUEST,//0x27
    SM_RESPONDER_PH1_PAIRING_REQUEST_RECEIVED,//0x28
    SM_RESPONDER_PH1_SEND_PAIRING_RESPONSE,//0x29
    SM_RESPONDER_PH1_W4_PAIRING_CONFIRM,//0x2A
    SM_RESPONDER_PH2_W4_PAIRING_RANDOM,//0x2B
    SM_RESPONDER_PH2_W4_LTK_REQUEST,//0x2C
    SM_RESPONDER_PH2_SEND_LTK_REPLY,//0x2D

    // Phase 4: re-establish previously distributed LTK
    // state == 46
    SM_RESPONDER_PH4_Y_GET_ENC,//0x2E
    SM_RESPONDER_PH4_Y_W4_ENC,//0x2F
    SM_RESPONDER_PH4_LTK_GET_ENC,//0x30
    SM_RESPONDER_PH4_LTK_W4_ENC,//0x31
    SM_RESPONDER_PH4_SEND_LTK_REPLY,//0x32

    // INITITIATOR ROLE
    // state = 51
    SM_INITIATOR_CONNECTED,//0x33
    SM_INITIATOR_PH0_HAS_LTK,//0x34
    SM_INITIATOR_PH0_SEND_START_ENCRYPTION,//0x35
    SM_INITIATOR_PH0_W4_CONNECTION_ENCRYPTED,//0x36
    SM_INITIATOR_PH1_W2_SEND_PAIRING_REQUEST,//0x37
    SM_INITIATOR_PH1_SEND_PAIRING_REQUEST,//0x38
    SM_INITIATOR_PH1_W4_PAIRING_RESPONSE,//0x39
    SM_INITIATOR_PH2_W4_PAIRING_CONFIRM,//0x3A
    SM_INITIATOR_PH2_W4_PAIRING_RANDOM,//0x3B
    SM_INITIATOR_PH3_SEND_START_ENCRYPTION,//0x3C

    // LE Secure Connections
    SM_SC_SEND_PUBLIC_KEY_COMMAND,//0x3D
    SM_SC_W4_PUBLIC_KEY_COMMAND,//0x3E
    SM_SC_W2_GET_RANDOM_A,//0x3F
    SM_SC_W4_GET_RANDOM_A,//0x40
    SM_SC_W2_GET_RANDOM_B,//0x41
    SM_SC_W4_GET_RANDOM_B,//0x42
    SM_SC_W2_CMAC_FOR_CONFIRMATION,//0x43
    SM_SC_W4_CMAC_FOR_CONFIRMATION,//0x44
    SM_SC_SEND_CONFIRMATION,//0x45
    SM_SC_W2_CMAC_FOR_CHECK_CONFIRMATION,//0x46
    SM_SC_W4_CMAC_FOR_CHECK_CONFIRMATION,//0x47
    SM_SC_W4_CONFIRMATION,//0x48
    SM_SC_SEND_PAIRING_RANDOM,//0x49
    SM_SC_W4_PAIRING_RANDOM,//0x4A
    SM_SC_W2_CALCULATE_G2,//0x4B
    SM_SC_W4_CALCULATE_G2,//0x4C
    SM_SC_W2_CALCULATE_F5_SALT,//0x4D
    SM_SC_W4_CALCULATE_F5_SALT,//0x4E
    SM_SC_W2_CALCULATE_F5_MACKEY,//0x4F
    SM_SC_W4_CALCULATE_F5_MACKEY,//0x50
    SM_SC_W2_CALCULATE_F5_LTK,//0x51
    SM_SC_W4_CALCULATE_F5_LTK,//0x52
    SM_SC_W2_CALCULATE_F6_FOR_DHKEY_CHECK,//0x53
    SM_SC_W4_CALCULATE_F6_FOR_DHKEY_CHECK,//0x54
    SM_SC_W2_CALCULATE_F6_TO_VERIFY_DHKEY_CHECK,//0x55
    SM_SC_W4_CALCULATE_F6_TO_VERIFY_DHKEY_CHECK,//0x56
    SM_SC_W4_USER_RESPONSE,//0x57
    SM_SC_SEND_DHKEY_CHECK_COMMAND,//0x58
    SM_SC_W4_DHKEY_CHECK_COMMAND,//0x59
    SM_SC_W4_LTK_REQUEST_SC,//0x5A
    SM_SC_W2_CALCULATE_H6_ILK,//0x5B
    SM_SC_W4_CALCULATE_H6_ILK,//0x5C
    SM_SC_W2_CALCULATE_H6_BR_EDR_LINK_KEY,//0x5D
    SM_SC_W4_CALCULATE_H6_BR_EDR_LINK_KEY//0x5E
} security_manager_state_t;

// Authorization state
// typedef enum
// {
//     AUTHORIZATION_UNKNOWN,
//     AUTHORIZATION_PENDING,
//     AUTHORIZATION_DECLINED,
//     AUTHORIZATION_GRANTED
// } authorization_state_t;

//
// SM internal types and globals
//

typedef enum
{
    IRK_LOOKUP_IDLE,
    IRK_LOOKUP_W4_READY,
    IRK_LOOKUP_STARTED,
    IRK_LOOKUP_SUCCEEDED,
    IRK_LOOKUP_FAILED
} irk_lookup_state_t;

//sm encrypt control block
// typedef struct
// {
//     uint8_t type  :3;
//     uint8_t idx   :5;
// }sm_pending_msg_t;

// typedef struct
// {
//     sm_pending_msg_t *msg_queue;
//     uint8_t queue_rd;
//     uint8_t queue_wr;
//     uint8_t max_queue_size;
//     uint8_t curr_sm_type;
//     uint8_t curr_role_idx;
// }sm_encrypt_ctrl_block_t;

// data needed for security setup
typedef struct sm_setup_context
{

    //btstack_timer_source_t sm_timeout;

    // used in all phases
    uint8_t   sm_pairing_failed_reason;

    // user response, (Phase 1 and/or 2)
    uint8_t   sm_user_response;
    uint8_t   sm_keypress_notification;

    // Phase 2 (Pairing over SMP)
    stk_generation_method_t sm_stk_generation_method;
    sm_key_t  sm_tk;
    uint8_t   sm_use_secure_connections;
    uint8_t   sm_have_oob_data ;
    sm_key_t  sm_c1_t3_value;   // c1 calculation
    sm_pairing_packet_t sm_m_preq; // pairing request - needed only for c1
    sm_pairing_packet_t sm_s_pres; // pairing response - needed only for c1
    sm_key_t  sm_local_random;
    sm_key_t  sm_local_confirm;
    sm_key_t  sm_peer_random;
    sm_key_t  sm_peer_confirm;
    uint8_t   sm_m_addr_type;   // address and type can be removed
    uint8_t   sm_s_addr_type;   //  ''
    bd_addr_t sm_m_address;     //  ''
    bd_addr_t sm_s_address;     //  ''
    sm_key_t  sm_ltk;

    uint8_t   sm_state_vars;
    // defines which keys will be send after connection is encrypted - calculated during Phase 1, used Phase 3
    int       sm_key_distribution_send_set;
    int       sm_key_distribution_received_set;

#ifdef ENABLE_LE_SECURE_CONNECTIONS
    uint8_t   sm_peer_qx[32];   // also stores random for EC key generation during init
    uint8_t   sm_peer_qy[32];   //  ''
    sm_key_t  sm_peer_nonce;    // might be combined with sm_peer_random
    sm_key_t  sm_local_nonce;   // might be combined with sm_local_random
    sm_key_t  sm_peer_dhkey_check;
    sm_key_t  sm_local_dhkey_check;
    sm_key_t  sm_ra;
    sm_key_t  sm_rb;
    sm_key_t  sm_t;             // used for f5 and h6
    sm_key_t  sm_mackey;
    uint8_t   sm_passkey_bit;   // also stores number of generated random bytes for EC key generation
    sm_key_t  sm_local_ltk;
#endif

    // Phase 3

    // key distribution, we generate
    uint16_t  sm_local_y;
    uint16_t  sm_local_div;
    uint16_t  sm_local_ediv;
    uint8_t   sm_local_rand[8];
    sm_key_t  sm_local_csrk;
    //sm_key_t  sm_local_irk;
    // sm_local_address/addr_type not needed

    // key distribution, received from peer
    // uint16_t  sm_peer_y;
    // uint16_t  sm_peer_div;
    uint16_t  sm_peer_ediv;
    uint8_t   sm_peer_rand[8];
    sm_key_t  sm_peer_ltk;
    sm_key_t  sm_peer_irk;
    sm_key_t  sm_peer_csrk;
    uint8_t   sm_peer_addr_type;
    bd_addr_t sm_peer_address;

} sm_setup_context_t;

typedef struct
{
    sm_setup_context_t the_setup;
        
    // int32_t sm_le_db_index;
    sm_pair_state_t * cur_context;
    uint16_t sm_cur_index;
    uint16_t sm_local_ediv;
    uint8_t sm_role;   // 0 - IamMaster, 1 = IamSlave
    uint8_t sm_security_request_received;
    uint8_t sm_bonding_requested;
    uint8_t sm_local_addr_type;
    uint8_t sm_local_address[6];
    uint8_t sm_peer_addr_type;
    uint8_t sm_peer_address[6];
    security_manager_state_t sm_engine_state;
    irk_lookup_state_t sm_irk_lookup_state;
    // uint8_t sm_connection_encrypted;
    // uint8_t sm_connection_authenticated;   // [0..1]
    // uint8_t sm_actual_encryption_key_size;
    uint8_t sm_m_preq[7];  // only used during c1
    // authorization_state_t sm_connection_authorization_state;
    uint8_t sm_local_rand[8];
    // uint8_t encryption_key_size;
    // uint8_t authenticated;
    // uint8_t authorized;
    // uint8_t bonding_status;
    // uint8_t connection_state;
} sm_connection;
//typedef enum
//{
//    SM_PAIR_IDLE=0,
//    SM_PAIR_WAITTING_TO_START,
//    SM_PAIR_CACHE_RECV_AND_WAITTING,
//    SM_PAIR_CACHE_SEND_AND_WAITTING,
//    SM_PAIR_INIT,
//    SM_PAIR_ACTIVE,
//    SM_PAIR_TIMEOUT,
//    SM_PAIR_OVER,
//} sm_pair_state ;
//typedef enum
//{
//    SM_TIMER_IDLE=0,
//    SM_TIMER_ACTIVE,
//    SM_TIMER_RUN_BACKGROUD,
//} sm_timer_sta;
// typedef struct le_device_memory_db
// {

//     // Identification
//     uint8_t  addr_type;
//     uint8_t  key_size;
//     uint8_t  authenticated;
//     uint8_t  authorized;
//     bd_addr_t addr;
//     uint16_t ediv;
//     uint8_t  rand[8];
//     // Stored pairing information allows to re-establish an enncrypted connection
//     // with a peripheral that doesn't have any persistent memory
//     sm_key_t ltk;
//     sm_key_t irk;

//     // Signed Writes by remote
//     sm_key_t remote_csrk;
//     uint32_t remote_counter;

//     // Signed Writes by us
//     sm_key_t local_csrk;
//     uint32_t local_counter;

// } le_device_memory_db_t;
// typedef struct
// {
//     uint8_t   sm_role; 
//     uint8_t   sm_local_addr_type;
//     uint8_t   sm_local_address[6];
//     uint8_t   sm_timer_active;
//     uint8_t   sm_peer_addr_type;
//     uint8_t   sm_peer_address[6];    
//     uint8_t   packet_cache[7];
//     uint8_t   pair_state;
//     uint32_t  gotoConLo_for_rtc_cnt;
//     uint32_t  timeLo_for_rtc_cnt;
//     uint8_t sm_connection_encrypted;
//     uint8_t sm_connection_authenticated;   // [0..1]
//     uint8_t sm_actual_encryption_key_size;
//     uint8_t encryption_key_size;
//     uint8_t authenticated;
//     uint8_t authorized;
//     uint8_t bonding_status;
//     uint8_t connection_state;
//     authorization_state_t sm_connection_authorization_state;
//     uint8_t   null[2];
//     uint8_t  confirm_sucess;
//     uint32_t  passkey;
    
//     // uint32_t  timerout_for_rtc_cnt;
//     le_device_memory_db_t le_device_db;
// } sm_pair_state_t;

typedef struct
{
    
    uint8_t key[16];
    uint8_t plain[16];
    uint16_t sm_aes_type  ;
}sm_aes_msg_st;




extern void rom_sm_handle_encryption_result(uint16_t conn_handle,  uint8_t* data );
extern void rom_sm_run( uint16_t conn_handle );
extern void rom_sm_cmac_run( uint8_t* data );
extern void rom_sm_dkg_run( uint8_t* data );
extern void sm_rau_run( uint8_t* data );
extern void rom_sm_csrk_run( uint16_t conn_handle, uint8_t* data );
extern void rom_sm_event_disconn_complete_for_multi_con( sm_pair_state_t *p_sm_state );
extern void rom_sm_event_pair_state_active(  sm_pair_state_t *p_sm_state );
extern void rom_sm_event_conn_complete_for_multi_con( sm_pair_state_t *p_sm_state, uint8_t conn_role, uint8_t local_addr_type, uint8_t *local_addr, uint8_t peer_addr_type, uint8_t *peer_addr );
extern void rom_sm_just_works_confirm(sm_connection* sm_conn);
extern uint8_t sm_get_idx_from_sm_conn( sm_connection* sm_conn );
extern void rom_sm_event_encrypt_change( uint16_t conn_handle,uint8_t encrypted );
extern void rom_sm_event_key_refresh( uint16_t conn_handle );
extern void rom_sm_dhk_init( void );
extern void rom_sm_sc_calculate_dhkey( uint16_t conn_handle );
extern void rom_sm_ec_calc_calculate_pubkey (uint16_t conn_handle );
extern void rom_sm_pdu_handler( uint16_t conn_handle, uint8_t* packet, uint16_t size );
extern int rom_sm_request_pairing ( uint16_t conn_handle );
extern void rom_sm_event_long_term_key( uint16_t conn_handle, uint16_t ediv, uint8_t *rand );
extern void rom_sm_cmac_signed_write_start( uint8_t* k, uint8_t size, uint8_t* packet, void ( *done_handler )( uint8_t* hash ) );
extern void ( *sm_cmac_done_handler )( uint8_t* hash );
extern int rom_sm_cmac_ready( void );
extern int rom_sm_le_device_index( uint16_t conn_handle );
extern void sm_send_security_request( uint16_t conn_handle );
extern void rom_sm_passkey_input( uint16_t conn_handle );
extern void rom_sm_numeric_comparison_confirm ( uint16_t conn_handle );
extern void rom_sm_para_update( uint8_t iocap, uint8_t authreq, uint8_t keysize );
extern void rom_sm_authorization_decline( uint16_t conn_handle );
extern void rom_sm_authorization_grant( uint16_t conn_handle );
extern void rom_sm_bonding_decline( uint16_t conn_handle );
extern void sm_update_irk( void );
extern uint8_t* sm_get_irk( void );
extern void rom_sm_bond_info_save_by_app_config( uint32_t onoff );
extern int rom_sm_slave_mode_is_not_busy ( uint16_t conn_handle );
//extern void sm_aes128_start ( uint16_t conn_handle, sm_key_t key, uint8_t processing_module );
extern void rom_sm_set_bond_info_for_encryption_conn(uint16_t conn_handle,  uint16_t ediv, uint8_t rand[8], uint8_t ltk[16], uint8_t key_size, uint8_t authenticated, uint8_t authorized );
extern void rom_sm_register_oob_data_callback ( int ( *get_oob_data_callback ) ( uint8_t peer_addr_type, uint8_t peer_addr[6], uint8_t  oob_data[16] ) );
extern void sm_tx_buffer_commit(uint16_t conn_handle, uint8_t *p_data, uint16_t data_size, uint8_t need_feedbacke);
extern int sm_event_enc_fail_and_repair ( uint16_t conn_handle );
extern void rom_sm_pair_trigger_next( uint16_t conn_handle );
extern void rom_sm_on_packet_tx_over(uint16_t conn_handle );
extern void rom_sm_send_pkt ( uint16_t conn_handle, uint8_t* data, uint16_t len, uint8_t need_feedback );
void rom_sm_trigger_run ( uint16_t conn_handle );
void rom_sm_api_send_security_req ( uint16_t conn_handle );
// void rom_sm_api_set_bond_info_for_encryption_conn ( uint16_t conn_handle,  uint16_t ediv, uint8_t rand[8], uint8_t ltk[16] );
void rom_sm_api_update_pair_para ( uint8_t iocap, uint8_t authreq, uint8_t keysize );
void rom_sm_api_input_passkey_during_pair ( uint16_t conn_handle, uint32_t passkey );
void rom_sm_api_sm_numeric_comparison_confirm ( uint16_t conn_handle, uint8_t confirm_sucess );
void rom_sm_api_long_term_key_request_reply ( uint16_t conn_idx, uint8_t *ltk );
void rom_sm_api_long_term_key_request_negative_reply ( uint16_t conn_idx );
void rom_sm_api_register_oob_data_callback ( int ( *get_oob_data_callback ) ( uint8_t peer_addr_type, uint8_t peer_addr[6], uint8_t  oob_data[16] ) );
void rom_sm_api_register_sc_oob_data_callback ( int ( *get_sc_oob_data_callback ) ( uint8_t addres_type, uint8_t addr[6], uint8_t *oob_sc_peer_confirm, uint8_t *oob_sc_peer_random ) );
void rom_sm_api_sm_bond_info_save_by_app_config_only_for_legacy_pair ( uint32_t onoff );
void  rom_sm_api_set_pair_pin_code ( bool is_use_random_num, uint32_t pin_num );
void rom_sm_api_generate_local_sc_oob_data ( void ( *callback ) ( const uint8_t *confirm_value, const uint8_t *random_value ) );
void rom_sm_init ( void);
void rom_sm_api_get_irk ( uint8_t irk[16] );
//extern sm_aes128_state_t  sm_aes128_state;
// extern uint8_t     sm_cmac_message_idx;
// extern uint8_t* sm_cmac_message;
// extern uint16_t     sm_cmac_message_len;
void rom_sm_api_set_key_distribution ( bool bIDKey,bool bSignKey); 
void rom_sm_api_set_secure_connections_only ( uint8_t u8Enable );
void rom_sm_timeout_run ( uint16_t conn_handle );
void rom_encrypt_aes_run (uint8_t sm_type, uint16_t idx, uint8_t *key, uint8_t *plaintext  );
bool rom_sm_need_long_sm_tx_buffer ( host_connection_t *host_conn,uint8_t* packet  );
#if defined __cplusplus
}
#endif

#endif // __SM_H
