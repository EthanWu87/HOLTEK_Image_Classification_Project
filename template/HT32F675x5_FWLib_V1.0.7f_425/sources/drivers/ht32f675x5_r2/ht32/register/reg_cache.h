/*************************************************************************************************************
 * @file    reg_cache.h
 * @version V1.0
 * @date    2020-03-31
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


#ifndef __REG_CACHE_H__
#define __REG_CACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

//=====================================================================================================================
// DEFAULT CONFIG
//=====================================================================================================================
#define CACHE_READ_MODE_DEFAULT(MODE)                                                       \
( ((MODE & MEM_CACHE_READ_CMD_MSK) << MEM_CACHE_READ_CMD_SHIFT)         | /* bit0~bit7 */   \
  ((SFLASH_CMD_SUS & MEM_CACHE_SUS_CMD_MSK) << MEM_CACHE_HPM_CMD_SHIFT) | /* bit8~bit15 */  \
  ((SFLASH_CMD_RES & MEM_CACHE_RES_CMD_MSK) << MEM_CACHE_HPM_CMD_SHIFT) | /* bit16~bit23 */ \
  ((SFLASH_CMD_HPM & MEM_CACHE_HPM_CMD_MSK) << MEM_CACHE_HPM_CMD_SHIFT)   /* bit24~bit31 */ \
)


//=====================================================================================================================
// TYPEDEF STRUCT
//=====================================================================================================================
typedef struct
{
    __IOM uint32_t CACHE_CTRL;              /* [0x00](RW) */
    __OM  uint32_t CACHE_CMD_EN;            /* [0x04](WO) */
    __IM  uint32_t CACHE_CMD_BUSY;          /* [0x08](RO) */

} stCACHE_Handle_t, *pstCACHE_Handle_t;


//=====================================================================================================================
// [0x00]CACHE_CTRL Register
//=====================================================================================================================
#define CACHE_CTRL_DEFAULT                 (0x00000000)

//=============================================================================
// CACHE_CTRL[6] CACHE_WRAP Define
#define CACHE_WRAP_SHIFT                   (6)
#define CACHE_WRAP_MSK                     ((0x01 << 1) - 1)

//=============================================================================
// CACHE_CTRL[5:1] CACHE_CMD Define
#define CACHE_CMD_SHIFT                    (1)
#define CACHE_CMD_MSK                      ((0x01 << 5) - 1)

//=============================================================================
// CACHE_CTRL[0] CACHE_EN Define
#define CACHE_EN_SHIFT                     (0)
#define CACHE_EN_MSK                       ((0x01 << 1) - 1)

typedef enum
{
    CACHE_DISABLE  = 0x00,
    CACHE_ENABLE   = 0x01,

} EN_CACHE_ENABLE_T;

#define IS_VALID_CACHE_ENABLE(EN)   (((EN) == CACHE_DISABLE) || \
                                     ((EN) == CACHE_ENABLE))


//=====================================================================================================================
// [0x04]CACHE_CMD_EN Register
//=====================================================================================================================
#define CACHE_CMD_EN_SHIFT                 (0)
#define CACHE_CMD_EN_MSK                   ((0x01 << 1) - 1)

typedef enum
{
    CACHE_CMD_DISABLE  = 0,
    CACHE_CMD_ENABLE   = 1,

} EN_CACHE_CMD_ENABLE_T;

#define IS_VALID_CACHE_CMD_ENABLE(EN)   (((EN) == CACHE_CMD_DISABLE) || \
                                         ((EN) == CACHE_CMD_ENABLE))

//=====================================================================================================================
// [0x08]CACHE_CMD_BUSY Register
//=====================================================================================================================
#define CACHE_CMD_STATUS_SHIFT             (0)
#define CACHE_CMD_STATUS_MSK               ((0x01 << 1) - 1)
#define CACHE_CMD_STATUS_BUSY              ((CACHE_CMD_BUSY & CACHE_CMD_STATUS_MSK) << CACHE_CMD_STATUS_SHIFT)

typedef enum
{
    CACHE_CMD_FINISHED  = 0,
    CACHE_CMD_BUSY      = 1,

} EN_CACHE_CMD_STATUS_T;



#ifdef __cplusplus
}
#endif

#endif /* __REG_CACHE_H__ */


