/*************************************************************************************************************
 * @file    hw_cpto.h
 * @version V1.0
 * @date    2022-02-18
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


#ifndef __HW_CPTO_H__
#define __HW_CPTO_H__

#ifdef __cplusplus
#if __cplusplus
 extern "C" {
#endif
#endif /* __cplusplus */




/**
 * @brief  128bit AES encrypt.
 * @param  pu32Key: Key used for AES algorithm, its length should be 16Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_aes_encrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut);


/**
 * @brief  128bit AES decrypt.
 * @param  pu32Key: Key used for AES algorithm, its length should be 16Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_aes_decrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut);


/**
 * @brief  192bit AES encrypt.
 * @param  pu32Key: Key used for AES algorithm, its length should be 24Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_aes192_encrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut);


/**
 * @brief  192bit AES decrypt.
 * @param  pu32Key: Key used for AES algorithm, its length should be 24Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_aes192_decrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut);


/**
 * @brief  256bit AES encrypt.
 * @param  pu32Key: Key used for AES algorithm, its length should be 32Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_aes256_encrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut);


/**
 * @brief  256bit AES decrypt.
 * @param  pu32Key: Key used for AES algorithm, its length should be 32Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_aes256_decrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut);


/**
 * @brief  cmac decrypt.
 * @param  pu32Key: Key used for CMAC algorithm, its length should be 16Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length can be 0, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @param  u32DataInLen: length of the output buffer.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_cmac_encrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut,
                                        uint32_t u32DataInLen);


/**
 * @brief  ECB encrypt.
 * @param  pu32Key: Key used for ECB algorithm, its length should be 16Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_ecb_encrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut);


/**
 * @brief  CBC encrypt.
 * @param  pu32Key: Key used for CBC algorithm, its length should be 16Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @param  pu32IV: pointer to the IV buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_cbc_encrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut, uint32_t *pu32IV);


/**
 * @brief  CTR encrypt.
 * @param  pu32Key: Key used for CTR algorithm, its length should be 16Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @param  pu32IV: pointer to the IV buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_ctr_encrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut, uint32_t *pu32IV);


/**
 * @brief  CTR decrypt.
 * @param  pu32Key: Key used for CTR algorithm, its length should be 16Bytes, little endian.
 * @param  pu32DataIn: pointer to the input buffer, its length should be 16Bytes, little endian.
 * @param  pu32DataOut: pointer to the output buffer, its length should be 16Bytes, little endian.
 * @param  pu32IV: pointer to the IV buffer, its length should be 16Bytes, little endian.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_ctr_decrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut, uint32_t *pu32IV);


/**
 * @brief  config parameter for CCM encrypt/decrypt.
 * @param  u8CcmCfg: bit 4 directionbit 1: M->S 0: S->M;[3:2]llid of PDU header.
 * @param  pu32IV: IV, 8bytes.
 * @param  pu32EncPktCnt: Encrypt packet counter, only for encryption.
 * @param  pu32DecPktCnt: Decrypt packet counter, only for decryption.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_cpto_config_for_ccm(uint8_t u8CcmCfg, uint32_t* pu32IV, uint32_t* pu32EncPktCnt,
                                               uint32_t* pu32DecPktCnt);


/**
 * @brief  CCM encrypt.
 * @param  pu32Key: ccm session key, its length should be 16Bytes, little endian.
 * @param  pu32DataIn: data to be encrypted, little endian.
 * @param  pu32DataOut: buffer for plaint data after encrypted, little endian.
 * @param  u16DataInlen: length of pu32DataIn.
 * @param  pu32GeneratedMIC: mic.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_ccm_encrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut,
                                       uint16_t u16DataInlen, uint32_t* pu32GeneratedMIC);


/**
 * @brief  CCM decrypt.
 * @param  pu32Key: ccm session key, its length should be 16Bytes, little endian.
 * @param  pu32DataIn: data to be decrypted,  little endian.
 * @param  pu32DataOut: buffer for plaint data after decrypted, little endian.
 * @param  u16DataInlen: length of pu32DataIn.
 * @param  pu32GeneratedMIC: mic.
 * @return status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T rom_hw_ccm_decrypt(uint32_t* pu32Key, uint32_t* pu32DataIn, uint32_t* pu32DataOut,
                                       uint16_t u16DataInlen, uint32_t* pu32GeneratedMIC);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HW_CPTO_H__ */

