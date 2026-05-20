/*************************************************************************************************************
 * @file    llc_spec_5_1.h
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
#ifndef LLC_SPEC_5_1_H
#define LLC_SPEC_5_1_H


typedef enum
{
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_ADV_IND         = 0,
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_DIRECT_IND      = 1,
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_NONCONN_IND     = 2,
    
    ////same value
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_SCAN_REQ        = 3,
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_AUX_SCAN_REQ    = 3,
    ////
    
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_SCAN_RSP        = 4,
    
    ////same value
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_CONNECT_IND     = 5,
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_AUX_CONNECT_REQ = 5,
    ////
    
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_ADV_SCAN_IND    = 6,
    
    ////same value
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_ADV_EXT_IND     = 7,
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_AUX_ADV_IND     = 7,
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_AUX_SCAN_RSP    = 7,
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_AUX_SYNC_IND    = 7,
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_AUX_CHAIN_IND   = 7,
    ////
    
    LLC_SPEC_5_1_ADV_CH_PDU_TYPE_AUX_CONNECT_RSP = 8,
}
EN_LLC_SPEC_5_1_ADV_CH_PDU_TYPE_T;

typedef struct
{
    uint8_t PDUType : 4;
    uint8_t RFU     : 1;
    uint8_t ChSel   : 1;
    uint8_t TxAdd   : 1;
    uint8_t RxAdd   : 1;
    uint8_t Length  : 8;
} __attribute__((packed))
stLlcSpec51AdvChannelPduHeaderBitField_t;


typedef union
{
    uint16_t u16Value;
    stLlcSpec51AdvChannelPduHeaderBitField_t bitField;
}
stLlcSpec51AdvChannelPduHeader_t;


#define LLC_SPEC_5_1_CONNECT_IND_PAYLOAD_SIZE   (34)
typedef struct
{
    uint8_t InitA[6];
    uint8_t AdvA[6];
    uint32_t AA;
    uint32_t CRCInit    :24;
    uint8_t WinSize;
    uint16_t WinOffset;
    uint16_t Interval;
    uint16_t Latency;
    uint16_t TimeOut;
    uint8_t ChM[5];
    uint8_t Hop         :5;
    uint8_t SCA         :3;
} __attribute__((packed))
stLlcSpec51ConnectIndBitField_t;
typedef union
{
    uint8_t pu8Buf[LLC_SPEC_5_1_CONNECT_IND_PAYLOAD_SIZE];
    stLlcSpec51ConnectIndBitField_t bitField;
}
stLlcSpec51ConnectInd_t;



#define LLC_SPEC_5_1_SCAN_REQ_PAYLOAD_SIZE  (12)
typedef struct
{
    uint8_t ScanA[6];
    uint8_t AdvA[6];
} __attribute__((packed))
stLlcSpec51ScanReqBitField_t;
typedef union
{
    stLlcSpec51ScanReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_SCAN_REQ_PAYLOAD_SIZE];
}
stLlcSpec51ScanReq_t;


#define LLC_SPEC_5_1_AUX_SCAN_REQ_PAYLOAD_SIZE  (12)
typedef struct
{
    uint8_t ScanA[6];
    uint8_t AdvA[6];
} __attribute__((packed))
stLlcSpec51AuxScanReqBitField_t;
typedef union
{
    stLlcSpec51AuxScanReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_AUX_SCAN_REQ_PAYLOAD_SIZE];
}
stLlcSpec51AuxScanReq_t;


#define LLC_SPEC_5_1_AUX_CONNECT_REQ_PAYLOAD_SIZE   (34)
typedef struct
{
    uint8_t InitA[6];
    uint8_t AdvA[6];
    uint32_t AA;
    uint32_t CRCInit    :24;
    uint8_t WinSize;
    uint16_t WinOffset;
    uint16_t Interval;
    uint16_t Latency;
    uint16_t TimeOut;
    uint8_t ChM[5];
    uint8_t Hop         :5;
    uint8_t SCA         :3;
} __attribute__((packed))
stLlcSpec51AuxConnectReqBitField_t;
typedef union
{
    stLlcSpec51AuxConnectReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_AUX_CONNECT_REQ_PAYLOAD_SIZE];
}
stLlcSpec51AuxConnectReq_t;


#define LLC_SPEC_5_1_AUX_CONNECT_RSP_PAYLOAD_SIZE   (13)//1 + 6 + 6

#define LLC_SPEC_5_1_EXTENDED_ADV_MAX_ADVERTISING_DATA_LENGTH (1650)

#define LLC_SPEC_5_1_ADV_CHANNEL_PDU_MAX_PAYLOAD_SIZE (255)


#define LLC_SPEC_5_1_ADV_CHANNEL_ACCESS_ADDRESS (0x8E89BED6)
#define LLC_SPEC_5_1_ADV_CHANNEL_CRC_INIT (0x555555)
#define LLC_SPEC_5_1_CONNECT_IND_TRANSMIT_WINDOW_DELAY_US    (1250)
#define LLC_SPEC_5_1_UNCODED_AUX_CONNECT_REQ_TRANSMIT_WINDOW_DELAY_US    (2500)
#define LLC_SPEC_5_1_CODED_AUX_CONNECT_REQ_TRANSMIT_WINDOW_DELAY_US    (3750)
#define LLC_SPEC_5_1_T_MAFS_US   (300)



typedef struct
{
    uint32_t LLID       : 2;
    uint32_t NESN       : 1;
    uint32_t SN         : 1;
    uint32_t MD         : 1;
    uint32_t CP         : 1;
    uint32_t rfu0       : 2;
    uint32_t Length     : 8;
    uint32_t CTETime    : 5;
    uint32_t rfu1       : 1;
    uint32_t CTEType    : 2;
    uint32_t rfu2       : 8;//do NOT omit
} __attribute__((packed))
stLlcSpec51DataChannelPduHeaderBitField_t;


typedef union
{
    uint32_t u32Value;
    stLlcSpec51DataChannelPduHeaderBitField_t bitField;
}
stLlcSpec51DataChannelPduHeader_t;

#define LLC_SPEC_5_1_DATA_CHANNEL_HEADER_SIZE_MIN    (2)
#define LLC_SPEC_5_1_DATA_CHANNEL_HEADER_SIZE_MAX    (3)


////"DLE" : Data Length Extension
#define LLC_SPEC_5_1_CONN_TRX_MIN_OCTETS                    (27)
#define LLC_SPEC_5_1_CONN_TRX_MAX_OCTETS_NO_DLE             (27)
#define LLC_SPEC_5_1_CONN_TRX_MAX_OCTETS_DLE                (251)
#define LLC_SPEC_5_1_CONN_TRX_MIN_TIME_US                   (328)
#define LLC_SPEC_5_1_CONN_TRX_MAX_TIME_US_UNCODED_NO_DLE    (328)
#define LLC_SPEC_5_1_CONN_TRX_MAX_TIME_US_UNCODED_DLE       (2120)
#define LLC_SPEC_5_1_CONN_TRX_MAX_TIME_US_CODED_NO_DLE      (2704)
#define LLC_SPEC_5_1_CONN_TRX_MAX_TIME_US_CODED_DLE         (17040)


typedef enum
{
    LLC_SPEC_5_1_LLID_DATA_CONTINUATION_OR_EMPTY    = 1,
    LLC_SPEC_5_1_LLID_DATA_START_OR_COMPLETE        = 2,
    LLC_SPEC_5_1_LLID_CTRL                          = 3,
}
EN_LLC_SPEC_5_1_LLID_T;


#define LLC_SPEC_5_1_MIC_SIZE    (4)
#define LLC_SPEC_5_1_T_IFS_US   (150)
#define LLC_SPEC_5_1_ADV_CHANNEL_ACCESS_ADDRESS (0x8E89BED6)
#define LLC_SPEC_5_1_ADV_CHANNEL_CRC_INIT (0x555555)

typedef enum
{
    ////todo : impl
    
    
    LLC_SPEC_5_1_ERROR_CODE_SUCCESS                                                     = 0x00,
    LLC_SPEC_5_1_ERROR_CODE_UNKNOWN_HCI_COMMAND                                         = 0x01,
    LLC_SPEC_5_1_ERROR_CODE_UNKNOWN_CONNECTION_IDENTIFIER                               = 0x02,
    LLC_SPEC_5_1_ERROR_CODE_HARDWARE_FAILURE                                            = 0x03,
    
    LLC_SPEC_5_1_ERROR_CODE_AUTHENTICATION_FAILURE                                      = 0x05,
    LLC_SPEC_5_1_ERROR_CODE_PIN_OR_KEY_MISSING                                          = 0x06,
    LLC_SPEC_5_1_ERROR_CODE_MEMORY_CAPACITY_EXCEEDED                                    = 0x07,
    LLC_SPEC_5_1_ERROR_CODE_CONNECTION_TIMEOUT                                          = 0x08,
    
    LLC_SPEC_5_1_ERROR_CODE_CONNECTION_ALREADY_EXISTS                                   = 0x0B,
    LLC_SPEC_5_1_ERROR_CODE_COMMAND_DISALLOWED                                          = 0x0C,
    
    LLC_SPEC_5_1_ERROR_CODE_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE                      = 0x11,
    LLC_SPEC_5_1_ERROR_CODE_INVALID_HCI_COMMAND_PARAMETERS                              = 0x12,
    LLC_SPEC_5_1_ERROR_CODE_REMOTE_USER_TERMINATED_CONNECTION                           = 0x13,
    LLC_SPEC_5_1_ERROR_CODE_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES    = 0x14,
    LLC_SPEC_5_1_ERROR_CODE_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_POWER_OFF        = 0x15,
    LLC_SPEC_5_1_ERROR_CODE_CONNECTION_TERMINATED_BY_LOCAL_HOST                         = 0x16,
    
    ////same code
    LLC_SPEC_5_1_ERROR_CODE_UNSUPPORTED_REMOTE_FEATURE                                  = 0x1A,
    LLC_SPEC_5_1_ERROR_CODE_UNSUPPORTED_LMP_FEATURE                                     = 0x1A,
    ////
    
    LLC_SPEC_5_1_ERROR_CODE_INVALID_LL_PARAMETERS                                       = 0x1E,
    
    ////same code
    LLC_SPEC_5_1_ERROR_CODE_LMP_RESPONSE_TIMEOUT                                        = 0x22,
    LLC_SPEC_5_1_ERROR_CODE_LL_RESPONSE_TIMEOUT                                         = 0x22,
    ////
    ////same code
    LLC_SPEC_5_1_ERROR_CODE_LMP_ERROR_TRANSACTION_COLLISION                             = 0x23,
    LLC_SPEC_5_1_ERROR_CODE_LL_PROCEDURE_COLLISION                                      = 0x23,
    ////
    
    LLC_SPEC_5_1_ERROR_CODE_INSTANT_PASSED                                              = 0x28,
    LLC_SPEC_5_1_ERROR_CODE_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED                         = 0x29,
    LLC_SPEC_5_1_ERROR_CODE_DIFFERENT_TRANSACTION_COLLISION                             = 0x2A,
    
    LLC_SPEC_5_1_ERROR_CODE_CONTROLLER_BUSY                                             = 0x3A,
    LLC_SPEC_5_1_ERROR_CODE_UNACCEPTABLE_CONNECTION_PARAMETERS                          = 0x3B,
    LLC_SPEC_5_1_ERROR_CODE_ADVERTISING_TIMEOUT                                         = 0x3C,
    LLC_SPEC_5_1_ERROR_CODE_CONNECTION_TERMINATED_DUE_TO_MIC_FAILURE                    = 0x3D,
    ////same code
    LLC_SPEC_5_1_ERROR_CODE_CONNECTION_FAILED_TO_BE_ESTABLISHED                         = 0x3E,
    LLC_SPEC_5_1_ERROR_CODE_SYNCHRONIZATION_TIMEOUT                                     = 0x3E,
    ////
    
    LLC_SPEC_5_1_ERROR_CODE_UNKNOWN_ADVERTISING_IDENTIFIER                              = 0x42,
    LLC_SPEC_5_1_ERROR_CODE_LIMIT_REACHED                                               = 0x43,
    
    LLC_SPEC_5_1_ERROR_CODE_PACKET_TOO_LONG                                             = 0x45,
}
EN_LLC_SPEC_5_1_ERROR_CODE_T;



typedef enum
{
    LLC_SPEC_5_1_FEATURE_SET_LE_ENCRYPTION                                  = (1ULL << 0),
    LLC_SPEC_5_1_FEATURE_SET_CONNECTION_PARAMETERS_REQUEST_PROCEDURE        = (1ULL << 1),
    LLC_SPEC_5_1_FEATURE_SET_EXTENDED_REJECT_INDICATION                     = (1ULL << 2),
    LLC_SPEC_5_1_FEATURE_SET_SLAVE_INITIATED_FEATURES_EXCHANGE              = (1ULL << 3),
    LLC_SPEC_5_1_FEATURE_SET_LE_PING                                        = (1ULL << 4),
    LLC_SPEC_5_1_FEATURE_SET_LE_DATA_PACKET_LENGTH_EXTENSION                = (1ULL << 5),
    LLC_SPEC_5_1_FEATURE_SET_LL_PRIVACY                                     = (1ULL << 6),
    LLC_SPEC_5_1_FEATURE_SET_EXTENDED_SCANNER_FILTER_POLICIES               = (1ULL << 7),
    LLC_SPEC_5_1_FEATURE_SET_LE_2M_PHY                                      = (1ULL << 8),
    LLC_SPEC_5_1_FEATURE_SET_STABLE_MODULATION_INDEX_TRANSMITTER            = (1ULL << 9),
    LLC_SPEC_5_1_FEATURE_SET_STABLE_MODULATION_INDEX_RECEIVER               = (1ULL << 10),
    LLC_SPEC_5_1_FEATURE_SET_LE_CODED_PHY                                   = (1ULL << 11),
    LLC_SPEC_5_1_FEATURE_SET_LE_EXTENDED_ADVERTISING                        = (1ULL << 12),
    LLC_SPEC_5_1_FEATURE_SET_LE_PERIODIC_ADVERTISING                        = (1ULL << 13),
    LLC_SPEC_5_1_FEATURE_SET_CHANNEL_SELECTION_ALGORITHM_NO2                = (1ULL << 14),
    LLC_SPEC_5_1_FEATURE_SET_LE_POWER_CLASS_1                               = (1ULL << 15),
    LLC_SPEC_5_1_FEATURE_SET_MINIMUM_NUMBER_OF_USED_CHANNELS_PROCEDURE      = (1ULL << 16),
    LLC_SPEC_5_1_FEATURE_SET_CONNECTION_CTE_REQUEST                         = (1ULL << 17),
    LLC_SPEC_5_1_FEATURE_SET_CONNECTION_CTE_RESPONSE                        = (1ULL << 18),
    LLC_SPEC_5_1_FEATURE_SET_CONNECTIONLESS_CTE_TRANSMITTER                 = (1ULL << 19),
    LLC_SPEC_5_1_FEATURE_SET_CONNECTIONLESS_CTE_RECEIVER                    = (1ULL << 20),
    LLC_SPEC_5_1_FEATURE_SET_AOD                                            = (1ULL << 21),
    LLC_SPEC_5_1_FEATURE_SET_AOA                                            = (1ULL << 22),
    LLC_SPEC_5_1_FEATURE_SET_RECEIVING_CONSTANT_TONE_EXTENSIONS             = (1ULL << 23),
    LLC_SPEC_5_1_FEATURE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_SENDER      = (1ULL << 24),
    LLC_SPEC_5_1_FEATURE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECIPIENT   = (1ULL << 25),
    LLC_SPEC_5_1_FEATURE_SET_SLEEP_CLOCK_ACCURACY_UPDATES                   = (1ULL << 26),
    LLC_SPEC_5_1_FEATURE_SET_REMOTE_PUBLIC_KEY_VALIDATION                   = (1ULL << 27),
}
EN_LLC_SPEC_5_1_FEATURE_SET_T;


#define LLC_SPEC_5_1_FEATURE_SET_VALID_FROM_PEER_BITMASK    ( LLC_SPEC_5_1_FEATURE_SET_LE_ENCRYPTION \
                                                            | LLC_SPEC_5_1_FEATURE_SET_CONNECTION_PARAMETERS_REQUEST_PROCEDURE \
                                                            | LLC_SPEC_5_1_FEATURE_SET_EXTENDED_REJECT_INDICATION \
                                                            | LLC_SPEC_5_1_FEATURE_SET_SLAVE_INITIATED_FEATURES_EXCHANGE \
                                                            | LLC_SPEC_5_1_FEATURE_SET_LE_DATA_PACKET_LENGTH_EXTENSION \
                                                            | LLC_SPEC_5_1_FEATURE_SET_LE_2M_PHY \
                                                            | LLC_SPEC_5_1_FEATURE_SET_STABLE_MODULATION_INDEX_TRANSMITTER \
                                                            | LLC_SPEC_5_1_FEATURE_SET_STABLE_MODULATION_INDEX_RECEIVER \
                                                            | LLC_SPEC_5_1_FEATURE_SET_LE_CODED_PHY \
                                                            | LLC_SPEC_5_1_FEATURE_SET_CHANNEL_SELECTION_ALGORITHM_NO2 \
                                                            | LLC_SPEC_5_1_FEATURE_SET_LE_POWER_CLASS_1 \
                                                            | LLC_SPEC_5_1_FEATURE_SET_MINIMUM_NUMBER_OF_USED_CHANNELS_PROCEDURE \
                                                            | LLC_SPEC_5_1_FEATURE_SET_CONNECTION_CTE_REQUEST \
                                                            | LLC_SPEC_5_1_FEATURE_SET_CONNECTION_CTE_RESPONSE \
                                                            | LLC_SPEC_5_1_FEATURE_SET_RECEIVING_CONSTANT_TONE_EXTENSIONS \
                                                            | LLC_SPEC_5_1_FEATURE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_SENDER \
                                                            | LLC_SPEC_5_1_FEATURE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECIPIENT \
                                                            | LLC_SPEC_5_1_FEATURE_SET_SLEEP_CLOCK_ACCURACY_UPDATES )

#define LLC_SPEC_5_1_FEATURE_SET_MASKED_TO_PEER_BITMASK     (LLC_SPEC_5_1_FEATURE_SET_REMOTE_PUBLIC_KEY_VALIDATION)




////BLUETOOTH CORE SPECIFICATION Version 5.1 | Vol 6, Part B
////Core_v5.1, Page 2720
typedef enum
{
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_CONNECTION_UPDATE_IND   = 0x00,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_CHANNEL_MAP_IND         = 0x01,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_TERMINATE_IND           = 0x02,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_ENC_REQ                 = 0x03,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_ENC_RSP                 = 0x04,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_START_ENC_REQ           = 0x05,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_START_ENC_RSP           = 0x06,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_UNKNOWN_RSP             = 0x07,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_FEATURE_REQ             = 0x08,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_FEATURE_RSP             = 0x09,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_PAUSE_ENC_REQ           = 0x0A,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_PAUSE_ENC_RSP           = 0x0B,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_VERSION_IND             = 0x0C,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_REJECT_IND              = 0x0D,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_SLAVE_FEATURE_REQ       = 0x0E,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_CONNECTION_PARAM_REQ    = 0x0F,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_CONNECTION_PARAM_RSP    = 0x10,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_REJECT_EXT_IND          = 0x11,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_PING_REQ                = 0x12,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_PING_RSP                = 0x13,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_LENGTH_REQ              = 0x14,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_LENGTH_RSP              = 0x15,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_PHY_REQ                 = 0x16,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_PHY_RSP                 = 0x17,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_PHY_UPDATE_IND          = 0x18,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_MIN_USED_CHANNELS_IND   = 0x19,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_CTE_REQ                 = 0x1A,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_CTE_RSP                 = 0x1B,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_PERIODIC_SYNC_IND       = 0x1C,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_CLOCK_ACCURACY_REQ      = 0x1D,
    LLC_SPEC_5_1_CTRL_PDU_OPCODE_LL_CLOCK_ACCURACY_RSP      = 0x1E,
}
EN_LLC_SPEC_5_1_CTRL_PDU_OPCODE_T;


#define LLC_SPEC_5_1_CTRL_PROCEDURE_TIMEOUT_US  (40000000)//40s

#define LLC_SPEC_5_1_CTRL_PDU_PAYLOAD_MAX_SIZE  (35)
#define LLC_SPEC_5_1_CTRL_PDU_PAYLOAD_MIN_SIZE  (1)


#define LLC_SPEC_5_1_LL_TERMINATE_IND_PAYLOAD_SIZE  (2)
typedef struct
{
    uint8_t Opcode;
    uint8_t ErrorCode;
} __attribute__((packed))
stLlcSpec51LlTerminateIndBitField_t;
typedef union
{
    stLlcSpec51LlTerminateIndBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_TERMINATE_IND_PAYLOAD_SIZE];
}
stLlcSpec51LlTerminateInd_t;


#define LLC_SPEC_5_1_LL_UNKNOWN_RSP_PAYLOAD_SIZE  (2)
typedef struct
{
    uint8_t Opcode;
    uint8_t UnknownType;
} __attribute__((packed))
stLlcSpec51LlUnknownRspBitField_t;
typedef union
{
    stLlcSpec51LlUnknownRspBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_UNKNOWN_RSP_PAYLOAD_SIZE];
}
stLlcSpec51LlUnknownRsp_t;


#define LLC_SPEC_5_1_LL_REJECT_IND_PAYLOAD_SIZE  (2)
typedef struct
{
    uint8_t Opcode;
    uint8_t ErrorCode;
} __attribute__((packed))
stLlcSpec51LlRejectIndBitField_t;
typedef union
{
    stLlcSpec51LlRejectIndBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_REJECT_IND_PAYLOAD_SIZE];
}
stLlcSpec51LlRejectInd_t;

#define LLC_SPEC_5_1_LL_REJECT_EXT_IND_PAYLOAD_SIZE  (3)
typedef struct
{
    uint8_t Opcode;
    uint8_t RejectOpcode;
    uint8_t ErrorCode;
} __attribute__((packed))
stLlcSpec51LlRejectExtIndBitField_t;
typedef union
{
    stLlcSpec51LlRejectExtIndBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_REJECT_EXT_IND_PAYLOAD_SIZE];
}
stLlcSpec51LlRejectExtInd_t;

#define LLC_SPEC_5_1_LL_FEATURE_REQ_PAYLOAD_SIZE  (9)
typedef struct
{
    uint8_t Opcode;
    uint8_t FeatureSet[8];
} __attribute__((packed))
stLlcSpec51LlFeatureReqBitField_t;
typedef union
{
    stLlcSpec51LlFeatureReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_FEATURE_REQ_PAYLOAD_SIZE];
}
stLlcSpec51LlFeatureReq_t;


#define LLC_SPEC_5_1_LL_FEATURE_RSP_PAYLOAD_SIZE  (9)
typedef struct
{
    uint8_t Opcode;
    uint8_t FeatureSet[8];
} __attribute__((packed))
stLlcSpec51LlFeatureRspBitField_t;
typedef union
{
    stLlcSpec51LlFeatureRspBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_FEATURE_RSP_PAYLOAD_SIZE];
}
stLlcSpec51LlFeatureRsp_t;


#define LLC_SPEC_5_1_LL_SLAVE_FEATURE_REQ_PAYLOAD_SIZE  (9)
typedef struct
{
    uint8_t Opcode;
    uint8_t FeatureSet[8];
} __attribute__((packed))
stLlcSpec51LlSlaveFeatureReqBitField_t;
typedef union
{
    stLlcSpec51LlSlaveFeatureReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_SLAVE_FEATURE_REQ_PAYLOAD_SIZE];
}
stLlcSpec51LlSlaveFeatureReq_t;


#define LLC_SPEC_5_1_LL_VERSION_IND_PAYLOAD_SIZE  (6)
typedef struct
{
    uint8_t Opcode;
    uint8_t VersNr;
    uint16_t CompId;
    uint16_t SubVersNr;
} __attribute__((packed))
stLlcSpec51LlVersionIndBitField_t;
typedef union
{
    stLlcSpec51LlVersionIndBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_VERSION_IND_PAYLOAD_SIZE];
}
stLlcSpec51LlVersionInd_t;

#define LLC_SPEC_5_1_LL_CONNECTION_UPDATE_IND_PAYLOAD_SIZE  (12)
typedef struct
{
    uint8_t Opcode;
    uint8_t WinSize;
    uint16_t WinOffset;
    uint16_t Interval;
    uint16_t Latency;
    uint16_t Timeout;
    uint16_t Instant;
} __attribute__((packed))
stLlcSpec51LlConnectionUpdateIndBitField_t;
typedef union
{
    stLlcSpec51LlConnectionUpdateIndBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_CONNECTION_UPDATE_IND_PAYLOAD_SIZE];
}
stLlcSpec51LlConnectionUpdateInd_t;


#define LLC_SPEC_5_1_LL_CHANNEL_MAP_IND_PAYLOAD_SIZE  (8)
typedef struct
{
    uint8_t Opcode;
    uint8_t pu8ChM[5];
    uint16_t Instant;
} __attribute__((packed))
stLlcSpec51LlChannelMapIndBitField_t;
typedef union
{
    stLlcSpec51LlChannelMapIndBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_CHANNEL_MAP_IND_PAYLOAD_SIZE];
}
stLlcSpec51LlChannelMapInd_t;

#define LLC_SPEC_5_1_LL_ENC_REQ_PAYLOAD_SIZE  (23)
typedef struct
{
    uint8_t Opcode;
    uint8_t Rand[8];
    uint8_t EDIV[2];
    uint8_t SKDm[8];
    uint8_t IVm[4];
} __attribute__((packed))
stLlcSpec51LlEncReqBitField_t;
typedef union
{
    stLlcSpec51LlEncReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_ENC_REQ_PAYLOAD_SIZE];
}
stLlcSpec51LlEncReq_t;

#define LLC_SPEC_5_1_LL_ENC_RSP_PAYLOAD_SIZE  (13)
typedef struct
{
    uint8_t Opcode;
    uint8_t SKDs[8];
    uint8_t IVs[4];
} __attribute__((packed))
stLlcSpec51LlEncRspBitField_t;
typedef union
{
    stLlcSpec51LlEncRspBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_ENC_RSP_PAYLOAD_SIZE];
}
stLlcSpec51LlEncRsp_t;



#define LLC_SPEC_5_1_LL_START_ENC_REQ_PAYLOAD_SIZE  (1)
typedef struct
{
    uint8_t Opcode;
} __attribute__((packed))
stLlcSpec51LlStartEncReqBitField_t;
typedef union
{
    stLlcSpec51LlStartEncReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_START_ENC_REQ_PAYLOAD_SIZE];
}
stLlcSpec51LlStartEncReq_t;

#define LLC_SPEC_5_1_LL_START_ENC_RSP_PAYLOAD_SIZE  (1)
typedef struct
{
    uint8_t Opcode;
} __attribute__((packed))
stLlcSpec51LlStartEncRspBitField_t;
typedef union
{
    stLlcSpec51LlStartEncRspBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_START_ENC_RSP_PAYLOAD_SIZE];
}
stLlcSpec51LlStartEncRsp_t;


#define LLC_SPEC_5_1_LL_PAUSE_ENC_REQ_PAYLOAD_SIZE  (1)
typedef struct
{
    uint8_t Opcode;
} __attribute__((packed))
stLlcSpec51LlPauseEncReqBitField_t;
typedef union
{
    stLlcSpec51LlPauseEncReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_PAUSE_ENC_REQ_PAYLOAD_SIZE];
}
stLlcSpec51LlPauseEncReq_t;

#define LLC_SPEC_5_1_LL_PAUSE_ENC_RSP_PAYLOAD_SIZE  (1)
typedef struct
{
    uint8_t Opcode;
} __attribute__((packed))
stLlcSpec51LlPauseEncRspBitField_t;
typedef union
{
    stLlcSpec51LlPauseEncRspBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_PAUSE_ENC_RSP_PAYLOAD_SIZE];
}
stLlcSpec51LlPauseEncRsp_t;

#define LLC_SPEC_5_1_LL_LENGTH_REQ_PAYLOAD_SIZE  (9)
typedef struct
{
    uint8_t Opcode;
    uint16_t MaxRxOctets;
    uint16_t MaxRxTime;
    uint16_t MaxTxOctets;
    uint16_t MaxTxTime;
} __attribute__((packed))
stLlcSpec51LlLengthReqBitField_t;
typedef union
{
    stLlcSpec51LlLengthReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_LENGTH_REQ_PAYLOAD_SIZE];
}
stLlcSpec51LlLengthReq_t;

#define LLC_SPEC_5_1_LL_LENGTH_RSP_PAYLOAD_SIZE  (9)
typedef struct
{
    uint8_t Opcode;
    uint16_t MaxRxOctets;
    uint16_t MaxRxTime;
    uint16_t MaxTxOctets;
    uint16_t MaxTxTime;
} __attribute__((packed))
stLlcSpec51LlLengthRspBitField_t;
typedef union
{
    stLlcSpec51LlLengthRspBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_LENGTH_RSP_PAYLOAD_SIZE];
}
stLlcSpec51LlLengthRsp_t;


#define LLC_SPEC_5_1_LL_PHY_REQ_PAYLOAD_SIZE  (3)
typedef struct
{
    uint8_t Opcode;
    uint8_t TX_PHYS;
    uint8_t RX_PHYS;
} __attribute__((packed))
stLlcSpec51LlPhyReqBitField_t;
typedef union
{
    stLlcSpec51LlPhyReqBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_PHY_REQ_PAYLOAD_SIZE];
}
stLlcSpec51LlPhyReq_t;

#define LLC_SPEC_5_1_LL_PHY_RSP_PAYLOAD_SIZE  (3)
typedef struct
{
    uint8_t Opcode;
    uint8_t TX_PHYS;
    uint8_t RX_PHYS;
} __attribute__((packed))
stLlcSpec51LlPhyRspBitField_t;
typedef union
{
    stLlcSpec51LlPhyRspBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_PHY_RSP_PAYLOAD_SIZE];
}
stLlcSpec51LlPhyRsp_t;

#define LLC_SPEC_5_1_LL_PHY_UPDATE_IND_PAYLOAD_SIZE  (5)
typedef struct
{
    uint8_t Opcode;
    uint8_t M_TO_S_PHY;
    uint8_t S_TO_M_PHY;
    uint16_t Instant;
} __attribute__((packed))
stLlcSpec51LlPhyUpdateIndBitField_t;
typedef union
{
    stLlcSpec51LlPhyUpdateIndBitField_t bitField;
    uint8_t pu8Payload[LLC_SPEC_5_1_LL_PHY_UPDATE_IND_PAYLOAD_SIZE];
}
stLlcSpec51LlPhyUpdateInd_t;





typedef enum
{
    ////0x00 to 0x3F
    
    LLC_SPEC_5_1_HCI_OGF_LINK_CONTROL_COMMANDS              = 0x01,
    LLC_SPEC_5_1_HCI_OGF_LINK_POLICY_COMMANDS               = 0x02,
    LLC_SPEC_5_1_HCI_OGF_CONTROLLER_AND_BASEBAND_COMMANDS   = 0x03,
    LLC_SPEC_5_1_HCI_OGF_INFORMATIONAL_PARAMETERS           = 0x04,
    LLC_SPEC_5_1_HCI_OGF_STATUS_PARAMETERS                  = 0x05,
    LLC_SPEC_5_1_HCI_OGF_TESTING_COMMANDS                   = 0x06,
    LLC_SPEC_5_1_HCI_OGF_LE_CONTROLLER_COMMANDS             = 0x08,
    LLC_SPEC_5_1_HCI_OGF_VENDOR_COMMANDS                    = 0x3F,
}
EN_LLC_SPEC_5_1_HCI_OGF_T;


typedef enum
{
    ////0x0000 to 0x03FF
    
    ////same OCF
    LLC_SPEC_5_1_HCI_OCF_HCI_Set_Event_Mask                                 = 0x0001,
    LLC_SPEC_5_1_HCI_OCF_HCI_Read_Local_Version_Information                 = 0x0001,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Event_Mask                              = 0x0001,
    ////
    
    ////same OCF
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Buffer_Size                            = 0x0002,
    LLC_SPEC_5_1_HCI_OCF_HCI_Read_Local_Supported_Commands                  = 0x0002,
    ////
    
    ////same OCF
    LLC_SPEC_5_1_HCI_OCF_HCI_Reset                                          = 0x0003,
    LLC_SPEC_5_1_HCI_OCF_HCI_Read_Local_Supported_Features                  = 0x0003,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Local_Supported_Features               = 0x0003,
    ////
    
    ////same OCF
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Random_Address                          = 0x0005,
    LLC_SPEC_5_1_HCI_OCF_HCI_Read_RSSI                                      = 0x0005,
    ////
    
    ////same OCF
    LLC_SPEC_5_1_HCI_OCF_HCI_Disconnect                                     = 0x0006,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Advertising_Parameters                  = 0x0006,
    ////
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Advertising_Physical_Channel_Tx_Power  = 0x0007,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Advertising_Data                        = 0x0008,
    
    ////same OCF
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Scan_Response_Data                      = 0x0009,
    LLC_SPEC_5_1_HCI_OCF_HCI_Read_BD_ADDR                                   = 0x0009,
    ////
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Advertising_Enable                      = 0x000A,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Scan_Parameters                         = 0x000B,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Scan_Enable                             = 0x000C,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Create_Connection                           = 0x000D,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Create_Connection_Cancel                    = 0x000E,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_White_List_Size                        = 0x000F,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Clear_White_List                            = 0x0010,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Add_Device_To_White_List                    = 0x0011,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Remove_Device_From_White_List               = 0x0012,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Connection_Update                           = 0x0013,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Host_Channel_Classification             = 0x0014,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Channel_Map                            = 0x0015,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Remote_Features                        = 0x0016,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Encrypt                                     = 0x0017,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Rand                                        = 0x0018,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Start_Encryption                            = 0x0019,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Long_Term_Key_Request_Reply                 = 0x001A,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Long_Term_Key_Request_Negative_Reply        = 0x001B,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Supported_States                       = 0x001C,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_Read_Remote_Version_Information                = 0x001D,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Data_Length                             = 0x0022,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Suggested_Default_Data_Length          = 0x0023,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Write_Suggested_Default_Data_Length         = 0x0024,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Add_Device_To_Resolving_List                = 0x0027,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Remove_Device_From_Resolving_List           = 0x0028,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Clear_Resolving_List                        = 0x0029,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Resolving_List_Size                    = 0x002A,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Address_Resolution_Enable               = 0x002D,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Resolvable_Private_Address_Timeout      = 0x002E,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Maximum_Data_Length                    = 0x002F,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_PHY                                    = 0x0030,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Default_PHY                             = 0x0031,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_PHY                                     = 0x0032,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Advertising_Set_Random_Address          = 0x0035,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Extended_Advertising_Parameters         = 0x0036,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Extended_Advertising_Data               = 0x0037,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Extended_Scan_Response_Data             = 0x0038,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Extended_Advertising_Enable             = 0x0039,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Maximum_Advertising_Data_Length        = 0x003A,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Number_of_Supported_Advertising_Sets   = 0x003B,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Remove_Advertising_Set                      = 0x003C,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Clear_Advertising_Sets                      = 0x003D,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Extended_Scan_Parameters                = 0x0041,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Extended_Scan_Enable                    = 0x0042,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Extended_Create_Connection                  = 0x0043,
    
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Read_Transmit_Power                         = 0x004B,
    LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Privacy_Mode                            = 0x004E,
    
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Set_Public_Address                          = 0x0301,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Set_Advertising_Parameters                  = 0x0302,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Set_Advertising_Data                        = 0x0303,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Set_Scan_Response_Data                      = 0x0304,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Set_Advertising_Enable                      = 0x0305,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Set_Scan_Parameters                         = 0x0306,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Create_Connection                           = 0x0307,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Update_Channel_Map                          = 0x0308,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Set_Extended_Advertising_Parameters         = 0x0309,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Set_Extended_Scan_Parameters                = 0x030A,//Vendor Commands
    LLC_SPEC_5_1_HCI_OCF_VENDOR_Extended_Create_Connection                  = 0x030B,//Vendor Commands
}
EN_LLC_SPEC_5_1_HCI_OCF_T; 

typedef enum
{
    LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Disconnection_Complete                      = 0x05,
    LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Encryption_Change                           = 0x08,
    LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Read_Remote_Version_Information_Complete    = 0x0C,
    LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Complete                            = 0x0E,
    LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Status                              = 0x0F,
    LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Hardware_Error                              = 0x10,
    LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Number_Of_Completed_Packets                 = 0x13,
    LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Encryption_Key_Refresh_Complete             = 0x30,
    
    LLC_SPEC_5_1_HCI_EVENT_CODE_LE_Meta_event                                   = 0x3E,
    
    LLC_SPEC_5_1_HCI_EVENT_CODE_VENDOR                                          = 0xFF,
}
EN_LLC_SPEC_5_1_HCI_EVENT_CODE_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Connection_Complete           = 0x01,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Advertising_Report            = 0x02,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Connection_Update_Complete    = 0x03,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Read_Remote_Features_Complete = 0x04,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Long_Term_Key_Request         = 0x05,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Data_Length_Change            = 0x07,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Enhanced_Connection_Complete  = 0x0A,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Directed_Advertising_Report   = 0x0B,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_PHY_Update_Complete           = 0x0C,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Extended_Advertising_Report   = 0x0D,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Scan_Timeout                  = 0x11,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Advertising_Set_Terminated    = 0x12,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Scan_Request_Received         = 0x13,
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_HCI_LE_Channel_Selection_Algorithm   = 0x14,
    
    
    
    LLC_SPEC_5_1_HCI_SUBEVENT_CODE_VENDOR_Connection_Complete           = 0xFF,//Vendor Commands
}
EN_LLC_SPEC_5_1_HCI_SUBEVENT_CODE_T;





#define LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(Octet, Bit)            ((((Octet)&0x3F)<<8)|((Bit) & 0x7))
#define LLC_SPEC_5_1_SUPPORTED_COMMANDS_GET_OCTET(enumSupportedCommand) (((enumSupportedCommand)>>8)&0x3F)
#define LLC_SPEC_5_1_SUPPORTED_COMMANDS_GET_BIT(enumSupportedCommand)   ((enumSupportedCommand)&0xF)
typedef enum
{
    //(Octet<<8)|(Bit)
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_Disconnect                                          = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(0,5),
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_Read_Remote_Version_Information                     = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(2,7),
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_Set_Event_Mask                                      = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(5,6),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_Reset                                               = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(5,7),
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_Read_Local_Version_Information                      = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(14,3),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_Read_Local_Supported_Features                       = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(14,5),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_Read_BD_ADDR                                        = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(15,1),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_Read_RSSI                                           = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(15,5),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Event_Mask                                   = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(25,0),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Buffer_Size                                 = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(25,1),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Local_Supported_Features                    = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(25,2),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Random_Address                               = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(25,4),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Advertising_Parameters                       = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(25,5),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Advertising_Physical_Channel_Tx_Power       = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(25,6),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Advertising_Data                             = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(25,7),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Scan_Response_Data                           = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(26,0),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Advertising_Enable                           = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(26,1),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Scan_Parameters                              = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(26,2),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Scan_Enable                                  = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(26,3),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Create_Connection                                = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(26,4),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Create_Connection_Cancel                         = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(26,5),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_White_List_Size                             = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(26,6),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Clear_White_List                                 = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(26,7),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Add_Device_To_White_List                         = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(27,0),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Remove_Device_From_White_List                    = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(27,1),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Connection_Update                                = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(27,2),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Host_Channel_Classification                  = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(27,3),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Channel_Map                                 = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(27,4),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Remote_Features                             = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(27,5),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Encrypt                                          = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(27,6),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Rand                                             = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(27,7),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Start_Encryption                                 = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(28,0),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Long_Term_Key_Request_Reply                      = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(28,1),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Long_Term_Key_Request_Negative_Reply             = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(28,2),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Supported_States                            = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(28,3),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Data_Length                                  = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(33,6),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Suggested_Default_Data_Length               = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(33,7),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Write_Suggested_Default_Data_Length              = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(34,0),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Add_Device_To_Resolving_List                     = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(34,3),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Remove_Device_From_Resolving_List                = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(34,4),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Clear_Resolving_List                             = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(34,5),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Resolving_List_Size                         = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(34,6),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Address_Resolution_Enable                    = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(35,1),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Resolvable_Private_Address_Timeout           = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(35,2),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Maximum_Data_Length                         = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(35,3),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_PHY                                         = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(35,4),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Default_PHY                                  = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(35,5),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_PHY                                          = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(35,6),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Advertising_Set_Random_Address               = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(36,1),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Extended_Advertising_Parameters              = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(36,2),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Extended_Advertising_Data                    = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(36,3),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Extended_Scan_Response_Data                  = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(36,4),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Extended_Advertising_Enable                  = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(36,5),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Maximum_Advertising_Data_Length             = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(36,6),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Number_of_Supported_Advertising_Sets        = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(36,7),
    
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Remove_Advertising_Set                           = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(37,0),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Clear_Advertising_Sets                           = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(37,1),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Extended_Scan_Parameters                     = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(37,5),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Extended_Scan_Enable                         = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(37,6),
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Extended_Create_Connection                       = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(37,7),
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Read_Transmit_Power                              = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(38,7),
    
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_HCI_LE_Set_Privacy_Mode                                 = LLC_SPEC_5_1_SUPPORTED_COMMANDS_GENERATE(39,2),
    
    
    //mandatory supported command, like HCI_Read_Local_Version_Information
    LLC_SPEC_5_1_SUPPORTED_COMMANDS_MANDATORY_SUPPORTED                                     = 0xFFFF,
}
EN_LLC_SPEC_5_1_SUPPORTED_COMMANDS_T;


typedef enum
{
    LLC_SPEC_5_1_EVNET_MASK_HCI_Disconnection_Complete                              = 1ULL << 4,
    
    LLC_SPEC_5_1_EVNET_MASK_HCI_Encryption_Change                                   = 1ULL << 7,
    
    LLC_SPEC_5_1_EVNET_MASK_HCI_Read_Remote_Version_Information_Complete            = 1ULL << 11,
    
    LLC_SPEC_5_1_EVNET_MASK_HCI_Encryption_Key_Refresh_Complete                     = 1ULL << 47,
    
    LLC_SPEC_5_1_EVNET_MASK_LE_Meta_event                                           = 1ULL << 61,
}
EN_LLC_SPEC_5_1_EVENT_MASK_T;


typedef enum
{
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Connection_Complete                           = 1ULL << 0,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Advertising_Report                            = 1ULL << 1,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Connection_Update_Complete                    = 1ULL << 2,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Read_Remote_Features_Complete                 = 1ULL << 3,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Long_Term_Key_Request                         = 1ULL << 4,
    
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Data_Length_Change                            = 1ULL << 6,
    
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Enhanced_Connection_Complete                  = 1ULL << 9,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Directed_Advertising_Report                   = 1ULL << 10,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_PHY_Update_Complete                           = 1ULL << 11,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Extended_Advertising_Report                   = 1ULL << 12,
    
    
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Scan_Timeout                                  = 1ULL << 16,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Advertising_Set_Terminated                    = 1ULL << 17,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Scan_Request_Received                         = 1ULL << 18,
    LLC_SPEC_5_1_LE_EVNET_MASK_HCI_LE_Channel_Selection_Algorithm                   = 1ULL << 19,
    
    
    LLC_SPEC_5_1_LE_EVNET_MASK_RESEVED                                              = 1ULL << 63,//make enum 8 bytes
}
EN_LLC_SPEC_5_1_LE_EVENT_MASK_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_ENCRYPTION_ENABLED_OFF = 0x00,
    
    ////same code
    LLC_SPEC_5_1_HCI_ENCRYPTION_ENABLED_ON_E0_FOR_BR_EDR = 0x01,
    LLC_SPEC_5_1_HCI_ENCRYPTION_ENABLED_ON_AES_CCM_FOR_LE = 0x01,
    ////
    
    LLC_SPEC_5_1_HCI_ENCRYPTION_ENABLED_ON_AES_CCM_FOR_BR_EDR = 0x02,
}
EN_LLC_SPEC_5_1_HCI_ENCRYPTION_ENABLED_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_ROLE_MASTER    = 0x00,
    LLC_SPEC_5_1_HCI_ROLE_SLAVE     = 0x01,
}
EN_LLC_SPEC_5_1_HCI_ROLE_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_PHY_NONE       = 0x00,
    LLC_SPEC_5_1_HCI_PHY_LE_1M      = 0x01,
    LLC_SPEC_5_1_HCI_PHY_LE_2M      = 0x02,
    LLC_SPEC_5_1_HCI_PHY_LE_CODED   = 0x03,
}
EN_LLC_SPEC_5_1_HCI_PHY_T;


typedef enum
{
    LLC_SPEC_5_1_PHY_OPTION_CODED_TX_PREFER_NO_PREFER = 0,
    LLC_SPEC_5_1_PHY_OPTION_CODED_TX_PREFER_S2 = 1,
    LLC_SPEC_5_1_PHY_OPTION_CODED_TX_PREFER_S8 = 2,
}
LLC_SPEC_5_1_PHY_OPTION_CODED_TX_PREFER_T;



typedef struct
{
    uint16_t CodedTxPrefer  : 2;
    uint16_t                : 14;//rfu
} __attribute__((packed))
stLlcSpec51HciPhyOptionsBitField_t;


typedef union
{
    stLlcSpec51HciPhyOptionsBitField_t bitField;
    uint16_t u16Value;
}
stLlcSpec51HciPhyOptions_t;



typedef enum
{
    LLC_SPEC_5_1_HCI_ADV_TYPE_ADV_IND                    = 0x00,
    LLC_SPEC_5_1_HCI_ADV_TYPE_DIRECT_IND_HIGH_DUTY_CYCLE = 0x01,
    LLC_SPEC_5_1_HCI_ADV_TYPE_ADV_SCAN_IND               = 0x02,
    LLC_SPEC_5_1_HCI_ADV_TYPE_NONCONN_IND                = 0x03,
    LLC_SPEC_5_1_HCI_ADV_TYPE_DIRECT_IND_LOW_DUTY_CYCLE  = 0x04,
}
EN_LLC_SPEC_5_1_HCI_ADV_TYPE_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_ADDRESS_TYPE_PUBLIC    = 0x00,
    LLC_SPEC_5_1_HCI_ADDRESS_TYPE_RANDOM    = 0x01,
    LLC_SPEC_5_1_HCI_ADDRESS_TYPE_ANONYMOUS = 0xFF,
}
EN_LLC_SPEC_5_1_HCI_ADDRESS_TYPE_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_OWN_ADDRESS_TYPE_PUBLIC = 0x00,
    LLC_SPEC_5_1_HCI_OWN_ADDRESS_TYPE_RANDOM = 0x01,
    LLC_SPEC_5_1_HCI_OWN_ADDRESS_TYPE_RESOLVABLE_OR_PUBLIC = 0x02,
    LLC_SPEC_5_1_HCI_OWN_ADDRESS_TYPE_RESOLVABLE_OR_RANDOM = 0x03,
}
EN_LLC_SPEC_5_1_HCI_OWN_ADDRESS_TYPE_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_ADV_PEER_ADDRESS_TYPE_PUBLIC_OR_PUBLIC_IDENTITY = 0x00,
    LLC_SPEC_5_1_HCI_ADV_PEER_ADDRESS_TYPE_RANDOM_OR_RANDOM_IDENTITY = 0x01,
}
EN_LLC_SPEC_5_1_HCI_ADV_PEER_ADDRESS_TYPE_T;



typedef enum
{
    LLC_SPEC_5_1_PEER_IDENTITY_ADDRESS_TYPE_PUBLIC_IDENTITY = 0x00,
    LLC_SPEC_5_1_PEER_IDENTITY_ADDRESS_TYPE_RANDOM_IDENTITY = 0x01,
}
EN_LLC_SPEC_5_1_PEER_IDENTITY_ADDRESS_TYPE_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_SCANNER_ADDRESS_TYPE_PUBLIC = 0x00,
    LLC_SPEC_5_1_HCI_SCANNER_ADDRESS_TYPE_RANDOM = 0x01,
    LLC_SPEC_5_1_HCI_SCANNER_ADDRESS_TYPE_PUBLIC_IDENTITY = 0x02,
    LLC_SPEC_5_1_HCI_SCANNER_ADDRESS_TYPE_RANDOM_IDENTITY = 0x03,
}
EN_LLC_SPEC_5_1_HCI_SCANNER_ADDRESS_TYPE_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_ADV_CHANNEL_MAP_37 = (1U << 0),
    LLC_SPEC_5_1_HCI_ADV_CHANNEL_MAP_38 = (1U << 1),
    LLC_SPEC_5_1_HCI_ADV_CHANNEL_MAP_39 = (1U << 2),
}
EN_LLC_SPEC_5_1_HCI_ADV_CHANNEL_MAP_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_ADV_FILTER_POLICY_CONN_ALL_SCAN_ALL                = 0x00,
    LLC_SPEC_5_1_HCI_ADV_FILTER_POLICY_CONN_ALL_SCAN_WHITELIST          = 0x01,
    LLC_SPEC_5_1_HCI_ADV_FILTER_POLICY_CONN_WHITELIST_SCAN_ALL          = 0x02,
    LLC_SPEC_5_1_HCI_ADV_FILTER_POLICY_CONN_WHITELIST_SCAN_WHITELIST    = 0x03,
}
EN_LLC_SPEC_5_1_HCI_ADV_FILTER_POLICY_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_SCAN_TYPE_PASSIVE = 0x00,
    LLC_SPEC_5_1_HCI_SCAN_TYPE_ACTIVE  = 0x01,
}
EN_LLC_SPEC_5_1_HCI_SCAN_TYPE_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_SCAN_FILTER_POLICY_ACCEPT_ALL                              = 0x00,
    LLC_SPEC_5_1_HCI_SCAN_FILTER_POLICY_ACCEPT_WHITELIST                        = 0x01,
    LLC_SPEC_5_1_HCI_SCAN_FILTER_POLICY_ACCEPT_ALL_NOT_RESOLVED_DIRECTED        = 0x02,
    LLC_SPEC_5_1_HCI_SCAN_FILTER_POLICY_ACCEPT_WHITELIST_NOT_RESOLVED_DIRECTED  = 0x03,
}
EN_LLC_SPEC_5_1_HCI_SCAN_FILTER_POLICY_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_SCAN_ENABLE_DISABLED = 0x00,
    LLC_SPEC_5_1_HCI_SCAN_ENABLE_ENABLED  = 0x01,
}
EN_LLC_SPEC_5_1_HCI_SCAN_ENABLE_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_INITIATOR_FILTER_POLICY_WHITELIST_IS_NOT_USED   = 0x00,
    LLC_SPEC_5_1_HCI_INITIATOR_FILTER_POLICY_WHITELIST_IS_USED       = 0x01,
}
EN_LLC_SPEC_5_1_HCI_INITIATOR_FILTER_POLICY_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_CONN_PEER_ADDRESS_TYPE_PUBLIC          = 0x00,
    LLC_SPEC_5_1_HCI_CONN_PEER_ADDRESS_TYPE_RANDOM          = 0x01,
    LLC_SPEC_5_1_HCI_CONN_PEER_ADDRESS_TYPE_PUBLIC_IDENTITY = 0x02,
    LLC_SPEC_5_1_HCI_CONN_PEER_ADDRESS_TYPE_RANDOM_IDENTITY = 0x03,
}
EN_LLC_SPEC_5_1_HCI_CONN_PEER_ADDRESS_TYPE_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_PACKET_BOUNDARY_FLAG_FIRST_NON_AUTO_FLUSHABLE_PACKET_FROM_HOST_TO_CONTROLLER   = 0x00,
    LLC_SPEC_5_1_HCI_PACKET_BOUNDARY_FLAG_CONTINUING_FRAGMENT                                       = 0x01,
    LLC_SPEC_5_1_HCI_PACKET_BOUNDARY_FLAG_FIRST_AUTO_FLUSHABLE_PACKET                               = 2, //0b10  0x10,
    LLC_SPEC_5_1_HCI_PACKET_BOUNDARY_FLAG_COMPLETE_AUTO_FLUSHABLE_PACKET                            = 3, //0b11  0x11,
}
EN_LLC_SPEC_5_1_HCI_PACKET_BOUNDARY_FLAG_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_EVENT_TYPE_ADV_IND          = 0x00,
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_EVENT_TYPE_ADV_DIRECT_IND   = 0x01,
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_EVENT_TYPE_ADV_SCAN_IND     = 0x02,
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_EVENT_TYPE_ADV_NONCONN_IND  = 0x03,
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_EVENT_TYPE_SCAN_RSP         = 0x04,
}
EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_EVENT_TYPE_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_PUBLIC          = 0x00,
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_RANDOM          = 0x01,
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_PUBLIC_IDENTITY = 0x02,
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_RANDOM_IDENTITY = 0x03,
    
    LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_ANONYMOUS       = 0xFF,
}
EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_PUBLIC = 0x00,
    LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_RANDOM = 0x01,
    LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_PUBLIC_IDENTITY = 0x02,
    LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_RANDOM_IDENTITY = 0x03,
    
    LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_RANDOM_CONTROLLER_UNABLE_TO_RESOLVE = 0xFE,
}
EN_LLC_SPEC_5_1_HCI_DIRECT_ADDRESS_TYPE_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_EXT_CONN_PEER_ADDRESS_TYPE_PUBLIC_OR_PUBLIC_IDENTITY   = 0x00,
    LLC_SPEC_5_1_HCI_EXT_CONN_PEER_ADDRESS_TYPE_RANDOM_OR_RANDOM_IDENTITY   = 0x01,
}
EN_LLC_SPEC_5_1_HCI_EXT_CONN_PEER_ADDRESS_TYPE_T;


#define LLC_SPEC_5_1_HCI_RSSI_IS_NOT_AVAILABLE   (0x7F)
#define LLC_SPEC_5_1_HCI_TX_POWER_IS_NOT_AVAILABLE  (0x7F)
#define LLC_SPEC_5_1_HCI_TX_POWER_NO_PREFERENCE     (0x7F)


typedef enum
{
    LLC_SPEC_5_1_HCI_CHANNEL_SELECTION_ALGORITHM_NO_1 = 0x00,
    LLC_SPEC_5_1_HCI_CHANNEL_SELECTION_ALGORITHM_NO_2 = 0x01,
}
EN_LLC_SPEC_5_1_HCI_CHANNEL_SELECTION_ALGORITHM_T;






typedef enum
{
    LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_CONNECTABLE                          = (1U << 0),
    LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_SCANNABLE                            = (1U << 1),
    LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_DIRECTED                             = (1U << 2),
    LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_HIGH_DUTY_CYCLE_DIRECTED_CONNECTABLE = (1U << 3),
    LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_USE_LEGACY_PDUS                      = (1U << 4),
    LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_OMIT_ADDRESS                         = (1U << 5),
    LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_INCLUDE_TX_POWER                     = (1U << 6),
}
EN_LLC_SPEC_5_1_ADVERTISING_EVENT_PROPERTIES_FLAG_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_SCAN_REQUEST_NOTIFICATION_ENABLE_DISABLED = 0x00,
    LLC_SPEC_5_1_HCI_SCAN_REQUEST_NOTIFICATION_ENABLE_ENABLED  = 0x01,
}
EN_LLC_SPEC_5_1_HCI_SCAN_REQUEST_NOTIFICATION_ENABLE_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_ADV_DATA_OPERATION_INTERMEDIATE_FRAGMENT   = 0x00,
    LLC_SPEC_5_1_HCI_ADV_DATA_OPERATION_FIRST_FRAGMENT          = 0x01,
    LLC_SPEC_5_1_HCI_ADV_DATA_OPERATION_LAST_FRAGMENT           = 0x02,
    LLC_SPEC_5_1_HCI_ADV_DATA_OPERATION_COMPLETE                = 0x03,
    LLC_SPEC_5_1_HCI_ADV_DATA_OPERATION_UNCHANGE                = 0x04,
}
EN_LLC_SPEC_5_1_HCI_ADV_DATA_OPERATION_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_SCAN_RESPONSE_DATA_OPERATION_INTERMEDIATE_FRAGMENT   = 0x00,
    LLC_SPEC_5_1_HCI_SCAN_RESPONSE_DATA_OPERATION_FIRST_FRAGMENT          = 0x01,
    LLC_SPEC_5_1_HCI_SCAN_RESPONSE_DATA_OPERATION_LAST_FRAGMENT           = 0x02,
    LLC_SPEC_5_1_HCI_SCAN_RESPONSE_DATA_OPERATION_COMPLETE                = 0x03,
}
EN_LLC_SPEC_5_1_HCI_SCAN_RESPONSE_DATA_OPERATION_T;


typedef enum
{
    LLC_SPEC_5_1_HCI_FRAGMENT_PREFERENCE_MAY_FRAGMENT       = 0x00,
    LLC_SPEC_5_1_HCI_FRAGMENT_PREFERENCE_MAY_NOT_FRAGMENT   = 0x01,
}
EN_LLC_SPEC_5_1_HCI_FRAGMENT_PREFERENCE_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_FILTER_DUPLICATES_DISABLED                                 = 0x00,
    LLC_SPEC_5_1_HCI_FILTER_DUPLICATES_ENABLED                                  = 0x01,
    LLC_SPEC_5_1_HCI_FILTER_DUPLICATES_ENABLED_AND_RESET_FOR_EACH_SCAN_PERIOD   = 0x02,
}
EN_LLC_SPEC_5_1_HCI_FILTER_DUPLICATES_T;

typedef enum
{
    LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_DATA_STATUS_COMPLETE                = 0,
    LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_DATA_STATUS_INCOMPLETE_MORE_DATA    = 1,
    LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_DATA_STATUS_INCOMPLETE_NO_MORE_DATA = 2,
}
EN_LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_DATA_STATUS_T;
typedef struct
{
    uint16_t Connectable : 1;
    uint16_t Scannable : 1;
    uint16_t Directed : 1;
    uint16_t ScanResponse : 1;
    uint16_t LegacyPDUsUsed : 1;
    EN_LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_EVENT_TYPE_DATA_STATUS_T DataStatus: 2;
    uint16_t :9;//rfu
} __attribute__((packed))
stLlcSpec51HciExtendedAdvertisingReportEventTypeBitField_t;

typedef union
{
    stLlcSpec51HciExtendedAdvertisingReportEventTypeBitField_t bitField;
    uint16_t u16Value;
} __attribute__((packed))
stLlcSpec51HciExtendedAdvertisingReportEventType_t;

typedef enum
{
    LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_LEGACY_EVENT_TYPE_ADV_IND                      = 0x0013,
    LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_LEGACY_EVENT_TYPE_ADV_DIRECT_IND               = 0x0015,
    LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_LEGACY_EVENT_TYPE_ADV_SCAN_IND                 = 0x0012,
    LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_LEGACY_EVENT_TYPE_ADV_NONCONN_IND              = 0x0010,
    LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_LEGACY_EVENT_TYPE_SCAN_RSP_TO_ADV_IND          = 0x001B,
    LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_LEGACY_EVENT_TYPE_SCAN_RSP_TO_ADV_SCAN_IND     = 0x001A,
}
EN_LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_LEGACY_EVENT_TYPE_T;

#define LLC_SPEC_5_1_HCI_EXTENDED_ADVERTISING_REPORT_SID_NO_ADI_PROVIDED    (0xFF)



////APIs below

////todo : move to rom_llc_spec_5_1.c
#define LLC_SPEC_5_1_GET_LL_CTRL_PDU_OPCODE_FROM_PAYLOAD(pu8Payload)    ((pu8Payload)[0])

bool rom_llc_spec_5_1_is_instant_passed(uint16_t u16TargetInstant, uint16_t u16CurInstant);

uint16_t rom_llc_spec_5_1_get_ppm_by_sca(uint8_t u8Sca);

uint8_t rom_llc_spec_5_1_get_sca_by_ppm(uint16_t u16Ppm);

bool rom_llc_spec_5_1_is_valid_connection_update_param(uint16_t u16ConnIntervalMin1250us, uint16_t u16ConnIntervalMax1250us, uint16_t u16ConnLatency, uint16_t u16SuperVisionTimeout10Ms);

bool rom_llc_spec_5_1_is_valid_trx_octets_and_time(uint16_t u16TrxOctets, uint16_t u16TrxTime);

bool rom_llc_spec_5_1_is_valid_scan_parameters(uint8_t u8ScanType, uint16_t u16ScanInterval625us, uint16_t u16ScanWindow625us, 
    uint8_t u8OwnAddrType, uint8_t u8ScanFilterPolicy);


#endif
