/*************************************************************************************************************
 * @file    hw_psram.h
 * @version V1.0
 * @date    2022-01-17
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



#ifndef __HW_PSRAM_H__
#define __HW_PSRAM_H__

//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define PSRAM_CMD_TIMEOUT_US               ( 1000 )   // unit us


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef enum
{
    SPI_READ = 0x00,
    SPI_FAST_READ,
    QPI_FAST_READ,
    SPI_FAST_QUAD_READ,
    QPI_FAST_QUAD_READ,
} EN_PSRAM_READ_MODE_T;

typedef enum
{
    SPI_WRITE           = 0x00,
    QPI_WRITE,
    SPI_QUAD_WRITE,
    QPI_QUAD_WRITE,
} EN_PSRAM_WRITE_MODE_T;

typedef enum
{

    PSRAM_BUS_MODE_SPI = 0x01,
//    BUS_MODE_DPI ,
    PSRAM_BUS_MODE_QPI,

} EN_PSRAM_BUS_MODE_T;

/**********************************************************************************************************************
 * @brief  Init Psram Controller.
 * @param  pstPsram:  QSPI 0 ~ 3.
 * @param  u8InputDlyCfg: Input delay config.
 * @param  u8OutputDlyCfg: Output delay config.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
extern EN_ERR_STA_T rom_hw_psram_init ( stQSPI_Handle_t* pstPsram, uint8_t u8InputDlyCfg, uint8_t u8OutputDlyCfg );


/**********************************************************************************************************************
 * @brief  Send a psram command.
 * @param  pstPsram:  QSPI 0 ~3.
 * @param  u32CmdCfg: Pointer to command config.
 * @param  u32LenCfg: Pointer to length config.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
extern EN_ERR_STA_T rom_hw_psram_send_command ( stQSPI_Handle_t* pstPsram, uint32_t u32CmdCfg, uint32_t u32LenCfg );


/**********************************************************************************************************************
 * @brief  Qspi txfifo write psram bytes.
 * @param  pstPsram:  QSPI 0~3.
 * @param  u32Addr: Start write address of psram.
 * @param  pu8Buf: Write data buffer which will be written to psram memory.
 * @param  u16Len: Length of write data.
 * @param  enMode: Write mode, @ref EN_PSRAM_WRITE_MODE_T.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_fifo_write_bytes ( stQSPI_Handle_t* pstPsram, uint32_t u32Addr,
                                             uint8_t* pu8Buf, uint16_t u16Len, EN_PSRAM_WRITE_MODE_T enMode );


/**********************************************************************************************************************
 * @brief  Qspi rxfifo read psram bytes.
 * @param  pstPsram: QSPI 0~3.
 * @param  u32Addr: Read start Address of psram.
 * @param  pu8Buf: Read buffer which will be written from psram memory.
 * @param  u16Len: Length of read data.
 * @param  enMode: Read mode, @ref EN_PSRAM_READ_MODE_T.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_fifo_read_bytes ( stQSPI_Handle_t* pstPsram, uint32_t u32Addr, uint8_t* pu8Buf,
                                            uint16_t u16Len, EN_PSRAM_READ_MODE_T enMode );


/**********************************************************************************************************************
 * @brief  Enable psram direct write.
 * @param  pstPsram: QSPI 0~3.
 * @param  enWriteMode: Write mode, @ref EN_PSRAM_WRITE_MODE_T.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_direct_write_enable ( stQSPI_Handle_t* pstPsram, EN_PSRAM_WRITE_MODE_T enWriteMode );

/**********************************************************************************************************************
 * @brief  Enable psram direct read.
 * @param  pstPsram: QSPI 0~3.
 * @param  enReadMode: Read mode, @ref EN_PSRAM_READ_MODE_T.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_direct_read_enable ( stQSPI_Handle_t* pstPsram, EN_PSRAM_READ_MODE_T enReadMode );


/**********************************************************************************************************************
 * @brief  Direct read psram bytes.
 * @param  pstPsram: QSPI 0~3.
 * @param  u32Addr: Read start address of psram.
 * @param  pu8Buf: Read buffer which will be written from psram memory.
 * @param  u16Len: Length of write data.
 * @param  enMode: Read mode, @ref EN_PSRAM_READ_MODE_T.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_direct_read_bytes ( stQSPI_Handle_t* pstPsram, uint32_t u32Addr, uint8_t* pu8Buf,
                                              uint16_t u16Len, EN_PSRAM_READ_MODE_T enMode );


/**********************************************************************************************************************
 * @brief  Direct write psram bytes.
 * @param  pstPsram: QSPI 0~3.
 * @param  u32Addr: Write start address of psram.
 * @param  pu8Buf: Write buffer which will be written to psram memory.
 * @param  u16Len: Length of write data.
 * @param  enMode: Write mode as below, @ref EN_PSRAM_WRITE_MODE_T.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_direct_write_bytes ( stQSPI_Handle_t* pstPsram, uint32_t u32Addr, uint8_t* pu8Buf,
                                               uint16_t u16Len, EN_PSRAM_WRITE_MODE_T enMode );


/**********************************************************************************************************************
 * @brief  Enter quad mode.
 * @param  pstPsram:  QSPI 0~3.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_enter_quad_mode (  stQSPI_Handle_t* pstPsram );


/**********************************************************************************************************************
 * @brief  Exit quad mode.
 * @param  pstPsram:  PSRAM 0~3.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_exit_quad_mode (  stQSPI_Handle_t* pstPsram );


/**********************************************************************************************************************
 * @brief  Reset psram.
 * @param  pstPsram:  QSPI 0~3.
 * @param  enPsramMode:  Psarm bus mode.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_reset ( stQSPI_Handle_t* pstPsram, EN_PSRAM_BUS_MODE_T enPsramMode );


/**********************************************************************************************************************
 * @brief  Get psram memory ID.
 * @param  pstPsram:  QSPI 0~3.
 * @param  pu32ID: Pointer to a 32-bit to save the memory id.
 * @output
 * @return HW status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T rom_hw_psram_get_id ( stQSPI_Handle_t* pstPsram, uint32_t* pu32ID );


#endif
