/*************************************************************************************************************
 * @file    ota.c
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
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "boards.h"
#include "app_cfg.h"
#include "utility.h"
#include "crc.h"
#include "version.h"
#include "bluetooth.h"
#include "host_stack_conn_hdl.h"
#include "gap_api.h"
#include "gatt_client_api.h"
#include "hw_crg.h"
#include "flash.h"
#include "ota_service.h"
#include "ota.h"

#define CRC16_DEFAULT   (0x0)

static uint16_t gu16ConnHandle = 0;
static uint16_t gu16OldMtu = 0;
static uint32_t gu32BinSize = 0;
static uint32_t gu32BinCrc = 0;
static uint32_t gu32ContinuousCodeSize = 0;
static uint16_t gu16PkgIdx = 0;
static uint32_t gu32CmpltCodeSize = 0;

/**********************************************************************************************************************
 * @brief  OTA parameters initialization.
 * @output
 * @return None
 *********************************************************************************************************************/
static void ota_params_init(void)
{
    gu32BinSize = 0;
    gu32BinCrc = 0;
    gu32ContinuousCodeSize = 0;
    gu16PkgIdx = 0;
    gu32CmpltCodeSize = 0;
}

/**********************************************************************************************************************
 * @brief  Whether mtu is exchanging.
 * @output
 * @return None
 *********************************************************************************************************************/
static bool is_mtu_exchanging(void)
{
    if (gu16ConnHandle == 0)
        return false;
    att_connection_t *pAttState = rom_att_connection_for_handle(gu16ConnHandle);
    if (pAttState->mtu_exchange_state != MTU_IS_EXCHANGING)
        return false;
    return true;
}

/**********************************************************************************************************************
 * @brief  OTA update ble connection parameters.
 * @param  u32TimeoutMs: Waiting for mtu exchange.
 * @output
 * @return None
 *********************************************************************************************************************/
static void ota_update_connect_param(uint32_t u32TimeoutMs)
{
//    uint16_t gu16OldMtu = rom_gap_api_get_mtu(gu16ConnHandle);
//    uint32_t u32Timeout = 0;
//    
//    if (gu16OldMtu != BLE_OTA_MTU)
//        rom_gatt_client_api_mtu_exchange(gu16ConnHandle,BLE_OTA_MTU);

//    while(is_mtu_exchanging())
//    {
//        if (u32Timeout++ > u32TimeoutMs)
//        {
//            PRINTF("MTU Exchange Timeout\n");
//            break;
//        }
//        rom_delay_ms(1);
//    }
//    
    stGapConnectionUpdate_t stConnectionUpdateParam =
    {
        .u16ConnIntervalMax1250us = MSEC_TO_UNITS(BLE_OTA_MAXCONNINTERVAL,UNIT_1_25_MS),
        .u16ConnIntervalMin1250us = MSEC_TO_UNITS(BLE_OTA_MINCONNINTERVAL,UNIT_1_25_MS),
        .u16ConnLatency = 0,
        .u16SupervisionTimeout10ms = MSEC_TO_UNITS(BLE_OTA_SUPERTIMOUT,UNIT_10_MS),
    };
    
    rom_gap_api_connection_parameters_update(gu16ConnHandle, &stConnectionUpdateParam);
}


/**********************************************************************************************************************
 * @brief  OTA get firmware information package parse and respond.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
static EN_ERR_STA_T ota_get_firmware_info(void)
{
    uint8_t pu8RspBuf[OTA_RSP_GET_FIRMWARE_INFO_DATA_LEN + OTA_PACKAGE_MIN_LEN] = {0};
    uint8_t pu8DevAddr[6] = {0};
    uint16_t u16RspDataLen = 0,u16Crc; 
    
    pu8RspBuf[u16RspDataLen++] = EN_OTA_CHIP_TO_APP_CMD;
    pu8RspBuf[u16RspDataLen++] = EN_OTA_EVT_GET_FIRMWARE_INFO;
    pu8RspBuf[u16RspDataLen++] = LO_UINT16(OTA_RSP_GET_FIRMWARE_INFO_DATA_LEN);
    pu8RspBuf[u16RspDataLen++] = HI_UINT16(OTA_RSP_GET_FIRMWARE_INFO_DATA_LEN);
    pu8RspBuf[u16RspDataLen++] = HT32F675x5;
    pu8RspBuf[u16RspDataLen++] = ROM_VERSION;
    pu8RspBuf[u16RspDataLen++] = BOOT2_VERSION;
    pu8RspBuf[u16RspDataLen++] = LO_UINT16(APP_VERSION);
    pu8RspBuf[u16RspDataLen++] = HI_UINT16(APP_VERSION);
    pu8RspBuf[u16RspDataLen++] = EN_OTA_SKIP_HANDSHAKE;

    rom_gap_api_get_public_device_address(pu8DevAddr);
    for (uint8_t i = 0; i < sizeof(pu8DevAddr); i++)
        pu8RspBuf[u16RspDataLen++] = pu8DevAddr[i];
    
    u16Crc = rom_get_crc16_ccitt(pu8RspBuf,u16RspDataLen,CRC16_DEFAULT);
    pu8RspBuf[u16RspDataLen++] = LO_UINT16(u16Crc);
    pu8RspBuf[u16RspDataLen++] = HI_UINT16(u16Crc);

    return ota_send_notify(gu16ConnHandle,pu8RspBuf,u16RspDataLen);
}

/**********************************************************************************************************************
 * @brief  OTA parse handshake data package and respond package.
 * @param  pu8Data: handshake package
 * @param  u16DataLen: the length of handshake package.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
static EN_ERR_STA_T ota_rsp_handshake(const uint8_t *pu8Data,uint16_t u16DataLen)
{
    uint8_t pu8RspBuf[1 + OTA_PACKAGE_MIN_LEN] = {0};
    uint16_t u16RspDataLen = 0,u16Crc; 
    
    pu8RspBuf[u16RspDataLen++] = EN_OTA_CHIP_TO_APP_CMD;
    pu8RspBuf[u16RspDataLen++] = EN_OTA_EVT_HANDSHAKE;
    pu8RspBuf[u16RspDataLen++] = LO_UINT16(1);
    pu8RspBuf[u16RspDataLen++] = HI_UINT16(1);
    pu8RspBuf[u16RspDataLen++] = 0x00;

    u16Crc = rom_get_crc16_ccitt(pu8RspBuf,u16RspDataLen,CRC16_DEFAULT);
    pu8RspBuf[u16RspDataLen++] = LO_UINT16(u16Crc);
    pu8RspBuf[u16RspDataLen++] = HI_UINT16(u16Crc);

    return ota_send_notify(gu16ConnHandle,pu8RspBuf,u16RspDataLen);
}

/**********************************************************************************************************************
 * @brief  OTA parse upgrade request package and respond package.
 * @param  pu8Data: Upgrade request package
 * @param  u16DataLen: The length of upgrade request package.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
static EN_ERR_STA_T ota_rsp_upgrade_request(const uint8_t *pu8Data,uint16_t u16DataLen)
{
    uint8_t pu8RspData[OTA_RSP_FIRMWARE_UPGRADE_REQUEST_DATA_LEN+OTA_PACKAGE_MIN_LEN] = {0};
    uint16_t u16RspDataLen = 0;
    uint16_t u16Crc = 0,u16RecvDataSize = 0;
    
//    PRINTF("OTA Upgrade Request\n");
    ota_params_init();
    gu32BinSize = BUILD_UINT32(pu8Data[OTA_FM_REQ_DATA_BIN_SIZE_IDX],
                               pu8Data[OTA_FM_REQ_DATA_BIN_SIZE_IDX+1],
                               pu8Data[OTA_FM_REQ_DATA_BIN_SIZE_IDX+2],
                               pu8Data[OTA_FM_REQ_DATA_BIN_SIZE_IDX+3]);
    
    gu32BinCrc = BUILD_UINT32(pu8Data[OTA_FM_REQ_DATA_BIN_CRC_IND],
                              pu8Data[OTA_FM_REQ_DATA_BIN_CRC_IND+1],
                              pu8Data[OTA_FM_REQ_DATA_BIN_CRC_IND+2],
                              pu8Data[OTA_FM_REQ_DATA_BIN_CRC_IND+3]);
    
    pu8RspData[u16RspDataLen++] = EN_OTA_CHIP_TO_APP_CMD;
    pu8RspData[u16RspDataLen++] = EN_OTA_EVT_UPGRADE_REQUEST;
    pu8RspData[u16RspDataLen++] = LO_UINT16(OTA_RSP_FIRMWARE_UPGRADE_REQUEST_DATA_LEN);
    pu8RspData[u16RspDataLen++] = HI_UINT16(OTA_RSP_FIRMWARE_UPGRADE_REQUEST_DATA_LEN);
    pu8RspData[u16RspDataLen++] = EN_OTA_FIRMWARE_UPGRADE;

    u16RecvDataSize = rom_gap_api_get_mtu(gu16ConnHandle);

    if (OTA_PACKAGE_MAX_LEN < u16RecvDataSize)
        u16RecvDataSize = OTA_PACKAGE_CODE_MAX_LEN;
    else
    {
        // OTA_PACKAGE_MIN_LEN(CmdType + CmdVal + DataLength + Crc16) + Opcode(1) + Handle(2)
        u16RecvDataSize -= (OTA_PACKAGE_MIN_LEN + 3);
    }
    
    pu8RspData[u16RspDataLen++] = LO_UINT16(u16RecvDataSize);
    pu8RspData[u16RspDataLen++] = HI_UINT16(u16RecvDataSize);
    pu8RspData[u16RspDataLen++] = LO_UINT16(OTA_CONTINUOUS_TRANS_MAX_LEN);
    pu8RspData[u16RspDataLen++] = HI_UINT16(OTA_CONTINUOUS_TRANS_MAX_LEN);
    u16Crc = rom_get_crc16_ccitt(pu8RspData, sizeof(pu8RspData) - sizeof(u16Crc), CRC16_DEFAULT);
    pu8RspData[u16RspDataLen++] = LO_UINT16(u16Crc);
    pu8RspData[u16RspDataLen++] = HI_UINT16(u16Crc);

    return ota_send_notify(gu16ConnHandle,pu8RspData,u16RspDataLen);
}

/**********************************************************************************************************************
 * @brief  OTA respond status of received code package.
 * @param  enStatus: Received code package status
 * @param  u32ErrorInfo: Error information.
 * @param  u32ErrorInfo: The length of error information package.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
static EN_ERR_STA_T ota_rsp_recv_code(EN_RSP_STATUS_T enStatus, uint32_t u32ErrorInfo, uint8_t u8datalen)
{
    uint8_t gpu8RspData[11] = {0};
    uint8_t u8RspDataLen = 0;
    uint16_t U16RespCrc = 0;

    gpu8RspData[u8RspDataLen++] = EN_OTA_CHIP_TO_APP_CMD;
    gpu8RspData[u8RspDataLen++] = EN_OTA_EVT_UPGRADE_CODE;
    gpu8RspData[u8RspDataLen++] = LO_UINT16(u8datalen);
    gpu8RspData[u8RspDataLen++] = HI_UINT16(u8datalen);
    gpu8RspData[u8RspDataLen++] = enStatus;

    if (enStatus == EN_OTA_RSP_SAVE_FLASH_ERROR)
    {
        gpu8RspData[u8RspDataLen++] = BREAK_UINT32(u32ErrorInfo, 0);
        gpu8RspData[u8RspDataLen++] = BREAK_UINT32(u32ErrorInfo, 1);
        gpu8RspData[u8RspDataLen++] = BREAK_UINT32(u32ErrorInfo, 2);
        gpu8RspData[u8RspDataLen++] = BREAK_UINT32(u32ErrorInfo, 3);
        U16RespCrc = rom_get_crc16_ccitt(gpu8RspData, sizeof(gpu8RspData) - sizeof(U16RespCrc), CRC16_DEFAULT);
        gpu8RspData[u8RspDataLen++] = LO_UINT16(U16RespCrc);
        gpu8RspData[u8RspDataLen++] = HI_UINT16(U16RespCrc);
        
        return ota_send_notify(gu16ConnHandle,gpu8RspData,u8RspDataLen);
    }
    else if (enStatus == EN_OTA_RSP_SAVE_FLASH_OK)
    {
        U16RespCrc = rom_get_crc16_ccitt(gpu8RspData, 5, CRC16_DEFAULT);
        gpu8RspData[u8RspDataLen++] = LO_UINT16(U16RespCrc);
        gpu8RspData[u8RspDataLen++] = HI_UINT16(U16RespCrc);
        return ota_send_notify(gu16ConnHandle,gpu8RspData,u8RspDataLen);
    }
    else if ((enStatus == EN_OTA_RSP_CRC_ERROR) || (enStatus == EN_OTA_RSP_PACKAGE_INDEX_ERROR))
    {
        gpu8RspData[u8RspDataLen++] = LO_UINT16((uint16_t)u32ErrorInfo);
        gpu8RspData[u8RspDataLen++] = HI_UINT16((uint16_t)u32ErrorInfo);
        U16RespCrc = rom_get_crc16_ccitt(gpu8RspData, 7, CRC16_DEFAULT);
        gpu8RspData[u8RspDataLen++] = LO_UINT16(U16RespCrc);
        gpu8RspData[u8RspDataLen++] = HI_UINT16(U16RespCrc);
        return ota_send_notify(gu16ConnHandle,gpu8RspData,u8RspDataLen);
    }
    
    return ERR_STA_ERROR;
}

/**********************************************************************************************************************
 * @brief  Respond OTA status package.
 * @param  enStatus: Upgrade code package
 * @param  u32ErrorInfo: Error information.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
static EN_ERR_STA_T ota_rsp_status(EN_RSP_STATUS_T enStatus, uint32_t u32ErrorInfo)
{
    uint8_t u8RspDataLen = 0;
    gu32ContinuousCodeSize = 0;

    switch (enStatus)
    {
    case EN_OTA_RSP_SAVE_FLASH_ERROR:
        u8RspDataLen = 5;
        break;
    case EN_OTA_RSP_SAVE_FLASH_OK:
        u8RspDataLen = 1;
        break;
    case EN_OTA_RSP_CRC_ERROR:
        u8RspDataLen = 3;
        break;
    case EN_OTA_RSP_PACKAGE_INDEX_ERROR:
        u8RspDataLen = 3;
        break;
    default:
        return ERR_STA_ERROR;
        break;
    }
    return ota_rsp_recv_code(enStatus, u32ErrorInfo, u8RspDataLen);
}

/**********************************************************************************************************************
 * @brief  Parse OTA received upgrade code package and reponse status package when reached maxlength of continuous transmit.
 * @param  pu8Data: Upgrade code package
 * @param  u16DataLen: The length of upgrade code package.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
static EN_ERR_STA_T ota_recv_upgrade_code(const uint8_t *pu8Data,uint16_t u16DataLen)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint16_t u16CodeLen = 0;
    uint16_t u16PkgLen = 0;
    uint16_t u16PkgCrc = 0;
    uint16_t u16CalCrc = 0;
    uint16_t u16PkgIdx = 0;
    uint8_t ret = 0;

    u16CodeLen = BUILD_UINT16(pu8Data[OTA_PACKAGE_DATA_LEN_INDEX], pu8Data[OTA_PACKAGE_DATA_LEN_INDEX+1]);
    u16PkgIdx = BUILD_UINT16(pu8Data[OTA_PACKAGE_DATA_INDEX], pu8Data[OTA_PACKAGE_DATA_INDEX+1]);
    
    if (u16CodeLen > OTA_PACKAGE_MAX_LEN)
    {
        PRINTF("[%s][%d] : Code Length Error : %d\n",__func__,__LINE__,u16CodeLen);
        return ERR_STA_ERROR;
    }
    
    if (u16PkgIdx != gu16PkgIdx)
    {
        ota_rsp_status(EN_OTA_RSP_PACKAGE_INDEX_ERROR,gu16PkgIdx);
        PRINTF("[%s][%d] : OTA Package Index Error\n",__func__,__LINE__);
        return ERR_STA_ERROR;
    }
    
//    PRINTF("Pkg Idx : %d\n",u16PkgIdx);
    
    u16PkgCrc = BUILD_UINT16(pu8Data[OTA_PACKAGE_CRC_INDEX(u16CodeLen)],pu8Data[OTA_PACKAGE_CRC_INDEX(u16CodeLen)+1]);
    u16CalCrc = rom_get_crc16_ccitt(pu8Data, u16CodeLen + 2 + 1 + 1, CRC16_DEFAULT);
    
    if (u16CalCrc != u16PkgCrc)
    {
        ota_rsp_status(EN_OTA_RSP_CRC_ERROR,gu16PkgIdx);
        PRINTF("[%s][%d] : OTA Package CRC Error\n",__func__,__LINE__);
        return ERR_STA_ERROR;
    }
    
    // Ignore Package Index
    u16CodeLen -= 2;
    
    enRet = flash_write(OTA_CODE_ADDR_OFFSET + gu32CmpltCodeSize,(uint8_t *)&pu8Data[OTA_PACKAGE_DATA_INDEX+2],u16CodeLen,false);
    if (enRet != ERR_STA_OK)
    {
        ota_rsp_status(EN_OTA_RSP_SAVE_FLASH_ERROR,enRet);
        PRINTF("[%s][%d] : OTA Flash Write Failed\n",__func__,__LINE__);
        return ERR_STA_ERROR;
    }
    
    gu16PkgIdx++;
    gu32ContinuousCodeSize += u16CodeLen;
    gu32CmpltCodeSize += u16CodeLen;
    
    if (gu32ContinuousCodeSize >= OTA_CONTINUOUS_TRANS_MAX_LEN)
        ota_rsp_status(EN_OTA_RSP_SAVE_FLASH_OK, 0);
    
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Get CRC32 value of upgrade code in flash.
 * @output
 * @return CRC32 value
 *********************************************************************************************************************/
static uint32_t ota_get_code_crc32()
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint32_t u32OldCrc = CRC32_DEFAULT,u32Crc = 0;
    uint32_t u32BinSize = gu32BinSize;
    uint8_t pu8ReadBuf[FLASH_PAGE_SIZE];
    
    for(int i=0;i<gu32BinSize/FLASH_PAGE_SIZE;i++)
    {
        enRet = flash_read(OTA_CODE_ADDR_OFFSET+i*FLASH_PAGE_SIZE,pu8ReadBuf,FLASH_PAGE_SIZE);
        if (ERR_STA_OK != enRet)
        {
            PRINTF("[%s][%d] : OTA Flash Read Code Failed\n",__func__,__LINE__);
            return 0;
        }
        
        u32Crc = rom_get_crc32(pu8ReadBuf,FLASH_PAGE_SIZE,u32OldCrc);
        u32OldCrc = u32Crc;
        u32BinSize -= FLASH_PAGE_SIZE;
    }
    
    if (0 == u32BinSize)
        return u32Crc;
    
    enRet = flash_read(OTA_CODE_ADDR_OFFSET + (gu32BinSize-u32BinSize),pu8ReadBuf,u32BinSize);
    if (ERR_STA_OK != enRet)
    {
        PRINTF("[%s][%d] : OTA Flash Read Code Failed\n",__func__,__LINE__);
        return 0;
    }
    
    return rom_get_crc32(pu8ReadBuf,u32BinSize,u32OldCrc);
}

/**********************************************************************************************************************
 * @brief  Parse received ota finished package and reponse status package.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
static EN_ERR_STA_T ota_rsp_upgrade_finish(void)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint8_t pu8RspData[OTA_PACKAGE_MIN_LEN + 9] = {0};
    uint16_t u16RspDataLen = 0;
    uint16_t u16Crc = 0;
    uint32_t u32Crc = 0;
    uint8_t *pData = NULL;
    uint8_t u8len = 0;
    
    enRet = flash_sync();
    if (ERR_STA_OK != enRet)
    {
        PRINTF("[%s][%d] : OTA Flash Sync Failed\n",__func__,__LINE__);
        ota_rsp_status(EN_OTA_RSP_SAVE_FLASH_ERROR,enRet);
        return ERR_STA_ERROR;
    }
    
    pu8RspData[u16RspDataLen++] = EN_OTA_CHIP_TO_APP_CMD;
    pu8RspData[u16RspDataLen++] = EN_OTA_EVT_UPGRADE_FINISH;
    u32Crc = ota_get_code_crc32();
    
    if (u32Crc != gu32BinCrc)
    {
        PRINTF("[%s][%d] : CRC ERROR Code CRC : 0x%08X FLASH CRC : 0x%08X\n",__func__,__LINE__,gu32BinCrc,u32Crc);
        pu8RspData[u16RspDataLen++] = LO_UINT16(9);
        pu8RspData[u16RspDataLen++] = HI_UINT16(9);
        pu8RspData[u16RspDataLen++] = EN_OTA_RSP_CRC_ERROR;
        pu8RspData[u16RspDataLen++] = BREAK_UINT32(gu32BinCrc,0);
        pu8RspData[u16RspDataLen++] = BREAK_UINT32(gu32BinCrc,1);
        pu8RspData[u16RspDataLen++] = BREAK_UINT32(gu32BinCrc,2);
        pu8RspData[u16RspDataLen++] = BREAK_UINT32(gu32BinCrc,3);
        pu8RspData[u16RspDataLen++] = BREAK_UINT32(u32Crc,0);
        pu8RspData[u16RspDataLen++] = BREAK_UINT32(u32Crc,1);
        pu8RspData[u16RspDataLen++] = BREAK_UINT32(u32Crc,2);
        pu8RspData[u16RspDataLen++] = BREAK_UINT32(u32Crc,3);
    }
    else
    {
        pu8RspData[u16RspDataLen++] = LO_UINT16(1);
        pu8RspData[u16RspDataLen++] = HI_UINT16(1);
        pu8RspData[u16RspDataLen++] = EN_OTA_RSP_SAVE_FLASH_OK;
    }
    
    u16Crc = rom_get_crc16_ccitt(pu8RspData,u16RspDataLen,CRC16_DEFAULT);
    pu8RspData[u16RspDataLen++] = LO_UINT16(u16Crc);
    pu8RspData[u16RspDataLen++] = HI_UINT16(u16Crc);
    
    enRet = ota_send_notify(gu16ConnHandle,pu8RspData,u16RspDataLen);
    if (ERR_STA_OK != enRet)
        return enRet;
    
    if (u32Crc != gu32BinCrc)
        return ERR_STA_OK;

    stFwUpgradeCodeInfo_t stFwUpgradeCodeInfo =
    {
        .u16HT32Flag = HT32_BLE_SOC_FLAG,
        .u8RomVer = ROM_VERSION,
        .u8Boot2Ver = BOOT2_VERSION,
        .u32NeedFwUpgradeFlag = 0x476A6778,
        .u32BinFlashAddrOffset = OTA_CODE_ADDR_OFFSET,
        .u32BinCodeSize = gu32BinSize,
        .u32BinCodeCrc = gu32BinCrc,
        .u32RunningCodeAddrOffset = FLASH_MP_APP_CODE_ADDR - FLASH_BASE_ADDR,
        .u32RunningCodeSize = FLASH_MP_APP_CODE_SIZE_MAX,
        .u32StructCrc = 0,
    };
    pData = (uint8_t *)&stFwUpgradeCodeInfo;
    u8len = sizeof(stFwUpgradeCodeInfo_t) - sizeof(stFwUpgradeCodeInfo.u32StructCrc);
    stFwUpgradeCodeInfo.u32StructCrc = rom_get_crc32(pData,u8len,CRC32_DEFAULT);

    enRet = flash_write(OTA_UPGRADE_INFO_ADDR_OFFSET,pData,sizeof(stFwUpgradeCodeInfo_t),true);
    if (ERR_STA_OK != enRet)
    {
        PRINTF("[%s][%d] : OTA Write Upgrade Info Failed\n",__func__,__LINE__);
        return ERR_STA_ERROR;
    }
    
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Parse OTA received restart package and reponse status package.
 * @param  bRestartRightNow: Whether restart right now
 * @param  u32ResetDelayMs: After @ref u32ResetDelayMs ms restart.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T ota_rsp_restart(bool bRestartRightNow, uint32_t u32ResetDelayMs)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    uint8_t pu8RspData[9] = {0};
    uint16_t u16RspDataLen = 0;
    uint16_t u16Crc = 0;
    
    pu8RspData[u16RspDataLen++] = EN_OTA_CHIP_TO_APP_CMD;
    pu8RspData[u16RspDataLen++] = EN_OTA_EVT_CHIP_RESTART;
    pu8RspData[u16RspDataLen++] = LO_UINT16(OTA_RSP_CHIP_RESTART_DATA_LEN);
    pu8RspData[u16RspDataLen++] = HI_UINT16(OTA_RSP_CHIP_RESTART_DATA_LEN);
    
    if (bRestartRightNow)
        pu8RspData[u16RspDataLen++] = EN_OTA_RESTART;
    else
        pu8RspData[u16RspDataLen++] = EN_OTA_NOT_RESTART;

    pu8RspData[u16RspDataLen++] = LO_UINT16(u32ResetDelayMs);
    pu8RspData[u16RspDataLen++] = HI_UINT16(u32ResetDelayMs);
    u16Crc = rom_get_crc16_ccitt(pu8RspData,u16RspDataLen,CRC16_DEFAULT);
    pu8RspData[u16RspDataLen++] = LO_UINT16(u16Crc);
    pu8RspData[u16RspDataLen++] = HI_UINT16(u16Crc);

    enRet = ota_send_notify(gu16ConnHandle,pu8RspData,u16RspDataLen);
    if (ERR_STA_OK != enRet)
    {
        PRINTF("[%s][%d] : OTA Response Chip Restart Failed\n",__func__,__LINE__);
        return ERR_STA_ERROR;
    }
    
    if (bRestartRightNow)
    {
        PRINTF("---------------CHIP RESTART----------------\n");
        rom_delay_ms(u32ResetDelayMs);
        rom_hw_crg_system_reset();
    }
    return ERR_STA_OK;
}

/**********************************************************************************************************************
 * @brief  Parse and distribute package to data parsing flow by CmdValue.
 * @param  u16ConnHandle: Ble connection handle
 * @param  pu8Data: OTA package.
 * @param  u16DataLen: The length of OTA package.
 * @param  eventCb: OTA event callback.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T ota_protocol_parse(uint16_t u16ConnHandle,uint8_t *pu8Data,uint16_t u16DataLen,ota_event_callback_t eventCb)
{
    EN_ERR_STA_T enRet = ERR_STA_OK;
    
    if (pu8Data[OTA_PACKAGE_CMD_TYPE_INDEX] != EN_OTA_APP_TO_CHIP_CMD)
        return ERR_STA_ERROR;
    
    if (0 == u16ConnHandle)
        return ERR_STA_ERROR;
    
    gu16ConnHandle = u16ConnHandle;
    
    switch(pu8Data[OTA_PACKAGE_CMD_VALUE_INDEX])
    {
        case EN_OTA_EVT_GET_FIRMWARE_INFO:
        {
            ota_update_connect_param(500);
            enRet = ota_get_firmware_info();
            if (ERR_STA_OK != enRet)
            {
                PRINTF("[%s][%d] : OTA Get Firmware Info failed\n",__func__,__LINE__);
                return enRet;
            }
            break;
        }
        case EN_OTA_EVT_HANDSHAKE:
        {
            ota_rsp_handshake(pu8Data,u16DataLen);
            break;
        }
        case EN_OTA_EVT_UPGRADE_REQUEST:
        {
            enRet = ota_rsp_upgrade_request(pu8Data,u16DataLen);
            if (ERR_STA_OK != enRet)
            {
                PRINTF("[%s][%d] : OTA Response Upgrade Request failed\n",__func__,__LINE__);
                return enRet;
            }
            break;
        }
        case EN_OTA_EVT_UPGRADE_CODE:
        {
            enRet = ota_recv_upgrade_code(pu8Data,u16DataLen);
            if (ERR_STA_OK != enRet)
            {
                PRINTF("[%s][%d] : OTA Receive Upgrade Code failed\n",__func__,__LINE__);
                return enRet;
            }
            break;
        }
        case EN_OTA_EVT_UPGRADE_FINISH:
        {
            enRet = ota_rsp_upgrade_finish();
            if (ERR_STA_OK != enRet)
            {
                PRINTF("[%s][%d] : OTA Response Upgrade Finish failed\n",__func__,__LINE__);
                return enRet;
            }
            break;
        }
        case EN_OTA_EVT_CHIP_RESTART:
        {
            break;
        }
        default:
            return ERR_STA_ERROR;
    }
    
    if (eventCb)
        eventCb(pu8Data[OTA_PACKAGE_CMD_VALUE_INDEX]);
    
    return ERR_STA_OK;
}

