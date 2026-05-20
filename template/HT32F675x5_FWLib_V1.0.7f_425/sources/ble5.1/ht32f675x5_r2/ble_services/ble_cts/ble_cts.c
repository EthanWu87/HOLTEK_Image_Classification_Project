/*************************************************************************************************************
 * @file    ble_cts.c
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

#include "err_def.h"
#include "app_cfg.h"
#include "utility.h"

#include "gatt_uuid_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"

#include "ble_cts.h"

typedef struct
{
    uint16_t u16SrvHandle;
    uint16_t u16ChrCtHandle;
    uint16_t u16ChrCtCfgHandle;
    uint8_t u8ChrCtCfg;
    EN_ERR_STA_T (*cts_get_time_handler)(stCtsDateTime_t *stCtsDateTime);
    EN_ERR_STA_T (*cts_set_time_handler)(const stCtsDateTime_t *stCtsDateTime);
}stCtsHandle_t;

static stCtsHandle_t gstCtsHandle;
static stCtsDateTime_t gstCtsDateTime;

static uint16_t cts_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle);
static uint16_t cts_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);
static uint32_t cts_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize);

static gatt_serviceCBs_t gCtsCb =
{
    cts_get_attr_cb,        /* Get Attribute Callback */
    cts_read_attr_cb,       /* Read Attribute Callback */
    cts_write_attr_cb,      /* Write Attribute Callback */
};

/**********************************************************************************************************************
 * @brief  Current Time Service Init.
 * @param  stCtsInit: Configuration of CTS
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ble_cts_init(const stCtsInit_t *stCtsInit)
{   
    EN_ERR_STA_T enRet = ERR_STA_OK;

    if (NULL == stCtsInit || NULL == stCtsInit->cts_get_time_handler)
        return ERR_PARA_ERR;


    gstCtsHandle.cts_get_time_handler = stCtsInit->cts_get_time_handler;
    gstCtsHandle.cts_set_time_handler = stCtsInit->cts_set_time_handler;

    gstCtsHandle.u8ChrCtCfg = 1;

    gstCtsHandle.u16SrvHandle = patch_gatts_api_add_service_start(0,CURRENT_TIME_SERV_UUID,NULL,&gCtsCb);
    if (0 == gstCtsHandle.u16SrvHandle)
        return ERR_STA_ERROR;

    gstCtsHandle.u16ChrCtHandle = patch_gatts_api_add_char(0,CURRENT_TIME_UUID,NULL,
                                    ATT_PROPERTY_READ | ATT_PROPERTY_WRITE | ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC, 
                                    NULL, 0);
    if (0 == gstCtsHandle.u16ChrCtHandle)
        return ERR_STA_ERROR;

    gstCtsHandle.u16ChrCtCfgHandle = rom_gatts_api_add_char_descrip_client_config();
    if (0 == gstCtsHandle.u16ChrCtCfgHandle)
        return ERR_STA_ERROR;

    patch_gatts_api_add_service_end();

    gstCtsDateTime.stAdjustReson.u8ManualTimeUpdate = 1;

    return enRet;
}

/**********************************************************************************************************************
 * @brief  Get Current Time.
 * @param  pu8Buf: Data Buffer
 * @param  pu8Buf: The Length of Data Buffer
 * @output
 * @return The Length of Data.
 *********************************************************************************************************************/
static uint16_t cts_get_current_time(uint8_t *pu8Buf,uint16_t u16BufSize)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;

    enRet = gstCtsHandle.cts_get_time_handler(&gstCtsDateTime);
    if (ERR_STA_OK != enRet)
        return 0;

    return ble_cts_date_time_encode(&gstCtsDateTime,pu8Buf);
}

/**********************************************************************************************************************
 * @brief  Set Current Time.
 * @param  pu8Buf: Data Buffer
 * @param  pu8Buf: The Length of Data Buffer
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
static EN_ERR_STA_T cts_set_current_time(uint8_t *pu8Buf,uint16_t u16BufSize)
{
    if (NULL == gstCtsHandle.cts_set_time_handler)
        return ERR_STA_OK;

    memset(&gstCtsDateTime.stAdjustReson,0,sizeof(stCtsAdjustReason_t));

    ble_cts_date_time_decode(&gstCtsDateTime,pu8Buf);
    gstCtsDateTime.stAdjustReson.u8ExternalReferenceTimeUpdate = 1;

    return gstCtsHandle.cts_set_time_handler(&gstCtsDateTime);
}


static uint16_t cts_get_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle)
{
    if (u16AttrHandle == gstCtsHandle.u16ChrCtCfgHandle)
        return 2;
    else
        return sizeof(stCtsDateTime_t);
}

static uint16_t cts_read_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{
    if (u16AttrHandle == gstCtsHandle.u16ChrCtCfgHandle)
    {
        pu8Buf[0] = gstCtsHandle.u8ChrCtCfg;
        pu8Buf[1] = 0;
        return 2;
    }
    else
        return cts_get_current_time(pu8Buf,u16BufSize);
}

static uint32_t cts_write_attr_cb(uint16_t u16ConnHandle, uint16_t u16AttrHandle, uint16_t u16Mode, uint16_t u16Offset, uint8_t *pu8Buf, uint16_t u16BufSize)
{ 
    if (NULL == pu8Buf)
        return 0;

    if (u16AttrHandle == gstCtsHandle.u16ChrCtCfgHandle)
        gstCtsHandle.u8ChrCtCfg = pu8Buf[0];
    else
        cts_set_current_time(pu8Buf,u16BufSize);

    return 0;
}

/**********************************************************************************************************************
 * @brief  Send Current Time to Client.
 * @param  u16ConnHandle: Connection Handle of Ble
 * @output
 * @return status: @ref EN_ERR_STA_T.
 *********************************************************************************************************************/
EN_ERR_STA_T ble_cts_send_time(uint16_t u16ConnHandle)
{
    uint32_t u32Ret = 0;
    uint8_t pu8SendBuf[sizeof(stCtsDateTime_t)];

    if (0x00 == gstCtsHandle.u8ChrCtCfg)
        return ERR_STA_OK;

    u32Ret = cts_get_current_time(pu8SendBuf,sizeof(pu8SendBuf));
    if (0 == u32Ret)
        return ERR_STA_ERROR;

    u32Ret = rom_gatts_api_send_notify(u16ConnHandle,gstCtsHandle.u16ChrCtHandle,pu8SendBuf,u32Ret);
    if (0 != u32Ret)
        return ERR_STA_ERROR;

    return ERR_STA_OK;
}

