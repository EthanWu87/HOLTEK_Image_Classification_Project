/*************************************************************************************************************
 * @file    reg_uart.h
 * @version V1.1
 * @date    2022-01-13
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


#ifndef __REG_UART_H__
#define __REG_UART_H__

#ifdef __cplusplus
 extern "C" {
#endif


//=====================================================================================================================
// DEFAULT CONFIG
//=====================================================================================================================
#define UART_INIT_DEFAULT(enParity)                                                 \
( ((1 & UART_TX_FIFO_THLD_MSK) << UART_TX_FIFO_THLD_SHIFT)      | /* bit0~bit4 */   \
  ((1 & UART_RX_FIFO_THLD_MSK) << UART_RX_FIFO_THLD_SHIFT)      | /* bit5~bit9 */   \
  (UART_STOP_SIZE_1BIT << UART_STOP_SIZE_SHIFT)                 | /* bit10~bit11 */ \
  (UART_DATA_BITS_8 << UART_DATA_SIZE_SHIFT)                    | /* bit12~bit13 */ \
  ((enParity & UART_PARITY_MODE_MSK) << UART_PARITY_MODE_SHIFT) | /* bit14~bit16 */ \
  (UART_LITTLE_ENDIAN << UART_ENDIAN_MODE_SHIFT)                | /* bit17 */       \
  (UART_LINEBREAK_DISABLE << UART_LINE_BREAK_EN_SHIFT)          | /* bit18 */       \
  (0 << UART_FLOW_CTRL_EN_SHIFT)                                | /* bit19 */       \
  (16 << UART_RTS_THLD_SHIFT)                                   | /* bit20~bit24 */ \
  (UART_DISCARD_DISABLE << UART_ERR_DISCARD_EN_SHIFT)             /* bit25 */       \
)


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __OM  uint32_t UART_TX_FIFO;        /* [0x00](WO) */
    __IM  uint32_t UART_RX_FIFO;        /* [0x04](RO) */
    __IM  uint32_t UART_INT_FLAG;       /* [0x08](RO) */
    __IOM uint32_t UART_INT_EN;         /* [0x0C](RW) */
    __OM  uint32_t UART_INT_CLR;        /* [0x10](WO) */
    __IOM uint32_t UART_CFG;            /* [0x14](RW) */
    __IOM uint32_t UART_TIMEOUT;        /* [0x18](RW) */
    __IOM uint32_t UART_CLK_CFG;        /* [0x1C](RW) */
    __IM  uint32_t UART_RXFIFO_CNT;     /* [0x20](RO) */
    __IM  uint32_t UART_TXFIFO_CNT;     /* [0x24](RO) */
    __OM  uint32_t UART_RXFIFO_CLR;     /* [0x28](WO) */
    __OM  uint32_t UART_TXFIFO_CLR;     /* [0x2C](WO) */
    __IOM uint32_t UART_EXT_CG_EN;      /* [0x30](RW) */
    __IOM uint32_t UART2_PHY_CFG;       /* [0x34](RW) */
    __IOM uint32_t UART2_CFG;           /* [0x38](RW) */
    __OM  uint32_t UART2_MODE_TRIG;     /* [0x3C](WO) */

} stUART_Handle_t, *pstUART_Handle_t;

#define IS_VALID_UART_HANDLE(pstUART)   ((UART0) == (pstUART) || \
                                         (UART1) == (pstUART) || \
                                         (UART2) == (pstUART))


//=====================================================================================================================
// [0x00](WO) UART_TX_FIFO
//=====================================================================================================================
#define UART_TX_FIFO_DATA_SHIFT            (0)
#define UART_TX_FIFO_DATA_MSK              ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x04](RO) UART_RX_FIFO
//=====================================================================================================================
#define UART_RX_FIFO_DATA_SHIFT            (0)
#define UART_RX_FIFO_DATA_MSK              ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x08~0x10] UART_INT_FLAG(RO) / UART_INT_EN(RW) / UART_INT_CLR(WO)
//=====================================================================================================================
#define UART2_RX_START_FRAME_SHIFT         (12)
#define UART_TX_FINISHED_SHIFT             (11)
#define UART_TXFIFO_OVERFLOW_SHIFT         (10)
#define UART_RXFIFO_UNDER_FLOW_SHIFT       (9)
#define UART_RXFIFO_NOT_EMPTY_SHIFT        (8)
#define UART_RXFIFO_OVERFLOW_SHIFT         (7)
#define UART_RXFIFO_OVER_THLD_SHIFT        (6)
#define UART_TXFIFO_EMPTY_SHIFT            (5)
#define UART_TXFIFO_UNDER_THLD_SHIFT       (4)
#define UART_RX_TIMEOUT_SHIFT              (3)
#define UART_RX_LINE_BREAK_SHIFT           (2)
#define UART_PARITY_ERR_SHIFT              (1)
#define UART_STOP_ERR_SHIFT                (0)

typedef enum
{
    UART_INT_STOP_ERR             = (0x01 << UART_STOP_ERR_SHIFT),
    UART_INT_PARITY_ERR           = (0x01 << UART_PARITY_ERR_SHIFT),
    UART_INT_LINE_BREAK           = (0x01 << UART_RX_LINE_BREAK_SHIFT),
    UART_INT_RX_TIMEOUT           = (0x01 << UART_RX_TIMEOUT_SHIFT),

    UART_INT_TXFIFO_UNDER_THLD    = (0x01 << UART_TXFIFO_UNDER_THLD_SHIFT),
    UART_INT_TXFIFO_EMPTY         = (0x01 << UART_TXFIFO_EMPTY_SHIFT),
    UART_INT_RXFIFO_OVER_THLD     = (0x01 << UART_RXFIFO_OVER_THLD_SHIFT),
    UART_INT_RXFIFO_OVER_FLOW     = (0x01 << UART_RXFIFO_OVERFLOW_SHIFT),

    UART_INT_RXFIFO_NOT_EMPTY     = (0x01 << UART_RXFIFO_NOT_EMPTY_SHIFT),
    UART_INT_RXFIFO_UNDER_FLOW    = (0x01 << UART_RXFIFO_UNDER_FLOW_SHIFT),
    UART_INT_TXFIFO_OVER_FLOW     = (0x01 << UART_TXFIFO_OVERFLOW_SHIFT),
    UART_INT_TX_FINISHED          = (0x01 << UART_TX_FINISHED_SHIFT),

    UART2_INT_RX_START_FRAME      = (0x01 << UART2_RX_START_FRAME_SHIFT),

} EN_UART_INT_FLAG_T;

#define UART_INT_MASK                      (0x1FFF)


//=====================================================================================================================
// [0x14](RW) UART_CONFIG Register
//=====================================================================================================================
#define UART_CONFIG_DEFAULT                (0x00F93108)

//=============================================================================
// UART_CONFIG[26] UART2_UART_SCC_SEL Define
#define UART2_UART_SCC_SEL_SHIFT           (26)
#define UART2_UART_SCC_SEL_MSK             ((0x01 << 1) - 1)

typedef enum
{
    UART_SEL_UART  = 0x00,
    UART_SEL_SCC   = 0x01,

} EN_UART_UART_SCC_SEL_T;

//=============================================================================
// UART_CONFIG[25] UART_ERR_DISCARD_EN Define
#define UART_ERR_DISCARD_EN_SHIFT          (25)
#define UART_ERR_DISCARD_EN_MSK            ((0x01 << 1) - 1)

typedef enum
{
    UART_DISCARD_DISABLE  = 0x00,   /* Disable the discard */
    UART_DISCARD_ENABLE   = 0x01,   /* Enables the discard */
} EN_UART_DISCARD_EN_T;

#define IS_UART_DISCARD_EN_VALID(DISCARD) (((DISCARD) == UART_DISCARD_DISABLE) || \
                                           ((DISCARD) == UART_DISCARD_ENABLE))

//=============================================================================
// UART_CONFIG[24:20] UART_RTS_THLD Define
#define UART_RTS_THLD_SHIFT                (20)
#define UART_RTS_THLD_MSK                  ((0x01 << 5) - 1)

//=============================================================================
// UART_CONFIG[19] UART_FLOWCTRL_EN Define
#define UART_FLOW_CTRL_EN_SHIFT            (19)
#define UART_FLOW_CTRL_EN_MSK              ((0x01 << 1) - 1)

typedef enum
{
    UART_FLOW_DISABLE  = 0x00,
    UART_FLOW_ENABLE   = 0x01,

} EN_UART_FLOW_EN_T;

#define IS_VALID_UART_FLOW_EN(EN) (((EN) == UART_FLOW_DISABLE) || \
                                   ((EN) == UART_FLOW_ENABLE))

//=============================================================================
// UART_CONFIG[18] UART_LINE_BREAK_EN Define
#define UART_LINE_BREAK_EN_SHIFT           (18)
#define UART_LINE_BREAK_EN_MSK             ((0x01 << 1) - 1)

typedef enum
{
    UART_LINEBREAK_DISABLE  = 0x00,   /* line break disable */
    UART_LINEBREAK_ENABLE   = 0x01,   /* line break enable */

} EN_UART_LB_EN_T;

#define IS_VALID_UART_LINEBREAK_EN(EN) (((EN) == UART_LINEBREAK_DISABLE) || \
                                        ((EN) == UART_LINEBREAK_ENABLE))

//=============================================================================
// UART_CONFIG[17] UART_EDNIAN_MODE Define
#define UART_ENDIAN_MODE_SHIFT             (17)
#define UART_ENDIAN_MODE_MSK               ((0x01 << 1) - 1)

typedef enum
{
    UART_LITTLE_ENDIAN      = 0x00,   /* Little endian mode */
    UART_BIG_ENDIAN         = 0x01,   /* Big endian mode */

} EN_UART_ENDIAN_T;

#define IS_VALID_UART_ENDIAN(ENDIAN) (((ENDIAN) == UART_LITTLE_ENDIAN) || \
                                      ((ENDIAN) == UART_BIG_ENDIAN))

//=============================================================================
// UART_CONFIG[16:14] UART_PARITY_MODE Define
#define UART_PARITY_MODE_SHIFT             (14)
#define UART_PARITY_MODE_MSK               ((0x01 << 3) - 1)

typedef enum
{
    UART_PARITY_ODD          = 0x00,   /* odd parity */
    UART_PARITY_EVEN         = 0x01,   /* Even parity */
    UART_PARITY_STICK_1      = 0x02,   /* The parity bit is always 1. */
    UART_PARITY_STICK_0      = 0x03,   /* The parity bit is always 0. */
    UART_PARITY_NONE         = 0x04,   /* No parity */

} EN_UART_PARITY_BITS_T;

#define IS_VALID_UART_PARITY(PARITY) (((PARITY) == UART_PARITY_ODD)     || \
                                      ((PARITY) == UART_PARITY_EVEN)    || \
                                      ((PARITY) == UART_PARITY_STICK_1) || \
                                      ((PARITY) == UART_PARITY_STICK_0) || \
                                      ((PARITY) == UART_PARITY_NONE))

//=============================================================================
// UART_CONFIG[13:12] UART_DATA_SIZE Define
#define UART_DATA_SIZE_SHIFT               (12)
#define UART_DATA_SIZE_MSK                 ((0x01 << 2) - 1)

typedef enum
{
    UART_DATA_BITS_5  = 0x00,   /* 5-bit data length */
    UART_DATA_BITS_6  = 0x01,   /* 6-bit data length */
    UART_DATA_BITS_7  = 0x02,   /* 7-bit data length */
    UART_DATA_BITS_8  = 0x03,   /* 8-bit data length */

} EN_UART_DATA_SIZE_T;

#define IS_UART_DATA_BITS_VALID(BITS) (((BITS) == UART_DATA_BITS_5) || \
                                       ((BITS) == UART_DATA_BITS_6) || \
                                       ((BITS) == UART_DATA_BITS_7) || \
                                       ((BITS) == UART_DATA_BITS_8))

//=============================================================================
// UART_CONFIG[11:10] UART_STOP_SIZE Define
#define UART_STOP_SIZE_SHIFT               (10)
#define UART_STOP_SIZE_MSK                 ((0x01 << 2) - 1)

typedef enum
{
    UART_STOP_SIZE_1BIT    = 0x00,   /* 1 stop bit */
    UART_STOP_SIZE_1P5BIT  = 0x01,   /* 1.5stop bit */
    UART_STOP_SIZE_2BIT    = 0x02,   /* 2 stop bits */

} EN_UART_STOP_SIZE_T;

#define IS_UART_STOP_BITS_VALID(STOPBITS) (((STOPBITS) == UART_STOP_SIZE_1BIT)   || \
                                           ((STOPBITS) == UART_STOP_SIZE_1P5BIT) || \
                                           ((STOPBITS) == UART_STOP_SIZE_2BIT))

//=============================================================================
// UART_CONFIG[9:5] UART_RXFIFO_THLD Define
#define UART_RX_FIFO_THLD_SHIFT            (5)
#define UART_RX_FIFO_THLD_MSK              ((0x01 << 5) - 1)
#define UART_RXFIFO_THLD_MAX               (0x01 << 4)

//=============================================================================
// UART_CONFIG[4:0] UART_TXFIFO_THLD Define
#define UART_TX_FIFO_THLD_SHIFT            (0)
#define UART_TX_FIFO_THLD_MSK              ((0x01 << 5) - 1)
#define UART_TXFIFO_THLD_MAX               (0x01 << 4)


//=====================================================================================================================
// [0x18](RW) UART_TIMEOUT Register
//=====================================================================================================================
#define UART_TIMEOUT_DEFAULT               (0x000000FF)

#define UART_RX_TIMEOUT_THLD_SHIFT         (0)
#define UART_RX_TIMEOUT_THLD_MSK           ((0x01 << 8) - 1)

//=====================================================================================================================
// [0x1C](RW) UART_CLK_CFG Register
//=====================================================================================================================
#define UART_CLK_CFG_DEFAULT               (0x00130089)

//=============================================================================
// UART_CLK_CFG[25:16] UART_TRIG_INTVAL Define
#define UART_TRIG_INTVAL_SHIFT             (16)
#define UART_TRIG_INTVAL_MSK               ((0x01 << 10) - 1)

//=============================================================================
// UART_CLK_CFG[15:0] UART_CAP_INTV Define
#define UART_CAP_INTV_SHIFT                (0)
#define UART_CAP_INTV_MSK                  ((0x01 << 16) - 1)

//=====================================================================================================================
// [0x20](RO) UART_RXFIFO_CNT Register
//=====================================================================================================================
#define UART_RX_FIFO_CNT_SHIFT             (0)
#define UART_RX_FIFO_CNT_MSK               ((0x01 << 5) - 1)
#define UART_RX_FIFO_CNT_MAX               (16)

//=====================================================================================================================
// [0x24](RO) UART_TXFIFO_CNT Register
//=====================================================================================================================
#define UART_TX_FIFO_CNT_SHIFT             (0)
#define UART_TX_FIFO_CNT_MSK               ((0x01 << 5) - 1)
#define UART_TX_FIFO_CNT_MAX               (16)


//=====================================================================================================================
// [0x28](WO) UART_RXFIFO_CLR Register
//=====================================================================================================================
#define UART_RXFIFO_CLR_SHIFT              (0)
#define UART_RXFIFO_CLR_MSK                ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x2C](WO) UART_TXFIFO_CLR Register
//=====================================================================================================================
#define UART_TXFIFO_CLR_SHIFT              (0)
#define UART_TXFIFO_CLR_MSK                ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x30](RW) UART2_PHY_CFG Register
//=====================================================================================================================
//=============================================================================
// UART2_PHY_CFG[11:4] UART2_START_FRAME Define
#define UART2_START_FRAME_SHIFT            (4)
#define UART2_START_FRAME_MSK              ((0x01 << 8) - 1)

//=============================================================================
// UART2_PHY_CFG[4:0] UART2_TX_WAIT_TIME Define
#define UART2_TX_WAIT_TIME_SHIFT           (0)
#define UART2_TX_WAIT_TIME_MSK             ((0x01 << 5) - 1)


#ifdef __cplusplus
}
#endif

#endif


