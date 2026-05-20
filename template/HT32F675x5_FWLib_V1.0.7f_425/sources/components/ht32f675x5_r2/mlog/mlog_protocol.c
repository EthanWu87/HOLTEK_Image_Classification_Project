/*************************************************************************************************************
 * @file    mlog_protocol.c
 * @version V1.0
 * @date    2023-07-11
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

#include "RegHT32F675x5.h"

#include "mlog.h"
#include "mlog_protocol.h"

void mlog_protocol_0(uint16_t u16LogId);

void mlog_protocol_16(uint16_t u16LogId, uint16_t u16Param1);
void mlog_protocol_32(uint16_t u16LogId, uint32_t u32Param1);
void mlog_protocol_64(uint16_t u16LogId, uint64_t u64Param1);

void mlog_protocol_88(uint16_t u16LogId, uint8_t u8Param1, uint8_t u8Param2);
void mlog_protocol_1616(uint16_t u16LogId, uint16_t u16Param1, uint16_t u16Param2);
void mlog_protocol_3216(uint16_t u16LogId, uint32_t u32Param1, uint16_t u16Param2);
void mlog_protocol_3232(uint16_t u16LogId, uint32_t u32Param1, uint32_t u32Param2);

void mlog_protocol_1688(uint16_t u16LogId, uint16_t u16Param1, uint8_t u8Param2, uint8_t u8Param3);
void mlog_protocol_161616(uint16_t u16LogId, uint16_t u16Param1, uint16_t u16Param2, uint16_t u16Param3);
void mlog_protocol_3288(uint16_t u16LogId, uint32_t u32Param1, uint8_t u8Param2, uint8_t u8Param3);
void mlog_protocol_321616(uint16_t u16LogId, uint32_t u32Param1, uint16_t u16Param2, uint16_t u16Param3);

void mlog_protocol_x(uint16_t u16LogId, uint8_t *pu8Data, uint8_t u8DataSize);

callback_mlog_protocol_print g_mlogBackendCallbackPrint = NULL;

////todo : use 32-bit based protocol to improve performance
////8-bit based buffer is impl-friendly
uint8_t g_pu8MlogProtocolBuffer[MLOG_PROTOCOL_BUFFER_SIZE] __attribute__((aligned(4)));

volatile uint16_t g_u16WriteIndex = 0;
volatile uint16_t g_u16ReadIndex  = 0;

void mlog_protocol_print_callback_register(callback_mlog_protocol_print callback)
{
    g_mlogBackendCallbackPrint = callback;

    g_mlogCallback0 = mlog_protocol_0;

    g_mlogCallback16 = mlog_protocol_16;
    g_mlogCallback32 = mlog_protocol_32;
    g_mlogCallback64 = mlog_protocol_64;

    g_mlogCallback88   = mlog_protocol_88;
    g_mlogCallback1616 = mlog_protocol_1616;
    g_mlogCallback3216 = mlog_protocol_3216;
    g_mlogCallback3232 = mlog_protocol_3232;

    g_mlogCallback1688   = mlog_protocol_1688;
    g_mlogCallback161616 = mlog_protocol_161616;
    g_mlogCallback3288   = mlog_protocol_3288;
    g_mlogCallback321616 = mlog_protocol_321616;

    g_mlogCallbackX = mlog_protocol_x;
}

void mlog_protocol_print(void)
{
    if (NULL == g_mlogBackendCallbackPrint)
    {
        return;
    }

    // reentry RISK

    uint16_t u16ReadIdx  = g_u16ReadIndex;
    uint16_t u16WriteIdx = g_u16WriteIndex;
    if (u16ReadIdx == u16WriteIdx)
    {
        return;
    }
    g_u16ReadIndex = u16WriteIdx;

    if (u16WriteIdx > u16ReadIdx)
    {
        g_mlogBackendCallbackPrint(&g_pu8MlogProtocolBuffer[u16ReadIdx], u16WriteIdx - u16ReadIdx);
    }
    else
    {
        g_mlogBackendCallbackPrint(&g_pu8MlogProtocolBuffer[u16ReadIdx], sizeof(g_pu8MlogProtocolBuffer) - u16ReadIdx);
        g_mlogBackendCallbackPrint(&g_pu8MlogProtocolBuffer[0], u16WriteIdx);
    }
}

static bool mlog_request_write(uint16_t u16RequestSize, uint16_t *pu16WriteIndex)
{
    // reentry-able design
    uint32_t u32Primask = __get_PRIMASK();
    __disable_irq();
    uint16_t u16ReadIdx  = g_u16ReadIndex;
    uint16_t u16WriteIdx = g_u16WriteIndex;

    // check
    uint16_t u16LeftLength;
    if (u16WriteIdx >= u16ReadIdx)
    {
        u16LeftLength = sizeof(g_pu8MlogProtocolBuffer) - (u16WriteIdx - u16ReadIdx) - 1;
    }
    else
    {
        u16LeftLength = u16ReadIdx - u16WriteIdx - 1;
    }

    if (u16LeftLength < u16RequestSize) // prefix + length + logid + param
    {
        /// log lost
        __set_PRIMASK(u32Primask);
        return false;
    }

    g_u16WriteIndex += u16RequestSize;
    if (g_u16WriteIndex >= sizeof(g_pu8MlogProtocolBuffer))
    {
        g_u16WriteIndex -= sizeof(g_pu8MlogProtocolBuffer);
    }
    *pu16WriteIndex = u16WriteIdx;
    __set_PRIMASK(u32Primask);
    return true;
}

static void mlog_write(uint16_t u16WriteIndex, uint8_t *pu8Buffer, uint16_t u16WriteLength)
{
    uint16_t u16RemainSize = sizeof(g_pu8MlogProtocolBuffer) - u16WriteIndex;
    if (u16RemainSize >= u16WriteLength)
    {
        memcpy(&g_pu8MlogProtocolBuffer[u16WriteIndex], pu8Buffer, u16WriteLength);
    }
    else
    {
        memcpy(&g_pu8MlogProtocolBuffer[u16WriteIndex], pu8Buffer, u16RemainSize);
        memcpy(&g_pu8MlogProtocolBuffer[0], &pu8Buffer[u16RemainSize], u16WriteLength - u16RemainSize);
    }
}

void mlog_protocol_0(uint16_t u16LogId)
{
    uint8_t pu8Buffer[6];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    pu8Buffer[4] = 0;
    pu8Buffer[5] = 0;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_16(uint16_t u16LogId, uint16_t u16Param1)
{
    uint8_t pu8Buffer[6];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    pu8Buffer[4] = (u16Param1 >> 8) & 0xFF;
    pu8Buffer[5] = u16Param1 & 0xFF;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_32(uint16_t u16LogId, uint32_t u32Param1)
{
    uint8_t pu8Buffer[8];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    pu8Buffer[4] = (u32Param1 >> 24) & 0xFF;
    pu8Buffer[5] = (u32Param1 >> 16) & 0xFF;
    pu8Buffer[6] = (u32Param1 >> 8) & 0xFF;
    pu8Buffer[7] = (u32Param1 >> 0) & 0xFF;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_64(uint16_t u16LogId, uint64_t u64Param1)
{
    ////todo : impl mlog
}

void mlog_protocol_88(uint16_t u16LogId, uint8_t u8Param1, uint8_t u8Param2)
{
    uint8_t pu8Buffer[6];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    pu8Buffer[4] = u8Param1;
    pu8Buffer[5] = u8Param2;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_1616(uint16_t u16LogId, uint16_t u16Param1, uint16_t u16Param2)
{
    uint8_t pu8Buffer[8];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    pu8Buffer[4] = (u16Param1 >> 8) & 0xFF;
    pu8Buffer[5] = (u16Param1 >> 0) & 0xFF;
    pu8Buffer[6] = (u16Param2 >> 8) & 0xFF;
    pu8Buffer[7] = (u16Param2 >> 0) & 0xFF;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_3216(uint16_t u16LogId, uint32_t u32Param1, uint16_t u16Param2)
{
    uint8_t pu8Buffer[10];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    pu8Buffer[4] = (u32Param1 >> 24) & 0xFF;
    pu8Buffer[5] = (u32Param1 >> 16) & 0xFF;
    pu8Buffer[6] = (u32Param1 >> 8) & 0xFF;
    pu8Buffer[7] = (u32Param1 >> 0) & 0xFF;
    pu8Buffer[8] = (u16Param2 >> 8) & 0xFF;
    pu8Buffer[9] = (u16Param2 >> 0) & 0xFF;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_3232(uint16_t u16LogId, uint32_t u32Param1, uint32_t u32Param2)
{
    uint8_t pu8Buffer[12];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0]  = 0xFE;
    pu8Buffer[1]  = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2]  = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3]  = u16LogId & 0xFF;
    pu8Buffer[4]  = (u32Param1 >> 24) & 0xFF;
    pu8Buffer[5]  = (u32Param1 >> 16) & 0xFF;
    pu8Buffer[6]  = (u32Param1 >> 8) & 0xFF;
    pu8Buffer[7]  = (u32Param1 >> 0) & 0xFF;
    pu8Buffer[8]  = (u32Param2 >> 24) & 0xFF;
    pu8Buffer[9]  = (u32Param2 >> 16) & 0xFF;
    pu8Buffer[10] = (u32Param2 >> 8) & 0xFF;
    pu8Buffer[11] = (u32Param2 >> 0) & 0xFF;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_1688(uint16_t u16LogId, uint16_t u16Param1, uint8_t u8Param2, uint8_t u8Param3)
{
    uint8_t pu8Buffer[8];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    pu8Buffer[4] = (u16Param1 >> 8) & 0xFF;
    pu8Buffer[5] = (u16Param1 >> 0) & 0xFF;
    pu8Buffer[6] = u8Param2;
    pu8Buffer[7] = u8Param3;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_161616(uint16_t u16LogId, uint16_t u16Param1, uint16_t u16Param2, uint16_t u16Param3)
{
    uint8_t pu8Buffer[10];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    pu8Buffer[4] = (u16Param1 >> 8) & 0xFF;
    pu8Buffer[5] = (u16Param1 >> 0) & 0xFF;
    pu8Buffer[6] = (u16Param2 >> 8) & 0xFF;
    pu8Buffer[7] = (u16Param2 >> 0) & 0xFF;
    pu8Buffer[8] = (u16Param3 >> 8) & 0xFF;
    pu8Buffer[9] = (u16Param3 >> 0) & 0xFF;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_3288(uint16_t u16LogId, uint32_t u32Param1, uint8_t u8Param2, uint8_t u8Param3)
{
    uint8_t pu8Buffer[10];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    pu8Buffer[4] = (u32Param1 >> 24) & 0xFF;
    pu8Buffer[5] = (u32Param1 >> 16) & 0xFF;
    pu8Buffer[6] = (u32Param1 >> 8) & 0xFF;
    pu8Buffer[7] = (u32Param1 >> 0) & 0xFF;
    pu8Buffer[8] = u8Param2;
    pu8Buffer[9] = u8Param3;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_321616(uint16_t u16LogId, uint32_t u32Param1, uint16_t u16Param2, uint16_t u16Param3)
{
    uint8_t pu8Buffer[12];

    uint16_t u16WriteIndex;
    if (!mlog_request_write(sizeof(pu8Buffer), &u16WriteIndex))
    {
        return;
    }

    // mlog v3.0 protocol
    pu8Buffer[0]  = 0xFE;
    pu8Buffer[1]  = 0xC0 | (sizeof(pu8Buffer));
    pu8Buffer[2]  = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3]  = u16LogId & 0xFF;
    pu8Buffer[4]  = (u32Param1 >> 24) & 0xFF;
    pu8Buffer[5]  = (u32Param1 >> 16) & 0xFF;
    pu8Buffer[6]  = (u32Param1 >> 8) & 0xFF;
    pu8Buffer[7]  = (u32Param1 >> 0) & 0xFF;
    pu8Buffer[8]  = (u16Param2 >> 8) & 0xFF;
    pu8Buffer[9]  = (u16Param2 >> 0) & 0xFF;
    pu8Buffer[10] = (u16Param3 >> 8) & 0xFF;
    pu8Buffer[11] = (u16Param3 >> 0) & 0xFF;

    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));
}

void mlog_protocol_x(uint16_t u16LogId, uint8_t *pu8Data, uint8_t u8DataSize)
{
    if (u8DataSize > 20)
    {
        u8DataSize = 20;
    }

    uint16_t u16TotalSize = 4 + (u8DataSize + 1) / 2 * 2;

    uint16_t u16WriteIndex;
    if (!mlog_request_write(u16TotalSize, &u16WriteIndex))
    {
        return;
    }
    // mlog v3.0 protocol
    uint8_t pu8Buffer[4];
    pu8Buffer[0] = 0xFE;
    pu8Buffer[1] = 0xC0 | (u16TotalSize);
    pu8Buffer[2] = (u16LogId >> 8) & 0xFF;
    pu8Buffer[3] = u16LogId & 0xFF;
    mlog_write(u16WriteIndex, pu8Buffer, sizeof(pu8Buffer));

    u16WriteIndex += 4;
    if (u16WriteIndex >= sizeof(g_pu8MlogProtocolBuffer))
    {
        u16WriteIndex -= sizeof(g_pu8MlogProtocolBuffer);
    }

    mlog_write(u16WriteIndex, pu8Data, u8DataSize);
}
