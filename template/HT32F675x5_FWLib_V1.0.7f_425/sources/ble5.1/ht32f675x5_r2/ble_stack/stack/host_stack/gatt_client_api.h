/*************************************************************************************************************
 * @file    gatt_client_api.h
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


#ifndef _GATT_CLIENT_H_
#define _GATT_CLIENT_H_



#if defined __cplusplus
extern "C" {
#endif

// typedef enum
// {
//     P_READY,
//     P_W2_SEND_SERVICE_QUERY,/*1*/
//     P_W4_SERVICE_QUERY_RESULT,
//     P_W2_SEND_SERVICE_WITH_UUID_QUERY,
//     P_W4_SERVICE_WITH_UUID_RESULT,
//     P_W2_SEND_MTU_EXCHG,
//     P_W4_MTU_EXCHG_RESULT,

//     P_W2_SEND_ALL_CHARACTERISTICS_OF_SERVICE_QUERY,/*5*/
//     P_W4_ALL_CHARACTERISTICS_OF_SERVICE_QUERY_RESULT,
//     P_W2_SEND_CHARACTERISTIC_WITH_UUID_QUERY,
//     P_W4_CHARACTERISTIC_WITH_UUID_QUERY_RESULT,

//     P_W2_SEND_ALL_CHARACTERISTIC_DESCRIPTORS_QUERY,
//     P_W4_ALL_CHARACTERISTIC_DESCRIPTORS_QUERY_RESULT,

//     P_W2_SEND_INCLUDED_SERVICE_QUERY,/*0xB*/
//     P_W4_INCLUDED_SERVICE_QUERY_RESULT,
//     P_W2_SEND_INCLUDED_SERVICE_WITH_UUID_QUERY,
//     P_W4_INCLUDED_SERVICE_UUID_WITH_QUERY_RESULT,

//     P_W2_SEND_READ_CHARACTERISTIC_VALUE_QUERY,
//     P_W4_READ_CHARACTERISTIC_VALUE_RESULT,

//     P_W2_SEND_READ_BLOB_QUERY,/*0x11*/
//     P_W4_READ_BLOB_RESULT,

//     P_W2_SEND_READ_BY_TYPE_REQUEST,
//     P_W4_READ_BY_TYPE_RESPONSE,

//     P_W2_SEND_READ_MULTIPLE_REQUEST,
//     P_W4_READ_MULTIPLE_RESPONSE,

//     P_W2_SEND_WRITE_CHARACTERISTIC_VALUE,/*0x17*/
//     P_W4_WRITE_CHARACTERISTIC_VALUE_RESULT,

//     P_W2_PREPARE_WRITE,
//     P_W4_PREPARE_WRITE_RESULT,
//     P_W2_PREPARE_RELIABLE_WRITE,
//     P_W4_PREPARE_RELIABLE_WRITE_RESULT,

//     P_W2_EXECUTE_PREPARED_WRITE,/*0x1D*/
//     P_W4_EXECUTE_PREPARED_WRITE_RESULT,
//     P_W2_CANCEL_PREPARED_WRITE,
//     P_W4_CANCEL_PREPARED_WRITE_RESULT,
//     P_W2_CANCEL_PREPARED_WRITE_DATA_MISMATCH,
//     P_W4_CANCEL_PREPARED_WRITE_DATA_MISMATCH_RESULT,

//     P_W2_SEND_READ_CLIENT_CHARACTERISTIC_CONFIGURATION_QUERY,/*0x23*/
//     P_W4_READ_CLIENT_CHARACTERISTIC_CONFIGURATION_QUERY_RESULT,
//     P_W2_WRITE_CLIENT_CHARACTERISTIC_CONFIGURATION,
//     P_W4_CLIENT_CHARACTERISTIC_CONFIGURATION_RESULT,

//     P_W2_SEND_READ_CHARACTERISTIC_DESCRIPTOR_QUERY,
//     P_W4_READ_CHARACTERISTIC_DESCRIPTOR_RESULT,

//     P_W2_SEND_READ_BLOB_CHARACTERISTIC_DESCRIPTOR_QUERY,
//     P_W4_READ_BLOB_CHARACTERISTIC_DESCRIPTOR_RESULT,/*0x2A*/

//     P_W2_SEND_WRITE_CHARACTERISTIC_DESCRIPTOR,
//     P_W4_WRITE_CHARACTERISTIC_DESCRIPTOR_RESULT,

//     // all long writes use this
//     P_W2_PREPARE_WRITE_CHARACTERISTIC_DESCRIPTOR,
//     P_W4_PREPARE_WRITE_CHARACTERISTIC_DESCRIPTOR_RESULT,
//     P_W2_EXECUTE_PREPARED_WRITE_CHARACTERISTIC_DESCRIPTOR,
//     P_W4_EXECUTE_PREPARED_WRITE_CHARACTERISTIC_DESCRIPTOR_RESULT,/*0x30*/

//     // gatt reliable write API use this (manual version of the above)
//     P_W2_PREPARE_WRITE_SINGLE,
//     P_W4_PREPARE_WRITE_SINGLE_RESULT,

//     P_W4_CMAC_READY,
//     P_W4_CMAC_RESULT,
//     P_W2_SEND_SIGNED_WRITE,
//     P_W4_SEND_SINGED_WRITE_DONE,
// } gatt_client_state_t;


// typedef enum
// {
//     CENTRAL_IDLE,
//     CENTRAL_W4_NAME_QUERY_COMPLETE,
//     CENTRAL_W4_NAME_VALUE,
//     CENTRAL_W4_MTU_EXCHG,
//     CENTRAL_W4_RECONNECTION_ADDRESS_QUERY_COMPLETE,
//     CENTRAL_W4_PERIPHERAL_PRIVACY_FLAG_QUERY_COMPLETE,
//     CENTRAL_W4_SIGNED_WRITE_QUERY_COMPLETE,
//     CENTRAL_W4_PRIMARY_SERVICES_ALL,
//     CENTRAL_W4_PRIMARY_SERVICES_ONE_BY_UUID,
//     CENTRAL_W4_INCLUDED_SERVICE_QUERY,
//     CENTRAL_ENTER_SERVICE_UUID_4_DISCOVER_CHARACTERISTICS,
//     CENTRAL_ENTER_START_HANDLE_4_DISCOVER_CHARACTERISTICS,
//     CENTRAL_ENTER_END_HANDLE_4_DISCOVER_CHARACTERISTICS,
//     CENTRAL_W4_DISCOVER_CHARACTERISTICS_ALL_FOR_A_SERVICE,
//     CENTRAL_W4_DISCOVER_CHARACTERISTICS_ONE_BY_UUID,
//     CENTRAL_W4_CHARACTERISTICS,
//     CENTRAL_W4_DISCOVER_CHARACTERISTIC_DESCRIPTORS,
//     CENTRAL_W4_READ_CHARACTERISTIC_VALUE_BY_HANDLE,
//     CENTRAL_ENTER_HANDLE_4_READ_CHARACTERISTIC_VALUE_BY_UUID,
//     CENTRAL_W4_READ_CHARACTERISTIC_VALUE_BY_UUID,
//     CENTRAL_ENTER_OFFSET_4_READ_LONG_CHARACTERISTIC_VALUE_BY_HANDLE,
//     CENTRAL_W4_READ_LONG_CHARACTERISTIC_VALUE_BY_HANDLE,
//     CENTRAL_W4_READ_CHARACTERISTIC_DESCRIPTOR_BY_HANDLE,
//     CENTRAL_ENTER_OFFSET_4_READ_LONG_CHARACTERISTIC_DESCRIPTOR_BY_HANDLE,
//     CENTRAL_W4_READ_LONG_CHARACTERISTIC_DESCRIPTOR_BY_HANDLE,
//     CENTRAL_W4_READ_MULTIPLE_CHARACTERISTIC_VALUES,
//     CENTRAL_W4_WRITE_WITHOUT_RESPONSE,
//     CENTRAL_W4_WRITE_CHARACTERICISTIC_VALUE,
//     CENTRAL_ENTER_HANDLE_4_WRITE_LONG_CHARACTERISTIC_VALUE,
//     CENTRAL_W4_WRITE_LONG_CHARACTERISTIC_VALUE,
//     CENTRAL_W4_RELIABLE_WRITE_LONG_CHARACTERISTIC_VALUE,
//     CENTRAL_W4_WRITE_CHARACTERISTIC_DESCRIPTOR,
//     CENTRAL_ENTER_HANDLE_4_WRITE_LONG_CHARACTERISTIC_DESCRIPTOR,
//     CENTRAL_W4_WRITE_LONG_CHARACTERISTIC_DESCRIPTOR,
//     CENTRAL_W4_INCLUDED_SERVICES,
//     CENTRAL_W4_SIGNED_WRITE,
//     CENTRAL_W4_WRITE_CLIENT_CHARACTERISTIC_CONFIGURATION,
//     CENTRAL_W4_PREPARE_WRITE_CHAR_VALUE,
//     CENTRAL_W4_PREPARE_WRITE_EXCUTE_CHAR_VALUE,
//     CENTRAL_W4_PREPARE_WRITE_CANCEL_CHAR_VALUE,

//     CENTRAL_W4_ENTER_HANDLE_4_PREPARE_WRITE,
//     CENTRAL_W4_ENTER_OFFSET_4_PREPARE_WRITE,

//     CENTRAL_GPA_ENTER_UUID,
//     CENTRAL_GPA_ENTER_START_HANDLE,
//     CENTRAL_GPA_ENTER_END_HANDLE,
//     CENTRAL_GPA_W4_RESPONSE,
//     CENTRAL_GPA_W4_RESPONSE2,
//     CENTRAL_GPA_W4_RESPONSE3,
//     CENTRAL_GPA_W4_RESPONSE4,
// } central_state_t;



typedef enum
{
    GATTC_USER_NOTIFICATION,
    GATTC_USER_INDICATION,
    GATTC_USER_MTU_EXCHG,
    GATTC_USER_INCLUDE_SERVICES_QUERY,
    GATTC_USER_PRIMARY_SERVICES_QUERY_ALL,
    GATTC_USER_PRIMARY_SERVICES_QUERY_ONE,
    GATTC_USER_CHARACTERISTICS_QUERY_ALL,
    GATTC_USER_CHARACTERISTICS_QUERY_ONE_BY_UUID,
    GATTC_USER_CHARACTERISTICS_DESCRIPTOR_QUERY,
    GATTC_USER_CHARACTERISTICS_WRITE_RESULT,
    GATTC_USER_CHARACTERISTICS_READ_BY_HANDLE_RESULT,
    GATTC_USER_WRITE_CLIENT_CHARACTERISTIC_CONFIGURATION,
    GATTC_USER_CHARACTERISTICS_READ_BY_UUID_RESULT,
    GATTC_USER_CHARACTERISTICS_BLOB_READ_BY_HANDLE_RESULT,
    GATTC_USER_PREPARE_WRITE_CHAR_RESULT,
    GATTC_USER_PREPARE_WRITE_EXCUTE_CHAR_RESULT,
    GATTC_USER_PREPARE_WRITE_CANCEL_CHAR_RESULT,

    GATTC_USER_WRITE_LONG_CHAR_RESULT,
    GATTC_USER_RELIABLE_WRITE_LONG_CHAR_RESULT,


    GATTC_USER_CHARACTERISTICS_DESCRIP_WRITE_RESULT,
    GATTC_USER_CHARACTERISTICS_DESCRIP_READ_RESULT,

} user_client_state;

/* API_START */
typedef struct
{
    uint16_t include_handle;
    uint16_t include_serv_start_group_handle;
    uint16_t include_serv_end_group_handle;
    uint16_t uuid16;
    uint8_t  uuid128[16];
} gatt_client_include_service_t;

typedef struct
{
    uint16_t start_group_handle;
    uint16_t end_group_handle;
    uint16_t uuid16;
    uint8_t  uuid128[16];
} gatt_client_service_t;

typedef struct
{
    uint16_t start_handle;
    uint16_t value_handle;
    uint16_t end_handle;
    uint16_t properties;
    uint16_t uuid16;
    uint8_t  uuid128[16];
} gatt_client_characteristic_t;

typedef struct
{
    uint16_t handle;
    uint16_t uuid16;
    uint8_t  uuid128[16];
} gatt_client_characteristic_descriptor_t;


// typedef struct
// {
//     gatt_client_state_t gatt_client_state;
//     central_state_t central_state;

//     uint16_t  u16Uuid16;
//     uint8_t  uuid128[16];

//     uint16_t start_group_handle;
//     uint16_t end_group_handle;

//     uint16_t query_start_handle;
//     uint16_t query_end_handle;

//     uint8_t  characteristic_properties;
//     uint16_t characteristic_start_handle;

//     uint16_t attribute_handle;
//     uint16_t attribute_offset;
//     uint16_t attribute_length;
//     uint8_t* attribute_value;

//     // read multiple characteristic values
//     uint16_t    read_multiple_handle_count;
//     uint16_t*   read_multiple_handles;

//     uint16_t client_characteristic_configuration_handle;
//     uint8_t  client_characteristic_configuration_value[2];

//     uint8_t  filter_with_uuid;
//     uint8_t  send_confirmation;

//     int      le_device_index;
//     uint8_t  cmac[8];

// } t_gatt_client;

//extern t_gatt_client *g_gatt_client;

typedef uint32_t ( *gatt_client_call_back ) ( uint16_t u16ConnHandle, uint16_t u16OpCode, uint16_t u16ErrCode, uint8_t* pu8Buf, uint16_t  u16Len );
/**
 * @brief Set up GATT client.
 */
extern void rom_gatt_client_api_init ( gatt_client_call_back callback );
extern uint8_t rom_gatt_client_api_discover_primary_services ( uint16_t u16ConnHandle );
extern uint8_t rom_gatt_client_api_discover_primary_services_by_uuid16 ( uint16_t u16ConnHandle, uint16_t  u16Uuid16 );
extern uint8_t rom_gatt_client_api_discover_primary_services_by_uuid128 ( uint16_t u16ConnHandle, uint8_t* pu8Uuid128 );
extern uint8_t rom_gatt_client_api_discover_characteristics_for_handle_range_by_uuid16 ( uint16_t u16ConnHandle, uint16_t  u16StartHandle, uint16_t  u16EndHandle, uint16_t  u16Uuid16 );
extern uint8_t rom_gatt_client_api_discover_characteristics_for_handle_range_by_uuid128 ( uint16_t u16ConnHandle, uint16_t  u16StartHandle, uint16_t  u16EndHandle, uint8_t* pu8Uuid128 );
extern uint8_t rom_gatt_client_api_discover_characteristic_descriptors ( uint16_t u16ConnHandle, gatt_client_characteristic_t* pstCharacteristic );
extern uint8_t rom_gatt_client_api_discover_characteristics_for_service ( uint16_t u16ConnHandle, gatt_client_service_t* pstService );
extern uint8_t rom_gatt_client_api_find_included_services_for_service ( uint16_t u16ConnHandle, gatt_client_service_t* pstService );


extern uint8_t rom_gatt_client_api_write_client_characteristic_configuration  ( uint16_t u16ConnHandle, gatt_client_characteristic_t* pstCharacteristic, uint16_t configuration );
extern uint8_t rom_gatt_client_api_read_long_value_of_characteristic_using_value_handle_with_offset ( uint16_t u16ConnHandle, uint16_t characteristic_value_handle, uint16_t  u16Offset );
extern uint8_t rom_gatt_client_api_cancel_write ( uint16_t u16ConnHandle );
extern uint8_t rom_gatt_client_api_execute_write ( uint16_t u16ConnHandle );
extern uint8_t rom_gatt_client_api_prepare_write ( uint16_t u16ConnHandle, uint16_t attribute_handle, uint16_t  u16Offset, uint16_t  u16Len, uint8_t* pu8Data );
extern uint8_t rom_gatt_client_api_reliable_write_long_value_of_characteristic ( uint16_t u16ConnHandle, uint16_t  u16ValueHandle, uint16_t value_length, uint8_t* pu8Value );
extern uint8_t rom_gatt_client_api_write_long_value_of_characteristic ( uint16_t u16ConnHandle, uint16_t  u16ValueHandle, uint16_t value_length, uint8_t* pu8Value );
extern uint8_t rom_gatt_client_api_write_value_of_characteristic_without_response ( uint16_t u16ConnHandle, uint16_t  u16ValueHandle, uint16_t value_length, uint8_t* pu8Value );
extern uint8_t rom_gatt_client_api_write_value_of_characteristic ( uint16_t u16ConnHandle, uint16_t  u16ValueHandle, uint16_t value_length, uint8_t* pu8Data );
extern uint8_t rom_gatt_client_api_read_value_of_characteristic_using_value_handle ( uint16_t u16ConnHandle, uint16_t  u16ValueHandle );
extern uint8_t rom_gatt_client_api_read_value_of_characteristics_by_uuid16 ( uint16_t u16ConnHandle, uint16_t  u16StartHandle, uint16_t  u16EndHandle, uint16_t  u16Uuid16 );
extern uint8_t rom_gatt_client_api_read_value_of_characteristics_by_uuid128 ( uint16_t u16ConnHandle, uint16_t  u16StartHandle, uint16_t  u16EndHandle, uint8_t* pu8Uuid128 );
extern uint8_t rom_gatt_client_api_write_characteristic_descriptor_using_descriptor_handle ( uint16_t u16ConnHandle, uint16_t u16DescriptorHandle, uint16_t  u16Len, uint8_t* pu8Data );
extern uint8_t rom_gatt_client_api_mtu_exchange ( uint16_t conn_handle,  uint16_t u16Mtu );


#if defined __cplusplus
}
#endif

#endif
