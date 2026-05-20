/*************************************************************************************************************
 * @file    att_db_util.h
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



#ifndef __ATT_DB_UTIL
#define __ATT_DB_UTIL


extern void rom_att_db_util_init(uint8_t* profile_buf,uint32_t profile_buflen,uint8_t const* profile_data, uint16_t size, uint16_t most_handle);

extern uint16_t rom_att_db_util_add_attribute_uuid16(uint16_t uuid16, uint16_t flags, uint8_t * data, uint16_t data_len);

extern uint16_t rom_att_db_util_add_attribute_uuid128(uint8_t * uuid128, uint16_t flags, uint8_t * data, uint16_t data_len);

extern uint16_t rom_att_db_util_add_service_uuid128(uint8_t* pu8Uuid128,uint16_t u16SrvTypeUuid );

extern uint16_t rom_att_db_util_add_service_uuid16(uint16_t u16SrvUuid,uint16_t u16SrvTypeUuid);

extern uint16_t rom_att_db_util_get_last_handle(void);

extern uint16_t rom_att_db_util_add_characteristic_uuid16(uint16_t uuid16, uint16_t properties, uint8_t * data, uint16_t data_len);

extern uint16_t rom_att_db_util_add_characteristic_uuid128(uint8_t * uuid128, uint16_t properties, uint8_t * data, uint16_t data_len);

extern uint16_t rom_att_db_util_add_characteristic_descrip_client_cfg(void);

extern uint16_t rom_att_db_util_get_size(void);

extern uint16_t rom_att_db_util_get_last_handle(void);

extern uint8_t  * att_db;

extern uint8_t  * att_db_util_get_db_start_adr(void);
extern uint8_t  * att_db_util_get_serv_char_adr(uint8_t  * pdb,int type);
extern uint8_t  * att_db_util_get_start_adr_before_add(void);
extern uint16_t rom_att_db_util_set_next_handle(uint16_t hdl);

extern uint16_t att_prepare_write_handle;
#endif
