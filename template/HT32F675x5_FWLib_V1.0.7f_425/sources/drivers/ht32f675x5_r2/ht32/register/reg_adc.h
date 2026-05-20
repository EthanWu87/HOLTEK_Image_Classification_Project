/*************************************************************************************************************
 * @file    reg_adc.h
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


#ifndef __REG_ADC_H__
#define __REG_ADC_H__

#ifdef __cplusplus
extern "C"
{
#endif

//=====================================================================================================================
// DEFAULT CONFIG
//=====================================================================================================================
#define ADC_CFG_INIT_DEFAULT(enFormat, enCIC)                           \
(   (0 << ADC_CIC_DOWNSP_DGC_SHIFT)                      | /* [4:0]  */ \
    (0)                                                  | /* [5]    */ \
    (enFormat << ADC_DATA_FORMAT_SHIFT)                  | /* [6]    */ \
    (enCIC << ADC_CIC_EN_SHIFT)                          | /* [7]    */ \
    (ADC_SAMP_BY_NEG_EDGE << ADC_SAMP_MODE_SHIFT)        | /* [8]    */ \
    (EN_ADC_FIFO_THLD_HALF_WORD << ADC_FIFO_THLD_SHIFT)  | /* [10:9] */ \
    (ADC_CLK_EN_DYNAMIC << ADC_CLK_EN_MODE_SHIFT)        | /* [11]   */ \
    (ADC_DATA_0_TO_1 << ADC_DATA_PROCESS_MODE_SHIFT)     | /* [12]   */ \
    (0 << ADC_COMPST_FLITER_EN_SHIFT)                    | /* [13]   */ \
    (4 << ADC_DOWNSP_OUT_THLD_SHIFT)                       /* [16:14]*/ \
)


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t ADC_RX_FIFO;        /* [0x00](RO) */
    __IOM uint32_t ADC_DOWNSP;         /* [0x04](RW) */
    __IOM uint32_t ADC_COEFF0;         /* [0x08](RW) */
    __IOM uint32_t ADC_COEFF1;         /* [0x0C](RW) */
    __IOM uint32_t ADC_COEFF2;         /* [0x10](RW) */
    __IOM uint32_t ADC_COEFF3;         /* [0x14](RW) */
    __IOM uint32_t ADC_CFG;            /* [0x18](RW) */
    __IM  uint32_t ADC_INT_FLAG;       /* [0x1C](RO) */
    __OM  uint32_t ADC_INT_CLR;        /* [0x20](WO) */
    __IOM uint32_t ADC_INT_EN;         /* [0x24](RW) */
    __IM  uint32_t ADC_OVERFLOW;       /* [0x28](RO) */
    __IOM uint32_t ADC_SAMP_CFG;       /* [0x2C](RW) */
    __IOM uint32_t ADC_ENABLE;         /* [0x30](RW) */
          uint32_t RESERVED[8];        /* [0x34~0x50] */

    __IOM uint32_t ADC_DEBUG_CFG;      /* [0x54](RW) */
    __IOM uint32_t ADC_CH_EN;          /* [0x58](RW) */
    __IOM uint32_t ADC_STABLE_TIME;    /* [0x5C](RW) */
    __IOM uint32_t ADC_SAMP_NUM;       /* [0x60](RW) */
    __OM  uint32_t ADC_TRIG;           /* [0x64](WO) */
    __IM  uint32_t ADC_STATUS;         /* [0x68](RO) */
    __IM  uint32_t ADC_CFG_STATUS;     /* [0x6C](RO) */

} stADC_Handle_t, *pstADC_Handle_t;

#define IS_VALID_ADC_HANDLE(pstADC)    ((ADC0) == (pstADC) || (ADC1) == (pstADC))


//=====================================================================================================================
// [0x00](RO) ADC_RX_FIFO
//=====================================================================================================================
//=============================================================================
//ADC_RX_FIFO[15:0] ADC_RX_FIFO, fifo depth is 8
#define ADC_RX_FIFO_SHIFT                  (0)
#define ADC_RX_FIFO_MSK                    (0xFFFF)


//=====================================================================================================================
// [0x04](RW) ADC_DOWNSP, Set adc accuracy by setting adc downsample.
//=====================================================================================================================
//=============================================================================
// ADC_DOWNSP[11:0] ADC_DOWNSP
#define ADC_DOWNSP_SHIFT                   (0)
#define ADC_DOWNSP_MSK                     ((0x01 << 12) - 1)

typedef enum
{
    EN_ADC_DOWNSP_10BIT  = 0x0200,
    EN_ADC_DOWNSP_11BIT  = 0x0004,
    EN_ADC_DOWNSP_12BIT  = 0x0010,
    EN_ADC_DOWNSP_13BIT  = 0x0040,
    EN_ADC_DOWNSP_14BIT  = 0x0100,

} EN_ADC_DOWNSP_MODE_T;

#define IS_VALID_ADC_DOWNSP(VALUE) (((VALUE) == EN_ADC_DOWNSP_10BIT)  \
                                 || ((VALUE) == EN_ADC_DOWNSP_11BIT)  \
                                 || ((VALUE) == EN_ADC_DOWNSP_12BIT)  \
                                 || ((VALUE) == EN_ADC_DOWNSP_13BIT)  \
                                 || ((VALUE) == EN_ADC_DOWNSP_14BIT))


//=====================================================================================================================
// [0x18](RW) ADC_CFG
//=====================================================================================================================
#define ADC_CFG_DEFAULT                    (0x3800)

//=============================================================================
//ADC_CFG[16:14] ADC_DOWNSP_OUT_THLD
#define ADC_DOWNSP_OUT_THLD_SHIFT          (14)
#define ADC_DOWNSP_OUT_THLD_MSK            ((0x01 << 3) - 1)

//=============================================================================
//ADC_CFG[13] ADC_COMPST_FLITER_EN:
#define ADC_COMPST_FLITER_EN_SHIFT         (13)
#define ADC_COMPST_FLITER_EN_MSK           ((0x01 << 1) - 1)

//=============================================================================
// ADC_CFG[12] ADC_DATA_PROCESS_MODE
#define ADC_DATA_PROCESS_MODE_SHIFT        (12)
#define ADC_DATA_PROCESS_MODE_MSK          ((0x01 << 1) - 1)

typedef enum
{
    ADC_DATA_NO_PROCESS = 0x00,
    ADC_DATA_0_TO_1     = 0x01,

} EN_ADC_DATA_PROCESS_MODE_T;

//=============================================================================
// ADC_CFG[11] ADC_CLK_EN_MODE Define
#define ADC_CLK_EN_MODE_SHIFT              (11)
#define ADC_CLK_EN_MODE_MSK                ((0x01 << 1) - 1)

typedef enum
{
    ADC_CLK_EN_ALWAYS  = 0x00,
    ADC_CLK_EN_DYNAMIC = 0x01,

} EN_ADC_CLK_EN_MODE_T;

//=============================================================================
// ADC_CFG[10:9] ADC_FIFO_THLD Define
#define ADC_FIFO_THLD_SHIFT                (9)
#define ADC_FIFO_THLD_MSK                  ((0x01 << 2) - 1)

typedef enum
{
    EN_ADC_FIFO_THLD_HALF_WORD    = 0x00,  // fifo not empty
    EN_ADC_FIFO_THLD_ONE_WORD     = 0x01,  // fifo 1/4 full req
    EN_ADC_FIFO_THLD_TWO_WORD     = 0x02,  // fifo 2/4 full req
    EN_ADC_FIFO_THLD_FOUR_WORD    = 0x03,  // fifo 4/4 full req

} EN_ADC_FIFO_THLD_T;

#define IS_VALID_ADC_FIFO_THLD(THLD)       ((THLD) <= ADC_FIFO_THLD_MSK)

//=============================================================================
// ADC_CFG[8] ADC_SAMP_MODE
#define ADC_SAMP_MODE_SHIFT                (8)
#define ADC_SAMP_MODE_MSK                  ((0x01 << 1) - 1)

typedef enum
{
    ADC_SAMP_BY_NEG_EDGE = 0x00, /* falling edge */
    ADC_SAMP_BY_POS_EDGE = 0x01, /* rising  edge */

} EN_ADC_SAMP_MODE_T;

#define IS_VALID_ADC_SAMP_MODE(MODE)  (((MODE) == ADC_SAMP_BY_NEG_EDGE) \
                                    || ((MODE) == ADC_SAMP_BY_POS_EDGE))

//=============================================================================
// ADC_CFG[7] ADC_CIC_EN Define
#define ADC_CIC_EN_SHIFT                   (7)
#define ADC_CIC_EN_MSK                     ((0x01 << 1) - 1)

typedef enum
{
    ADC_CIC_DISABLE = 0x00, /* ADC Data Transfer to SRAM Directly */
    ADC_CIC_ENABLE  = 0x01, /* ADC Data Transfer to DownSamp First */

} EN_ADC_CIC_EN_T;

#define IS_VALID_ADC_CIC_EN(EN) (((EN) == ADC_CIC_DISABLE) \
                              || ((EN) == ADC_CIC_ENABLE))

//=============================================================================
// ADC_CFG[6] ADC_DATA_FORMAT
#define ADC_DATA_FORMAT_SHIFT              (6)
#define ADC_DATA_FORMAT_MSK                ((0x01 << 1) - 1)

typedef enum
{
    ADC_DATA_FORMAT_COMPLEMENT = 0x00,
    ADC_DATA_FORMAT_ORIGINAL   = 0x01,

} EN_ADC_DATA_FORMAT_T;

#define IS_VALID_ADC_DATA_FORMAT(FORMAT) (((FORMAT) == ADC_DATA_FORMAT_COMPLEMENT) \
                                       || ((FORMAT) == ADC_DATA_FORMAT_ORIGINAL))

//=============================================================================
// ADC_CFG[4:0] ADC_CIC_DOWNSP_DGC, CIC down sample filter DGC (digital gain control) coefficient
#define ADC_CIC_DOWNSP_DGC_SHIFT           (0)
#define ADC_CIC_DOWNSP_DGC_MSK             ((0x01 << 5) - 1)

typedef enum
{
    EN_ADC_CIC_DGC_10BIT = 0x00,
    EN_ADC_CIC_DGC_11BIT = 0x1C,
    EN_ADC_CIC_DGC_12BIT = 0x14,
    EN_ADC_CIC_DGC_13BIT = 0x0C,
    EN_ADC_CIC_DGC_14BIT = 0x04,

} EN_ADC_DGC_VALUE_T;

#define IS_VALID_ADC_CIC_DGC_VALUE(VALUE) (((VALUE) == EN_ADC_CIC_DGC_10BIT) \
                                        || ((VALUE) == EN_ADC_CIC_DGC_11BIT) \
                                        || ((VALUE) == EN_ADC_CIC_DGC_12BIT) \
                                        || ((VALUE) == EN_ADC_CIC_DGC_13BIT) \
                                        || ((VALUE) == EN_ADC_CIC_DGC_14BIT))

#define ADC_CFG_SHIFT                      (0)
#define ADC_CFG_MSK                        ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x1C~0x24] ADC_INT_FLAG / ADC_INT_EN  / ADC_INT_CLR
//=====================================================================================================================
#define ADC_READ_FIFO_THR_FLAG_SHIFT       (14)
#define ADC_READ_FIFO_UNDER_FLOW_SHIFT     (13)
#define ADC_WRITE_FIFO_OVERFLOW_SHIFT      (12)
#define ADC_BUSY_BY_AUDIO_SHIFT            (11)
#define ADC_CH_READY_SHIFT                 (10)
#define ADC_TEMP_CH_SAMPLE_FIN_SHIFT       (9)
#define ADC_VBAT_CH_SAMPLE_FIN_SHIFT       (8)
#define ADC_CH7_CH_SAMPLE_FIN_SHIFT        (7)
#define ADC_CH6_CH_SAMPLE_FIN_SHIFT        (6)
#define ADC_CH5_CH_SAMPLE_FIN_SHIFT        (5)
#define ADC_CH4_CH_SAMPLE_FIN_SHIFT        (4)
#define ADC_CH3_CH_SAMPLE_FIN_SHIFT        (3)
#define ADC_CH2_CH_SAMPLE_FIN_SHIFT        (2)
#define ADC_CH1_CH_SAMPLE_FIN_SHIFT        (1)
#define ADC_CH0_CH_SAMPLE_FIN_SHIFT        (0)

#define ADC_INT_MASK                       (0x7FFF)

typedef enum
{
    ADC_READ_FIFO_THR_FLAG      = (0x01 << ADC_READ_FIFO_THR_FLAG_SHIFT),
    ADC_READ_FIFO_UNDER_FLOW    = (0x01 << ADC_READ_FIFO_UNDER_FLOW_SHIFT),
    ADC_WRITE_FIFO_OVERFLOW     = (0x01 << ADC_WRITE_FIFO_OVERFLOW_SHIFT),

    ADC_BUSY_BY_AUDIO           = (0x01 << ADC_BUSY_BY_AUDIO_SHIFT),
    ADC_CH_READY                = (0x01 << ADC_CH_READY_SHIFT),
    ADC_TEMP_CH_SAMPLE_FIN      = (0x01 << ADC_TEMP_CH_SAMPLE_FIN_SHIFT),
    ADC_VBAT_CH_SAMPLE_FIN      = (0x01 << ADC_VBAT_CH_SAMPLE_FIN_SHIFT),

    ADC_CH7_CH_SAMPLE_FIN       = (0x01 << ADC_CH7_CH_SAMPLE_FIN_SHIFT),
    ADC_CH6_CH_SAMPLE_FIN       = (0x01 << ADC_CH6_CH_SAMPLE_FIN_SHIFT),
    ADC_CH5_CH_SAMPLE_FIN       = (0x01 << ADC_CH5_CH_SAMPLE_FIN_SHIFT),
    ADC_CH4_CH_SAMPLE_FIN       = (0x01 << ADC_CH4_CH_SAMPLE_FIN_SHIFT),

    ADC_CH3_CH_SAMPLE_FIN       = (0x01 << ADC_CH3_CH_SAMPLE_FIN_SHIFT),
    ADC_CH2_CH_SAMPLE_FIN       = (0x01 << ADC_CH2_CH_SAMPLE_FIN_SHIFT),
    ADC_CH1_CH_SAMPLE_FIN       = (0x01 << ADC_CH1_CH_SAMPLE_FIN_SHIFT),
    ADC_CH0_CH_SAMPLE_FIN       = (0x01 << ADC_CH0_CH_SAMPLE_FIN_SHIFT),

} EN_ADC_INT_FLAG_T;


//=====================================================================================================================
// [0x2C](RW) ADC_SAMP_CFG
//=====================================================================================================================
//=============================================================================
// ADC_SAMP_CFG[8:6] ADC_PWM_SAMP_SRC_SEL
#define ADC_PWM_SAMP_SRC_SEL_SHIFT         (6)
#define ADC_PWM_SAMP_SRC_SEL_MSK           ((0x01 << 3) - 1)

typedef enum
{
    ADC_PWM_SAMP_SRC_PWM0_CHA = 0x00,
    ADC_PWM_SAMP_SRC_PWM0_CHB = 0x01,
    ADC_PWM_SAMP_SRC_PWM1_CHA = 0x02,
    ADC_PWM_SAMP_SRC_PWM1_CHB = 0x03,
    ADC_PWM_SAMP_SRC_PWM2_CHA = 0x04,
    ADC_PWM_SAMP_SRC_PWM2_CHB = 0x05,
    ADC_PWM_SAMP_SRC_PWM3_CHA = 0x06,
    ADC_PWM_SAMP_SRC_PWM3_CHB = 0x07,

} EN_ADC_PWM_SAMP_SRC_SEL_T;

#define IS_VALID_ADC_ADC_PWM_SAMP_SRC_SEL(SEL) ((SEL) <= ADC_PWM_SAMP_SRC_SEL_MSK)

//=============================================================================
// ADC_SAMP_CFG[5:4] ADC_SAMP_MODE_SEL
#define ADC_SAMP_MODE_SEL_SHIFT            (4)
#define ADC_SAMP_MODE_SEL_MSK              ((0x01 << 2) - 1)

typedef enum
{
    ADC_SAMP_BY_SW_TRIG       = 0x00,
    ADC_SAMP_BY_GPIO_PWM_TRIG = 0x01,
    ADC_SAMP_BY_AUTO_TRIG     = 0x02,

} EN_ADC_SAMP_MODE_SEL_T;

#define IS_VALID_ADC_SAMP_MODE_SEL(SEL) ((SEL) <= ADC_SAMP_BY_AUTO_TRIG)

//=============================================================================
// ADC_SAMP_CFG[3:0] ADC_SAMP_SRC_SEL
#define ADC_SAMP_SRC_SEL_SHIFT             (0)
#define ADC_SAMP_SRC_SEL_MSK               ((0x01 << 4) - 1)

typedef enum
{
    ADC_SAMP_BY_GPIO_RISING_EDGE  = 0x00, /* __--*/
    ADC_SAMP_BY_GPIO_FALLING_EDGE = 0x01, /* --__*/
    ADC_SAMP_BY_PWM_RISING_EDGE   = 0x02, /* __--*/
    ADC_SAMP_BY_PWM_FALLING_EDGE  = 0x03, /* --__*/
    ADC_SAMP_BY_GPIO_BOTH_EDGE    = 0x04,
    ADC_SAMP_BY_PWM_BOTH_EDGE     = 0x06,
    ADC_SAMP_BY_GPIO_HIGH_LEVEL   = 0x08,
    ADC_SAMP_BY_GPIO_LOW_LEVEL    = 0x09,
    ADC_SAMP_BY_PWM_HIGH_LEVEL    = 0x0A,
    ADC_SAMP_BY_PWM_LOW_LEVEL     = 0x0B,

} EN_ADC_SAMP_SRC_SEL_T;

#define IS_VALID_ADC_SAMP_SRC_SEL(SEL) ((SEL) <= ADC_SAMP_SRC_SEL_MSK)


//=====================================================================================================================
// [0x30](RW) GPADC_EN
//=====================================================================================================================
//=============================================================================
// GPADC_EN[0] ADC_EN Define
#define ADC_ENABLE_SHIFT                   (0)
#define ADC_ENABLE_MSK                     ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x54](RW) GPADC_DEBUG_DATA
//=====================================================================================================================
//=============================================================================
// GPADC_DEBUG_DATA[10] ADC_DEBUG_DATA_EN
#define ADC_DEBUG_DATA_EN_SHIFT            (10)
#define ADC_DEBUG_DATA_EN_MSK              ((0x01 << 1) - 1)

//=============================================================================
// GPADC_DEBUG_DATA[9:0] ADC_DEBUG_DATA_VALUE
#define ADC_DEBUG_DATA_VALUE_SHIFT         (0)
#define ADC_DEBUG_DATA_VALUE_MSK           ((0x01 << 10) - 1)


//=====================================================================================================================
// [0x58](RW) ADC_ENABLE
//=====================================================================================================================
//=============================================================================
// ADC_ENABLE[9:0] ADC_ENABLE Define
#define ADC_CH_ENABLE_SHIFT                (0)
#define ADC_CH_ENABLE_MSK                  ((0x01 << 10) - 1)

typedef enum
{
    ADC_CH_0    = (0x01 << 0),
    ADC_CH_1    = (0x01 << 1),
    ADC_CH_2    = (0x01 << 2),
    ADC_CH_3    = (0x01 << 3),
    ADC_CH_4    = (0x01 << 4),
    ADC_CH_5    = (0x01 << 5),
    ADC_CH_6    = (0x01 << 6),
    ADC_CH_7    = (0x01 << 7),
    ADC_CH_VDDR = (0x01 << 8),
    ADC_CH_TEMP = (0x01 << 9)

} EN_ADC_CH_T;

#define IS_VALID_ADC_CH(CH) ((CH) <= ADC_CH_ENABLE_MSK)
#define ADC_CH_IO_MSK       (0xFF)

//=====================================================================================================================
// [0x5C](RW) ADC_STABLE_TIME
//=====================================================================================================================
//=============================================================================
// ADC_STABLE_TIME[11:0] ADC_STABLE_TIME Define
#define ADC_STABLE_TIME_SHIFT              (0)
#define ADC_STABLE_TIME_MSK                ((0x01 << 12) - 1)
#define ADC_STABLE_TIME_US_MSK             (0x01 << 8)
#define ADC_STABLE_TIME_DEFAULT            (0x140)

#define IS_VALID_ADC_STABLE_TIME(VAL)      ((VAL) <= ADC_STABLE_TIME_US_MSK)


//=====================================================================================================================
// [0x60](RW) ADC_SAMP_NUM
//=====================================================================================================================
//=============================================================================
// ADC_SAMP_NUM[15:0] ADC_SAMP_NUM Define
#define ADC_SAMP_NUM_SHIFT                 (0)
#define ADC_SAMP_NUM_MSK                   ((0x01 << 16) - 1)
#define ADC_SAMP_NUM_MAX                   ((0x01 << 15) - 1) /* trig once ,Adc sample two*/

#define IS_VALID_ADC_SAMP_NUM(NUM)         ((NUM) <= ADC_SAMP_NUM_MAX)


//=====================================================================================================================
// [0x64](WO) ADC_TRIG
//=====================================================================================================================
//=============================================================================
// ADC_TRIG[3] ADC_SAMPLE_CNT_CLR Define
#define ADC_SAMPLE_CNT_CLR_SHIFT           (3)
#define ADC_SAMPLE_CNT_CLR_MSK             ((0x01 << 1) - 1)

//=============================================================================
// ADC_TRIG[2] ADC_TRIG_STOP Define
#define ADC_TRIG_STOP_SHIFT                (2)
#define ADC_TRIG_STOP_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// ADC_TRIG[1] ADC_SMAP_TRIG_START
#define ADC_SMAP_TRIG_START_SHIFT          (1)
#define ADC_SMAP_TRIG_START_MSK            ((0x01 << 1) - 1)

//=============================================================================
// ADC_TRIG[0] ADC_TRIG_START Define
#define ADC_TRIG_START_SHIFT               (0)
#define ADC_TRIG_START_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x68](RO) ADC_STATUS
//=====================================================================================================================
//=============================================================================
// ADC_STATUS[31:16] ADC_RAW_DATA
#define ADC_RAW_DATA_SHIFT                 (16)
#define ADC_RAW_DATA_MSK                   ((0x01 << 16) - 1)

//=============================================================================
//ADC_STATUS[15:0] ADC_SAMPL_CNT
#define ADC_SAMPL_CNT_SHIFT                (0)
#define ADC_SAMPL_CNT_MSK                  ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x6C](RO) ADC_CFG_STATUS
//=====================================================================================================================
//=============================================================================
// ADC_CFG_STATUS[21:18] ADC_FIFO_CNT
#define ADC_FIFO_CNT_SHIFT                 (18)
#define ADC_FIFO_CNT_MSK                   ((0x01 << 4) - 1)

//=============================================================================
// ADC_CFG_STATUS[17:15] ADC_FSM_STATUS
#define ADC_FSM_STATUS_SHIFT               (15)
#define ADC_FSM_STATUS_MSK                 ((0x01 << 3) - 1)

//=============================================================================
// ADC_CFG_STATUS[14] ADC_R_EN_STATUS
#define ADC_R_EN_STATUS_SHIFT              (14)
#define ADC_R_EN_STATUS_MSK                ((0x01 << 1) - 1)

//=============================================================================
// ADC_CFG_STATUS[13:10] ADC_R_BUF_GAIN_VALUE
#define ADC_R_BUF_GAIN_VALUE_SHIFT         (10)
#define ADC_R_BUF_GAIN_VALUE_MSK           ((0x01 << 4) - 1)

//=============================================================================
// ADC_CFG_STATUS[9:0] ADC_CH_SEL_STATUS
#define ADC_CH_SEL_STATUS_SHIFT            (0)
#define ADC_CH_SEL_STATUS_MSK              ((0x01 << 10) - 1)


#ifdef __cplusplus
}
#endif

#endif /* __REG_ADC_H__ */


