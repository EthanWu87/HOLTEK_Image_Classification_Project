#include "ht32f493x5_board.h"
#include "ht32f493x5_clock.h"
#include "i2c_application.h"
#include "hm01b0.h"

#define MS_TICK   (system_core_clock / 1000U)

extern int ei_main(void);

volatile uint8_t g_frame_ready = 0;

uint8_t hm01b0_frame_buffer[HM01B0_IMAGE_SIZE_BYTES];

i2c_handle_type hm01b0_hi2c;

/**
  * @brief  config systick and enable interrupt.
  * @param  none
  * @retval none
  */
static uint32_t systick_interrupt_config(uint32_t ticks)
{
  if((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);
  }

  SysTick->LOAD  = (uint32_t)(ticks - 1UL);
  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
  SysTick->VAL   = 0UL;
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

  return (0UL);
}

int main(void)
{
	system_clock_config();

	/* Config systick reload value and enable interrupt */
	systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
	systick_interrupt_config(MS_TICK);
	
	ht32_board_init();
	
	uart_print_init(2250000);
		
	i2c_handle_type hm01b0_hi2c;
	hm01b0_hi2c.i2cx = HM01B0_I2C_PORT;
	hm01b0_init(&hm01b0_hi2c);
	printf("I2C Init Done\r\n");
	
	hm01b0_spi_dma_init(hm01b0_frame_buffer, HM01B0_IMAGE_SIZE_BYTES);
	printf("SPI and DMA Init Done\r\n");
	
	ei_main();
	
	while(1)
	{

	}
}
