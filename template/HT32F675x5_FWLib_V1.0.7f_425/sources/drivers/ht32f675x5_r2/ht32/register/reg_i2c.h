/*************************************************************************************************************
 * @file    reg_i2c.h
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



#ifndef __REG_I2C_H__
#define __REG_I2C_H__



#ifdef __cplusplus
extern "C" {
#endif

//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __OM  uint32_t I2C_TX_FIFO;             /* [0x00](WO) */
    __IM  uint32_t I2C_RX_FIFO;             /* [0x04](RO) */
    __IM  uint32_t I2C_INT_FLAG;            /* [0x08](RO) */
    __IOM uint32_t I2C_INT_EN;              /* [0x0C](RW) */
    __OM  uint32_t I2C_INT_CLR;             /* [0x10](WO) */
    __IOM uint32_t I2C_RXFIFO_THLD;         /* [0x14](RW) */
    __IOM uint32_t I2C_TXFIFO_THLD;         /* [0x18](RW) */
    __IOM uint32_t I2C_RX_TIMEOUT_THLD;     /* [0x1C](RW) */
    __IOM uint32_t I2C_TXFIFO_IDLE_DATA;    /* [0x20](RW) */
    __IOM uint32_t I2C_MASTER_CFG;          /* [0x24](RW) */
    __IOM uint32_t I2C_ADDRESS;             /* [0x28](RW) */
    __IOM uint32_t I2C_SLAVE_CFG;           /* [0x2C](RW) */
    __IM  uint32_t I2C_SLAVE_STATUS;        /* [0x30](RO) */
    __IM  uint32_t I2C_RXFIFO_CNT;          /* [0x34](RO) */
    __IM  uint32_t I2C_TXFIFO_CNT;          /* [0x38](RO) */
    __IM  uint32_t I2C_MASTER_STATUS;       /* [0x3C](RO) */
    __OM  uint32_t I2C_RXFIFO_CLR;          /* [0x40](WO) */
    __OM  uint32_t I2C_TXFIFO_CLR;          /* [0x44](WO) */
    __OM  uint32_t I2C_MASTER_CMD;          /* [0x48](WO) */
    __OM  uint32_t I2C_SLAVE_CMD;           /* [0x4C](WO) */
    __IOM uint32_t I2C_RXFIFO_FULL_VAL;     /* [0x50](RW) */
    __IOM uint32_t I2C_EXT_CG_EN;           /* [0x54](RW) */

} stI2C_Handle_t, *pstI2C_Handle_t;

#define IS_VALID_I2C_HANDLE(pstI2C)    ((I2C0) == (pstI2C) \
                                     || (I2C1) == (pstI2C) \
                                     || (I2C2) == (pstI2C) \
                                     || (I2C3) == (pstI2C) )


//=====================================================================================================================
// [0x00] I2C_TX_FIFO
//=====================================================================================================================
#define I2C_TX_FIFO_SHIFT                  (0)
#define I2C_TX_FIFO_MSK                    ((0x01 << 8) - 1)


//=====================================================================================================================
// [0x04] I2C_RX_FIFO
//=====================================================================================================================
#define I2C_RX_FIFO_SHIFT                  (0)
#define I2C_RX_FIFO_MSK                    ((0x01 << 8) - 1)
#define I2C_RX_FIFO_MAX                    (16)


//=====================================================================================================================
// [0x08~0x10] I2C_INT_FLAG / I2C_INT_EN  / I2C_INT_CLR
//=====================================================================================================================
#define I2C_SLAVE_NOT_READY_RECV_SHIFT     (15)
#define I2C_SLAVE_NOT_READY_SEND_SHIFT     (14)
#define I2C_TX_FINISHED_SHIFT              (13)
#define I2C_SLAVE_ADDR_MATCH_SHIFT         (12)
#define I2C_SLAVE_BUS_ERROR_SHIFT          (11)
#define I2C_MASTER_ARBITRATE_LOST_SHIFT    (10)
#define I2C_MASTER_TRANSMIT_DONE_SHIFT     (9) /* master receive or transmitter completed flag */
#define I2C_RXFIFO_EMPTY_SHIFT             (8)
#define I2C_RXFIFO_NOT_EMPTY_SHIFT         (7)
#define I2C_RXFIFO_FULL_SHIFT              (6)
#define I2C_RXFIFO_OVER_THLD_SHIFT         (5)
#define I2C_TXFIFO_WRITE_FULL_SHIFT        (4)/* transmit FIFO over write when transmit FIFO full  */
#define I2C_TXFIFO_READ_EMPTY_SHIFT        (3)/* transmit FIFO over read when transmit FIFO empty  */
#define I2C_TXFIFO_EMPTY_SHIFT             (2)
#define I2C_TXFIFO_UNDER_THLD_SHIFT        (1)
#define I2C_RX_TIMEOUT_SHIFT               (0)

typedef enum
{
    I2C_INT_RXTIME_OUT              = (0x01 << I2C_RX_TIMEOUT_SHIFT),
    I2C_INT_TXFIFO_UNDER_THLD       = (0x01 << I2C_TXFIFO_UNDER_THLD_SHIFT),
    I2C_INT_TXFIFO_EMPTY            = (0x01 << I2C_TXFIFO_EMPTY_SHIFT),
    I2C_INT_TXFIFO_READ_EMPTY       = (0x01 << I2C_TXFIFO_READ_EMPTY_SHIFT),

    I2C_INT_TXFIFO_WRITE_FULL       = (0x01 << I2C_TXFIFO_WRITE_FULL_SHIFT),
    I2C_INT_RXFIFO_OVER_THLD        = (0x01 << I2C_RXFIFO_OVER_THLD_SHIFT),
    I2C_INT_RXFIFO_FULL             = (0x01 << I2C_RXFIFO_FULL_SHIFT),
    I2C_INT_RXFIFO_NOT_EMPTY        = (0x01 << I2C_RXFIFO_NOT_EMPTY_SHIFT),

    I2C_INT_RXFIFO_EMPTY            = (0x01 << I2C_RXFIFO_EMPTY_SHIFT),
    I2C_INT_MASTER_TRANSMIT_DONE    = (0x01 << I2C_MASTER_TRANSMIT_DONE_SHIFT),
    I2C_INT_MASTER_ARBITRATE_LOST   = (0x01 << I2C_MASTER_ARBITRATE_LOST_SHIFT),
    I2C_INT_SLAVE_BUS_ERROR         = (0x01 << I2C_SLAVE_BUS_ERROR_SHIFT),

    I2C_INT_SLAVE_ADDR_MATCH        = (0x01 << I2C_SLAVE_ADDR_MATCH_SHIFT),
    I2C_INT_TX_FINISHED             = (0x01 << I2C_TX_FINISHED_SHIFT),
    I2C_INT_SLAVE_NOT_READY_SEND    = (0x01 << I2C_SLAVE_NOT_READY_SEND_SHIFT),
    I2C_INT_SLAVE_NOT_READY_RECV    = (0x01 << I2C_SLAVE_NOT_READY_RECV_SHIFT),

} EN_I2C_INT_FLAG_T;

#define I2C_INT_MASK                       (0xFFFF)


//=====================================================================================================================
// [0x14] I2C_RXFIFO_THLD Register
//=====================================================================================================================
#define I2C_RXFIFO_THLD_SHIFT              (0)
#define I2C_RXFIFO_THLD_MSK                ((0x01 << 5) - 1)
#define I2C_RXFIFO_THLD_DEFAULT            (8)
#define I2C_RXFIFO_THLD_MAX                (16)


//=====================================================================================================================
// [0x18] I2C_TXFIFO_THLD Register
//=====================================================================================================================
#define I2C_TXFIFO_THLD_SHIFT              (0)
#define I2C_TXFIFO_THLD_MSK                ((0x01 << 5) - 1)
#define I2C_TXFIFO_THLD_DEFAULT            (8)
#define I2C_TXFIFO_THLD_MAX                (16)


//=====================================================================================================================
// [0x1C]I2C_RX_TIMEOUT_THLD Register
//=====================================================================================================================
#define I2C_RX_TIMEOUT_THLD_SHIFT          (0) /* I2C rx time out threshold. Unit is SCL period when as master. */
#define I2C_RX_TIMEOUT_THLD_MSK            ((0x01 << 8) - 1)
#define I2C_RX_TIMEOUT_THLD_DEFAULT        (0xFF)


//=====================================================================================================================
// [0x20]I2C_TXFIFO_IDLE_DATA Register
//=====================================================================================================================
#define I2C_TXFIFO_IDLE_DATA_SHIFT         (0) /* read tfifo when tfifo empty, get tfifo_idle_data. */
#define I2C_TXFIFO_IDLE_DATA_MSK           ((0x01 << 8) - 1)
#define I2C_TXFIFO_IDLE_DATA_DEFAULT       (0xFF)


//=====================================================================================================================
// [0x24]I2C_MASTER_CFG Register
//=====================================================================================================================
#define I2C_MASTER_CFG_DEFAULT             (0x00000000)

//=============================================================================
// I2C_MASTER_CFG[20] I2C_MASTER_EN Define
#define I2C_MASTER_ENABLE_SHIFT            (20)
#define I2C_MASTER_ENABLE_MSK              ((0x01 << 1) - 1)

typedef enum
{
    I2C_DISABLE = 0x00,
    I2C_ENABLE  = 0x01,

} EN_I2C_ENABLE_T;

//=============================================================================
// I2C_MASTER_CFG[19:18] I2C_MASTER_MODE Define
#define I2C_MASTER_MODE_SHIFT              (18)
#define I2C_MASTER_MODE_MSK                ((0x01 << 2) - 1)

typedef enum
{
    I2C_MASTER_MODE_WRITE = 0x01,
    I2C_MASTER_MODE_READ  = 0x02,

} EN_I2C_MASTER_MODE_T;

/* This macro checks if MODE is a valid I2C master mode value */
#define IS_VALID_I2C_MASTER_MODE(MODE)   (((MODE) == I2C_MASTER_MODE_WRITE) || \
                                             ((MODE) == I2C_MASTER_MODE_READ))

//=============================================================================
// I2C_MASTER_CFG[17] I2C_MASTER_ADDR_MODE Define
#define I2C_MASTER_ADDR_MODE_SHIFT         (17)
#define I2C_MASTER_ADDR_MODE_MSK           ((0x01 << 1) - 1)

typedef enum
{
    I2C_ADDR_MODE_7_BITS   = 0x00,
    I2C_ADDR_MODE_10_BITS  = 0x01,

} EN_I2C_ADDR_MODE_T;

/* This macro checks if MODE is a valid I2C master addr mode value */
#define IS_VALID_I2C_ADDR_MODE(MODE)     (((MODE) == I2C_ADDR_MODE_7_BITS) || \
                                             ((MODE) == I2C_ADDR_MODE_10_BITS))

//=============================================================================
// I2C_MASTER_CFG[16] I2C_MASTER_STRETCH_EN Define
#define I2C_MASTER_STRETCH_EN_SHIFT        (16)
#define I2C_MASTER_STRETCH_EN_MSK          ((0x01 << 1) - 1)

typedef enum
{
    I2C_STRETCH_DISABLE   = 0x00,
    I2C_STRETCH_ENABLE    = 0x01,

} EN_I2C_STRETCH_EN_T;

/* This macro checks if MODE is a valid I2C master addr mode value */
#define IS_VALID_I2C_STRETCH_EN(MODE)    (((MODE) == I2C_STRETCH_DISABLE) || \
                                             ((MODE) == I2C_STRETCH_ENABLE))

//=============================================================================
// I2C_MASTER_CFG[15] I2C_CLK_DIV Define
#define I2C_CLK_DIV_SHIFT                  (0)
#define I2C_CLK_DIV_MSK                    ((0x01 << 15) - 1)


//=====================================================================================================================
// [0x28]I2C_ADDRESS Register
//=====================================================================================================================
#define I2C_ADDRESS_SHIFT                  (0)
#define I2C_ADDRESS_MSK                    ((0x01 << 10) - 1)


//=====================================================================================================================
// [0x2C]I2C_SLAVE_CFG Register
//=====================================================================================================================
#define I2C_SLAVE_CFG_DEFAULT              (0x00000000)

//=============================================================================
// I2C_SLAVE_CFG[3] I2C_MODE Define
#define I2C_MODE_SHIFT                     (3)
#define I2C_MODE_MSK                       ((0x01 << 1) - 1)

typedef enum
{
    I2C_MODE_SLAVE   = 0x00,
    I2C_MODE_MASTER  = 0x01,

} EN_I2C_MODE_T;

/* This macro checks if MODE is a valid I2C mode value */
#define IS_VALID_I2C_MODE(MODE)   (((MODE) == I2C_MODE_SLAVE) || \
                                      ((MODE) == I2C_MODE_MASTER))

//=============================================================================
// I2C_SLAVE_CFG[2] I2C_SLAVE_STRETCH_EN Define
#define I2C_SLAVE_STRETCH_EN_SHIFT         (2)
#define I2C_SLAVE_STRETCH_EN_MSK           ((0x01 << 1) - 1)

//=============================================================================
// I2C_SLAVE_CFG[1] I2C_SLAVE_ADDR_MODE Define
#define I2C_SLAVE_ADDR_MODE_SHIFT          (1)
#define I2C_SLAVE_ADDR_MODE_MSK            ((0x01 << 1) - 1)

//=============================================================================
// I2C_SLAVE_CFG[0] I2C_SLAVE_EN Define
#define I2C_SLAVE_ENABLE_SHIFT             (0)
#define I2C_SLAVE_ENABLE_MSK               ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x30]I2C_SLAVE_STATUS Register
//=====================================================================================================================
//=============================================================================
// I2C_SLAVE_STATUS[10] I2C_SLAVE_ Define
#define I2C_MASTER_READ_SHIFT              (10)
#define I2C_MASTER_READ_MSK                ((0x01 << 1) - 1)

//=============================================================================
// I2C_SLAVE_STATUS[9] I2C_SLAVE_ Define
#define I2C_MASTER_WRITE_SHIFT             (9)
#define I2C_MASTER_WRITE_MSK               ((0x01 << 1) - 1)

//=============================================================================
// I2C_SLAVE_STATUS[8] I2C_SLAVE_ Define
#define I2C_SLAVE_BUSY_SHIFT               (8)
#define I2C_SLAVE_BUSY_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// I2C_SLAVE_STATUS[7:5] I2C_SLAVE_ Define
#define I2C_SLAVE_BIT_CTR_STA_SHIFT        (5)
#define I2C_SLAVE_BIT_CTR_STA_MSK          ((0x01 << 3) - 1)

//=============================================================================
// I2C_SLAVE_STATUS[4:0] I2C_SLAVE_ Define
#define I2C_SLAVE_BYTE_CTR_STA_SHIFT       (0)
#define I2C_SLAVE_BYTE_CTR_STA_MSK         ((0x01 << 5) - 1)

typedef enum
{
    SLV_IDLE          = 0,
    SLV_ADDR1_RCV     = 1,
    SLV_ADDR1_NACK    = 2,
    SLV_ADDR1_ACK     = 3,
    SLV_ADDR2_RCV     = 4,
    SLV_ADDR2_ACK     = 5,
    SLV_ADDR2_NACK    = 6,
    DATA_RCV          = 7,
    SLV_DATA_ACK      = 8,
    SLV_DATA_NACK     = 9,
    DATA_SEND         = 10,
    MST_DATA_ACK      = 11,
    WIIT_STOP         = 12,
    NACK_STOP         = 13,
    SLV_ILLEGAL       = 14,
    FULL_STRETCH      = 15,
    EMPTY_STRETCH     = 16,

} EN_I2C_SLAVE_STA_T;


//========================================================================================================
// [0x34] I2C_RXFIFO_CNT Register
//=======================================================================================================
#define I2C_RXFIFO_CNT_SHIFT               (0)
#define I2C_RXFIFO_CNT_MSK                 ((0x01 << 5) - 1)
#define I2C_RXFIFO_CNT_MAX                 (16)

//========================================================================================================
// [0x38] I2C_TXFIFO_CNT Register
//=======================================================================================================
#define I2C_TXFIFO_CNT_SHIFT               (0)
#define I2C_TXFIFO_CNT_MSK                 ((0x01 << 5) - 1)
#define I2C_TXFIFO_CNT_MAX                 (16)


//=====================================================================================================================
// [0x3C]I2C_MASTER_STATUS Register
//=====================================================================================================================
//=============================================================================
// I2C_MASTER_STATUS[15] I2C_MASTER_STATUS_BUS Define
#define I2C_MASTER_STATUS_BUS_SHIFT        (15) /* i2c bus signal between start and stop when i2c master mode */
#define I2C_MASTER_STATUS_BUS_MSK          ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_STATUS[14] I2C_MASTER_STATUS_RCV_ACK Define
#define I2C_MASTER_STATUS_RCV_ACK_SHIFT    (14)
#define I2C_MASTER_STATUS_RCV_ACK_MSK      ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_STATUS[13] I2C_MASTER_STATUS_ARBITRATE_LOST Define
#define I2C_MASTER_STATUS_ARBITRATE_LOST_SHIFT (13)
#define I2C_MASTER_STATUS_ARBITRATE_LOST_MSK   ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_STATUS[12] I2C_MASTER_STATUS_TX_ING Define
#define I2C_MASTER_STATUS_TX_ING_SHIFT     (12)
#define I2C_MASTER_STATUS_TX_ING_MSK       ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_STATUS[11] I2C_MASTER_BYTE_TX_DONE Define
#define I2C_MASTER_BYTE_TX_DONE_SHIFT      (11)
#define I2C_MASTER_BYTE_TX_DONE_MSK        ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_STATUS[10] I2C_MASTER_CLK_STRETCH Define
#define I2C_MASTER_CLK_STRETCH_SHIFT       (10)
#define I2C_MASTER_CLK_STRETCH_MSK         ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_STATUS[9:5] I2C_MASTER_BIT_CTR_STA Define
#define I2C_MASTER_BIT_CTR_STA_SHIFT       (5)
#define I2C_MASTER_BIT_CTR_STA_MSK         ((0x01 << 5) - 1)

//=============================================================================
// I2C_MASTER_STATUS[4:0] I2C_MASTER_BYTE_CTR_STA Define
#define I2C_MASTER_BYTE_CTR_STA_SHIFT      (0)
#define I2C_MASTER_BYTE_CTR_STA_MSK        ((0x01 << 5) - 1)

typedef enum
{
    MST_IDLE              = 0,
    MST_START             = 1,
    MST_SEND_ADDR1        = 2,
    MST_SEND_RW_CMD       = 3,
    MST_RCV_ADDR1_ACK     = 4,
    MST_SEND_ADDR2        = 5,
    MST_RCV_ADDR2_ACK     = 6,
    MST_SNED_DATA         = 7,
    MST_RCV_DATA_ACK      = 8,
    MST_RCV_DATA          = 9,
    MST_SEND_DATA_ACK     = 10,
    MST_SEND_DATA_NACK    = 11,
    MST_STOP              = 12,
    MST_NACK_STRETCH      = 13,
    MST_EMPTY_STRETCH     = 14,
    MST_FULL_STRETCH      = 15,

} EN_I2C_MASTER_STA_T;


//========================================================================================================
// [0x40] I2C_RXFIFO_CLR Register
//=======================================================================================================
#define I2C_CLR_RXFIFO_SHIFT               (0)
#define I2C_CLR_RXFIFO_MSK                 ((0x01 << 1) - 1)


//========================================================================================================
// [0x44] I2C_TXFIFO_CLR Register
//=======================================================================================================
#define I2C_CLR_TXFIFO_SHIFT               (0)
#define I2C_CLR_TXFIFO_MSK                 ((0x01 << 1) - 1)


//========================================================================================================
// [0x48](WO) I2C_MASTER_CMD Register
//=======================================================================================================
#define I2C_MASTER_CMD_DEFAULT             (0x00000000)

//=============================================================================
// I2C_MASTER_CMD[5] I2C_MASTER_CMD_CLR_STATE Define
#define I2C_MASTER_CMD_CLR_STATE_SHIFT     (5)
#define I2C_MASTER_CMD_CLR_STATE_MSK       ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_CMD[4] I2C_MASTER_CMD_RESTART Define
#define I2C_MASTER_CMD_RESTART_SHIFT       (4)
#define I2C_MASTER_CMD_RESTART_MSK         ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_CMD[3] I2C_MASTER_CMD_NACK Define
#define I2C_MASTER_CMD_NACK_SHIFT          (3)
#define I2C_MASTER_CMD_NACK_MSK            ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_CMD[2] I2C_MASTER_CMD_ACK Define
#define I2C_MASTER_CMD_ACK_SHIFT           (2)
#define I2C_MASTER_CMD_ACK_MSK             ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_CMD[1] I2C_MASTER_CMD_STOP Define
#define I2C_MASTER_CMD_STOP_SHIFT          (1)
#define I2C_MASTER_CMD_STOP_MSK            ((0x01 << 1) - 1)

//=============================================================================
// I2C_MASTER_CMD[0] I2C_MASTER_CMD_START Define
#define I2C_MASTER_CMD_START_SHIFT         (0)
#define I2C_MASTER_CMD_START_MSK           ((0x01 << 1) - 1)


//========================================================================================================
// [0x4C] I2C_SLAVE_CMD Register
//=======================================================================================================
//=============================================================================
// I2C_SLAVE_CMD[3] I2C_SLAVE_CMD_CLR_STATE Define
#define I2C_SLAVE_CMD_CLR_STATE_SHIFT      (3)
#define I2C_SLAVE_CMD_CLR_STATE_MSK        ((0x01 << 1) - 1)

//=============================================================================
// I2C_SLAVE_CMD[2] I2C_SLAVE_CMD_IDLE Define
#define I2C_SLAVE_CMD_IDLE_SHIFT           (2)
#define I2C_SLAVE_CMD_IDLE_MSK             ((0x01 << 1) - 1)

//=============================================================================
// I2C_SLAVE_CMD[1] I2C_SLAVE_CMD_ACK Define
#define I2C_SLAVE_CMD_ACK_SHIFT            (1)
#define I2C_SLAVE_CMD_ACK_MSK              ((0x01 << 1) - 1)

//=============================================================================
// I2C_SLAVE_CMD[0] I2C_SLAVE_CMD_NACK Define
#define I2C_SLAVE_CMD_NACK_SHIFT           (0)
#define I2C_SLAVE_CMD_NACK_MSK             ((0x01 << 1) - 1)


//========================================================================================================
// [0x50] I2C_RXFIFO_FULL_VAL Register
//=======================================================================================================
#define I2C_RXFIFO_FULL_VAL_SHIFT          (0)
#define I2C_RXFIFO_FULL_VAL_MSK            ((0x01 << 5) - 1)
#define I2C_RXFIFO_FULL_VAL_MAX            (16)


//========================================================================================================
// [0x54] I2C_EXT_CG_EN Register
//=======================================================================================================
#define I2C_EXT_CG_EN_SHIFT                (0)
#define I2C_EXT_CG_EN_MSK                  ((0x01 << 1) - 1)


#ifdef __cplusplus
}
#endif

#endif /* __REG_I2C_H__ */


