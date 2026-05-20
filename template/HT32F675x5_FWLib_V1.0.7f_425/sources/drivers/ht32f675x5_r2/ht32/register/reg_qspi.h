/*************************************************************************************************************
 * @file    reg_qspi.h
 * @version V1.1
 * @date    2022-01-18
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


#ifndef __REG_QSPI_H__
#define __REG_QSPI_H__

#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t QSPI_RX_FIFO;                    /* [0x00](RO) */
    __OM  uint32_t QSPI_TX_FIFO;                    /* [0x04](WO) */
    __IM  uint32_t QSPI_INT_FLAG;                   /* [0x08](RO) */
    __IOM uint32_t QSPI_INT_EN;                     /* [0x0C](RW) */
    __OM  uint32_t QSPI_INT_CLR;                    /* [0x10](WO) */
    __IOM uint32_t QSPI_TXFIFO_THLD;                /* [0x14](RW) */
    __IOM uint32_t QSPI_RXFIFO_THLD;                /* [0x18](RW) */
    __IOM uint32_t QSPI_CLK_EN;                     /* [0x1C](RW) */
    __IOM uint32_t QSPI_EXT_CG_EN;                  /* [0x20](RW) */
    __IOM uint32_t QSPI_SCRAMBLE_EN;                /* [0x24](RW) */
    __IOM uint32_t QSPI_SCRAMBLE_KEY;               /* [0x28](RW) */
    __IOM uint32_t QSPI_CFG;                        /* [0x2C](RW) */
    __IOM uint32_t QSPI_DELAY_CFG;                  /* [0x30](RW) */
    __IOM uint32_t QSPI_MEM_OPI_CFG;                /* [0x34](RW) */
          uint32_t RESERVED0[2];                    /* [0x38~0x3C] */

    __IOM uint32_t QSPI_MEM_TX_CFG;                 /* [0x40](RW) */
    __IOM uint32_t QSPI_MEM_DATA_LEN;               /* [0x44](RW) */
    __IOM uint32_t QSPI_MEM_CMD;                    /* [0x48](RW) */
    __IOM uint32_t QSPI_MEM_ADDR;                   /* [0x4C](RW) */
    __IOM uint32_t QSPI_MEM_LEN_CFG;                /* [0x50](RW) */
    __IOM uint32_t QSPI_FLASH_BUSY;                 /* [0x54](RW) */
    __IOM uint32_t QSPI_FLASH_AUTO_BUSY_EN;         /* [0x58](RW) */
    __IOM uint32_t QSPI_FLASH_CHECK_BUSY_INTERVAL;  /* [0x5C](RW) */
    __IOM uint32_t QSPI_FLASH_CHECK_BUSY_CMD;       /* [0x60](RW) */
    __IOM uint32_t QSPI_FLASH_SUSPEND_CTRL;         /* [0x64](RW) */
    __OM  uint32_t QSPI_FLASH_SUSPEND_EN;           /* [0x68](WO) */
    __OM  uint32_t QSPI_FLASH_TX_EN;                /* [0x6C](WO) */
    __IM  uint32_t QSPI_FLASH_AUTO_BUSY_FLAG;       /* [0x70](RO) */
          uint32_t RESERVED1[3];                    /* [0x74~0x7C] */

    __IOM uint32_t QSPI_MEM_CACHE_CMD1;             /* [0x80](RW) */
    __IOM uint32_t QSPI_MEM_CACHE_CMD2;             /* [0x84](RW) */
    __IOM uint32_t QSPI_FLASH_CACHE_DELAY_CFG;      /* [0x88](RW) */
    __IOM uint32_t QSPI_MEM_CACHE_CFG;              /* [0x8C](RW) */
    __IOM uint32_t QSPI_FLASH_CONTINUE_READ_CFG;    /* [0x90](RW) */
    __IM  uint32_t QSPI_FLASH_CONTINUE_STATUS;      /* [0x94](RO) */
    __OM  uint32_t QSPI_FLASH_RESET_CFG;            /* [0x98](WO) */
    __IM  uint32_t QSPI_FLASH_RESET_STATUS;         /* [0x9C](RO) */
    __IM  uint32_t QSPI_FLASH_CACHE_ACCESS_STATUS;  /* [0xA0](RO) */
    __IM  uint32_t QSPI_MEM_STATUS;                 /* [0xA4](RO) */
          uint32_t RESERVED2[6];                    /* [0xA8~0xBC] */

    __IOM uint32_t QSPI_LCD_CFG;                    /* [0xC0](RW) */
    __IOM uint32_t QSPI_LCD_CTRL;                   /* [0xC4](RW) */
    __OM  uint32_t QSPI_LCD_RX_EN;                  /* [0xC8](WO) */
    __IM  uint32_t QSPI_LCD_TX_STATUS;              /* [0xCC](RO) */
    __IM  uint32_t QSPI_LCD_RX_STATUS;              /* [0xD0](RO) */
    __IOM uint32_t QSPI_HPM_BYPASS_CFG;             /* [0xD4](RW) */
    __IOM uint32_t QSPI_AUTOM_RSP_CFG;              /* [0xD8](RW) */
    __OM  uint32_t QSPI_HPM_CLR;                    /* [0xDC](WO) */

} stQSPI_Handle_t, *pstQSPI_Handle_t;

#define IS_VALID_FLASH_HANDLE(handle)    ((FLASH0) == (handle) || (FLASH1) == (handle))
#define IS_VALID_QSPI_HANDLE(handle)     ((QSPI0) == (handle) || (QSPI1) == (handle))


//=====================================================================================================================
// [0x08~0x10] QSPI_INT_FLAG / QSPI_INT_EN  / QSPI_INT_CLR
//=====================================================================================================================
#define QSPI_RX_FINISHED_SHIFT             (9)
#define QSPI_TX_FINISHED_SHIFT             (8)
#define QSPI_RXFIFO_UNDER_FLOW_SHIFT       (7)
#define QSPI_RXFIFO_OVER_THLD_SHIFT        (6)
#define QSPI_RXFIFO_FULL_SHIFT             (5)
#define QSPI_RXFIFO_NOT_EMPTY_SHIFT        (4)
#define QSPI_TXFIFO_OVER_FLOW_SHIFT        (3)
#define QSPI_TXFIFO_UNDER_THLD_SHIFT       (2)
#define QSPI_TXFIFO_FULL_SHIFT             (1)
#define QSPI_TXFIFO_EMPTY_SHIFT            (0)

typedef enum
{
    QSPI_INT_TXFIFO_EMPTY         = (0x01 << QSPI_TXFIFO_EMPTY_SHIFT),
    QSPI_INT_TXFIFO_FULL          = (0x01 << QSPI_TXFIFO_FULL_SHIFT),
    QSPI_INT_TXFIFO_UNDER_THLD    = (0x01 << QSPI_TXFIFO_UNDER_THLD_SHIFT),
    QSPI_INT_TXFIFO_OVER_FLOW     = (0x01 << QSPI_TXFIFO_OVER_FLOW_SHIFT),
    QSPI_INT_RXFIFO_NOT_EMPTY     = (0x01 << QSPI_RXFIFO_NOT_EMPTY_SHIFT),
    QSPI_INT_RXFIFO_FULL          = (0x01 << QSPI_RXFIFO_FULL_SHIFT),
    QSPI_INT_RXFIFO_OVER_THLD     = (0x01 << QSPI_RXFIFO_OVER_THLD_SHIFT),
    QSPI_INT_RXFIFO_UNDER_FLOW    = (0x01 << QSPI_RXFIFO_UNDER_FLOW_SHIFT),
    QSPI_INT_TX_FINISHED          = (0x01 << QSPI_TX_FINISHED_SHIFT),
    QSPI_INT_RX_FINISHED          = (0x01 << QSPI_RX_FINISHED_SHIFT),

} EN_QSPI_INT_FLAG_T;

#define QSPI_INT_MASK      (0x3FF)


//=====================================================================================================================
// [0x24](RW) QSPI_SCRAMBLE_EN
//=====================================================================================================================
//=============================================================================
// QSPI_SCRAMBLE_EN[1:0] QSPI_SCRAMBLE_EN Define
#define QSPI_SCRAMBLE_EN_SHIFT             (0)
#define QSPI_SCRAMBLE_EN_MSK               ((0x01 << 2) - 1)


//=====================================================================================================================
// [0x28](RW) QSPI_SCRAMBLE_KEY
//=====================================================================================================================
//=============================================================================
// QSPI_SCRAMBLE_KEY[31:0] QSPI_SCRAMBLE_KEY Define
#define QSPI_SCRAMBLE_KEY_SHIFT            (0)
#define QSPI_SCRAMBLE_KEY_MSK              (WORD_MSK)


//=====================================================================================================================
// [0x2C](RW) QSPI_CFG
//=====================================================================================================================
//=============================================================================
// QSPI_CFG[5] QSPI_SAMPLE_EDGE_SEL Define
#define QSPI_SAMPLE_EDGE_SEL_SHIFT         (5)
#define QSPI_SAMPLE_EDGE_SEL_MSK           ((0x01 << 1) - 1)

//=============================================================================
// QSPI_CFG[4:3] QSPI_DATA_FORMATE Define
#define QSPI_DATA_FORMATE_SHIFT            (3)
#define QSPI_DATA_FORMATE_MSK              ((0x01 << 2) - 1)

typedef enum
{
    QSPI_DATA_FORMATE_FLASH     = 0x00,
    QSPI_DATA_FORMATE_LCD       = 0x01,
    QSPI_DATA_FORMATE_SPARE1    = 0x02,
    QSPI_DATA_FORMATE_SPARE2    = 0x03,

} EN_QSPI_DATA_FORMATE_T;

//=============================================================================
// QSPI_CFG[2] QSPI_SDA_MODE Define
#define QSPI_SDA_MODE_SHIFT                (2)
#define QSPI_SDA_MODE_MSK                  ((0x01 << 1) - 1)

typedef enum
{
    QSPI_SDA_MODE0 = 0x00, // SI used for send data, and SO used for receieve data when SPI read mode.
    QSPI_SDA_MODE1 = 0x01, // SI used for send and receieve data when SPI read mode.

} EN_QSPI_SDA_MODE_T;

//=============================================================================
// QSPI_CFG[1:0] QSPI_CPOL_CPHA Define
#define QSPI_CPOL_CPHA_SHIFT               (0)
#define QSPI_CPOL_CPHA_MSK                 ((0x01 << 2) - 1)

typedef enum
{
    QSPI_CPHA_0_0  = 0x00,
    QSPI_CPHA_0_1  = 0x01,
    QSPI_CPHA_1_0  = 0x02,
    QSPI_CPHA_1_1  = 0x03,

} EN_QSPI_CPHA_TYPE_T;

#define IS_VALID_QSPI_CPHA(CPHA) (((CPHA) == QSPI_CPHA_0_0) || \
                                  ((CPHA) == QSPI_CPHA_0_1) || \
                                  ((CPHA) == QSPI_CPHA_1_0) || \
                                  ((CPHA) == QSPI_CPHA_1_1))


//=====================================================================================================================
// [0x30](RW)QSPI_DELAY_CFG
//=====================================================================================================================
//=============================================================================
// QSPI_DELAY_CFG[5:3] QSPI_INPUT_DELAY Define
#define QSPI_INPUT_DELAY_SHIFT             (3)
#define QSPI_INPUT_DELAY_MSK               ((0x01 << 3) - 1)
#define QSPI_INPUT_DELAY_DEFAULT           (3)

//=============================================================================
// QSPI_DELAY_CFG[2:0] QSPI_OUTPUT_DELAY Define
#define QSPI_OUTPUT_DELAY_SHIFT            (0)
#define QSPI_OUTPUT_DELAY_MSK              ((0x01 << 3) - 1)


//=====================================================================================================================
// [0x40](RW) QSPI_MEM_TX_CFG
//=====================================================================================================================
//=============================================================================
// QSPI_MEM_TX_CFG[10:6] QSPI_MEM_CMD_TYPE Define
#define QSPI_MEM_CMD_TYPE_SHIFT            (6)
#define QSPI_MEM_CMD_TYPE_MSK              ((0x01 << 5) - 1)

typedef enum
{
    TPYE_CMD            = 0x00,
    TPYE_CMD_ADDR       = 0x0C,
    TPYE_CMD_ADDR_WRITE = 0x0D,
    TPYE_CMD_ADDR_READ  = 0x0E,
    TPYE_CMD_WRITE      = 0x14,
    TPYE_CMD_READ       = 0x18,

} EN_QSPI_MEM_CMD_TYPE_T;

//=============================================================================
// QSPI_MEM_TX_CFG[5:4] QSPI_MEM_CMD_MODE Define
#define QSPI_MEM_CMD_MODE_SHIFT            (4)
#define QSPI_MEM_CMD_MODE_MSK              ((0x01 << 2) - 1)

//=============================================================================
// QSPI_MEM_TX_CFG[3:2] QSPI_MEM_ADDR_MODE Define
#define QSPI_MEM_ADDR_MODE_SHIFT           (2)
#define QSPI_MEM_ADDR_MODE_MSK             ((0x01 << 2) - 1)

//=============================================================================
// QSPI_MEM_TX_CFG[1:0] QSPI_MEM_DATA_MODE Define
#define QSPI_MEM_DATA_MODE_SHIFT           (0)
#define QSPI_MEM_DATA_MODE_MSK             ((0x01 << 2) - 1)

typedef enum
{
    BUS_MODE_SPI = 0x00,
    BUS_MODE_DPI = 0x02,
    BUS_MODE_QPI = 0x03,

} EN_FLASH_BUS_MODE_T;

#define IS_VALID_FLASH_BUS_MODE(MODE)   (((MODE) == BUS_MODE_SPI) || \
                                         ((MODE) == BUS_MODE_DPI) || \
                                         ((MODE) == BUS_MODE_QPI))

#define QSPI_MEM_TX_CFG_MSK                ((0x01 << 11) - 1)


//=====================================================================================================================
// [0x50](RW) QSPI_MEM_LEN_CFG
//=====================================================================================================================
//=============================================================================
// QSPI_MEM_LEN_CFG[11:6] QSPI_MEM_CMD_LEN Define
#define QSPI_MEM_CMD_LEN_SHIFT             (6)
#define QSPI_MEM_CMD_LEN_MSK               ((0x01 << 6) - 1)

//=============================================================================
// QSPI_MEM_LEN_CFG[5:0] QSPI_MEM_ADDR_LEN Define
#define QSPI_MEM_ADDR_LEN_SHIFT            (0)
#define QSPI_MEM_ADDR_LEN_MSK              ((0x01 << 6) - 1)


//=====================================================================================================================
// [0x54](RW) QSPI_FLASH_BUSY
//=====================================================================================================================
//=============================================================================
// QSPI_FLASH_BUSY[0] QSPI_FLASH_BUSY Define
#define QSPI_FLASH_BUSY_SHIFT              (0)
#define QSPI_FLASH_BUSY_MSK                ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x58](RW) QSPI_FLASH_AUTO_BUSY_EN
//=====================================================================================================================
//=============================================================================
// QSPI_FLASH_AUTO_BUSY_EN[0] AUTO_BUSY_EN Define
#define AUTO_BUSY_EN_SHIFT                 (0)
#define AUTO_BUSY_EN_MSK                   ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x5C](RW) QSPI_FLASH_CHECK_BUSY_INTERVAL
//=====================================================================================================================
//=============================================================================
// QSPI_FLASH_CHECK_BUSY_INTERVAL[31:12] CHECK_BUSY_INIT_PERIOD
#define CHECK_BUSY_INIT_PERIOD_SHIFT       (12)
#define CHECK_BUSY_INIT_PERIOD_MSK         ((0x01 << 20) - 1)

//=============================================================================
// QSPI_FLASH_CHECK_BUSY_INTERVAL[11:0] CHECK_BUSY_PERIOD
#define CHECK_BUSY_PERIOD_SHIFT            (0)
#define CHECK_BUSY_PERIOD_MSK              ((0x01 << 12) - 1)


//=====================================================================================================================
// [0x60](RW) QSPI_FLASH_CHECK_BUSY_CMD
//=====================================================================================================================
//=============================================================================
// QSPI_FLASH_CHECK_BUSY_CMD[9:8] CHECK_BUSY_CMD_MODE
#define CHECK_BUSY_CMD_MODE_SHIFT          (8)
#define CHECK_BUSY_CMD_MODE_MSK            ((0x01 << 2) - 1)

//=============================================================================
// QSPI_FLASH_CHECK_BUSY_CMD[7:0] CHECK_BUSY_CMD
#define CHECK_BUSY_CMD_SHIFT               (0)
#define CHECK_BUSY_CMD_MSK                 ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x64](RW) QSPI_FLASH_SUSPEND_CTRL
//=====================================================================================================================
#define QSPI_FLASH_SUSPEND_CTRL_DEFAULT    (0x1eff140f)

//=============================================================================
// QSPI_FLASH_SUSPEND_CTRL[31:24] QSPI_FLASH_SUS_TPESL
#define QSPI_FLASH_SUS_TPESL_SHIFT         (24)
#define QSPI_FLASH_SUS_TPESL_MSK           ((0x01 << 8) - 1)
#define QSPI_FLASH_SUS_TPESL               (3 * 4) // 3 * 10 * 4 us = 120us

//=============================================================================
// QSPI_FLASH_SUSPEND_CTRL[23:16] QSPI_FLASH_SUS_TPEFOR
#define QSPI_FLASH_SUS_TPEFOR_SHIFT        (16)
#define QSPI_FLASH_SUS_TPEFOR_MSK          ((0x01 << 8) - 1)
#define QSPI_FLASH_SUS_TPEFOR              (50 * 4) // 50 * 10 * 4 us = 2000us

//=============================================================================
// QSPI_FLASH_SUSPEND_CTRL[15:8] QSPI_FLASH_SUS_TERS
#define QSPI_FLASH_SUS_TERS_SHIFT          (8)
#define QSPI_FLASH_SUS_TERS_MSK            ((0x01 << 8) - 1)
#define QSPI_FLASH_SUS_TERS                (2 * 4) // 2 * 10 * 4 = 80us

//=============================================================================
// QSPI_FLASH_SUSPEND_CTRL[7:0] QSPI_FLASH_SUS_UNIT_CFG
#define QSPI_FLASH_SUS_UNIT_CFG_SHIFT      (0)
#define QSPI_FLASH_SUS_UNIT_CFG_MSK        ((0x01 << 8) - 1)
#define QSPI_FLASH_SUS_UNIT_10US           (160) // 10us


//=====================================================================================================================
// [0x68](W0) QSPI_FLASH_SUSPEND_EN
//=====================================================================================================================
#define SUSPEND_EN_SHIFT                   (0)
#define SUSPEND_EN_MSK                     ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x6C](WO) QSPI_FLASH_TX_EN
//=====================================================================================================================
#define QSPI_FLASH_TX_EN_SHIFT             (0)
#define QSPI_FLASH_TX_EN_MSK               ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x70](RO) QSPI_FLASH_AUTO_BUSY_FLAG
//=====================================================================================================================
#define AUTO_BUSY_FLAG_SHIFT               (0)
#define AUTO_BUSY_FLAG_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x80] QSPI_MEM_CACHE_CMD1
//=====================================================================================================================
#define MEM_CACHE_CMD1_DEFAULT             (0xA37A750B)

//=============================================================================
// FLASH_CACHE_CMD1[31:24] MEM_CACHE_HPM_CMD Define
#define MEM_CACHE_HPM_CMD_SHIFT            (24)
#define MEM_CACHE_HPM_CMD_MSK              ((0x01 << 8) - 1)

//=============================================================================
// FLASH_CACHE_CMD1[23:16] MEM_CACHE_RES_CMD Define
#define MEM_CACHE_RES_CMD_SHIFT            (16)
#define MEM_CACHE_RES_CMD_MSK              ((0x01 << 8) - 1)

//=============================================================================
// FLASH_CACHE_CMD1[15:8] MEM_CACHE_SUS_CMD Define
#define MEM_CACHE_SUS_CMD_SHIFT            (8)
#define MEM_CACHE_SUS_CMD_MSK              ((0x01 << 8) - 1)

//=============================================================================
// FLASH_CACHE_CMD1[7:0] MEM_CACHE_READ_CMD Define
#define MEM_CACHE_READ_CMD_SHIFT           (0)
#define MEM_CACHE_READ_CMD_MSK             ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x84] QSPI_MEM_CACHE_CMD2
//=====================================================================================================================
#define MEM_CACHE_CMD2_DEFAULT             (0x0000A006)

//=============================================================================
// QSPI_MEM_CACHE_CMD2[23:16] MEM_CACHE_WRITE_CMD Define
#define MEM_CACHE_WRITE_CMD_SHIFT          (16)
#define MEM_CACHE_WRITE_CMD_MSK            ((0x01 << 8) - 1)

//=============================================================================
// QSPI_MEM_CACHE_CMD2[15:8] FLASH_CONTINUOUS_MODE Define
#define FLASH_CONTINUOUS_MODE_SHIFT        (8)
#define FLASH_CONTINUOUS_MODE_MSK          ((0x01 << 8) - 1)

//=============================================================================
// QSPI_MEM_CACHE_CMD2[7:0] FLASH_EXIT_HPM_MODE Define
#define FLASH_EXIT_HPM_MODE_SHIFT          (0)
#define FLASH_EXIT_HPM_MODE_MSK            ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x88]QSPI_FLASH_CACHE_DELAY_CFG
//=====================================================================================================================
//=============================================================================
// QSPI_FLASH_CACHE_DELAY_CFG[5:0] CACHE_HPM_DELAY_MAX Define
#define CACHE_HPM_DELAY_MAX_SHIFT          (0)
#define CACHE_HPM_DELAY_MAX_MSK            ((0x01 << 6) - 1)
#define CACHE_HPM_DELAY_MAX                (0x14)

//=====================================================================================================================
// [0x8C](RW) QSPI_MEM_CACHE_CFG
//=====================================================================================================================
// QSPI_MEM_CACHE_CFG[31:28] CACHE_ADDR_DUMMY_LEN Define
#define CACHE_ADDR_DUMMY_LEN_SHIFT         (28)
#define CACHE_ADDR_DUMMY_LEN_MSK           ((0x01 << 4) - 1)

//=============================================================================
// QSPI_MEM_CACHE_CFG[27] CACHE_WRITE_EN Define
#define CACHE_WRITE_EN_SHIFT               (27)
#define CACHE_WRITE_EN_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// QSPI_MEM_CACHE_CFG[26] CACHE_ADDR_MODE Define
#define CACHE_ADDR_MODE_SHIFT              (26)
#define CACHE_ADDR_MODE_MSK                ((0x01 << 1) - 1)

typedef enum
{
    CACHE_ADDR_3_BYTE = 0,
    CACHE_ADDR_4_BYTE = 1,

} EN_CACHE_ADDR_MODE_T;

//=============================================================================
// QSPI_MEM_CACHE_CFG[25:24] CACHE_CMD_BUS_MODE Define
#define CACHE_CMD_BUS_MODE_SHIFT           (24)
#define CACHE_CMD_BUS_MODE_MSK             ((0x01 << 2) - 1)

//=============================================================================
// QSPI_MEM_CACHE_CFG[23:22] CACHE_ADDR_BUS_MODE Define
#define CACHE_ADDR_BUS_MODE_SHIFT          (22)
#define CACHE_ADDR_BUS_MODE_MSK            ((0x01 << 2) - 1)

//=============================================================================
// QSPI_MEM_CACHE_CFG[21:20] CACHE_DATA_BUS_MODE Define
#define CACHE_DATA_BUS_MODE_SHIFT          (20)
#define CACHE_DATA_BUS_MODE_MSK            ((0x01 << 2) - 1)

//=============================================================================
// QSPI_MEM_CACHE_CFG[19:16] CACHE_CMD_DUMMY_LEN Define
#define CACHE_CMD_DUMMY_LEN_SHIFT          (16)
#define CACHE_CMD_DUMMY_LEN_MSK            ((0x01 << 4) - 1)
#define CACHE_CMD_DUMMY_LEN                (7)

//=============================================================================
// QSPI_MEM_CACHE_CFG[15:12] CACHE_CMD_LEN Define
#define CACHE_CMD_LEN_SHIFT                (12)
#define CACHE_CMD_LEN_MSK                  ((0x01 << 4) - 1)
#define CACHE_CMD_LEN                      (7)

//=============================================================================
// QSPI_MEM_CACHE_CFG[11:6] CACHE_ADDR_LEN Define
#define CACHE_ADDR_LEN_SHIFT               (6)
#define CACHE_ADDR_LEN_MSK                 ((0x01 << 6) - 1)
#define CACHE_ADDR_LEN                     (0x1F)
#define CACHE_DADDR_LEN                    (0x0F)
#define CACHE_QADDR_LEN                    (0x0B)

//=============================================================================
// QSPI_MEM_CACHE_CFG[5:0] CACHE_HPM_LEN Define
#define CACHE_HPM_LEN_SHIFT                (0)
#define CACHE_HPM_LEN_MSK                  ((0x01 << 6) - 1)
#define CACHE_HPM_LEN                      (0x1F)


//=====================================================================================================================
// [0x90](RW) FLASH_CONTINUE_READ_CFG
//=====================================================================================================================
#define FLASH_CONTINUE_READ_CFG_SHIFT      (0)
#define FLASH_CONTINUE_READ_CFG_MSK        ((0x01 << 8) - 1)
#define FLASH_CONTINUE_READ_CFG            (0xA0)


//=====================================================================================================================
// [0x94](RO) QSPI_FLASH_CONTINUE_STATUS
//=====================================================================================================================
#define QSPI_FLASH_CONTINUE_STATUS_SHIFT   (0)
#define QSPI_FLASH_CONTINUE_STATUS_MSK     ((0x01 << 1) - 1)
#define FLASH_IN_CONTINUE_READ_MODE        (QSPI_FLASH_CONTINUE_STATUS_MSK << QSPI_FLASH_CONTINUE_STATUS_SHIFT)


//=====================================================================================================================
//  STATUS Register
//=====================================================================================================================
typedef enum
{
    QSPI_DISABLE  = 0x00,
    QSPI_ENABLE   = 0x01,

} EN_QSPI_ENABLE_T;

#define IS_VALID_QSPI_ENABLE(EN)   (((EN) == QSPI_DISABLE) || ((EN) == QSPI_ENABLE))


//=====================================================================================================================
// [0xA4](RO) QSPI_MEM_STATUS
//=====================================================================================================================
#define QSPI_MEM_STATUS_SHIFT              (0)
#define QSPI_MEM_STATUS_MSK                ((0x01 << 1) - 1)
#define MEM_IN_BUSY_STATUS                 (QSPI_MEM_STATUS_MSK << QSPI_MEM_STATUS_SHIFT)


#ifdef __cplusplus
}
#endif

#endif /* __REG_QSPI_H__ */


