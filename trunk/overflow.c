/*
 * overflow.c
 */

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int add64(int64_t *, int64_t, int64_t);

int
main(int argc, char **argv)
{
    int64_t res = 0;

    if (add64(&res, INT64_MAX, 1))
        puts("Overflow");
    else
        printf("%" PRIi64 "\n", res);

    if (add64(&res, 2, -6))
        puts("Overflow");
    else
        printf("%" PRIi64 "\n", res);

    return EXIT_SUCCESS;
}

/* vi: set expandtab sw=4 ts=4: */
