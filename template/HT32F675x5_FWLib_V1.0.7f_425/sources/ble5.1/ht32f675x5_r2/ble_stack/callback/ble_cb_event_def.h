/*************************************************************************************************************
 * @file    ble_cb_event_def.h
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

#ifndef __BLE_CB_EVENT_DEF_H__
#define __BLE_CB_EVENT_DEF_H__


/**
 * @brief  ble to app message type definition
 */
typedef enum
{
    //ADV MSG command connection
    MSG_BLE_RESET = 0,              //0
 
    //CONNECT 
    MSG_BLE_CONNECTED_IND=1,         
    MSG_BLE_DISCONNECTED_IND ,      
    MSG_BLE_LL_VERSION_IND,  
    MSG_BLE_LL_FEATRUE_IND,  
    MSG_BLE_CONNECTION_UPDATE_COMPLETE_IND,
    MSG_BLE_DATA_LENGTH_UPDATE_COMPLETE_IND,
    MSG_BLE_PHY_UPDATE_COMPLETE_IND,  
    MSG_BLE_ENCRYPTED_CHANGED_IND ,  
    MSG_BLE_ENCRYPTED_REFRESH_IND ,  
    MSG_BLE_MTU_EXCHANGED_IND ,  
    MSG_BLE_RELEASE_TX_BUF_IND ,  
    MSG_BLE_LLCAP_CONN_UPDATE_RSP_IND ,  

//PAIR
    MSG_BLE_PAIR_USER_PASSKEYREQ_IND = 0x20,                        //0x37
    MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_IND,
    MSG_BLE_PAIR_USER_PASSKEYREQ_CONF_IND,
    MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_CANCEL_IND,
    MSG_BLE_PAIR_KEYPRESS_NOTIFICATION_IND,
    MSG_BLE_PAIR_COMPLETED_IND,
    MSG_BLE_PAIR_FAIL_IND,
    MSG_LTK_REQ_WHEN_RECONECT_AFTER_PAIR_IND,

//ADV & SCAN
    MSG_BLE_ADV_REPORT_IND=0x30, 
    MSG_BLE_EXT_ADV_REPORT_IND, 
    MSG_BLE_ADVERTISING_SET_TERMINATED_IND,/**This event will be generated every time connectable advertising in an
                                            advertising set results in a connection being created or because the advertising
                                            duration or the maximum number of extended advertising events has been
                                            reached. It will not be generated if user disables the advertising set**/
    MSG_RFU1,
    MSG_RFU2,
    MSG_RFU3,
    MSG_BLE_HIGH_DUTY_DIRECT_ADV_END_IND, 

    
    MSG_BLE_READ_RSSI_COMMAND_RESULT = 0x40,
    MSG_BLE_DISCONNECT_COMMAND_RESULT,
    MSG_BLE_SET_RANDOM_ADDRESS_COMMAND_RESULT,
    MSG_BLE_SET_ADVERTISING_PARAMETERS_COMMAND_RESULT,
    MSG_BLE_SET_ADVERTISING_DATA_COMMAND_RESULT,
    MSG_BLE_SET_SCAN_RESPONSE_DATA_COMMAND_RESULT,
    MSG_BLE_SET_ADVERTISING_ENABLE_COMMAND_RESULT,
    
    MSG_BLE_SET_SCAN_PARAMETERS_COMMAND_RESULT,
    MSG_BLE_SET_SCAN_ENABLE_COMMAND_RESULT,
    
    MSG_BLE_CLEAR_WHITE_LIST_COMMAND_RESULT,
    MSG_BLE_ADD_DEVICE_TO_WHITE_LIST_COMMAND_RESULT,
    MSG_BLE_REMOVE_DEVICE_FROM_WHITE_LIST_COMMAND_RESULT,
    
    MSG_BLE_CREATE_CONNECTION_CANCEL_COMMAND_RESULT,
    MSG_BLE_CONNECTION_UPDATE_COMMAND_RESULT,
    
    MSG_BLE_LONG_TERM_KEY_REQUEST_REPLY_COMMAND_RESULT,
    MSG_BLE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_COMMAND_RESULT,
    
    MSG_BLE_SET_DATA_LENGTH_COMMAND_RESULT,
    MSG_BLE_SET_PHY_COMMAND_RESULT,
    MSG_BLE_READ_REMOTE_FEATURES_COMMAND_RESULT,
    
    MSG_BLE_ADD_DEVICE_TO_RESOLVING_LIST_COMMAND_RESULT,
    MSG_BLE_REMOVE_DEVICE_FROM_RESOLVING_LIST_COMMAND_RESULT,
    MSG_BLE_CLEAR_RESOLVING_LIST_COMMAND_RESULT,
    MSG_BLE_SET_ADDRESS_RESOLUTION_ENABLE_COMMAND_RESULT,
    MSG_BLE_SET_PRIVACY_MODE_COMMAND_RESULT,
    
    MSG_BLE_READ_CHANNEL_MAP_COMMAND_RESULT,
    
    MSG_BLE_SET_ADVERTISING_SET_RANDOM_ADDRESS_COMMAND_RESULT,
    MSG_BLE_SET_EXTENDED_ADVERTISING_PARAMETERS_COMMAND_RESULT,
    MSG_BLE_SET_EXTENDED_ADVERTISING_DATA_COMMAND_RESULT,
    MSG_BLE_SET_EXTENDED_SCAN_RESPONSE_DATA_COMMAND_RESULT,
    MSG_BLE_SET_EXTENDED_ADVERTISING_ENABLE_COMMAND_RESULT,
    MSG_BLE_REMOVE_ADVERTISING_SET_COMMAND_RESULT,
    MSG_BLE_CLEAR_ADVERTISING_SETS_COMMAND_RESULT,
    
    MSG_BLE_SET_EXTENDED_SCAN_PARAMETERS_COMMAND_RESULT,
    MSG_BLE_SET_EXTENDED_SCAN_ENABLE_COMMAND_RESULT,
    
    MSG_BLE_SET_PUBLIC_ADDRESS_COMMAND_RESULT,
    
    MSG_BLE_CREATE_CONNECTION_COMMAND_RESULT,
    
    MSG_BLE_UPDATE_CHANNEL_MAP_COMMAND_RESULT,
    
    MSG_BLE_EXTENDED_CREATE_CONNECTION_COMMAND_RESULT,
    
} BLE_EVT_MSG;
 
 

typedef struct
{
    uint16_t conn_handle;
    uint8_t passkey[4];
}__attribute__((packed))
st_passkey_display_event;

typedef struct
{
    uint16_t conn_handle;
    uint8_t  key_size;
    uint8_t  authenticated;
    uint8_t  authorized;
    uint8_t peer_addr_type;    
    uint8_t peer_addr[6];
    uint8_t peer_irk[16];
    uint8_t local_irk[16];
    uint8_t ltk[16];
    uint8_t rand[8];
    uint16_t  ediv;
}__attribute__((packed))
st_pair_complete_event;

typedef struct
{
    uint16_t conn_handle;
    uint8_t reason;
}__attribute__((packed))
st_pair_failed_event;

typedef struct
{
    uint16_t conn_handle;
    uint8_t key_notification_type;
}__attribute__((packed))
st_key_pressed_event;

typedef struct
{
    uint16_t conn_handle;
    uint8_t rand[8];
    uint16_t ediv;
}__attribute__((packed))
st_ltk_req_event;

typedef struct
{
    uint16_t  conn_handle;
    uint16_t  mtu;
}__attribute__((packed))
st_mtu_exchange_complete_event;

typedef struct
{
    uint16_t  conn_handle;
    uint16_t  result;
}__attribute__((packed))
st_llcap_conn_update_rsp_event;

#endif  //#ifndef __BLE_EVENT_DEF_H__

