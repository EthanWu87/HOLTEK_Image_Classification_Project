/*************************************************************************************************************
 * @file    gls_meas.c
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
#include <stdbool.h>
#include <string.h>

#include "err_def.h"
#include "utility.h"

#include "gatt_service_api.h"
#include "ble_gls.h"
#include "gls_meas.h"

static uint8_t gu8IsNotifyEnable = 1;

/**********************************************************************************************************************
 * @brief  Get GLS Measurement Client Characteristic Configuration Descriptor.
 *
 * @return Client Characteristic Configuration Descriptor.
 *********************************************************************************************************************/
uint8_t gls_meas_get_cfg(void)
{
    return gu8IsNotifyEnable;
}

/**********************************************************************************************************************
 * @brief  Set GLS Measurement Client Characteristic Configuration Descriptor.
 * @param  u8Cfg: Client Characteristic Configuration Descriptor.
 *                  0x00 : Disable
 *                  0x01 : Enable
 * @return None.
 *********************************************************************************************************************/
void gls_meas_set_cfg(uint8_t u8Cfg)
{
    gu8IsNotifyEnable = (u8Cfg & 1);
}

/**********************************************************************************************************************
 * @brief  Packed Measurement Record.
 * @param  pstGlsHandle: GLS Global Handle.
 * @param  pstRecord: GLS Measurement Record.
 * @param  pu8Pkg: Package Buffer.
 *
 * @return Length of Package.
 *********************************************************************************************************************/
static uint8_t gls_record_pack(stGlsHandle_t *pstHandle,const stGlsMeasRec_t *pstRecord,uint8_t *pu8Pkg)
{
    uint8_t u8Len = 0;
    uint8_t u8Flags = pstRecord->u8Flags;

    pu8Pkg[u8Len++] = u8Flags;

    rom_little_endian_store_16(pu8Pkg,u8Len,pstRecord->u16SequenceNumber);
    u8Len += 2;

    u8Len += gls_date_time_encode(&pstRecord->stBaseTime,&pu8Pkg[u8Len]);

    if (u8Flags & GLS_MEAS_FLAGS_TIME_OFFSET)
    {
        rom_little_endian_store_16(pu8Pkg,u8Len,pstRecord->u16TimeOffset);
        u8Len += 2;
    }

    if (u8Flags & GLS_MEAS_FLAGS_GLUCOSE_CONCENTRATION_AND_TYPE_SAMPLE_LOCATION)
    {
        rom_little_endian_store_16(pu8Pkg,u8Len,pstRecord->u16GlucoseConcentration);
        u8Len += 2;
        pu8Pkg[u8Len++] = pstRecord->stTypeSampleLocation.u8SampleLocation << 4 | pstRecord->stTypeSampleLocation.u8Type;
    }

    if (u8Flags & GLS_MEAS_FLAGS_SENSOR_STATUS_ANNUNCAITION)
    {
        rom_little_endian_store_16(pu8Pkg,u8Len,pstRecord->u16Status);
        u8Len += 2;
    }

    return u8Len;
}

/**********************************************************************************************************************
 * @brief  Send Measurement Record by GATT Notify.
 * @param  pstHandle: GLS Global Handle.
 * @param  pstRecord: GLS Measurement Record.
 *
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T gls_meas_send_notify(stGlsHandle_t *pstHandle,const stGlsMeasRec_t *pstRecord)
{
    uint32_t u32Ret = 0;
    uint8_t u8Pkg[sizeof(stGlsMeasRec_t)] = {0};
    uint8_t u8Len = 0;

    u8Len = gls_record_pack(pstHandle,pstRecord,u8Pkg);

    u32Ret = rom_gatts_api_send_notify(pstHandle->u16ConnHandle,pstHandle->stChrsHandle.u16Measurement,u8Pkg,u8Len);

    if (0 != u32Ret)
        return ERR_STA_ERROR;

    return ERR_STA_OK;
}

