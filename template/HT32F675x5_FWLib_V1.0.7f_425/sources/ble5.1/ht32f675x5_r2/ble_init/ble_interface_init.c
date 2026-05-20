/*************************************************************************************************************
 * @file    ble_interface_init.c
 * @version V1.0
 * @date    2023-05-26
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


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ble_config.h"
#include "err_def.h"
#include "hal_rf.h"

#include "llc_spec_5_1.h"
#include "llc_llp_interface.h"
#include "llp_hw.h"
#include "llp.h"
#include "llc.h"

#include "hci.h"
#include "bluetooth.h"
#include "host_stack_conn_hdl.h"
#include "host_interface.h"
#include "controller_event_mask.h"
#include "controller_interface.h"

void ble_interface_init(void)
{
    // llp
    rom_llp_set_schedule_report_callback(rom_llc_on_schedule);
    rom_llp_set_fragment_start_report_callback(rom_llc_on_llp_fragment_start);
    rom_llp_set_fragment_stop_report_callback(rom_llc_on_llp_fragment_stop);
    rom_llp_set_tx_end_report_callback(rom_llc_on_llp_tx_end);
    rom_llp_set_rx_end_report_callback(rom_llc_on_llp_rx_end);
    rom_llp_set_rf_rx_calib_callback(rom_hal_rf_rx_dc_cal_offset_update);
    rom_llp_set_rf_tx_calib_callback(rom_hal_rf_set_modgain_cail_correction);

    // llc
    rom_llc_set_trig_schedule_report_callback(rom_llp_trig_schedule);
    rom_llc_set_timer_enable_callback(rom_llp_timer_enable);
    rom_llc_set_timer_get_count_callback(rom_llp_timer_get_count);
    rom_llc_set_llp_clock_accuracy_callback(rom_llp_get_clock_accuracy_ppm);
    rom_llc_set_start_adv_fragment_callback(rom_llp_start_adv_fragment);
    rom_llc_set_start_scan_fragment_callback(rom_llp_start_scan_fragment);
    rom_llc_set_start_init_fragment_callback(rom_llp_start_init_fragment);
    rom_llc_set_start_slave_fragment_callback(rom_llp_start_slave_fragment);
    rom_llc_set_start_master_fragment_callback(rom_llp_start_master_fragment);
    rom_llc_set_stop_fragment_callback(rom_llp_stop_fragment);
    rom_llc_set_update_tx_pdu_callback(rom_llp_update_tx_pdu);
    rom_llc_set_update_rx_pdu_callback(rom_llp_update_rx_pdu);
    rom_llc_set_get_rssi_callback(rom_llp_get_rssi);

    // hci
    rom_hci_set_get_event_paramter_max_length_callback(rom_host_interface_get_hci_event_parameter_max_length);
    rom_hci_set_host_send_command_packet_callback(rom_controller_interface_process_command_packet);
    rom_hci_set_host_send_acl_data_callback(rom_controller_interface_process_acl_data);
    rom_hci_set_controller_report_event_callback(rom_host_interface_process_event);
    rom_hci_set_controller_report_acl_data_callback(rom_host_interface_process_acl_data);

    rom_controller_event_mask_set_event_mask(0xFFFFFFFFFFFFFFFF);
    rom_controller_event_mask_set_le_event_mask(0xFFFFFFFFFFFFFFFF);
}
