/*
 * overflow_test.c
 */

#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void test_addu64u64(void);
static void test_adds64s64(void);

static void test_addu32u32(void);
static void test_adds32s32(void);

static void test_subu64u64(void);
static void test_subs64s64(void);

static void test_subu32u32(void);
static void test_subs32s32(void);

static void test_mulu64u64(void);
static void test_muls64s64(void);

static void test_mulu32u32(void);
static void test_muls32s32(void);

static void (*const test_fns[])(void) = {
    &test_addu64u64,
    &test_adds64s64,
    &test_addu32u32,
    &test_adds32s32,
    &test_subu64u64,
    &test_subs64s64,
    &test_subu32u32,
    &test_subs32s32,
    &test_mulu64u64,
    &test_muls64s64,
    &test_mulu32u32,
    &test_muls32s32
};

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* 64-bit implementations */

uint64_t addu64u64(uint64_t, uint64_t, int *);
int64_t adds64s64(int64_t, int64_t, int *);

uint32_t addu32u32(uint32_t, uint32_t, int *);
int32_t adds32s32(int32_t, int32_t, int *);

uint64_t subu64u64(uint64_t, uint64_t, int *);
int64_t subs64s64(int64_t, int64_t, int *);

uint32_t subu32u32(uint32_t, uint32_t, int *);
int32_t subs32s32(int32_t, int32_t, int *);

uint64_t mulu64u64(uint64_t, uint64_t, int *);
int64_t muls64s64(int64_t, int64_t, int *);

uint32_t mulu32u32(uint32_t, uint32_t, int *);
int32_t muls32s32(int32_t, int32_t, int *);

static void put_output(int, const char *, ...);

static void
put_output(int overflow, const char *pri, ...)
{
    if (overflow)
        puts("Overflow");
    else {
        char fmt[8];
        va_list ap;

        snprintf(fmt, sizeof(fmt), "%%%s\n", pri);

        va_start(ap, pri);
        vprintf(fmt, ap);
        va_end(ap);
    }
}

static void
test_addu64u64()
{
    int overflow;
    uint64_t res;

    overflow = 0;
    res = addu64u64(UINT64_MAX, 1, &overflow);
    put_output(overflow, PRIu64, res);

    overflow = 0;
    res = addu64u64(2, 2, &overflow);
    put_output(overflow, PRIu64, res);
}

static void
test_adds64s64()
{
    int overflow;
    int64_t res;

    overflow = 0;
    res = adds64s64(INT64_MAX, 1, &overflow);
    put_output(overflow, PRIi64, res);

    overflow = 0;
    res = adds64s64(2, -6, &overflow);
    put_output(overflow, PRIi64, res);
}

static void
test_addu32u32()
{
    int overflow;
    uint32_t res;

    overflow = 0;
    res = addu32u32(UINT32_MAX, 1, &overflow);
    put_output(overflow, PRIu32, res);

    overflow = 0;
    res = addu32u32(2, 2, &overflow);
    put_output(overflow, PRIu32, res);
}

static void
test_adds32s32()
{
    int overflow;
    int32_t res;

    overflow = 0;
    res = adds32s32(INT32_MAX, 1, &overflow);
    put_output(overflow, PRIi32, res);

    overflow = 0;
    res = adds32s32(2, -6, &overflow);
    put_output(overflow, PRIi32, res);
}

static void
test_subu64u64()
{
    int overflow;
    uint64_t res;

    overflow = 0;
    res = subu64u64(0, 1, &overflow);
    put_output(overflow, PRIu64, res);

    overflow = 0;
    res = subu64u64(6, 2, &overflow);
    put_output(overflow, PRIu64, res);
}

static void
test_subs64s64()
{
    int overflow;
    int64_t res;

    overflow = 0;
    res = subs64s64(INT64_MIN, 1, &overflow);
    put_output(overflow, PRIi64, res);

    overflow = 0;
    res = subs64s64(2, 6, &overflow);
    put_output(overflow, PRIi64, res);
}

static void
test_subu32u32()
{
    int overflow;
    uint32_t res;

    overflow = 0;
    res = subu32u32(0, 1, &overflow);
    put_output(overflow, PRIu32, res);

    overflow = 0;
    res = subu32u32(6, 2, &overflow);
    put_output(overflow, PRIu32, res);
}

static void
test_subs32s32()
{
    int overflow;
    int32_t res;

    overflow = 0;
    res = subs32s32(INT32_MIN, 1, &overflow);
    put_output(overflow, PRIi32, res);

    overflow = 0;
    res = subs32s32(2, 6, &overflow);
    put_output(overflow, PRIi32, res);
}

static void
test_mulu64u64()
{
    int overflow;
    uint64_t res;

    overflow = 0;
    res = mulu64u64(UINT64_MAX, 2, &overflow);
    put_output(overflow, PRIu64, res);

    overflow = 0;
    res = mulu64u64(2, 2, &overflow);
    put_output(overflow, PRIu64, res);
}

static void
test_muls64s64()
{
    int overflow;
    int64_t res;

    overflow = 0;
    res = muls64s64(INT64_MIN, 2, &overflow);
    put_output(overflow, PRIi64, res);

    overflow = 0;
    res = muls64s64(2, -2, &overflow);
    put_output(overflow, PRIi64, res);
}

static void
test_mulu32u32()
{
    int overflow;
    uint32_t res;

    overflow = 0;
    res = mulu32u32(UINT32_MAX, 2, &overflow);
    put_output(overflow, PRIu32, res);

    overflow = 0;
    res = mulu32u32(2, 2, &overflow);
    put_output(overflow, PRIu32, res);
}

static void
test_muls32s32()
{
    int overflow;
    int32_t res;

    overflow = 0;
    res = muls32s32(INT32_MIN, 2, &overflow);
    put_output(overflow, PRIi32, res);

    overflow = 0;
    res = muls32s32(2, -2, &overflow);
    put_output(overflow, PRIi32, res);
}

int
main(int argc, char **argv)
{
    size_t i;

    (void)argc;
    (void)argv;

    for (i = 0; i < ARRAY_SIZE(test_fns); i++)
        (*test_fns[i])();

    return EXIT_SUCCESS;
}

/* vi: set expandtab sw=4 ts=4: */
