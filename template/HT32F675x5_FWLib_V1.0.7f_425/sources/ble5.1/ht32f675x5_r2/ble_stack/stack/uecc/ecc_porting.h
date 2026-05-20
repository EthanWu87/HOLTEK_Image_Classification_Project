#ifndef _ECC_PORTING_H_
#define _ECC_PORTING_H_
int rom_bt_dhkey_gen ( const uint8_t remote_pk[64], const uint8_t privkey[32],  uint8_t dhkey[32] );


int rom_bt_pub_priv_key_gen ( uint8_t pub_key[64], uint8_t priv_key[32] );
#endif
