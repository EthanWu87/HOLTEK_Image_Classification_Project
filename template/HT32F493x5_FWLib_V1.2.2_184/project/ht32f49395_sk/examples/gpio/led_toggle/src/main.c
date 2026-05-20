#include "ht32f493x5_board.h"
#include "ht32f493x5_clock.h"
#include "hm01b0.h"
#include "i2c_application.h"

i2c_handle_type hi2c;
hi2c.i2cx = i2cx;

int main(void)
{
  system_clock_config();
  
  ht32_board_init();

  uart_print_init(115200);

  uint8_t data = 0x55;


  while(1)
  {
        i2c_master_transmit(&hi2c, 0x24, &data, sizeof(data), I2C_TIMEOUT);


    delay_ms(1000);
  }
}
