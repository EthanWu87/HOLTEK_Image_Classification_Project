#include "ht32f493x5_board.h"
#include "ht32f493x5_clock.h"
#include "i2c_application.h"
#include "hm01b0.h"

i2c_handle_type hm01b0_hi2c;
uint8_t hm01b0_frame_buffer[HM01B0_IMAGE_SIZE_BYTES];
uint8_t edge_impulse_clean_buffer[160 * 120];
volatile uint8_t g_frame_ready = 0;

int main(void)
{
  hm01b0_hi2c.i2cx = HM01B0_I2C_PORT;

  system_clock_config();
  
  ht32_board_init();

  uart_print_init(2000000);
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
      nvic_irq_disable(HM01B0_VSYNC_IRQn);
      nvic_irq_disable(EXINT4_IRQn);
      
      g_frame_ready = 0; 
      
      printf("---FRAME_START---");
      while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET); 

    for(int r = 0; r < 120; r++)
    {
      // 每行都跳過開頭的 2 個垃圾 Byte，精準複製 160 個有效像素到乾淨的 Buffer 中
      memcpy(&edge_impulse_clean_buffer[r * 160], (&hm01b0_frame_buffer[r * 164 + 2]), 160);
    }

      for(uint32_t i = 0; i < HM01B0_IMAGE_SIZE_BYTES; i++)
      {
          while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
          usart_data_transmit(USART1, edge_impulse_clean_buffer[i]);
      }
      
      exint_flag_clear(HM01B0_VSYNC_EXINT_LINE);
      exint_flag_clear(EXINT_LINE_4);
      
      nvic_irq_enable(HM01B0_VSYNC_IRQn, 0, 0);
      nvic_irq_enable(EXINT4_IRQn, 0, 0);
    }
  }
}
