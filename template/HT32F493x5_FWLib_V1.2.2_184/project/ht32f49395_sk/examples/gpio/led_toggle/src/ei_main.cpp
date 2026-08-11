#include "ei_main.h"                  
#include "ht32f493x5_board.h"          
#include "ht32f493x5_clock.h"
#include "ht32f493x5_conf.h"
#include <string.h>
#include "ei_run_classifier.h"         
#include "edge-impulse-sdk/porting/ei_classifier_porting.h" 
#include "math.h"
#include "hm01b0.h"

#define EI_TARGET_WIDTH  96
#define EI_TARGET_HEIGHT 96
#define EI_BUFFER_SIZE 9216

extern uint8_t hm01b0_frame_buffer[HM01B0_IMAGE_SIZE_BYTES];
extern volatile uint8_t g_frame_ready;

uint8_t edge_impulse_clean_buffer[EI_BUFFER_SIZE];

void usart_send_string(usart_type* usart_x, const char *s)
{
  while(*s)
  {
    while(usart_flag_get(usart_x, USART_TDBE_FLAG) == RESET);
    usart_data_transmit(usart_x, (uint16_t)(*s++));
  }
	
  while(usart_flag_get(usart_x, USART_TDC_FLAG) == RESET);
}

void read_hm01b0_data()
{
	int start_row = (120 - EI_TARGET_HEIGHT) / 2;
	int start_col = (160 - EI_TARGET_WIDTH) / 2;

	for(int r = 0; r < EI_TARGET_HEIGHT; r++)
	{
		uint8_t *src_ptr = &hm01b0_frame_buffer[(start_row + r) * 164 + 2 + start_col];
		
		memcpy(&edge_impulse_clean_buffer[r * EI_TARGET_WIDTH], src_ptr, EI_TARGET_WIDTH);
	}

	usart_send_string(USART2, "---FRAME_START---");
	for(uint32_t i = 0; i < EI_BUFFER_SIZE; i++)
	{
		while(usart_flag_get(USART2, USART_TDBE_FLAG) == RESET);
		usart_data_transmit(USART2, edge_impulse_clean_buffer[i]);
	}
	usart_send_string(USART2, "---FRAME_END---");
}

int raw_feature_get_data(size_t offset, size_t length, float *out_ptr)
{
    uint8_t *src = &edge_impulse_clean_buffer[offset];
    for (size_t i = 0; i < length; i++) {
        uint8_t gray = src[i];
        uint32_t rgb = (gray << 16) | (gray << 8) | gray;
        out_ptr[i] = (float)rgb;
    }
    return 0;
}

int ei_main(void)
{
	ei_impulse_result_t result = {0};

	while(1)
	{
		ei_printf("Edge Impulse standalone inferencing (ht32f493x5)\n");

		if(sizeof(edge_impulse_clean_buffer) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE)
		{
			ei_printf("The size of your buffer is not correct. Expected %d items, but had %u\n",
											EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(edge_impulse_clean_buffer));
			return 1;          
		}

		ei_printf("Entering the loop!\n");
			
		while(1)
		{
			ei_printf("\nStarting inferencing\r\n");
			//delay_ms(500);

			//ei_printf("Sampling...\n");
			//delay_ms(500);

			if(g_frame_ready)
			{
				nvic_irq_disable(HM01B0_VSYNC_IRQn);
				g_frame_ready = 0;

				read_hm01b0_data();

				exint_flag_clear(HM01B0_VSYNC_EXINT_LINE);
				nvic_irq_enable(HM01B0_VSYNC_IRQn, 0, 0);
				
				signal_t features_signal;
				features_signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
				features_signal.get_data = &raw_feature_get_data;

				EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, false);
				printf("success\n");
				
				if(res != 0)
				{
					return 1;
				}
				
				ei_printf("Predictions (DSP: %d ms., Classification: %d ms., Anomaly: %d ms.): \n",
						result.timing.dsp, result.timing.classification, result.timing.anomaly);

				#if EI_CLASSIFIER_OBJECT_DETECTION == 1
					ei_printf("Object detection bounding boxes:\r\n");
					for (uint32_t i = 0; i < result.bounding_boxes_count; i++)
					{
						ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
						ei_printf("  %s (", bb.label);
						ei_printf_float(bb.value);
						ei_printf(") [ x: %u, y: %u, width: %u, height: %u ]\r\n",
							bb.x,
							bb.y,
							bb.width,
							bb.height);
					}

				// Print the prediction results (classification)
				#else
					ei_printf("Predictions:\r\n");
					for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
						ei_printf("  %s: ", result.classification[i].label);
						ei_printf_float(result.classification[i].value);
						ei_printf("\r\n");
					}
				#endif
			}
		}
	}
}
