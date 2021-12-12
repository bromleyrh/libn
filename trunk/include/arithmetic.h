/*
 * arithmetic.h
 */

#ifndef _ARITHMETIC_H
#define _ARITHMETIC_H

#define _LIBN_H_INTERNAL
#include <arithmetic/libn_common.h>
#undef _LIBN_H_INTERNAL

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern LIBN_EXPORTED __thread int arithmetic_status;

#define in \
    do { \
        arithmetic_status = 0; \
        do
#define trap \
        while (0); \
    } while (0); \
    if (arithmetic_status != 0)

#define addou64u64(x, y) addu64u64(x, y, &arithmetic_status)
#define addos64s64(x, y) adds64s64(x, y, &arithmetic_status)

#define addou32u32(x, y) addu32u32(x, y, &arithmetic_status)
#define addos32s32(x, y) adds32s32(x, y, &arithmetic_status)

#define subou64u64(x, y) subu64u64(x, y, &arithmetic_status)
#define subos64s64(x, y) subs64s64(x, y, &arithmetic_status)

#define subou32u32(x, y) subu32u32(x, y, &arithmetic_status)
#define subos32s32(x, y) subs32s32(x, y, &arithmetic_status)

#define mulou64u64(x, y) mulu64u64(x, y, &arithmetic_status)
#define mulos64s64(x, y) muls64s64(x, y, &arithmetic_status)

#define mulou32u32(x, y) mulu32u32(x, y, &arithmetic_status)
#define mulos32s32(x, y) muls32s32(x, y, &arithmetic_status)

#define divzu64u64(x, y) divu64u64(x, y, &arithmetic_status)
#define divzs64s64(x, y) divs64s64(x, y, &arithmetic_status)

#define divzu32u32(x, y) divu32u32(x, y, &arithmetic_status)
#define divzs32s32(x, y) divs32s32(x, y, &arithmetic_status)

#if __WORDSIZE__ == 64
#define addouzuz(x, y) addou64u64(x, y)
#define subouzuz(x, y) subou64u64(x, y)
#define mulouzuz(x, y) mulou64u64(x, y)
#define divzuzuz(x, y) divzu64u64(x, y)
#else
#define addouzuz(x, y) addou32u32(x, y)
#define subouzuz(x, y) subou32u32(x, y)
#define mulouzuz(x, y) mulou32u32(x, y)
#define divzuzuz(x, y) divzu32u32(x, y)
#endif

LIBN_EXPORTED uint64_t addu64u64(uint64_t x, uint64_t y, int *overflow);
LIBN_EXPORTED int64_t adds64s64(int64_t x, int64_t y, int *overflow);

LIBN_EXPORTED uint32_t addu32u32(uint32_t x, uint32_t y, int *overflow);
LIBN_EXPORTED int32_t adds32s32(int32_t x, int32_t y, int *overflow);

LIBN_EXPORTED uint64_t subu64u64(uint64_t x, uint64_t y, int *overflow);
LIBN_EXPORTED int64_t subs64s64(int64_t x, int64_t y, int *overflow);

LIBN_EXPORTED uint32_t subu32u32(uint32_t x, uint32_t y, int *overflow);
LIBN_EXPORTED int32_t subs32s32(int32_t x, int32_t y, int *overflow);

LIBN_EXPORTED uint64_t mulu64u64(uint64_t x, uint64_t y, int *overflow);
LIBN_EXPORTED int64_t muls64s64(int64_t x, int64_t y, int *overflow);

LIBN_EXPORTED uint32_t mulu32u32(uint32_t x, uint32_t y, int *overflow);
LIBN_EXPORTED int32_t muls32s32(int32_t x, int32_t y, int *overflow);

LIBN_EXPORTED uint64_t divu64u64(uint64_t x, uint64_t y, int *diverr);
LIBN_EXPORTED int64_t divs64s64(int64_t x, int64_t y, int *diverr);

LIBN_EXPORTED uint32_t divu32u32(uint32_t x, uint32_t y, int *diverr);
LIBN_EXPORTED int32_t divs32s32(int32_t x, int32_t y, int *diverr);

#ifdef __cplusplus
}
#endif

#endif

