/*************************************************************************************************************
 * @file    hci.h
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
#ifndef HCI_H
#define HCI_H


#define HCI_EVENT_PARAM_COMMAND_COMPLETE_BUFFER_SIZE    (128)


typedef struct
{
    uint8_t Status;
    uint8_t Num_HCI_Command_Packets;
    uint16_t Command_Opcode;
}__attribute__((packed))
stHciEventParamCommandStatus_t;


typedef struct
{
    uint8_t Status;
}__attribute__((packed))
stHciReturnParametersStatusOnly_t;

typedef struct
{
    uint8_t Subevent_Code;
    uint8_t Status;
    uint16_t Connection_Handle;
    uint8_t Role;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint16_t Conn_Interval;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint8_t Master_Clock_Accuracy;
}__attribute__((packed))
stHciEventParamLEConnectionComplete_t;
typedef struct
{
    uint8_t Subevent_Code;
    uint8_t Status;
    uint16_t Connection_Handle;
    uint8_t Role;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint8_t Local_Resolvable_Private_Address[6];
    uint8_t Peer_Resolvable_Private_Address[6];
    uint16_t Conn_Interval;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint8_t Master_Clock_Accuracy;
}__attribute__((packed))
stHciEventParamLEEnhancedConnectionComplete_t;

typedef struct
{
    uint8_t Status;
    uint16_t Connection_Handle;
    uint8_t Reason;
}__attribute__((packed))
stHciEventParamDisconnectionComplete_t;

typedef struct
{
    uint8_t Status;
    uint16_t Connection_Handle;
    uint8_t Encryption_Enabled;
}__attribute__((packed))
stHciEventParamEncryptionChange_t;
 
 
typedef struct
{
    uint8_t Status;
    uint16_t Connection_Handle;
}__attribute__((packed))
stHciEventParamEncryptionKeyRefreshComplete_t;


typedef struct
{
    uint8_t Subevent_Code;
    uint8_t Status;
    uint16_t Connection_Handle;
    uint16_t Conn_Interval;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
}stHciEventParamLEConnectionUpdateComplete_t;
 

typedef struct
{
    uint8_t Subevent_Code;
    uint16_t Connection_Handle;
    uint8_t Random_Number[8];
    uint16_t Encrypted_Diversifier;
}__attribute__((packed))
stHciEventParamLELongTermKeyRequest_t;

 
typedef struct
{
    uint8_t Subevent_Code;
    uint16_t Connection_Handle;
    uint16_t MaxTxOctets;
    uint16_t MaxTxTime;
    uint16_t MaxRxOctets;
    uint16_t MaxRxTime;
}__attribute__((packed))
stHciEventParamLEDataLengthChange_t;


typedef struct
{
    uint8_t Subevent_Code;
    uint8_t Status;
    uint16_t Connection_Handle;
    uint8_t TX_PHY;
    uint8_t RX_PHY;
}__attribute__((packed))
stHciEventParamLEPhyUpdateComplete_t;


typedef struct
{
    uint8_t Status;
    uint16_t Connection_Handle;
    uint8_t Version;
    uint16_t Manufacturer_Name;
    uint16_t Subversion;
}__attribute__((packed))
stHciEventParamReadRemoteVersionInformationComplete_t;


typedef struct
{
    uint8_t Subevent_Code;
    uint8_t Status;
    uint16_t Connection_Handle;
    uint64_t LE_Features;
}__attribute__((packed))
stHciEventParamLEReadRemoteFeaturesComplete_t;

typedef struct
{
    uint8_t Number_of_Handles;
    uint16_t Connection_Handle;
    uint16_t Num_Of_Completed_Packets;
}__attribute__((packed))
stHciEventParamNumberOfCompletedPackets_t;

typedef struct
{
    uint8_t Subevent_Code;
    uint8_t Status;
    uint8_t Advertising_Handle;
    uint16_t Connection_Handle;
    uint8_t Num_Completed_Extended_Advertising_Events;
}__attribute__((packed))
stHciEventParamLEAdvertisingSetTerminated_t;

typedef struct
{
    uint8_t Subevent_Code;
    uint8_t Advertising_Handle;
    uint8_t Scanner_Address_Type;
    uint8_t Scanner_Address[6];
}__attribute__((packed))
stHciEventParamLEScanRequestReceived_t;

typedef struct
{
    uint8_t Subevent_Code;
}__attribute__((packed))
stHciEventParamLEScanTimeout_t;


typedef struct
{
    uint8_t Subevent_Code;
    uint16_t Connection_Handle;
    uint8_t Channel_Selection_Algorithm;
}__attribute__((packed))
stHciEventParamLEChannelSelectionAlgorithm_t;


typedef struct
{
    uint16_t Connection_Handle;
    uint8_t Reason;
}__attribute__((packed))
stHciCommandParamHCIDisconnect_t;

typedef struct
{
    uint16_t Connection_Handle;
    uint16_t Conn_Interval_Min;
    uint16_t Conn_Interval_Max;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint16_t Minimum_CE_Length;
    uint16_t Maximum_CE_Length;
}__attribute__((packed))
stHciCommandParamLEConnectionUpdate_t;
typedef struct
{
    uint16_t Connection_Handle;
    uint16_t Conn_Interval_Min;
    uint16_t Conn_Interval_Max;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint16_t Minimum_CE_Length;
    uint16_t Maximum_CE_Length;
}__attribute__((packed))
stHciCommandParamLEEnhanceConnectionUpdate_t;


typedef struct
{
    uint16_t Connection_Handle;
    uint8_t Long_Term_Key[16];
}__attribute__((packed))
stHciCommandParamLELongTermKeyRequestReply_t;
typedef struct
{
    uint8_t Status;
    uint16_t Connection_Handle;
}__attribute__((packed))
stHciReturnParametersLELongTermKeyRequestReply_t;

typedef struct
{
    uint16_t Connection_Handle;
}__attribute__((packed))
stHciCommandParamLELongTermKeyRequestNegativeReply_t;
typedef struct
{
    uint8_t Status;
    uint16_t Connection_Handle;
}__attribute__((packed))
stHciReturnParametersLELongTermKeyRequestNegativeReply_t;

typedef struct
{
    uint16_t Connection_Handle;
    uint8_t Random_Number[8];
    uint16_t Encrypted_Diversifier;
    uint8_t Long_Term_Key[16];
}__attribute__((packed))
stHciCommandParamLEStartEncryption_t;

typedef struct
{
    uint16_t Connection_Handle;
    uint16_t TxOctets;
    uint16_t TxTime;
}__attribute__((packed))
stHciCommandParamLESetDataLength_t;
typedef struct
{
    uint8_t Status;
    uint16_t Connection_Handle;
}__attribute__((packed))
stHciReturnParametersLESetDataLength_t;

typedef struct
{
    uint8_t Random_Address[6];
}__attribute__((packed))
stHciCommandParamLESetRandomAddress_t;

typedef struct
{
    //no params
}__attribute__((packed))
stHciCommandParamLEReadWhiteListSize_t;
typedef struct
{
    uint8_t Status;
    uint8_t White_List_Size;
}__attribute__((packed))
stHciReturnParametersLEReadWhiteListSize_t;

typedef struct
{
    //no params
}__attribute__((packed))
stHciCommandParamLEClearWhiteList_t;

typedef struct
{
    uint8_t Address_Type;
    uint8_t Address[6];
}__attribute__((packed))
stHciCommandParamLEAddDeviceToWhiteList_t;

typedef struct
{
    uint8_t Address_Type;
    uint8_t Address[6];
}__attribute__((packed))
stHciCommandParamLERemoveDeviceFromWhiteList_t;

typedef struct
{
    uint16_t Advertising_Interval_Min;
    uint16_t Advertising_Interval_Max;
    uint8_t Advertising_Type;
    uint8_t Own_Address_Type;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint8_t Advertising_Channel_Map;
    uint8_t Advertising_Filter_Policy;
}__attribute__((packed))
stHciCommandParamLESetAdvertisingParameters_t;

typedef struct
{
    uint8_t Advertising_Data_Length;
    uint8_t Advertising_Data[31];
}__attribute__((packed))
stHciCommandParamLESetAdvertisingData_t;

typedef struct
{
    uint8_t Scan_Response_Data_Length;
    uint8_t Scan_Response_Data[31];
}__attribute__((packed))
stHciCommandParamLESetScanResponseData_t;

typedef struct
{
    uint8_t Advertising_Enable;
}__attribute__((packed))
stHciCommandParamLESetAdvertisingEnable_t;

typedef struct
{
    uint8_t LE_Scan_Type;
    uint16_t LE_Scan_Interval;
    uint16_t LE_Scan_Window;
    uint8_t Own_Address_Type;
    uint8_t Scanning_Filter_Policy;
}__attribute__((packed))
stHciCommandParamLESetScanParameters_t;

typedef struct
{
    uint8_t LE_Scan_Enable;
    uint8_t Filter_Duplicates;
}__attribute__((packed))
stHciCommandParamLESetScanEnable_t;

typedef struct
{
    uint16_t LE_Scan_Interval;
    uint16_t LE_Scan_Window;
    uint8_t Initiator_Filter_Policy;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint8_t Own_Address_Type;
    uint16_t Conn_Interval_Min;
    uint16_t Conn_Interval_Max;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint16_t Minimum_CE_Length;
    uint16_t Maximum_CE_Length;
}__attribute__((packed))
stHciCommandParamLECreateConnection_t;

typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLECreateConnectionCancel_t;
typedef struct
{
    uint16_t Connection_Handle;
    uint8_t ALL_PHYS; //bit 0 no preference for tx phy ,bit 1 no preference for rx phy
    uint8_t TX_PHYS; //bit 0  1 2 for 1m 2m coded  that host prefer to use
    uint8_t RX_PHYS;//bit 0  1 2 for 1m 2m coded  that host prefer to use
    uint16_t PHY_options;//val 0 for no preferred coding, 1 for prefer S=2 ,2 for S=8
}__attribute__((packed))
stHciCommandParamLESetPHY_t;


typedef struct
{
    uint16_t Connection_Handle;
}__attribute__((packed))
stHciCommandParamReadRemoteVersionInformation_t;


typedef struct
{
    uint16_t Connection_Handle;
}__attribute__((packed))
stHciCommandParamLEReadRemoteFeatures_t;


typedef struct
{
    uint8_t Peer_Identity_Address_Type;
    uint8_t Peer_Identity_Address[6];
    uint8_t Peer_IRK[16];
    uint8_t Local_IRK[16];
}__attribute__((packed))
stHciCommandParamLEAddDevToResolvingList_t;


typedef struct
{
    uint8_t Peer_Identity_Address_Type;
    uint8_t Peer_Identity_Address[6];
}__attribute__((packed))
stHciCommandParamLERemoveDevToResolvingList_t;

typedef struct
{
    uint8_t Status;
    uint8_t Resolving_List_Size;
}__attribute__((packed))
stHciReturnParametersLEReadResolvingListSize_t;

typedef struct
{
    uint8_t Address_Resolution_Enable;
}__attribute__((packed))
stHciCommandParamLESetAddressResolutionEnable_t;


typedef struct
{
    uint16_t RPA_Timeout ; //Range: 0x0001 to 0xA1B8(1 s to approximately 11.5 hours)Default: 0x0384 (900 s or 15 minutes)
}__attribute__((packed))
stHciCommandParamLESetResolvablePrivateAddressTimeout_t;

typedef struct
{
    uint8_t Peer_Identity_Address_Type;
    uint8_t Peer_Identity_Address[6];
    uint8_t Privacy_Mode;
}__attribute__((packed))
stHciCommandParamLESetPrivacyMode_t;


typedef struct
{
    uint16_t Handle;
}__attribute__((packed))
stHciCommandParamHCIReadRSSI_t;

typedef struct
{
    uint8_t Status;
    uint16_t Handle;
    int8_t RSSI;
}__attribute__((packed))
stHciReturnParametersHCIReadRSSI_t;


typedef struct
{
    uint16_t Connection_Handle;
}__attribute__((packed))
stHciCommandParamLEReadChannelMap_t;

typedef struct
{
    uint8_t Status;
    uint16_t Connection_Handle;
    uint8_t Channel_Map[5];
}__attribute__((packed))
stHciReturnParametersLEReadChannelMap_t;



typedef struct
{
    uint8_t Advertising_Handle;
    uint8_t Advertising_Random_Address[6];
}__attribute__((packed))
stHciCommandParamLESetAdvertisingSetRandomAddress_t;


typedef struct
{
    uint8_t Advertising_Handle;
    uint16_t Advertising_Event_Properties;
    uint8_t Primary_Advertising_Interval_Min[3];
    uint8_t Primary_Advertising_Interval_Max[3];
    uint8_t Primary_Advertising_Channel_Map;
    uint8_t Own_Address_Type;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint8_t Advertising_Filter_Policy;
    int8_t Advertising_Tx_Power;
    uint8_t Primary_Advertising_PHY;
    uint8_t Secondary_Advertising_Max_Skip;
    uint8_t Secondary_Advertising_PHY;
    uint8_t Advertising_SID;
    uint8_t Scan_Request_Notification_Enable;
}__attribute__((packed))
stHciCommandParamLESetExtendedAdvertisingParameters_t;
typedef struct
{
    uint8_t Status;
    int8_t Selected_Tx_Power;
}__attribute__((packed))
stHciReturnParametersLESetExtendedAdvertisingParameters_t;

typedef struct
{
    uint8_t Advertising_Handle;
    uint16_t Advertising_Event_Properties;
    uint8_t Primary_Advertising_Interval_Min[3];
    uint8_t Primary_Advertising_Interval_Max[3];
    uint8_t Primary_Advertising_Channel_Map;
    uint8_t Secondary_Advertising_Channel_Map[5];
    uint8_t Own_Address_Type;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint8_t Advertising_Filter_Policy;
    int8_t Advertising_Tx_Power;
    uint8_t Primary_Advertising_PHY;
    uint8_t Secondary_Advertising_Max_Skip;
    uint8_t Secondary_Advertising_PHY;
    uint16_t PHY_Options;
    uint8_t Advertising_SID;
    uint8_t Scan_Request_Notification_Enable;
}__attribute__((packed))
stHciCommandParamVendorSetExtendedAdvertisingParameters_t;
typedef struct
{
    uint8_t Status;
    int8_t Selected_Tx_Power;
}__attribute__((packed))
stHciReturnParametersVendorSetExtendedAdvertisingParameters_t;

typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEReadMaximumAdvertisingDataLength_t;
typedef struct
{
    uint8_t Status;
    uint16_t Maximum_Advertising_Data_Length;
}__attribute__((packed))
stHciReturnParametersLEReadMaximumAdvertisingDataLength_t;

typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEReadNumberofSupportedAdvertisingSets_t;
typedef struct
{
    uint8_t Status;
    uint8_t Num_Supported_Advertising_Sets;
}__attribute__((packed))
stHciReturnParametersLEReadNumberofSupportedAdvertisingSets_t;

typedef struct
{
    uint8_t Advertising_Handle;
}__attribute__((packed))
stHciCommandParamLERemoveAdvertisingSet_t;

typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEClearAdvertisingSets_t;


typedef struct
{
    uint8_t Enable;
    uint8_t Filter_Duplicates;
    uint16_t Duration;
    uint16_t Period;
}__attribute__((packed))
stHciCommandParamLESetExtendedScanEnable_t;


typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEReadBufferSize_t;
typedef struct
{
    uint8_t Status;
    uint16_t LE_Data_Packet_Length;
    uint8_t Total_Num_LE_Data_Packets;
}__attribute__((packed))
stHciReturnParametersLEReadBufferSize_t;


typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamReadLocalVersionInformation_t;
typedef struct
{
    uint8_t Status;
    uint8_t HCI_Version;
    uint16_t HCI_Revision;
    uint8_t LMP_Version;
    uint16_t Manufacturer_Name;
    uint16_t LMP_Subversion;
}__attribute__((packed))
stHciReturnParametersReadLocalVersionInformation_t;


typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamReadLocalSupportedCommands_t;
typedef struct
{
    uint8_t Status;
    uint8_t Supported_Commands[64];
}__attribute__((packed))
stHciReturnParametersReadLocalSupportedCommands_t;


typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamReadLocalSupportedFeatures_t;
typedef struct
{
    uint8_t Status;
    uint8_t LMP_Features[8];
}__attribute__((packed))
stHciReturnParametersReadLocalSupportedFeatures_t;

typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEReadSupportedStates_t;
typedef struct
{
    uint8_t Status;
    uint8_t LE_States[8];
}__attribute__((packed))
stHciReturnParametersLEReadSupportedStates_t;


typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamReadBDADDR_t;
typedef struct
{
    uint8_t Status;
    uint8_t BD_ADDR[6];
}__attribute__((packed))
stHciReturnParametersReadBDADDR_t;


typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEReadLocalSupportedFeatures_t;
typedef struct
{
    uint8_t Status;
    uint8_t LE_Features[8];
}__attribute__((packed))
stHciReturnParametersLEReadLocalSupportedFeatures_t;


typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEReadSuggestedDefaultDataLength_t;
typedef struct
{
    uint8_t Status;
    uint16_t SuggestedMaxTxOctets;
    uint16_t SuggestedMaxTxTime;
}__attribute__((packed))
stHciReturnParametersLEReadSuggestedDefaultDataLength_t;


typedef struct
{
    uint16_t SuggestedMaxTxOctets;
    uint16_t SuggestedMaxTxTime;
}__attribute__((packed))
stHciCommandParamLEWriteSuggestedDefaultDataLength_t;


typedef struct
{
    uint8_t Channel_Map[5];
}__attribute__((packed))
stHciCommandParamLESetHostChannelClassification_t;


typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEReadMaximumDataLength_t;
typedef struct
{
    uint8_t Status;
    uint16_t supportedMaxTxOctets;
    uint16_t supportedMaxTxTime;
    uint16_t supportedMaxRxOctets;
    uint16_t supportedMaxRxTime;
}__attribute__((packed))
stHciReturnParametersLEReadMaximumDataLength_t;


typedef struct
{
    uint16_t Connection_Handle;
}__attribute__((packed))
stHciCommandParamLEReadPHY_t;
typedef struct
{
    uint8_t Status;
    uint16_t Connection_Handle;
    uint8_t TX_PHY;
    uint8_t RX_PHY;
    
}__attribute__((packed))
stHciReturnParametersLEReadPHY_t;



typedef struct
{
    uint8_t ALL_PHYS;
    uint8_t TX_PHYS;
    uint8_t RX_PHYS;
}__attribute__((packed))
stHciCommandParamLESetDefaultPHY_t;



typedef struct
{
    uint8_t Key[16];
    uint8_t Plaintext_Data[16];
}__attribute__((packed))
stHciCommandParamLEEncrypt_t;
typedef struct
{
    uint8_t Status;
    uint8_t Encrypted_Data[16];
}__attribute__((packed))
stHciReturnParametersLEEncrypt_t;

typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLERand_t;
typedef struct
{
    uint8_t Status;
    uint8_t Random_Number[8];
}__attribute__((packed))
stHciReturnParametersLERand_t;

typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEReadTransmitPower_t;
typedef struct
{
    uint8_t Status;
    int8_t Min_Tx_Power;
    int8_t Max_Tx_Power;
}__attribute__((packed))
stHciReturnParametersLEReadTransmitPower_t;


typedef struct
{
    ////no param
}__attribute__((packed))
stHciCommandParamLEReadAdvertisingPhysicalChannelTxPower_t;
typedef struct
{
    uint8_t Status;
    int8_t Transmit_Power_Level;
}__attribute__((packed))
stHciReturnParametersLEReadAdvertisingPhysicalChannelTxPower_t;


typedef struct
{
    uint64_t Event_Mask;
}__attribute__((packed))
stHciCommandParamSetEventMask_t;

typedef struct
{
    uint64_t LE_Event_Mask;
}__attribute__((packed))
stHciCommandParamLESetEventMask_t;

typedef struct
{
    uint8_t Subevent_Code;
    uint8_t Status;
    uint16_t Connection_Handle;
    uint8_t Role;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint8_t Peer_RPA_Resoluted; //only  Peer_RPA_Resoluted,Peer_Identify_Address exists
    uint8_t Peer_Identify_Address_Type;
    uint8_t Peer_Identify_Address[6];
    uint16_t Conn_Interval;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint8_t Master_Clock_Accuracy;
    uint8_t Own_Address_Type;
    uint8_t Own_Address_Be_RPA;
    uint8_t Own_Address[6];
}__attribute__((packed))
stHciEventParamVendorConnectionComplete_t;

typedef struct
{
    uint8_t Public_Address[6];
}__attribute__((packed))
stHciCommandParamVendorSetPublicAddress_t;

typedef struct
{
    uint8_t Advertising_Index;
    uint16_t Advertising_Interval_Min;
    uint16_t Advertising_Interval_Max;
    uint8_t Advertising_Type;
    uint8_t Own_Address_Type;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint8_t Advertising_Channel_Map;
    uint8_t Advertising_Filter_Policy;
}__attribute__((packed))
stHciCommandParamVendorSetAdvertisingParameters_t;

typedef struct
{
    uint8_t Advertising_Index;
    uint8_t Advertising_Data_Length;
    uint8_t Advertising_Data[31];
}__attribute__((packed))
stHciCommandParamVendorSetAdvertisingData_t;

typedef struct
{
    uint8_t Advertising_Index;
    uint8_t Scan_Response_Data_Length;
    uint8_t Scan_Response_Data[31];
}__attribute__((packed))
stHciCommandParamVendorSetScanResponseData_t;

typedef struct
{
    uint8_t Advertising_Index;
    uint8_t Advertising_Enable;
}__attribute__((packed))
stHciCommandParamVendorSetAdvertisingEnable_t;

typedef struct
{
    uint8_t LE_Scan_Channel_Map;
    uint8_t LE_Scan_Type;
    uint16_t LE_Scan_Interval;
    uint16_t LE_Scan_Window;
    uint8_t Own_Address_Type;
    uint8_t Scanning_Filter_Policy;
}__attribute__((packed))
stHciCommandParamVendorSetScanParameters_t;

typedef struct
{
    uint8_t LE_Scan_Channel_Map;
    uint16_t LE_Scan_Interval;
    uint16_t LE_Scan_Window;
    uint8_t Initiator_Filter_Policy;
    uint8_t Peer_Address_Type;
    uint8_t Peer_Address[6];
    uint8_t Own_Address_Type;
    uint16_t Conn_Interval_Min;
    uint16_t Conn_Interval_Max;
    uint16_t Conn_Latency;
    uint16_t Supervision_Timeout;
    uint16_t Minimum_CE_Length;
    uint16_t Maximum_CE_Length;
}__attribute__((packed))
stHciCommandParamVendorCreateConnection_t;

typedef struct
{
    uint16_t Connection_Handle;
    uint8_t Channel_Map[5];
}__attribute__((packed))
stHciCommandParamVendorUpdateChannelMap_t;


typedef uint16_t (*callback_get_event_parameter_max_length)(void);

typedef bool (*callback_host_send_command_packet)(uint8_t OGF, uint16_t OCF, uint8_t Parameter_Total_Length, uint8_t* Parameters);
typedef bool (*callback_host_send_acl_data)(uint16_t Handle, uint8_t Packet_Boundary_Flag, uint8_t Broadcast_Flag, uint16_t Data_Total_Length, uint8_t* Data);
typedef bool (*callback_controller_report_acl_data)(uint16_t Handle, uint8_t Packet_Boundary_Flag, uint8_t Broadcast_Flag, uint16_t Data_Total_Length, uint8_t* Data);
typedef bool (*callback_controller_report_event)(uint8_t Event_Code, uint8_t Parameter_Total_Length, uint8_t* Event_Parameter);


void rom_hci_set_get_event_paramter_max_length_callback(callback_get_event_parameter_max_length callback);
void rom_hci_set_host_send_command_packet_callback(callback_host_send_command_packet callback);
void rom_hci_set_host_send_acl_data_callback(callback_host_send_acl_data callback);
void rom_hci_set_controller_report_acl_data_callback(callback_controller_report_acl_data callback);
void rom_hci_set_controller_report_event_callback(callback_controller_report_event callback);


uint16_t rom_hci_get_event_parameter_max_length(void);
bool rom_hci_host_send_command_packet(uint8_t OGF, uint16_t OCF, uint8_t Parameter_Total_Length, uint8_t* Parameters);
bool rom_hci_host_send_acl_data(uint16_t Handle, uint8_t Packet_Boundary_Flag, uint8_t Broadcast_Flag, uint16_t Data_Total_Length, uint8_t* Data);
bool rom_hci_controller_report_acl_data(uint16_t Handle, uint8_t Packet_Boundary_Flag, uint8_t Broadcast_Flag, uint16_t Data_Total_Length, uint8_t* Data);
bool rom_hci_controller_report_event(uint8_t Event_Code, uint8_t Parameter_Total_Length, uint8_t* Event_Parameter);


#endif
