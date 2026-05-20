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

#include "llc_spec_5_1.h"
#include "hci.h"
#include "gap_api.h"
#include "gatt_client_api.h"

#include "ble_cb_event_def.h"
#include "ble_callback.h"

#include "app_cfg.h"
#include "utility.h"
#include "mlog.h"

#define AVOID_NOT_USED_WARNING(v) ((void)v)

/**
 * @brief  LOCAL VARIABLES
 */
static uint8_t m_u8BlePeerMac[6] = BLE_SCAN_PEER_MAC;
static uint8_t u8scanReportBuf[256];

/**
 * @brief  BLE event advertising report.
 * @param  pu8Buf: Pointer to the save peer device advertising data.
 * @note   LE Advertising Report event package formart:
 *         - Subevent_Code,
 *         - Report Num, 1Byte
 *           - ADV Event Type, 1Byte
 *           - ADV Address Type, 1Byte
 *           - ADV Address, 6Bytes
 *           - ADV Data Length, 1Byte
 *           - ADV Data, n Bytes
 *           - RSSI, 1Byte
 * @param  u32BufSize: Advertising data length.
 */
static void ble_event_adv_report(uint8_t *pu8Buf, uint32_t u32BufSize)
{
    uint32_t i;
    uint8_t  u8ReportsNum              = 0;
    uint8_t  u8ParametersCurrentLength = 2;
    uint8_t  u8NextReportOffset        = 2;
    uint16_t u16ReportSize;
    uint8_t  u8AdvDataLen;

    // 1. Check adv report buffer and buffer length.
    if ((NULL == pu8Buf) || (u32BufSize < 2))
    {
        PRINTF("u32BufSize[<2] is Error!\n");
        return;
    }

    // 2. Check adv report number.
    u8ReportsNum = pu8Buf[1];
    if (0 == u8ReportsNum)
    {
        PRINTF("u8ReportsNum[=0] is Error\n");
        return;
    }

    // 3. Check adv report.
    for (i = 0; i < u8ReportsNum; i++)
    {
        // EventType(1) + AddressType(1) + Address(6) + AdvDataLength(1) + Data(variable) + RSSI(1)
        u8AdvDataLen  = pu8Buf[u8NextReportOffset + 8];
        u16ReportSize = 1 + 1 + 6 + 1 + u8AdvDataLen + 1;

        u8ParametersCurrentLength += u16ReportSize;
        u8NextReportOffset += u16ReportSize;
    }

    if (u8ParametersCurrentLength != u32BufSize)
    {
        // Invalid adv report
        PRINTF("[u8ParametersCurrentLength != u32BufSize] is Error\n");
        return;
    }

    // 4. Parse and report adv.
    for (u8NextReportOffset = 2; u8NextReportOffset < u32BufSize; u8NextReportOffset += u16ReportSize)
    {
        u8AdvDataLen  = pu8Buf[u8NextReportOffset + 8];
        u16ReportSize = 1 + 1 + 6 + 1 + u8AdvDataLen + 1;

        // 4.1 Adv event type.
        EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_EVENT_TYPE_T enAdvEventType = pu8Buf[u8NextReportOffset];

        // 4.2 Adv address Type.
        EN_LLC_SPEC_5_1_HCI_ADVERTISING_REPORT_ADDRESS_TYPE_T enAdvAddrType = pu8Buf[u8NextReportOffset + 1];

        // 4.3 Adv address
        uint8_t *pu8Address = &pu8Buf[u8NextReportOffset + 2];

        // 4.4 Adv data
        uint8_t *pu8Data = &pu8Buf[u8NextReportOffset + 9];

        // 4.5 RSSI
        int8_t s8Rssi = (int8_t)(pu8Buf[u8NextReportOffset + 9 + u8AdvDataLen]);

        // 4.6 Check adv address.
        // if (0 == memcmp(pu8Address, m_u8BlePeerMac, sizeof(m_u8BlePeerMac)))
        {
            u8scanReportBuf[0] = enAdvEventType;
            u8scanReportBuf[1] = enAdvAddrType;
            memcpy(&u8scanReportBuf[2], pu8Address, 6);
            u8scanReportBuf[8] = s8Rssi;
            u8scanReportBuf[9] = u8AdvDataLen;
            memcpy(&u8scanReportBuf[10], pu8Data, u8AdvDataLen);

            PRINTF("\nScan Report Event: \n");
            PRINTF("EventType: %02X\n", enAdvEventType);
            PRINTF("AddrType:  %02X\n", enAdvAddrType);
            PRINTF("Address:   %02X: %02X: %02X: %02X: %02X: %02X\n", u8scanReportBuf[2], u8scanReportBuf[3],
                   u8scanReportBuf[4], u8scanReportBuf[5], u8scanReportBuf[6], u8scanReportBuf[7]);
            PRINTF("RSSI:      %d\n", s8Rssi);
            PRINTF("DataLen:   %d\n", u8AdvDataLen);

            // 4.7 Disable scan.
            // rom_gap_api_set_scan_enable(false, false);

            // 4.8 Creat connect.
            stGapCreateConnection_t stConnParam = {
                .u16ConnIntervalMin1250us  = BLE_CONNECT_INTERVAL,
                .u16ConnIntervalMax1250us  = BLE_CONNECT_INTERVAL,
                .u16SupervisionTimeout10ms = BLE_CONNECT_TIMEOUT,
                .u16ConnLatency            = 0,
                .u16ScanInterval625us      = BLE_SCAN_INTERVAL,
                .u16ScanWindow625us        = BLE_SCAN_WINDOW,
                .enumOwnAddressType        = GAP_OWN_ADDRESS_TYPE_PUBLIC,
                .enumPeerAddressType       = GAP_INITIATOR_PEER_ADDRESS_TYPE_PUBLIC,
                .enumInitiatorFilterPolicy = GAP_INITIATOR_FILTER_POLICY_WHITELIST_IS_NOT_USED,
                .u8ScanChannelMap          = BLE_SCAN_CHANNEL,
            };
            memcpy(stConnParam.pu8PeerAddress, m_u8BlePeerMac, sizeof(m_u8BlePeerMac));

            // rom_gap_api_create_connection(&stConnParam);
        }
    }
}

/**
 * @brief  handle all ble slave message.
 * @param  None.
 */
static void ble_event_handler(uint32_t u32Cmd, const void *pData, uint32_t u32Len)
{
    uint8_t *pu8Buf = (uint8_t *)pData;

    switch (u32Cmd)
    {
        case MSG_BLE_ADV_REPORT_IND:
        {
            ble_event_adv_report(pu8Buf, u32Len);
            break;
        }
        case MSG_BLE_CONNECTED_IND:
        {
            stHciEventParamVendorConnectionComplete_t *pstEvent = (stHciEventParamVendorConnectionComplete_t *)pu8Buf;

            // Start to discover primary services.
            rom_gatt_client_api_discover_primary_services(pstEvent->Connection_Handle);

            PRINTF("[CONNECTED]Handle = %d\n", pstEvent->Connection_Handle);
            break;
        }
        case MSG_BLE_DISCONNECTED_IND:
        {
            stHciEventParamDisconnectionComplete_t *pstEvent = (stHciEventParamDisconnectionComplete_t *)pu8Buf;

            MLOG88D(0xa005, "MSG_BLE_DISCONNECTED_IND Handle = %d, reason = 0x%X", pstEvent->Connection_Handle,
                    pstEvent->Reason);
            PRINTF("[DISCONNECTED]Handle = %d, reason = 0x%X\n", pstEvent->Connection_Handle, pstEvent->Reason);

            // Enable scan.
            rom_gap_api_set_scan_enable(true, false);
            break;
        }
        case MSG_BLE_ENCRYPTED_CHANGED_IND:
        {
            stHciEventParamEncryptionChange_t *pstEvent = (stHciEventParamEncryptionChange_t *)pu8Buf;

            MLOG88D(0xa007, "MSG_BLE_ENCRYPTED_CHANGED_IND Handle = %d, Encryption_Enabled = 0x%X",
                    pstEvent->Connection_Handle, pstEvent->Encryption_Enabled);
            PRINTF("[ENCRYPTED_CHANGED]Handle = %d, Encryption_Enabled = 0x%X\n", pstEvent->Connection_Handle,
                   pstEvent->Encryption_Enabled);
            break;
        }
        case MSG_BLE_ENCRYPTED_REFRESH_IND:
        {
            stHciEventParamEncryptionKeyRefreshComplete_t *pstEvent =
                (stHciEventParamEncryptionKeyRefreshComplete_t *)pu8Buf;

            MLOGD(0xa008, "MSG_BLE_ENCRYPTED_REFRESH_IND Handle = %d", pstEvent->Connection_Handle);
            PRINTF("[ENCRYPTED_REFRESH]Handle = %d\n", pstEvent->Connection_Handle);
            break;
        }
        case MSG_BLE_LL_VERSION_IND:
        {
            stHciEventParamReadRemoteVersionInformationComplete_t *pstEvent =
                (stHciEventParamReadRemoteVersionInformationComplete_t *)pu8Buf;

            MLOG1688D(0xa009, "MSG_BLE_LL_VERSION_IND Manufacturer_Name = 0x%X, Handle = %d, Version = 0x%X",
                      pstEvent->Manufacturer_Name, pstEvent->Connection_Handle, pstEvent->Version);
            PRINTF("[LL_VERSION]Name = 0x%X, Handle = %d, Version = 0x%X\n", pstEvent->Manufacturer_Name,
                   pstEvent->Connection_Handle, pstEvent->Version);
            break;
        }
        case MSG_BLE_LL_FEATRUE_IND:
        {
            stHciEventParamLEReadRemoteFeaturesComplete_t *pstEvent =
                (stHciEventParamLEReadRemoteFeaturesComplete_t *)pu8Buf;

            MLOGD(0xa00a, "MSG_BLE_LL_FEATRUE_IND Handle = %d", pstEvent->LE_Features);
            MLOGXD(0xa00b, "MSG_BLE_LL_FEATRUE_IND LE_Features", (uint8_t *)&pstEvent->LE_Features, 8);
            PRINTF("[MSG_BLE_LL_FEATRUE_IND]LE_Features = %llu\n", pstEvent->LE_Features);
            break;
        }
        case MSG_BLE_CONNECTION_UPDATE_COMPLETE_IND:
        {
            stHciEventParamLEConnectionUpdateComplete_t *pstEvent =
                (stHciEventParamLEConnectionUpdateComplete_t *)pu8Buf;

            MLOG161616D(0xa00c,
                        "MSG_BLE_CONNECTION_UPDATE_COMPLETE_IND Conn_Interval = 0x%X, Conn_Latency = 0x%X, "
                        "Supervision_Timeou = 0x%X",
                        pstEvent->Conn_Interval, pstEvent->Conn_Latency, pstEvent->Supervision_Timeout);
            PRINTF(
                "[MSG_BLE_CONNECTION_UPDATE_COMPLETE_IND] Conn_Interval = 0x%X, Conn_Latency = 0x%X, "
                "Supervision_Timeou = 0x%X\n",
                pstEvent->Conn_Interval, pstEvent->Conn_Latency, pstEvent->Supervision_Timeout);
            break;
        }
        case MSG_BLE_DATA_LENGTH_UPDATE_COMPLETE_IND:
        {
            stHciEventParamLEDataLengthChange_t *pstEvent = (stHciEventParamLEDataLengthChange_t *)pu8Buf;

            MLOG161616D(0xa00d,
                        "MSG_BLE_DATA_LENGTH_UPDATE_COMPLETE_IND Handle = %d, MaxTxOctets = 0x%X, MaxRxOctets = 0x%X",
                        pstEvent->Connection_Handle, pstEvent->MaxTxOctets, pstEvent->MaxRxOctets);
            break;
        }
        case MSG_BLE_PHY_UPDATE_COMPLETE_IND:
        {
            stHciEventParamLEPhyUpdateComplete_t *pstEvent = (stHciEventParamLEPhyUpdateComplete_t *)pu8Buf;

            MLOG1688D(0xa00e, "MSG_BLE_PHY_UPDATE_COMPLETE_IND Handle = %d, TX_PHY = 0x%X, RX_PHY = 0x%X",
                      pstEvent->Connection_Handle, pstEvent->TX_PHY, pstEvent->RX_PHY);
            PRINTF("[MSG_BLE_PHY_UPDATE_COMPLETE_IND] Handle = %d, TX_PHY = 0x%X, RX_PHY = 0x%X\n",
                   pstEvent->Connection_Handle, pstEvent->TX_PHY, pstEvent->RX_PHY);
            break;
        }
        case MSG_BLE_MTU_EXCHANGED_IND:
        {
            st_mtu_exchange_complete_event *pstEvent = (st_mtu_exchange_complete_event *)pu8Buf;

            MLOG1616D(0xa00f, "MSG_BLE_MTU_EXCHANGED_IND Handle = %d, mtu = %d", pstEvent->conn_handle, pstEvent->mtu);
            PRINTF("[MTU_EXCHANGED]Handle = %d, mtu = %d\n", pstEvent->conn_handle, pstEvent->mtu);
            break;
        }
        case MSG_BLE_LLCAP_CONN_UPDATE_RSP_IND:
        {
            st_llcap_conn_update_rsp_event *pstEvent = (st_llcap_conn_update_rsp_event *)pu8Buf;
            AVOID_NOT_USED_WARNING(pstEvent);
            break;
        }
        case MSG_BLE_PAIR_USER_PASSKEYREQ_IND:
        {
            uint16_t u16ConnectionHandle = *((uint16_t *)pu8Buf);
            MLOGD(0xa010, "MSG_BLE_PAIR_USER_PASSKEYREQ_IND Handle = %d", u16ConnectionHandle);
            break;
        }
        case MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_IND:
        {
            st_passkey_display_event *pstEvent = (st_passkey_display_event *)pu8Buf;

            MLOG3216D(0xa011, "MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_IND passkey = %d, Handle = %d",
                      rom_little_endian_read_32(pstEvent->passkey, 0), pstEvent->conn_handle);
            break;
        }
        case MSG_BLE_PAIR_USER_PASSKEYREQ_CONF_IND:
        {
            st_passkey_display_event *pstEvent = (st_passkey_display_event *)pu8Buf;

            MLOG3216D(0xa012, "MSG_BLE_PAIR_USER_PASSKEYREQ_CONF_IND passkey = %d, Handle = %d",
                      rom_little_endian_read_32(pstEvent->passkey, 0), pstEvent->conn_handle);
            break;
        }
        case MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_CANCEL_IND:
        {
            uint16_t u16ConnectionHandle = *((uint16_t *)pu8Buf);

            MLOGD(0xa013, "MSG_BLE_PAIR_USER_PASSKEY_DISPLAY_CANCEL_IND Handle = %d", u16ConnectionHandle);
            break;
        }
        case MSG_BLE_PAIR_COMPLETED_IND:
        {
            st_pair_complete_event *pstPairEvt = (st_pair_complete_event *)pu8Buf;

            MLOGD(0xa014, "MSG_BLE_PAIR_COMPLETED_IND Handle = %d  ", pstPairEvt->conn_handle);
            break;
        }
        case MSG_BLE_PAIR_FAIL_IND:
        {
            // Pair fail reason
            st_pair_failed_event *pstPairEvt = (st_pair_failed_event *)pu8Buf;

            MLOG88D(0xa015, "MSG_BLE_PAIR_FAIL_IND Handle = %d, reason = 0x%X", pstPairEvt->conn_handle,
                    pstPairEvt->reason);
            break;
        }
        case MSG_LTK_REQ_WHEN_RECONECT_AFTER_PAIR_IND:
        {
            st_ltk_req_event *pstEvent = (st_ltk_req_event *)pu8Buf;

            MLOG1616D(0xa016, "MSG_LTK_REQ_WHEN_RECONECT_AFTER_PAIR_IND Handle = %d, ediv = 0x%X",
                      pstEvent->conn_handle, pstEvent->ediv);
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
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_SET_RANDOM_ADDRESS_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_SET_SCAN_PARAMETERS_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa026, "MSG_BLE_SET_SCAN_PARAMETERS_COMMAND_RESULT - Status:0x%02x", u8Status);
            PRINTF("[SET_SCAN_PARAMETERS]Status: 0x%02X\n", u8Status);
            break;
        }
        case MSG_BLE_SET_SCAN_ENABLE_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            MLOGD(0xa027, "MSG_BLE_SET_SCAN_ENABLE_COMMAND_RESULT - Status:0x%02x", u8Status);
            PRINTF("[SET_SCAN_ENABLE][%d]Status: 0x%02X\n", u32Len, u8Status);
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
            AVOID_NOT_USED_WARNING(u8Status);
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
            AVOID_NOT_USED_WARNING(pstResult);
            break;
        }
        case MSG_BLE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY_COMMAND_RESULT:
        {
            stHciReturnParametersLELongTermKeyRequestNegativeReply_t *pstResult =
                (stHciReturnParametersLELongTermKeyRequestNegativeReply_t *)pu8Buf;
            AVOID_NOT_USED_WARNING(pstResult);
            break;
        }
        case MSG_BLE_SET_DATA_LENGTH_COMMAND_RESULT:
        {
            stHciReturnParametersLESetDataLength_t *pstResult = (stHciReturnParametersLESetDataLength_t *)pu8Buf;
            AVOID_NOT_USED_WARNING(pstResult);
            break;
        }
        case MSG_BLE_SET_PHY_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_READ_REMOTE_FEATURES_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_ADD_DEVICE_TO_RESOLVING_LIST_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_REMOVE_DEVICE_FROM_RESOLVING_LIST_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_CLEAR_RESOLVING_LIST_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_SET_ADDRESS_RESOLUTION_ENABLE_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_SET_PRIVACY_MODE_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_READ_CHANNEL_MAP_COMMAND_RESULT:
        {
            stHciReturnParametersLEReadChannelMap_t *pstResult = (stHciReturnParametersLEReadChannelMap_t *)pu8Buf;
            AVOID_NOT_USED_WARNING(pstResult);
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
            AVOID_NOT_USED_WARNING(u8Status);
            break;
        }
        case MSG_BLE_CLEAR_ADVERTISING_SETS_COMMAND_RESULT:
        {
            uint8_t u8Status = pu8Buf[0];
            AVOID_NOT_USED_WARNING(u8Status);
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
            AVOID_NOT_USED_WARNING(u8Status);
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
