/*************************************************************************************************************
 * @file    reg_crg.h
 * @version V1.1
 * @date    2022-01-11
 * @brief   Clock and Reset register
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


#ifndef __REG_CRG_H__
#define __REG_CRG_H__


#ifdef __cplusplus
extern "C" {
#endif


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IOM uint32_t CRG_CLK_CFG;            /* [0x00](RW) */
    __IM  uint32_t CRG_SYS_CLK_SRC;        /* [0x04](RO) */
    __OM  uint32_t CRG_SYS_CLK_CTRL;       /* [0x08](WO) */
    __IM  uint32_t CRG_CLK_DIV_STA;        /* [0x0C](RO) */
    __IOM uint32_t CRG_CLK_DIV_CFG0;       /* [0x10](RW) */
    __IOM uint32_t CRG_CLK_DIV_CFG1;       /* [0x14](RW) */
    __IOM uint32_t CRG_CLK_DIV_CFG2;       /* [0x18](RW) */
    __IOM uint32_t CRG_CLK_EXT_EN0;        /* [0x1C](RW) */
    __IOM uint32_t CRG_CLK_EXT_EN1;        /* [0x20](RW) */
    __IOM uint32_t CRG_CLK_EN0;            /* [0x24](RW) */
    __IOM uint32_t CRG_CLK_EN1;            /* [0x28](RW) */
          uint32_t RESERVED[21];           /* [0x2C~0x7C] */

    __IOM uint32_t CRG_PERI_SW_RST_EN0;    /* [0x80](RW) */
    __IOM uint32_t CRG_PERI_SW_RST_EN1;    /* [0x84](RW) */
    __OM  uint32_t CRG_MP_SW_RST_EN;       /* [0x88](WO) */
    __OM  uint32_t CRG_CP_SW_RST_EN;       /* [0x8C](WO) */
    __OM  uint32_t CRG_SYS_SW_RST_EN;      /* [0x90](WO) */
    __IM  uint32_t CRG_RST_FLG;            /* [0x94](RO) */
    __OM  uint32_t CRG_RST_CLR;            /* [0x98](WO) */
    __IOM uint32_t CRG_WDT1_RST_EN;        /* [0x9C](RW) */
          uint32_t RESERVED1[24];          /* [0xA0~0xFC] */

    __IOM uint32_t CRG_CALIB_CTRL;         /* [0x100](RW) */
    __IM  uint32_t CRG_CALIB_32K_PERIOD;   /* [0x104](RO) */
          uint32_t RESERVED2[30];          /* [0x108~0x17C] */

    __IOM uint32_t CRG_TEST_CLK_REUSE;     /* [0x180](RW) */

} stCRG_Handle_t, *pstCRG_Handle_t;


//=====================================================================================================================
// [0x00](RW) CRG_CLK_CFG
//=====================================================================================================================
//=============================================================================
// CRG_CLK_CFG[5:4] CRG_PLL128M_CLK_DIV Define
#define CRG_PLL128M_CLK_DIV_SHIFT       (4)
#define CRG_PLL128M_CLK_DIV_MSK         ((0x01 << 2) - 1)

typedef enum
{
    EN_PLL128M_CLK_DIV_1  = 0,
    EN_PLL128M_CLK_DIV_2  = 1,
    EN_PLL128M_CLK_DIV_4  = 2,

} EN_PLL128M_CLK_DIV_T;

#define IS_VALID_PLL128M_CLK_DIV(DIV)   (EN_PLL128M_CLK_DIV_4 >= (DIV))

//=============================================================================
// CRG_CLK_CFG[3:2] CRG_LPWR_CLK_SRC_SEL Define
#define CRG_LPWR_CLK_SRC_SEL_SHIFT         (2)
#define CRG_LPWR_CLK_SRC_SEL_MSK           ((0x01 << 2) - 1)

typedef enum
{
    LPWR_CLK_RC_LCLK            = 0,
    LPWR_CLK_DCXO_LCLK          = 1,
    LPWR_CLK_RC_HCLK_DIV_LCLK   = 2,
    LPWR_CLK_DCXO_HCLK_DIV_LCLK = 3,

} EN_LPWR_CLK_SRC_T;

#define IS_VALID_LPWR_CLK_SRC(SRC)   (LPWR_CLK_DCXO_HCLK_DIV_LCLK >= (SRC))

//=============================================================================
// CRG_CLK_CFG[1] CRG_HCLK_DIV_LCLK_EN Define
#define CRG_HCLK_DIV_LCLK_EN_SHIFT         (1)
#define CRG_HCLK_DIV_LCLK_EN_MSK           ((0x01 << 1) - 1)

//=============================================================================
// CRG_CLK_CFG[0] CRG_DCXO_HCLK_FREQ_SEL Define
#define CRG_DCXO_HCLK_FREQ_SEL_SHIFT       (0)
#define CRG_DCXO_HCLK_FREQ_SEL_MSK         ((0x01 << 1) - 1)

typedef enum
{
    EN_DCXO_HCLK_FREQ_16M = 0,
    EN_DCXO_HCLK_FREQ_32M = 1,

} EN_DCXO_HCLK_FREQ_T;

#define IS_VALID_DCXO_HCLK_FREQ(FREQ)   ((FREQ) == EN_DCXO_HCLK_FREQ_16M \
                                      || (FREQ) == EN_DCXO_HCLK_FREQ_32M)


//=====================================================================================================================
// [0x04](RO) CRG_SYS_CLK_SRC
//=====================================================================================================================
//=============================================================================
// CRG_SYS_CLK_SRC[1:0] CRG_SYS_CLK_SRC Define
#define CRG_SYS_CLK_SRC_SHIFT              (0)
#define CRG_SYS_CLK_SRC_MSK                ((0x01 << 2) - 1)

typedef enum
{
    SYS_CLK_SRC_RC_HCLK         = 0,
    SYS_CLK_SRC_DCXO_HCLK       = 3,
    SYS_CLK_SRC_DCXO_HCLK_DIV2  = 2,
    SYS_CLK_SRC_PLL_CLK         = 1,

} EN_SYS_CLK_SRC_T;


//=====================================================================================================================
// [0x08](WO) CRG_SYS_CLK_CTRL
//=====================================================================================================================
//=============================================================================
// CRG_SYS_CLK_CTRL[3:0] CRG_SYS_CLK_SEL Define
#define CRG_SYS_CLK_SEL_SHIFT              (0)
#define CRG_SYS_CLK_SEL_MSK                ((0x01 << 4) - 1)

typedef enum
{
    SYS_CLK_RC_HCLK         = 0x01,
    SYS_CLK_DCXO_HCLK       = 0x02,
    SYS_CLK_DCXO_HCLK_DIV2  = 0x04,
    SYS_CLK_PLL_CLK         = 0x08,

} EN_SYS_CLK_SEL_T;

#define IS_VALID_SYS_CLK_SEL(SEL)   (((SEL) == SYS_CLK_RC_HCLK)        \
                                  || ((SEL) == SYS_CLK_DCXO_HCLK)      \
                                  || ((SEL) == SYS_CLK_DCXO_HCLK_DIV2) \
                                  || ((SEL) == SYS_CLK_PLL_CLK))


//=====================================================================================================================
// [0x0C](RO) CRG_CLK_DIV_STA
//=====================================================================================================================
//=============================================================================
// CRG_CLK_DIV_STA[16:14] CRG_CPTO1_CLK_DIV_STA_SHIFT Define
#define CRG_CPTO1_CLK_DIV_STA_SHIFT        (14)

//=============================================================================
// CRG_CLK_DIV_STA[13:11] CRG_CPTO0_CLK_DIV_STA Define
#define CRG_CPTO0_CLK_DIV_STA_SHIFT        (11)
#define CRG_CPTO_CLK_DIV_STA_MSK           ((0x01 << 3) - 1)

//=============================================================================
// CRG_CLK_DIV_STA[10:8] CRG_LLC_CLK_DIV_STA Define
#define CRG_LLC_CLK_DIV_STA_SHIFT          (8)
#define CRG_LLC_CLK_DIV_STA_MSK            ((0x01 << 3) - 1)

//=============================================================================
// CRG_CLK_DIV_STA[7:5] CRG_CP_AHB_CLK_DIV_STA Define
#define CRG_CP_AHB_CLK_DIV_STA_SHIFT       (5)
#define CRG_CP_AHB_CLK_DIV_STA_MSK         ((0x01 << 3) - 1)

//=============================================================================
// CRG_CLK_DIV_STA[4:2] CRG_MP_APB_CLK_DIV_STA Define
#define CRG_MP_APB_CLK_DIV_STA_SHIFT       (2)
#define CRG_MP_APB_CLK_DIV_STA_MSK         ((0x01 << 3) - 1)

//=============================================================================
// CRG_CLK_DIV_STA[1:0] CRG_MP_AHB_CLK_DIV_STA Define
#define CRG_MP_AHB_CLK_DIV_STA_SHIFT       (0)
#define CRG_MP_AHB_CLK_DIV_STA_MSK         ((0x01 << 2) - 1)


//=====================================================================================================================
// [0x10](RW) CRG_CLK_DIV_CFG0
//=====================================================================================================================
//=============================================================================
// CRG_CLK_DIV_CFG0[27:25] CRG_CPTO1_CLK_DIV Define
#define CRG_CPTO1_CLK_DIV_SHIFT            (25)
#define CRG_CPTO_CLK_DIV_MSK               ((0x01 << 3) - 1)

typedef enum
{
    EN_CPTO_CLK_DIV_1    = 0,
    EN_CPTO_CLK_DIV_2    = 1,
    EN_CPTO_CLK_DIV_4    = 2,
    EN_CPTO_CLK_DIV_8    = 3,

} EN_CPTO_CLK_DIV_T;

#define IS_VALID_CPTO_CLK_DIV(DIV)   (((DIV) == EN_CPTO_CLK_DIV_1) \
                                   || ((DIV) == EN_CPTO_CLK_DIV_2) \
                                   || ((DIV) == EN_CPTO_CLK_DIV_4) \
                                   || ((DIV) == EN_CPTO_CLK_DIV_8))

//=============================================================================
// CRG_CLK_DIV_CFG0[24:22] CRG_GTIM_SYS_CLK_DIV Define
#define CRG_GTIM_SYS_CLK_DIV_SHIFT         (22)
#define CRG_GTIM_SYS_CLK_DIV_MSK           ((0x01 << 2) - 1)

typedef enum
{
    EN_GTIM_SYS_CLK_DIV_1    = 0,
    EN_GTIM_SYS_CLK_DIV_2    = 1,
    EN_GTIM_SYS_CLK_DIV_4    = 2,
    EN_GTIM_SYS_CLK_DIV_8    = 3,

} EN_GTIM_SYS_CLK_DIV_T;

#define IS_GTIM_SYS_CLK_DIV_VALID(DIV)   (((DIV) == EN_GTIM_SYS_CLK_DIV_1) \
                                       || ((DIV) == EN_GTIM_SYS_CLK_DIV_2) \
                                       || ((DIV) == EN_GTIM_SYS_CLK_DIV_4) \
                                       || ((DIV) == EN_GTIM_SYS_CLK_DIV_8))

//=============================================================================
// CRG_CLK_DIV_CFG0[21:19] CRG_PMU_HCLK_DIV Define
#define CRG_PMU_HCLK_DIV_SHIFT             (19)
#define CRG_PMU_HCLK_DIV_MSK               ((0x01 << 3) - 1)

typedef enum
{
    EN_PMU_HCLK_DIV_16    = 4,
    EN_PMU_HCLK_DIV_32    = 5,
    EN_PMU_HCLK_DIV_64    = 6,
    EN_PMU_HCLK_DIV_128   = 7,

} EN_PMU_HCLK_DIV_T;

#define IS_VALID_PMU_CLK_DIV(DIV)   (((DIV) == EN_PMU_HCLK_DIV_16) \
                                  || ((DIV) == EN_PMU_HCLK_DIV_32) \
                                  || ((DIV) == EN_PMU_HCLK_DIV_64) \
                                  || ((DIV) == EN_PMU_HCLK_DIV_128))

//=============================================================================
// CRG_CLK_DIV_CFG0[13:11] CRG_CPTO1_CLK_DIV Define
#define CRG_CPTO0_CLK_DIV_SHIFT            (11)

typedef enum
{
    CRG_CPTO0    = 0,
    CRG_CPTO1    = 1,

} EN_CRG_CPTO_T;

//=============================================================================
// CRG_CLK_DIV_CFG0[10:8] CRG_LLC_CLK_DIV Define
#define CRG_LLC_CLK_DIV_SHIFT              (8)
#define CRG_LLC_CLK_DIV_MSK                ((0x01 << 3) - 1)

typedef enum
{
    EN_LLC_CLK_DIV_1    = 0,
    EN_LLC_CLK_DIV_2    = 1,
    EN_LLC_CLK_DIV_4    = 2,
    EN_LLC_CLK_DIV_8    = 3,

} EN_LLC_CLK_DIV_T;

#define IS_VALID_LLC_CLK_DIV(DIV)   (EN_LLC_CLK_DIV_8 >= (DIV))

//=============================================================================
// CRG_CLK_DIV_CFG0[7:5] CRG_CP_AHB_CLK_DIV Define
#define CRG_CP_AHB_CLK_DIV_SHIFT           (5)
#define CRG_CP_AHB_CLK_DIV_MSK             ((0x01 << 3) - 1)

//=============================================================================
// CRG_CLK_DIV_CFG0[4:2] CRG_MP_APB_CLK_DIV Define
#define CRG_MP_APB_CLK_DIV_SHIFT           (2)
#define CRG_MP_APB_CLK_DIV_MSK             ((0x01 << 3) - 1)

typedef enum
{
    EN_APB_CLK_DIV_1    = 0,
    EN_APB_CLK_DIV_2    = 1,
    EN_APB_CLK_DIV_4    = 2,
    EN_APB_CLK_DIV_8    = 3,
    EN_APB_CLK_DIV_16   = 4,
    EN_APB_CLK_DIV_32   = 5,
    EN_APB_CLK_DIV_64   = 6,
    EN_APB_CLK_DIV_128  = 7,

} EN_APB_CLK_DIV_T;

#define IS_VALID_APB_CLK_DIV(DIV)   (EN_APB_CLK_DIV_128 >= (DIV))

//=============================================================================
// CRG_CLK_DIV_CFG0[1:0] CRG_MP_AHB_CLK_DIV Define
#define CRG_MP_AHB_CLK_DIV_SHIFT           (0)
#define CRG_MP_AHB_CLK_DIV_MSK             ((0x01 << 2) - 1)

typedef enum
{
    EN_AHB_CLK_DIV_1    = 0,
    EN_AHB_CLK_DIV_2    = 1,
    EN_AHB_CLK_DIV_4    = 2,
    EN_AHB_CLK_DIV_8    = 3,

} EN_AHB_CLK_DIV_T;

#define IS_VALID_AHB_CLK_DIV(DIV)   (EN_AHB_CLK_DIV_8 >= (DIV))


//=====================================================================================================================
// [0x14](RW) CRG_CLK_DIV_CFG1
//=====================================================================================================================
//=============================================================================
// CRG_CLK_DIV_CFG1[29:25] CRG_I2S_BCLK_DIV Define
#define CRG_I2S_BCLK_DIV_SHIFT             (25)
#define CRG_I2S_BCLK_DIV_MSK               ((0x01 << 5) - 1)

typedef enum
{
    EN_CRG_I2S_BCLK_DIV_1   = 0,
    EN_CRG_I2S_BCLK_DIV_2   = 1,
    EN_CRG_I2S_BCLK_DIV_4   = 2,
    EN_CRG_I2S_BCLK_DIV_6   = 3,
    EN_CRG_I2S_BCLK_DIV_8   = 4,
    EN_CRG_I2S_BCLK_DIV_10  = 5,
    EN_CRG_I2S_BCLK_DIV_12  = 6,
    EN_CRG_I2S_BCLK_DIV_14  = 7,
    EN_CRG_I2S_BCLK_DIV_16  = 8,
    EN_CRG_I2S_BCLK_DIV_18  = 9,
    EN_CRG_I2S_BCLK_DIV_20  = 10,
    EN_CRG_I2S_BCLK_DIV_22  = 11,
    EN_CRG_I2S_BCLK_DIV_24  = 12,
    EN_CRG_I2S_BCLK_DIV_26  = 13,
    EN_CRG_I2S_BCLK_DIV_28  = 14,
    EN_CRG_I2S_BCLK_DIV_30  = 15,
    EN_CRG_I2S_BCLK_DIV_32  = 16,
    EN_CRG_I2S_BCLK_DIV_34  = 17,
    EN_CRG_I2S_BCLK_DIV_36  = 18,
    EN_CRG_I2S_BCLK_DIV_38  = 19,
    EN_CRG_I2S_BCLK_DIV_40  = 20,
    EN_CRG_I2S_BCLK_DIV_42  = 21,
    EN_CRG_I2S_BCLK_DIV_44  = 22,
    EN_CRG_I2S_BCLK_DIV_46  = 23,
    EN_CRG_I2S_BCLK_DIV_48  = 24,
    EN_CRG_I2S_BCLK_DIV_50  = 25,
    EN_CRG_I2S_BCLK_DIV_52  = 26,
    EN_CRG_I2S_BCLK_DIV_54  = 27,
    EN_CRG_I2S_BCLK_DIV_56  = 28,
    EN_CRG_I2S_BCLK_DIV_58  = 29,
    EN_CRG_I2S_BCLK_DIV_60  = 30,
    EN_CRG_I2S_BCLK_DIV_62  = 31

} EN_I2S_BCLK_DIV_T;


//=============================================================================
// CRG_CLK_DIV_CFG1[24:21] CRG_ANA_OUT_CLK_SRC_SEL Define
#define CRG_ANA_OUT_CLK_SRC_SEL_SHIFT      (21)
#define CRG_ANA_OUT_CLK_SRC_SEL_MSK        ((0x01 << 4) - 1)

typedef enum
{
    ANA_OUT_CLK_RC_HCLK           = 0,
    ANA_OUT_CLK_RC_LCLK           = 1,
    ANA_OUT_CLK_DCXO_LCLK         = 2,
    ANA_OUT_CLK_DCXO_HCLK         = 3,
    ANA_OUT_CLK_PLL96M_CLK        = 4,
    ANA_OUT_CLK_PLL128M_CLK       = 5,
    ANA_OUT_CLK_PERI_LCLK         = 6,
    ANA_OUT_CLK_LPWR_CLK          = 7,
    ANA_OUT_CLK_SYN_CLK_LO16      = 8,
    ANA_OUT_CLK_SYN_CLK_SDM       = 9,
    ANA_OUT_CLK_USB_48M           = 10,
    ANA_OUT_CLK_SYS_CLK           = 11,
    ANA_OUT_CLK_DCXO_FIX_16M_CLK  = 12,

} EN_ANA_OUT_CLK_SRC_T;

#define IS_VALID_ANA_OUT_CLK_SRC(CLK)   (ANA_OUT_CLK_DCXO_FIX_16M_CLK >= (CLK))

//=============================================================================
// CRG_CLK_DIV_CFG1[20:17] CRG_SYS_OUT_CLK_DIV Define
#define CRG_SYS_OUT_CLK_DIV_SHIFT          (17)
#define CRG_SYS_OUT_CLK_DIV_MSK            ((0x01 << 4) - 1)

typedef enum
{
    EN_CRG_SYS_OUT_CLK_DIV_1   = 0,
    EN_CRG_SYS_OUT_CLK_DIV_2   = 1,
    EN_CRG_SYS_OUT_CLK_DIV_4   = 2,
    EN_CRG_SYS_OUT_CLK_DIV_6   = 3,
    EN_CRG_SYS_OUT_CLK_DIV_8   = 4,
    EN_CRG_SYS_OUT_CLK_DIV_10  = 5,
    EN_CRG_SYS_OUT_CLK_DIV_12  = 6,
    EN_CRG_SYS_OUT_CLK_DIV_14  = 7,
    EN_CRG_SYS_OUT_CLK_DIV_16  = 8,
    EN_CRG_SYS_OUT_CLK_DIV_18  = 9,
    EN_CRG_SYS_OUT_CLK_DIV_20  = 10,
    EN_CRG_SYS_OUT_CLK_DIV_22  = 11,
    EN_CRG_SYS_OUT_CLK_DIV_24  = 12,
    EN_CRG_SYS_OUT_CLK_DIV_26  = 13,
    EN_CRG_SYS_OUT_CLK_DIV_28  = 14,
    EN_CRG_SYS_OUT_CLK_DIV_30  = 15

} EN_SYS_OUT_CLK_DIV_T;

//=============================================================================
// CRG_CLK_DIV_CFG1[16:15/14:13/12:11/10:9] CRG_GTIM_CLK_SRC Define
#define CRG_GTIM0_CLK_SRC_SHIFT            (9)
#define CRG_GTIM1_CLK_SRC_SHIFT            (11)
#define CRG_GTIM2_CLK_SRC_SHIFT            (13)
#define CRG_GTIM3_CLK_SRC_SHIFT            (15)
#define CRG_GTIM_CLK_SRC_MSK               ((0x01 << 2) - 1)

typedef enum
{
    GTIM_CLK_SRC_SYS_CLK     = 0,
    GTIM_CLK_SRC_LPWR_CLK    = 1,
    GTIM_CLK_SRC_GPIO_INPUT  = 2

} EN_GTIM_CLK_SRC_T;

#define IS_VALID_GTIM_CLK_SRC(SRC)   (GTIM_CLK_SRC_GPIO_INPUT >= (SRC))

typedef enum
{
    CRG_GTIM0    = 0,
    CRG_GTIM1    = 1,
    CRG_GTIM2    = 2,
    CRG_GTIM3    = 3,

} EN_CRG_GTIM_T;

//=============================================================================
// CRG_CLK_DIV_CFG1[8] CRG_ADC0_CLK_SRC_SEL Define
#define CRG_ADC0_CLK_SRC_SEL_SHIFT         (8)
#define CRG_ADC_CLK_SRC_SEL_MSK            ((0x01 << 1) - 1)

typedef enum
{
    ADC_CLK_PERI_LCLK    = 0,
    ADC_CLK_SYS_CLK      = 1,

} EN_ADC_CLK_SRC_T;

#define IS_VALID_ADC_CLK_SRC(SRC)   (((SRC) == ADC_CLK_PERI_LCLK) \
                                  || ((SRC) == ADC_CLK_SYS_CLK))

//=============================================================================
// CRG_CLK_DIV_CFG1[7:0] CRG_ADC0_CLK_DIV Define
#define CRG_ADC0_CLK_DIV_SHIFT             (0)
#define CRG_ADC_CLK_DIV_MSK                ((0x01 << 8) - 1)

typedef enum
{
    CRG_ADC0  = 0,
    CRG_ADC1  = 1,

} EN_CRG_ADC_T;


//=====================================================================================================================
// [0x18](RW) CRG_CLK_DIV_CFG2
//=====================================================================================================================
//=============================================================================
// CRG_CLK_DIV_CFG2[29] CRG_RC_HCLK_DIV_EN Define
#define CRG_RC_HCLK_DIV_EN_SHIFT           (29)
#define CRG_RC_HCLK_DIV_EN_MSK             ((0x01 << 1) - 1)

typedef enum
{
    EN_RC_HCLK_FREQ_48M = 0,
    EN_RC_HCLK_FREQ_16M = 1,

} EN_RC_HCLK_FREQ_T;

#define IS_VALID_RC_HCLK_FREQ(FREQ)   ((EN_RC_HCLK_FREQ_16M == (FREQ)) \
                                    || (EN_RC_HCLK_FREQ_48M == (FREQ)))

//=============================================================================
// CRG_CLK_DIV_CFG2[28] CRG_ADC1_CLK_SRC_SEL Define
#define CRG_ADC1_CLK_SRC_SEL_SHIFT         (28)

//=============================================================================
// CRG_CLK_DIV_CFG2[27:20] CRG_ADC1_CLK_DIV Define
#define CRG_ADC1_CLK_DIV_SHIFT             (20)

//=============================================================================
// CRG_CLK_DIV_CFG2[19:18/14:13/9:8/4:3] CRG_QSPI0_CLK_SRC Define
#define CRG_QSPI0_CLK_SRC_SHIFT            (3)
#define CRG_QSPI1_CLK_SRC_SHIFT            (8)
#define CRG_QSPI2_CLK_SRC_SHIFT            (13)
#define CRG_QSPI3_CLK_SRC_SHIFT            (18)
#define CRG_QSPI_CLK_SRC_MSK               ((0x01 << 2) - 1)

typedef enum
{
    QSPI_CLK_SYS_CLK       = 0,
    QSPI_CLK_PLL96M_CLK    = 1,
    QSPI_CLK_PLL128M_CLK   = 2,

} EN_QSPI_CLK_SRC_T;

#define IS_VALID_QSPI_CLK_SRC(SRC)   (QSPI_CLK_PLL128M_CLK >= (SRC))

//=============================================================================
// CRG_CLK_DIV_CFG2[17:15/12:10/7:5/2:0] CRG_QSPI0_CLK_DIV Define
#define CRG_QSPI0_CLK_DIV_SHIFT            (0)
#define CRG_QSPI1_CLK_DIV_SHIFT            (5)
#define CRG_QSPI2_CLK_DIV_SHIFT            (10)
#define CRG_QSPI3_CLK_DIV_SHIFT            (15)
#define CRG_QSPI_CLK_DIV_MSK               ((0x01 << 3) - 1)

typedef enum
{
    EN_QSPI_CLK_DIV_1    = 0,
    EN_QSPI_CLK_DIV_2    = 1,
    EN_QSPI_CLK_DIV_4    = 2,
    EN_QSPI_CLK_DIV_8    = 3,
    EN_QSPI_CLK_DIV_16   = 4,

} EN_QSPI_CLK_DIV_T;

#define IS_VALID_QSPI_CLK_DIV(DIV)   (EN_QSPI_CLK_DIV_16 >= (DIV))

typedef enum
{
    CRG_QSPI0    = 0,
    CRG_QSPI1    = 1,
    CRG_QSPI2    = 2,
    CRG_QSPI3    = 3,

} EN_CRG_QSPI_T;


//=====================================================================================================================
// [0x24~0x28](RW) CRG_CLK_EN0 / CRG_CLK_EN1
//=====================================================================================================================
#define CRG_CLK_EN0_SHIFT                  (0)
#define CRG_CLK_EN0_MSK                    (WORD_MSK)

#define CRG_CLK_EN1_SHIFT                  (0)
#define CRG_CLK_EN1_MSK                    ((0x01 << 22) - 1)

typedef enum
{
    CRG_GTIM0_CLK_GATE           = 0x00, /* 0 */
    CRG_GTIM1_CLK_GATE           = 0x01, /* 1 */
    CRG_GTIM2_CLK_GATE           = 0x02, /* 2 */
    CRG_GTIM3_CLK_GATE           = 0x03, /* 3 */
    CRG_STIM0_CLK_GATE           = 0x04, /* 4 */
    CRG_STIM1_CLK_GATE           = 0x05, /* 5 */
    CRG_RTC_APB_CLK_GATE         = 0x06, /* 6 */
    CRG_RTC_RC_LCLK_GATE         = 0x07, /* 7 */
    CRG_WDT0_LCLK_GATE           = 0x08, /* 8 */
    CRG_WDT1_LCLK_GATE           = 0x09, /* 9 */
    CRG_FD_CLK_GATE              = 0x0A, /* 10 */
    CRG_LO_CLK_GATE              = 0x0B, /* 11 */
    CRG_SDM_CLK_GATE             = 0x0C, /* 12 */
    CRG_MDM_CLK_GATE             = 0x0D, /* 13 */
    CRG_LLC_HCLK_GATE            = 0x0E, /* 14 */
    CRG_LLC_LCLK_GATE            = 0x0F, /* 15 */
    CRG_CPTO0_CLK_GATE           = 0x10, /* 16 */
    CRG_CALI_CLK_GATE            = 0x11, /* 17 */
    CRG_TRNG_CLK_GATE            = 0x12, /* 18 */
    CRG_AUDIO_CLK_GATE           = 0x13, /* 19 */
    CRG_ADC0_CLK_GATE            = 0x14, /* 20 */
    CRG_ADC1_CLK_GATE            = 0x15, /* 21 */
    CRG_I2S_CLK_GATE             = 0x16, /* 22 */
    CRG_DMA_CLK_GATE             = 0x17, /* 23 */
    CRG_QSPI1_CLK_GATE           = 0x18, /* 24 */
    CRG_QSPI2_CLK_GATE           = 0x19, /* 25 */
    CRG_QSPI3_CLK_GATE           = 0x1A, /* 26 */
    CRG_USB_CLK_GATE             = 0x1B, /* 27 */
    CRG_I2C0_CLK_GATE            = 0x1C, /* 28 */
    CRG_I2C1_CLK_GATE            = 0x1D, /* 29 */
    CRG_I2C2_CLK_GATE            = 0x1E, /* 30 */
    CRG_I2C3_CLK_GATE            = 0x1F, /* 31 */
    CRG_MP_CLK_GATE              = 0x20, /* 32 */
    CRG_AHB5_CLK_GATE            = 0x21, /* 33 */
    CRG_H2P1_AHB_CLK_GATE        = 0x22, /* 34 */
    CRG_SYS_CTRL_CLK_GATE        = 0x23, /* 35 */
    CRG_EFUSE_CLK_GATE           = 0x24, /* 36 */
    CRG_GPIO_CLK_GATE            = 0x25, /* 37 */
    CRG_PWT_LCLK_GATE            = 0x26, /* 38 */
    CRG_QSPI0_CLK_GATE           = 0x27, /* 39 */
    CRG_AHB4_CLK_GATE            = 0x28, /* 40 */
    CRG_CP_CLK_GATE              = 0x29, /* 41 */
    CRG_CP_DAP_CLK_GATE          = 0x2A, /* 42 */
    CRG_UART0_CLK_GATE           = 0x2B, /* 43 */
    CRG_UART1_CLK_GATE           = 0x2C, /* 44 */
    CRG_UART2_CLK_GATE           = 0x2D, /* 45 */
    CRG_SPI0_CLK_GATE            = 0x2E, /* 46 */
    CRG_SPI1_CLK_GATE            = 0x2F, /* 47 */
    CRG_QDEC_CLK_GATE            = 0x30, /* 48 */
    CRG_SYS_DIV_OUT_CLK_GATE     = 0x31, /* 49 */
    CRG_ANA_OUT_CLK_GATE         = 0x32, /* 50 */
    CRG_DCXO_LCLK_OUT0_CLK_GATE  = 0x33, /* 51 */
    CRG_DCXO_LCLK_OUT1_CLK_GATE  = 0x34, /* 52 */
    CRG_CPTO1_CLK_GATE           = 0x35, /* 53 */

} EN_CRG_CLK_GATE_T;

#define CRG_CLK_GATE_MAX                   (54)


//=====================================================================================================================
// [0x80~0x84](RW) CRG_PERI_SW_RST_EN0 / CRG_PERI_SW_RST_EN1
//=====================================================================================================================
#define CRG_PERI_SW_RST_EN0_SHIFT          (0)
#define CRG_PERI_SW_RST_EN0_MSK            (WORD_MSK)

#define CRG_PERI_SW_RST_EN1_SHIFT          (0)
#define CRG_PERI_SW_RST_EN1_MSK            ((0x01 << 10) - 1)

typedef enum
{
    CRG_UART0_SW_RST     = 0x00, /* 0 */
    CRG_UART1_SW_RST     = 0x01, /* 1 */
    CRG_UART2_SW_RST     = 0x02, /* 2 */
    CRG_I2C0_SW_RST      = 0x03, /* 3 */
    CRG_I2C1_SW_RST      = 0x04, /* 4 */
    CRG_I2C2_SW_RST      = 0x05, /* 5 */
    CRG_SPI1_SW_RST      = 0x06, /* 6 */
    CRG_SPI0_SW_RST      = 0x07, /* 7 */
    CRG_QDEC_SW_RST      = 0x08, /* 8 */
    CRG_USB_SW_RST       = 0x09, /* 9 */
    CRG_GTIM0_SW_RST     = 0x0A, /* 10 */
    CRG_GTIM1_SW_RST     = 0x0B, /* 11 */
    CRG_GTIM2_SW_RST     = 0x0C, /* 12 */
    CRG_GTIM3_SW_RST     = 0x0D, /* 13 */
    CRG_GPIO_SW_RST      = 0x0E, /* 14 */
    CRG_I2S_SW_RST       = 0x0F, /* 15 */
    CRG_EFUSE_SW_RST     = 0x10, /* 16 */
    CRG_AUDIO_SW_RST     = 0x11, /* 17 */
    CRG_ADC0_SW_RST      = 0x12, /* 18 */
    CRG_QSPI0_SW_RST     = 0x13, /* 19 */
    CRG_QSPI1_SW_RST     = 0x14, /* 20 */
    CRG_QSPI2_SW_RST     = 0x15, /* 21 */
    CRG_QSPI3_SW_RST     = 0x16, /* 22 */
    CRG_DMA_SW_RST       = 0x17, /* 23 */
    CRG_AHB4_SW_RST      = 0x18, /* 24 */
    CRG_WDT0_SW_RST      = 0x19, /* 25 */
    CRG_PWT_SW_RST       = 0x1A, /* 26 */
    CRG_RTC_SW_RST       = 0x1B, /* 27 */
    CRG_SYS_CTRL_SW_RST  = 0x1C, /* 28 */
    CRG_CALI_SW_RST      = 0x1D, /* 29 */
    CRG_AHB5_SW_RST      = 0x1E, /* 30 */
    CRG_I2C3_SW_RST      = 0x1F, /* 31 */
    CRG_CP_SW_RST        = 0x20, /* 32 */
    CRG_LLC_SW_RST       = 0x21, /* 33 */
    CRG_MDM_SW_RST       = 0x22, /* 34 */
    CRG_CPTO0_SW_RST     = 0x23, /* 35 */
    CRG_TRNG_SW_RST      = 0x24, /* 36 */
    CRG_ADC1_SW_RST      = 0x25, /* 37 */
    CRG_WDT1_SW_RST      = 0x26, /* 38 */
    CRG_STIM0_SW_RST     = 0x27, /* 39 */
    CRG_STIM1_SW_RST     = 0x28, /* 40 */
    CRG_CPTO1_SW_RST     = 0x29, /* 41 */

} EN_CRG_SW_RST_T;

#define CRG_SW_RST0_IDX_MAX                (31)
#define CRG_SW_RST_NUM_MAX                 (42)
#define IS_VALID_CRG_SW_RST(NUM)           (CRG_SW_RST_NUM_MAX >= (NUM))


//=====================================================================================================================
// [0x88](WO) CRG_MP_SW_RST_EN
//=============================================================================
// CRG_MP_SW_RST_EN[0] CRG_MP_SW_RST_EN Define
#define CRG_MP_SW_RST_EN_SHIFT             (0)
#define CRG_MP_SW_RST_EN_MSK               ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x8C](WO) CRG_CP_SW_RST_EN
//=============================================================================
// CRG_CP_SW_RST_EN[0] CRG_CP_SW_RST_EN Define
#define CRG_CP_SW_RST_EN_SHIFT             (0)
#define CRG_CP_SW_RST_EN_MSK               ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x90](WO) CRG_SYS_SW_RST_EN
//=============================================================================
// CRG_SYS_SW_RST_EN[7:0] CRG_SYS_SW_RST_EN Define
#define CRG_SYS_SW_RST_EN_SHIFT            (0)
#define CRG_SYS_SW_RST_EN_MSK              ((0x01 << 8) - 1)

#define CRG_SYS_SW_RST                     (0x5A)


//=====================================================================================================================
// [0x94](RO) CRG_RST_FLG / CRG_RST_CLR
//=====================================================================================================================
#define CRG_WDT1_RST_FLAG_SHIFT            (8)
#define CRG_POWER_ON_RST_FLAG_SHIFT        (7)
#define CRG_HW_RST_FLAG_SHIFT              (6)
#define CRG_SW_RST_FLAG_SHIFT              (5)
#define CRG_WDT0_RST_FLAG_SHIFT            (4)
#define CRG_MP_SW_RST_FLAG_SHIFT           (3)
#define CRG_MP_SYS_RST_FLAG_SHIFT          (2)
#define CRG_CP_SW_RST_FLAG_SHIFT           (1)
#define CRG_CP_SYS_RST_FLAG_SHIFT          (0)

typedef enum
{
    CRG_CP_SYS_RST_FLAG      = (0x01 << CRG_CP_SYS_RST_FLAG_SHIFT),
    CRG_CP_SW_RST_FLAG       = (0x01 << CRG_CP_SW_RST_FLAG_SHIFT),
    CRG_MP_SYS_RST_FLAG      = (0x01 << CRG_MP_SYS_RST_FLAG_SHIFT),
    CRG_MP_SW_RST_FLAG       = (0x01 << CRG_MP_SW_RST_FLAG_SHIFT),

    CRG_WDT0_RST_FLAG        = (0x01 << CRG_WDT0_RST_FLAG_SHIFT),
    CRG_SW_RST_FLAG          = (0x01 << CRG_SW_RST_FLAG_SHIFT),
    CRG_HW_RST_FLAG          = (0x01 << CRG_HW_RST_FLAG_SHIFT),
    CRG_POWER_ON_RST_FLAG    = (0x01 << CRG_POWER_ON_RST_FLAG_SHIFT),

    CRG_WDT1_RST_FLAG        = (0x01 << CRG_WDT1_RST_FLAG_SHIFT),

} EN_CRG_RST_FLAG_T;

#define CRG_RESET_MASK                     (0x1FF)


//=====================================================================================================================
// [0x9C](RW) CRG_WDT1_RST_EN
//=====================================================================================================================
#define CRG_WDT1_RST_EN_SHIFT              (0)
#define CRG_WDT1_RST_EN_MSK                ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x100](RW) CRG_CALIB_CLK_CFG
//=====================================================================================================================
//=============================================================================
// CRG_CALIB_CLK_CFG[6:3] CRG_CALIB_CLK_SPEED_CFG Define
#define CRG_CALIB_CLK_SPEED_CFG_SHIFT      (3)
#define CRG_CALIB_CLK_SPEED_CFG_MSK        ((0x01 << 4) - 1)

//=============================================================================
// CRG_CALIB_CLK_CFG[2] CRG_CALIB_CLK_SEL Define
#define CRG_CALIB_CLK_SEL_SHIFT            (2)
#define CRG_CALIB_CLK_SEL_MSK              ((0x01 << 2) - 1)

typedef enum
{
    CRG_RC_LCLK          = 0,
    CRG_RC_HCLK_DIV4096  = 1,

} EN_CRG_CALIB_CLK_SEL_T;

#define IS_VALID_CRG_CALIB_CLK_SEL(SEL)   (((SEL) == CRG_RC_LCLK) \
                                        || ((SEL) == CRG_RC_HCLK_DIV4096))

//=============================================================================
// CRG_CALIB_CLK_CFG[1] CRG_PMU_CALIB_EN Define
#define CRG_PMU_CALIB_EN_SHIFT             (1)
#define CRG_PMU_CALIB_EN_MSK               ((0x01 << 1) - 1)

//=============================================================================
// CRG_CALIB_CLK_CFG[0] CRG_CALIB_EN Define
#define CRG_CALIB_EN_SHIFT                 (0)
#define CRG_CALIB_EN_MSK                   ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x104](RO) CRG_CALIB_32K_PERIOD
//=====================================================================================================================
#define CRG_CALIB_32K_PERIOD_SHIFT         (0)
#define CRG_CALIB_32K_PERIOD_MSK           ((0x01 << 16) - 1)


#ifdef __cplusplus
}
#endif

#endif /* __REG_CRG_H__ */


