/*************************************************************************************************************
 * @file    hid_service.c
 * @version V1.0
 * @date    2021-09-04
 * @brief   Human Interface Device Service
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
#include "bluetooth.h"
#include "err_def.h"

#include "gatt_uuid_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"

#include "stack_utility.h"
#include "ble_cb_event_def.h"

#include "app_cfg.h"

#include "hid_service.h"


//=====================================================================================================================
// DEFINE
//=====================================================================================================================
/* HID information flags */
#define HID_FLAGS_REMOTE_WAKE           (0x01) /* RemoteWake */
#define HID_FLAGS_NORMALLY_CONNECTABLE  (0x02) /* NormallyConnectable */

#define HID_KEY_REPORT_ID               (0x01)
#define HID_CONSUMER_REPORT_ID          (0x02)
#define HID_VOICE_REPORT_ID             (0x5A)

/* HID Report type */
#define HID_REPORT_TYPE_INPUT           (1)

//=====================================================================================================================
// GLOBAL VARIABLES
//=====================================================================================================================


//=====================================================================================================================
// LOCAL VARIABLES
//=====================================================================================================================
/* HID Information characteristic value */
static const uint8_t HID_INFO[] =
{
    0x11, 0x01,             /* bcdHID (USB HID version) */
    0x00,                                                   /* bCountryCode */
    HID_FLAGS_REMOTE_WAKE | HID_FLAGS_NORMALLY_CONNECTABLE  /* Flags */
};

static uint16_t u16HandleHidInfo = 0;
static uint16_t u16HandleHidControlPoint = 0;
static uint16_t u16HandleHidMap = 0;

static uint16_t u16HandleReportKeyBord = 0;
static uint16_t u16HandleReportKeyBordConfig = 0;
static uint16_t u16HandleKeyBordReportRef = 0;



static const uint8_t KBD_REPORT_REF[] = { 2, HID_REPORT_TYPE_INPUT };
static volatile uint8_t u8KeyborddReport[KBD_REPORT_NUM] = {0};
static uint16_t gu16KbdConfig = 0;

static uint16_t u16HandleReportConsumer = 0;
static uint16_t u16HandleReportConsumerConfig = 0;
static uint16_t u16HandleConsumerReportRef = 0;

static const uint8_t CONSUMER_REPORT_REF[] = { 3, HID_REPORT_TYPE_INPUT };
static volatile uint16_t u16ConsumerReport[CONSUMER_REPORT_NUM] = {0};
static uint16_t gu16ConsumerConfig = 0;

/* define the HID report map */
static const uint8_t HID_REPORT_MAP[] =
{
    0x05, 0x01,  // Usage Page (Generic Desktop)
    0x09, 0x02,  // Usage (Mouse)
    0xA1, 0x01,  // Collection (Application)
    0x09, 0x01,  //   Usage (Pointer)
    0xA1, 0x00,  //   Collection (Physical)
    0x85, 0x01,  // Report Id (1)
    0x05, 0x09,  //  Usage Page (Buttons)
    0x19, 0x01,  //  Usage Minimum (01) - Button 1
    0x29, 0x03,  //  Usage Maximum (03) - Button 3
    0x15, 0x00,  //  Logical Minimum (0)
    0x25, 0x01,  //  Logical Maximum (1)
    0x75, 0x01,  //  Report Size (1)
    0x95, 0x03,  //  Report Count (3)
    0x81, 0x02,  //  Input (Data, Variable, Absolute) - Button states
    0x75, 0x05,  //  Report Size (5)
    0x95, 0x01,  //  Report Count (1)
    0x81, 0x01,  //  Input (Constant) - Padding or Reserved bits
    0x05, 0x01,  //  Usage Page (Generic Desktop)
    0x09, 0x30,  //  Usage (X)
    0x09, 0x31,  //  Usage (Y)
    0x09, 0x38,  //  Usage (Wheel)
    0x15, 0x81,  //  Logical Minimum (-127)
    0x25, 0x7F,  //  Logical Maximum (127)
    0x75, 0x08,  //  Report Size (8)
    0x95, 0x03,  //  Report Count (3)
    0x81, 0x06,  //  Input (Data, Variable, Relative) - X & Y coordinate`
    0xC0,         //   End Collection
    0xC0,         // End Collection

    0x05, 0x01,     /* Usage Pg (Generic Desktop) */
    0x09, 0x06,     /* Usage (Keyboard) */
    0xA1, 0x01,     /* Collection: (Application) */
    0x85, 0x02,     /* Report ID (2) */
    0x05, 0x07,     /* Usage Pg (Key Codes) */
    0x19, 0xe0,     /* Usage Min (224) */
    0x29, 0xe7,     /* Usage Max (231) */
    0x15, 0x00,     /* Log Min (0) */
    0x25, 0x01,     /* Log Max (1 */
    0x75, 0x01,     /* report Size (1) */
    0x95, 0x08,     /* Report Count (8) */
    0x81, 0x02,     /* Input: (Data, Array) */
    0x95, 0x01,     /* Report Count (1) */
    0x75, 0x08,     /* report Size (8) */
    0x81, 0x01,     /* Input: constant */
    0x95, 0x05,     /* report count(5) */
    0x75, 0x01,     /* report size(1) */
    0x05, 0x08,     /* usage pg(leds) */
    0x19, 0x01,     /* usage min(1) */
    0x29, 0x05,     /* usage max(5) */
    0x91, 0x02,     /* output:(data, variable, absolute) */
    0x95, 0x01,     /* report count(1) */
    0x75, 0x03,     /* report size(3) */
    0x91, 0x01,     /* output: constant */
    0x95, 0x06,     /* report count(6) */
    0x75, 0x08,     /* report size(8) */
    0x15, 0x00,     /* log min(0) */
    0x25, 0xA5,     /* log max(165) */
    0x05, 0x07,     /* usage pg(key codes) */
    0x19, 0x00,     /* usage min(0) */
    0x29, 0xA5,     /* usage max(165) */
    0x81, 0x00,     /* input:(data, array) */
    0xC0,           /* End Collection */

    0x05, 0x0C,       /* Usage Page(Consumer) */
    0x09, 0x01,       /* Usage(Consumer Control) */
    0xA1, 0x01,       /* Collection(Application) */
    0x85, 0x03,       /* Report ID (3)   */
    0x19, 0x00,       /* Usage Min (0x00) */
    0x2a, 0x9c, 0x02, /* Usage Max (0x029c) */
    0x15, 0x00,       /* Logical Min (0x00) */
    0x26, 0x9c, 0x02, /* Logical Max (0x029c) */
    0x75, 0x10,       /* Report Size (0x10) */
    0x95, 0x08,       /* Report Count (0x08) */
    0x81, 0x00,       /* Input (Data,Ary,Abs) */
    0xC0,             /* End Collection(Application) */
};


//=====================================================================================================================
// LOCAL FUNCTIONS
//=====================================================================================================================

//static void rcu_send_audio_report(uint8 u8ConnHandle, uint8_t *report);

//=====================================================================================================================
// LOCAL FUNCTIONS
//=====================================================================================================================
static uint16_t hid_service_get_attribute_len_callback(uint16_t conn_handle,uint16_t attribute_handle);
static uint16_t hid_service_read_attr_callback(uint16_t conn_handle,uint16_t attribute_handle, uint16_t offset, uint8_t  * buffer, uint16_t  buffer_size);
static uint32_t hid_service_write_attr_callback(uint16_t conn_handle,uint16_t attribute_handle, uint16_t  transaction_mode, uint16_t offset, uint8_t  *buffer, uint16_t buffer_size);


static gatt_serviceCBs_t stHidServiceCallBacks =
{
    hid_service_get_attribute_len_callback,
    hid_service_read_attr_callback,
    hid_service_write_attr_callback,
};

static uint16_t hid_service_get_attribute_len_callback ( uint16_t conn_handle,uint16_t u16AttributeHandle )
{
    PRINTF ( "hid get len handle = %04X\r\n", u16AttributeHandle );
    if ( u16AttributeHandle == u16HandleHidInfo )
    {
        PRINTF ( "HID_INFO = %04X\r\n", sizeof ( HID_INFO ) );
        return sizeof ( HID_INFO );
    }
    else if ( u16AttributeHandle == u16HandleHidMap )
    {
        PRINTF ( "HID_REPORT_MAP= %04X\r\n", sizeof ( HID_REPORT_MAP ) );
        return sizeof ( HID_REPORT_MAP );
    }

    else if ( u16AttributeHandle == u16HandleReportKeyBord )
    {
        PRINTF ( "u8KeyborddReport= %04X\r\n", sizeof ( u8KeyborddReport ) );
        return sizeof ( u8KeyborddReport );
    }
    else if ( u16AttributeHandle == u16HandleReportKeyBordConfig )
    {
        PRINTF ( "gu16KbdConfig= %04X\r\n", sizeof ( gu16KbdConfig ) );
        return sizeof ( gu16KbdConfig );
    }

    else if ( u16AttributeHandle == u16HandleReportConsumer )
    {
        PRINTF ( "u16ConsumerReport= %04X\r\n", sizeof ( u16ConsumerReport ) );
        return sizeof ( u16ConsumerReport );
    }

    else if ( u16AttributeHandle == u16HandleReportConsumerConfig )
    {
        PRINTF ( "u16HandleReportConsumerConfig = %04X\r\n", 2 );
        return 2;
    }
    else if(u16AttributeHandle == u16HandleKeyBordReportRef)
    {
        PRINTF ( "u16HandleKeyBordReportRef = %04X\r\n", u16HandleKeyBordReportRef );
        return sizeof ( KBD_REPORT_REF );
    }
    else if(u16AttributeHandle == u16HandleConsumerReportRef)
    {
        PRINTF ( "u16HandleConsumerReportRef = %04X\r\n", u16HandleConsumerReportRef );
        return sizeof ( CONSUMER_REPORT_REF );
    }
    return 0;
}


static uint16_t hid_service_read_attr_callback (uint16_t conn_handle,uint16_t u16AttributeHandle, uint16_t u16Offset, uint8_t  * pBuffer, uint16_t  u16BufferSize )
{
    PRINTF ( "hid read handle = %04X,offset = %d,buff size:%d\r\n", u16AttributeHandle, u16Offset,u16BufferSize);
    if ( u16AttributeHandle == u16HandleHidInfo )
    {
        memcpy ( pBuffer, ( uint8_t* ) HID_INFO + u16Offset, u16BufferSize );
        return u16BufferSize;
    }
    else if ( u16AttributeHandle == u16HandleHidMap )
    {
        memcpy ( pBuffer, HID_REPORT_MAP + u16Offset, u16BufferSize );
        return sizeof ( u16BufferSize );
    }

    else if ( u16AttributeHandle == u16HandleReportKeyBord )
    {
        memcpy ( pBuffer, ( uint8_t* ) u8KeyborddReport + u16Offset, u16BufferSize );
        return u16BufferSize;
    }
    else if ( u16AttributeHandle == u16HandleReportKeyBordConfig )
    {
        memcpy ( pBuffer, ( uint8_t* ) &gu16KbdConfig, u16BufferSize );
        return sizeof ( gu16KbdConfig );
    }

    else if ( u16AttributeHandle == u16HandleReportConsumer )
    {
        memcpy ( pBuffer, ( uint8_t* ) u16ConsumerReport + u16Offset, u16BufferSize );
        return u16BufferSize;
    }

    else if ( u16AttributeHandle == u16HandleReportConsumerConfig )
    {
        memcpy ( pBuffer, ( uint8_t* ) &gu16ConsumerConfig, u16BufferSize );
        return sizeof ( u16BufferSize );
    }
    else if(u16AttributeHandle == u16HandleKeyBordReportRef)
    {
        PRINTF ( "u16HandleKeyBordReportRef = %04X\r\n", u16HandleKeyBordReportRef );
        memcpy ( pBuffer, ( uint8_t* ) KBD_REPORT_REF, u16BufferSize );
        return sizeof ( u16BufferSize );
    }
    else if(u16AttributeHandle == u16HandleConsumerReportRef)
    {
        PRINTF ( "u16HandleConsumerReportRef = %04X\r\n", u16HandleConsumerReportRef );
        memcpy ( pBuffer, ( uint8_t* ) CONSUMER_REPORT_REF, u16BufferSize );
        return sizeof ( u16BufferSize );
    }
    return 0;

}
static uint32_t hid_service_write_attr_callback ( uint16_t conn_handle,uint16_t u16AttributeHandle, uint16_t  transaction_mode, uint16_t u16Offset, uint8_t  *pBuffer, uint16_t buffer_size)
{
    PRINTF ( "hid write handle = %04X,offset = %d\r\n", u16AttributeHandle, u16Offset );
    if ( u16AttributeHandle == u16HandleHidControlPoint )
    {

    }
    else if ( u16AttributeHandle == u16HandleReportKeyBordConfig )
    {
        gu16KbdConfig = pBuffer[0] + ( pBuffer[1] << 8 );
    }
    else if ( u16AttributeHandle == u16HandleReportConsumerConfig )
    {
        u16HandleReportConsumerConfig = pBuffer[0] + ( pBuffer[1] << 8 );
    }
    return 0;
}


void hid_service_init ( void )
{
    uint16_t u16Handle = 0;

    u16Handle = patch_gatts_api_add_service_start ( 0, HID_SERV_UUID, NULL, ( gatt_serviceCBs_t* ) &stHidServiceCallBacks );
    if ( 0 == u16Handle )
    {
        return;
    }

    /* add char: hid infomation */
    u16Handle = 0;
    u16Handle = patch_gatts_api_add_char ( 0, HID_INFORMATION_UUID, NULL, ATT_PROPERTY_READ , ( uint8_t* ) HID_INFO, sizeof ( HID_INFO ) );
    if ( 0 == u16Handle )
    {
        return;
    }
    u16HandleHidInfo = u16Handle;
//    PRINTF("u16HandleHidInfo:%04X\r\n",u16HandleHidInfo);

    /* add char: hid control point */
    u16Handle = 0;
    u16Handle = patch_gatts_api_add_char ( 0, HID_CTRL_PT_UUID, NULL, ATT_PROPERTY_WRITE_WITHOUT_RESPONSE | ATT_PROPERTY_DYNAMIC, NULL, 0 );
    if ( 0 == u16Handle )
    {
        return;
    }
    u16HandleHidControlPoint = u16Handle;
//    PRINTF("u16HandleHidControlPoint:%04X\r\n",u16HandleHidControlPoint);

    /* add char: hid pReport map */ //ATT_PROPERTY_AUTHENTICATION_REQUIRED
    u16Handle = 0;
    u16Handle = patch_gatts_api_add_char ( 0, REPORT_MAP_UUID, NULL, ATT_PROPERTY_READ | ATT_PROPERTY_AUTHENTICATION_REQUIRED , \
                                    ( uint8_t* ) HID_REPORT_MAP, sizeof ( HID_REPORT_MAP ) );
    if ( 0 == u16Handle )
    {
        return;
    }
    u16HandleHidMap = u16Handle;
//    PRINTF("u16HandleHidMap:%04X,size:%d\r\n",u16HandleHidMap,sizeof ( HID_REPORT_MAP ));

    /* add char: HID Report characteristic,keyboard input */
    u16Handle = 0;
    u16Handle = patch_gatts_api_add_char ( 0, REPORT_UUID, NULL, ATT_PROPERTY_READ | ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC | ATT_PROPERTY_AUTHENTICATION_REQUIRED, NULL, 0 );
    if ( 0 == u16Handle )
    {
        return;
    }
    u16HandleReportKeyBord = u16Handle;
//    PRINTF("u16HandleReportKeyBord:%04X\r\n",u16HandleReportKeyBord);

    /* HID Report characteristic client characteristic configuration */
    u16Handle = 0;
    u16Handle = rom_gatts_api_add_char_descrip_client_config();
    if ( 0 == u16Handle )
    {
        return;
    }
    u16HandleReportKeyBordConfig = u16Handle;
//    PRINTF("u16HandleReportKeyBordConfig:%04X\r\n",u16HandleReportKeyBordConfig);

    /* HID Report Reference characteristic descriptor, keyboard input */
    u16Handle = 0;
    u16Handle = rom_gatts_api_add_char_descrip ( GATT_REPORT_REF_UUID, ATT_PROPERTY_READ, 
                                            ( uint8_t* ) KBD_REPORT_REF, sizeof ( KBD_REPORT_REF ) );
    if ( 0 == u16Handle )
    {
        return;
    }
    u16HandleKeyBordReportRef = u16Handle;
//    PRINTF("u16HandleKeyBordReportRef:%04X\r\n",u16HandleKeyBordReportRef);
    /* add char:   HID Report characteristic,consumer control input */
    u16Handle = 0;
    u16Handle = patch_gatts_api_add_char ( 0, REPORT_UUID, NULL, ATT_PROPERTY_READ | ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC | ATT_PROPERTY_AUTHENTICATION_REQUIRED, NULL, 0 );
    if ( 0 == u16Handle )
    {
        return;
    }
    u16HandleReportConsumer = u16Handle;
//    PRINTF("u16HandleReportConsumer:%04X\r\n",u16HandleReportConsumer);

    /* HID Report characteristic client characteristic configuration */
    u16Handle = 0;
    u16Handle = rom_gatts_api_add_char_descrip_client_config();
    if ( 0 == u16Handle )
    {
        return;
    }
    u16HandleReportConsumerConfig = u16Handle;
//    PRINTF("u16HandleReportConsumerConfig:%04X\r\n",u16HandleReportConsumerConfig);

    /* HID Report Reference characteristic descriptor, keyboard input */
    u16Handle = 0;
    u16Handle = rom_gatts_api_add_char_descrip ( GATT_REPORT_REF_UUID, ATT_PROPERTY_READ, ( uint8_t* ) CONSUMER_REPORT_REF, sizeof ( CONSUMER_REPORT_REF ) );
    if ( 0 == u16Handle )
    {
        return;
    }
    u16HandleConsumerReportRef = u16Handle;
//    PRINTF("u16HandleConsumerReportRef:%04X\r\n",u16HandleConsumerReportRef);
    patch_gatts_api_add_service_end();
    
    // PRINTF("hid servive init done.\r\n");
}

bool hid_kbd_report ( uint16_t u16ConnHandle, uint8_t* pReport, uint8_t u8DateLen)
{
    uint8_t u8Ret = 0;
    if((NULL == pReport) || (0 == u8DateLen) || (KBD_REPORT_NUM < u8DateLen))
    {
        return false;
    }
//    u8Ret = rom_gatts_api_send_notify ( u16ConnHandle, u16HandleReportKeyBord, ( uint8_t* ) pReport, KBD_REPORT_NUM );
    u8Ret = rom_gatts_api_send_notify ( u16ConnHandle, u16HandleReportKeyBord, pReport, u8DateLen );
    if(u8Ret)
    {
        PRINTF("hid base send fail : %d\r\n",u8Ret);
        return false;
    }
    PRINTF("rcu.notify.HID(07): 0x");
    for(int i=0; i<u8DateLen; i++)
    {
        PRINTF("%02X ", pReport[i]);
    }
    PRINTF("\n");
    return true;
}

bool hid_consumer_report ( uint16_t u16ConnHandle, uint16_t* pReport, uint8_t u8DateLen)
{
    uint8_t u8Ret = 0;
    if((NULL == pReport) || (0 == u8DateLen) || ((CONSUMER_REPORT_NUM<<1) < u8DateLen))
    {
        return false;
    }
//    u8Ret = rom_gatts_api_send_notify ( u16ConnHandle, u16HandleReportConsumer, (uint8_t*)pReport, CONSUMER_REPORT_NUM << 1 );
    u8Ret = rom_gatts_api_send_notify ( u16ConnHandle, u16HandleReportConsumer, (uint8_t*)pReport, u8DateLen );
    if(u8Ret)
    {
        PRINTF("hid consumer send fail : %d\r\n",u8Ret);
        return false;
    }
    PRINTF("rcu.notify.HID(0C): 0x");
    for(int i=0; i<u8DateLen; i++)
    {
        PRINTF("%04X ", pReport[i]);
    }
    PRINTF("\n");
    return true;
}

