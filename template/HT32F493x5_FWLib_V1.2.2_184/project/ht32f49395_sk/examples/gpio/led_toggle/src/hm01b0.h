#ifndef _HM01B0_H_
#define _HM01B0_H_

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "ht32f493x5.h"
#include "ht32f493x5_board.h"
#include "i2c_application.h"

#define HM01B0_I2C_TIMEOUT            0xFFFFFFFF

#define HM01B0_I2C_SPEED              100000
#define HM01B0_I2C_ADDRESS            0x48

#define HM01B0_I2C_PORT               I2C1
#define HM01B0_I2C_CLK                CRM_I2C1_PERIPH_CLOCK

#define HM01B0_I2C_SCL_PIN            GPIO_PINS_6
#define HM01B0_I2C_SCL_PORT           GPIOB
#define HM01B0_I2C_SCL_GPIO_CLK       CRM_GPIOB_PERIPH_CLOCK

#define HM01B0_I2C_SDA_PIN            GPIO_PINS_7
#define HM01B0_I2C_SDA_GPIO_PORT      GPIOB
#define HM01B0_I2C_SDA_GPIO_CLK       CRM_GPIOB_PERIPH_CLOCK

#define HM01B0_I2C_EVT_IRQn           I2C1_EVT_IRQn
#define HM01B0_I2C_ERR_IRQn           I2C1_ERR_IRQn

void hm01b0_init(i2c_handle_type* hi2c);
void hm01b0_write_reg8(i2c_handle_type* hi2c, uint16_t address, uint8_t value);
void hm01b0_write_reg16(i2c_handle_type* hi2c, uint16_t address, uint16_t value);

#endif
