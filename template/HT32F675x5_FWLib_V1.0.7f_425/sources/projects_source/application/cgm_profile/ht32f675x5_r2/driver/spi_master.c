/*************************************************************************************************************
 * @file    spi_master.c
 * @version V1.0
 * @date    2021-02-06
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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_gpio.h"
#include "app_cfg.h"
#include "boards.h"
#include "utility.h"

#include "hw_spi.h"
#include "patch_hw_spi.h"
#include "hw_crg.h"
#include "hw_sys_ctrl.h"

#include "spi_master.h"

#if SPI_CMD_SUPPORT

static bool gbIsMasterInit = false;

/**********************************************************************************************************************
 * @brief  SPI Master Set CS Busy.
 *
 * @return None.
 *********************************************************************************************************************/
static void spi_master_set_cs(void)
{
    rom_hw_gpio_set_pin_output_level(CGM_SPI_MASTER_CS_GPIO_PORT,CGM_SPI_MASTER_CS_GPIO_PIN,GPIO_LEVEL_LO);
}

/**********************************************************************************************************************
 * @brief  SPI Master Set CS Idle.
 *
 * @return None.
 *********************************************************************************************************************/
static void spi_master_clr_cs(void)
{
    rom_hw_gpio_set_pin_output_level(CGM_SPI_MASTER_CS_GPIO_PORT,CGM_SPI_MASTER_CS_GPIO_PIN,GPIO_LEVEL_HI);
}

/**********************************************************************************************************************
 * @brief  SPI Master Reinit.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T spi_master_reinit(void)
{
    EN_ERR_STA_T enRet;
    
    if (gbIsMasterInit)
        return ERR_STA_OK;
    
    if (SPI0 == CGM_SPI_MASTER_HANDLE)
    {
        // 1. Init GPIO.
        rom_hw_gpio_set_pin_pid(CGM_SPI_MASTER_CLK_GPIO_PORT, CGM_SPI_MASTER_CLK_GPIO_PIN, PID_SPI0_CLK);
        rom_hw_gpio_set_pin_pid(CGM_SPI_MASTER_MOSI_GPIO_PORT, CGM_SPI_MASTER_MOSI_GPIO_PIN, PID_SPI0_MOSI);
        rom_hw_gpio_set_pin_pid(CGM_SPI_MASTER_MISO_GPIO_PORT, CGM_SPI_MASTER_MISO_GPIO_PIN, PID_SPI0_MISO);
        
        // 2. Turn SPI clock gating on.
        rom_hw_crg_enable_clk_gate(CRG_SPI0_CLK_GATE);
    }
    else if (SPI1 == CGM_SPI_MASTER_HANDLE)
    {
        // 1. Init GPIO.
        rom_hw_gpio_set_pin_pid(CGM_SPI_MASTER_CLK_GPIO_PORT, CGM_SPI_MASTER_CLK_GPIO_PIN, PID_SPI1_CLK);
        rom_hw_gpio_set_pin_pid(CGM_SPI_MASTER_MOSI_GPIO_PORT, CGM_SPI_MASTER_MOSI_GPIO_PIN, PID_SPI1_MOSI);
        rom_hw_gpio_set_pin_pid(CGM_SPI_MASTER_MISO_GPIO_PORT, CGM_SPI_MASTER_MISO_GPIO_PIN, PID_SPI1_MISO);
        
        // 2. Turn SPI clock gating on.
        rom_hw_crg_enable_clk_gate(CRG_SPI1_CLK_GATE);
    }
    else
        return ERR_STA_ERROR;
    
    stSpiInit_t stSpiInit = {
        .u32ClkDiv          = EN_SPI_CLK_DIV_16M_1M,
        .unSpiCfg.u32SpiCfg = SPI_INIT_DEFAULT(SPI_MODE_MASTER, SPI_CPHA_0_0, SPI_MODE_FULL_TXRX),
    };
    
    enRet = rom_hw_spi_init(CGM_SPI_MASTER_HANDLE, &stSpiInit);
    if (ERR_STA_OK != enRet)
        return enRet;
    
    rom_hw_spi_enable(CGM_SPI_MASTER_HANDLE);
    
    gbIsMasterInit = true;
    
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  SPI Master Deinit.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T spi_master_deinit(void)
{
    if (false == gbIsMasterInit)
        return ERR_STA_OK;
    
    gbIsMasterInit = false;
    
    rom_hw_gpio_set_pin_input_output(CGM_SPI_MASTER_CLK_GPIO_PORT, CGM_SPI_MASTER_CLK_GPIO_PIN, GPIO_MODE_IMPEDANCE);
    rom_hw_gpio_set_pin_input_output(CGM_SPI_MASTER_MOSI_GPIO_PORT, CGM_SPI_MASTER_MOSI_GPIO_PIN, GPIO_MODE_IMPEDANCE);
    rom_hw_gpio_set_pin_input_output(CGM_SPI_MASTER_MISO_GPIO_PORT, CGM_SPI_MASTER_MISO_GPIO_PIN, GPIO_MODE_IMPEDANCE);
    
    if (SPI0 == CGM_SPI_MASTER_HANDLE)
        return rom_hw_crg_disable_clk_gate(CRG_SPI0_CLK_GATE);
    else if (SPI1 == CGM_SPI_MASTER_HANDLE)
        return rom_hw_crg_disable_clk_gate(CRG_SPI1_CLK_GATE);
    else
        return ERR_STA_ERROR;
}

/**********************************************************************************************************************
 * @brief  SPI Master Init.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T spi_master_init(void)
{
    rom_hw_gpio_set_pin_input_output(CGM_SPI_MASTER_CS_GPIO_PORT,CGM_SPI_MASTER_CS_GPIO_PIN,GPIO_MODE_OUTPUT);
    rom_hw_gpio_set_pin_output_level(CGM_SPI_MASTER_CS_GPIO_PORT,CGM_SPI_MASTER_CS_GPIO_PIN,GPIO_LEVEL_HI);

    return spi_master_reinit();
}

/**********************************************************************************************************************
 * @brief  SPI Master Transmit Bytes to Slave and Receive Bytes From Slave.
 * @param  u8TxBuf: Send Data Buffer.
 * @param  u8RxBuf: Receive Data Buffer.
 * @param  u16TrxLen: The length of Send and Receive Data Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T spi_master_transmit_receive_bytes(uint8_t *u8TxBuf,uint8_t *u8RxBuf,uint16_t u16TrxLen)
{
    EN_ERR_STA_T enRet;
    
    if (false == gbIsMasterInit)
        spi_master_reinit();
    
    spi_master_set_cs();
    enRet = patch_hw_spi_transmit_bytes(CGM_SPI_MASTER_HANDLE,u8TxBuf,u8RxBuf,u16TrxLen);
    spi_master_clr_cs();
    
    return enRet;
}

/**********************************************************************************************************************
 * @brief  SPI Master Transmit Bytes to Slave.
 * @param  u8TxBuf: Send Data Buffer.
 * @param  u16TxLen: The length of Send Data Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T spi_master_transmit_bytes(uint8_t *u8TxBuf,uint16_t u16TxLen)
{
    EN_ERR_STA_T enRet;
    
    if (false == gbIsMasterInit)
        spi_master_reinit();
    
    spi_master_set_cs();
    enRet = patch_hw_spi_transmit_bytes(CGM_SPI_MASTER_HANDLE,u8TxBuf,NULL,u16TxLen);
    spi_master_clr_cs();
    
    return enRet;
}

/**********************************************************************************************************************
 * @brief  SPI Master Receive Bytes From Slave.
 * @param  u8RxBuf: Receive Data Buffer.
 * @param  u16RxLen: The length of Receive Data Buffer.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T spi_master_receive_bytes(uint8_t *u8RxBuf,uint16_t u16RxLen)
{
    EN_ERR_STA_T enRet;
    
    if (false == gbIsMasterInit)
        spi_master_reinit();
    
    spi_master_set_cs();
    enRet = patch_hw_spi_transmit_bytes(CGM_SPI_MASTER_HANDLE,NULL,u8RxBuf,u16RxLen);
    spi_master_clr_cs();
    
    return enRet;
}

#endif