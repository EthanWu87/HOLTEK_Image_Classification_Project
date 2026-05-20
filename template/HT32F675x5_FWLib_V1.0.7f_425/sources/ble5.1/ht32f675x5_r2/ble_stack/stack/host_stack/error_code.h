/*************************************************************************************************************
 * @file    error_code.h
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
#ifndef __ERROR_CODE_H__
#define __ERROR_CODE_H__

#define ERROR_CODE_SUCCESS                                                                          0x00
#define ERROR_CODE_UNKNOWN_HCI_COMMAND                                                              0x01
#define ERROR_CODE_UNKNOWN_CONNECTION_IDENTIFIER                                                    0x02
#define ERROR_CODE_HARDWARE_FAILURE                                                                 0x03
#define ERROR_CODE_PAGE_TIMEOUT                                                                     0x04
#define ERROR_CODE_AUTHENTICATION_FAILURE                                                           0x05
#define ERROR_CODE_PIN_OR_KEY_MISSING                                                               0x06
#define ERROR_CODE_MEMORY_CAPACITY_EXCEEDED                                                         0x07
#define ERROR_CODE_CONNECTION_TIMEOUT                                                               0x08
#define ERROR_CODE_CONNECTION_LIMIT_EXCEEDED                                                        0x09
#define ERROR_CODE_SYNCHRONOUS_CONNECTION_LIMIT_TO_A_DEVICE_EXCEEDED                                0x0A
#define ERROR_CODE_CONNECTION_ALREADY_EXISTS                                                        0x0B
#define ERROR_CODE_COMMAND_DISALLOWED                                                               0x0C
#define ERROR_CODE_CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES                                     0x0D
#define ERROR_CODE_CONNECTION_REJECTED_DUE_TO_SECURITY_REASONS                                      0x0E
#define ERROR_CODE_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR                                  0x0F
#define ERROR_CODE_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED                                               0x10
#define ERROR_CODE_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE                                           0x11
#define ERROR_CODE_INVALID_HCI_COMMAND_PARAMETERS                                                   0x12
#define ERROR_CODE_REMOTE_USER_TERMINATED_CONNECTION                                                0x13
#define ERROR_CODE_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES                         0x14
#define ERROR_CODE_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_POWER_OFF                             0x15
#define ERROR_CODE_CONNECTION_TERMINATED_BY_LOCAL_HOST                                              0x16
#define ERROR_CODE_REPEATED_ATTEMPTS                                                                0x17
#define ERROR_CODE_PAIRING_NOT_ALLOWED                                                              0x18
#define ERROR_CODE_UNKNOWN_LMP_PDU                                                                  0x19
#define ERROR_CODE_UNSUPPORTED_REMOTE_FEATURE_OR_UNSUPPORTED_LMP_FEATURE                            0x1A
#define ERROR_CODE_SCO_OFFSET_REJECTED                                                              0x1B
#define ERROR_CODE_SCO_INTERVAL_REJECTED                                                            0x1C
#define ERROR_CODE_SCO_AIR_MODE_REJECTED                                                            0x1D
#define ERROR_CODE_INVALID_LMP_PARAMETERS_OR_INVALID_LL_PARAMETERS                                  0x1E
#define ERROR_CODE_UNSPECIFIED_ERROR                                                                0x1F
#define ERROR_CODE_UNSUPPORTED_LMP_PARAMETER_VALUE_OR_UNSUPPORTED_LL_PARAMETER_VALUE                0x20
#define ERROR_CODE_ROLE_CHANGE_NOT_ALLOWED                                                          0x21
#define ERROR_CODE_LMP_RESPONSE_TIMEOUT_OR_LL_RESPONSE_TIMEOUT                                      0x22
#define ERROR_CODE_LMP_ERROR_TRANSACTION_COLLISION_OR_LL_PROCEDURE_COLLISION                        0x23
#define ERROR_CODE_LMP_PDU_NOT_ALLOWED                                                              0x24
#define ERROR_CODE_ENCRYPTION_MODE_NOT_ACCEPTABLE                                                   0x25
#define ERROR_CODE_LINK_KEY_CANNOT_BE_CHANGED                                                       0x26
#define ERROR_CODE_REQUESTED_QOS_NOT_SUPPORTED                                                      0x27
#define ERROR_CODE_INSTANT_PASSED                                                                   0x28
#define ERROR_CODE_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED                                              0x29
#define ERROR_CODE_DIFFERENT_TRANSACTION_COLLISION                                                  0x2A
#define ERROR_CODE_RESERVED_FOR_FUTURE_USE                                                          0x2B
#define ERROR_CODE_QOS_UNACCEPTABLE_PARAMETER                                                       0x2C
#define ERROR_CODE_QOS_REJECTED                                                                     0x2D
#define ERROR_CODE_CHANNEL_CLASSIFICATION_NOT_SUPPORTED                                             0x2E
#define ERROR_CODE_INSUFFICIENT_SECURITY                                                            0x2F
#define ERROR_CODE_PARAMETER_OUT_OF_MANDATORY_RANGE                                                 0x30
//#define ERROR_CODE_RESERVED_FOR_FUTURE_USE                                                          0x31
#define ERROR_CODE_ROLE_SWITCH_PENDING                                                              0x32
//#define ERROR_CODE_RESERVED_FOR_FUTURE_USE                                                          0x33
#define ERROR_CODE_RESERVED_SLOT_VIOLATION                                                          0x34
#define ERROR_CODE_ROLE_SWITCH_FAILED                                                               0x35
#define ERROR_CODE_EXTENDED_INQUIRY_RESPONSE_TOO_LARGE                                              0x36
#define ERROR_CODE_SECURE_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST                                      0x37
#define ERROR_CODE_HOST_BUSY_PAIRING                                                                0x38
#define ERROR_CODE_CONNECTION_REJECTED_DUE_TO_NO_SUITABLE_CHANNEL_FOUND                             0x39
#define ERROR_CODE_CONTROLLER_BUSY                                                                  0x3A
#define ERROR_CODE_UNACCEPTABLE_CONNECTION_PARAMETERS                                               0x3B
#define ERROR_CODE_ADVERTISING_TIMEOUT                                                              0x3C
#define ERROR_CODE_CONNECTION_TERMINATED_DUE_TO_MIC_FAILURE                                         0x3D
#define ERROR_CODE_CONNECTION_FAILED_TO_BE_ESTABLISHED_OR_SYNCHRONIZATION_TIMEOUT                   0x3E
#define ERROR_CODE_MAC_CONNECTION_FAILED                                                            0x3F
#define ERROR_CODE_COARSE_CLOCK_ADJUSTMENT_REJECTED_BUT_WILL_TRY_TO_ADJUST_USING_CLOCK_DRAGGING     0x40
#define ERROR_CODE_TYPE0_SUBMAP_NOT_DEFINED                                                         0x41
#define ERROR_CODE_UNKNOWN_ADVERTISING_IDENTIFIER                                                   0x42
#define ERROR_CODE_LIMIT_REACHED                                                                    0x43
#define ERROR_CODE_OPERATION_CANCELLED_BY_HOST                                                      0x44
#define ERROR_CODE_PACKET_TOO_LONG                                                                  0x45
//the custom error codes
#define ERROR_CODE_ADDR_ALIG                                                                        0xE0
#define ERROR_CODE_OFFERED_MEMORY_INSUFFICIENT                                                      0xE1
#define ERROR_CODE_UNKNOWN_SCAN_ID                                                                  0xE2
#define ERROR_CODE_UNKNOWN_INIT_ID                                                                  0xE3
#define ERROR_CODE_NEED_INITIALIZATION                                                              0xE4
#define ERROR_CODE_FAIL                                                                             0xFF

#endif
