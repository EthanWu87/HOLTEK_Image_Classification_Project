/*************************************************************************************************************
 * @file    reg_cpto.h
 * @version V1.0 
 * @date    2020-08-15
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


#ifndef __REG_CPTO_H__
#define __REG_CPTO_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
#define CPTO_LLC_IV_NUMB     ( 0x02 )
#define CPTO_SW_IV_NUMB      ( 0x04 )


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IOM uint32_t CPTO_LLC_MODE;                  /* [0x00](RW) */
    __IOM uint32_t CPTO_LLC_KEY_READ_ADDR;         /* [0x04](RW) key initial value read from SRAM, address low 20 bits.*/
    __IOM uint32_t CPTO_LLC_DATA_WRITE_ADDR;       /* [0x08](RW) data PDU SRAM write address low 20bits.*/
    __IOM uint32_t CPTO_LLC_READ_ADDR;             /* [0x0C](RW) SRAM read address low 20bits*/
    __IOM uint32_t CPTO_LLC_CTRL_WRITE_ADDR;       /* [0x10](RW) ctrl PDU SRAM write address low 20bits.*/
    __IOM uint32_t CPTO_LLC_ADV_WRITE_ADDR;        /* [0x14](RW) adv channel PDU SRAM write address low 20bits.*/
    __IOM uint32_t CPTO_LLC_IV[CPTO_LLC_IV_NUMB];  /* [0x18~0x1C](RW) */
    __IOM uint32_t CPTO_LLC_MAX_LEN;               /* [0x20](RW) */
    __IOM uint32_t CPTO_LLC_ENC_PKT_CNT_HI;        /* [0x24] (RW) */
    __IOM uint32_t CPTO_LLC_ENC_PKT_CNT_LO;        /* [0x28] (RW) */
    __IOM uint32_t CPTO_LLC_DEC_PKT_CNT_HI;        /* [0x2C](RW) */
    __IOM uint32_t CPTO_LLC_DEC_PKT_CNT_LO;        /* [0x30](RW) */
    __IOM uint32_t CPTO_LLC_RX_HEADER_NUMB;        /* [0x34](RW) Valid when LLC works in bypass mode */
    __IOM uint32_t CPTO_LLC_CCM_MIC_DATA_LLC;      /* [0x38](RO) */
    __IOM uint32_t CPTO_LLC_CCM_MIC_DATA_SW;       /* [0x3C](RW) */
          uint32_t RESERVED_SECTOR1[16];           /* [0x18~0x1C] */
    
    __IOM uint32_t CPTO_SW_CFG;                    /* [0x80](RW) */
    __IOM uint32_t CPTO_SW_LEN;                    /* [0x84](RW) */
    __IOM uint32_t CPTO_SW_KEY_READ_ADDR;          /* [0x88](RW) */
    __IOM uint32_t CPTO_SW_DATA_WRITE_ADDR;        /* [0x8C](RW) */
    __IOM uint32_t CPTO_SW_DATA_READ_ADDR;         /* [0x90](RW) */
    __IOM uint32_t CPTO_SW_KEY_EXP_WRITE_ADDR;     /* [0x94](RW) */
    __IOM uint32_t CPTO_SW_CCM_CFG;                /* [0x98](RW) */
    __IOM uint32_t CPTO_SW_IV[CPTO_SW_IV_NUMB];    /* [0x9C-A8](RW) */
    __IOM uint32_t CPTO_SW_ENC_CNT_HI;             /* [0xAC] (RW) */
    __IOM uint32_t CPTO_SW_ENC_CNT_LO;             /* [0xB0] (RW) */
    __IOM uint32_t CPTO_SW_DEC_CNT_HI;             /* [0xB4](RW) */
    __IOM uint32_t CPTO_SW_DEC_CNT_LO;             /* [0xB8](RW) */
    __OM  uint32_t CPTO_SW_TRIG;                   /* [0xBC](WO) */
    __IM  uint32_t CPTO_STATUS;                    /* [0xC0](RO) */
          uint32_t RESERVED_SECTOR2[15];           /* [0xC4~0xFC] */

    __IOM uint32_t CPTO_INT_EN;                    /* [0x100](RW) */
    __OM  uint32_t CPTO_INT_CLR;                   /* [0x104](WO) */
    __IM  uint32_t CPTO_INT_FLAG;                  /* [0x108](RO) */

} stCPTO_Handle_t,*pstCPTO_Handle_t;




//=====================================================================================================================
// For all SRAM cfg Register
//=====================================================================================================================
#define CPTO_SRAM_ADDR_SHIFT               (0)
#define CPTO_SRAM_ADDR_MSK                 ((1U << 22) - 1)

//addr 0x200xxxxx and 4-byte aligned
#define IS_VALID_CPTO_SRAM_ADDR(ADDR) ((((ADDR) & 0xFFF00000)==0x20000000) && (((ADDR) & 0x3)==0))


//=====================================================================================================================
// [0x00](RW) CPTO_LLC_MODE Register 
//=====================================================================================================================
//=============================================================================
// CPTO_LLC_MODE[0] CPTO_LLC_MODE Define
#define CPTO_LLC_WORK_MODE_SHIFT           (0)
#define CPTO_LLC_WORK_MODE_MSK             ((1U << 2) - 1)

typedef enum
{
    EN_CPTO_LLC_MODE_ALL_BYPASS   = 0,
    EN_CPTO_LLC_MODE_TX_BYPASS    = 1,
    EN_CPTO_LLC_MODE_RX_BYPASS    = 2,
    EN_CPTO_LLC_MODE_NONE_BYPASS  = 3,

} EN_CPTO_LLC_WORK_MODE_T;

#define IS_VALID_CPTO_LLC_WORK_MODE(mode) ((mode) <= EN_CPTO_LLC_MODE_NONE_BYPASS)


//=====================================================================================================================
// [0x04](RW) CPTO_LLC_KEY_READ_ADDR Register 
//=====================================================================================================================


//=====================================================================================================================
// [0x08](RW) CPTO_LLC_DATA_WRITE_ADDR Register 
//=====================================================================================================================


//=====================================================================================================================
// [0x0C](RW) CPTO_LLC_READ_ADDR Register 
//=====================================================================================================================


//=====================================================================================================================
// [0x10](RW) CPTO_LLC_CTRL_WRITE_ADDR Register 
//=====================================================================================================================


//=====================================================================================================================
// [0x14](RW) CPTO_LLC_ADV_WRITE_ADDR Register 
//=====================================================================================================================


//=====================================================================================================================
// [0x18-0x1C](RW) CPTO_LLC_IV[2] Register 
//=====================================================================================================================


//=====================================================================================================================
// [0x20](RW) CPTO_LLC_MAX_LEN Register 
//=====================================================================================================================
//=============================================================================
// CPTO_LLC_MAX_LEN[15:8] CPTO_LLC_CTRL_MAX_LEN Define
#define CPTO_LLC_CTRL_MAX_LEN_SHIFT        (8)
#define CPTO_LLC_CTRL_MAX_LEN_MSK          ((1U << 8) - 1)

//=============================================================================
// CPTO_LLC_MAX_LEN[7:0] CPTO_LLC_DATA_MAX_LEN Define
#define CPTO_LLC_DATA_MAX_LEN_SHIFT        (0)
#define CPTO_LLC_DATA_MAX_LEN_MSK          ((1U << 8) - 1)


//=====================================================================================================================
// [0x24-0x28](RW) CPTO_LLC_ENC_PKT_CNT_HI / CPTO_LLC_ENC_PKT_CNT_LO Register 
//=====================================================================================================================
//=============================================================================
// CPTO_LLC_ENC_PKT_CNT_HI[7:0] CPTO_LLC_ENC_PKT_CNT_HI Define
#define CPTO_LLC_ENC_PKT_CNT_HI_SHIFT      (0)
#define CPTO_LLC_ENC_PKT_CNT_HI_MSK        ((1U << 7) - 1)

//=============================================================================
// CPTO_LLC_ENC_PKT_CNT_LO[31:0] CPTO_LLC_ENC_PKT_CNT_LO Define
#define CPTO_LLC_ENC_PKT_CNT_LO_SHIFT      (0)
#define CPTO_LLC_ENC_PKT_CNT_LO_MSK        (WORD_MSK)


//=====================================================================================================================
// [0x2C-0x30](RW) CPTO_LLC_DEC_PKT_CNT_HI / CPTO_LLC_DEC_PKT_CNT_LO Register 
//=====================================================================================================================
//=============================================================================
// CPTO_LLC_DEC_PKT_CNT_HI[7:0] CPTO_LLC_DEC_PKT_CNT_HI Define
#define CPTO_LLC_DEC_PKT_CNT_HI_SHIFT      (0)
#define CPTO_LLC_DEC_PKT_CNT_HI_MSK        ((1U << 7) - 1)

//=============================================================================
// CPTO_LLC_DEC_PKT_CNT_LO[31:0] CPTO_LLC_DEC_PKT_CNT_LO Define
#define CPTO_LLC_DEC_PKT_CNT_LO_SHIFT      (0)
#define CPTO_LLC_DEC_PKT_CNT_LO_MSK        (WORD_MSK)


//=====================================================================================================================
// [0x34](RW) CPTO_LLC_RX_HEADER_NUMB 
//=====================================================================================================================
//=============================================================================
// CPTO_LLC_RX_HEADER_NUMB[3:0] CPTO_LLC_RX_HEADER_NUMB Define
#define CPTO_LLC_RX_HEADER_NUMB_SHIFT      (0)
#define CPTO_LLC_RX_HEADER_NUMB_MSK        ((1U << 4) - 1)


//=====================================================================================================================
// [0x38](RO) CPTO_LLC_CCM_MIC_DATA 
//=====================================================================================================================
//=============================================================================
// CPTO_LLC_CCM_MIC_DATA[31:0] 
#define CPTO_LLC_CCM_MIC_DATA_SHIFT        (0)
#define CPTO_LLC_CCM_MIC_DATA_MSK          (WORD_MSK)


//=====================================================================================================================
// [0x3C](RW) CPTO_LLC_SRAM_WRITE_EN 
//=====================================================================================================================
//=============================================================================
// CPTO_LLC_SRAM_WRITE_EN[0]
#define CPTO_LLC_SRAM_WRITE_EN_SHIFT       (0)
#define CPTO_LLC_SRAM_WRITE_EN_MSK         ((1U << 1) - 1)


//=====================================================================================================================
// [0x80](RW) CPTO_SW_CFG 
//=====================================================================================================================
//=============================================================================
// CPTO_SW_CFG[9]: CPTO_SW_DWORD_UNCONVERT_EN
// CPTO_SW_DWORD_UNCONVERT_EN = 1:  DWORD not convert to 2 WORDs
// CPTO_SW_DWORD_UNCONVERT_EN = 0 : DWORD convert to 2 WORDs
#define CPTO_SW_DWORD_UNCONVERT_EN_SHIFT   (9)
#define CPTO_SW_DWORD_UNCONVERT_EN_MSK     ((1U << 1) - 1)

//=============================================================================
// CPTO_SW_CFG[8]: CPTO_SW_WORD_CONVERT_EN
// CPTO_SW_WORD_CONVERT_EN = 1:  WORD convert to 2 bytes
// CPTO_SW_WORD_CONVERT_EN = 0 : WORD convert to 2 bytes
#define CPTO_SW_WORD_CONVERT_EN_SHIFT      (8)
#define CPTO_SW_WORD_CONVERT_EN_MSK        ((1U << 1) - 1)

//=============================================================================
// CPTO_SW_CFG[7:6]: CPTO_SW_KEY_SIZE
#define CPTO_SW_KEY_SIZE_SHIFT             (6)
#define CPTO_SW_KEY_SIZE_MSK               ((1U << 2) - 1)

typedef enum
{
    CPTO_SW_KEY_128BIT = 0,
    CPTO_SW_KEY_192BIT = 1,
    CPTO_SW_KEY_256BIT = 2,

} EN_CPTO_SW_KEY_SIZE_T;

//=============================================================================
// CPTO_SW_CFG[5:4]: CPTO_SW_AES_MODE_MSK
#define CPTO_SW_AES_MODE_SHIFT             (4)
#define CPTO_SW_AES_MODE_MSK               ((1U << 2) - 1)

typedef enum
{
    CPTO_SW_AES_ENCRYPT = 0,
    CPTO_SW_AES_DECRYPT_WITH_DECKEY = 1,
    CPTO_SW_AES_DECRYPT_WITH_ENCKEY = 2,
    CPTO_SW_AES_GEN_KEY             = 3,

} EN_CPTO_SW_AES_MODE_T;

//=============================================================================
// CPTO_SW_CFG[3]: CPTO_SW_ENCRYP_SEL
#define CPTO_SW_ENCRYP_SEL_SHIFT           (3)
#define CPTO_SW_ENCRYP_SEL_MSK             ((1U << 1) - 1)

typedef enum
{
    CPTO_SW_ENCRYPT_MODE = 0,
    CPTO_SW_DECRYPT_MODE = 1,

} EN_CPTO_SW_ENCRYPT_T;

//=============================================================================
// CPTO_SW_CFG[2:0]: CPTO_SW_MODE_SEL
#define CPTO_SW_MODE_SEL_SHIFT             (0)
#define CPTO_SW_MODE_SEL_MSK               ((1U << 3) - 1)

typedef enum
{
    CPTO_SW_MODE_DIS       = 0,
    CPTO_SW_MODE_AES       = 1,
    CPTO_SW_MODE_CCM_4BYTE = 2,
    CPTO_SW_MODE_CCM_8BYTE = 3,
    CPTO_SW_MODE_CMAC      = 4,
    CPTO_SW_MODE_ECB       = 5,
    CPTO_SW_MODE_CBC       = 6,
    CPTO_SW_MODE_CTR       = 7,

} EN_CPTO_SW_MODE_T;

typedef struct
{
    uint32_t ubit2SWMode          : 3;
    uint32_t ubit1EncOrDec        : 1;
    uint32_t ubit2AesMode         : 2;
    uint32_t ubit2KeySize         : 2;
    uint32_t ubit1WordConvertEn   : 1;
    uint32_t ubit1DWordConvertDis : 1;

} stCptoSwCfg_t,*pstCptoSwCfg_t;

typedef union
{
    uint32_t      u32Cfg;
    stCptoSwCfg_t stCfg;
    
} unCptoSwCfg_t, *punCptoSwCfg_t;


//=====================================================================================================================
// [0x84](RW) CPTO_SW_LEN 
//=====================================================================================================================
//=============================================================================
// CPTO_SW_LEN[11:0]: REG_CPTO_SW_DATA_LEN
#define CPTO_SW_DATA_LEN_SHIFT             (0)
#define CPTO_SW_DATA_LEN_MSK               ((1U << 12) - 1)


//=====================================================================================================================
// [0x88~94](RW) CPTO_SW_KEY_READ_ADDR / CPTO_SW_DATA_WRITE_ADDR 
//             / CPTO_SW_DATA_READ_ADDR / CPTO_SW_KEY_EXP_WRITE_ADDR
//=====================================================================================================================


//=====================================================================================================================
// [0x98](RW) CPTO_SW_CCM_CFG 
//=====================================================================================================================
//=============================================================================
// CPTO_SW_CCM_CFG[4] : CPTO_SW_RBUS_DIR
#define CPTO_SW_RBUS_DIR_SHIFT             (4)
#define CPTO_SW_RBUS_DIR_MSK               ((1U << 1) - 1)

typedef enum
{
    EN_CPTO_RBUS_DIR_SLV_TO_MST   = 0x00,
    EN_CPTO_RBUS_DIR_MST_TO_SLV   = 0x01,
} EN_CPTO_SW_RBUS_DIR_T;

//=============================================================================
// CPTO_SW_CCM_CFG[3:2] : CPTO_SW_CCM_PDU_TYPE
#define CPTO_SW_CCM_LLC_PDU_TYPE_SHIFT     (2)
#define CPTO_SW_CCM_LLC_PDU_TYPE_MSK       ((1U << 2) - 1)

typedef enum
{
    EN_CPTO_SW_CCM_PDU_TYPE_DATA_CONTINUE_OR_EMPTY = 0x01,
    EN_CPTO_SW_CCM_PDU_TYPE_DATA_START_OR_COMPLETE = 0x02,
    EN_CPTO_SW_CCM_PDU_TYPE_CTRL  = 0x03,

} EN_CPTO_SW_CCM_PDU_TYPE_T;

//=============================================================================
// CPTO_SW_CCM_CFG[1:0] : CPTO_SW_CCM_PKT_TYPE
#define CPTO_SW_CCM_PKT_TYPE_SHIFT         (0)
#define CPTO_SW_CCM_PKT_TYPE_MSK           ((1U << 2) - 1)


//=====================================================================================================================
// [0x9C~A8](RW) CPTO_SW_IV[4] 
//=====================================================================================================================


//=====================================================================================================================
// [0xAC-0xB0](RW) CPTO_SW_ENC_CNT_HI / CPTO_SW_ENC_CNT_LO
//=====================================================================================================================
//=============================================================================
// CPTO_SW_ENC_CNT_HI[6:0]
#define CPTO_SW_ENC_CNT_HI_SHIFT           (0)
#define CPTO_SW_ENC_CNT_HI_MSK             ((1U << 7) - 1)

//=============================================================================
// CPTO_SW_ENC_CNT_LO[31:0]
#define CPTO_SW_ENC_CNT_LO_SHIFT           (0)
#define CPTO_SW_ENC_CNT_LO_MSK             (WORD_MSK)


//=====================================================================================================================
// [0xB4-0xB8](RW) CPTO_SW_DEC_CNT_HI / CPTO_SW_DEC_CNT_LO
//=====================================================================================================================
//=============================================================================
// CPTO_SW_DEC_CNT_HI[6:0]
#define CPTO_SW_DEC_CNT_HI_SHIFT           (0)
#define CPTO_SW_DEC_CNT_HI_MSK             ((1U << 7) - 1)

//=============================================================================
// CPTO_SW_DEC_CNT_LO[31:0]
#define CPTO_SW_DEC_CNT_LO_SHIFT           (0)
#define CPTO_SW_DEC_CNT_LO_MSK             (WORD_MSK)


//=====================================================================================================================
// [0xBC](WO) CPTO_SW_TRIG
//=====================================================================================================================
//=============================================================================
// CPTO_SW_TRIG[0] CPTO_SW_START_EN Define
#define CPTO_SW_TRIG_START_EN_SHIFT        (0)
#define CPTO_SW_TRIG_START_EN_MSK          ((1U << 1) - 1)


//=====================================================================================================================
// [0xC0](RO) CPTO_STATUS
//=====================================================================================================================
#define CPTO_SW_STA_ALL_MSK                ((1U << 13) - 1)

//=============================================================================
// CPTO_STATUS[12:8] CPTO_SW_AES_STA Define
#define CPTO_SW_AES_STA_SHIFT              (8)
#define CPTO_SW_AES_STA_MSK                ((1U << 5) - 1)

typedef enum
{
    EN_CPTO_AES_STA_MIDLE     = 0x00,
    EN_CPTO_AES_STA_MINIT     = 0x01,
    EN_CPTO_AES_STA_MSTA0     = 0x02,
    EN_CPTO_AES_STA_MSTA1     = 0x03,
    EN_CPTO_AES_STA_MSTA2     = 0x04,
    EN_CPTO_AES_STA_MSTA3     = 0x05,
    EN_CPTO_AES_STA_MSTA4     = 0x06,
    EN_CPTO_AES_STA_MSTA5     = 0x07,
    EN_CPTO_AES_STA_MSTA6     = 0x08,
    EN_CPTO_AES_STA_MSTA7     = 0x09,
    EN_CPTO_AES_STA_MSTA8     = 0x0A,
    EN_CPTO_AES_STA_MSTA9     = 0x0B,
    EN_CPTO_AES_STA_MSTA10    = 0x0C,
    EN_CPTO_AES_STA_MSTA11    = 0x0D,
    EN_CPTO_AES_STA_MSTA12    = 0x0E,
    EN_CPTO_AES_STA_MSTA13    = 0x0F,
    EN_CPTO_AES_STA_MSTA14    = 0x10,
    EN_CPTO_AES_STA_MEND      = 0x11,
    EN_CPTO_AES_STA_KRND0     = 0x14,
    EN_CPTO_AES_STA_KRND1     = 0x15,
    EN_CPTO_AES_STA_KRND2     = 0x16,
    EN_CPTO_AES_STA_KRND3     = 0x17,
    EN_CPTO_AES_STA_KRND4     = 0x18,
    EN_CPTO_AES_STA_KRND5     = 0x19,
    EN_CPTO_AES_STA_KRND6     = 0x1A,
    EN_CPTO_AES_STA_KRND7     = 0x1B,
    EN_CPTO_AES_STA_KRND8     = 0x1C,
    EN_CPTO_AES_STA_KRND9     = 0x1D,
    EN_CPTO_AES_STA_KEND      = 0x1E,

}  EN_CPTO_AES_STA_T;

//=============================================================================
// CPTO_STATUS[7:4] CPTO_SW_SUB_STA Define
#define CPTO_SW_SUB_STA_SHIFT             (4)
#define CPTO_SW_SUB_STA_MSK               ((1U << 4) - 1)

typedef enum
{
    EN_CPTO_SW_SSTA_IDLE    = 0x00,
    EN_CPTO_SW_SSTA_FPRE    = 0x01,
    EN_CPTO_SW_SSTA_OMEM    = 0x05,
    EN_CPTO_SW_SSTA_CAES    = 0x06,

}  EN_CPTO_SUB_STA_T;

//=============================================================================
// CPTO_STATUS[3:0] CPTO_SW_MAIN_STA  Define
#define CPTO_SW_MAIN_STA_SHIFT              (0)
#define CPTO_SW_MAIN_STA_MSK                ((1U << 4) - 1)

typedef enum
{
    EN_CPTO_SW_MSTA_IDLE    = 0x00,
    EN_CPTO_SW_MSTA_CHK     = 0x01,
    
    EN_CPTO_SW_MSTA_PROC    = 0x02,
    EN_CPTO_SW_MSTA_FINISH  = 0x03,

}  EN_CPTO_MAIN_STA_T;


//=====================================================================================================================
// [0x100~0x10C] CPTO_INT_EN(RW) / CPTO_INT_CLR(WO) / CPTO_INT_FLAG(RO)
//=====================================================================================================================
#define CPTO_HW_DONE_SHIFT            (0)
#define CPTO_MIC_FAILED_SHIFT         (1)
#define CPTO_PACKAGE_EMPTY_SHIFT      (2)
#define CPTO_LEN_LIMITE_SHIFT         (3)
#define CPTO_RECV_HEADER_SHIFT        (4)   //  Valid when LLC works in bypass mode
#define CPTO_RECV_DONE_SHIFT          (5)   //  Valid when LLC works in bypass mode
#define CPTO_AES_DONE_SHIFT           (6)
#define CPTO_SW_DONE_SHIFT            (7)
#define CPTO_SW_BREAK_SHIFT           (8)

typedef enum
{
    CPTO_INT_HW_DONE            = (1U << CPTO_HW_DONE_SHIFT),
    CPTO_INT_MIC_FAILED         = (1U << CPTO_MIC_FAILED_SHIFT),
    CPTO_INT_PACKAGE_EMPTY      = (1U << CPTO_PACKAGE_EMPTY_SHIFT),
    CPTO_INT_LEN_LIMITE         = (1U << CPTO_LEN_LIMITE_SHIFT),
    
    CPTO_INT_RECV_HEADER        = (1U << CPTO_RECV_HEADER_SHIFT),
    CPTO_INT_RECV_DONE          = (1U << CPTO_RECV_DONE_SHIFT),
    CPTO_INT_AES_DONE           = (1U << CPTO_AES_DONE_SHIFT),
    CPTO_INT_SW_DONE            = (1U << CPTO_SW_DONE_SHIFT),

    CPTO_INT_SW_BREAK           = (1U << CPTO_SW_BREAK_SHIFT)

} EN_CPTO_INT_FLAG_T;

#define CPTO_ALL_INT_MASK                  ((1U << 9) - 1)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __REG_CPTO_H__ */


