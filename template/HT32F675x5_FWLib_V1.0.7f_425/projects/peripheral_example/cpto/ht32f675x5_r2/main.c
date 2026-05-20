/*************************************************************************************************************
 * @file    main.c
 * @version V1.0
 * @date    2022-10-31
 * @brief   CPTO module example code.
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
#include "hw_pmu.h"
#include "hw_crg.h"
#include "hw_efuse.h"
#include "hw_gpio.h"
#include "hw_sys_ctrl.h"
#include "hw_wdt.h"
#include "hal_pmu.h"
#include "hw_cpto.h"


#include "app_cfg.h"
#include "boards.h"
#include "utility.h"
#include "app_debug.h"
#include "rand.h"

#define CPTO_AES_KEY_MAX_LEN    (32)
#define CPTO_AES_DATA_LEN       (16)
#define CPTO_AES_128BIT_KEY_LEN (16)
#define CPTO_AES_IV_LEN         (16)
#define CPTO_AES_CBC_DATA_LEN   (16)
#define CPTO_AES_ECB_DATA_LEN   (16)

/**
 * @brief  CPTO example case.
 */
typedef enum
{
    CPTO_EXAMPLE_AES      = 0,
    CPTO_EXAMPLE_AES_CBC  = 1,
    CPTO_EXAMPLE_AES_CTR  = 2,
    CPTO_EXAMPLE_AES_ECB  = 3,
    CPTO_EXAMPLE_AES_CMAC = 4,
    CPTO_EXAMPLE_CCM      = 5,

} EN_CPTO_EXAMPLE_T;

typedef enum
{
    AES_KEY_128BIT = 0,
    AES_KEY_192BIT = 1,
    AES_KEY_256BIT = 2,

} EN_AES_KEY_SIZE_T;

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
    PRINTF("[%s T %s]CPTO example code start to work.\n", __DATE__, __TIME__);
#endif
}

/**
 * @brief  AES encryption and decryption example.
 * @param  enKeySize: Key size, @ref EN_AES_KEY_SIZE_T.
 * @note   example1: 128bit
 *         KEY:        000102030405060708090a0b0c0d0e0f
 *         Plaintext:  00112233445566778899aabbccddeeff
 *         Ciphertext: 69c4e0d86a7b0430d8cdb78070b4c55a
 * @note   example2: 192bit
 *         KEY:        000102030405060708090a0b0c0d0e0f1011121314151617
 *         Plaintext:  00112233445566778899aabbccddeeff
 *         Ciphertext: dda97ca4864cdfe06eaf70a0ec0d7191
 * @note   example3: 256bit
 *         KEY:        000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f
 *         Plaintext:  00112233445566778899aabbccddeeff
 *         Ciphertext: 8ea2b7ca516745bfeafc49904b496089
 * @return status: @ref EN_ERR_STA_T.
 */
static uint8_t cpto_example_aes(EN_AES_KEY_SIZE_T enKeySize)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    uint8_t au8Key[CPTO_AES_KEY_MAX_LEN] __ALIGNED(4)     = {0x00};
    uint8_t au8Plaintext[CPTO_AES_DATA_LEN] __ALIGNED(4)  = {0x00};
    uint8_t au8Ciphertext[CPTO_AES_DATA_LEN] __ALIGNED(4) = {0x00};
    uint8_t au8DataOut[CPTO_AES_DATA_LEN] __ALIGNED(4)    = {0x00};
    EN_ERR_STA_T (*encrypt_func)(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut) = NULL;
    EN_ERR_STA_T (*decrypt_func)(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut) = NULL;

    // 1. Data init.
    for (uint8_t i = 0; i < sizeof(au8Key); i++)
    {
        au8Key[i] = rom_get_rand();
    }
    for (uint16_t i = 0; i < sizeof(au8Plaintext); i++)
    {
        au8Plaintext[i] = rom_get_rand();
    }
    memset(au8Ciphertext, 0, sizeof(au8Ciphertext));
    memset(au8DataOut, 0, sizeof(au8DataOut));

    
    switch(enKeySize)
    {
        case AES_KEY_128BIT:
        {
            encrypt_func = rom_hw_aes_encrypt;
            decrypt_func = rom_hw_aes_decrypt;
            break;
        }
        case AES_KEY_192BIT:
        {
            encrypt_func = rom_hw_aes192_encrypt;
            decrypt_func = rom_hw_aes192_decrypt;
            break;
        }
        case AES_KEY_256BIT:
        {
            encrypt_func = rom_hw_aes256_encrypt;
            decrypt_func = rom_hw_aes256_decrypt;
            break;
        }
        default:break;
    }
    
    if (encrypt_func)
    {
        // 2. aes encryption.
        enRet = encrypt_func((uint32_t *)au8Key, (uint32_t *)au8Plaintext, (uint32_t *)au8Ciphertext);
        if (enRet)
        {
            PRINTF("[%d]aes encrypt fail, reason: %d.\n", enKeySize, enRet);
            return enRet;
        }
    }
    
    if (decrypt_func)
    {
        // 3. aes decryption.
        enRet = decrypt_func((uint32_t *)au8Key, (uint32_t *)au8Ciphertext, (uint32_t *)au8DataOut);

        if (enRet)
        {
            PRINTF("[%d]aes decryption fail, reason: %d.\n", enKeySize, enRet);
        }
        else
        {
            // Compare encryption data and decryption data.
            if (memcmp(au8Plaintext, au8DataOut, sizeof(au8DataOut)))
            {
                PRINTF("[%d]aes decryption return ok, but ciphertext is wrong.\n", enKeySize);
                return ERR_STA_ERROR;
            }
    
            PRINTF("[%d]aes encryption and decryption pass.\n", enKeySize);
        }
    }

    return enRet;
}

/**
 * @brief  AES-CBC encryption and decryption example.
 * @param  u16DataInLen: Encryption and encryption data len, range is 16 ~ 496.
 * @note   example:
 *         KEY:        2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c
 *         IV:         00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f
 *         Plaintext:  6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a
 *         Ciphertext: 7649abac8119b246cee98e9b12e9197d
 * @return status: @ref EN_ERR_STA_T.
 */
static uint8_t cpto_example_aes_cbc(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    uint8_t au8Key[CPTO_AES_128BIT_KEY_LEN] __ALIGNED(4)          = {0x3c ,0x4f ,0xcf ,0x09 ,0x88 ,0x15 ,0xf7 ,0xab ,
                                                                     0xa6 ,0xd2 ,0xae ,0x28 ,0x16 ,0x15 ,0x7e ,0x2b};
    uint8_t au8IV[CPTO_AES_IV_LEN] __ALIGNED(4)                   = {0x0f ,0x0e ,0x0d ,0x0c ,0x0b ,0x0a ,0x09 ,0x08 ,
                                                                     0x07 ,0x06 ,0x05 ,0x04 ,0x03 ,0x02 ,0x01 ,0x00};
    uint8_t au8Plaintext[CPTO_AES_CBC_DATA_LEN] __ALIGNED(4)  = {0x2a,0x17,0x93,0x73,0x11,0x7e,0x3d,0xe9,0x96,0x9f,0x40,0x2e,0xe2,0xbe,0xc1,0x6b};
    uint8_t au8Ciphertext[CPTO_AES_CBC_DATA_LEN] __ALIGNED(4) = {0x00};
    uint8_t au8Ciphertext2[CPTO_AES_CBC_DATA_LEN] = {0x7D,0x19,0xE9,0x12,0x9B,0x8E,0xE9,0xCE,0x46,0xB2,0x19,0x81,0xAC,0xAB,0x49,0x76};

    memset(au8Ciphertext, 0, sizeof(au8Ciphertext));

    enRet = rom_hw_cbc_encrypt((uint32_t *)au8Key, (uint32_t *)au8Plaintext,(uint32_t *)au8Ciphertext, (uint32_t *)au8IV);
    if (enRet)
    {
        PRINTF("aes-cbc encrypt fail, reason: %d.\n", enRet);
        return enRet;
    }
    
    if (memcmp(au8Ciphertext,au8Ciphertext2,sizeof(au8Ciphertext)))
    {
        PRINTF("aes-cbc encryption return ok, but ciphertext is wrong.\n");
        return ERR_STA_ERROR;
    }
    else
    {
        PRINTF("aes-cbc encryption match succeed\n");
    }

    return enRet;
}

/**
 * @brief  AES-CTR encryption example.
 * @note   example:
 *         KEY:        2b7e151628aed2a6abf7158809cf4f3c
 *         IV:         f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff
 *         Plaintext:  6bc1bee22e409f96e93d7e117393172a
 *         Ciphertext: 874d6191b620e3261bef6864990db6ce
 * @return status: @ref EN_ERR_STA_T.
 */
static uint8_t cpto_example_aes_ctr(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    uint8_t au8Key[CPTO_AES_KEY_MAX_LEN] __ALIGNED(4)      = {0x3c, 0x4f, 0xcf, 0x09, 0x88, 0x15, 0xf7, 0xab,
                                                              0xa6, 0xd2, 0xae, 0x28, 0x16, 0x15, 0x7e, 0x2b};
    uint8_t au8IV[CPTO_AES_IV_LEN] __ALIGNED(4)            = {0xff, 0xfe, 0xfd, 0xfc, 0xfb, 0xfa, 0xf9, 0xf8,
                                                              0xf7, 0xf6, 0xf5, 0xf4, 0xf3, 0xf2, 0xf1, 0xf0};
    uint8_t au8Plaintext[CPTO_AES_DATA_LEN] __ALIGNED(4)   = {0x2a, 0x17, 0x93, 0x73, 0x11, 0x7e, 0x3d, 0xe9,
                                                              0x96, 0x9f, 0x40, 0x2e, 0xe2, 0xbe, 0xc1, 0x6b};
    uint8_t au8Plaintext2[CPTO_AES_DATA_LEN] __ALIGNED(4)  = {0x00};
    uint8_t au8Ciphertext[CPTO_AES_DATA_LEN] __ALIGNED(4)  = {0x00};
    uint8_t au8Ciphertext2[CPTO_AES_DATA_LEN] __ALIGNED(4) = {0xCE, 0xB6, 0x0D, 0x99, 0x64, 0x68, 0xEF, 0x1B,
                                                              0x26, 0xE3, 0x20, 0xB6, 0x91, 0x61, 0x4D, 0x87};

    // 1. Data init.
    memset(au8Ciphertext, 0, sizeof(au8Ciphertext));

    // 2. aes-ctr encryption.
    enRet = rom_hw_ctr_encrypt((uint32_t *)au8Key, (uint32_t *)au8Plaintext,(uint32_t *)au8Ciphertext, (uint32_t *)au8IV);

    if (enRet)
    {
        PRINTF("aes-ctr encrypt fail, reason: %d.\n", enRet);
        return enRet;
    }
    else
    {
        // Compare encryption.
        if (memcmp(au8Ciphertext, au8Ciphertext2, sizeof(au8Ciphertext2)))
        {
            PRINTF("aes-ctr encryption return ok, but ciphertext is wrong.\n");
            return ERR_STA_ERROR;
        }

        PRINTF("aes-ctr encryption pass.\n");
        
        enRet = rom_hw_ctr_decrypt((uint32_t *)au8Key,(uint32_t *)au8Ciphertext,(uint32_t *)au8Plaintext2, (uint32_t *)au8IV);
        if (enRet)
        {
            PRINTF("aes-ctr decrypt fail, reason: %d.\n", enRet);
            return enRet;
        }
        
        if (memcmp(au8Plaintext,au8Plaintext2,sizeof(au8Plaintext)))
        {
            PRINTF("aes-ctr decryption return ok, but au8Plaintext2 is wrong.\n");
            return ERR_STA_ERROR;
        }
    }

    return enRet;
}

/**
 * @brief  AES-ECB encryption and decryption example.
 * @param  u16DataInLen: Encryption and encryption data len, range is 16 ~ 496.
 * @note   example:
 *         KEY:        2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c
 *         Plaintext:  6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a
 *         Ciphertext: 3a d7 7b b4 0d 7a 36 60 a8 9e ca f3 24 66 ef 97
 * @return status: @ref EN_ERR_STA_T.
 */
static uint8_t cpto_example_aes_ecb(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    uint8_t au8Key[CPTO_AES_128BIT_KEY_LEN] __ALIGNED(4)      = {0x3c,0x4f,0xcf,0x09,0x88,0x15,0xf7,0xab,0xa6,0xd2,0xae,0x28,0x16,0x15,0x7e,0x2b};
    uint8_t au8Plaintext[CPTO_AES_ECB_DATA_LEN] __ALIGNED(4)  = {0x2a,0x17,0x93,0x73,0x11,0x7e,0x3d,0xe9,0x96,0x9f,0x40,0x2e,0xe2,0xbe,0xc1,0x6b};
    uint8_t au8Ciphertext[CPTO_AES_ECB_DATA_LEN] __ALIGNED(4) = {0x97,0xef,0x66,0x24,0xf3,0xca,0x9e,0xa8,0x60,0x36,0x7a,0x0d,0xb4,0x7b,0xd7,0x3a};
    uint8_t au8Ciphertext2[CPTO_AES_ECB_DATA_LEN] __ALIGNED(4) = {0x97,0xEF,0x66,0x24,0xF3,0xCA,0x9E,0xA8,0x60,0x36,0x7A,0x0D,0xB4,0x7B,0xD7,0x3A};

    enRet = rom_hw_ecb_encrypt((uint32_t *)au8Key, (uint32_t *)au8Plaintext, (uint32_t *)au8Ciphertext);
    if (enRet)
    {
        PRINTF("aes-ecb encrypt fail, reason: %d.\n", enRet);
        return enRet;
    }

    if (memcmp(au8Ciphertext,au8Ciphertext2,sizeof(au8Ciphertext)))
    {
        PRINTF("aes-ecb decryption return ok, but au8Ciphertext is wrong.\n");
        return ERR_STA_ERROR;
    }
    else
    {
        PRINTF("aes-ecb encryption match succeed\n");
    }
    
    return enRet;
}

/**
 * @brief  AES-CMAC encryption example.
 * @note   example: Plaintext = 16Bytes
 *         KEY:        2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c
 *         Plaintext:  6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a
 *         Ciphertext: 07 0a 16 b4 6b 4d 41 44 f7 9b dd 9d d0 4a 28 7c
 * @return status: @ref EN_ERR_STA_T.
 */
static uint8_t cpto_example_aes_cmac(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    uint8_t au8Key[CPTO_AES_128BIT_KEY_LEN] __ALIGNED(4)  = {0x3c, 0x4f, 0xcf, 0x09, 0x88, 0x15, 0xf7, 0xab,
                                                             0xa6, 0xd2, 0xae, 0x28, 0x16, 0x15, 0x7e, 0x2b};
    uint8_t au8Plaintext[CPTO_AES_DATA_LEN] __ALIGNED(4) = {0x2a, 0x17, 0x93, 0x73, 0x11, 0x7e, 0x3d, 0xe9,
                                                             0x96, 0x9f, 0x40, 0x2e, 0xe2, 0xbe, 0xc1, 0x6b};

    uint8_t au8Ciphertext[CPTO_AES_DATA_LEN] __ALIGNED(4)  = {0x00};
    uint8_t au8Ciphertext1[CPTO_AES_DATA_LEN] __ALIGNED(4) = {0x7C, 0x28, 0x4A, 0xD0, 0x9D, 0xDD, 0x9B, 0xF7,
                                                              0x44, 0x41, 0x4D, 0x6B, 0xB4, 0x16, 0x0A, 0x07};

    // 1. Data init.
    memset(au8Ciphertext, 0, sizeof(au8Ciphertext));

    // 2. aes-cmac encryption.
    enRet = rom_hw_cmac_encrypt((uint32_t *)au8Key, (uint32_t *)au8Plaintext, (uint32_t *)au8Ciphertext,CPTO_AES_DATA_LEN);
    if (enRet)
    {
        PRINTF("aes-cmac encrypt fail, reason: %d.\n", enRet);
    }
    else
    {
        // Compare encryption.
        if (memcmp(au8Ciphertext, au8Ciphertext1, sizeof(au8Ciphertext)))
        {
            PRINTF("aes-cmac encryption return ok, but ciphertext is wrong.\n");
        }
        else
        {
            PRINTF("aes-cmac encryption pass.\n");
        }
    }

    return enRet;
}

/**
 * @brief  cpto example code.
 */
static void cpto_example(void)
{
    uint8_t u8Case = CPTO_EXAMPLE_AES;

    // Enable clock gate.
    rom_hw_crg_enable_clk_gate(CRG_CPTO1_CLK_GATE);
    rom_hw_crg_enable_clk_gate(CRG_AHB4_CLK_GATE);
    rom_rand_init(0);
    
    switch (u8Case)
    {
        case CPTO_EXAMPLE_AES:
        {
            cpto_example_aes(AES_KEY_128BIT);
            cpto_example_aes(AES_KEY_192BIT);
            cpto_example_aes(AES_KEY_256BIT);
            break;
        }
        case CPTO_EXAMPLE_AES_CBC:
        {
            cpto_example_aes_cbc();
            break;
        }
        case CPTO_EXAMPLE_AES_CTR:
        {
            cpto_example_aes_ctr();
            break;
        }
        case CPTO_EXAMPLE_AES_ECB:
        {
            cpto_example_aes_ecb();
            break;
        }
        case CPTO_EXAMPLE_AES_CMAC:
        {
            cpto_example_aes_cmac();
            break;
        }
    }
}

/**
 * @brief  CPTO example code main function.
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

    cpto_example();
    
    for (;;);

    return 0;
}
