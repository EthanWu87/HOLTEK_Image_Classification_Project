/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2024-05-21
 * @brief   I2C module example code.
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
#include "hw_i2c.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hal_pmu.h"
#include "hw_dma.h"
#include "patch_hw_i2c.h"

#include "app_cfg.h"
#include "type_def.h"
#include "boards.h"

#include "utility.h"
#include "app_debug.h"

typedef enum
{
    EN_I2C_EXAMPLE_MASTER_BLOCK,
    EN_I2C_EXAMPLE_SLAVE_BLOCK,
    EN_I2C_EXAMPLE_SLAVE_DMA,
}EN_I2C_EXAMPLE_T;

#define I2C_BUF_SIZE    (32)
static uint8_t gpu8MasterSendData[I2C_BUF_SIZE];
static uint8_t gpu8MasterRecvData[I2C_BUF_SIZE];
static uint8_t gpu8SlaveSendData[I2C_BUF_SIZE];
static uint8_t gpu8SlaveRecvData[I2C_BUF_SIZE];

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

    PRINTF("[%s T %s]I2C example code start to work.\n", __DATE__, __TIME__);
#endif
}

static EN_ERR_STA_T i2c_example_slave_read_by_dma(stI2C_Handle_t *pstI2C,stDMA_Handle_t *pstDMA, uint8_t *pu8RxBuf, uint16_t u16Len)
{
    uint32_t u32DmaCfg;
    EN_ERR_STA_T enRet;
    
    if (NULL == pstI2C || NULL == pstDMA || NULL == pu8RxBuf || 0 == u16Len)
        return ERR_PARA_ERR;
    
    /* Set DMA Src Addr */
    pstDMA->DMA_SRC_ADDR = (uint32_t)&pstI2C->I2C_RX_FIFO;
    
    /* Set DMA Dst Addr */
    pstDMA->DMA_DST_ADDR = (uint32_t)pu8RxBuf;
    
    /* Set DMA Recv Data Length */
    u32DmaCfg = pstDMA->DMA_CFG;
    
    u32DmaCfg &= ~(DMA_LENGTH_VAL_MSK << DMA_LENGTH_VAL_SHIFT);
    u32DmaCfg |= (u16Len & DMA_LENGTH_VAL_MSK) << 0;
    
    pstDMA->DMA_CFG = u32DmaCfg;

    /* Set I2C Rx Thld */
    enRet = rom_hw_i2c_set_rxfifo_thld(pstI2C,1);
    ERR_RETURN_IF_ERROR(enRet);
    
    enRet = rom_hw_dma_clear_interrupt_flag(pstDMA,DMA_INT_MSK);
    ERR_RETURN_IF_ERROR(enRet);
    
    /* Enable DMA Interrupt */
    enRet = rom_hw_dma_enable_interrupt(pstDMA,DMA_INT_4_4_DONE);
    ERR_RETURN_IF_ERROR(enRet);
    
    /* Enable DMA */
    enRet = rom_hw_dma_enable(pstDMA);
    ERR_RETURN_IF_ERROR(enRet);
    
    return ERR_STA_OK;
}

static EN_ERR_STA_T i2c_example_slave_write_by_dma(stI2C_Handle_t *pstI2C,stDMA_Handle_t *pstDMA, uint8_t *pu8TxBuf, uint16_t u16Len)
{
    uint32_t u32DmaCfg;
    EN_ERR_STA_T enRet;
    
    if (NULL == pstI2C || NULL == pstDMA || NULL == pu8TxBuf || 0 == u16Len)
        return ERR_PARA_ERR;
    
    /* Set DMA Src Addr */
    pstDMA->DMA_SRC_ADDR = (uint32_t)pu8TxBuf;
    
    /* Set DMA Dst Addr */
    pstDMA->DMA_DST_ADDR = (uint32_t)&pstI2C->I2C_TX_FIFO;
    
    /* Set DMA Send Data Length */
    u32DmaCfg = pstDMA->DMA_CFG;
    
    u32DmaCfg &= ~(DMA_LENGTH_VAL_MSK << DMA_LENGTH_VAL_SHIFT);
    u32DmaCfg |= (u16Len & DMA_LENGTH_VAL_MSK) << 0;
    
    pstDMA->DMA_CFG = u32DmaCfg;
    
    enRet = rom_hw_dma_clear_interrupt_flag(pstDMA,DMA_INT_MSK);
    ERR_RETURN_IF_ERROR(enRet);
    
    /* Enable DMA Interrupt */
    enRet = rom_hw_dma_enable_interrupt(pstDMA,DMA_INT_4_4_DONE);
    ERR_RETURN_IF_ERROR(enRet);
    
    enRet = rom_hw_dma_set_interval_tx_index(pstDMA, 0);
    ERR_RETURN_IF_ERROR(enRet);
    
    /* Enable DMA */
    enRet = rom_hw_dma_enable(pstDMA);
    ERR_RETURN_IF_ERROR(enRet);
    
    return ERR_STA_OK;
}

static void i2c_example_irq_handler(void)
{
    uint16_t u16IntFlag;
    uint16_t u16RecvCnt = 0;
    
    rom_hw_i2c_get_interrupt_flag(I2C_HANDLE,&u16IntFlag);

    if (u16IntFlag & I2C_INT_RXFIFO_NOT_EMPTY)
    {
        while(I2C_HANDLE->I2C_RXFIFO_CNT && u16RecvCnt < I2C_BUF_SIZE)
        {
            gpu8SlaveRecvData[u16RecvCnt++] = I2C_HANDLE->I2C_RX_FIFO;
        }
        if (u16RecvCnt)
        {
            for (int i=0;i<u16RecvCnt;i++)
            {
                PRINTF("%02X ",gpu8SlaveRecvData[i]);
            }
            u16RecvCnt = 0;
        }
    }

    rom_hw_i2c_clear_interrupt_flag(I2C_HANDLE,u16IntFlag);
}

void I2C0_IRQ_Handler(void)
{
    i2c_example_irq_handler();
}

void I2C1_IRQ_Handler(void)
{
    i2c_example_irq_handler();
}

void I2C2_IRQ_Handler(void)
{
    i2c_example_irq_handler();
}

void DMA_IRQ6_Handler()
{
    uint8_t u8IntFlag;
    uint16_t u16RxCnt;
    rom_hw_dma_get_interrupt_flag(I2C_RX_DMA_HANDLE,&u8IntFlag);
    rom_hw_dma_clear_interrupt_flag(I2C_RX_DMA_HANDLE,u8IntFlag);
    
    if (u8IntFlag & DMA_INT_4_4_DONE)
    {
        rom_hw_dma_get_trx_pointer(I2C_RX_DMA_HANDLE,&u16RxCnt);
        rom_hw_dma_disable(I2C_RX_DMA_HANDLE);
        PRINTF("rx done\n");
        for(int i=0;i<u16RxCnt;i++)
        {
            PRINTF("%02X ",gpu8SlaveRecvData[i]);
        }
        PRINTF("\n");
        i2c_example_slave_read_by_dma(I2C_HANDLE,I2C_RX_DMA_HANDLE,gpu8SlaveRecvData,sizeof(gpu8SlaveRecvData));
    }
    
    u8IntFlag = 0;
    rom_hw_dma_get_interrupt_flag(I2C_TX_DMA_HANDLE,&u8IntFlag);
    rom_hw_dma_clear_interrupt_flag(I2C_TX_DMA_HANDLE,u8IntFlag);
    
    if (u8IntFlag & DMA_INT_4_4_DONE)
    {
        rom_hw_dma_disable(I2C_TX_DMA_HANDLE);
        
        PRINTF("tx done\n");
        i2c_example_slave_write_by_dma(I2C_HANDLE,I2C_TX_DMA_HANDLE,gpu8SlaveSendData,sizeof(gpu8SlaveSendData));
    }
}

static void i2c_example_clk_and_gpio_init(void)
{
    EN_GPIO_PID_T enSclkPid;
    EN_GPIO_PID_T enSdaPid;
    EN_CRG_CLK_GATE_T enClkGate;
    
    if (I2C0 == I2C_HANDLE)
    {
        enClkGate = CRG_I2C0_CLK_GATE;
        enSclkPid = PID_I2C0_SCL;
        enSdaPid = PID_I2C0_SDA;
    }
    else if (I2C1 == I2C_HANDLE)
    {
        enClkGate = CRG_I2C1_CLK_GATE;
        enSclkPid = PID_I2C1_SCL;
        enSdaPid = PID_I2C1_SDA;
    }
    else
    {
        enClkGate = CRG_I2C2_CLK_GATE;
        enSclkPid = PID_I2C2_SCL;
        enSdaPid = PID_I2C2_SDA;
    }
    
    /* Enable Clock */
    rom_hw_crg_enable_clk_gate(enClkGate);
    /* IO Multiplexing */
    rom_hw_gpio_set_pin_pid(GPIO_PORT_I2C_SCLK,GPIO_PIN_I2C_SCLK,enSclkPid);
    rom_hw_gpio_set_pin_pid(GPIO_PORT_I2C_SDA,GPIO_PIN_I2C_SDA,enSdaPid);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_I2C_SCLK,GPIO_PIN_I2C_SCLK,GPIO_PULL_UP);
    rom_hw_gpio_set_pin_pull_mode(GPIO_PORT_I2C_SDA,GPIO_PIN_I2C_SDA,GPIO_PULL_UP);
}

static void i2c_example_master_init(void)
{
    i2c_example_clk_and_gpio_init();
    
    stI2cMasterInit_t stInit;
    stInit.u32BaudRate = I2C_BAUDRATE_100K;
    stInit.u16SlaveAddr = 0x6A;
    stInit.unCfg.stCfg.u8AddrMode = I2C_ADDR_MODE_7_BITS;
    stInit.unCfg.stCfg.u8StretchEn = I2C_STRETCH_ENABLE;
    stInit.unCfg.stCfg.u8TrxMode = I2C_MASTER_MODE_READ;
    stInit.unCfg.stCfg.u8Enable = I2C_ENABLE;
    
    rom_hw_i2c_master_init(I2C_HANDLE,&stInit);
    
    for (int i=0;i<I2C_BUF_SIZE;i++)
    {
        gpu8MasterSendData[i] = i;
    }
}

static void i2c_example_master_block(void)
{
    EN_ERR_STA_T enRet;
    EN_I2C_MASTER_STAT_T enMasterSta;
    
    i2c_example_master_init();
    
    while(1)
    {
        rom_delay_ms(10);
        
        enMasterSta = patch_hw_i2c_master_write(I2C_HANDLE,gpu8MasterSendData,sizeof(gpu8MasterSendData),1);
        if (EN_I2C_MASTER_STAT_OK != enMasterSta)
        {
            PRINTF("Master Write Failed : %d\n",enMasterSta);
            continue;
        }
        
        rom_delay_ms(100);
        
        enMasterSta = patch_hw_i2c_master_read(I2C_HANDLE,gpu8MasterRecvData,sizeof(gpu8MasterRecvData),0);
        if (EN_I2C_MASTER_STAT_OK != enMasterSta) // GNU Warning Issue
        {
            PRINTF("Master Read Failed : %d\n",enMasterSta);
            continue;
        }

        enRet = patch_hw_i2c_master_send_stop(I2C_HANDLE);
        if (ERR_STA_OK != enRet)
        {
            PRINTF("Master Send Stop Failed : %d\n",enRet);
            continue;
        }
        
        PRINTF("Master Read : ");
        for (int i=0;i<sizeof(gpu8MasterRecvData);i++)
            PRINTF("0x%02X ",gpu8MasterRecvData[i]);
        PRINTF("\r\n");
        
        rom_delay_ms(1000);
    }
}

static void i2c_example_slave_init(void)
{
    i2c_example_clk_and_gpio_init();
    
    rom_hw_i2c_slave_set_addr_mode(I2C_HANDLE, I2C_ADDR_MODE_7_BITS);
    rom_hw_i2c_set_addr(I2C_HANDLE, 0x6A);
    rom_hw_i2c_slave_enable(I2C_HANDLE);
    
    for (int i=0;i<I2C_BUF_SIZE;i++)
    {
        gpu8SlaveSendData[i] = i;
    }
}

static EN_ERR_STA_T i2c_example_slave_dma_init(void)
{
    EN_ERR_STA_T enRet;
    EN_DMA_PERI_SEL_T enRxPeriID;
    EN_DMA_PERI_SEL_T enTxPeriID;
    
    if (I2C0 == I2C_HANDLE)
    {
        enRxPeriID = DMA_PERI_I2C0_RX;
        enTxPeriID = DMA_PERI_I2C0_TX;
    }
    else if (I2C1 == I2C_HANDLE)
    {
        enRxPeriID = DMA_PERI_I2C1_RX;
        enTxPeriID = DMA_PERI_I2C1_TX;
    }
    else
    {
        enRxPeriID = DMA_PERI_I2C2_RX;
        enTxPeriID = DMA_PERI_I2C2_TX;
    }
    
    enRet = rom_hw_crg_enable_clk_gate(CRG_DMA_CLK_GATE);
    ERR_RETURN_IF_ERROR(enRet);
    
    stDmaInit_t stDmaInit;
    stDmaInit.unPeriSel.stPeriSel.enPeriID = enRxPeriID;
    stDmaInit.u32TimeOut = 200;
    stDmaInit.u32SrcAddr = (uint32_t)&I2C_HANDLE->I2C_RX_FIFO;
    stDmaInit.unCfg.stDmaCfg.u8CircEn = DMA_NORM;
    stDmaInit.unCfg.stDmaCfg.u8Priority = DMA_PRIO_LEVEL_LOW;
    stDmaInit.unCfg.stDmaCfg.u8WorkMode = DMA_PERI_TO_MEM;
    stDmaInit.unCfg.stDmaCfg.u8DstSize = DMA_DATA_1BYTE;
    stDmaInit.unCfg.stDmaCfg.u8DstIncEN = DMA_ADDR_INC_ENABLE;
    stDmaInit.unCfg.stDmaCfg.u8SrcSize = DMA_DATA_1BYTE;
    stDmaInit.unCfg.stDmaCfg.u8SrcIncEN = DMA_ADDR_INC_DISABLE;
    stDmaInit.unCfg.stDmaCfg.u8StopCfg = 0;
    stDmaInit.unCfg.stDmaCfg.u8PauseEn = 0;
    stDmaInit.unCfg.stDmaCfg.u8Enable = DMA_DISABLE;
    enRet = rom_hw_dma_init(I2C_RX_DMA_HANDLE,&stDmaInit);
    ERR_RETURN_IF_ERROR(enRet);

    // set dma interrupt
    enRet = rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, DMA_IRQ6);
    ERR_RETURN_IF_ERROR(enRet);
    
    NVIC_ClearPendingIRQ(DMA_IRQ6);
    NVIC_SetPriority(DMA_IRQ6, 0x03);
    NVIC_EnableIRQ(DMA_IRQ6);
    
    enRet = rom_hw_dma_set_interrupt_channel(I2C_RX_DMA_HANDLE, DMA_INT6);
    ERR_RETURN_IF_ERROR(enRet);
    
    stDmaInit.unPeriSel.stPeriSel.enPeriID = enTxPeriID;
    stDmaInit.u32DstAddr = (uint32_t)&I2C_HANDLE->I2C_TX_FIFO;
    stDmaInit.unCfg.stDmaCfg.u8WorkMode = DMA_MEM_TO_PERI;
    stDmaInit.unCfg.stDmaCfg.u8SrcIncEN = DMA_ADDR_INC_ENABLE;
    stDmaInit.unCfg.stDmaCfg.u8DstIncEN = DMA_ADDR_INC_DISABLE;
   
    enRet = rom_hw_dma_init(I2C_TX_DMA_HANDLE,&stDmaInit);
    ERR_RETURN_IF_ERROR(enRet);
    
    enRet = rom_hw_dma_set_interrupt_channel(I2C_TX_DMA_HANDLE, DMA_INT6);
    ERR_RETURN_IF_ERROR(enRet);
    
    return ERR_STA_OK;
}

static void i2c_example_slave_block(void)
{
    i2c_example_slave_init();
    
    IRQn_Type enIrqType;
    if (I2C0 == I2C_HANDLE)
        enIrqType = I2C0_IRQ;
    else if (I2C1 == I2C_HANDLE)
        enIrqType = I2C1_IRQ;
    else
        enIrqType = I2C2_IRQ;
    
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP,enIrqType);
    rom_hw_i2c_enable_interrupt(I2C_HANDLE,I2C_INT_RXFIFO_NOT_EMPTY);
    NVIC_ClearPendingIRQ(enIrqType);
    NVIC_SetPriority(enIrqType, 0x3);
    NVIC_EnableIRQ(enIrqType);
    
    while(1)
    {
        patch_hw_i2c_slave_write(I2C_HANDLE,gpu8SlaveSendData,sizeof(gpu8SlaveSendData));
    }
}

static void i2c_example_slave_dma(void)
{
    i2c_example_slave_init();
    
    i2c_example_slave_dma_init();
    
    i2c_example_slave_read_by_dma(I2C_HANDLE,I2C_RX_DMA_HANDLE,gpu8SlaveRecvData,sizeof(gpu8SlaveRecvData));
    i2c_example_slave_write_by_dma(I2C_HANDLE,I2C_TX_DMA_HANDLE,gpu8SlaveSendData,sizeof(gpu8SlaveSendData));
    
    for(;;){}
}

/**
 * @brief  I2C module example code.
 */
static void i2c_example(void)
{
    switch(EN_I2C_EXAMPLE_MASTER_BLOCK)
    {
        case EN_I2C_EXAMPLE_MASTER_BLOCK:
        {
            // I2C0 acts as the Master
            i2c_example_master_block();
            break;
        }
        case EN_I2C_EXAMPLE_SLAVE_BLOCK:
        {
            // I2C1 acts as the Slave
            i2c_example_slave_block();
            break;
        }
        case EN_I2C_EXAMPLE_SLAVE_DMA:
        {
            i2c_example_slave_dma();
            break;
        }
        default:break;
    }
}


/**
 * @brief  I2C example code main function.
 * @return 0.
 */
int main(void)
{
    // Disable watchdog timer.
    rom_hw_wdt_disable(WDT0);

    rom_delay_ms(100);

    system_power_init();
    system_clock_init(EN_SYS_CLK_DCXO16M); // EN_SYS_CLK_DCXO16M EN_SYS_CLK_PLL64M
    peripheral_init();

    i2c_example();

    for (;;)
        ;

    return 0;
}
