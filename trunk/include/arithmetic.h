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

