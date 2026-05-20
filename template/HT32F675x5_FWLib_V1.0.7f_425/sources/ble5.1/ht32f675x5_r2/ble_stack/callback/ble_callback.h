/*************************************************************************************************************
 * @file    ble_callback.h
 * @version V1.0
 * @date    2021-05-21
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


#ifndef __BLE_CALLBACK_H__
#define __BLE_CALLBACK_H__

// include header here to avoid confusion
#include <stdint.h>
#include <stdbool.h>

typedef struct stack_msg
{
    uint16_t conn_handle;
    uint8_t  module_type;
    uint8_t  len_of_ext_info;
    void    *p_ext_info;
    void    *dataPoolId;
} stack_msg_st;

typedef bool (*func_task_set_signals)(uint8_t module_type, uint16_t conn_handle, uint8_t len, uint8_t *pdata);

typedef void (*func_ble_event)(uint32_t u32Cmd, const void *p, uint32_t u32Len);
typedef bool (*func_ble_timer_start)(void *pTimerHandle, uint32_t u32TimeOutMs, void *pContext);
typedef bool (*func_ble_timer_stop)(void *pTimerHandle);
typedef bool (*func_ble_timer_create)(void *pTimerHandle, void *pTimeOutHandler);
typedef bool (*func_ble_timer_delete)(void *pTimerHandle);

void ble_callback_send_event(uint32_t u32Cmd, const void *p, uint32_t u32Len);
bool ble_callback_send_msg_to_stack_task(uint8_t module_type, uint16_t conn_handle, uint8_t len, uint8_t *pdata);
bool ble_callback_timer_create(void *pTimerHandle, void *pTimeOutHandler);
bool ble_callback_timer_start(void *pTimerHandle, uint32_t u32TimeOutMs, void *pContext);
bool ble_callback_timer_stop(void *pTimerHandle);
bool ble_callback_timer_delete(void *pTimerHandle);
void ble_callback_set_send_msg_to_stack_task_callback(func_task_set_signals callback);
void ble_callback_set_host_stack_send_event_callback(func_ble_event callback);
void ble_callback_set_timer_create_callback(func_ble_timer_create callback);
void ble_callback_set_timer_start_callback(func_ble_timer_start callback);
void ble_callback_set_send_timer_stop_callback(func_ble_timer_stop callback);
void ble_callback_set_send_timer_delete_callback(func_ble_timer_delete callback);

extern func_task_set_signals g_taskSetSignalCallback;
extern func_ble_event        g_bleEventCallback;

extern func_ble_timer_start g_bleTimerStartCallback;
extern func_ble_timer_stop  g_bleTimerStopCallback;

#endif /* __BLE_CALLBACK_H__ */
