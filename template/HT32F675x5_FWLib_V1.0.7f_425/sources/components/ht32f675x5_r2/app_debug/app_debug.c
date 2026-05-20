/*************************************************************************************************************
 * @file    app_debug.c
 * @version V1.0
 * @date    2020-05-07
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


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_crg.h"
#include "hw_gpio.h"
#include "hw_uart.h"

#include "app_cfg.h"
#include "app_debug.h"

/**
 * @brief  Local variables.
 */
static uint32_t m_u32DebugIoTx;
static uint32_t m_u32DebugUartBps;
static uint16_t m_u16DebugTxIdx;
static uint16_t m_u16DebugRxIdx;

static stUART_Handle_t *m_pstDebugUartHandle;
static stGPIO_Handle_t *m_pstDebugGpioHandle;
static stDebugBuf_t    *m_pstDebugBuf = NULL;

/**
 * @brief  App debug init.
 * @param  pstGPIO: GPIO handle, Should be PERI_GPIOA/GPIOB.
 * @param  enPin: The pin which would be set tx function.
 * @param  pstUART: UART handle, Should be PERI_UART0/PERI_UART1/PERI_UART2.
 * @param  u32BaudRate: Uart baudrate.
 * @param  pststDebugBuf: Point to app debug buf struct.
 * @return retuen status, @ref EN_HAL_STA_T.
 */
EN_ERR_STA_T app_debug_init(stGPIO_Handle_t *pstGPIO, uint32_t u32Pin, stUART_Handle_t *pstUART, uint32_t u32BaudRate,
                            stDebugBuf_t *pststDebugBuf)
{
    if ((!(IS_VALID_UART_HANDLE(pstUART))) || (!IS_VALID_GPIO_HANDLE(pstGPIO)))
    {
        return ERR_PARA_ERR;
    }

    m_pstDebugBuf = pststDebugBuf;

    if (NULL != m_pstDebugBuf)
    {
        m_u16DebugTxIdx = 0;
        m_u16DebugRxIdx = 0;
    }

    m_pstDebugUartHandle = pstUART;
    m_pstDebugGpioHandle = pstGPIO;
    m_u32DebugIoTx       = u32Pin;
    m_u32DebugUartBps    = (uint32_t)u32BaudRate;

    return app_debug_reinit();
}

/**
 * @brief  Set app debug io high impedance.
 */
void app_debug_deinit(void)
{
    rom_hw_gpio_set_pin_input_output(m_pstDebugGpioHandle, m_u32DebugIoTx, GPIO_MODE_IMPEDANCE);
    rom_hw_gpio_set_pin_pull_mode(m_pstDebugGpioHandle, m_u32DebugIoTx, GPIO_PULL_NONE);

    if (UART0 == m_pstDebugUartHandle)
    {
        rom_hw_crg_disable_clk_gate(CRG_UART0_CLK_GATE);
    }
    else if (UART1 == m_pstDebugUartHandle)
    {
        rom_hw_crg_disable_clk_gate(CRG_UART1_CLK_GATE);
    }
    else
    {
        rom_hw_crg_disable_clk_gate(CRG_UART2_CLK_GATE);
    }
}

/**
 * @brief  App debug reinit.
 * @return retuen status, @ref EN_HAL_STA_T.
 */
EN_ERR_STA_T app_debug_reinit(void)
{
    EN_ERR_STA_T enRet;
    stUartInit_t stUartInit;

    if (UART0 == m_pstDebugUartHandle)
    {
        rom_hw_crg_enable_clk_gate(CRG_UART0_CLK_GATE);
        enRet = rom_hw_gpio_set_pin_pid(m_pstDebugGpioHandle, m_u32DebugIoTx, PID_UART0_TXD);
    }
    else if (UART1 == m_pstDebugUartHandle)
    {
        rom_hw_crg_enable_clk_gate(CRG_UART1_CLK_GATE);
        enRet = rom_hw_gpio_set_pin_pid(m_pstDebugGpioHandle, m_u32DebugIoTx, PID_UART1_TXD);
    }
    else
    {
        rom_hw_crg_enable_clk_gate(CRG_UART2_CLK_GATE);
        enRet = rom_hw_gpio_set_pin_pid(m_pstDebugGpioHandle, m_u32DebugIoTx, PID_UART2_TXD);
    }
    ERR_RETURN_IF_ERROR(enRet);

    enRet = rom_hw_gpio_set_pin_pull_mode(m_pstDebugGpioHandle, m_u32DebugIoTx, GPIO_PULL_UP);
    ERR_RETURN_IF_ERROR(enRet);

    stUartInit.u32UartBaudRate = m_u32DebugUartBps;

    // TxFifoThld and RxFifoThld is 8, StopBit is 1, 8bit, no parity, little-ending
    stUartInit.unUartCfg.u32UartCfg = UART_INIT_DEFAULT(UART_PARITY_NONE);

    return rom_hw_uart_init(m_pstDebugUartHandle, &stUartInit);
}

/**
 * @brief  Check app debug is print done.
 * @return false(0) - app debug is working.
 * @return true(1)  - app debug is idle.
 */
bool app_debug_print_complete(void)
{
    if (NULL == m_pstDebugBuf)
    {
        return true;
    }

    return (m_u16DebugTxIdx == m_u16DebugRxIdx);
}

/**
 * @brief  Print all data by uart
 */
void app_debug_printf(void)
{
    if (NULL == m_pstDebugBuf)
    {
        return;
    }

    while (m_u16DebugTxIdx != m_u16DebugRxIdx)
    {
        rom_hw_uart_send_byte(m_pstDebugUartHandle, m_pstDebugBuf->pu8buf[m_u16DebugTxIdx]);

        m_u16DebugTxIdx++;
        if (m_u16DebugTxIdx >= m_pstDebugBuf->u16MaxLen)
        {
            m_u16DebugTxIdx = 0;
        }
    }
}

/**
 * @brief  Print hex string.
 * @param  pPreStr: Preamble string.
 * @param  pu8Buf: Data buffer.
 * @param  u16BufLen: Buffer length.
 */
void app_debug_printf_hex_string(char *pPreStr, const uint8_t *pu8Buf, uint16_t u16BufLen)
{
    uint16_t i;

    PRINTF("[%s][%d]:", pPreStr, u16BufLen);

    for (i = 0; i < u16BufLen; i++)
    {
        PRINTF(" %02X", pu8Buf[i]);
    }

    PRINTF("\n");
}

/**
 * @brief
 * @param  pre
 * @param  buff
 * @param  len
 */
void app_printf_dec(char *pre, const uint8_t *buff, uint16_t len)
{
    printf("[%s][%d]:", pre, len);
    for (int i = 0; i < len; i++)
    {
        printf(" %d", buff[i]);
    }
    printf("\n");
}

/**
 * @brief  Print char
 * @param  pre
 * @param  buff
 * @param  len
 */
void app_printf_char(char *pre, const char *buff, uint16_t len)
{
    printf("[%s][%d]:", pre, len);
    for (int i = 0; i < len; i++)
    {
        printf("%c", buff[i]);
    }
    printf("\n");
}

/**
 * @brief  printf function
 * @param  c
 * @param  f
 * @return c
 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
int fputc(int c, FILE *f)
{
    if (NULL == m_pstDebugBuf)
    {
        uint8_t data = c & 0xFF;

        rom_hw_uart_transmit( m_pstDebugUartHandle, &data, 1 );
    }
    else
    {
        m_pstDebugBuf->pu8buf[m_u16DebugRxIdx] = c;

        m_u16DebugRxIdx++;
        if (m_u16DebugRxIdx >= m_pstDebugBuf->u16MaxLen)
        {
            m_u16DebugRxIdx = 0;
        }
    }

    return c;
}
#elif defined (__GNUC__)
#include <sys/stat.h>

int _write(int fd, char *ptr, int len)
{
  int written = 0;

  if (fd == -1)
  {
    return 0;
  }
  /* Check for stdout and stderr
     (only necessary if FILE descriptors are enabled.)  */
  if (fd != 1 && fd != 2)
  {
    return -1;
  }

  for (int i = 0; i < len; i++)
  {
    if (NULL == m_pstDebugBuf)
    {
      // Write directly to UART
      if (rom_hw_uart_send_byte(m_pstDebugUartHandle, ptr[i] & 0xFF) != ERR_STA_OK)
      {
        // Handle error
        return -1;
      }
    }
    else
    {
      // Write to the debug buffer
      m_pstDebugBuf->pu8buf[m_u16DebugRxIdx] = ptr[i];

      m_u16DebugRxIdx++;
      if (m_u16DebugRxIdx >= m_pstDebugBuf->u16MaxLen)
      {
        m_u16DebugRxIdx = 0;
      }
    }
    written++;
  }

  return written;
}

int _isatty(int fd __attribute__ ((unused)))
{
  return 1;
}

int _close(int fd __attribute__ ((unused)))
{
  return -1;
}

int _lseek(int fd __attribute__ ((unused)), int ptr __attribute__ ((unused)), int dir __attribute__ ((unused)))
{
  return 0;
}

int _fstat(int fd __attribute__ ((unused)), struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _read(int fd __attribute__ ((unused)), char *ptr __attribute__ ((unused)), int len __attribute__ ((unused)))
{
  return 0;
}

int _getpid(void __attribute__ ((unused)))
{
  return 1;
}

int _kill(int pid __attribute__ ((unused)), int sig __attribute__ ((unused)))
{
  return -1;
}
#endif
