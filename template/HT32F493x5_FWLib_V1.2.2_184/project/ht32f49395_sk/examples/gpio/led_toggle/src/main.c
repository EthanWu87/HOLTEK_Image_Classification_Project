#include "ht32f493x5_board.h"
#include "ht32f493x5_clock.h"
#include "i2c_application.h"
#include "hm01b0.h"

extern int ei_main(void);

i2c_handle_type hm01b0_hi2c;

uint8_t hm01b0_frame_buffer[HM01B0_IMAGE_SIZE_BYTES];
volatile uint8_t g_frame_ready = 0;

void cam_view_uart_init()
{
	gpio_init_type gpio_init_struct;

	crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

	gpio_default_para_init(&gpio_init_struct);

  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_2;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PRINT_UART_TX_GPIO, &gpio_init_struct);	
	
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_3;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init(PRINT_UART_RX_GPIO, &gpio_init_struct);
	
	usart_init(USART2, 921600, USART_DATA_8BITS, USART_STOP_1_BIT);
  usart_transmitter_enable(USART2, TRUE);
	usart_receiver_enable(USART2, TRUE);
  usart_enable(USART2, TRUE);
}

int main(void)
{
	system_clock_config();
	
	//SysTick_Config(240000U);
	
	ht32_board_init();
	
	uart_print_init(115200);
	
	cam_view_uart_init();
	
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
