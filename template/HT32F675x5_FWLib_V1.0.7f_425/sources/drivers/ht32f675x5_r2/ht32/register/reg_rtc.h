/*************************************************************************************************************
 * @file    reg_rtc.h
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


#ifndef __REG_RTC_H__
#define __REG_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum
{
    RTC_CH0 = 0,
    RTC_CH1 = 1,
    RTC_CH2 = 2,
    RTC_CH3 = 3,

} EN_RTC_CH_T;

#define RTC_CH_MAX            (4)
#define IS_VALID_RTC_CH(CH)   ((CH) < RTC_CH_MAX)


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IOM uint32_t HI;                            /* [0x18](RW) */
    __IOM uint32_t LO;                            /* [0x1C](RW) */

} ST_RTC_COMPARE_T;

typedef struct
{
    __IM  uint32_t RTC_INT_FLAG;                  /* [0x00](RO) */
    __IOM uint32_t RTC_INT_EN;                    /* [0x04](RW) */
    __OM  uint32_t RTC_INT_CLR;                   /* [0x08](WO) */
    __IOM uint32_t RTC_INT_EN1;                   /* [0x0C](RW) */
    __OM  uint32_t RTC_CNT_READ;                  /* [0x10](WO) */
          uint32_t RESERVED1;                     /* [0x14] */

    ST_RTC_COMPARE_T ST_RTC_COMPARE[RTC_CH_MAX];  /* [0x18~0x34](RW) */
    __OM  uint32_t RTC_LOAD_TRIG;                 /* [0x38](WO) */
    __IM  uint32_t RTC_TRIG_FLAG;                 /* [0x3C](RO) */
    __OM  uint32_t RTC_CLR_FLAG;                  /* [0x40](WO) */
    __IM  uint32_t RTC_CNT_HI;                    /* [0x44](RO) */
    __IM  uint32_t RTC_CNT_LO;                    /* [0x48](RO) */
    __IM  uint32_t RTC_WORK_STATUS;               /* [0x4C](RO) */
    __IM  uint32_t RTC_WAKEUP_STATUS;             /* [0x50](RO) */
          uint32_t RESERVED2[8];                  /* [0x54~0x70] */

    __IOM uint32_t RTC_EXT_CG_EN;                 /* [0x74](RW) */

} stRTC_Handle_t, *pstRTC_Handle_t;



//=====================================================================================================================
// [0x04](RW) RTC_INT_EN
//=============================================================================
#define RTC_INT_OVERFLOW_WAKEUP_SHIFT      (11)
#define RTC_INT_TICK_WAKEUP_SHIFT          (10)
#define RTC_CH3_INT_MATCH_WAKEUP_SHIFT     (9)
#define RTC_CH2_INT_MATCH_WAKEUP_SHIFT     (8)
#define RTC_CH1_INT_MATCH_WAKEUP_SHIFT     (7)
#define RTC_CH0_INT_MATCH_WAKEUP_SHIFT     (6)

typedef enum
{
    RTC_CH0_INT_MATCH_WAKEUP  = (0x01 << RTC_CH0_INT_MATCH_WAKEUP_SHIFT),
    RTC_CH1_INT_MATCH_WAKEUP  = (0x01 << RTC_CH1_INT_MATCH_WAKEUP_SHIFT),
    RTC_CH2_INT_MATCH_WAKEUP  = (0x01 << RTC_CH2_INT_MATCH_WAKEUP_SHIFT),
    RTC_CH3_INT_MATCH_WAKEUP  = (0x01 << RTC_CH3_INT_MATCH_WAKEUP_SHIFT),
    RTC_INT_TICK_WAKEUP       = (0x01 << RTC_INT_TICK_WAKEUP_SHIFT),
    RTC_INT_OVERFLOW_WAKEUP   = (0x01 << RTC_INT_OVERFLOW_WAKEUP_SHIFT),

} EN_RTC_INT_WAKEUP_EN_T;

#define RTC_INT_WAKEUP_EN_MASK            (0xFC0)


//=====================================================================================================================
// [0x00~0x08] RTC_INT_FLAG / RTC_INT_EN / RTC_INT_CLR
//=====================================================================================================================
#define RTC_INT_OVERFLOW_WAKEUP_SHIFT      (11)
#define RTC_INT_TICK_WAKEUP_SHIFT          (10)
#define RTC_CH3_INT_MATCH_WAKEUP_SHIFT     (9)
#define RTC_CH2_INT_MATCH_WAKEUP_SHIFT     (8)
#define RTC_CH1_INT_MATCH_WAKEUP_SHIFT     (7)
#define RTC_CH0_INT_MATCH_WAKEUP_SHIFT     (6)
#define RTC_INT_OVERFLOW_SHIFT             (5)
#define RTC_INT_TICK_SHIFT                 (4)
#define RTC_CH3_INT_MATCH_SHIFT            (3)
#define RTC_CH2_INT_MATCH_SHIFT            (2)
#define RTC_CH1_INT_MATCH_SHIFT            (1)
#define RTC_CH0_INT_MATCH_SHIFT            (0)

typedef enum
{
    RTC_CH0_INT_MATCH  = ((0x01 << RTC_CH0_INT_MATCH_SHIFT) | (0x01 << RTC_CH0_INT_MATCH_WAKEUP_SHIFT)),
    RTC_CH1_INT_MATCH  = ((0x01 << RTC_CH1_INT_MATCH_SHIFT) | (0x01 << RTC_CH1_INT_MATCH_WAKEUP_SHIFT)),
    RTC_CH2_INT_MATCH  = ((0x01 << RTC_CH2_INT_MATCH_SHIFT) | (0x01 << RTC_CH2_INT_MATCH_WAKEUP_SHIFT)),
    RTC_CH3_INT_MATCH  = ((0x01 << RTC_CH3_INT_MATCH_SHIFT) | (0x01 << RTC_CH3_INT_MATCH_WAKEUP_SHIFT)),

    RTC_INT_TICK       = ((0x01 << RTC_INT_TICK_SHIFT) | (0x01 << RTC_INT_TICK_WAKEUP_SHIFT)),
    RTC_INT_OVERFLOW   = ((0x01 << RTC_INT_OVERFLOW_SHIFT)  | (0x01 << RTC_INT_OVERFLOW_WAKEUP_SHIFT)),

} EN_RTC_INT_FLAG_T;

#define RTC_INT_MASK                      (0x3F)
#define RTC_INT_EN_MASK                   (0xFFF)


//=====================================================================================================================
// [0x0C](RW) RTC_INT_EN1
//=====================================================================================================================
//=============================================================================
// CH3_INT
#define RTC_CH3_INT_OVFLW_EN_SHIFT         (7)
#define RTC_CH3_INT_TICK_EN_SHIFT          (6)

// CH2_INT
#define RTC_CH2_INT_OVFLW_EN_SHIFT         (5)
#define RTC_CH2_INT_TICK_EN_SHIFT          (4)

// CH1_INT
#define RTC_CH1_INT_OVFLW_EN_SHIFT         (3)
#define RTC_CH1_INT_TICK_EN_SHIFT          (2)

//=============================================================================
// RTC_INT_EN1[1] RTC_CH0_INT_OVERFLOW_EN Define
#define RTC_CH0_INT_OVFLW_EN_SHIFT         (1)
#define RTC_CH0_INT_OVFLW_EN_MSK           ((0x01 << 1) - 1)

//=============================================================================
// RTC_INT_EN1[0] RTC_CH0_INT_TICK_EN Define
#define RTC_CH0_INT_TICK_EN_SHIFT          (0)
#define RTC_CH0_INT_TICK_EN_MSK            ((0x01 << 1) - 1)

typedef enum
{
    RTC_CH0_INT_TICK   = (0x01 << RTC_CH0_INT_TICK_EN_SHIFT),
    RTC_CH0_INT_OVFLW  = (0x01 << RTC_CH0_INT_OVFLW_EN_SHIFT),
    RTC_CH1_INT_TICK   = (0x01 << RTC_CH1_INT_TICK_EN_SHIFT),
    RTC_CH1_INT_OVFLW  = (0x01 << RTC_CH1_INT_OVFLW_EN_SHIFT),
    RTC_CH2_INT_TICK   = (0x01 << RTC_CH2_INT_TICK_EN_SHIFT),
    RTC_CH2_INT_OVFLW  = (0x01 << RTC_CH2_INT_OVFLW_EN_SHIFT),
    RTC_CH3_INT_TICK   = (0x01 << RTC_CH3_INT_TICK_EN_SHIFT),
    RTC_CH3_INT_OVFLW  = (0x01 << RTC_CH3_INT_OVFLW_EN_SHIFT),

} EN_RTC_INT_TICK_OVFLW_T;

#define RTC_INT_TICK_OVFLW_MASK            (0xFF)


//=====================================================================================================================
// [0x10](WO) RTC_CNT_READ
//=====================================================================================================================
#define RTC_CNT_READ_SHIFT                 (0)
#define RTC_CNT_READ_MSK                   ((0x01 << 1) - 1)

//=====================================================================================================================
// [0x14] RTC_COMPARE0_HI
//=====================================================================================================================
#define RTC_COMPARE_HI_SHIFT               (0)
#define RTC_COMPARE_HI_MSK                 ((0x01 << 8) - 1)

//=====================================================================================================================
// [0x18] RTC_COMPARE0_LO
//=====================================================================================================================
#define RTC_COMPARE_LO_SHIFT               (0)
#define RTC_COMPARE_LO_MSK                 (WORD_MSK)

//=====================================================================================================================
// [0x1C] RTC_COMPARE1_HI, @ref RTC_COMPARE_HI
//=====================================================================================================================

//=====================================================================================================================
// [0x20] RTC_COMPARE1_LO, @ref RTC_COMPARE_LO
//=====================================================================================================================


//=====================================================================================================================
// [0x38](WO) RTC_LOAD_TRIG
//=====================================================================================================================
//=============================================================================
// RTC_LOAD_TRIG[4:0]
#define RTC_WAKEUP_EN_SHIFT                (4)
#define RTC_CH3_INT_OVFLW_EN_MSK           ((0x01 << 1) - 1)

#define RTC_CH0_COMPARE_EN_SHIFT           (0)


//=====================================================================================================================
// [0x3C] RTC_TRIG_FLAG
//=====================================================================================================================
//=============================================================================
// RTC_TRIG_FLAG[9:0]
#define RTC_PRESCALE_DONE_SHIFT            (9)
#define RTC_OVERFLOW_DONE_SHIFT            (8)
#define RTC_CLR_CNT_DONE_SHIFT             (7)
#define RTC_STOP_DONE_SHIFT                (6)
#define RTC_START_DONE_SHIFT               (5)
#define RTC_WAKEUP_EN_DONE_SHIFT           (4)
#define RTC_CH3_COMPARE_DONE_SHIFT         (3)
#define RTC_CH2_COMPARE_DONE_SHIFT         (2)
#define RTC_CH1_COMPARE_DONE_SHIFT         (1)
#define RTC_CH0_COMPARE_DONE_SHIFT         (0)

#define RTC_TRIG_FLAG_DONE_MSK             ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x40] RTC_CLR_FLAG
//=====================================================================================================================
//=============================================================================
// RTC_CLR_FLAG[9:0]
#define RTC_PRESCALE_CLR_SHIFT             (9)
#define RTC_OVERFLOW_CLR_SHIFT             (8)
#define RTC_CLR_CNT_CLR_SHIFT              (7)
#define RTC_STOP_CLR_SHIFT                 (6)
#define RTC_START_CLR_SHIFT                (5)
#define RTC_WAKEUP_CLR_SHIFT               (4)
#define RTC_CH3_COMPARE_CLR_SHIFT          (3)
#define RTC_CH2_COMPARE_CLR_SHIFT          (2)
#define RTC_CH1_COMPARE_CLR_SHIFT          (1)
#define RTC_CH0_COMPARE_CLR_SHIFT          (0)

#define RTC_FLAG_CLEAR_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x44] RTC_CNT_HI
//=====================================================================================================================
#define RTC_CNT_HI_SHIFT                   (0)
#define RTC_CNT_HI_MSK                     ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x48] RTC_CNT_LO
//=====================================================================================================================
#define RTC_CNT_LO_SHIFT                   (0)
#define RTC_CNT_LO_MSK                     (WORD_MSK)

#define RTC_CNT_MAX                        (0xFFFFFFFFFFULL)


//=====================================================================================================================
// [0x4C](RO) RTC_WORK_STATUS
//=====================================================================================================================
//=============================================================================
// RTC_WORK_STATUS[0] RTC_WORK_STATUS Define
#define RTC_WORK_STATUS_SHIFT              (0)
#define RTC_WORK_STATUS_MSK                ((0x01 << 1) - 1)

typedef enum
{
    RTC_HAS_STOPED = 0,
    RTC_IS_WORKING = 1,

} EN_RTC_WORK_STATUS_T;


//=====================================================================================================================
// [0x50](RO) RTC_WAKEUP_STATUS
//=====================================================================================================================
//=============================================================================
// RTC_WAKEUP_STATUS[3:0] RTC_WAKEUP_STATUS Define
#define RTC_WAKUP_STATUS_SHIFT             (0)
#define RTC_WAKUP_STATUS_MSK               ((0x01 << 4) - 1)

typedef enum
{
    RTC_CH0_WAKEUP_STATUS = 0x01,
    RTC_CH1_WAKEUP_STATUS = 0x02,
    RTC_CH2_WAKEUP_STATUS = 0x04,
    RTC_CH3_WAKEUP_STATUS = 0x08,

} EN_RTC_WAKEUP_STATUS_T;


#ifdef __cplusplus
}
#endif

#endif /* __REG_RTC_H__ */


