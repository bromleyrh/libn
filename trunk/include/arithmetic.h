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

#define OVERFLOW 1
#define DIVERR 2

#define ASTKMAX 16

extern LIBN_EXPORTED __thread sigjmp_buf aenv[ASTKMAX];
extern LIBN_EXPORTED __thread int abreak[ASTKMAX+1];
extern LIBN_EXPORTED __thread size_t aenvoff;
extern LIBN_EXPORTED __thread int atmp;

#define aenvcur aenv[aenvoff-1]
#define abreakcur abreak[aenvoff]

#define trap \
    for (atmp = ((++aenvoff <= ASTKMAX) || astko()); \
         !abreakcur; \
         abreakcur = 0, --aenvoff) \
        while (!abreakcur) \
            if ((abreakcur = 1) && (sigsetjmp(aenvcur, 0) != 0)) { \
                do
#define in \
                while (0); \
            } else

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

LIBN_EXPORTED int astko(void);

#ifdef __cplusplus
}
#endif

#endif

