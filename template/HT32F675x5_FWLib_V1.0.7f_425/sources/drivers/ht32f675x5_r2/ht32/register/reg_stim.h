/*************************************************************************************************************
 * @file    reg_stim.h
 * @version V1.1
 * @date    2022-01-12
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


#ifndef __REG_STIM_H__
#define __REG_STIM_H__


#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum
{
    STIM_CH0 = 0,
    STIM_CH1 = 1,
    STIM_CH2 = 2,
    STIM_CH3 = 3,

} EN_STIM_CH_T;

#define STIM_CH_MAX (4)
#define IS_VALID_STIM_CH(CH)    (STIM_CH_MAX > (CH))


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IOM uint32_t CNT;                           /* [0x18](RW) */

} ST_STIM_COMPARE_T;

typedef struct
{
    __IM  uint32_t STIM_INT_FLAG;                 /* [0x00](RO) */
    __IOM uint32_t STIM_INT_EN;                   /* [0x04](RW) */
    __OM  uint32_t STIM_INT_CLR;                  /* [0x08](WO) */
    __IOM uint32_t STIM_INT_EN1;                  /* [0x0C](RW) */
    __OM  uint32_t STIM_TRIG_CFG;                 /* [0x10](WO) */
    __IOM uint32_t STIM_PRESCALE;                 /* [0x14](RW) */
    ST_STIM_COMPARE_T STIM_COMPARE[STIM_CH_MAX];  /* [0x18~0x24](RW) */
    __OM  uint32_t STIM_LOAD_TRIG;                /* [0x28](WO) */
    __IM  uint32_t STIM_TRIG_FLAG;                /* [0x2C](RO) */
    __OM  uint32_t STIM_CLR_FLAG;                 /* [0x30](WO) */
    __IM  uint32_t STIM_CNT;                      /* [0x34](RO) */
    __IM  uint32_t STIM_WORK_STATUS;              /* [0x38](RO) */
    __IM  uint32_t STIM_WAKEUP_STATUS;            /* [0x3C](RO) */
          uint32_t STIM_RESERVE[8];               /* [0x40~0x5C] */

    __IOM uint32_t STIM_EXT_CG_EN;                /* [0x60](RW) */

} stSTIM_Handle_t, *pstSTIM_Handle_t;

#define IS_VALID_STIM_HANDLE(pstSTIM)  ((STIM0) == (pstSTIM) || (STIM1) == (pstSTIM))


//=====================================================================================================================
// [0x04](RW) STIM_INT_EN
//=============================================================================
#define STIM_INT_OVERFLOW_WAKEUP_SHIFT     (11)
#define STIM_INT_TICK_WAKEUP_SHIFT         (10)
#define STIM_CH3_INT_MATCH_WAKEUP_SHIFT    (9)
#define STIM_CH2_INT_MATCH_WAKEUP_SHIFT    (8)
#define STIM_CH1_INT_MATCH_WAKEUP_SHIFT    (7)
#define STIM_CH0_INT_MATCH_WAKEUP_SHIFT    (6)

#define STIM_CH0_INT_WAKEUP_MASK           ((0x01 << 1) - 1)

typedef enum
{
    STIM_CH0_INT_MATCH_WAKEUP  = (0x01 << STIM_CH0_INT_MATCH_WAKEUP_SHIFT),
    STIM_CH1_INT_MATCH_WAKEUP  = (0x01 << STIM_CH1_INT_MATCH_WAKEUP_SHIFT),
    STIM_CH2_INT_MATCH_WAKEUP  = (0x01 << STIM_CH2_INT_MATCH_WAKEUP_SHIFT),
    STIM_CH3_INT_MATCH_WAKEUP  = (0x01 << STIM_CH3_INT_MATCH_WAKEUP_SHIFT),
    STIM_INT_TICK_WAKEUP       = (0x01 << STIM_INT_TICK_WAKEUP_SHIFT),
    STIM_INT_OVERFLOW_WAKEUP   = (0x01 << STIM_INT_OVERFLOW_WAKEUP_SHIFT),

} EN_STIM_INT_WAKEUP_EN_T;

#define STIM_INT_WAKEUP_EN_MASK            (0xFC0)

//=============================================================================
// [0x00~0x08] STIM_INT_FLAG / STIM_INT_EN / STIM_INT_CLR
//=============================================================================
#define STIM_INT_OVERFLOW_SHIFT            (5)
#define STIM_INT_TICK_SHIFT                (4)
#define STIM_CH3_INT_MATCH_SHIFT           (3)
#define STIM_CH2_INT_MATCH_SHIFT           (2)
#define STIM_CH1_INT_MATCH_SHIFT           (1)
#define STIM_CH0_INT_MATCH_SHIFT           (0)

typedef enum
{
    STIM_CH0_INT_MATCH  = (0x01 << STIM_CH0_INT_MATCH_SHIFT),
    STIM_CH1_INT_MATCH  = (0x01 << STIM_CH1_INT_MATCH_SHIFT),
    STIM_CH2_INT_MATCH  = (0x01 << STIM_CH2_INT_MATCH_SHIFT),
    STIM_CH3_INT_MATCH  = (0x01 << STIM_CH3_INT_MATCH_SHIFT),
    STIM_INT_TICK       = (0x01 << STIM_INT_TICK_SHIFT),
    STIM_INT_OVERFLOW   = (0x01 << STIM_INT_OVERFLOW_SHIFT),

} EN_STIM_INT_T;

#define STIM_INT_MASK    (0x3F)


//=====================================================================================================================
// [0x0C](RW) STIM_INT_EN1
//=====================================================================================================================
//=============================================================================
// CH3_INT
#define STIM_CH3_INT_OVFLW_EN_SHIFT        (7)
#define STIM_CH3_INT_TICK_EN_SHIFT         (6)

// CH2_INT
#define STIM_CH2_INT_OVFLW_EN_SHIFT        (5)
#define STIM_CH2_INT_TICK_EN_SHIFT         (4)

// CH1_INT
#define STIM_CH1_INT_OVFLW_EN_SHIFT        (3)
#define STIM_CH1_INT_TICK_EN_SHIFT         (2)

//=============================================================================
// STIM_INT_EN1[1] STIM_CH0_INT_OVERFLOW_EN Define
#define STIM_CH0_INT_OVFLW_EN_SHIFT        (1)
#define STIM_CH0_INT_OVFLW_EN_MSK          ((0x01 << 1) - 1)

//=============================================================================
// STIM_INT_EN1[0] STIM_CH0_INT_TICK_EN Define
#define STIM_CH0_INT_TICK_EN_SHIFT         (0)
#define STIM_CH0_INT_TICK_EN_MSK           ((0x01 << 1) - 1)

typedef enum
{
    STIM_CH0_INT_TICK   = (0x01 << STIM_CH0_INT_TICK_EN_SHIFT),
    STIM_CH0_INT_OVFLW  = (0x01 << STIM_CH0_INT_OVFLW_EN_SHIFT),
    STIM_CH1_INT_TICK   = (0x01 << STIM_CH1_INT_TICK_EN_SHIFT),
    STIM_CH1_INT_OVFLW  = (0x01 << STIM_CH1_INT_OVFLW_EN_SHIFT),
    STIM_CH2_INT_TICK   = (0x01 << STIM_CH2_INT_TICK_EN_SHIFT),
    STIM_CH2_INT_OVFLW  = (0x01 << STIM_CH2_INT_OVFLW_EN_SHIFT),
    STIM_CH3_INT_TICK   = (0x01 << STIM_CH3_INT_TICK_EN_SHIFT),
    STIM_CH3_INT_OVFLW  = (0x01 << STIM_CH3_INT_OVFLW_EN_SHIFT),

} EN_STIM_INT_TICK_OVFLW_T;

#define STIM_INT_TICK_OVFLW_MASK    (0xFF)


//=====================================================================================================================
// [0x10](WO) STIM_TRIG_CFG
//=====================================================================================================================
//=============================================================================
// STIM_TRIG[4] STIM_CNT_READ Define
#define STIM_CNT_READ_SHIFT                (4)
#define STIM_CNT_READ_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG[3] STIM_OVERFLOW Define
#define STIM_OVERFLOW_SHIFT                (3)
#define STIM_OVERFLOW_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG[2] STIM_CLR Define
#define STIM_CLR_SHIFT                     (2)
#define STIM_CLR_MSK                       ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG[1] STIM_STOP Define
#define STIM_STOP_SHIFT                    (1)
#define STIM_STOP_MSK                      ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG[0] STIM_START Define
#define STIM_START_SHIFT                   (0)
#define STIM_START_MSK                     ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x14](RW) STIM_PRESCALE
//=====================================================================================================================
#define STIM_PRESCALE_SHIFT                (0)
#define STIM_PRESCALE_MSK                  ((0x01 << 12) - 1)


//=====================================================================================================================
// [0x18](RW) STIM_COMPARE0
//=====================================================================================================================
#define STIM_COMPARE_SHIFT                 (0)
#define STIM_COMPARE_MSK                   (WORD_MSK)


//=====================================================================================================================
// [0x1C~0x24] @ref STIM_COMPARE[1~3]
//=====================================================================================================================


//=====================================================================================================================
// [0x28](WO) STIM_LOAD_TRIG
//=====================================================================================================================
//=============================================================================
// STIM_LOAD_TRIG[5] STIM_WAKEUP_LOAD Define
#define STIM_WAKEUP_LOAD_SHIFT             (5)
#define STIM_WAKEUP_LOAD_MSK               ((0x01 << 1) - 1)

// STIM_LOAD_TRIG[4] STIM_PRESCALE_LOAD Define
#define STIM_PRESCALE_LOAD_SHIFT           (4)
#define STIM_PRESCALE_LOAD_MSK             ((0x01 << 1) - 1)

// STIM_LOAD_TRIG[0] STIM_CH0_COMPARE_LOAD Define
#define STIM_CH0_COMPARE_LOAD_SHIFT        (0)
#define STIM_CH0_COMPARE_LOAD_MSK          ((0x01 << 1) - 1)



//=====================================================================================================================
// [0x2C](RO) STIM_TRIG_FLAG
//=====================================================================================================================
//=============================================================================
// STIM_TRIG_FLAG[9] STIM_OVERFLOW_DONE Define
#define STIM_OVERFLOW_DONE_SHIFT           (9)
#define STIM_OVERFLOW_DONE_MSK             ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG_FLAG[8] STIM_CLR_CNT_DONE Define
#define STIM_CLR_CNT_DONE_SHIFT            (8)
#define STIM_CLR_CNT_DONE_MSK              ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG_FLAG[7] STIM_STOP_DONE Define
#define STIM_STOP_DONE_SHIFT               (7)
#define STIM_STOP_DONE_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG_FLAG[6] STIM_START_DONE Define
#define STIM_START_DONE_SHIFT              (6)
#define STIM_START_DONE_MSK                ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG_FLAG[5] STIM_WAKEUP_EN_DONE Define
#define STIM_WAKEUP_EN_DONE_SHIFT          (5)
#define STIM_WAKEUP_EN_DONE_MSK            ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG_FLAG[4] STIM_PRESCALE_DONE Define
#define STIM_PRESCALE_DONE_SHIFT           (4)
#define STIM_PRESCALE_DONE_MSK             ((0x01 << 1) - 1)

//=============================================================================
// STIM_TRIG_FLAG[0] STIM_CH0_COMPARE_DONE Define
#define STIM_CH0_COMPARE_DONE_SHIFT        (0)
#define STIM_CH0_COMPARE_DONE_MSK          ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x30](WO) STIM_CLR_FLAG
//=====================================================================================================================
//=============================================================================
// STIM_CLR_FLAG[9] STIM_OVERFLOW_CLR Define
#define STIM_OVERFLOW_CLR_SHIFT            (9)
#define STIM_OVERFLOW_CLR_MSK              ((0x01 << 1) - 1)

//=============================================================================
// STIM_CLR_FLAG[8] STIM_CLR_CNT_CLR Define
#define STIM_CLR_CNT_CLR_SHIFT             (8)
#define STIM_CLR_CNT_CLR_MSK               ((0x01 << 1) - 1)

//=============================================================================
// STIM_CLR_FLAG[7] STIM_STOP_CLR Define
#define STIM_STOP_CLR_SHIFT                (7)
#define STIM_STOP_CLR_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// STIM_CLR_FLAG[6] STIM_START_CLR Define
#define STIM_START_CLR_SHIFT               (6)
#define STIM_START_CLR_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// STIM_CLR_FLAG[5] STIM_WAKEUP_CLR Define
#define STIM_WAKEUP_CLR_SHIFT              (5)
#define STIM_WAKEUP_CLR_MSK                ((0x01 << 1) - 1)

//=============================================================================
// STIM_CLR_FLAG[4] STIM_PRESCALE_CLR Define
#define STIM_PRESCALE_CLR_SHIFT            (4)
#define STIM_PRESCALE_CLR_MSK              ((0x01 << 1) - 1)

//=============================================================================
// STIM_CLR_FLAG[0] STIM_CH0_COMPARE_CLR Define
#define STIM_CH0_COMPARE_CLR_SHIFT         (0)
#define STIM_CH0_COMPARE_CLR_MSK           ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x34](RO) STIM_CNT
//=====================================================================================================================
#define STIM_CNT_SHIFT                     (0)
#define STIM_CNT_MSK                       (WORD_MSK)

#define STIM_CNT_MAX                       (0xFFFFFFFF)


//=====================================================================================================================
// [0x34](RO) STIM_WORK_STATUS
//=====================================================================================================================
//=============================================================================
// STIM_WORK_STATUS[0] STIM_WORK_STATUS Define
#define STIM_WORK_STATUS_SHIFT            (0)
#define STIM_WORK_STATUS_MSK              ((0x01 << 1) - 1)

typedef enum
{
    EN_STIM_HAS_STOPED  = 0,
    EN_STIM_IS_WORKING  = 1,

} EN_STIM_WORK_STATUS_T;


//=====================================================================================================================
// [0x3C](RO) STIM_WAKEUP_STATUS
//=====================================================================================================================
//=============================================================================
// STIM_WAKEUP_STATUS[3:0] STIM_WAKEUP_STATUS Define
#define STIM_WAKEUP_STATUS_SHIFT           (0)
#define STIM_WAKEUP_STATUS_MSK             ((0x01 << 4) - 1)

typedef enum
{
    STIM_CH0_WAKEUP_STATUS = 0x01,
    STIM_CH1_WAKEUP_STATUS = 0x02,
    STIM_CH2_WAKEUP_STATUS = 0x04,
    STIM_CH3_WAKEUP_STATUS = 0x08,

} EN_STIM_WAKEUP_STATUS_T;




#ifdef __cplusplus
}
#endif

#endif /* __REG_STIM_H__ */


