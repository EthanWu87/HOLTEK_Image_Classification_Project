#include "ht32f493x5_board.h"
#include "ht32f493x5_clock.h"
#include "hm01b0.h"
#include "i2c_application.h"

i2c_handle_type hm01b0_hi2c;

int main(void)
{
  hm01b0_hi2c.i2cx = HM01B0_I2C_PORT;

  system_clock_config();
  
  ht32_board_init();

  uart_print_init(115200);

  hm01b0_init(&hm01b0_hi2c);

  while(1)
  {
    delay_ms(1000);
  }
}
