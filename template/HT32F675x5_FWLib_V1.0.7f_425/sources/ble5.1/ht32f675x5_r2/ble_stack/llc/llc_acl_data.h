/*************************************************************************************************************
 * @file    llc_acl_data.h
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
#ifndef LLC_ACL_DATA_H
#define LLC_ACL_DATA_H



typedef struct stLlcAclDataNode
{
    uint16_t u16ConnHandle;
    uint8_t u8PacketBoundaryFlag;
    uint8_t u8BroacastFlag;
    uint16_t u16DataOffset;
    uint16_t u16DataLength;
    uint8_t* pu8Payload;
    uint16_t u16PayloadBufSize;
    struct stLlcAclDataNode* prev;
    struct stLlcAclDataNode* next;
    bool bMemUsed;
    uint32_t u32Reserved;
} __attribute__((aligned(4)))
stLlcAclData_t;


bool rom_llc_acl_data_mem_init(stLlcAclData_t* pstAclDataMemBuffer, uint16_t u16AclDataSize, uint8_t u8AclDataNum);

uint16_t rom_llc_acl_data_get_max_size(void);

uint8_t rom_llc_acl_data_get_max_num(void);

uint8_t rom_llc_acl_data_get_remaining_num(void);

stLlcAclData_t* rom_llc_acl_data_alloc(void);

void rom_llc_acl_data_free(stLlcAclData_t* pstAclData);

#endif
