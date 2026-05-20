/*************************************************************************************************************
 * @file    gls_utility.h
 * @version V1.0
 * @date    2021-02-06
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
#ifndef CGMS_UTILITY_H
#define CGMS_UTILITY_H

typedef struct
{
  int8_t  i8Exponent;           /**< Base 10 exponent, only 4 bits */
  int16_t i16Mantissa;          /**< Mantissa, only 12 bits */
}sfloat_t;

sfloat_t float_to_sfloat(float fInput);
float sfloat_to_float(sfloat_t sfloat);
uint16_t sfloat_to_u16(sfloat_t sfloat);
sfloat_t u16_to_sfloat(uint16_t u16Input);
bool str_to_float(const char *str,float *f);
#endif