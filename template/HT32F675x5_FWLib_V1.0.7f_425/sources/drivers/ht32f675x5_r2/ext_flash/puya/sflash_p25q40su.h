/*************************************************************************************************************
 * @file    sflash_p25q40su.h
 * @version V1.0
 * @date    2023-08-11
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


#ifndef __SFLASH_P25Q40SU_H__
#define __SFLASH_P25Q40SU_H__

#define P25Q40SU_CHIP_ID                   (0x136085)

#define P25Q40SU_PROGRAM_TIME_US           (3000)  // 2ms ~ 3ms
#define P25Q40SU_PAGE_ERASE_TIME_US        (30000) // 16ms ~ 30ms
#define P25Q40SU_SECTOR_ERASE_TIME_US      (30000) // 16ms ~ 30ms
#define P25Q40SU_BLOCK32K_ERASE_TIME_US    (30000) // 16ms ~ 30ms
#define P25Q40SU_BLOCK64K_ERASE_TIME_US    (30000) // 16ms ~ 30ms
#define P25Q40SU_CHIP_ERASE_TIME_US        (30000) // 16ms ~ 30ms

#define P25Q40SU_MEM_SIZE_BYTE             (0x80000) // 512KBytes
#define P25Q40SU_ADDR_BITS                 (0x18)

#define SFLASH_ADDR_BITS                   (P25Q40SU_ADDR_BITS)


//=====================================================================================================================
// FLASH PAGE/SECTOR/BLOCK Define
//=====================================================================================================================
#define SFLASH_PAGE_BYTE_SIZE              (0x100)
#define SFLASH_PAGE_SHIFT_BITS             (0x08)
#define SFLASH_PAGE_MASK                   ((0x01 << SFLASH_PAGE_SHIFT_BITS) - 1)

#define SFLASH_SECTOR_BYTE_SIZE            (4096)
#define SFLASH_SECTOR_SHIFT_BITS           (12)

#define SFLASH_BLOCK_32KB_BYTE_SIZE        (32768)
#define SFLASH_BLOCK_32KB_SHIFT_BITS       (15)

#define SFLASH_BLOCK_64KB_BYTE_SIZE        (65536)
#define SFLASH_BLOCK_64KB_SHIFT_BITS       (16)


//=====================================================================================================================
// The Write Enable (WREN) instruction is for setting Write Enable Latch (WEL) bit.
// For those instructions like PP, QPP, PE, SE, BE32K,BE, CE, BFPP and WRSR, WRCR, ERSCUR, PRSCUR which are intended to
// change the device content, should be set every time after the WREN instruction setting the WEL bit.
//=====================================================================================================================
#define SFLASH_CMD_WREN                    (0x06)
#define SFLASH_WREN_TYPE                   (TPYE_CMD << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_WREN_CMD_LEN                (0x07)
#define SFLASH_WREN_ADDR_LEN               (0x00)
#define SFLASH_WREN_DATA_LEN               (0x00)
#define SFLASH_WREN_CMD_CFG                (SFLASH_CMD_WREN | (SFLASH_WREN_TYPE << HALF_WORD_BITS))
#define SFLASH_WREN_LEN_CFG                (SFLASH_WREN_ADDR_LEN | (SFLASH_WREN_CMD_LEN << BYTE_BITS) | (SFLASH_WREN_DATA_LEN << HALF_WORD_BITS))

// The Write Disable (WRDI) instruction is for resetting Write Enable Latch (WEL) bit
#define SFLASH_CMD_WRDI                    (0x04)

//=====================================================================================================================
// The RDSR instruction is for reading Status Register Bits. The Read Status Register can be read at any time(even in 
// program/erase/write status register condition)
// It is recommended to check the Write in Progress(WIP) bit before sending a new instruction when a program, erase, or 
// write status register operation is in progress. For command code "05H", the SO will output Status Register bits S7~S0. 
// The command code"35H", the SO will output Status Register bits S15~S8.
//=====================================================================================================================
#define SFLASH_CMD_RDSR                    (0x05)
#define SFLASH_RDSR_TYPE                   (TPYE_CMD_READ << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_RDSR_CMD_LEN                (0x07)
#define SFLASH_RDSR_ADDR_LEN               (0x00)
#define SFLASH_RDSR_DATA_LEN               (0x02 - 0x01)
#define SFLASH_RDSR_CMD_CFG                (SFLASH_CMD_RDSR | (SFLASH_RDSR_TYPE << HALF_WORD_BITS))
#define SFLASH_RDSR_LEN_CFG                (SFLASH_RDSR_ADDR_LEN | (SFLASH_RDSR_CMD_LEN << BYTE_BITS) | (SFLASH_RDSR_DATA_LEN << HALF_WORD_BITS))

#define SFLASH_CMD_HRDSR                   (0x35)
#define SFLASH_HRDSR_TYPE                  (TPYE_CMD_READ << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_HRDSR_CMD_LEN               (0x07)
#define SFLASH_HRDSR_ADDR_LEN              (0x00)
#define SFLASH_HRDSR_DATA_LEN              (0x02 - 0x01)
#define SFLASH_HRDSR_CMD_CFG               (SFLASH_CMD_HRDSR | (SFLASH_HRDSR_TYPE << HALF_WORD_BITS))
#define SFLASH_HRDSR_LEN_CFG               (SFLASH_HRDSR_ADDR_LEN | (SFLASH_HRDSR_CMD_LEN << BYTE_BITS) | (SFLASH_HRDSR_DATA_LEN << HALF_WORD_BITS))

// Write in Progress(WIP), Indicates whether the memory is busy in program/erase/write status
#define SFLASH_STATUS_WIP_SHIFT            (0)
#define SFLASH_STATUS_WIP_MSK              ((0x01 << 1) - 1)
#define SFLASH_STATUS_WIP                  (SFLASH_STATUS_WIP_MSK << SFLASH_STATUS_WIP_SHIFT)

// Write Enable Latch (WEL),Indicates the status of the internal write enable latch.
#define SFLASH_STATUS_WEL_BITS             (1)
#define SFLASH_STATUS_WEL_SHIFT            (1)
#define SFLASH_STATUS_WEL_MSK              ((0x01 << 1) - 1)

// Block Protct (BP). The (BP4, BP3, BP2, BP1, and BP0) bits are non-volatile. 
#define SFLASH_STATUS_BP_BITS              (5)
#define SFLASH_STATUS_BP_SHIFT             (2)
#define SFLASH_STATUS_BP_MSK               ((0x01 << 5) - 1)

typedef enum
{
    BP_LOWER_0KB   = 0x00,
    BP_LOWER_4KB   = 0x19,
    BP_LOWER_8KB   = 0x1A,
    BP_LOWER_16KB  = 0x1B,
    BP_LOWER_32KB  = 0x1C,
    BP_LOWER_64KB  = 0x09,
    BP_LOWER_128KB = 0x0A,
    BP_LOWER_256KB = 0x0B,
    BP_UPPER_4KB   = 0x11,
    BP_UPPER_8KB   = 0x12,
    BP_UPPER_16KB  = 0x13,
    BP_UPPER_32KB  = 0x14,
    BP_UPPER_64KB  = 0x01,
    BP_UPPER_128KB = 0x02,
    BP_UPPER_256KB = 0x03,
    BP_ALL         = 0x04,

} EN_SFLASH_BP_T;

// Status Register Protect (SRP). The (SRP1 and SRP0) bits are non-volatile. 
#define SFLASH_STATUS_SRP_BITS             (2)
#define SFLASH_STATUS_SRP_SHIFT            (7)
#define SFLASH_STATUS_SRP_MSK              ((0x01 << 2) - 1)

// The Quad Enable (QE) bit is a non-volatile Read/Write bit that allows Quad operation.
#define SFLASH_STATUS_QE_BITS              (1)
#define SFLASH_STATUS_QE_SHIFT             (9)
#define SFLASH_STATUS_QE_MSK               ((0x01 << 1) - 1)

// The Erase/Program Fail bit is a read only bit which shows the status of the last Program/Erase operation. 
#define SFLASH_STATUS_EP_FAIL_BITS         (1)
#define SFLASH_STATUS_EP_FAIL_SHIFT        (10)
#define SFLASH_STATUS_EP_FAIL_MSK          ((0x01 << 1) - 1)

// The LB3, LB2, LB1, bits are non-volatile One Time Program (OTP) bits in Status Register (S13-S11) that
// provide the write protect control and status to the Security Registers. 
#define SFLASH_STATUS_LB_BITS              (3)
#define SFLASH_STATUS_LB_SHIFT             (11)
#define SFLASH_STATUS_LB_MSK               ((0x01 << 3) - 1)

// The CMP bit is a non-volatile Read/Write bit in the Status Register(S14).
#define SFLASH_STATUS_CMP_BITS             (1)
#define SFLASH_STATUS_CMP_SHIFT            (14)
#define SFLASH_STATUS_CMP_MSK              ((0x01 << 1) - 1)

// The SUS bit is read only bit in the status register (S15) that is set to 1 after executing an Program/Erase
// Suspend (75H) command. The SUS bit is cleared to 0 by Program/Erase Resume (7AH) command as well as
// a power-down, power-up cycle.
#define SFLASH_STATUS_SUS_BITS             (1)
#define SFLASH_STATUS_SUS_SHIFT            (15)
#define SFLASH_STATUS_SUS_MSK              ((0x01 << 1) - 1)

//=====================================================================================================================
// The Write Status Register (WRSR) command allows new values to be written to the Status Register. Before it
// can be accepted, a Write Enable (WREN) command must previously have been executed. After the Write
// Enable (WREN) command has been decoded and executed, the device sets the Write Enable Latch (WEL).
//=====================================================================================================================
#define SFLASH_CMD_WRSR                    (0x01)
#define SFLASH_WRSR_TYPE                   (TPYE_CMD_WRITE << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_WRSR_CMD_LEN                (0x07)
#define SFLASH_WRSR_ADDR_LEN               (0x00)
#define SFLASH_WRSR_DATA_LEN               (0x02 - 1) 
#define SFLASH_WRSR_CMD_CFG                (SFLASH_CMD_WRSR | (SFLASH_WRSR_TYPE << HALF_WORD_BITS))
#define SFLASH_WRSR_LEN_CFG                (SFLASH_WRSR_ADDR_LEN | (SFLASH_WRSR_CMD_LEN << BYTE_BITS) | (SFLASH_WRSR_DATA_LEN << HALF_WORD_BITS))


//=====================================================================================================================
// The read instruction is for reading data out. The address is latched on rising edge of SCLK, and data shifts
// out on the falling edge of SCLK at a maximum frequency fR.
//=====================================================================================================================
// Standard SPI read data mode
#define SFLASH_CMD_READ                    (0x03)
#define SFLASH_READ_TYPE                   ((TPYE_CMD_ADDR_READ << QSPI_MEM_CMD_TYPE_SHIFT) | (BUS_MODE_SPI << QSPI_MEM_DATA_MODE_SHIFT))
#define SFLASH_READ_CMD_LEN                (0x07)
#define SFLASH_READ_ADDR_LEN               (SFLASH_ADDR_BITS - 1)
#define SFLASH_READ_DATA_LEN               (0x00)
#define SFLASH_READ_CMD_CFG                (SFLASH_CMD_READ | (SFLASH_READ_TYPE << HALF_WORD_BITS))
#define SFLASH_READ_LEN_CFG                (SFLASH_READ_ADDR_LEN | (SFLASH_READ_CMD_LEN << BYTE_BITS))

#define SFLASH_CMD_FREAD                   (0x0B)

// The DREAD instruction enable double throughput of Serial NOR Flash in read mode. The address is latched on rising edge
// of SCLK, and data of every two bits (interleave on 2 I/O pins) shift out on the falling edge of SCLK at a maximum frequency fT.
#define SFLASH_CMD_DREAD                   (0x3B)
#define SFLASH_DREAD_TYPE                  ((TPYE_CMD_ADDR_READ << QSPI_MEM_CMD_TYPE_SHIFT) | (BUS_MODE_DPI << QSPI_MEM_DATA_MODE_SHIFT))
#define SFLASH_DREAD_CMD_LEN               (0x07)
#define SFLASH_DREAD_ADDR_LEN              (0x20 -1)
#define SFLASH_DREAD_DATA_LEN              (0x02 - 1)
#define SFLASH_DREAD_CMD_CFG               (SFLASH_CMD_DREAD | (SFLASH_DREAD_TYPE << HALF_WORD_BITS))
#define SFLASH_DREAD_LEN_CFG               (SFLASH_DREAD_ADDR_LEN | (SFLASH_DREAD_CMD_LEN << BYTE_BITS))

// The QREAD instruction enable quad throughput of Serial NOR Flash in read mode. A Quad Enable (QE) bit of
// status Register must be set to "1" before sending the QREAD instruction. The address is latched on rising
// edge of SCLK, and data of every four bits (interleave on 4 I/O pins) shift out on the falling edge of SCLK at a maximum frequency fQ. 
#define SFLASH_CMD_QREAD                   (0x6B)
#define SFLASH_QREAD_TYPE                  ((TPYE_CMD_ADDR_READ << QSPI_MEM_CMD_TYPE_SHIFT) | (BUS_MODE_QPI << QSPI_MEM_DATA_MODE_SHIFT))
#define SFLASH_QREAD_CMD_LEN               (0x07)
#define SFLASH_QREAD_ADDR_LEN              (0x20 - 1)
#define SFLASH_QREAD_DATA_LEN              (0x02 - 1)
#define SFLASH_QREAD_CMD_CFG               (SFLASH_CMD_QREAD | (SFLASH_QREAD_TYPE << HALF_WORD_BITS))
#define SFLASH_QREAD_LEN_CFG               (SFLASH_QREAD_ADDR_LEN | (SFLASH_QREAD_CMD_LEN << BYTE_BITS))

// The 2READ instruction enables Double Transfer Rate of Serial NOR Flash in read mode. 
// The address is latched on rising edge of SCLK, and data of every two bits (interleave on 2 I/O pins) shift out on the falling
// edge of SCLK at a maximum frequency fT. 
#define SFLASH_CMD_2READ                   (0xBB)

// The 4READ instruction enable quad throughput of Serial NOR Flash in read mode. A Quad Enable (QE) bit of
// status Register must be set to "1" before sending the 4READ instruction. The address is latched on rising
// edge of SCLK, and data of every four bits (interleave on 4 I/O pins) shift out on the falling edge of SCLK at a
// maximum frequency fQ. 
#define SFLASH_CMD_4READ                   (0xEB)


//=====================================================================================================================
// The Page Program (PP/QPP) instruction is for programming the memory to be "0" with SPI/DPI/QPI interface
// A Write Enable (WREN) instruction must execute to set the Write Enable Latch (WEL) bit before sending the Page Program (PP).
// Notes: Whether SPI or QPP command, the command and address transmited with SPI mode(24-bit address)
//=====================================================================================================================
#define SFLASH_CMD_PP                      (0x02)
#define SFLASH_PP_TYPE                     ((TPYE_CMD_ADDR_WRITE << QSPI_MEM_CMD_TYPE_SHIFT) | (BUS_MODE_SPI << QSPI_MEM_DATA_MODE_SHIFT))
#define SFLASH_PP_CMD_LEN                  (0x07)
#define SFLASH_PP_ADDR_LEN                 (SFLASH_ADDR_BITS - 1)
#define SFLASH_PP_DATA_LEN                 (0x00)
#define SFLASH_PP_CMD_CFG                  (SFLASH_CMD_PP | (SFLASH_PP_TYPE << HALF_WORD_BITS))
#define SFLASH_PP_LEN_CFG                  (SFLASH_PP_ADDR_LEN | (SFLASH_PP_CMD_LEN << BYTE_BITS))

//DPP not support by p25q40su
#define SFLASH_CMD_DPP                     (0xA2)
#define SFLASH_DPP_TYPE                    ((TPYE_CMD_ADDR_WRITE << QSPI_MEM_CMD_TYPE_SHIFT) | (BUS_MODE_DPI << QSPI_MEM_DATA_MODE_SHIFT))
#define SFLASH_DPP_CMD_LEN                 (0x07)
#define SFLASH_DPP_ADDR_LEN                (24 - 1)
#define SFLASH_DPP_DATA_LEN                (0x00)
#define SFLASH_DPP_CMD_CFG                 (SFLASH_CMD_DPP | (SFLASH_DPP_TYPE << HALF_WORD_BITS))
#define SFLASH_DPP_LEN_CFG                 (SFLASH_DPP_ADDR_LEN | (SFLASH_DPP_CMD_LEN << BYTE_BITS))


// Additionally, Quad Enable (QE) bit must be set to "1" before sending the Quad Page Program (QPP). 
// The Quad Page Programming takes four pins: SIO0, SIO1, SIO2, and SIO3 as data input. 
#define SFLASH_CMD_QPP                     (0x32)
#define SFLASH_QPP_TYPE                    ((TPYE_CMD_ADDR_WRITE << QSPI_MEM_CMD_TYPE_SHIFT) | (BUS_MODE_QPI << QSPI_MEM_DATA_MODE_SHIFT))
#define SFLASH_QPP_CMD_LEN                 (0x07)
#define SFLASH_QPP_ADDR_LEN                (24 - 1)
#define SFLASH_QPP_DATA_LEN                (0x00)
#define SFLASH_QPP_CMD_CFG                 (SFLASH_CMD_QPP | (SFLASH_QPP_TYPE << HALF_WORD_BITS))
#define SFLASH_QPP_LEN_CFG                 (SFLASH_QPP_ADDR_LEN | (SFLASH_QPP_CMD_LEN << BYTE_BITS))


//=====================================================================================================================
// The Deep Power-down (DP) instruction is for setting the device on the minimizing the power consumption (to entering 
// the Deep Power-down mode). during the Deep Power-down mode, all Write/Program/Erase instruction are ignored except 
// the Release from Deep Power-down mode(RDP), Read Electronic Signature (RES) instruction, and soft reset instruction(66H, 99H).
//=====================================================================================================================
#define SFLASH_CMD_DP                      (0xB9)
#define SFLASH_DP_TYPE                     (TPYE_CMD << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_DP_CMD_LEN                  (0x07)
#define SFLASH_DP_ADDR_LEN                 (0x00)
#define SFLASH_DP_DATA_LEN                 (0x00)
#define SFLASH_DP_CMD_CFG                  (SFLASH_CMD_DP | (SFLASH_DP_TYPE << HALF_WORD_BITS))
#define SFLASH_DP_LEN_CFG                  (SFLASH_DP_ADDR_LEN | (SFLASH_DP_CMD_LEN<< BYTE_BITS) | (SFLASH_DP_DATA_LEN << HALF_WORD_BITS))


//=====================================================================================================================
// The Release from Deep Power-down (RDP) instruction is terminated by driving Chip Select (CS#) High. When
// Chip Select (CS#) is driven high, the device is put in the Stand-by Power mode. 
//=====================================================================================================================
#define SFLASH_CMD_RDP                     (0xAB)
#define SFLASH_RDP_TYPE                    (TPYE_CMD << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_RDP_CMD_LEN                 (0x07)
#define SFLASH_RDP_ADDR_LEN                (0x00)
#define SFLASH_RDP_DATA_LEN                (0x00)
#define SFLASH_RDP_CMD_CFG                 (SFLASH_CMD_RDP | (SFLASH_RDP_TYPE << HALF_WORD_BITS))
#define SFLASH_RDP_LEN_CFG                 (SFLASH_RDP_ADDR_LEN | (SFLASH_RDP_CMD_LEN<< BYTE_BITS) | (SFLASH_RDP_DATA_LEN << HALF_WORD_BITS))

// The REMS instruction returns both the JEDEC assigned manufacturer ID and the device ID. 
#define SFLASH_CMD_REMS                    (0x90)

//=====================================================================================================================
// The RDID instruction is for reading the manufacturer ID of 1-byte and followed by Device ID of 2-byte.
// The RDID instruction is for reading the manufacturer ID of 1-byte and followed by Device ID of 2-byte. The
// PUYA Manufacturer ID and Device ID are list as "Table . ID Definitions".
//=====================================================================================================================
#define SFLASH_CMD_RDID                    (0x9F)
#define SFLASH_RDID_TYPE                   (TPYE_CMD_READ << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_RDID_CMD_LEN                (0x07)
#define SFLASH_RDID_ADDR_LEN               (0x00)
#define SFLASH_RDID_DATA_LEN               (0x03 - 1)
#define SFLASH_RDID_CMD_CFG                (SFLASH_CMD_RDID | (SFLASH_RDID_TYPE << HALF_WORD_BITS))
#define SFLASH_RDID_LEN_CFG                (SFLASH_RDID_ADDR_LEN | (SFLASH_RDID_CMD_LEN<< BYTE_BITS) | (SFLASH_RDID_DATA_LEN << HALF_WORD_BITS))


//=====================================================================================================================
//=====================================================================================================================
#define SFLASH_CMD_VWREN                   (0x50)
#define SFLASH_VWREN_TYPE                  (TPYE_CMD << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_VWREN_CMD_LEN               (0x07)
#define SFLASH_VWREN_ADDR_LEN              (0x00)
#define SFLASH_VWREN_DATA_LEN              (0x00) // the lengthe of RDSR is 2 byte, 
#define SFLASH_VWREN_CMD_CFG               (SFLASH_CMD_VWREN | (SFLASH_VWREN_TYPE << HALF_WORD_BITS))
#define SFLASH_VWREN_LEN_CFG               (SFLASH_VWREN_ADDR_LEN | (SFLASH_VWREN_CMD_LEN<< BYTE_BITS) | (SFLASH_VWREN_DATA_LEN << HALF_WORD_BITS))


//=====================================================================================================================
// The Page/Sector/Block/Chip Erase instructions is for erasing the data of the chosen Page to be "1". 
// A Write Enable (WREN)instruction must execute to set the Write Enable Latch (WEL) bit before sending the Erase cmd.
//=====================================================================================================================
// The Page Erase instruction(PE)
#define SFLASH_CMD_PE                      (0x81)
#define SFLASH_PE_TYPE                     (TPYE_CMD_ADDR << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_PE_CMD_LEN                  (0x07)
#define SFLASH_PE_ADDR_LEN                 (SFLASH_ADDR_BITS - 1)
#define SFLASH_PE_DATA_LEN                 (0x03-1) // the length of RDID is 3 byte, 
#define SFLASH_PE_CMD_CFG                  (SFLASH_CMD_PE | (SFLASH_PE_TYPE << HALF_WORD_BITS))
#define SFLASH_PE_LEN_CFG                  (SFLASH_PE_ADDR_LEN | (SFLASH_PE_CMD_LEN<< BYTE_BITS) | (SFLASH_PE_DATA_LEN << HALF_WORD_BITS))

//The Sector Erase instruction(SE)
#define SFLASH_CMD_SE                      (0x20)
#define SFLASH_SE_TYPE                     (TPYE_CMD_ADDR << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_SE_CMD_LEN                  (0x07)
#define SFLASH_SE_ADDR_LEN                 (SFLASH_ADDR_BITS - 1)
#define SFLASH_SE_DATA_LEN                 (0x03-1) // the length of RDID is 3 byte, 
#define SFLASH_SE_CMD_CFG                  (SFLASH_CMD_SE | (SFLASH_SE_TYPE << HALF_WORD_BITS))
#define SFLASH_SE_LEN_CFG                  (SFLASH_SE_ADDR_LEN | (SFLASH_SE_CMD_LEN<< BYTE_BITS) | (SFLASH_SE_DATA_LEN << HALF_WORD_BITS))

// The Block32k Erase instruction(BE32)
#define SFLASH_CMD_BE32K                   (0x52)
#define SFLASH_BE32K_TYPE                  (TPYE_CMD_ADDR << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_BE32K_CMD_LEN               (0x07)
#define SFLASH_BE32K_ADDR_LEN              (SFLASH_ADDR_BITS - 1)
#define SFLASH_BE32K_DATA_LEN              (0x03-1)
#define SFLASH_BE32K_CMD_CFG               (SFLASH_CMD_BE32K | (SFLASH_BE32K_TYPE << HALF_WORD_BITS))
#define SFLASH_BE32K_LEN_CFG               (SFLASH_BE32K_ADDR_LEN | (SFLASH_BE32K_CMD_LEN<< BYTE_BITS) | (SFLASH_BE32K_DATA_LEN << HALF_WORD_BITS))

// The Block64k Erase instruction(BE)
#define SFLASH_CMD_BE                      (0xD8)
#define SFLASH_BE_TYPE                     (TPYE_CMD_ADDR << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_BE_CMD_LEN                  (0x07)
#define SFLASH_BE_ADDR_LEN                 (SFLASH_ADDR_BITS - 1)
#define SFLASH_BE_DATA_LEN                 (0x03-1)
#define SFLASH_BE_CMD_CFG                  (SFLASH_CMD_BE | (SFLASH_BE_TYPE << HALF_WORD_BITS))
#define SFLASH_BE_LEN_CFG                  (SFLASH_BE_ADDR_LEN | (SFLASH_BE_CMD_LEN<< BYTE_BITS) | (SFLASH_BE_DATA_LEN << HALF_WORD_BITS))

// The Chip Erase instruction(CE) 
#define SFLASH_CMD_CE                      (0xC7)
#define SFLASH_CE_TYPE                     (TPYE_CMD << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_CE_CMD_LEN                  (0x07)
#define SFLASH_CE_ADDR_LEN                 (0x00)
#define SFLASH_CE_DATA_LEN                 (0x00)
#define SFLASH_CE_CMD_CFG                  (SFLASH_CMD_CE | (SFLASH_CE_TYPE << HALF_WORD_BITS))
#define SFLASH_CE_LEN_CFG                  (SFLASH_CE_ADDR_LEN | (SFLASH_CE_CMD_LEN<< BYTE_BITS) | (SFLASH_CE_DATA_LEN << HALF_WORD_BITS))


//=====================================================================================================================
// The product provides three 512-byte Security Registers which can be erased and programmed individually.
// These registers may be used by the system manufacturers to store security and other important information
// separately from the main memory array.
//=====================================================================================================================
// Erase Security Registers (ERSCUR)
#define SFLASH_CMD_ERSCUR                  (0x44)
#define SFLASH_ERSCUR_TYPE                 (TPYE_CMD_ADDR << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_ERSCUR_CMD_LEN              (0x07)
#define SFLASH_ERSCUR_ADDR_LEN             (SFLASH_ADDR_BITS - 1)
#define SFLASH_ERSCUR_DATA_LEN             (0x00)
#define SFLASH_ERSCUR_CMD_CFG              (SFLASH_CMD_ERSCUR | (SFLASH_ERSCUR_TYPE << HALF_WORD_BITS))
#define SFLASH_ERSCUR_LEN_CFG              (SFLASH_ERSCUR_ADDR_LEN | (SFLASH_ERSCUR_CMD_LEN<< BYTE_BITS) | (SFLASH_ERSCUR_DATA_LEN << HALF_WORD_BITS))

// Program Security Registers (PRSCUR)
#define SFLASH_CMD_PRSCUR                  (0x42)
#define SFLASH_PRSCUR_TYPE                 ((TPYE_CMD_ADDR_WRITE << QSPI_MEM_CMD_TYPE_SHIFT) | (BUS_MODE_SPI << QSPI_MEM_DATA_MODE_SHIFT))
#define SFLASH_PRSCUR_CMD_LEN              (0x07)
#define SFLASH_PRSCUR_ADDR_LEN             (SFLASH_ADDR_BITS - 1)
#define SFLASH_PRSCUR_DATA_LEN             (0x00)
#define SFLASH_PRSCUR_CMD_CFG              (SFLASH_CMD_PRSCUR | (SFLASH_PRSCUR_TYPE << HALF_WORD_BITS))
#define SFLASH_PRSCUR_LEN_CFG              (SFLASH_PRSCUR_ADDR_LEN | (SFLASH_PRSCUR_CMD_LEN << BYTE_BITS))

// Read Security Registers (RDSCUR)
#define SFLASH_CMD_RDSCUR                  (0x48)
#define SFLASH_RDSCUR_TYPE                 ((TPYE_CMD_ADDR_READ << QSPI_MEM_CMD_TYPE_SHIFT) | (BUS_MODE_SPI << QSPI_MEM_DATA_MODE_SHIFT))
#define SFLASH_RDSCUR_CMD_LEN              (0x07)
#define SFLASH_RDSCUR_ADDR_LEN             (32 - 1)
#define SFLASH_RDSCUR_DATA_LEN             (0x00)
#define SFLASH_RDSCUR_CMD_CFG              (SFLASH_CMD_RDSCUR | (SFLASH_RDSCUR_TYPE << HALF_WORD_BITS))         //xx48
#define SFLASH_RDSCUR_LEN_CFG              (SFLASH_RDSCUR_ADDR_LEN | (SFLASH_RDSCUR_CMD_LEN << BYTE_BITS))    // 0717

#define SFLASH_CMD_ASI                     (0x25)
#define SFLASH_CMD_HPM                     (0xA3U)

//=====================================================================================================================
// The Suspend instruction interrupts a Page Program, Page Erase, Sector Erase, or Block Erase operation to
// allow access to the memory array. 
//=====================================================================================================================
#define SFLASH_CMD_SUS                      (0x75)
#define SFLASH_SUS_TYPE                     (TPYE_CMD << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_SUS_CMD_LEN                  (0x07)
#define SFLASH_SUS_ADDR_LEN                 (0x00)
#define SFLASH_SUS_DATA_LEN                 (0x00)
#define SFLASH_SUS_CMD_CFG                  (SFLASH_CMD_SUS | (SFLASH_SUS_TYPE << HALF_WORD_BITS))
#define SFLASH_SUS_LEN_CFG                  (SFLASH_SUS_ADDR_LEN | (SFLASH_SUS_CMD_LEN<< BYTE_BITS) | (SFLASH_SUS_DATA_LEN << HALF_WORD_BITS))

//=====================================================================================================================
// The Resume instruction resumes a suspended Page Program, Page Erase, Sector Erase, or Block Erase operation.
// Note: Before issuing the Resume instruction to restart a suspended erase operation, make sure that there
// is no Page Program operation in progress.
//=====================================================================================================================
#define SFLASH_CMD_RES                      (0x7A)
#define SFLASH_RES_TYPE                     (TPYE_CMD << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_RES_CMD_LEN                  (0x07)
#define SFLASH_RES_ADDR_LEN                 (0x00)
#define SFLASH_RES_DATA_LEN                 (0x00)
#define SFLASH_RES_CMD_CFG                  (SFLASH_CMD_RES | (SFLASH_RES_TYPE << HALF_WORD_BITS))
#define SFLASH_RES_LEN_CFG                  (SFLASH_RES_ADDR_LEN | (SFLASH_RES_CMD_LEN<< BYTE_BITS) | (SFLASH_RES_DATA_LEN << HALF_WORD_BITS))


//=====================================================================================================================
// The Software Reset operation combines two instructions: Reset-Enable (RSTEN) command and Reset
// (RST) command. It returns the device to a standby mode. All the volatile bits and settings will be cleared then,
// which makes the device return to the default status as power on
//=====================================================================================================================
#define SFLASH_CMD_RSTEN                   (0x66)
#define SFLASH_RSTEN_TYPE                  (TPYE_CMD  << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_RSTEN_CMD_LEN               (0x07)
#define SFLASH_RSTEN_ADDR_LEN              (0x00)
#define SFLASH_RSTEN_DATA_LEN              (0x00) 
#define SFLASH_RSTEN_CMD_CFG               (SFLASH_CMD_RSTEN | (SFLASH_RSTEN_TYPE << HALF_WORD_BITS))
#define SFLASH_RSTEN_LEN_CFG               (SFLASH_RSTEN_ADDR_LEN | (SFLASH_RSTEN_CMD_LEN<< BYTE_BITS) | (SFLASH_RSTEN_DATA_LEN << HALF_WORD_BITS))

#define SFLASH_CMD_RST                     (0x99)
#define SFLASH_RST_TYPE                    (TPYE_CMD  << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_RST_CMD_LEN                 (0x07)
#define SFLASH_RST_ADDR_LEN                (0x00)
#define SFLASH_RST_DATA_LEN                (0x00)  
#define SFLASH_RST_CMD_CFG                 (SFLASH_CMD_RST | (SFLASH_RST_TYPE << HALF_WORD_BITS))
#define SFLASH_RST_LEN_CFG                 (SFLASH_RST_ADDR_LEN | (SFLASH_RST_CMD_LEN<< BYTE_BITS) | (SFLASH_RST_DATA_LEN << HALF_WORD_BITS))

#define SFLASH_CMD_DREMS                   (0x92)
#define SFLASH_CMD_QREMS                   (0x94)
#define SFLASH_CMD_SBL                     (0x77)
#define SFLASH_CMD_RDSFDP                  (0x5A)

#define SFLASH_CMD_RUID                    (0x4B)
#define SFLASH_RUID_TYPE                   (TPYE_CMD_ADDR_READ << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_RUID_CMD_LEN                (0x07)
#define SFLASH_RUID_ADDR_LEN               (31) // 4Byte dummy
#define SFLASH_RUID_DATA_LEN               (0x10 - 1) // the lengthe of RUID is 16 byte
#define SFLASH_RUID_CMD_CFG                (SFLASH_CMD_RUID | (SFLASH_RUID_TYPE << HALF_WORD_BITS))
#define SFLASH_RUID_LEN_CFG                (SFLASH_RUID_ADDR_LEN | (SFLASH_RUID_CMD_LEN<< BYTE_BITS) | (SFLASH_RUID_DATA_LEN << HALF_WORD_BITS))


//=====================================================================================================================
// To exit the QPI mode and return to Standard/Dual/Quad SPI mode, the "Disable QPI (FFH)" command must be issued. 
//=====================================================================================================================
#define SFLASH_CMD_CRMR                    (0xFF)
#define SFLASH_CRMR_TYPE                   (TPYE_CMD << QSPI_MEM_CMD_TYPE_SHIFT)
#define SFLASH_CRMR_CMD_LEN                (0x07)
#define SFLASH_CRMR_ADDR_LEN               (0x00)
#define SFLASH_CRMR_DATA_LEN               (0x02 - 1) 
#define SFLASH_CRMR_CMD_CFG                (SFLASH_CMD_CRMR | (SFLASH_CRMR_TYPE << HALF_WORD_BITS))
#define SFLASH_CRMR_LEN_CFG                (SFLASH_CRMR_ADDR_LEN | (SFLASH_CRMR_CMD_LEN << BYTE_BITS) | (SFLASH_CRMR_DATA_LEN << HALF_WORD_BITS))


//=====================================================================================================================
// CMD_LEN_DEFAULT
//=====================================================================================================================
#define SFLASH_CMD_LEN                     (0x07)



#endif /* __SFLASH_P25Q40SU_H__ */


