/*************************************************************************************************************
 * @file    mlog.h
 * @version V1.0
 * @date    2023-07-11
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


#ifndef __MLOG_H__
#define __MLOG_H__

//------------------------------------------------0 param start--------------------------------------
#define MLOG0E(ID, SCRIPT)                        mlog_0(ID)
#define MLOG0W(ID, SCRIPT)                        mlog_0(ID)
#define MLOG0I(ID, SCRIPT)                        mlog_0(ID)
#define MLOG0D(ID, SCRIPT)                        mlog_0(ID)
//------------------------------------------------0 param end--------------------------------------

//------------------------------------------------1 param start--------------------------------------
// for 1 param log, e.g.
// MLOGE ( 0x1001, "error the u16 is %x", u16 );
// MLOG32E ( 0x1001, "error the u32 is %x", u32 );
#define MLOGD(ID, SCRIPT, u16)                    mlog_16(ID, u16)
#define MLOG32D(ID, SCRIPT, u32)                  mlog_32(ID, u32)
// #define MLOG64D(ID, SCRIPT, u64 )       mlog_64(ID, u64)

#define MLOGI(ID, SCRIPT, u16)                    mlog_16(ID, u16)
#define MLOG32I(ID, SCRIPT, u32)                  mlog_32(ID, u32)
// #define MLOG64I(ID, SCRIPT, u64 )       mlog_64(ID, u64)

#define MLOGW(ID, SCRIPT, u16)                    mlog_16(ID, u16)
#define MLOG32W(ID, SCRIPT, u32)                  mlog_32(ID, u32)
// #define MLOG64W(ID, SCRIPT, u64 )       mlog_64(ID, u64)

#define MLOGE(ID, SCRIPT, u16)                    mlog_16(ID, u16)
#define MLOG32E(ID, SCRIPT, u32)                  mlog_32(ID, u32)
// #define MLOG64E(ID, SCRIPT, u64 )       mlog_64(ID, u64)
//------------------------------------------------1 param end--------------------------------------

//------------------------------------------------2 param start--------------------------------------
// for 2 param log ,e.g. MLOG88E ( 0x2001, "error:MLOG88E a is %x  val b=%x", u8a, u8b );
// MLOG3216E ( 0x2001, "error:MLOG3216E a is %x  val b=%x", u32a, u16b );
#define MLOG88D(ID, SCRIPT, u8a, u8b)             mlog_88(ID, u8a, u8b)
#define MLOG1616D(ID, SCRIPT, u16a, u16b)         mlog_1616(ID, u16a, u16b)
#define MLOG3216D(ID, SCRIPT, u32a, u16b)         mlog_3216(ID, u32a, u16b)
#define MLOG3232D(ID, SCRIPT, u32a, u32b)         mlog_3232(ID, u32a, u32b)

#define MLOG88I(ID, SCRIPT, u8a, u8b)             mlog_88(ID, u8a, u8b)
#define MLOG1616I(ID, SCRIPT, u16a, u16b)         mlog_1616(ID, u16a, u16b)
#define MLOG3216I(ID, SCRIPT, u32a, u16b)         mlog_3216(ID, u32a, u16b)
#define MLOG3232I(ID, SCRIPT, u32a, u32b)         mlog_3232(ID, u32a, u32b)

#define MLOG88W(ID, SCRIPT, u8a, u8b)             mlog_88(ID, u8a, u8b)
#define MLOG1616W(ID, SCRIPT, u16a, u16b)         mlog_1616(ID, u16a, u16b)
#define MLOG3216W(ID, SCRIPT, u32a, u16b)         mlog_3216(ID, u32a, u16b)
#define MLOG3232W(ID, SCRIPT, u32a, u32b)         mlog_3232(ID, u32a, u32b)

#define MLOG88E(ID, SCRIPT, u8a, u8b)             mlog_88(ID, u8a, u8b)
#define MLOG1616E(ID, SCRIPT, u16a, u16b)         mlog_1616(ID, u16a, u16b)
#define MLOG3216E(ID, SCRIPT, u32a, u16b)         mlog_3216(ID, u32a, u16b)
#define MLOG3232E(ID, SCRIPT, u32a, u32b)         mlog_3232(ID, u32a, u32b)
//------------------------------------------------2 param end--------------------------------------

//------------------------------------------------3 oaram start--------------------------------------
// for 3 param log ,e.g. MLOG1688E ( 0x3001, "error u16=%x vala is %x  valb=%x", u16, u8a, u8b );
// MLOG321616E ( 0x3002, "error:MLOG321616E  u32=%x u16a=%x v16b is %x ", u32, u16a, u16b );
#define MLOG1688D(ID, SCRIPT, u16, u8a, u8b)      mlog_1688(ID, u16, u8a, u8b)
#define MLOG161616D(ID, SCRIPT, u16a, u16b, u16c) mlog_161616(ID, u16a, u16b, u16c)
#define MLOG3288D(ID, SCRIPT, u32, u8a, u8b)      mlog_3288(ID, u32, u8a, u8b)
#define MLOG321616D(ID, SCRIPT, u32, u16a, u16b)  mlog_321616(ID, u32, u16a, u16b)

#define MLOG1688I(ID, SCRIPT, u16, u8a, u8b)      mlog_1688(ID, u16, u8a, u8b)
#define MLOG161616I(ID, SCRIPT, u16a, u16b, u16c) mlog_161616(ID, u16a, u16b, u16c)
#define MLOG3288I(ID, SCRIPT, u32, u8a, u8b)      mlog_3288(ID, u32, u8a, u8b)
#define MLOG321616I(ID, SCRIPT, u32, u16a, u16b)  mlog_321616(ID, u32, u16a, u16b)

#define MLOG1688W(ID, SCRIPT, u16, u8a, u8b)      mlog_1688(ID, u16, u8a, u8b)
#define MLOG161616W(ID, SCRIPT, u16a, u16b, u16c) mlog_161616(ID, u16a, u16b, u16c)
#define MLOG3288W(ID, SCRIPT, u32, u8a, u8b)      mlog_3288(ID, u32, u8a, u8b)
#define MLOG321616W(ID, SCRIPT, u32, u16a, u16b)  mlog_321616(ID, u32, u16a, u16b)

#define MLOG1688E(ID, SCRIPT, u16, u8a, u8b)      mlog_1688(ID, u16, u8a, u8b)
#define MLOG161616E(ID, SCRIPT, u16a, u16b, u16c) mlog_161616(ID, u16a, u16b, u16c)
#define MLOG3288E(ID, SCRIPT, u32, u8a, u8b)      mlog_3288(ID, u32, u8a, u8b)
#define MLOG321616E(ID, SCRIPT, u32, u16a, u16b)  mlog_321616(ID, u32, u16a, u16b)
//------------------------------------------------3 param end--------------------------------------

//------------------------------------------------x start--------------------------------------
// for hex str log ,e.g. MLOGXE ( 0x6001, "error hexstr is",hex_array,len);
#define MLOGXD(ID, SCRIPT, buffer, len)           mlog_x(ID, buffer, len)
#define MLOGXI(ID, SCRIPT, buffer, len)           mlog_x(ID, buffer, len)
#define MLOGXW(ID, SCRIPT, buffer, len)           mlog_x(ID, buffer, len)
#define MLOGXE(ID, SCRIPT, buffer, len)           mlog_x(ID, buffer, len)
//------------------------------------------------x end--------------------------------------

typedef void (*callback_mlog_0)(uint16_t u16LogId);

typedef void (*callback_mlog_16)(uint16_t u16LogId, uint16_t u16Param1);
typedef void (*callback_mlog_32)(uint16_t u16LogId, uint32_t u32Param1);
typedef void (*callback_mlog_64)(uint16_t u16LogId, uint64_t u64Param1);

typedef void (*callback_mlog_88)(uint16_t u16LogId, uint8_t u8Param1, uint8_t u8Param2);
typedef void (*callback_mlog_1616)(uint16_t u16LogId, uint16_t u16Param1, uint16_t u16Param2);
typedef void (*callback_mlog_3216)(uint16_t u16LogId, uint32_t u32Param1, uint16_t u16Param2);
typedef void (*callback_mlog_3232)(uint16_t u16LogId, uint32_t u32Param1, uint32_t u32Param2);

typedef void (*callback_mlog_1688)(uint16_t u16LogId, uint16_t u16Param1, uint8_t u8Param2, uint8_t u8Param3);
typedef void (*callback_mlog_161616)(uint16_t u16LogId, uint16_t u16Param1, uint16_t u16Param2, uint16_t u16Param3);
typedef void (*callback_mlog_3288)(uint16_t u16LogId, uint32_t u32Param1, uint8_t u8Param2, uint8_t u8Param3);
typedef void (*callback_mlog_321616)(uint16_t u16LogId, uint32_t u32Param1, uint16_t u16Param2, uint16_t u16Param3);

typedef void (*callback_mlog_x)(uint16_t u16LogId, uint8_t *pu8Data, uint8_t u8DataSize);

extern callback_mlog_0 g_mlogCallback0;

extern callback_mlog_16 g_mlogCallback16;
extern callback_mlog_32 g_mlogCallback32;
extern callback_mlog_64 g_mlogCallback64;

extern callback_mlog_88   g_mlogCallback88;
extern callback_mlog_1616 g_mlogCallback1616;
extern callback_mlog_3216 g_mlogCallback3216;
extern callback_mlog_3232 g_mlogCallback3232;

extern callback_mlog_1688   g_mlogCallback1688;
extern callback_mlog_161616 g_mlogCallback161616;
extern callback_mlog_3288   g_mlogCallback3288;
extern callback_mlog_321616 g_mlogCallback321616;

extern callback_mlog_x g_mlogCallbackX;

extern void mlog_0(uint16_t u16LogId);

extern void mlog_16(uint16_t u16LogId, uint16_t u16Param1);
extern void mlog_32(uint16_t u16LogId, uint32_t u32Param1);
extern void mlog_64(uint16_t u16LogId, uint64_t u64Param1);

extern void mlog_88(uint16_t u16LogId, uint8_t u8Param1, uint8_t u8Param2);
extern void mlog_1616(uint16_t u16LogId, uint16_t u16Param1, uint16_t u16Param2);
extern void mlog_3216(uint16_t u16LogId, uint32_t u32Param1, uint16_t u16Param2);
extern void mlog_3232(uint16_t u16LogId, uint32_t u32Param1, uint32_t u32Param2);

extern void mlog_1688(uint16_t u16LogId, uint16_t u16Param1, uint8_t u8Param2, uint8_t u8Param3);
extern void mlog_161616(uint16_t u16LogId, uint16_t u16Param1, uint16_t u16Param2, uint16_t u16Param3);
extern void mlog_3288(uint16_t u16LogId, uint32_t u32Param1, uint8_t u8Param2, uint8_t u8Param3);
extern void mlog_321616(uint16_t u16LogId, uint32_t u32Param1, uint16_t u16Param2, uint16_t u16Param3);

extern void mlog_x(uint16_t u16LogId, uint8_t *pu8Data, uint8_t u8DataSize);

#endif /* __MLOG_H__ */
