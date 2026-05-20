/*************************************************************************************************************
 * @file    msg_queue.c
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

#include "app_cfg.h"
#include "msg_queue.h"




/**
 * @brief  Create queue.
 * @param  pstQueue: Pointer to the queue, @ref stQueueDef_t.
 * @param  pstQueueBuf: Pointer the buffer to save data.
 * @param  u32BufSize: Buffer size.
 * @param  u32MsgCount: Number of the messages.
 * @param  u32MsgSize: Size of the message.
 * @param  enMode: Write mode, @ref EN_QUEUE_MODE_T.
 * @return msgQueueId_t.
 */
pMsgQueueId_t msg_queue_create(stQueueDef_t *pstQueue, uint8_t *pstQueueBuf, uint32_t u32BufSize,
                               uint32_t u32MsgCount, uint32_t u32MsgSize, EN_QUEUE_MODE_T enMode)
{
    if ((NULL == pstQueue) || (NULL == pstQueueBuf) || \
        (0U == u32BufSize) || (0U == u32MsgCount) || (0U == u32MsgSize))
    {
        return NULL;
    }

    pstQueue->pu32Buffer          = pstQueueBuf;
    pstQueue->u32BlockSize        = u32MsgSize;
    pstQueue->u32MsgCount         = (u32MsgCount - 1);
    pstQueue->u32BufSize          = u32BufSize;
    pstQueue->pstCb.u8Front       = 0;
    pstQueue->pstCb.u8Back        = 0;
    pstQueue->pstCb.u8Utilization = 0;
    pstQueue->enMode              = enMode;

    return pstQueue;
}

/**
 * @brief  Get the next idx of the message queue.
 * @param  pstQueue: point to the queue, @ref stQueueDef_t.
 * @param  u8Idx: index.
 * @return index.
 */
static uint8_t msg_queue_next_idx(stQueueDef_t const *pstQueue, uint8_t u8Idx)
{
    if (NULL == pstQueue)
    {
        return QUEUE_ERR;
    }

    return (u8Idx < pstQueue->u32MsgCount) ? (u8Idx + 1) : 0;
}

/**
 * @brief  Determine if the message queue is full.
 * @param  pstQueue: point to the queue, @ref stQueueDef_t.
 * @return true or false.
 */
bool msg_queue_is_full(stQueueDef_t const *pstQueue)
{
    if (NULL == pstQueue)
    {
        return QUEUE_ERR;
    }

    uint8_t front = pstQueue->pstCb.u8Front;
    uint8_t back = pstQueue->pstCb.u8Back;

    return (msg_queue_next_idx(pstQueue, back) == front);
}

/**
 * @brief  Determine if the message queue is full.
 * @param  pstQueue: point to the queue, @ref stQueueDef_t.
 * @return true or false.
 */
bool msg_queue_is_empty(stQueueDef_t const *pstQueue)
{
    if (NULL == pstQueue)
    {
        return QUEUE_ERR;
    }

    uint8_t front = pstQueue->pstCb.u8Front;
    uint8_t back = pstQueue->pstCb.u8Back;

    return (front == back);
}

/**
 * @brief  Push a message in the message queue.
 * @param  pstQueue: point to the queue, @ref stQueueDef_t.
 * @param  pElement: Point to the element to be written.
 * @return queue state, @ref EN_QUEUE_ERR_STA_T.
 */
EN_QUEUE_ERR_STA_T msg_queue_push(stQueueDef_t *pstQueue, void const *pElement)
{
    if (NULL == pstQueue || NULL == pElement)
    {
        return QUEUE_ERR;
    }

    bool bIsFull = msg_queue_is_full(pstQueue);

    if (!bIsFull || (pstQueue->enMode == QUEUE_MODE_OVERFLOW))
    {
        // Get write position.
        uint8_t u8Pos = pstQueue->pstCb.u8Back;

        pstQueue->pstCb.u8Back = msg_queue_next_idx(pstQueue, pstQueue->pstCb.u8Back);

        if (bIsFull)
        {
            // Overwrite the oldest element.
            pstQueue->pstCb.u8Front = msg_queue_next_idx(pstQueue, pstQueue->pstCb.u8Front);
        }

        // Determining if there is a memory leak
        if ((u8Pos) * (pstQueue->u32BlockSize) > (pstQueue->u32BufSize))
        {
            return QUEUE_STA_ERR;
        }

        // Write a new element.
        memcpy((pstQueue->pu32Buffer + u8Pos * pstQueue->u32BlockSize), pElement, pstQueue->u32BlockSize);
    }
    else
    {
        return QUEUE_STA_BUSY;
    }

    return QUEUE_STA_OK;
}

/**
 * @brief  Pop up a message.
 * @param  pstQueue: point to the queue, @ref stQueueDef_t.
 * @param  pElement: Point to the element to be pop.
 * @return queue state, @ref EN_QUEUE_ERR_STA_T.
 */
EN_QUEUE_ERR_STA_T msg_queue_pop(stQueueDef_t *pstQueue, void *pElement)
{
    if (NULL == pstQueue || NULL == pElement)
    {
        return QUEUE_ERR;
    }

    if (!msg_queue_is_empty(pstQueue))
    {
        // Get read position.
        uint8_t u8Pos = pstQueue->pstCb.u8Front;

        // Update next read position.
        pstQueue->pstCb.u8Front = msg_queue_next_idx(pstQueue, pstQueue->pstCb.u8Front);

        // Read element.
        memcpy(pElement, (pstQueue->pu32Buffer + u8Pos * pstQueue->u32BlockSize), pstQueue->u32BlockSize);
    }
    else
    {
        return QUEUE_STA_ERR;
    }

    return QUEUE_STA_OK;
}

