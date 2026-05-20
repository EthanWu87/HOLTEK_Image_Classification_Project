/*************************************************************************************************************
 * @file    msg_queue.h
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


#ifndef __MSG_QUEUE_H__
#define __MSG_QUEUE_H__


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef void *pMsgQueueId_t;


typedef enum
{
    QUEUE_MODE_OVERFLOW,       //!< If the queue is full, new element will overwrite the oldest.
    QUEUE_MODE_NO_OVERFLOW,    //!< If the queue is full, new element will not be accepted.
    QUEUE_MODE_NONE

} EN_QUEUE_MODE_T;

typedef enum
{
    QUEUE_ERR_NONE,
    QUEUE_ERR,
    QUEUE_STA_OK,
    QUEUE_STA_ERR,
    QUEUE_STA_BUSY,

} EN_QUEUE_ERR_STA_T;

typedef struct
{
    uint8_t u8Front;          //!< Queue front index.
    uint8_t u8Back;           //!< Queue back index.
    uint8_t u8Utilization;    //!< utilization of the queue.

} stQueueCb_t;


typedef struct
{
    stQueueCb_t     pstCb;           //!< Pointer to the instance control block.
    uint8_t        *pu32Buffer;      //!< Pointer to the memory that is used as storage.
    uint32_t        u32BufSize;      //!< Size of the queue.
    uint32_t        u32MsgCount;
    uint32_t        u32BlockSize;    //!< Size of one element.
    EN_QUEUE_MODE_T enMode;          //!< Mode of the queue.

} stQueueDef_t;




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
extern pMsgQueueId_t msg_queue_create(stQueueDef_t *pstQueue, uint8_t *pstQueueBuf, uint32_t u32BufSize,
                                      uint32_t u32MsgCount, uint32_t u32MsgSize, EN_QUEUE_MODE_T enMode);


/**
 * @brief  Determine if the message queue is full.
 * @param  pstQueue: point to the queue, @ref stQueueDef_t.
 * @return true or false.
 */
extern bool msg_queue_is_full(stQueueDef_t const *pstQueue);


/**
 * @brief  Determine if the message queue is full.
 * @param  pstQueue: point to the queue, @ref stQueueDef_t.
 * @return true or false.
 */
extern bool msg_queue_is_empty(stQueueDef_t const *pstQueue);


/**
 * @brief  Push a message in the message queue.
 * @param  pstQueue: point to the queue, @ref stQueueDef_t.
 * @param  pElement: Point to the element to be written.
 * @return queue state, @ref EN_QUEUE_ERR_STA_T.
 */
extern EN_QUEUE_ERR_STA_T msg_queue_push(stQueueDef_t *pstQueue, void const *pElement);


/**
 * @brief  Pop up a message.
 * @param  pstQueue: point to the queue, @ref stQueueDef_t.
 * @param  pElement: Point to the element to be pop.
 * @return queue state, @ref EN_QUEUE_ERR_STA_T.
 */
extern EN_QUEUE_ERR_STA_T msg_queue_pop(stQueueDef_t *pstQueue, void *pElement);




#endif /* __MSG_QUEUE_H__ */

