/*************************************************************************************************************
 * @file    llc_hook.h
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
#ifndef LLC_HOOK_H
#define LLC_HOOK_H

typedef enum
{
    LLC_HOOK_PREFIX_schedule_algorithm_get_next_event = 0,
    LLC_HOOK_PREFIX_scheduler_add_event,
    LLC_HOOK_PREFIX_scheduler_is_event_added,
    LLC_HOOK_PREFIX_scheduler_remove_event,
    LLC_HOOK_PREFIX_scheduler_main,
    LLC_HOOK_PREFIX_scheduler_request_reschedule,
    LLC_HOOK_PREFIX_scheduler_on_schedule,
    LLC_HOOK_PREFIX_scheduler_on_llp_fragment_start,
    LLC_HOOK_PREFIX_scheduler_on_llp_fragment_stop,
    LLC_HOOK_PREFIX_scheduler_on_llp_tx_end,
    LLC_HOOK_PREFIX_scheduler_on_llp_rx_end,
    LLC_HOOK_PREFIX_llc_channel_selection_algorithm_no_1,
    LLC_HOOK_PREFIX_llc_channel_selection_algorithm_no_2,
    LLC_HOOK_PREFIX_white_list_is_device_in_list,
    LLC_HOOK_PREFIX_white_list_clear,
    LLC_HOOK_PREFIX_white_list_add_device,
    LLC_HOOK_PREFIX_white_list_remove_device,
    LLC_HOOK_PREFIX_address_get_own_resolvable_private_address,
    LLC_HOOK_PREFIX_address_get_own_resolvable_private_address_with_peer_addr,
    LLC_HOOK_PREFIX_address_set_random_address,
    LLC_HOOK_PREFIX_privacy_resolve_peer_RPA,
    LLC_HOOK_PREFIX_privacy_resolve_local_RPA,
    LLC_HOOK_PREFIX_privacy_is_device_in_resolving_list,
    LLC_HOOK_PREFIX_privacy_is_resolving_enabled,
    LLC_HOOK_PREFIX_privacy_is_adv_scan_init_active,
    LLC_HOOK_PREFIX_data_channel_pdu_get_max_size,
    LLC_HOOK_PREFIX_data_channel_pdu_alloc,
    LLC_HOOK_PREFIX_data_channel_pdu_free,
    LLC_HOOK_PREFIX_adv_channel_pdu_alloc,
    LLC_HOOK_PREFIX_adv_channel_pdu_free,
    LLC_HOOK_PREFIX_acl_data_alloc,
    LLC_HOOK_PREFIX_acl_data_free,
    LLC_HOOK_PREFIX_hci_command_get_parameters_size,
    LLC_HOOK_PREFIX_hci_command_get_num,
    LLC_HOOK_PREFIX_hci_command_alloc,
    LLC_HOOK_PREFIX_hci_command_free,
    LLC_HOOK_PREFIX_legacy_adv_default_paramters_init,
    LLC_HOOK_PREFIX_legacy_adv_check_RPA_and_white_list_disallowed_peer_scan,
    LLC_HOOK_PREFIX_legacy_adv_check_RPA_and_white_list_disallowed_peer_connect,
    LLC_HOOK_PREFIX_legacy_adv_set_tx_ptr_to_advertising_data,
    LLC_HOOK_PREFIX_legacy_adv_set_tx_ptr_to_scan_response_data,
    LLC_HOOK_PREFIX_legacy_scan_init,
    LLC_HOOK_PREFIX_legacy_initiator_init,
    LLC_HOOK_PREFIX_connection_role_alloc_instance,
    LLC_HOOK_PREFIX_connection_role_get_allocated_instance_by_conn_handle,
    LLC_HOOK_PREFIX_connection_role_free_instance,
    LLC_HOOK_PREFIX_connection_role_connection_init,
    LLC_HOOK_PREFIX_connection_role_free_tx_pdu,
    LLC_HOOK_PREFIX_connection_role_alloc_rx_pdu,
    LLC_HOOK_PREFIX_connection_role_free_rx_pdu,
    LLC_HOOK_PREFIX_connection_role_add_tx_data_pdu,
    LLC_HOOK_PREFIX_connection_role_add_tx_ctrl_pdu,
    LLC_HOOK_PREFIX_connection_role_add_host_to_controller_acl_data,
    LLC_HOOK_PREFIX_connection_role_on_connection_event_closed,
    LLC_HOOK_PREFIX_connection_role_get_conn_effective_params,
    LLC_HOOK_PREFIX_connection_role_preset_connection_event,
    LLC_HOOK_PREFIX_data_connection_role_init,
    LLC_HOOK_PREFIX_data_rx_pdu_process,
    LLC_HOOK_PREFIX_data_ctrl_tx_pdu_process,
    LLC_HOOK_PREFIX_data_data_tx_pdu_process,
    LLC_HOOK_PREFIX_data_acl_data_process,
    LLC_HOOK_PREFIX_data_process_main,
    LLC_HOOK_PREFIX_data_process_on_connection_event_closed,
    LLC_HOOK_PREFIX_data_disconnect_when_rx_data_pdu,
    LLC_HOOK_PREFIX_data_enable_tx_data_pdu_process_async,
    LLC_HOOK_PREFIX_slave_init,
    LLC_HOOK_PREFIX_master_init,
    LLC_HOOK_PREFIX_slave_latency_init,
    LLC_HOOK_PREFIX_slave_latency_on_scheduler_event_prepare,
    LLC_HOOK_PREFIX_slave_latency_on_conn_event_closed,
    LLC_HOOK_PREFIX_slave_latency_on_tx_data_added,
    LLC_HOOK_PREFIX_ctrl_procedure_init,
    LLC_HOOK_PREFIX_ctrl_procedure_check_and_init_peer_initiated_procedure_by_first_pdu,
    LLC_HOOK_PREFIX_ctrl_procedure_alloc_tx_ctrl_pdu,
    LLC_HOOK_PREFIX_ctrl_procedure_free_tx_ctrl_pdu,
    LLC_HOOK_PREFIX_ctrl_procedure_send_ctrl_pdu,
    LLC_HOOK_PREFIX_ctrl_procedure_send_ctrl_pdu_after_existing_pdu_send_over,
    LLC_HOOK_PREFIX_ctrl_procedure_rsp_unknown_with_acked_callback,
    LLC_HOOK_PREFIX_ctrl_procedure_rsp_reject_with_acked_callback,
    LLC_HOOK_PREFIX_ctrl_procedure_get_self_initial_procedure_target_instant,
    LLC_HOOK_PREFIX_ctrl_procedure_on_recv_ctrl_pdu,
    LLC_HOOK_PREFIX_priority_on_event_added,
    LLC_HOOK_PREFIX_priority_on_event_config_failed,
    LLC_HOOK_PREFIX_priority_on_event_blocked,
    LLC_HOOK_PREFIX_priority_on_event_stopped,
    LLC_HOOK_PREFIX_priority_is_a_higher_than_b,
    LLC_HOOK_PREFIX_controller_event_HCI_Command_Complete,
    LLC_HOOK_PREFIX_controller_event_HCI_Command_Status,
}
EN_LLC_HOOK_PREFIX_T;
#define LLC_HOOK_PREFIX_MAX_NUM  (100)
extern void* g_llcHookPrefixTable[LLC_HOOK_PREFIX_MAX_NUM];


typedef void* (*llc_hook_prefix_schedule_algorithm_get_next_event) (bool* pbIsDone, void* pstEventListArray, void* pstTempListArray, uint32_t u32EventNum);

typedef bool (*llc_hook_prefix_scheduler_add_event)(bool* pbIsDone, void* pstEvent);
typedef bool (*llc_hook_prefix_scheduler_is_event_added) (bool* pbIsDone, void* pstEvent);
typedef bool (*llc_hook_prefix_scheduler_remove_event)(bool* pbIsDone, void* pstEvent);
typedef void (*llc_hook_prefix_scheduler_main)(bool* pbIsDone);
typedef void (*llc_hook_prefix_scheduler_request_reschedule) (bool* pbIsDone, void* pstEvent);
typedef void (*llc_hook_prefix_scheduler_on_schedule)(bool* pbIsDone);
typedef void (*llc_hook_prefix_scheduler_on_llp_fragment_start)(bool* pbIsDone);
typedef void (*llc_hook_prefix_scheduler_on_llp_fragment_stop)(bool* pbIsDone);
typedef uint8_t (*llc_hook_prefix_scheduler_on_llp_tx_end) (bool* pbIsDone, void *pstReport);
typedef uint8_t (*llc_hook_prefix_scheduler_on_llp_rx_end) (bool* pbIsDone, void *pstReport);

typedef uint8_t (*llc_hook_prefix_llc_channel_selection_algorithm_no_1) (bool* pbIsDone, uint8_t* pu8ChM5Octecs, uint32_t u32HopIncrement, uint8_t* pu8LastUnmappedChannel);
typedef uint8_t (*llc_hook_prefix_llc_channel_selection_algorithm_no_2) (bool* pbIsDone, uint8_t* pu8ChM5Octecs, uint16_t u16Counter, uint32_t u32AccessAddress);

typedef bool (*llc_hook_prefix_white_list_is_device_in_list) (bool* pbIsDone, uint8_t u8AddrType, uint8_t pu8Addr[6]);
typedef uint8_t (*llc_hook_prefix_white_list_clear) (bool* pbIsDone);
typedef uint8_t (*llc_hook_prefix_white_list_add_device) (bool* pbIsDone, uint8_t u8AddressType, uint8_t pu8Address[6]);
typedef uint8_t (*llc_hook_prefix_white_list_remove_device) (bool* pbIsDone, uint8_t u8AddressType, uint8_t pu8Address[6]);

typedef bool (*llc_hook_prefix_address_get_own_resolvable_private_address) (bool* pbIsDone, uint8_t pu8Addr[6]);
typedef bool (*llc_hook_prefix_address_get_own_resolvable_private_address_with_peer_addr) (bool* pbIsDone, uint8_t pu8LocalRPA[6],uint8_t u8PeerIdentifyAddrType, uint8_t pu8PeerIdentifyAddr[6]);
typedef uint8_t (*llc_hook_prefix_address_set_random_address) (bool* pbIsDone, uint8_t pu8RandomAddr[6]);

typedef bool (*llc_hook_prefix_privacy_resolve_peer_RPA) (bool* pbIsDone, uint8_t pu8RPA_peer[6], uint8_t pu8PeerIdentifyAddr[6], uint8_t *pu8PeerIdentifyAddrType );
typedef bool (*llc_hook_prefix_privacy_resolve_local_RPA) (bool* pbIsDone, uint8_t pu8RPA_local[6] );
typedef bool (*llc_hook_prefix_privacy_is_device_in_resolving_list) (bool* pbIsDone, uint8_t u8PeerIdentifyAddrType, uint8_t pu8PeerIdentifyAddr[6], uint8_t *privacy_mode, uint8_t *irk_is_all_zero );
typedef bool (*llc_hook_prefix_privacy_is_resolving_enabled)(bool* pbIsDone);
typedef bool (*llc_hook_prefix_privacy_is_adv_scan_init_active)(bool* pbIsDone);

typedef uint16_t (*llc_hook_prefix_data_channel_pdu_get_max_size) ( bool* pbIsDone, bool bTxOrRx );
typedef void* (*llc_hook_prefix_data_channel_pdu_alloc) ( bool* pbIsDone, uint16_t  u16RequestPayloadSize);
typedef void (*llc_hook_prefix_data_channel_pdu_free) ( bool* pbIsDone, void* pstPdu);

typedef void* (*llc_hook_prefix_adv_channel_pdu_alloc) ( bool* pbIsDone, uint16_t  u16RequestPayloadSize);
typedef void (*llc_hook_prefix_adv_channel_pdu_free) ( bool* pbIsDone, void* pstPdu);

typedef void* (*llc_hook_prefix_acl_data_alloc) (bool* pbIsDone);
typedef void (*llc_hook_prefix_acl_data_free) (bool* pbIsDone, void* pstAclData);

typedef uint16_t (*llc_hook_prefix_hci_command_get_parameters_size) (bool* pbIsDone);
typedef uint8_t (*llc_hook_prefix_hci_command_get_num) (bool* pbIsDone);
typedef void* (*llc_hook_prefix_hci_command_alloc) (bool* pbIsDone);
typedef void (*llc_hook_prefix_hci_command_free) (bool* pbIsDone, void* pstLlcHciCommand);

typedef void (*llc_hook_prefix_legacy_adv_default_paramters_init) (bool* pbIsDone, void* pstLegacyAdv);
typedef bool (*llc_hook_prefix_legacy_adv_check_RPA_and_white_list_disallowed_peer_scan) (bool* pbIsDone, void* pstLegacyAdv, bool bIsPeerRandomOrPublic, uint8_t pu8PeerAddr[6]);
typedef bool (*llc_hook_prefix_legacy_adv_check_RPA_and_white_list_disallowed_peer_connect) (bool* pbIsDone, void* pstLegacyAdv, bool bIsPeerRandomOrPublic, uint8_t pu8PeerAddr[6]);
typedef void (*llc_hook_prefix_legacy_adv_set_tx_ptr_to_advertising_data) (bool* pbIsDone, void* pstLegacyAdv);
typedef void (*llc_hook_prefix_legacy_adv_set_tx_ptr_to_scan_response_data) (bool* pbIsDone, void* pstLegacyAdv);

typedef void (*llc_hook_prefix_legacy_scan_init) (bool* pbIsDone);

typedef void (*llc_hook_prefix_legacy_initiator_init) (bool* pbIsDone);

typedef void* (*llc_hook_prefix_connection_role_alloc_instance) (bool* pbIsDone);
typedef void* (*llc_hook_prefix_connection_role_get_allocated_instance_by_conn_handle) (bool* pbIsDone, uint16_t u16ConnHandle);
typedef void (*llc_hook_prefix_connection_role_free_instance) (bool* pbIsDone,  void* pstRole );
typedef void (*llc_hook_prefix_connection_role_connection_init) (bool* pbIsDone, void* pstRole, uint8_t enumPhy, uint32_t u32RssiRelatedValue);
typedef void (*llc_hook_prefix_connection_role_free_tx_pdu) (bool* pbIsDone, void* pstRole, void* pstPdu);
typedef void* (*llc_hook_prefix_connection_role_alloc_rx_pdu) (bool* pbIsDone, void* pstRole);
typedef void (*llc_hook_prefix_connection_role_free_rx_pdu) (bool* pbIsDone, void* pstRole, void* pstPdu);
typedef void (*llc_hook_prefix_connection_role_add_tx_data_pdu) (bool* pbIsDone, void* pstRole, void* pstPdu);
typedef void (*llc_hook_prefix_connection_role_add_tx_ctrl_pdu) (bool* pbIsDone, void* pstRole, void* pstPdu);
typedef void (*llc_hook_prefix_connection_role_add_host_to_controller_acl_data) (bool* pbIsDone, void* pstRole, void* pstAclData);
typedef void (*llc_hook_prefix_connection_role_on_connection_event_closed) (bool* pbIsDone, void* pstRole);
typedef void (*llc_hook_prefix_connection_role_get_conn_effective_params) (bool* pbIsDone, void* pstRole, void* pstParams);
typedef void (*llc_hook_prefix_connection_role_preset_connection_event) (bool* pbIsDone, void* pstRole, uint16_t u16IncreasedEventCount);

typedef void (*llc_hook_prefix_data_connection_role_init) (bool* pbIsDone, void *pstRole );
typedef uint8_t (*llc_hook_prefix_data_rx_pdu_process) (bool* pbIsDone, void *pstRole );
typedef uint8_t (*llc_hook_prefix_data_ctrl_tx_pdu_process) (bool* pbIsDone, void *pstRole );
typedef uint8_t (*llc_hook_prefix_data_data_tx_pdu_process) (bool* pbIsDone, void *pstRole );
typedef uint8_t (*llc_hook_prefix_data_acl_data_process) (bool* pbIsDone, void *pstRole);
typedef void (*llc_hook_prefix_data_process_main) (bool* pbIsDone, void *pstRole );
typedef void (*llc_hook_prefix_data_process_on_connection_event_closed) (bool* pbIsDone, void *pstRole );
typedef void (*llc_hook_prefix_data_disconnect_when_rx_data_pdu) (bool* pbIsDone, void* pstRole, bool bDisconnectWhenRecvDataPdu);
typedef void (*llc_hook_prefix_data_enable_tx_data_pdu_process_async) (bool* pbIsDone, void *pstRole, bool bEnable);

typedef bool (*llc_hook_prefix_slave_init) (bool* pbIsDone, void* pstRole, void* pstParam);

typedef bool (*llc_hook_prefix_master_init) (bool* pbIsDone, void* pstRole, void* pstParam);

typedef void (*llc_hook_prefix_slave_latency_init) (bool* pbIsDone, void* pstRole);
typedef void (*llc_hook_prefix_slave_latency_on_scheduler_event_prepare) (bool* pbIsDone, void* pstRole);
typedef void (*llc_hook_prefix_slave_latency_on_conn_event_closed) (bool* pbIsDone, void* pstRole);
typedef void (*llc_hook_prefix_slave_latency_on_tx_data_added) (bool* pbIsDone, void* pstRole);

typedef void (*llc_hook_prefix_ctrl_procedure_init) (bool* pbIsDone, void *pstRole);
typedef bool (*llc_hook_prefix_ctrl_procedure_check_and_init_peer_initiated_procedure_by_first_pdu) (bool* pbIsDone, void* pstRole, void* pstCtrlPdu);
typedef void* (*llc_hook_prefix_ctrl_procedure_alloc_tx_ctrl_pdu) (bool* pbIsDone, void *pstRole);
typedef void (*llc_hook_prefix_ctrl_procedure_free_tx_ctrl_pdu) (bool* pbIsDone, void *pstRole, void* pstPdu);
typedef void (*llc_hook_prefix_ctrl_procedure_send_ctrl_pdu) (bool* pbIsDone, void *pstRole, void* pstRelateProcedure, void* pstPdu);
typedef void (*llc_hook_prefix_ctrl_procedure_send_ctrl_pdu_after_existing_pdu_send_over) (bool* pbIsDone, void *pstRole, void* pstRelateProcedure, void* pstPdu);
typedef void (*llc_hook_prefix_ctrl_procedure_rsp_unknown_with_acked_callback) (bool* pbIsDone, void *pstRole, void* pstRelateProcedure, uint8_t u8UnknownType, 
    void* ackedCallback, uint32_t u32AckedParameter);
typedef void (*llc_hook_prefix_ctrl_procedure_rsp_reject_with_acked_callback) (bool* pbIsDone, void *pstRole, void* pstRelateProcedure, uint8_t u8RejectOpcode, uint8_t u8ErrCode,
    void* ackedCallback, uint32_t u32AckedParameter);
typedef uint16_t (*llc_hook_prefix_ctrl_procedure_get_self_initial_procedure_target_instant) (bool* pbIsDone, void *pstRole);
typedef uint8_t (*llc_hook_prefix_ctrl_procedure_on_recv_ctrl_pdu) (bool* pbIsDone, void *pstRole, void* pstCtrlPdu);

typedef void (*llc_hook_prefix_priority_on_event_added) (bool* pbIsDone, void* pstEvent);
typedef void (*llc_hook_prefix_priority_on_event_config_failed) (bool* pbIsDone, void* pstEvent);
typedef void (*llc_hook_prefix_priority_on_event_blocked) (bool* pbIsDone, void* pstEvent, uint32_t u32BlockedCount);
typedef void (*llc_hook_prefix_priority_on_event_stopped) (bool* pbIsDone, void* pstEvent);
typedef bool (*llc_hook_prefix_priority_is_a_higher_than_b) (bool* pbIsDone, uint8_t u8PriorityA, uint8_t u8PriorityB);

typedef void (*llc_hook_prefix_controller_event_HCI_Command_Complete) (bool* pbIsDone, uint8_t OGF, uint16_t OCF, uint8_t Return_Parameters_Size, uint8_t* Return_Parameters);
typedef void (*llc_hook_prefix_controller_event_HCI_Command_Status) (bool* pbIsDone, uint8_t OGF, uint16_t OCF, uint8_t Status);

#endif
