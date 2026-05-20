#ifndef _HM01B0_H_
#define _HM01B0_H_

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "ht32f493x5.h"
#include "ht32f493x5_board.h"
#include "i2c_application.h"

#define I2C_TIMEOUT                      0xFFFFFFFF

#define I2Cx_SPEED                       100000
#define I2Cx_ADDRESS                     0xA0

#define I2Cx_PORT                        I2C1
#define I2Cx_CLK                         CRM_I2C1_PERIPH_CLOCK

#define I2Cx_SCL_PIN                     GPIO_PINS_6
#define I2Cx_SCL_GPIO_PORT               GPIOB
#define I2Cx_SCL_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define I2Cx_SDA_PIN                     GPIO_PINS_7
#define I2Cx_SDA_GPIO_PORT               GPIOB
#define I2Cx_SDA_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define I2Cx_EVT_IRQn                    I2C1_EVT_IRQn
#define I2Cx_ERR_IRQn                    I2C1_ERR_IRQn

void hm01b0_i2c_init(void);

int hm01b0_init(void);

#endif
