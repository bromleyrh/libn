/*
 * mul.c
 */

#include "arithmetic.h"

#include <limits.h>
#include <stdint.h>

uint64_t
mulu64u64(uint64_t x, uint64_t y, int *overflow)
{
    if (y > UINT64_MAX / x)
        *overflow |= 1;

    return x * y;
}

int64_t
muls64s64(int64_t x, int64_t y, int *overflow)
{
    if (y < 0) {
        if (x < 0) {
            if (x >= INT64_MAX / y)
                goto no_overflow;
        } else if (x == 0)
            goto no_overflow;
        else if (y >= INT64_MIN / x)
            goto no_overflow;
    } else if (x < 0) {
        if (y == 0)
            goto no_overflow;
        else if (x >= INT64_MIN / y)
            goto no_overflow;
    } else if ((x == 0) || (y == 0))
        goto no_overflow;
    else if (y <= INT64_MAX / x)
        goto no_overflow;

    *overflow |= 1;

no_overflow:
    return x * y;
}

uint32_t
mulu32u32(uint32_t x, uint32_t y, int *overflow)
{
    if (y > UINT32_MAX / x)
        *overflow |= 1;

    return x * y;
}

int32_t
muls32s32(int32_t x, int32_t y, int *overflow)
{
    if (y < 0) {
        if (x < 0) {
            if (x >= INT32_MAX / y)
                goto no_overflow;
        } else if (x == 0)
            goto no_overflow;
        else if (y >= INT32_MIN / x)
            goto no_overflow;
    } else if (x < 0) {
        if (y == 0)
            goto no_overflow;
        else if (x >= INT32_MIN / y)
            goto no_overflow;
    } else if ((x == 0) || (y == 0))
        goto no_overflow;
    else if (y <= INT32_MAX / x)
        goto no_overflow;

    *overflow |= 1;

no_overflow:
    return x * y;
}

/* vi: set expandtab sw=4 ts=4: */
