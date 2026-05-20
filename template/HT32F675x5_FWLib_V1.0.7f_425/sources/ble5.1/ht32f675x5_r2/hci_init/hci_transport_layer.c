/*************************************************************************************************************
 * @file    hci_transport_layer.c
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

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "app_cfg.h"

#include "RegHT32F675x5.h"
#include "boards.h"

#include "llc_spec_5_1.h"
#include "patch_llc_spec_5_1.h"
#include "llc_llp_interface.h"
#include "hci.h"
#include "llc_tool.h"
#include "patch_llc_tool.h"

#include "err_def.h"
#include "hw_gpio.h"
#include "hw_sys_ctrl.h"
#include "hw_crg.h"
#include "hw_uart.h"
#include "patch_hw_uart.h"
#include "hw_crg.h"

#include "utility.h"
#include "app_debug.h"

#include "rtx_lib.h"

#include "hci_transport_layer.h"


#define UART_INTERRUPT_FLAGS (UART_INT_RX_TIMEOUT|UART_INT_RXFIFO_OVER_THLD|UART_INT_RXFIFO_OVER_FLOW)


typedef enum
{
    HCI_PACKET_TYPE_COMMAND          = 0x01,
    HCI_PACKET_TYPE_ACL_DATA         = 0x02,
    HCI_PACKET_TYPE_SYNCHRONOUS_DATA = 0x03,
    HCI_PACKET_TYPE_EVENT            = 0x04,
}
EN_HCI_PACKET_TYPE_T;



typedef struct
{
    uint16_t u16DataSize;
    uint8_t pu8Data[HCI_MSG_DATA_MAX_SIZE];
}
stHciTaskMsg_t;


#define HCI_SET_EVENT_MASK_COMMAND_OPCODE    (((LLC_SPEC_5_1_HCI_OGF_CONTROLLER_AND_BASEBAND_COMMANDS&0x3F)<<10)|(LLC_SPEC_5_1_HCI_OCF_HCI_Set_Event_Mask&0x3FF))

#define HCI_LE_SET_EVENT_MASK_COMMAND_OPCODE    (((LLC_SPEC_5_1_HCI_OGF_LE_CONTROLLER_COMMANDS&0x3F)<<10)|(LLC_SPEC_5_1_HCI_OCF_HCI_LE_Set_Event_Mask&0x3FF))

#define HCI_RESET_COMMAND_OPCODE    (((LLC_SPEC_5_1_HCI_OGF_CONTROLLER_AND_BASEBAND_COMMANDS&0x3F)<<10)|(LLC_SPEC_5_1_HCI_OCF_HCI_Reset&0x3FF))
const uint8_t hciResetCommandData[] = 
{
    HCI_PACKET_TYPE_COMMAND,
    (HCI_RESET_COMMAND_OPCODE)&0xFF,
    ((HCI_RESET_COMMAND_OPCODE)>>8)&0xFF,
    0
};


const uint8_t hciHardwareErrorEventData[] = 
{
    HCI_PACKET_TYPE_EVENT,
    LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Hardware_Error,
    1,
    0,//Hardware_Code
};


static uint32_t hciTxTaskCb[osRtxThreadCbSize / 4U] __attribute__((aligned(4)));
static uint64_t hciTxTaskStack[(HCI_TX_TASK_STACK_SIZE) / 8U];
osThreadId_t hciTxTaskId;
osMessageQueueId_t hciTxTaskMsgQueueId;
static uint32_t hciTxTaskMsgQueueCb[osRtxMessageQueueCbSize / 4U];
static uint32_t hciTxTaskMsgQueueMem[osRtxMessageQueueMemSize(HCI_TX_TASK_MSG_COUNT, sizeof(stHciTaskMsg_t)) / 4U];

#define HCI_RX_TASK_FLAG       (0x01)
static uint32_t hciRxTaskCb[osRtxThreadCbSize / 4U] __attribute__((aligned(4)));
static uint64_t hciRxTaskStack[(HCI_RX_TASK_STACK_SIZE) / 8U];
osThreadId_t hciRxTaskId;


static uint8_t hciUartRxBuffer[(HCI_MSG_DATA_MAX_SIZE)*4];
static volatile uint16_t hciUartReadPos = 0;
static volatile uint16_t hciUartWritePos = 0;


////global msg struct to reduce task stack
static uint8_t hciProcessBuffer[sizeof(hciUartRxBuffer)];
static stHciTaskMsg_t hciTxTaskMsg;
static stHciTaskMsg_t hciHciHardwareErrorEventMsg;
static stHciTaskMsg_t hciReportAclDataMsg;
////


//invoked in rx task
void hci_transport_layer_add_hci_hardware_error_event_to_tx_queue(void)
{
    stHciTaskMsg_t* pstMsg = &hciHciHardwareErrorEventMsg;
    memcpy(pstMsg->pu8Data, hciHardwareErrorEventData, sizeof(hciHardwareErrorEventData));
    pstMsg->u16DataSize = sizeof(hciHardwareErrorEventData);
    
    osMessageQueuePut(hciTxTaskMsgQueueId, pstMsg, 0, osWaitForever);
}



static void hci_tx_task(void *argument)
{
    osStatus_t status;
    stHciTaskMsg_t* pstMsg = &hciTxTaskMsg;
    for (;;)
    {
        status = osMessageQueueGet(hciTxTaskMsgQueueId, pstMsg, NULL, osWaitForever);
        if (osOK != status)
        {
            continue;
        }
        if ((0 == pstMsg->u16DataSize) || (pstMsg->u16DataSize > HCI_MSG_DATA_MAX_SIZE))
        {
            continue;
        }
        patch_hw_uart_transmit(UART_HANDLE_HCI, hciTxTaskMsg.pu8Data, hciTxTaskMsg.u16DataSize);
    }
}

//#define OPEN_FOR_HCI_GEN_CASE 1
#ifdef OPEN_FOR_HCI_GEN_CASE  
uint16_t g_u16OpCode =0;
uint8_t g_bLeSetAdvParam =0;
uint8_t g_bLeSetExtAdvParam =0;
uint8_t g_bLeSetScanParam =0;
uint8_t g_bLeSetExtScanParam =0;
#endif
static void hci_command_packet_process(uint8_t *pu8Packet, uint16_t u16PacketSize)
{
    uint16_t u16OpCode = rom_little_endian_read_16(pu8Packet, 0);
    
    uint8_t OGF = (u16OpCode>>10)&0x3F;
    uint16_t OCF = (u16OpCode & 0x3FF);
    uint8_t Parameter_Total_Length = pu8Packet[2];
    uint8_t* Parameters = &pu8Packet[3];
    
    
    PRINTF("COMMAND OGF:0x%02x OCF:0x%04x\n", OGF, OCF);
    
    ////intercept HCI_Reset
    if ((LLC_SPEC_5_1_HCI_OGF_CONTROLLER_AND_BASEBAND_COMMANDS == OGF)
        && (LLC_SPEC_5_1_HCI_OCF_HCI_Reset == OCF))
    {

    #if APP_DEBUG_ENABLED
        PRINTF("HCI_Reset\n");
        app_debug_printf();
        rom_delay_ms(10);
    #endif
    #ifdef OPEN_FOR_HCI_GEN_CASE  
          g_u16OpCode =0;
          g_bLeSetAdvParam =0;
          g_bLeSetExtAdvParam =0;
          g_bLeSetScanParam =0;
          g_bLeSetExtScanParam =0;
     #endif   
        //reset system
        rom_hw_crg_system_reset();
        for(;;);
    }
    else
    {
#ifdef OPEN_FOR_HCI_GEN_CASE        
        g_u16OpCode =u16OpCode;
        uint8_t Event_Parameters[4] = 
        {
            //Num_HCI_Command_Packets
            1,
            
            //Command_Opcode
            u16OpCode&0xFF,
            ((u16OpCode)>>8)&0xFF,
            
            //Status
            LLC_SPEC_5_1_ERROR_CODE_COMMAND_DISALLOWED,
        };
        uint8_t Event_status_p[4] = 
            {
                //Status
                LLC_SPEC_5_1_ERROR_CODE_COMMAND_DISALLOWED,
                //Num_HCI_Command_Packets
                1,
                
                //Command_Opcode
                u16OpCode&0xFF,
                ((u16OpCode)>>8)&0xFF,
                
                
            };
        if(g_bLeSetAdvParam && ((0x2036 <= u16OpCode && u16OpCode<= 0x2040)||(0x205d == u16OpCode)||(0x205c == u16OpCode)))
            {
         
                hci_transport_layer_report_event(LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Complete, sizeof(Event_Parameters), Event_Parameters);
                return;
            } 
           else if(g_bLeSetExtAdvParam && ((0x2006 <= u16OpCode && u16OpCode<= 0x200A)))
            {
               
         
                hci_transport_layer_report_event(LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Complete, sizeof(Event_Parameters), Event_Parameters);
                return;
            }       
            else if(g_bLeSetScanParam && ((0x2041 <= u16OpCode && u16OpCode<= 0x204A)))
            {
                
                if(0x2043 == u16OpCode)
                {
                    
                   hci_transport_layer_report_event(LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Status, sizeof(Event_status_p), Event_status_p);
                    return; 
                }
         
                hci_transport_layer_report_event(LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Complete , sizeof(Event_Parameters), Event_Parameters);
                return;
            } 
            else if(g_bLeSetExtScanParam && ((0x200B <= u16OpCode && u16OpCode<= 0x200D)))
            {
                 if(0x200d == u16OpCode)
                {
                    
                   hci_transport_layer_report_event(LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Status, sizeof(Event_status_p), Event_status_p);
                    return; 
                }
               
         
                hci_transport_layer_report_event(LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Complete, sizeof(Event_Parameters), Event_Parameters);
                return;
            }                 
        if(0x2006 == u16OpCode)
        {
            g_bLeSetAdvParam = 1;
        }
        else if(0x2036 == u16OpCode)
        {
            g_bLeSetExtAdvParam = 1;
        }
        else if(0x200B == u16OpCode)
        {
            g_bLeSetScanParam = 1;
        }
        else if(0x2041 == u16OpCode)
        {
            g_bLeSetExtScanParam = 1;
        } 
        if(0x201f == u16OpCode)
        {
            uint8_t status_p[6] = 
            {
                
                1,
                
                //Command_Opcode
                u16OpCode&0xFF,
                ((u16OpCode)>>8)&0xFF,
                //Status
                1,0,0
                //Num_HCI_Command_Packets
                
                
            };
           hci_transport_layer_report_event(LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Complete, sizeof(status_p), status_p);
            return; 
        }
#endif        
        rom_hci_host_send_command_packet(OGF, OCF, Parameter_Total_Length, Parameters);
    }
}


static bool hci_acl_data_packet_process(uint8_t *pu8Packet, uint16_t u16PacketSize)
{
    
    uint16_t u16Header = rom_little_endian_read_16(pu8Packet, 0);
    
    uint16_t Handle = u16Header&0xFFF;
    uint8_t Packet_Boundary_Flag = (u16Header>>12)&0x3;
    uint8_t Broadcast_Flag = (u16Header>>14)&0x3;
    uint16_t Data_Total_Length = rom_little_endian_read_16(pu8Packet, 2);
    uint8_t* Data = &pu8Packet[4];
    
    PRINTF("ACL Handle:0x%04x Data_Total_Length:%u\n", Handle, Data_Total_Length);
    
    return rom_hci_host_send_acl_data(Handle, Packet_Boundary_Flag, Broadcast_Flag, Data_Total_Length, Data);
}

static uint16_t hci_rx_buffer_process(uint8_t *pu8RxBuffer, uint16_t u16RxSize, bool* pbWaitMoreData)
{

    if (0 == u16RxSize)
    {
        *pbWaitMoreData = true;
        return 0;
    }
    
#if 1
    PRINTF("hci_rx_buffer_process - ");
    uint32_t i;
    for(i = 0; i < u16RxSize; i++)
    {
        PRINTF("%02x ", pu8RxBuffer[i]);
    }
    PRINTF("\n\n");
#endif
    
    EN_HCI_PACKET_TYPE_T enumPacketType = pu8RxBuffer[0];
    uint8_t *pu8Packet = &(pu8RxBuffer[1]);
    uint16_t u16PacketReceivedSize = u16RxSize - 1;
    
    switch(enumPacketType)
    {
        case HCI_PACKET_TYPE_COMMAND:
        {
            if (u16RxSize < 3)
            {
                //keep and wait more data
                *pbWaitMoreData = true;
                return 0;
            }
            
            uint8_t Parameter_Total_Length = pu8Packet[2];
            uint16_t u16PacketSize = Parameter_Total_Length + 3;
            
            if (u16PacketSize > u16PacketReceivedSize)
            {
                //keep and wait more data
                *pbWaitMoreData = true;
                return 0;
            }
            
            hci_command_packet_process(pu8Packet, u16PacketSize);
            return u16PacketSize + 1;//+1 type
        }
            break;
        
        case HCI_PACKET_TYPE_ACL_DATA:
        {
            if (u16RxSize < 4)
            {
                //keep and wait more data
                *pbWaitMoreData = true;
                return 0;
            }
            
            uint16_t Data_Totol_Length = rom_little_endian_read_16(pu8Packet, 2);
            uint16_t u16PacketSize = Data_Totol_Length + 4;
            
            if (u16PacketSize > u16PacketReceivedSize)
            {
                //keep and wait more data
                *pbWaitMoreData = true;
                return 0;
            }
            
            if (hci_acl_data_packet_process(pu8Packet, u16PacketSize))
            {
                *pbWaitMoreData = false;
                return u16PacketSize + 1;//+1 type
            }
            else
            {
                //repeat
                *pbWaitMoreData = false;
                return 0;
            }
        }
            break;
        
        case HCI_PACKET_TYPE_SYNCHRONOUS_DATA:
        {
            if (u16RxSize < 3)
            {
                //keep and wait more data
                *pbWaitMoreData = true;
                return 0;
            }
            
            uint8_t Data_Totol_Length = pu8Packet[2];
            uint16_t u16PacketSize = Data_Totol_Length + 3;
            
            if (u16PacketSize > u16PacketReceivedSize)
            {
                //keep and wait more data
                *pbWaitMoreData = true;
                return 0;
            }
            
            //unsupported type, discard packet
            *pbWaitMoreData = false;
            return u16PacketSize + 1;//+1 type
        }
            break;
        
        case HCI_PACKET_TYPE_EVENT:
        default:
        {
            PRINTF("RX PACKET ERROR at line:%u\n", __LINE__);
            //try re-sync
            hci_transport_layer_add_hci_hardware_error_event_to_tx_queue();
            *pbWaitMoreData = false;
            return u16RxSize;
        }
            break;
    }
}


static void hci_rx_task(void *argument)
{
    bool bWaitMoreData = false;
    for (;;)
    {
        if (bWaitMoreData)
        {
            osThreadFlagsWait(HCI_RX_TASK_FLAG, 0, osWaitForever);
        }
        else
        {
            osThreadYield();
        }
        
        bWaitMoreData = false;
        
        uint32_t u32Primask = __get_PRIMASK();
        __disable_irq();
        uint16_t u16ReadPos = hciUartReadPos;
        uint16_t u16WritePos = hciUartWritePos;
        __set_PRIMASK(u32Primask);
        
        if (u16ReadPos == u16WritePos)
        {
            //nothing recevied
            bWaitMoreData = true;
            continue;
        }
        
        
        uint8_t* pu8RxBuffer = hciProcessBuffer;
        uint16_t u16RxSize;
        if (u16ReadPos < u16WritePos)
        {
            //  ___|01|02|03|04|...|xx|___
            u16RxSize = u16WritePos - u16ReadPos;
            memcpy(pu8RxBuffer, &hciUartRxBuffer[u16ReadPos], u16RxSize);
        }
        else
        {
            //  |04|...|xx|______|01|02|03
            memcpy(pu8RxBuffer, &hciUartRxBuffer[u16ReadPos], sizeof(hciUartRxBuffer) - u16ReadPos);
            memcpy(&pu8RxBuffer[sizeof(hciUartRxBuffer) - u16ReadPos], hciUartRxBuffer, u16WritePos);
            u16RxSize = sizeof(hciUartRxBuffer) - u16ReadPos + u16WritePos;
        }
        
        uint16_t u16ProcessedSize = hci_rx_buffer_process(pu8RxBuffer, u16RxSize, &bWaitMoreData);
        if (0 == u16ProcessedSize)
        {
            //keep all rx data
        }
        else if (u16ProcessedSize >= u16RxSize)
        {
            //discard all rx data
            __disable_irq();
            hciUartReadPos = u16WritePos;
            __set_PRIMASK(u32Primask);
        }
        else
        {
            //discard part of rx data
            
            __disable_irq();
            if (u16ReadPos + u16ProcessedSize < sizeof(hciUartRxBuffer))
            {
                hciUartReadPos = u16ReadPos + u16ProcessedSize;
            }
            else
            {
                hciUartReadPos = (uint32_t)u16ReadPos + u16ProcessedSize - sizeof(hciUartRxBuffer);
            }
            __set_PRIMASK(u32Primask);
            
        }
        
        //after data process, if uart interrupt disabled, enable it and trig int
        if (0 == UART_HANDLE_HCI->UART_INT_EN)
        {
            UART_HANDLE_HCI->UART_INT_EN = UART_INTERRUPT_FLAGS;
            NVIC_SetPendingIRQ(UART0_IRQ);
        }
    }
}



bool hci_transport_layer_task_init(void)
{
    hciUartReadPos = 0;
    hciUartWritePos = 0;
    
    const osMessageQueueAttr_t hciTxTaskMsgQueueAttr =
    {
        .name = "hci_tx_task_msg_queue",
        .attr_bits = 0,
        .cb_mem = hciTxTaskMsgQueueCb,
        .cb_size = sizeof(hciTxTaskMsgQueueCb),
        .mq_mem = hciTxTaskMsgQueueMem,
        .mq_size = sizeof(hciTxTaskMsgQueueMem),
    };
    hciTxTaskMsgQueueId = osMessageQueueNew(HCI_TX_TASK_MSG_COUNT, sizeof(stHciTaskMsg_t), &hciTxTaskMsgQueueAttr);
    if (NULL == hciTxTaskMsgQueueId)
    {
        return false;
    }
    
    const osThreadAttr_t hciTxTaskAttr =
    {
        .name = "hci_tx_task",
        .attr_bits = osThreadJoinable,
        .cb_mem = &hciTxTaskCb,
        .cb_size = sizeof(hciTxTaskCb),
        .stack_mem = hciTxTaskStack,
        .stack_size = sizeof(hciTxTaskStack),
        .priority = osPriorityAboveNormal,
    };
    hciTxTaskId = osThreadNew(hci_tx_task, NULL, &hciTxTaskAttr);
    if (NULL == hciTxTaskId)
    {
        return false;
    }
    
    const osThreadAttr_t hciRxTaskAttr =
    {
        .name = "hci_rx_task",
        .attr_bits = osThreadJoinable,
        .cb_mem = &hciRxTaskCb,
        .cb_size = sizeof(hciRxTaskCb),
        .stack_mem = hciRxTaskStack,
        .stack_size = sizeof(hciRxTaskStack),
        .priority = osPriorityAboveNormal,
    };
    hciRxTaskId = osThreadNew(hci_rx_task, NULL, &hciRxTaskAttr);
    if (NULL == hciRxTaskId)
    {
        return false;
    }
    
    
    return true;
}




void UART0_IRQ_Handler(void)
{
    uint16_t u16IntFlags;
    rom_hw_uart_get_interrupt_flag(UART_HANDLE_HCI, &u16IntFlags);
    rom_hw_uart_clear_interrupt_flag(UART_HANDLE_HCI, u16IntFlags);
    
    //rx to buffer and detect overflow
    uint8_t u8UartRxFifoCnt;
    rom_hw_uart_get_rxfifo_cnt(UART_HANDLE_HCI, &u8UartRxFifoCnt);
    while(u8UartRxFifoCnt > 0)
    {
        uint16_t u16ExpectedHciUartWritePosNew = hciUartWritePos + 1;
        if (u16ExpectedHciUartWritePosNew >= sizeof(hciUartRxBuffer))
        {
            u16ExpectedHciUartWritePosNew = 0;
        }
        if (u16ExpectedHciUartWritePosNew == hciUartReadPos)
        {
            //hciUartRxBuffer overflow!
            //disable uart interrupts and wait for data process
            UART_HANDLE_HCI->UART_INT_EN = 0;
            return;
        }
        else
        {
            rom_hw_uart_get_byte(UART_HANDLE_HCI, &hciUartRxBuffer[hciUartWritePos]);
            hciUartWritePos = u16ExpectedHciUartWritePosNew;
            
            rom_hw_uart_get_rxfifo_cnt(UART_HANDLE_HCI, &u8UartRxFifoCnt);
        }
    }
    
    if (NULL != hciRxTaskId)
    {
        osThreadFlagsSet(hciRxTaskId, HCI_RX_TASK_FLAG);
    }
}


bool hci_transport_layer_uart_init(void)
{
    EN_ERR_STA_T enRet;
    
    
    enRet = rom_hw_gpio_set_pin_pid( GPIO_PORT_HCI_TX, GPIO_PIN_HCI_TX, GPIO_PID_HCI_UART_TX );
    if (ERR_STA_OK != enRet)
    {
        return false;
    }
    
    enRet = rom_hw_gpio_set_pin_pid( GPIO_PORT_HCI_RX, GPIO_PIN_HCI_RX, GPIO_PID_HCI_UART_RX );
    if (ERR_STA_OK != enRet)
    {
        return false;
    }
    
    enRet = rom_hw_gpio_set_pin_pull_mode( GPIO_PORT_HCI_RX, GPIO_PIN_HCI_RX, GPIO_PULL_UP );
    if (ERR_STA_OK != enRet)
    {
        return false;
    }
    
    enRet = rom_hw_gpio_set_pin_pid( GPIO_PORT_HCI_RTS, GPIO_PIN_HCI_RTS, GPIO_PID_HCI_UART_RTS );
    if (ERR_STA_OK != enRet)
    {
        return false;
    }
    
    enRet = rom_hw_gpio_set_pin_pid( GPIO_PORT_HCI_CTS, GPIO_PIN_HCI_CTS, GPIO_PID_HCI_UART_CTS );
    if (ERR_STA_OK != enRet)
    {
        return false;
    }
    
    enRet = rom_hw_gpio_set_pin_pull_mode( GPIO_PORT_HCI_CTS, GPIO_PIN_HCI_CTS, GPIO_PULL_DOWN );
    if (ERR_STA_OK != enRet)
    {
        return false;
    }
    
    
    
    rom_hw_sys_ctrl_enable_peri_int(SYS_CTRL_CP, UART0_IRQ);
    NVIC_ClearPendingIRQ(UART0_IRQ);
    NVIC_SetPriority(UART0_IRQ, 3);
    NVIC_EnableIRQ(UART0_IRQ);
    
    
    enRet = rom_hw_crg_enable_clk_gate ( CRG_CLK_GATE_HCI_UART );
    if (ERR_STA_OK != enRet)
    {
        return false;
    }
    
    stUartInit_t stUartInit = 
    {
        .u32UartBaudRate = UART_BPS_HCI,
        .unUartCfg = ((1 & UART_TX_FIFO_THLD_MSK) << UART_TX_FIFO_THLD_SHIFT)
                      |((1 & UART_RX_FIFO_THLD_MSK) << UART_RX_FIFO_THLD_SHIFT)
                      |(UART_STOP_SIZE_1BIT << UART_STOP_SIZE_SHIFT)
                      |(UART_DATA_BITS_8 << UART_DATA_SIZE_SHIFT)
                      |((UART_PARITY_NONE & UART_PARITY_MODE_MSK) << UART_PARITY_MODE_SHIFT)
                      |(UART_LITTLE_ENDIAN << UART_ENDIAN_MODE_SHIFT)
                      |(UART_LINEBREAK_DISABLE << UART_LINE_BREAK_EN_SHIFT)
                      |(UART_FLOW_ENABLE << UART_FLOW_CTRL_EN_SHIFT)
                      |((8 & UART_RTS_THLD_MSK) << UART_RTS_THLD_SHIFT)
                      |(UART_DISCARD_DISABLE << UART_ERR_DISCARD_EN_SHIFT),
    };
    enRet = rom_hw_uart_init( UART_HANDLE_HCI, &stUartInit );
    if (ERR_STA_OK != enRet)
    {
        return false;
    }
    enRet = rom_hw_uart_enable_interrupt(UART_HANDLE_HCI, UART_INTERRUPT_FLAGS);
    if (ERR_STA_OK != enRet)
    {
        return false;
    }
    
    return true;
}


bool hci_transport_layer_init(void)
{
    
    if  (!hci_transport_layer_task_init())
    {
        return false;
    }
    
    if (!hci_transport_layer_uart_init())
    {
        return false;
    }
    
    return true;
}


void hci_transport_layer_on_hci_ready(void)
{
    uint16_t u16ResetFlags;
    if ( ERR_STA_OK == rom_hw_crg_get_reset_flag(&u16ResetFlags))
    {
        ////reset by software
        if (u16ResetFlags & CRG_SW_RST_FLAG)
        {
            //send Return parameters of HCI_Reset
            
            uint8_t Event_Parameters[4] = 
            {
                //Num_HCI_Command_Packets
                1,
                
                //Command_Opcode
                (HCI_RESET_COMMAND_OPCODE)&0xFF,
                ((HCI_RESET_COMMAND_OPCODE)>>8)&0xFF,
                
                //Status
                LLC_SPEC_5_1_ERROR_CODE_SUCCESS,
            };
            PRINTF("send hci reset evt\n");
            hci_transport_layer_report_event(LLC_SPEC_5_1_HCI_EVENT_CODE_HCI_Command_Complete, sizeof(Event_Parameters), Event_Parameters);
           
        }
    }
}

uint16_t hci_transport_layer_get_event_parameter_max_length(void)
{
    if (HCI_MSG_DATA_MAX_SIZE <= 3)
    {
        return 0;
    }
    
    uint16_t u16ParameterMaxLength = HCI_MSG_DATA_MAX_SIZE - 3;
    if (u16ParameterMaxLength > 255)
    {
        return 255;
    }
    else
    {
        return u16ParameterMaxLength;
    }
}


bool hci_transport_layer_report_event(uint8_t Event_Code, uint8_t Parameter_Total_Length, uint8_t* Event_Parameter)
{
#if APP_DEBUG_ENABLED
    PRINTF("REPORT EVENT - Event_Code:0x%04x\nEvent_Parameter:", 
        Event_Code);
    uint32_t i;
    for(i = 0; i < Parameter_Total_Length; i++)
    {
        PRINTF("%02x ", Event_Parameter[i]);
    }
    PRINTF("\n\n");
#endif
    
    
    
    if (3 + Parameter_Total_Length > HCI_MSG_DATA_MAX_SIZE)
    {
        PRINTF("REPORT EVENT ERR at line:%u\n", __LINE__);
        return false;
    }
    
    if ((0 != Parameter_Total_Length) && (NULL == Event_Parameter))
    {
        PRINTF("REPORT EVENT ERR at line:%u\n", __LINE__);
        return false;
    }
    
    if (NULL == hciTxTaskMsgQueueId)
    {
        PRINTF("REPORT EVENT ERR at line:%u\n", __LINE__);
        return false;
    }
    
    stHciTaskMsg_t stMsg;
    stMsg.pu8Data[0] = HCI_PACKET_TYPE_EVENT;
    stMsg.pu8Data[1] = Event_Code;
    stMsg.pu8Data[2] = Parameter_Total_Length;
    memcpy(&stMsg.pu8Data[3], Event_Parameter, Parameter_Total_Length);
    stMsg.u16DataSize = 3 + Parameter_Total_Length;
    
    //may run in irq
    osStatus_t status = osMessageQueuePut(hciTxTaskMsgQueueId, &stMsg, 0, 0);
    
    if (osOK == status)
    {
        return true;
    }
    else
    {
        PRINTF("REPORT EVENT ERR - status:%d\n", status);
        return false;
    }
}



bool hci_transport_layer_report_acl_data(uint16_t Handle, uint8_t Packet_Boundary_Flag, uint8_t Broadcast_Flag, uint16_t Data_Total_Length, uint8_t* Data)
{
    
#if APP_DEBUG_ENABLED
    PRINTF("REPORT ACL - Handle:0x%04x Packet_Boundary_Flag:0x%02x Broadcast_Flag:0x%02x\nData:", 
        Handle, Packet_Boundary_Flag, Broadcast_Flag);
    uint32_t i;
    for(i = 0; i < Data_Total_Length; i++)
    {
        PRINTF("%02x ", Data[i]);
    }
    PRINTF("\n\n");
#endif
    
    if (5 + Data_Total_Length > HCI_MSG_DATA_MAX_SIZE)
    {
        return false;
    }
    
    if ((0 != Data_Total_Length) && (NULL == Data))
    {
        return false;
    }
    
    if (NULL == hciTxTaskMsgQueueId)
    {
        return false;
    }
    if(0x10  == Packet_Boundary_Flag)
    {
        Packet_Boundary_Flag =2;
    }
    
    stHciTaskMsg_t* pstMsg = &hciReportAclDataMsg;
    pstMsg->pu8Data[0] = HCI_PACKET_TYPE_ACL_DATA;
    
    uint16_t u16Header = (Handle & 0xFFF)|(((uint16_t)(Packet_Boundary_Flag&0x3))<<12)|(((uint16_t)(Broadcast_Flag&0x3))<<14);
    rom_little_endian_store_16(pstMsg->pu8Data, 1, u16Header);
    rom_little_endian_store_16(pstMsg->pu8Data, 3, Data_Total_Length);
    memcpy(&pstMsg->pu8Data[5], Data, Data_Total_Length);
    pstMsg->u16DataSize = 5 + Data_Total_Length;
    
    osStatus_t status = osMessageQueuePut(hciTxTaskMsgQueueId, pstMsg, 0, osWaitForever);
    
    if (osOK == status)
    {
        return true;
    }
    else
    {
        PRINTF("REPORT ACL - status:0x%08x\n", status);
        return false;
    }
}
