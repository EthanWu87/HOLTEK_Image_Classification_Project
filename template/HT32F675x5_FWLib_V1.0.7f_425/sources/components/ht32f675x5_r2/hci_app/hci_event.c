/*************************************************************************************************************
 * @file    hci_event.c
 * @version V1.0
 * @date    2023-07-11
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

#include "cmsis_os2.h"
#include "rtx_lib.h"

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "app_cfg.h"

#include "hci_struct.h"
#include "hci_event.h"

/**
 * @brief  Extern variables
 */
extern osThreadId_t hciAppEventTaskId;

/**
 * @brief  Hci app event packet
 * @param  pstEventBuf: Data point which hci event buffer
 * @param  pstEvent: Data point which hci event
 */
void hci_event_generate(stHciBuf_t *pstEventBuf, stEvent_t *pstEvent)
{
    uint8_t *pu8Evt = NULL;
    uint8_t *pu8Buf = NULL;
    uint16_t u16Tx;
    uint16_t u16Rx;
    uint16_t u16Len;
    uint16_t u16UnuseBufLen;

    u16Tx  = pstEventBuf->u16Tx;
    u16Rx  = pstEventBuf->u16Rx;
    pu8Buf = pstEventBuf->pu8Buf;

    if (u16Tx <= u16Rx)
    {
        u16UnuseBufLen = u16Tx + HCI_EVENT_BUF_SIZE - u16Rx;
    }
    else
    {
        u16UnuseBufLen = u16Tx - u16Rx;
    }

    u16Len = 3 + pstEvent->u8Len;

    // PRINTF("Event: %d,%d,%d,%d\n",u16Tx,u16Rx,u16Len,u16UnuseBufLen);
    if (u16Len <= u16UnuseBufLen)
    {
        if (u16Rx + u16Len <= HCI_EVENT_BUF_SIZE)
        {
            memcpy(&pu8Buf[u16Rx], (uint8_t *)pstEvent, u16Len);
        }
        else
        {
            pu8Evt = (uint8_t *)pstEvent;
            memcpy(&pu8Buf[u16Rx], pu8Evt, HCI_EVENT_BUF_SIZE - u16Rx);
            memcpy(&pu8Buf[0], &pu8Evt[HCI_EVENT_BUF_SIZE - u16Rx], u16Len + u16Rx - HCI_EVENT_BUF_SIZE);
        }
        pstEventBuf->u16Rx = ((u16Rx + u16Len) & (HCI_EVENT_BUF_SIZE - 1));

        osThreadFlagsSet(hciAppEventTaskId, 0x01U);
    }
    else
    {
        PRINTF("Event fifo not enough.\n");
        // need return ???
    }
}

#if 0
uint16 g_rssi_from_reg = 0x4309;

//special event
void hci_le_adv_report_event ( uint8* pdata )
{
    le_adv_report_evt le_adv_report;
    uint16 evt_length;
    uint8 pdu_type;
    uint8 pdu_len;

    pdu_type = pdata[0];
    le_adv_report.subEvtCode = HT32_ADV_RPT_RESLT_CODE;
    le_adv_report.numReports = 0x01;      // our chip support 1 report
    le_adv_report.addr_type = pdata[1];
    pdu_len = pdata[2];
    memcpy ( le_adv_report.addr6Oct, pdata + 3, 6 ) ;

    if ( ( 1 != pdu_type ) && ( pdu_len > 6 ) )
    {
        le_adv_report.length_data =  pdu_len - 6;      // -6 : !AdvA is not in the len!
        memcpy ( ( uint8* ) le_adv_report.data31Oct, pdata+11, le_adv_report.length_data );
    }
    else
    {
        le_adv_report.length_data = 0;
    }

//    le_adv_report.rssi_S8 = ht32_calc_dbm_from_read_rssi ( rssi_from_reg );

    * ( ( uint8* ) le_adv_report.data31Oct + le_adv_report.length_data ) = le_adv_report.rssi_S8; //the le_adv_report_evt is bigger than actual report evet, so copy rssi to the last byte so le_adv_report can be report directly
    evt_length =  12 + le_adv_report.length_data;
    le_adv_report.evtType = pdu_type;

    if ( 6 ==   le_adv_report.evtType )
    {
        le_adv_report.evtType = GAP_ADTYPE_ADV_SCAN_IND;
    }
    else if ( 2 ==   le_adv_report.evtType )
    {
        le_adv_report.evtType = GAP_ADTYPE_ADV_NONCONN_IND;
    }
    //consider how to send message or signal to stack task, , stack master role not support temporary by stack_transfer@wenjie
    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, evt_length, (uint8 *)&le_adv_report,0,0);
}

void hci_le_connection_complete_event( uint8 idx, uint8 status, uint8 *pdata)
{
    le_cnnct_cmplt_evt le_cnnct_cmplt;
    uint8 evt_length;
    
    le_cnnct_cmplt.subEvtCode = HT32_CNNCT_CMPLT_CODE;
    le_cnnct_cmplt.status = status;
    if(0x3C != status)
    {
        le_cnnct_cmplt.cnnctH16bitlo = idx;
        le_cnnct_cmplt.cnnctH16bithi = 0;
        
        le_cnnct_cmplt.role = 1;
        le_cnnct_cmplt.peerAddrType = pdata[0];
        memcpy( le_cnnct_cmplt.peerAddr6Oct, &pdata[1], 6);
        
        le_cnnct_cmplt.cnnctInterval16bitlo = pdata[7];
        le_cnnct_cmplt.cnnctInterval16bithi = pdata[8];

        le_cnnct_cmplt.cnnctLatency16bitlo = pdata[9];
        le_cnnct_cmplt.cnnctLatency16bithi = pdata[10];

        le_cnnct_cmplt.supervisionTimeout16bitlo = pdata[11];
        le_cnnct_cmplt.supervisionTimeout16bithi = pdata[12];
    }
    else
    {
        le_cnnct_cmplt.cnnctInterval16bitlo = 0;
        le_cnnct_cmplt.cnnctInterval16bithi = 0;
        le_cnnct_cmplt.role = 1;
        le_cnnct_cmplt.cnnctInterval16bitlo = 0;
        le_cnnct_cmplt.cnnctInterval16bithi = 0;
        le_cnnct_cmplt.cnnctLatency16bitlo = 0;
        le_cnnct_cmplt.cnnctLatency16bithi = 0;
        le_cnnct_cmplt.supervisionTimeout16bitlo = 0;
        le_cnnct_cmplt.supervisionTimeout16bithi = 0;
        le_cnnct_cmplt.masterClockAccuracy = 0;
    }
    evt_length = 19;
    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, evt_length, (uint8 *)&le_cnnct_cmplt,0,0);
}


void hci_disconnect_complete_event(uint8 idx, uint8 disconn_reason )
{
    discnnt_cmplt_evt discnnt_cmplt;
    uint8 evt_length;

    discnnt_cmplt.subEvtCode = HT32_DISCNNCT_CMPLT_CODE;
    discnnt_cmplt.status = 0;
    discnnt_cmplt.cnnctHandlelo8 = idx;
    discnnt_cmplt.cnnctHandlehi8 = 0;
    discnnt_cmplt.reason = disconn_reason;
    evt_length = 5;
    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, evt_length, (uint8 *)&discnnt_cmplt,0,0);
}


void hci_encryption_chg_event(uint8 idx, uint8 status, uint8  Encryption_Enabled)
{

    enc_chg_evt enc_chg;
    uint8 evt_length;
    enc_chg.subEvtCode = HT32_ENCRYPTION_STATUS_CHG_CODE;
    enc_chg.status = status;
    enc_chg.cnnctHlo8 = idx;
    enc_chg.cnnctHhi8 = 0;
    enc_chg.Encryption_Enabled = Encryption_Enabled;
    evt_length = 5;
    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, evt_length, (uint8 *)&enc_chg,0,0);
}


void hci_le_cnnct_update_complete_event(uint8 idx, uint8 *p_status)
{
    le_connection_update_cmplt_evt le_connection_update_cmplt;
    uint8 evt_length;
    le_connection_update_cmplt.subEvtCode = HT32_CNNCT_UPDATE_CODE;
    le_connection_update_cmplt.status = p_status[0];
    le_connection_update_cmplt.cnnctH16bitlo = idx;
    le_connection_update_cmplt.cnnctH16bithi = 0;

    le_connection_update_cmplt.cnnctInterval16bitlo = p_status[1];
    le_connection_update_cmplt.cnnctInterval16bithi = p_status[2];

    le_connection_update_cmplt.cnnctLatency16bitlo = p_status[3];
    le_connection_update_cmplt.cnnctLatency16bithi = p_status[4];

    le_connection_update_cmplt.supervisionTimeout16bitlo = p_status[5];
    le_connection_update_cmplt.supervisionTimeout16bithi = p_status[6];

    evt_length = 10;
    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, evt_length, (uint8 *)&le_connection_update_cmplt,0,0);
}

void hci_le_mtu_rpt_event(uint8 idx, uint8 status, uint8 *pdata)
{
    uint8 data[6];

    data[0] = HT32_MTU_RPT_CODE;
    data[1] = status;
    data[2] = idx;
    data[3] = 0;
    data[4] = pdata[0];
    data[5] = pdata[1];

    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, 6, data,0,0);
}

void hci_num_of_complete_pkt_event ( uint8 idx )
{
    num_of_cmplt_pkt_evt num_of_cmplt_pkt;
    uint8 evt_length;

    num_of_cmplt_pkt.subEvtCode = HT32_NUM_OF_CMPLT_PKTS_CODE;

    num_of_cmplt_pkt.Number_of_Handles = 1;
    num_of_cmplt_pkt.Connection_Handlelo8 = idx;
    num_of_cmplt_pkt.Connection_Handlehi8 = 0;
    num_of_cmplt_pkt.HC_Num_Of_Completed_Packetslo8 = 1;
    num_of_cmplt_pkt.HC_Num_Of_Completed_Packetshi8 = 0;
    evt_length = 6;
    
    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, evt_length, (uint8 *)&num_of_cmplt_pkt,0,0);
}

void hci_data_rpt_event(uint8 idx, uint8 * value,  uint8 length)
{
    uint8 data_rpt[4];
    
    data_rpt[0] = HT32_DATA_RPT_CODE;
    data_rpt[1] = idx;
    data_rpt[2] = 0;

    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, length, value,3,data_rpt);
}

void hci_le_save_bond_device_sucess_event(void)
{
    // Command Status Event
    uint8 cmd_status_evt[9] = { 
        HT32_CMD_STATUS_CODE,    // SubCode, 
        0x00,   // Status,
        0x01,   // Num of Packet
        0xC6,   // Command OP Code L8bit
        0xFC,   // Command OP Code H8bit
        0x00,   // RFU
        0x00,   // RFU
        0x00,   // RFU
        0x00    // RFU
    };
    
    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, 9, cmd_status_evt,0,0);
}
void hci_le_bond_device_rpt_event(uint8 *info)
{
    uint8 le_bond_device_rpt[2];

    le_bond_device_rpt[0] = HT32_BOND_DEVICE_RPT;

    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, 50, info,1,le_bond_device_rpt);
}

void hci_ready_to_work_event(void)
{
    uint8 data[4] = { 
        HT32_READY_TO_WORK, // SubCode
        0x00,   // RFU
        0x00,   // RFU 
        0x00    // RFU
    };
    
    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, 4, data,0,0);
}

void hci_peri_timer_notify_event(void *param)
{
    uint8 data[4] = { 
        HT32_PERI_TIMER_NOTIFY,  // SubCode
        0x00,   // RFU
        0x00,   // RFU
        0x00    // RFU
    };

    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, 4, data,0,0);
}

void hci_unknow_command_event(uint16 cmd_len)
{
    uint8 data[4] = { 
        HT32_UNKNOW_PACKET, // SubCode
        0x00,   // RFU
        0x00,   // Command Length, L8bit
        0x00    // Command Length, H8bit
    };

    data[2] = cmd_len & 0xFF;
    data[3] = (cmd_len >> 8) & 0xFF;
    
    hci_event_generate(HT32_SPECIFIED_EVENT_CODE, 4, data,0,0); 
}
#endif /* #if 0 */
