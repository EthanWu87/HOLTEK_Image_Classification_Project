/*************************************************************************************************************
 * @file    tt_service.c
 * @version Initial Draft
 * @date    2023-08-25
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
#include "stack_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"
#include "gatt_client_api.h"

#include "gatt_uuid_def.h"
#include "utility.h"
#include "gap_api.h"

#include "app_cfg.h"
#include "ble_event.h"

#include "tt_service.h"

typedef struct
{
    uint16_t u16SrvHandle;
    uint16_t u16TxHandle;
    uint16_t u16RxHandle;
    uint16_t u16TxCfgHandle;
    uint8_t u8TxEnable;
}stTtsHandle_t;

static stTtsHandle_t gstTtsHandle;
static tt_recv_handler grxCb = NULL;

static uint16_t tt_get_attrLen_cb(uint16_t u16ConnHandle,uint16_t u16AttrHandle);
static uint16_t tt_read_attr_cb(uint16_t u16ConnHandle,uint16_t u16AttrHandle,uint16_t u16Offset,uint8_t *pu8Buf,uint16_t u16BufSize);
static uint32_t tt_write_attr_cb(uint16_t u16ConnHandle,uint16_t u16AttrHandle,uint16_t u16Mode,uint16_t u16Offset,uint8_t *pu8Buf,uint16_t u16BufSize);

static gatt_serviceCBs_t stTtServer_cb =
{
    tt_get_attrLen_cb,  // get dynamic attr len
    tt_read_attr_cb,    // Read callback function pointer
    tt_write_attr_cb,   // Write callback function pointer
};


EN_ERR_STA_T tt_service_init(tt_recv_handler rxCb)
{
    grxCb = rxCb;
    // Add the tt service.
    gstTtsHandle.u16SrvHandle = patch_gatts_api_add_service_start(0,TT_SERVICE_UUID,NULL,&stTtServer_cb );
    if (0 == gstTtsHandle.u16SrvHandle)
        return ERR_STA_ERROR;

    // Add the TX Characteristic.
    gstTtsHandle.u16TxHandle = patch_gatts_api_add_char(0,TT_TX_UUID,NULL,(ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC),NULL,0);
    if (0 == gstTtsHandle.u16TxHandle)
        return ERR_STA_ERROR;
    
    // Add the TX Characteristic Description.
    gstTtsHandle.u16TxCfgHandle = rom_gatts_api_add_char_descrip_client_config();
    if (0 == gstTtsHandle.u16TxCfgHandle)
        return ERR_STA_ERROR;
    
    // Add the RX Characteristic.
    gstTtsHandle.u16RxHandle = patch_gatts_api_add_char(0,TT_RX_UUID,NULL,(ATT_PROPERTY_WRITE_WITHOUT_RESPONSE | ATT_PROPERTY_DYNAMIC),NULL,0);
    if (0 == gstTtsHandle.u16RxHandle)
        return ERR_STA_ERROR;
    
    // End
    patch_gatts_api_add_service_end();
    
    gstTtsHandle.u8TxEnable = 1;
    
    return  0;
}


EN_ERR_STA_T tt_serivce_send(uint16_t u16ConnHandle, uint8_t *pu8Data, uint16_t u16DataLen)
{
    uint32_t u32Ret;
    
    u32Ret = rom_gatts_api_send_notify(u16ConnHandle,gstTtsHandle.u16TxHandle,pu8Data,u16DataLen);
    if (0 != u32Ret)
        return ERR_STA_ERROR;
    
    return ERR_STA_OK;
}


static uint16_t tt_get_attrLen_cb (uint16_t u16ConnHandle,uint16_t u16AttrHandle)
{
    if (gstTtsHandle.u16TxCfgHandle == u16AttrHandle)
        return 2;
    
    return 0;
}

static uint16_t tt_read_attr_cb (uint16_t u16ConnHandle,uint16_t u16AttrHandle,uint16_t u16Offset,uint8_t *pu8Buf,uint16_t u16BufSize)
{
    if (gstTtsHandle.u16TxCfgHandle == u16AttrHandle)
    {
        pu8Buf[0] = gstTtsHandle.u8TxEnable;
        pu8Buf[1] = 0;
        return 2;
    }
    return 0;
}


uint32_t tt_write_attr_cb (uint16_t u16ConnHandle,uint16_t u16AttrHandle,uint16_t u16Mode,uint16_t u16Offset,uint8_t *pu8Buf,uint16_t u16BufSize)
{
    if (gstTtsHandle.u16TxCfgHandle == u16AttrHandle)
        gstTtsHandle.u8TxEnable = pu8Buf[0];
    else if (gstTtsHandle.u16RxHandle == u16AttrHandle)
    {
        if (pu8Buf && grxCb)
            grxCb(pu8Buf,u16BufSize);
    }
    
    return 0;
}