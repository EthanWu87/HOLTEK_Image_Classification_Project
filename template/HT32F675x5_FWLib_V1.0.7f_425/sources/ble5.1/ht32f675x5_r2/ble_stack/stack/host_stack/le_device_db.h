/*************************************************************************************************************
 * @file    le_device_db.h
 * @version V1.0.0
 * @date    2016-11-18
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


#ifndef __LE_DEVICE_DB_H
#define __LE_DEVICE_DB_H


/**

    LE Device DB for pure LE Peripherals is only required for signed writes

    Per bonded device, it can store
    - it stores the Identity Resolving Key (IRK) and its address to resolve private addresses
    - it stores the LTK + EDIV, RAND. EDIV + RAND allow a LE Perihperal to reconstruct the LTK
    - it stores the Connection Signature Resolving Key (CSRK) and the last used counter.
        The CSRK is used to generate the signatur on the remote device and is needed to verify the signature itself
        The Counter is necessary to prevent reply attacks

*/

#define LE_DEVICE_MEMORY_SIZE 2    //for multi connect
#define INVALID_ENTRY_ADDR_TYPE 0xff

// Central Device db implemenation using static memory
// typedef struct le_device_memory_db
// {

//     // Identification
//     uint8_t  addr_type;
//     uint8_t  key_size;
//     uint8_t  authenticated;
//     uint8_t  authorized;
//     bd_addr_t addr;
//     uint16_t ediv;
//     uint8_t  rand[8];
//     // Stored pairing information allows to re-establish an enncrypted connection
//     // with a peripheral that doesn't have any persistent memory
//     sm_key_t ltk;
//     sm_key_t irk;

//     // Signed Writes by remote
//     sm_key_t remote_csrk;
//     uint32_t remote_counter;

//     // Signed Writes by us
//     sm_key_t local_csrk;
//     uint32_t local_counter;

// } le_device_memory_db_t;

extern void le_device_db_clear(void);

extern void le_device_db_init(void);

// @returns number of device in db
extern int32_t le_device_db_count(void);

// free device
extern void le_device_db_remove(sm_pair_state_t *p_sm_state);

extern int rom_le_device_db_add(sm_pair_state_t *p_sm_state,uint32_t addr_type, bd_addr_t addr, sm_key_t irk);

extern void rom_le_device_db_info_get(sm_pair_state_t *p_sm_state, int * addr_type, bd_addr_t addr, sm_key_t irk);


extern void rom_le_device_db_encryption_set(sm_pair_state_t *p_sm_state, uint16_t ediv, uint8_t rand[8], sm_key_t ltk, uint8_t key_size, uint8_t authenticated, uint8_t authorized);


extern void rom_le_device_db_encryption_get(sm_pair_state_t *p_sm_state, uint16_t * ediv, uint8_t rand[8], sm_key_t ltk, int * key_size, int * authenticated, int * authorized);


// get signature key
extern void rom_le_device_db_remote_csrk_get(sm_pair_state_t *p_sm_state, sm_key_t csrk);


extern void rom_le_device_db_remote_csrk_set(sm_pair_state_t *p_sm_state, sm_key_t csrk);


extern void rom_le_device_db_local_csrk_get(sm_pair_state_t *p_sm_state, sm_key_t csrk);

extern void rom_le_device_db_local_csrk_set(sm_pair_state_t *p_sm_state, sm_key_t csrk);

// query last used/seen signing counter
extern uint32_t rom_le_device_db_remote_counter_get(sm_pair_state_t *p_sm_state);
// update signing counter
extern void rom_le_device_db_remote_counter_set(sm_pair_state_t *p_sm_state, uint32_t counter);

// query last used/seen signing counter
extern uint32_t rom_le_device_db_local_counter_get(sm_pair_state_t *p_sm_state);

// update signing counter
extern void rom_le_device_db_local_counter_set(sm_pair_state_t *p_sm_state, uint32_t counter);

extern uint32_t rom_le_device_db_remote_counter_get(sm_pair_state_t *p_sm_state);

extern void rom_le_device_db_remote_csrk_get(sm_pair_state_t *p_sm_state, sm_key_t csrk);

//extern le_device_memory_db_t le_devices[LE_DEVICE_MEMORY_SIZE];

#endif // __LE_DEVICE_DB_H
