/*************************************************************************************************************
 * @file    reg_qdec.h
 * @version V1.0
 * @date    2020-03-15
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


#ifndef __REG_QDEC_H__
#define __REG_QDEC_H__

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum
{
    QDEC_CH_X   = 0,
    QDEC_CH_Y   = 1,
    QDEC_CH_Z   = 2,
    QDEC_CH_MAX = 3

} EN_QDEC_CH_T;

#define IS_VALID_QDEC_CH(CH)   (CH < QDEC_CH_MAX)


//=====================================================================================================================
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t QDEC_INT_FLAG;           /* [0x00](RO) */
    __IOM uint32_t QDEC_INT_EN;             /* [0x04](RW) */
    __OM  uint32_t QDEC_INT_CLR;            /* [0x08](WO) */
    __IOM uint32_t QDEC_CTRL;               /* [0x0C](RW) */
    __IOM uint32_t QDEC_LED_POL;            /* [0x10](RW) */
    __IOM uint32_t QDEC_LED_PERIOD;         /* [0x14](RW) */
    __IOM uint32_t QDEC_SAMPLE_PERIOD;      /* [0x18](RW) */
    __IOM uint32_t QDEC_ACC_THLD;           /* [0x1C](RW) */
    __IOM uint32_t QDEC_ACC_DBL_THLD;       /* [0x20](RW) */
    __IOM uint32_t QDEC_ACC_NO_CHANGE_THLD; /* [0x24](RW) */
    __IM  uint32_t QDEC_DETECT_RESULT;      /* [0x28](RO) */
    __OM  uint32_t QDEC_CLR;                /* [0x2C](WO) */
    __IM  uint32_t QDEC_ACC_CNT;            /* [0x30](RO) */
    __IM  uint32_t QDEC_ACC_DBL_CNT;        /* [0x34](RO) */
    __IM  uint32_t QDEC_ACC_NO_CHANGE_CNT;  /* [0x38](RO) */

} stQDEC_Handle_t, *pstQDEC_Handle_t;



//=====================================================================================================================
// [0x00~0x08] QDEC_INT_FLAG / QDEC_INT_EN  / QDEC_INT_CLR
//=====================================================================================================================
#define QDEC_GOTO_SLEEP_SHIFT              (5)
#define QDEC_ACC_OVERFLOW_SHIFT            (4) /* Register (qdec_chx_acc) accumulating the valid transitions is overflow */
#define QDEC_ACC_DBL_OVERFLOW_SHIFT        (3)
#define QDEC_ACC_NO_CHANGE_OVERFLOW_SHIFT  (2)
#define QDEC_NEGATIVE_DIR_SHIFT            (1)
#define QDEC_POSITIVE_DIR_SHIFT            (0)

typedef enum
{
    QDEC_INT_POSITIVE_DIR              = (0x01 << QDEC_POSITIVE_DIR_SHIFT),
    QDEC_INT_NEGATIVE_DIR              = (0x01 << QDEC_NEGATIVE_DIR_SHIFT),
    QDEC_INT_ACC_NO_CHANGE_OVERFLOW    = (0x01 << QDEC_ACC_NO_CHANGE_OVERFLOW_SHIFT),
    QDEC_INT_ACC_DBL_OVERFLOW          = (0x01 << QDEC_ACC_DBL_OVERFLOW_SHIFT),

    QDEC_INT_ACC_OVERFLOW              = (0x01 << QDEC_ACC_OVERFLOW_SHIFT),
    QDEC_INT_GOTO_SLEEP                = (0x01 << QDEC_GOTO_SLEEP_SHIFT),

} EN_QDEC_INT_FLAG_T;

#define QDEC_INT_MASK        (0x3F)


//=====================================================================================================================
// [0x0C]QDEC_CTRL Register
//=====================================================================================================================
//=============================================================================
// QDEC_CTRL[2] QDEC_DIR_POL Define
#define QDEC_DIR_POL_SHIFT                 (2)
#define QDEC_DIR_POL_MSK                   ((0x01 << 1) - 1)

typedef enum
{
    QDEC_DIR_POL_00_01  = 0x00,
    QDEC_DIR_POL_00_10  = 0x01,

} EN_QDEC_DIR_POL_T;

#define IS_VALID_QDEC_DIR_POL(POL)   (((POL) == QDEC_DIR_POL_00_01) || \
                                      ((POL) == QDEC_DIR_POL_00_10))

//=============================================================================
// QDEC_CTRL[1] QDEC_DEBOUNCE_EN Define
#define QDEC_DEBOUNCE_EN_SHIFT             (1)
#define QDEC_DEBOUNCE_EN_MSK               ((0x01 << 1) - 1)

//=============================================================================
// QDEC_CTRL[0] QDEC_EN Define
#define QDEC_EN_SHIFT                      (0)
#define QDEC_EN_MSK                        ((0x01 << 1) - 1)

//=====================================================================================================================
// [0x10]QDEC_LED_POL Register
//=====================================================================================================================
#define QDEC_LED_POL_SHIFT                 (0)
#define QDEC_LED_POL_MSK                   ((0x01 << 1) - 1)

typedef enum
{
    QDEC_LED_ACTIVE_LOW   = 0x00,
    QDEC_LED_ACTIVE_HIGH  = 0x01,

} EN_QDEC_LED_POL_T;

#define IS_VALID_QDEC_LED_POL(POL)       (((POL) == QDEC_LED_ACTIVE_LOW) || ((POL) == QDEC_LED_ACTIVE_HIGH))


//=====================================================================================================================
// [0x14](RW) QDEC_LED_PERIOD Register
//=====================================================================================================================
#define QDEC_LED_PERIOD_SHIFT              (0) /* time period the LED is switched on, unit is 62.5ns */
#define QDEC_LED_PERIOD_MSK                ((0x01 << 21) - 1)


//=====================================================================================================================
// [0x18](RW) QDEC_SAMPLE_PERIOD Register
//=====================================================================================================================
#define QDEC_SAMPLE_PERIOD_SHIFT           (0)
#define QDEC_SAMPLE_PERIOD_MSK             ((0x01 << 4) - 1)

typedef enum
{
    QDEC_SAMPLE_PERIOD_128US    = 0,
    QDEC_SAMPLE_PERIOD_256US    = 1,
    QDEC_SAMPLE_PERIOD_512US    = 2,
    QDEC_SAMPLE_PERIOD_1024US   = 3,
    QDEC_SAMPLE_PERIOD_2048US   = 4,
    QDEC_SAMPLE_PERIOD_4096US   = 5,
    QDEC_SAMPLE_PERIOD_8192US   = 6,
    QDEC_SAMPLE_PERIOD_16384US  = 7,
    QDEC_SAMPLE_PERIOD_32768US  = 8,
    QDEC_SAMPLE_PERIOD_65536US  = 9,
    QDEC_SAMPLE_PERIOD_131072US = 10,
    QDEC_SAMPLE_PERIOD_MAX      = 11,

} EN_QDEC_SAMPLE_PERIOD_T;

#define IS_VALID_QDEC_SAMPLE_PERIOD(PERIOD)   (PERIOD < QDEC_SAMPLE_PERIOD_MAX)


//=====================================================================================================================
// [0x1C](RW) QDEC_ACC_THLD Register
//=====================================================================================================================
#define QDEC_ACC_THLD_SHIFT                (0)
#define QDEC_ACC_THLD_MSK                  ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x20](RW) QDEC_ACC_DBL_THLD Register
//=====================================================================================================================
#define QDEC_ACC_DBL_THLD_SHIFT            (0)
#define QDEC_ACC_DBL_THLD_MSK              ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x24](RW) QDEC_ACC_NO_CHANGE_THLD Register
//=====================================================================================================================
#define QDEC_ACC_NO_CHANGE_THLD_SHIFT      (0)
#define QDEC_ACC_NO_CHANGE_THLD_MSK        ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x28](RO) QDEC_DETECT_RESULT Register
//=====================================================================================================================
#define QDEC_DETECT_RESULT_SHIFT           (0)
#define QDEC_DETECT_RESULT_MSK             ((0x01 << 3) - 1)

typedef enum
{
    QDEC_DETECT_NO_MOVEMENT       = 0,
    QDEC_DETECT_POSITIVE_DIR      = 1,
    QDEC_DETECT_DOUBLE_TRANSITION = 2,
    QDEC_DETECT_NEGATIVE_DIR      = 7,

} EN_QDEC_DETECT_RESULT_T;

#define IS_VALID_QDEC_DETECT_RESULT(RESULT)   (RESULT == QDEC_DETECT_NO_MOVEMENT       || \
                                               RESULT == QDEC_DETECT_POSITIVE_DIR      || \
                                               RESULT == QDEC_DETECT_DOUBLE_TRANSITION || \
                                               RESULT == QDEC_DETECT_NEGATIVE_DIR)


//=====================================================================================================================
// [0x2C](WO) QDEC_CLR Register
//=====================================================================================================================
//=============================================================================
// QDEC_CLR[2:0] QDEC_CLR_CNT Define
#define QDEC_CLR_CNT_SHIFT                 (0)
#define QDEC_CLR_CNT_MSK                   ((0x01 << 3) - 1)

typedef enum
{
    QDEC_CLR_ACC_CNT            = 0x01,
    QDEC_CLR_ACC_DBL_CNT        = 0x02,
    QDEC_CLR_ACC_NO_CHANGE_CNT  = 0x04,

} EN_QDEC_CLR_CNT_T;


//=====================================================================================================================
// [0x30](RO) QDEC_ACC_CNT Register
//=====================================================================================================================
#define QDEC_ACC_CNT_BITS                  (7)
#define QDEC_ACC_CNT_SHIFT                 (0)
#define QDEC_ACC_CNT_MSK                   ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x34](RO) QDEC_ACC_DBL_CNT Register
//=====================================================================================================================
#define QDEC_ACC_DBL_CNT_SHIFT             (0)
#define QDEC_ACC_DBL_CNT_MSK               ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x38](RO) QDEC_ACC_NO_CHANGE_CNT Register
//=====================================================================================================================
#define QDEC_ACC_NO_CHANGE_CNT_SHIFT       (0)
#define QDEC_ACC_NO_CHANGE_CNT_MSK         ((0x01 << 8) - 1)


#ifdef __cplusplus
}
#endif

#endif /* __REG_QDEC_H__ */

