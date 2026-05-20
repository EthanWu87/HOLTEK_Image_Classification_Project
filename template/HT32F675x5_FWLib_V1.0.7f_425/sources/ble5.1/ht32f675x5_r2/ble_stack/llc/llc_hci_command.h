/*************************************************************************************************************
 * @file    llc_hci_command.h
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
#ifndef LLC_HCI_COMMAND_H
#define LLC_HCI_COMMAND_H

typedef struct
{
    uint8_t* pu8ParametersBuffer;
    uint16_t u16ParametersBufferSize;
    uint16_t u16OCF;
    uint8_t u8OGF;
    uint8_t u8ParameterTotalLength;
    bool bMemUsed;
    uint32_t u32Reserved;
} __attribute__((aligned(4)))
stLlcHciCommand_t;


bool rom_llc_hci_command_mem_init(stLlcHciCommand_t* pstLlcHciCommandMemBuffer, uint16_t u16ParametersBufferSize, uint8_t u8LlcHciCommandNum);

uint16_t rom_llc_hci_command_get_parameters_size(void);

uint8_t rom_llc_hci_command_get_num(void);

stLlcHciCommand_t* rom_llc_hci_command_alloc(void);

void rom_llc_hci_command_free(stLlcHciCommand_t* pstLlcHciCommand);


#endif
