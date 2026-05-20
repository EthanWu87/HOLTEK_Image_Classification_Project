/*************************************************************************************************************
 * @file    reg_gpio.h
 * @version V1.1
 * @date    2022-01-11
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



#ifndef __REG_GPIO_H__
#define __REG_GPIO_H__


#ifdef __cplusplus
extern "C" {
#endif

//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum
{
    GPIO_PIN_0   = ((uint32_t) 0x00000001U),
    GPIO_PIN_1   = ((uint32_t) 0x00000002U),
    GPIO_PIN_2   = ((uint32_t) 0x00000004U),
    GPIO_PIN_3   = ((uint32_t) 0x00000008U),
    GPIO_PIN_4   = ((uint32_t) 0x00000010U),
    GPIO_PIN_5   = ((uint32_t) 0x00000020U),
    GPIO_PIN_6   = ((uint32_t) 0x00000040U),
    GPIO_PIN_7   = ((uint32_t) 0x00000080U),
    GPIO_PIN_8   = ((uint32_t) 0x00000100U),
    GPIO_PIN_9   = ((uint32_t) 0x00000200U),
    GPIO_PIN_10  = ((uint32_t) 0x00000400U),
    GPIO_PIN_11  = ((uint32_t) 0x00000800U),
    GPIO_PIN_12  = ((uint32_t) 0x00001000U),
    GPIO_PIN_13  = ((uint32_t) 0x00002000U),
    GPIO_PIN_14  = ((uint32_t) 0x00004000U),
    GPIO_PIN_15  = ((uint32_t) 0x00008000U),
    GPIO_PIN_16  = ((uint32_t) 0x00010000U),
    GPIO_PIN_17  = ((uint32_t) 0x00020000U),
    GPIO_PIN_18  = ((uint32_t) 0x00040000U),
    GPIO_PIN_19  = ((uint32_t) 0x00080000U),
    GPIO_PIN_20  = ((uint32_t) 0x00100000U),
    GPIO_PIN_21  = ((uint32_t) 0x00200000U),
    GPIO_PIN_22  = ((uint32_t) 0x00400000U),
    GPIO_PIN_23  = ((uint32_t) 0x00800000U),
    GPIO_PIN_24  = ((uint32_t) 0x01000000U),
    GPIO_PIN_25  = ((uint32_t) 0x02000000U),
    GPIO_PIN_26  = ((uint32_t) 0x04000000U),
    GPIO_PIN_27  = ((uint32_t) 0x08000000U),
    GPIO_PIN_28  = ((uint32_t) 0x10000000U),
    GPIO_PIN_29  = ((uint32_t) 0x20000000U),
    GPIO_PIN_30  = ((uint32_t) 0x40000000U),
    GPIO_PIN_31  = ((uint32_t) 0x80000000U),

} EN_GPIO_PIN_T;

#define GPIO_PIN_675X5_NUM_MAX         (54)

#define GPIO_PORT_A_NUM                ((uint32_t)32) /* 32 pins */
#define GPIO_PORT_B_NUM                ((uint32_t)22) /* 22 pins */

#define GPIO_PORT_A_MSK                ((uint32_t)0xFFFFFFFFU) /* 32 pins */
#define GPIO_PORT_B_MSK                ((uint32_t)0x003FFFFFU) /* 22 pins */

#define GPION(n)                       (((n) < GPIO_PORT_A_NUM) ? GPIOA : GPIOB)
#define GPIO_PIN_N(n)                  (0x01 << (n % GPIO_PORT_A_NUM))


typedef enum
{
    GPIO_SWD_PIN_SWCLK  = ((uint8_t) 0x01),
    GPIO_SWD_PIN_SWDIO  = ((uint8_t) 0x02),

} EN_GPIO_SWD_NUM_T;

#define GPIO_SWD_PIN_NUM_MAX           (2)
#define GPIO_SWD_PIN_MSK               ((uint8_t)0x03) /* 2 pins */


typedef enum
{
    GPIO_INT_CH0 = 0,
    GPIO_INT_CH1 = 1,
    GPIO_INT_CH2 = 2,

} EN_GPIO_INT_CH_T;

#define GPIO_INT_CH_MAX           (3)
#define IS_VALID_GPIO_INT_CH(CH)  ((CH) < GPIO_INT_CH_MAX)


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IOM uint32_t IOMUX_CFG[GPIO_PIN_675X5_NUM_MAX]; /* [0x00~0xD4](RW) */
          uint32_t RESERVED0[46];                     /* [0xD8~0x18C] */

    __IOM uint32_t IOMUX_QSPI_CTRL;                   /* [0x190](RW) */
    __IOM uint32_t IOMUX_IR_CTRL;                     /* [0x194](RW) */
          uint32_t RESERVED1;                         /* [0x198] */

    __IOM uint32_t IOMUX_FPGA_MODEM_CTRL;             /* [0x19C](RW) */

} stIOMUX_Handle_t, *pstIOMUX_Handle_t;

typedef struct
{
    __IM  uint32_t GPIO_INT_FLAG;                     /* [0x00](RO) */
    __IOM uint32_t GPIO_INT_EN;                       /* [0x04](RW) */
    __OM  uint32_t GPIO_INT_CLR;                      /* [0x08](WO) */
    __IM  uint32_t GPIO_OUT_STATUS;                   /* [0x0C](RO) */
    __OM  uint32_t GPIO_OUT_SET;                      /* [0x10](WO) */
    __OM  uint32_t GPIO_OUT_CLR;                      /* [0x14](WO) */
    __IOM uint32_t GPIO_INT_POL;                      /* [0x18](RW) */
    __IOM uint32_t GPIO_INT_EORL;                     /* [0x1C](RW) */
    __IOM uint32_t GPIO_INT_EDGE;                     /* [0x20](RW) */
    __IOM uint32_t GPIO_INT_VECTOR[GPIO_INT_CH_MAX];  /* [0x24~0x2C](RW) */
    __IM  uint32_t GPIO_IN_STATUS;                    /* [0x30](RO) */
    __IOM uint32_t GPIO_WAKEUP_POL;                   /* [0x34](RW) */
    __IOM uint32_t GPIO_WAKEUP_EN;                    /* [0x38](RW) */

} stGPIO_Handle_t, *pstGPIO_Handle_t;

#define IS_VALID_GPIO_HANDLE(pstGPIO)    ((GPIOA) == (pstGPIO) || (GPIOB) == (pstGPIO))

typedef struct
{
    __OM  uint32_t GPIO_WAKEUP_TRIG;                  /* [0x00](WO) */
    __IOM uint32_t GPIO_WAKEUP_DEBOUNCE;              /* [0x04](RW) */
    __OM  uint32_t GPIO_WAKEUP_CLR;                   /* [0x08](WO) */

} stGPIO_WAKEUP_Handle_t;

typedef struct
{
    __OM  uint32_t GPIO_SWD_OUT_SET;                  /* [0x00](WO) */
    __OM  uint32_t GPIO_SWD_OUT_CLR;                  /* [0x04](WO) */
    __IOM uint32_t GPIO_SWD_CFG[2];                   /* [0x08~0x0C](RW) */
    __IM  uint32_t GPIO_SWD_IN_STATUS;                /* [0x10](RO) */
    __IOM uint32_t GPIO_SWD_DISABLE;                  /* [0x14](RW) */
    __IOM uint32_t GPIO_EXT_CG_EN;                    /* [0x18](RW) */

} stGPIO_SWD_Handle_t, *pstGPIO_SWD_Handle_t;

#define IS_VALID_GPIO_SWD_HANDLE(pstGPIO)    ((GPIO_SWD_CP) == (pstGPIO) || (GPIO_SWD_MP) == (pstGPIO))

typedef struct
{
    __IOM uint32_t GPIO_EXT_CG_EN;                    /* [0x00](RW) */
    __IOM uint32_t GPIO_DCXO_LCLK_OUT_CFG;            /* [0x04](RW) */
    __IM  uint32_t GPIO_WAKEUP_SRC_FLAG;              /* [0x08](RO) */

} stGPIO_DBG_Handle_t, *pstGPIO_DBG_Handle_t;




//=====================================================================================================================
// [0x000~0x14C](RW) IOMUX_CFG
//=====================================================================================================================
//=============================================================================
// IOMUX_CFG[14] GPIO_INPUT_MODE Define
#define GPIO_INPUT_MODE_SHIFT              (14)
#define GPIO_INPUT_MODE_MSK                ((0x01 << 1) - 1)

typedef enum
{
    GPIO_INPUT_CMOS   = 0x00,    /* Cmos input buffer */
    GPIO_INPUT_SCHMIT = 0x01,    /* Schmitt trigger input buffer */

} EN_GPIO_INPUT_MODE_T;

#define IS_VALID_GPIO_INPUT_MODE(MODE) (((MODE) == GPIO_INPUT_CMOS) || \
                                        ((MODE) == GPIO_INPUT_SCHMIT))

//=============================================================================
// IOMUX_CFG[13:12] GPIO_DRV_STRENGTH Define
#define GPIO_DRV_STRENGTH_SHIFT            (12)
#define GPIO_DRV_STRENGTH_MSK              ((0x01 << 2) - 1)

typedef enum
{
    GPIO_DRV_STRENGTH_LEVEL0 = 0x00,  /* Lowest drive strength */
    GPIO_DRV_STRENGTH_LEVEL1 = 0x01,  /* Lower drive strength */
    GPIO_DRV_STRENGTH_LEVEL2 = 0x02,  /* higher drive strength */
    GPIO_DRV_STRENGTH_LEVEL3 = 0x03,  /* highest drive strength */

} EN_GPIO_DRV_STRENGTH_T;

#define IS_GPIO_DRV_STRENGTH_VALID(Level) ((Level) <= GPIO_DRV_STRENGTH_LEVEL3)

//=============================================================================
// IOMUX_CFG[11:10] GPIO_MODE Define
#define GPIO_PULL_SHIFT                    (10)
#define GPIO_PULL_MSK                      ((0x01 << 2) - 1)

typedef enum
{
    GPIO_PULL_NONE    = 0x00, /* pull none */
    GPIO_PULL_DOWN    = 0x01, /* pull down */
    GPIO_PULL_UP      = 0x02, /* pull up */
    GPIO_PULL_DOWN_UP = 0x03,

} EN_GPIO_PULL_MODE_T;

#define IS_VALID_GPIO_PULL_MODE(MODE) (((MODE) == GPIO_PULL_NONE) || \
                                       ((MODE) == GPIO_PULL_DOWN) || \
                                       ((MODE) == GPIO_PULL_UP)   || \
                                       ((MODE) == GPIO_PULL_DOWN_UP))

//=============================================================================
// IOMUX_CFG[9:8] GPIO_MODE Define
#define GPIO_MODE_SHIFT                    (8)
#define GPIO_MODE_MSK                      ((0x01 << 2) - 1)

typedef enum
{
    GPIO_MODE_IMPEDANCE    = 0x00,
    GPIO_MODE_OUTPUT       = 0x01,
    GPIO_MODE_INPUT        = 0x02,

} EN_GPIO_PIN_MODE_T;

#define IS_VALID_GPIO_MODE(MODE) (((MODE) == GPIO_MODE_IMPEDANCE) || \
                                  ((MODE) == GPIO_MODE_OUTPUT)    || \
                                  ((MODE) == GPIO_MODE_INPUT))

//=============================================================================
// IOMUX_CFG[7:0] GPIO_PID Define
#define GPIO_PID_SHIFT                     (0)
#define GPIO_PID_MASK                      ((0x01 << 7) - 1)

typedef enum
{
    PID_GPIO_PIN          = 0x00, /* 0 */
    PID_UART0_CTS         = 0x01, /* 1 */
    PID_UART0_RXD         = 0x02, /* 2 */
    PID_UART0_RTS         = 0x03, /* 3 */
    PID_UART0_TXD         = 0x04, /* 4 */
    PID_UART1_CTS         = 0x05, /* 5 */
    PID_UART1_RXD         = 0x06, /* 6 */
    PID_UART1_RTS         = 0x07, /* 7 */
    PID_UART1_TXD         = 0x08, /* 8 */
    PID_UART2_CTS         = 0x09, /* 9 */
    PID_UART2_RXD         = 0x0A, /* 10 */
    PID_UART2_RTS         = 0x0B, /* 11 */
    PID_UART2_TXD         = 0x0C, /* 12 */
    PID_7816_CLK          = 0x0D, /* 13 */
    PID_7816_DATA         = 0x0E, /* 14 */
    PID_7816_NRST         = 0x0F, /* 15 */
    PID_SPI1_CLK          = 0x10, /* 16 */
    PID_SPI1_MISO         = 0x11, /* 17 */
    PID_SPI1_CSN          = 0x12, /* 18 */
    PID_SPI1_MOSI         = 0x13, /* 19 */
    PID_SPI0_CLK          = 0x14, /* 20 */
    PID_SPI0_MISO         = 0x15, /* 21 */
    PID_SPI0_CSN          = 0x16, /* 22 */
    PID_SPI0_MOSI         = 0x17, /* 23 */
    PID_USB_DEBUG         = 0x18, /* 24 */
    PID_ANA_OUT_CLK       = 0x18, /* 24 */
    PID_RADIO_TEST        = 0x19, /* 25 */
    PID_I2C0_SCL          = 0x1A, /* 26 */
    PID_I2C0_SDA          = 0x1B, /* 27 */
    PID_I2C1_SCL          = 0x1C, /* 28 */
    PID_I2C1_SDA          = 0x1D, /* 29 */
    PID_I2C2_SCL          = 0x1E, /* 30 */
    PID_I2C2_SDA          = 0x1F, /* 31 */
    PID_I2S_OUT_DATA      = 0x20, /* 32 */
    PID_I2S_BCLK          = 0x21, /* 33 */
    PID_I2S_WCLK          = 0x22, /* 34 */
    PID_I2S_IN_DATA       = 0x23, /* 35 */
    PID_I2S_MCLK          = 0x24, /* 36 */
    PID_QDEC_PHASEA       = 0x25, /* 37 */
    PID_QDEC_PHASEB       = 0x26, /* 38 */
    PID_QDEC_LED          = 0x27, /* 39 */
    PID_GTIM_CAP0_CHA     = 0x28, /* 40 */
    PID_GTIM_CAP0_CHB     = 0x29, /* 41 */
    PID_GTIM_PWM0_CHA     = 0x2A, /* 42 */
    PID_GTIM_PWM0_CHB     = 0x2B, /* 43 */
    PID_GTIM_DECODE0_CHA  = 0x2C, /* 44 */
    PID_GTIM_DECODE0_CHB  = 0x2D, /* 45 */
    PID_IR_OUT            = 0x2E, /* 46 */
    PID_GTIM_CAP1_CHA     = 0x2F, /* 47 */
    PID_GTIM_CAP1_CHB     = 0x30, /* 48 */
    PID_GTIM_PWM1_CHA     = 0x31, /* 49 */
    PID_GTIM_PWM1_CHB     = 0x32, /* 50 */
    PID_GTIM_DECODE1_CHA  = 0x33, /* 51 */
    PID_GTIM_DECODE1_CHB  = 0x34, /* 52 */
    PID_GTIM_CAP2_CHA     = 0x35, /* 53 */
    PID_GTIM_CAP2_CHB     = 0x36, /* 54 */
    PID_GTIM_PWM2_CHA     = 0x37, /* 55 */
    PID_GTIM_PWM2_CHB     = 0x38, /* 56 */
    PID_GTIM_DECODE2_CHA  = 0x39, /* 57 */
    PID_GTIM_DECODE2_CHB  = 0x3A, /* 58 */
    PID_GTIM_CAP3_CHA     = 0x3B, /* 59 */
    PID_GTIM_CAP3_CHB     = 0x3C, /* 60 */
    PID_GTIM_PWM3_CHA     = 0x3D, /* 61 */
    PID_GTIM_PWM3_CHB     = 0x3E, /* 62 */
    PID_GTIM_DECODE3_CHA  = 0x3F, /* 63 */
    PID_GTIM_DECODE3_CHB  = 0x40, /* 64 */
    PID_QSPI0_CLK         = 0x41, /* 65 */
    PID_QSPI0_CS          = 0x42, /* 66 */
    PID_QSPI0_SI          = 0x43, /* 67 */
    PID_QSPI0_SO          = 0x44, /* 68 */
    PID_QSPI0_WP          = 0x45, /* 69 */
    PID_QSPI0_HOLD        = 0x46, /* 70 */
    PID_PDM_CLK_OUT       = 0x47, /* 71 */
    PID_PDM_DATA_IN       = 0x48, /* 72 */

    PID_GTIM0_CLK_IN      = 0x66, /* 102 */
    PID_GTIM1_CLK_IN      = 0x67, /* 103 */
    PID_GTIM2_CLK_IN      = 0x68, /* 104 */
    PID_GTIM3_CLK_IN      = 0x69, /* 105 */
    PID_TRXS_RF_SWITCH0   = 0x6A, /* 106 */
    PID_TRXS_RF_SWITCH1   = 0x6B, /* 107 */
    PID_TRXS_RF_SWITCH2   = 0x6C, /* 108 */
    PID_SYS_CLK_OUT       = 0x6D, /* 109 */
    PID_DEBUG_MODE        = 0x6E, /* 110 */
    PID_EXT_PA_EN         = 0x6F, /* 111 */
    PID_EXT_LNA_EN        = 0x70, /* 112 */
    PID_ADC0_TRIG         = 0x71, /* 113 */
    PID_SOI0              = 0x72, /* 114 */
    PID_SOI1              = 0x73, /* 115 */
    PID_SOI2              = 0x74, /* 116 */
    PID_ADC1_TRIG         = 0x75, /* 117 */

    PID_QSPI1_CLK         = 0x79, /* 121 */
    PID_QSPI1_CS          = 0x7A, /* 122 */
    PID_QSPI1_SI          = 0x7B, /* 123 */
    PID_QSPI1_SO          = 0x7C, /* 124 */
    PID_QSPI1_WP          = 0x7D, /* 125 */
    PID_QSPI1_HOLD        = 0x7E, /* 126 */

} EN_GPIO_PID_T;

#define PID_MAX                   (154)
#define IS_VALID_GPIO_PID(PID)    ((PID) < PID_MAX)


//=====================================================================================================================
// [0x190](RW) IOMUX_QSPI_CTRL
//=====================================================================================================================
//=============================================================================
// IOMUX_QSPI_CTRL[3:0] IOMUX_QSPI_FIXED_GPIO_EN Define
#define IOMUX_QSPI_FIXED_GPIO_EN_SHIFT     (0)
#define IOMUX_QSPI_FIXED_GPIO_EN_MSK       ((0x01 << 3) - 1)

typedef enum
{
    QSPI0_FIXED_GPIO_EN = 0x01,
    QSPI1_FIXED_GPIO_EN = 0x02,
    QSPI2_FIXED_GPIO_EN = 0x04,
    QSPI3_FIXED_GPIO_EN = 0x08,

} EN_QSPI_FIXED_GPIO_EN_T;


//=====================================================================================================================
// [0x194](RW) IOMUX_IR_CTRL
//=====================================================================================================================
//=============================================================================
// IOMUX_IR_CTRL[4] IR_TX_OUT_EN Define
#define IR_TX_OUT_EN_SHIFT                 (4)
#define IR_TX_OUT_EN_MSK                   ((0x01 << 1) - 1)

//=============================================================================
// IOMUX_IR_CTRL[3] IR_RX_AMP_EN Define
#define IR_RX_AMP_EN_SHTFT                 (3)
#define IR_RX_AMP_EN_MSK                   ((0x01 << 1) - 1)

//=============================================================================
// IOMUX_IR_CTRL[1:0] IR_RX_RTUNE Define
#define IR_RX_RTUNE_SHTFT                  (0)
#define IR_RX_RTUNE_MSK                    ((0x01 << 2) - 1)


//=====================================================================================================================
// [0x18~0x20](RW) GPIO_INT_POL / GPIO_INT_EORL / GPIO_INT_EDGE
//=====================================================================================================================
typedef enum
{
    GPIO_INT_HIGH_LEVEL   = 0x00,  /* interrupt at high leavel */
    GPIO_INT_LOW_LEVEL    = 0x01,  /* interrupt at low leavel */
    GPIO_INT_RISING_EDGE  = 0x02,  /* interrupt at rising edge */
    GPIO_INT_FALLING_EDGE = 0x03,  /* interrupt at falling edge */
    GPIO_INT_BOTH_EDGE    = 0x04   /* interrupt at both edge */

} EN_GPIO_INT_TYPE_T;

#define IS_VALID_GPIO_INT_TYPE(TYPE) (((TYPE) == GPIO_INT_HIGH_LEVEL)   || \
                                      ((TYPE) == GPIO_INT_LOW_LEVEL)    || \
                                      ((TYPE) == GPIO_INT_RISING_EDGE)  || \
                                      ((TYPE) == GPIO_INT_FALLING_EDGE) || \
                                      ((TYPE) == GPIO_INT_BOTH_EDGE))

typedef enum
{
    GPIO_INT_DISABLE = 0x00,
    GPIO_INT_ENABLE  = 0x01,

} EN_GPIO_INT_EN_T;

#define IS_VALID_GPIO_INT_EN(EN) (((EN) == GPIO_INT_DISABLE) || \
                                  ((EN) == GPIO_INT_ENABLE))

typedef enum
{
    GPIO_LEVEL_LO = 0x00,
    GPIO_LEVEL_HI = 0x01,

} EN_GPIO_LEVEL_T;

#define IS_VALID_GPIO_LEVEL(LEVEL) (((LEVEL) == GPIO_LEVEL_LO) || \
                                    ((LEVEL) == GPIO_LEVEL_HI))


//=====================================================================================================================
// [0x34](RW) GPIO_WAKEUP_POL
//=====================================================================================================================
//=============================================================================
// GPIO_WAKEUP_POL[31:0] GPIO_WAKEUP_POL Define
typedef enum
{
    GPIO_WAKEUP_HIGH_LEVEL  = 0x00,
    GPIO_WAKEUP_LOW_LEVEL   = 0x01,

} EN_GPIO_WAKEUP_POL_T;

#define IS_VALID_GPIO_WAKEUP_POL(POL)   ((POL) == GPIO_WAKEUP_LOW_LEVEL || (POL) == GPIO_WAKEUP_HIGH_LEVEL)




//=====================================================================================================================
// [0x00](WO) GPIO_WAKEUP_TRIG
//=====================================================================================================================
//=============================================================================
// GPIO_WAKEUP_TRIG[0] GPIO_WAKEUP_TRIG Define
#define GPIO_WAKEUP_TRIG_SHIFT             (0)
#define GPIO_WAKEUP_TRIG_MSK               ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x04](RW) GPIO_WAKEUP_DEBOUNCE
//=====================================================================================================================
//=============================================================================
// GPIO_WAKEUP_DEBOUNCE[6] GPIO_WAKEUP_DEB_UNIT Define
#define GPIO_WAKEUP_DEB_UNIT_SHIFT         (6)
#define GPIO_WAKEUP_DEB_UNIT_MSK           ((0x01 << 1) - 1)

typedef enum
{
    GPIO_WAKEUP_DEB_UNIT_30US   = 0x00,
    GPIO_WAKEUP_DEB_UNIT_1MS    = 0x01,

} EN_GPIO_WAKEUP_DEBOUNCE_UNIT_T;

#define IS_VALID_GPIO_WAKEUP_DEBOUNCE_UNIT(UNIT)   ((UNIT) == GPIO_WAKEUP_DEB_UNIT_30US || \
                                                    (UNIT) == GPIO_WAKEUP_DEB_UNIT_1MS)

//=============================================================================
// GPIO_WAKEUP_DEBOUNCE[5:0] GPIO_WAKEUP_DEB_VAL Define
#define GPIO_WAKEUP_DEB_VAL_SHIFT          (0)
#define GPIO_WAKEUP_DEB_VAL_MSK            ((0x01 << 6) - 1)


//=====================================================================================================================
// [0x08](WO) GPIO_WAKEUP_CLR
//=====================================================================================================================
//=============================================================================
// GPIO_WAKEUP_CLR[0] GPIO_WAKEUP_CLR Define
#define GPIO_WAKEUP_CLR_SHIFT              (0)
#define GPIO_WAKEUP_CLR_MSK                ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x00](WO) GPIO_SWD_OUT_SET Register
//=====================================================================================================================

//......

//=====================================================================================================================
// [0x08/0x0C](RW) GPIO_SWCLK_CFG/GPIO_SWDIO_CFG Register
//=====================================================================================================================
//=============================================================================
// GPIO_SWD_CFG[6] GPIO_SWD_INPUT_MODE Define
#define GPIO_SWD_INPUT_MODE_SHIFT          (6)
#define GPIO_SWD_INPUT_MODE_MSK            ((0x01 << 1) - 1)

//=============================================================================
// GPIO_SWD_CFG[5:4] GPIO_SWD_DRV_STRENGTH Define
#define GPIO_SWD_DRV_STRENGTH_SHIFT        (4)
#define GPIO_SWD_DRV_STRENGTH_MSK          ((0x01 << 2) - 1)

//=============================================================================
// GPIO_SWD_CFG[3:2] GPIO_SW_MODE Define
#define GPIO_SWD_PULL_SHIFT                (2)
#define GPIO_SWD_PULL_MSK                  ((0x01 << 2) - 1)

//=============================================================================
// GPIO_SWD_CFG[1:0] GPIO_SW_MODE Define
#define GPIO_SWD_MODE_SHIFT                (0)
#define GPIO_SWD_MODE_MSK                  ((0x01 << 2) - 1)


//=====================================================================================================================
// [0x14](RW) GPIO_SWD_DISABLE Register
//=====================================================================================================================
#define GPIO_SWD_DISABLE_SHIFT             (0)
#define GPIO_SWD_DISABLE_MSK               ((0x01 << 1) - 1)


//=====================================================================================================================
// [0x04](RW) GPIO_DCXO_LCLK_OUT_CFG
//=====================================================================================================================
//=============================================================================
// GPIO_DCXO_LCLK_OUT_CFG[10] GPIO_DCXO32K_OUT_CFG
#define GPIO_DCXO32K_OUT_CFG_SHIFT         (0)
#define GPIO_DCXO32K_OUT_CFG_MSK           ((0x01 << 2) - 1)

typedef enum
{
    DCXO32K_OUT_FORM_PB07  = 0x01,
    DCXO32K_OUT_FORM_PB10  = 0x02,

} EN_DCXO32K_OUT_CFG_T;

#define IS_VALID_DCXO32K_OUT_CFG(CFG)   ((CFG) <= GPIO_DCXO32K_OUT_CFG_MSK)




#ifdef __cplusplus
}
#endif


#endif /* __REG_GPIO_H__ */


