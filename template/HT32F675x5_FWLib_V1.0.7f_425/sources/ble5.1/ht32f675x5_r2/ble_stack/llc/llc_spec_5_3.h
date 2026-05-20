/*************************************************************************************************************
 * @file    llc_spec_5_3.h
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
#ifndef LLC_SPEC_5_3_H
#define LLC_SPEC_5_3_H


typedef enum
{
    LLC_SPEC_5_3_FEATURE_SET_LE_ENCRYPTION                                  = (1ULL << 0),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTION_PARAMETERS_REQUEST_PROCEDURE        = (1ULL << 1),
    LLC_SPEC_5_3_FEATURE_SET_EXTENDED_REJECT_INDICATION                     = (1ULL << 2),
    LLC_SPEC_5_3_FEATURE_SET_SLAVE_INITIATED_FEATURES_EXCHANGE              = (1ULL << 3),
    LLC_SPEC_5_3_FEATURE_SET_LE_PING                                        = (1ULL << 4),
    LLC_SPEC_5_3_FEATURE_SET_LE_DATA_PACKET_LENGTH_EXTENSION                = (1ULL << 5),
    LLC_SPEC_5_3_FEATURE_SET_LL_PRIVACY                                     = (1ULL << 6),
    LLC_SPEC_5_3_FEATURE_SET_EXTENDED_SCANNER_FILTER_POLICIES               = (1ULL << 7),
    LLC_SPEC_5_3_FEATURE_SET_LE_2M_PHY                                      = (1ULL << 8),
    LLC_SPEC_5_3_FEATURE_SET_STABLE_MODULATION_INDEX_TRANSMITTER            = (1ULL << 9),
    LLC_SPEC_5_3_FEATURE_SET_STABLE_MODULATION_INDEX_RECEIVER               = (1ULL << 10),
    LLC_SPEC_5_3_FEATURE_SET_LE_CODED_PHY                                   = (1ULL << 11),
    LLC_SPEC_5_3_FEATURE_SET_LE_EXTENDED_ADVERTISING                        = (1ULL << 12),
    LLC_SPEC_5_3_FEATURE_SET_LE_PERIODIC_ADVERTISING                        = (1ULL << 13),
    LLC_SPEC_5_3_FEATURE_SET_CHANNEL_SELECTION_ALGORITHM_NO2                = (1ULL << 14),
    LLC_SPEC_5_3_FEATURE_SET_LE_POWER_CLASS_1                               = (1ULL << 15),
    LLC_SPEC_5_3_FEATURE_SET_MINIMUM_NUMBER_OF_USED_CHANNELS_PROCEDURE      = (1ULL << 16),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTION_CTE_REQUEST                         = (1ULL << 17),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTION_CTE_RESPONSE                        = (1ULL << 18),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTIONLESS_CTE_TRANSMITTER                 = (1ULL << 19),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTIONLESS_CTE_RECEIVER                    = (1ULL << 20),
    LLC_SPEC_5_3_FEATURE_SET_AOD                                            = (1ULL << 21),
    LLC_SPEC_5_3_FEATURE_SET_AOA                                            = (1ULL << 22),
    LLC_SPEC_5_3_FEATURE_SET_RECEIVING_CONSTANT_TONE_EXTENSIONS             = (1ULL << 23),
    LLC_SPEC_5_3_FEATURE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_SENDER      = (1ULL << 24),
    LLC_SPEC_5_3_FEATURE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECIPIENT   = (1ULL << 25),
    LLC_SPEC_5_3_FEATURE_SET_SLEEP_CLOCK_ACCURACY_UPDATES                   = (1ULL << 26),
    LLC_SPEC_5_3_FEATURE_SET_REMOTE_PUBLIC_KEY_VALIDATION                   = (1ULL << 27),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTED_ISOCHRONOUS_STREAM_CENTRAL           = (1ULL << 28),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTED_ISOCHRONOUS_STREAM_PERIPHERAL        = (1ULL << 29),
    LLC_SPEC_5_3_FEATURE_SET_ISOCHRONOUS_BROADCASTER                        = (1ULL << 30),
    LLC_SPEC_5_3_FEATURE_SET_SYNCHRONIZED_RECEIVER                          = (1ULL << 31),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTED_ISOCHRONOUS_STREAM_HOST_SUPPORT      = (1ULL << 32),
    LLC_SPEC_5_3_FEATURE_SET_LE_POWER_CONTROL_REQUEST                       = (1ULL << 33),
    LLC_SPEC_5_3_FEATURE_SET_LE_POWER_CONTROL_REQUEST_2                     = (1ULL << 34),
    LLC_SPEC_5_3_FEATURE_SET_LE_PATH_LOSS_MONITORING                        = (1ULL << 35),
    LLC_SPEC_5_3_FEATURE_SET_PERIODIC_ADVERTISING_ADI_SUPPORT               = (1ULL << 36),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTION_SUBRATING                           = (1ULL << 37),
    LLC_SPEC_5_3_FEATURE_SET_CONNECTION_SUBRATING_HOST_SUPPORT              = (1ULL << 38),
    LLC_SPEC_5_3_FEATURE_SET_CHANNEL_CLASSIFICATION                         = (1ULL << 39),
}
EN_LLC_SPEC_5_3_FEATURE_SET_T;


#define LLC_SPEC_5_3_FEATURE_SET_SEND_TO_PEER_BITMASK       (~( \
                                                                  LLC_SPEC_5_3_FEATURE_SET_LE_PING \
                                                                | LLC_SPEC_5_3_FEATURE_SET_LL_PRIVACY \
                                                                | LLC_SPEC_5_3_FEATURE_SET_EXTENDED_SCANNER_FILTER_POLICIES \
                                                                | LLC_SPEC_5_3_FEATURE_SET_LE_EXTENDED_ADVERTISING \
                                                                | LLC_SPEC_5_3_FEATURE_SET_LE_PERIODIC_ADVERTISING \
                                                                | LLC_SPEC_5_3_FEATURE_SET_CONNECTIONLESS_CTE_TRANSMITTER \
                                                                | LLC_SPEC_5_3_FEATURE_SET_CONNECTIONLESS_CTE_RECEIVER \
                                                                | LLC_SPEC_5_3_FEATURE_SET_AOD \
                                                                | LLC_SPEC_5_3_FEATURE_SET_AOA \
                                                                | LLC_SPEC_5_3_FEATURE_SET_REMOTE_PUBLIC_KEY_VALIDATION \
                                                                | LLC_SPEC_5_3_FEATURE_SET_PERIODIC_ADVERTISING_ADI_SUPPORT \
                                                            ))

#define LLC_SPEC_5_3_FEATURE_SET_HOST_CONTROLLED_BITMASK    (~( \
                                                                  LLC_SPEC_5_3_FEATURE_SET_CONNECTED_ISOCHRONOUS_STREAM_HOST_SUPPORT \
                                                                | LLC_SPEC_5_3_FEATURE_SET_CONNECTION_SUBRATING_HOST_SUPPORT \
                                                             ))



#endif
