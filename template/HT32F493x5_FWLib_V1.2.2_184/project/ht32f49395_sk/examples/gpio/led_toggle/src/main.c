#include "ht32f493x5_board.h"
#include "ht32f493x5_clock.h"
#include "i2c_application.h"
#include "hm01b0.h"

i2c_handle_type hm01b0_hi2c;
uint8_t hm01b0_frame_buffer[HM01B0_IMAGE_SIZE_BYTES];
volatile uint8_t g_frame_ready = 0;

int main(void)
{
  hm01b0_hi2c.i2cx = HM01B0_I2C_PORT;

  system_clock_config();
  
  ht32_board_init();

  uart_print_init(921600);
  printf("\r\n--- System Starting ---\r\n");

  /* Initialize I2C and Registers */
  hm01b0_init(&hm01b0_hi2c);
  printf("I2C Init Done\r\n");

  /* Initialize SPI + DMA Data Path */
  hm01b0_spi_dma_init(hm01b0_frame_buffer, HM01B0_IMAGE_SIZE_BYTES);
  printf("SPI+DMA Init Done, Waiting for VSYNC...\r\n");

  while(1)
  {
    if(g_frame_ready)
    {
      g_frame_ready = 0; 
      
      /* Disable VSYNC interrupt during transmission */
      nvic_irq_disable(HM01B0_VSYNC_IRQn);
      
      ht32_led_toggle(LED3);
      
      printf("---FRAME_START---");
      /* 
         Critical Correction for Ghosting:
         Sensor outputs 162 pixels per line (160 active + 2 border).
         We capture 162 but only send 160 to match Python's 160x120 expectation.
         Skip bytes (y*162 + 0) and (y*162 + 1) which are the border pixels.
      */
      for(int y = 0; y < 120; y++)
      {
          for(int x = 0; x < 160; x++)
          {
              uint32_t index = (y * 162) + (x + 2);
              while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
              usart_data_transmit(USART1, hm01b0_frame_buffer[index]);
          }
      }
      
      /* Clear any pending VSYNC that happened during UART transmission */
      exint_flag_clear(HM01B0_VSYNC_EXINT_LINE);
      /* Re-enable VSYNC interrupt */
      nvic_irq_enable(HM01B0_VSYNC_IRQn, 0, 0);
    }
  }
}
