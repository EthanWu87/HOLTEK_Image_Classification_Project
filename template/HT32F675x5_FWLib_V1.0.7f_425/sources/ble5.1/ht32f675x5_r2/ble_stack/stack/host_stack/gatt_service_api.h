/*************************************************************************************************************
 * @file    gatt_service_api.h
 * @version V1.0
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


#ifndef __GATT_SERVICE_API_H__
#define __GATT_SERVICE_API_H__

/**
 * ATT
 */
 // Minimum/default MTU
#define ATT_DEFAULT_MTU               23
    // MARK: ATT Error Codes
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
    // custom BTstack ATT error coders
#define ATT_ERROR_DATA_MISMATCH                    0x7e
#define ATT_ERROR_TIMEOUT                          0x7F


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
    // 128 bit UUID used
#define ATT_PROPERTY_UUID128             0x200
    // Authentication required
#define ATT_PROPERTY_AUTHENTICATION_REQUIRED 0x400
    // Authorization from user required
#define ATT_PROPERTY_AUTHORIZATION_REQUIRED  0x800
    // Encryption key size stored in upper 4 bits, 0 == no encryption, encryption key size - 1 otherwise
#define ATT_PROPERTY_KEY_SIZE_REQUIRED_MASK  0xF000    
    // ATT Transaction Timeout of 30 seconds for Command/Response or Incidationc/Confirmation
#define ATT_TRANSACTION_TIMEOUT_MS     30000
    
#define ATT_TRANSACTION_MODE_NONE      0x0
#define ATT_TRANSACTION_MODE_ACTIVE    0x1
#define ATT_TRANSACTION_MODE_EXECUTE   0x2
#define ATT_TRANSACTION_MODE_CANCEL    0x3
#define ATT_TRANSACTION_MODE_CONFIRM_FOR_INDICAT    0x4


//#define HI_UINT16(a) (((a) >> 8) & 0xFF)
//#define LO_UINT16(a) ((a) & 0xFF)

#define GATT_CLIENT_CFG_NOTIFY           0x0001 //!< The Characteristic Value shall be notified
#define GATT_CLIENT_CFG_INDICATE         0x0002 //!< The Characteristic Value shall be indicated
#define GATT_CLIENT_CFG_NONE             0x0000 



/*** Generic Status Return Values ***/
#define RTN_OK                   0x00
#define RTN_FAIL                   0x01
#define RTN_INSUFF_MEM          0x02
#define INVALID_TASK              0x03
#define MSG_BUFFER_NOT_AVAIL      0x04
#define INVALID_MSG_POINTER       0x05
#define INVALID_EVENT_ID          0x06
#define INVALID_INTERRUPT_ID      0x07
#define NO_TIMER_AVAIL            0x08
#define NV_ITEM_UNINIT            0x09
#define NV_OPER_FAILED            0x0A
#define INVALID_MEM_SIZE          0x0B
#define NV_BAD_ITEM_LEN           0x0C


typedef uint16_t (*att_get_attribute_length_callback_t)(uint16_t conn_handle, uint16_t attribute_handle);
typedef uint16_t (*att_read_callback_t)(uint16_t conn_handle, uint16_t attribute_handle, uint16_t offset, uint8_t * buffer, uint16_t buffer_size);

typedef uint32_t (*att_write_callback_t)(uint16_t conn_handle, uint16_t attribute_handle, uint16_t transaction_mode, uint16_t offset, uint8_t *buffer, uint16_t buffer_size);

/**
 * GATT Structure for service callback functions - must be setup by the application
 * and used when GATTServApp_RegisterService() is called.
 */
typedef struct
{
    att_get_attribute_length_callback_t pfn_get_attribute_len_cb;         //!<get attribute len callback function pointer
    att_read_callback_t pfn_read_attr_cb;           //!< Read callback function pointer
    att_write_callback_t pfn_write_attr_cb;         //!< Write callback function pointer
} gatt_serviceCBs_t;

typedef struct
{
    uint16_t       start_handle;
    uint16_t      end_handle;
    gatt_serviceCBs_t  *pfnCB;

} gatts_serv_info_st;


//extern void rom_gatts_api_init ( uint8_t *pu8ProfileBuf, uint16_t u16ProfileBufLen ,gatts_serv_info_st *pstGattsServInfoBuffer,uint16_t u16GattsServInfoBufferNum);

//extern uint16_t rom_gatts_api_add_service_start(bool is_uuid128, uint16_t uuid16, uint8_t* uuid128, gatt_serviceCBs_t  *pServiceCBs);
                                    

//extern uint16_t rom_gatts_api_add_service_end(void);


//extern uint16_t rom_gatts_api_add_char(bool is_uuid128, uint16_t uuid16, uint8_t* uuid128, uint16_t  properties, uint8_t  * data, uint16_t  data_len);


extern uint16_t rom_gatts_api_add_char_descrip(uint16_t uuid16, uint16_t  properties, uint8_t  * data, uint16_t  data_len);

extern uint16_t rom_gatts_api_add_char_descrip_client_config(void);

extern uint32_t rom_gatts_api_send_notify( uint16_t conn_handle, uint16_t  attribute_handle, uint8_t  *value, uint16_t  value_len );

extern uint32_t rom_gatts_api_send_indicate( uint16_t conn_handle, uint16_t attribute_handle, uint8_t  *value, uint16_t  value_len);
extern uint16_t rom_gatts_api_add_include_service (  uint16_t  u16SrvHandle,  uint16_t  u16SrvHandleEnd ,bool is_uuid128, uint16_t u16SrvUuid16, uint8_t *pu8ServUuid128);

extern uint16_t rom_gatts_api_get_last_attribute_handle ( void );
extern bool rom_gatts_api_set_next_attribute_handle ( uint16_t u16Handle );
extern uint16_t rom_gatts_api_get_profile_buffer_used_size ( void );

#endif /* __GATT_SERVICE_API_H__ */


