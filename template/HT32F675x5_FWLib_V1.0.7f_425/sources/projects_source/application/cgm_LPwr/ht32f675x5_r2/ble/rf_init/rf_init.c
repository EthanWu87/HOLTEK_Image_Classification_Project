/*************************************************************************************************************
 * @file    rf_init.c
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


#include <stdint.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_rf.h"
#include "hal_rf.h"
#include "app_cfg.h"

/**
 * @brief  rf init.
 */
EN_ERR_STA_T rf_init(void)
{
    EN_ERR_STA_T enRet;

    // rf init
    rom_hal_rf_cali_init();
    rom_hal_rf_tx_cali();

    enRet = rom_hal_rf_rx_cali();
    ERR_RETURN_IF_ERROR(enRet);

    rom_hal_rf_rx_dc_cal_sweep();
    rom_hal_rf_tx_power_table_init((uint8_t *)g_pu8TxGainDefaultTable);
    rom_hal_rf_tx_power_set(TX_0_DBM);
#if (SYSTEM_POWER_VOLTAGE == 110)
    rom_hw_rf_ldo_voltage ( EN_LDO_RF_1050mV );
#elif (SYSTEM_POWER_VOLTAGE == 115)
    rom_hw_rf_ldo_voltage ( EN_LDO_RF_1100mV );
#endif
    rom_hw_rf_tx_pa_h2_config(0x0B);

    return ERR_STA_OK;
}
