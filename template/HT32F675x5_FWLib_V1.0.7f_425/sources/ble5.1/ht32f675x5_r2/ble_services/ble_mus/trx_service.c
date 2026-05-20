/*************************************************************************************************************
 * @file    trx_service.c
 * @version Initial Draft
 * @date    2016-11-11
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

//0x9000~0x903F : trx_service.c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stack_def.h"
#include "gatt_service_api.h"
#include "patch_gatt_service_api.h"
#include "gatt_client_api.h"

#include "gatt_uuid_def.h"
#include "utility.h"
//#include "hci_struct.h"
//#include "hci_event.h"
#include "gap_api.h"

#include "trx_service.h"
#include "mlog.h"


uint16_t txrx_server_hdl[12] = {0};
uint8_t rxClientCharCfg = 0;
uint8_t txrx_cmd_char_cfg = 0;
uint8_t txrx_indicate_char_cfg = 0;

uint32_t g_data_down = 0;
uint32_t g_data_down_pkt_cnt = 0;
uint32_t g_data_down_data_cnt = 0;
uint32_t g_data_up = 0;
uint32_t g_data_up_data_cnt = 0;

uint32_t g_data_up_snd_cnt = 0;
uint32_t g_data_up_snd_cmplt_cnt = 0;

uint8_t *pbuffer_for_prepwrite = NULL;
uint16_t offset_for_prepwrite = 0;
uint16_t offset_for_prepwrite_start = 0;
uint16_t g_data_indicate_ent = 0;


uint8_t char_blobread_prepwrite[128] = {0};
uint8_t char2_blobread_prepwrite[128] = {0};
uint8_t desp_blobread_prepwrite[128] = {0};
uint8_t g_pdata[256] = {0};
uint8_t val;
#define BLE_MEM_POOL_SIZE 256
uint8_t mem_for_prepwrite[BLE_MEM_POOL_SIZE];
uint8_t mem_for_prepwrite2[BLE_MEM_POOL_SIZE];
uint8_t *pbuffer_for_prepwrite2 = NULL;
uint16_t offset_for_prepwrite2 = 0;
//stAppTimerNode_t g_trx_notify_timer;
uint16_t g_trx_notify_data_len = 4000;
uint16_t g_trx_notifyed_len = 0;
uint8_t g_trx_notifying = false;
#define TRX_BEFORE_NOTIFY_WAIT  100
uint8_t g_trx_before_notify_wait = 0;


gatt_serviceCBs_t txrxCBs =
{
    trx_get_attrLenCB,  // get dynamic attr len
    trx_read_attrCB,    // Read callback function pointer
    trx_write_attrCB,   // Write callback function pointer
};
uint16_t txrx_encpt_val=0;
uint16_t txrx_w_val=0;
extern  uint16_t g_u16ServiceHandle;
extern  uint16_t g_u16ServiceEndHandle;
uint8_t txrx_test_indicate_data ( uint16_t conn_handle, uint16_t flag );
//#define GATT_SR_GAW_BV_01
#define GATT_SR_GAW_BI_09
uint32_t trx_init_service ( void )
{
    MLOG0D ( 0x9000, "trx_init_service" );
    uint16_t hdl = 0;
    int i = 0;
    rom_gatts_api_set_next_attribute_handle ( 0x100 );
    hdl = patch_gatts_api_add_service_start ( 0, HT32_TX_RX_SERVICE_UUID, NULL, &txrxCBs );
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    // hdl = rom_gatts_api_add_include_service (g_u16ServiceHandle, g_u16ServiceEndHandle, 0, DEVINFO_SERV_UUID, NULL  );
    // if ( hdl == 0 )
    // {
    //     return RTN_FAIL;
    // }
#ifdef GATT_SR_GAW_BV_01 //for   GATT/SR/GAW/BV-01-C
 hdl = patch_gatts_api_add_char ( 0, HT32_TRX_W_TEST_UUID, NULL, ( ATT_PROPERTY_READ |ATT_PROPERTY_WRITE_WITHOUT_RESPONSE | ATT_PROPERTY_DYNAMIC ), NULL, 0 );
   if ( hdl == 0 )
   {
       return RTN_FAIL;
   }
   txrx_server_hdl[10] = hdl;
#else 
#ifdef GATT_SR_GAW_BI_09
    hdl = patch_gatts_api_add_char ( 0, HT32_TRX_BLOBREAD_PREPWRITE_TEST_UUID, NULL, ( ATT_PROPERTY_READ | ATT_PROPERTY_WRITE  | ATT_PROPERTY_DYNAMIC ), NULL, 0 );
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[6] = hdl;
   
#else    
    hdl = patch_gatts_api_add_char ( 0, TX_CUS_UUID, NULL, ( ATT_PROPERTY_WRITE_WITHOUT_RESPONSE | ATT_PROPERTY_DYNAMIC ), NULL, 0 );
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[TX_WRITE] = hdl;

    hdl = patch_gatts_api_add_char ( 0, RX_CUS_UUID, NULL, ( ATT_PROPERTY_NOTIFY | ATT_PROPERTY_DYNAMIC ), NULL, 0 );
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[RX_NOTIFY] = hdl;

    hdl = rom_gatts_api_add_char_descrip_client_config();
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[RX_NOTIFY_CONFIG] = hdl;

    hdl = patch_gatts_api_add_char ( 0, HT32_TRX_CMD_UUID, NULL, ( ATT_PROPERTY_NOTIFY | ATT_PROPERTY_WRITE_WITHOUT_RESPONSE  | ATT_PROPERTY_DYNAMIC ), NULL, 0 );
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[TXRX_CMD] = hdl;

    hdl = rom_gatts_api_add_char_descrip_client_config();
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[TXRX_CMD_CONFIG] = hdl;
#if 1 // PTS_AUTHEN_TEST
    rom_gatts_api_set_next_attribute_handle ( 0x11f );
    hdl = patch_gatts_api_add_char ( 0, HT32_TRX_READ_FOR_ENCPT_UUID, NULL, ( ATT_PROPERTY_READ | ATT_PROPERTY_WRITE| ATT_PROPERTY_AUTHENTICATION_REQUIRED|ATT_PROPERTY_KEY_SIZE_REQUIRED_MASK| ATT_PROPERTY_DYNAMIC ), NULL, 0 );
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }

    txrx_server_hdl[TXRX_READ_FOR_ENCPT] = hdl;
#endif

    //for test blob read and prepare write
    hdl = patch_gatts_api_add_char ( 0, HT32_TRX_BLOBREAD_PREPWRITE_TEST_UUID, NULL, ( ATT_PROPERTY_READ | ATT_PROPERTY_WRITE  | ATT_PROPERTY_DYNAMIC ), NULL, 0 );
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[6] = hdl;
    //fot test  indicate
    hdl = patch_gatts_api_add_char ( 0, HT32_TRX_INDICATE_UUID, NULL, ( ATT_PROPERTY_INDICATE | ATT_PROPERTY_DYNAMIC ), NULL, 0 );
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[7] = hdl;
    hdl = rom_gatts_api_add_char_descrip_client_config();
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[8] = hdl;
    hdl =     rom_gatts_api_add_char_descrip ( GATT_CHAR_USER_DESC_UUID,
                                       ATT_PROPERTY_READ | ATT_PROPERTY_WRITE  | ATT_PROPERTY_DYNAMIC, NULL, 0 );

    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[9] = hdl;

   hdl = patch_gatts_api_add_char ( 0, HT32_TRX_W_TEST_UUID, NULL, ( ATT_PROPERTY_READ |ATT_PROPERTY_WRITE | ATT_PROPERTY_DYNAMIC ), NULL, 0 );
   if ( hdl == 0 )
   {
       return RTN_FAIL;
   }
   txrx_server_hdl[10] = hdl;
  //for test blob read and prepare write
    hdl = patch_gatts_api_add_char ( 0, HT32_TRX_BLOBREAD_PREPWRITE_TEST_UUID2, NULL, ( ATT_PROPERTY_READ | ATT_PROPERTY_WRITE  | ATT_PROPERTY_DYNAMIC ), NULL, 0 );
    if ( hdl == 0 )
    {
        return RTN_FAIL;
    }
    txrx_server_hdl[11] = hdl;
#endif
#endif
    offset_for_prepwrite2 = 0;
    patch_gatts_api_add_service_end();
    for ( i = 0; i < sizeof ( char_blobread_prepwrite ); i++ )
    {
        char_blobread_prepwrite[i] = 'A' + i;
        desp_blobread_prepwrite[i] = 'F' + i;
    }
    return  0;

}
uint16_t  trx_get_attrLenCB ( uint16_t conn_handle, uint16_t attribute_handle )
{
    if ( txrx_server_hdl[RX_NOTIFY_CONFIG] == attribute_handle )
    {
        return 2;
    }
    if ( txrx_server_hdl[TXRX_CMD_CONFIG] == attribute_handle )
    {
        return 2;
    }
    if ( txrx_server_hdl[TXRX_READ_FOR_ENCPT] == attribute_handle )
    {
        return 2;
    }
    if ( txrx_server_hdl[8] == attribute_handle )
    {
        return 2;
    }
    if ( txrx_server_hdl[10] == attribute_handle )
    {
        return 2;
    }
    if ( txrx_server_hdl[6] == attribute_handle )
    {
        return sizeof ( char_blobread_prepwrite );
    }
    if ( txrx_server_hdl[11] == attribute_handle )
    {
        return sizeof ( char2_blobread_prepwrite );
    }
    if ( txrx_server_hdl[9] == attribute_handle )
    {
        return sizeof ( desp_blobread_prepwrite );;
    }
    return 0;
}
uint16_t  trx_read_attrCB ( uint16_t conn_handle, uint16_t attribute_handle, uint16_t offset, uint8_t   *buffer, uint16_t  buffer_size )
{
    MLOGD ( 0x9001, "trx_read_attrCB %x", attribute_handle );
    if ( txrx_server_hdl[RX_NOTIFY_CONFIG] == attribute_handle )
    {
        if ( buffer )
        {
            buffer[0] = rxClientCharCfg;
            buffer[1] = 0;
        }
        return 2;
    }
    if ( txrx_server_hdl[TXRX_CMD_CONFIG] == attribute_handle )
    {
        if ( buffer )
        {
            buffer[0] = txrx_cmd_char_cfg;
            buffer[1] = 0;
        }
        return 2;
    }
    if ( txrx_server_hdl[TXRX_READ_FOR_ENCPT] == attribute_handle )
    {
        if ( buffer )
        {
            buffer[0] = txrx_encpt_val&0xff;
            buffer[1] = txrx_encpt_val>>8;
        }
        return 2;
    }
    if ( txrx_server_hdl[10] == attribute_handle )
    {
        if ( buffer )
        {
            buffer[0] = txrx_w_val&0xff;
            buffer[1] = txrx_w_val>>8;
        }
        return 2;
    }
    if ( txrx_server_hdl[8] == attribute_handle )
    {
        if ( buffer )
        {
            buffer[0] = txrx_indicate_char_cfg;
            //LOG ( 0xDC12, txrx_indicate_char_cfg );
            buffer[1] = 0;
        }
        return 2;
    }
    if ( txrx_server_hdl[6] == attribute_handle ) //blob read
    {
        int copylen = buffer_size;
        if ( ( offset + copylen ) > sizeof ( char_blobread_prepwrite ) )
        {
            copylen = sizeof ( char_blobread_prepwrite ) - offset;
        }
        if ( buffer )
        {
            memcpy ( buffer, char_blobread_prepwrite + offset, copylen );

        }
        return copylen;
    }
    if ( txrx_server_hdl[11] == attribute_handle ) //blob read
    {
        int copylen = buffer_size;
        if ( ( offset + copylen ) > sizeof ( char2_blobread_prepwrite ) )
        {
            copylen = sizeof ( char2_blobread_prepwrite ) - offset;
        }
        if ( buffer )
        {
            memcpy ( buffer, char2_blobread_prepwrite + offset, copylen );

        }
        return copylen;
    }
    if ( txrx_server_hdl[9] == attribute_handle ) //blob read
    {
        
        int copylen = buffer_size;
        if ( ( offset + copylen ) > sizeof ( desp_blobread_prepwrite ) )
        {
            copylen = sizeof ( desp_blobread_prepwrite ) - offset;
        }
        if ( buffer )
        {
            memcpy ( buffer,   desp_blobread_prepwrite + offset, copylen );

        }
        return copylen;
    }
    return 0;
}

uint16_t g_last_size=0;
uint32_t trx_write_attrCB ( uint16_t conn_handle, uint16_t attribute_handle, uint16_t  transaction_mode, uint16_t offset, uint8_t  *buffer, uint16_t buffer_size )
{
    MLOG88D ( 0x9002, "trx_write_attrCB hdl=0x%x buffer_size=%d", attribute_handle,buffer_size );
    // LOG ( 0xDC10, transaction_mode );
    if ( ( txrx_server_hdl[TX_WRITE] == attribute_handle ) && ( ATT_TRANSACTION_MODE_NONE == transaction_mode ) )
    {
        //txrx_server_receive ( conn_handle, buffer, buffer_size );
        if((g_last_size +1 != buffer_size) && (g_last_size < buffer_size))
        {
            MLOG88E ( 0x9003, "trx_write_attrCB g_last_size %d buffer_size %d", g_last_size,buffer_size );
        }
        g_last_size=buffer_size;
    }
    else if ( ( txrx_server_hdl[TXRX_CMD] == attribute_handle ) && ( ATT_TRANSACTION_MODE_NONE == transaction_mode ) )
    {
        //txrx_cmd_receive ( conn_handle, buffer, buffer_size );
    }
    if ( txrx_server_hdl[TXRX_READ_FOR_ENCPT] == attribute_handle )
    {
          
            txrx_encpt_val = buffer[0] |buffer[1]<<8;
         
    }
    else if ( txrx_server_hdl[RX_NOTIFY_CONFIG] == attribute_handle )
    {
        rxClientCharCfg = buffer[0];
    }
    else if ( txrx_server_hdl[TXRX_CMD_CONFIG] == attribute_handle )
    {
        txrx_cmd_char_cfg = buffer[0];
    }
    else if (  txrx_server_hdl[10] == attribute_handle   )
    {
        if ( buffer_size != 2 )
        {
            return ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH;
        }
        txrx_w_val = buffer[0] |buffer[1]<<8;
    }
    else if ( txrx_server_hdl[8] == attribute_handle )
    {
        //LOG ( 0xDC13, txrx_indicate_char_cfg );
        txrx_indicate_char_cfg = buffer[0];
    }
    else if ( txrx_server_hdl[6] == attribute_handle )
    {
        if ( ATT_TRANSACTION_MODE_NONE == transaction_mode )  //normal write
        {

            int copylen = buffer_size;
            if ( buffer_size > sizeof ( char_blobread_prepwrite ) )
            {
                copylen = sizeof ( char_blobread_prepwrite );
                return ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH;
            }
            memcpy ( char_blobread_prepwrite, buffer, copylen );


        }
        else if ( ATT_TRANSACTION_MODE_ACTIVE == transaction_mode )   //prepare write
        {
            if ( NULL == pbuffer_for_prepwrite )
            {
                pbuffer_for_prepwrite = mem_for_prepwrite;
                offset_for_prepwrite = 0;
                offset_for_prepwrite_start = offset;
            }
            if ( NULL != pbuffer_for_prepwrite )
            {
                int copylen = buffer_size;
                if ( offset  >= sizeof ( char_blobread_prepwrite ) )
                {
                    copylen = 0;
                     //return ATT_ERROR_INVALID_OFFSET;
                }
                else if ( ( offset + copylen ) > BLE_MEM_POOL_SIZE )
                {
                    copylen = BLE_MEM_POOL_SIZE - offset;
                     
                }
                if ( copylen  &&  buffer )
                {
                    memcpy ( pbuffer_for_prepwrite + offset, buffer, copylen );
                    offset_for_prepwrite += copylen;
                }

            }
        }
        else if ( ATT_TRANSACTION_MODE_EXECUTE == transaction_mode )  //execute write
        {

            if ( pbuffer_for_prepwrite  && ( offset_for_prepwrite || offset_for_prepwrite_start ) )
            {
                int copylen = offset_for_prepwrite;
                if ( offset_for_prepwrite_start  >= sizeof ( char_blobread_prepwrite ) )
                {
                    offset_for_prepwrite = 0;
                    offset_for_prepwrite_start = 0;
                    return ATT_ERROR_INVALID_OFFSET;
                }
                if ( offset_for_prepwrite > sizeof ( char_blobread_prepwrite ) - offset_for_prepwrite_start )
                {
                    copylen = sizeof ( char_blobread_prepwrite );
                    offset_for_prepwrite = 0;
                    offset_for_prepwrite_start = 0;
                    return ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH;
                }
                memcpy ( char_blobread_prepwrite+offset_for_prepwrite_start, pbuffer_for_prepwrite, copylen );
            }
            if ( pbuffer_for_prepwrite )
            {
                //osPoolFree ( ble_pool_id, pbuffer_for_prepwrite );
                pbuffer_for_prepwrite = NULL;
            }
            offset_for_prepwrite = 0;
            offset_for_prepwrite_start = 0;
             if ( pbuffer_for_prepwrite2  && ( offset_for_prepwrite2 > 0 ) )
            {
                int copylen = offset_for_prepwrite2;
                if ( offset_for_prepwrite2 > sizeof ( char2_blobread_prepwrite ) )
                {
                    copylen = sizeof ( char2_blobread_prepwrite );
                    return ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH;
                }
                memcpy ( char2_blobread_prepwrite, pbuffer_for_prepwrite2, copylen );
            }
            if ( pbuffer_for_prepwrite2 )
            {
                //osPoolFree ( ble_pool_id, pbuffer_for_prepwrite );
                pbuffer_for_prepwrite2 = NULL;
            }
            offset_for_prepwrite2 = 0;
        }
        else if ( ATT_TRANSACTION_MODE_CANCEL == transaction_mode ) //cancel write
        {
             
            if ( pbuffer_for_prepwrite )
            {
                //osPoolFree ( ble_pool_id, pbuffer_for_prepwrite );
                pbuffer_for_prepwrite = NULL;
            }
            offset_for_prepwrite = 0;
            offset_for_prepwrite_start = 0;
            if ( pbuffer_for_prepwrite2 )
            {
                //osPoolFree ( ble_pool_id, pbuffer_for_prepwrite );
                pbuffer_for_prepwrite2 = NULL;
            }
            offset_for_prepwrite2 = 0;
        }

    }
    else if ( txrx_server_hdl[11] == attribute_handle )
    {
        if ( ATT_TRANSACTION_MODE_NONE == transaction_mode )  //normal write
        {

            int copylen = buffer_size;
            if ( buffer_size > sizeof ( char2_blobread_prepwrite ) )
            {
                copylen = sizeof ( char2_blobread_prepwrite );
                return ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH;
            }
            memcpy ( char2_blobread_prepwrite, buffer, copylen );


        }
        else if ( ATT_TRANSACTION_MODE_ACTIVE == transaction_mode )   //prepare write
        {
            if ( NULL == pbuffer_for_prepwrite2 )
            {
                pbuffer_for_prepwrite2 = mem_for_prepwrite2;
                offset_for_prepwrite2 = 0;
            }
            if ( NULL != pbuffer_for_prepwrite2 )
            {
                int copylen = buffer_size;
                if ( offset  >= sizeof ( char2_blobread_prepwrite ) )
                {
                    copylen = 0;
                     return ATT_ERROR_INVALID_OFFSET;
                }
                else if ( ( offset + copylen ) > BLE_MEM_POOL_SIZE )
                {
                    copylen = BLE_MEM_POOL_SIZE - offset;
                     
                }
                if ( copylen  &&  buffer )
                {
                    memcpy ( pbuffer_for_prepwrite2 + offset, buffer, copylen );
                    offset_for_prepwrite2 += copylen;
                }

            }
        }
        else if ( ATT_TRANSACTION_MODE_EXECUTE == transaction_mode )  //execute write
        {

            if ( pbuffer_for_prepwrite2  && ( offset_for_prepwrite2 > 0 ) )
            {
                int copylen = offset_for_prepwrite2;
                if ( offset_for_prepwrite2 > sizeof ( char2_blobread_prepwrite ) )
                {
                    copylen = sizeof ( char2_blobread_prepwrite );
                    return ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH;
                }
                memcpy ( char2_blobread_prepwrite, pbuffer_for_prepwrite2, copylen );
            }
            if ( pbuffer_for_prepwrite2 )
            {
                //osPoolFree ( ble_pool_id, pbuffer_for_prepwrite );
                pbuffer_for_prepwrite2 = NULL;
            }
            offset_for_prepwrite2 = 0;
            if ( pbuffer_for_prepwrite  && ( offset_for_prepwrite > 0 ) )
            {
                int copylen = offset_for_prepwrite;
                if ( offset_for_prepwrite > sizeof ( char_blobread_prepwrite ) )
                {
                    copylen = sizeof ( char_blobread_prepwrite );
                    return ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH;
                }
                memcpy ( char_blobread_prepwrite, pbuffer_for_prepwrite, copylen );
            }
            if ( pbuffer_for_prepwrite )
            {
                //osPoolFree ( ble_pool_id, pbuffer_for_prepwrite );
                pbuffer_for_prepwrite = NULL;
            }
            offset_for_prepwrite = 0;
        }
        else if ( ATT_TRANSACTION_MODE_CANCEL == transaction_mode ) //cancel write
        {
            if ( pbuffer_for_prepwrite2 )
            {
                //osPoolFree ( ble_pool_id, pbuffer_for_prepwrite );
                pbuffer_for_prepwrite2 = NULL;
            }
            offset_for_prepwrite2 = 0;
            if ( pbuffer_for_prepwrite )
            {
                //osPoolFree ( ble_pool_id, pbuffer_for_prepwrite );
                pbuffer_for_prepwrite = NULL;
            }
            offset_for_prepwrite = 0;
        }

    }
    else if ( ( txrx_server_hdl[7] == attribute_handle ) && ( ATT_TRANSACTION_MODE_CONFIRM_FOR_INDICAT == transaction_mode ) )
    {
        if ( g_data_indicate_ent > 0 )
        {
            //txrx_test_indicate_data ( conn_handle, g_data_indicate_ent );
            g_data_indicate_ent--;
        }
    }    
    else if ( txrx_server_hdl[9] == attribute_handle )
    {
        if ( ATT_TRANSACTION_MODE_NONE == transaction_mode )  //normal write
        {

            int copylen = buffer_size;
            if ( buffer_size > sizeof ( desp_blobread_prepwrite ) )
            {
                copylen = sizeof ( desp_blobread_prepwrite );
            }
            memcpy ( desp_blobread_prepwrite, buffer, copylen );


        }
        else if ( ATT_TRANSACTION_MODE_ACTIVE == transaction_mode )   //prepare write
        {
            if ( NULL == pbuffer_for_prepwrite )
            {
                pbuffer_for_prepwrite = mem_for_prepwrite;
                offset_for_prepwrite = 0;
            }
            if ( NULL != pbuffer_for_prepwrite )
            {
                int copylen = buffer_size;
                if ( offset  >= sizeof ( desp_blobread_prepwrite )  )
                {
                    copylen = 0;
                    return ATT_ERROR_INVALID_OFFSET;
                }
                else if ( ( offset + copylen ) > BLE_MEM_POOL_SIZE )
                {
                    copylen = BLE_MEM_POOL_SIZE - offset;
                      
                }
                if ( copylen  &&  buffer )
                {
                    memcpy ( pbuffer_for_prepwrite + offset, buffer, copylen );
                    offset_for_prepwrite += copylen;
                }

            }
        }
        else if ( ATT_TRANSACTION_MODE_EXECUTE == transaction_mode )  //execute write
        {

            if ( pbuffer_for_prepwrite  && ( offset_for_prepwrite > 0 ) )
            {
                int copylen = offset_for_prepwrite;
                if ( offset_for_prepwrite > sizeof ( desp_blobread_prepwrite ) )
                {
                    copylen = sizeof ( desp_blobread_prepwrite );
                    return ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH;
                }
                memcpy ( desp_blobread_prepwrite, pbuffer_for_prepwrite, copylen );
            }
            if ( pbuffer_for_prepwrite )
            {

                pbuffer_for_prepwrite = NULL;
            }
            offset_for_prepwrite = 0;
        }
        else if ( ATT_TRANSACTION_MODE_CANCEL == transaction_mode ) //cancel write
        {
            if ( pbuffer_for_prepwrite )
            {
                pbuffer_for_prepwrite = NULL;
            }
            offset_for_prepwrite = 0;
        }

    }
    return 0;
}


/**
* @brief  server transfer data to client
* @param   uint8_t *data databuffer, uinit16 databuffer length
* @return  0 succeed, 1 fail
*/
uint32_t txrx_server_transfer ( uint16_t conn_handle, uint8_t *data, uint32_t length )
{
    uint32_t ret_code = 0;

    if ( rxClientCharCfg )
    {
        ret_code = rom_gatts_api_send_notify ( conn_handle, txrx_server_hdl[RX_NOTIFY], data, length );
    }
    else
    {
        ret_code = 0xFE; // notify disable
    }

    return ret_code;
}
uint8_t txrx_server_write( uint16_t conn_handle, uint8_t *data, uint32_t length )
{    

    return rom_gatt_client_api_write_value_of_characteristic_without_response ( conn_handle, txrx_server_hdl[TX_WRITE],  length,data );
    
}

uint8_t txrx_test_cmd_transfer ( uint16_t conn_handle, uint8_t *data, uint16_t length )
{
    return rom_gatts_api_send_notify ( conn_handle, txrx_server_hdl[TXRX_CMD], data, length );

}

uint8_t txrx_test_indicate_data ( uint16_t conn_handle, uint16_t flag )
{
    uint8_t i = 0;
    for ( i = 0; i < 20; i++ )
    {

        g_pdata[i] =  i + flag * 20;

    }


    i = rom_gatts_api_send_indicate ( conn_handle, txrx_server_hdl[7], g_pdata, 20 );
    //LOG ( 0xDC31, i << 8 | flag );
    return i;

}
#if 0
int trx_up_snd_a_pkt ( uint16_t conn_handle, int mtu )
{
    int len = g_data_up_data_cnt;
    int i = 0;

    if ( g_data_up_data_cnt > mtu - 3 )
    {
        len = mtu - 3;////252 251 250
    }

    for ( i = 0; i < len; i++ )
    {
        int val = ( i >> 1 ) + g_data_up_data_cnt - len; //? - ?
        if ( i & 0x1 )
        {
            g_pdata[i] = ( val >> 8 ) & 0xff;
        }
        else
        {
            g_pdata[i] =  val & 0xff;
        }
    }

    if ( 0 == txrx_server_transfer ( conn_handle, g_pdata, len ) )
    {
        g_data_up_data_cnt -= len;
        LOG ( 0xd055, g_data_up_data_cnt );
        return 0;
    }
    return 1;
}
void trx_up ( uint16_t conn_handle )
{
    int mtu = 0; //ble_api_get_mtu(0);
    //uint16_t intv,  laty, tout;
    uint8_t sdata[4] = { 0xF0, 0x4D, 0};
    if ( 0 == g_data_up )
    {
        return;
    }
    LOG ( 0xd056,     g_data_up_snd_cnt );
    if ( g_data_up_data_cnt == 0 )
    {
        //   up over
        txrx_server_transfer ( conn_handle, sdata, 2 );
        g_data_up = 0;
        return;
    }
    mtu = ble_api_get_mtu ( conn_handle );
    if ( 0 == trx_up_snd_a_pkt ( conn_handle, mtu ) )
    {
        g_data_up_snd_cnt++;
    }
    //ble_api_get_con_para(0,&intv,&laty,&tout);

    // mtu = ble_api_get_mtu ( conn_handle );
    // if ( 0 == g_data_up_snd_cnt )
    // {

    //     if ( 0 == trx_up_snd_a_pkt ( conn_handle, mtu ) )
    //     {
    //         g_data_up_snd_cnt++;
    //     }
    // }
    // else
    // {
    //     g_data_up_snd_cmplt_cnt++;
    // }

    // if ( g_data_up_snd_cnt < 4 + g_data_up_snd_cmplt_cnt )
    // {
    //     int i = 0;
    //     for ( i = 0; i < 3; i++ )
    //     {
    //         if ( 0 == trx_up_snd_a_pkt ( conn_handle, mtu ) )
    //         {
    //             g_data_up_snd_cnt++;
    //         }
    //     }

    // }


}
uint16_t txrx_cmd_receive ( uint16_t conn_handle, uint8_t *data, uint16_t length )
{
    LOG ( 0xDC11, data[0] << 8 | data[2] );
    if ( data[0] == 0xf0 && data[1] == 0x8d && length == 2 ) //start down
    {
        g_data_down = 1;
        g_data_down_pkt_cnt = 0;
        g_data_down_data_cnt = 0;
        g_data_up = 0;
    }
    else if ( data[0] == 0xf0 && data[1] == 0xcd && length == 2 ) //end down
    {
        uint8_t sdata[8] = { 0xF0, 0x0C, 0}; //  F0 0C  //len 90 01 00 00  //count 00 00

        rom_little_endian_store_32 ( sdata, 2, g_data_down_data_cnt );
        rom_little_endian_store_16 ( sdata, 6, g_data_down_pkt_cnt );

        txrx_server_transfer ( conn_handle, sdata, 8 );
        g_data_down = 0;
    }
    else if ( data[0] == 0xf0 && data[1] == 0x8e  && data[2] == 0x0d && length == 3 ) //start up
    {
        uint16_t intv,  laty, tout;
        uint8_t sdata[4] = { 0xF0, 0x0D, 0}; //   F0 0D 30 75  start up
        ble_api_get_con_para ( conn_handle, &intv, &laty, &tout );
        g_data_up = 1;
        if ( intv < 800 )
        {
            g_data_up_data_cnt = 30000;
        }
        else
        {
            g_data_up_data_cnt = 3000;
        }
        g_data_up_snd_cnt = 0;
        g_data_up_snd_cmplt_cnt = 0;
        rom_little_endian_store_16 ( sdata, 2, g_data_up_data_cnt );
        txrx_server_transfer ( conn_handle, sdata, 4 );

    }
    else if ( data[0] == 1 && data[1] == 1 && length == 2 ) //disconnect
    {
        ble_api_terminate_conn ( conn_handle, 0x13 );
    }
    else if ( data[0] == 2 && data[1] == 2 && length == 4 ) //set interval
    {
        uint16_t intv;
        uint16_t tout;

        intv = rom_little_endian_read_16 ( data, 2 );
        LOG ( 0xDC11, intv );
        if ( intv == 101 )
        {
            ble_api_send_phy_updata ( conn_handle, GAP_PHY_1MBPS, GAP_PHY_1MBPS );
        }
        else if ( intv == 102 )
        {
            ble_api_send_phy_updata ( conn_handle, GAP_PHY_2MBPS, GAP_PHY_2MBPS );
        }
        else if ( intv == 103 )
        {
            ble_api_send_phy_updata ( conn_handle, GAP_PHY_CODED, GAP_PHY_CODED );
        }
        else if ( intv == 100 )
        {
            ble_api_terminate_conn ( conn_handle, 0x13 );
        }
        else if ( intv == 105 )
        {
            ll_ctrl_start_ll_version_req ( conn_handle );
        }
        else
        {
            tout =  intv << 2 ;
            if ( intv  > 0x0C80 )
            {
                intv = 0x0C80;
            }
            if ( tout  > 0x0C80 )
            {
                tout = 0x0C80;
            }

            ble_api_update_conn_para ( conn_handle, intv, intv, 0, tout );
        }



    }
    else if ( data[0] == 3 && data[1] == 3 && length == 2 ) //read interval
    {
        uint16_t intv,  laty, tout;
        uint8_t sdata[4] = {3, 3, 0, 200};
        ble_api_get_con_para ( conn_handle, &intv, &laty, &tout );
        sdata[2] = intv & 0xff;
        sdata[3] = intv >> 8;
        txrx_test_cmd_transfer ( conn_handle, sdata, 4 );
    }
    else if ( data[0] == 4 && data[1] == 4 && length == 4 ) //set mtu
    {
        uint16_t mtu = rom_little_endian_read_16 ( data, 2 );
        ble_api_exchange_mtu ( conn_handle, mtu );
    }
    else if ( data[0] == 5 && data[1] == 5 && length == 2 ) //read mtu
    {
        uint16_t mtu = 0;
        uint8_t sdata[4] = {5, 5, 0, 0};
        mtu = ble_api_get_mtu ( conn_handle );
        sdata[2] = mtu & 0xff;
        sdata[3] = mtu >> 8;
        txrx_test_cmd_transfer ( conn_handle, sdata, 4 );
    }
    else if ( data[0] == 0xd0 && data[1] == 0xd0 && length == 2 ) //start indicate
    {
        g_data_indicate_ent = 5;
        txrx_test_indicate_data ( conn_handle, g_data_indicate_ent );
    }
    return 0;
}

uint16_t txrx_server_receive ( uint16_t conn_handle, uint8_t *data, uint16_t length )
{
    if ( length == 2 && data[0] == 0xf0 && data[1] == 0x8d )   //start down
    {
        g_data_down = 1;
        g_data_down_pkt_cnt = 0;
        g_data_down_data_cnt = 0;
        g_data_up = 0;
    }
    else if ( length == 2 && data[0] == 0xf0 && data[1] == 0xcd )   //end down
    {
        uint8_t sdata[8] = { 0xF0, 0x0C, 0}; //  F0 0C  //len 90 01 00 00  //count 00 00

        rom_little_endian_store_32 ( sdata, 2, g_data_down_data_cnt );
        rom_little_endian_store_16 ( sdata, 6, g_data_down_pkt_cnt );

        txrx_server_transfer ( conn_handle, sdata, 8 );
        g_data_down = 0;
    }
    else if ( length == 3 && data[0] == 0xf0 && data[1] == 0x8e  && data[2] == 0x0d )   //start up
    {
        uint16_t intv,  laty, tout;
        uint8_t sdata[4] = { 0xF0, 0x0D, 0}; //   F0 0D 30 75  start up
        ble_api_get_con_para ( conn_handle, &intv, &laty, &tout );
        g_data_up = 1;
        if ( intv < 800 )
        {
            g_data_up_data_cnt = 30000;
        }
        else
        {
            g_data_up_data_cnt = 3000;
        }
        g_data_up_snd_cnt = 0;
        g_data_up_snd_cmplt_cnt = 0;
        rom_little_endian_store_16 ( sdata, 2, g_data_up_data_cnt );
        txrx_server_transfer ( conn_handle, sdata, 4 );

    }
    if ( 1 == g_data_down )
    {
        g_data_down_pkt_cnt++;
        g_data_down_data_cnt += length;
        return 0;
    }

#ifdef HCI_FUNC_EN

    hci_data_rpt_event ( conn_handle, data, length );

#endif

    return 0;
}

uint8_t trx_server_notify ( uint16_t conn_handle, uint8_t *data, uint16_t length )
{
    uint8_t ret_err;
    ret_err = rom_gatts_api_send_notify ( conn_handle, txrx_server_hdl[10], data, length );
    return ret_err;
}

void trx_server_notify_data_handler ( void *p_param )
{
    uint8_t ret_err;
    uint16_t packet_len = 252;

    if ( g_trx_before_notify_wait < TRX_BEFORE_NOTIFY_WAIT )
    {
        g_trx_before_notify_wait++;
        return ;
    }
    if ( g_trx_notifyed_len < g_trx_notify_data_len )
    {
        ret_err = trx_server_notify ( ( uint8_t ) p_param, g_pdata, packet_len );
        if ( 0 == ret_err )
        {
            g_trx_notifyed_len += packet_len;
        }
        LOG ( 0xdff1, att_get_avail_data_buffer_num() );
    }
    else
    {
        g_trx_notifyed_len = 0;
//      trx_server_stop_notify_data();
    }
}
void trx_server_set_notify_data ( void )
{
    uint16_t i;
    for ( i = 0; i < sizeof ( g_pdata ); i++ )
    {
        g_pdata[i] = i;
    }
}
void trx_server_notify_data ( uint16_t conn_handle )
{
    if ( false == g_trx_notifying )
    {
        g_trx_notifying = true;
        trx_server_set_notify_data();
        //app_timer_create ( &g_trx_notify_timer, APP_TIMER_MODE_REPEAT, trx_server_notify_data_handler );
        //app_timer_start ( &g_trx_notify_timer, 5, ( void* ) conn_handle );
        g_trx_notifyed_len = 0;
        g_trx_before_notify_wait = 0;
    }
}

void trx_server_stop_notify_data ( void )
{
    g_trx_notifying = false;
    //app_timer_stop ( &g_trx_notify_timer );
}
#endif
#if 0
extern uint8_t g_con_idx;
void sys_test_con_cmd_handler ( uint16_t opcode, uint8_t *data, uint16_t payload_length )
{
    uint8_t ret_err;
    gap_create_connection_params_t init_params = {0};
    switch ( opcode )
    {
    case 0x2000:
    {
        ble_api_terminate_conn ( g_con_idx, 0x13 );
        break;
    }
    case 0x2001:
    {
        ble_api_send_phy_updata ( g_con_idx, GAP_PHY_1MBPS, GAP_PHY_1MBPS );
        break;
    }
    case 0x2002:
    {
        ble_api_send_phy_updata ( g_con_idx, GAP_PHY_2MBPS, GAP_PHY_2MBPS );
        break;
    }
    case 0x2003:
    {
        ble_api_send_phy_updata ( g_con_idx, GAP_PHY_CODED, GAP_PHY_CODED );
        break;
    }
    case 0x2004:
    {
        uint16_t mtu = rom_little_endian_read_16 ( data, 0 );
        ble_api_exchange_mtu ( g_con_idx, mtu );
        break;
    }
    case 0x2005:
    {
        ble_api_send_long_length_req ( g_con_idx );
        break;
    }
    case 0x2006:
    {
        ble_api_start_feature_exchange ( g_con_idx );
        break;
    }
    case 0x2007:
    {
        ble_api_send_version_req ( g_con_idx );
        break;
    }
    case 0x2008:
    {
        ble_api_send_security_req ( g_con_idx );
        break;
    }
    case 0x2010:
    {
        uint16_t intv;
        uint16_t tout;

        intv = rom_little_endian_read_16 ( data, 0 );
        tout = rom_little_endian_read_16 ( data, 2 );
        //tout =  intv << 2 ;
        if ( intv  > 0x0C80 )
        {
            intv = 0x0C80;
        }
        if ( tout  > 0x0C80 )
        {
            tout = 0x0C80;
        }

        ble_api_update_conn_para ( g_con_idx, intv, intv, 0, tout );
        break;
    }


    }


}
#endif