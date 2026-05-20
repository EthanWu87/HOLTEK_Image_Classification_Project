/*************************************************************************************************************
 * @file    reg_sys_ctrl.h
 * @version V1.1
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



#ifndef __REG_SYS_CTRL_H__
#define __REG_SYS_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif



#define SYS_CTRL_COMMON_REG_MAX            (7)
#define SYS_CTRL_LOCK_CLASS_MAX            (3)


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IM  uint32_t SYS_CTRL_LOCK_STA;            /* [0x40](RO) */
    __OM  uint32_t SYS_CTRL_LOCK_SET;            /* [0x44](WO) */
    __OM  uint32_t SYS_CTRL_LOCK_CLR;            /* [0x48](WO) */

} stSysCtrlLock_t;

typedef struct
{
    __IOM uint32_t SYS_CTRL_CP_REMAP_CFG;        /* [0x00](RW) */
    __IOM uint32_t SYS_CTRL_H2H_DELAY_EN;        /* [0x04](RW) */
    __IOM uint32_t SYS_CTRL_SRAM_TIMMING_CFG;    /* [0x08](RW) */
    __IOM uint32_t SYS_CTRL_SRAM_TIMMING_CFG1;   /* [0x0C](RW) */
    __IOM uint32_t SYS_CTRL_CACHE_TIMING_CFG;    /* [0x10](RW) */
          uint32_t RESERVED[11];                 /* [0x14~0x3C] */

    stSysCtrlLock_t LOCK[SYS_CTRL_LOCK_CLASS_MAX]; /* [0x40~0x60] */
    __IOM uint32_t SYS_CTRL_MP_RESET_ADDR;       /* [0x64](RW) */
          uint32_t RESERVED2[6];                 /* [0x68~0x7C] */

    __IM  uint32_t SYS_CTRL_MP_SW_INT_FLAG;      /* [0x80](RO) */
    __OM  uint32_t SYS_CTRL_MP_SW_INT_TRIG;      /* [0x84](WO) */
    __OM  uint32_t SYS_CTRL_MP_SW_INT_CLR;       /* [0x88](WO) */
    __IM  uint32_t SYS_CTRL_CP_SW_INT_FLAG;      /* [0x8C](RO) */
    __OM  uint32_t SYS_CTRL_CP_SW_INT_TRIG;      /* [0x90](WO) */
    __OM  uint32_t SYS_CTRL_CP_SW_INT_CLR;       /* [0x94](WO) */
          uint32_t RESERVED3[10];                /* [0x98~0xBC] */

    __IOM uint32_t SYS_CTRL_CP_PERI_INT_EN;      /* [0xC0](RW) */
    __IOM uint32_t SYS_CTRL_MP_PERI_INT_EN0;     /* [0xC4](RW) */
    __IOM uint32_t SYS_CTRL_MP_PERI_INT_EN1;     /* [0xC8](RW) */
    __IOM uint32_t SYS_CTRL_PMU_INT_EN;          /* [0xCC](RW) */
          uint32_t RESERVED4[12];                /* [0xD0~0xFC] */

    __IOM uint32_t SYS_CTRL_COM_REG[SYS_CTRL_COMMON_REG_MAX]; /* [0x100~0x118](RW) */
          uint32_t RESERVED5[9];                 /* [0x11C~0x13C] */

    __OM  uint32_t SYS_CTRL_TIMER_SYNC;          /* [0x140](WO) */
          uint32_t RESERVED6[15];                /* [0x144~0x17C] */

    __IM  uint32_t SYS_CTRL_USB_INT_FLAG;        /* [0x180](RO) */
    __IOM uint32_t SYS_CTRL_USB_INT_EN;          /* [0x184](RW) */
    __OM  uint32_t SYS_CTRL_USB_INT_CLR;         /* [0x188](WO) */
    __IM  uint32_t SYS_CTRL_USB_INT_EVENT_FLAG;  /* [0x18C](RO) */
          uint32_t RESERVED7[12];                /* [0x190~0x1BC] */

    __IM  uint32_t SYS_CTRL_WDT_WAKEUP_INT_FLAG; /* [0x1C0](RO) */
    __IOM uint32_t SYS_CTRL_WDT_WAKEUP_INT_EN;   /* [0x1C4](RW) */
    __OM  uint32_t SYS_CTRL_WDT_WAKEUP_INT_CLR;  /* [0x1C8](WO) */
          uint32_t RESERVED8[12];                /* [0x1D0~0x1FC] */

    __IOM uint32_t SYS_CTRL_CP_SYSTICK_CFG;      /* [0x200](RW) */
    __IOM uint32_t SYS_CTRL_MP_SYSTICK_CFG;      /* [0x204](RW) */

} stSYSCTRL_Handle_t, *pstSYSCTRL_Handle_t;




//=====================================================================================================================
// [0x00]SYS_CTRL_CP_REMAP_CFG Register
//=====================================================================================================================
//=============================================================================
// SYS_CTRL_CP_REMAP_CFG[31:10] CP_MEM_SIZE Define
#define CP_MEM_SIZE_SHIFT                 (10)
#define CP_MEM_SIZE_MSK                   ((0x01 << 22) - 1)

//=============================================================================
// SYS_CTRL_CP_REMAP_CFG[9:2] CP_MEM_RANG_LOWER Define
#define CP_MEM_RANG_LOWER_SHIFT           (2)
#define CP_MEM_RANG_LOWER_MSK             ((0x01 << 8) - 1)

//=============================================================================
// SYS_CTRL_CP_REMAP_CFG[0] CP_MEM_REMAP_EN Define
#define CP_MEM_REMAP_EN_SHIFT             (0)
#define CP_MEM_REMAP_EN_MSK               ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x40~0x60]SYS_CTRL_LOCK_STA / SYS_CTRL_LOCK_SET / SYS_CTRL_LOCK_CLR Register
//=====================================================================================================================
#define SYS_CTRL_LOCK_PER_REG              (16)
#define SYS_CTRL_LOCK_MAX                  (SYS_CTRL_LOCK_PER_REG * SYS_CTRL_LOCK_CLASS_MAX) // 48

#define SYS_CTRL_LOCK_IDX(id)              ((id) / SYS_CTRL_LOCK_PER_REG)
#define SYS_CTRL_LOCK_SHIFT(id)            ((id) * 2 % 32)
#if defined(__MAIN_PROCESSOR)
    #define SYS_CTRL_LOCK_MSK              (1U)
#else /* __CO_PROCESSOR */
    #define SYS_CTRL_LOCK_MSK              (2U)
#endif

typedef enum
{
    SYS_CTRL_LOCK_ID_IPC_MASTER            = 0,
    SYS_CTRL_LOCK_ID_IPC_SLAVE             = 1,
    SYS_CTRL_LOCK_ID_RECEIVE_STATUS_MASTER = 2,
    SYS_CTRL_LOCK_ID_RECEIVE_STATUS_SLAVE  = 3,

} EN_SYS_CTRL_LOCK_ID_T;


//=====================================================================================================================
// [0x80~0x88, 0x8C~0x94]SYS_CTRL_CP/MP_SW_INT_FLAG, SYS_CTRL_CP/MP_SW_INT_EN, SYS_CTRL_CP/MP_SW_INT_CLR
//=====================================================================================================================
#define SYS_CTRL_SW_INT_BIT2_SHIFT         (2)
#define SYS_CTRL_SW_INT_BIT1_SHIFT         (1)
#define SYS_CTRL_SW_INT_BIT0_SHIFT         (0)

typedef enum
{
    SYS_CTRL_SW_INT_BIT0  = (0x01 << SYS_CTRL_SW_INT_BIT0_SHIFT),
    SYS_CTRL_SW_INT_BIT1  = (0x01 << SYS_CTRL_SW_INT_BIT1_SHIFT),
    SYS_CTRL_SW_INT_BIT2  = (0x01 << SYS_CTRL_SW_INT_BIT2_SHIFT),

} EN_SYS_CTRL_SW_INT_FLAG_T;

#define SYS_CTRL_SW_INT_MASK               (0x07)

typedef enum
{
    SYS_CTRL_CP = 0,
    SYS_CTRL_MP = 1

} EN_SYS_CTRL_CORE_SEL_T;

#define IS_VALID_SYS_CTRL_CORE_SEL(CORE) ((CORE) == (SYS_CTRL_CP) || (CORE) == (SYS_CTRL_MP))


//=====================================================================================================================
// [0xC0~0xC8](RW)SYS_CTRL_CP/MP_PERI_INT_EN Register
//=====================================================================================================================
#define SYS_CTRL_PERI_INT_EN_SHIFT         (0)
#define SYS_CTRL_CP_PERI_INT_EN_MASK       (WORD_MSK)

#define SYS_CTRL_MP_PERI_INT_EN0_MASK      (WORD_MSK)
#define SYS_CTRL_MP_PERI_INT_EN1_MASK      (HALF_WORD_MSK)

#define SYS_CTRL_MP_PERI_INT0_MAX          (32)

#if defined(__CO_PROCESSOR)
#define SYS_CTRL_PERI_INT_MAX              (32)
#else
#define SYS_CTRL_PERI_INT_MAX              (58)
#endif


//=====================================================================================================================
// [0x100~0x118](RW)SYS_CTRL_COM_REG Register
//=====================================================================================================================
#define SYS_CTRL_COM_REG_SHIFT             (0)
#define SYS_CTRL_COM_REG_MSK               (WORD_MSK)

typedef enum
{
    SYS_CTRL_COM_REG_REMAP_ADDR                = 0,
    SYS_CTRL_COM_REG_CP_WFI_FLAG               = 1,
    SYS_CTRL_COM_REG_IPC_ID_MASTER             = 2,
    SYS_CTRL_COM_REG_IPC_ID_SLAVE              = 3,
    SYS_CTRL_COM_REG_CTRL_CP                   = 4,
    SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_MASTER = 5,
    SYS_CTRL_COM_REG_IPC_RECEIVE_STATUS_SLAVE  = 6,

} EN_SYS_CTRL_COM_REG_T;

#define IS_VALID_SYS_CTRL_COM_REG(IDX) ((IDX) < (SYS_CTRL_COMMON_REG_MAX))


//=====================================================================================================================
// [0x140](WO)SYS_CTRL_TIMER_SYNC Register
//=====================================================================================================================
#define TIMER3_CHB_SYNC_STOP_SHIFT         (15)
#define TIMER3_CHB_SYNC_START_SHIFT        (14)
#define TIMER3_CHA_SYNC_STOP_SHIFT         (13)
#define TIMER3_CHA_SYNC_START_SHIFT        (12)
#define TIMER2_CHB_SYNC_STOP_SHIFT         (11)
#define TIMER2_CHB_SYNC_START_SHIFT        (10)
#define TIMER2_CHA_SYNC_STOP_SHIFT         (9)
#define TIMER2_CHA_SYNC_START_SHIFT        (8)
#define TIMER1_CHB_SYNC_STOP_SHIFT         (7)
#define TIMER1_CHB_SYNC_START_SHIFT        (6)
#define TIMER1_CHA_SYNC_STOP_SHIFT         (5)
#define TIMER1_CHA_SYNC_START_SHIFT        (4)
#define TIMER0_CHB_SYNC_STOP_SHIFT         (3)
#define TIMER0_CHB_SYNC_START_SHIFT        (2)
#define TIMER0_CHA_SYNC_STOP_SHIFT         (1)
#define TIMER0_CHA_SYNC_START_SHIFT        (0)

typedef enum
{
    TIMER0_CHA_SYNC_START  = (0x01 << TIMER0_CHA_SYNC_START_SHIFT),
    TIMER0_CHA_SYNC_STOP   = (0x01 << TIMER0_CHA_SYNC_STOP_SHIFT),
    TIMER0_CHB_SYNC_START  = (0x01 << TIMER0_CHB_SYNC_START_SHIFT),
    TIMER0_CHB_SYNC_STOP   = (0x01 << TIMER0_CHB_SYNC_STOP_SHIFT),
    TIMER1_CHA_SYNC_START  = (0x01 << TIMER1_CHA_SYNC_START_SHIFT),
    TIMER1_CHA_SYNC_STOP   = (0x01 << TIMER1_CHA_SYNC_STOP_SHIFT),
    TIMER1_CHB_SYNC_START  = (0x01 << TIMER1_CHB_SYNC_START_SHIFT),
    TIMER1_CHB_SYNC_STOP   = (0x01 << TIMER1_CHB_SYNC_STOP_SHIFT),
    TIMER2_CHA_SYNC_START  = (0x01 << TIMER2_CHA_SYNC_START_SHIFT),
    TIMER2_CHA_SYNC_STOP   = (0x01 << TIMER2_CHA_SYNC_STOP_SHIFT),
    TIMER2_CHB_SYNC_START  = (0x01 << TIMER2_CHB_SYNC_START_SHIFT),
    TIMER2_CHB_SYNC_STOP   = (0x01 << TIMER2_CHB_SYNC_STOP_SHIFT),
    TIMER3_CHA_SYNC_START  = (0x01 << TIMER3_CHA_SYNC_START_SHIFT),
    TIMER3_CHA_SYNC_STOP   = (0x01 << TIMER3_CHA_SYNC_STOP_SHIFT),
    TIMER3_CHB_SYNC_START  = (0x01 << TIMER3_CHB_SYNC_START_SHIFT),
    TIMER3_CHB_SYNC_STOP   = (0x01 << TIMER3_CHB_SYNC_STOP_SHIFT),

} EN_SYS_CTRL_TIMER_SYNC_CTRL_T;

#define TIMER_SYNC_CTRL_MASK               (0xFFFF)


//=====================================================================================================================
// [0x180](RO)SYS_CTRL_USB_INT_FLAG Register
//=====================================================================================================================
#define USB_PHY_INT_FALG_SHIFT             (0)
#define USB_PHY_INT_FALG_MSK               ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x184](RW)SYS_CTRL_USB_INT_EN Register
//=====================================================================================================================
#define USB_PHY_INT_EN_SHIFT               (0)
#define USB_PHY_INT_EN_MSK                 ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x188](WO)SYS_CTRL_USB_INT_CLR Register
//=====================================================================================================================
#define USB_PHY_INT_CLR_SHIFT              (0)
#define USB_PHY_INT_CLR_MSK                ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x18C](RW)SYS_CTRL_USB_INT_EVENT_FLAG Register
//=====================================================================================================================
#define USB_PHY_INT_EVENT_SHIFT            (0)
#define USB_PHY_INT_EVENT_MSK              ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x1C0](RW)SYS_CTRL_WDT_WAKEUP_INT_FLAG Register 
//=====================================================================================================================
#define WDT_WAKEUP_INT_FLAG_SHIFT          (0)
#define WDT_WAKEUP_INT_FLAG_MSK            ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x1C4](RW)SYS_CTRL_WDT_WAKEUP_INT_EN Register 
//=====================================================================================================================
#define WDT_WAKEUP_INT_EN_SHIFT            (0)
#define WDT_WAKEUP_INT_EN_MSK              ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x1C8](RW)SYS_CTRL_WDT_WAKEUP_INT_CLR Register 
//=====================================================================================================================
#define WDT_WAKEUP_INT_CLR_SHIFT           (0)
#define WDT_WAKEUP_INT_CLR_MSK             ((0x01 << 1) - 1)




#ifdef __cplusplus
}
#endif

#endif /* __REG_SYS_CTRL_H__ */


