/*
 * arithmetic.c
 */

#include "arithmetic.h"

#include <limits.h>
#include <stdint.h>

typedef union {
    struct {
        uint32_t    lo;
        uint32_t    hi;
    };
    uint64_t emul;
} cuint64_t;

typedef union {
    struct {
        uint32_t    lo;
        int32_t     hi;
    };
    int64_t emul;
} cint64_t;

__thread int arithmetic_status;

#ifdef I386
void _addu64u64(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t *, uint32_t *,
                int *);
void _adds64s64(int32_t, int32_t, int32_t, int32_t, int32_t *, uint32_t *,
                int *);

void _subu64u64(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t *, uint32_t *,
                int *);
void _subs64s64(int32_t, int32_t, int32_t, int32_t, int32_t *, uint32_t *,
                int *);

void _mulu64u64(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t *, uint32_t *,
                int *);
void _muls64s64(int32_t, int32_t, int32_t, int32_t, int32_t *, uint32_t *,
                int *);

#endif

#ifdef I386
uint64_t
addu64u64(uint64_t x, uint64_t y, int *overflow)
{
    cuint64_t *cx = (cuint64_t *)&x, *cy = (cuint64_t *)&y;
    cuint64_t cres;

    _addu64u64(cx->hi, cx->lo, cy->hi, cy->lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

int64_t
adds64s64(int64_t x, int64_t y, int *overflow)
{
    cint64_t *cx = (cint64_t *)&x, *cy = (cint64_t *)&y;
    cint64_t cres;

    _adds64s64(cx->hi, cx->lo, cy->hi, cy->lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

uint64_t
subu64u64(uint64_t x, uint64_t y, int *overflow)
{
    cuint64_t *cx = (cuint64_t *)&x, *cy = (cuint64_t *)&y;
    cuint64_t cres;

    _subu64u64(cx->hi, cx->lo, cy->hi, cy->lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

int64_t
subs64s64(int64_t x, int64_t y, int *overflow)
{
    cint64_t *cx = (cint64_t *)&x, *cy = (cint64_t *)&y;
    cint64_t cres;

    _subs64s64(cx->hi, cx->lo, cy->hi, cy->lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

uint64_t
mulu64u64(uint64_t x, uint64_t y, int *overflow)
{
    cuint64_t *cx = (cuint64_t *)&x, *cy = (cuint64_t *)&y;
    cuint64_t cres;

    _mulu64u64(cx->hi, cx->lo, cy->hi, cy->lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

int64_t
muls64s64(int64_t x, int64_t y, int *overflow)
{
    cint64_t *cx = (cint64_t *)&x, *cy = (cint64_t *)&y;
    cint64_t cres;

    _muls64s64(cx->hi, cx->lo, cy->hi, cy->lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

#endif

uint64_t
divu64u64(uint64_t x, uint64_t y, int *diverr)
{
    if (y == 0) {
        *diverr |= DIVERR;
        return UINT64_MAX;
    }

    return x / y;
}

int64_t
divs64s64(int64_t x, int64_t y, int *diverr)
{
    if (y == 0) {
        *diverr |= DIVERR;
        return INT64_MAX;
    }

    return x / y;
}

uint32_t
divu32u32(uint32_t x, uint32_t y, int *diverr)
{
    if (y == 0) {
        *diverr |= DIVERR;
        return UINT32_MAX;
    }

    return x / y;
}

int32_t
divs32s32(int32_t x, int32_t y, int *diverr)
{
    if (y == 0) {
        *diverr |= DIVERR;
        return INT32_MAX;
    }

    return x / y;
}

/* vi: set expandtab sw=4 ts=4: */
