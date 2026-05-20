/*************************************************************************************************************
 * @file    controller_interface.h
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
#ifndef CONTROLLER_INTERFACE_H
#define CONTROLLER_INTERFACE_H



////todo : move event impl to another file

////for hci
bool rom_controller_interface_process_command_packet(uint8_t OGF, uint16_t OCF, uint8_t Parameter_Total_Length, uint8_t* Parameters);
bool rom_controller_interface_process_acl_data(uint16_t Handle, uint8_t Packet_Boundary_Flag, uint8_t Broadcast_Flag, uint16_t Data_Total_Length, uint8_t* Data);

////for llc

void rom_controller_event_HCI_Command_Complete(uint8_t OGF, uint16_t OCF, uint8_t Return_Parameters_Size, uint8_t* Return_Parameters);

void rom_controller_event_HCI_Command_Status(uint8_t OGF, uint16_t OCF, uint8_t Status);

void rom_controller_event_HCI_Number_Of_Completed_Packets(uint16_t Connection_Handle, uint16_t Num_Of_Completed_Packets);
////


////encryption
void rom_controller_command_HCI_LE_Start_Encryption(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_LE_Long_Term_Key_Request(uint16_t Connection_Handle, uint8_t Random_Number[8], uint16_t Encrypted_Diversifier);
void rom_controller_command_HCI_LE_Long_Term_Key_Request_Negative_Reply(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Long_Term_Key_Request_Reply(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_Encryption_Change(uint8_t Status, uint16_t Connection_Handle, uint8_t Encryption_Enabled);
void rom_controller_event_HCI_Encryption_Key_Refresh_Complete(uint8_t Status, uint16_t Connection_Handle);
////


////connection
void rom_controller_command_HCI_LE_Create_Connection(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Create_Connection_Cancel(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_LE_Connection_Complete(uint8_t Status, uint16_t Connection_Handle, uint8_t Role, uint8_t Peer_Address_Type, uint8_t Peer_Address[6],
    uint16_t Conn_Interval, uint16_t Conn_Latency, uint16_t Supervision_Timeout, uint8_t Master_Clock_Accuracy);
void rom_controller_event_HCI_LE_Channel_Selection_Algorithm(uint16_t Connection_Handle, uint8_t Channel_Selection_Algorithm);
void rom_controller_event_HCI_LE_Enhanced_Connection_Complete(uint8_t Status, uint16_t Connection_Handle, uint8_t Role, uint8_t Peer_Address_Type, uint8_t Peer_Address[6],
    uint8_t Local_Resolvable_Private_Address[6],uint8_t Peer_Resolvable_Private_Address[6],uint16_t Conn_Interval, uint16_t Conn_Latency, uint16_t Supervision_Timeout, uint8_t Master_Clock_Accuracy);
void rom_controller_command_HCI_Disconnect(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_Disconnection_Complete(uint8_t Status, uint16_t Connection_Handle, uint8_t Reason);
////


////connection update
void rom_controller_command_HCI_LE_Connection_Update(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_LE_Connection_Update_Complete(uint8_t Status, uint16_t Connection_Handle, uint16_t Conn_Interval, uint16_t Conn_Latency, uint16_t Supervision_Timeout);
////


////data length
void rom_controller_command_HCI_LE_Set_Data_Length(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_LE_Data_Length_Change(uint16_t Connection_Handle, uint16_t MaxTxOctets, uint16_t MaxTxTime, uint16_t MaxRxOctets, uint16_t MaxRxTime);
////

////phy update
void rom_controller_command_HCI_LE_Set_PHY(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_LE_PHY_Update_Complete(uint8_t Status, uint16_t Connection_Handle, uint8_t TX_PHY, uint8_t RX_PHY);
////


////advertising
void rom_controller_command_HCI_LE_Set_Advertising_Parameters(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Advertising_Data(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Scan_Response_Data(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Advertising_Enable(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////


////white list
void rom_controller_command_HCI_LE_Read_White_List_Size(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Clear_White_List(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Add_Device_To_White_List(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Remove_Device_From_White_List(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////random address
void rom_controller_command_HCI_LE_Set_Random_Address(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////scan
void rom_controller_command_HCI_LE_Set_Scan_Parameters(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Scan_Enable(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_LE_Set_Scan_Enable(uint8_t u8Status);
void rom_controller_event_HCI_LE_Advertising_Report(uint8_t Parameter_Total_Length, uint8_t* Event_Parameter);
////


////version
void rom_controller_command_HCI_Read_Remote_Version_Information(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_Read_Remote_Version_Information_Complete(uint8_t Status, uint16_t Connection_Handle, uint8_t Version, 
    uint16_t Manufacturer_Name, uint16_t Subversion);
////

////feature exchange
void rom_controller_command_HCI_LE_Read_Remote_Features(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_LE_Read_Remote_Features_Complete(uint8_t Status, uint16_t Connection_Handle, uint64_t LE_Features);
////

////privacy
void rom_controller_command_HCI_LE_Read_Resolving_List_Size(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Add_Device_To_Resolving_List(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Remove_Device_From_Resolving_List(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Clear_Resolving_List(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Address_Resolution_Enable(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Privacy_Mode(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Resolvable_Private_Address_Timeout(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////RSSI
void rom_controller_command_HCI_Read_RSSI(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////Read Channel Map
void rom_controller_command_HCI_LE_Read_Channel_Map(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////vendor commands below

//// public addr
void rom_controller_command_VENDOR_Set_Public_Address(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////advertising
void rom_controller_command_VENDOR_Set_Advertising_Parameters(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_VENDOR_Set_Advertising_Data(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_VENDOR_Set_Scan_Response_Data(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_VENDOR_Set_Advertising_Enable(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////scan
void rom_controller_command_VENDOR_Set_Scan_Parameters(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////initiator
void rom_controller_command_VENDOR_Create_Connection(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////channel map update
void rom_controller_command_VENDOR_Update_Channel_Map(uint8_t Parameter_Total_Length, uint8_t* Parameters);
////

////vendor events below

////connection
void rom_controller_event_VENDOR_Connection_Complete(uint8_t Status, uint16_t Connection_Handle, uint8_t Role, uint8_t Peer_Address_Type, uint8_t Peer_Address[6],
    uint16_t Conn_Interval, uint16_t Conn_Latency, uint16_t Supervision_Timeout, uint8_t Master_Clock_Accuracy, uint8_t Own_Address_Type, uint8_t Own_Address[6],uint8_t Own_Address_Be_RPA,uint8_t Peer_RPA_Resoluted,uint8_t Peer_Identify_Address_Type,uint8_t Peer_Identify_Address[6]);
////


void rom_controller_command_HCI_Set_Event_Mask(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_Read_Local_Version_Information(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_Read_Local_Supported_Commands(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_Read_Local_Supported_Features(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_Read_BD_ADDR(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_Buffer_Size(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_Supported_States(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_Local_Supported_Features(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Host_Channel_Classification(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Encrypt(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Rand(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_Transmit_Power(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_Advertising_Physical_Channel_Tx_Power(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Event_Mask(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_Suggested_Default_Data_Length(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Write_Suggested_Default_Data_Length(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_Maximum_Data_Length(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_PHY(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Default_PHY(uint8_t Parameter_Total_Length, uint8_t* Parameters);


#endif
