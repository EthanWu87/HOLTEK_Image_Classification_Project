#include "hm01b0.h"

#define HM01B0_I2C_ADDRESS 0x24

static void hm01b0_write_reg8(uint16_t address, uint8_t value);
static void hm01b0_write_reg16(uint16_t address, uint16_t value);

static void I2C_MasterSendData(i2c_type* i2cx, uint16_t address, uint8_t* data, uint16_t size)
{
    /*
        i2c_handle_type hi2c;
    hi2c.i2cx = i2cx;
    
    i2c_master_transmit(&hi2c, address, data, size, I2C_TIMEOUT);
    */

}

void hm01b0_i2c_init(void)
{
    gpio_init_type gpio_initstructure;

    /* i2c periph clock enable */
    crm_periph_clock_enable(I2Cx_CLK, TRUE);
    crm_periph_clock_enable(I2Cx_SCL_GPIO_CLK, TRUE);
    crm_periph_clock_enable(I2Cx_SDA_GPIO_CLK, TRUE);

    /* gpio configuration */
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;

    /* configure i2c pins: scl */
    gpio_initstructure.gpio_pins = I2Cx_SCL_PIN;
    gpio_init(I2Cx_SCL_GPIO_PORT, &gpio_initstructure);

    /* configure i2c pins: sda */
    gpio_initstructure.gpio_pins = I2Cx_SDA_PIN;
    gpio_init(I2Cx_SDA_GPIO_PORT, &gpio_initstructure);

    /* configure and enable i2c interrupt */
    nvic_irq_enable(I2Cx_EVT_IRQn, 0, 0);
    nvic_irq_enable(I2Cx_ERR_IRQn, 0, 0);

    i2c_init(I2Cx_PORT, I2C_FSMODE_DUTY_2_1, I2Cx_SPEED);

    i2c_own_address1_set(I2Cx_PORT, I2C_ADDRESS_MODE_7BIT, I2Cx_ADDRESS);
}

int hm01b0_init(void)
{
    /* hm01b0 register initialization for 320x240, 8-bit mode (QVGA) */
    uint8_t readout_x_val          = 0x01;   // 0x0383
    uint8_t readout_y_val          = 0x01;   // 0x0387
    uint8_t binning_mode_val       = 0x00;   // 0x0390
    uint8_t qvga_win_en_val        = 0x01;   // 0x3010
    uint16_t frame_length_lines_val= 0x0104; // 0x0340
    uint16_t line_length_pclk_val  = 0x0178; // 0x0342
    uint8_t bit_control_val        = 0x02;   // 0x3059 (8-bit data)

    hm01b0_i2c_init();

    // Software Reset
    hm01b0_write_reg8(0x0103, 0x01);
    
    // Setup registers
    hm01b0_write_reg8(0x3059, bit_control_val);
    hm01b0_write_reg8(0x0383, readout_x_val);
    hm01b0_write_reg8(0x0387, readout_y_val);
    hm01b0_write_reg8(0x0390, binning_mode_val);
    hm01b0_write_reg8(0x3010, qvga_win_en_val);
    hm01b0_write_reg16(0x0340, frame_length_lines_val);
    hm01b0_write_reg16(0x0342, line_length_pclk_val);
    
    hm01b0_write_reg8(0x3060, 0x08 | 0); // OSC_CLK_DIV
    hm01b0_write_reg16(0x0202, line_length_pclk_val / 2); // INTEGRATION_H
    hm01b0_write_reg8(0x0104, 0x01); // GRP_PARAM_HOLD

    return 0;
}

static void hm01b0_write_reg8(uint16_t address, uint8_t value)
{
    uint8_t data[3];

    *((uint16_t*)data) = __REV16(address);
    data[2] = value;

    I2C_MasterSendData(I2Cx_PORT, HM01B0_I2C_ADDRESS, data, sizeof(data));
}

static void hm01b0_write_reg16(uint16_t address, uint16_t value)
{
    uint8_t data[4];

    *((uint16_t*)data + 0) = __REV16(address);
    *((uint16_t*)data + 1) = __REV16(value);
   
    I2C_MasterSendData(I2Cx_PORT, HM01B0_I2C_ADDRESS, data, sizeof(data));
}
