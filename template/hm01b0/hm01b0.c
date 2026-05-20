#include "HM01B0.h"
#include <stdio.h>

#define HM01B0_TIMEOUT 0xFFFFFFFF

static hm01b0_config_t curr_config;

static int hm01b0_reset(void);

#define HM01B0_I2C_ADDRESS 0x24

uint8_t hm01b0_read_reg8(uint16_t address)
{
    uint8_t addr_buf[2];
    uint8_t val = 0;
    addr_buf[0] = (address >> 8) & 0xFF;
    addr_buf[1] = address & 0xFF;

    i2c_master_transmit(curr_config.hi2cx, HM01B0_I2C_ADDRESS, addr_buf, 2, HM01B0_TIMEOUT);
    i2c_master_receive(curr_config.hi2cx, HM01B0_I2C_ADDRESS, &val, 1, HM01B0_TIMEOUT);
    return val;
}

uint16_t hm01b0_read_reg16(uint16_t address)
{
    uint8_t addr_buf[2];
    uint8_t val[2] = {0, 0};
    addr_buf[0] = (address >> 8) & 0xFF;
    addr_buf[1] = address & 0xFF;

    i2c_master_transmit(curr_config.hi2cx, HM01B0_I2C_ADDRESS, addr_buf, 2, HM01B0_TIMEOUT);
    i2c_master_receive(curr_config.hi2cx, HM01B0_I2C_ADDRESS, val, 2, HM01B0_TIMEOUT);
    return (val[0] << 8) | val[1];
}

void hm01b0_write_reg8(uint16_t address, uint8_t value)
{
    uint8_t data[3];
    data[0] = (address >> 8) & 0xFF;
    data[1] = address & 0xFF;
    data[2] = value;
    i2c_master_transmit(curr_config.hi2cx, HM01B0_I2C_ADDRESS, data, 3, HM01B0_TIMEOUT);
}

void hm01b0_write_reg16(uint16_t address, uint16_t value)
{
    uint8_t data[4];
    data[0] = (address >> 8) & 0xFF;
    data[1] = address & 0xFF;
    data[2] = (value >> 8) & 0xFF;
    data[3] = value & 0xFF;
    i2c_master_transmit(curr_config.hi2cx, HM01B0_I2C_ADDRESS, data, 4, HM01B0_TIMEOUT);
}

static int hm01b0_reset(void)
{
		int retries;

    hm01b0_write_reg8(0x0103, 0x01);
    for (retries = 0; retries < 10000; retries++) {
        if (hm01b0_read_reg8(0x0100) == 0x00) {
            return 0;
        }
    }
    return -1;
}

int hm01b0_init(hm01b0_config_t* config)
{
    curr_config = *config;

    uint8_t readout_x_val;
    uint8_t readout_y_val;
    uint8_t binning_mode_val;
    uint8_t qvga_win_en_val;
    uint16_t frame_length_lines_val;
    uint16_t line_length_pclk_val;
    uint8_t bit_control_val;

    if (config->width == 320 && config->height == 320) {
        readout_x_val          = 0x01;
        readout_y_val          = 0x01;
        binning_mode_val       = 0x00;
        qvga_win_en_val        = 0x00;
        frame_length_lines_val = 0x0158;
        line_length_pclk_val   = 0x0178;
    } else if (config->width == 320 && config->height == 240) {
        readout_x_val          = 0x01;
        readout_y_val          = 0x01;
        binning_mode_val       = 0x00;
        qvga_win_en_val        = 0x01;
        frame_length_lines_val = 0x0104;
        line_length_pclk_val   = 0x0178;
    } else if (config->width == 160 && config->height == 120) {
        readout_x_val          = 0x03;
        readout_y_val          = 0x03;
        binning_mode_val       = 0x03;
        qvga_win_en_val        = 0x01;
        frame_length_lines_val = 0x0080;
        line_length_pclk_val   = 0x00D7;
    } else {
        return -1;
    }

    if (config->data_bits == 8) {
        bit_control_val = 0x02;
    } else if (config->data_bits == 4) {
        bit_control_val = 0x42;
    } else if (config->data_bits == 1) {
        bit_control_val = 0x22;
    } else {
        return -1;
    }

    uint16_t model_id = hm01b0_read_reg16(0x0000);
    if (model_id != 0x01b0) {
        return -1;
    }

    if (hm01b0_reset() != 0) {
        return -1;
    }

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

void hm01b0_set_coarse_integration(unsigned int lines)
{
    if (lines < 2) {
        lines = 2;
    } else if (lines > 0xffff) {
        lines = 0xffff;
    }
    lines -= 2;
    hm01b0_write_reg16(0x0202, lines); // INTEGRATION_H
    hm01b0_write_reg8(0x0104, 0x01); // GRP_PARAM_HOLD
}

