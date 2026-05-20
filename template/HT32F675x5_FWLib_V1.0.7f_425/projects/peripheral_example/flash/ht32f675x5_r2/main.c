/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2023-01-16
 * @brief   flash module example code.
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
#include "sflash.h"
#include "hw_flash.h"
#include "hw_stim.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hal_pmu.h"
#include "patch_hw_flash.h"

#include "app_cfg.h"
#include "type_def.h"
#include "boards.h"
#include "utility.h"
#include "app_debug.h"

#include "app_flash.h"

/**
 * @brief  Macro definitions.
 */
#define FLASH_EXAMPLE_BYTE_SIZE       (4096)
#define FLASH_EXAMPLE_ERASE_UNIT      (ERASE_SECTOR)
#define FLASH_EXAMPLE_CACHE_READ_LEN  (256)
#define FLASH_EXAMPLE_CACHE_READ_ADDR (FLASH_BASE_ADDR + FLASH_USER_DATA_ADDR + 0x10000)

/**
 * @brief  Flash example case.
 */
typedef enum
{
    FLASH_EXAMPLE_GET_ID      = 0x01, // Get id
    FLASH_EXAMPLE_ERW         = 0x02, // Erase, Read and Write
    FLASH_EXAMPLE_ERW_SUSPEND = 0x03, // Erase and Write with suspend

} enExampleCase_t;

/**
 * @brief  Local variables.
 */
static uint8_t m_au8FlashWriteBuf[FLASH_EXAMPLE_BYTE_SIZE];
static uint8_t m_au8FlashReadBuf[FLASH_EXAMPLE_BYTE_SIZE];

static uint32_t m_au32CacheReadBuf[FLASH_EXAMPLE_CACHE_READ_LEN];
static uint8_t  m_u8SuspendFlag = 0;

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
#if APP_DEBUG_ENABLED
    app_debug_init(GPIO_PORT_APP_DEBUG_TX, GPIO_PIN_APP_DEBUG_TX, UART_HANDLE_APP_DEBUG, UART_BPS_APP_DEBUG, NULL);
    PRINTF("[%s T %s]Flash example code start to work.\n", __DATE__, __TIME__);
#endif
}

/**
 * @brief  Flash read and write data check.
 * @param  pu8TxBuf: write data.
 * @param  pu8RxBuf: read data.
 * @param  u16Len: data length.
 * @return uint8_t: Data right or not.
 */
static uint8_t flash_example_check_data(uint8_t *pu8TxBuf, uint8_t *pu8RxBuf, uint16_t u16Len)
{
    uint16_t i, j;

    if (pu8TxBuf == NULL)
    {
        for (i = 0; i < u16Len; i++)
        {
            if (0XFF != pu8RxBuf[i])
            {
                PRINTF("Read data error, should be all 0xFF. Read data:\n");
                for (j = 0; j < u16Len; j++)
                {
                    PRINTF("%02X ", pu8RxBuf[j]);
                }
                PRINTF("\n");
                return ERR_STA_ERROR;
            }
        }
    }
    else
    {
        if (memcmp(pu8TxBuf, pu8RxBuf, u16Len))
        {
            PRINTF("Read data error. Write data:\n");
            for (j = 0; j < u16Len; j++)
            {
                PRINTF("%02X ", pu8TxBuf[j]);
            }
            PRINTF("\nRead data:\n");
            for (j = 0; j < u16Len; j++)
            {
                PRINTF("%02X ", pu8RxBuf[j]);
            }
            PRINTF("\n");
            return ERR_STA_ERROR;
        }
    }

    return ERR_STA_OK;
}

/**
 * @brief  Get flash mmemory ID.
 */
__RAM_FUNC static void flash_example_get_id(void)
{
    uint32_t u32ChipID      = 0;
    uint8_t  u8UniqueID[16] = {0};

    // Read id
    rom_hw_flash_set_quad_enable(FLASH, QSPI_DISABLE);

    rom_hw_flash_get_id(FLASH, &u32ChipID);
    patch_hw_flash_get_unique_id(FLASH, u8UniqueID);

    rom_hw_flash_set_quad_enable(FLASH, QSPI_ENABLE);

    // Printf
    PRINTF("Flash chip id: %08X\n", u32ChipID);

    PRINTF("Flash unique id:");
    for (uint8_t i = 0; i < sizeof(u8UniqueID); i++)
    {
        PRINTF(" %02X", u8UniqueID[i]);
    }
    PRINTF("\n");
}

/**
 * @brief  Flash erase, read and write example code.
 */
static void flash_example_erw(void)
{
    uint16_t i;
    uint8_t  u8Ret;

    // 1. Data buffer init
    memset(m_au8FlashReadBuf, 0, sizeof(m_au8FlashReadBuf));

    // 2. Erase flash in FLASH_USER_DATA_ADDR address.
    app_flash_erase(FLASH_EXAMPLE_ERASE_UNIT, FLASH_USER_DATA_ADDR / FLASH_EXAMPLE_BYTE_SIZE);

    // 3. Read flash data.
    app_flash_read(FLASH_USER_DATA_ADDR, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf), BUS_MODE_QPI);

    // 4. Check data.
    u8Ret = flash_example_check_data(NULL, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf));
    PRINTF("[%d]Erase and read flash done.\n", u8Ret);

    // 5. Data buffer init
    memset(m_au8FlashReadBuf, 0, sizeof(m_au8FlashReadBuf));
    for (i = 0; i < sizeof(m_au8FlashWriteBuf); i++)
    {
        m_au8FlashWriteBuf[i] = i & 0xFF;
    }

    // 6. Write flash data.
    app_flash_write(FLASH_USER_DATA_ADDR, m_au8FlashWriteBuf, sizeof(m_au8FlashWriteBuf), BUS_MODE_QPI);

    // 7. Read flash data.
    app_flash_read(FLASH_USER_DATA_ADDR, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf), BUS_MODE_QPI);

    // 8. Check data.
    u8Ret = flash_example_check_data(m_au8FlashWriteBuf, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf));

    PRINTF("[%d]Write and read flash done.\n", u8Ret);
}

/**
 * @brief  stim0 channel 0 irq handler.
 */
__RAM_FUNC void STIM0_IRQ0_Handler(void)
{
    uint32_t u32Count = 0;
    uint8_t  u8Ret;

    rom_hw_stim_clear_interrupt_flag(STIM0, STIM_INT_MASK);

    if (m_u8SuspendFlag)
    {
        memset(m_au32CacheReadBuf, 0, sizeof(m_au32CacheReadBuf));
        memcpy(m_au32CacheReadBuf, (const void *)((volatile uint32_t *)(FLASH_EXAMPLE_CACHE_READ_ADDR)),
               sizeof(m_au32CacheReadBuf));

        u8Ret = flash_example_check_data(NULL, (uint8_t *)m_au32CacheReadBuf, sizeof(m_au32CacheReadBuf));
        PRINTF("[%d]I ", u8Ret);
    }

    // Read stim count.
    rom_hw_stim_get_count(STIM0, &u32Count);
    rom_hw_stim_set_compare(STIM0, STIM_CH0, u32Count + 32);
}

/**
 * @brief  stim wakeup init.
 */
static void flash_example_stim_init()
{
    // Enable stim0 module clock gate.
    rom_hw_crg_enable_clk_gate(CRG_STIM0_CLK_GATE);

    // Set stim prescale to 0(default).
    rom_hw_stim_set_prescale(STIM0, 0);

    // Configuration stim0 ch0 peripheral int
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_MP, STIM0_IRQ0);
    NVIC_ClearPendingIRQ(STIM0_IRQ0);
    NVIC_SetPriority(STIM0_IRQ0, 3);
    NVIC_EnableIRQ(STIM0_IRQ0);

    // Configure stim0 ch0 interrupt and compare value.
    rom_hw_stim_disable_interrupt(STIM0, STIM_INT_MASK);
    rom_hw_stim_enable_interrupt(STIM0, STIM_CH0_INT_MATCH);
    rom_hw_stim_set_compare(STIM0, STIM_CH0, TIME_MS_TO_32K_CNT(100));

    // Start stim0 counter.
    rom_hw_stim_start(STIM0);
}

/**
 * @brief  Flash erase and write with suspend example code.
 */
static void flash_example_erw_suspend(void)
{
    uint8_t  u8Ret;
    uint16_t u16Num;
    uint32_t u32TestCount = 60;

    // 1. stim init.
    flash_example_stim_init();

    // 2. Data buffer init
    for (uint32_t i = 0; i < sizeof(m_au8FlashWriteBuf); i++)
    {
        m_au8FlashWriteBuf[i] = i & 0xFF;
    }

    while (u32TestCount--)
    {
        // init data.
        {
            rom_hw_stim_stop(STIM0);

            // 3. Write flash data.
            app_flash_write(FLASH_USER_DATA_ADDR, m_au8FlashWriteBuf, sizeof(m_au8FlashWriteBuf), BUS_MODE_QPI);

            // 4. Read flash data.
            memset(m_au8FlashReadBuf, 0, sizeof(m_au8FlashReadBuf));
            app_flash_read(FLASH_USER_DATA_ADDR, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf), BUS_MODE_QPI);

            // 5. Check data.
            u8Ret = flash_example_check_data(m_au8FlashWriteBuf, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf));
            PRINTF("[%d]Write and read flash done.\n", u8Ret);

            memset(m_au32CacheReadBuf, 0, sizeof(m_au32CacheReadBuf));
            memcpy(m_au32CacheReadBuf, (const void *)((volatile uint32_t *)(FLASH_EXAMPLE_CACHE_READ_ADDR)),
                   sizeof(m_au32CacheReadBuf));
            u8Ret = flash_example_check_data(NULL, (uint8_t *)m_au32CacheReadBuf, sizeof(m_au32CacheReadBuf));
            PRINTF("[%d]Cache read status.\n", u8Ret);

            rom_hw_stim_start(STIM0);
        }

        // 6. Erase flash data.
        m_u8SuspendFlag = 1;
        u16Num          = FLASH_USER_DATA_ADDR / FLASH_EXAMPLE_BYTE_SIZE;
        for (uint32_t i = 0; i < 16; i++)
        {
            u8Ret = patch_hw_flash_erase_suspendable(FLASH, FLASH_EXAMPLE_ERASE_UNIT, u16Num + i,
                                                     SFLASH_SECTOR_ERASE_TIME_US);
            PRINTF("\n[%d]Erase with suspend status.\n", u8Ret);
        }
        m_u8SuspendFlag = 0;

        // 7. Read flash data.
        memset(m_au8FlashReadBuf, 0, sizeof(m_au8FlashReadBuf));
        rom_hw_flash_read_bytes(FLASH, FLASH_USER_DATA_ADDR, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf),
                                BUS_MODE_QPI);

        // 8. Check data.
        u8Ret = flash_example_check_data(NULL, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf));
        PRINTF("[%d]Erase and read flash done.\n", u8Ret);

        // 9. Write flash data.
        m_u8SuspendFlag = 2;
        for (uint32_t i = 0; i < 16; i++)
        {
            patch_hw_flash_write_bytes_suspendable(FLASH, FLASH_USER_DATA_ADDR + i * sizeof(m_au8FlashReadBuf),
                                                   m_au8FlashWriteBuf, sizeof(m_au8FlashReadBuf), BUS_MODE_QPI,
                                                   FLASH_PROGRAM_TIMEOUT_US);
            PRINTF("\n[%d]Write with suspend status.\n", u8Ret);
        }
        m_u8SuspendFlag = 0;

        // 10. Read flash data.
        memset(m_au8FlashReadBuf, 0, sizeof(m_au8FlashReadBuf));
        rom_hw_flash_read_bytes(FLASH, FLASH_USER_DATA_ADDR, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf),
                                BUS_MODE_QPI);

        // 11. Check data.
        u8Ret = flash_example_check_data(m_au8FlashWriteBuf, m_au8FlashReadBuf, sizeof(m_au8FlashReadBuf));
        PRINTF("[%d]Write and read flash done.\n", u8Ret);

        rom_delay_ms(1000);
    }

    rom_hw_stim_stop(STIM0);
    PRINTF("Flash erase and write with suspend test done.\n");
}

/**
 * @brief  Flash example code.
 */
static void flash_example(void)
{
    uint8_t u8Case = FLASH_EXAMPLE_GET_ID;

    switch (u8Case)
    {
        case FLASH_EXAMPLE_GET_ID:
        {
            flash_example_get_id();
            break;
        }
        // Flash erase, read and write example code.
        case FLASH_EXAMPLE_ERW:
        {
            flash_example_erw();
            break;
        }
        // Flash erase and write with suspend example code.
        case FLASH_EXAMPLE_ERW_SUSPEND:
        {
            flash_example_erw_suspend();
            break;
        }
    }
}

/**
 * @brief  Flash example code main function.
 * @return 0.
 */
int main(void)
{
    // Disable watchdog timer.
    rom_hw_wdt_disable(WDT0);

    rom_delay_ms(100);

    system_power_init();
    system_clock_init(EN_SYS_CLK_DCXO16M);
    peripheral_init();

    flash_example();

    for (;;);

    return 0;
}
