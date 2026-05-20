/*************************************************************************************************************
 * @file    reg_i2s.h
 * @version V1.1
 * @date    2022-01-22
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


#ifndef __REG_I2S_H__
#define __REG_I2S_H__

#ifdef __cplusplus
extern "C"
{
#endif

//=====================================================================================================================
// DEFAULT CONFIG
//=====================================================================================================================
#define I2S_CFG_INIT_DEFAULT(enMode, enStandard, enDataFormat, enChSel, enBclkCpol) \
(   (enBclkCpol << I2S_BCLK_CPOL_SHIFT)                      | /* [0] */            \
    (I2S_WCLK_CPOL_L << I2S_WCLK_CPOL_SHIFT)                 | /* [1] */            \
    (enStandard << I2S_STANDARD_SHIFT)                       | /* [3:2] */          \
    (enDataFormat << I2S_DATA_FORMAT_SHIFT)                  | /* [5:4] */          \
    (enChSel << I2S_CH_SEL_SHIFT)                            | /* [7:6] */          \
    (EN_I2S_MCLK_SEL_2M << I2S_MCLK_SEL_SHIFT)               | /* [9:8] */          \
    (enMode << I2S_WORK_MODE_SHIFT)                          | /* [10] */           \
    (3 << 11)                                                | /* [12:11] */        \
    (0)                                                      | /* [13] */           \
    (0 << I2S_MCLK_EN_SHIFT)                                 | /* [14] */           \
    (0x00)                                                   | /* [15] */           \
    (0x00)                                                   | /* [16] */           \
    (0x00)                                                   | /* [17] */           \
    (I2S_RX_DATA_RIGHT_LEFT << I2S_RX_DATA_STRG_EX_SHIFT)      /* [18] */           \
)


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t I2S_RX_FIFO;    /* [0x00](RO) */
    __OM  uint32_t I2S_TX_FIFO;    /* [0x04](Wo)*/
    __IM  uint32_t I2S_INT_FLAG;   /* [0x08](RO) */
          uint32_t RESERVED;       /* [0x0C] */

    __OM  uint32_t I2S_INT_CLR;    /* [0x10](WO) */
    __IOM uint32_t I2S_INT_EN;     /* [0x14](RW) */
    __IOM uint32_t I2S_CFG;        /* [0x18](RW) */
    __IOM uint32_t I2S_CFG2;       /* [0x1C](RW) */
    __IOM uint32_t I2S_EXT_CG_EN;  /* [0x20](RW) */

} stI2S_Handle_t, *pstI2S_Handle_t;


//=====================================================================================================================
// [0x00] I2S_RX_FIFO
//=====================================================================================================================
#define I2S_RX_FIFO_SHIFT                  (0)
#define I2S_RX_FIFO_MSK                    (WORD_MSK)
#define I2S_RX_FIFO_DEPTH                  (4)


//=====================================================================================================================
// [0x04] I2S_TX_FIFO
//=====================================================================================================================
#define I2S_TX_FIFO_SHIFT                  (0)
#define I2S_TX_FIFO_MSK                    (WORD_MSK)


//=====================================================================================================================
// [0x08~0x14] I2S_INT_FLAG / I2S_INT_SET / I2S_INT_CLR / I2S_INT_EN
//=====================================================================================================================
#define I2S_TX_DONE_SHIFT                  (9) // tx fifo empty,last bit shift out done
#define I2S_WCLK_TIMEOUT_SHIFT             (8) // if WCLK > 255*BLCK
#define I2S_WCLK_CLK_ERROR_SHIFT           (7) // WCLK appears within five BCLK, both high level and low level
#define I2S_TX_FIFO_OVER_FLOW_SHIFT        (6)
#define I2S_TX_FIFO_FULL_SHIFT             (5)
#define I2S_TX_FIFO_EMPTY_SHIFT            (4)
#define I2S_RX_FIFO_OVER_FLOW_SHIFT        (3)
#define I2S_RX_FIFO_UNDER_FLOW_SHIFT       (2)
#define I2S_RX_FIFO_FULL_SHIFT             (1)
#define I2S_RX_FIFO_NOT_EMPTY_SHIFT        (0)

typedef enum
{
    I2S_TX_DONE             = (0x01 << I2S_TX_DONE_SHIFT),
    I2S_WCLK_TIMEOUT        = (0x01 << I2S_WCLK_TIMEOUT_SHIFT),
    I2S_WCLK_CLK_ERROR      = (0x01 << I2S_WCLK_CLK_ERROR_SHIFT),
    I2S_TX_FIFO_OVER_FLOW   = (0x01 << I2S_TX_FIFO_OVER_FLOW_SHIFT),
    I2S_TX_FIFO_FULL        = (0x01 << I2S_TX_FIFO_FULL_SHIFT),
    I2S_TX_FIFO_EMPTY       = (0x01 << I2S_TX_FIFO_EMPTY_SHIFT),

    I2S_RX_FIFO_OVER_FLOW   = (0x01 << I2S_RX_FIFO_OVER_FLOW_SHIFT),
    I2S_RX_FIFO_UNDER_FLOW  = (0x01 << I2S_RX_FIFO_UNDER_FLOW_SHIFT),
    I2S_RX_FIFO_FULL        = (0x01 << I2S_RX_FIFO_FULL_SHIFT),
    I2S_RX_FIFO_NOT_EMPTY   = (0x01 << I2S_RX_FIFO_NOT_EMPTY_SHIFT),
    
} EN_I2S_INT_FLAG_T;

#define I2S_INT_MASK                       ((0x01 << 10) - 1)


//=====================================================================================================================
// I2S_CFG[0x18](RW) i2s cfg Register
//=====================================================================================================================
#define I2S_CFG_SHIFT                      (0)
#define I2S_CFG_MSK                        ((0x01 << 19) - 1)
#define I2S_CFG_DEFAULT                    (0x1835)

//=============================================================================
// I2S_CFG[18] I2S_RX_DATA_STRG_EX: I2S RX DATA storage to fifo exchage
#define I2S_RX_DATA_STRG_EX_SHIFT          (18)
#define I2S_RX_DATA_STRG_EX_MSK            ((0x01 << 1) - 1)

typedef enum
{
    I2S_RX_DATA_RIGHT_LEFT = 0x00, // hight 16 bits storage by left, low 16bit storage by right
    I2S_RX_DATA_LEFT_RIGHT = 0x01, // hight 16 bits storage by left, low 16bit storage by right

} EN_I2S_RX_DATA_STRG_EX_T;

#define IS_VALID_I2S_RX_DATA_STRG_EX(EXCHAGE)  (((EXCHAGE) == I2S_RX_DATA_RIGHT_LEFT) || \
                                                ((EXCHAGE) == I2S_RX_DATA_LEFT_RIGHT))

//=============================================================================
// I2S_CFG[17:15] Reserved

//=============================================================================
// I2S_CFG[14] I2S_MCLK_EN Define: Set/Read mclk status: enable or disable
#define I2S_MCLK_EN_SHIFT                  (14)
#define I2S_MCLK_EN_MSK                    ((0x01 << 1) - 1)

//=============================================================================
// I2S_CFG[13:11] Reserved.

//=============================================================================
// I2S_CFG[10] I2S_WORK_MODE Define: Set/Read i2s work mode: Master or Slave
#define I2S_WORK_MODE_SHIFT                (10)
#define I2S_WORK_MODE_MSK                  ((0x01 << 1) - 1)

typedef enum
{
    I2S_WORK_MODE_SLAVE     = 0x00,
    I2S_WORK_MODE_MASTER    = 0x01,

} EN_I2S_WORK_MODE_T;

#define IS_VALID_I2S_WORK_MODE(MODE)  (((MODE) == I2S_WORK_MODE_SLAVE) || \
                                       ((MODE) == I2S_WORK_MODE_MASTER))

//=============================================================================
// I2S_CFG[9:8] I2S_MCLK_SEL Define: Set/Read mclk freq value: 2/4/8/16Mhz
#define I2S_MCLK_SEL_SHIFT                 (8)
#define I2S_MCLK_SEL_MSK                   ((0x01 << 2) - 1)

typedef enum
{
    EN_I2S_MCLK_SEL_2M  = 0x00,
    EN_I2S_MCLK_SEL_4M  = 0x01,
    EN_I2S_MCLK_SEL_8M  = 0x02,
    EN_I2S_MCLK_SEL_16M = 0x03,

} EN_I2S_MCLK_SEL_T;

#define IS_VALID_I2S_MCLK_SEL(CLK) (((CLK) == EN_I2S_MCLK_SEL_2M) || \
                                     ((CLK) == EN_I2S_MCLK_SEL_4M) || \
                                     ((CLK) == EN_I2S_MCLK_SEL_8M) || \
                                     ((CLK) == EN_I2S_MCLK_SEL_16M))

//=============================================================================
// I2S_CFG[7:6] I2S_CH_SEL Define: Set/Read I2s channel: Left/Right/Stereo
#define I2S_CH_SEL_SHIFT                   (6)
#define I2S_CH_SEL_MSK                     ((0x01 << 2) - 1)

typedef enum
{
    I2S_CH_DISABLE = 0x00,
    I2S_CH_LEFT    = 0x01,
    I2S_CH_RIGHT   = 0x02,
    I2S_CH_STEREO  = 0x03,

} EN_I2S_CH_SEL_T;

#define IS_VALID_I2S_CH_SEL(CH) (((CH) == I2S_CH_DISABLE) || \
                                  ((CH) == I2S_CH_LEFT)    || \
                                  ((CH) == I2S_CH_RIGHT)   || \
                                  ((CH) == I2S_CH_STEREO))

//=============================================================================
// I2S_CFG[5:4] I2S_DATA FORMAT Define
// Set/Read i2s data Format: 16Bit/20Bit/24Bit/32Bit, but 32bit only i2s/Ljf support, pcm-A&pcm-B not support
#define I2S_DATA_FORMAT_SHIFT              (4)
#define I2S_DATA_FORMAT_MSK                ((0x01 << 2) - 1)

typedef enum
{
    EN_I2S_DATA_FORMAT_16BIT = 0x00,
    EN_I2S_DATA_FORMAT_20BIT = 0x01,
    EN_I2S_DATA_FORMAT_24BIT = 0x02,
    EN_I2S_DATA_FORMAT_32BIT = 0x03, //only support i2s ljf

} EN_I2S_DATA_FORMAT_T;

#define IS_VALID_I2S_DATA_FORMAT(DATAFORMAT) (((DATAFORMAT) == EN_I2S_DATA_FORMAT_16BIT) || \
                                               ((DATAFORMAT) == EN_I2S_DATA_FORMAT_20BIT) || \
                                               ((DATAFORMAT) == EN_I2S_DATA_FORMAT_24BIT) || \
                                               ((DATAFORMAT) == EN_I2S_DATA_FORMAT_32BIT))

//=============================================================================
// I2S_CFG[3:2] I2S_STANDARD, I2S_standard Define: i2s standard reg
#define I2S_STANDARD_SHIFT                 (2)
#define I2S_STANDARD_MSK                   ((0x01 << 2) - 1)

typedef enum
{
    I2S_STANDARD_LJF   = 0x00,
    I2S_STANDARD_I2S   = 0x01,
    I2S_STANDARD_PCM_A = 0x02,
    I2S_STANDARD_PCM_B = 0x03,

} EN_I2S_STANDARD_T;

#define IS_VALID_I2S_STANDARD(STANDARD)  (((STANDARD) == I2S_STANDARD_LJF)   || \
                                           ((STANDARD) == I2S_STANDARD_I2S)   || \
                                           ((STANDARD) == I2S_STANDARD_PCM_A) || \
                                           ((STANDARD) == I2S_STANDARD_PCM_B))

//=============================================================================
// I2S_CFG[1] I2S_INVERT_WCLK Define
#define I2S_WCLK_CPOL_SHIFT                (1)
#define I2S_WCLK_CPOL_MSK                  ((0x01 << 1) - 1)

typedef enum
{
    I2S_WCLK_CPOL_L = 0x00,  /* L: left,  H: right */
    I2S_WCLK_CPOL_H = 0x01,  /* L: Right, H: left */

} EN_I2S_WCLK_CPOL_T;

#define IS_VALID_I2S_WCLK_CPOL(LEVEL)  (((LEVEL) == I2S_WCLK_CPOL_L) || \
                                        ((LEVEL) == I2S_WCLK_CPOL_H))

//=============================================================================
// I2S_CFG[0] I2S_BCLK_EDGE Define
#define I2S_BCLK_CPOL_SHIFT                (0)
#define I2S_BCLK_CPOL_MSK                  ((0x01 << 1) - 1)

typedef enum
{
    I2S_BCLK_CPOL_NEGATIVE = 0x00,  /* sample on rising edge  */
    I2S_BCLK_CPOL_POSITIVE = 0x01,  /* sample on falling edge */

} EN_I2S_BCLK_CPOL_T;

#define IS_VALID_I2S_BCLK_CPOL(CPOL)  (((CPOL) == I2S_BCLK_CPOL_NEGATIVE) || \
                                       ((CPOL) == I2S_BCLK_CPOL_POSITIVE))


//=====================================================================================================================
// [0x1C](RW) I2S_CFG2 Register
//=====================================================================================================================
#define I2S_CFG2_DEFAULT                   (0x20)

//=============================================================================
// I2S_CFG2[9] TX EN Define
#define I2S_TX_ENABLE_SHIFT                (9)
#define I2S_TX_ENABLE_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// I2S_CFG2[8] RX EN Define
#define I2S_RX_ENABLE_SHIFT                (8)
#define I2S_RX_ENABLE_MSK                  ((0x01 << 1) - 1)

#define I2S_TRX_ENABLE_MSK                 ((0x01 << 2) - 1)


//=============================================================================
// I2S_CFG2[7:0] WCLK WIDTH Define: Sample Freq div or TRX data Width
#define I2S_WCLK_WIDTH_SHIFT               (0)
#define I2S_WCLK_WIDTH_MSK                 ((0x01 << 8) - 1)

typedef enum
{
    EN_I2S_WCLK_WIDTH_16 = 16,
    EN_I2S_WCLK_WIDTH_32 = 32,
    
} EN_I2S_WCLK_WIDTH_T;

#define IS_VALID_I2S_WCLK_WIDTH(VALUE)  (((VALUE) == EN_I2S_WCLK_WIDTH_16) || \
                                         ((VALUE) == EN_I2S_WCLK_WIDTH_32))

typedef enum
{
    EN_I2S_SAMPLE_RATE_8K  = 0,
    EN_I2S_SAMPLE_RATE_16K = 1,
    EN_I2S_SAMPLE_RATE_32K = 2,
    EN_I2S_SAMPLE_RATE_44K = 3,
    EN_I2S_SAMPLE_RATE_64K = 4
    
} EN_I2S_SAMPLE_RATE_T;

#define IS_VALID_I2S_SAMPLE_RATE(RATE) ((RATE) <= EN_I2S_SAMPLE_RATE_64K)


//=====================================================================================================================
// [0x20](RW) I2S_Ext_Crg_Clock Register
//=====================================================================================================================
#define I2S_CLOCK_CFG_SHIFT                (0)
#define I2S_CLOCK_CFG_MSK                  ((0x01 << 1)- 1)


#ifdef __cplusplus
}
#endif

#endif /* __REG_I2S_H__ */


