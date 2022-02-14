/*
 * sub.c
 */

#include "arithmetic.h"

#include <limits.h>
#include <stdint.h>

uint64_t
subu64u64(uint64_t x, uint64_t y, int *overflow)
{
    if (y > x)
        *overflow |= 1;

    return x - y;
}

int64_t
subs64s64(int64_t x, int64_t y, int *overflow)
{
    if (y < 0) {
        if (y >= x - INT64_MAX)
            goto no_overflow;
    } else if (y <= x - INT64_MIN)
        goto no_overflow;

    *overflow |= 1;

no_overflow:
    return x - y;
}

uint32_t
subu32u32(uint32_t x, uint32_t y, int *overflow)
{
    if (y > x)
        *overflow |= 1;

    return x - y;
}

int32_t
subs32s32(int32_t x, int32_t y, int *overflow)
{
    if (y < 0) {
        if (y >= x - INT32_MAX)
            goto no_overflow;
    } else if (y <= x - INT32_MIN)
        goto no_overflow;

    *overflow |= 1;

no_overflow:
    return x - y;
}

/* vi: set expandtab sw=4 ts=4: */
