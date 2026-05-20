/*************************************************************************************************************
 * @file    reg_pmu.h
 * @version V1.1
 * @date    2022-01-10
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


#ifndef __REG_PMU_H__
#define __REG_PMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PMU_LUT_MAX                        (16)

//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t PMU_LUT_ROW_INT_FLAG;         /* [0x00](RO) */
    __OM  uint32_t PMU_LUT_ROW_INT_CLR;          /* [0x04](WO) */
    __IOM uint32_t PMU_LUT_ROW[PMU_LUT_MAX];     /* [0x08~0x44](RW) */
    __IOM uint32_t PMU_PWR_ON_CFG;               /* [0x48](RW) */
    __IOM uint32_t PMU_CLK_SYNC_OUT;             /* [0x4C](RW) */
    __IOM uint32_t PMU_PWR_OFF_CFG;              /* [0x50](RW) */
    __IOM uint32_t PMU_DCDC_TRIM;                /* [0x54](RW) */
    __IOM uint32_t PMU_PSW_CFG;                  /* [0x58](RW) */
    __IOM uint32_t PMU_DCXO_HCLK_STABLE_TIME;    /* [0x5C](RW) */
    __IOM uint32_t PMU_SRAM_RET_EN;              /* [0x60](RW) */
    __IOM uint32_t PMU_SLEEP_MODE;               /* [0x64](RW) */
    __IOM uint32_t PMU_PD_SYS_RET_CFG;           /* [0x68](RW) */
    __OM  uint32_t PMU_FORCE_SLEEP;              /* [0x6C](WO) */
    __IOM uint32_t PMU_DCDC_ACT_OUT_EN;          /* [0x70](RW) */
    __IOM uint32_t PMU_DCDC_ACT_CFG;             /* [0x74](RW) */
    __IOM uint32_t PMU_DCDC_FB_CFG;              /* [0x78](RW) */
    __IOM uint32_t PMU_DCDC_LPWR_OUT_EN;         /* [0x7C](RW) */
    __IOM uint32_t PMU_DCDC_LPWR_ZCD_CFG;        /* [0x80](RW) */
    __IOM uint32_t PMU_DCDC_LPWR_N_CFG;          /* [0x84](RW) */
    __IOM uint32_t PMU_DCDC_LPWR_CFG;            /* [0x88](RW) */
    __IOM uint32_t PMU_DCDC_LPWR_CLK;            /* [0x8C](RW) */
    __IOM uint32_t PMU_LDO_ACT_OUT_EN;           /* [0x90](RW) */
    __IOM uint32_t PMU_LDO_ACT_CFG;              /* [0x94](RW) */
    __IOM uint32_t PMU_LDO_1V8_OUT_EN;           /* [0x98](RW) */
    __IOM uint32_t PMU_LDO_DIG_OUT_EN;           /* [0x9C](RW) */
    __IOM uint32_t PMU_LDO_DIG_CFG;              /* [0xA0](RW) */
    __IOM uint32_t PMU_LDO_RET_CTRL;             /* [0xA4](RW) */
    __IOM uint32_t PMU_LDO_RET_CFG;              /* [0xA8](RW) */
    __OM  uint32_t PMU_CLK_CTRL;                 /* [0xAC](WO) */
    __IM  uint32_t PMU_CLK_STATUS;               /* [0xB0](RO) */
    __IOM uint32_t PMU_DCXO_HCLK_PWR_SEL;        /* [0xB4](RW) */
    __IOM uint32_t PMU_DCXO_HCLK_CFG;            /* [0xB8](RW) */
    __IOM uint32_t PMU_RC_HCLK_TUNE;             /* [0xBC](RW) */
    __IOM uint32_t PMU_RC_LCLK_TUNE;             /* [0xC0](RW) */
    __IOM uint32_t PMU_PLL_CFG;                  /* [0xC4](RW) */
    __OM  uint32_t PMU_PD_ON;                    /* [0xC8](WO) */
    __OM  uint32_t PMU_PD_OFF;                   /* [0xCC](WO) */
    __IM  uint32_t PMU_DPSW_STATUS;              /* [0xD0](RO) */
    __IOM uint32_t PMU_CODE;                     /* [0xD4](RW) */
    __IOM uint32_t PMU_RET_RESET_SEL;            /* [0xD8](RW) */
    __IOM uint32_t PMU_USB_PHY_SEL;              /* [0xDC](RW) */
    __IOM uint32_t PMU_BAND_GAP_CFG;             /* [0xE0](RW) */
    __IOM uint32_t PMU_ANA_BKUP;                 /* [0xE4](RW) */
    __IOM uint32_t PMU_TEST_CTRL;                /* [0xE8](RW) */
    __IOM uint32_t PMU_FORCE_CTRL;               /* [0xEC](RW) */
    __IOM uint32_t PMU_ANA_BKUP2;                /* [0xF0](RW) */
    __IM  uint32_t PMU_ANA_BKUP_STA;             /* [0xF4](RO) */
    __IM  uint32_t PMU_CDC_CNT;                  /* [0xF8](RO) */

} stPMU_Handle_t, *pstPMU_Handle_t;


//=====================================================================================================================
// [0x00~0x04] PMU_LUT_ROW_INT_FLAG / PMU_LUT_ROW_INT_CLR
//=====================================================================================================================
#define PMU_INT_MSK                        (0x1FFFF)


//=====================================================================================================================
// [0x08~0x44] PMU_LUT_ROW
//=====================================================================================================================
//=============================================================================
// PMU_LUT_ROW[1:0] LUT_TRIG_SEL Define
#define LUT_TRIG_SEL_SHIFT                 (0)
#define LUT_TRIG_SEL_MSK                   ((0x01 << 2) - 1)

//=============================================================================
// PMU_LUT_ROW[6:2] LUT_TRIG_ID Define
#define LUT_TRIG_ID_SHIFT                  (2)
#define LUT_TRIG_ID_MSK                    ((0x01 << 5) - 1)

//=============================================================================
// PMU_LUT_ROW[10:7] LUT_ACTION Define
#define LUT_ACTION_SHIFT                   (7)
#define LUT_ACTION_MSK                     ((0x01 << 4) - 1)

typedef enum
{
    LUT_TRIG_ID_GPIOA       = (0x00), // GPIO Wakeup without debounce
    LUT_TRIG_ID_GPIOB       = (0x01), // GPIO Wakeup without debounce
    LUT_TRIG_ID_GPIOC       = (0x02), // GPIO Wakeup without debounce
    LUT_TRIG_ID_OTHER       = (0x03)

} PUM_LUT_TRIG_SEL_T;

typedef enum
{
    LUT_TRIG_ID_RTC_CH0      = (0),
    LUT_TRIG_ID_RTC_CH1      = (1),
    LUT_TRIG_ID_RTC_CH2      = (2),
    LUT_TRIG_ID_RTC_CH3      = (3),
    LUT_TRIG_ID_LLC          = (4),
    LUT_TRIG_ID_GTIM0        = (5),
    LUT_TRIG_ID_GTIM1        = (6),
    LUT_TRIG_ID_GTIM2        = (7),
    LUT_TRIG_ID_GTIM3        = (8),
    LUT_TRIG_ID_GPIO         = (9), // GPIO Wakeup with debounce
    LUT_TRIG_ID_CP_SWD       = (10),
    LUT_TRIG_ID_MP_SWD       = (11),
    LUT_TRIG_ID_USB          = (12),
    LUT_TRIG_ID_STIM0_CH0    = (13),
    LUT_TRIG_ID_STIM0_CH1    = (14),
    LUT_TRIG_ID_STIM0_CH2    = (15),
    LUT_TRIG_ID_STIM0_CH3    = (16),
    LUT_TRIG_ID_STIM1_CH0    = (17),
    LUT_TRIG_ID_STIM1_CH1    = (18),
    LUT_TRIG_ID_STIM1_CH2    = (19),
    LUT_TRIG_ID_STIM1_CH3    = (20),
    LUT_TRIG_ID_WDT1         = (21),

} EN_LUT_TRIG_ID_T;

typedef enum
{
    LUT_ACT_PD_SYS_ON       = (0x01 << 0), /* bit[7] */
    LUT_ACT_DCXO_HCLK_ON    = (0x01 << 1), /* bit[8] */
    LUT_ACT_CP_IRQ_EN       = (0x01 << 2), /* bit[9] */
    LUT_ACT_MP_IRQ_EN       = (0x01 << 3), /* bit[10] */

} EN_LUT_ACT_T;

//=====================================================================================================================
// [0x4C](RW) PMU_CLK_SYNC_OUT
//=====================================================================================================================
//=============================================================================
// PMU_CLK_SYNC_OUT[0] RC_HCLK_SYNC_OUT
#define RC_HCLK_SYNC_OUT_SHIFT             (0)
#define RC_HCLK_SYNC_OUT_MSK               ((0x01 << 1) - 1)

typedef enum
{
    RC_HCLK_OUT_STABLE   = 0, // Delay 0.5 to 1.5 32K clock cycles to output RC_HCLK after turn on RC_HCLK.
    RC_HCLK_OUT_QUICKLY  = 1, // Output RC_HCLK while turning on RC_HCLK immediately.

} EN_RC_HCLK_SYNC_OUT_MODE_T;


//=====================================================================================================================
// [0x54](RW) PMU_DCDC_TRIM
//=====================================================================================================================
//=============================================================================
// PMU_DCDC_TRIM[0] DCDC_SLEEP_2_ACT_TIME, From sleep to active
#define DCDC_SLEEP_2_ACT_TIME_SHIFT        (0)
#define DCDC_SLEEP_2_ACT_TIME_MSK          ((0x01 << 1) - 1)

//=============================================================================
// PMU_DCDC_TRIM[1] DCDC_ACT_2_SLEEP_TIME Define, From active to sleep
#define DCDC_ACT_2_SLEEP_TIME_SHIFT        (1)
#define DCDC_ACT_2_SLEEP_TIME_MSK          ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x58](RW) PMU_PSW_CFG
//=====================================================================================================================
//=============================================================================
// PMU_PSW_CFG[3:0] LDO_DIG_PSW_CFG, From ALL digital on to Retention time.
#define LDO_DIG_PSW_CFG_SHIFT              (0)
#define LDO_DIG_PSW_CFG_MSK                ((0x01 << 4) - 1)

//=============================================================================
// PMU_PSW_CFG[7:4] LDO_RET_PSW_CFG, From Retention to ALL digital on time.
#define LDO_RET_PSW_CFG_SHIFT              (4)
#define LDO_RET_PSW_CFG_MSK                ((0x01 << 4) - 1)


//=====================================================================================================================
// [0x5C](RW) PMU_DCXO_HCLK_STABLE_TIME
//=====================================================================================================================
//=============================================================================
// PMU_DCXO_HCLK_STABLE_TIME[7:0] DCXO_HCLK_STABLE_TIME Define (UNIT: 31.25us)
#define DCXO_HCLK_STABLE_TIME_SHIFT        (0)
#define DCXO_HCLK_STABLE_TIME_MSK          ((0x01 << 8) - 1)

#define DCXO_HCLK_STABLE_TIME_MAX_US       (7968) /* 255 * 31.25 = 7,968.75 */


//=====================================================================================================================
// [0x60](WR) PMU_SRAM_RET_EN
//=====================================================================================================================
//=============================================================================
// PMU_SRAM_RET_EN[19:0] SRAM_BLOCK_EN
#define SRAM_BLOCK_EN_SHIT                 (0)
#define SRAM_BLOCK_EN_MSK                  ((0x01 << 20) - 1)

typedef enum
{
    EN_SRAM_BLOCK0   =  0,
    EN_SRAM_BLOCK1   =  1,
    EN_SRAM_BLOCK2   =  2,
    EN_SRAM_BLOCK3   =  3,
    EN_SRAM_BLOCK4   =  4,
    EN_SRAM_BLOCK5   =  5,
    EN_SRAM_BLOCK6   =  6,
    EN_SRAM_BLOCK7   =  7,
    EN_SRAM_BLOCK8   =  8,
    EN_SRAM_BLOCK9   =  9,
    EN_SRAM_BLOCK10  =  10,
    EN_SRAM_BLOCK11  =  11,
    EN_SRAM_BLOCK12  =  12,
    EN_SRAM_BLOCK13  =  13,
    EN_SRAM_BLOCK14  =  14,
    EN_SRAM_BLOCK15  =  15,
    EN_SRAM_BLOCK16  =  16,
    EN_SRAM_BLOCK17  =  17,
    EN_SRAM_BLOCK18  =  18,
    EN_SRAM_BLOCK19  =  19

} EN_SRAM_BLOCK_EN_T;


//=====================================================================================================================
// [0x64](RW) PMU_SLEEP_MODE
//=====================================================================================================================
//=============================================================================
// PMU_SLEEP_MODE[1:0] PWR_MODE_SEL Define
#define PWR_MODE_SEL_SHIFT                 (0)
#define PWR_MODE_SEL_MSK                   ((0x01 << 2) - 1)

typedef enum
{
    PWR_MODE_SLEEP        = 0, /* SRAM keep retention. */
    PWR_MODE_DEEPSLEEP    = 1, /* SRAM will power down, LCLK clock will keep working(shutdown with 32K). */
    PWR_MODE_HIBERNATION  = 2, /* SRAM will power down, LCLK clock will turn off(shutdown without 32K). */

} EN_PWR_MODE_T;

#define IS_VALID_PWR_MODE(MODE) (((MODE) == PWR_MODE_SLEEP)     \
                              || ((MODE) == PWR_MODE_DEEPSLEEP) \
                              || ((MODE) == PWR_MODE_HIBERNATION))


//=====================================================================================================================
// [0x70](RW) PMU_DCDC_ACT_OUT_EN
//=====================================================================================================================
//=============================================================================
// PMU_DCDC_ACT_OUT_EN[0] DCDC_ACT_OUT_EN Define
#define DCDC_ACT_OUT_EN_SHIFT              (0)
#define DCDC_ACT_OUT_EN_MSK                ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x74](RW) PMU_DCDC_ACT_CFG
//=====================================================================================================================
//=============================================================================
// PMU_DCDC_ACT_CFG[2:0] DCDC_DO_BBM
#define DCDC_DO_BBM_SHIFT                  (0)
#define DCDC_DO_BBM_MSK                    ((0x01 << 3) - 1)

//=============================================================================
// PMU_DCDC_ACT_CFG[5:3] DCDC_ZCD_CMP_HYS
#define DCDC_ZCD_CMP_HYS_SHIFT             (3)
#define DCDC_ZCD_CMP_HYS_MSK               ((0x01 << 3) - 1)

//=============================================================================
// PMU_DCDC_ACT_CFG[8:6] DCDC_OCP_CMP_HYS
#define DCDC_OCP_CMP_HYS_SHIFT             (6)
#define DCDC_OCP_CMP_HYS_MSK               ((0x01 << 3) - 1)

//=============================================================================
// PMU_DCDC_ACT_CFG[11:9] DCDC_TOFF
#define DCDC_TOFF_SHIFT                    (9)
#define DCDC_TOFF_MSK                      ((0x01 << 3) - 1)

//=============================================================================
// PMU_DCDC_ACT_CFG[13:12] DCDC_HYSB
#define DCDC_HYSB_SHIFT                    (12)
#define DCDC_HYSB_MSK                      ((0x01 << 2) - 1)

//=============================================================================
// PMU_DCDC_ACT_CFG[16:14] DCDC_BBM
#define DCDC_BBM_SHIFT                     (14)
#define DCDC_BBM_MSK                       ((0x01 << 3) - 1)

//=============================================================================
// PMU_DCDC_ACT_CFG[19:17] DCDC_PLUSE
#define DCDC_PLUSE_SHIFT                   (17)
#define DCDC_PLUSE_MSK                     ((0x01 << 3) - 1)

//=============================================================================
// PMU_DCDC_ACT_CFG[22:20] DCDC_TON
#define DCDC_TON_SHIFT                     (20)
#define DCDC_TON_MSK                       ((0x01 << 3) - 1)

//=============================================================================
// PMU_DCDC_ACT_CFG[26:23] DCDC_ZCD
#define DCDC_ZCD_SHIFT                     (23)
#define DCDC_ZCD_MSK                       ((0x01 << 4) - 1)

//=============================================================================
// PMU_DCDC_ACT_CFG[30:27] DCDC_OCP
#define DCDC_OCP_SHIFT                     (27)
#define DCDC_OCP_MSK                       ((0x01 << 4) - 1)


//=====================================================================================================================
// [0x78](RW) PMU_DCDC_FB_CFG
//=====================================================================================================================
//=============================================================================
// PMU_DCDC_FB_CFG[6:0] DCDC_FB_HI_VOLT
#define DCDC_FB_HI_VOLT_SHIFT              (0)
#define DCDC_FB_HI_VOLT_MSK                ((0x01 << 7) - 1)

//=============================================================================
// PMU_DCDC_FB_CFG[13:7] DCDC_FB_LO_VOLT
#define DCDC_FB_LO_VOLT_SHIFT              (7)
#define DCDC_FB_LO_VOLT_MSK                ((0x01 << 7) - 1)

typedef enum
{
    EN_DCDC_ACT_VOLT_950mV   = 0x7F,
    EN_DCDC_ACT_VOLT_1000mV  = 0x3F,
    EN_DCDC_ACT_VOLT_1050mV  = 0x1F,
    EN_DCDC_ACT_VOLT_1100mV  = 0x0F,
    EN_DCDC_ACT_VOLT_1150mV  = 0x07,
    EN_DCDC_ACT_VOLT_1200mV  = 0x03,
    EN_DCDC_ACT_VOLT_1250mV  = 0x01,
    EN_DCDC_ACT_VOLT_1300mV  = 0x00,

} EN_DCDC_ACT_VOLT_T;


//=====================================================================================================================
// [0x7C](RW) PMU_DCDC_LPWR_OUT_EN
//=====================================================================================================================
//=============================================================================
// PMU_DCDC_LPWR_OUT_EN[0] DCDC_LPWR_OUT_EN Define
#define DCDC_LPWR_OUT_EN_SHIFT             (0)
#define DCDC_LPWR_OUT_EN_MSK               ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x80](RW) PMU_DCDC_LPWR_ZCD_CFG
//=====================================================================================================================
//=============================================================================
// PMU_DCDC_LPWR_ZCD_CFG[0] DCDC_LPWR_ZCD_LO_SEL
#define DCDC_LPWR_ZCD_LO_SEL_SHIFT         (0)
#define DCDC_LPWR_ZCD_LO_SEL_MSK           ((0x01 << 1) - 1)

//=============================================================================
// PMU_DCDC_LPWR_ZCD_CFG[1] DCDC_LPWR_ZCD_HI_SEL
#define DCDC_LPWR_ZCD_HI_SEL_SHIFT         (1)
#define DCDC_LPWR_ZCD_HI_SEL_MSK           ((0x01 << 1) - 1)

//=============================================================================
// PMU_DCDC_LPWR_ZCD_CFG[2] DCDC_LPWR_ZCD_LO_EN
#define DCDC_LPWR_ZCD_LO_EN_SHIFT          (2)
#define DCDC_LPWR_ZCD_LO_EN_MSK            ((0x01 << 1) - 1)

//=============================================================================
// PMU_DCDC_LPWR_ZCD_CFG[3] DCDC_LPWR_ZCD_HI_EN
#define DCDC_LPWR_ZCD_HI_EN_SHIFT          (3)
#define DCDC_LPWR_ZCD_HI_EN_MSK            ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x84](RW) PMU_DCDC_LPWR_N_CFG
//=====================================================================================================================
//=============================================================================
// PMU_DCDC_LPWR_N_CFG[15:0] DCDC_LPWR_N_LO
#define DCDC_LPWR_N_LO_SHIFT               (0)
#define DCDC_LPWR_N_LO_MSK                 ((0x01 << 16) - 1)

//=============================================================================
// PMU_DCDC_LPWR_N_CFG[31:16] DCDC_LPWR_N_HI
#define DCDC_LPWR_N_HI_SHIFT               (16)
#define DCDC_LPWR_N_HI_MSK                 ((0x01 << 16) - 1)


//=====================================================================================================================
// [0x88](RW) PMU_DCDC_LPWR_CFG
//=====================================================================================================================
//=============================================================================
// PMU_DCDC_LPWR_CFG[7:0] DCDC_LPWR_P_LO
#define DCDC_LPWR_P_LO_SHIFT               (0)
#define DCDC_LPWR_P_LO_MSK                 ((0x01 << 8) - 1)

//=============================================================================
// PMU_DCDC_LPWR_CFG[15:8] DCDC_LPWR_P_HI
#define DCDC_LPWR_P_HI_SHIFT               (8)
#define DCDC_LPWR_P_HI_MSK                 ((0x01 << 8) - 1)

//=============================================================================
// PMU_DCDC_LPWR_CFG[19:16] DCDC_LPWR_FB_LO
#define DCDC_LPWR_FB_LO_SHIFT              (16)
#define DCDC_LPWR_FB_LO_MSK                ((0x01 << 4) - 1)

//=============================================================================
// PMU_DCDC_LPWR_CFG[23:20] DCDC_LPWR_FB_LO
#define DCDC_LPWR_FB_HO_SHIFT              (20)
#define DCDC_LPWR_FB_HO_MSK                ((0x01 << 4) - 1)

//=============================================================================
// PMU_DCDC_LPWR_CFG[24:26] DCDC_LPWR_BBM
#define DCDC_LPWR_BBM_SHIFT                (24)
#define DCDC_LPWR_BBM_MSK                  ((0x01 << 3) - 1)

typedef enum
{
    EN_DCDC_LPWR_VOLT_950mV  = 0x01,
    EN_DCDC_LPWR_VOLT_1050mV = 0x00,

} EN_DCDC_LPWR_VOLT_T;

//=============================================================================
// PMU_DCDC_LPWR_CFG[23:20] DCDC_LPWR_FB_HI
#define DCDC_LPWR_FB_HI_SHIFT              (20)
#define DCDC_LPWR_FB_HI_MSK                ((0x01 << 4) - 1)

//=============================================================================
// PMU_DCDC_LPWR_CFG[26:24] DCDC_LPWR_BBM
#define DCDC_LPWR_BBM_SHIFT                (24)
#define DCDC_LPWR_BBM_MSK                  ((0x01 << 3) - 1)


//=====================================================================================================================
// [0x8C](RW) PMU_DCDC_LPWR_CLK
//=====================================================================================================================
//=============================================================================
// PMU_DCDC_LPWR_CLK[2:0] DCDC_LPWR_CLK Define  (Range: 1K ~ 32K)
#define DCDC_LPWR_CLK_SHIFT                (0)
#define DCDC_LPWR_CLK_MSK                  ((0x01 << 3) - 1)

typedef enum
{
    EN_DCDC_LPWR_CLK_32K   = 0,    // 32KHz
    EN_DCDC_LPWR_CLK_16K   = 1,    // 16KHz
    EN_DCDC_LPWR_CLK_8K    = 2,    // 8KHz
    EN_DCDC_LPWR_CLK_4K    = 3,    // 4KHz
    EN_DCDC_LPWR_CLK_2K    = 4,    // 2KHz
    EN_DCDC_LPWR_CLK_1K    = 5,    // 1KHz
    EN_DCDC_LPWR_CLK_512   = 6,    // 512Hz
    EN_DCDC_LPWR_CLK_256   = 7,    // 256Hz

} EN_DCDC_LPWR_CLK_T;

#define IS_VALID_DCDC_LPWR_CLK(CLK)   (EN_DCDC_LPWR_CLK_256 >= (CLK))


//=====================================================================================================================
// [0x90](RW) PMU_LDO_ACT_OUT_EN
//=====================================================================================================================
//=============================================================================
// PMU_LDO_ACT_OUT_EN[0] LDO_ACT_OUT_EN Define
#define LDO_ACT_OUT_EN_SHIFT               (0)
#define LDO_ACT_OUT_EN_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x94](RW) PMU_LDO_ACT_CFG
//=====================================================================================================================
//=============================================================================
// PMU_LDO_ACT_CFG[0] LDO_ACT_BYPASS
#define LDO_ACT_BYPASS_SHIFT               (0)
#define LDO_ACT_BYPASS_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// PMU_LDO_ACT_CFG[4:1] LDO_ACT_VOLT
#define LDO_ACT_VOLT_SHIFT                 (1)
#define LDO_ACT_VOLT_MSK                   ((0x01 << 4) - 1)

typedef enum
{
    EN_LDO_ACT_1300mV = 0,
    EN_LDO_ACT_1250mV = 1,
    EN_LDO_ACT_1200mV = 2,
    EN_LDO_ACT_1150mV = 3,
    EN_LDO_ACT_1100mV = 4,
    EN_LDO_ACT_1050mV = 5,
    EN_LDO_ACT_1000mV = 6,
    EN_LDO_ACT_950mV  = 7,

} EN_LDO_ACT_VOLT_T;


//=====================================================================================================================
// [0x98](RW) PMU_LDO_1V8_OUT_EN
//=============================================================================
// PMU_LDO_1V8_OUT_EN[0] LDO_1V8_OUT_EN Define
#define LDO_1V8_OUT_EN_SHIFT               (0)
#define LDO_1V8_OUT_EN_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x9C](RW) PMU_LDO_DIG_OUT_EN
//=============================================================================
// PMU_LDO_DIG_OUT_EN[0] LDO_DIG_OUT_EN Define (KEEP TO 1 ALWAYS)
#define LDO_DIG_OUT_EN_SHIFT               (0)
#define LDO_DIG_OUT_EN_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0xA0](RW) PMU_LDO_DIG_CFG
//=====================================================================================================================
//=============================================================================
// PMU_LDO_DIG_CFG[0] LDO_DIG_BYPASS
#define LDO_DIG_BYPASS_SHIFT               (0)
#define LDO_DIG_BYPASS_MSK                 ((0x01 << 1) - 1)

//=============================================================================
// PMU_LDO_DIG_CFG[3:1] PMU_LDO_DIG_VOLT
#define LDO_DIG_VOLT_SHIFT                 (1)
#define LDO_DIG_VOLT_MSK                   ((0x01 << 3) - 1)

typedef enum
{
    EN_LDO_DIG_1100mV = 0,
    EN_LDO_DIG_1050mV = 1,
    EN_LDO_DIG_1000mV = 2,
    EN_LDO_DIG_950mV  = 3,
    EN_LDO_DIG_900mV  = 4,

} EN_LDO_DIG_VOLT_T;


//=====================================================================================================================
// [0xA8](RW) PMU_LDO_RET_CFG
//=====================================================================================================================
//=============================================================================
// PMU_LDO_RET_CFG[2:0] LDO_RET_ACT_VOLT LDO_RET Output Voltage When system works in Active Mode.
#define LDO_RET_ACT_VOLT_SHIFT             (0)
#define LDO_RET_ACT_VOLT_MSK               ((0x01 << 3) - 1)

//=============================================================================
// PMU_LDO_RET_CFG[5:3] LDO_RET_SLEEP_VOLT LDO_RET Output Voltage When System Works in Sleep Mode.
#define LDO_RET_SLEEP_VOLT_SHIFT           (3)
#define LDO_RET_SLEEP_VOLT_MSK             ((0x01 << 3) - 1)

typedef enum
{
    EN_LDO_RET_1100mV = 0,
    EN_LDO_RET_1050mV = 1,
    EN_LDO_RET_1000mV = 2,
    EN_LDO_RET_950mV  = 3,

} EN_LDO_RET_VOLT_T;


//=====================================================================================================================
// [0xAC](WO) PMU_CLK_CTRL
//=====================================================================================================================
//=============================================================================
// PMU_CLK_CTRL[17:0] PMU_CLK_CTRL Output and Power Define
#define RC_LCLK_OUT_DIS_SHIFT              (0)
#define RC_LCLK_OUT_EN_SHIFT               (1)
#define RC_HCLK_OUT_DIS_SHIFT              (2)
#define RC_HCLK_OUT_EN_SHIFT               (3)
#define DCXO_HCLK_OUT_DIS_SHIFT            (4)
#define DCXO_HCLK_OUT_EN_SHIFT             (5)
#define DCXO_HCLK_PWR_OFF_SHIFT            (6)
#define DCXO_HCLK_PWR_ON_SHIFT             (7)
#define PLL96M_CLK_OUT_DIS_SHIFT           (8)
#define PLL128M_CLK_OUT_DIS_SHIFT          (9)
#define PLL96M_CLK_OUT_EN_SHIFT            (10)
#define PLL128M_CLK_OUT_EN_SHIFT           (11)
#define PLL_CLK_PWR_OFF_SHIFT              (12)
#define PLL_CLK_PWR_ON_SHIFT               (13)

typedef enum
{
    EN_RC_LCLK_OUT_CTRL     = 0,
    EN_RC_HCLK_OUT_CTRL     = 1,
    EN_DCXO_LCLK_OUT_CTRL   = 2,
    EN_DCXO_HCLK_OUT_CTRL   = 3,
    EN_PLL96M_CLK_OUT_CTRL  = 4,
    EN_PLL128M_CLK_OUT_CTRL = 5,

} EN_CLK_OUT_CTRL_T;

typedef enum
{
    EN_DCXO_LCLK_POWER_CTRL = 0,
    EN_DCXO_HCLK_POWER_CTRL = 1,
    EN_PLL_CLK_POWER_CTRL   = 2,

} EN_CLK_POWER_CTRL_T;


//=====================================================================================================================
// [0xB0](RO) PMU_CLK_STATUS
//=====================================================================================================================
//=============================================================================
#define PLL_CLK_PWR_STATUS_SHIFT           (7)
#define PLL128M_CLK_OUT_STATUS_SHIFT       (6)
#define PLL96M_CLK_OUT_STATUS_SHIFT        (5)
#define DCXO_HCLK_OUT_STATUS_SHIFT         (4)
#define DCXO_HCLK_PWR_STATUS_SHIFT         (3)
#define RC_HCLK_OUT_STATUS_SHIFT           (2)
#define RC_HCLK_PWR_STATUS_SHIFT           (1)
#define RC_LCLK_STATUS_SHIFT               (0)

#define PMU_CLK_STATUS_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0xB4](RW) PMU_DCXO_HCLK_PWR_SEL
//=====================================================================================================================
//=============================================================================
// PMU_DCXO_HCLK_PWR_SEL[0] DCXO_HCLK_PWR_SEL
#define DCXO_HCLK_PWR_SEL_SHIFT            (0)
#define DCXO_HCLK_PWR_SEL_MSK              ((0x01 << 1) - 1)

typedef enum
{
    EN_DCXO_HCLK_PWR_VDDR      = 0,
    EN_DCXO_HCLK_PWR_DCDC_ACT  = 1,

} EN_DCXO_HCLK_PWR_T;


//=====================================================================================================================
// [0xB8](RW) PMU_DCXO_HCLK_CFG
//=====================================================================================================================
//=============================================================================
// PMU_DCXO_HCLK_CFG[7:0] DCXO_HCLK_CAPR
#define DCXO_HCLK_CAPR_SHIFT               (0)
#define DCXO_HCLK_CAPR_MSK                 ((0x01 << 8) - 1)

//=============================================================================
// PMU_DCXO_HCLK_CFG[15:8] DCXO_HCLK_CAPL
#define DCXO_HCLK_CAPL_SHIFT               (8)
#define DCXO_HCLK_CAPL_MSK                 ((0x01 << 8) - 1)
#define DCXO_HCLK_CAP_3PF                  (30)
#define DCXO_HCLK_CAP_10PF                 (100)
#define DCXO_HCLK_CAP_15PF                 (150)
#define DCXO_HCLK_CAP_28PF5                (285)

//=============================================================================
// PMU_DCXO_HCLK_CFG[18:16] DCXO_HCLK_NGM
#define DCXO_HCLK_NGM_SHIFT                (16)
#define DCXO_HCLK_NGM_MSK                  ((0x01 << 3) - 1)
#define DCXO_HCLK_NGM_3                    (3)

//=============================================================================
// PMU_DCXO_HCLK_CFG[21:19] DCXO_HCLK_IB
#define DCXO_HCLK_IB_SHIFT                 (19)
#define DCXO_HCLK_IB_MSK                   ((0x01 << 3) - 1)
#define DCXO_HCLK_IB_3                     (3)

//=============================================================================
// PMU_DCXO_HCLK_CFG[29:22] DCXO_HCLK_BKUP
#define DCXO_HCLK_BKUP_SHIFT               (22)
#define DCXO_HCLK_BKUP_MSK                 ((0x01 << 8) - 1)

typedef struct
{
    uint8_t  u8Ib;
    uint8_t  u8Ngm;
    uint8_t  u8Capl;
    uint8_t  u8Capr;
    uint32_t u32Backup;

} stDCXOParam_t, *pstDcxoParam_t;


//=====================================================================================================================
// [0xBC](RW) PMU_RC_HCLK_TUNE
//=====================================================================================================================
//=============================================================================
// PMU_RC_HCLK_TUNE[7:0] RC_HCLK_TUNE
#define RC_HCLK_TUNE_SHIFT                 (0)
#define RC_HCLK_TUNE_MSK                   ((0x01 << 8) - 1)


//=====================================================================================================================
// [0xC0](RW) PMU_RC_LCLK_TUNE
//=====================================================================================================================
//=============================================================================
// PMU_RC_LCLK_TUNE[7:0] RC_LCLK_TUNE
#define RC_LCLK_TUNE_SHIFT                 (0)
#define RC_LCLK_TUNE_MSK                   ((0x01 << 8) - 1)


//=====================================================================================================================
// [0xC4](RW) PMU_PLL_CFG
//=====================================================================================================================
//=============================================================================
// PMU_PLL_CFG[1:0] PLL_VCO_TUNE
#define PLL_VCO_TUNE_SHIFT                 (0)
#define PLL_VCO_TUNE_MSK                   ((0x01 << 2) - 1)

//=============================================================================
// PMU_PLL_CFG[2] PLL_TEST_EN
#define PLL_TEST_EN_SHIFT                  (2)
#define PLL_TEST_EN_MSK                    ((0x01 << 1) - 1)

//=============================================================================
// PMU_PLL_CFG[3] PLL_DOUBLER_EN
#define PLL_DOUBLER_SHIFT                  (3)
#define PLL_DOUBLER_EN_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0xDC](RW) PMU_USB_PHY_SEL
//=====================================================================================================================
//=============================================================================
// PMU_USB_PHY_SEL[1:0] USB_PHY_SEL
#define USB_PHY_SEL_SHIFT                  (0)
#define USB_PHY_SEL_MSK                    ((0x01 << 2) - 1)

typedef enum
{
    USB_PHY_RX_ISO_0  = 0,
    USB_PHY_RX_ISO_1  = 1,
    USB_PHY_RX_ISO_PU = 2,

} EN_USB_PHY_RX_ISO_CFG_T;


//=====================================================================================================================
// [0xE0](RW) PMU_BAND_GAP_CFG
//=====================================================================================================================
//=============================================================================
// PMU_BAND_GAP_CFG[2:0] BAND_GAP_VSUB_CTRL
#define BAND_GAP_VSUB_CTRL_SHIFT           (0)
#define BAND_GAP_VSUB_CTRL_MSK             ((0x01 << 3) - 1)

//=============================================================================
// PMU_BAND_GAP_CFG[4:3] BAND_GAP_VCM_CTRL
#define BAND_GAP_VCM_CTRL_SHIFT            (3)
#define BAND_GAP_VCM_CTRL_MSK              ((0x01 << 2) - 1)


#ifdef __cplusplus
}
#endif

#endif /* __REG_PMU_H__ */


