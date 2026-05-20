/*************************************************************************************************************
 * @file    host_stack_mem.h
 * @version V1.0
 * @date    2022-01-03
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



#ifndef __HOST_STACK_MEM_H__
#define __HOST_STACK_MEM_H__

//=====================================================================================================================
// DEFINE STRUCT
//=====================================================================================================================
typedef struct st_ll_buffer_record
{

    uint8_t max_conn_num;
    uint8_t max_total_acl_data_num;
    uint8_t max_short_acl_data_num;    
    uint8_t max_long_acl_data_num;
    uint16_t max_short_acl_data_size;
    uint16_t max_long_acl_data_size;
     
} ble_mem_cfg_t;


typedef struct st_stack_acl_data
{ 
    uint8_t *pu8AclData ;
    uint32_t u32MaxBufSize;
    uint16_t u16DataBufSize;
    uint16_t acl_size;
    uint16_t conn_handle;
    uint8_t bMemUsed; 
    uint8_t b_rx_pdu; 
    struct st_stack_acl_data* next; 
}st_stack_acl_data_t;



//memory configure record
extern ble_mem_cfg_t g_ble_mem_cfg;

 

uint8_t * rom_host_get_avail_data_buffer( uint16_t u16BufLen);
uint8_t   rom_host_get_avail_data_buffer_num(void);
uint8_t rom_host_get_avail_long_data_buffer_num_after_alloc ( uint16_t u16NeedLen );
bool rom_l2cap_tx_buffer_commit( uint16_t con_handle, uint16_t CID, uint8_t *p_data, uint16_t data_size);
void rom_host_free_data_buffer ( uint8_t* pdata );
uint8_t rom_host_add_rx_packet_from_llc(uint16_t con_handle,uint8_t* indata,uint16_t len,uint8_t start01_or_continue00);
uint8_t* rom_host_get_rx_packet_from_list(void* pConnContext , uint16_t *outlen);
uint16_t rom_ble_stack_get_max_acl_buf_size(void);
bool rom_host_stack_mem_acl_data_mem_init ( uint8_t *buffer, uint16_t offered_size );
bool rom_host_stack_mem_ctrl_init ( uint8_t *buffer, uint16_t offered_size );
void rom_ble_host_stack_mem_init ( uint8_t u8MaxConNum,uint8_t u8MaxShortAclBufNum,uint16_t u16MaxShortAclBufSize,uint8_t u8MaxLongAclBufNum,uint16_t u16MaxLongAclBufSize  );
void rom_ble_host_stack_timer_init ( void* ptimer_node, uint8_t u8TimerNodeNum,uint32_t u32PointLen);
bool  rom_host_tx_acl_data_to_llc ( void  );
void  rom_clear_tx_acl_data_on_disconn_event ( uint16_t conn_handle );
bool rom_l2cap_buffer_for_sm_tx_is_valid ( void );
bool rom_host_stack_check_has_enough_buffer_to_rsp ( void* pConnContext );
uint8_t *rom_l2cap_get_avail_data_buffer_for_sm_tx ( void );
void rom_host_get_avail_data_buffer_num_ext ( uint8_t *pu8LongBufferCnt, uint8_t *pu8ShortBufferCnt);
#endif  /* __HOST_STACK_MEM_H__ */

