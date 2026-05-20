/*************************************************************************************************************
 * @file    hci_init.c
 * @version V1.0
 * @date    2023-05-27
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

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_pmu.h"
#include "hw_crg.h"
#include "hw_sys_ctrl.h"
#include "hal_rf.h"

#include "llc_llp_interface.h"
#include "llp_hw.h"
#include "llp_dtm.h"
#include "llp.h"
#include "llp_sleep.h"
#include "llc.h"
#include "llc_spec_5_1.h"
#include "llc_dtm.h"
#include "llc_address.h"

#include "controller_interface.h"

#include "ble_impl.h"

#include "hci.h"
#include "hci_transport_layer.h"
#include "hci_llc_scheduler.h"

#include "app_cfg.h"

#include "rf_init.h"

/**
 * @brief  GLOBAL FUNCTIONS.
 */
extern bool hci_controller_init(void);
extern void hci_interface_init(void);

/**
 * @brief  Link Layer Controller Interrupt Handler.
 */
void LLC_IRQ_Handler(void)
{
    patch_llp_hw_int_irq_handler();
}

int8_t hci_get_advertising_physical_channel_tx_power(void)
{
    return 0;
}

void llc_llp_interface_init(void)
{
    //llp
    rom_llp_set_schedule_report_callback(rom_llc_on_schedule);
    rom_llp_set_fragment_start_report_callback(rom_llc_on_llp_fragment_start);
    rom_llp_set_fragment_stop_report_callback(rom_llc_on_llp_fragment_stop);
    rom_llp_set_tx_end_report_callback(rom_llc_on_llp_tx_end);
    rom_llp_set_rx_end_report_callback(rom_llc_on_llp_rx_end);
    rom_llp_set_rf_rx_calib_callback(hal_rf_rx_dc_cal_offset_update);
    rom_llp_set_rf_tx_calib_callback(patch_hal_rf_set_modgain_cail_correction);
    

    //llc
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
}

void hci_interface_init(void)
{
    // hci
    rom_hci_set_get_event_paramter_max_length_callback(hci_transport_layer_get_event_parameter_max_length);
    patch_hci_set_controller_report_event_callback(hci_transport_layer_report_event);
    rom_hci_set_controller_report_acl_data_callback(hci_transport_layer_report_acl_data);

    // send command data callback was set in patch lib
    rom_hci_set_host_send_acl_data_callback(rom_controller_interface_process_acl_data);
}

EN_ERR_STA_T hci_init(void)
{
    // rf init
    if (ERR_STA_OK != rf_init())
    {
        return ERR_STA_ERROR;
    }
    rom_ble_impl_set_tx_power_range(-20, 10);
    rom_ble_impl_set_advertising_physical_channel_tx_power_callback(hci_get_advertising_physical_channel_tx_power);

    // llc interrupt init
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_CP, LLC_IRQ);
    NVIC_ClearPendingIRQ(LLC_IRQ);
    NVIC_SetPriority(LLC_IRQ, 0);
    NVIC_EnableIRQ(LLC_IRQ);

    // llc wakeup init
    rom_hw_pmu_set_wakeup_source(LUT_INDEX_CP_LLC, LUT_TRIG_ID_OTHER, LUT_TRIG_ID_LLC,
                                 LUT_ACT_PD_SYS_ON | LUT_ACT_DCXO_HCLK_ON | LUT_ACT_CP_IRQ_EN);

    // llc llp interface init
    llc_llp_interface_init();
    
    // controller init
    if (!hci_controller_init())
    {
        return ERR_STA_ERROR;
    }

    // patch ble init.
    patch_ble_init();

#if ((EXT_ADV_NUM) > 0) || (EXT_SCAN_ENABLE) || (EXT_INITIATOR_ENABLE)
    ble_extended_init();
#endif

    hci_llc_scheduler_init();

    // hci transport layer init
    hci_transport_layer_init();

    // hci interface init
    hci_interface_init();

    rom_ble_impl_set_consecutive_conn_events_with_rx_empty_pdu_to_use_latency(1);

    rom_ble_impl_set_command_filter_enable(true);

    //set address
    uint8_t pu8Address[6]={0xBC,0xC9,0xAE,0xE8,0x07,0xC0};//C0:07:E8:AE:C9:BC {0x88,0x66,0x66,0x66,3,0xba};
    rom_llc_address_set_public_address( pu8Address );

    hci_transport_layer_on_hci_ready();

    return ERR_STA_OK;
}

