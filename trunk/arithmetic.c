/*
 * arithmetic.c
 */

#include "arithmetic.h"

#include <limits.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u64_t uint64_t
#define s64_t int64_t
#define u32_t uint32_t
#define s32_t int32_t

struct trap_frame {
    void    *bp;
    int     n;
};

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

_Thread_local sigjmp_buf aenv[ASTKMAX];
_Thread_local int abreak[ASTKMAX+1] = {[0] = 1};
_Thread_local size_t aenvoff;
_Thread_local int atmp;

static __thread struct trap_frame trap_stack[ASTKMAX+1];

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
static uint64_t
op_with_trap_u64u64(uint64_t (*)(uint64_t, uint64_t, int *), uint64_t, uint64_t,
                    sigjmp_buf);
static int64_t
op_with_trap_s64s64(int64_t (*)(int64_t, int64_t, int *), int64_t, int64_t,
                    sigjmp_buf);
static uint32_t
op_with_trap_u32u32(uint32_t (*)(uint32_t, uint32_t, int *), uint32_t, uint32_t,
                    sigjmp_buf);
static int32_t
op_with_trap_s32s32(int32_t (*)(int32_t, int32_t, int *), int32_t, int32_t,
                    sigjmp_buf);

#define DEFINE_GENERIC_OP_WITH_TRAP(typ) \
    static typ##_t \
    op_with_trap_##typ##typ(typ##_t (*op)(typ##_t, typ##_t, int *), typ##_t x, \
                            typ##_t y, sigjmp_buf env) \
    { \
        int flags = 0; \
        typ##_t res; \
        \
        res = (*op)(x, y, &flags); \
        if (flags != 0) \
            siglongjmp(env, 1); \
        \
        return res; \
    }

#define DEFINE_OP_WITH_TRAP(op, typ) \
    typ##_t \
    op##t##typ##typ(typ##_t x, typ##_t y, sigjmp_buf env) \
    { \
        return op_with_trap_##typ##typ(&op##typ##typ, x, y, env); \
    }

DEFINE_GENERIC_OP_WITH_TRAP(u64)
DEFINE_GENERIC_OP_WITH_TRAP(s64)
DEFINE_GENERIC_OP_WITH_TRAP(u32)
DEFINE_GENERIC_OP_WITH_TRAP(s32)

#ifdef I386
uint64_t
addu64u64(uint64_t x, uint64_t y, int *overflow)
{
    cuint64_t cx = {.emul = x}, cy = {.emul = y};
    cuint64_t cres;

    _addu64u64(cx.hi, cx.lo, cy.hi, cy.lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

int64_t
adds64s64(int64_t x, int64_t y, int *overflow)
{
    cint64_t cx = {.emul = x}, cy = {.emul = y};
    cint64_t cres;

    _adds64s64(cx.hi, cx.lo, cy.hi, cy.lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

uint64_t
subu64u64(uint64_t x, uint64_t y, int *overflow)
{
    cuint64_t cx = {.emul = x}, cy = {.emul = y};
    cuint64_t cres;

    _subu64u64(cx.hi, cx.lo, cy.hi, cy.lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

int64_t
subs64s64(int64_t x, int64_t y, int *overflow)
{
    cint64_t cx = {.emul = x}, cy = {.emul = y};
    cint64_t cres;

    _subs64s64(cx.hi, cx.lo, cy.hi, cy.lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

uint64_t
mulu64u64(uint64_t x, uint64_t y, int *overflow)
{
    cuint64_t cx = {.emul = x}, cy = {.emul = y};
    cuint64_t cres;

    _mulu64u64(cx.hi, cx.lo, cy.hi, cy.lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

int64_t
muls64s64(int64_t x, int64_t y, int *overflow)
{
    cint64_t cx = {.emul = x}, cy = {.emul = y};
    cint64_t cres;

    _muls64s64(cx.hi, cx.lo, cy.hi, cy.lo, &cres.hi, &cres.lo, overflow);

    return cres.emul;
}

#endif

uint64_t
divu64u64(uint64_t x, uint64_t y, int *diverr)
{
    if (y == 0) {
        *diverr |= ADIVERR;
        return UINT64_MAX;
    }

    return x / y;
}

int64_t
divs64s64(int64_t x, int64_t y, int *diverr)
{
    if (y == 0) {
        *diverr |= ADIVERR;
        return INT64_MAX;
    }

    return x / y;
}

uint32_t
divu32u32(uint32_t x, uint32_t y, int *diverr)
{
    if (y == 0) {
        *diverr |= ADIVERR;
        return UINT32_MAX;
    }

    return x / y;
}

int32_t
divs32s32(int32_t x, int32_t y, int *diverr)
{
    if (y == 0) {
        *diverr |= ADIVERR;
        return INT32_MAX;
    }

    return x / y;
}

DEFINE_OP_WITH_TRAP(add, u64)
DEFINE_OP_WITH_TRAP(add, s64)
DEFINE_OP_WITH_TRAP(add, u32)
DEFINE_OP_WITH_TRAP(add, s32)

DEFINE_OP_WITH_TRAP(sub, u64)
DEFINE_OP_WITH_TRAP(sub, s64)
DEFINE_OP_WITH_TRAP(sub, u32)
DEFINE_OP_WITH_TRAP(sub, s32)

DEFINE_OP_WITH_TRAP(mul, u64)
DEFINE_OP_WITH_TRAP(mul, s64)
DEFINE_OP_WITH_TRAP(mul, u32)
DEFINE_OP_WITH_TRAP(mul, s32)

DEFINE_OP_WITH_TRAP(div, u64)
DEFINE_OP_WITH_TRAP(div, s64)
DEFINE_OP_WITH_TRAP(div, u32)
DEFINE_OP_WITH_TRAP(div, s32)

int
trapinit(void *bp, int n)
{
    size_t i;

    fprintf(stderr, "%s(): %p, %d\n", __FUNCTION__, bp, n);

    trap_stack[aenvoff].bp = bp;
    trap_stack[aenvoff].n = n;
    for (i = 0; (trap_stack[i].bp != bp) || (trap_stack[i].n != n); i++)
        ;
    if (i < aenvoff) {
        /* supports the case where return, goto, or longjmp() is used to
           directly exit a trap-in block */
        fprintf(stderr, "%s(): %p, %d found at %d\n", __FUNCTION__, bp, n, i);
        aenvoff = i;
        memset(abreak + 1 + i, 0, sizeof(abreak) - (1+i) * sizeof(abreak[0]));
    }

    ++aenvoff;

    return 0;
}

int
atrapcond(int set)
{
    int ret;

    fprintf(stderr, "%s(): aenvoff == %d\n", __FUNCTION__, aenvoff);

    ret = !abreak[aenvoff];
    fprintf(stderr, "%s(): abreak[%d] == %d\n", __FUNCTION__, aenvoff, !ret);
    if (set) {
        fprintf(stderr, "%s(): set abreak[%d]\n", __FUNCTION__, aenvoff);
        abreak[aenvoff] = 1;
    }

    return ret;
}

void
atrapend()
{
    fprintf(stderr, "%s(): reset abreak[%d]\n", __FUNCTION__, aenvoff);
    abreak[aenvoff] = 0;
    --aenvoff;

    trap_stack[aenvoff].bp = NULL;
}

/* vi: set expandtab sw=4 ts=4: */
