/*************************************************************************************************************
 * @file    llc_adv_channel_pdu.h
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
#ifndef LLC_ADV_CHANNEL_PDU_H
#define LLC_ADV_CHANNEL_PDU_H


typedef struct stLlcAdvChannelPduNode
{
    uint32_t u32Header;
    uint8_t* pu8Payload;
    uint16_t u16PayloadBufSize;
    bool bMemUsed;
    uint8_t u8ReportAddrType;
    uint32_t u32RssiRelatedValue;    
    struct stLlcAdvChannelPduNode* prev;
    struct stLlcAdvChannelPduNode* next;
    uint32_t u32Reserved;
} __attribute__((aligned(4)))
stLlcAdvChannelPdu_t;

typedef struct
{
    stLlcAdvChannelPdu_t* pstLongAdvChannelPduMemBuffer;
    uint16_t u16LongAdvChannelPduPayloadSize;
    uint8_t u8LongAdvChannelPduNum;
    
    stLlcAdvChannelPdu_t* pstShortAdvChannelPduMemBuffer;
    uint16_t u16ShortAdvChannelPduPayloadSize;
    uint8_t u8ShortAdvChannelPduNum;
}
stLlcAdvChannelPduMemCfg_t;

bool rom_llc_adv_channel_pdu_mem_init(stLlcAdvChannelPduMemCfg_t* pstCfg);

uint16_t rom_llc_adv_channel_pdu_get_max_size( void );

stLlcAdvChannelPdu_t* rom_llc_adv_channel_pdu_alloc(  uint16_t  u16RequestPayloadSize);

void rom_llc_adv_channel_pdu_free( stLlcAdvChannelPdu_t* pstPdu);



#endif
