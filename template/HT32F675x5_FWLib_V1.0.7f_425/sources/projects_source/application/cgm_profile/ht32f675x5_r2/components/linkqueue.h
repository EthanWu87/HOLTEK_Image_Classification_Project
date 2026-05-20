/*************************************************************************************************************
 * @file    linkqueue.h
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
#ifndef LINKQUEUE_H
#define LINKQUEUE_H

typedef void *stLinkQueue_t;

/**********************************************************************************************************************
 * @brief  Create a Link Queue.
 * @output
 * @return Link Queue Handle.
 *********************************************************************************************************************/
stLinkQueue_t *link_queue_create(void);

/**********************************************************************************************************************
 * @brief  Link Queue Put.
 * @param  stLinkQueue: Link Queue Handle.
 * @param  pu8Data: Data Put into the Queue.
 * @param  u16DataLen: The Length of Data Put into the Queue.
 * @output
 * @return 0 : Succeed   1 : Parameters Error  2 : Malloc Failed.
 *********************************************************************************************************************/
uint8_t link_queue_put(stLinkQueue_t stLinkQueue,const uint8_t *pu8Data,uint16_t u16DataLen);

/**********************************************************************************************************************
 * @brief  Get Data From Link Queue But Don't Remove Data.
 * @param  stLinkQueue: Link Queue Handle.
 * @param  pu8Data: Point to Data Buffer.
 * @output
 * @return The Length of The Data Successfully Get from The Queue.
 *********************************************************************************************************************/
uint16_t link_queue_peek(stLinkQueue_t stLinkQueue,uint8_t **pu8Data);

/**********************************************************************************************************************
 * @brief  Link Queue Get and Remove Data From Link Queue.
 * @param  stLinkQueue: Link Queue Handle.
 * @param  pu8Data: Point to Data Buffer.
 * @param  u16DataLen: Buffer Size
 * @output
 * @return The Length of The Data Successfully Get from The Queue.
 *********************************************************************************************************************/
uint16_t link_queue_get(stLinkQueue_t stLinkQueue,uint8_t *pu8Data,uint16_t u16DataLen);

/**********************************************************************************************************************
 * @brief  Link Queue Front Data Size.
 * @param  stLinkQueue: Link Queue Handle.
 * @output
 * @return Data Size.
 *********************************************************************************************************************/
uint16_t link_queue_get_front_data_size(stLinkQueue_t stLinkQueue);

/**********************************************************************************************************************
 * @brief  Clear All Data in Link Queue.
 * @param  stLinkQueue: Link Queue Handle.
 * @output
 * @return None.
 *********************************************************************************************************************/
void link_queue_clear(stLinkQueue_t stLinkQueue);

/**********************************************************************************************************************
 * @brief  Clear All Data in Link Queue and Destroy Link Queue Handle.
 * @param  stLinkQueue: Link Queue Handle.
 * @output
 * @return None.
 *********************************************************************************************************************/
void link_queue_destroy(stLinkQueue_t stLinkQueue);

/**********************************************************************************************************************
 * @brief  Whether the Link Queue is Empty.
 * @param  stLinkQueue: Link Queue Handle.
 * @output
 * @return false : not empty  , true : empty.
 *********************************************************************************************************************/
bool link_queue_is_empty(stLinkQueue_t stLinkQueue);

#endif
