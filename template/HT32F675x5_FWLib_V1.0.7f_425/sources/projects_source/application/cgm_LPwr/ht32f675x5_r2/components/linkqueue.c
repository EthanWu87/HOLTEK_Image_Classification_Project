/*************************************************************************************************************
 * @file    linkqueue.c
 * @version V1.0
 * @date    2021-02-06
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
#include <stdlib.h>

#include "linkqueue.h"
#include "app_cfg.h"


typedef struct Node
{
    uint8_t *pu8Data;
    uint16_t u16DataLen;
    struct Node *next;
}LinkQueueNode_t;

typedef struct
{
    LinkQueueNode_t *front;
    LinkQueueNode_t *rear;
}LinkQueue_t;

/**********************************************************************************************************************
 * @brief  Create a Link Queue.
 * @output
 * @return Link Queue Handle.
 *********************************************************************************************************************/
stLinkQueue_t *link_queue_create(void)
{
    LinkQueue_t *stHandle = (LinkQueue_t *)malloc(sizeof(LinkQueue_t));
    if (NULL == stHandle)
        return NULL;
    
    LinkQueueNode_t *stNewNode = (LinkQueueNode_t *)malloc(sizeof(LinkQueueNode_t));
    if (NULL == stNewNode)
    {
        INFO("Link Queue Create Alloc Memory Failed\n");
        free(stHandle);
        return NULL;
    }
    
    stHandle->front = stHandle->rear = stNewNode;
    stHandle->front->next = NULL;
    
    return (stLinkQueue_t)stHandle;
}

/**********************************************************************************************************************
 * @brief  Link Queue Put.
 * @param  stLinkQueue: Link Queue Handle.
 * @param  pu8Data: Data Put into the Queue.
 * @param  u16DataLen: The Length of Data Put into the Queue.
 * @output
 * @return 0 : Succeed   1 : Parameters Error  2 : Malloc Failed.
 *********************************************************************************************************************/
uint8_t link_queue_put(stLinkQueue_t stLinkQueue,const uint8_t *pu8Data,uint16_t u16DataLen)
{
    LinkQueue_t *stHandle = (LinkQueue_t *)stLinkQueue;
    
    if (NULL == stLinkQueue || NULL == pu8Data || 0 == u16DataLen)
        return 1;
    
    LinkQueueNode_t *stNewNode = (LinkQueueNode_t *)malloc(sizeof(LinkQueueNode_t));
    if (NULL == stNewNode)
        return 2;
    
    stNewNode->next = NULL;
    stNewNode->pu8Data = (uint8_t *)malloc(u16DataLen);
    if (NULL == stNewNode->pu8Data)
    {
        INFO("Link Queue Put Alloc Memory Failed\n");
        return 2;
    }
    memcpy(stNewNode->pu8Data,pu8Data,u16DataLen);
    stNewNode->u16DataLen = u16DataLen;
    
    if (NULL == stHandle->front->next)
        stHandle->front->next = stNewNode;
    
    stHandle->rear->next = stNewNode;
    stHandle->rear = stNewNode;
    
    return 0;
}

/**********************************************************************************************************************
 * @brief  Get Data From Link Queue But Don't Remove Data.
 * @param  stLinkQueue: Link Queue Handle.
 * @param  pu8Data: Point to Data Buffer.
 * @output
 * @return The Length of The Data Successfully Get from The Queue.
 *********************************************************************************************************************/
uint16_t link_queue_peek(stLinkQueue_t stLinkQueue,uint8_t **pu8Data)
{
    LinkQueue_t *stHandle = (LinkQueue_t *)stLinkQueue;
    LinkQueueNode_t *stFrontNode = NULL;
    
    if (NULL == stLinkQueue || NULL == pu8Data)
        return 0;
    
    stFrontNode = stHandle->front->next;
    if (NULL == stFrontNode)
        return 0;
    
    *pu8Data = stHandle->front->next->pu8Data;

    return stHandle->front->next->u16DataLen;
}

/**********************************************************************************************************************
 * @brief  Link Queue Get and Remove Data From Link Queue.
 * @param  stLinkQueue: Link Queue Handle.
 * @param  pu8Data: Point to Data Buffer.
 * @param  u16DataLen: Buffer Size
 * @output
 * @return The Length of The Data Successfully Get from The Queue.
 *********************************************************************************************************************/
uint16_t link_queue_get(stLinkQueue_t stLinkQueue,uint8_t *pu8Data,uint16_t u16DataLen)
{
    LinkQueue_t *stHandle = (LinkQueue_t *)stLinkQueue;
    LinkQueueNode_t *stFrontNode = NULL;
    
    if (NULL == stLinkQueue)
        return 0;
    
    stFrontNode = stHandle->front->next;
    if (NULL == stFrontNode)
    {
        stHandle->rear = stHandle->front;
        return 0;
    }
    
    if (u16DataLen > stFrontNode->u16DataLen)
        u16DataLen = stFrontNode->u16DataLen;
    
    if (pu8Data)
        memcpy(pu8Data,stFrontNode->pu8Data,u16DataLen);
    
    free(stFrontNode->pu8Data);
    stHandle->front->next = stFrontNode->next;
    free(stFrontNode);
    
    return u16DataLen;
}

/**********************************************************************************************************************
 * @brief  Link Queue Front Data Size.
 * @param  stLinkQueue: Link Queue Handle.
 * @output
 * @return Data Size.
 *********************************************************************************************************************/
uint16_t link_queue_get_front_data_size(stLinkQueue_t stLinkQueue)
{
    LinkQueue_t *stHandle = (LinkQueue_t *)stLinkQueue;
    LinkQueueNode_t *stFrontNode = NULL;
    
    if (NULL == stLinkQueue)
        return 0;
    
    stFrontNode = stHandle->front->next;
    
    if (NULL == stFrontNode)
        return 0;
    
    return stFrontNode->u16DataLen;

}


/**********************************************************************************************************************
 * @brief  Clear All Data in Link Queue.
 * @param  stLinkQueue: Link Queue Handle.
 * @output
 * @return None.
 *********************************************************************************************************************/
void link_queue_clear(stLinkQueue_t stLinkQueue)
{
    LinkQueue_t *stHandle = (LinkQueue_t *)stLinkQueue;
    LinkQueueNode_t *stFrontNode = NULL;

    if (NULL == stLinkQueue)
        return;
    
    stFrontNode = stHandle->front->next;
    
    while(stFrontNode)
    {
        stHandle->front->next = stFrontNode->next;
        free(stFrontNode->pu8Data);
        free(stFrontNode);
        
        stFrontNode = stHandle->front->next;
    }
    
    stHandle->rear = stHandle->front;
}

/**********************************************************************************************************************
 * @brief  Clear All Data in Link Queue and Destroy Link Queue Handle.
 * @param  stLinkQueue: Link Queue Handle.
 * @output
 * @return None.
 *********************************************************************************************************************/
void link_queue_destroy(stLinkQueue_t stLinkQueue)
{
    LinkQueue_t *stHandle = (LinkQueue_t *)stLinkQueue;
    LinkQueueNode_t *stFrontNode = NULL;

    if (NULL == stLinkQueue)
        return;
    
    stFrontNode = stHandle->front->next;
    
    while(stFrontNode)
    {
        stHandle->front->next = stFrontNode->next;
        free(stFrontNode->pu8Data);
        free(stFrontNode);
        
        stFrontNode = stHandle->front->next;
    }
    
    free(stHandle->front);
    free(stHandle);
}

/**********************************************************************************************************************
 * @brief  Whether the Link Queue is Empty.
 * @param  stLinkQueue: Link Queue Handle.
 * @output
 * @return false : not empty  , true : empty.
 *********************************************************************************************************************/
bool link_queue_is_empty(stLinkQueue_t stLinkQueue)
{
    LinkQueue_t *stHandle = (LinkQueue_t *)stLinkQueue;
    if (NULL == stHandle)
        return true;
    
    if (NULL == stHandle->front->next)
        return true;
    return false;
}


