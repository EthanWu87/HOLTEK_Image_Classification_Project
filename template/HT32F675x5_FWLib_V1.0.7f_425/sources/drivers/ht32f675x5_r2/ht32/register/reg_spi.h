/*************************************************************************************************************
 * @file    reg_spi.h
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


#ifndef __REG_SPI_H__
#define __REG_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================================================================
// DEFAULT CONFIG
//=====================================================================================================================
#define SPI_INIT_DEFAULT(SPI_MODE, CPOL_CPHA, TRX_MODE)                 \
( (0 << SPI_ENABLE_SHIFT)                           | /* bit0 */        \
  (CPOL_CPHA << SPI_CPOL_CPHA_SHIFT)                | /* bit1~bit2 */   \
  (SPI_MODE << SPI_WORK_MODE_SHIFT)                 | /* bit3 */        \
  (0xFF << SPI_RX_TIMEOUT_THLD_SHIFT)               | /* bit4~bit11 */  \
  (TRX_MODE << SPI_TRX_MODE_SHIFT)                  | /* bit12~bit13 */ \
  (SPI_DATA_BITS_8 << SPI_DATA_SIZE_SHIFT)          | /* bit14~bit15 */ \
  (SPI_WORD_SPACE_DIS << SPI_WORD_SPACE_SHIFT)      | /* bit16 */       \
  (SPI_SW_SET_CS_HIGH << SPI_CS_SET_SHIFT)          | /* bit17 */       \
  (SPI_HW_CS << SPI_CS_MODE_SHIFT)                    /* bit18 */       \
)

//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __OM  uint32_t SPI_TX_FIFO;         /* [0x00](WO) */
    __IM  uint32_t SPI_RX_FIFO;         /* [0x04](RO) */
    __IM  uint32_t SPI_INT_FLAG;        /* [0x08](RO) */
    __IOM uint32_t SPI_INT_EN;          /* [0x0C](RW) */
    __OM  uint32_t SPI_INT_CLR;         /* [0x10](WO) */
    __IOM uint32_t SPI_CONFIG;          /* [0x14](RW) */
    __IOM uint32_t SPI_RX_LENGTH;       /* [0x18](RW) */
    __IOM uint32_t SPI_CLK_CFG;         /* [0x1C](RW) */
    __IOM uint32_t SPI_RXFIFO_THLD;     /* [0x20](RW) */
    __IOM uint32_t SPI_TXFIFO_THLD;     /* [0x24](RW) */
    __IM  uint32_t SPI_RXFIFO_CNT;      /* [0x28](RO) */
    __IM  uint32_t SPI_TXFIFO_CNT;      /* [0x2C](RO) */
    __IOM uint32_t SPI_AUTO_TX_CFG;     /* [0x30](RW) */
    __IOM uint32_t SPI_AUTO_RSP_CFG;    /* [0x34](RW) */
    __OM  uint32_t SPI_RXFIFO_CLR;      /* [0x38](WO) */
    __OM  uint32_t SPI_TXFIFO_CLR;      /* [0x3C](WO) */
    __IOM uint32_t SPI_EXT_CG_EN;       /* [0x40](RW) */

} stSPI_Handle_t, *pstSPI_Handle_t;

#define IS_VALID_SPI_HANDLE(pstSPI)   (((SPI0) == (pstSPI)) || ((SPI1) == (pstSPI)))


//=====================================================================================================================
// [0x00] SPI_TX_FIFO
//=====================================================================================================================
#define SPI_TX_FIFO_BITS                   (8)
#define SPI_TX_FIFO_SHIFT                  (0)
#define SPI_TX_FIFO_MSK                    ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x04] SPI_RX_FIFO
//=====================================================================================================================
#define SPI_RX_FIFO_BITS                   (8)
#define SPI_RX_FIFO_SHIFT                  (0)
#define SPI_RX_FIFO_MSK                    ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x08~0x10] SPI_INT_FLAG / SPI_INT_EN  / SPI_INT_CLR
//=====================================================================================================================
#define SPI_TX_FINISHED_SHIFT              (12)
#define SPI_RX_FINISHED_SHIFT              (11)
#define SPI_TXFIFO_FULL_SHIFT              (10)
#define SPI_RXFIFO_FULL_SHIFT              (9)
#define SPI_TXFIFO_OVERFLOW_SHIFT          (8)
#define SPI_TXFIFO_UNDERFLOW_SHIFT         (7)
#define SPI_RXFIFO_UNDERFLOW_SHIFT         (6)
#define SPI_RXFIFO_NOT_EMPTY_SHIFT         (5)
#define SPI_RXFIFO_OVERFLOW_SHIFT          (4)
#define SPI_RXFIFO_OVER_THLD_SHIFT         (3)
#define SPI_TXFIFO_EMPTY_SHIFT             (2)
#define SPI_TXFIFO_UNDER_THLD_SHIFT        (1)
#define SPI_RX_TIMEOUT_SHIFT               (0)

typedef enum
{
    SPI_INT_RXTIME_OUT              = (0x01 << SPI_RX_TIMEOUT_SHIFT),
    SPI_INT_TXFIFO_UNDER_THLD       = (0x01 << SPI_TXFIFO_UNDER_THLD_SHIFT),
    SPI_INT_TXFIFO_EMPTY            = (0x01 << SPI_TXFIFO_EMPTY_SHIFT),
    SPI_INT_RXFIFO_OVER_THLD        = (0x01 << SPI_RXFIFO_OVER_THLD_SHIFT),

    SPI_INT_RXFIFO_OVER_FLOW        = (0x01 << SPI_RXFIFO_OVERFLOW_SHIFT),
    SPI_INT_RXFIFO_NOT_EMPTY        = (0x01 << SPI_RXFIFO_NOT_EMPTY_SHIFT),
    SPI_INT_RXFIFO_UNDER_FLOW       = (0x01 << SPI_RXFIFO_UNDERFLOW_SHIFT),
    SPI_INT_TXFIFO_UNDER_FLOW       = (0x01 << SPI_TXFIFO_UNDERFLOW_SHIFT),

    SPI_INT_TXFIFO_OVER_FLOW        = (0x01 << SPI_TXFIFO_OVERFLOW_SHIFT),
    SPI_INT_RXFIFO_FULL             = (0x01 << SPI_RXFIFO_FULL_SHIFT),
    SPI_INT_TXFIFO_FULL             = (0x01 << SPI_TXFIFO_FULL_SHIFT),
    SPI_INT_RX_FINISHED             = (0x01 << SPI_RX_FINISHED_SHIFT),

    SPI_INT_TX_FINISHED             = (0x01 << SPI_TX_FINISHED_SHIFT),

} EN_SPI_INT_FLAG_T;

#define SPI_INT_MASK         (0x1FFF)


//=====================================================================================================================
// [0x14] SPI_CTRL_CFG Register
//=====================================================================================================================
#define SPI_CONFIG_DEFAULT                 (0x00000FF0)

//=============================================================================
// SPI_CTRL_CFG[18] SPI_CS_MODE Define
#define SPI_CS_MODE_SHIFT                  (18)
#define SPI_CS_MODE_MSK                    ((0x01 << 1) - 1)

typedef enum
{
    SPI_HW_CS  = 0x00,
    SPI_SW_CS  = 0x01,

} EN_SPI_CS_MODE_T;

#define IS_VALID_SPI_CS_MODE(MODE)  (((MODE) == SPI_HW_CS) || \
                                     ((MODE) == SPI_SW_CS))

//=============================================================================
// SPI_CTRL_CFG[17] SPI_SW_SET_CS Define
#define SPI_CS_SET_SHIFT                   (17)
#define SPI_CS_SET_MSK                     ((0x01 << 1) - 1)

typedef enum
{
    SPI_SW_SET_CS_LOW   = 0x00,
    SPI_SW_SET_CS_HIGH  = 0x01,

} EN_SPI_CS_LEVEL_T;

#define IS_VALID_SPI_CS(LEVEL)  (((LEVEL) == SPI_SW_SET_CS_HIGH) || \
                                 ((LEVEL) == SPI_SW_SET_CS_LOW))

//=============================================================================
// SPI_CTRL_CFG[16] SPI_WORD_SPACE_EN Define
#define SPI_WORD_SPACE_SHIFT               (16)
#define SPI_WORD_SPACE_MSK                 ((0x01 << 1) - 1)

typedef enum
{
    SPI_WORD_SPACE_DIS = 0x00,
    SPI_WORD_SPACE_EN  = 0x01,

} EN_SPI_WORD_SPACE_EN_T;

#define IS_VALID_SPI_WORD_SPACE_EN(MODE)  (((MODE) == SPI_WORD_SPACE_EN) || \
                                           ((MODE) == SPI_WORD_SPACE_DIS))

//=============================================================================
// SPI_CTRL_CFG[15:14] SPI_DATA_SIZE Define
#define SPI_DATA_SIZE_SHIFT                (14)
#define SPI_DATA_SIZE_MSK                  ((0x01 << 2) - 1)

typedef enum
{
    SPI_DATA_BITS_8     = 0x00,   /* 8-bit word length */

} EN_SPI_DATA_SIZE_T;

#define IS_VALID_SPI_DATA_BITS(BITS) (((BITS) == SPI_DATA_BITS_8))

//=============================================================================
// SPI_CTRL_CFG[13:12] SPI_TRX_MODE Define
#define SPI_TRX_MODE_SHIFT                 (12)
#define SPI_TRX_MODE_MSK                   ((0x01 << 2) - 1)

typedef enum
{
    SPI_MODE_FULL_TXRX  = 0x00,
    SPI_MODE_TX_ONLY    = 0x01,
    SPI_MODE_RX_ONLY    = 0x02,
    SPI_MODE_NONE_TXRX  = 0x03,

} EN_SPI_TRX_MODE_T;

#define IS_VALID_SPI_TRX_MODE(MODE) ((SPI_MODE_FULL_TXRX == (MODE)) \
                                  || (SPI_MODE_TX_ONLY == (MODE))   \
                                  || (SPI_MODE_RX_ONLY == (MODE))   \
                                  || (SPI_MODE_NONE_TXRX == (MODE)))

//=============================================================================
// SPI_CTRL_CFG[11:4] SPI_RX_TIMEOUT_THLD Define
#define SPI_RX_TIMEOUT_THLD_SHIFT          (4)
#define SPI_RX_TIMEOUT_THLD_MSK            ((0x01 << 8) - 1)

//=============================================================================
// SPI_CTRL_CFG[3] SPI_WORK_MODE  Define
#define SPI_WORK_MODE_SHIFT                (3)
#define SPI_WORK_MODE_MSK                  ((0x01 << 1) - 1)

typedef enum
{
    SPI_MODE_SLAVE  = 0x00,
    SPI_MODE_MASTER = 0x01,

} EN_SPI_WORK_MODE_T;

#define IS_VALID_SPI_WORK_MODE(MODE)  (((MODE) == SPI_MODE_MASTER) || \
                                       ((MODE) == SPI_MODE_SLAVE))

//=============================================================================
// SPI_CTRL_CFG[2:1] SPI_CPOL_CPHA   Define
#define SPI_CPOL_CPHA_SHIFT                (1)
#define SPI_CPOL_CPHA_MSK                  ((0x01 << 2) - 1)

typedef enum
{
    SPI_CPHA_0_0  = 0x00,
    SPI_CPHA_0_1  = 0x01,
    SPI_CPHA_1_0  = 0x02,
    SPI_CPHA_1_1  = 0x03,

} EN_SPI_CPHA_TYPE_T;


#define IS_VALID_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_0_0) || \
                                 ((CPHA) == SPI_CPHA_0_1) || \
                                 ((CPHA) == SPI_CPHA_1_0) || \
                                 ((CPHA) == SPI_CPHA_1_1))

//=============================================================================
// SPI_CTRL_CFG[0] SPI_ENABLE   Define
#define SPI_ENABLE_SHIFT                   (0)
#define SPI_ENABLE_MSK                     ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x18] SPI_RX_LENGTH Register
//=====================================================================================================================
#define SPI_RX_LENGTH_SHIFT                (0)
#define SPI_RX_LENGTH_MSK                  ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x1C] SPI_CLK_CFG Register
//=====================================================================================================================
#define SPI_CLK_DIV_SHIFT                  (0)
#define SPI_CLK_DIV_MSK                    ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x20] SPI_RXFIFO_THLD Register
//=====================================================================================================================
#define SPI_RXFIFO_THLD_SHIFT              (0)
#define SPI_RXFIFO_THLD_MSK                ((0x01 << 5) - 1)
#define SPI_RXFIFO_THLD_DEFAULT            (8)
#define SPI_RXFIFO_THLD_MAX                (16)


//=====================================================================================================================
// [0x24] SPI_TXFIFO_THLD Register
//=====================================================================================================================
#define SPI_TXFIFO_THLD_SHIFT              (0)
#define SPI_TXFIFO_THLD_MSK                ((0x01 << 5) - 1)
#define SPI_TXFIFO_THLD_DEFAULT            (8)
#define SPI_TXFIFO_THLD_MAX                (16)


//=====================================================================================================================
// [0x28] SPI_RXFIFO_CNT Register
//=====================================================================================================================
#define SPI_RXFIFO_CNT_SHIFT               (0)
#define SPI_RXFIFO_CNT_MSK                 ((0x01 << 5) - 1)
#define SPI_RXFIFO_CNT_MAX                 (16)


//=====================================================================================================================
// [0x2C] SPI_TXFIFO_CNT Register
//=====================================================================================================================
#define SPI_TXFIFO_CNT_SHIFT               (0)
#define SPI_TXFIFO_CNT_MSK                 ((0x01 << 5) - 1)
#define SPI_TXFIFO_CNT_MAX                 (16)


//=====================================================================================================================
// [0x30] SPI_AUTO_TX_CFG Register
//=====================================================================================================================
#define SPI_AUTO_TX_CFG_DEFAULT            (0x000000FF)

//=============================================================================
// SPI_AUTO_TX_CFG[8] SPI_AUTO_TX_EN Define
#define SPI_AUTO_TX_EN_SHIFT               (8)
#define SPI_AUTO_TX_EN_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// SPI_AUTO_TX_CFG[7:0] SPI_MST_AUTO_TX_DATA Define
#define SPI_MST_AUTO_TX_DATA_SHIFT         (0)
#define SPI_MST_AUTO_TX_DATA_MSK           ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x34] SPI_AUTO_RSP_CFG Register
//=====================================================================================================================
#define SPI_AUTO_RSP_CFG_DEFAULT           (0x00000000)

//=============================================================================
// SPI_AUTO_RSP_CFG[8] SPI_AUTO_RSP_EN Define
#define SPI_AUTO_RSP_EN_SHIFT              (8)
#define SPI_AUTO_RSP_EN_MSK                ((0x01 << 1) - 1)

typedef enum
{
    SPI_AUTO_RSP_DISABLE = 0x00,
    SPI_AUTO_RSP_ENABLE  = 0x01,

} EN_SPI_AUTO_RSP_EN_T;

#define IS_VALID_SPI_AUTO_RSP_EN(EN)  (((EN) == SPI_AUTO_RSP_ENABLE) || ((EN) == SPI_AUTO_RSP_DISABLE))

//=============================================================================
// SPI_AUTO_RSP_CFG[7:0] SPI_AUTO_RSP_CMD Define
#define SPI_AUTO_RSP_CMD_SHIFT             (0)
#define SPI_AUTO_RSP_CMD_MSK               ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x38] SPI_RXFIFO_CLR Register
//=====================================================================================================================
#define SPI_CLR_RXFIFO_SHIFT               (0)
#define SPI_CLR_RXFIFO_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x3C] SPI_TXFIFO_CLR Register
//=====================================================================================================================
#define SPI_CLR_TXFIFO_SHIFT               (0)
#define SPI_CLR_TXFIFO_MSK                 ((0x01 << 1) - 1)


#ifdef __cplusplus
}
#endif

#endif /* __REG_SPI_H__ */


