/*************************************************************************************************************
 * @file    boards.h
 * @version V1.0
 * @date    2022-09-22
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


#ifndef __BOARDS_H__
#define __BOARDS_H__

#if 0  /* 0: Legacy Board, 1: For BCT-32F67575 or BM53A595A                                                 */
// HT32F67575 SoC Development Board
#if defined(HT32F67575_EVB)
    #include "ht32f67575_evb_legacy.h"

// HT32F67595 SoC Socket Development Board
#elif defined(HT32F67595_EVB)
    #include "ht32f67595_evb_legacy.h"
// Undefine board
#else
    #error "Undefine board config"
#endif
#else
// HT32F67575 SoC Development Board (BCT-32F67575)
#if defined(HT32F67575_EVB)
    #include "ht32f67575_evb.h"

// HT32F67595 SoC BMduino Board (BM53A595A)
#elif defined(HT32F67595_EVB)
    #include "ht32f67595_evb.h"
// Undefine board
#else
    #error "Undefine board config"
#endif
#endif

#endif /* __BOARDS_H__ */


