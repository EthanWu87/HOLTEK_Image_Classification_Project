/*************************************************************************************************************
 * @file    ble_event.c
 * @version V1.0
 * @date    2022-11-01
 * @brief   ble_peripheral ble event
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

#include "RegHT32F675x5.h"
#include "err_def.h"

#include "llc_llp_interface.h"
#include "hci.h"
#include "gap_def.h"
#include "gap_api.h"

#include "ble_cb_event_def.h"
#include "ble_callback.h"

#include "app_cfg.h"
#include "utility.h"
#include "mlog.h"

/**
 * @brief  LOCAL VARIABLES
 */
static uint16_t m_u16ConnHandle = 0;

/**
 * @brief  handle all ble slave message.
 * @param  None.
 */
static void ble_event_handler(uint32_t u32Cmd, const void *pData, uint32_t u32Len)
{
    uint8_t *pu8Buf = (uint8_t *)pData;

    // MLOGD ( 0xa002, "ble_event_proc u32Cmd = 0x%X", u32Cmd );
    // PRINTF ( "ble_event_proc u32Cmd = 0x%X\n", u32Cmd );

    switch (u32Cmd)
    {
        case MSG_BLE_CONNECTED_IND:
        {
            stHciEventParamVendorConnectionComplete_t *pstEvent = (stHciEventParamVendorConnectionComplete_t *)pu8Buf;

            MLOGD(0xa003, "MSG_BLE_CONNECTED_IND = 0x%X", pstEvent->Connection_Handle);
            PRINTF("[MSG_BLE_CONNECTED_IND]Handle = 0x%04X\n", pstEvent->Connection_Handle);

            m_u16ConnHandle = pstEvent->Connection_Handle;
            break;
        }
        case MSG_BLE_DISCONNECTED_IND:
        {
            stHciEventParamDisconnectionComplete_t *pstEvt = (stHciEventParamDisconnectionComplete_t *)pu8Buf;

            MLOG88D(0xa005, "MSG_BLE_DISCONNECTED_IND Handle = 0x%X, reason = 0x%X", pstEvt->Connection_Handle,
                    pstEvt->Reason);
            PRINTF("[MSG_BLE_DISCONNECTED_IND] Handle = 0x%X, reason = 0x%X\n", pstEvt->Connection_Handle,
                   pstEvt->Reason);

            m_u16ConnHandle = 0;

            rom_gap_api_set_advertising_enable(0, true);
            break;
        }
        case MSG_BLE_ENCRYPTED_CHANGED_IND:
        {
            stHciEventParamEncryptionChange_t *pstEvt = (stHciEventParamEncryptionChange_t *)pu8Buf;

            MLOG88D(0xa007, "MSG_BLE_ENCRYPTED_CHANGED_IND Handle = 0x%X, Encryption_Enabled = 0x%X",
                    pstEvt->Connection_Handle, pstEvt->Encryption_Enabled);
            PRINTF("[MSG_BLE_ENCRYPTED_CHANGED_IND] Handle = 0x%X, Encryption_Enabled = 0x%X\n",
                   pstEvt->Connection_Handle, pstEvt->Encryption_Enabled);
            break;
        }
        case MSG_BLE_ENCRYPTED_REFRESH_IND:
        {
            stHciEventParamEncryptionKeyRefreshComplete_t *pstEvt =
                (stHciEventParamEncryptionKeyRefreshComplete_t *)pu8Buf;

            MLOGD(0xa008, "MSG_BLE_ENCRYPTED_REFRESH_IND Handle = 0x%X", pstEvt->Connection_Handle);
            PRINTF("[MSG_BLE_ENCRYPTED_REFRESH_IND] Handle = 0x%X\n", pstEvt->Connection_Handle);
            break;
        }
        case MSG_BLE_LL_VERSION_IND:
        {
            stHciEventParamReadRemoteVersionInformationComplete_t *pstEvt =
                (stHciEventParamReadRemoteVersionInformationComplete_t *)pu8Buf;

            stGapSetPhy_t stPhy;
            stPhy.u8PreferTxPhys = GAP_PREFER_PHY_2M;
            stPhy.u8PreferRxPhys = GAP_PREFER_PHY_2M;
            // rom_gap_api_connection_set_phy(pstEvt->Connection_Handle, &stPhy);

            MLOG1688D(0xa009, "MSG_BLE_LL_VERSION_IND Manufacturer_Name = 0x%X, Handle = 0x%X, Version = 0x%X",
                      pstEvt->Manufacturer_Name, pstEvt->Connection_Handle, pstEvt->Version);
            PRINTF("[MSG_BLE_LL_VERSION_IND] Manufacturer_Name = 0x%X, Handle = 0x%X, Version = 0x%X\n",
                   pstEvt->Manufacturer_Name, pstEvt->Connection_Handle, pstEvt->Version);
            break;
        }
        case MSG_BLE_LL_FEATRUE_IND:
        {
            stHciEventParamLEReadRemoteFeaturesComplete_t *pstEvt =
                (stHciEventParamLEReadRemoteFeaturesComplete_t *)pu8Buf;

            MLOGD(0xa00a, "MSG_BLE_LL_FEATRUE_IND Handle = 0x%X", pstEvt->LE_Features);
            MLOGXD(0xa00b, "MSG_BLE_LL_FEATRUE_IND LE_Features", (uint8_t *)&pstEvt->LE_Features, 8);
            PRINTF("[MSG_BLE_LL_FEATRUE_IND] Handle = 0x%LX\n", pstEvt->LE_Features);
            break;
        }
        case MSG_BLE_CONNECTION_UPDATE_COMPLETE_IND:
        {
            stHciEventParamLEConnectionUpdateComplete_t *pstEvt = (stHciEventParamLEConnectionUpdateComplete_t *)pu8Buf;

            MLOG161616D(0xa00c,
                        "MSG_BLE_CONNECTION_UPDATE_COMPLETE_IND Conn_Interval = 0x%X, Conn_Latency = 0x%X, "
                        "Supervision_Timeou = 0x%X",
                        pstEvt->Conn_Interval, pstEvt->Conn_Latency, pstEvt->Supervision_Timeout);
            PRINTF(
                "[MSG_BLE_CONNECTION_UPDATE_COMPLETE_IND] Conn_Interval = 0x%X, Conn_Latency = 0x%X, "
                "Supervision_Timeou = 0x%X\n",
                pstEvt->Conn_Interval, pstEvt->Conn_Latency, pstEvt->Supervision_Timeout);
            break;
        }
        case MSG_BLE_DATA_LENGTH_UPDATE_COMPLETE_IND:
        {
            stHciEventParamLEDataLengthChange_t *pstEvt = (stHciEventParamLEDataLengthChange_t *)pu8Buf;

            MLOG161616D(0xa00d,
                        "MSG_BLE_DATA_LENGTH_UPDATE_COMPLETE_IND Handle = 0x%X, MaxTxOctets = 0x%X, MaxRxOctets = 0x%X",
                        pstEvt->Connection_Handle, pstEvt->MaxTxOctets, pstEvt->MaxRxOctets);
            break;
        }
        case MSG_BLE_PHY_UPDATE_COMPLETE_IND:
        {
            stHciEventParamLEPhyUpdateComplete_t *pstEvt = (stHciEventParamLEPhyUpdateComplete_t *)pu8Buf;

            MLOG1688D(0xa00e, "MSG_BLE_PHY_UPDATE_COMPLETE_IND Handle = 0x%X, TX_PHY = 0x%X, RX_PHY = 0x%X",
                      pstEvt->Connection_Handle, pstEvt->TX_PHY, pstEvt->RX_PHY);
            PRINTF("[MSG_BLE_PHY_UPDATE_COMPLETE_IND] Handle = 0x%X, TX_PHY = 0x%X, RX_PHY = 0x%X\n",
                   pstEvt->Connection_Handle, pstEvt->TX_PHY, pstEvt->RX_PHY);
            break;
        }
        case MSG_BLE_MTU_EXCHANGED_IND:
        {
            st_mtu_exchange_complete_event *pstEvt = (st_mtu_exchange_complete_event *)pu8Buf;

            MLOG1616D(0xa00f, "MSG_BLE_MTU_EXCHANGED_IND Handle = 0x%X, mtu = %d", pstEvt->conn_handle, pstEvt->mtu);
            PRINTF("[MSG_BLE_MTU_EXCHANGED_IND] Handle = 0x%X, mtu = %d\n", pstEvt->conn_handle, pstEvt->mtu);
            break;
        }
        case MSG_BLE_LLCAP_CONN_UPDATE_RSP_IND:
        {
            st_llcap_conn_update_rsp_event *pstEvt = (st_llcap_conn_update_rsp_event *)pu8Buf;
            break;
        }
        case MSG_BLE_PAIR_USER_PASSKEYREQ_IND:
        {
            uint16_t u16ConnectionHandle = *((uint16_t *)pu8Buf);
            MLOGD(0xa010, "MSG_BLE_PAIR_USER_PASSKEYREQ_IND Handle = 0x%X", u16ConnectionHandle);
            break;
        }
        case MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_IND:
        {
            st_passkey_display_event *pstEvt = (st_passkey_display_event *)pu8Buf;

            MLOG3216D(0xa011, "MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_IND passkey = %d, Handle = 0x%X",
                      rom_little_endian_read_32(pstEvt->passkey, 0), pstEvt->conn_handle);
            break;
        }
        case MSG_BLE_PAIR_USER_PASSKEYREQ_CONF_IND:
        {
            st_passkey_display_event *pstEvt = (st_passkey_display_event *)pu8Buf;

            MLOG3216D(0xa012, "MSG_BLE_PAIR_USER_PASSKEYREQ_CONF_IND passkey = %d, Handle = 0x%X",
                      rom_little_endian_read_32(pstEvt->passkey, 0), pstEvt->conn_handle);
            break;
        }
        case MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_CANCEL_IND:
        {
            uint16_t u16ConnectionHandle = *((uint16_t *)pu8Buf);

            MLOGD(0xa013, "MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_CANCEL_IND Handle = 0x%X", u16ConnectionHandle);
            break;
        }
        case MSG_BLE_PAIR_COMPLETED_IND:
        {
            st_pair_complete_event *pstPairEvt = (st_pair_complete_event *)pu8Buf;

            MLOGD(0xa014, "MSG_BLE_PAIR_COMPLETED_IND Handle = 0x%X  ", pstPairEvt->conn_handle);
            break;
        }
        case MSG_BLE_PAIR_FAIL_IND:
        {
            // Pair fail reason
            st_pair_failed_event *pstPairEvt = (st_pair_failed_event *)pu8Buf;

            MLOG88D(0xa015, "MSG_BLE_PAIR_FAIL_IND Handle = 0x%X, reason = 0x%X", pstPairEvt->conn_handle,
                    pstPairEvt->reason);
            break;
        }
        case MSG_LTK_REQ_WHEN_RECONECT_AFTER_PAIR_IND:
        {
            st_ltk_req_event *pstEvt = (st_ltk_req_event *)pu8Buf;

            MLOG1616D(0xa016, "MSG_LTK_REQ_WHEN_RECONECT_AFTER_PAIR_IND Handle = 0x%X, ediv = 0x%X",
                      pstEvt->conn_handle, pstEvt->ediv);
            break;
        }
        case MSG_BLE_READ_RSSI_COMMAND_RESULT:
        {
            stHciReturnParametersHCIReadRSSI_t *pstReturnParam = (stHciReturnParametersHCIReadRSSI_t *)pData;
            MLOG88D(0xa021, "MSG_BLE_READ_RSSI_COMMAND_RESULT - Status:0x%02x RSSI:-%udBm", pstReturnParam->Status,
                    (~(pstReturnParam->RSSI)) + 1);
            break;
        }
        case MSG_BLE_DISCONNECT_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_SET_RANDOM_ADDRESS_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_SET_ADVERTISING_PARAMETERS_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa022, "MSG_BLE_SET_ADVERTISING_PARAMETERS_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_SET_ADVERTISING_DATA_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];

            MLOGD(0xa023, "MSG_BLE_SET_ADVERTISING_DATA_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_SET_SCAN_RESPONSE_DATA_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];

            MLOGD(0xa024, "MSG_BLE_SET_SCAN_RESPONSE_DATA_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_SET_ADVERTISING_ENABLE_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa025, "MSG_BLE_SET_ADVERTISING_ENABLE_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_SET_SCAN_PARAMETERS_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa026, "MSG_BLE_SET_SCAN_PARAMETERS_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_SET_SCAN_ENABLE_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa027, "MSG_BLE_SET_SCAN_ENABLE_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_CLEAR_WHITE_LIST_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa028, "MSG_BLE_CLEAR_WHITE_LIST_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_ADD_DEVICE_TO_WHITE_LIST_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa029, "MSG_BLE_ADD_DEVICE_TO_WHITE_LIST_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_REMOVE_DEVICE_FROM_WHITE_LIST_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa02a, "MSG_BLE_REMOVE_DEVICE_FROM_WHITE_LIST_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_CREATE_CONNECTION_CANCEL_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_CONNECTION_UPDATE_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa02b, "MSG_BLE_CONNECTION_UPDATE_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_LONG_TERM_KEY_REQUEST_REPLY_COMMAND_RESULT:
        {
            stHciReturnParametersLELongTermKeyRequestReply_t *pstResult =
                (stHciReturnParametersLELongTermKeyRequestReply_t *)pu8Buf;
            break;
        }
        case MSG_BLE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_COMMAND_RESULT:
        {
            stHciReturnParametersLELongTermKeyRequestNegativeReply_t *pstResult =
                (stHciReturnParametersLELongTermKeyRequestNegativeReply_t *)pu8Buf;
            break;
        }
        case MSG_BLE_SET_DATA_LENGTH_COMMAND_RESULT:
        {
            stHciReturnParametersLESetDataLength_t *pstResult = (stHciReturnParametersLESetDataLength_t *)pu8Buf;
            break;
        }
        case MSG_BLE_SET_PHY_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_READ_REMOTE_FEATURES_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_ADD_DEVICE_TO_RESOLVING_LIST_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_REMOVE_DEVICE_FROM_RESOLVING_LIST_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_CLEAR_RESOLVING_LIST_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_SET_ADDRESS_RESOLUTION_ENABLE_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_SET_PRIVACY_MODE_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_READ_CHANNEL_MAP_COMMAND_RESULT:
        {
            stHciReturnParametersLEReadChannelMap_t *pstResult = (stHciReturnParametersLEReadChannelMap_t *)pu8Buf;
            break;
        }
        case MSG_BLE_SET_ADVERTISING_SET_RANDOM_ADDRESS_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa02c, "MSG_BLE_SET_ADVERTISING_SET_RANDOM_ADDRESS_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_REMOVE_ADVERTISING_SET_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_CLEAR_ADVERTISING_SETS_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        case MSG_BLE_SET_PUBLIC_ADDRESS_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa033, "MSG_BLE_SET_PUBLIC_ADDRESS_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_CREATE_CONNECTION_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa034, "MSG_BLE_CREATE_CONNECTION_COMMAND_RESULT - Status:0x%02x", u8Status);
            break;
        }
        case MSG_BLE_UPDATE_CHANNEL_MAP_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            break;
        }
        default:
            break;
    }
}

/**
 * @brief  ble event init.
 */
void ble_event_init(void)
{
    ble_callback_set_host_stack_send_event_callback(ble_event_handler);
}
