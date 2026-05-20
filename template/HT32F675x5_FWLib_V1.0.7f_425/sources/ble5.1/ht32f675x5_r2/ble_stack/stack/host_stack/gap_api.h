/*************************************************************************************************************
 * @file    gap_api.h
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

#ifndef GAP_API_H
#define GAP_API_H


typedef enum
{
    GAP_ADVERTISING_TYPE_ADV_IND                    = 0x00,
    GAP_ADVERTISING_TYPE_DIRECT_IND_HIGH_DUTY_CYCLE = 0x01,
    GAP_ADVERTISING_TYPE_ADV_SCAN_IND               = 0x02,
    GAP_ADVERTISING_TYPE_NONCONN_IND                = 0x03,
    GAP_ADVERTISING_TYPE_DIRECT_IND_LOW_DUTY_CYCLE  = 0x04,
}
EN_GAP_ADVERTISING_TYPE_T;


typedef enum
{
    GAP_WHITE_LIST_ADDRESS_TYPE_PUBLIC    = 0x00,
    GAP_WHITE_LIST_ADDRESS_TYPE_RANDOM    = 0x01,
    GAP_WHITE_LIST_ADDRESS_TYPE_ANONYMOUS = 0xFF,
}
EN_GAP_WHITE_LIST_ADDRESS_TYPE_T;


typedef enum
{
    GAP_OWN_ADDRESS_TYPE_PUBLIC = 0x00,
    GAP_OWN_ADDRESS_TYPE_RANDOM = 0x01,
    GAP_OWN_ADDRESS_TYPE_RESOLVABLE_OR_PUBLIC = 0x02,
    GAP_OWN_ADDRESS_TYPE_RESOLVABLE_OR_RANDOM = 0x03,
}
EN_GAP_OWN_ADDRESS_TYPE_T;


typedef enum
{
    GAP_ADV_PEER_ADDRESS_TYPE_PUBLIC_OR_PUBLIC_IDENTITY = 0x00,
    GAP_ADV_PEER_ADDRESS_TYPE_RANDOM_OR_RANDOM_IDENTITY = 0x01,
}
EN_GAP_ADV_PEER_ADDRESS_TYPE_T;

typedef enum
{
    GAP_INITIATOR_PEER_ADDRESS_TYPE_PUBLIC = 0x00,
    GAP_INITIATOR_PEER_ADDRESS_TYPE_RANDOM = 0x01,
    GAP_INITIATOR_PEER_ADDRESS_TYPE_PUBLIC_IDENTITY = 0x02,
    GAP_INITIATOR_PEER_ADDRESS_TYPE_RANDOM_IDENTITY = 0x03,
}
EN_GAP_INITIATOR_PEER_ADDRESS_TYPE_T;

typedef enum
{
    GAP_ADV_CHANNEL_MAP_37 = (1U << 0),
    GAP_ADV_CHANNEL_MAP_38 = (1U << 1),
    GAP_ADV_CHANNEL_MAP_39 = (1U << 2),
}
EN_GAP_ADV_CHANNEL_MAP_T;

typedef enum
{
    GAP_ADV_FILTER_POLICY_CONN_ALL_SCAN_ALL                = 0x00,
    GAP_ADV_FILTER_POLICY_CONN_ALL_SCAN_WHITELIST          = 0x01,
    GAP_ADV_FILTER_POLICY_CONN_WHITELIST_SCAN_ALL          = 0x02,
    GAP_ADV_FILTER_POLICY_CONN_WHITELIST_SCAN_WHITELIST    = 0x03,
}
EN_GAP_ADV_FILTER_POLICY_T;

typedef struct
{
    uint16_t u16AdvertisingIntervalMin625us;
    uint16_t u16AdvertisingIntervalMax625us;
    EN_GAP_ADVERTISING_TYPE_T enumAdvertisingType;
    EN_GAP_OWN_ADDRESS_TYPE_T enumOwnAddressType;
    EN_GAP_ADV_PEER_ADDRESS_TYPE_T enumPeerAddressType;
    uint8_t pu8PeerAddress[6];
    uint8_t u8AdvertisingChannelMap;
    EN_GAP_ADV_FILTER_POLICY_T enumAdvertisingFilterPolicy;
}__attribute__((packed))
stGapSetAdvertisingParameters_t;


typedef enum
{
    GAP_SCAN_TYPE_PASSIVE = 0x00,
    GAP_SCAN_TYPE_ACTIVE  = 0x01,
}
EN_GAP_SCAN_TYPE_T;

typedef enum
{
    GAP_SCAN_FILTER_POLICY_ACCEPT_ALL                              = 0x00,
    GAP_SCAN_FILTER_POLICY_ACCEPT_WHITELIST                        = 0x01,
    GAP_SCAN_FILTER_POLICY_ACCEPT_ALL_NOT_RESOLVED_DIRECTED        = 0x02,
    GAP_SCAN_FILTER_POLICY_ACCEPT_WHITELIST_NOT_RESOLVED_DIRECTED  = 0x03,
}
EN_GAP_SCAN_FILTER_POLICY_T;

typedef struct
{
    EN_GAP_SCAN_TYPE_T enumScanType;
    uint8_t u8ScanChannelMap;
    uint16_t u16ScanInterval625us;
    uint16_t u16ScanWindow625us;
    EN_GAP_OWN_ADDRESS_TYPE_T enumOwnAddressType;
    EN_GAP_SCAN_FILTER_POLICY_T enumScanningFilterPolicy;
}__attribute__((packed))
stGapSetScanParameters_t;

typedef enum
{
    GAP_INITIATOR_FILTER_POLICY_WHITELIST_IS_NOT_USED   = 0x00,
    GAP_INITIATOR_FILTER_POLICY_WHITELIST_IS_USED       = 0x01,
}
EN_GAP_INITIATOR_FILTER_POLICY_T;

typedef struct
{
    uint8_t u8ScanChannelMap;
    uint16_t u16ScanInterval625us;
    uint16_t u16ScanWindow625us;
    EN_GAP_INITIATOR_FILTER_POLICY_T enumInitiatorFilterPolicy;
    EN_GAP_INITIATOR_PEER_ADDRESS_TYPE_T enumPeerAddressType;
    uint8_t pu8PeerAddress[6];
    EN_GAP_OWN_ADDRESS_TYPE_T enumOwnAddressType;
    uint16_t u16ConnIntervalMin1250us;
    uint16_t u16ConnIntervalMax1250us;
    uint16_t u16ConnLatency;
    uint16_t u16SupervisionTimeout10ms;
}__attribute__((packed))
stGapCreateConnection_t;

typedef enum
{
    GAP_DISCONNECT_REASON_AUTHENTICATION_FAILURE                                      = 0x05,
    
    GAP_DISCONNECT_REASON_REMOTE_USER_TERMINATED_CONNECTION                           = 0x13,
    GAP_DISCONNECT_REASON_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES    = 0x14,
    GAP_DISCONNECT_REASON_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_POWER_OFF        = 0x15,
    
    GAP_DISCONNECT_REASON_UNSUPPORTED_REMOTE_FEATURE                                  = 0x1A,
    
    GAP_DISCONNECT_REASON_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED                         = 0x29,
    
    GAP_DISCONNECT_REASON_UNACCEPTABLE_CONNECTION_PARAMETERS                          = 0x3B,
}
EN_GAP_DISCONNECT_REASON_T;

typedef struct
{
    uint16_t u16ConnIntervalMin1250us;
    uint16_t u16ConnIntervalMax1250us;
    uint16_t u16ConnLatency;
    uint16_t u16SupervisionTimeout10ms;
}__attribute__((packed))
stGapConnectionUpdate_t;


typedef enum
{
    GAP_PREFER_PHY_1M    = (1U<<0),
    GAP_PREFER_PHY_2M    = (1U<<1),
    GAP_PREFER_PHY_CODED = (1U<<2),
}
EN_GAP_PREFER_PHY_T;

typedef enum
{
    GAP_CODED_PHY_OPTION_TX_NO_PREFER = 0,
    GAP_CODED_PHY_OPTION_TX_PREFER_S2 = 1,
    GAP_CODED_PHY_OPTION_TX_PREFER_S8 = 2,
}
EN_GAP_CODED_PHY_OPTION_T;

typedef struct
{
    uint8_t u8PreferTxPhys;
    uint8_t u8PreferRxPhys;
    EN_GAP_CODED_PHY_OPTION_T enumCodedPhyOption;
}__attribute__((packed))
stGapSetPhy_t;

typedef struct
{
    uint16_t u16Ediv;
    uint8_t pu8Rand[8];
    uint8_t pu8Ltk[16];
    uint8_t u8KeySize;
    uint8_t u8Authenticated;
    uint8_t u8Authorized;
    
}__attribute__((packed))
stGapBondInfo_t;




typedef enum
{
    GAP_EXTENDED_ADVERTISING_TYPE_LEGACY_CONNECTABLE_SCANNABLE_UNDIRECTED = 0,                  //ADV_IND
    GAP_EXTENDED_ADVERTISING_TYPE_LEGACY_CONNECTABLE_NONSCANNABLE_DIRECTED_HIGH_DUTY_CYCLE,     //ADV_DIRECT_IND
    GAP_EXTENDED_ADVERTISING_TYPE_LEGACY_CONNECTABLE_NONSCANNABLE_DIRECTED_LOW_DUTY_CYCLE,      //ADV_DIRECT_IND
    GAP_EXTENDED_ADVERTISING_TYPE_LEGACY_NONCONNECTABLE_SCANNABLE_UNDIRECTED,                   //ADV_SCAN_IND
    GAP_EXTENDED_ADVERTISING_TYPE_LEGACY_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED,                //ADV_NONCONN_IND
    
    
    GAP_EXTENDED_ADVERTISING_TYPE_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED,
    GAP_EXTENDED_ADVERTISING_TYPE_NONCONNECTABLE_NONSCANNABLE_DIRECTED,
    
    GAP_EXTENDED_ADVERTISING_TYPE_CONNECTABLE_NONSCANNABLE_UNDIRECTED,
    GAP_EXTENDED_ADVERTISING_TYPE_CONNECTABLE_NONSCANNABLE_DIRECTED,
    
    GAP_EXTENDED_ADVERTISING_TYPE_NONCONNECTABLE_SCANNABLE_UNDIRECTED,
    GAP_EXTENDED_ADVERTISING_TYPE_NONCONNECTABLE_SCANNABLE_DIRECTED,
}
EN_GAP_EXTENDED_ADVERTISING_TYPE_T;

typedef enum
{
    GAP_PHY_1M    = 0x01,
    GAP_PHY_2M    = 0x02,
    GAP_PHY_CODED = 0x03,
}
EN_GAP_PHY_T;

typedef struct
{
    EN_GAP_EXTENDED_ADVERTISING_TYPE_T enumAdvertisingType;
    bool bAnonymous;/** Omit advertiser's address from all PDUs.
                        @note Anonymous advertising is only available for
                        @ref GAP_EXTENDED_ADVERTISING_TYPE_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED and
                        @ref GAP_EXTENDED_ADVERTISING_TYPE_NONCONNECTABLE_NONSCANNABLE_DIRECTED. **/
    
    uint32_t u32PrimaryAdvertisingIntervalMin625us;/** 0x000000~0xFFFFFF **/
    uint32_t u32PrimaryAdvertisingIntervalMax625us;/** 0x000000~0xFFFFFF, no less than @ref u32PrimaryAdvertisingIntervalMin625us**/
    uint8_t u8PrimaryAdvertisingChannelMap;/**a bit fields that indicates the advertising channels 
                                                    that shall be used when transmitting advertising packets, @ref EN_GAP_ADV_CHANNEL_MAP_T **/
    uint8_t pu8SecondaryAdvertisingChannelMap[5];/**a bit fields that indicates the secondary advertising channels 
                                                    that shall be used when transmitting advertising packets, This parameter contains 37 1-bit fields.
                                                    The n-th such field (in the range 0 to 36) contains the value for the
                                                    Link Layer channel index n.
                                                    Channel n is unused = 0.
                                                    Channel n is used = 1.
                                                    The most significant bits are reserved for future use.
                                                    as an exception, if all bits sets to zero(non channel used), all channels will be used instead**/
    EN_GAP_CODED_PHY_OPTION_T enumCodedPhyOption;
    EN_GAP_PHY_T enumPrimaryAdvertisingPhy;/** @ref GAP_PHY_1M or @ref GAP_PHY_CODED **/
    
    EN_GAP_OWN_ADDRESS_TYPE_T enumOwnAddressType;
    EN_GAP_ADV_PEER_ADDRESS_TYPE_T enumPeerAddressType;
    uint8_t pu8PeerAddress[6];
    EN_GAP_ADV_FILTER_POLICY_T enumAdvertisingFilterPolicy;
    
    uint8_t u8SecondaryAdvertisingMaxSkip;/**Maximum advertising events the Controller can skip before sending the
                                            AUX_ADV_IND packets on the secondary advertising physical channel **/
    EN_GAP_PHY_T enumSecondaryAdvertisingPhy;
    
    uint8_t u8AdvertisingSID;/** 0x00~0x0F,  Value of the Advertising SID subfield in the ADI field of the PDU**/
    
    bool bScanRequestNotificationEnable; /** The Scan_Request_Notification_Enable parameter indicates whether the
                                            Controller shall send notifications upon the receipt of a scan request PDU that 
                                            is in response to an advertisement from the specified advertising set that
                                            contains its device address and is from a scanner that is allowed by the
                                            advertising filter policy **/
    
}__attribute__((packed))
stGapSetExtendedAdvertisingParameters_t;

typedef enum
{
    GAP_EXTENDED_ADVERTISING_DATA_OPERATION_INTERMEDIATE_FRAGMENT = 0x00,
    GAP_EXTENDED_ADVERTISING_DATA_OPERATION_FIRST_FRAGMENT        = 0x01,
    GAP_EXTENDED_ADVERTISING_DATA_OPERATION_LAST_FRAGMENT         = 0x02,
    GAP_EXTENDED_ADVERTISING_DATA_OPERATION_COMPLETE              = 0x03,
    GAP_EXTENDED_ADVERTISING_DATA_OPERATION_UNCHANGE              = 0x04,
}
EN_GAP_EXTENDED_ADVERTISING_DATA_OPERATION_T;

typedef enum
{
    GAP_EXTENDED_ADVERTISING_SCAN_RESPONSE_DATA_OPERATION_INTERMEDIATE_FRAGMENT   = 0x00,
    GAP_EXTENDED_ADVERTISING_SCAN_RESPONSE_DATA_OPERATION_FIRST_FRAGMENT          = 0x01,
    GAP_EXTENDED_ADVERTISING_SCAN_RESPONSE_DATA_OPERATION_LAST_FRAGMENT           = 0x02,
    GAP_EXTENDED_ADVERTISING_SCAN_RESPONSE_DATA_OPERATION_COMPLETE                = 0x03,
}
EN_GAP_EXTENDED_ADVERTISING_SCAN_RESPONSE_DATA_OPERATION_T;

typedef struct
{
    bool bEnable;                           /** Enable:true or Disable:false **/
    uint16_t u16Duration10ms;               /** Advertising Duration
                                                0 : No advertising duration. Continuous Advertising
                                                0x0001~0xFFFF : 10 ms to 655,350 ms**/
    uint8_t u8MaxExtendedAdvertisingEvents; /**Maximum number of extended advertising events the Controller shall 
                                                    attempt to send prior to terminating the extended advertising
                                                0 : No maximum number of advertising events**/
}__attribute__((packed))
stGapSetExtendedAdvertisingEnable_t;

typedef struct
{
    EN_GAP_OWN_ADDRESS_TYPE_T enumOwnAddressType;
    EN_GAP_SCAN_FILTER_POLICY_T enumScanningFilterPolicy;
    uint16_t u16ScanInterval625us;/** scan interval for all scannning phys **/
    
    bool bEnableScanningPhy1M;
    EN_GAP_SCAN_TYPE_T enumScanType1M;
    uint16_t u16ScanWindow625us1M;
    uint8_t u8ScanChannelMap1M;/**a bit fields that indicates the scanning channels 
                                                    that shall be used when scanning advertising packets, @ref EN_GAP_ADV_CHANNEL_MAP_T **/
    
    bool bEnableScanningPhyCoded;
    EN_GAP_SCAN_TYPE_T enumScanTypeCoded;
    uint16_t u16ScanWindow625usCoded;
    uint8_t u8ScanChannelMapCoded;/**a bit fields that indicates the scanning channels 
                                                    that shall be used when scanning advertising packets, @ref EN_GAP_ADV_CHANNEL_MAP_T **/
}__attribute__((packed))
stGapSetExtendedScanParameters_t;


typedef struct
{
    EN_GAP_INITIATOR_FILTER_POLICY_T enumInitiatorFilterPolicy;
    EN_GAP_OWN_ADDRESS_TYPE_T enumOwnAddressType;
    EN_GAP_INITIATOR_PEER_ADDRESS_TYPE_T enumPeerAddressType;
    uint8_t pu8PeerAddress[6];
    
    bool bEnabledScan1M;
    uint16_t u16ScanInterval1M625us;
    uint16_t u16ScanWindow1M625us;
    uint8_t u8ScanMap1M;
    
    bool bEnabledScanCoded;
    uint16_t u16ScanIntervalCoded625us;
    uint16_t u16ScanWindowCoded625us;
    uint8_t u8ScanMapCoded;
    
    uint16_t u16ConnIntervalMin1250us;
    uint16_t u16ConnIntervalMax1250us;
    uint16_t u16ConnLatency;
    uint16_t u16SupervisionTimeout10ms;
}__attribute__((packed))
stGapExtendedCreateConnection_t;


/**
@ref MSG_BLE_SET_ADVERTISING_PARAMETERS_COMMAND_RESULT
*/
bool rom_gap_api_set_advertising_parameters(uint8_t u8AdvertisingIndex, stGapSetAdvertisingParameters_t* pstParam);

/**
@ref MSG_BLE_SET_ADVERTISING_DATA_COMMAND_RESULT
*/
bool rom_gap_api_set_advertising_data(uint8_t u8AdvertisingIndex, uint8_t* pu8AdvertisingData, uint8_t u8AdvertisingDataLength);

/**
@ref MSG_BLE_SET_SCAN_RESPONSE_DATA_COMMAND_RESULT
*/
bool rom_gap_api_set_scan_response_data(uint8_t u8AdvertisingIndex, uint8_t* pu8ScanResponseData, uint8_t u8ScanResponseDataLength);

/**
@ref MSG_BLE_SET_ADVERTISING_ENABLE_COMMAND_RESULT
*/
bool rom_gap_api_set_advertising_enable(uint8_t u8AdvertisingIndex, bool bAdvertisingEnable);

/**
@ref MSG_BLE_SET_SCAN_PARAMETERS_COMMAND_RESULT
*/
bool rom_gap_api_set_scan_parameters(stGapSetScanParameters_t* pstParam);

/**
@ref MSG_BLE_SET_SCAN_ENABLE_COMMAND_RESULT
**/
bool rom_gap_api_set_scan_enable(bool bScanEnable, bool bFilterDuplicates);

/**
@ref MSG_BLE_CREATE_CONNECTION_COMMAND_RESULT
*/
bool rom_gap_api_create_connection(stGapCreateConnection_t* pstParam);

/**
@ref MSG_BLE_CREATE_CONNECTION_CANCEL_COMMAND_RESULT
*/
bool rom_gap_api_create_connection_cancel(void);

/**
@ref MSG_BLE_DISCONNECT_COMMAND_RESULT
@ref MSG_BLE_DISCONNECTED_IND
**/
bool rom_gap_api_disconnect(uint16_t u16ConnHandle, EN_GAP_DISCONNECT_REASON_T enumDisconnectReason);

/**
@ref MSG_BLE_SET_EXTENDED_ADVERTISING_PARAMETERS_COMMAND_RESULT
*/
bool rom_gap_api_set_extended_advertising_parameters(uint8_t u8AdvertisingHandle, stGapSetExtendedAdvertisingParameters_t* pstParam);

/**
@ref MSG_BLE_SET_ADVERTISING_SET_RANDOM_ADDRESS_COMMAND_RESULT
*/
bool rom_gap_api_set_extended_advertising_random_address(uint8_t u8AdvertisingHandle, uint8_t pu8RandomAddress[6]);

/**
@param u8AdvertisingDataLength : 0 ~ min( @ref HCI_COMMAND_PARAMETERS_SIZE - 4, 251)
@ref MSG_BLE_SET_EXTENDED_ADVERTISING_DATA_COMMAND_RESULT
*/
bool rom_gap_api_set_extended_advertising_data(uint8_t u8AdvertisingHandle, EN_GAP_EXTENDED_ADVERTISING_DATA_OPERATION_T enumOperation, bool bFragmentPreferred,
    uint8_t* pu8AdvertisingData, uint8_t u8AdvertisingDataLength);

/**
@param u8ScanResponseDataLength : 0 ~ min( @ref HCI_COMMAND_PARAMETERS_SIZE - 4, 251)
@ref MSG_BLE_SET_EXTENDED_SCAN_RESPONSE_DATA_COMMAND_RESULT
*/
bool rom_gap_api_set_extended_scan_response_data(uint8_t u8AdvertisingHandle, EN_GAP_EXTENDED_ADVERTISING_SCAN_RESPONSE_DATA_OPERATION_T enumOperation, bool bFragmentPreferred,
    uint8_t* pu8ScanResponseData, uint8_t u8ScanResponseDataLength);

/**
@ref MSG_BLE_SET_EXTENDED_ADVERTISING_ENABLE_COMMAND_RESULT
*/
bool rom_gap_api_set_extended_advertising_enable(uint8_t u8AdvertisingHandle, stGapSetExtendedAdvertisingEnable_t* pstEnableParam);

/**
@ref MSG_BLE_REMOVE_ADVERTISING_SET_COMMAND_RESULT
*/
bool rom_gap_api_remove_extended_advertising_set(uint8_t u8AdvertisingHandle);

/**
@ref MSG_BLE_SET_EXTENDED_SCAN_PARAMETERS_COMMAND_RESULT
*/
bool rom_gap_api_set_extended_scan_parameters(stGapSetExtendedScanParameters_t* pstParam);

/**
@ref MSG_BLE_SET_EXTENDED_SCAN_ENABLE_COMMAND_RESULT
*/
bool rom_gap_api_set_extended_scan_enable(bool bScanEnable, bool bFilterDuplicates);

/**
@ref MSG_BLE_EXTENDED_CREATE_CONNECTION_COMMAND_RESULT
*/
bool rom_gap_api_extended_create_connection(stGapExtendedCreateConnection_t* pstParam);

/**
@ref MSG_BLE_SET_PUBLIC_ADDRESS_COMMAND_RESULT
*/
bool rom_gap_api_set_public_device_address(uint8_t pu8Address[6]);

/**
@ref MSG_BLE_SET_RANDOM_ADDRESS_COMMAND_RESULT
*/
bool rom_gap_api_set_random_device_address(uint8_t pu8Address[6]);

//synchronized API
bool rom_gap_api_get_public_device_address(uint8_t pu8Address[6]);

//synchronized API
bool rom_gap_api_get_random_device_address(uint8_t pu8Address[6]);

/**
@ref MSG_BLE_CLEAR_WHITE_LIST_COMMAND_RESULT
*/
bool rom_gap_api_clear_white_list(void);

/**
@ref MSG_BLE_ADD_DEVICE_TO_WHITE_LIST_COMMAND_RESULT
*/
bool rom_gap_api_add_device_to_white_list(EN_GAP_WHITE_LIST_ADDRESS_TYPE_T enumDeviceType, uint8_t pu8DeviceAddress[6]);

/**
@ref MSG_BLE_REMOVE_DEVICE_FROM_WHITE_LIST_COMMAND_RESULT
*/
bool rom_gap_api_remove_device_from_white_list(EN_GAP_WHITE_LIST_ADDRESS_TYPE_T enumDeviceType, uint8_t pu8DeviceAddress[6]);

/**
@ref MSG_BLE_CONNECTION_UPDATE_COMMAND_RESULT as master
@ref MSG_BLE_CONNECTION_UPDATE_COMPLETE_IND
*/
bool rom_gap_api_connection_parameters_update(uint16_t u16ConnHandle, stGapConnectionUpdate_t* pstParam);

/**
@ref MSG_BLE_SET_PHY_COMMAND_RESULT
*/
bool rom_gap_api_connection_set_phy(uint16_t u16ConnHandle, stGapSetPhy_t* pstParam);

bool rom_gap_api_read_remote_version( uint16_t u16ConnHandle );

/**
@ref MSG_BLE_READ_REMOTE_FEATURES_COMMAND_RESULT
*/
bool rom_gap_api_read_remote_features( uint16_t u16ConnHandle );

/**
@ref MSG_BLE_SET_DATA_LENGTH_COMMAND_RESULT
*/
bool rom_gap_api_set_data_length( uint16_t u16ConnHandle, uint16_t u16TxOctets);

/**
@ref MSG_BLE_READ_RSSI_COMMAND_RESULT
*/
bool rom_gap_api_read_rssi( uint16_t u16ConnHandle );

/**
@ref MSG_BLE_READ_CHANNEL_MAP_COMMAND_RESULT
*/
bool rom_gap_api_read_channel_map(uint16_t u16ConnHandle);

/**
@ref MSG_BLE_UPDATE_CHANNEL_MAP_COMMAND_RESULT
*/
bool rom_gap_api_update_channel_map(uint16_t u16ConnHandle, uint8_t pu8ChannelMap[5]);

bool rom_gap_api_set_default_channel_map(uint8_t pu8ChannelMap[5]);

/**
* @brief  get maximum transmission unit
* @param  N/A
* @return mtu
*/
extern uint16_t rom_gap_api_get_mtu( uint16_t u16ConnHandle );

 


/**
* @brief as slave ,send security request PDU, to notify master start pair or encrypt;as master start pair or encrypt
* @param  N/A
* @return BLE_SUCCESS for success.
*/
extern void rom_gap_api_send_security_req ( uint16_t u16ConnHandle );


/**
* @brief    config the value of key which display in peer device,during the Pairing process
* @param conn_handle:
 connect index for Multi - connection, always 0 for single connection
* @param passkey:
 the value of key which display in peer device,during the Pairing process, if need local device input key, use this API
* @return  none
*/
extern void rom_gap_api_input_passkey_during_pair( uint16_t u16ConnHandle, uint32_t u32Passkey );

/**
* @brief      reject for long term key req, so the connect will not be encrypted
* @param   conn_handle: connect index for Multi - connection, always 0 for single connection
* @return   none
* @ref MSG_BLE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_COMMAND_RESULT
*/
extern void rom_gap_api_long_term_key_request_negative_reply( uint16_t u16ConnHandle );

/**
* @brief  config long term key to make  the connect encrypted
* @param  ltk: pointer to ltk
* @return BLE_API_RET_CODE_ENUM.
* @ref MSG_BLE_LONG_TERM_KEY_REQUEST_REPLY_COMMAND_RESULT
*/
extern void rom_gap_api_long_term_key_request_reply( uint16_t u16ConnHandle, uint8_t* pu8Ltk );

/**
 * @brief  set pin num,if not use random num,  peer device should input this pin_num when pair
 * @param  is_use_random_num: 1 for use random num to pair; 0 for use pin_num to pair
 * @param  u32PinNum: pin num, range(0~999999), valid when 0==is_use_random_num
 * @return none
 */
extern void rom_gap_api_set_pair_pin_code( bool is_use_random_num, uint32_t u32PinNum);

/**
* @brief       set period to update resolved address
* @param    u32Ms, period
* @return     none
*/
extern void gap_api_set_period_to_update_resolved_address( uint32_t u32Ms );

/**
* @brief      config bond info save by app or by stack,default by stack
*               only for legacy pair, for sc pair bond info mast be saved by app
* @param   onoff: 0 means bond info saved by stack,1 means bond info saved by app
* @return   none
*/
extern void rom_gap_api_sm_bond_info_save_by_app_config_only_for_legacy_pair( uint32_t onoff );

/**
* @brief      start or stop use resolved address
* @param    u8En, 1 for start ,0 for stop
* @return     alway 0
*/
extern int  gap_api_start_stop_use_resolved_address( uint8_t u8En );

/**
* @brief  update Pair parameter
* @param iocap :
    IO_CAPABILITY_DISPLAY_ONLY = 0,
    IO_CAPABILITY_DISPLAY_YES_NO=1,
    IO_CAPABILITY_KEYBOARD_ONLY=2,
    IO_CAPABILITY_NO_INPUT_NO_OUTPUT=3,
    IO_CAPABILITY_KEYBOARD_DISPLAY=4,
* @param authreq:
#define SM_AUTHREQ_NO_BONDING        0x00
#define SM_AUTHREQ_BONDING           0x01
#define SM_AUTHREQ_MITM_PROTECTION   0x04
#define SM_AUTHREQ_SECURE_CONNECTION 0x08
#define SM_AUTHREQ_KEYPRESS          0x10

ex. authreq=SM_AUTHREQ_BONDING|SM_AUTHREQ_MITM_PROTECTION
* @param keysize:
range 7-16,   16 is recommended
* @return  none
*/
extern void rom_gap_api_update_pair_para( uint8_t iocap, uint8_t authreq, uint8_t keysize );

/**
* @brief    as master role, set bond info to setup encrytion
* @param  conn_handle
* @param  stGapBondInfo_t
* @return   none
*/
extern void rom_gap_api_set_bond_info_for_setup_encryption (uint16_t u16ConnHandle,stGapBondInfo_t* pstBondinfo);  

/**
* @brief      register call back function to set oob data, for using OOB pair method
* @param   get_oob_data_callback: call back function to set oob data
* @return   none
*/
extern void rom_gap_api_register_oob_data_callback( int ( *get_oob_data_callback ) ( uint8_t peer_addr_type, uint8_t peer_addr[6], uint8_t  oob_data[16] ) );

/**
* @brief      register call back function to get oob data, for using OOB pair method in Secure connection Mode
* @param   get_oob_data_callback: call back function to get remote oob data: confirm and random generate from pub key
* @return   none
*/
extern void rom_gap_api_register_sc_oob_data_callback( int ( *get_sc_oob_data_callback ) (uint8_t addres_type, uint8_t addr[6], uint8_t * oob_sc_peer_confirm, uint8_t * oob_sc_peer_random) );

/**
* @brief      register call back function to get oob data, and start to generate local oob data: confirm and random generate from pub key
            local oob data should give to remote by using out of band mothod, i.e. NFC
* @param   get_oob_data_callback: call back function to get local oob data: confirm and random generate from pub key
* @return   none
*/
extern void rom_gap_api_sm_generate_local_sc_oob_data ( void ( *callback ) ( const uint8_t *confirm_value, const uint8_t *random_value ) );

/**
* @brief    check if the number displayed by local is same as peer  during numeric_comparison pairing
* @param conn_handle:
 connect index for Multi - connection, always 0 for single connection
* @param confirm_sucess:
   1  for the number is same as peer, 0 for different
* @return  none
*/
extern void rom_gap_api_sm_numeric_comparison_confirm( uint16_t u16ConnHandle ,uint8_t confirm_sucess);

extern void rom_gap_api_set_secure_connections_only ( uint8_t u8Enable );

/**
@ref MSG_BLE_ADD_DEVICE_TO_RESOLVING_LIST_COMMAND_RESULT
*/
bool  rom_gap_api_add_device_to_resolving_list ( uint8_t Peer_Identity_Address_Type, uint8_t *Peer_Identity_Address , uint8_t *Peer_IRK , uint8_t* Local_IRK  );

/**
@ref MSG_BLE_REMOVE_DEVICE_FROM_RESOLVING_LIST_COMMAND_RESULT
*/
bool  rom_gap_api_remove_device_from_resolving_list ( uint8_t Peer_Identity_Address_Type, uint8_t Peer_Identity_Address[6] );

/**
@ref MSG_BLE_SET_PRIVACY_MODE_COMMAND_RESULT
*/
bool  rom_gap_api_set_privacy_mode_for_peer_device ( uint8_t Peer_Identity_Address_Type, uint8_t Peer_Identity_Address[6], uint8_t Privacy_Mode );

/**
@ref MSG_BLE_CLEAR_RESOLVING_LIST_COMMAND_RESULT
*/
bool  rom_gap_api_clear_resolving_list ( void );

/**
@ref MSG_BLE_SET_ADDRESS_RESOLUTION_ENABLE_COMMAND_RESULT
*/
bool  rom_gap_api_set_addr_resolution_enable ( uint8_t enable );

int   rom_gap_api_get_read_resolving_list_size ( void );
bool rom_gap_api_connection_role_is_slave ( uint16_t conn_handle );
void rom_gap_api_sm_init ( void );

#endif 
