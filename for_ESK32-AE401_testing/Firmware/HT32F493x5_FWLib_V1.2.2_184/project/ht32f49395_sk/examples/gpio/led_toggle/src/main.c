#include "ht32f493x5_board.h"
#include "ht32f493x5_clock.h"
#include "i2c_application.h"
#include "hm01b0.h"

#define EI_TARGET_WIDTH  96
#define EI_TARGET_HEIGHT 96
#define EI_BUFFER_SIZE 9216

i2c_handle_type hm01b0_hi2c;

uint8_t hm01b0_frame_buffer[HM01B0_IMAGE_SIZE_BYTES];
uint8_t edge_impulse_clean_buffer[EI_BUFFER_SIZE];

volatile uint8_t g_frame_ready = 0;

int main(void)
{
  hm01b0_hi2c.i2cx = HM01B0_I2C_PORT;

  system_clock_config();
  
  ht32_board_init();

  uart_print_init(2250000);
  printf("\r\n--- System Starting ---\r\n");

  /* Initialize I2C and Registers */
  hm01b0_init(&hm01b0_hi2c);
  printf("I2C Init Done\r\n");

  /* Initialize SPI + DMA Data Path */
	hm01b0_parallel_dma_init(hm01b0_frame_buffer, HM01B0_IMAGE_SIZE_BYTES);
  printf("SPI+DMA Init Done, Waiting for VSYNC...\r\n");

  while(1)
  {
    if(g_frame_ready)
    {
		  exint_flag_clear(HM01B0_VSYNC_EXINT_LINE);
      nvic_irq_disable(HM01B0_VSYNC_IRQn);
			
      g_frame_ready = 0; 
	

			
			uint8_t width_offset  = HM01B0_IMAGE_WIDTH_DUMMY / 2;
			uint8_t height_offset = HM01B0_IMAGE_HEIGHT_DUMMY / 2;
			int start_col = ((HM01B0_IMGAE_WIDTH_EFFECTIVE - EI_TARGET_WIDTH) / 2) + width_offset;
			int start_row = ((HM01B0_IMGAE_HEIGHT_EFFECTIVE - EI_TARGET_HEIGHT) / 2) + height_offset;
			
			printf("IMG_S");   // image start header 
			for(int r = 0; r < EI_TARGET_HEIGHT; r++)
			{
				uint8_t *src_ptr = &hm01b0_frame_buffer[(start_row + r) * HM01B0_IMAGE_WIDTH_ACTIVE + start_col];
				uint8_t *dest_ptr = &edge_impulse_clean_buffer[r * EI_TARGET_WIDTH];
				
				memcpy(dest_ptr, src_ptr, EI_TARGET_WIDTH);
				
				for(int c = 0; c < EI_TARGET_WIDTH; c++)
				{
					while(usart_flag_get(USART1, USART_TDBE_FLAG) == RESET);
					usart_data_transmit(USART1, dest_ptr[c]);
				}
			}
			printf("IMG_E\r\n");

      nvic_irq_enable(HM01B0_VSYNC_IRQn, 0, 0);
    }
  }
}
