/*
 * overflow_test.c
 */

#include "arithmetic.h"

#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static int testnum;

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

static void test_fn(void);

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

static void put_output(int, const char *, ...);

static void put_bug(void);
static void put_success(void);

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
put_bug()
{
    fputs("Bug\n", stderr);
}

static void
put_success()
{
    ++testnum;
    fprintf(stderr, "Overflow %d trapped\n", testnum);
}

static void
test_addu64u64()
{
    int overflow;
    uint64_t res;

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

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

    fprintf(stderr, "%s():\n", __FUNCTION__);

    overflow = 0;
    res = muls32s32(INT32_MIN, 2, &overflow);
    put_output(overflow, PRIi32, res);

    overflow = 0;
    res = muls32s32(2, -2, &overflow);
    put_output(overflow, PRIi32, res);
}

static void
test_fn()
{
    uint64_t n;

    n = mulou64u64(INT64_MAX, INT64_MAX);
    (void)n;
}

int
main(int argc, char **argv)
{
    size_t i;

    (void)argc;
    (void)argv;

    for (i = 0; i < ARRAY_SIZE(test_fns); i++)
        (*test_fns[i])();

    trap
        put_success();
    in
        test_fn();

    if (1)
        trap
            if (1)
                put_success();
        in
            test_fn();
    else
        put_bug();

    if (0)
        ;
    else
        trap
            if (1)
                put_success();
        in
            test_fn();

    for (i = 0; i < 3; i++)
        trap
            if (1)
                put_success();
        in
            test_fn();

    do {
        trap
            if (1)
                put_success();
        in
            test_fn();
    } while (0);

    trap
        put_bug();
    in {
        trap
            put_bug();
        in
            trap
                put_bug();
            in {
                trap
                    put_success();
                in
                    test_fn();
                trap {
                    put_success();
                    trap
                        put_success();
                    in
                        test_fn();
                } in
                    test_fn();
            }
        trap
            put_success();
        in {
            trap
                put_bug();
            in {
                trap {
                    put_success();
                    trap
                        put_success();
                    in
                        test_fn();
                } in
                    test_fn();
                trap
                    put_success();
                in
                    test_fn();
            }
            test_fn();
        }
    }

    return EXIT_SUCCESS;
}

/* vi: set expandtab sw=4 ts=4: */
