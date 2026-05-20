/*************************************************************************************************************
 * @file    llp_hook.h
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
#ifndef LLP_HOOK_H
#define LLP_HOOK_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    LLP_HOOK_PREFIX_interrupt_proc = 0,
    
    LLP_HOOK_PREFIX_hw_set_idle_mode,
    LLP_HOOK_PREFIX_hw_set_adv_mode,
    LLP_HOOK_PREFIX_hw_set_scan_mode,
    LLP_HOOK_PREFIX_hw_set_init_mode,
    LLP_HOOK_PREFIX_hw_set_slave_mode,
    LLP_HOOK_PREFIX_hw_set_master_mode,
    LLP_HOOK_PREFIX_hw_set_work_time_us,
    LLP_HOOK_PREFIX_hw_set_slave_rx_window,
    LLP_HOOK_PREFIX_hw_is_work_time_reached,
    LLP_HOOK_PREFIX_hw_set_trx_param,
    LLP_HOOK_PREFIX_hw_set_tx_pdu,
    LLP_HOOK_PREFIX_hw_set_rx_pdu,
    LLP_HOOK_PREFIX_hw_get_rx_packet_start_end_time,
    LLP_HOOK_PREFIX_hw_set_ifs,
    LLP_HOOK_PREFIX_hw_set_trt_mode_start_time,
    LLP_HOOK_PREFIX_hw_set_rtr_mode_start_time,
    LLP_HOOK_PREFIX_hw_get_peer_tx_phy,
    LLP_HOOK_PREFIX_sleep_wakeup,
    LLP_HOOK_PREFIX_sleep_on_fragment_config_succeed,
    LLP_HOOK_PREFIX_sleep_on_wakeup_interrupt,
    LLP_HOOK_PREFIX_sleep_is_system_sleep_allowed,
}
EN_LLP_HOOK_PREFIX_T;
#define LLP_HOOK_PREFIX_MAX_NUM  (30)
extern void* g_llpHookPrefixTable[LLP_HOOK_PREFIX_MAX_NUM];


typedef void (*llp_hook_prefix_interrupt_proc) (bool* pbIsDone, uint32_t u32IntState);

typedef void (*llp_hook_prefix_hw_set_idle_mode) (bool* pbIsDone);
typedef void (*llp_hook_prefix_hw_set_adv_mode) (bool* pbIsDone);
typedef void (*llp_hook_prefix_hw_set_scan_mode) (bool* pbIsDone);
typedef void (*llp_hook_prefix_hw_set_init_mode) (bool* pbIsDone);
typedef void (*llp_hook_prefix_hw_set_slave_mode) (bool* pbIsDone);
typedef void (*llp_hook_prefix_hw_set_master_mode) (bool* pbIsDone);
typedef uint8_t (*llp_hook_prefix_hw_set_work_time_us) (bool* pbIsDone, uint8_t enumFragmentType, uint32_t u32WorkTimeUs);
typedef uint8_t (*llp_hook_prefix_hw_set_slave_rx_window) (bool* pbIsDone, uint32_t u32RxWindowUs, uint8_t enumRxPhy);
typedef bool (*llp_hook_prefix_hw_is_work_time_reached) (bool* pbIsDone);
typedef uint8_t (*llp_hook_prefix_hw_set_trx_param) (bool* pbIsDone, bool bIsSecondaryChannel, uint8_t u8ChannelIdx, uint32_t u32AccessAddress, uint32_t u32CrcInit,
                               bool bWhiteningEn, uint8_t txPhy, uint8_t rxPhy );
typedef uint8_t (*llp_hook_prefix_hw_set_tx_pdu) (bool* pbIsDone, void* pstLlpTxPduPtr);
typedef uint8_t (*llp_hook_prefix_hw_set_rx_pdu) (bool* pbIsDone, void* pstLlpRxPduPtr, uint16_t u16RxPayloadSizeLimit);
typedef void (*llp_hook_prefix_hw_get_rx_packet_start_end_time) (bool* pbIsDone, uint64_t* pu64StartTime, uint64_t* pu64EndTime);
typedef uint8_t (*llp_hook_prefix_hw_set_ifs) (bool* pbIsDone, uint8_t enumRxPhy, uint16_t u16IfsUs, uint16_t u16IfsWindowUs);
typedef uint8_t (*llp_hook_prefix_hw_set_trt_mode_start_time) (bool* pbIsDone, uint64_t u64StartTimeUs, uint8_t enumTxPhy);
typedef uint8_t (*llp_hook_prefix_hw_set_rtr_mode_start_time) (bool* pbIsDone, uint64_t u64StartTimeUs, uint8_t enumRxPhy);
typedef uint8_t (*llp_hook_prefix_hw_get_peer_tx_phy) (bool* pbIsDone);

typedef void (*llp_hook_prefix_sleep_wakeup) (bool* pbIsDone);
typedef void (*llp_hook_prefix_sleep_on_fragment_config_succeed) (bool* pbIsDone, uint64_t u64FragmentStartTime);
typedef void (*llp_hook_prefix_sleep_on_wakeup_interrupt) (bool* pbIsDone);
typedef bool (*llp_hook_prefix_sleep_is_system_sleep_allowed) (bool* pbIsDone);

#endif
