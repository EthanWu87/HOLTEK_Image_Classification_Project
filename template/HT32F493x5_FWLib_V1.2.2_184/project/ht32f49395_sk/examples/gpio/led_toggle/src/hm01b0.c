#include "hm01b0.h"

void hm01b0_init(i2c_handle_type* hi2c)
{
  hm01b0_i2c_init(hi2c);
  hm01b0_pclk_exint_init();

  /* HM01B0 register initialization for 160x120 */
  uint8_t readout_x_val           = 0x03;
  uint8_t readout_y_val           = 0x03;
  uint8_t binning_mode_val        = 0x03;
  uint8_t qvga_win_en_val         = 0x01;
  uint16_t frame_length_lines_val = 0x0080;
  uint16_t line_length_pclk_val   = 0x00D7;
  uint8_t bit_control_val         = 0x22;

  /* Scan model id */
  uint16_t model_id = hm01b0_read_reg16(hi2c, 0x0000);
  if(model_id != 0x01b0)
  {
    printf("Invalid model id: 0x%04X\n", model_id);
  }

  if(hm01b0_reset(hi2c) != 0)
  {
    printf("Reset failed!\n");
  }

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

  hm01b0_write_reg8(hi2c, 0x0104, 0x00); 

  hm01b0_write_reg8(hi2c, 0x0100, 0x01);
}

int hm01b0_reset(i2c_handle_type* hi2c)
{
  hm01b0_write_reg8(hi2c, 0x0103, 0x01);

  for(int retries = 0; retries < 10; retries++)
  {
    if(hm01b0_read_reg8(hi2c, 0x0100) == 0x00)
    {
      return 0;
    }

    delay_ms(100);
  }

  return -1;
}

void hm01b0_i2c_init(i2c_handle_type* hi2c)
{
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

    nvic_irq_enable(HM01B0_I2C_EVT_IRQn, 1, 0);
    nvic_irq_enable(HM01B0_I2C_ERR_IRQn, 1, 0);
  }

  i2c_enable(hi2c->i2cx, TRUE);
}

void hm01b0_pclk_exint_init()
{
  exint_init_type exint_init_struct;

  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(HM01B0_PCLK_EXINT_CLK, TRUE);

  gpio_exint_line_config(HM01B0_PCLK_EXINT_PORT, HM01B0_PCLK_EXINT_PIN);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPT;
  exint_init_struct.line_select = EXINT_LINE_0;
  exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
  exint_init(&exint_init_struct);

  nvic_irq_enable(HM01B0_PCLK_EXINT_IRQn, 0, 0);
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

uint8_t hm01b0_read_reg8(i2c_handle_type* hi2c, uint16_t address)
{
  uint8_t result = 0xff;

  i2c_memory_read(hi2c, I2C_MEM_ADDR_WIDIH_16, HM01B0_I2C_ADDRESS, address, &result, 1, HM01B0_I2C_TIMEOUT);
  return result;
}

uint16_t hm01b0_read_reg16(i2c_handle_type* hi2c, uint16_t address)
{
  uint8_t data[2] = {0, 0};
  uint16_t result = 0xffff;

  if(i2c_memory_read(hi2c, I2C_MEM_ADDR_WIDIH_16, HM01B0_I2C_ADDRESS, address, data, 2, HM01B0_I2C_TIMEOUT) == I2C_OK)
  {
    // HM01B0 returns data in Big-Endian (High byte, then Low byte)
    result = (uint16_t)(data[0] << 8) | data[1];
  }
  
  return result;
}
