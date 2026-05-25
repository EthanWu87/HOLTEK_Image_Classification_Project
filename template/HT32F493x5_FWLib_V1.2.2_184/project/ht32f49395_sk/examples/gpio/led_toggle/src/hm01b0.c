#include "hm01b0.h"

void hm01b0_init(i2c_handle_type* hi2c)
{
  /* I2C initialization */
  i2c_reset(hi2c->i2cx);

  gpio_init_type gpio_initstructure;

  if(hi2c->i2cx == HM01B0_I2C_PORT)
  {
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(HM01B0_I2C_CLK, TRUE);
    crm_periph_clock_enable(HM01B0_I2C_SCL_GPIO_CLK, TRUE);
    crm_periph_clock_enable(HM01B0_I2C_SDA_GPIO_CLK, TRUE);

    //gpio_pin_remap_config(I2C1_MUX, FALSE);

    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
        
    gpio_initstructure.gpio_pins = HM01B0_I2C_SCL_PIN;
    gpio_init(HM01B0_I2C_SCL_PORT, &gpio_initstructure);

    gpio_initstructure.gpio_pins = HM01B0_I2C_SDA_PIN;
    gpio_init(HM01B0_I2C_SDA_GPIO_PORT, &gpio_initstructure);

    i2c_init(hi2c->i2cx, I2C_FSMODE_DUTY_2_1, HM01B0_I2C_SPEED);

    nvic_irq_enable(HM01B0_I2C_EVT_IRQn, 0, 0);
    nvic_irq_enable(HM01B0_I2C_ERR_IRQn, 0, 0);
  }

  i2c_enable(hi2c->i2cx, TRUE);

  /* hm01b0 register initialization for 320x240, 8-bit mode (QVGA) */
  uint8_t readout_x_val           = 0x01;
  uint8_t readout_y_val           = 0x01;
  uint8_t binning_mode_val        = 0x00;
  uint8_t qvga_win_en_val         = 0x01;
  uint16_t frame_length_lines_val = 0x0104;
  uint16_t line_length_pclk_val   = 0x0178;
  uint8_t bit_control_val         = 0x02;

  // Software Reset
  hm01b0_write_reg8(hi2c, 0x0103, 0x01);

  // Setup registers
  hm01b0_write_reg8(hi2c, 0x3059, bit_control_val);
  hm01b0_write_reg8(hi2c, 0x0383, readout_x_val);
  hm01b0_write_reg8(hi2c, 0x0387, readout_y_val);
  hm01b0_write_reg8(hi2c, 0x0390, binning_mode_val);
  hm01b0_write_reg8(hi2c, 0x3010, qvga_win_en_val);
  hm01b0_write_reg16(hi2c, 0x0340, frame_length_lines_val);
  hm01b0_write_reg16(hi2c, 0x0342, line_length_pclk_val);

  hm01b0_write_reg8(hi2c, 0x3060, 0x08 | 0); // OSC_CLK_DIV
  hm01b0_write_reg16(hi2c, 0x0202, line_length_pclk_val / 2); // INTEGRATION_H
  hm01b0_write_reg8(hi2c, 0x0104, 0x01); // GRP_PARAM_HOLD
}

void hm01b0_write_reg8(i2c_handle_type* hi2c, uint16_t address, uint8_t value)
{
  uint8_t data[3];

  *((uint16_t*)data) = __REV16(address);
  data[2] = value;

  i2c_master_transmit(hi2c, HM01B0_I2C_ADDRESS, data, sizeof(data), HM01B0_I2C_TIMEOUT);
}

void hm01b0_write_reg16(i2c_handle_type* hi2c, uint16_t address, uint16_t value)
{
  uint8_t data[4];

  *((uint16_t*)data + 0) = __REV16(address);
  *((uint16_t*)data + 1) = __REV16(value);
  
  i2c_master_transmit(hi2c, HM01B0_I2C_ADDRESS, data, sizeof(data), HM01B0_I2C_TIMEOUT);
}
