/*************************************************************************************************************
 * @file    hw_dma.h
 * @version V1.1
 * @date    2022-01-13
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


#ifndef __HW_DMA_H__
#define __HW_DMA_H__

#ifdef __cplusplus
extern "C"
{
#endif

//=====================================================================================================================
// TYPEDEF
//=====================================================================================================================
typedef union
{
    uint32_t u32DMACfg;

    struct
    {
        uint32_t u16Length    : 16; /*!< The length of DMA data transfer. >*/
        uint32_t u8CircEn     : 1;  /*!< DMA work in circulation mode or not >*/
        uint32_t u8Priority   : 1;  /*!< DMA priority >*/
        uint32_t u8WorkMode   : 2;  /*!< DMA transfer mode >*/
        uint32_t u8DstSize    : 2;  /*!< DMA destination data bits wide >*/
        uint32_t u8DstIncEN   : 1;  /*!< DMA destination data address increase or not >*/
        uint32_t u8SrcSize    : 2;  /*!< DMA source data bits wide >*/
        uint32_t u8SrcIncEN   : 1;  /*!< DMA source data address increase or not >*/
        uint32_t u8StopCfg    : 1;  /*!<  >*/
        uint32_t u8PauseEn    : 1;  /*!< Pause DMA controller. >*/
        uint32_t u8Enable     : 1;  /*!< Enable/Disable DMA controller. >*/

    } stDmaCfg;

} unDmaCfg_t;

typedef union
{
    struct
    {
        EN_DMA_PERI_SEL_T enPeriID;

    } stPeriSel;

    struct
    {
        EN_DMA_PERI_SEL_T enSrcPeriID;    /*!< DMA Source Peripheral ID > */
        EN_DMA_PERI_SEL_T enDstPeriID;    /*!< DMA Dstination Peripheral ID > */

    } stPeri2PeriSel;

} unDmaPeriSel_t;

typedef struct
{
    uint32_t u32SrcAddr;
    uint32_t u32DstAddr;
    uint32_t u32TimeOut; /*!< DMA Timeout, unit: us > */
    unDmaCfg_t unCfg;
    unDmaPeriSel_t unPeriSel;

} stDmaInit_t, *pstDmaInit_t;

typedef struct
{
    uint32_t u32SrcAddr;
    uint32_t u32DstAddr;
    uint32_t u32TimeOut;
    EN_DMA_PERI_SEL_T enSrcPeriID;    /*!< DMA Source Peripheral ID > */
    EN_DMA_PERI_SEL_T enDstPeriID;    /*!< DMA Dstination Peripheral ID > */
    unDmaCfg_t unCfg;

} stDmaPeriToPeriInit_t, *pstDmaPeriToPeriInit_t;




/**
 * @brief  Initialize indicated DMA Channel.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @note   Only DMA0 can work in from peripherals to peripherals mode.
 * @param  pstDmaInit: Pointer to DMA Initialize struct, @ref stDmaInit_t.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_init(stDMA_Handle_t *pstDMA, stDmaInit_t *pstDmaInit);


/**
 * @brief  Enable dma controller.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_enable(stDMA_Handle_t *pstDMA);


/**
 * @brief  Disable dma controller.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_disable(stDMA_Handle_t *pstDMA);


/**
 * @brief  Pause DMA transfer.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_pause_dma(stDMA_Handle_t *pstDMA);


/**
 * @brief  Continue DMA transfer.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_continue_dma(stDMA_Handle_t *pstDMA);


/**
 * @brief  Configure DMA interrupt route.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  u8IntSel: DMA interrupt route, @erf EN_DMA_INT_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_set_interrupt_channel(stDMA_Handle_t *pstDMA, EN_DMA_INT_T enInt);


/**
 * @brief  Enable indicated DMA Channel interrupt.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  u8IntMsk: Indicate which interrupt should be enable.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_enable_interrupt(stDMA_Handle_t *pstDMA, uint8_t u8IntMsk);


/**
 * @brief  Disable indicated DMA Channel interrupt.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  u8IntMsk: Indicate which interrupt should be disable.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_disable_interrupt(stDMA_Handle_t *pstDMA, uint8_t u8IntMsk);


/**
 * @brief  Clear indicated DMA Channelinterrupt flag.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  u8IntFlag: Indicate which interrupt will be clear.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_clear_interrupt_flag(stDMA_Handle_t *pstDMA, uint8_t u8IntFlag);


/**
 * @brief  Get DMA interrupt flagwith indicated channel by enCh.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  pu8IntFlag: Point to save the interrupt flag.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_get_interrupt_flag(stDMA_Handle_t *pstDMA, uint8_t *pu8IntFlag);


/**
 * @brief  set circ mode total len.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  u32TotalLen: The total data length of dma transfer when DMA is in circulation mode.
 *                      if DMA_STOP_CFG is 1, DMA will stop when the total length transferred is equal to u32TotalLen.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_set_circ_total_len(stDMA_Handle_t *pstDMA, uint32_t u32TotalLen);


/**
 * @brief  Get the total data length in circulation mode which dma has been transferred.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  pu32Count: Used to save the counter value.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_get_circ_count(stDMA_Handle_t *pstDMA, uint32_t *pu32Count);


/**
 * @brief  Get the dma trx pointer.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  pu16Pointer: DMA trx pointer.
 * @note   in circ mode, it automatically returns to 0 when reach at DMA_CFG[15:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_get_trx_pointer(stDMA_Handle_t *pstDMA, uint16_t *pu16Pointer);


/**
 * @brief  Trigger DMA tx start when data ready in circulation mode.
 * @param  pstDMA : DMA handle, Should be DMA0 ~ DMA7.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_set_circ_mode_data_ready(stDMA_Handle_t *pstDMA);


/**
 * @brief  Enable DMA interval tx mode.
 * @param  pstDMA : DMA handle, Should be DMA0 ~ DMA7.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_interval_tx_mode_enable(stDMA_Handle_t *pstDMA);


/**
 * @brief  Disable DMA interval tx mode.
 * @param  pstDMA : DMA handle, Should be DMA0 ~ DMA7.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_interval_tx_mode_disable(stDMA_Handle_t *pstDMA);


/**
 * @brief  Set DMA tx index relative to the source address with indicated channel.
 * @note   the length of dma tx equals to (current u16TxIndex - previous u16TxIndex).
 * @param  pstDMA : DMA handle, Should be DMA0 ~ DMA7.
 * @param  u16TxIndex: dma will pause transfer when dma tx pointer equals to u16TxIndex, u16TxIndex should <= DMA_CFG[15:0].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_set_interval_tx_index(stDMA_Handle_t *pstDMA, uint16_t u16TxIndex);


/**
 * @brief  Set DMA timeout threshold with indicated channel.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  u8Timeout: Timeout threshold value, range is [0, 255].
 * @param  enUnit: Timeout unit, 1us/10us/100us/1000us, @ref EN_DMA_TIMEOUT_UNIT_T.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_set_timeout(stDMA_Handle_t *pstDMA, uint8_t u8Timeout, EN_DMA_TIMEOUT_UNIT_T enUnit);


/**
 * @brief  Set DMA timeout threshold with indicated channel.
 * @param  pstDMA: DMA handle, Should be DMA0 ~ DMA7.
 * @param  u32TimeoutUs: Timeout threshold value, unit is us, range is [0, 255000].
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_dma_set_timeout_us(stDMA_Handle_t *pstDMA, uint32_t u32TimeoutUs);


#ifdef __cplusplus
}
#endif

#endif /* __HW_DMA_H__ */

