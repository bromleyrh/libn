/*
 * arithmetic_test.c
 */

#include "arithmetic.h"
#include "common.h"

#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NA 0

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int
main(int argc, char **argv)
{
    size_t i;

    static const struct ent {
        int64_t opnd1;
        int64_t opnd2;
        int64_t expected_res;
        int     expected_overflow;
    } tests[] = {
        {               0,               0,               0, 0},
        {               0,               1,               0, 0},
        {               1,               0,               0, 0},
        {               1,               1,               1, 0},

        {               0,              -1,               0, 0},
        {              -1,               0,               0, 0},
        {               1,              -1,              -1, 0},
        {              -1,               1,              -1, 0},
        {              -1,              -1,               1, 0},

        {               0,               2,               0, 0},
        {               2,               0,               0, 0},
        {               1,               2,               2, 0},
        {               2,               1,               2, 0},
        {               2,               2,               4, 0},

        {               0,              -2,               0, 0},
        {              -2,               0,               0, 0},
        {               1,              -2,              -2, 0},
        {              -1,               2,              -2, 0},
        {              -1,              -2,               2, 0},
        {               2,              -1,              -2, 0},
        {              -2,               1,              -2, 0},
        {              -2,              -1,               2, 0},
        {               2,              -2,              -4, 0},
        {              -2,               2,              -4, 0},
        {              -2,              -2,               4, 0},

        {             255,             255,           65025, 0},

        {               0,       INT64_MAX,               0, 0},
        {       INT64_MAX,               0,               0, 0},
        {               1,       INT64_MAX,       INT64_MAX, 0},
        {       INT64_MAX,               1,       INT64_MAX, 0},
        {               2,       INT64_MAX,              NA, 1},
        {       INT64_MAX,               2,              NA, 1},
        {              -1,       INT64_MAX,      -INT64_MAX, 0},
        {       INT64_MAX,              -1,      -INT64_MAX, 0},
        {              -2,       INT64_MAX,              NA, 1},
        {       INT64_MAX,              -2,              NA, 1},

        {               0,      -INT64_MAX,               0, 0},
        {      -INT64_MAX,               0,               0, 0},
        {               1,      -INT64_MAX,      -INT64_MAX, 0},
        {      -INT64_MAX,               1,      -INT64_MAX, 0},
        {               2,      -INT64_MAX,              NA, 1},
        {      -INT64_MAX,               2,              NA, 1},
        {              -1,      -INT64_MAX,       INT64_MAX, 0},
        {      -INT64_MAX,              -1,       INT64_MAX, 0},
        {              -2,      -INT64_MAX,              NA, 1},
        {      -INT64_MAX,              -2,              NA, 1},

        {               0,       INT64_MIN,               0, 0},
        {       INT64_MIN,               0,               0, 0},
        {               1,       INT64_MIN,       INT64_MIN, 0},
        {       INT64_MIN,               1,       INT64_MIN, 0},
        {               2,       INT64_MIN,              NA, 1},
        {       INT64_MIN,               2,              NA, 1},
        {              -1,       INT64_MIN,              NA, 1},
        {       INT64_MIN,              -1,              NA, 1},
        {              -2,       INT64_MIN,              NA, 1},
        {       INT64_MIN,              -2,              NA, 1},

        {       INT64_MAX,       INT64_MAX,               0, 1},
        {       INT64_MAX,      -INT64_MAX,               0, 1},
        {      -INT64_MAX,       INT64_MAX,              NA, 1},
        {      -INT64_MAX,      -INT64_MAX,              NA, 1},

        {       INT64_MIN,       INT64_MIN,               0, 1},

        {               0,        UINT_MAX,               0, 0},
        {        UINT_MAX,               0,               0, 0},
        {               1,        UINT_MAX,  1ll * UINT_MAX, 0},
        {        UINT_MAX,               1,  1ll * UINT_MAX, 0},
        {               2,        UINT_MAX,    8589934590ll, 0},
        {        UINT_MAX,               2,    8589934590ll, 0},
        {              -1,        UINT_MAX, -1ll * UINT_MAX, 0},
        {        UINT_MAX,              -1, -1ll * UINT_MAX, 0},
        {              -2,        UINT_MAX, -2ll * UINT_MAX, 0},
        {        UINT_MAX,              -2, -2ll * UINT_MAX, 0},

        {               0, -1ll * UINT_MAX,               0, 0},
        { -1ll * UINT_MAX,               0,               0, 0},
        {               1, -1ll * UINT_MAX, -1ll * UINT_MAX, 0},
        { -1ll * UINT_MAX,               1, -1ll * UINT_MAX, 0},
        {               2, -1ll * UINT_MAX,   -8589934590ll, 0},
        { -1ll * UINT_MAX,               2,   -8589934590ll, 0},
        {              -1, -1ll * UINT_MAX,  1ll * UINT_MAX, 0},
        { -1ll * UINT_MAX,              -1,  1ll * UINT_MAX, 0},
        {              -2, -1ll * UINT_MAX,  2ll * UINT_MAX, 0},
        { -1ll * UINT_MAX,              -2,  2ll * UINT_MAX, 0},

        {               0,         INT_MAX,               0, 0},
        {         INT_MAX,               0,               0, 0},
        {               1,         INT_MAX,   1ll * INT_MAX, 0},
        {         INT_MAX,               1,   1ll * INT_MAX, 0},
        {               2,         INT_MAX,    4294967294ll, 0},
        {         INT_MAX,               2,    4294967294ll, 0},
        {              -1,         INT_MAX,  -1ll * INT_MAX, 0},
        {         INT_MAX,              -1,  -1ll * INT_MAX, 0},
        {              -2,         INT_MAX,  -2ll * INT_MAX, 0},
        {         INT_MAX,              -2,  -2ll * INT_MAX, 0},

        {               0,  -1ll * INT_MAX,               0, 0},
        {  -1ll * INT_MAX,               0,               0, 0},
        {               1,  -1ll * INT_MAX,  -1ll * INT_MAX, 0},
        {  -1ll * INT_MAX,               1,  -1ll * INT_MAX, 0},
        {               2,  -1ll * INT_MAX,   -4294967294ll, 0},
        {  -1ll * INT_MAX,               2,   -4294967294ll, 0},
        {              -1,  -1ll * INT_MAX,   1ll * INT_MAX, 0},
        {  -1ll * INT_MAX,              -1,   1ll * INT_MAX, 0},
        {              -2,  -1ll * INT_MAX,   2ll * INT_MAX, 0},
        {  -1ll * INT_MAX,              -2,   2ll * INT_MAX, 0}
    };
    const struct ent *t;

    (void)argc;
    (void)argv;

    for (i = 0; i < ARRAY_SIZE(tests); i++) {
        int overflow;
        int64_t res;

        t = &tests[i];

        overflow = 0;
        res = muls64s64(t->opnd1, t->opnd2, &overflow);
        if (overflow != t->expected_overflow) {
            errmsgf("Incorrect overflow status %d (expected %d)\n",
                    overflow, t->expected_overflow);
            return EXIT_FAILURE;
        }
        if (!overflow && (res != t->expected_res)) {
            errmsgf("Incorrect result %" PRIi64 " (expected %" PRIi64 ")\n",
                    res, t->expected_res);
            return EXIT_FAILURE;
        }

        infomsgf("Test %zu: ", i + 1);
        if (overflow)
            infomsg("Overflow");
        else {
            infomsgf("%" PRIi64 " * %" PRIi64 " == %" PRIi64,
                     t->opnd1, t->opnd2, res);
        }
        infochr('\n');
    }

    return EXIT_SUCCESS;
}

/* vi: set expandtab sw=4 ts=4: */
