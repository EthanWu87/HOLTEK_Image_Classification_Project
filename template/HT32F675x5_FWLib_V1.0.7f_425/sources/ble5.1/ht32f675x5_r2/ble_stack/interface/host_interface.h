/*************************************************************************************************************
 * @file    host_interface.h
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
#ifndef HOST_INTERFACE_H
#define HOST_INTERFACE_H


//=====================================================================================================================
// DEFINE
//=====================================================================================================================



//=====================================================================================================================
// DEFINE STRUCT
//=====================================================================================================================
 
uint32_t  rom_host_interface_get_random(void);
void  rom_host_interface_get_random_array(uint8_t rand[16]);
void  rom_host_interface_get_chip_id(uint8_t chip_id[16]);
void  rom_host_interface_timer_start(stack_timer_source_t * timer);
void  rom_host_interface_timer_stop(stack_timer_source_t * timer);
void  rom_host_interface_timer_restart(stack_timer_source_t * timer);
void  rom_host_interface_timer_delete(stack_timer_source_t * ptimer);
void rom_host_interface_start_encryption (uint16_t conn_handle, uint8_t *rand, uint16_t ediv, uint8_t *ltk );


void rom_host_interface_long_term_key_request_reply ( uint16_t conn_handle, uint8_t *ltk );

void rom_host_interface_long_term_key_request_negative_reply ( uint16_t conn_handle );

void rom_host_interface_set_hci_event_parameter_max_length(uint16_t u16MaxLength);
uint16_t rom_host_interface_get_hci_event_parameter_max_length(void);
bool rom_host_interface_process_acl_data(uint16_t Handle, uint8_t Packet_Boundary_Flag, uint8_t Broadcast_Flag, uint16_t Data_Total_Length, uint8_t* Data);
bool rom_host_interface_process_event(uint8_t Event_Code, uint8_t Parameter_Total_Length, uint8_t* Event_Parameter);
void rom_host_interface_get_own_identify_address(uint8_t pu8OwnIdentifyAddr[6],uint8_t * pu8OwnIdentifyAddrType);
#endif  /* __STACK_PORTING_H__ */

