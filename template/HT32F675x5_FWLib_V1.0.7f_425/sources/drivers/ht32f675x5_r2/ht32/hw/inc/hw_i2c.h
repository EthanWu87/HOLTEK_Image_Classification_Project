/*************************************************************************************************************
 * @file    hw_i2c.h
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



#ifndef __HW_I2C_H__
#define __HW_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef enum
{
    I2C_BAUDRATE_MIN     = ( 0x00 ),
    I2C_BAUDRATE_100K    = ( 100 ),
    I2C_BAUDRATE_400K    = ( 400 ),
    I2C_BAUDRATE_MAX     = ( I2C_BAUDRATE_400K )

} EN_I2C_BARDRATE_T;

typedef enum
{
    I2C_DIV_100K         = ( 31 ),
    I2C_DIV_400K         = ( 7 ),

} EN_I2C_DIVISOR_T;

typedef union
{
    uint32_t u32Cfg;

    struct
    {
        uint32_t u16ClkDiv      : 16;   /**< I2C master clock prescale register */
        uint32_t u8StretchEn    : 1;    /**< I2C master clock stretching enable */
        uint32_t u8AddrMode     : 1;    /**< I2C master addr mode, 1:10bit, 0:7bit */
        uint32_t u8TrxMode      : 2;    /**< I2C read or write mode **/
        uint32_t u8Enable       : 1;    /**< I2C master enable */

    } stCfg;

} unI2CMasterCfg_t, *punI2CMasterCfg_t;

typedef struct
{
    uint32_t u32BaudRate;  // I2C Clk, unit is KHz
    uint16_t u16SlaveAddr;
    unI2CMasterCfg_t unCfg;

} stI2cMasterInit_t, *pstI2cMasterInit_t;

typedef union
{
    uint32_t u32I2cCfg;

    struct
    {
        uint32_t u8Enable       : 1;    /**< I2C slave enable */
        uint32_t u8AddrMode     : 1;    /**< I2C master addr mode, 1:10bit, 0:7bit */
        uint32_t u8StretchEn    : 1;    /**< I2C master clock stretching enable */
        uint32_t u8I2cMode      : 1;    /**< I2C master or slave mode **/

    } stI2cCfg;

} unI2CSlaveCfg_t, *punI2CSlaveCfg_t;

typedef struct
{
    uint16_t u16SlaveAddr;
    unI2CSlaveCfg_t unCfg;

} stI2cSlaveInit_t, *pstI2cSlaveInit_t;

typedef enum
{
    ONE_BYTE    = 1,
    TWO_BYTE    = 2,
    THREE_BYTE  = 3,
    FOUR_BYTE   = 4,

} EN_I2C_SLAVE_REG_LEN_T;

#define IS_VALID_I2C_SLAVE_REG_LEN( LEN )  ( ((LEN) == ONE_BYTE)   || \
                                             ((LEN) == TWO_BYTE)   || \
                                             ((LEN) == THREE_BYTE) || \
                                             ((LEN) == FOUR_BYTE) )




/**
 * @brief  Initializes the I2C mode according to the specified parameters in
 *         the stI2CInitType_t and create the associated handle.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  pstInitType: Pointer to a stI2CInit_t structure that contains I2C configuation and baudrate.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_init(stI2C_Handle_t* pstI2C, stI2cMasterInit_t* pstInitType);


/**
 * @brief  Enable I2C master function.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_enable(stI2C_Handle_t* pstI2C);


/**
 * @brief  Disable I2C master function.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_disable(stI2C_Handle_t* pstI2C);


/**
 * @brief  Set I2C TRX mode by write bits I2C_TRX_MODE in I2C_CTRL_CFG register.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  enTrxMode: Which work mode will be write to I2C_CTRL_CFG, See EN_I2C_TRX_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_set_trx_mode(stI2C_Handle_t* pstI2C, EN_I2C_MASTER_MODE_T enTrxMode);


/**
 * @brief  Set i2c slave address mode. 7bit or 10bit.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  enMode: I2C address mode, @ref EN_I2C_ADDR_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_set_addr_mode(stI2C_Handle_t* pstI2C, EN_I2C_ADDR_MODE_T enMode);


/**
 * @brief  Enable i2c stretch clock when as master mode.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_enable_stretch(stI2C_Handle_t *pstI2C);


/**
 * @brief  Disable i2c stretch clock when as master mode.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_disable_stretch(stI2C_Handle_t *pstI2C);


/**
 * @brief  Set I2C baudrate by write I2C_CLK_CFG register with corresponding clk division value.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u32Rate: I2C speeds, Unit is Hz
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_set_speed(stI2C_Handle_t* pstI2C, uint32_t u32Rate);


/**
 * @brief  Set i2c rx fifo full value when as master. The range of value is [0:15].
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u8Val: RX fifo full value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_set_rxfifo_full_value(stI2C_Handle_t* pstI2C, uint8_t u8Val);


/**
 * @brief  Initializes the I2C mode according to the specified parameters in
 *         the unI2CSlaveCfg_t and create the associated handle.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  punCfg: Pointer to a unI2CSlaveCfg_t structure that contains I2C configuation.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_slave_init(stI2C_Handle_t* pstI2C, unI2CSlaveCfg_t* punCfg);


/**
 * @brief  Enable I2C slave function.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_slave_enable(stI2C_Handle_t* pstI2C);


/**
 * @brief  Disable I2C slave function.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_slave_disable(stI2C_Handle_t* pstI2C);


/**
 * @brief  Set i2c own address mode. 7bit or 10bit.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  enMode: I2C address mode, @ref EN_I2C_ADDR_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_slave_set_addr_mode(stI2C_Handle_t* pstI2C, EN_I2C_ADDR_MODE_T enMode);


/**
 * @brief  Enable i2c stretch clock when as slave mode.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_slave_enable_stretch(stI2C_Handle_t *pstI2C);


/**
 * @brief  Disable i2c stretch clock when as slave mode.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_slave_disable_stretch(stI2C_Handle_t *pstI2C);


/**
 * @brief  Set I2C mode to master or slave.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  enMode: I2C mode, @ref EN_I2C_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_set_mode(stI2C_Handle_t* pstI2C, EN_I2C_MODE_T enMode);


/**
 * @brief  Set i2c address.
 *         When i2c as master mode, it means target slave address.
 *         When i2c as slave mode, it means own address.
 *         Support 7bit or 10bit address mode.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u16I2cAddr: I2C address.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_set_addr(stI2C_Handle_t* pstI2C, uint16_t u16I2cAddr);


/**
 * @brief  Set I2C TX FIFO threshold value.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u8Thld: Threshold for I2C TX FIFO.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_set_txfifo_thld(stI2C_Handle_t* pstI2C, uint8_t u8Thld);


/**
 * @brief  Set I2C RX FIFO threshold value.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u8Thld: Threshold for I2C RX FIFO.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_set_rxfifo_thld(stI2C_Handle_t* pstI2C, uint8_t u8Thld);


/**
 * @brief  Set i2c rxfifo timeout threshold. The range of value is [0:255].Unit is SCL period when as master.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2
 * @param  u8TimeoutThld: rxfifo timeout threshold.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_set_timeout_thld(stI2C_Handle_t* pstI2C, uint8_t u8TimeoutThld);


/**
 * @brief  Get I2C TX FIFO counter by read the I2C_TXFIFO_CNT register.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  pu8Cnt: Counter of bytes of i2c tx fifo.
 * @return status: @ref EN_ERR_STA_T.
 */
uint8_t rom_hw_i2c_get_txfifo_cnt(stI2C_Handle_t* pstI2C, uint8_t* pu8Cnt);


/**
 * @brief  Get I2C RX FIFO counter by read the I2C_RXFIFO_CNT register.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  pu8Cnt: Counter of bytes of i2c rx fifo.
 * @return status: @ref EN_ERR_STA_T.
 */
uint8_t rom_hw_i2c_get_rxfifo_cnt(stI2C_Handle_t* pstI2C, uint8_t* pu8Cnt);


/**
 * @brief  Get indicated I2C interrupt flag(status) by read the I2C_INT_FLAG register.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  pu16IntMsk: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
uint16_t rom_hw_i2c_get_interrupt_flag(stI2C_Handle_t* pstI2C, uint16_t* pu16IntMsk);


/**
 * @brief  Clear indicated I2C interrupt flag(status) by write the I2C_INT_CLR register.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u16Msk: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_clear_interrupt_flag(stI2C_Handle_t* pstI2C, uint16_t u16Msk);


/**
 * @brief  Enable indicated I2C interrupt byt write I2C_INT_EN register with indicated bits.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u16IntEn: Indicate which interrupt will be enable,
 *                   bit-1 means enable
 *                   bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_enable_interrupt(stI2C_Handle_t* pstI2C, uint16_t u16IntEn);


/**
 * @brief  Disable indicated I2C interrupt byt write I2C_INT_CLR register with indicated bits.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u16IntDis: Indicate which interrupt will be enable,
 *                    bit-1 means disable
 *                    bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_disable_interrupt(stI2C_Handle_t* pstI2C, uint16_t u16IntDis);


/**
 * @brief  Write multiple bytes to I2C slave.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  pu8TxBuf: Pointer to a buffer which used to write.
 * @param  u16Len: Length of write data
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_write(stI2C_Handle_t* pstI2C, uint8_t* pu8TxBuf, uint16_t u16Len);


/**
 * @brief  Read multiple bytes from I2C slave, no reg addr.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u16Len: Length of read data
 * @param  pu8RxBuf: Pointer to a buffer which used to save the read data.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_read(stI2C_Handle_t* pstI2C, uint8_t* pu8RxBuf, uint16_t u16Len);


/**
 * @brief  Write multiple bytes to I2C master.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  pu8TxBuf: Pointer to a buffer which used to write.
 * @param  u16Len: Length of write data
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_slave_write(stI2C_Handle_t* pstI2C, uint8_t* pu8TxBuf, uint16_t u16Len);


/**
 * @brief  Write multiple bytes to I2C slave to specified register.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u32RegAddr: I2C slave register address.
 * @param  enRegLen: I2C slave register address length, @ref EN_I2C_SLAVE_REG_LEN_T.
 * @param  pu8TxBuf: Pointer to a buffer which used to write.
 * @param  u16Len: Length of write data, unit is byte.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_reg_write(stI2C_Handle_t* pstI2C, uint32_t u32RegAddr, EN_I2C_SLAVE_REG_LEN_T enRegLen,
                                                uint8_t* pu8TxBuf, uint16_t u16Len);


/**
 * @brief  Read multiple bytes to I2C slave from specified register.
 * @param  pstI2C: I2C handle, Should be I2C0 / I2C1 / I2C2.
 * @param  u32RegAddr: I2C slave register address.
 * @param  enRegLen: I2C slave register address length, @ref EN_I2C_SLAVE_REG_LEN_T.
 * @param  u16Len: Length of read data, unit is byte.
 * @param  pu8RxBuf: Pointer to a buffer which used to save the read data.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_i2c_master_reg_read(stI2C_Handle_t* pstI2C, uint32_t u32RegAddr, EN_I2C_SLAVE_REG_LEN_T enRegLen,
                                               uint8_t* pu8RxBuf, uint16_t u16Len);


#ifdef __cplusplus
}
#endif

#endif /* _HW_I2C_H_ */


