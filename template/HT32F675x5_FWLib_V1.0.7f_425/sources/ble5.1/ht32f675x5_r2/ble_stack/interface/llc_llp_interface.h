/*************************************************************************************************************
 * @file    llc_llp_interface.h
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
#ifndef LLC_LLP_INTERFACE_H
#define LLC_LLP_INTERFACE_H



#define LLP_RSSI_IS_NOT_AVAILABLE   (0x7F)


typedef enum
{
    LLP_ERR_NONE = 0,
    LLP_ERR_SYSTEM,
    LLP_ERR_UNSUPPORT,
    LLP_ERR_TIME_POINT,
    LLP_ERR_PARAM,
}
EN_LLP_ERR_T;

typedef enum
{
    LLP_STATE_CMD_CONTINUE = 0,
    LLP_STATE_CMD_STOP_FRAGMENT,
    LLP_STATE_CMD_CANCEL_TX,
}
EN_LLP_STATE_CMD_T;


typedef enum
{
    LL_PHY_1M = 0,
    LL_PHY_2M,
    LL_PHY_CODED_S8,
    LL_PHY_CODED_S2,
}
EN_LL_PHY_T;


typedef enum
{
    LLP_RX_RESULT_CRC_OK = 0,
    LLP_RX_RESULT_LOST,
    LLP_RX_RESULT_CRC_ERR,
}
EN_LLP_RX_RESULT_T;

typedef enum
{
    LLP_TX_RESULT_OK = 0,
    LLP_TX_RESULT_FAIL,
}
EN_LLP_TX_RESULT_T;


typedef struct
{
    volatile uint32_t* pu32Header;
    volatile uint16_t* pu16PayloadBufSize;//include Payload and MIC
    volatile uint8_t* pu8Payload;//include Payload and MIC
} __attribute__((aligned(8)))
stLlpPduPointer_t; //for data trans between llc and llp


typedef struct
{
    uint32_t u32TxIntervalUs; 
    uint8_t u8ChannelIdx;
    EN_LL_PHY_T enumPhy; 
    uint32_t u32AccessAddress; 
    uint32_t u32CrcInit;
    stLlpPduPointer_t* pstLlpTxPduPtr;
} __attribute__((aligned(8)))
stLlpDtmTxFragmentParam_t;

typedef struct
{
    uint8_t u8ChannelIdx; 
    EN_LL_PHY_T enumPhy; 
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    stLlpPduPointer_t* pstLlpRxPduPtr;
    uint16_t u16RxPayloadSizeLimit;//允许接收的最大Payload长度，超过时RX会立即结束
} __attribute__((aligned(8)))
stLlpDtmRxFragmentParam_t;

typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint16_t u16IfsUs;
    uint16_t u16IfsRxWindowUs;
    uint8_t u8ChannelIdx;
    EN_LL_PHY_T enumPhy;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint16_t u16RxPayloadSizeLimit;//允许接收的最大Payload长度，超过时RX会立即结束
    stLlpPduPointer_t* pstLlpTxPduPtr;
    stLlpPduPointer_t* pstLlpRxPduPtr;
} __attribute__((aligned(8)))
stLlpAdvFragmentParam_t;

typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint16_t u16IfsUs;
    uint16_t u16IfsRxWindowUs;
    uint8_t u8ChannelIdx;
    EN_LL_PHY_T enumPhy;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint16_t u16RxPayloadSizeLimit;//允许接收的最大Payload长度，超过时RX会立即结束
    stLlpPduPointer_t* pstLlpTxPduPtr;
    stLlpPduPointer_t* pstLlpRxPduPtr;
} __attribute__((aligned(8)))
stLlpScanFragmentParam_t;

typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint16_t u16IfsUs;
    uint16_t u16IfsRxWindowUs;
    uint8_t u8ChannelIdx;
    EN_LL_PHY_T enumPhy;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint16_t u16RxPayloadSizeLimit;//允许接收的最大Payload长度，超过时RX会立即结束
    stLlpPduPointer_t* pstLlpTxPduPtr;
    stLlpPduPointer_t* pstLlpRxPduPtr;
} __attribute__((aligned(8)))
stLlpInitFragmentParam_t;

typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint32_t u32RxWindowUs;
    uint16_t u16IfsUs;
    uint16_t u16IfsRxWindowUs;
    uint8_t u8ChannelIdx;
    EN_LL_PHY_T enumTxPhy;
    EN_LL_PHY_T enumRxPhy;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint16_t u16RxPayloadSizeLimit;//允许接收的最大Payload长度，超过时RX会立即结束
    stLlpPduPointer_t* pstLlpTxPduPtr;
    stLlpPduPointer_t* pstLlpRxPduPtr;
} __attribute__((aligned(8)))
stLlpSlaveFragmentParam_t;

typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint16_t u16IfsUs;
    uint16_t u16IfsRxWindowUs;
    uint8_t u8ChannelIdx;
    EN_LL_PHY_T enumTxPhy;
    EN_LL_PHY_T enumRxPhy;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint16_t u16RxPayloadSizeLimit;//允许接收的最大Payload长度，超过时RX会立即结束
    stLlpPduPointer_t* pstLlpTxPduPtr;
    stLlpPduPointer_t* pstLlpRxPduPtr;
} __attribute__((aligned(8)))
stLlpMasterFragmentParam_t;



typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint16_t u16IfsUs;
    uint16_t u16IfsRxWindowUs;
    uint8_t u8ChannelIdx;
    bool bIsSecondaryChannel;
    EN_LL_PHY_T enumPhy;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint16_t u16RxPayloadSizeLimit;//允许接收的最大Payload长度，超过时RX会立即结束
    stLlpPduPointer_t* pstLlpTxPduPtr;
    stLlpPduPointer_t* pstLlpRxPduPtr;
} __attribute__((aligned(8)))
stLlpExtAdvFragmentParam_t;


typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint32_t u32AnchorWindowUs;/**从u64StartTimeUs开始往后计算的窗口，当在这个窗口中未接收到AccessAddress时，fragment会提前结束
                                0 :  关闭此功能**/
    uint16_t u16IfsUs;
    uint16_t u16IfsRxWindowUs;
    uint8_t u8ChannelIdx;
    bool bIsSecondaryChannel;
    EN_LL_PHY_T enumPhy;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint16_t u16RxPayloadSizeLimit;//允许接收的最大Payload长度，超过时RX会立即结束
    stLlpPduPointer_t* pstLlpTxPduPtr;
    stLlpPduPointer_t* pstLlpRxPduPtr;
} __attribute__((aligned(8)))
stLlpExtScanFragmentParam_t;

typedef struct
{
    uint64_t u64StartTimeUs;
    uint32_t u32WorkTimeUs;
    uint32_t u32AnchorWindowUs;/**从u64StartTimeUs开始往后计算的窗口，当在这个窗口中未接收到AccessAddress时，fragment会提前结束
                                0 :  关闭此功能**/
    uint16_t u16IfsUs;
    uint16_t u16IfsRxWindowUs;
    uint8_t u8ChannelIdx;
    bool bIsSecondaryChannel;
    EN_LL_PHY_T enumPhy;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint16_t u16RxPayloadSizeLimit;//允许接收的最大Payload长度，超过时RX会立即结束
    stLlpPduPointer_t* pstLlpTxPduPtr;
    stLlpPduPointer_t* pstLlpRxPduPtr;
} __attribute__((aligned(8)))
stLlpExtInitFragmentParam_t;


typedef struct
{
    EN_LLP_TX_RESULT_T enumTxResult;//for debug
    //0 means not support
    uint64_t u64TxPacketEndTime;
} __attribute__((aligned(8)))
stLlpTxEndReport_t;

typedef struct
{
    EN_LLP_RX_RESULT_T enumRxResult;
    
    //0 means not support
    uint64_t u64RxPacketStartTime;
    uint64_t u64RxPacketEndTime;
    uint32_t u32RssiRelatedValue;//底层上报的与RSSI相关的数值，之后LLC可以通过api_llp_get_rssi获得其对应的实际RSSI
    EN_LL_PHY_T enumPeerTxPhy;
    
} __attribute__((aligned(8)))
stLlpRxEndReport_t;


typedef void (*api_llp_timer_enable) (bool bEnable);
typedef uint64_t (*api_llp_timer_get_count)(bool bHighAccuracy);
typedef uint16_t (*api_llp_get_clock_accuracy_ppm)(void);

typedef EN_LLP_ERR_T (*api_llp_start_dtm_tx_fragment)(stLlpDtmTxFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_start_dtm_rx_fragment)(stLlpDtmRxFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_start_adv_fragment)(stLlpAdvFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_start_scan_fragment)(stLlpScanFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_start_init_fragment)(stLlpInitFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_start_slave_fragment)(stLlpSlaveFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_start_master_fragment)(stLlpMasterFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_start_ext_adv_fragment)(stLlpExtAdvFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_start_ext_scan_fragment)(stLlpExtScanFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_start_ext_init_fragment)(stLlpExtInitFragmentParam_t *pstParam);
typedef EN_LLP_ERR_T (*api_llp_stop_fragment)(void);


typedef EN_LLP_ERR_T (*api_llp_update_tx_pdu)(stLlpPduPointer_t* pstLlpTxPduPtr);
//u16RxPayloadSizeLimit : 允许接收的最大Payload长度，超过时RX会立即结束
typedef EN_LLP_ERR_T (*api_llp_update_rx_pdu)(stLlpPduPointer_t* pstLlpRxPduPtr, uint16_t u16RxPayloadSizeLimit);
typedef void (*api_llp_trig_schedule_report)(void);
typedef int8_t (*api_llp_get_rssi) (uint32_t u32RssiRelatedValue);


typedef void (*callback_on_llp_fragment_start)(void);
typedef void (*callback_on_llp_fragment_stop)(void);
typedef void (*callback_on_schedule)(void);
typedef EN_LLP_STATE_CMD_T (*callback_on_llp_tx_end)(stLlpTxEndReport_t* pstReport);
typedef EN_LLP_STATE_CMD_T (*callback_on_llp_rx_end)(stLlpRxEndReport_t* pstReport);


#endif
