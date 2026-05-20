/*************************************************************************************************************
 * @file    bluetooth.h
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

#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#define ENABLE_LE_SECURE_CONNECTIONS
// #define DEFINE_CMAC_AND_SIGNED_WRITE

#define BD_ADDR_LEN 6


typedef uint8_t bd_addr_t[BD_ADDR_LEN];
typedef uint8_t sm_key_t[16];
typedef uint8_t sm_key24_t[3];
typedef uint8_t sm_key56_t[7];
typedef uint8_t sm_key256_t[32];
typedef enum
{
    BD_ADDR_TYPE_LE_PUBLIC = 0,
    BD_ADDR_TYPE_LE_RANDOM = 1,
    BD_ADDR_TYPE_LE_PRIVAT_FALLBACK_PUBLIC = 2,
    BD_ADDR_TYPE_LE_PRIVAT_FALLBACK_RANDOM = 3,
    BD_ADDR_TYPE_SCO       = 0xfc,
    BD_ADDR_TYPE_ACL       = 0xfd,
    BD_ADDR_TYPE_UNKNOWN   = 0xfe,  // also used as 'invalid'
} bd_addr_type_t;


#define LINK_KEY_LEN 16
#define LINK_KEY_STR_LEN (LINK_KEY_LEN*2)
typedef uint8_t link_key_t[LINK_KEY_LEN];

/**
 * @brief link key type
 */
typedef enum
{
    COMBINATION_KEY = 0,  // standard pairing
    LOCAL_UNIT_KEY,     // ?
    REMOTE_UNIT_KEY,    // ?
    DEBUG_COMBINATION_KEY,  // SSP with debug
    UNAUTHENTICATED_COMBINATION_KEY_GENERATED_FROM_P192, // SSP Simple Pairing
    AUTHENTICATED_COMBINATION_KEY_GENERATED_FROM_P192,   // SSP Passkey, Number confirm, OOB
    CHANGED_COMBINATION_KEY,               // Link key changed using Change Connection Lnk Key
    UNAUTHENTICATED_COMBINATION_KEY_GENERATED_FROM_P256, // SSP Simpe Pairing
    AUTHENTICATED_COMBINATION_KEY_GENERATED_FROM_P256,   // SSP Passkey, Number confirm, OOB
} link_key_type_t;



//// hci packet header sizes
//#define HCI_CMD_HEADER_SIZE          3
//#define HCI_ACL_HEADER_SIZE          4
//#define HCI_SCO_HEADER_SIZE          3
//#define HCI_EVENT_HEADER_SIZE        2

//#define HCI_HEADER_SIZE_FOR_BUFFER        5
//#define HCI_PACKET_TYPE_ACL_DATA      2

//typedef struct
//{
//    uint16_t flag4handle12;
//    uint16_t  length;
//}hci_acl_header_t;


// ERRORS

// last error code in 2.1 is 0x38 - we start with 0x50 for BTstack errors
#define BTSTACK_CONNECTION_TO_BTDAEMON_FAILED              0x50
#define BTSTACK_ACTIVATION_FAILED_SYSTEM_BLUETOOTH         0x51
#define BTSTACK_ACTIVATION_POWERON_FAILED                  0x52
#define BTSTACK_ACTIVATION_FAILED_UNKNOWN                  0x53
#define BTSTACK_NOT_ACTIVATED                              0x54
#define BTSTACK_BUSY                                       0x55
#define BTSTACK_MEMORY_ALLOC_FAILED                        0x56
#define BTSTACK_ACL_BUFFERS_FULL                           0x57

// l2cap errors - enumeration by the command that created them
#define L2CAP_COMMAND_REJECT_REASON_COMMAND_NOT_UNDERSTOOD 0x60
#define L2CAP_COMMAND_REJECT_REASON_SIGNALING_MTU_EXCEEDED 0x61
#define L2CAP_COMMAND_REJECT_REASON_INVALID_CID_IN_REQUEST 0x62

#define L2CAP_CONNECTION_RESPONSE_RESULT_SUCCESSFUL        0x63
#define L2CAP_CONNECTION_RESPONSE_RESULT_PENDING           0x64
#define L2CAP_CONNECTION_RESPONSE_RESULT_REFUSED_PSM       0x65
#define L2CAP_CONNECTION_RESPONSE_RESULT_REFUSED_SECURITY  0x66
#define L2CAP_CONNECTION_RESPONSE_RESULT_REFUSED_RESOURCES 0x67
#define L2CAP_CONNECTION_RESPONSE_RESULT_RTX_TIMEOUT       0x68

#define L2CAP_SERVICE_ALREADY_REGISTERED                   0x69
#define L2CAP_DATA_LEN_EXCEEDS_REMOTE_MTU                  0x6A

#define RFCOMM_MULTIPLEXER_STOPPED                         0x70
#define RFCOMM_CHANNEL_ALREADY_REGISTERED                  0x71
#define RFCOMM_NO_OUTGOING_CREDITS                         0x72
#define RFCOMM_AGGREGATE_FLOW_OFF                          0x73
#define RFCOMM_DATA_LEN_EXCEEDS_MTU                        0x74

#define SDP_HANDLE_ALREADY_REGISTERED                      0x80
#define SDP_QUERY_INCOMPLETE                               0x81
#define SDP_SERVICE_NOT_FOUND                              0x82
#define SDP_HANDLE_INVALID                                 0x83
#define SDP_QUERY_BUSY                                     0x84

#define ATT_HANDLE_VALUE_INDICATION_IN_PORGRESS            0x90
#define ATT_HANDLE_VALUE_INDICATION_TIMEOUT                0x91

#define GATT_CLIENT_NOT_FOUND                              0x92
#define GATT_CLIENT_NOT_CONNECTED                          0x93
#define GATT_CLIENT_BUSY                                   0x94
#define GATT_CLIENT_IN_WRONG_STATE                         0x95
#define GATT_CLIENT_DIFFERENT_CONTEXT_FOR_ADDRESS_ALREADY_EXISTS 0x96
#define GATT_CLIENT_VALUE_TOO_LONG                         0x97
#define GATT_CLIENT_CHARACTERISTIC_NOTIFICATION_NOT_SUPPORTED 0x98
#define GATT_CLIENT_CHARACTERISTIC_INDICATION_NOT_SUPPORTED   0x99
#define GATT_CLIENT_INVALID_HANDLE                          0x9A

#define BNEP_SERVICE_ALREADY_REGISTERED                    0xA0
#define BNEP_CHANNEL_NOT_CONNECTED                         0xA1
#define BNEP_DATA_LEN_EXCEEDS_MTU                          0xA2


/**
 * L2CAP Layer
 */

#define L2CAP_HEADER_SIZE 4

// minimum signaling MTU
#define L2CAP_MINIMAL_MTU 48
#define L2CAP_DEFAULT_MTU 672
    
// Minimum/default MTU
#define L2CAP_LE_DEFAULT_MTU  23

// L2CAP Fixed Channel IDs    
#define L2CAP_CID_SIGNALING                        0x0001
#define L2CAP_CID_CONNECTIONLESS_CHANNEL           0x0002
#define L2CAP_CID_ATTRIBUTE_PROTOCOL               0x0004
#define L2CAP_CID_SIGNALING_LE                     0x0005
#define L2CAP_CID_SECURITY_MANAGER_PROTOCOL        0x0006

// L2CAP Configuration Result Codes
#define L2CAP_CONF_RESULT_UNKNOWN_OPTIONS   0x0003

// L2CAP Reject Result Codes
#define L2CAP_REJ_CMD_UNKNOWN               0x0000

// Response Timeout eXpired
#define L2CAP_RTX_TIMEOUT_MS   10000

// Extended Response Timeout eXpired
#define L2CAP_ERTX_TIMEOUT_MS 120000

// Fixed PSM numbers
#define PSM_SDP           0x01
#define PSM_RFCOMM        0x03
#define PSM_BNEP          0x0F
#define PSM_HID_CONTROL   0x11
#define PSM_HID_INTERRUPT 0x13





/**
 * ATT
 */

// Minimum/default MTU
#define ATT_DEFAULT_MTU               23

// MARK: ATT Error Codes
#define ATT_ERROR_SUCCESS                          0x00
#define ATT_ERROR_INVALID_HANDLE                   0x01
#define ATT_ERROR_READ_NOT_PERMITTED               0x02
#define ATT_ERROR_WRITE_NOT_PERMITTED              0x03
#define ATT_ERROR_INVALID_PDU                      0x04
#define ATT_ERROR_INSUFFICIENT_AUTHENTICATION      0x05
#define ATT_ERROR_REQUEST_NOT_SUPPORTED            0x06
#define ATT_ERROR_INVALID_OFFSET                   0x07
#define ATT_ERROR_INSUFFICIENT_AUTHORIZATION       0x08
#define ATT_ERROR_PREPARE_QUEUE_FULL               0x09
#define ATT_ERROR_ATTRIBUTE_NOT_FOUND              0x0a
#define ATT_ERROR_ATTRIBUTE_NOT_LONG               0x0b
#define ATT_ERROR_INSUFFICIENT_ENCRYPTION_KEY_SIZE 0x0c
#define ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH   0x0d
#define ATT_ERROR_UNLIKELY_ERROR                   0x0e
#define ATT_ERROR_INSUFFICIENT_ENCRYPTION          0x0f
#define ATT_ERROR_UNSUPPORTED_GROUP_TYPE           0x10
#define ATT_ERROR_INSUFFICIENT_RESOURCES           0x11

// MARK: ATT Error Codes defined by BTstack
#define ATT_ERROR_HCI_DISCONNECT_RECEIVED          0x1f
#define ATT_ERROR_BONDING_INFORMATION_MISSING      0x70
#define ATT_ERROR_DATA_MISMATCH                    0x7e
#define ATT_ERROR_TIMEOUT                          0x7F
#define ATT_ERROR_WRITE_RESPONSE_PENDING           0x100

// MARK: ATT Error Codes from Cycling Power Service spec
#define CYCLING_POWER_ERROR_CODE_INAPPROPRIATE_CONNECTION_PARAMETERS                          0x80
#define CYCLING_POWER_ERROR_CODE_PROCEDURE_ALREADY_IN_PROGRESS                                0xFE
#define CYCLING_POWER_ERROR_CODE_CCC_DESCRIPTOR_IMPROPERLY_CONFIGURED                         0xFD

// MARK: ATT Error Codes from Cycling Speed and Cadence Service spec
#define CYCLING_SPEED_AND_CADENCE_ERROR_CODE_PROCEDURE_ALREADY_IN_PROGRESS                    0x80
#define CYCLING_SPEED_AND_CADENCE_ERROR_CODE_CCC_DESCRIPTOR_IMPROPERLY_CONFIGURED             0x81


// MARK: Attribute Property Flags
#define ATT_PROPERTY_BROADCAST           0x01
#define ATT_PROPERTY_READ                0x02
#define ATT_PROPERTY_WRITE_WITHOUT_RESPONSE 0x04
#define ATT_PROPERTY_WRITE               0x08
#define ATT_PROPERTY_NOTIFY              0x10
#define ATT_PROPERTY_INDICATE            0x20
#define ATT_PROPERTY_AUTHENTICATED_SIGNED_WRITE 0x40
#define ATT_PROPERTY_EXTENDED_PROPERTIES 0x80

// MARK: Attribute Property Flag, BTstack extension
// value is asked from client
#define ATT_PROPERTY_DYNAMIC             0x100

// Security levels
#define ATT_SECURITY_NONE 0
#define ATT_SECURITY_ENCRYPTED 1
#define ATT_SECURITY_AUTHENTICATED 2
#define ATT_SECURITY_AUTHORIZED 3
#define ATT_SECURITY_AUTHENTICATED_SC 4

// ATT Transaction Timeout of 30 seconds for Command/Response or Indication/Confirmation
#define ATT_TRANSACTION_TIMEOUT_MS     30000

#define ATT_TRANSACTION_MODE_NONE      0x0
#define ATT_TRANSACTION_MODE_ACTIVE    0x1
#define ATT_TRANSACTION_MODE_EXECUTE   0x2
#define ATT_TRANSACTION_MODE_CANCEL    0x3
#define ATT_TRANSACTION_MODE_VALIDATE  0x4

// MARK: GATT UUIDs
#define GATT_PRIMARY_SERVICE_UUID                   0x2800
#define GATT_SECONDARY_SERVICE_UUID                 0x2801
#define GATT_INCLUDE_SERVICE_UUID                   0x2802
#define GATT_CHARACTERISTICS_UUID                   0x2803
#define GATT_CHARACTERISTIC_EXTENDED_PROPERTIES     0x2900
#define GATT_CHARACTERISTIC_USER_DESCRIPTION        0x2901
#define GATT_CLIENT_CHARACTERISTICS_CONFIGURATION   0x2902
#define GATT_SERVER_CHARACTERISTICS_CONFIGURATION   0x2903
#define GATT_CHARACTERISTIC_PRESENTATION_FORMAT     0x2904
#define GATT_CHARACTERISTIC_AGGREGATE_FORMAT        0x2905

#define GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NONE          0
#define GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NOTIFICATION  1
#define GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_INDICATION    2

#define GATT_CLIENT_ANY_CONNECTION      0xffff
#define GATT_CLIENT_ANY_VALUE_HANDLE    0x0000

// GAP Service and Characteristics
#define GAP_SERVICE_UUID               0x1800
#define GAP_DEVICE_NAME_UUID           0x2a00
#define GAP_APPEARANCE_UUID            0x2a01
#define GAP_PERIPHERAL_PRIVACY_FLAG    0x2a02
#define GAP_RECONNECTION_ADDRESS_UUID  0x2a03
#define GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_UUID 0x2a04
#define GAP_SERVICE_CHANGED            0x2a05

// Bluetooth GATT types

typedef struct {
    uint16_t year;      // 0 - year  is not known; or [1582,9999]
    uint8_t  month;     // 0 - month is not known; or [1,12]
    uint8_t  day;       // 0 - day   is not known; or [1,31]
    uint8_t  hours;     // [0,23]
    uint8_t  minutes;   // [0,59]
    uint8_t  seconds;   // [0,59]
} gatt_date_time_t;

/**
 * SM - LE Security Manager 
 */
// Bluetooth Spec definitions
typedef enum {
    SM_CODE_PAIRING_REQUEST = 0X01,
    SM_CODE_PAIRING_RESPONSE,
    SM_CODE_PAIRING_CONFIRM,
    SM_CODE_PAIRING_RANDOM,
    SM_CODE_PAIRING_FAILED,
    SM_CODE_ENCRYPTION_INFORMATION,
    SM_CODE_MASTER_IDENTIFICATION,
    SM_CODE_IDENTITY_INFORMATION,
    SM_CODE_IDENTITY_ADDRESS_INFORMATION,
    SM_CODE_SIGNING_INFORMATION,
    SM_CODE_SECURITY_REQUEST,
    SM_CODE_PAIRING_PUBLIC_KEY,
    SM_CODE_PAIRING_DHKEY_CHECK,
    SM_CODE_KEYPRESS_NOTIFICATION,
} SECURITY_MANAGER_COMMANDS;

// IO Capability Values
typedef enum {
    IO_CAPABILITY_DISPLAY_ONLY = 0,
    IO_CAPABILITY_DISPLAY_YES_NO,
    IO_CAPABILITY_KEYBOARD_ONLY,
    IO_CAPABILITY_NO_INPUT_NO_OUTPUT,
    IO_CAPABILITY_KEYBOARD_DISPLAY, // not used by secure simple pairing
} io_capability_t;

// Authentication requirement flags
#define SM_AUTHREQ_NO_BONDING        0x00
#define SM_AUTHREQ_BONDING           0x01
#define SM_AUTHREQ_MITM_PROTECTION   0x04
#define SM_AUTHREQ_SECURE_CONNECTION 0x08
#define SM_AUTHREQ_KEYPRESS          0x10
#define SM_AUTHREQ_CT2               0x20

// Key distribution flags used by spec
#define SM_KEYDIST_ENC_KEY  0x01
#define SM_KEYDIST_ID_KEY   0x02
#define SM_KEYDIST_SIGN     0x04
#define SM_KEYDIST_LINK_KEY 0x08

// Key distribution flags used internally
#define SM_KEYDIST_FLAG_ENCRYPTION_INFORMATION       0x01
#define SM_KEYDIST_FLAG_MASTER_IDENTIFICATION        0x02
#define SM_KEYDIST_FLAG_IDENTITY_INFORMATION         0x04
#define SM_KEYDIST_FLAG_IDENTITY_ADDRESS_INFORMATION 0x08
#define SM_KEYDIST_FLAG_SIGNING_IDENTIFICATION       0x10

// STK Generation Methods
#define SM_STK_GENERATION_METHOD_JUST_WORKS          0x01
#define SM_STK_GENERATION_METHOD_OOB                 0x02
#define SM_STK_GENERATION_METHOD_PASSKEY             0x04
#define SM_STK_GENERATION_METHOD_NUMERIC_COMPARISON  0x08

// Pairing Failed Reasons
#define SM_REASON_RESERVED                     0x00
#define SM_REASON_PASSKEY_ENTRY_FAILED         0x01
#define SM_REASON_OOB_NOT_AVAILABLE            0x02
#define SM_REASON_AUTHENTHICATION_REQUIREMENTS 0x03
#define SM_REASON_CONFIRM_VALUE_FAILED         0x04
#define SM_REASON_PAIRING_NOT_SUPPORTED        0x05
#define SM_REASON_ENCRYPTION_KEY_SIZE          0x06
#define SM_REASON_COMMAND_NOT_SUPPORTED        0x07
#define SM_REASON_UNSPECIFIED_REASON           0x08
#define SM_REASON_REPEATED_ATTEMPTS            0x09
#define SM_REASON_INVALID_PARAMETERS           0x0a
#define SM_REASON_DHKEY_CHECK_FAILED           0x0b
#define SM_REASON_NUMERIC_COMPARISON_FAILED    0x0c

// also, invalid parameters
// and reserved

#define SM_REASON_TIMEOUT    0x20


// Keypress Notifications
#define SM_KEYPRESS_PASSKEY_ENTRY_STARTED      0x00
#define SM_KEYPRESS_PASSKEY_DIGIT_ENTERED      0x01
#define SM_KEYPRESS_PASSKEY_DIGIT_ERASED       0x02
#define SM_KEYPRESS_PASSKEY_CLEARED            0x03
#define SM_KEYPRESS_PASSKEY_ENTRY_COMPLETED    0x04



#endif
