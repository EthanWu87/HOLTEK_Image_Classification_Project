/*************************************************************************************************************
 * @file    reg_trng.h
 * @version V1.1
 * @date    2022-01-23
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


#ifndef __REG_TRNG_H__
#define __REG_TRNG_H__

#ifdef __cplusplus
 extern "C" {
#endif

//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define TRNG_32BIT_DATA_LEN                (6)  // 192bit
#define TRNG_8BIT_DATA_LEN                 (24) // 192bit


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t TRNG_RX_FIFO;                   /* [0x000](RO) */
          uint32_t RESERVED[63];                   /* [0x004~0x0FC] */

    __IOM uint32_t TRNG_INT_EN;                    /* [0x100](RW) */
    __IM  uint32_t TRNG_INT_FLAG;                  /* [0x104](RO) */
    __OM  uint32_t TRNG_INT_CLR;                   /* [0x108](WO) */
    __IOM uint32_t TRNG_CFG;                       /* [0x10C](RW) */
    __IM  uint32_t TRNG_VALID;                     /* [0x110](RO) */
    __IM  uint32_t TRNG_DATA[TRNG_32BIT_DATA_LEN]; /* [0x114~0x128](RO) */
    __IOM uint32_t TRNG_ENABLE;                    /* [0x12C](RW) */
    __IOM uint32_t TRNG_SAMPLE_CNT;                /* [0x130](RW) */
    __IOM uint32_t TRNG_AUTOCORR;                  /* [0x134](RW) */
    __IOM uint32_t TRNG_BYPASS_CTRL;               /* [0x138](RW) */
          uint32_t RESERVED1;                      /* [0x13C] */

    __OM  uint32_t TRNG_RESET;                     /* [0x140](WO) */
          uint32_t RESERVED2[29];                  /* [0x144~0x1B4] */

    __IM  uint32_t TRNG_BUSY;                      /* [0x1B8](RO) */
    __OM  uint32_t TRNG_RESET_CNT;                 /* [0x1BC](WO) */
    __IM  uint32_t TRNG_VERSION;                   /* [0x1C0](RO) */
          uint32_t RESERVED3[7];                   /* [0x1C4~0x1DC] */

    __IM  uint32_t TRNG_BIST_CNT0;                 /* [0x1E0](RO) */
    __IM  uint32_t TRNG_BIST_CNT1;                 /* [0x1E4](RO) */
    __IM  uint32_t TRNG_BIST_CNT2;                 /* [0x1E8](RO) */
    __IOM uint32_t TRNG_ANA_CFG;                   /* [0x1EC](RW) */
    __IM  uint32_t TRNG_ANA_DATA;                  /* [0x1F0](RO) */

} stTRNG_Handle_t, *pstTRNG_Handle_t;




//=====================================================================================================================
// [0x00](RO) TRNG_RX_FIFO: DMA read TRNG FIFO data via this register
//=====================================================================================================================
#define TRNG_RX_FIFO_SHIFT                 (0)
#define TRNG_RX_FIFO_MSK                   (WORD_MSK)


//=====================================================================================================================
// [0x100~0x108] TRNG_INT_EN / TRNG_INT_FLAG / TRNG_INT_CLR
//=====================================================================================================================
#define TRNG_RXFIFO_READ_EMPTY_SHIFT       (5) /* RX FIFO read empty interrupt */
#define TRNG_RXFIFO_OVERFLOW_SHIFT         (4) /* RX FIFO overflow interrupt */
#define TRNG_VON_NEUMAN_ERR_SHIFT          (3) /* Error in von neuman occurs if 32 consecutive collected bits are identical, zero or one */
#define TRNG_TEST_FAIL_SHIFT               (2) /* Failure occurs when two consecutive blocks of 16 collected bits are equal. */
#define TRNG_AUTOCORR_FAIL_SHIFT           (1) /* Trng cease from functioning until next reset. */
#define TRNG_DONE_SHIFT                    (0) /* 192 bits trng have been collected in the rng, ready to be read. */

typedef enum
{
    TRNG_DONE                 = (0x01 << TRNG_DONE_SHIFT),
    TRNG_AUTOCORR_FAIL        = (0x01 << TRNG_AUTOCORR_FAIL_SHIFT),
    TRNG_TEST_FAIL            = (0x01 << TRNG_TEST_FAIL_SHIFT),
    TRNG_VON_NEUMAN_ERR       = (0x01 << TRNG_VON_NEUMAN_ERR_SHIFT),
    TRNG_RXFIFO_OVERFLOW      = (0x01 << TRNG_RXFIFO_OVERFLOW_SHIFT),
    TRNG_RXFIFO_READ_EMPTY    = (0x01 << TRNG_RXFIFO_READ_EMPTY_SHIFT),

} EN_TRNG_INT_FLAG_T;

#define TRNG_INT_MASK                      (0x3F)


//=====================================================================================================================
// [0x10C](RW) TRNG_CFG
//=====================================================================================================================
//=============================================================================
// TRNG_CFG[7:6] TRNG_LEVEL_CH3 Define
#define TRNG_LEVEL_CH3_SHIFT               (6)
#define TRNG_LEVEL_CH2_SHIFT               (4)
#define TRNG_LEVEL_CH1_SHIFT               (2)
#define TRNG_LEVEL_CH0_SHIFT               (0)

#define TRNG_LEVEL_CH_MSK                  ((0x01 << 2) - 1)

#define TRNG_LEVEL_SHIFT                   (0)
#define TRNG_LEVEL_MSK                     ((0x01 << 8) - 1)
#define TRNG_LEVEL_CFG                     (TRNG_LEVEL_MSK)


//=====================================================================================================================
// [0x110](RO) TRNG_VALID
//=====================================================================================================================
//=============================================================================
// TRNG_VALID[0] TRNG_VALID Define
#define TRNG_VALID_SHIFT                   (0)
#define TRNG_VALID_MSK                     ((0x01 << 1) - 1)

typedef enum
{
    EN_TRNG_DATA_UNREADY  = 0,
    EN_TRNG_DATA_READY    = 1,

} EN_TRNG_VALID_T;


//=====================================================================================================================
// [0x12C](RW) TRNG_ENABLE
//=====================================================================================================================
//=============================================================================
// TRNG_ENABLE[5] TRNG_DMA_EN Define
#define TRNG_DMA_EN_SHIFT                  (5)
#define TRNG_DMA_EN_MSK                    ((0x01 << 1) - 1)

//=============================================================================
// TRNG_ENABLE[4:0] TRNG_SRC_CH_EN Define
#define TRNG_SRC_CH_EN_SHIFT               (0)
#define TRNG_SRC_CH_EN_MSK                 ((0x01 << 5) - 1)

typedef enum
{
    EN_TRNG_SRC_DIG_CH0  = 0x01,
    EN_TRNG_SRC_DIG_CH1  = 0x02,
    EN_TRNG_SRC_DIG_CH2  = 0x04,
    EN_TRNG_SRC_DIG_CH3  = 0x08,
    EN_TRNG_SRC_ANA_CH   = 0x10,

} EN_TRNG_SRC_CH_EN_T;

#define EN_TRNG_SRC_ALL_DIG_CH             (0x0F)
#define EN_TRNG_SRC_ALL_CH                 (0x1F)

#define IS_VALID_TRNG_SRC_CH_EN(CH) ((CH) <= EN_TRNG_SRC_ALL_CH)


//=====================================================================================================================
// [0x130](RW) TRNG_SAMPLE_CNT
//=====================================================================================================================
//=============================================================================
// TRNG_VALID[0] TRNG_VALID Define
#define TRNG_SAMPLE_CNT_SHIFT              (0)
#define TRNG_SAMPLE_CNT_MSK                (0xFFFFFFFF)
#define TRNG_SAMPLE_CNT_CFG                (20)
#define TRNG_SAMPLE_CNT_4                  (4)

//=====================================================================================================================
// [0x138](RW) TRNG_BYPASS_CTRL
//=====================================================================================================================
//=============================================================================
// TRNG_BYPASS_CTRL[6] TRNG_OUT_SRC_SEL Define
#define TRNG_OUT_SRC_SEL_SHIFT             (6)
#define TRNG_OUT_SRC_SEL_MSK               ((0x01 << 1) - 1)

typedef enum
{
    EN_TRNG_OUT_PARALLEL_DATA  = 0,
    EN_TRNG_OUT_SERIAL_DATA    = 1,

} EN_TRNG_OUT_SRC_SEL_T;

//=============================================================================
// TRNG_BYPASS_CTRL[5] TRNG_CONTINUE_EN Define
#define TRNG_CONTINUE_EN_SHIFT             (5)
#define TRNG_CONTINUE_EN_MSK               ((0x01 << 1) - 1)

//=============================================================================
// TRNG_BYPASS_CTRL[4:0] TRNG_BYPASS_CTRL Define
#define TRNG_BYPASS_CTRL_SHIFT             (0)
#define TRNG_BYPASS_CTRL_MSK               ((0x01 << 5) - 1)
#define TRNG_BYPASS_CTRL_CFG               (0x0E)


//=====================================================================================================================
// [0x1EC](RW) TRNG_ANA_CFG
//=====================================================================================================================
//=============================================================================
// TRNG_ANA_CFG[2] TRNG_ANA_SRC_EN Define
#define TRNG_ANA_SRC_EN_SHIFT              (2)
#define TRNG_ANA_SRC_EN_MSK                ((0x01 << 1) - 1)


#ifdef __cplusplus
}
#endif

#endif /* __REG_TRNG_H__ */

