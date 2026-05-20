/*************************************************************************************************************
 * @file    hw_spi.h
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


#ifndef __HW_SPI_H__
#define __HW_SPI_H__


#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum
{
    EN_SPI_BAUDRATE_31P25    = (32),
    EN_SPI_BAUDRATE_100K     = (100),
    EN_SPI_BAUDRATE_500K     = (500),
    EN_SPI_BAUDRATE_1M       = (1000),
    EN_SPI_BAUDRATE_2M       = (2000),
    EN_SPI_BAUDRATE_4M       = (4000),
    EN_SPI_BAUDRATE_8M       = (8000),
    EN_SPI_BAUDRATE_12M      = (12000),
    EN_SPI_BAUDRATE_16M      = (16000),
    EN_SPI_BAUDRATE_24M      = (24000),
    EN_SPI_BAUDRATE_32M      = (32000),
    EN_SPI_BAUDRATE_48M      = (48000),
    EN_SPI_BAUDRATE_64M      = (64000),
    EN_SPI_BAUDRATE_MIN      = (EN_SPI_BAUDRATE_31P25),
    EN_SPI_BAUDRATE_MAX      = (EN_SPI_BAUDRATE_64M)

} EN_SPI_BARDRATE_T;

typedef enum
{
    // SPI Clock Divison When SYS_CLK is 16MHz
    EN_SPI_CLK_DIV_16M_31P25    = (255),
    EN_SPI_CLK_DIV_16M_100K     = (79),
    EN_SPI_CLK_DIV_16M_500K     = (15),
    EN_SPI_CLK_DIV_16M_1M       = (7),
    EN_SPI_CLK_DIV_16M_2M       = (3),
    EN_SPI_CLK_DIV_16M_4M       = (1),
    EN_SPI_CLK_DIV_16M_8M       = (0),

    // SPI Clock Divison When SYS_CLK is 32MHz
    EN_SPI_CLK_DIV_32M_100K     = (159),
    EN_SPI_CLK_DIV_32M_500K     = (31),
    EN_SPI_CLK_DIV_32M_1M       = (15),
    EN_SPI_CLK_DIV_32M_2M       = (7),
    EN_SPI_CLK_DIV_32M_4M       = (3),
    EN_SPI_CLK_DIV_32M_8M       = (1),
    EN_SPI_CLK_DIV_32M_16M      = (0),

    // SPI Clock Divison When SYS_CLK is 48MHz
    EN_SPI_CLK_DIV_48M_100K     = (239),
    EN_SPI_CLK_DIV_48M_500K     = (47),
    EN_SPI_CLK_DIV_48M_1M       = (23),
    EN_SPI_CLK_DIV_48M_2M       = (11),
    EN_SPI_CLK_DIV_48M_4M       = (5),
    EN_SPI_CLK_DIV_48M_8M       = (2),
    EN_SPI_CLK_DIV_48M_12M      = (1),
    EN_SPI_CLK_DIV_48M_24M      = (0),

    // SPI Clock Divison When SYS_CLK is 64MHz
    EN_SPI_CLK_DIV_64M_100K     = (319),
    EN_SPI_CLK_DIV_64M_500K     = (63),
    EN_SPI_CLK_DIV_64M_1M       = (31),
    EN_SPI_CLK_DIV_64M_2M       = (15),
    EN_SPI_CLK_DIV_64M_4M       = (7),
    EN_SPI_CLK_DIV_64M_8M       = (3),
    EN_SPI_CLK_DIV_64M_16M      = (1),

    // SPI Clock Divison When SYS_CLK is 96MHz
    EN_SPI_CLK_DIV_96M_100K     = (479),
    EN_SPI_CLK_DIV_96M_500K     = (95),
    EN_SPI_CLK_DIV_96M_1M       = (47),
    EN_SPI_CLK_DIV_96M_2M       = (23),
    EN_SPI_CLK_DIV_96M_4M       = (11),
    EN_SPI_CLK_DIV_96M_8M       = (5),
    EN_SPI_CLK_DIV_96M_12M      = (3),
    EN_SPI_CLK_DIV_96M_16M      = (2),
    EN_SPI_CLK_DIV_96M_24M      = (1),
    EN_SPI_CLK_DIV_96M_48M      = (0),

    // SPI Clock Divison When SYS_CLK is 128MHz
    EN_SPI_CLK_DIV_128M_100K    = (639),
    EN_SPI_CLK_DIV_128M_500K    = (127),
    EN_SPI_CLK_DIV_128M_1M      = (63),
    EN_SPI_CLK_DIV_128M_2M      = (31),
    EN_SPI_CLK_DIV_128M_4M      = (31),
    EN_SPI_CLK_DIV_128M_8M      = (7),
    EN_SPI_CLK_DIV_128M_16M     = (3),
    EN_SPI_CLK_DIV_128M_64M     = (0),

} EN_SPI_CLK_DIV_T;


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef union
{
    uint32_t u32SpiCfg;

    struct
    {
        uint32_t u8Enable       : 1;    /**< SPI_ENABLE */
        uint32_t u8Cpha         : 2;    /**< SPI clock phase and polarity*/
        uint32_t u8WorkMode     : 1;    /**< SPI Master or slave mode selection */
        uint32_t u8RxTimeOut    : 8;    /**< SPI rx time out threshold */
        uint32_t u8TrxMode      : 2;    /**< SPI trx mode **/
        uint32_t u8DataBits     : 2;    /**< SPI master mode csn frame size */
        uint32_t u8ByteWait     : 1;    /**< SPI byte wait en */
        uint32_t u8CsSwCtrl     : 1;    /**< SPI cs host ctrl */
        uint32_t u8CsMode       : 1;    /**< SPI cs host mode */

    } stSpiCfg;

} unSPICfg_t, *punSPICfg_t;

typedef struct
{
    uint32_t   u32ClkDiv;
    unSPICfg_t unSpiCfg;

} stSpiInit_t, *pstSpiInit_t;




/**
 * @brief  Deinitializes the SPI Module and reset the registers.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_deinit(stSPI_Handle_t* pstSPI);


/**
 * @brief  Initializes the SPI mode according to the specified parameters in
 *         the stSpiInitType_t and create the associated handle.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  pstInitType: Pointer to a stSpiInit_t structure that contains SPI configuation and baudrate.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_init(stSPI_Handle_t* pstSPI, stSpiInit_t* pstInitType);


/**
 * @brief  Get indicated spi interrupt flag(status) by read the SPI_INT_FLAG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  pu16IntMsk: Indicate which interrupt flag will be read.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_get_interrupt_flag(stSPI_Handle_t* pstSPI, uint16_t* pu16IntMsk);


/**
 * @brief  Clear indicated spi interrupt flag(status) by write the SPI_INT_CLR register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u16Msk: Indicate which flag will be cleared.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_clear_interrupt_flag(stSPI_Handle_t* pstSPI, uint16_t u16Msk);


/**
 * @brief  Enable indicated spi interrupt byt write SPI_INT_EN register with indicated bits.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u16IntEn: Indicate which interrupt will be enable,
 *                   bit-1 means enable
 *                   bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_enable_interrupt(stSPI_Handle_t* pstSPI, uint16_t u16IntEn);


/**
 * @brief  Disable indicated SPI interrupt by write SPI_INT_EN register with indicated bits.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u16IntDis: Indicate which interrupt will be disable
 *                    bit-1 means disable
 *                    bit-0 means no impact
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_disable_interrupt(stSPI_Handle_t* pstSPI, uint16_t u16IntDis);


/**
 * @brief  Set SPI clock divisor by write SPI_CLK_CFG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  enDiv: SPI clock divisor, SPI Master Speed = HCLK / 2 / (1 + enDiv). @ref EN_SPI_CLK_DIV_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_clk_divisor(stSPI_Handle_t* pstSPI, EN_SPI_CLK_DIV_T enDiv);


/**
 * @brief  Get SPI TX FIFO counter by read the SPI_TXFIFO_CNT register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  pu8Cnt: Counter of bytes of SPI tx fifo.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_get_txfifo_cnt(stSPI_Handle_t* pstSPI, uint8_t* pu8Cnt);


/**
 * @brief  Get SPI RX FIFO counter by read the SPI_RXFIFO_CNT register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  pu8Cnt: Counter of bytes of SPI rx fifo.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_get_rxfifo_cnt(stSPI_Handle_t* pstSPI, uint8_t* pu8Cnt);


/**
 * @brief  Set SPI Work mode by write bits SPI_WORK_MODE in SPI_CTRL_CFG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  enWorkMode: Which work mode will be write to SPI_CTRL_CFG, @ref EN_SPI_WORK_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_work_mode(stSPI_Handle_t* pstSPI, EN_SPI_WORK_MODE_T enWorkMode);


/**
 * @brief  Set SPI TRX mode by write bits SPI_TRX_MODE in SPI_CTRL_CFG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  enTrxMode: Which work mode will be write to SPI_CTRL_CFG, @ref EN_SPI_TRX_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_trx_mode(stSPI_Handle_t* pstSPI, EN_SPI_TRX_MODE_T enTrxMode);


/**
 * @brief  Set SPI CS work mode by write bits SPI_CS_MODE in SPI_CTRL_CFG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  enCsMode: Which CS work mode will be write to SPI_CTRL_CFG, @ref EN_SPI_CS_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_cs_mode(stSPI_Handle_t* pstSPI, EN_SPI_CS_MODE_T enCsMode);


/**
 * @brief  Set SPI CPOL and CPHA mode by write bits SPI_CPOL_CPHA in SPI_CTRL_CFG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  enType: SPI CPOL and CPHA mode, @ref EN_SPI_CPHA_TYPE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_cpha_cpol_mode(stSPI_Handle_t* pstSPI, EN_SPI_CPHA_TYPE_T enType);


/**
 * @brief  Enable SPI by write bits SPI_ENABLE in SPI_CTRL_CFG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_enable(stSPI_Handle_t* pstSPI);


/**
 * @brief  Disable SPI by write bits SPI_ENABLE in SPI_CTRL_CFG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_disable(stSPI_Handle_t* pstSPI);


/**
 * @brief  Set CS Pin as High level by set bit SPI_CS_SET as LEVEL_HI(1) in SPI_CTRL_CFG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_sw_set_cs(stSPI_Handle_t* pstSPI);


/**
 * @brief  Set CS Pin as LOW level by set bit SPI_CS_SET as LEVEL_LO(0) in SPI_CTRL_CFG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_sw_clr_cs(stSPI_Handle_t* pstSPI);


/**
 * @brief  Set SPI TX FIFO threshold value.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u8Thld: Threshold for SPI TX FIFO
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_txfifo_thld(stSPI_Handle_t* pstSPI, uint8_t u8Thld);


/**
 * @brief  Set SPI RX FIFO threshold value.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u8Thld: Threshold for SPI RX FIFO
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_rxfifo_thld(stSPI_Handle_t* pstSPI, uint8_t u8Thld);


/**
 * @brief  Set SPI RX Time out value,
 *         When SPI didn't receive data from SPI bus for a SPI_RX_TIMEOUT_THLD, it will set RX_TIMOUT_FLAG in
 *         SPI_INT_FLAG register and trig interrupt when SPI_INT_RXTIME_OUT was enabled.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u8Timeout: Threshold for SPI RX TIMOUT, unit is 1 byte.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_rx_timeout(stSPI_Handle_t* pstSPI, uint8_t u8Timeout);


/**
 * @brief  Set SPI Data Size when transmit and receive.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  enDataBits: The SPI data size, @ref EN_SPI_DATA_SIZE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_data_bits(stSPI_Handle_t* pstSPI, EN_SPI_DATA_SIZE_T enDataBits);


/**
 * @brief  SPI transmits idle data to external master when tfifo is empty.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u8Data: Idle data.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_idle_data(stSPI_Handle_t* pstSPI, uint8_t u8Data);


/**
 * @brief  SPI transmits idle data to external master when tfifo is empty.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u8Data: Idle data length.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_idle_data_len(stSPI_Handle_t* pstSPI, uint8_t u8Length);


/**
 * @brief  SPI in slave mode. If received byte (in the current frame) matches mread_length_cmd, SPI transmits one byte
 *         data (rfifio counter) for next frame to external master.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_enable_auto_rsp(stSPI_Handle_t* pstSPI);


/**
 * @brief  SPI in slave mode. If received byte (in the current frame) matches mread_length_cmd, SPI transmits one byte
 *         data (rfifio counter) for next frame to external master.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  enCsMode: SPI enable or disable will be write to SPI_AUTO_RSP_CFG, @ref EN_SPI_AUTO_RSP_EN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_disable_auto_rsp(stSPI_Handle_t* pstSPI);


/**
 * @brief  SPI in slave mode. If received byte (in the current frame) matches mread_length_cmd, SPI transmits one byte
 *         data (rfifio counter) for next frame to external master.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u8Cmd: mread_length_cmd.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_auto_rsp_cmd(stSPI_Handle_t* pstSPI, uint8_t u8Cmd);


/**
 * @brief   Byte-to-byte continuity or wait three clock cycles between bytes.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  enWordSpaceMdoe: @ref EN_SPI_WORD_SPACE_EN_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_set_byte_space(stSPI_Handle_t* pstSPI, EN_SPI_WORD_SPACE_EN_T enWordSpaceMdoe);


/**
 * @brief  Read a byte from SPI RX FIFO when RX FIFO is not empty.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  pu8Data: Pointer the data which be readed from SPI RX FIFO register.
 * @return status: @ref EN_ERR_STA_T.
 */
//extern EN_ERR_STA_T rom_hw_spi_read_rxfifo_byte(stSPI_Handle_t* pstSPI, uint8_t* pu8Data);


/**
 * @brief  Write a byte data to SPI bus bye write one byte data to SPI_TX_FIFO when SPI_TX_FIFO is not full.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  pu8Data: The data which should be send out to SPI bus.
 * @return status: @ref EN_ERR_STA_T.
 */
//extern EN_ERR_STA_T rom_hw_spi_write_txfifo_byte(stSPI_Handle_t* pstSPI, uint8_t u8TxData);


/**
 * @brief  Send a byte data to SPI bus bye write one byte data to SPI_TX_FIFO when SPI_TX_FIFO is not full.
 *         Waiting until the RX finished when bit RX_FINISHED be set in SPI_INT_FLAG register.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  u8TxData: The data which should be send out to SPI bus.
 * @param  pu8RxData: The data which should be receive from SPI bus.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_spi_trx_byte(stSPI_Handle_t* pstSPI, uint8_t u8TxData, uint8_t* pu8RxData);


/**
 * @brief  Send a data buffer to SPI bus with indicated length, and receive the same length of data.
 * @param  pstSPI: SPI handle, Should be SPI0 / SPI1.
 * @param  pu8TxBuf: Point to tx buffer This arguments can set to NULL, when SPI work at RX_ONLY mode.
 * @param  pu8RxBuf: Point to rx buffer. This arguments can set to NULL, when SPI work at TX_ONLY mode.
 * @param  u16TxLen: The Length which will be send out.
 * @return status: @ref EN_ERR_STA_T.
 */
//extern EN_ERR_STA_T rom_hw_spi_transmit_bytes(stSPI_Handle_t* pstSPI, uint8_t* pu8TxBuf, uint8_t* pu8RxBuf,uint16_t u16TrxLen);




#ifdef __cplusplus
}
#endif

#endif



