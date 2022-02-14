/*
 * add.c
 */

#include "arithmetic.h"

#include <limits.h>
#include <stdint.h>

uint64_t
addu64u64(uint64_t x, uint64_t y, int *overflow)
{
    if (y > UINT64_MAX - x)
        *overflow |= 1;

    return x + y;
}

int64_t
adds64s64(int64_t x, int64_t y, int *overflow)
{
    if (y < 0) {
        if (y >= INT64_MIN - x)
            goto no_overflow;
    } else if (y <= INT64_MAX - x)
        goto no_overflow;

    *overflow |= 1;

no_overflow:
    return x + y;
}

uint32_t
addu32u32(uint32_t x, uint32_t y, int *overflow)
{
    if (y > UINT32_MAX - x)
        *overflow |= 1;

    return x + y;
}

int32_t
adds32s32(int32_t x, int32_t y, int *overflow)
{
    if (y < 0) {
        if (y >= INT32_MIN - x)
            goto no_overflow;
    } else if (y <= INT32_MAX - x)
        goto no_overflow;

    *overflow |= 1;

no_overflow:
    return x + y;
}

/* vi: set expandtab sw=4 ts=4: */
