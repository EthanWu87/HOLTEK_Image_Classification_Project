/*************************************************************************************************************
 * @file    llc_common_extended_advertising_payload_format.h
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
#ifndef LLC_COMMON_EXTENDED_ADVERTISING_PAYLOAD_FORMAT_H
#define LLC_COMMON_EXTENDED_ADVERTISING_PAYLOAD_FORMAT_H






typedef struct
{
    stLlcSpec51AdvChannelPduHeader_t Header;
    
    bool Connectable;
    bool Scannable;
    
    //AdvA
    bool AdvA_Present;
    uint8_t* AdvA;
    
    
    //TargetA
    bool TargetA_Present;
    uint8_t* TargetA;
    
    
    ////todo : CTEInfo not impl now
    bool CTEInfo_Present;
    
    
    //AdvDataInfo
    bool ADI_Present;
    uint16_t ADI_DID;
    uint8_t ADI_SID;
    
    
    //AuxPtr
    bool AuxPtr_Present;
    uint8_t AuxPtr_ChannelIndex;
    uint16_t AuxPtr_ClockAccuracyPpm;
    uint32_t AuxPtr_Offset30Us;
    uint8_t AuxPtr_OffsetUnits30Us;//useless when generate a pdu
    EN_LL_PHY_T AuxPtr_Phy; //@ref EN_LL_PHY_T
    
    
    bool SyncInfo_Present;
    uint32_t SyncInfo_SyncPacketOffset30Us;
    uint8_t SyncInfo_OffsetUnits30Us;//useless when generate a pdu
    bool SyncInfo_OffsetAdjust;//useless when generate a pdu
    uint16_t SyncInfo_Interval1250Us;
    uint8_t SyncInfo_ChM[5];
    uint16_t SyncInfo_ClockAccuracyPpm;
    uint32_t SyncInfo_AA;//AccessAddress
    uint32_t SyncInfo_CRCInit;//24bit
    uint16_t SyncInfo_EventCounter;
    
    
    //TxPower
    bool TxPower_Present;
    int8_t TxPower;
    
    
    //ACAD
    bool ACAD_Present;
    uint8_t ACAD_Length;
    uint8_t* ACAD;
    
    
    //AdvData
    bool AdvData_Present;
    uint8_t AdvData_Length;
    uint8_t* AdvData;
} __attribute__((aligned(4)))
stLlcCommonExtendedAdvertisingPayloadFormat_t;

bool rom_llc_common_extended_advertising_payload_parse(stLlcAdvChannelPdu_t* pstPdu, stLlcCommonExtendedAdvertisingPayloadFormat_t* pstFormat);

bool rom_llc_common_extended_advertising_payload_generate(stLlcAdvChannelPdu_t* pstPdu, stLlcCommonExtendedAdvertisingPayloadFormat_t* pstFormat);

uint16_t rom_llc_common_extended_advertising_payload_calculate_payload_length(bool AdvA_Present,
    bool TargetA_Present,
    bool CTEInfo_Present,
    bool ADI_Present,
    bool Aux_PtrPresent,
    bool SyncInfo_Present,
    bool TxPower_Present,
    uint8_t ACAD_Length,
    uint16_t u16AdvDataLength);
    
uint16_t rom_llc_common_extended_advertising_payload_get_avaliable_AdvData_length(uint16_t u16PayloadBufferLength,
    bool AdvA_Present,
    bool TargetA_Present,
    bool CTEInfo_Present,
    bool ADI_Present,
    bool AuxPtr_Present,
    bool SyncInfo_Present,
    bool TxPower_Present,
    uint8_t ACAD_Length);

bool rom_llc_common_extended_advertising_payload_update_AdvA(stLlcAdvChannelPdu_t* pstPdu, uint8_t AdvA[6], bool TxAdd);
    
bool rom_llc_common_extended_advertising_payload_update_TargetA(stLlcAdvChannelPdu_t* pstPdu, uint8_t TargetA[6], bool RxAdd);
    
bool rom_llc_common_extended_advertising_payload_update_ADI(stLlcAdvChannelPdu_t* pstPdu, uint16_t DID, uint8_t SID);

bool rom_llc_common_extended_advertising_payload_update_AuxPtr(stLlcAdvChannelPdu_t* pstPdu,
    uint8_t AuxPtr_ChannelIndex,
    uint16_t AuxPtr_ClockAccuracyPpm,
    uint32_t AuxPtr_Offset30Us,
    EN_LL_PHY_T AuxPtr_Phy);


bool rom_llc_common_extended_advertising_payload_append_AdvData(stLlcAdvChannelPdu_t* pstPdu, uint8_t* pu8Data, uint8_t u8DataLength);



#endif
