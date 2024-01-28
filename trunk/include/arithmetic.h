/*
 * arithmetic.h
 */

#ifndef _ARITHMETIC_H
#define _ARITHMETIC_H

#define _LIBN_H_INTERNAL
#include <arithmetic/libn_common.h>
#undef _LIBN_H_INTERNAL

#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AOVERFLOW 1
#define ADIVERR 2

#define ASTKMAX 16

extern LIBN_EXPORTED _Thread_local sigjmp_buf aenv[ASTKMAX];
extern LIBN_EXPORTED _Thread_local int abreak[ASTKMAX+1];
extern LIBN_EXPORTED _Thread_local size_t aenvoff;
extern LIBN_EXPORTED _Thread_local int atmp;

#define aenvcur aenv[aenvoff-1]

#define trap \
    for (atmp = atrapinit(); atrapcond(0); atrapend()) \
        while (atrapcond(1)) \
            if (sigsetjmp(aenvcur, 0) != 0) { \
                do
#define in \
                while (0); \
            } else

#if __WORDSIZE__ == 32
#define adduzuz addu64u64
#define subuzuz subu64u64
#define muluzuz mulu64u64
#define divuzuz divu64u64
#else
#define adduzuz addu32u32
#define subuzuz subu32u32
#define muluzuz mulu32u32
#define divuzuz divu32u32
#endif

#define addou64u64(x, y) addtu64u64(x, y, aenvcur)
#define addos64s64(x, y) addts64s64(x, y, aenvcur)

#define addou32u32(x, y) addtu32u32(x, y, aenvcur)
#define addos32s32(x, y) addts32s32(x, y, aenvcur)

#define subou64u64(x, y) subtu64u64(x, y, aenvcur)
#define subos64s64(x, y) subts64s64(x, y, aenvcur)

#define subou32u32(x, y) subtu32u32(x, y, aenvcur)
#define subos32s32(x, y) subts32s32(x, y, aenvcur)

#define mulou64u64(x, y) multu64u64(x, y, aenvcur)
#define mulos64s64(x, y) mults64s64(x, y, aenvcur)

#define mulou32u32(x, y) multu32u32(x, y, aenvcur)
#define mulos32s32(x, y) mults32s32(x, y, aenvcur)

#define divzu64u64(x, y) divtu64u64(x, y, aenvcur)
#define divzs64s64(x, y) divts64s64(x, y, aenvcur)

#define divzu32u32(x, y) divtu32u32(x, y, aenvcur)
#define divzs32s32(x, y) divts32s32(x, y, aenvcur)

#if __WORDSIZE__ == 64
#define addouzuz addou64u64
#define subouzuz subou64u64
#define mulouzuz mulou64u64
#define divzuzuz divzu64u64
#else
#define addouzuz addou32u32
#define subouzuz subou32u32
#define mulouzuz mulou32u32
#define divzuzuz divzu32u32
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

LIBN_EXPORTED uint64_t addtu64u64(uint64_t x, uint64_t y, sigjmp_buf env);
LIBN_EXPORTED int64_t addts64s64(int64_t x, int64_t y, sigjmp_buf env);

LIBN_EXPORTED uint32_t addtu32u32(uint32_t x, uint32_t y, sigjmp_buf env);
LIBN_EXPORTED int32_t addts32s32(int32_t x, int32_t y, sigjmp_buf env);

LIBN_EXPORTED uint64_t subtu64u64(uint64_t x, uint64_t y, sigjmp_buf env);
LIBN_EXPORTED int64_t subts64s64(int64_t x, int64_t y, sigjmp_buf env);

LIBN_EXPORTED uint32_t subtu32u32(uint32_t x, uint32_t y, sigjmp_buf env);
LIBN_EXPORTED int32_t subts32s32(int32_t x, int32_t y, sigjmp_buf env);

LIBN_EXPORTED uint64_t multu64u64(uint64_t x, uint64_t y, sigjmp_buf env);
LIBN_EXPORTED int64_t mults64s64(int64_t x, int64_t y, sigjmp_buf env);

LIBN_EXPORTED uint32_t multu32u32(uint32_t x, uint32_t y, sigjmp_buf env);
LIBN_EXPORTED int32_t mults32s32(int32_t x, int32_t y, sigjmp_buf env);

LIBN_EXPORTED uint64_t divtu64u64(uint64_t x, uint64_t y, sigjmp_buf env);
LIBN_EXPORTED int64_t divts64s64(int64_t x, int64_t y, sigjmp_buf env);

LIBN_EXPORTED uint32_t divtu32u32(uint32_t x, uint32_t y, sigjmp_buf env);
LIBN_EXPORTED int32_t divts32s32(int32_t x, int32_t y, sigjmp_buf env);

LIBN_EXPORTED int atrapinit(void);
LIBN_EXPORTED int atrapcond(int);
LIBN_EXPORTED void atrapend(void);

#ifdef __cplusplus
}
#endif

#endif

