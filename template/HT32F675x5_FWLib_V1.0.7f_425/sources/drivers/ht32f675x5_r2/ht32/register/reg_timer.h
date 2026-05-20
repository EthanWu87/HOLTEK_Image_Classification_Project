/*************************************************************************************************************
 * @file    reg_timer.h
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


#ifndef __REG_TIMER_H__
#define __REG_TIMER_H__


#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum
{
    TIMER_CHA   = 0x02, /* 16-bit TimerA */
    TIMER_CHB   = 0x01, /* 16-bit TimerB */
    TIMER_CHAB  = 0x07, /* 32-bit Timer */

} EN_TIMER_CH_T;

#define IS_VALID_TIMER_CH(CH) ((CH) == TIMER_CHA   || \
                               (CH) == TIMER_CHB   || \
                               (CH) == TIMER_CHAB)

typedef enum
{
    IR_CHB    = 0x01, /* 16bit TimerB IR */
    IR_CHA    = 0x02, /* 16bit TimerA IR */
    IR_CHAB   = 0x07, /* 32bit Timer IR */
    
} EN_IR_CH_T;

#define IS_VALID_IR_CH(CH) ((CH) == IR_CHB   || \
                            (CH) == IR_CHA   || \
                            (CH) == IR_CHAB)

typedef enum
{
    TIMER_CLK_DIV1   = 0,
    TIMER_CLK_DIV2   = 1,
    TIMER_CLK_DIV4   = 3,
    TIMER_CLK_DIV8   = 7,
    TIMER_CLK_DIV16  = 15,

} EN_TIMER_CLK_T;


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __OM  uint32_t TIMER_CFG_EN;           /* [0x00](WO) */
    __IM  uint32_t TIMER_CFG_FLAG;         /* [0x04](RO) */
    __OM  uint32_t TIMER_CFG_CLR;          /* [0x08](WO) */
    __IOM uint32_t TIMER_MODE;             /* [0x0C](RW) */
    __IOM uint32_t TIMER_CFG;              /* [0x10](RW) */
    __OM  uint32_t TIMER_TRIG;             /* [0x14](WO) */
    __IM  uint32_t TIMER_CNT;              /* [0x18](RO) */
    __IOM uint32_t TIMER_COMPARE;          /* [0x1C](RW) */
    __IM  uint32_t TIMER_CHAB_CAP_CNT;     /* [0x20](RO) */
    __IM  uint32_t TIMER_CHA_CAP_CNT;      /* [0x24](RO) */
    __IM  uint32_t TIMER_CHB_CAP_CNT;      /* [0x28](RO) */
    __IOM uint32_t TIMER_DECODE_INTVAL;    /* [0x2C](RW) */
    __IOM uint32_t TIMER_PWM_CNT_LO;       /* [0x30](RW) */
    __IOM uint32_t TIMER_PWM_CNT_HI;       /* [0x34](RW) */
    __IM  uint32_t TIMER_CHB_INT_FLAG;     /* [0x38](RO) */
    __OM  uint32_t TIMER_CHB_INT_CLR;      /* [0x3c](WO) */
    __IOM uint32_t TIMER_CHB_INT_EN;       /* [0x40](RW) */
    __IM  uint32_t TIMER_CHA_INT_FLAG;     /* [0x44](RO) */
    __OM  uint32_t TIMER_CHA_INT_CLR;      /* [0x48](WO) */
    __IOM uint32_t TIMER_CHA_INT_EN;       /* [0x4C](RW) */
    __IOM uint32_t TIMER_CHA_CTRL;         /* [0x50](RW) */
    __IOM uint32_t TIMER_CHB_CTRL;         /* [0x54](RW) */
    __IM  uint32_t TIMER_CHA_WORK_FLAG;    /* [0x58](RO) */
    __IM  uint32_t TIMER_CHB_WORK_FLAG;    /* [0x5C](RO) */
    __IM  uint32_t TIMER_WAKEUP_FLAG;      /* [0x60](RO) */
          uint32_t RESERVED[8];            /* [0x64~0x80] */

    __IOM uint32_t TIMER_EXT_CG_EN;        /* [0x84](RW) */

} stTIMER_Handle_t, *pstTIMER_Handle_t;


#define IS_VALID_TIMER_HANDLE(pstTIMER)  ((TIMER0) == (pstTIMER) \
                                       || (TIMER1) == (pstTIMER) \
                                       || (TIMER2) == (pstTIMER) \
                                       || (TIMER3) == (pstTIMER))

#define IS_VALID_IR_HANDLE(pstIR)        ((IR0) == (pstIR) \
                                       || (IR1) == (pstIR) \
                                       || (IR2) == (pstIR) \
                                       || (IR3) == (pstIR))


//=====================================================================================================================
// [0x00](WO) TIMER_CFG_EN
//=====================================================================================================================
//=============================================================================
// TIMER_CFG_EN[1:0] TIMER_CFG_EN Define
#define TIMER_CFG_EN_SHIFT                 (0)
#define TIMER_CFG_EN_MSK                   ((0x01 << 2) - 1)


//=====================================================================================================================
// [0x04](RO) TIMER_CFG_FLAG
//=====================================================================================================================
//=============================================================================
// TIMER_CFG_FLAG[1:0] TIMER_CFG_FLAG Define
#define TIMER_CFG_FLAG_SHIFT               (0)
#define TIMER_CFG_FLAG_MSK                 ((0x01 << 2) - 1)


//=====================================================================================================================
// [0x08](WO) TIMER_CFG_CLR
//=====================================================================================================================
//=============================================================================
// TIMER_CFG_CLR[1:0] TIMER_CFG_CLR Define
#define TIMER_CFG_CLR_SHIFT                (0)
#define TIMER_CFG_CLR_MSK                  ((0x01 << 2) - 1)


//=====================================================================================================================
// [0x0C](RW) TIMER_MODE
//=====================================================================================================================
//=============================================================================
// TIMER_MODE[7:6] IR_SEND_PATH Define
#define IR_SEND_PATH_SHIFT                 (6)
#define IR_SEND_PATH_MSK                   ((0x01 << 2) - 1)

typedef enum
{
    IR_SEND_DEFAULT_PATH = 0,
    IR_SEND_BY_IR_TX_PIN = 1,
    IR_SEND_BY_GPIO      = 2,
    IR_SEND_BY_BOTH      = 3,

} EN_IR_SEND_PATH_T;

#define IS_VALID_IR_SEND_PATH(PATH)   (IR_SEND_BY_BOTH >= (PATH))

//=============================================================================
// TIMER_MODE[5] TIMER_CAP_CHB_SRC Define
#define TIMER_CAP_CHB_SRC_SHIFT            (5)
#define TIMER_CAP_CHB_SRC_MSK              ((0x01 << 1) - 1)

typedef enum
{
    TIMER_CAP_CHB_SRC_GPIO_IR = 0,
    TIMER_CAP_CHB_SRC_DECODE  = 1,

} EN_CAP_CHB_SRC_T;

#define IS_VALID_CAP_CHB_SRC(SRC)   (TIMER_CAP_CHB_SRC_DECODE >= (SRC))

//=============================================================================
// TIMER_MODE[4] IR_EN Define
#define IR_EN_SHIFT                        (4)
#define IR_EN_MSK                          ((0x01 << 1) - 1)

//=============================================================================
// TIMER_MODE[3] IR_POL Define
#define IR_POL_SHIFT                       (3)
#define IR_POL_MSK                         ((0x01 << 1) - 1)

typedef enum
{
    IR_POL_FALLING = 0,     /* High to low: ---____ */
    IR_POL_RISING  = 1,     /* Low to high: ____--- */

} EN_IR_POL_T;

#define IS_VALID_IR_POL(POL)   (((POL) == IR_POL_RISING) || \
                                ((POL) == IR_POL_FALLING))

//=============================================================================
// TIMER_MODE[2:0] TIMER_MODE Define
#define TIMER_MODE_SHIFT                   (0)
#define TIMER_MODE_MSK                     ((0x01 << 3) - 1)


//=====================================================================================================================
// [0x10](RW) TIMER_CFG
//=====================================================================================================================
//=============================================================================
// TIMER_CFG[31] PWM_CHA_EN Define
#define PWM_CHA_EN_SHIFT                   (31)
#define PWM_CHA_EN_MSK                     ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CFG[30] PWM_CHA_POL Define
#define PWM_CHA_POL_SHIFT                  (30)
#define PWM_CHA_POL_MSK                    ((0x01 << 1) - 1)

typedef enum
{
    PWM_POL_RISING  = 0,    /* Low to high: ____--- */
    PWM_POL_FALLING = 1,    /* High to low: ---____ */

} EN_PWM_POL_T;

#define IS_VALID_PWM_POLARITY(POL)   (((POL) == PWM_POL_RISING) || \
                                      ((POL) == PWM_POL_FALLING))

//=============================================================================
// TIMER_CFG[29] DECODE_CHA_EN Define
#define DECODE_CHA_EN_SHIFT                (29)
#define DECODE_CHA_EN_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CFG[28] DECODE_CHA_POL Define
#define DECODE_CHA_POL_SHIFT               (28)
#define DECODE_CHA_POL_MSK                 ((0x01 << 1) - 1)

typedef enum
{
    DECODE_POL_IDEL_LOW_LEVEL   = 0x00,
    DECODE_POL_IDEL_HIGH_LEVEL  = 0x01,

} EN_DECODE_POL_T;

#define IS_VALID_DECODE_POL(POL)   (DECODE_POL_IDEL_HIGH_LEVEL >= (POL))

//=============================================================================
// TIMER_CFG[27:26] DECODE_CHA_MODE Define
#define DECODE_CHA_MODE_SHIFT              (26)
#define DECODE_CHA_MODE_MSK                ((0x01 << 2) - 1)

typedef enum
{
    DECODE_MODE_POS_EDGE  = 1,  /* __-- */
    DECODE_MODE_NEG_EDGE  = 2,  /* --__ */
    DECODE_MODE_BOTH_EDGE = 3,  /* __-- & --__ */

} EN_DECODE_MODE_T;

#define IS_VALID_DECODE_MODE(MODE)   (DECODE_MODE_BOTH_EDGE >= (MODE))

//=============================================================================
// TIMER_CFG[25] CAP_CHA_EN Define
#define CAP_CHA_EN_SHIFT                   (25)
#define CAP_CHA_EN_MSK                     ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CFG[24] CAP_CHA_SIGNAL_SEL Define
#define CAP_CHA_SIGNAL_SEL_SHIFT           (24)
#define CAP_CHA_SIGNAL_SEL_MSK             ((0x01 << 1) - 1)

typedef enum
{
    CAP_DECODE_SIGNAL_GPIO  = 0x00,
    CAP_DECODE_SIGNAL_IR    = 0x01,

} EN_CAP_DECODE_SIGNAL_T;

#define IS_VALID_CAP_DECODE_SIGNAL(SIGNAL) (CAP_DECODE_SIGNAL_GPIO == (SIGNAL) \
                                         || CAP_DECODE_SIGNAL_IR)

//=============================================================================
// TIMER_CFG[23:22] CAP_CHA_MODE Define
#define CAP_CHA_MODE_SHIFT                 (22)
#define CAP_CHA_MODE_MSK                   ((0x01 << 2) - 1)

typedef enum
{
    CAP_MODE_POS_EDGE  = 0x01, /* __-- */
    CAP_MODE_NEG_EDGE  = 0x02, /* --__ */
    CAP_MODE_BOTH_EDGE = 0x03, /* __-- & --__ */

} EN_CAP_MODE_T;

#define IS_VALID_CAP_MODE(MODE) (CAP_MODE_POS_EDGE == (MODE) \
                              || CAP_MODE_NEG_EDGE == (MODE) \
                              || CAP_MODE_BOTH_EDGE == (MODE))

//=============================================================================
// TIMER_CFG[21:18] TIMER_CHA_PRESCALE Define
#define TIMER_CHA_PRESCALE_SHIFT           (18)
#define TIMER_CHA_PRESCALE_MSK             ((0x01 << 4) - 1)

//=============================================================================
// TIMER_CFG[17:16] TIMER_CHA_CNT_MODE Define
#define TIMER_CHA_CNT_MODE_SHIFT           (16)
#define TIMER_CHA_CNT_MODE_MSK             ((0x01 << 2) - 1)

typedef enum
{
    TIMER_CNT_MODE_CONTINU         = 0x00, /* The timer repeatedly counts from zero to 0xFFFF(or 0xFFFFFFFF) */
    TIMER_CNT_MODE_UP              = 0x01, /* The timer repeatedly counts from zero to the value of compare */
    TIMER_CNT_MODE_CONTINU_UP_DOWN = 0x02, /* The timer repeatedly counts from zero up to 0xFFFF(or 0xFFFFFFFF)
                                              and back down to zero. */
    TIMER_CNT_MODE_UP_DOWN         = 0x03, /* The timer repeatedly counts from zero up to the value of compare
                                              and back down to zero. */

} EN_TIMER_CNT_MODE_T;

#define IS_VALID_TIMER_CNT_MODE(MODE)    (TIMER_CNT_MODE_CONTINU         == (MODE)\
                                       || TIMER_CNT_MODE_UP              == (MODE)\
                                       || TIMER_CNT_MODE_CONTINU_UP_DOWN == (MODE)\
                                       || TIMER_CNT_MODE_UP_DOWN         == (MODE))

//=============================================================================
// TIMER_CFG[15] PWM_CHB_EN Define
#define PWM_CHB_EN_SHIFT                   (15)
#define PWM_CHB_EN_MSK                     ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CFG[14] PWM_CHB_POL Define
#define PWM_CHB_POL_SHIFT                  (14)
#define PWM_CHB_POL_MSK                    ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CFG[13] DECODE_CHB_EN Define
#define DECODE_CHB_EN_SHIFT                (13)
#define DECODE_CHB_EN_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CFG[12] DECODE_CHB_POL Define
#define DECODE_CHB_POL_SHIFT               (12)
#define DECODE_CHB_POL_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CFG[11:10] DECODE_CHA_MODE Define
#define DECODE_CHB_MODE_SHIFT              (10)
#define DECODE_CHB_MODE_MSK                ((0x01 << 2) - 1)

//=============================================================================
// TIMER_CFG[9] CAP_CHB_EN Define
#define CAP_CHB_EN_SHIFT                   (9)
#define CAP_CHB_EN_MSK                     ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CFG[8] CAP_CHB_SIGNAL_SEL Define
#define CAP_CHB_SIGNAL_SEL_SHIFT           (8)
#define CAP_CHB_SIGNAL_SEL_MSK             ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CFG[7:6] CAP_CHB_MODE Define
#define CAP_CHB_MODE_SHIFT                 (6)
#define CAP_CHB_MODE_MSK                   ((0x01 << 2) - 1)

//=============================================================================
// TIMER_CFG[5:2] TIMER_CHB_PRESCALE Define
#define TIMER_CHB_PRESCALE_SHIFT           (2)
#define TIMER_CHB_PRESCALE_MSK             ((0x01 << 4) - 1)

//=============================================================================
// TIMER_CFG[1:0] TIMER_CHB_CNT_MODE Define
#define TIMER_CHB_CNT_MODE_SHIFT           (0)
#define TIMER_CHB_CNT_MODE_MSK             ((0x01 << 2) - 1)


//=====================================================================================================================
// [0x14](WO) TIMER_TRIG
//=====================================================================================================================
//=============================================================================
// TIMER_TRIG[6] TIMER_CHA_CLR Define
#define TIMER_CHA_CLR_SHIFT                (6)
#define TIMER_CHA_CLR_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// TIMER_TRIG[5] TIMER_CHA_STOP Define
#define TIMER_CHA_STOP_SHIFT               (5)
#define TIMER_CHA_STOP_MSK                 ((0x01 << 1) - 1)

// TIMER_TRIG[4] TIMER_CHA_START Define
#define TIMER_CHA_START_SHIFT              (4)
#define TIMER_CHA_START_MSK                ((0x01 << 1) - 1)

//=============================================================================
// TIMER_TRIG[2] TIMER_CHB_CLR Define
#define TIMER_CHB_CLR_SHIFT                (2)
#define TIMER_CHB_CLR_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// TIMER_TRIG[1] TIMER_CHB_STOP Define
#define TIMER_CHB_STOP_SHIFT               (1)
#define TIMER_CHB_STOP_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// TIMER_TRIG[0] TIMER_CHB_START Define
#define TIMER_CHB_START_SHIFT              (0)
#define TIMER_CHB_START_MSK                ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x18](RO) TIMER_CNT
//=====================================================================================================================
//=============================================================================
// TIMER_CNT[31:16] TIMER_CHA_CNT Define
#define TIMER_CHA_CNT_SHIFT                (16)
#define TIMER_CHA_CNT_MSK                  ((0x01 << 16) - 1)

//=============================================================================
// TIMER_CNT[15:0] TIMER_CHB_CNT Define
#define TIMER_CHB_CNT_SHIFT                (0)
#define TIMER_CHB_CNT_MSK                  ((0x01 << 16) - 1)

#define TIMER_CNT_MSK                      (WORD_MSK)


//=====================================================================================================================
// [0x1C](RW) TIMER_COMPARE
//=====================================================================================================================
//=============================================================================
// TIMER_COMPARE[31:16] TIMER_CHA_COMPARE Define
#define TIMER_CHA_COMPARE_SHIFT            (16)
#define TIMER_CHA_COMPARE_MSK              ((0x01 << 16) - 1)

//=============================================================================
// TIMER_COMPARE[15:0] TIMER_CHB_COMPARE Define
#define TIMER_CHB_COMPARE_SHIFT            (0)
#define TIMER_CHB_COMPARE_MSK              ((0x01 << 16) - 1)

//=============================================================================
// TIMER_COMPARE[31:0] TIMER_CHAB_COMPARE Define
#define TIMER_COMPARE_SHIFT                (0)
#define TIMER_COMPARE_MSK                  (WORD_MSK)


//=====================================================================================================================
// [0x20](RO) TIMER_CHAB_CAP_CNT
//=====================================================================================================================
//=============================================================================
// TIMER_CHAB_CAP_CNT[31:0] TIMER_CHAB_CAP_CNT Define
#define TIMER_CHAB_CAP_CNT_SHIFT           (0)
#define TIMER_CHAB_CAP_CNT_MSK             (WORD_MSK)


//=====================================================================================================================
// [0x24](RO) TIMER_CHA_CAP_CNT
//=====================================================================================================================
//=============================================================================
// TIMER_CHA_CAP_CNT[15:0] TIMER_CHA_CAP_CNT Define
#define TIMER_CHA_CAP_CNT_SHIFT            (0)
#define TIMER_CHA_CAP_CNT_MSK              ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x28](RO) TIMER_CHB_CAP_CNT
//=====================================================================================================================
//=============================================================================
// TIMER_CHB_CAP_CNT[15:0] TIMER_CHB_CAP_CNT Define
#define TIMER_CHB_CAP_CNT_SHIFT            (0)
#define TIMER_CHB_CAP_CNT_MSK              ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x2C](RW) TIMER_DECODE_INTVAL
//=====================================================================================================================
//=============================================================================
// TIMER_DECODE_INTVAL[15:8] DECODE_CHA_INTVAL Define
#define DECODE_CHA_INTVAL_SHIFT            (8)
#define DECODE_CHA_INTVAL_MSK              ((0x01 << 8) - 1)

//=============================================================================
// TIMER_DECODE_INTVAL[7:0] DECODE_CHB_INTVAL Define
#define DECODE_CHB_INTVAL_SHIFT            (0)
#define DECODE_CHB_INTVAL_MSK              ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x30](RW) TIMER_PWM_CNT_LO
//=====================================================================================================================
//=============================================================================
// TIMER_PWM_CNT_LO[31:16] PWM_CHA_CNT_LO Define
#define PWM_CHA_CNT_LO_SHIFT               (16)
#define PWM_CHA_CNT_LO_MSK                 ((0x01 << 16) - 1)

//=============================================================================
// TIMER_PWM_CNT_LO[15:0] PWM_CHB_CNT_LO Define
#define PWM_CHB_CNT_LO_SHIFT               (0)
#define PWM_CHB_CNT_LO_MSK                 ((0x01 << 16) - 1)

//=============================================================================
// TIMER_PWM_CNT_LO[31:0] PWM_CHAB_CNT_LO Define
#define PWM_CHAB_CNT_LO_SHIFT              (0)
#define PWM_CHAB_CNT_LO_MSK                (WORD_MSK)


//=====================================================================================================================
// [0x34](RW) TIMER_PWM_CNT_HI
//=====================================================================================================================
//=============================================================================
// TIMER_PWM_CNT_HI[31:16] PWM_CHA_CNT_HI Define
#define PWM_CHA_CNT_HI_SHIFT               (16)
#define PWM_CHA_CNT_HI_MSK                 ((0x01 << 16) - 1)

//=============================================================================
// TIMER_PWM_CNT_HI[15:0] PWM_CHB_CNT_HI Define
#define PWM_CHB_CNT_HI_SHIFT               (0)
#define PWM_CHB_CNT_HI_MSK                 ((0x01 << 16) - 1)

//=============================================================================
// TIMER_PWM_CNT_HI[31:0] PWM_CHAB_CNT_HI Define
#define PWM_CHAB_CNT_HI_SHIFT              (0)
#define PWM_CHAB_CNT_HI_MSK                (WORD_MSK)


//=====================================================================================================================
// [0x38~0x4C] TIMER_INT_FLAG / TIMER_INT_EN  / TIMER_INT_CLR
//=====================================================================================================================
#define TIMER_INT_CAPTURE_SHIFT            (4)
#define TIMER_INT_DECODE_SHIFT             (3)
#define TIMER_INT_CAP_COV_SHIFT            (2)
#define TIMER_INT_OVERFLOW_SHIFT           (1)
#define TIMER_INT_MATCH_SHIFT              (0)

typedef enum
{
    TIMER_INT_MATCH       = (0x01 << TIMER_INT_MATCH_SHIFT),
    TIMER_INT_OVERFLOW    = (0x01 << TIMER_INT_OVERFLOW_SHIFT),
    TIMER_INT_CAP_COV     = (0x01 << TIMER_INT_CAP_COV_SHIFT),
    TIMER_INT_DECODE      = (0x01 << TIMER_INT_DECODE_SHIFT),
    TIMER_INT_CAPTURE     = (0x01 << TIMER_INT_CAPTURE_SHIFT),

} EN_TIMER_INT_FLAG_T;

#define TIMER_INT_MASK      (0x1F)


//=====================================================================================================================
// [0x40/0x4C](RW) TIMER_INT_EN
//=====================================================================================================================
#define TIMER_WAKEUP_CAPTURE_SHIFT         (9)
#define TIMER_WAKEUP_DECODE_SHIFT          (8)
#define TIMER_WAKEUP_CAP_COV_SHIFT         (7)
#define TIMER_WAKEUP_OVERFLOW_SHIFT        (6)
#define TIMER_WAKEUP_MATCH_SHIFT           (5)

typedef enum
{
    TIMER_WAKEUP_MATCH       = (0x01 << TIMER_WAKEUP_MATCH_SHIFT),
    TIMER_WAKEUP_OVERFLOW    = (0x01 << TIMER_WAKEUP_OVERFLOW_SHIFT),
    TIMER_WAKEUP_CAP_COV     = (0x01 << TIMER_WAKEUP_CAP_COV_SHIFT),
    TIMER_WAKEUP_DECODE      = (0x01 << TIMER_WAKEUP_DECODE_SHIFT),
    TIMER_WAKEUP_CAPTURE     = (0x01 << TIMER_WAKEUP_CAPTURE_SHIFT)

} EN_TIMER_WAKEUP_SRC_T;

#define TIMER_WAKEUP_MASK    (0x3E0)


//=====================================================================================================================
// [0x50~0x54](RW) TIMER_CTRL
//=====================================================================================================================
//=============================================================================
// TIMER_CTRL[4] TIMR_CAP_TRIGGER_MODE Define
#define TIMR_CAP_TRIGGER_MODE_SHIFT        (4)
#define TIMR_CAP_TRIGGER_MODE_MSK          ((0x01 << 1) - 1)

typedef enum
{
    CAP_TRIG_MODE_DMA = 0x00,
    CAP_TRIG_MODE_INT = 0x01,

} EN_CAP_TRIG_MODE_T;

#define IS_VALID_CAP_TRIG_MODE(MODE)   (CAP_TRIG_MODE_INT >= (MODE))

//=============================================================================
// TIMER_CTRL[3] TIMR_SYNC_START Define
#define TIMR_SYNC_START_SHIFT              (3)
#define TIMR_SYNC_START_MSK                ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CTRL[2] TIMR_SYNC_STOP Define
#define TIMR_SYNC_STOP_SHIFT               (2)
#define TIMR_SYNC_STOP_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// TIMER_CTRL[1] TIMR_CAP_CNT_FORMAT Define
#define TIMR_CAP_CNT_FORMAT_SHIFT          (1)
#define TIMR_CAP_CNT_FORMAT_MSK            ((0x01 << 1) - 1)

typedef enum
{
    CAP_CNT_FORMAT_UNSIGNED = 0,
    CAP_CNT_FORMAT_SIGNED   = 1,

} EN_CAP_CNT_FORMAT_T;

#define IS_VALID_CAP_CNT_FORMAT(FORMAT)   (CAP_CNT_FORMAT_SIGNED >= (FORMAT))

//=============================================================================
// TIMER_CTRL[0] TIMER_COMPARE_VALID_DELAY Define
#define TIMER_COMPARE_VALID_DELAY_SHIFT    (0)
#define TIMER_COMPARE_VALID_DELAY_MSK      ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x58~0x5C](RO) TIMER_WORK_FLAG
//=====================================================================================================================
//=============================================================================
// TIMER_WORK_FLAG[1] TIMER_WORK_STATUS
#define TIMER_WORK_STATUS_SHIFT            (1)
#define TIMER_WORK_STATUS_MSK              ((0x01 << 1) - 1)

typedef enum
{
    TIMER_STATUS_STOP    = 0,
    TIMER_STATUS_RUNNING = 1,

} EN_TIMER_STATUS_T;

//=============================================================================
// TIMER_WORK_FLAG[0] TIMER_COUNTER_MODE Define
#define TIMER_COUNTER_MODE_SHIFT           (0)
#define TIMER_COUNTER_MODE_MSK             ((0x01 << 1) - 1)

typedef enum
{
    TIMER_COUNTER_MODE_DECREASE = 0,
    TIMER_COUNTER_MODE_INCREASE = 1,

} EN_TIMER_COUNTER_MODE_T;


//=====================================================================================================================
// [0x60](RO) TIMER_WAKEUP_FLAG
//=====================================================================================================================
//=============================================================================
// TIMER_WAKEUP_FLAG[1] TIMER_WAKEUP_FLAG
#define TIMER_WAKEUP_FLAG_SHIFT            (0)
#define TIMER_WAKEUP_FLAG_MSK              ((0x01 << 1) - 1)


#ifdef __cplusplus
}
#endif

#endif /* __REG_TIMER_H__ */

