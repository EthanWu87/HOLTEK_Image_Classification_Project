/*************************************************************************************************************
 * @file    reg_audio.h
 * @version V1.0
 * @date    2020-09-12
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


#ifndef __REG_AUDIO_H__
#define __REG_AUDIO_H__

#ifdef __cplusplus
extern "C"
{
#endif


//=====================================================================================================================
// DEFAULT CONFIG
//=====================================================================================================================
// enAdcCicEn: @ref EN_AUDIO_CIC_CTRL_T
// enAdcSlpfEn: @ref EN_AUDIO_SLPF_EN_T
// enAdcCompEn: @ref EN_AUDIO_COMP_FILTER_EN_T
#define AUDIO_ADC_INIT_DEFAULT(enAdcCicEn, enAdcSlpfEn, enAdcCompEn)           \
(   (EN_GAIN_MULT_ADC << AUDIO_CIC_DGC_SHIFT)                    | /* [4:0] */ \
    (0 << AUDIO_ADC_DBG_OUT_SHIFT)                               | /* [5] */   \
    (EN_AUDIO_ADC_CODE_COMP << AUDIO_ADC_CODE_MODE_SHIFT)        | /* [6] */   \
    (1 << AUDIO_CIC_SLPF_FLG_EN_SHIFT)                           | /* [7] */   \
    ((!enAdcSlpfEn) << AUDIO_CIC_SLPF_EN_SHIFT)                  | /* [8] */   \
    ((!enAdcCompEn) << AUDIO_CIC_COMP_FILTER_ENABLE_SHIFT)       | /* [9] */   \
    (EN_CIC_SOURCE_DATA_ENABLE << AUDIO_DATA_SOURCE_EN_SHIFT)    | /* [10] */  \
    (0x00)                                                       | /* [11] */  \
    (EN_AUDIO_ADC_POL_FALLING << AUDIO_ADC_POL_SHIFT)            | /* [12] */  \
    (EN_AUDIO_CIC_SOURCE_FROM_ADC << AUDIO_CIC_SOURCE_SEL_SHIFT) | /* [13] */  \
    (enAdcCicEn << AUDIO_CIC_CTRL_SHIFT)                         | /* [14] */  \
    (enAdcCicEn << AUDIO_CIC_ZERO_MOVE_EN_SHITF)                   /* [15] */  \
)

// enPdmCicEn: @ref EN_AUDIO_CIC_CTRL_T
// enPdmSlpfEn: @ref EN_AUDIO_SLPF_EN_T
// enPdmCompEn: @ref EN_AUDIO_COMP_FILTER_EN_T
// enPdmGainMult: @ref EN_PDM_GAIN_MULT
#define AUDIO_PDM_INIT_DEFAULT(enPdmCicEn, enPdmSlpfEn, enPdmCompEn, enPdmGainMult)   \
(   (enPdmGainMult << AUDIO_CIC_DGC_SHIFT)                       | /* [4:0] */        \
    (0 << AUDIO_ADC_DBG_OUT_SHIFT)                               | /* [5] */          \
    (EN_AUDIO_ADC_CODE_COMP << AUDIO_ADC_CODE_MODE_SHIFT)        | /* [6] */          \
    (1 <<AUDIO_CIC_SLPF_FLG_EN_SHIFT)                            | /* [7] */          \
    ((!enPdmSlpfEn) << AUDIO_CIC_SLPF_EN_SHIFT)                  | /* [8] */          \
    ((!enPdmCompEn) << AUDIO_CIC_COMP_FILTER_ENABLE_SHIFT)       | /* [9] */          \
    (EN_CIC_SOURCE_DATA_ENABLE << AUDIO_DATA_SOURCE_EN_SHIFT)    | /* [10] */         \
    (0x00)                                                       | /* [11] */         \
    (EN_AUDIO_ADC_POL_FALLING << AUDIO_ADC_POL_SHIFT)            | /* [12] */         \
    (EN_AUDIO_CIC_SOURCE_FROM_PDM << AUDIO_CIC_SOURCE_SEL_SHIFT) | /* [13] */         \
    (enPdmCicEn << AUDIO_CIC_CTRL_SHIFT)                         | /* [14] */         \
    (enPdmCicEn<< AUDIO_CIC_ZERO_MOVE_EN_SHITF)                    /* [15] */         \
)

// enPdmGainMult: @ref EN_PDM_GAIN_MULT
#define AUDIO_PDM_INIT_BITSTREM_MODE(enPdmGainMult)                                           \
(   (enPdmGainMult << AUDIO_CIC_DGC_SHIFT)                                      | /* [4:0] */ \
    (0 << AUDIO_ADC_DBG_OUT_SHIFT)                                              | /* [5] */   \
    (EN_AUDIO_ADC_CODE_COMP << AUDIO_ADC_CODE_MODE_SHIFT)                       | /* [6] */   \
    (0 << AUDIO_CIC_SLPF_FLG_EN_SHIFT)                                          | /* [7] */   \
    (EN_AUDIO_CIC_SLPF_DISABLE <<AUDIO_CIC_SLPF_EN_SHIFT)                       | /* [8] */   \
    ((!EN_AUDIO_CIC_COMP_FILTER_DISABLE) << AUDIO_CIC_COMP_FILTER_ENABLE_SHIFT) | /* [9] */   \
    (EN_CIC_SOURCE_DATA_DISABLE << AUDIO_DATA_SOURCE_EN_SHIFT)                  | /* [10] */  \
    (0x00)                                                                      | /* [11] */  \
    (EN_AUDIO_ADC_POL_FALLING << AUDIO_ADC_POL_SHIFT)                           | /* [12] */  \
    (EN_AUDIO_CIC_SOURCE_FROM_PDM << AUDIO_CIC_SOURCE_SEL_SHIFT)                | /* [13] */  \
    (EN_AUDIO_CIC_ENABLE << AUDIO_CIC_CTRL_SHIFT)                               | /* [14] */  \
    (EN_AUDIO_CIC_DISABLE<< AUDIO_CIC_ZERO_MOVE_EN_SHITF)                         /* [15] */  \
)


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t AUDIO_RX_FIFO;        /* [0x00](RO) */
    __IOM uint32_t AUDIO_DOWNSP;         /* [0x04](RW) */
    __IOM uint32_t AUDIO_COEFF0;         /* [0x08](RW) */
    __IOM uint32_t AUDIO_COEFF1;         /* [0x0C](RW) */
    __IOM uint32_t AUDIO_COEFF2;         /* [0x10](RW) */
    __IOM uint32_t AUDIO_COEFF3;         /* [0x14](RW) */
    __IOM uint32_t AUDIO_CFG;            /* [0x18](RW) */
    __IM  uint32_t AUDIO_INT_FLAG;       /* [0x1C](RO) */
    __OM  uint32_t AUDIO_INT_EN;         /* [0x20](WO) */
    __IOM uint32_t AUDIO_INT_CLR;        /* [0x24](RW) */
    __IM  uint32_t AUDIO_OVERFLOW_FLAG;  /* [0x28](RO) */
    __IOM uint32_t AUDIO_PDM_CFG;        /* [0x2C](RW) */
          uint32_t RESERVED;             /* [0x30]     */

    __IOM uint32_t AUDIO_EXT_CG_EN;      /* [0x34](RW) */

} stAUDIO_Handle_t, *pstAUDIO_Handle_t;

#define IS_VALID_AUDIO_HANDLE(pstAUDIO)  ((AUDIO0) == (pstAUDIO) ||\
                                          (AUDIO1) == (pstAUDIO))


//=====================================================================================================================
// [0x00](RO) AUDIO_RX_FIFO
//=====================================================================================================================
//=============================================================================
#define AUDIO_RX_FIFO_SHIFT                (0)
#define AUDIO_RX_FIFO_MSK                  (0xFFFFFFFF)


//=====================================================================================================================
// [0x04](RW) AUDIO_DOWNSP
//=====================================================================================================================
//=============================================================================
// AUDIO_DOWNSP[8:0] AUDIO OVERSAMPLE: Audio over sample value
#define AUDIO_SAMPLE_RATE_DIV_SHIFT        (0)
#define AUDIO_SAMPLE_RATE_DIV_MSK          ((0x01 << 9) - 1)
#define AUDIO_SAMPLE_RATE_DIV_DEFAULT      (0x1F4)

typedef enum
{
    EN_AUDIO_SAMPLE_RATE_8K    = 0,
    EN_AUDIO_SAMPLE_RATE_16K   = 1,
    EN_AUDIO_SAMPLE_RATE_22K   = 2,
    EN_AUDIO_SAMPLE_RATE_32K   = 3,
    EN_AUDIO_SAMPLE_RATE_44K   = 4,
    EN_AUDIO_SAMPLE_RATE_64K   = 5

} EN_AUDIO_SAMPLE_RATE_T;

#define IS_VALID_AUDIO_SAMPLE_RATE(RATE) ((RATE) <= EN_AUDIO_SAMPLE_RATE_64K)


//=====================================================================================================================
// [0x08~0x14](RW) AUDIO_COMP_COEFF0 ~ AUDIO_COMP_COEFF3: AUDIO Compensation Filter Coefficient x: < Signed>
//=====================================================================================================================
#define AUDIO_CIC_COMP_COEFFX_SHIFT        (0)
#define AUDIO_CIC_COMP_COEFFX_MSK          ((0x01 << 9) - 1)


//=====================================================================================================================
// [0x18](RW) AUDIO_CFG
//=====================================================================================================================
//=============================================================================
#define AUDIO_CFG_DEFAULT                  (0x408C)

//=============================================================================
// AUDIO_CFG[15] CIC_MOVE_ZERO, if CIC on, move zero
#define AUDIO_CIC_ZERO_MOVE_EN_SHITF       (15)
#define AUDIO_CIC_ZERO_MOVE_EN_MSK         ((0x01 << 1) - 1)

typedef enum
{
    EN_AUDIO_CIC_ZERO_MOVE_DISABLE = 0x00,
    EN_AUDIO_CIC_ZERO_MOVE_ENABLE  = 0x01

} EN_AUDIO_CIC_ZERO_MOVE_T;

//=============================================================================
// AUDIO_CFG[14] CIC CTRL: CIC enable/disable
#define AUDIO_CIC_CTRL_SHIFT               (14)
#define AUDIO_CIC_CTRL_MSK                 ((0x01 << 1) - 1)

typedef enum
{
    EN_AUDIO_CIC_DISABLE   = 0x00,
    EN_AUDIO_CIC_ENABLE    = 0x01,

} EN_AUDIO_CIC_CTRL_T;

#define IS_VALID_AUDIO_CIC_CTRL(MODE)    (((MODE) == EN_AUDIO_CIC_DISABLE) || \
                                          ((MODE) == EN_AUDIO_CIC_ENABLE))

//=============================================================================
// AUDIO_CFG[13] CIC_SOURCE_SEL: AUDIO Source select
#define AUDIO_CIC_SOURCE_SEL_SHIFT         (13)
#define AUDIO_CIC_SOURCE_SEL_MSK           ((0x01 << 1) - 1)

typedef enum
{
    EN_AUDIO_CIC_SOURCE_FROM_ADC = 0x00,
    EN_AUDIO_CIC_SOURCE_FROM_PDM = 0x01,

} EN_AUDIO_CIC_SOURCE_T;

#define IS_VALID_AUDIO_CIC_SOURCE(SRC)  (((SRC) == EN_AUDIO_CIC_SOURCE_FROM_ADC) || \
                                         ((SRC) == EN_AUDIO_CIC_SOURCE_FROM_PDM))

//=============================================================================
// AUDIO_CFG[12] AUDIO_ADC_POL: falling/Raising
#define AUDIO_ADC_POL_SHIFT                (12)
#define AUDIO_ADC_POL_MSK                  ((0x01 << 1) - 1)

typedef enum
{
    EN_AUDIO_ADC_POL_FALLING   = 0x00,
    EN_AUDIO_ADC_POL_RAISING   = 0x01

} EN_AUDIO_ADC_POL_T;

#define IS_VALID_AUDIO_ADC_POL(POL)  (((POL) == EN_AUDIO_ADC_POL_FALLING) || \
                                      ((POL) == EN_AUDIO_ADC_POL_RAISING))

//=============================================================================
// AUDIO_CFG[11] Reserved, Must be set 0

//=============================================================================
// AUDIO_CFG[10] AUDIO_DATA_SOURCE_EN
#define AUDIO_DATA_SOURCE_EN_SHIFT         (10)
#define AUDIO_DATA_SOURCE_EN_MSK           ((0x01 << 1) - 1)

typedef enum
{
    EN_CIC_SOURCE_DATA_ENABLE   = 0x00, /* Source not bypass: FIFO data comes from PDM and ADC data after CIC */
    EN_CIC_SOURCE_DATA_DISABLE  = 0x01  /* Source bypass: bypass CIC Date, FIFO data comes from PDM and ADC */

} EN_AUDIO_SOURCE_DATA_EN_T;

#define IS_VALID_AUDIO_SOURCE_DATA_EN(EN) (((EN) == EN_CIC_SOURCE_DATA_ENABLE) || \
                                           ((EN) == EN_CIC_SOURCE_DATA_DISABLE))

//=============================================================================
// AUDIO_CFG[9] AUDIO_CIC_COMP_FILTER_ENABLE
#define AUDIO_CIC_COMP_FILTER_ENABLE_SHIFT (9)
#define AUDIO_CIC_COMP_FILTER_ENABLE_MSK   ((0x01 << 1) - 1)

typedef enum
{
    EN_AUDIO_CIC_COMP_FILTER_ENABLE   = 0x01, /* Compensation filter not bypass */
    EN_AUDIO_CIC_COMP_FILTER_DISABLE  = 0x00  /* Compensation filter bypass */

} EN_AUDIO_COMP_FILTER_EN_T;

#define IS_VALID_AUDIO_COMP_FILTER_EN(EN)   (((EN) == EN_AUDIO_CIC_COMP_FILTER_ENABLE) ||\
                                             ((EN) == EN_AUDIO_CIC_COMP_FILTER_DISABLE))

//=============================================================================
// AUDIO_CFG[8] cic slpf ctrl
#define AUDIO_CIC_SLPF_EN_SHIFT            (8)
#define AUDIO_CIC_SLPF_EN_MSK              ((0x01 << 1) - 1)

typedef enum
{
    EN_AUDIO_CIC_SLPF_ENABLE   = 0x01, /* Strong low pass filter not bypass */
    EN_AUDIO_CIC_SLPF_DISABLE  = 0x00  /* Strong low pass filter bypass */

} EN_AUDIO_SLPF_EN_T;

#define IS_VALID_AUDIO_CIC_SLPF_EN_EN(EN)   (((EN) == EN_AUDIO_CIC_SLPF_ENABLE) || \
                                             ((EN) == EN_AUDIO_CIC_SLPF_DISABLE))

//=============================================================================
// AUDIO_CFG[7] CIC_SLPF_FLAG_EN
// If cic is enabled, this bit must be set to 1; or don't care.
#define AUDIO_CIC_SLPF_FLG_EN_SHIFT        (7)
#define AUDIO_CIC_SLPF_FLG_EN_MSK          ((0x01 << 1) - 1)

//=============================================================================
// AUDIO_CFG[6] AUDIO_CODE_MODE
#define AUDIO_ADC_CODE_MODE_SHIFT          (6)
#define AUDIO_ADC_CODE_MODE_MSK            ((0x01 << 1) - 1)

typedef enum
{
    EN_AUDIO_ADC_CODE_COMP  = 0,    // Complement Code
    EN_AUDIO_ADC_CODE_ORG   = 1,    // Original Code

} EN_AUDIO_ADC_CODE_MODE_T;

#define CIC_ADC_CODE_MODE_VALID(MODE)    (((MODE) == EN_AUDIO_ADC_CODE_COMP) ||\
                                          ((MODE) == EN_AUDIO_ADC_CODE_ORG))

//=============================================================================
// AUDIO_CFG[5] AUDIO_ADC_DBG_OUT
#define AUDIO_ADC_DBG_OUT_SHIFT            (5)
#define AUDIO_ADC_DBG_OUT_MSK              ((0x01 << 1) - 1)

//=============================================================================
// AUDIO_CFG [4:0] AUDIO_CIC_DGC
// CIC_CIC_DCR_N, Audio Adc mode Set 0, Audio pdm mode set @ref EN_PDM_GAIN_MULT
#define AUDIO_CIC_DGC_SHIFT                (0)
#define AUDIO_CIC_DGC_MSK                  ((0x01 << 5) - 1)

typedef enum
{
    EN_GAIN_MULT_PDM_2DBM   = 0x0A,
    EN_GAIN_MULT_PDM_4DBM   = 0x0C,
    EN_GAIN_MULT_PDM_6DBM   = 0x0E,
    EN_GAIN_MULT_PDM_8DBM   = 0x10,
    EN_GAIN_MULT_ADC        = 0x00,

} EN_PDM_GAIN_MULT;

#define IS_VALID_AUDIO_PDM_GAIN_MULT(GAIN)  (((GAIN) == EN_GAIN_MULT_PDM_2DBM) || \
                                             ((GAIN) == EN_GAIN_MULT_PDM_4DBM) || \
                                             ((GAIN) == EN_GAIN_MULT_PDM_6DBM) || \
                                             ((GAIN) == EN_GAIN_MULT_PDM_8DBM) || \
                                             ((GAIN) == EN_GAIN_MULT_ADC))


//=====================================================================================================================
// [0x1C](RO) CIC_STATUS: CIC Status Register
//=====================================================================================================================
//=============================================================================
// CIC_STATUS[1] cic fifo underflow
#define AUDIO_CIC_CLR_FIFO_UNDER_SHIFT     (1)
#define AUDIO_CIC_CLR_FIFO_UNDER_MSK       ((0x01 << 1) - 1)

//=============================================================================
// CIC_STATUS[0] cic fifo overflow
#define AUDIO_CIC_CLR_FIFO_OVERFLOW_SHIFT  (0)
#define AUDIO_CIC_CLR_FIFO_OVERFLOW_MSK    ((0x01 << 1) - 1)

typedef enum
{
    AUDIO_UNDER_FLOW = (AUDIO_CIC_CLR_FIFO_UNDER_MSK << AUDIO_CIC_CLR_FIFO_UNDER_SHIFT),
    AUDIO_OVER_FLOW  = (AUDIO_CIC_CLR_FIFO_OVERFLOW_MSK  << AUDIO_CIC_CLR_FIFO_OVERFLOW_SHIFT),

} EN_AUDIO_INT_FLAG_T;

#define AUDIO_INT_SHIFT                    (0x00)
#define AUDIO_INT_MASK                     (0x03)
#define AUDIO_INT_DEFAULT                  (AUDIO_OVER_FLOW | AUDIO_UNDER_FLOW)


//=====================================================================================================================
// [0x28](RO) CIC_OVFLOW:not used register
//=====================================================================================================================


//=====================================================================================================================
// [0x2C](RW) CIC_PDM_CONFIG：
//=====================================================================================================================
#define AUDIO_PDM_CLK_DEFAULT              (0x273)

//=============================================================================
// CIC_PDM_CONFIG[9] PDM_RATE_CFG, config pdm clock: 2M/1M
#define CIC_PDM_CONFIG_RATE_SHIFT          (9)
#define CIC_PDM_CINFIG_RATE_MSK            ((0x01 << 1) - 1)

typedef enum
{
    EN_PDM_CLOCK_1M = 0x00,
    EN_PDM_CLOCK_2M = 0x01,  // Recommended value.

} EN_PDM_CLOCK_T;

#define IS_VALID_AUDIO_PDM_CLOCK(CLK)   (((CLK)  == EN_PDM_CLOCK_1M) || \
                                          ((CLK)  == EN_PDM_CLOCK_2M))

//=============================================================================
// CIC_PDM_CONFIG[8] PDM_CTRL: PDM Mode Set 1, Adc Mode Set 0
#define AUDIO_PDM_CONFIG_CTRL_SHIFT        (8)
#define AUDIO_PDM_CONFIG_CTRL_MSK          ((0x01 << 1) - 1)

typedef enum
{
    EN_PDM_DISABLE = 0x00,
    EN_PDM_ENABLE  = 0x01,

} EN_PDM_CTRL_T;

#define IS_VALID_AUDIO_PDM_CTRL(EN)  (((EN) == EN_PDM_DISABLE) || \
                                      ((EN) == EN_PDM_ENABLE))

//=============================================================================
// CIC_PDM_CONFIG[7:4] AUDIO_PDM_CONFIG_FALL_EDGE, PDM falldge Count
#define AUDIO_PDM_CONFIG_FALL_EDGE_SHIFT   (4)
#define AUDIO_PDM_CONFIG_FALL_EDGE_MSK     ((0x01 << 4) - 1)

#define IS_VALID_AUDIO_PDM_FALL_COUNT(CNT) ((CNT) <= AUDIO_PDM_CONFIG_FALL_EDGE_MSK)

//=============================================================================
// CIC_PDM_CONFIG[3:0] PDM risedge Count
#define AUDIO_PDM_CONFIG_RISE_EDGE_SHIFT   (0)
#define AUDIO_PDM_CONFIG_RISE_EDGE_MSK     ((0x01 << 4) - 1)

#define IS_VALID_AUDIO_PDM_RISE_COUNT(CNT) ((CNT) <= AUDIO_PDM_CONFIG_RISE_EDGE_MSK)


//=====================================================================================================================
// [0x34](RW) AUDIO_EXT_CG_EN
//=====================================================================================================================
//=============================================================================
// AUDIO_EXT_CG_EN[0] cic extern clock ctrl
#define AUDIO_CIC_EXT_CLOCK_CTRL_SHIFT     (0)
#define AUDIO_CIC_EXT_CLOCK_CTRL_MSK       ((0x01 << 1) - 1)

typedef enum
{
    EN_CIC_EXT_CLOCK_ENABLE    = 0x01,
    EN_CIC_EXT_CLOCK_DISABLE   = 0x00,

} EN_CIC_EXT_CLOCK_CTRL_T;

#define IS_VALID_AUDIO_CIC_EXT_CLOCK_CTRL(EN) (((EN) == EN_CIC_EXT_CLOCK_ENABLE) || \
                                               ((EN) == EN_CIC_EXT_CLOCK_DISABLE))

#ifdef __cplusplus
}
#endif

#endif /* __REG_AUDIO_H__ */




