/*************************************************************************************************************
 * @file    ota.h
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
#ifndef OTA_H
#define OTA_H

/* OTA One Package Minimum Length : CmdType(1Byte) + CmdVal(1Byte) + DataLength(2Bytes) + Crc16(2Bytes) */
#define OTA_PACKAGE_MIN_LEN                         (6)
/* OTA Upgrade Code Maxlength */
#define OTA_PACKAGE_CODE_MAX_LEN                    (187)
/* The MaxLength of continuous transmit ota upgrade code of no reply required */
#define OTA_CONTINUOUS_TRANS_MAX_LEN                (60 * 1024)
/* OTA Package Maxlength */
#define OTA_PACKAGE_MAX_LEN                         (OTA_PACKAGE_CODE_MAX_LEN + OTA_PACKAGE_MIN_LEN + 3)
/* Ble OTA Mtu */
#define BLE_OTA_MTU                                 (200)
#define BLE_OTA_MAXCONNINTERVAL                     (50)				/*unit ms*/
#define BLE_OTA_MINCONNINTERVAL                     (50)				/*unit ms*/
#define BLE_OTA_SUPERTIMOUT                         (5000)       	/*unit ms*/
#define OTA_CHIP_DELAY_RESET_TIME                   (500)

#define OTA_PACKAGE_CMD_TYPE_INDEX                  (0)
#define OTA_PACKAGE_CMD_VALUE_INDEX                 (1)
#define OTA_PACKAGE_DATA_LEN_INDEX                  (2)
#define OTA_PACKAGE_DATA_INDEX                      (4)
#define OTA_PACKAGE_CRC_INDEX(dataLen)              (OTA_PACKAGE_DATA_INDEX + dataLen)

#define OTA_GET_FIRMWARE_INFO_DATA_LEN              (0)
#define OTA_RSP_GET_FIRMWARE_INFO_DATA_LEN          (12)

#define OTA_FIRMWARE_UPGRADE_REQUEST_DATA_LEN       (13)
#define OTA_FM_REQ_DATA_CHIP_TYPE_IDX               (OTA_PACKAGE_DATA_INDEX)
#define OTA_FM_REQ_DATA_ROM_VERISION_IDX            (OTA_FM_REQ_DATA_CHIP_TYPE_IDX + 1)
#define OTA_FM_REQ_DATA_BOOT2_VERSION_IDX           (OTA_FM_REQ_DATA_ROM_VERISION_IDX + 1)
#define OTA_FM_REQ_DATA_APP_VERSION_IDX             (OTA_FM_REQ_DATA_BOOT2_VERSION_IDX + 1)
#define OTA_FM_REQ_DATA_BIN_SIZE_IDX                (OTA_FM_REQ_DATA_APP_VERSION_IDX + 2)
#define OTA_FM_REQ_DATA_BIN_CRC_IND                 (OTA_FM_REQ_DATA_BIN_SIZE_IDX + 4)
#define OTA_RSP_FIRMWARE_UPGRADE_REQUEST_DATA_LEN   (5)

#define OTA_RSP_CHIP_RESTART_DATA_LEN               (3)

/* OTA Package Response */
typedef enum
{
    EN_OTA_RSP_SAVE_FLASH_OK            = 0x00,
    EN_OTA_RSP_CRC_ERROR                = 0x01,
    EN_OTA_RSP_SAVE_FLASH_ERROR         = 0x02,
    EN_OTA_RSP_PACKAGE_INDEX_ERROR      = 0X03,
} EN_RSP_STATUS_T;

/* OTA Command Value (Event) */
typedef enum
{
    EN_OTA_EVT_GET_FIRMWARE_INFO        = 0x01,
    EN_OTA_EVT_HANDSHAKE                = 0x02,
    EN_OTA_EVT_UPGRADE_REQUEST          = 0x03,
    EN_OTA_EVT_UPGRADE_CODE             = 0x04,
    EN_OTA_EVT_UPGRADE_FINISH           = 0x05,
    EN_OTA_EVT_CHIP_RESTART             = 0x06
}EN_OTA_EVT_T;

/* OTA Command Type */
typedef enum
{
    EN_OTA_APP_TO_CHIP_CMD      = 0x01,
    EN_OTA_SYNC_STATE_CMD       = 0x02,
    EN_OTA_CHIP_TO_APP_CMD      = 0x03,
}EN_OTA_CMD_T;

/* OTA Handshake */
typedef enum
{
    EN_OTA_SKIP_HANDSHAKE           = 0x01,
    EN_OTA_HANDSHAKE_NOT_ENCRYPT    = 0x02,
    EN_OTA_HANDSHAKE_AND_ENCRYPT    = 0x03,

}EN_OTA_HANDSHAKE_T;

/* OTA Firmware Upgrade Type */
typedef enum
{
    EN_OTA_FIRMWARE_UPGRADE_NOT_ALLOWED     = 0x00,
    EN_OTA_FIRMWARE_UPGRADE                 = 0x01
}EN_OTA_UPGRADE_T;

/* OTA Restart Type */
typedef enum
{
    EN_OTA_RESTART = 0x00,
    EN_OTA_NOT_RESTART = 0x01,
}EN_CHIP_RESTART_T;

/* OTA Upgrade Code Information */
typedef struct __attribute__((aligned(4)))
{
    // Information
    uint16_t u16HT32Flag;          // HT32 Flag: 2A4B, customer can not change.
    uint8_t u8RomVer;              // Rom version.
    uint8_t u8Boot2Ver;            // Secondary boot version.
    uint32_t u32NeedFwUpgradeFlag; // Need upgrade or not.

    // Firmware upgrade saved information
    uint32_t u32BinFlashAddrOffset; // The offset address of bin code saved in flash.
    uint32_t u32BinCodeSize;        // Bin code size
    uint32_t u32BinCodeCrc;         // Bin code crc32

    // Current running code region.
    uint32_t u32RunningCodeAddrOffset; // Current running code offset address.
    uint32_t u32RunningCodeSize;       // Current running code size.

    uint32_t u32StructCrc; // Struct information crc32.

} stFwUpgradeCodeInfo_t;

/* OTA Event Callback Type */
typedef void (*ota_event_callback_t)(EN_OTA_EVT_T enEvt);

/**********************************************************************************************************************
 * @brief  Parse and distribute package to data parsing flow by CmdValue.
 * @param  u16ConnHandle: Ble connection handle
 * @param  pu8Data: OTA package.
 * @param  u16DataLen: The length of OTA package.
 * @param  eventCb: OTA event callback.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T ota_protocol_parse(uint16_t u16ConnHandle,uint8_t *pu8Data,uint16_t u16DataLen,ota_event_callback_t eventCb);

/**********************************************************************************************************************
 * @brief  Parse OTA received restart package and reponse status package.
 * @param  bRestartRightNow: Whether restart right now
 * @param  u32ResetDelayMs: After @ref u32ResetDelayMs ms restart.
 * @output
 * @return HW status: @ref EN_ERR_STA_T
 *********************************************************************************************************************/
EN_ERR_STA_T ota_rsp_restart(bool bRestartRightNow, uint32_t u32ResetDelayMs);

#endif
