#ifndef _HM01B0_H_
#define _HM01B0_H_

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "ht32f493x5.h"
#include "ht32f493x5_board.h"
#include "i2c_application.h"
#include "ht32f493x5_exint.h"
#include "ht32f493x5_spi.h"
#include "ht32f493x5_dma.h"

#define HM01B0_IMAGE_WIDTH            164 /* 160 + 2 border pixels */
#define HM01B0_IMAGE_HEIGHT           120
#define HM01B0_IMAGE_SIZE_BYTES       (HM01B0_IMAGE_WIDTH * HM01B0_IMAGE_HEIGHT) 

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

/* SPI 1-bit Data Path */
#define HM01B0_SPI_PORT               SPI1
#define HM01B0_SPI_CLK                CRM_SPI1_PERIPH_CLOCK
#define HM01B0_SPI_GPIO_CLK           CRM_GPIOA_PERIPH_CLOCK

#define HM01B0_PCLK_PIN               GPIO_PINS_5  /* SPI1_SCK */
#define HM01B0_PCLK_PORT              GPIOA
#define HM01B0_D0_PIN                 GPIO_PINS_7  /* SPI1_MOSI */
#define HM01B0_D0_PORT                GPIOA

#define HM01B0_HREF_PIN               GPIO_PINS_4  /* SPI1_NSS  */
#define HM01B0_HREF_PORT              GPIOA
#define HM01B0_HREF_IRQn              EXINT4_IRQn

/* Frame Sync */
#define HM01B0_VSYNC_PIN              GPIO_PINS_0
#define HM01B0_VSYNC_PORT             GPIOB
#define HM01B0_VSYNC_GPIO_CLK         CRM_GPIOB_PERIPH_CLOCK
#define HM01B0_VSYNC_EXINT_LINE       EXINT_LINE_0
#define HM01B0_VSYNC_IRQn             EXINT0_IRQn

/* DMA */
#define HM01B0_DMA_CHANNEL            DMA1_CHANNEL2
#define HM01B0_DMA_CLK                CRM_DMA1_PERIPH_CLOCK

extern volatile uint8_t g_frame_ready;

void hm01b0_init(i2c_handle_type* hi2c);
void hm01b0_i2c_init(i2c_handle_type* hi2c);
void hm01b0_spi_dma_init(void* buffer, uint32_t size);
int  hm01b0_reset(i2c_handle_type* hi2c);
void hm01b0_write_reg8(i2c_handle_type* hi2c, uint16_t address, uint8_t value);
void hm01b0_write_reg16(i2c_handle_type* hi2c, uint16_t address, uint16_t value);
uint8_t  hm01b0_read_reg8(i2c_handle_type* hi2c, uint16_t address);
uint16_t hm01b0_read_reg16(i2c_handle_type* hi2c, uint16_t address);

#endif
