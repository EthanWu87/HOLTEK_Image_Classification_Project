/*************************************************************************************************************
 * @file    reg_ecc.h
 * @version V1.0 
 * @date    2020-05-20
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



#ifndef __REG_ECC_H__
#define __REG_ECC_H__


#ifdef __cplusplus
 extern "C" {
#endif


//=====================================================================================================================
// DEFAULT CONFIG
//=====================================================================================================================
#define ECC_INIT_RX_DEFAULT( u16Length, u8DataSize )                  \
( (u16Length)                                     | /* bit0~bit15 */  \
  (ECC_LOOP_EN_MSK << ECC_LOOP_EN_SHIFT)          | /* bit16 */       \
  (ECC_PRIO_LEVEL_LOW << ECC_PRIORITY_SEL_SHIFT)  | /* bit17 */       \
  (ECC_PERI_TO_MEM << ECC_WORK_MODE_SEL_SHIFT)    | /* bit22~bit23 */ \
  (u8DataSize << ECC_DST_DATA_SIZE_SHIFT)         | /* bit24~bit25 */ \
  (ECC_ADDR_INC_ENABLE << ECC_DST_INC_EN_SHIFT)   | /* bit26 */       \
  (u8DataSize << ECC_SRC_DATA_SIZE_SHIFT)         | /* bit27~bit28 */ \
  (ECC_ADDR_INC_DISABLE << ECC_SRC_INC_EN_SHIFT)    /* bit29 */       \
)

#define ECC_INIT_TX_DEFAULT( u16Length, u8DataSize )                  \
( (u16Length)                                     | /* bit0~bit15 */  \
  (ECC_LOOP_EN_MSK << ECC_LOOP_EN_SHIFT)          | /* bit16 */       \
  (ECC_PRIO_LEVEL_LOW << ECC_PRIORITY_SEL_SHIFT)  | /* bit17 */       \
  (ECC_MEM_TO_PERI << ECC_WORK_MODE_SEL_SHIFT)    | /* bit22~bit23 */ \
  (u8DataSize << ECC_DST_DATA_SIZE_SHIFT)         | /* bit24~bit25 */ \
  (ECC_ADDR_INC_DISABLE << ECC_DST_INC_EN_SHIFT)  | /* bit26 */       \
  (u8DataSize << ECC_SRC_DATA_SIZE_SHIFT)         | /* bit27~bit28 */ \
  (ECC_ADDR_INC_ENABLE << ECC_SRC_INC_EN_SHIFT)     /* bit29 */       \
)


//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum
{
    ECC_CH0 = 0,
    ECC_CH1 = 1,
    ECC_CH2 = 2,
    ECC_CH3 = 3,
    ECC_CH_MAX = 4,
    
} EN_ECC_CH_T;

#define IS_VALID_ECC_CH( CH ) ( (CH) < ECC_CH_MAX )

typedef enum
{
    ECC_DATA0 = 0,
    ECC_DATA1 = 1,
    ECC_DATA2 = 2,
    ECC_DATA3 = 3,
    ECC_DATA4 = 4,
    ECC_DATA5 = 5,
    ECC_DATA6 = 6,
    ECC_DATA7 = 7,
    ECC_DATA_MAX = 8,
    
} EN_ECC_DATA_T;

typedef enum
{
    ECC_DATA_M0 = 0,
    ECC_DATA_M1 = 1,
    ECC_DATA_M2 = 2,
    ECC_DATA_M3 = 3,
    ECC_DATA_M4 = 4,
    ECC_DATA_M5 = 5,
    ECC_DATA_M6 = 6,
    ECC_DATA_M_MAX = 7,
    
} EN_ECC_DATA_M_T;


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IO uint32_t ECC_CMD;                                  /* [0x000](RW) */
    __IO uint32_t ECC_CFG;                                  /* [0x004](RW) */
    __O  uint32_t ECC_TRIG_START;                           /* [0x008](WO) */
    __I  uint32_t ECC_INT_FLAG;                             /* [0x00C](RO) */
    __O  uint32_t ECC_INT_CLR;                              /* [0x010](WO) */
    __IO uint32_t ECC_INT_EN;                               /* [0x014](RW) */
    __IO uint32_t ECC_RESERVED[250];                        /* [0x018~0x3FC](RW) */
    __IO uint32_t ECC_DATA_M[ECC_DATA_M_MAX][ECC_DATA_MAX]; /* [0x400~0x4DC](RW) */
    __IO uint32_t ECC_DATA_MP[ECC_DATA_MAX];                /* [0x4E0~0x4FC](RW) */
    __IO uint32_t ECC_DATA_MK[ECC_DATA_MAX];                /* [0x500~0x51C](RW) */
    __IO uint32_t ECC_DATA_GX[ECC_DATA_MAX];                /* [0x520~0x53C](RW) */
    __IO uint32_t ECC_DATA_GY[ECC_DATA_MAX];                /* [0x540~0x55C](RW) */
    
} stECC_Handle_t,*pstECC_Handle_t;


//#define IS_VALID_ECC_HANDLE( pstECC ) ( (PERI_ECC) == (pstECC) )

//=====================================================================================================================
// [0x000] ECC_CMD Register
//=====================================================================================================================
#define ECC_CMD_DEFAULT                    (0x00000B03)

//=============================================================================
// ECC_CMD[11:9] ECC_DATA_SIZE Define
#define ECC_DATA_SIZE_BITS                 (3)
#define ECC_DATA_SIZE_SHIFT                (9)
#define ECC_DATA_SIZE_MSK                  ((0x01<<3)-1)

typedef enum
{
    ECC_DATA_SIZE_32BIT  = 0,
    ECC_DATA_SIZE_64BIT  = 1,
    ECC_DATA_SIZE_128BIT = 2,
    ECC_DATA_SIZE_192BIT = 3,
    ECC_DATA_SIZE_224BIT = 4,
    ECC_DATA_SIZE_256BIT = 5,
    
} EN_ECC_DATA_SIZE_T;

#define IS_VALID_ECC_DATA_SIZE( SIZE )   ( (SIZE) <= ECC_DATA_SIZE_256BIT )


//=====================================================================================================================
// [0x00~0x08] ECC_INT_FLAG / ECC_INT_EN / ECC_INT_CLR Register
//=====================================================================================================================
#define ECC_1_4_DONE_BITS                  (1)
#define ECC_1_4_DONE_SHIFT                 (4)
#define ECC_1_4_DONE_MSK                   ((0x01<<1)-1)

#define ECC_1_2_DONE_BITS                  (1)
#define ECC_1_2_DONE_SHIFT                 (3)
#define ECC_1_2_DONE_MSK                   ((0x01<<1)-1)

#define ECC_3_4_DONE_BITS                  (1)
#define ECC_3_4_DONE_SHIFT                 (2)
#define ECC_3_4_DONE_MSK                   ((0x01<<1)-1)

#define ECC_DONE_BITS                      (1)
#define ECC_DONE_SHIFT                     (1)
#define ECC_DONE_MSK                       ((0x01<<1)-1)

#define ECC_TIMEOUT_BITS                   (1)
#define ECC_TIMEOUT_SHIFT                  (0)
#define ECC_TIMEOUT_MSK                    ((0x01<<1)-1)

typedef enum
{
    ECC_1_4_DONE    = ( ECC_1_4_DONE_MSK << ECC_1_4_DONE_SHIFT ),
    ECC_1_2_DONE    = ( ECC_1_2_DONE_MSK << ECC_1_2_DONE_SHIFT ),
    ECC_3_4_DONE    = ( ECC_3_4_DONE_MSK << ECC_3_4_DONE_SHIFT ),
    ECC_DONE        = ( ECC_DONE_MSK << ECC_DONE_SHIFT ),
    ECC_TIMEOUT     = ( ECC_TIMEOUT_MSK << ECC_TIMEOUT_SHIFT )
    
} EN_ECC_INT_BITS_T;

#define ECC_INT_BITS                       (0x05)
#define ECC_INT_MSK                        (0x1F)

//=====================================================================================================================
// [0x0C] ECC_CFG Register
//=====================================================================================================================
#define ECC_CFG_DEFAULT                    (0x00000000)

//=============================================================================
// ECC_CFG[31] ECC_ENABLE Define
#define ECC_ENABLE_BITS                    (1)
#define ECC_ENABLE_SHIFT                   (31)
#define ECC_ENABLE_MSK                     ((0x01U<<1)-1)//U:fix warnning

typedef enum
{
    ECC_DISABLE  = (0x00),
    ECC_ENABLE   = (0x01),
    
} EN_ECC_ENABLE_T;

#define IS_VALID_ECC_EN( EN )   ( ((EN) == ECC_DISABLE) || ((EN) == ECC_ENABLE) )

//=============================================================================
// ECC_CFG[30] ECC_PAUSE_EN Define
#define ECC_PAUSE_EN_BITS                  (1)
#define ECC_PAUSE_EN_SHIFT                 (30)
#define ECC_PAUSE_EN_MSK                   ((0x01<<1)-1)

typedef enum
{
    ECC_PAUSE_DISABLE  = (0x00),
    ECC_PAUSE_ENABLE   = (0x01),
    
} EN_ECC_PAUSE_ENABLE_T;

#define IS_VALID_ECC_PAUSE_EN( EN )   ( ((EN) == ECC_PAUSE_DISABLE) || \
                                        ((EN) == ECC_PAUSE_ENABLE) )

//=============================================================================
// ECC_CFG[29] ECC_SRC_INC_EN Define
#define ECC_SRC_INC_EN_BITS                (1)
#define ECC_SRC_INC_EN_SHIFT               (29)
#define ECC_SRC_INC_EN_MSK                 ((0x01<<1)-1)

//=============================================================================
// ECC_CFG[28:27] ECC_SRC_DATA_SIZE Define
#define ECC_SRC_DATA_SIZE_BITS             (2)
#define ECC_SRC_DATA_SIZE_SHIFT            (27)
#define ECC_SRC_DATA_SIZE_MSK              ((0x01<<2)-1)

//=============================================================================
// ECC_CFG[26] ECC_DST_INC_EN Define
#define ECC_DST_INC_EN_BITS                (1)
#define ECC_DST_INC_EN_SHIFT               (26)
#define ECC_DST_INC_EN_MSK                 ((0x01<<1)-1)

typedef enum
{
    ECC_ADDR_INC_DISABLE  = (0x00),
    ECC_ADDR_INC_ENABLE   = (0x01),
    
} EN_ECC_ADDR_INC_EN_T;



#ifdef __cplusplus
}
#endif

#endif /* __REG_ECC_H__ */


