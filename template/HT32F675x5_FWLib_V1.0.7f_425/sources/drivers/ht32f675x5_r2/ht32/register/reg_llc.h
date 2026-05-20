/*************************************************************************************************************
 * @file    reg_llc.h
 * @version V1.0 
 * @date    2020-06-19
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



#ifndef __REG_LLC_H__
#define __REG_LLC_H__


#ifdef __cplusplus
 extern "C" {
#endif




//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t LLC_INT_FLAG;             /* [0x00](RO) */
    __IOM uint32_t LLC_INT_EN;               /* [0x04](RW) */
    __OM  uint32_t LLC_INT_CLR;              /* [0x08](WO) */
    
    __IOM uint32_t LLC_DATA_RATE;            /* [0x0C][RW] */
    __IOM uint32_t LLC_CTRL;                 /* [0x10][RW] */
    __OM  uint32_t LLC_STOP_CTRL;            /* [0x14][WO] */
    
    __OM  uint32_t LLC_TRIG_CTRL;            /* [0x18][WO] */   // Not Confirm with Digital designer

    
    __IOM uint32_t LLC_CLK_RATIO_CFG;        /* [0x1C][RW] */   
    
    __IOM uint32_t LLC_TX_PDU_HEADER;        /* [0x20][RW] */   
    
    __IOM uint32_t LLC_RX_PDU_HEADER;        /* [0x24][RW] */   
    
    __IOM uint32_t LLC_TRX_CHANNEL_CFG;      /* [0x28][RW] */   
    
    __IOM uint32_t LLC_DATA_CHAN_ACCESS_KEY;  /* [0x2C][RW] */ 

    
    __IOM uint32_t LLC_P2G4_DEFAULT_TX_DATA; /* [0x30][RW] */ 

    __IOM uint32_t LLC_BLE_CFG;              /* [0x34][RW] */ 
    
    __IOM uint32_t LLC_BLE_CTRL;             /* [0x38][RW] */ 

    __IOM uint32_t LLC_P2G4_CFG;             /* [0x3C][RW] P2G4 Only */ 
    __IOM uint32_t LLC_P2G4_CTRL;            /* [0x40][RW] P2G4 Only */ 
    __IOM uint32_t LLC_P2G4_CSMA_CFG;        /* [0x44][RW] P2G4 Only */ 
    __OM  uint32_t LLC_P2G4_TRIG_CTRL;       /* [0x48][WO] P2G4 Only */ 
    
    __IOM uint32_t LLC_CRC_INIT_VAL;         /* [0x4C][RW] */ 
    __IOM uint32_t LLC_CRC_CFG;              /* [0x50][RW] */ 
    __IOM uint32_t LLC_CRC_READ_CFG;         /* [0x54][RW] */ 

    
    __IOM uint32_t LLC_SLEEP_PERIOD;           /* [0x58][RW] */ 
    __IOM uint32_t LLC_SLP_ACT_CONVERT_CNT;    /* [0x5C][RW] */ 
    
    __IOM uint32_t LLC_INTV_PERIOD_HI;         /* [0x60][RW] */ 
    __IOM uint32_t LLC_INTV_PERIOD_LO;         /* [0x64][RW] */ 
    
    __IOM uint32_t LLC_INTV_RELOAD_DELTA_HI;   /* [0x68][RW] */ 
    __IOM uint32_t LLC_INTV_RELOAD_DELTA_LO;   /* [0x6C][RW] */ 

    
    __IOM uint32_t LLC_INTV_PERIOD_MAX_HI;     /* [0x70][RW] */ 
    __IOM uint32_t LLC_INTV_PERIOD_MAX_LO;     /* [0x74][RW] */ 

    __IOM uint32_t LLC_INTV_PERIOD_MIN_HI;     /* [0x78][RW] */ 
    __IOM uint32_t LLC_INTV_PERIOD_MIN_LO;     /* [0x7C][RW] */ 

    __IOM uint32_t LLC_IFS_TIME_CFG;           /* [0x80][RW] */ 
    __IOM uint32_t LLC_IFS_WINDOW_CFG;         /* [0x84][RW] */ 

    __IOM uint32_t LLC_LISTEN_BEGIN_HI;        /* [0x88][RW] */ 
    __IOM uint32_t LLC_LISTEN_BEGIN_LO;        /* [0x8C][RW] */

    __IOM uint32_t LLC_LISTEN_END_HI;          /* [0x90][RW] */ 
    __IOM uint32_t LLC_LISTEN_END_LO;          /* [0x94][RW] */

    __IOM uint32_t LLC_RX_STOP_TIME_HI;        /* [0x98][RW] Befor Listen End */   
    __IOM uint32_t LLC_RX_STOP_TIME_LO;        /* [0x9C][RW] Befor Listen End */

    __IOM uint32_t LLC_INTV_PRE_TIME_CFG;      /* [0xA0][RW]  */

    __IOM uint32_t LLC_TRX_STOP_TIME_HI;           /* [0xA4][RW] Before Next Interval */   
    __IOM uint32_t LLC_TRX_STOP_TIME_LO;           /* [0xA8][RW] Before Next Interval */

    
    __IOM uint32_t LLC_IFS_PRE_TIME_CFG;            /* [0xAC][RW]  */

    
    __IOM uint32_t LLC_CCM_PREPARE_TIME_CFG;        /* [0xB0][RW]  */

    __IOM uint32_t LLC_RADIO_TURNON_PRE_TIME_CFG;   /* [0xB4][RW]  */

    __IOM uint32_t LLC_RADIO_TURNOFF_TIME_CFG;      /* [0xB8][RW]  */
    
    __IM uint32_t RESERVED0;                       /* [0xBC][RO]  */
    
    __IOM uint32_t LLC_INTERRUPT_DELAY_CFG;         /* [0xC0][RW]  */

    
    __IOM uint32_t LLC_INIT_ADDR_HI;                /* [0xC4][RW]  Used to check ADV_DIRECT_IND InitA */
    __IOM uint32_t LLC_INIT_ADDR_LO;                /* [0xC8][RW]  */
    __IOM uint32_t LLC_ADV_ADDR_HI;                 /* [0xCC][RW]  Used to check CONN_REQ AdvA */
    __IOM uint32_t LLC_ADV_ADDR_LO;                 /* [0xD0][RW]  */
    __IOM uint32_t LLC_ADV_DIRECT_IND_CFG;          /* [0xD4][RW]  Used to check ADV_DIRECT_IND */

    __IOM uint32_t LLC_DBG_BREAK_POINT;             /* [0xD8][RW]  Used to Debug Purpose */
    __IOM uint32_t LLC_DBG_SEL_POINT;               /* [0xDC][RW]  Used to Debug Purpose */

    
    __IM  uint32_t LTC_WORK_STATE;                  /* [0xE0][RO]  */

    __IM  uint32_t LLC_P2G4_BUSY_FLG;               /* [0xE4][RO] P2G4 Only */

    __IM  uint32_t LLC_TX_EX_ADV_STA;               /* [0xE8][RO]  Used when TX EXT_ADV */
    __IM  uint32_t LLC_TX_UPDATE_STA;               /* [0xEC][RO]   */
    __IM  uint32_t LLC_RX_STA;                      /* [0xF0][RO]   */
    __IM  uint32_t LLC_RX_UPDATE_STA;               /* [0xF4][RO]   */
    
    __IM  uint32_t LLC_RX_HEADER_VAL;               /* [0xF8][RO]   */
    
    __IM  uint32_t LLC_CRC_FLAG;                    /* [0xFC][RO]   */

    __IM  uint32_t LLC_WORK_STA;                    /* [0x100][RO]   */
    
    __IM  uint32_t LLC_RX_NESN;                     /* [0x104][RO]   */
    __IM  uint32_t LLC_RX_SN;                       /* [0x108][RO]   */

    __IM  uint32_t P2G4_LSM_STA;                    /* [0x10C][RO]   */

    
    __IM  uint32_t LLC_INTV_ACT_CNT_HI;              /* [0x110][RO]   */
    __IM  uint32_t LLC_INTV_ACT_CNT_LO;              /* [0x114][RO]   */

    __IM  uint32_t LLC_INTV_ACT_TRIG_CNT_HI;         /* [0x118][RO]   */
    __IM  uint32_t LLC_INTV_ACT_TRIG_CNT_LO;         /* [0x11C][RO]   */

    __IM  uint32_t LLC_IFS_CNT;                      /* [0x120][RO]   */
    __IM  uint32_t LLC_IFS_TRIG_CNT;                 /* [0x124][RO]   */

    __IM  uint32_t LLC_SCH_ACT_CNT_HI;               /* [0x128][RO]   */
    __IM  uint32_t LLC_SCH_ACT_CNT_LO;               /* [0x12C][RO]   */

    __IM  uint32_t LLC_SCH_ACT_TRIG_CNT_HI;          /* [0x130][RO]   */
    __IM  uint32_t LLC_SCH_ACT_TRIG_CNT_LO;          /* [0x134][RO]   */

    __IM  uint32_t LLC_SLEEP_CNT;                    /* [0x138][RO]   */

    __IM  uint32_t LLC_SLEEP_CONVERT_TO_ACT_CNT_HI;  /* [0x13C][RO]   The Value = LLC_SLEEP_CNT x LLC_CLK_RATIO_CFG */  
    __IM  uint32_t LLC_SLEEP_CONVERT_TO_ACT_CNT_LO;  /* [0x140][RO]   The Value = LLC_SLEEP_CNT x LLC_CLK_RATIO_CFG */  

    __IM  uint32_t LLC_ANCHOR_POS_HI;                /* [0x144][RO]    */  
    __IM  uint32_t LLC_ANCHOR_POS_LO;                /* [0x148][RO]    */  

    __IM  uint32_t LLC_SCH_AUXPTR_CNT_HI;            /* [0x14C][RO]    */  
    __IM  uint32_t LLC_SCH_AUXPTR_CNT_LO;            /* [0x150][RO]    */  

} stLLC_CFG_Handle_t,*pstLLC_CFG_Handle_t;



//=====================================================================================================================
// [0x00~0x08] LLC_INT_FLAG(RO) / LLC_INT_EN(RW) / LLC_INT_CLR(WO)
//=====================================================================================================================
#define G24_RX_END_OK_SHIFT                ( 21 )   //  2.4G Only
#define G24_STOP_SHIFT                     ( 20 )   //  2.4G Only
#define G24_RX_DEF_LOST_SHIFT              ( 19 )   //  2.4G Only
#define G24_TX_DEF_DATA_SHIFT              ( 18 )   //  2.4G Only
#define G24_CSMA_TIME_OUT_SHIFT            ( 17 )   //  2.4G Only
#define G24_ADDR_NOT_MATCH_SHIFT           ( 16 )   //  2.4G Only

#define LLC_TX_FAIL_SHIFT                  ( 15 )   // 
#define LLC_RX_END_SHIFT                   ( 14 )   // What deffirence with LLC_RX_END_VLD  [21]
#define LLC_SLEEP_CNT_OVERFLOW_SHIFT       ( 13 )   
#define LLC_RX_LOST_SHIFT                  ( 12 )
#define LLC_RX_CRC_ERRO_SHIFT              ( 11 )
#define LLC_RX_CRC_OK_SHIFT                ( 10 )

#define LLC_TX_END_SHIFT                   ( 9 )
#define LLC_RX_PRE_IFS_SHIFT               ( 8 )
#define LLC_TX_PRE_IFS_SHIFT               ( 7 )


#define LLC_SLEEP_BEGIN_SHIFT              ( 6 )
#define LLC_RELOAD_UNDERFLOW_SHIFT         ( 5 )
#define LLC_RELOAD_OVERFLOW_SHIFT          ( 4 )
#define LLC_LISEN_END_SHIFT                ( 3 )
#define LLC_INTERVAL_END_SHIFT             ( 2 )
#define LLC_RX_PRE_INTERVAL_SHIFT          ( 1 )
#define LLC_TX_PRE_INTERVAL_SHIFT          ( 0 )


typedef enum
{
    G24_INT_RX_END_OK             = ( 0x01 << G24_RX_END_OK_SHIFT ),      // [21]  2.4G Only
    G24_INT_2G4_STOP              = ( 0x01 << G24_RX_END_OK_SHIFT ),      // [20] 2.4G Only
    G24_INT_RX_DEF_LOST           = ( 0x01 << G24_RX_DEF_LOST_SHIFT ),    // [19] 2.4G Only
    G24_INT_TX_DEF_DATA           = ( 0x01 << G24_TX_DEF_DATA_SHIFT ),    // [18]2.4G Only
    G24_INT_CSMA_TIME_OUT         = ( 0x01 << G24_CSMA_TIME_OUT_SHIFT),   // [17] 2.4G Only
    G24_INT_ADDR_NOT_MATCH        = ( 0x01 << G24_ADDR_NOT_MATCH_SHIFT ), // [16] 2.4G Only

    LLC_INT_TX_FAIL               = ( 0x01 << LLC_TX_FAIL_SHIFT ),              // [15]
    LLC_INT_RX_END                = ( 0x01 << LLC_RX_END_SHIFT ),               // [14]
    LLC_INT_SLEEP_CNT_OVERFLOW    = ( 0x01 << LLC_SLEEP_CNT_OVERFLOW_SHIFT ),   // [13] 
    LLC_INT_RX_LOST               = ( 0x01 << LLC_RX_LOST_SHIFT ),              // [12] 
    
    LLC_INT_RX_CRC_ERRO           = ( 0x01 << LLC_RX_CRC_ERRO_SHIFT ),          // [11] 
    LLC_INT_RX_CRC_OK             = ( 0x01 << LLC_RX_CRC_OK_SHIFT ),            // [10] 
    LLC_INT_TX_END                = ( 0x01 << LLC_TX_END_SHIFT ),               // [09]
    LLC_INT_RX_PRE_IFS            = ( 0x01 << LLC_RX_PRE_IFS_SHIFT ),           // [08] 

    LLC_INT_TX_PRE_IFS            = ( 0x01 << LLC_TX_PRE_IFS_SHIFT ),           // [07] 
    LLC_INT_SLEEP_BEGIN           = ( 0x01 << LLC_SLEEP_BEGIN_SHIFT ),          // [06] 
    LLC_INT_RELOAD_UNDERFLOW      = ( 0x01 << LLC_RELOAD_UNDERFLOW_SHIFT ),     // [05] 
    LLC_INT_RELOAD_OVERFLOW       = ( 0x01 << LLC_RELOAD_OVERFLOW_SHIFT ),      // [04]
    
    LLC_INT_LISEN_END             = ( 0x01 << LLC_LISEN_END_SHIFT ),            // [03] 
    LLC_INT_INTERVAL_END          = ( 0x01 << LLC_INTERVAL_END_SHIFT ),         // [02] 
    LLC_INT_RX_PRE_INTERVAL       = ( 0x01 << LLC_RX_PRE_INTERVAL_SHIFT ),      // [01] 
    LLC_INT_TX_PRE_INTERVAL       = ( 0x01 << LLC_TX_PRE_INTERVAL_SHIFT ),      // [00] 

} EN_LLC_INT_FLAG_T;

#define LLC_ALL_INT_MASK      ( (0x01 << 22) - 1 )


//=====================================================================================================================
// [0x0C](RW) LLC_DATA_RATE
//=====================================================================================================================
//=============================================================================
// LLC_DATA_RATE[3:2] LLC_TX_DATA_RATE Define
#define LLC_TX_DATA_RATE_SHIFT             ( 2 )
#define LLC_TX_DATA_RATE_MSK               ( (0x01 << 2) - 1 )

//=============================================================================
// LLC_DATA_RATE[1:0] LLC_RX_DATA_RATE Define
#define LLC_RX_DATA_RATE_SHIFT             ( 0 )
#define LLC_RX_DATA_RATE_MSK               ( (0x01 << 2) - 1 )

typedef enum
{
    EN_LLC_DATA_RATE_125K = 0x00,
    EN_LLC_DATA_RATE_500K = 0x01,
    EN_LLC_DATA_RATE_1M   = 0x02,
    EN_LLC_DATA_RATE_2M   = 0x03,

    EN_LLC_DATA_RATE_NUMB = 0x04,
    
} EN_LLC_DATA_RATE_T;


//=====================================================================================================================
// [0x10](RW) LLC_CTRL
//=====================================================================================================================
//=============================================================================
// LLC_CTRL[0] LLC_LTC_EN Define 
#define LLC_LTC_EN_MSK                     ( (0x01 << 1) - 1 )
#define LLC_LTC_EN_SHIFT                   ( 0 )

//=============================================================================
// LLC_CTRL[1] LLC_DTM_EN Define
#define LLC_DTM_EN_SHIFT                   ( 1 )
#define LLC_DTM_EN_MSK                     ( (0x01 << 1) - 1 )

//=============================================================================
// LLC_CTRL[2] LLC_DATA_BYPASS_EN Define 
#define LLC_DATA_BYPASS_EN_MSK      (( 0x01 << 1 ) - 1)
#define LLC_DATA_BYPASS_EN_SHIFT    ( 2 )

//=============================================================================
// LLC_CTRL[3] LLC_PNGEN_BYPASS_EN Define 
#define LLC_DATA_WHITEN_EN_SHIFT           ( 3 )
#define LLC_DATA_WHITEN_EN_MSK             ( (0x01 << 1) - 1 )

//=============================================================================
// LLC_CTRL[4] LLC_HOST_EN Define 
#define LLC_HOST_EN_MSK             (( 0x01 << 1 ) - 1)
#define LLC_HOST_EN_SHIFT           ( 4 )

//=============================================================================
// LLC_CTRL[5:6] LLC_HOST_RX_EN Define 
#define LLC_HOST_MODE_SEL_MSK       (( 0x01 << 2 ) - 1)
#define LLC_HOST_MODE_SEL_SHIFT      ( 5 )

typedef enum
{ 
    EN_LLC_HOST_NONE      = 0,
    EN_LLC_HOST_RX_ONLY   = 1,
    EN_LLC_HOST_TX_ONLY   = 2,
    EN_LLC_HOST_TRX       = 3,
} EN_LLC_HOST_MODE_T;


//=====================================================================================================================
// [0x14](RW) LLC_STOP_CTRL
//=====================================================================================================================
//=============================================================================
// LLC_STOP_CTRL[1] LLC_STOP_TRX_EN
#define LLC_STOP_TRX_EN_MSK                ( (0x01 << 1) - 1 )
#define LLC_STOP_TRX_EN_SHIFT              ( 1 )

//=============================================================================
// LLC_STOP_CTRL[0] LLC_WHITE_LIST_FAIL_STOP_EN
#define LLC_WHITE_LIST_FAIL_STOP_EN_MSK    ( (0x01 << 1) - 1 )
#define LLC_WHITE_LIST_FAIL_STOP_EN_SHIFT  ( 0 )


//not confirm with digital designer
//=====================================================================================================================
// [0x18](WO) LLC_TRIG_CTRL
//=====================================================================================================================
//=============================================================================
// LLC_TRIG_CTRL[0] LLC_TRIG_SLEEP  Define
#define LLC_SLEEP_EN_SHIFT                 ( 0 )
#define LLC_SLEEP_EN_MSK                   ( (0x01 << 1) - 1 )

#define LLC_WAKEUP_EN_SHIFT                ( 1 )
#define LLC_WAKEUP_EN_MSK                  ( (0x01 << 1) - 1 )

#define LLC_READ_COUNTER_EN_SHIFT          ( 2 )
#define LLC_READ_COUNTER_EN_MSK            ( (0x01 << 1) - 1 )

#define LLC_RELOAD_INTV_SHIFT              ( 3 )
#define LLC_RELOAD_INTV_MSK                ( (0x01 << 1) - 1 )

#define LLC_SYNC_32K_SHIFT                 ( 4 )
#define LLC_SYNC_32K_MSK                   ( (0x01 << 1) - 1 )

#define LLC_RELOAD_SCH_SHIFT               ( 5 )
#define LLC_RELOAD_SCH_MSK                 ( (0x01 << 1) - 1 )

#define LLC_TRIG_ALL_MSK                   ( (0x01 << 6) - 1 )


//=====================================================================================================================
// [0x1C](RW) LLC_CLK_RATIO_CFG
//=====================================================================================================================
//=============================================================================
// LLC_CLK_RATIO_CFG[0:15] LLC_CLK_RATIO_VAL 
#define LLC_CLK_RATIO_VAL_MSK         (( 0x01 << 16 ) - 1 )
#define LLC_CLK_RATIO_VAL_SHIFT       ( 0 )

#define LLC_CLK_RATIO_INVALIDE_MSK    (( 0x01 << 1 ) - 1 )
#define LLC_CLK_RATIO_INVALIDE_SHIFT  ( 16 )


//=====================================================================================================================
// [0x20](RW) LLC_TX_PDU_HEADER
//=====================================================================================================================
//=============================================================================
// LLC_TX_PDU_HEADER[23:0] LLC_TX_PDU_HEADER
#define LLC_TX_PDU_HEADER_SHIFT            ( 0 )
#define LLC_TX_PDU_HEADER_MSK              ( (0x01 << 24) - 1 )

typedef struct
{
    uint32_t u4BitPduType : 4;  // [3:0] PDU TYPE
    uint32_t u4BitZero    : 4;  // [7:4] Keep to Zero
    uint32_t u8BitLen     : 8;  // [15:8] Length 
    uint32_t u16BitRes    : 16; // [31:16] Reserved

} stTxPduHeader_t, *pstTxPduHeader_t;

typedef struct
{
    uint32_t u4BitPduType : 4;  // [3:0] 
    uint32_t u2BitRFU     : 2;  // [5:4] Reserved for future.
    uint32_t u1BitTxAdd   : 1;  // [6] Tx Add
    uint32_t u1BitRxAdd   : 1;  // [7] Rx Add
    uint32_t u8BitLen     : 8;  // [15:8] Length
    uint32_t u16BitRes    : 16; // [16:31] Reserved
    
} stAdvPduHeader_t, *pstAdvPduHeader_t;

typedef struct
{
    uint32_t u2BitLLID    : 2; // [1:0]
    uint32_t u1BitNESN    : 1; // [2] Next Data package Serial Number
    uint32_t u1BitSN      : 1; // [3] Data Package Serial Number
    uint32_t u1MD         : 1; // [4] MD = 1 means not finished.
    uint32_t u3RFU        : 3; // [7:5] Reserved for future.
    uint32_t u8BitLen     : 8; // [15:8] Length
    uint32_t u8BitCTE     : 8; // [23:16] CTE Info
    uint32_t u8bitRes     : 8; // [31:24] Reserved
    
} stDataPduHeader_t, *pstDataPduHeader_t;

typedef struct
{
    uint32_t u9BitTxLen   : 9;  // [8:0]
    uint32_t u23bitRes    : 23; // [31:9] Reserved
    
} stBypassPduHeader_t, *pstBypassPduHeader_t;

typedef struct
{
    uint32_t u9BitTxLen   : 9;  // [8:0]
    uint32_t u7DevAddr    : 7;  // [15:9]
    uint32_t u16bitRes    : 16; // [31:16] Reserved
    
} st2G4Header_t, *pst2G4Header_t;


//=====================================================================================================================
// [0x24](RW) LLC_RX_PDU_HEADER
//=====================================================================================================================
//=============================================================================
// LLC_RX_PDU_HEADER[7:0] LLC_RX_PDU_MAX_LEN
#define LLC_RX_PDU_MAX_LEN_SHIFT           ( 0 )
#define LLC_RX_PDU_MAX_LEN_MSK             ( (0x01 << 8) - 1 )

typedef struct
{
    uint32_t u8BitRxMaxLen : 8;  // [7:0]
    uint32_t u24bitRes     : 24; // [8:31] Reserved
    
} stRxHeader_t, *pstRxHeader_t;


//=====================================================================================================================
// [0x28](RW) LLC_TRX_CHANNEL_CFG
//=====================================================================================================================
//=============================================================================
// LLC_TRX_CHANNEL_CFG[6] LLC_TRX_CHN_SEL
#define LLC_TRX_CHN_SEL_SHIFT              ( 6 )
#define LLC_TRX_CHN_SEL_MSK                ( (0x01 << 1) - 1 )

typedef enum
{
    EN_LLC_TRX_PRIMARY_CHN   = 0,
    EN_LLC_TRX_SECONDARY_CHN = 1,
    
} EN_LLC_TRX_CHN_SEL_T;

#define IS_VALID_LLC_TRX_CHN_SEL( SEL )  ( ((SEL) == EN_LLC_TRX_PRIMARY_CHN) \
                                        || ((SEL) == EN_LLC_TRX_SECONDARY_CHN) )

//=============================================================================
// LLC_TRX_CHANNEL_CFG[5:0] LLC_TRX_CHN_INDEX
#define LLC_TRX_CHN_INDEX_SHIFT            ( 0 )
#define LLC_TRX_CHN_INDEX_MSK              ( (0x01 << 6) - 1 )
#define LLC_TRX_MAX_CHN_NUMB               ( 39 )


//=====================================================================================================================
// [0x2C](RW) LLC_DATA_CHAN_ACCESS_KEY
//=====================================================================================================================
//=============================================================================
// LLC_DATA_CHAN_ACCESS_KEY[3] LLC_DATA_CHAN_ACCESS_KEY
#define LLC_DATA_CHAN_ACCESS_KEY_SHIFT     ( 0 )
#define LLC_DATA_CHAN_ACCESS_KEY_MSK       ( WORD_MSK )

#define LLC_DATA_CHN_ACCESS_KEY            ( 0x8E89BED6 )


//=====================================================================================================================
// [0x34] (RW) LLC_BLE_CFG
//=====================================================================================================================
//=============================================================================
// LLC_BLE_CFG[3] LLC_RX_PDU_TYPE
#define LLC_RX_PDU_TYPE_SHIFT              ( 3 )
#define LLC_RX_PDU_TYPE_MSK                ( (0x01 << 1) - 1 )

typedef enum
{ 
    EN_LLC_RX_TONE_END  = 0,
    EN_LLC_RX_PDU_END   = 1,

} EN_LLC_RX_PDU_TYPE_T;

//=============================================================================
// LLC_BLE_CFG[2:0] LLC_WORK_MODE
#define LLC_WORK_MODE_SHIFT                ( 0 )
#define LLC_WORK_MODE_MSK                  ( (0x01 << 3) - 1 )

typedef enum
{
    EN_LLC_IDLE     = 0x00,
    EN_LLC_ADV      = 0x01,
    EN_LLC_SCAN     = 0x02,
    EN_LLC_INIT     = 0x03,
    EN_LLC_SLAVE    = 0x04,
    EN_LLC_MASTER   = 0x05,

} EN_LLC_WORK_MODE_T;

typedef struct
{
    uint32_t u3BitWorkMode : 3;  // [2:0]
    uint32_t u1BitRxPdu    : 1;  // [3]
    uint32_t u28bitRes     : 28; // [4:31] Reserved
    
} stLlcBleCfg_t, *pstLlcBleCfg_t;


//=====================================================================================================================
// [0x38] (RW) LLC_BLE_CTRL
//=====================================================================================================================
#define LLC_ACTIVE_SCAN_EN_MSK            (( 0x01 << 1 ) - 1 )
#define LLC_ACTIVE_SCAN_EN_SHIFT          ( 0 )

#define LLC_RECV_RES_PACKET_EN_MSK        (( 0x01 << 1 ) - 1 )
#define LLC_RECV_RES_PACKET_EN_SHIFT      ( 1 )

#define LLC_CHK_EXPECT_PACKET_EN_MSK      (( 0x01 << 1 ) - 1 )
#define LLC_CHK_EXPECT_PACKET_EN_SHIFT    ( 2 )


//=====================================================================================================================
// [0x3C] (RW)LLC_P2G4_CFG
//=====================================================================================================================
#define LLC_P2G4_WORK_MODE_MSK            (( 0x01 << 3 ) - 1 )
#define LLC_P2G4_WORK_MODE_SHIFT          ( 0 )

typedef enum
{
    EN_P2G4_TX_RX       = 0,
    EN_P2G4_TX_ONCE     = 1,
    EN_P2G4_TX_CONTINUE = 2,
    EN_P2G4_RX_TX       = 4,
    EN_P2G4_RX_ONCE     = 5,

} EN_P2G4_WORK_MODE_T;



//=====================================================================================================================
// [0x40] (RW)LLC_P2G4_CTRL  2G4 only
//=====================================================================================================================
#define LLC_P2G4_CSMA_EN_MSK          (( 0x01 << 1 ) - 1 )
#define LLC_P2G4_CSMA_EN_SHIFT        ( 0 )

#define LLC_P2G4_AUTO_STOP_EN_MSK     (( 0x01 << 1 ) - 1 )
#define LLC_P2G4_AUTO_STOP_EN_SHIFT   ( 1 )

#define LLC_P2G4_STOP_EN_MSK          (( 0x01 << 1 ) - 1 )
#define LLC_P2G4_STOP__EN_SHIFT       ( 2 )


#define LLC_P2G4_REPEAT_EN_MSK        (( 0x01 << 1 ) - 1 )
#define LLC_P2G4_REPEAT__EN_SHIFT     ( 3 )


//=====================================================================================================================
// [0x44] (RW) LLC_P2G4_CSMA_CFG;       P2G4 Only 
//=====================================================================================================================
#define LLC_P2G4_CSMA_LEN_MSK          (( 0x01 << 16 ) - 1 )
#define LLC_P2G4_CSMA_LEN_SHIFT        ( 0 )

#define LLC_P2G4_CSMA_TIMEOUT_MSK      (( 0x01 << 16 ) - 1 )
#define LLC_P2G4_CSMA_TIMEOUT_SHIFT    ( 16 )

//=====================================================================================================================

// [0x48] (WO) LLC_P2G4_TRIG_CTRL
//=====================================================================================================================
#define LLC_P2G4_START_MSK          (( 0x01 << 1 ) - 1 )
#define LLC_P2G4_START_SHIFT        ( 1 )

#define LLC_P2G4_READY_MSK          (( 0x01 << 1 ) - 1 )
#define LLC_P2G4_READY_SHIFT        ( 0 )


//=====================================================================================================================
// [0x4C] (RW) LLC_CRC_INIT_VAL
//=====================================================================================================================
//=============================================================================
// LLC_CRC_INIT_VAL[23:0] LLC_CRC_INIT_VAL
#define LLC_CRC_INIT_VAL_SHIFT             ( 0 )
#define LLC_CRC_INIT_VAL_MSK               ( (0x01 << 24) - 1 )

#define LLC_CRC_INIT_VALUE                 ( 0x00555555 )


//=====================================================================================================================
// [0x50] (RW) LLC_CRC_CFG
//=====================================================================================================================
#define LLC_CRC_BITS_CFG_MSK       (( 0x01 << 2 ) - 1 )
#define LLC_CRC_BITS_CFG_SHIFT     ( 0 )

typedef enum
{
    EN_CRC_24BIT   = 0,
    EN_CRC_23BIT   = 1,    // LSB[0] invalid
    EN_CRC_22BIT   = 2,    // LSB[0:1] invalid
    
} EN_CRC_BITS_T;


//=====================================================================================================================
// [0x54] (RW) LLC_CRC_READ_CFG
//=====================================================================================================================
#define LLC_CRC_READ_CFG_MSK        (( 0x01 << 2 ) - 1 )
#define LLC_CRC_READ_CFG_SHIFT      ( 0 )

typedef enum
{
    EN_CRC_READ_AFTER_WHITEN = 1,
    EN_CRC_READ_AFTER_CRC    = 0,

} EN_CRC_READ_CFG_T;


//=====================================================================================================================
// [0x58] (RW) LLC_SLEEP_PERIOD; unit : 8K/16K/32K
//=====================================================================================================================
//=============================================================================
// LLC_SLEEP_PERIOD[28:0] LLC_SLEEP_PERIOD
#define LLC_SLEEP_PERIOD_SHIFT             ( 0 )
#define LLC_SLEEP_PERIOD_MSK               ( (0x01 << 29) - 1 )


//=====================================================================================================================
// [0x5C] (RW) LLC_SLP_ACT_CONVERT_CNT; unit : 8K/16K/32K
//=====================================================================================================================

#define LLC_SLP_ACT_CONVERT_CNT_MSK      (( 0x01 << 29 ) - 1 )
#define LLC_SLP_ACT_CONVERT_CNT_SHIFT    ( 0 )


typedef enum
{
    EN_LLC_SLEEP_CLK_UINT_8K  = 0x00,
    EN_LLC_SLEEP_CLK_UINT_16K = 0x01,
    EN_LLC_SLEEP_CLK_UINT_32K = 0x02,
    
} EN_SLEEP_CLK_UNIT_T;

//=====================================================================================================================
// [0x60][0x64] (RW) LLC_INTV_PERIOD_HI / LLC_INTV_PERIOD_LO unit : 16mHz
//=====================================================================================================================
//=============================================================================
// LLC_INTV_PERIOD_HI[5:0] LLC_INTV_PERIOD_HI Define
#define LLC_INTV_PERIOD_HI_SHIFT           ( 0 )
#define LLC_INTV_PERIOD_HI_MSK             ( (0x01 << 6) - 1 )

//=============================================================================
// LLC_INTV_PERIOD_LO[31:0] LLC_INTV_PERIOD_LO Define
#define LLC_INTV_PERIOD_LO_SHIFT           ( 0 )
#define LLC_INTV_PERIOD_LO_MSK             ( WORD_MSK )


//=====================================================================================================================
// [0x68~0x6C] (RW) LLC_INTV_RELOAD_DELTA_HI/LLC_INTV_RELOAD_DELTA_LO, unit is 16MHz
//=====================================================================================================================
//=============================================================================
// LLC_INTV_RELOAD_DELTA_HI[6] LLC_INTV_RELOAD_MODE Define
#define LLC_INTV_RELOAD_MODE_SHIFT         ( 6 )
#define LLC_INTV_RELOAD_MODE_MSK           ( (0x01 << 1) - 1 )

typedef enum
{
    EN_LLC_INTV_RELOAD_MINUS  = 0,
    EN_LLC_INTV_RELOAD_PLUS   = 1,
    
} EN_LLC_INTV_RELOAD_MODE_T;

//=============================================================================
// LLC_INTV_RELOAD_DELTA_HI[5:0] LLC_INTV_RELOAD_HI Define
#define LLC_INTV_RELOAD_HI_SHIFT           ( 0 )
#define LLC_INTV_RELOAD_HI_MSK             ( (0x01 << 6) - 1 )

//=============================================================================
// LLC_INTV_RELOAD_DELTA_LO[31:0] LLC_INTV_RELOAD_LO Define
#define LLC_INTV_RELOAD_LO_SHIFT           ( 0 )
#define LLC_INTV_RELOAD_LO_MSK             ( WORD_MSK )


//=====================================================================================================================
// [0x70][0x74] (RW) LLC_INTV_PERIOD_MAX_HI /LLC_INTV_PERIOD_MAX_LO unit : 16mHz
//=====================================================================================================================
#define LLC_INTV_PERIOD_MAX_HI_MSK      (( 0x01u << 6 ) - 1 )
#define LLC_INTV_PERIOD_MAX_HI_SHIFT    ( 0 )

#define LLC_INTV_PERIOD_MAX_LO_MSK      ( WORD_MSK )
#define LLC_INTV_PERIOD_MAX_LO_SHIFT    ( 0 )


//=====================================================================================================================
// [0x78][0x7C] (RW) LLC_INTV_PERIOD_MIN_HI /LLC_INTV_PERIOD_MIN_LO unit : 16mHz
//=====================================================================================================================
#define LLC_INTV_PERIOD_MIN_HI_MSK      (( 0x01u << 6 ) - 1 )
#define LLC_INTV_PERIOD_MIN_HI_SHIFT    ( 0 )

#define LLC_INTV_PERIOD_MIN_LO_MSK      ( WORD_MSK )
#define LLC_INTV_PERIOD_MIN_LO_SHIFT    ( 0 )
 

//=====================================================================================================================
// [0x80] (RW) LLC_IFS_TIME_CFG unit : 16mHz
//=====================================================================================================================
//=============================================================================
// LLC_IFS_TIME_CFG[31:16] LLC_RX_IFS_TIME, Default: 0x8C8
#define LLC_RX_IFS_TIME_SHIFT              ( 16 )
#define LLC_RX_IFS_TIME_MSK                ( (0x01 << 16) - 1 )

//=============================================================================
// LLC_IFS_TIME_CFG[15:0] LLC_TX_IFS_TIME, Default: 0x8A0
#define LLC_TX_IFS_TIME_SHIFT              ( 0 )
#define LLC_TX_IFS_TIME_MSK                ( (0x01 << 16) - 1 )


//=====================================================================================================================
// [0x84] (RW) LLC_IFS_WINDOW_CFG unit : 16mHz, defualt : 0x4B0
//=====================================================================================================================
//=============================================================================
// LLC_IFS_WINDOW_CFG[15:0] LLC_RX_IFS_WINDOW, Default: 0x4B0
#define LLC_RX_IFS_WINDOW_SHIFT            ( 0 )
#define LLC_RX_IFS_WINDOW_MSK              ( (0x01 << 16) - 1 )


//=====================================================================================================================
// [0x88][0x8C] (RW) LLC_LISTEN_BEGIN_HI / LLC_LISTEN_BEGIN_LO, unit: 16mHz
//=====================================================================================================================
//=============================================================================
// LLC_LISTEN_BEGIN_HI[5:0] LLC_LISTEN_BEGIN_HI Define
#define LLC_LISTEN_BEGIN_HI_SHIFT          ( 0 )
#define LLC_LISTEN_BEGIN_HI_MSK            ( (0x01 << 6) - 1 )

//=============================================================================
// LLC_LISTEN_BEGIN_LO[31:0] LLC_LISTEN_BEGIN_LO Define
#define LLC_LISTEN_BEGIN_LO_SHIFT          ( 0 )
#define LLC_LISTEN_BEGIN_LO_MSK            ( WORD_MSK )


//=====================================================================================================================
// [0x90][0x94] (RW) LLC_LISTEN_END_HI / LLC_LISTEN_END_LO unit : 16mHz
//=====================================================================================================================
//=============================================================================
// LLC_LISTEN_END_HI[5:0] LLC_LISTEN_END_HI Define
#define LLC_LISTEN_END_HI_SHIFT            ( 0 )
#define LLC_LISTEN_END_HI_MSK              ( (0x01 << 6) - 1 )

//=============================================================================
// LLC_LISTEN_END_LO[31:0] LLC_LISTEN_END_LO Define
#define LLC_LISTEN_END_LO_SHIFT            ( 0 )
#define LLC_LISTEN_END_LO_MSK              ( WORD_MSK )


//=====================================================================================================================
// [0x98][0x9C] (RW) LLC_RX_STOP_TIME_HI / LLC_RX_STOP_TIME_LO unit : 16mHz
//=====================================================================================================================
#define LLC_RX_STOP_TIME_HI_MSK        (( 0x01 << 6 ) - 1 )
#define LLC_RX_STOP_TIME_HI_SHIFT      ( 0 )

#define LLC_RX_STOP_TIME_LO_MSK        ( WORD_MSK )
#define LLC_RX_STOP_TIME_LO_SHIFT      ( 0 )


//=====================================================================================================================
// [0xA0](RW) LLC_INTV_PRE_TIME_CFG unit : 16mHz
//=====================================================================================================================
#define LLC_INTV_RX_PRE_TIME_MSK      (( 0x01u << 13 ) - 1 )
#define LLC_INTV_RX_PRE_TIME_SHIFT    ( 0 )

#define LLC_INTV_TX_PRE_TIME_MSK      (( 0x01u << 13 ) - 1 )
#define LLC_INTV_TX_PRE_TIME_SHIFT    ( 13 )


//=====================================================================================================================
// [0xA4][0xA8](RW) LLC_TRX_STOP_TIME_HI / LLC_TRX_STOP_TIME_LO unit : 16mHz
//=====================================================================================================================
//=============================================================================
// LLC_TRX_STOP_TIME_HI[5:0] LLC_TRX_STOP_TIME_HI Define
#define LLC_TRX_STOP_TIME_HI_SHIFT         ( 0 )
#define LLC_TRX_STOP_TIME_HI_MSK           ( (0x01 << 6) - 1 )

//=============================================================================
// LLC_TRX_STOP_TIME_LO[31:0] LLC_TRX_STOP_TIME_LO Define
#define LLC_TRX_STOP_TIME_LO_SHIFT         ( 0 )
#define LLC_TRX_STOP_TIME_LO_MSK           ( WORD_MSK )


//=====================================================================================================================
// [0xAC] (RW) LLC_IFS_PRE_TIME_CFG unit : 16mHz
//=====================================================================================================================

#define LLC_IFS_RX_PRE_TIME_MSK       (( 0x01u << 13 ) - 1 )
#define LLC_IFS_RX_PRE_TIME_SHIFT     ( 0 )

#define LLC_IFS_TX_PRE_TIME_MSK       (( 0x01u << 13 ) - 1 )
#define LLC_IFS_TX_PRE_TIME_SHIFT     ( 13 )


//=====================================================================================================================
// [0xB0] (RW) LLC_CCM_PREPARE_TIME_CFG unit : 16mHz
//=====================================================================================================================

#define LLC_RX_CCM_PREPARE_TIME_MSK      (( 0x01u << 16 ) - 1 )
#define LLC_RX_CCM_PREPARE_TIME_SHIFT    ( 0 )

#define LLC_TX_CCM_PREPARE_TIME_MSK      (( 0x01u << 16 ) - 1 )
#define LLC_TX_CCM_PREPARE_TIME_SHIFT    ( 16 )



//=====================================================================================================================
// [0xB4] (RW) LLC_RADIO_TURNON_PRE_TIME_CFG unit : 16mHz
//=====================================================================================================================
//=============================================================================
// LLC_RADIO_TURNON_PRE_TIME_CFG[28:16] LLC_TXRADIO_TURNON_PRE_TIME Define
#define LLC_TXRADIO_TURNON_PRE_TIME_SHIFT  ( 13 )
#define LLC_TXRADIO_TURNON_PRE_TIME_MSK    ( (0x01 << 13) - 1 )

//=============================================================================
// LLC_RADIO_TURNON_PRE_TIME_CFG[12:0] LLC_RXRADIO_TURNON_PRE_TIME Define
#define LLC_RXRADIO_TURNON_PRE_TIME_SHIFT  ( 0 )
#define LLC_RXRADIO_TURNON_PRE_TIME_MSK    ( (0x01 << 13) - 1 )

typedef struct
{
    uint32_t u13RxPreTime : 13;
    uint32_t u3Reserved0  : 3;
    uint32_t u13TxPreTime : 13;
    uint32_t u3Reserved1  : 3;
    
} stRadioPreTime_t;

typedef union
{
    uint32_t          u32RadioPreTime;
    stRadioPreTime_t  stRadioPreTime;
    
}unRadioPreTime_t;



//=====================================================================================================================
// [0xB8] (RW) LLC_RADIO_TURNOFF_TIME_CFG unit : 16mHz
//=====================================================================================================================
#define LLC_RXRADIO_TURNOFF_TIME_MSK          (( 1u << 12 ) - 1 )
#define LLC_RXRADIO_TURNOFF_TIME_SHIFT        ( 0 )


#define LLC_TXRADIO_TURNOFF_TIME_MSK          (( 1u << 12 ) - 1 )
#define LLC_TXRADIO_TURNOFF_TIME_SHIFT        ( 12 )


//=====================================================================================================================
// [0xC0] (RW) LLC_INTERRUPT_DELAY_CFG unit : 16mHz
//=====================================================================================================================

#define LLC_TX_END_INT_DELAY_MSK            (( 0x01u << 8 ) - 1 )
#define LLC_TX_END_INT_DELAY_SHIFT          ( 0 )

#define LLC_RX_PDU_END_INT_DELAY_MSK        (( 0x01u << 8 ) - 1 )
#define LLC_RX_PDU_END_INT_DELAY_SHIFT      ( 8 )

#define LLC_RX_END_INT_DELAY_MSK            (( 0x01u << 8 ) - 1 )
#define LLC_RX_END_INT_DELAY_SHIFT          ( 16 )




//=====================================================================================================================
// [0xC4][0xC8] (RW) LLC_INIT_ADDR_HI / LLC_INIT_ADDR_LO
//=====================================================================================================================

#define LLC_INIT_ADDR_HI_MSK             (( 0x01u << 16 ) - 1 )
#define LLC_INIT_ADDR_HI_SHIFT           ( 0 )

#define LLC_INIT_ADDR_LO_MSK             ( WORD_MSK )
#define LLC_INIT_ADDR_LO_SHIFT           ( 0 )


//=====================================================================================================================
// [0xCC][0xD0] (RW) LLC_ADV_ADDR_HI / LLC_ADV_ADDR_LO
//=====================================================================================================================
#define LLC_ADV_ADDR_HI_MSK             (( 0x01u << 16 ) - 1 )
#define LLC_ADV_ADDR_HI_SHIFT           ( 0 )

#define LLC_ADV_ADDR_LO_MSK             ( WORD_MSK )
#define LLC_ADV_ADDR_LO_SHIFT           ( 0 )



//=====================================================================================================================
// [0xD4] (RW) LLC_ADV_DIRECT_IND_CFG
//=====================================================================================================================
#define LLC_ADV_DIRECT_IND_ADVA_MATCH_EN_MSK      (( 0x01u << 1 ) - 1 )
#define LLC_ADV_DIRECT_IND_ADVA_MATCH_EN_SHIFT    ( 0 )

#define LLC_ADV_DIRECT_IND_INITA_MATCH_EN_MSK      (( 0x01u << 1 ) - 1 )
#define LLC_ADV_DIRECT_IND_INITA_MATCH_EN_SHIFT    ( 1 )



#define LLC_ADV_DIRECT_IND_MATCH_ADDR_MSK      (( 0x01u << 2 ) - 1 )
#define LLC_ADV_DIRECT_IND_MATCH_ADDR_SHIFT    ( 0 )

typedef enum
{
  EN_ADV_DIRCT_IND_MATCH_NONE       = 0,
  EN_ADV_DIRCT_IND_MATCH_ADVA       = 1,
  EN_ADV_DIRCT_IND_MATCH_INITA      = 2,
  EN_ADV_DIRCT_IND_MATCH_ADVA_INITA = 3,

} EN_ADV_DIRCT_IND_ADDR_MATCH_T;

//=====================================================================================================================
// [0xE0] (RW) LTC_WORK_STATE; 
//=====================================================================================================================
#define LTC_WORK_STA_MSK       (( 1U << 1 ) - 1 )
#define LTC_WORK_STA_SHIFT     ( 0 )

typedef enum
{
    EN_LTC_WORK_STA_ACTIVE = 0,
    EN_LTC_WORK_STA_SLEEP  = 1,

} EN_LTC_WORK_STA_T;

//=====================================================================================================================
// [0xE8] (RO) LLC_TX_EX_ADV_STA; 
//=====================================================================================================================

#define LLC_TX_EX_ADV_LEN_MSK      (( 0x01 << 6 ) - 1 )
#define LLC_TX_EX_ADV_LEN_SHIFT    ( 0 )

#define LLC_EX_ADV_MODE_MSK        (( 0x01 << 2 ) - 1 )
#define LLC_EX_ADV_MODE_SHIFT      ( 6 )

typedef enum
{
    EN_EX_ADV_NONE_CONN_NONE_SCAN  = 0,
    EN_EX_ADV_CONN_NONE_SCAN       = 1,
    EN_EX_ADV_NONE_CONN_SCAN       = 2,
} EN_EX_ADV_MODE_T;


//=====================================================================================================================
// [0xF0] (RO) LLC_RX_STA; 
//=====================================================================================================================
//=============================================================================
// LLC_RX_STA[9:8] LLC_RX_CI
#define LLC_RX_CI_SHIFT                    ( 8 )
#define LLC_RX_CI_MSK                      ( (0x01 << 2) - 1 )

typedef enum
{
    EN_LLC_RX_CI_S_8  = 0,
    EN_LLC_RX_CI_S_2  = 1,
    
} EN_LLC_RX_CI_T;






//=====================================================================================================================
// LLC_RX_STA[7:6] LLC_RX_CI
#define LLC_EXT_ADV_MODE_MSK    (( 0x01 << 2) - 1 )
#define LLC_EXT_ADV_MODE_SHIFT  ( 6 )

typedef enum
{
    EN_NON_CONN_NON_SCAN_MODE = 0x00,
    EN_CONN_NON_SCAN_MODE     = 0x01,
    EN_NON_CONN_SCAN_MODE     = 0x02
    
} EN_LLC_RX_EXT_ADV_MODE_T;

//=====================================================================================================================
// LLC_RX_STA[7:6] LLC_EXT_HEADER_LEN
#define LLC_EXT_HEADER_LEN_MSK    (( 0x01 << 5 ) - 1 )
#define LLC_EXT_HEADER_LEN_SHIFT  ( 0 )


//=====================================================================================================================
// [0xF8] (RO) LLC_RX_HEADER_VAL
//=====================================================================================================================
//=============================================================================
// LLC_RX_HEADER_VAL[15:0] LLC_RX_HEADER
#define LLC_RX_HEADER_SHIFT                ( 0 )
#define LLC_RX_HEADER_MSK                  ( (0x01 << 16) - 1 )


//=====================================================================================================================
// [0x110~0x114] (RO) LLC_INTV_ACT_CNT_HI / LLC_INTV_ACT_CNT_LO
//=====================================================================================================================
//=============================================================================
// LLC_INTV_ACT_CNT_HI[5:0] LLC_INTV_ACT_CNT_HI Define
#define LLC_INTV_ACT_CNT_HI_SHIFT          ( 0 )
#define LLC_INTV_ACT_CNT_HI_MSK            ( (0x01 << 6) - 1 )

//=============================================================================
// LLC_INTV_ACT_CNT_LO[31:0] LLC_INTV_ACT_CNT_LO Define
#define LLC_INTV_ACT_CNT_LO_SHIFT          ( 0 )
#define LLC_INTV_ACT_CNT_LO_MSK            ( WORD_MSK )

//=====================================================================================================================
// [0x118~0x11C] (RO) LLC_INTV_ACT_TRIG_CNT_HI / LLC_INTV_ACT_TRIG_CNT_LO
//=====================================================================================================================
//=============================================================================
// LLC_INTV_ACT_TRIG_CNT_HI[5:0] LLC_INTV_ACT_TRIG_CNT_HI Define
#define LLC_INTV_ACT_TRIG_CNT_HI_SHIFT          ( 0 )
#define LLC_INTV_ACT_TRIG_CNT_HI_MSK            ( (0x01 << 6) - 1 )

//=============================================================================
// LLC_INTV_ACT_TRIG_CNT_LO[31:0] LLC_INTV_ACT_CNT_LO Define
#define LLC_INTV_ACT_TRIG_CNT_LO_SHIFT          ( 0 )
#define LLC_INTV_ACT_TRIG_CNT_LO_MSK            ( WORD_MSK )


//=====================================================================================================================
// [0x124][RO] LLC_IFS_TRIG_CNT
//=====================================================================================================================
//=============================================================================
// LLC_IFS_TRIG_CNT[16:0] LLC_IFS_TRIG_CNT Define
#define LLC_IFS_TRIG_CNT_SHIFT           ( 0 )
#define LLC_IFS_TRIG_CNT_MSK             ( (0x01 << 17) - 1 )


//=====================================================================================================================
// [0x128~0x12C] (RO) LLC_SCH_ACT_CNT_HI / LLC_SCH_ACT_CNT_LO
//=====================================================================================================================
//=============================================================================
// LLC_SCH_ACT_CNT_HI[5:0] LLC_SCH_ACT_CNT_HI Define
#define LLC_SCH_ACT_CNT_HI_SHIFT           ( 0 )
#define LLC_SCH_ACT_CNT_HI_MSK             ( (0x01 << 6) - 1 )

//=============================================================================
// LLC_SCH_ACT_CNT_LO[31:0] LLC_SCH_ACT_CNT_LO Define
#define LLC_SCH_ACT_CNT_LO_SHIFT           ( 0 )
#define LLC_SCH_ACT_CNT_LO_MSK             ( WORD_MSK )

//=====================================================================================================================
// [0x130~0x134] (RO) LLC_SCH_ACT_TRIG_CNT_HI / LLC_SCH_ACT_TRIG_CNT_LO
//=====================================================================================================================
//=============================================================================
// LLC_SCH_ACT_TRIG_CNT_HI[5:0] LLC_SCH_ACT_TRIG_CNT_HI Define
#define LLC_SCH_ACT_TRIG_CNT_HI_SHIFT           ( 0 )
#define LLC_SCH_ACT_TRIG_CNT_HI_MSK             ( (0x01 << 6) - 1 )

//=============================================================================
// LLC_SCH_ACT_TRIG_CNT_LO[31:0] LLC_SCH_ACT_TRIG_CNT_LO Define
#define LLC_SCH_ACT_TRIG_CNT_LO_SHIFT           ( 0 )
#define LLC_SCH_ACT_TRIG_CNT_LO_MSK             ( WORD_MSK )


//=====================================================================================================================
// [0x138](RO) LLC_SLEEP_CNT
//=====================================================================================================================
//=============================================================================
// LLC_SLEEP_CNT[28:0] LLC_SLEEP_CNT Define
#define LLC_SLEEP_CNT_SHIFT                ( 0 )
#define LLC_SLEEP_CNT_MSK                  ( (0x01 << 29) - 1 )


#ifdef __cplusplus
}
#endif

#endif /* __REG_LLC_H__ */


