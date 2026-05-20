/*************************************************************************************************************
 * @file    reg_dma.h
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



#ifndef __REG_DMA_H__
#define __REG_DMA_H__


#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================================================================
// DEFAULT CONFIG
//=====================================================================================================================
// Memory to Memory
#define DMA_INIT_MEM_TO_MEM_DEFAULT_CFG(u16Length, u8DataSize)          \
(   (u16Length)                                     | /* bit0~bit15 */  \
    (0 << DMA_CIRC_EN_SHIFT)                        | /* bit16 */       \
    (DMA_PRIO_LEVEL_LOW << DMA_PRIORITY_SEL_SHIFT)  | /* bit17 */       \
    (DMA_MEM_TO_MEM << DMA_WORK_MODE_SEL_SHIFT)     | /* bit18~bit19 */ \
    (u8DataSize << DMA_DST_DATA_SIZE_SHIFT)         | /* bit20~bit21 */ \
    (DMA_ADDR_INC_ENABLE << DMA_DST_INC_EN_SHIFT)   | /* bit22 */       \
    (u8DataSize << DMA_SRC_DATA_SIZE_SHIFT)         | /* bit23~bit24 */ \
    (DMA_ADDR_INC_ENABLE << DMA_SRC_INC_EN_SHIFT)   | /* bit25 */       \
    (0 << DMA_STOP_CTRL_SHIFT)                        /* bit26 */       \
)

// Peripheral to Memory
#define DMA_INIT_PERI_TO_MEM_DEFAULT_CFG(u16Length, u8DataSize)         \
(   (u16Length)                                     | /* bit0~bit15 */  \
    (DMA_CIRC_EN_MSK << DMA_CIRC_EN_SHIFT)          | /* bit16 */       \
    (DMA_PRIO_LEVEL_LOW << DMA_PRIORITY_SEL_SHIFT)  | /* bit17 */       \
    (DMA_PERI_TO_MEM << DMA_WORK_MODE_SEL_SHIFT)    | /* bit18~bit19 */ \
    (u8DataSize << DMA_DST_DATA_SIZE_SHIFT)         | /* bit20~bit21 */ \
    (DMA_ADDR_INC_ENABLE << DMA_DST_INC_EN_SHIFT)   | /* bit22 */       \
    (u8DataSize << DMA_SRC_DATA_SIZE_SHIFT)         | /* bit23~bit24 */ \
    (DMA_ADDR_INC_DISABLE << DMA_SRC_INC_EN_SHIFT)  | /* bit25 */       \
    (0 << DMA_STOP_CTRL_SHIFT)                        /* bit26 */       \
)

// Memory to Peripheral
#define DMA_INIT_MEM_TO_PERI_DEFAULT_CFG(u16Length, u8DataSize)         \
(   (u16Length)                                     | /* bit0~bit15 */  \
    (DMA_CIRC_EN_MSK << DMA_CIRC_EN_SHIFT)          | /* bit16 */       \
    (DMA_PRIO_LEVEL_LOW << DMA_PRIORITY_SEL_SHIFT)  | /* bit17 */       \
    (DMA_MEM_TO_PERI << DMA_WORK_MODE_SEL_SHIFT)    | /* bit18~bit19 */ \
    (u8DataSize << DMA_DST_DATA_SIZE_SHIFT)         | /* bit20~bit21 */ \
    (DMA_ADDR_INC_DISABLE << DMA_DST_INC_EN_SHIFT)  | /* bit22 */       \
    (u8DataSize << DMA_SRC_DATA_SIZE_SHIFT)         | /* bit23~bit24 */ \
    (DMA_ADDR_INC_ENABLE << DMA_SRC_INC_EN_SHIFT)   | /* bit25 */       \
    (0 << DMA_STOP_CTRL_SHIFT)                        /* bit26 */       \
)

// Peripheral to Peripheral
#define DMA_INIT_PERI_TO_PERI_DEFAULT_CFG(u8SrcDataSize, u8DstDataSize) \
(   (0)                                             | /* bit0~bit15 */  \
    (DMA_CIRC_EN_MSK << DMA_CIRC_EN_SHIFT)          | /* bit16 */       \
    (DMA_PRIO_LEVEL_LOW << DMA_PRIORITY_SEL_SHIFT)  | /* bit17 */       \
    (DMA_PERI_TO_PERI << DMA_WORK_MODE_SEL_SHIFT)   | /* bit18~bit19 */ \
    (u8DstDataSize << DMA_DST_DATA_SIZE_SHIFT)      | /* bit20~bit21 */ \
    (DMA_ADDR_INC_DISABLE << DMA_DST_INC_EN_SHIFT)  | /* bit22 */       \
    (u8SrcDataSize << DMA_SRC_DATA_SIZE_SHIFT)      | /* bit23~bit24 */ \
    (DMA_ADDR_INC_DISABLE << DMA_SRC_INC_EN_SHIFT)  | /* bit25 */       \
    (0 << DMA_STOP_CTRL_SHIFT)                        /* bit26 */       \
)




//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t DMA_INT_FLAG;           /* [0x00](RO) */
    __IOM uint32_t DMA_INT_EN;             /* [0x04](RW) */
    __OM  uint32_t DMA_INT_CLR;            /* [0x08](WO) */
    __IOM uint32_t DMA_CFG;                /* [0x0C](RW) */
    __IOM uint32_t DMA_TOTAL_LEN;          /* [0x10](RW) */
    __IOM uint32_t DMA_SRC_ADDR;           /* [0x14](RW) */
    __IOM uint32_t DMA_DST_ADDR;           /* [0x18](RW) */
    __IM  uint32_t DMA_TRANS_CNT;          /* [0x1C](RO) */
    __IM  uint32_t DMA_TOTAL_CNT;          /* [0x20](RO) */
    __IOM uint32_t DMA_TIMEOUT;            /* [0x24](RW) */
    __IOM uint32_t DMA_PERI_SEL;           /* [0x28](RW) */
    __IOM uint32_t DMA_INTERVAL_TX_CFG;    /* [0x2C](RW) */
    __OM  uint32_t DMA_DATA_READY;         /* [0x30](WO) */
    __IOM uint32_t DMA_INT_SEL;            /* [0x34](RW) */
    __IOM uint32_t DMA_PERI_2_PERI_SEL;    /* [0x38](RW) */
    __IOM uint32_t DMA_RAM_CTRL;           /* [0x3C](RW) */

} stDMA_Handle_t, *pstDMA_Handle_t;

#define IS_VALID_DMA_HANDLE(pstDMA)    ((DMA0) == (pstDMA) \
                                     || (DMA1) == (pstDMA) \
                                     || (DMA2) == (pstDMA) \
                                     || (DMA3) == (pstDMA) \
                                     || (DMA4) == (pstDMA) \
                                     || (DMA5) == (pstDMA) \
                                     || (DMA6) == (pstDMA) \
                                     || (DMA7) == (pstDMA))


//=====================================================================================================================
// [0x00~0x08] DMA_INT_FLAG / DMA_INT_EN / DMA_INT_CLR Register
//=====================================================================================================================
#define DMA_INT_FIFO_OVERFLOW_SHIFT    (6)
#define DMA_INT_TOTAL_DONE_SHIFT       (5)
#define DMA_INT_1_4_DONE_SHIFT         (4)
#define DMA_INT_2_4_DONE_SHIFT         (3)
#define DMA_INT_3_4_DONE_SHIFT         (2)
#define DMA_INT_4_4_DONE_SHIFT         (1)
#define DMA_INT_TIMEOUT_SHIFT          (0)

typedef enum
{
    DMA_INT_FIFO_OVERFLOW    = (0x01 << DMA_INT_FIFO_OVERFLOW_SHIFT),
    DMA_INT_TOTAL_DONE       = (0x01 << DMA_INT_TOTAL_DONE_SHIFT),
    DMA_INT_1_4_DONE         = (0x01 << DMA_INT_1_4_DONE_SHIFT),
    DMA_INT_2_4_DONE         = (0x01 << DMA_INT_2_4_DONE_SHIFT),
    DMA_INT_3_4_DONE         = (0x01 << DMA_INT_3_4_DONE_SHIFT),
    DMA_INT_4_4_DONE         = (0x01 << DMA_INT_4_4_DONE_SHIFT),
    DMA_INT_TIMEOUT          = (0x01 << DMA_INT_TIMEOUT_SHIFT)

} EN_DMA_INT_MSK_T;

#define DMA0_INT_MSK                       (0x7F)
#define DMA_INT_MSK                        (0x3F)


//=====================================================================================================================
// [0x0C] DMA_CFG Register
//=====================================================================================================================
//=============================================================================
// DMA_CFG[28] DMA_ENABLE Define
#define DMA_ENABLE_SHIFT                   (28)
#define DMA_ENABLE_MSK                     ((0x01U << 1) - 1) /* U:fix warnning */

typedef enum
{
    DMA_DISABLE  = (0x00),
    DMA_ENABLE   = (0x01),

} EN_DMA_ENABLE_T;

#define IS_VALID_DMA_EN(EN)   (((EN) == DMA_DISABLE) || ((EN) == DMA_ENABLE))

//=============================================================================
// DMA_CFG[27] DMA_PAUSE_CTRL Define
#define DMA_PAUSE_CTRL_SHIFT               (27)
#define DMA_PAUSE_CTRL_MSK                 ((0x01 << 1) - 1)

typedef enum
{
    DMA_CONTINUE_TRANSFER  = (0x00),
    DMA_PAUSE_TRANSFER     = (0x01),

} EN_DMA_PAUSE_ENABLE_T;

//=============================================================================
// DMA_CFG[26] DMA_STOP_CTRL Define
#define DMA_STOP_CTRL_SHIFT                (26)
#define DMA_STOP_CTRL_MSK                  ((0x01 << 1) - 1)

//=============================================================================
// DMA_CFG[25] DMA_SRC_INC_EN Define
#define DMA_SRC_INC_EN_SHIFT               (25)
#define DMA_SRC_INC_EN_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// DMA_CFG[24:23] DMA_SRC_DATA_SIZE Define
#define DMA_SRC_DATA_SIZE_SHIFT            (23)
#define DMA_SRC_DATA_SIZE_MSK              ((0x01 << 2) - 1)

typedef enum
{
    DMA_DATA_1BYTE     = (0x00),
    DMA_DATA_2BYTES    = (0x01),
    DMA_DATA_4BYTES    = (0x02),

} EN_DMA_DATA_SIZE_T;

//=============================================================================
// DMA_CFG[22] DMA_DST_INC_EN Define
#define DMA_DST_INC_EN_SHIFT               (22)
#define DMA_DST_INC_EN_MSK                 ((0x01 << 1) - 1)

typedef enum
{
    DMA_ADDR_INC_DISABLE  = (0x00),
    DMA_ADDR_INC_ENABLE   = (0x01),

} EN_DMA_ADDR_INC_EN_T;

//=============================================================================
// DMA_CFG[21:20] DMA_DST_DATA_SIZE Define
#define DMA_DST_DATA_SIZE_SHIFT            (20)
#define DMA_DST_DATA_SIZE_MSK              ((0x01 << 2) - 1)

//=============================================================================
// DMA_CFG[19:18] DMA_WORK_MODE_SEL Define
#define DMA_WORK_MODE_SEL_SHIFT            (18)
#define DMA_WORK_MODE_SEL_MSK              ((0x01 << 2) - 1)

typedef enum
{
    DMA_MEM_TO_MEM    = (0x00),
    DMA_MEM_TO_PERI   = (0x01),
    DMA_PERI_TO_MEM   = (0x02),
    DMA_PERI_TO_PERI  = (0x03),

} EN_DMA_WORK_MODE_T;

//=============================================================================
// DMA_CFG[17] DMA_PRIORITY_SEL Define
#define DMA_PRIORITY_SEL_SHIFT             (17)
#define DMA_PRIORITY_SEL_MSK               ((0x01 << 1) - 1)

typedef enum
{
    DMA_PRIO_LEVEL_LOW    = (0x00),
    DMA_PRIO_LEVEL_HIGH   = (0x01),

} EN_DMA_PRIORITY_T;

//=============================================================================
// DMA_CFG[16] DMA_CIRC_EN Define
#define DMA_CIRC_EN_SHIFT                  (16)
#define DMA_CIRC_EN_MSK                    ((0x01 << 1) - 1)

typedef enum
{
    DMA_NORM     = (0x00),
    DMA_CIRC     = (0x01),

} EN_DMA_MODE_T;

//=============================================================================
// DMA_CFG[15:0] DMA_LENGTH_VAL Define
#define DMA_LENGTH_VAL_SHIFT               (0)
#define DMA_LENGTH_VAL_MSK                 ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x10] DMA_TOTAL_LEN Register
//=====================================================================================================================
#define DMA_TOTAL_LEN_SHIFT                (0)
#define DMA_TOTAL_LEN_MSK                  (WORD_MSK)


//=====================================================================================================================
// [0x14] DMA_SRC_ADDR Register
//=====================================================================================================================
#define DMA_SRC_ADDR_SHIFT                 (0)
#define DMA_SRC_ADDR_MSK                   ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x18] DMA_DST_ADDR Register
//=====================================================================================================================
#define DMA_DST_ADDR_SHIFT                 (0)
#define DMA_DST_ADDR_MSK                   ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x1C] DMA_TRANS_CNT Register
//=====================================================================================================================
#define DMA_TRANS_CNT_SHIFT                (0)
#define DMA_TRANS_CNT_MSK                  ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x24] DMA_TIMEOUT Register
//=====================================================================================================================
//=============================================================================
// DMA_TIMEOUT[9:8] DMA_TIMEOUT_UNIT Define
#define DMA_TIMEOUT_UNIT_SHIFT             (8)
#define DMA_TIMEOUT_UNIT_MSK               ((0x01 << 2) - 1)

typedef enum
{
    EN_DMA_TIMEOUT_UNIT_1US      = (0x00),
    EN_DMA_TIMEOUT_UNIT_10US     = (0x01),
    EN_DMA_TIMEOUT_UNIT_100US    = (0x02),
    EN_DMA_TIMEOUT_UNIT_1000US   = (0x03)

} EN_DMA_TIMEOUT_UNIT_T;

#define IS_VALID_DMA_TIMEOUT_UNIT(UNIT)  (EN_DMA_TIMEOUT_UNIT_1000US >= UNIT)

//=============================================================================
// DMA_TIMEOUT[7:0] DMA_TIMEOUT_VAL Define
#define DMA_TIMEOUT_VAL_SHIFT              (0)
#define DMA_TIMEOUT_VAL_MSK                ((0x01 << 8) - 1)

typedef enum
{
    DMA_TIMEOUT_MAX_1US      = (DMA_TIMEOUT_VAL_MSK * 1U),
    DMA_TIMEOUT_MAX_10US     = (DMA_TIMEOUT_VAL_MSK * 10U),
    DMA_TIMEOUT_MAX_100US    = (DMA_TIMEOUT_VAL_MSK * 100U),
    DMA_TIMEOUT_MAX_1000US   = (DMA_TIMEOUT_VAL_MSK * 1000U)

} EN_DMA_TIMEOUT_MAX_T;

#define IS_VALID_DMA_TIMEOUT(TIMEOUT)    (DMA_TIMEOUT_MAX_1000US >= TIMEOUT)


//=====================================================================================================================
// [0x28] DMA_PERI_SEL Register
//=====================================================================================================================
//=============================================================================
// DMA_PERI_SEL[5:0] DMA_PERI_SEL Define
#define DMA_PERI_SEL_SHIFT                 (0)
#define DMA_PERI_SEL_MSK                   ((0x01 << 6) - 1)

typedef enum
{
    DMA_PERI_UART0_TX    = 0,
    DMA_PERI_UART0_RX    = 1,
    DMA_PERI_UART1_TX    = 2,
    DMA_PERI_UART1_RX    = 3,
    DMA_PERI_UART2_TX    = 4,
    DMA_PERI_UART2_RX    = 5,
    DMA_PERI_I2C0_TX     = 6,
    DMA_PERI_I2C0_RX     = 7,
    DMA_PERI_I2C1_TX     = 8,
    DMA_PERI_I2C1_RX     = 9,
    DMA_PERI_I2C2_TX     = 10,
    DMA_PERI_I2C2_RX     = 11,
    DMA_PERI_SPI0_TX     = 12,
    DMA_PERI_SPI0_RX     = 13,
    DMA_PERI_SPI1_TX     = 14,
    DMA_PERI_SPI1_RX     = 15,
    DMA_PERI_AUDIO0_RX   = 16,
    DMA_PERI_TRNG_RX     = 17,
    DMA_PERI_GTIM0_CHA   = 18,
    DMA_PERI_GTIM0_CHB   = 19,
    DMA_PERI_GTIM1_CHA   = 20,
    DMA_PERI_GTIM1_CHB   = 21,
    DMA_PERI_GTIM2_CHA   = 22,
    DMA_PERI_GTIM2_CHB   = 23,
    DMA_PERI_GTIM3_CHA   = 24,
    DMA_PERI_GTIM3_CHB   = 25,

    DMA_PERI_MORX_RX     = 28,
    DMA_PERI_ADC0_RX     = 29,
    DMA_PERI_QSPI0_TX    = 30,
    DMA_PERI_QSPI0_RX    = 31,
    DMA_PERI_QSPI1_TX    = 32,
    DMA_PERI_QSPI1_RX    = 33,

    DMA_PERI_I2S_TX      = 38,
    DMA_PERI_I2S_RX      = 39,
    DMA_PERI_AUDIO1_RX   = 40,
    DMA_PERI_ADC1_RX     = 41,

} EN_DMA_PERI_SEL_T;

#define IS_VALID_DMA_PERI_SEL(SEL)    (DMA_PERI_ADC1_RX >= (SEL))


//=====================================================================================================================
// [0x2C] DMA_INTERVAL_TX_CFG
//=====================================================================================================================
//=============================================================================
// DMA_INTERVAL_TX_CFG[16] DMA_INTERVAL_TX_EN Define
#define DMA_INTERVAL_TX_EN_SHIFT           (16)
#define DMA_INTERVAL_TX_EN_MSK             ((0x01 << 1) - 1)

//=============================================================================
// DMA_INTERVAL_TX_CFG[15:0] DMA_TX_INDEX Define
#define DMA_TX_INDEX_SHIFT                 (0)
#define DMA_TX_INDEX_MSK                   ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x30](WO) DMA_CIRC_DATA_READY
//=====================================================================================================================
//=============================================================================
// DMA_CIRC_DATA_READY[0] DMA_CIRC_DATA_READY Define
#define DMA_CIRC_DATA_READY_SHIFT          (0)
#define DMA_CIRC_DATA_READY_MSK            ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x34] DMA_INT_SEL Register
//=====================================================================================================================
//=============================================================================
// DMA_INT_SEL[2:0] DMA_CH0_INT_SEL Define
#define DMA_CH0_INT_SEL_SHIFT              (0)
#define DMA_CH0_INT_SEL_MSK                ((0x01 << 3) - 1)

#define DMA_INT_SEL_SHIFT                  (0)
#define DMA_INT_SEL_MSK                    ((0x01 << 3) - 1)

#ifdef __MAIN_PROCESSOR
typedef enum
{
    DMA_INT0    = 0,
    DMA_INT1    = 1,
    DMA_INT2    = 2,
    DMA_INT3    = 3,
    DMA_INT4    = 4,
    DMA_INT5    = 5,
    DMA_INT6    = 6,
    DMA_INT7    = 7,

} EN_DMA_INT_T;

#define DMA_INT_MAX (8)
#else //__CO_PROCESSOR
typedef enum
{
    DMA_INT4    = 4,
    DMA_INT5    = 5,
    DMA_INT6    = 6,
    DMA_INT7    = 7,

} EN_DMA_INT_T;

#define DMA_INT_MAX (8)

#endif

#define IS_VALID_DMA_INT(INT)    ((INT) < DMA_INT_MAX)


//=====================================================================================================================
// [0x38] DMA_PERI_2_PERI_SEL
//=====================================================================================================================
//=============================================================================
// DMA_PERI_2_PERI_SEL[13:8] DMA_PERI_SRC_SEL Define
#define DMA_PERI_SRC_SEL_SHIFT             (8)
#define DMA_PERI_SRC_SEL_MSK               ((0x01 << 6) - 1)

//=============================================================================
// DMA_PERI_2_PERI_SEL[5:0] DMA_PERI_DST_SEL Define
#define DMA_PERI_DST_SEL_SHIFT             (0)
#define DMA_PERI_DST_SEL_MSK               ((0x01 << 6) - 1)


//=====================================================================================================================
// [0x3C] DMA_RAM_CTRL
//=====================================================================================================================
//=============================================================================
// DMA_RAM_CTRL[31:0] DMA_RAM_CTRL Define
#define DMA_RAM_CTRL_CFG                   (0x50)



#ifdef __cplusplus
}
#endif

#endif /* __REG_DMA_H__ */


