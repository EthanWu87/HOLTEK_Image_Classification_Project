/*************************************************************************************************************
 * @file    host_hook.h
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
#ifndef __HOSTHOOK_H__
#define __HOSTHOOK_H__
typedef enum
{
    HOST_HOOK_PREFIX_host_interface_process_event  =0,
    HOST_HOOK_PREFIX_att_packet_handler  ,
    HOST_HOOK_PREFIX_sm_pdu_handler ,
    HOST_HOOK_PREFIX_l2cap_signaling_handler,
    HOST_HOOK_PREFIX_rx_acl_data_handler  ,
    HOST_HOOK_PREFIX_host_stack_task_handler ,
    HOST_HOOK_PREFIX_gatt_client_run ,
    HOST_HOOK_PREFIX_sm_run_core ,
    HOST_HOOK_PREFIX_sm_run_core_0 ,
    HOST_HOOK_PREFIX_sm_run_core_1 ,
    HOST_HOOK_PREFIX_sm_run_core_2 ,
    HOST_HOOK_PREFIX_sm_handle_encryption_result ,
    HOST_HOOK_PREFIX_sm_key_distribution_handle_all_received ,
    HOST_HOOK_PREFIX_gatt_complete_event ,
    HOST_HOOK_PREFIX_host_interface_get_chip_id ,
    HOST_HOOK_PREFIX_att_validate_security ,
    HOST_HOOK_PREFIX_host_interface_get_own_identify_address,
    HOST_HOOK_PREFIX_sm_pair_trigger_next,
    HOST_HOOK_PREFIX_sm_pair_trigger_next_2,
    HOST_HOOK_PREFIX_host_get_avail_long_data_buffer_num_after_alloc,
    HOST_HOOK_PREFIX_host_free_data_buffer,
    HOST_HOOK_PREFIX_host_get_avail_data_buffer,
    HOST_HOOK_PREFIX_host_l2cap_tx_buffer_commit,
    HOST_HOOK_PREFIX_sm_notify_pair_complt,
    HOST_HOOK_PREFIX_host_add_rx_packet_from_llc,
    
}
ENUM_HOST_HOOK_PREFIX;
#define HOST_HOOK_PREFIX_MAX_NUM  (26)
extern void* g_hostHookPrefixTable[HOST_HOOK_PREFIX_MAX_NUM];


typedef bool (*host_hook_prefix_host_interface_process_event) (bool* pbIsDone, uint8_t Event_Code, uint8_t Parameter_Total_Length, uint8_t* Event_Parameter);
typedef void (*host_hook_prefix_rx_acl_data_handler) (bool* pbIsDone, uint16_t u16ConHandle);
typedef void (*host_hook_prefix_host_stack_task_handler) (bool* pbIsDone, void *pstMsg);
typedef int (*host_hook_prefix_gatt_client_run) (bool* pbIsDone, void *pstMsg);
typedef void (*host_hook_prefix_sm_run_core) (bool* pbIsDone, void *pstMsg);
typedef void (*host_hook_prefix_sm_run_core_0) (bool* pbIsDone, void *pstMsg,void *pstMsg1,void *pstMsg2);
typedef void (*host_hook_prefix_sm_run_core_1) (bool* pbIsDone, void *pstMsg,void *pstMsg1,void *pstMsg2);
typedef void (*host_hook_prefix_sm_run_core_2) (bool* pbIsDone, void *pstMsg,void *pstMsg1,void *pstMsg2);
typedef void (*host_hook_prefix_sm_handle_encryption_result) (bool* pbIsDone, uint16_t u16ConHandle,uint8_t* pu8Data);
typedef void (*host_hook_prefix_sm_key_distribution_handle_all_received) (bool* pbIsDone, void *pstMsg,void* pu8Data);
typedef void (*host_hook_prefix_gatt_complete_event) (bool* pbIsDone, void *pstMsg, uint8_t status);
typedef void (*host_hook_prefix_att_packet_handler) (bool* pbIsDone, uint16_t conn_handle, uint8_t *packet, uint16_t size );
typedef void (*host_hook_prefix_sm_pdu_handler) (bool* pbIsDone, uint16_t conn_handle, uint8_t *packet, uint16_t size );
typedef void (*host_hook_prefix_l2cap_signaling_handler) (bool* pbIsDone, uint16_t conn_handle, uint8_t *packet, uint16_t size );
typedef void (*host_hook_prefix_host_interface_get_chip_id) (bool* pbIsDone, uint8_t  chip_id[16] );
typedef uint8_t (*host_hook_prefix_att_validate_security) (bool* pbIsDone,  void *pstMsg,void *pstMsg1 );
typedef void (*host_hook_prefix_host_interface_get_own_identify_address) (bool* pbIsDone, uint8_t pu8OwnIdentifyAddr[6],uint8_t * pu8OwnIdentifyAddrType);
typedef void (*host_hook_prefix_sm_pair_trigger_next) (bool* pbIsDone, uint16_t conn_handle);
typedef void (*host_hook_prefix_sm_pair_trigger_next_2) (bool* pbIsDone, uint16_t conn_handle);
typedef uint8_t * (*host_hook_prefix_host_get_avail_data_buffer) (bool* pbIsDone, uint16_t u16BufLen );
typedef void (*host_hook_prefix_host_free_data_buffer) (bool* pbIsDone, uint8_t *pdata );
typedef uint8_t (*host_hook_prefix_host_get_avail_long_data_buffer_num_after_alloc) (bool* pbIsDone, uint16_t u16NeedLen);
typedef uint8_t (*host_hook_prefix_host_l2cap_tx_buffer_commit) (bool* pbIsDone,  uint16_t u16ConHandle, uint16_t U16Cid, uint8_t *u8Buff, uint16_t u16Len);
typedef uint8_t (*host_hook_prefix_host_add_rx_packet_from_llc) (bool* pbIsDone,  uint16_t u16ConHandle, uint8_t *u8Buff, uint16_t u16Len);
typedef void (*host_hook_prefix_sm_notify_pair_complt) (bool* pbIsDone, void *pstMsg);

#endif /* __HOSTHOOK_H__ */


