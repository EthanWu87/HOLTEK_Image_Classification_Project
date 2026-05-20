/*************************************************************************************************************
 * @file    llc_dtm.h
 * @version V1.0
 * @date    2021-12-29
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


#ifndef LLC_DTM_H
#define LLC_DTM_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef enum //ref HCI
{
    DTM_PKT_PRBS9       = 0x00,
    DTM_PKT_11110000    = 0x01,
    DTM_PKT_10101010    = 0x02,
    DTM_PKT_PRBS15      = 0x03,
    DTM_PKT_11111111    = 0x04,
    DTM_PKT_00000000    = 0x05,
    DTM_PKT_00001111    = 0x06,
    DTM_PKT_01010101    = 0x07
}
ENUM_DTM_PKT_T;

typedef struct
{
    //range is [0,39] ,freq = 2402MHz + channel*2MHz
    uint8_t u8Channel;
    
    //range is [37,255]
    uint8_t u8PacketSize;
    
    ENUM_DTM_PKT_T enumPacketType;
    
    EN_LL_PHY_T enumPhy;
    
}stDtmTxParam_t;

typedef struct
{
    uint8_t u8Channel;
    EN_LL_PHY_T enumPhy;
}stDtmRxParam_t;


/**********************************************************************************************************************
 interfaces with llp START
 *********************************************************************************************************************/
extern void rom_llc_dtm_set_start_tx_fragment_callback(api_llp_start_dtm_tx_fragment callback);
extern void rom_llc_dtm_set_start_rx_fragment_callback(api_llp_start_dtm_rx_fragment callback);
extern void rom_llc_dtm_set_stop_fragment_callback(api_llp_stop_fragment callback);;
extern EN_LLP_STATE_CMD_T rom_llc_dtm_on_llp_tx_end(stLlpTxEndReport_t* pstReport);
extern EN_LLP_STATE_CMD_T rom_llc_dtm_on_llp_rx_end(stLlpRxEndReport_t* pstReport);
/**********************************************************************************************************************
 interfaces with llp END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 * @brief  dtm init
 * @param  pu8Buf: user provided buffer, should be 4-byte aligned
 * @param  u16BufSize: user provide buffer size, should not be smaller than 256
 * @return EN_LLP_ERR_T: @ref EN_LLP_ERR_T
 *********************************************************************************************************************/
extern EN_LLP_ERR_T rom_llc_dtm_init(uint8_t *pu8Buf, uint16_t u16BufSize);


/**********************************************************************************************************************
 * @brief  start DTM tx test with param
 * @param  pstParam: @ref stDtmTxParam_t
 * @return EN_LLP_ERR_T: @ref EN_LLP_ERR_T
 *********************************************************************************************************************/
extern EN_LLP_ERR_T rom_llc_dtm_tx_start(stDtmTxParam_t *pstParam);


/**********************************************************************************************************************
 * @brief  start DTM rx test with param
 * @param  pstParam: @ref stDtmRxParam_t
 * @return EN_LLP_ERR_T: @ref EN_LLP_ERR_T
 *********************************************************************************************************************/
extern EN_LLP_ERR_T rom_llc_dtm_rx_start(stDtmRxParam_t *pstParam);


/**********************************************************************************************************************
 * @brief  stop tx or rx test
 * @param  void
 * @return void
 *********************************************************************************************************************/
extern void rom_llc_dtm_trx_stop(void);


/**********************************************************************************************************************
 * @brief  get sent packet count
 * @param  bNeedClear: true to set count to 0 after return
 * @param  pu32TxCount: pointer of a word to hold sent packet count, could be NULL
 * @return EN_LLP_ERR_T: @ref EN_LLP_ERR_T
 *********************************************************************************************************************/
extern EN_LLP_ERR_T rom_llc_dtm_get_tx_count(bool bNeedClear, uint32_t* pu32TxCount);


/**********************************************************************************************************************
 * @brief  get received packet count
 * @param  bNeedClear: true to set count to 0 after return
 * @param  pu32CrcOkCount: pointer of a word to hold received packet count with CRC_OK, could be NULL
 * @param  pu32CrcErrCount: pointer of a word to hold received packet count with CRC_ERR, could be NULL
 * @return EN_LLP_ERR_T: @ref EN_LLP_ERR_T
 *********************************************************************************************************************/
extern EN_LLP_ERR_T rom_llc_dtm_get_rx_count(bool bNeedClear, uint32_t* pu32CrcOkCount, uint32_t* pu32CrcErrCount);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
