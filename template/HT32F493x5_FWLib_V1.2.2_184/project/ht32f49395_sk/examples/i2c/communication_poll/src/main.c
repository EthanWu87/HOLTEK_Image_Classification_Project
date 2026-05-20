#include "ht32f493x5_board.h"
#include "ht32f493x5_clock.h"
#include "i2c_application.h"

#define I2C_TIMEOUT                      0x10000

#define I2Cx_SPEED                       100000
#define I2Cx_ADDRESS                     0x24

#define I2Cx_PORT                        I2C3
#define I2Cx_CLK                         CRM_I2C3_PERIPH_CLOCK

#define I2Cx_SCL_PIN                     GPIO_PINS_8
#define I2Cx_SCL_GPIO_PORT               GPIOA
#define I2Cx_SCL_GPIO_CLK                CRM_GPIOA_PERIPH_CLOCK

#define I2Cx_SDA_PIN                     GPIO_PINS_9
#define I2Cx_SDA_GPIO_PORT               GPIOC
#define I2Cx_SDA_GPIO_CLK                CRM_GPIOC_PERIPH_CLOCK

i2c_handle_type hi2cx;

void i2c_lowlevel_init(i2c_handle_type* hi2c)
{
  gpio_init_type gpio_initstructure;

  if(hi2c->i2cx == I2Cx_PORT)
  {
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(I2Cx_CLK, TRUE);
    crm_periph_clock_enable(I2Cx_SCL_GPIO_CLK | I2Cx_SDA_GPIO_CLK, TRUE);

    gpio_initstructure.gpio_pins           = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    
    gpio_init(GPIOB, &gpio_initstructure);

    i2c_init(hi2c->i2cx, I2C_FSMODE_DUTY_2_1, I2Cx_SPEED);

    i2c_own_address1_set(hi2c->i2cx, I2C_ADDRESS_MODE_7BIT, I2Cx_ADDRESS);
  }
}

int main(void)
{
  i2c_status_type i2c_status;

  system_clock_config();

  ht32_board_init();

  uart_print_init(115200);

  hi2cx.i2cx = I2Cx_PORT;

  i2c_config(&hi2cx);

  while(1)
  {
    i2c_master_write_addr(&hi2cx, I2Cx_ADDRESS, I2C_TIMEOUT);
    
    delay_ms(1000);
  }
}
