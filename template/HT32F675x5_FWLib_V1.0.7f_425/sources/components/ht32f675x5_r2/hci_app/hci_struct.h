/*************************************************************************************************************
 * @file    hci_struct.h
 * @version V1.0
 * @date    2021-02-05
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

#ifndef __HCI_STRUCT_H__
#define __HCI_STRUCT_H__

enum
{
    NO_ERROR = 0,
    FAIL  = 1,
    OVERFLOW = 2,
    NO_ENOUGH_FIFO = 3,
    ILLEGAL_COMMAND = 4,
    COMMAND_PAYLOAD_LENGTH_ERROR = 5,
    COMMAND_PAYLOAD_PARA_ERROR = 6,
    DTM_STATUS_ERROR = 7,
};

typedef struct
{
    uint8_t event;
    uint8_t  length;
}   hci_event_header_t;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
    int8_t txPwr;
}  read_tx_pwr_level_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t wlSize;
}  read_wl_size_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t hciVer;
    /*
     HCI_Version    0       Bluetooth Core Specification 1.0b
     1      Bluetooth Core Specification 1.1
     2      Bluetooth Core Specification 1.2
     3      Bluetooth Core Specification 2.0 + EDR
     4      Bluetooth Core Specification 2.1 + EDR
     5      Bluetooth Core Specification 3.0 + HS
     6 		Bluetooth Core Specification 4.0
     7      Bluetooth Core Specification 4.1
     8 - 255        Reserved
     */
    uint8_t hciReverlo8;
    uint8_t hciReverhi8;
    uint8_t lmpVer;                 // same as hciVer
    uint8_t mfNamelo8;				// manufacturer name
    uint8_t mfNamehi8;
    uint8_t lmpSubVerlo8;
    uint8_t lmpSubVerhi8;

}  read_local_ver_info_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t lmpFeature[8];

}  read_local_supported_features_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t bdAddr[6];
}  read_bd_addr_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
    int8_t rssi;
} read_rssi_evt;

typedef struct
{
    uint8_t status;
    uint8_t hcAclDataPcktLenlo8;               //HC_ACL_Data_Packet_Length     2
    uint8_t hcAclDataPcktLenhi8;               //HC_ACL_Data_Packet_Length     2
    uint8_t hcSyncDataPckLen;                //HC_Synchronous_Data_Packet_Length     1
    uint16_t hcTtlNumAclDataPckt;    //HC_Total_Num_ACL_Data_Packets 2
    uint16_t hcTtlNumSyncDataPckt;   //HC_Total_Num_Synchronous_Data_Packets 2
}  read_buffer_size_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t HC_LE_Data_Packet_Lengthlo8;               //HC_ACL_Data_Packet_Length     2
    uint8_t HC_LE_Data_Packet_Lengthhi8;               //HC_ACL_Data_Packet_Length     2
    uint8_t HC_Total_Num_LE_Data_Packets;                //HC_Synchronous_Data_Packet_Length     1
}  le_read_buffer_size_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t packetRecvlo8;               //HC_ACL_Data_Packet_Length     2
    uint8_t packetRecvhi8;               //HC_ACL_Data_Packet_Length     2
    uint8_t packetdata1_byte0;               //HC_ACL_Data_Packet_Length     2
    uint8_t packetdata1_byte1;               //HC_ACL_Data_Packet_Length     2
    uint8_t packetdata1_byte2;               //HC_ACL_Data_Packet_Length     2
    uint8_t packetdata1_byte3;               //HC_ACL_Data_Packet_Length     2
    uint8_t packet_crcerror_countlo8;               //HC_ACL_Data_Packet_Length     2
    uint8_t packet_crcerror_counthi8;               //HC_ACL_Data_Packet_Length     2

}  dtm_cmplt_evt;

typedef struct
{
    uint8_t status;
    int8_t advTxPwr;
}  le_read_adv_ch_tx_pwr_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t leSpptHost;
    uint8_t smltLeHost;      //Simultaneous_LE_Host

}  read_le_host_supported_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
    uint8_t authenticatedPayloadTimeoutlo8;
    uint8_t authenticatedPayloadTimeouthi8;

} read_authenticated_payload_timeout_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;

} write_authenticated_payload_timeout_evt;

typedef struct
{
    uint8_t status;
    uint8_t white_list_size;
} le_read_white_list_size_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
    uint8_t chnlMap[5];
} le_read_channel_map_evt;

typedef struct
{
    uint8_t status;
    uint8_t encrypted_data[16];
} le_encrypt_evt;

typedef struct
{
    uint8_t status;
    uint8_t random_number[8];
} le_rand_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
} le_long_term_key_request_reply_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
} le_long_term_key_request_negative_reply_evt;

typedef struct
{
    uint8_t status;
    uint8_t le_states[8];
} le_supported_states_evt;

typedef struct
{
    uint8_t status;
    uint8_t num_of_pktslo8;
    uint8_t num_of_pktshi8;
} le_test_end_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
} le_remote_cnnct_parameter_request_reply_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
} le_remote_cnnct_parameter_request_negative_reply_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
} le_set_data_length_evt;

typedef struct
{
    uint8_t status;
    uint8_t SuggestedMaxTxOctetslo8;
    uint8_t SuggestedMaxTxOctetshi8;
    uint8_t SuggestedMaxTxTimelo8;
    uint8_t SuggestedMaxTxTimehi8;
} le_read_suggested_default_data_length_evt;

typedef struct
{
    uint8_t status;
    uint8_t Resolving_List_Size;
} le_read_resolving_list_size_evt;

typedef struct
{
    uint8_t status;
    uint8_t Peer_Resolvable_Address[6];
} le_read_peer_resolvable_address_evt;

typedef struct
{
    uint8_t status;
    uint8_t Local_Resolvable_Address[6];
} le_read_local_resolvable_address_evt;

typedef struct
{
    uint8_t status;
    uint8_t supportedMaxTxOctetslo8;
    uint8_t supportedMaxTxOctetshi8;
    uint8_t supportedMaxTxTimelo8;
    uint8_t supportedMaxTxTimehi8;
    uint8_t supportedMaxRxOctetslo8;
    uint8_t supportedMaxRxOctetshi8;
    uint8_t supportedMaxRxTimelo8;
    uint8_t supportedMaxRxTimehi8;
} le_read_maximum_data_length_evt;

typedef struct
{
    uint8_t status;

}  common_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t numHciCmdPckts;
    uint8_t cmdOpCodelo;
    uint8_t cmdOpCodehi;
    uint8_t para0;
    uint8_t para1;
    uint8_t para2;
    uint8_t para3;
} cmd_status_evt;

typedef struct
{
    // 12+n byte
    uint8_t  subEvtCode; //=0x02 // 1byte
    uint8_t  numReports;             // 1byte
    uint8_t  evtType;                   // 1byte//depend on report number
    uint8_t  addr_type;                 // 1byte
    uint8_t  addr6Oct[6];              // 6byte
    uint8_t  length_data;                    // 1byte
    uint8_t  data31Oct[31];           // N byte
    int8_t  rssi_S8;        //signed 8  //1byte
} le_adv_report_evt;


typedef struct
{
    uint8_t  subEvtCode; //=0x02 // 1byte
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
    uint8_t reason;
} discnnt_cmplt_evt;

//zl @11.24
typedef struct
{
    uint8_t  subEvtCode; // =0x01

    uint8_t  status;
    uint8_t cnnctH16bitlo;
    uint8_t cnnctH16bithi;

    uint8_t  role;
    uint8_t  peerAddrType;

    uint8_t  peerAddr6Oct[6];

    uint8_t cnnctInterval16bitlo;
    uint8_t cnnctInterval16bithi;

    uint8_t cnnctLatency16bitlo;
    uint8_t cnnctLatency16bithi;

    uint8_t supervisionTimeout16bitlo;
    uint8_t supervisionTimeout16bithi;

    uint8_t  masterClockAccuracy;
}  le_cnnct_cmplt_evt;

typedef struct
{
    uint8_t   subEvtCode;
    uint8_t  status;
    uint8_t cnnctH16bitlo;
    uint8_t cnnctH16bithi;
    uint8_t cnnctInterval16bitlo;
    uint8_t cnnctInterval16bithi;
    uint8_t cnnctLatency16bitlo;
    uint8_t cnnctLatency16bithi;
    uint8_t supervisionTimeout16bitlo;
    uint8_t supervisionTimeout16bithi;

} le_connection_update_cmplt_evt;

typedef struct
{
    uint8_t subEvtCode;
    uint8_t  status;
    uint8_t cnnctH16bitlo;
    uint8_t cnnctH16bithi;
    uint8_t  leFeatures8Oct[8];

} le_read_rmt_used_features_cmplt_evt;

typedef struct
{
    uint8_t subEvtCode;
    uint8_t  Number_of_Handles; //=0x05
    uint8_t Connection_Handlelo8; //depend on the connection number
    uint8_t Connection_Handlehi8; //depend on the connection number
    uint8_t HC_Num_Of_Completed_Packetslo8;
    uint8_t HC_Num_Of_Completed_Packetshi8;
}  num_of_cmplt_pkt_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
    uint8_t version;
    uint16_t mnftName;
    uint16_t subVer;
} read_rmt_ver_info_cmplt_evt;

typedef struct
{
    uint8_t  subEvtCode; // =0x01
    uint8_t status;
    uint8_t cnnctHlo8;
    uint8_t cnnctHhi8;
    uint8_t   Encryption_Enabled;
} enc_chg_evt;

typedef struct
{
    uint8_t status;
    uint8_t cnnctHlo8;
    uint8_t cnnctHhi8;
} enc_key_fresh_evt;

typedef struct
{
    uint8_t  subEvtCode;
    uint8_t cnnctHlo8;
    uint8_t cnnctHhi8;
    uint8_t  randomNumber8Oct[8];
    uint8_t encryptionDiversifier2oct[2];
}  le_long_term_key_request_evt;

typedef struct
{
    uint8_t subEvtCode;
    uint8_t cnnctHlo8;
    uint8_t cnnctHhi8;
    uint8_t intv_minlo8;
    uint8_t intv_minhi8;
    uint8_t intv_maxlo8;
    uint8_t intv_maxhi8;
    uint8_t lantencylo8;
    uint8_t lantencyhi8;
    uint8_t timeOutlo8;
    uint8_t timeOuthi8;

} le_rmt_cnnct_para_req_evt;

typedef struct
{
    uint8_t subEvtCode;
    uint8_t cnnctHandlelo8;
    uint8_t cnnctHandlehi8;
    uint8_t maxtxoctetslo8;
    uint8_t maxtxoctetshi8;
    uint8_t maxtxtimelo8;
    uint8_t maxtxtimehi8;
    uint8_t maxrxoctetslo8;
    uint8_t maxrxoctetshi8;
    uint8_t maxrxtimelo8;
    uint8_t maxrxtimehi8;
}  le_data_len_chg_evt;

typedef struct
{
    uint8_t subEvtCode;
    uint8_t numReports;
    uint8_t eventType;
    uint8_t dataAddrType;
    uint8_t directAddr[6];
    uint8_t AddrType;
    uint8_t Addr[6];
    int8_t rssi;
}  le_direct_adv_rpt_evt;

typedef struct
{
    uint8_t linkType;
}  data_buffer_overflow_evt;

typedef struct
{
    uint8_t hw_code;
}  hw_err_evt;

typedef struct
{
    uint8_t subEvtCode;
    uint8_t status;
    uint16_t dhkey[64];
} le_read_local_P256_public_key_cmplt_evt;


typedef struct
{
    uint8_t subEvtCode;
    uint8_t status;
    uint16_t dhkey[32];
}  le_gen_dhkey_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t supported_command[64];
} read_local_supported_command_cmplt_evt;

typedef struct
{
    uint8_t status;
    uint8_t le_features[8];
} le_read_local_supported_features_cmplt_evt;

typedef union
{
    read_tx_pwr_level_cmplt_evt read_tx_pwr_levl_cmplt;
    read_wl_size_cmplt_evt     read_wl_size_cmplt;
    read_local_ver_info_cmplt_evt read_local_ver_info_cmplt;
    // read_local_supported_command_cmplt_evt read_local_supported_command_cmplt;
    //  read_local_supported_features_cmplt_evt read_local_supported_features_cmplt;
    read_bd_addr_cmplt_evt  read_bd_addr_cmplt;
    read_rssi_evt read_rssi;
    read_buffer_size_cmplt_evt read_buffer_size_cmplt;
    le_read_buffer_size_cmplt_evt le_read_buffer_size_cmplt;
    le_read_local_supported_features_cmplt_evt le_read_local_supported_features_cmplt;
    dtm_cmplt_evt dtm_cmplt;
    le_read_adv_ch_tx_pwr_cmplt_evt le_read_adv_ch_tx_pwr_cmplt;
    read_le_host_supported_cmplt_evt read_le_host_supported_cmplt;
    read_authenticated_payload_timeout_evt read_authenticated_payload_timeout;
    write_authenticated_payload_timeout_evt write_authenticated_payload_timeout;
    le_read_white_list_size_evt le_read_white_list_size;
    le_read_channel_map_evt le_read_channel_map;
    le_encrypt_evt le_encrypt;
    le_rand_evt le_rand;
    le_long_term_key_request_reply_evt le_long_term_key_request_reply;
    le_long_term_key_request_negative_reply_evt le_long_term_key_request_negative_reply;
    le_supported_states_evt  le_supported_states;
    le_test_end_evt le_test_end;
    le_remote_cnnct_parameter_request_reply_evt le_remote_cnnct_parameter_request_reply;
    le_remote_cnnct_parameter_request_negative_reply_evt le_remote_cnnct_parameter_request_negative_reply;
    le_set_data_length_evt le_set_data_length;
    le_read_suggested_default_data_length_evt le_read_suggested_default_data_length;
    le_read_resolving_list_size_evt le_read_resolving_list_size;
    le_read_peer_resolvable_address_evt le_read_peer_resolvable_address;
    le_read_local_resolvable_address_evt le_read_local_resolvable_address;
    le_read_maximum_data_length_evt le_read_maximum_data_length;
    common_cmplt_evt common_cmplt;
    uint8_t bytes[24];
} cmd_return_parameters;

typedef struct
{
    uint8_t reserved;//for 32 bit align
    uint8_t numHciCmdPck;
    uint8_t cmdOpcodelo8;
    uint8_t cmdOpcodehi8;
    cmd_return_parameters return_parameters;
}  cmd_cmplt_evt;


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
/* HCI Task Stack Size */
#define HCI_CMD_TASK_STACK_SIZE            ( 800 )
#define HCI_EVENT_TASK_STACK_SIZE          ( 800 )

/* HCI Data Buffer Size */
#define HCI_CMD_BUF_SIZE                   ( 1024 )
#define HCI_EVENT_BUF_SIZE                 ( 256 )
#define CHECK_HCI_CMD_INDEX(i)             ( ((i) >= HCI_CMD_BUF_SIZE) ? (i-HCI_CMD_BUF_SIZE) : (i) )


//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum
{
    HCI_TYPE_COMMAND = 0x01,
    HCI_TYPE_ACLDATA = 0x02,
    HCI_TYPE_EVENT   = 0x04
    
} enHciType_t;

typedef enum 
{
    HCI_STATE_TYPE = 0,
    HCI_STATE_CMD_OPCODE_LO,
    HCI_STATE_CMD_OPCODE_HI,
    HCI_STATE_CMD_LENGTH,
    HCI_STATE_DATA_START,
    HCI_STATE_DATA_CONT
    
} enHciState_t;


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    uint16_t u16Rx;
    uint16_t u16Tx;
    uint8_t  *pu8Buf;
    
} stHciBuf_t;

typedef struct
{
    uint8_t  u8Type;
    uint16_t u16OpCode;
    uint8_t  u8Len;
    
} stHciCmdHeader_t;


/*
 * Command Complete Event, Event Code: 0x0E.
 */
// LE Test End Command Return Parameters
typedef struct
{
    uint8_t u8Status;
    uint8_t u8NumPktsRxLo; // Number of packets received low 8bit
    uint8_t u8NumPktsRxHi; // Number of packets received high 8bit

} stLeTestEndEvt_t;

typedef union
{
    uint8_t u8Status;
    stLeTestEndEvt_t stLeTestEnd;
    uint8_t u8Para[4];

} unCmdCmpltEvtPara_t;

/*
 * Command Complete Event, Event Code: 0x0E.
 * The Command Complete event is used by the Controller for most commands
 * to transmit return status of a command and the other event parameters that are
 * specified for the issued HCI command.
 */
typedef struct
{
    uint8_t u8OpcodeLo;    // Opcode(Low 8bit) of the command which caused this event.
    uint8_t u8OpcodeHi;    // Opcode(High 8bit) of the command which caused this event.
    unCmdCmpltEvtPara_t unPar;

} stCmdCmpltEvt_t;

/*
 * Command Status Event, Event Code: 0x0F.
 * The Command Status event is used to indicate that the command described by 
 * the Command_Opcode parameter has been received, and that the Controller
 * is currently performing the task for this command.
 */
typedef struct
{
    uint8_t  u8Status;      //
    uint8_t  u8NumCmdPckts; // The Number of HCI command packets which are allowed to be sent to the 
                            // Controller from the Host.
    uint16_t u16Opcode;     // Opcode of the command which caused this event and is pendingcompletion.
    uint8_t  u8Para[4];

} stCmdStatusEvt_t;


typedef union
{
    stCmdCmpltEvt_t stCmpltEvt;
    stCmdStatusEvt_t stCmdSta;
    uint8_t u8Data[24];

} unEvtParameters_t;

typedef struct
{
    uint8_t u8Type;
    uint8_t u8EvtCode;
    uint8_t u8Len;
    uint8_t u8SubCode;
    unEvtParameters_t unPar;

} stEvent_t;


#endif /* __HCI_STRUCT_H__ */


