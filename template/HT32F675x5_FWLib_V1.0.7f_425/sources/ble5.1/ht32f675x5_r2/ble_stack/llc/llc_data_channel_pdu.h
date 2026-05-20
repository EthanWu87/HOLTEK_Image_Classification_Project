/*************************************************************************************************************
 * @file    llc_data_channel_pdu.h
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
#ifndef LLC_DATA_CHANNEL_PDU_H
#define LLC_DATA_CHANNEL_PDU_H

////forward declaration
struct stLlcDataChannelPduNode;
////

typedef void (*llc_data_channel_pdu_acked_callback) (uint16_t u16ConnHandle, struct stLlcDataChannelPduNode* pstPdu);

typedef struct stLlcDataChannelPduNode
{
    uint64_t u64EncryptPacketCounter; //39 bit
    uint32_t u32Header;
    uint8_t* pu8Payload;
    uint16_t u16PayloadBufSize;
    bool bMemUsed;
    bool bEncrypted;
    bool bTxOrRx;
    llc_data_channel_pdu_acked_callback ackedCallback;
    uint32_t u32AckedParameter;
    
    bool bIsLastPdu;
    
    struct stLlcDataChannelPduNode* next;
    uint32_t u32Reserved;
} __attribute__((aligned(8)))
stLlcDataChannelPdu_t;


typedef struct
{
    stLlcDataChannelPdu_t* pstLongTxDataChannelPduMemBuffer;
    uint16_t u16LongTxDataChannelPduPayloadSize;
    uint8_t u8LongTxDataChannelPduNum;
    
    stLlcDataChannelPdu_t* pstShortTxDataChannelPduMemBuffer;
    uint16_t u16ShortTxDataChannelPduPayloadSize;
    uint8_t u8ShortTxDataChannelPduNum;
    
    stLlcDataChannelPdu_t* pstLongRxDataChannelPduMemBuffer;
    uint16_t u16LongRxDataChannelPduPayloadSize;
    uint8_t u8LongRxDataChannelPduNum;
    
    stLlcDataChannelPdu_t* pstShortRxDataChannelPduMemBuffer;
    uint16_t u16ShortRxDataChannelPduPayloadSize;
    uint8_t u8ShortRxDataChannelPduNum;
}
stLlcDataChannelPduMemCfg_t;

bool rom_llc_data_channel_pdu_mem_init(stLlcDataChannelPduMemCfg_t* pstCfg);

uint16_t rom_llc_data_channel_pdu_get_max_size( bool bTxOrRx );

stLlcDataChannelPdu_t* rom_llc_data_channel_pdu_alloc( bool bTxOrRx, uint16_t  u16RequestPayloadSize);

void rom_llc_data_channel_pdu_free(stLlcDataChannelPdu_t* pstPdu);

bool rom_llc_data_channel_pdu_is_last_tx_pdu_of_acl_packet(stLlcDataChannelPdu_t* pstPdu);

void rom_llc_data_channel_pdu_set_last_tx_pdu_of_acl_packet(stLlcDataChannelPdu_t* pstPdu, bool bIsLastPdu);

#endif
