/*************************************************************************************************************
 * @file    hci_dtm.c
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

#include "RegHT32F675x5.h"
#include "llc_llp_interface.h"
#include "llc_dtm.h"

#include "hci_struct.h"
#include "hci_cmd.h"
#include "hci_event.h"
#include "hci_dtm.h"

#include "err_def.h"
#include "app_cfg.h"
#include "utility.h"

#include "hw_rf.h"
#include "hal_rf.h"

#define DTM_RF_PHY_T2_TIME_US  (60)
#define DTM_TRX_ON_TIME_US     (90)
#define DTM_TRX_OFF_TIME_US    (16)
/**
 * @brief  typedef
 */
typedef enum
{
    DTM_LE_1M_PHY       = 0x01,
    DTM_LE_2M_PHY       = 0x02,
    DTM_LE_CODED_PHY    = 0x03,
    DTM_LE_CODED_PHY_S8 = 0x03,
    DTM_LE_CODED_PHY_S2 = 0x04,

} enDTMCmdPhy_t;

/**
 * @brief  Local variables
 */
static bool m_u8SingleToneMode = false;

static void dtm_timing_config( void )
{
    reg_ltc_ret_pd_burst_on_time_btxen_brxen = ( (( (DTM_TRX_ON_TIME_US+DTM_RF_PHY_T2_TIME_US) * 16) << 16 ) | (DTM_TRX_ON_TIME_US*16) );
    reg_ltrx_ret_pd_burst_off_time_btxen_brxen = ((DTM_TRX_OFF_TIME_US*16)<<12) | (DTM_TRX_OFF_TIME_US*16);
    
    reg_llc_ret_pd_tx_rx_stop_before_intvl_hi = 0;
    reg_llc_ret_pd_tx_rx_stop_before_intvl_lo = (((DTM_TRX_ON_TIME_US+DTM_RF_PHY_T2_TIME_US) + 10)*16);
//    reg_llc_ret_pd_tx_rx_stop_before_intvl_lo = ((DTM_TRX_ON_TIME_US + 10)*16);

    rom_hw_rf_trx_timing_config ( T1_OV_60US, DTM_RF_PHY_T2_TIME_US, T3_TIME_4US, 0, 5, 4 );
}

/**
 * @brief  Hci dtm phy transform
 * @param  u8Phy: dtm command phy, @ref enDTMCmdPhy_t.
 */
static uint8_t hci_dtm_phy_transform(uint8_t u8Phy)
{
    uint8_t u8LlcPhy;

    switch (u8Phy)
    {
        case DTM_LE_1M_PHY:
        {
            u8LlcPhy = LL_PHY_1M;
            break;
        }
        case DTM_LE_2M_PHY:
        {
            u8LlcPhy = LL_PHY_2M;
            break;
        }
        case DTM_LE_CODED_PHY_S8: // or DTM_LE_CODED_PHY
        {
            u8LlcPhy = LL_PHY_CODED_S8;
            break;
        }
        case DTM_LE_CODED_PHY_S2:
        {
            u8LlcPhy = LL_PHY_CODED_S2;
            break;
        }
        default:
        {
            u8LlcPhy = LL_PHY_1M;
            break;
        }
    }

    return u8LlcPhy;
}

/**
 * @brief  Hci dtm cmd handler
 * @param  u16Opcode: op code.
 * @param  pu8Buf: payload data buffer
 * @param  u16Len: payload data buffer length
 * @param  pstEvent: event struct point
 */
void hci_dtm_cmd_handler(uint16_t u16Opcode, uint8_t *pu8Buf, uint16_t u16Len, stEvent_t *pstEvent)
{
    uint8_t freq;
    uint8_t dataSize;
    uint8_t dataType;
    uint8_t phyMode;

    // Event parameters
    pstEvent->u8Len                           = 0x04;
    pstEvent->u8SubCode                       = 1;
    pstEvent->u8EvtCode                       = CMD_CMPLT_EVT_CODE;
    pstEvent->unPar.stCmpltEvt.u8OpcodeLo     = LO_UINT16(u16Opcode);
    pstEvent->unPar.stCmpltEvt.u8OpcodeHi     = HI_UINT16(u16Opcode);
    pstEvent->unPar.stCmpltEvt.unPar.u8Status = ERR_STA_OK;

    switch (u16Opcode)
    {
        case HCI_RESET:
        {
            PRINTF("[HCI_RESET]\n");
            break;
        }
        case HCI_LE_RECEIVER_TEST:
        {
            stDtmRxParam_t stParam =
            {
                .enumPhy = LL_PHY_1M,
                .u8Channel = pu8Buf[0]
            };

            rom_llc_dtm_rx_start(&stParam);

            PRINTF("[HCI_LE_RX]Ch: %d.\n", pu8Buf[0]);
            break;
        }
        case HCI_LE_TRANSMITTER_TEST:
        {
            stDtmTxParam_t stParam = {
                .enumPhy        = LL_PHY_1M,
                .u8Channel      = pu8Buf[0],
                .u8PacketSize   = pu8Buf[1],
                .enumPacketType = pu8Buf[2],
            };

            rom_llc_dtm_tx_start(&stParam); 
            dtm_timing_config();

            PRINTF("[HCI_LE_TX]Ch: %d, Size: %d, Type: %d.\n", pu8Buf[0], pu8Buf[1], pu8Buf[2]);
            break;
        }
        case HCI_LE_TEST_END:
        {
            uint32_t u32RxPktsNumCrcOk  = 0;
            uint32_t u32RxPktsNumCrcErr = 0;

            if (true == m_u8SingleToneMode)
            {
                rom_hal_rf_single_tone_stop();
                rom_hw_rf_clear_lo();
            }

            rom_llc_dtm_trx_stop();
            rom_llc_dtm_get_rx_count(true, &u32RxPktsNumCrcOk, &u32RxPktsNumCrcErr);

            // Event parameters, return Number of packets received
            pstEvent->u8Len                                            = 0x06;
            pstEvent->u8SubCode                                        = 2;
            pstEvent->unPar.stCmpltEvt.unPar.stLeTestEnd.u8Status      = ERR_STA_OK;
            pstEvent->unPar.stCmpltEvt.unPar.stLeTestEnd.u8NumPktsRxLo = LO_UINT16(u32RxPktsNumCrcOk);
            pstEvent->unPar.stCmpltEvt.unPar.stLeTestEnd.u8NumPktsRxHi = HI_UINT16(u32RxPktsNumCrcOk);

            PRINTF("[HCI_LE_END]CRC OK Pkts: %d, CRC Err Pkts: %d.\n", u32RxPktsNumCrcOk, u32RxPktsNumCrcErr);
            break;
        }
        case HCI_LE_ENHANCED_RECEIVER_TEST:
        {
            stDtmRxParam_t stParam =
            {
                .enumPhy = hci_dtm_phy_transform(pu8Buf[1]),
                .u8Channel = pu8Buf[0]
            };

            rom_llc_dtm_rx_start(&stParam);

            PRINTF("[HCI_LE_ENH_RX]Ch: %d, Phy: %d.\n", pu8Buf[0], pu8Buf[1]);
            break;
        }
        case HCI_LE_ENHANCED_TRANSMITTER_TEST:
        {
            stDtmTxParam_t stParam = {
                .enumPhy        = hci_dtm_phy_transform(pu8Buf[3]),
                .u8Channel      = pu8Buf[0],
                .u8PacketSize   = pu8Buf[1],
                .enumPacketType = pu8Buf[2],
            };

            rom_llc_dtm_tx_start(&stParam);
            dtm_timing_config();

            PRINTF("[HCI_LE_ENH_TX]Ch: %d, Size: %d, Type: %d, Phy: %d.\n", pu8Buf[0], pu8Buf[1], pu8Buf[2], pu8Buf[3]);
            break;
        }
        case HCI_LE_SINGLE_TONE_TEST:
        {
            rom_hal_rf_single_tone_start(pu8Buf[0], rom_hal_rf_get_tx_gain());
            m_u8SingleToneMode = true;

            PRINTF("[HCI_LE_SINGLE_TONE_TEST]Ch: %d\n", pu8Buf[0]);
            break;
        }

        default: break;
    }
}
