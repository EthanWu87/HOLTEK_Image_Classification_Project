/*********************************************************************************************************//**
 * @file    ht32f493x5_int.c
 * @version $Rev:: 143         $
 * @date    $Date:: 2025-05-08 #$
 * @brief   main interrupt service routines.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* includes ------------------------------------------------------------------*/
#include "ht32f493x5_board.h"
#include "ht32f493x5_int.h"

/** @addtogroup HT32F493x5_periph_examples
  * @{
  */

/** @addtogroup HT32F493x5_GPIO_led_toggle
  * @{
  */

/**
  * @brief  this function handles nmi exception.
  * @param  none
  * @retval none
  */
void NMI_Handler(void)
{
}

/**
  * @brief  this function handles hard fault exception.
  * @param  none
  * @retval none
  */
void HardFault_Handler(void)
{
  /* go to infinite loop when hard fault exception occurs */
  while(1)
  {
  }
}

/**
  * @brief  this function handles memory manage exception.
  * @param  none
  * @retval none
  */
void MemManage_Handler(void)
{
  /* go to infinite loop when memory manage exception occurs */
  while(1)
  {
  }
}

/**
  * @brief  this function handles bus fault exception.
  * @param  none
  * @retval none
  */
void BusFault_Handler(void)
{
  /* go to infinite loop when bus fault exception occurs */
  while(1)
  {
  }
}

/**
  * @brief  this function handles usage fault exception.
  * @param  none
  * @retval none
  */
void UsageFault_Handler(void)
{
  /* go to infinite loop when usage fault exception occurs */
  while(1)
  {
  }
}

/**
  * @brief  this function handles svcall exception.
  * @param  none
  * @retval none
  */
void SVC_Handler(void)
{
}

/**
  * @brief  this function handles debug monitor exception.
  * @param  none
  * @retval none
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  this function handles pendsv_handler exception.
  * @param  none
  * @retval none
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  this function handles systick handler.
  * @param  none
  * @retval none
  */
void SysTick_Handler(void)
{
}

#include "hm01b0.h"

/**
  * @brief  this function handles VSYNC interrupt on EXINT LINE 0 (PB0).
  */
void EXINT0_IRQHandler(void)
{
  if(exint_interrupt_flag_get(HM01B0_VSYNC_EXINT_LINE) != RESET)
  {
    dma_channel_enable(HM01B0_DMA_CHANNEL, FALSE);
    spi_enable(HM01B0_SPI_PORT, FALSE); 
    
    (void)HM01B0_SPI_PORT->sts;
    (void)HM01B0_SPI_PORT->dt;
    
    dma_data_number_set(HM01B0_DMA_CHANNEL, HM01B0_IMAGE_SIZE_BYTES);

    spi_enable(HM01B0_SPI_PORT, TRUE);
    dma_channel_enable(HM01B0_DMA_CHANNEL, TRUE);
        
    ht32_led_on(LED2);
    exint_flag_clear(HM01B0_VSYNC_EXINT_LINE);
  }
}

/**
  * @brief  this function handles HREF interrupt on EXINT LINE 4 (PA4).
  *         It simulates "Hardware Trigger" by toggling SPI Software NSS.
  */
// void EXINT4_IRQHandler(void)
// {
//   if(exint_interrupt_flag_get(EXINT_LINE_4) != RESET)
//   {
//     /* HREF 狀態改變 (PA4) */
//     if(gpio_input_data_bit_read(HM01B0_HREF_PORT, HM01B0_HREF_PIN) != RESET)
//     {
//        /* HREF High -> Line Start -> SPI NSS Low (Selected) */
//        spi_software_cs_internal_level_set(HM01B0_SPI_PORT, SPI_SWCS_INTERNAL_LEVEL_LOW);
//     }
//     else
//     {
//        /* HREF Low -> Line End -> SPI NSS High (Deselected) */
//        spi_software_cs_internal_level_set(HM01B0_SPI_PORT, SPI_SWCS_INTERNAL_LEVEL_HIGHT);
//     }
    
//     exint_flag_clear(EXINT_LINE_4);
//   }
// }

/**
  * @brief  this function handles DMA1 Channel 2 interrupt (SPI RX Done).
  */
void DMA1_Channel2_IRQHandler(void)
{
  if(dma_interrupt_flag_get(DMA1_FDT2_FLAG) != RESET)
  {
    g_frame_ready = 1;
  
    dma_flag_clear(DMA1_FDT2_FLAG);
  }
}

/**
  * @}
  */

/**
  * @}
  */
