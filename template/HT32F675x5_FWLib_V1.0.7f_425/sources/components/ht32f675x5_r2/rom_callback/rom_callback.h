/*************************************************************************************************************
 * @file    rom_callback.h
 * @version V1.0
 * @date    2021-05-27
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


#ifndef __ROM_CALLBACK_H__
#define __ROM_CALLBACK_H__

/**
 * @brief  BLE callback id.
 */
typedef enum
{
    SYS_ERR_MODULE_LLP = 0x0000,
    SYS_ERR_MODULE_LLP_ADV,
    SYS_ERR_MODULE_LLP_SCAN,
    SYS_ERR_MODULE_LLP_INITIATOR,
    SYS_ERR_MODULE_LLP_SLAVE,
    SYS_ERR_MODULE_LLP_MASTER,
    SYS_ERR_MODULE_LLC_SCHEDULER,
    SYS_ERR_MODULE_LLC_ACL_DATA,
    SYS_ERR_MODULE_LLC_CHANNEL_SELECTION_ALGORITHM,
    SYS_ERR_MODULE_LLC_LEGACY_ADV,
    SYS_ERR_MODULE_LLC_LEGACY_ADV_ADV_IND,
    SYS_ERR_MODULE_LLC_LEGACY_ADV_ADV_DIRECT_IND,
    SYS_ERR_MODULE_LLC_LEGACY_ADV_ADV_NONCONN_IND,
    SYS_ERR_MODULE_LLC_LEGACY_ADV_ADV_SCAN_IND,
    SYS_ERR_MODULE_LLC_LEGACY_SCAN,
    SYS_ERR_MODULE_LLC_LEGACY_INITIATOR,
    SYS_ERR_MODULE_LLC_CONNECTION_ROLE,
    SYS_ERR_MODULE_LLC_SLAVE,
    SYS_ERR_MODULE_LLC_MASTER,
    SYS_ERR_MODULE_LLC_DATA,
    SYS_ERR_MODULE_LLC_CTRL_PROCEDURE,
    SYS_ERR_MODULE_LLC_CONNECTION_UPDATE_PROCEDURE,
    SYS_ERR_MODULE_LLC_FEATURE_EXCHANGE_PROCEDURE,
    SYS_ERR_MODULE_LLC_VERSION_EXCHANGE_PROCEDURE,
    SYS_ERR_MODULE_LLC_CHANNEL_MAP_UPDATE_PROCEDURE,
    SYS_ERR_MODULE_LLC_ENCRYPTION_PROCEDURE,
    SYS_ERR_MODULE_LLC_DATA_LENGTH_UPDATE_PROCEDURE,
    SYS_ERR_MODULE_LLC_PHY_UPDATE_PROCEDURE,
    SYS_ERR_MODULE_LLC_PRIORITY,
    SYS_ERR_MODULE_LLP_EXT_ADV,
    SYS_ERR_MODULE_LLC_EXT_ADV,
    SYS_ERR_MODULE_LLC_EXT_ADV_LEGACY_PDU_MANAGER,
    SYS_ERR_MODULE_LLC_EXT_ADV_LEGACY_STATE_MACHINE,
    SYS_ERR_MODULE_LLC_EXT_ADV_PDU_MANAGER,
    SYS_ERR_MODULE_LLC_EXT_ADV_STATE_MACHINE,
    SYS_ERR_MODULE_LLP_EXT_SCAN,
    SYS_ERR_MODULE_LLC_EXT_SCAN_STATE_MACHINE,
    SYS_ERR_MODULE_LLC_EXT_SCAN_PRIMARY_SCANNING,
    SYS_ERR_MODULE_LLC_EXT_SCAN_SECONDARY_SCANNING,
    SYS_ERR_MODULE_LLP_EXT_INITIATOR,
    SYS_ERR_MODULE_LLC_EXT_INITIATOR_STATE_MACHINE,
    SYS_ERR_MODULE_LLC_EXT_INITIATOR_PRIMARY_SCANNING,
    SYS_ERR_MODULE_LLC_EXT_INITIATOR_SECONDARY_SCANNING,

    SYS_ERR_MODULE_HOST_STACK_MEM = 0X100,
    SYS_ERR_MODULE_SM,
    SYS_ERR_MODULE_ATT_DB,
    SYS_ERR_MODULE_ATT_SERVER,
    SYS_ERR_MODULE_ATT_DB_UTIL,
    SYS_ERR_MODULE_GATTS_API,
    SYS_ERR_MODULE_GATT_CLIENT,
    SYS_ERR_MODULE_L2CAP_SIGNALING,
    SYS_ERR_MODULE_STACK_TASK,
    SYS_ERR_MODULE_HOST_STACK_CONN_HDL,

} EN_SYS_ERR_MODULE_T;

/**
 * @brief  FUNCTION CALLBACK TYPEDEF
 */
typedef void (*func_lib_assert)(uint16_t u16Addr, uint32_t u32Info);
typedef void (*func_lib_idle_task)(void);
typedef uint32_t (*func_lib_os_error)(uint32_t u32Code, void *pObjectId);
typedef void (*func_lib_system_error)(uint16_t u16ErrModule, uint16_t u16ErrLine, uint32_t u32ErrInfo1,
                                      uint32_t u32ErrInfo2);

/**
 * @brief  EXTERN FUNCTION CALLBACK
 */
extern func_lib_assert       g_libAssertCallback;
extern func_lib_idle_task    g_libIdleTaskCallback;
extern func_lib_os_error     g_libOsErrorCallback;
extern func_lib_system_error g_libSystemErrorCallback;

/**
 * @brief  System assert.
 */
void system_assert(uint16_t u16Addr, bool bCondition, uint32_t u32Info);

/**
 * @brief  System error.
 */
void system_error(uint16_t u16ErrModule, uint16_t u16ErrLine, uint32_t u32ErrInfo1, uint32_t u32ErrInfo2);

/**
 * @brief  Idle task processor callback for cp and mp.
 */
extern void idle_task_processor(void);

/**
 * @brief  os error processor callback for cp and mp.
 */
extern uint8_t os_error_processor(uint32_t u32Code, void *pObjectId);

#endif /* __ROM_CALLBACK_H__ */
