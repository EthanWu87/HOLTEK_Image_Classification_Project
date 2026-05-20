/*************************************************************************************************************
 * @file    hci_cmd.c
 * @version V1.0
 * @date    2022-07-11
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
#include <string.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"

#include "utility.h"
#include "app_cfg.h"

#include "hci_struct.h"
#include "hci_dtm.h"
#include "hci_cmd.h"

/**
 * @brief  Hci cmd handler
 * @param  pu8Buf: payload data buffer
 * @param  u16PayloadLen: payload data buffer length
 * @param  pstEvent: event struct point
 */
static void hci_cmd_handler(uint16_t u16Opcode, uint8_t *pu8Buf, uint16_t u16PayloadLen, stEvent_t *pstEvent)
{
    uint16_t         opcode;
    stCmdStatusEvt_t stSta;

    opcode = pstEvent->unPar.stCmdSta.u16Opcode;
    memcpy(&stSta, &pstEvent->unPar.stCmdSta, sizeof(stCmdStatusEvt_t));

    switch (opcode)
    {
        case HCI_HT32_READ_REG:
        {
            uint32_t regVal;
            uint32_t regAddr;

            regAddr = BUILD_UINT32(pu8Buf[0], pu8Buf[1], pu8Buf[2], pu8Buf[3]);

            if ((regAddr < ADDR_LLC_CFG_BASE) || (regAddr >= ADDR_END))
            {
                stSta.u8Status = ERR_PARA_ERR;
            }
            else
            {
                regVal = *((volatile uint32_t *)regAddr);
                memcpy(&stSta.u8Para, &regVal, sizeof(regVal));
                PRINTF("[R]: 0x%08X = 0x%08X\n", regAddr, regVal);
            }
            break;
        }
        case HCI_HT32_WRITE_REG:
        {
            uint32_t regVal;
            uint32_t regAddr;

            regAddr = BUILD_UINT32(pu8Buf[0], pu8Buf[1], pu8Buf[2], pu8Buf[3]);
            regVal  = BUILD_UINT32(pu8Buf[4], pu8Buf[5], pu8Buf[6], pu8Buf[7]);

            PRINTF("[W]: 0x%08X = 0x%08X\n", regAddr, regVal);

            if ((regAddr < ADDR_LLC_CFG_BASE) || (regAddr >= ADDR_END))
            {
                stSta.u8Status = ERR_PARA_ERR;
            }
            else
            {
                *((volatile uint32_t *)regAddr) = regVal;
            }
            break;
        }
        case HCI_EXT_SM_TEST:
        {
#if defined(SIG_PTS_TEST)
            extern void hci_sd_controller_sm_test_command_handle(uint8_t * params, uint16_t len);
            hci_sd_controller_sm_test_command_handle(pu8Buf, u16PayloadLen);
#endif
            break;
        }
        default: break;
    }

    memcpy(&pstEvent->unPar.stCmdSta, &stSta, sizeof(stCmdStatusEvt_t));
}

/**
 * @brief  Hci cmd dispatch
 * @param  u16Opcode: op code.
 * @param  pu8Buf: payload data buffer
 * @param  u16PayloadLen: payload data buffer length
 * @param  pstEvent: event struct point
 */
void hci_cmd_dispatch(uint16_t u16Opcode, uint8_t *pu8Buf, uint16_t u16PayloadLen, stEvent_t *pstEvent)
{
    uint16_t cmdType;

    cmdType = u16Opcode & (0x3F << 10);

    switch (cmdType)
    {
        case HC_G:
        case LE_G:
        {
            hci_dtm_cmd_handler(u16Opcode, pu8Buf, u16PayloadLen, pstEvent);
            break;
        }
        case E_G:
        {
            hci_cmd_handler(u16Opcode, pu8Buf, u16PayloadLen, pstEvent);
            break;
        }
        default: break;
    }
}
