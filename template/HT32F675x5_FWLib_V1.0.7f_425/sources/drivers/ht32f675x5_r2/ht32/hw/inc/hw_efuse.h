/*************************************************************************************************************
 * @file    hw_efuse.h
 * @version V1.1
 * @date    2022-01-14
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



#ifndef __HW_EFUSE_H__
#define __HW_EFUSE_H__

#ifdef __cplusplus
extern "C"
{
#endif


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
//=============================================================================
// eFuse define
#define EFUSE_SIZE_BYTES                              (64)

//=============================================================================
// [0x00]CHIP_TYPE, 4 bits, [3:0]
#define EFUSE_CHIP_TYPE_ADDR                          (0x00)
#define EFUSE_CHIP_TYPE_BITS                          (4)
#define EFUSE_CHIP_TYPE_MSK                           ((0x01 << EFUSE_CHIP_TYPE_BITS) - 1)
#define EFUSE_CHIP_TYPE_SHIFT                         (0)

typedef enum
{
    CHIP_TYPE_HT32F675X5 = 0,

} EN_CHIP_TYPE_T;

//=============================================================================
// [0x00]CHIP_MEM_SIZE, 4 bits, [7:4]
#define EFUSE_CHIP_MEM_SIZE_ADDR                      (0x00)
#define EFUSE_CHIP_MEM_SIZE_BITS                      (4)
#define EFUSE_CHIP_MEM_SIZE_MSK                       ((0x01 << EFUSE_CHIP_MEM_SIZE_BITS) - 1)
#define EFUSE_CHIP_MEM_SIZE_SHIFT                     (4)

typedef enum
{
    CHIP_MEM_SIZE_512KB  = 2,
    CHIP_MEM_SIZE_1024KB = 3,
} EN_CHIP_MEM_SIZE_T;

//=============================================================================
// [0x01]ROM_VERSION, 3 bit, [2:0]
#define EFUSE_ROM_VERSION_ADDR                        (0x01)
#define EFUSE_ROM_VERSION_BITS                        (3)
#define EFUSE_ROM_VERSION_MSK                         ((0x01 << EFUSE_ROM_VERSION_BITS) - 1)
#define EFUSE_ROM_VERSION_SHIFT                       (3)

//=============================================================================
// [0x01]USB_SUPPORT, 1 bit, [3]
#define EFUSE_USB_SUPPORT_ADDR                        (0x01)
#define EFUSE_USB_SUPPORT_BITS                        (1)
#define EFUSE_USB_SUPPORT_MSK                         ((0x01 << EFUSE_USB_SUPPORT_BITS) - 1)
#define EFUSE_USB_SUPPORT_SHIFT                       (3)

typedef enum
{
    CHIP_NOT_SUPPORT_USB  = 0,
    CHIP_SUPPORT_USB      = 1,

} EN_CHIP_USB_SUPPORT_T;

//=============================================================================
// [0x01]PACKAGE_TYPE, 4 bits, [7:4]
#define EFUSE_PACKAGE_TYPE_ADDR                       (0x01)
#define EFUSE_PACKAGE_TYPE_BITS                       (4)
#define EFUSE_PACKAGE_TYPE_MSK                        ((0x01 << EFUSE_PACKAGE_TYPE_BITS) - 1)
#define EFUSE_PACKAGE_TYPE_SHIFT                      (4)

typedef enum
{
    PACKAGE_TYPE_QFN40  = 2,
    PACKAGE_TYPE_BGA120 = 7
} EN_PACKAGE_TYPE_T;

//=============================================================================
// [0x02]CHIP_DEFINE, 8 bits
#define EFUSE_CHIP_DEFINE_ADDR                        (0x02)
#define EFUSE_CHIP_DEFINE_BITS                        (8)
#define EFUSE_CHIP_DEFINE_MSK                         (0xFF)
#define EFUSE_CHIP_DEFINE_SHIFT                       (0)

// [7] Has memory
#define EFUSE_CHIP_DEF_HAS_MEM_BITS                   (1)
#define EFUSE_CHIP_DEF_HAS_MEM_MSK                    ((0x01 << EFUSE_CHIP_DEF_HAS_MEM_BITS) - 1)
#define EFUSE_CHIP_DEF_HAS_MEM_SHIFT                  (7)

typedef enum
{
    ROM_ONLY   = 0, // No memory
    HAS_EX_MEM = 1, // Have memory

} EN_CHIP_DEF_HAS_MEM_T;

// [6:5] External memory type
#define EFUSE_CHIP_DEF_MEM_TYPE_BITS                  (2)
#define EFUSE_CHIP_DEF_MEM_TYPE_MSK                   ((0x01 << EFUSE_CHIP_DEF_MEM_TYPE_BITS) - 1)
#define EFUSE_CHIP_DEF_MEM_TYPE_SHIFT                 (5)

typedef enum
{
    EX_MEM_EFLASH             = 0, // Have memory, flash, Embed flash
    EX_MEM_EEPROM             = 1, // Have memory, eeprom
    EX_MEM_XIP_FLASH_FIXED_IO = 2, // Have memory, flash, xip flash, fixed io
    EX_MEM_XIP_FLASH_ANY_IO   = 3, // Have memory, flash, xip flash, any io

} EN_CHIP_DEF_MEM_TYPE_T;

// [4:3] Boot type
#define EFUSE_CHIP_DEF_BOOT_TYPE_BITS                 (2)
#define EFUSE_CHIP_DEF_BOOT_TYPE_MSK                  ((0x01 << EFUSE_CHIP_DEF_BOOT_TYPE_BITS) - 1)
#define EFUSE_CHIP_DEF_BOOT_TYPE_SHIFT                (3)

typedef enum
{
    BOOT_TYPE_SPI       = 0,
    BOOT_TYPE_UART      = 1,
    BOOT_TYPE_I2C       = 2,
    BOOT_TYPE_RESERVED  = 3,

} EN_CHIP_DEF_BOOT_TYPE_T;

// [2:0] Application ID
#define EFUSE_CHIP_DEF_ROM_APP_ID_BITS                (3)
#define EFUSE_CHIP_DEF_ROM_APP_ID_MSK                 ((0x01 << EFUSE_CHIP_DEF_ROM_APP_ID_BITS) - 1)
#define EFUSE_CHIP_DEF_ROM_APP_ID_SHIFT               (0)

typedef enum
{
    ROM_APP_ID_NONE    = 0,
    ROM_APP_ID_ROM_DTU = 1,
    ROM_APP_ID_ROM_RCU = 2,
    ROM_APP_ID_ROM_HID = 3,

} EN_CHIP_DEF_ROM_APP_ID_T;

// Chip Define - Flash
#define EFUSE_CHIP_DEF_MEM_TYPE_MASK                  (0xF8)
#define CHIP_DEF_FLASH_XIP_FIXED_IO                   (0xC0)
#define CHIP_DEF_FLASH_XIP_ANY_IO                     (0xE0)

//=============================================================================
// [0x09]PRODUCTION_DATE_YEAR, 4 bits, [3:0]
#define EFUSE_PRODUCTION_DATE_YEAR_ADDR               (0x09)
#define EFUSE_PRODUCTION_DATE_YEAR_BITS               (4)
#define EFUSE_PRODUCTION_DATE_YEAR_MSK                ((0x01 << EFUSE_PRODUCTION_DATE_YEAR_BITS) - 1)
#define EFUSE_PRODUCTION_DATE_YEAR_SHIFT              (0)

//=============================================================================
// [0x09]PRODUCTION_DATE_MON, 4 bits, [7:4]
#define EFUSE_PRODUCTION_DATE_MON_ADDR                (0x09)
#define EFUSE_PRODUCTION_DATE_MON_BITS                (4)
#define EFUSE_PRODUCTION_DATE_MON_MSK                 ((0x01 << EFUSE_PRODUCTION_DATE_MON_BITS) - 1)
#define EFUSE_PRODUCTION_DATE_MON_SHIFT               (4)

//=============================================================================
// [0x0A]PRODUCTION_DATE_DAY, 8 bits, [7:0]
#define EFUSE_PRODUCTION_DATE_DAY_ADDR                (0x0A)
#define EFUSE_PRODUCTION_DATE_DAY_BITS                (8)
#define EFUSE_PRODUCTION_DATE_DAY_MSK                 (0xFF)
#define EFUSE_PRODUCTION_DATE_DAY_SHIFT               (0)

//=============================================================================
// [0x0B]PRODUCTION_TIME_HOUR, 8 bits, [7:0]
#define EFUSE_PRODUCTION_TIME_HOUR_ADDR               (0x0B)
#define EFUSE_PRODUCTION_TIME_HOUR_BITS               (8)
#define EFUSE_PRODUCTION_TIME_HOUR_MSK                (0xFF)
#define EFUSE_PRODUCTION_TIME_HOUR_SHIFT              (0)

//=============================================================================
// [0x0C]PRODUCTION_TIME_MINUTE, 6 bits, [5:0]
#define EFUSE_PRODUCTION_TIME_MINUTE_ADDR             (0x0C)
#define EFUSE_PRODUCTION_TIME_MINUTE_BITS             (6)
#define EFUSE_PRODUCTION_TIME_MINUTE_MSK              ((0x01 << EFUSE_PRODUCTION_TIME_MINUTE_BITS) - 1)
#define EFUSE_PRODUCTION_TIME_MINUTE_SHIFT            (0)

//=============================================================================
// [0x0C]PRODUCTION_TIME_HMILLISECOND_LO, 2 bits, [7:6]
#define EFUSE_PRODUCTION_TIME_HMILLISECOND_LO_ADDR    (0x0C)
#define EFUSE_PRODUCTION_TIME_HMILLISECOND_LO_BITS    (2)
#define EFUSE_PRODUCTION_TIME_HMILLISECOND_LO_MSK     ((0x01 << EFUSE_PRODUCTION_TIME_HMILLISECOND_LO_BITS) - 1)
#define EFUSE_PRODUCTION_TIME_HMILLISECOND_LO_SHIFT   (6)

//=============================================================================
// [0x0D]PRODUCTION_TIME_SECOND, 6 bits, [5:0]
#define EFUSE_PRODUCTION_TIME_SECOND_ADDR             (0x0D)
#define EFUSE_PRODUCTION_TIME_SECOND_BITS             (6)
#define EFUSE_PRODUCTION_TIME_SECOND_MSK              ((0x01 << EFUSE_PRODUCTION_TIME_SECOND_BITS) - 1)
#define EFUSE_PRODUCTION_TIME_SECOND_SHIFT            (0)

//=============================================================================
// [0x0D]PRODUCTION_TIME_HMILLISECOND_HI, 2 bits, [7:6]
#define EFUSE_PRODUCTION_TIME_HMILLISECOND_HI_ADDR    (0x0D)
#define EFUSE_PRODUCTION_TIME_HMILLISECOND_HI_BITS    (2)
#define EFUSE_PRODUCTION_TIME_HMILLISECOND_HI_MSK     ((0x01 << EFUSE_PRODUCTION_TIME_HMILLISECOND_HI_BITS) - 1)
#define EFUSE_PRODUCTION_TIME_HMILLISECOND_HI_SHIFT   (6)

//=============================================================================
// [0x0E]PRODUCTION_EQUIPMENT_SOCKET_ID, 2 bits, [1:0]
#define EFUSE_PRODUCTION_EQUIPMENT_SOCKET_ID_ADDR     (0x0E)
#define EFUSE_PRODUCTION_EQUIPMENT_SOCKET_ID_BITS     (2)
#define EFUSE_PRODUCTION_EQUIPMENT_SOCKET_ID_MSK      ((0x01 << EFUSE_PRODUCTION_EQUIPMENT_SOCKET_ID_BITS) - 1)
#define EFUSE_PRODUCTION_EQUIPMENT_SOCKET_ID_SHIFT    (0)

//=============================================================================
// [0x0E]PRODUCTION_EQUIPMENT_HOST_ID, 6 bits, [7:2]
#define EFUSE_PRODUCTION_EQUIPMENT_HOST_ID_ADDR       (0x0E)
#define EFUSE_PRODUCTION_EQUIPMENT_HOST_ID_BITS       (6)
#define EFUSE_PRODUCTION_EQUIPMENT_HOST_ID_MSK        ((0x01 << EFUSE_PRODUCTION_EQUIPMENT_HOST_ID_BITS) - 1)
#define EFUSE_PRODUCTION_EQUIPMENT_HOST_ID_SHIFT      (2)

//=============================================================================
// [0x0F]RC_HCLK_TUNE, 8 bits
#define EFUSE_RC_HCLK_TUNE_ADDR                       (0x0F)
#define EFUSE_RC_HCLK_TUNE_BITS                       (8)
#define EFUSE_RC_HCLK_TUNE_MSK                        (0xFF)
#define EFUSE_RC_HCLK_TUNE_SHIFT                      (0)

//=============================================================================
// [0x10]RC_LCLK_TUNE, 8 bits
#define EFUSE_RC_LCLK_TUNE_ADDR                       (0x10)
#define EFUSE_RC_LCLK_TUNE_BITS                       (8)
#define EFUSE_RC_LCLK_TUNE_MSK                        (0xFF)
#define EFUSE_RC_LCLK_TUNE_SHIFT                      (0)

//=============================================================================
// [0x11~0x12]ADC0_VIO_LO_TUNE, 16 bits
#define EFUSE_ADC0_VIO_LO_TUNE_ADDR                   (0x11)
#define EFUSE_ADC0_VIO_LO_TUNE_BITS                   (16)
#define EFUSE_ADC0_VIO_LO_TUNE_MSK                    (0xFFFF)
#define EFUSE_ADC0_VIO_LO_TUNE_SHIFT                  (0)

//=============================================================================
// [0x13~0x14]ADC0_VIO_HI_TUNE, 16 bits
#define EFUSE_ADC0_VIO_HI_TUNE_ADDR                   (0x13)
#define EFUSE_ADC0_VIO_HI_TUNE_BITS                   (16)
#define EFUSE_ADC0_VIO_HI_TUNE_MSK                    (0xFFFF)
#define EFUSE_ADC0_VIO_HI_TUNE_SHIFT                  (0)

//=============================================================================
// [0x15~0x16]ADC1_VIO_LO_TUNE, 16 bits
#define EFUSE_ADC1_VIO_LO_TUNE_ADDR                   (0x15)
#define EFUSE_ADC1_VIO_LO_TUNE_BITS                   (16)
#define EFUSE_ADC1_VIO_LO_TUNE_MSK                    (0xFFFF)
#define EFUSE_ADC1_VIO_LO_TUNE_SHIFT                  (0)

//=============================================================================
// [0x17~0x18]ADC1_VIO_HI_TUNE, 16 bits
#define EFUSE_ADC1_VIO_HI_TUNE_ADDR                   (0x17)
#define EFUSE_ADC1_VIO_HI_TUNE_BITS                   (16)
#define EFUSE_ADC1_VIO_HI_TUNE_MSK                    (0xFFFF)
#define EFUSE_ADC1_VIO_HI_TUNE_SHIFT                  (0)

//=============================================================================
// [0x19~0x1A]ADC0_VDDR_LO_TUNE, 16 bits
#define EFUSE_ADC0_VDDR_LO_TUNE_ADDR                  (0x19)
#define EFUSE_ADC0_VDDR_LO_TUNE_BITS                  (16)
#define EFUSE_ADC0_VDDR_LO_TUNE_MSK                   (0xFFFF)
#define EFUSE_ADC0_VDDR_LO_TUNE_SHIFT                 (0)

//=============================================================================
// [0x1B~0x1C]ADC0_VDDR_HI_TUNE, 16 bits
#define EFUSE_ADC0_VDDR_HI_TUNE_ADDR                  (0x1B)
#define EFUSE_ADC0_VDDR_HI_TUNE_BITS                  (16)
#define EFUSE_ADC0_VDDR_HI_TUNE_MSK                   (0xFFFF)
#define EFUSE_ADC0_VDDR_HI_TUNE_SHIFT                 (0)

#define EFUSE_ADC_TUNE_BYTES                          (12)

//=============================================================================
// [0x1D]RF_TX_0DBM_TUNE, 8 bits
#define EFUSE_RF_TX_0DBM_TUNE_ADDR                    (0x1D)
#define EFUSE_RF_TX_0DBM_TUNE_BITS                    (8)
#define EFUSE_RF_TX_0DBM_TUNE_MSK                     (0xFF)
#define EFUSE_RF_TX_0DBM_TUNE_SHIFT                   (0)

//=============================================================================
// [0x1E]RF_TX_10DBM_TUNE, 8 bits
#define EFUSE_RF_TX_10DBM_TUNE_ADDR                   (0x1E)
#define EFUSE_RF_TX_10DBM_TUNE_BITS                   (8)
#define EFUSE_RF_TX_10DBM_TUNE_MSK                    (0xFF)
#define EFUSE_RF_TX_10DBM_TUNE_SHIFT                  (0)

//=============================================================================
// [0x1F]RF_RX_AGC_HI, 8 bits
#define EFUSE_RF_RX_AGC_HI_TUNE_ADDR                  (0x1F)
#define EFUSE_RF_RX_AGC_HI_TUNE_BITS                  (8)
#define EFUSE_RF_RX_AGC_HI_TUNE_MSK                   (0xFF)
#define EFUSE_RF_RX_AGC_HI_TUNE_SHIFT                 (0)

//=============================================================================
// [0x20]RF_RX_AGC_MID, 8 bits
#define EFUSE_RF_RX_AGC_MID_TUNE_ADDR                 (0x20)
#define EFUSE_RF_RX_AGC_MID_TUNE_BITS                 (8)
#define EFUSE_RF_RX_AGC_MID_TUNE_MSK                  (0xFF)
#define EFUSE_RF_RX_AGC_MID_TUNE_SHIFT                (0)

//=============================================================================
// [0x21]RF_RX_AGC_LO, 8 bits
#define EFUSE_RF_RX_AGC_LO_TUNE_ADDR                  (0x21)
#define EFUSE_RF_RX_AGC_LO_TUNE_BITS                  (8)
#define EFUSE_RF_RX_AGC_LO_TUNE_MSK                   (0xFF)
#define EFUSE_RF_RX_AGC_LO_TUNE_SHIFT                 (0)

//=============================================================================
// [0x22]RF_HD2_TUNE, 4 bits, [3:0]
#define EFUSE_RF_HD2_TUNE_ADDR                        (0x22)
#define EFUSE_RF_HD2_TUNE_BITS                        (4)
#define EFUSE_RF_HD2_TUNE_MSK                         ((0x01 << EFUSE_RF_HD2_TUNE_BITS) - 1)
#define EFUSE_RF_HD2_TUNE_SHIFT                       (0)

//=============================================================================
// [0x34~0x39]CUSTOM_MAC, 8 bits * 6 io = 48bits
#define EFUSE_CUSTOM_MAC_ADDR                         (0x34)
#define EFUSE_CUSTOM_MAC_BITS                         (48)
#define EFUSE_CUSTOM_MAC_MSK                          (0xFF)
#define EFUSE_CUSTOM_MAC_SHIFT                        (0)

//=============================================================================
// [0x3A~0x3F]FLASH_RESELECT_IO, 8 bits * 6 io = 48bits
#define EFUSE_FLASH_RESELECT_IO_ADDR                  (0x3A)
#define EFUSE_FLASH_RESELECT_IO_BITS                  (48)
#define EFUSE_FLASH_RESELECT_IO_MSK                   (0xFF)
#define EFUSE_FLASH_RESELECT_IO_SHIFT                 (0)




/**
 * @brief  Initialization efuse.
 * @param  u32Hz: Configure efuse clock, set when APB clk changed, (default 16000000).
 * @return Status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_efuse_init(uint32_t u32Hz);

/**
 * @brief  Read a mount of data from efuse.
 * @param  u8Addr: Indicate which address will be read. @ref EN_EFUSE_ADDR_T
 * @param  pu8Data: Pointer to the indicate data will be read.
 * @param  u8Len: Length of pu8Data.
 * @return Status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_efuse_read_bytes(uint8_t u8Addr, uint8_t* pu8Data, uint8_t u8Len);

/**
 * @brief  Write a mount of data to efuse with indirect mode.
 * @param  u8Addr: Indicate which address will be written. @ref EN_EFUSE_ADDR_T.
 * @param  pu8Data: Pointer to the indicate data will be written.
 * @param  u8Len: Length of pu8Data.
 * @return Status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_efuse_write_bytes(uint8_t u8Addr, uint8_t* pu8Data, uint8_t u8Len);


#ifdef __cplusplus
}
#endif

#endif /* __HW_EFUSE_H__ */

