/*************************************************************************************************************
 * @file    stack_task.h
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

#ifndef __STACK_TASK_H__
#define __STACK_TASK_H__



enum STACK_CTRL_TASK_CMD_ENUM
{
    ST_CTRL_VENDOR_CONNECTION_COMPLETE_EVT = 0,    //0
    ST_CTRL_DISCONNECT_COMPLETE_EVT = 1,    //1
    ST_CTRL_CONNECTION_PARAM_REQ_EVT = 2,   //2
    ST_CTRL_ENCRYPT_CHG_EVT = 3,            //3
    ST_CTRL_ENCRYPT_KEY_REFRESH_EVT = 4,    //4
    ST_CTRL_LTK_REQ_EVT = 5,                //5
    ST_CTRL_ACL_DATA_RPT = 6,               //6
    ST_CTRL_ACL_DATA_RPT_REPEAT  ,               
    ST_CTRL_TX_ACL_DATA_EVT,
    ST_CTRL_TRIGGER_SM_RUN  ,             
    ST_CTRL_TRIGGER_SM_CSRK_RUN  ,         
    ST_CTRL_TX_BUF_SEND_OVER  ,          
     
    ST_CTRL_HDCDA_TIMEOUT = 0xe,              //0xe
    ST_CTRL_LL_WAKEUP_DURATION_LATENCY = 0xf,   //0xf
    ST_CTRL_LE_EXT_ADV_REPORT_EVENT = 0x10,     //0x10
    ST_CTRL_ADV_DATA_UPDATE_COMPLETE_EVENT = 0x11,  //0x11
    ST_CTRL_ADV_EVENT_END = 0x12,               //0x12
    ST_CTRL_CONNECTION_UPDATE_COMPLETE, //0X13
    ST_CTRL_PHY_UPDATE_COMPLETE,    //0x14
    ST_CTRL_REMOTE_VERSION_EVT, //0x15
    ST_CTRL_REMOTE_FEATURE_EVT=0X16,    //0x16
    ST_CTRL_DATA_LENGTH_CHANGE_EVT, //0x17
    ST_CTRL_TRIGGER_SM_ECC_PUBKEY,  //0x18
    ST_CTRL_TRIGGER_SM_ECC_DHKEY,   //0x19
    ST_CTRL_TRIGGER_SM_PAIR_NEXT,   //0x20
    ST_CTRL_TRIGGER_SM_PAIR_TIMEOUT,   //0x21
    ST_CTRL_TRIGGER_SM_SECURITY_REQ,   //0x22
    ST_CTRL_TRIGGER_SM_INPUT_PASSKEY,   //0x23
    ST_CTRL_TRIGGER_SM_COMPARISON_CONFIRM ,   //0x24
    ST_CTRL_TRIGGER_SM_AES_RUN ,  
    ST_CTRL_LE_ADV_REPORT_EVENT,  
    ST_CTRL_HCI_COMMAND_COMPLETE,
    ST_CTRL_HCI_COMMAND_STATUS,
};


#endif



