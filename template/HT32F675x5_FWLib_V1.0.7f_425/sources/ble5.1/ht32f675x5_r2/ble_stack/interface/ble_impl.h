/*************************************************************************************************************
 * @file    ble_impl.h
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
#ifndef BLE_IMPL_H
#define BLE_IMPL_H

#define BLE_IMPL_FEATURE_SET   (LLC_SPEC_5_1_FEATURE_SET_LE_ENCRYPTION \
                                         |LLC_SPEC_5_1_FEATURE_SET_EXTENDED_REJECT_INDICATION\
                                         |LLC_SPEC_5_1_FEATURE_SET_SLAVE_INITIATED_FEATURES_EXCHANGE\
                                         |LLC_SPEC_5_1_FEATURE_SET_LL_PRIVACY\
                                         |LLC_SPEC_5_1_FEATURE_SET_EXTENDED_SCANNER_FILTER_POLICIES\
                                         |LLC_SPEC_5_1_FEATURE_SET_LE_DATA_PACKET_LENGTH_EXTENSION\
                                         |LLC_SPEC_5_1_FEATURE_SET_LE_2M_PHY\
                                         |LLC_SPEC_5_1_FEATURE_SET_LE_CODED_PHY\
                                         |LLC_SPEC_5_1_FEATURE_SET_CHANNEL_SELECTION_ALGORITHM_NO2)

#define BLE_IMPL_VERS_NR       (0x0C)   //BLE5.3 for authentication
#define BLE_IMPL_COMP_ID       (0x03BA)
#define BLE_IMPL_SUB_VERS_NR   (0x0001)


#define BLE_IMPL_IFS_WINDOW_US_FOR_1M_PHY      (8)
#define BLE_IMPL_IFS_WINDOW_US_FOR_2M_PHY      (8)
#define BLE_IMPL_IFS_WINDOW_US_FOR_CODED_PHY   (8)


#define BLE_IMPL_PROCEDURE_INSTANT_DELAY   (12)//min 6

#define BLE_IMPL_WINDOW_SIZE   (2) //2500us
#define BLE_IMPL_WINDOW_OFFSET  (2) //2500us


typedef enum
{
    BLE_IMPL_HOOK_PREFIX_init = 0,
    BLE_IMPL_HOOK_PREFIX_get_feature_set,
    BLE_IMPL_HOOK_PREFIX_get_vers_nr,
    BLE_IMPL_HOOK_PREFIX_get_sub_vers_nr,
    BLE_IMPL_HOOK_PREFIX_get_comp_id,
    BLE_IMPL_HOOK_PREFIX_get_ifs_rx_window_us,
    BLE_IMPL_HOOK_PREFIX_get_procedure_instant_delay,
    BLE_IMPL_HOOK_PREFIX_get_connection_window_size_and_window_offset,
    BLE_IMPL_HOOK_PREFIX_get_supported_max_tx_octets,
    BLE_IMPL_HOOK_PREFIX_get_supported_max_tx_time_uncoded,
    BLE_IMPL_HOOK_PREFIX_get_supported_max_tx_time_coded,
    BLE_IMPL_HOOK_PREFIX_get_supported_max_rx_octets,
    BLE_IMPL_HOOK_PREFIX_get_supported_max_rx_time_uncoded,
    BLE_IMPL_HOOK_PREFIX_get_supported_max_rx_time_coded,
    BLE_IMPL_HOOK_PREFIX_get_supported_tx_phys,
    BLE_IMPL_HOOK_PREFIX_get_supported_rx_phys,
    BLE_IMPL_HOOK_PREFIX_get_adv_inter_channel_space_time_us,
    BLE_IMPL_HOOK_PREFIX_is_channel_selection_algorithm_no_2_supported,
    BLE_IMPL_HOOK_PREFIX_determine_adv_interval,
    BLE_IMPL_HOOK_PREFIX_determine_create_connection_interval,
    BLE_IMPL_HOOK_PREFIX_get_adv_schedule_start_time,
    BLE_IMPL_HOOK_PREFIX_get_scan_schedule_start_time,
    BLE_IMPL_HOOK_PREFIX_get_initiator_schedule_start_time,
    BLE_IMPL_HOOK_PREFIX_get_default_public_addr,
    BLE_IMPL_HOOK_PREFIX_get_rand,
    BLE_IMPL_HOOK_PREFIX_generate_access_address,
    BLE_IMPL_HOOK_PREFIX_get_consecutive_conn_events_with_rx_empty_pdu_to_use_latency,
    BLE_IMPL_HOOK_PREFIX_is_slave_latency_enable,
    BLE_IMPL_HOOK_PREFIX_is_wakeup_during_latency_enable,
    BLE_IMPL_HOOK_PREFIX_aes128_encrypt,
    BLE_IMPL_HOOK_PREFIX_ccm4_encrypt,
    BLE_IMPL_HOOK_PREFIX_ccm4_decrypt,
    BLE_IMPL_HOOK_PREFIX_get_auto_fit_channel_map,
}
EN_BLE_IMPL_HOOK_PREFIX_T;
#define BLE_IMPL_HOOK_PREFIX_MAX_NUM  (40)
extern void* g_bleImplHookPrefixTable[BLE_IMPL_HOOK_PREFIX_MAX_NUM];


typedef void (*ble_impl_hook_prefix_init)(bool* pbIsDone);
typedef uint64_t (*ble_impl_hook_prefix_get_feature_set) (bool* pbIsDone);
typedef uint8_t (*ble_impl_hook_prefix_get_vers_nr) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_sub_vers_nr) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_comp_id) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_ifs_rx_window_us) (bool* pbIsDone, uint8_t enumRxPhy);
typedef uint16_t (*ble_impl_hook_prefix_get_procedure_instant_delay) (bool* pbIsDone);
typedef void (*ble_impl_hook_prefix_get_connection_window_size_and_window_offset) (bool* pbIsDone, uint8_t *pu8WindowSize, uint16_t *pu16WindowOffset);
typedef uint16_t (*ble_impl_hook_prefix_get_supported_max_tx_octets) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_supported_max_tx_time_uncoded) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_supported_max_tx_time_coded) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_supported_max_rx_octets) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_supported_max_rx_time_uncoded) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_supported_max_rx_time_coded) (bool* pbIsDone);
typedef uint8_t (*ble_impl_hook_prefix_get_supported_tx_phys) (bool* pbIsDone);
typedef uint8_t (*ble_impl_hook_prefix_get_supported_rx_phys) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_adv_inter_channel_space_time_us) (bool* pbIsDone);
typedef bool (*ble_impl_hook_prefix_is_channel_selection_algorithm_no_2_supported) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_determine_adv_interval) (bool* pbIsDone, uint8_t u8AdvIdx, uint16_t u16Itv625usMin, uint16_t u16MaxItv625usMax);
typedef uint16_t (*ble_impl_hook_prefix_determine_create_connection_interval) (bool* pbIsDone, uint16_t u16Itv1250usMin, uint16_t u16MaxItv1250usMax);
typedef uint64_t (*ble_impl_hook_prefix_get_adv_schedule_start_time) (bool* pbIsDone, uint8_t u8AdvIdx);
typedef uint64_t (*ble_impl_hook_prefix_get_scan_schedule_start_time) (bool* pbIsDone);
typedef uint64_t (*ble_impl_hook_prefix_get_initiator_schedule_start_time) (bool* pbIsDone);
typedef void (*ble_impl_hook_prefix_get_default_public_addr) (bool* pbIsDone, uint8_t pu8Addr[6]);
typedef uint32_t (*ble_impl_hook_prefix_get_rand)(bool* pbIsDone);
typedef uint32_t (*ble_impl_hook_prefix_generate_access_address) (bool* pbIsDone);
typedef uint16_t (*ble_impl_hook_prefix_get_consecutive_conn_events_with_rx_empty_pdu_to_use_latency) (bool* pbIsDone);
typedef bool (*ble_impl_hook_prefix_is_slave_latency_enable) (bool* pbIsDone, uint16_t u16ConnHandle);
typedef bool (*ble_impl_hook_prefix_is_wakeup_during_latency_enable) (bool* pbIsDone, uint16_t u16ConnHandle);
typedef bool (*ble_impl_hook_prefix_aes128_encrypt) (bool* pbIsDone, uint8_t pu8Key[16], uint8_t pu8InData[16], uint8_t pu8OutData[16]);
typedef bool (*ble_impl_hook_prefix_ccm4_encrypt) (bool* pbIsDone, bool bMasterToSlave, uint8_t u8LLID, uint64_t u64EncryptPacketCounter, uint8_t pu8IV[8], uint8_t pu8SessionKey[16],
    uint8_t *pu8DataBuffer, uint16_t u16DataSize, uint16_t u16DataBufferSize);
typedef bool (*ble_impl_hook_prefix_ccm4_decrypt) (bool* pbIsDone, bool bMasterToSlave, uint8_t u8LLID, uint64_t u64EncryptPacketCounter, uint8_t pu8IV[8], uint8_t pu8SessionKey[16],
    uint8_t *pu8DataBuffer, uint16_t u16DataSize, uint16_t u16DataBufferSize);
typedef void (*ble_impl_hook_prefix_get_auto_fit_channel_map) (bool* pbIsDone, uint8_t pu8ChannelMap[5]);


typedef int8_t (*callback_advertising_physical_channel_tx_power)(void);

void rom_ble_impl_init(void);

uint64_t rom_ble_impl_get_feature_set(void);

uint8_t rom_ble_impl_get_vers_nr(void);

uint16_t rom_ble_impl_get_sub_vers_nr(void);

uint16_t rom_ble_impl_get_comp_id(void);

uint16_t rom_ble_impl_get_ifs_rx_window_us(EN_LL_PHY_T enumRxPhy);

uint16_t rom_ble_impl_get_procedure_instant_delay(void);

void rom_ble_impl_get_connection_window_size_and_window_offset(uint8_t *pu8WindowSize, uint16_t *pu16WindowOffset);

uint16_t rom_ble_impl_get_supported_max_tx_octets(void);
uint16_t rom_ble_impl_get_supported_max_tx_time_uncoded(void);
uint16_t rom_ble_impl_get_supported_max_tx_time_coded(void);
uint16_t rom_ble_impl_get_supported_max_rx_octets(void);
uint16_t rom_ble_impl_get_supported_max_rx_time_uncoded(void);
uint16_t rom_ble_impl_get_supported_max_rx_time_coded(void);

uint8_t rom_ble_impl_get_supported_tx_phys(void);
uint8_t rom_ble_impl_get_supported_rx_phys(void);
uint16_t rom_ble_impl_get_adv_inter_channel_space_time_us(void);
bool rom_ble_impl_is_channel_selection_algorithm_no_2_supported(void);
uint16_t rom_ble_impl_determine_adv_interval(uint8_t u8AdvIdx, uint16_t u16Itv625usMin, uint16_t u16MaxItv625usMax);
uint16_t rom_ble_impl_determine_create_connection_interval(uint16_t u16Itv1250usMin, uint16_t u16MaxItv1250usMax);

uint64_t rom_ble_impl_get_adv_schedule_start_time(uint8_t u8AdvIdx);

uint64_t rom_ble_impl_get_scan_schedule_start_time(void);

uint64_t rom_ble_impl_get_initiator_schedule_start_time(void);

void rom_ble_impl_get_default_public_addr(uint8_t pu8Addr[6]);

uint32_t rom_ble_impl_get_rand(void);

uint32_t rom_ble_impl_generate_access_address(void);

uint16_t rom_ble_impl_get_consecutive_conn_events_with_rx_empty_pdu_to_use_latency(void);

bool rom_ble_impl_is_slave_latency_enable(uint16_t u16ConnHandle);
bool rom_ble_impl_is_wakeup_during_latency_enable(uint16_t u16ConnHandle);

bool rom_ble_impl_aes128_encrypt(uint8_t pu8Key[16], uint8_t pu8InData[16], uint8_t pu8OutData[16]);

bool rom_ble_impl_ccm4_encrypt(bool bMasterToSlave, uint8_t u8LLID, uint64_t u64EncryptPacketCounter, uint8_t pu8IV[8], uint8_t pu8SessionKey[16],
    uint8_t *pu8DataBuffer, uint16_t u16DataSize, uint16_t u16DataBufferSize);

bool rom_ble_impl_ccm4_decrypt(bool bMasterToSlave, uint8_t u8LLID, uint64_t u64EncryptPacketCounter, uint8_t pu8IV[8], uint8_t pu8SessionKey[16],
    uint8_t *pu8DataBuffer, uint16_t u16DataSize, uint16_t u16DataBufferSize);

void rom_ble_impl_ifs_mlog_enable(bool bEnable);

bool rom_ble_impl_is_ifs_mlog_enabled(void);

bool rom_ble_impl_set_default_channel_map(uint8_t pu8ChannelMap[5]);

void rom_ble_impl_get_default_channel_map(uint8_t pu8ChannelMap[5]);

void rom_ble_impl_get_auto_fit_channel_map(uint8_t pu8ChannelMap[5]);

uint32_t rom_ble_impl_get_time_us_between_primary_advertising_pdus(void);

uint32_t rom_ble_impl_get_time_us_between_ADV_EXT_IND_and_AUX_ADV_IND(void);

uint32_t rom_ble_impl_get_time_us_between_AUX_ADV_IND_and_AUX_CHAIN_IND(void);

uint32_t rom_ble_impl_get_time_us_between_AUX_SCAN_RSP_and_AUX_CHAIN_IND(void);

uint32_t rom_ble_impl_get_time_us_between_AUX_CHAIN_INDs(void);

uint16_t rom_ble_impl_get_ext_adv_chain_inter_pacekt_space_time_us(void);

uint32_t rom_ble_impl_determine_ext_adv_interval_30us(uint8_t u8AdvertisingHandle, uint32_t u32NeedTimeUs, uint32_t u32MinTimeUs, uint32_t u32MaxTimeUs);

uint64_t rom_ble_impl_get_ext_adv_schedule_start_time(uint8_t u8AdvertisingHandle);

uint64_t rom_ble_impl_get_ext_scan_schedule_start_time(void);

uint32_t rom_ble_impl_get_time_us_between_ext_scan_phys(void);

uint32_t rom_ble_impl_get_time_us_between_ext_scan_channel(void);

uint32_t rom_ble_impl_get_protect_time_us_beween_secondary_scanning_and_primary_scanning(void);

uint32_t rom_ble_impl_get_delay_time_us_for_primary_scanning_window_start(void);

uint64_t rom_ble_impl_get_ext_initiator_schedule_start_time(void);

void rom_ble_impl_get_supported_commands(uint8_t Supported_Commands[64]);

void rom_ble_impl_set_command_filter_enable(bool bEnable);

bool rom_ble_impl_is_command_filter_enabled(void);

bool rom_ble_impl_is_command_supported(uint8_t OGF, uint16_t OCF);

void rom_ble_impl_get_supported_lmp_features(uint8_t LMP_Features[8]);

void rom_ble_impl_get_supported_states(uint8_t LE_States[8]);

void rom_ble_impl_set_tx_power_range(int8_t s8MinTxPower, int8_t s8MaxTxPower);

void rom_ble_impl_get_tx_power_range(int8_t* ps8MinTxPower, int8_t* ps8MaxTxPower);

void rom_ble_impl_set_advertising_physical_channel_tx_power_callback(callback_advertising_physical_channel_tx_power callback);

int8_t rom_ble_impl_get_advertising_physical_channel_tx_power(void);

void rom_ble_impl_set_consecutive_conn_events_with_rx_empty_pdu_to_use_latency(uint16_t u16ConsecutiveConnEvents);

#endif
