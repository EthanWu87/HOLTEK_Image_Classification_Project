/*************************************************************************************************************
 * @file    extended_controller_interface.h
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
#ifndef EXTENDED_CONTROLLER_INTERFACE_H
#define EXTENDED_CONTROLLER_INTERFACE_H

////Extended Advertising
void rom_controller_command_HCI_LE_Set_Advertising_Set_Random_Address(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Extended_Advertising_Parameters(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_VENDOR_Set_Extended_Advertising_Parameters(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Extended_Advertising_Data(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Extended_Scan_Response_Data(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Set_Extended_Advertising_Enable(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_Maximum_Advertising_Data_Length(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Read_Number_of_Supported_Advertising_Sets(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Remove_Advertising_Set(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_command_HCI_LE_Clear_Advertising_Sets(uint8_t Parameter_Total_Length, uint8_t* Parameters);
void rom_controller_event_HCI_LE_Advertising_Set_Terminated(uint8_t Status, uint8_t Advertising_Handle, uint16_t Connection_Handle, uint8_t Num_Completed_Extended_Advertising_Events);
void rom_controller_event_HCI_LE_Scan_Request_Received(uint8_t Advertising_Handle, uint8_t Scanner_Address_Type, uint8_t Scanner_Address[6]);
////

////Extended Scan
void rom_controller_return_parameters_HCI_LE_Set_Extended_Scan_Enable(uint8_t Status);
void rom_controller_event_HCI_LE_Extended_Advertising_Report(uint8_t Parameter_Total_Length, uint8_t* Event_Parameter);
void rom_controller_event_HCI_LE_Scan_Timeout(void);
////


void extended_controller_interface(void);
bool extended_controller_interface_process_command_packet(uint8_t OGF, uint16_t OCF, uint8_t Parameter_Total_Length, uint8_t* Parameters);

#endif
