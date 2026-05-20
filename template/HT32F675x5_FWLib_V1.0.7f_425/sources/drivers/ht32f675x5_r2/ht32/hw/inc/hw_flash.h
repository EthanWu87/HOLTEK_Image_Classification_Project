/*************************************************************************************************************
 * @file    hw_flash.h
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



#ifndef __HW_FLASH_H__
#define __HW_FLASH_H__

//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define FLASH_PROGRAM_TIMEOUT_US           (SFLASH_PROGRAM_TIME_US )
#define FLASH_PAGE_ERASE_TIMEOUT_US        (SFLASH_PAGE_ERASE_TIME_US )
#define FLASH_CHIP_ERASE_TIMEOUT_US        (SFLASH_CHIP_ERASE_TIME_US )

#define FLASH_TRX_MAX_LENGTH               (64 * 1024) // 64KB
#define FLASH_TRX_MAX_MSK                  (FLASH_TRX_MAX_LENGTH - 1)


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef union
{
    struct stLenCfg_t
    {
        uint8_t  u8AddrLen;
        uint8_t  u8CmdLen;
        uint16_t u16DataLen;
        
    } stLenCfg;

    uint32_t u32LenCfg;

} unLenCfg_t;

typedef union
{
    struct stCmdType_t
    {
        uint8_t  u8Cmd;
        uint8_t  u8Res;  // Reserved
        uint16_t u16CmdType;
        
    } stCmdType;

    uint32_t u32CmdCfg;
    
} unCmdCfg_t;

typedef enum
{
    ERASE_PAGE = 0,
    ERASE_SECTOR,
    ERASE_BLOCK_32KB,
    ERASE_BLOCK_64KB,
    
} EN_SFLASH_ERASE_SIZE_T;


// Flash send command callback
typedef EN_ERR_STA_T(*FLASH_SEND_CMD_CB_FUNC)( stQSPI_Handle_t* pstFlash, uint32_t u32CmdCfg, uint32_t u32LenCfg);




/**
 * @brief  Init Sflash Controller.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u8DlyCfg: Flash delay config.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_init(stQSPI_Handle_t* pstFlash, uint8_t u8DlyCfg);


/**
 * @brief  Set flash encrypt and decrypt key.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u32Key: Flash encrypt and decrypt key, 32bit.
 * @return status: @ref EN_ERR_STA_T.
 */
// extern EN_ERR_STA_T rom_hw_flash_set_encrypt_key(stQSPI_Handle_t* pstFlash, uint32_t u32Key);


/**
 * @brief  Enable flash encrypt function.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @return status: @ref EN_ERR_STA_T.
 */
// extern EN_ERR_STA_T rom_hw_flash_enable_encrypt(stQSPI_Handle_t* pstFlash);


/**
 * @brief  Disable flash encrypt function.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @return status: @ref EN_ERR_STA_T.
 */
// extern EN_ERR_STA_T rom_hw_flash_disable_encrypt(stQSPI_Handle_t* pstFlash);


/**
 * @brief  Send a flash command.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u32CmdCfg: Pointer to command config.
 * @param  u32LenCfg: Pointer to length config.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_send_command(stQSPI_Handle_t* pstFlash, uint32_t u32CmdCfg, uint32_t u32LenCfg);


/**
 * @brief  Software Reset.
 *         After send comand RST(0x99), need wait 30us at least.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_reset(stQSPI_Handle_t* pstFlash);


/**
 * @brief  sFlash controller read XiP flash status[15:0].
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  pu16Status: Status[15:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_read_status(stQSPI_Handle_t* pstFlash, uint16_t* pu16Status);


/**
 * @brief  Flash controller write XiP flash status[15:0].
 *         The Write Status Register (WRSR) command allows new values to be written to the Status Register. Before it
 *         can be accepted, a Write Enable (WREN) command must previously have been executed. The WRSR command has no
 *         effect on S15, S10, S1 and S0 of the Status Register.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u16Status: new values to be written to the Status Register[15:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_write_status(stQSPI_Handle_t* pstFlash, uint16_t u16Status);


/**
 * @brief  sFlash controller read XiP flash status[15:8].
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  pu16Status: Status[15:8].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_read_status_high(stQSPI_Handle_t* pstFlash, uint8_t* pu8Status);


/**
 * @brief  sFlash controller read XiP flash status[7:0].
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  pu16Status: Status[15:8].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_read_status_low(stQSPI_Handle_t* pstFlash, uint8_t* pu8Status);


/**
 * @brief  sFlash wait until the flash operation is finished.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u32TimeoutUs: Timeout of WIP. The Write in Progress (WIP) bit indicates whether the memory is busy in
 *                       program/erase/write status register progress.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_wait_idle(stQSPI_Handle_t* pstFlash, uint32_t u32TimeoutUs);


/**
 * @brief  sFlash release flash from read enhanced mode.
 *         This function release from read enhanced mode.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  enBusMode: Access mode as below, @ref EN_FLASH_BUS_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_release_read_enhanced(stQSPI_Handle_t* pstFlash, EN_FLASH_BUS_MODE_T enBusMode);


/**
 * @brief  Set XiP flash quad access mode.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  enEn: Enable or Disable Quad mode @ref EN_QSPI_ENABLE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_set_quad_enable(stQSPI_Handle_t* pstFlash, EN_QSPI_ENABLE_T enEn);


/**
 * @brief  Set XiP Flash exit abnormal state.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_exit_abnormal_state(stQSPI_Handle_t* pstFlash);


/**
 * @brief  Get XiP Flash Mmemory ID by SFlash Controller.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  pu32ID: Pointer to a 32-bit to save the memory id.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_get_id(stQSPI_Handle_t* pstFlash, uint32_t* pu32ID);


/**
 * @brief  Get XiP Flash Mmemory Unique ID by SFlash Controller.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  pu8ID: Pointer to a 128-bit to save the unique id.
 * @return status: @ref EN_ERR_STA_T.
 */
// extern EN_ERR_STA_T rom_hw_flash_get_unique_id(stQSPI_Handle_t* pstFlash, uint8_t* pu8ID);


/**
 * @brief  Get into deep power down work mode.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  enBusMode: Access mode as below, @ref EN_FLASH_BUS_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_enter_deep_power_down( stQSPI_Handle_t* pstFlash, EN_FLASH_BUS_MODE_T enBusMode);


/**
 * @brief  Release from DEEP POWER DOWN state.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_release_deep_power_down(stQSPI_Handle_t* pstFlash);


/**
 * @brief  Set XiP FLASH MEMORY block Protect.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u16BlockCfg: Block protect area configuration.
 * @return status: @ref EN_ERR_STA_T.
 */
// extern EN_ERR_STA_T rom_hw_flash_set_block_protect(stQSPI_Handle_t* pstFlash, uint16_t u16BlockCfg);


/**
 * @brief  Erase XiP flash memory with indicated @ref EN_SFLASH_ERASE_SIZE_T number.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  enSize: The range of Erase, @ref EN_SFLASH_ERASE_SIZE_T.
 * @param  u16Num: Number of Erase.
 * @param  u32Timeoutus: Timeout of flash page/sector/block erase, unit is us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_erase(stQSPI_Handle_t* pstFlash, EN_SFLASH_ERASE_SIZE_T enSize, 
                                       uint16_t u16Num, uint32_t u32Timeoutus);


/**
 * @brief  Erase XiP flash memory.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u32Timeoutus: Timeout of flash chip erase, unit is us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_chip_erase(stQSPI_Handle_t* pstFlash, uint32_t u32Timeoutus);


/**
 * @brief  Write the buffer data to XiP flash memory in one page from indicated start address with indicated access mode.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u32Addr: Start Address of XiP FLASH MEMORY.
 * @param  pu8Buf: Pointer to a buffer which will be written to flash memory.
 * @param  u16Len: Length of write data.
 * @param  enMode: Access mode as below, @ref EN_FLASH_BUS_MODE_T.
 * @param  u16TimeoutUs: Timeout of flash page program, unit is us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_write_bytes_in_page(stQSPI_Handle_t* pstFlash, uint32_t u32Addr, uint8_t* pu8Buf, 
                                                     uint16_t u16Len, EN_FLASH_BUS_MODE_T enMode, uint16_t u16TimeoutUs);


/**
 * @brief  Write the buffer data to XiP flash memory from indicated start address with indicated access mode
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u32Addr: Start Address of XiP FLASH MEMORY.
 * @param  pu8Buf: Pointer to a buffer which will be written to flash memory.
 * @param  u32Len: Length of write data, maximum length is 64 * 1024 Bytes.
 * @param  enMode: Access mode as below, @ref EN_FLASH_BUS_MODE_T.
 * @param  u16TimeoutUs: Timeout of flash page program, unit is us.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_write_bytes(stQSPI_Handle_t* pstFlash, uint32_t u32Addr, uint8_t* pu8Buf, 
                                             uint32_t u32Len, EN_FLASH_BUS_MODE_T enMode, uint16_t u16TimeoutUs);


/**
 * @brief  Read XiP flash memory from indicated start address with indicated access mode.
 * @param  pstFlash: FLASH handle, Should be FLASH(FLASH0) / FLASH1.
 * @param  u32Addr: Start Address of XiP FLASH MEMORY.
 * @param  pu8Buf: Pointer to a buffer which used to save the read data.
 * @param  u32Len: Length of read data, maximum length is 64 * 1024 Bytes.
 * @param  enMode: Access mode as below, @ref EN_FLASH_BUS_MODE_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_flash_read_bytes(stQSPI_Handle_t* pstFlash, uint32_t u32Addr, uint8_t* pu8Buf,
                                            uint32_t u32Len, EN_FLASH_BUS_MODE_T enMode);


#endif /* __HW_FLASH_H__ */


