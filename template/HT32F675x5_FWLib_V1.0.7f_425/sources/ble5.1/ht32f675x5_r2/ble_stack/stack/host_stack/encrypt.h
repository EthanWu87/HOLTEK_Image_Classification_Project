/*************************************************************************************************************
 * @file    encrypt.h
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
#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

#define AES_PROECT_TIME_US  500

//define aes work status
#define MASK_AES_BUSYING        0x01
#define MASK_AES_BUFF_BUSYING   0x02
#define MASK_AES_FORCED_INTERRUPTION    0x04

////define aes pending module
//#define MASK_GEN_SK                   0x0001
//#define MASK_RESOLVE_PRIVATE_ADDR 0x0002
//#define MASK_GEN_PRIVATE_ADDR     0x0004
//#define MASK_SM_ENCRYPT               0x0008
//#define MASK_HOST_ENCRYPT         0x0010

enum AES_PENDING_MODULE_TYPE
{
    AES_SM_DKG,
    AES_SM_RAU,
    AES_SM_CMAC,
    AES_SM_CSRK,
    AES_SM_LINK,
    AES_RESOLVE_PRIVATE_ADDR,
    AES_GEN_PRIVATE_ADDR,
    AES_SK,
    AES_HOST,
    AES_APP,
//  // distributed key generation
//  AES_DKG,
//  // random address updates
//  AES_RAU,
//  AES_CMAC,
//  AES_CSRK,
//  AES_LINK,
};

enum AES_HANDLE_CB_TYPE
{
    AES_RPT_ENCRYPTED_DATA,
    AES_RPT_PENDING,
};

typedef void (*encrypt_handle_func_cb_t)(uint8_t cb_type,uint16_t conn_idx, uint8_t *encrypted_data);

typedef struct aes128_control_struct
{
    encrypt_handle_func_cb_t sm_handle_cb;
    uint32_t  key[4];
    uint32_t  plaintext[4];
    uint32_t  encrypted_data[4];
    uint32_t  pending;             //record pending module
    uint8_t role_idx;
    uint8_t module_type;
    uint8_t status;
    uint8_t need_trigger;
}aes128_ctrl_st;

typedef struct aes128_msg
{
    uint8_t key[16];
    uint8_t plaintext[16];
    uint16_t role_idx;
    uint16_t module_type;
  //  uint8_t module_sub_type;
    
}aes128_msg_st;

extern aes128_ctrl_st g_aes_ctrl;

extern void encrypt_init(void);
extern uint8_t encrypt_apply_for_aes_buffer( void );
extern void encrypt_aes_cfg(uint8_t module_type, uint8_t role_idx, uint8_t *key, uint8_t *plaintext, uint8_t data_len);
extern void encrypt_set_pending(uint8_t module_type);
extern void encrypt_sm_handle_cb_register(encrypt_handle_func_cb_t cb);
void encrypt_task_handler ( aes128_msg_st *msg );
#endif
