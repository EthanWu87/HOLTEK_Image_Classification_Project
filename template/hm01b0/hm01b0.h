#ifndef _HM01B0_H_
#define _HM01B0_H_

#include <stdint.h>
#include "ht32f493x5.h"
#include "i2c_application.h"

#define HM01B0_I2C_ADDRESS 0x48 /* 0x24 << 1 for 8-bit HT32 I2C driver */

typedef struct {
    i2c_handle_type* hi2cx;
    uint32_t width;
    uint32_t height;
    uint8_t data_bits;
} hm01b0_config_t;

int hm01b0_init(hm01b0_config_t* config);
void hm01b0_set_coarse_integration(unsigned int lines);
uint8_t hm01b0_read_reg8(uint16_t address);
uint16_t hm01b0_read_reg16(uint16_t address);
void hm01b0_write_reg8(uint16_t address, uint8_t value);
void hm01b0_write_reg16(uint16_t address, uint16_t value);

#endif
