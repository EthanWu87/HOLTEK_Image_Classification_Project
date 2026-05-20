/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2023-02-08
 * @brief   SPI module example code.
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


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_pmu.h"
#include "hw_efuse.h"
#include "hw_gpio.h"
#include "hw_spi.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hw_dma.h"
#include "hal_pmu.h"

#include "app_cfg.h"
#include "type_def.h"
#include "boards.h"

#include "utility.h"
#include "app_debug.h"
#include "patch_hw_spi.h"


#define SPI_MASTER_BUF_SIZE             (10)
#define SPI_SLAVE_BUF_SIZE              (40)
static uint8_t pu8SlaveRecvBuf[SPI_SLAVE_BUF_SIZE];
static uint8_t pu8SlaveSendBuf[SPI_SLAVE_BUF_SIZE];
static uint8_t pu8MasterSendBuf[SPI_MASTER_BUF_SIZE];
static uint8_t pu8MasterRecvBuf[SPI_MASTER_BUF_SIZE];


/**
 * @brief  System power manage.
 */
static void system_power_init(void)
{
    rom_hw_pmu_set_ldo_act_voltage(EN_LDO_ACT_1200mV);
    rom_hw_pmu_set_ldo_dig_voltage(EN_LDO_DIG_1100mV);
    rom_hw_pmu_set_ldo_ret_sleep_voltage(EN_LDO_RET_1100mV);

    // Power selection
    rom_hal_pmu_sel_power_act_out_mode(PWR_SEL_LDO);
}

/**
 * @brief  System clock init.
 * @param  enSrc: System clock source selection, @ref EN_SYS_CLK_SRC_SEL_T.
 */
static void system_clock_init(EN_SYS_CLK_SRC_SEL_T enSysClkSrc)
{
    uint8_t u8Tune = 0;

    /* Set rc_hclk tune value */
    rom_hw_efuse_read_bytes(EFUSE_RC_HCLK_TUNE_ADDR, &u8Tune, sizeof(u8Tune));
    if (0 == u8Tune)
    {
        rom_hw_pmu_set_rc_hclk_tune(RC_HCLK_TUNE_DEFAUT_VAL);
    }

    /* Set rc32k tune value */
    rom_hw_efuse_read_bytes(EFUSE_RC_LCLK_TUNE_ADDR, &u8Tune, sizeof(u8Tune));
    if (u8Tune)
    {
        rom_hw_pmu_set_rc_lclk_tune(u8Tune);
    }
    else
    {
        rom_hw_pmu_set_rc_lclk_tune(RC_LCLK_TUNE_DEFAUT_VAL);
    }

    /* System clock */
    rom_hw_pmu_sel_dcxo_hclk_pwr(EN_DCXO_HCLK_PWR_VDDR);
    rom_hal_pmu_cfg_dcxo_hclk_param(DCXO_HCLK_IB_3, DCXO_HCLK_NGM_3, DCXO_HCLK_CAP_10PF);
    rom_hal_pmu_set_sys_clk_src(enSysClkSrc, DCXO_HCLK_STABLE_TIME_2500US);
}

/**
 * @brief  All peripheral init.
 */
static void peripheral_init(void)
{
    /* Disable MP all Peripheral interrupt. */
    rom_hw_sys_ctrl_peri_int_ctrl(SYS_CTRL_MP, 0, 0);

#if APP_DEBUG_ENABLED
    app_debug_init(GPIO_PORT_APP_DEBUG_TX, GPIO_PIN_APP_DEBUG_TX, UART_HANDLE_APP_DEBUG, UART_BPS_APP_DEBUG, NULL);

    PRINTF("[%s T %s]SPI example code start to work.\n", __DATE__, __TIME__);
#endif
}



EN_ERR_STA_T spi_example_master_transmit_bytes(uint8_t *u8TxBuf,uint16_t u16TxLen,uint32_t u32Timeout)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    rom_hw_gpio_set_pin_output_level(GPIO_MASTER_PORT_SPI_CS,GPIO_MASTER_PIN_SPI_CS,GPIO_LEVEL_LO);
    enRet = patch_hw_spi_transmit_bytes(SPI_MASTER_HANDLE,u8TxBuf,NULL,u16TxLen);
    rom_hw_gpio_set_pin_output_level(GPIO_MASTER_PORT_SPI_CS,GPIO_MASTER_PIN_SPI_CS,GPIO_LEVEL_HI);

    return enRet;
}

EN_ERR_STA_T spi_example_master_receive_bytes(uint8_t *u8RxBuf,uint16_t u16RxLen,uint32_t u32Timeout)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    rom_hw_gpio_set_pin_output_level(GPIO_MASTER_PORT_SPI_CS,GPIO_MASTER_PIN_SPI_CS,GPIO_LEVEL_LO);
    enRet = patch_hw_spi_transmit_bytes(SPI_MASTER_HANDLE,NULL,u8RxBuf,u16RxLen);
    rom_hw_gpio_set_pin_output_level(GPIO_MASTER_PORT_SPI_CS,GPIO_MASTER_PIN_SPI_CS,GPIO_LEVEL_HI);

    return enRet;
}


EN_ERR_STA_T spi_example_master_transmit_receive(uint8_t *u8TxBuf,uint8_t *u8RxBuf,uint16_t u16TrxLen,uint32_t u32Timeout)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    rom_hw_gpio_set_pin_output_level(GPIO_MASTER_PORT_SPI_CS,GPIO_MASTER_PIN_SPI_CS,GPIO_LEVEL_LO);
    enRet = patch_hw_spi_transmit_bytes(SPI_MASTER_HANDLE,u8TxBuf,u8RxBuf,u16TrxLen);
    rom_hw_gpio_set_pin_output_level(GPIO_MASTER_PORT_SPI_CS,GPIO_MASTER_PIN_SPI_CS,GPIO_LEVEL_HI);

    return enRet;
}



/**
 * @brief  SPI master example, flash erase, read and write.
 */
static void spi_example_master_init(void)
{
    // 1. Init GPIO.
    rom_hw_gpio_set_pin_pid(GPIO_MASTER_PORT_SPI_CLK, GPIO_MASTER_PIN_SPI_CLK, PID_SPI0_CLK);
    rom_hw_gpio_set_pin_pid(GPIO_MASTER_PORT_SPI_SI, GPIO_MASTER_PIN_SPI_SI, PID_SPI0_MOSI);
    rom_hw_gpio_set_pin_pid(GPIO_MASTER_PORT_SPI_SO, GPIO_MASTER_PIN_SPI_SO, PID_SPI0_MISO);
    
    rom_hw_gpio_set_pin_input_output(GPIO_MASTER_PORT_SPI_CS,GPIO_MASTER_PIN_SPI_CS,GPIO_MODE_OUTPUT);
    rom_hw_gpio_set_pin_output_level(GPIO_MASTER_PORT_SPI_CS,GPIO_MASTER_PIN_SPI_CS,GPIO_LEVEL_HI);
    
    // 2. Turn SPI clock gating on.
    rom_hw_crg_enable_clk_gate(CRG_SPI0_CLK_GATE);
    
    // 3. Init and enable spi module.
    stSpiInit_t stSpiInit;
    stSpiInit.u32ClkDiv = EN_SPI_CLK_DIV_16M_1M;
    stSpiInit.unSpiCfg.stSpiCfg.u8Enable = 1;
    stSpiInit.unSpiCfg.stSpiCfg.u8Cpha = SPI_CPHA_0_0;
    stSpiInit.unSpiCfg.stSpiCfg.u8WorkMode = SPI_MODE_MASTER;
    stSpiInit.unSpiCfg.stSpiCfg.u8RxTimeOut = 0xFF;
    stSpiInit.unSpiCfg.stSpiCfg.u8TrxMode = SPI_MODE_FULL_TXRX;
    stSpiInit.unSpiCfg.stSpiCfg.u8DataBits = SPI_DATA_BITS_8;
    stSpiInit.unSpiCfg.stSpiCfg.u8ByteWait = SPI_WORD_SPACE_DIS;
    stSpiInit.unSpiCfg.stSpiCfg.u8CsMode = SPI_SW_CS;
    stSpiInit.unSpiCfg.stSpiCfg.u8CsSwCtrl = SPI_SW_SET_CS_HIGH;
    
    rom_hw_spi_init(SPI_MASTER_HANDLE, &stSpiInit);
}


void DMA_IRQ6_Handler()
{
    uint8_t u8Flag = 0;
    uint16_t u16RxCnt;
    
    /* SPI Rx DMA */
    rom_hw_dma_get_interrupt_flag(DMA6,&u8Flag);
    if (u8Flag & DMA_INT_TIMEOUT)
    {
        rom_hw_dma_disable(DMA6);
        rom_hw_dma_get_trx_pointer(DMA6,&u16RxCnt);
        PRINTF("Slave Receive : ");
        for(int i=0;i<u16RxCnt;i++)
            PRINTF("%d ",pu8SlaveRecvBuf[i]);
        PRINTF("\r\n");
        
        rom_hw_dma_enable(DMA6);
    }
    rom_hw_dma_clear_interrupt_flag(DMA6,u8Flag);
    
    /* SPI Tx DMA */
    rom_hw_dma_get_interrupt_flag(DMA7,&u8Flag);
    if (u8Flag & DMA_INT_TOTAL_DONE)
    {
        PRINTF("Slave Tx One Loop\n");
    }
    rom_hw_dma_clear_interrupt_flag(DMA7,u8Flag);

}


void SPI1_IRQ_Handler()
{
    uint16_t u16Flag = 0;
    
    rom_hw_spi_get_interrupt_flag(SPI_SLAVE_HANDLE,&u16Flag);
    
    if (u16Flag & SPI_INT_TX_FINISHED)
    {
        uint32_t u32Cnt = 0;
        rom_hw_dma_get_circ_count(DMA7,&u32Cnt);
        rom_hw_dma_set_interval_tx_index(DMA7,(u32Cnt + SPI_SLAVE_BUF_SIZE/4) % SPI_SLAVE_BUF_SIZE);
    }
    rom_hw_spi_clear_interrupt_flag(SPI_SLAVE_HANDLE,u16Flag);
}


static void spi_example_slave_dma_init(void)
{
    stDmaInit_t stInit;

    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP,DMA_IRQ6);
    NVIC_ClearPendingIRQ(DMA_IRQ6);
    NVIC_SetPriority(DMA_IRQ6,0x02);
    NVIC_EnableIRQ(DMA_IRQ6);
    
    rom_hw_crg_enable_clk_gate(CRG_DMA_CLK_GATE);
    
    /* SPI Rx DMA */
    stInit.u32SrcAddr = (uint32_t) &SPI_SLAVE_HANDLE->SPI_RX_FIFO;
    stInit.u32DstAddr = (uint32_t) pu8SlaveRecvBuf;
    stInit.u32TimeOut = 1000;
    stInit.unPeriSel.stPeriSel.enPeriID = DMA_PERI_SPI1_RX;
    stInit.unCfg.u32DMACfg = DMA_INIT_PERI_TO_MEM_DEFAULT_CFG(SPI_SLAVE_BUF_SIZE,DMA_DATA_1BYTE);
    rom_hw_dma_init(DMA6,&stInit);
    
    rom_hw_dma_set_interrupt_channel(DMA6,DMA_INT6);
    rom_hw_dma_enable_interrupt(DMA6,DMA_INT_TIMEOUT);
    rom_hw_dma_enable(DMA6);
    
    /* SPI Tx DMA */
    stInit.u32SrcAddr = (uint32_t) pu8SlaveSendBuf;
    stInit.u32DstAddr = (uint32_t) &SPI_SLAVE_HANDLE->SPI_TX_FIFO;
    stInit.unCfg.u32DMACfg = DMA_INIT_MEM_TO_PERI_DEFAULT_CFG(SPI_SLAVE_BUF_SIZE,DMA_DATA_1BYTE);
    stInit.unPeriSel.stPeriSel.enPeriID = DMA_PERI_SPI1_TX;
    rom_hw_dma_init(DMA7,&stInit);
    
    rom_hw_dma_set_interrupt_channel(DMA7,DMA_INT6);
    rom_hw_dma_enable_interrupt(DMA7,DMA_INT_TOTAL_DONE);
    rom_hw_dma_enable(DMA7);
    
    rom_hw_dma_interval_tx_mode_enable(DMA7);
    rom_hw_dma_set_interval_tx_index(DMA7,SPI_SLAVE_BUF_SIZE/4);
}


static void spi_example_slave_init(void)
{
    // 1. Init GPIO.
    rom_hw_gpio_set_pin_pid(GPIO_SLAVE_PORT_SPI_CLK, GPIO_SLAVE_PIN_SPI_CLK, PID_SPI1_CLK);
    rom_hw_gpio_set_pin_pid(GPIO_SLAVE_PORT_SPI_SI, GPIO_SLAVE_PIN_SPI_SI, PID_SPI1_MOSI);
    rom_hw_gpio_set_pin_pid(GPIO_SLAVE_PORT_SPI_SO, GPIO_SLAVE_PIN_SPI_SO, PID_SPI1_MISO);
    rom_hw_gpio_set_pin_pid(GPIO_SLAVE_PORT_SPI_CS,GPIO_SLAVE_PIN_SPI_CS,PID_SPI1_CSN);
    
    // 2. Turn SPI clock gating on.
    rom_hw_crg_enable_clk_gate(CRG_SPI1_CLK_GATE);
    
    // 3. Init and enable spi module.
    stSpiInit_t stSpiInit;
    stSpiInit.u32ClkDiv = EN_SPI_CLK_DIV_16M_1M;
    stSpiInit.unSpiCfg.stSpiCfg.u8Enable = 1;
    stSpiInit.unSpiCfg.stSpiCfg.u8Cpha = SPI_CPHA_0_0;
    stSpiInit.unSpiCfg.stSpiCfg.u8WorkMode = SPI_MODE_SLAVE;
    stSpiInit.unSpiCfg.stSpiCfg.u8RxTimeOut = 0xFF;
    stSpiInit.unSpiCfg.stSpiCfg.u8TrxMode = SPI_MODE_FULL_TXRX;
    stSpiInit.unSpiCfg.stSpiCfg.u8DataBits = SPI_DATA_BITS_8;
    stSpiInit.unSpiCfg.stSpiCfg.u8ByteWait = SPI_WORD_SPACE_DIS;
    stSpiInit.unSpiCfg.stSpiCfg.u8CsMode = SPI_SW_CS;
    stSpiInit.unSpiCfg.stSpiCfg.u8CsSwCtrl = SPI_SW_SET_CS_HIGH;
    
    rom_hw_spi_init(SPI_SLAVE_HANDLE, &stSpiInit);

    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP,SPI1_IRQ);
    NVIC_ClearPendingIRQ(SPI1_IRQ);
    NVIC_SetPriority(SPI1_IRQ,0x02);
    NVIC_EnableIRQ(SPI1_IRQ);
    
    rom_hw_spi_enable_interrupt(SPI_SLAVE_HANDLE,SPI_INT_TX_FINISHED);

    rom_hw_spi_set_rxfifo_thld(SPI_SLAVE_HANDLE,1);
    spi_example_slave_dma_init();
}



/**
 * @brief  SPI module example code.
 */
static void spi_example(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    for (uint8_t i = 0;i<SPI_MASTER_BUF_SIZE;i++)
        pu8MasterSendBuf[i] = i;
    
    for (uint8_t i = SPI_SLAVE_BUF_SIZE;i>0;i--)
        pu8SlaveSendBuf[SPI_SLAVE_BUF_SIZE - i] = i;
    
    spi_example_slave_init();
    spi_example_master_init();
    
    while(1)
    {
        enRet = spi_example_master_transmit_bytes(pu8MasterSendBuf,SPI_MASTER_BUF_SIZE,1000);
        if (enRet != ERR_STA_OK)
            PRINTF("Master Transmit Failed\n");
        enRet = spi_example_master_receive_bytes(pu8MasterRecvBuf,SPI_MASTER_BUF_SIZE,1000);
        if (enRet != ERR_STA_OK)
            PRINTF("enRet : %d\n",enRet);
        else
        {
            /* Avoid log conflicts */
            rom_delay_ms(100);
            PRINTF("Master Receive : ");
            for(uint8_t i=0;i<SPI_MASTER_BUF_SIZE;i++)
                PRINTF("%d ",pu8MasterRecvBuf[i]);
            PRINTF("\r\n");
        }
        enRet = spi_example_master_transmit_receive(pu8MasterSendBuf,pu8MasterRecvBuf,SPI_MASTER_BUF_SIZE,1000);
        if (enRet != ERR_STA_OK)
            PRINTF("enRet : %d\n",enRet);
        else
        {
            /* Avoid log conflicts */
            rom_delay_ms(100);
            PRINTF("Master Receive : ");
            for(uint8_t i=0;i<SPI_MASTER_BUF_SIZE;i++)
                PRINTF("%d ",pu8MasterRecvBuf[i]);
            PRINTF("\r\n");
        }
        
        rom_delay_ms(1000);
    }
}

/**
 * @brief  SPI example code main function.
 * @return 0.
 */
int main(void)
{
    rom_hw_wdt_disable(WDT0);
    system_power_init();
    system_clock_init(EN_SYS_CLK_DCXO16M);
    peripheral_init();

    spi_example();

    for (;;)
        ;

    return 0;
}
