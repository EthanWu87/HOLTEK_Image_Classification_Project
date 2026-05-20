/*************************************************************************************************************
 * @file    reg_rfsec.h
 * @version V1.0 
 * @date    2020-03-12
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



#ifndef __REG_RFSEC_H__
#define __REG_RFSEC_H__


#ifdef __cplusplus
 extern "C" {
#endif


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IO uint32_t RF_RBUS_CALI;            /* [0x00](RW) */
    __IO uint32_t RF_RBUS_RXRF_CFG;        /* [0x04](RW) */
    __IO uint32_t RF_RCFG1_CFG;            /* [0x08](RW) */
    __IO uint32_t RF_RCFG2_CFG;            /* [0x0C](RW) */
    __IO uint32_t RF_RCFG3_CFG;            /* [0x10](RW) */
    __IO uint32_t RF_PA_CTRL;              /* [0x14](RW) */
    __IO uint32_t RF_RBUS_RXRF_CFG2;       /* [0x18](RW) */
    __IO uint32_t AUDIO_ADC_CTRL;          /* [0x1C](RW) */
    __IO uint32_t IR_RBUS_RTRX;            /* [0x20](RW) */
    
} stRFSECB_Handle_t,*psRFSECB_Handle_t;


typedef struct
{
     __O uint32_t RF_READ_TRIG;            /* [0x00](W0) */
    __IO uint32_t RF_READ_ADDR;            /* [0x04](RW) */
    __IO uint32_t MDM_TO_MEM;              /* [0x08](RW) */
     __I uint32_t MDM_STAR_ADDR;           /* [0x0C](R0) */
    __IO uint32_t MDM_CLK_EN;              /* [0x10](WO) */
     __I uint32_t MDM_SMP_DONE;            /* [0x14](RO) */
    __IO uint32_t RF_SOFT_REST;            /* [0x18](RW) */
    __IO uint32_t ACT_INT;                 /* [0x1C](RW) */
     __O uint32_t ACT_INT_CLR;             /* [0x20](WO) */
     __I uint32_t ACC_LASTBYTE;            /* [0x24](R0) */
     __O uint32_t MDM_TO_MEM_POS;          /* [0x28](WO) */
    __IO uint32_t ACT_DELAY_TIM;           /* [0x2C](RW) */
    __IO uint32_t ACT_SDM_DIVN_HI;         /* [0x30](RW) */
    __IO uint32_t ACT_SDM_DIVN_LO;         /* [0x34](RW) */
         uint32_t RESERVED[46];            /* [0x38~0xF0] */

    __IO uint32_t RF_TEMPERATURE_CTRL2;    /* [0xF0](RW) */

} stRFSECG_Handle_t,*psRFSECG_Handle_t;

#define IS_VALID_RFSECG_HANDLE( pstRFSECG )   ( (RFSECG) == (pstRFSECG) )



//=====================================================================================================================
// [RFSECB] [0x1C] AUDIO_ADC_CTRL
//=====================================================================================================================
//=============================================================================
// AUDIO_CTRL[8:7] AUDIO_ADC_MIC_BIAS Define
#define AUDIO_ADC_MIC_BIAS_BITS            (2)
#define AUDIO_ADC_MIC_BIAS_SHIFT           (7)
#define AUDIO_ADC_MIC_BIAS_MSK             ((0x01<<2)-1)

typedef enum
{
    AUDIO_ADC_MIC_BIAS_DISABLE = 0,
    AUDIO_ADC_MIC_BIAS_1_8V    = 1,
    AUDIO_ADC_MIC_BIAS_2_5V    = 2,
    AUDIO_ADC_MIC_BIAS_VDDR    = 3
    
}EN_AUDIO_ADC_MIC_BIAS_T;

#define IS_VALID_AUDIO_ADC_MIC_BIAS( BIAS )   ( ((BIAS) == AUDIO_ADC_MIC_BIAS_DISABLE) || \
                                                ((BIAS) == AUDIO_ADC_MIC_BIAS_1_8V)    || \
                                                ((BIAS) == AUDIO_ADC_MIC_BIAS_2_5V)    || \
                                                ((BIAS) == AUDIO_ADC_MIC_BIAS_VDDR) )

//=============================================================================
// AUDIO_CTRL[6] AUDIO_ADC_EN Define
#define AUDIO_ADC_EN_BITS                  (1)
#define AUDIO_ADC_EN_SHIFT                 (6)
#define AUDIO_ADC_EN_MSK                   ((0x01<<1)-1)

typedef enum
{
    AUDIO_ADC_DISABLE = 0x00,
    AUDIO_ADC_ENABLE  = 0x01,
    
} EN_AUDIO_ADC_EN_T;

#define IS_VALID_AUDIO_ADC_EN( EN )   ( ((EN) == AUDIO_ADC_DISABLE) || \
                                        ((EN) == AUDIO_ADC_ENABLE) )

//=============================================================================
// AUDIO_CTRL[5:4] AUDIO_BIAS_CFG Define
#define AUDIO_BIAS_CFG_BITS                (2)
#define AUDIO_BIAS_CFG_SHIFT               (4)
#define AUDIO_BIAS_CFG_MSK                 ((0x01<<2)-1)

//=============================================================================
// AUDIO_CTRL[3:0] AUDIO_ADC_PGA_GAIN Define
#define AUDIO_ADC_PGA_GAIN_BITS            (4)
#define AUDIO_ADC_PGA_GAIN_SHIFT           (0)
#define AUDIO_ADC_PGA_GAIN_MSK             ((0x01<<4)-1)




//=====================================================================================================================
// [RFSECG] [0xF0] RF_TEMPERATURE_CTRL2 
//=====================================================================================================================

//=====================================================================================================================
//  [0x04] RF_READ_ADDR
//=====================================================================================================================

//=====================================================================================================================
//  [0x08] MDM_TO_MEM
//=====================================================================================================================

//=====================================================================================================================
//  [0x0C] MDM_TO_MEM
//=====================================================================================================================

//=====================================================================================================================


#ifdef __cplusplus
}
#endif

#endif /* __REG_RFSEC_H__ */


