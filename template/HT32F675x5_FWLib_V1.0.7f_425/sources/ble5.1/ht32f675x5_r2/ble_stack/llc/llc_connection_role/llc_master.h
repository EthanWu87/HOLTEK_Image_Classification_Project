/*************************************************************************************************************
 * @file    llc_master.h
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
#ifndef LLC_MASTER_H
#define LLC_MASTER_H


typedef struct
{
    uint64_t u64StartTime;
    uint64_t u64TimeOfLastSync;
    uint32_t u32AccessAddress;
    uint32_t u32CrcInit;
    uint16_t u16ConnItv1250us;
    uint16_t u16ConnSlaveLatency;
    uint16_t u16ConnSupervisionTimeout10ms;
    bool bChSel;
    uint8_t pu8ChM[5];
    uint8_t u8Hop;
    uint8_t u8Sca;
    EN_LL_PHY_T enumPhy;
    
    uint8_t u8SelfAddrType;
    uint8_t pu8SelfAddr[6];

    uint8_t Peer_RPA_Resoluted; //only  Peer_RPA_Resoluted,Peer_Identify_Address exists
    uint8_t Peer_Identify_Address_Type;
    uint8_t Peer_Identify_Address[6];
    uint8_t Own_Address_Be_RPA;
    
    uint8_t u8PeerAddrType;
    uint8_t pu8PeerAddr[6];
    uint32_t u32RssiRelatedValue;
} __attribute__((aligned(8)))
stLlcMasterInitParam_t;


bool rom_llc_master_init(stLlcConnectionRole_t* pstRole, stLlcMasterInitParam_t* pstParam);

uint32_t rom_llc_master_on_event_blocked(void* pstRoleInstance);


EN_LLP_ERR_T rom_llc_master_config_llp (void* pstRoleInstance, uint32_t u32MaxWorkWindowTimeUs);

void rom_llc_master_on_llp_fragment_start(void* pstRoleInstance);


bool rom_llc_master_on_llp_fragment_stop(void* pstRoleInstance);

EN_LLP_STATE_CMD_T rom_llc_master_on_llp_tx_end(void* pstRoleInstance, stLlpTxEndReport_t *pstReport);

EN_LLP_STATE_CMD_T rom_llc_master_on_llp_rx_end(void* pstRoleInstance, stLlpRxEndReport_t *pstReport);




#endif
