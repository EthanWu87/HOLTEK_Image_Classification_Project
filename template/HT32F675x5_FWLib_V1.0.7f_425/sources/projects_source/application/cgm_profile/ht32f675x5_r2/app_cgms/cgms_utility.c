/*************************************************************************************************************
 * @file    cgms_utility.c
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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cgms_utility.h"

/**
 * @brief  Float to IEEE Float16.
 * @return fInput: float.
 */
sfloat_t float_to_sfloat(float fInput)
{
    sfloat_t sfloat;
    if(fInput != fInput)            /* Check for NAN */
    {
        sfloat.i8Exponent = 0;
        sfloat.i16Mantissa = 0x07FF;
        return sfloat;
    }
    else if(fInput > (float)2E10)   /* Check for +INF */
    {
        sfloat.i8Exponent = 0;
        sfloat.i16Mantissa = 0x07FE;
        return sfloat;
    }
    else if(fInput < (float)-2E10)  /* Check for -INF */
    {
        sfloat.i8Exponent = 0;
        sfloat.i16Mantissa = 0x0802;
        return sfloat;
    }
    else
    {
        sfloat.i8Exponent = 0;
        
        if (fInput < 0.0001 && fInput > -0.0001 )
        {
            sfloat.i8Exponent = 0;
            sfloat.i16Mantissa = 0;
            return sfloat;
        }
        
        while(fInput > (float)0x7FF || fInput < -(float)0x7FF)
        {
            fInput /= 10;
            sfloat.i8Exponent += 1;
        }
        
        if (fInput < 0)
        {
            while(-fInput * 10 < (float)0x7FF)
            {
                fInput *= 10;
                sfloat.i8Exponent -= 1;
            }
        }
        else if (fInput > 0)
        {
            while(fInput * 10 < (float)0x7FF)
            {
                fInput *= 10;
                sfloat.i8Exponent -= 1;
            }
        }
        
        sfloat.i16Mantissa = ((int16_t)fInput) & 0xFFF;
        sfloat.i8Exponent &= 0xF;
        
        return sfloat;
    }
}

/**
 * @brief  IEEE Float16 to u16.
 * @return sfloat: IEEE Float16.
 */
uint16_t sfloat_to_u16(sfloat_t sfloat)
{
    return ((sfloat.i8Exponent << 12) & 0xF000) | ((sfloat.i16Mantissa << 0) & 0x0FFF);
}

sfloat_t u16_to_sfloat(uint16_t u16Input)
{
    sfloat_t sfloat;

    sfloat.i8Exponent = (u16Input & 0xF000) >> 12;
    sfloat.i16Mantissa = u16Input & 0x0FFF;

    return sfloat;
}

float sfloat_to_float(sfloat_t sfloat)
{
    float f;

    if ( (sfloat.i16Mantissa & 0x0800) > 0 )
        sfloat.i16Mantissa |= 0xF000;

    f = (float )sfloat.i16Mantissa;

    if ( (sfloat.i8Exponent & 0x08) > 0 )
        sfloat.i8Exponent |= 0xF0;

    while (sfloat.i8Exponent > 0)
    {
        f *= 10;
        sfloat.i8Exponent--;
    }
    
    while (sfloat.i8Exponent < 0)
    {
        f /= 10;
        sfloat.i8Exponent++;
    }
    
    return f;
}

bool str_to_float(const char *str,float *f)
{
    char *pEnd = NULL;
    const char *pBegin = str;

    *f = strtof(pBegin,&pEnd);
    if (pEnd == pBegin)
        return false;
    
    return true;
}
