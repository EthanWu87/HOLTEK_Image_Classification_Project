/*************************************************************************************************************
 * @file    reg_rtc_pdw.h
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



#ifndef __REG_RTC_PDW_H__
#define __REG_RTC_PDW_H__


#ifdef __cplusplus
extern "C" {
#endif




//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IOM uint32_t RTC_PRESCALE;             /* [0x00](RW) */
    __OM  uint32_t RTC_PDW_CTRL;             /* [0x04](WO) */
    __IOM uint32_t RTC_PDW_SW_RST_EN;        /* [0x08](RW) */
          uint32_t RESERVED0[13];            /* [0x0C~0x3C] */

    __IOM uint32_t RTC_CLK_SRC_SEL;          /* [0x40](RW) */
    __IOM uint32_t DCXO_LCLK_CFG;            /* [0x44](RW) */
    __IOM uint32_t DCXO_LCLK_PARA_CFG;       /* [0x48](RW) */
    __IOM uint32_t DCXO_LCLK_BUF;            /* [0x4C](RW) */
    __IM  uint32_t RTC_CLK_SRC_STA;          /* [0x50](RO) */
    __IM  uint32_t DCXO_LCLK_STA;            /* [0x54](RO) */
    __IM  uint32_t DCXO_LCLK_CFG_STA;        /* [0x58](RO) */
    __IM  uint32_t DCXO_LCLK_BUF_STA;        /* [0x5C](RO) */
    __OM  uint32_t DCXO_LCLK_CTRL;           /* [0x60](WO) */
          uint32_t RESERVED1[9];             /* [0x64~0x84] */

    __IOM uint32_t LDO_RET_VOLT;             /* [0x88](RW) */
    __IM  uint32_t LDO_RET_VOLT_STA;         /* [0x8C](RO) */
    __OM  uint32_t LDO_RET_VOLT_EN;          /* [0x90](WO) */
          uint32_t RESERVED2[13];            /* [0x94~0xC4] */

    __IOM uint32_t RTC_PDW_SW_FLAG;          /* [0xC8](RW) */
    __IM  uint32_t RTC_PDW_SW_FLAG_STA;      /* [0xCC](RO) */
    __OM  uint32_t RTC_PDW_SW_FLAG_CTRL;     /* [0xD0](WO) */

} stRTC_PDW_Handle_t, *pstRTC_PDW_Handle_t;




//=====================================================================================================================
// [0x00](RW) RTC_PRESCALE
//=====================================================================================================================
//=============================================================================
// RTC_PRESCALE[11:0] RTC_PRESCALE_VAL
#define RTC_PRESCALE_VAL_SHIFT             (0)
#define RTC_PRESCALE_VAL_MSK               ((0x01 << 12) - 1)
#define RTC_PRESCALE_VAL_MAX               ((0x01 << 12) - 1)


//=====================================================================================================================
// [0x04](WO) RTC_PDW_CTRL
//=====================================================================================================================
//=============================================================================
// RTC_PDW_CTRL[4:0]
#define RTC_TRIG_PRESCALE_SHIFT            (4)
#define RTC_TRIG_OVERFLOW_SHIFT            (3)
#define RTC_TRIG_CLR_SHIFT                 (2)
#define RTC_TRIG_STOP_SHIFT                (1)
#define RTC_TRIG_START_SHIFT               (0)


//=====================================================================================================================
// [0x08](RW) RTC_PDW_SW_RST_EN
//=====================================================================================================================
//=============================================================================
// RTC_PDW_SW_RST_EN[0] RTC_PDW_SW_RST_EN
#define RTC_PDW_SW_RST_EN_SHIFT            (0)
#define RTC_PDW_SW_RST_EN_MSK              ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x40](RW) RTC_CLK_SRC_SEL
//=====================================================================================================================
//=============================================================================
// RTC_CLK_SRC_SEL[0] RTC_CLK_SRC_SEL
#define RTC_CLK_SRC_SEL_SHIFT              (0)
#define RTC_CLK_SRC_SEL_MSK                ((0x01 << 1) - 1)

typedef enum
{
    EN_RTC_CLK_SRC_RC_LCLK   = 0,
    EN_RTC_CLK_SRC_DCXO_LCLK = 1
} EN_RTC_CLK_SRC_T;

#define IS_VALID_RTC_CLK_SRC(SRC)   ((SRC) == EN_RTC_CLK_SRC_DCXO_LCLK \
                                  || (SRC) == EN_RTC_CLK_SRC_RC_LCLK)


//=====================================================================================================================
// [0x44](RW) DCXO_LCLK_CFG
//=====================================================================================================================
//=============================================================================
// DCXO_LCLK_CFG[1] DCXO_LCLK_OUTPUT_CFG
#define DCXO_LCLK_OUTPUT_CFG_SHIFT         (1)
#define DCXO_LCLK_OUTPUT_CFG_MSK           ((0x01 << 1) - 1)

//=============================================================================
// DCXO_LCLK_CFG[0] DCXO_LCLK_POWER_CFG
#define DCXO_LCLK_POWER_CFG_SHIFT          (0)
#define DCXO_LCLK_POWER_CFG_MSK            ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x48](RW) DCXO_LCLK_PARA_CFG
//=====================================================================================================================
//=============================================================================
// DCXO_LCLK_PARA_CFG[29:22] DCXO_LCLK_BKUP
#define DCXO_LCLK_BKUP_SHIFT               (22)
#define DCXO_LCLK_BKUP_MSK                 ((0x01 << 8) - 1)

//=============================================================================
// DCXO_LCLK_PARA_CFG[21:19] DCXO_LCLK_IB
#define DCXO_LCLK_IB_SHIFT                 (19)
#define DCXO_LCLK_IB_MSK                   ((0x01 << 3) - 1)
#define DCXO_LCLK_IB_3                     (3)

//=============================================================================
// DCXO_LCLK_PARA_CFG[18:16] DCXO_LCLK_NGM
#define DCXO_LCLK_NGM_SHIFT                (16)
#define DCXO_LCLK_NGM_MSK                  ((0x01 << 3) - 1)
#define DCXO_LCLK_NGM_3                    (3)

//=============================================================================
// DCXO_LCLK_PARA_CFG[15:8] DCXO_LCLK_CAPL
#define DCXO_LCLK_CAPL_SHIFT               (8)
#define DCXO_LCLK_CAPL_MSK                 ((0x01 << 8) - 1)

//=============================================================================
// DCXO_LCLK_PARA_CFG[7:0] DCXO_LCLK_CAPR
#define DCXO_LCLK_CAPR_SHIFT               (0)
#define DCXO_LCLK_CAPR_MSK                 ((0x01 << 8) - 1)
#define DCXO_LCLK_CAP_6PF                  (60)


//=====================================================================================================================
// [0x4C](RW) DCXO_LCLK_BUF
//=====================================================================================================================
//=============================================================================
// DCXO_LCLK_BUF[5:3] DCXO_LCLK_POS_BUF
#define DCXO_LCLK_POS_BUF_SHIFT            (3)
#define DCXO_LCLK_POS_BUF_MSK              ((0x01 << 3) - 1)

//=============================================================================
// DCXO_LCLK_BUF[2:0] DCXO_LCLK_NEG_BUF
#define DCXO_LCLK_NEG_BUF_SHIFT            (0)
#define DCXO_LCLK_NEG_BUF_MSK              ((0x01 << 3) - 1)

#define DCXO_LCLK_BUF_3                    (3)

typedef struct
{
    uint8_t u8PosBuf;
    uint8_t u8NegBuf;

} stDCXOBuf_t, *pstDcxoBuf_t;


//=====================================================================================================================
// [0x50](RO) RTC_CLK_SRC_STA
//=====================================================================================================================
//=============================================================================
// RTC_CLK_SRC_STA[0] RTC_CLK_SRC_STA
#define RTC_CLK_SRC_STA_SHIFT              (0)
#define RTC_CLK_SRC_STA_MSK                ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x54](RW) DCXO_LCLK_STA
//=====================================================================================================================
//=============================================================================
// DCXO_LCLK_STA[1] DCXO_LCLK_OUTPUT_STA
#define DCXO_LCLK_OUTPUT_STA_SHIFT         (1)
#define DCXO_LCLK_OUTPUT_STA_MSK           ((0x01 << 1) - 1)

//=============================================================================
// DCXO_LCLK_STA[0] DCXO_LCLK_POWER_STA
#define DCXO_LCLK_POWER_STA_SHIFT          (0)
#define DCXO_LCLK_POWER_STA_MSK            ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x58](RO) DCXO_LCLK_CFG_STA
//=====================================================================================================================
//=============================================================================
// DCXO_LCLK_CFG_STA[29:0] DCXO_LCLK_CFG_STA
#define DCXO_LCLK_CFG_STA_SHIFT            (0)
#define DCXO_LCLK_CFG_STA_MSK              ((0x01 << 30) - 1)


//=====================================================================================================================
// [0x5C](RO) DCXO_LCLK_BUF_STA
//=====================================================================================================================
//=============================================================================
// DCXO_LCLK_BUF_STA[29:0] DCXO_LCLK_BUF_STA
#define DCXO_LCLK_BUF_STA_SHIFT            (0)
#define DCXO_LCLK_BUF_STA_MSK              ((0x01 << 6) - 1)


//=====================================================================================================================
// [0x60](WO) DCXO_LCLK_CTRL
//=====================================================================================================================
//=============================================================================
// DCXO_LCLK_CTRL[3] DCXO_LCLK_OUTPUT_EN
#define DCXO_LCLK_OUTPUT_EN_SHIFT          (3)
#define DCXO_LCLK_OUTPUT_EN_MSK            ((0x01 << 1) - 1)

//=============================================================================
// DCXO_LCLK_CTRL[2] DCXO_LCLK_POWER_EN
#define DCXO_LCLK_POWER_EN_SHIFT           (2)
#define DCXO_LCLK_POWER_EN_MSK             ((0x01 << 1) - 1)

//=============================================================================
// DCXO_LCLK_CTRL[1] DCXO_LCLK_CFG_EN
#define DCXO_LCLK_CFG_EN_SHIFT             (1)
#define DCXO_LCLK_CFG_EN_MSK               ((0x01 << 1) - 1)

//=============================================================================
// DCXO_LCLK_CTRL[0] RTC_CLK_SRC_EN
#define RTC_CLK_SRC_EN_SHIFT               (0)
#define RTC_CLK_SRC_EN_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x88](RW) LDO_RET_VOLT
//=====================================================================================================================
//=============================================================================
// LDO_RET_VOLT[2:0] RTC_LDO_RET_VOLT
#define RTC_LDO_RET_VOLT_SHIFT             (0)
#define RTC_LDO_RET_VOLT_MSK               ((0x01 << 3) - 1)

typedef enum
{
    EN_RTC_LDO_RET_1100mV = 0,
    EN_RTC_LDO_RET_1050mV = 1,
    EN_RTC_LDO_RET_1000mV = 2,
    EN_RTC_LDO_RET_950mV  = 3,
    EN_RTC_LDO_RET_900mV  = 4,
    EN_RTC_LDO_RET_850mV  = 5,
    EN_RTC_LDO_RET_800mV  = 6,
    EN_RTC_LDO_RET_750mV  = 7,

} EN_RTC_LDO_RET_VOLT_T;


//=====================================================================================================================
// [0x8C](RO) LDO_RET_VOLT_STA
//=====================================================================================================================
//=============================================================================
// LDO_RET_VOLT_STA[2:0] RTC_LDO_RET_VOLT_STA
#define RTC_LDO_RET_VOLT_STA_SHIFT         (0)
#define RTC_LDO_RET_VOLT_STA_MSK           ((0x01 << 3) - 1)


//=====================================================================================================================
// [0x90](WO) LDO_RET_VOLT_EN
//=====================================================================================================================
//=============================================================================
// LDO_RET_VOLT_EN[0] RTC_LDO_RET_VOLT_EN
#define RTC_LDO_RET_VOLT_EN_SHIFT         (0)
#define RTC_LDO_RET_VOLT_EN_MSK           ((0x01 << 1) - 1)


//=====================================================================================================================
// [0xC8](RW) RTC_PDW_SW_FLAG
//=====================================================================================================================
//=============================================================================
// RTC_PDW_SW_FLAG[31:0] RTC_PDW_SW_FLAG
#define RTC_PDW_SW_FLAG_SHIFT              (0)
#define RTC_PDW_SW_FLAG_MSK                (WORD_MSK)


//=====================================================================================================================
// [0xCC](RO) RTC_PDW_SW_FLAG_STA
//=====================================================================================================================
//=============================================================================
// RTC_PDW_SW_FLAG_STA[31:0] RTC_PDW_SW_FLAG_STA
#define RTC_PDW_SW_FLAG_STA_SHIFT          (0)
#define RTC_PDW_SW_FLAG_STA_MSK            (WORD_MSK)


//=====================================================================================================================
// [0xD0](WO) RTC_PDW_SW_FLAG_CTRL
//=====================================================================================================================
//=============================================================================
// RTC_PDW_SW_FLAG_CTRL[0] RTC_PDW_SW_FLAG_CTRL
#define RTC_PDW_SW_FLAG_CTRL_SHIFT         (0)
#define RTC_PDW_SW_FLAG_CTRL_MSK           ((0x01 << 1) - 1)




#ifdef __cplusplus
}
#endif

#endif /* __REG_RTC_PDW_H__ */


