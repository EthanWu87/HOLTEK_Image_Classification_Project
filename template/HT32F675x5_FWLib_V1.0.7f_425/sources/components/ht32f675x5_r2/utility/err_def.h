/*************************************************************************************************************
 * @file    err_def.h
 * @version V1.0
 * @date    2020-01-03
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


#ifndef __ERR_DEF_H__
#define __ERR_DEF_H__

#ifdef __cplusplus
extern "C"
{
#endif

//=====================================================================================================================
// TYPEDEF ENUM
//=====================================================================================================================
typedef enum
{
    ERR_STA_OK          = 0x00,
    ERR_STA_ERROR       = 0x01,
    ERR_STA_BUSY        = 0x02,
    ERR_STA_TIMEOUT     = 0x03,
    ERR_STA_BREAK       = 0x04,

    ERR_PARA_ERR        = 0x10,

    ERR_DATA_BUSY       = 0x20, // Data is not ready
    ERR_NOT_ALLOWED     = 0x21,
    ERR_DATA_NOT_FOUND  = 0x22,

} EN_ERR_STA_T;

#define ERR_RETURN_IF_ERROR(enRet) \
    do                             \
    {                              \
        if (ERR_STA_OK != (enRet)) \
        {                          \
            return (enRet);        \
        }                          \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* __ERR_DEF_H__ */
