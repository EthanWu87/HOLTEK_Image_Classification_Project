/*************************************************************************************************************
 * @file    RegHT32F675x5.h
 * @version V1.1
 * @date    2022-01-27
 * @brief   
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


#ifndef __REG_HT32F675X5_H__
#define __REG_HT32F675X5_H__

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(__MAIN_PROCESSOR)
    #include "ARMCM33_DSP_FP.h"
    #include "system_ARMCM33.h"
#elif defined(__CO_PROCESSOR)
    #include "ARMCM0plus.h"
    #include "system_ARMCM0plus.h"
#else
    #error "CORE unset"
#endif

//=====================================================================================
// Peripheral reg define
//=====================================================================================
#include "reg_adc.h"
#include "reg_adc_ana.h"
#include "reg_audio.h"
#include "reg_cache.h"
#include "reg_cpto.h"
#include "reg_crg.h"
#include "reg_dma.h"
#include "reg_ecc.h"
#include "reg_efuse.h"
#include "reg_gpio.h"
#include "reg_i2c.h"
#include "reg_i2s.h"
#include "reg_pmu.h"
#include "reg_qdec.h"
#include "reg_qspi.h"
#include "reg_rfsec.h"
#include "reg_rtc.h"
#include "reg_rtc_pdw.h"
#include "reg_spi.h"
#include "reg_stim.h"
#include "reg_sys_ctrl.h"
#include "reg_timer.h"
#include "reg_trng.h"
#include "reg_uart.h"
#include "reg_wdt.h"
#include "reg_cpto.h"
#include "reg_usb_ctrl.h"
#include "reg_usb_phy.h"
#include "ht32f675x5_reg.h"

//=====================================================================================
// Peripheral memory map
//=====================================================================================
#define ADDR_ROM_CODE_BASE     0x00000000 // Start: 0x00000000, End: 0x0001FFFF
#define ADDR_SRAM_CODE_BASE    0x00800000 // Start: 0x00800000, End: 0x0093FFFF
#define ADDR_QSPI0_CODE_BASE   0x10000000 // Start: 0x10000000, End: 0x11FFFFFF
#define ADDR_SRAM_DATA_BASE    0x20000000 // Start: 0x20000000, End: 0x2013FFFF
#define ADDR_QSPI0_DATA_BASE   0x30000000 // Start: 0x30000000, End: 0x31FFFFFF
#define ADDR_QSPI1_DATA_BASE   0x32000000 // Start: 0x32000000, End: 0x33FFFFFF
#define ADDR_ROM_DATA_BASE     0x3A000000 // Start: 0x3A000000, End: 0x3A01FFFF
#define ADDR_LLC_CFG_BASE      0x40000000 // Start: 0x40000000, End: 0x400003FF
#define ADDR_LLC_STA_BASE      0x40000400 // Start: 0x40000400, End: 0x400007FF
#define ADDR_TRNG_BASE         0x40001000 // Start: 0x40001000, End: 0x40001FFF
#define ADDR_RF_MDM_SECA_BASE  0x40008000 // Start: 0x40008000, End: 0x400087FF
#define ADDR_RF_MDM_SECB_BASE  0x40008800 // Start: 0x40008800, End: 0x40008883
#define ADDR_ADC_ANALOG0_BASE  0x40008884 // start: 0x40008884, End: 0x40008897
#define ADDR_ADC_ANALOG1_BASE  0x400088c8 // start: 0x400088c8, End: 0x400088dF
#define ADDR_RF_MDM_SECF_BASE  0x40009000 // Start: 0x40009000, End: 0x400097FF
#define ADDR_RF_MDM_SECG_BASE  0x40009800 // Start: 0x40009800, End: 0x40009FFF
#define ADDR_RF_MDM_SECR_BASE  0x4000A000 // Start: 0x4000A000, End: 0x4000A7FF
#define ADDR_RF_MDM_PMU_BASE   0x4000A800 // Start: 0x4000A800, End: 0x4000ABFF
#define ADDR_RF_MDM_TABLE_BASE 0x4000AC00 // Start: 0x4000AC00, End: 0x4000AFFF
#define ADDR_CPTO0_CFG_BASE    0x4000B000 // Start: 0x4000B000, End: 0x4000B3FF
#define ADDR_CPTO0_STA_BASE    0x4000B400 // Start: 0x4000B400, End: 0x4000B7FF
#define ADDR_CPTO1_CFG_BASE    0x4000C000 // Start: 0x4000B000, End: 0x4000B3FF
#define ADDR_QSPI0_CFG_BASE    0x50000000 // Start: 0x50000000, End: 0x50000FFF
#define ADDR_QSPI1_CFG_BASE    0x50001000 // Start: 0x50001000, End: 0x50001FFF
#define ADDR_QSPI2_CFG_BASE    0x50002000 // Start: 0x50002000, End: 0x50002FFF
#define ADDR_QSPI3_CFG_BASE    0x50003000 // Start: 0x50003000, End: 0x50003FFF
#define ADDR_SRAM_CACHE_BASE   0x50004000 // Start: 0x50004000, End: 0x50007FFF
#define ADDR_DMA_CFG_BASE      0x50008000 // Start: 0x50008000, End: 0x50008FFF
#define ADDR_CACHE_CFG_BASE    0x50009000 // Start: 0x50009000, End: 0x50009FFF
#define ADDR_PLCD_BASE         0x5000A000 // Start: 0x5000A000, End: 0x5000AFFF
#define ADDR_USB_CTRL_BASE     0x5000B000 // Start: 0x5000B000, End: 0x5000B01F
#define ADDR_USB_FIFO_BASE     0x5000B020 // Start: 0x5000B020, End: 0x5000B0FF
#define ADDR_USB_PHY_BASE      0x5000B100 // Start: 0x5000B100, End: 0x5000BFFF
#define ADDR_UART0_BASE        0x60000000 // Start: 0x60000000, End: 0x600003FF
#define ADDR_UART1_BASE        0x60000400 // Start: 0x60000400, End: 0x600007FF
#define ADDR_UART2_SCD_BASE    0x60000800 // Start: 0x60000800, End: 0x60000BFF
#define ADDR_SPI0_BASE         0x60001000 // Start: 0x60001000, End: 0x60001FFF
#define ADDR_SPI1_BASE         0x60002000 // Start: 0x60002000, End: 0x60002FFF
#define ADDR_I2C0_BASE         0x60003000 // Start: 0x60003000, End: 0x600033FF
#define ADDR_I2C1_BASE         0x60003400 // Start: 0x60003400, End: 0x600037FF
#define ADDR_I2C2_BASE         0x60003800 // Start: 0x60003800, End: 0x60003BFF
#define ADDR_I2C3_BASE         0x60003C00 // Start: 0x60003C00, End: 0x60003FFF
#define ADDR_IOMUX_BASE        0x60004000 // Start: 0x60004000, End: 0x60004FFF
#define ADDR_GPADC0_BASE       0x60020000 // Start: 0x60020000, End: 0x600203FF
#define ADDR_GPADC1_BASE       0x60020400 // Start: 0x60020400, End: 0x600207FF
#define ADDR_I2S_BASE          0x6002D000 // Start: 0x6002D000, End: 0x6002D3FF
#define ADDR_CIC0_BASE         0x6002E000 // Start: 0x6002E000, End: 0x6002E3FF
#define ADDR_CIC1_BASE         0x6002E400 // Start: 0x6002E400, End: 0x6002E7FF
#define ADDR_EFUSE_ARRY_BASE   0x6002F000 // Start: 0x6002F000, End: 0x6002F3FF
#define ADDR_EFUSE_REG_BASE    0x6002F400 // Start: 0x6002F400, End: 0x6002FFFF
#define ADDR_QDEC_BASE         0x60035000 // Start: 0x60035000, End: 0x60030FFF
#define ADDR_GTIM0_BASE        0x60032000 // Start: 0x60032000, End: 0x60032FFF
#define ADDR_GTIM1_BASE        0x60033000 // Start: 0x60033000, End: 0x60033FFF
#define ADDR_GTIM2_BASE        0x6003B000 // Start: 0x6003B000, End: 0x6003BFFF
#define ADDR_GTIM3_BASE        0x6003C000 // Start: 0x6003C000, End: 0x6003CFFF
#define ADDR_GPIO_BASE         0x6004B000 // Start: 0x6004B000, End: 0x6004BFFF
#define ADDR_GPIOA_BASE        0x6004B000 // Start: 0x6004B000, End: 0x6004B038
#define ADDR_GPIOB_BASE        0x6004B080 // Start: 0x6004B080, End: 0x6004B0B8
#define ADDR_GPIOC_BASE        0x6004B0BC // Start: 0x6004B0BC, End: 0x6004B0F4
#define ADDR_GPIO_WAKEUP       0x6004B100 // Start: 0x6004B100, End: 0x6004B108
#define ADDR_GPIO_SWD_CP_BASE  0x6004B140 // Start: 0x6004B140, End: 0x6004B154
#define ADDR_GPIO_SWD_MP_BASE  0x6004B158 // Start: 0x6004B158, End: 0x6004B16C
#define ADDR_GPIO_DBG_BASE     0x6004B170 // Start: 0x6004B170, End: 0x6004B174
#define ADDR_RTC_BASE          0x6004D000 // Start: 0x6004D000, End: 0x6004D3FF
#define ADDR_RTC_PDW_BASE      0x6004D400 // Start: 0x6004D400, End: 0x6004D7FF
#define ADDR_WDT_BASE          0x6004E000 // Start: 0x6004E000, End: 0x6004EFFF
#define ADDR_CRG_BASE          0x6004F000 // Start: 0x6004F000, End: 0x6004FFFF
#define ADDR_PMU_BASE          0x60050000 // Start: 0x60050000, End: 0x60050FFF
#define ADDR_SYS_CTRL_BASE     0x60051000 // Start: 0x60051000, End: 0x60051FFF
#define ADDR_STIM0_BASE        0x60052000 // Start: 0x60052000, End: 0x60052FFF
#define ADDR_STIM1_BASE        0x60053000 // Start: 0x60053000, End: 0x60053FFF
#define ADDR_END               0x60054000

/* --------------------------  Peripheral define  ------------------------------ */
// #define LLC_CFG               ((stLLC_CFG_Handle_t *)ADDR_LLC_CFG_BASE)
#define CPTO0                  ((stCPTO_Handle_t *)ADDR_CPTO0_CFG_BASE)
#define CPTO1                  ((stCPTO_Handle_t *)ADDR_CPTO1_CFG_BASE)
#define TRNG                   ((stTRNG_Handle_t *)ADDR_TRNG_BASE)
#define QSPI0                  ((stQSPI_Handle_t *)ADDR_QSPI0_CFG_BASE)
#define QSPI1                  ((stQSPI_Handle_t *)ADDR_QSPI1_CFG_BASE)
#define FLASH                  (QSPI0)
#define FLASH0                 (QSPI0)
#define FLASH1                 (QSPI1)
#define DMA0                   ((stDMA_Handle_t *)(ADDR_DMA_CFG_BASE))         // 0x50008000
#define DMA1                   ((stDMA_Handle_t *)(ADDR_DMA_CFG_BASE + 0x40))  // 0x50008040
#define DMA2                   ((stDMA_Handle_t *)(ADDR_DMA_CFG_BASE + 0x80))  // 0x50008080
#define DMA3                   ((stDMA_Handle_t *)(ADDR_DMA_CFG_BASE + 0xC0))  // 0x500080C0
#define DMA4                   ((stDMA_Handle_t *)(ADDR_DMA_CFG_BASE + 0x100)) // 0x50008100
#define DMA5                   ((stDMA_Handle_t *)(ADDR_DMA_CFG_BASE + 0x140)) // 0x50008140
#define DMA6                   ((stDMA_Handle_t *)(ADDR_DMA_CFG_BASE + 0x180)) // 0x50008180
#define DMA7                   ((stDMA_Handle_t *)(ADDR_DMA_CFG_BASE + 0x1C0)) // 0x500081C0
#define CACHE                  ((stCACHE_Handle_t *)ADDR_CACHE_CFG_BASE)
#define UART0                  ((stUART_Handle_t *)ADDR_UART0_BASE)
#define UART1                  ((stUART_Handle_t *)ADDR_UART1_BASE)
#define UART2                  ((stUART_Handle_t *)ADDR_UART2_SCD_BASE)
#define SPI0                   ((stSPI_Handle_t *)ADDR_SPI0_BASE)
#define SPI1                   ((stSPI_Handle_t *)ADDR_SPI1_BASE)
#define I2C0                   ((stI2C_Handle_t *)ADDR_I2C0_BASE)
#define I2C1                   ((stI2C_Handle_t *)ADDR_I2C1_BASE)
#define I2C2                   ((stI2C_Handle_t *)ADDR_I2C2_BASE)
#define I2C3                   ((stI2C_Handle_t *)ADDR_I2C3_BASE)
#define IOMUX                  ((stIOMUX_Handle_t *)ADDR_IOMUX_BASE)
#define ADC0                   ((stADC_Handle_t *)ADDR_GPADC0_BASE)
#define ADC1                   ((stADC_Handle_t *)ADDR_GPADC1_BASE)
#define ADC_ANA0               ((stADC_Analog_Handle_t *)ADDR_ADC_ANALOG0_BASE)
#define ADC_ANA1               ((stADC_Analog_Handle_t *)ADDR_ADC_ANALOG1_BASE)
#define I2S                    ((stI2S_Handle_t *)ADDR_I2S_BASE)
#define AUDIO0                 ((stAUDIO_Handle_t *)ADDR_CIC0_BASE)
#define AUDIO1                 ((stAUDIO_Handle_t *)ADDR_CIC1_BASE)
#define EFUSE_ARRAY            ((volatile uint32_t *)ADDR_EFUSE_ARRY_BASE)
#define EFUSE                  ((stEFUSE_Handle_t *)ADDR_EFUSE_REG_BASE)
#define QDEC                   ((stQDEC_Handle_t *)ADDR_QDEC_BASE)
#define USB_CTRL               ((stUSBCtrl_Handle_t *)ADDR_USB_CTRL_BASE)
#define USB_FIFO               ((volatile uint32_t *)ADDR_USB_FIFO_BASE)
#define USB_PHY                ((stUSBPHY_Handle_t *)ADDR_USB_PHY_BASE)
#define TIMER0                 ((stTIMER_Handle_t *)ADDR_GTIM0_BASE)
#define TIMER1                 ((stTIMER_Handle_t *)ADDR_GTIM1_BASE)
#define TIMER2                 ((stTIMER_Handle_t *)ADDR_GTIM2_BASE)
#define TIMER3                 ((stTIMER_Handle_t *)ADDR_GTIM3_BASE)
#define IR0                    (TIMER0)
#define IR1                    (TIMER1)
#define IR2                    (TIMER2)
#define IR3                    (TIMER3)
#define GPIOA                  ((stGPIO_Handle_t *)ADDR_GPIOA_BASE)
#define GPIOB                  ((stGPIO_Handle_t *)ADDR_GPIOB_BASE)
#define GPIOC                  ((stGPIO_Handle_t *)ADDR_GPIOC_BASE)
#define GPIO_WAKEUP            ((stGPIO_WAKEUP_Handle_t *)ADDR_GPIO_WAKEUP)
#define GPIO_SWD_CP            ((stGPIO_SWD_Handle_t *)ADDR_GPIO_SWD_CP_BASE)
#define GPIO_SWD_MP            ((stGPIO_SWD_Handle_t *)ADDR_GPIO_SWD_MP_BASE)
#define GPIO_DBG               ((stGPIO_DBG_Handle_t *)ADDR_GPIO_DBG_BASE)
#define RTC                    ((stRTC_Handle_t *)ADDR_RTC_BASE)
#define RTC_PDW                ((stRTC_PDW_Handle_t *)ADDR_RTC_PDW_BASE)
#define WDT0                   ((stWDT_Handle_t *)ADDR_WDT_BASE)
#define WDT1                   ((stWDT_Handle_t *)(ADDR_WDT_BASE + 0x800))
#define CRG                    ((stCRG_Handle_t *)ADDR_CRG_BASE)
#define PMU                    ((stPMU_Handle_t *)ADDR_PMU_BASE)
#define SYS_CTRL               ((stSYSCTRL_Handle_t *)ADDR_SYS_CTRL_BASE)
#define STIM0                  ((stSTIM_Handle_t *)ADDR_STIM0_BASE)
#define STIM1                  ((stSTIM_Handle_t *)ADDR_STIM1_BASE)

#ifdef __cplusplus
}
#endif

#endif /* __REG_HT32F675X5_H__ */
