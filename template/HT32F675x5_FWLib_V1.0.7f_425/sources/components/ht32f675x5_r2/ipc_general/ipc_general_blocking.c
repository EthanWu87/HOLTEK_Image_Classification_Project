/*************************************************************************************************************
 * @file    ipc_general_blocking.c
 * @version V1.0
 * @date    2022-12-27
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
#include <stdio.h>
#include <string.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_sys_ctrl.h"

#include "app_cfg.h"
#include "utility.h"

#include "ipc_general_blocking.h"

/**
 * @brief  DEFINE
 */
#if defined(__MAIN_PROCESSOR)
    #define SYS_CTRL_HANDLE    (SYS_CTRL_MP)
    #define IPC_SW_INT_CH      (SW_IRQ1)
    #define IPC_SW_IRQ_HANDLER SW_IRQ1_Handler
#elif defined(__CO_PROCESSOR)
    #define SYS_CTRL_HANDLE    (SYS_CTRL_CP)
    #define IPC_SW_INT_CH      (SW_IRQ0)
    #define IPC_SW_IRQ_HANDLER SW_IRQ0_Handler
#else
    #error "core unset"
#endif

#define IPC_SEND_TIMEOUT_MS (100)

/**
 * @brief  Local variables.
 */
static uint8_t *m_pu8RxDataBuf;
static uint8_t *m_pu8TxDataBuf;
static uint32_t m_u32TxDataBufLen;
static uint32_t m_u32DataLen;

/* Receive Task Callback Function */
static ipc_rx_msg_cb_func m_pfnIpcRxCbFunc;

/**
 * @brief  Trigger a software interrupt.
 */
static void ipc_general_trig_int(void)
{
#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_trigger_sw_int(SYS_CTRL_CP, SYS_CTRL_SW_INT_BIT0);
#else
    rom_hw_sys_ctrl_trigger_sw_int(SYS_CTRL_MP, SYS_CTRL_SW_INT_BIT1);
#endif
}

/**
 * @brief  Check IPC Receive Buffer ID.
 */
static void ipc_general_get_rx_data_buffer_id(void)
{
    uint32_t u32Id = 0;

#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_IPC_ID_SLAVE, &u32Id);
#else
    rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_IPC_ID_MASTER, &u32Id);
#endif

    m_pu8RxDataBuf = (uint8_t *)u32Id;
}

/**
 * @brief  IPC Receive Data.
 */
static void ipc_general_receive_handler(void)
{
    uint8_t  u8LockId        = 0;
    uint8_t  u8LockRcvStatus = 0;
    uint32_t u32RcvStatus    = 0;

#if defined(__MAIN_PROCESSOR)
    u8LockId        = SYS_CTRL_LOCK_ID_IPC_SLAVE;
    u8LockRcvStatus = SYS_CTRL_LOCK_ID_RECEIVE_STATUS_SLAVE;
#else
    u8LockId        = SYS_CTRL_LOCK_ID_IPC_MASTER;
    u8LockRcvStatus = SYS_CTRL_LOCK_ID_RECEIVE_STATUS_MASTER;
#endif

    while (1)
    {
        ipc_general_get_rx_data_buffer_id();

        if (NULL == m_pu8RxDataBuf)
        {
            PRINTF("Error, the rx data buffer is NULL.\n");
            return;
        }

        if (ERR_STA_OK == rom_hw_sys_ctrl_lock_device(u8LockId))
        {
            m_u32DataLen = BUILD_UINT32(m_pu8RxDataBuf[0], m_pu8RxDataBuf[1], m_pu8RxDataBuf[2], m_pu8RxDataBuf[3]);

            if (NULL != m_pfnIpcRxCbFunc)
            {

                u32RcvStatus = m_pfnIpcRxCbFunc(&m_pu8RxDataBuf[4], m_u32DataLen);
                while (1)
                {
                    if (ERR_STA_OK == rom_hw_sys_ctrl_lock_device(u8LockRcvStatus))
                    {
#if defined(__MAIN_PROCESSOR)
                        rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_SLAVE,
                                                      (uint32_t)u32RcvStatus);
#else
                        rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_MASTER,
                                                      (uint32_t)u32RcvStatus);
#endif

                        rom_hw_sys_ctrl_release_device(u8LockRcvStatus);
                        break;
                    }
                    rom_delay_us(1); // This delay is necessary. If no delay is added here, it will result in an error.
                };
            }

            rom_hw_sys_ctrl_release_device(u8LockId);
            break;
        }

        /* After proc a msg, yield */
        rom_delay_us(1);

    }; /* Loop until no msg exist */
}

/**
 * @brief  IPC SW interrupt IRQ handler.
 */
__RAM_FUNC void IPC_SW_IRQ_HANDLER(void)
{
    uint8_t intFlag = 0;

    rom_hw_sys_ctrl_get_sw_int_flag(SYS_CTRL_HANDLE, &intFlag);
    rom_hw_sys_ctrl_clear_sw_int_flag(SYS_CTRL_HANDLE, intFlag);

    if (intFlag)
    {
        ipc_general_receive_handler();
    }
}

/**
 * @brief  General ipc Initialization.
 * @param  pu8DataBuf: the buffer to save data.
 * @param  u32BufMaxLen: the buffersize to save data.
 * @param  pfnCallback: Callback functions.
 * @return status: @ref EN_ERR_STA_T.
 */
EN_ERR_STA_T ipc_general_init(uint8_t *pu8DataBuf, uint32_t u32BufMaxLen, ipc_rx_msg_cb_func pfnCallback)
{
    if (NULL == pu8DataBuf)
    {
        return ERR_PARA_ERR;
    }

    if ((NULL != pu8DataBuf) && (0 == u32BufMaxLen))
    {
        return ERR_PARA_ERR;
    }

    m_pu8TxDataBuf    = pu8DataBuf;
    m_u32TxDataBufLen = u32BufMaxLen;
    m_pfnIpcRxCbFunc  = pfnCallback;

#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_release_device(SYS_CTRL_LOCK_ID_IPC_MASTER);
    rom_hw_sys_ctrl_release_device(SYS_CTRL_LOCK_ID_RECEIVE_STATUS_MASTER);
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_ID_MASTER, (uint32_t)m_pu8TxDataBuf);
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_MASTER, 0xFFFFFFFF);
#else
    rom_hw_sys_ctrl_release_device(SYS_CTRL_LOCK_ID_IPC_SLAVE);
    rom_hw_sys_ctrl_release_device(SYS_CTRL_LOCK_ID_RECEIVE_STATUS_SLAVE);
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_ID_SLAVE, (uint32_t)m_pu8TxDataBuf);
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_SLAVE, 0xFFFFFFFF);
#endif

    // SW int initialization.
    NVIC_ClearPendingIRQ(IPC_SW_INT_CH);
    NVIC_SetPriority(IPC_SW_INT_CH, 3);
    NVIC_EnableIRQ(IPC_SW_INT_CH);
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_HANDLE, IPC_SW_INT_CH);

    return ERR_STA_OK;
}

/**
 * @brief  Send ipc message by blocking. This API can be called from Interrupt Service Routines (ISR).
 * @param  pu8Data: Pointer to the data buffer which will be sent.
 * @param  u32DataLen: Data length.
 * @return status: @ref EN_ERR_STA_T.
 */
uint32_t ipc_general_send_msg_blocking(uint8_t *pu8Data, uint32_t u32DataLen)
{
    uint8_t  u8Timeout       = 0;
    uint8_t  u8IntFlag       = 0;
    uint8_t  u8LockId        = 0;
    uint8_t  u8LockRcvStatus = 0;
    uint32_t u32MsgRcvStatus = 0;

    if (NULL == pu8Data)
    {
        return ERR_PARA_ERR;
    }

    if ((NULL == pu8Data) && (0 != u32DataLen))
    {
        return ERR_PARA_ERR;
    }

    if (u32DataLen > (m_u32TxDataBufLen - 4))
    {
        return ERR_PARA_ERR;
    }

#if defined(__MAIN_PROCESSOR)
    u8LockId        = SYS_CTRL_LOCK_ID_IPC_MASTER;
    u8LockRcvStatus = SYS_CTRL_LOCK_ID_RECEIVE_STATUS_MASTER;
#else
    u8LockId        = SYS_CTRL_LOCK_ID_IPC_SLAVE;
    u8LockRcvStatus = SYS_CTRL_LOCK_ID_RECEIVE_STATUS_SLAVE;
#endif

    if (rom_hw_sys_ctrl_lock_device(u8LockId))
    {
        return ERR_STA_BUSY;
    }

    m_pu8TxDataBuf[0] = BREAK_UINT32(u32DataLen, 0);
    m_pu8TxDataBuf[1] = BREAK_UINT32(u32DataLen, 1);
    m_pu8TxDataBuf[2] = BREAK_UINT32(u32DataLen, 2);
    m_pu8TxDataBuf[3] = BREAK_UINT32(u32DataLen, 3);

    memcpy(&m_pu8TxDataBuf[4], pu8Data, u32DataLen);

    rom_hw_sys_ctrl_release_device(u8LockId);
    ipc_general_trig_int();

    while (1)
    {
        if (ERR_STA_OK == rom_hw_sys_ctrl_lock_device(u8LockRcvStatus))
        {
#if defined(__MAIN_PROCESSOR)
            rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_MASTER, &u32MsgRcvStatus);
#else
            rom_hw_sys_ctrl_read_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_SLAVE, &u32MsgRcvStatus);
#endif

            if ((u32MsgRcvStatus == 0xFFFFEEEE) || (u32MsgRcvStatus == 0xFFFFFFFF))
            {
                rom_hw_sys_ctrl_release_device(u8LockRcvStatus);
            }
            else
            {
                break;
            }
        }
        rom_delay_ms(1); // This delay is necessary. If no delay is added here, it will result in an error.

        u8Timeout++;
        if (u8Timeout > IPC_SEND_TIMEOUT_MS)
        {
#if defined(__MAIN_PROCESSOR)
            rom_hw_sys_ctrl_get_sw_int_flag(SYS_CTRL_CP, &u8IntFlag);
            rom_hw_sys_ctrl_clear_sw_int_flag(SYS_CTRL_CP, u8IntFlag);
#else
            rom_hw_sys_ctrl_get_sw_int_flag(SYS_CTRL_MP, &u8IntFlag);
            rom_hw_sys_ctrl_clear_sw_int_flag(SYS_CTRL_MP, u8IntFlag);
#endif

            PRINTF("The operation timed out!\n");
            return ERR_STA_TIMEOUT;
        }
    }

#if defined(__MAIN_PROCESSOR)
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_MASTER, 0XFFFFEEEE);
#else
    rom_hw_sys_ctrl_write_com_reg(SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_SLAVE, 0XFFFFEEEE);
#endif

    rom_hw_sys_ctrl_release_device(u8LockRcvStatus);

    return u32MsgRcvStatus;
}
