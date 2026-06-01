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
      // 1. 安全防護：立刻關閉 VSYNC 與 EXINT4 (HREF) 中斷，防止 UART 傳送時被干擾
      nvic_irq_disable(HM01B0_VSYNC_IRQn);
      nvic_irq_disable(EXINT4_IRQn);
      
      g_frame_ready = 0; 
      ht32_led_toggle(LED3);
      
      // 2. 發送影格同步標頭
      printf("---FRAME_START---");
      while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET); 

      // 3. 循序發送 164 * 120 = 19680 位元組的 Raw Data
      // (保留你 Python 目前設定的 WIDTH = 164，把整張圖乾淨送出)
      for(uint32_t i = 0; i < HM01B0_IMAGE_SIZE_BYTES; i++)
      {
          while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
          usart_data_transmit(USART1, hm01b0_frame_buffer[i]);
      }
      
      // 4. 關鍵修正：傳送完畢，清除傳送期間可能產生的 VSYNC 懸掛旗標
      exint_flag_clear(HM01B0_VSYNC_EXINT_LINE);
      exint_flag_clear(EXINT_LINE_4);
      
      // 5. 重新開啟中斷，迎接下一幀影像的抓取！
      nvic_irq_enable(HM01B0_VSYNC_IRQn, 0, 0);
      nvic_irq_enable(EXINT4_IRQn, 0, 0);
    }
  }
}
