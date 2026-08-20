#include "hm01b0.h"

void hm01b0_init(i2c_handle_type* hi2c)
{
  hm01b0_i2c_init(hi2c);
  
  /* Initialization for QQVGA (160x120) */
  uint8_t readout_x_val           = 0x03;
  uint8_t readout_y_val           = 0x03;
  uint8_t binning_mode_val        = 0x03;
  uint8_t qvga_win_en_val         = 0x01;
  uint16_t frame_length_lines_val = 0x0154; 
  uint16_t line_length_pclk_val   = 0x00D7; 
  uint8_t bit_control_val         = 0x02; 
  uint8_t osc_clk_div             = 0x28;   
	
  uint8_t ae_enable_val           = 0x01;
  uint8_t ae_target_val           = 0x60;
  uint8_t ae_max_intg_h_val       = 0x01;
  uint8_t ae_max_intg_l_val       = 0x54;
	
  uint8_t group_consume           = 0x00;
  uint8_t group_hold              = 0x01;
	
  uint8_t OSC_mode_en             = 0x01;
	
  /* 啟動 MCLK (TMR3 PWM) */
  mclk_tmr3_init();
	
  if(hm01b0_reset(hi2c) != 0)
  {
    printf("Reset failed!\n");
  }

  uint16_t model_id = hm01b0_read_reg16(hi2c, 0x0000);
  if(model_id != 0x01b0)
  {
    printf("Invalid model id: 0x%04X\n", model_id);
  }

  hm01b0_write_reg8(hi2c, 0x3059, bit_control_val);
  hm01b0_write_reg8(hi2c, 0x0383, readout_x_val);
  hm01b0_write_reg8(hi2c, 0x0387, readout_y_val);
  hm01b0_write_reg8(hi2c, 0x0390, binning_mode_val);
  hm01b0_write_reg8(hi2c, 0x3010, qvga_win_en_val);
  hm01b0_write_reg16(hi2c, 0x0340, frame_length_lines_val);
  hm01b0_write_reg16(hi2c, 0x0342, line_length_pclk_val);

  hm01b0_write_reg8(hi2c, 0x3060, osc_clk_div | 0); 
  hm01b0_write_reg16(hi2c, 0x0202, frame_length_lines_val / 2);

  hm01b0_write_reg8(hi2c, 0x2100, ae_enable_val);
  hm01b0_write_reg8(hi2c, 0x2101, ae_target_val);
  hm01b0_write_reg8(hi2c, 0x2105, ae_max_intg_h_val);
  hm01b0_write_reg8(hi2c, 0x2106, ae_max_intg_l_val);
	
  hm01b0_write_reg8(hi2c, 0x0104, group_hold);
  hm01b0_write_reg8(hi2c, 0x0104, group_consume); 

	hm01b0_write_reg8(hi2c, 0x0601, 0x11);   // test image patterns

  hm01b0_write_reg8(hi2c, 0x3067, OSC_mode_en);
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

void mclk_tmr3_init(void)
{
  gpio_init_type gpio_init_struct = {0};
  tmr_output_config_type tmr_output_struct;
  crm_clocks_freq_type crm_clocks_freq_struct = {0};

  uint16_t timer_period = 0;
  uint16_t channel_pulse = 0;
	
  crm_clocks_freq_get(&crm_clocks_freq_struct);

  /* 使用巨集開啟外設時脈 */
  crm_periph_clock_enable(HM01B0_MCLK_TMR_CLK, TRUE);
  crm_periph_clock_enable(HM01B0_MCLK_CLK, TRUE);

  /* PA7 (TMR3_CH2) PWM 腳位配置 */
  gpio_init_struct.gpio_pins = HM01B0_MCLK_PIN;                      
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(HM01B0_MCLK_PORT, &gpio_init_struct);

  /* 計算 12MHz PWM 參數 */
  timer_period = (crm_clocks_freq_struct.sclk_freq / HM01B0_MCLK_FREQ) - 1;
  channel_pulse = (timer_period + 1) / 2;

  tmr_base_init(HM01B0_MCLK_TMR, timer_period, 0);
  tmr_cnt_dir_set(HM01B0_MCLK_TMR, TMR_COUNT_UP);

  tmr_output_default_para_init(&tmr_output_struct);
  tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
  tmr_output_struct.oc_output_state = TRUE;
  tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;

  /* 設定 Channel 2 輸出 */
  tmr_output_channel_config(HM01B0_MCLK_TMR, HM01B0_MCLK_TMR_CH, &tmr_output_struct);
  tmr_channel_value_set(HM01B0_MCLK_TMR, HM01B0_MCLK_TMR_CH, channel_pulse);

  tmr_output_enable(HM01B0_MCLK_TMR, TRUE);
  tmr_counter_enable(HM01B0_MCLK_TMR, TRUE);
}

void hm01b0_i2c_init(i2c_handle_type* hi2c)
{
  i2c_reset(hi2c->i2cx);

  gpio_init_type gpio_initstructure;

  if(hi2c->i2cx == HM01B0_I2C_PORT)
  {
    crm_periph_clock_enable(TXS0108EPWR_OE_GPIO_CLK, TRUE);

    gpio_initstructure.gpio_pins           = TXS0108EPWR_OE_PIN;
    gpio_initstructure.gpio_mode           = GPIO_MODE_OUTPUT;
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
    gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init(TXS0108EPWR_OE_GPIO_PORT, &gpio_initstructure);

    gpio_bits_set(TXS0108EPWR_OE_GPIO_PORT, TXS0108EPWR_OE_PIN);
		
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(HM01B0_I2C_CLK, TRUE);
    crm_periph_clock_enable(HM01B0_I2C_SCL_GPIO_CLK, TRUE);
    crm_periph_clock_enable(HM01B0_I2C_SDA_GPIO_CLK, TRUE);
		
    gpio_pin_remap_config(I2C1_MUX, TRUE);
		
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    
    gpio_initstructure.gpio_pins = HM01B0_I2C_SCL_PIN;
    gpio_init(HM01B0_I2C_SCL_GPIO_PORT, &gpio_initstructure);

    gpio_initstructure.gpio_pins = HM01B0_I2C_SDA_PIN;
    gpio_init(HM01B0_I2C_SDA_GPIO_PORT, &gpio_initstructure);

    i2c_init(hi2c->i2cx, I2C_FSMODE_DUTY_2_1, HM01B0_I2C_SPEED);

    nvic_irq_enable(HM01B0_I2C_EVT_IRQn, 1, 0);
    nvic_irq_enable(HM01B0_I2C_ERR_IRQn, 1, 0);
  }

  i2c_enable(hi2c->i2cx, TRUE);
}

void hm01b0_parallel_dma_init(void* buffer, uint32_t size)
{
  gpio_init_type gpio_init_struct;
  dma_init_type dma_init_struct;
  exint_init_type exint_init_struct;
  tmr_input_config_type tmr_ic_init_struct;

  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(HM01B0_DATA_GPIO_CLK, TRUE);
  crm_periph_clock_enable(HM01B0_CTRL_CLK_A, TRUE);
  crm_periph_clock_enable(HM01B0_PCLK_CLK, TRUE);
  crm_periph_clock_enable(HM01B0_PCLK_TMR_CLK, TRUE);
  crm_periph_clock_enable(HM01B0_DMA_CLK, TRUE);

  /* Data Pins (PC0~PC7) */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode      = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull      = GPIO_PULL_NONE;
  gpio_init_struct.gpio_pins      = HM01B0_DATA_PINS;
  gpio_init(HM01B0_DATA_PORT, &gpio_init_struct);

  /* VSYNC (PA2) & HREF (PA4) */
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = HM01B0_VSYNC_PIN | HM01B0_HREF_PIN;
  gpio_init(HM01B0_CTRL_PORT_A, &gpio_init_struct);

  /* PCLK (PB0) */
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_DOWN; 
  gpio_init_struct.gpio_pins = GPIO_PULL_NONE;
  gpio_init(HM01B0_PCLK_PORT, &gpio_init_struct);

  /* VSYNC EXINT 中斷配置 */
  gpio_exint_line_config(HM01B0_VSYNC_PORT_SRC, HM01B0_VSYNC_PIN_SRC);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPT;
  exint_init_struct.line_select = HM01B0_VSYNC_EXINT_LINE;
  exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
  exint_init(&exint_init_struct);
  nvic_irq_enable(HM01B0_VSYNC_IRQn, 0, 0);
	
	/*
	gpio_exint_line_config(HM01B0_HREF_PORT_SRC, HM01B0_HREF_PIN_SRC);
	exint_init_struct.line_enable   = TRUE;
	exint_init_struct.line_mode     = EXINT_LINE_INTERRUPT;
	exint_init_struct.line_select   = HM01B0_HREF_EXINT_LINE;
	exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
	exint_init(&exint_init_struct);
	nvic_irq_enable(HM01B0_HREF_IRQn, 1, 0);
	*/

  /* PCLK -> TMR3_CH3 Input Capture 觸發 DMA */
  tmr_input_default_para_init(&tmr_ic_init_struct);
  tmr_ic_init_struct.input_channel_select = HM01B0_PCLK_TMR_CH;
  tmr_ic_init_struct.input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_ic_init_struct.input_polarity_select = TMR_INPUT_RISING_EDGE; 	
  tmr_input_channel_init(HM01B0_PCLK_TMR, &tmr_ic_init_struct, TMR_CHANNEL_INPUT_DIV_1);

  tmr_dma_request_enable(HM01B0_PCLK_TMR, HM01B0_PCLK_DMA_REQ, TRUE);
  tmr_counter_enable(HM01B0_PCLK_TMR, TRUE);

  dma_flexible_config(HM01B0_DMA, HM01B0_DMA_FLEX_CHANNEL, HM01B0_PCLK_DMA_FLEX_REQ);

  /* DMA 傳輸配置 */
  dma_reset(HM01B0_DMA_CHANNEL);
  dma_init_struct.peripheral_base_addr = (uint32_t)&HM01B0_DATA_PORT->idt; 
  dma_init_struct.memory_base_addr = (uint32_t)buffer;
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.buffer_size = size;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_HIGH;
  dma_init(HM01B0_DMA_CHANNEL, &dma_init_struct);

  dma_interrupt_enable(HM01B0_DMA_CHANNEL, DMA_FDT_INT, TRUE);
  nvic_irq_enable(HM01B0_DMA_IRQn, 0, 0);
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
    result = (uint16_t)(data[0] << 8) | data[1];
  }
  
  return result;
}