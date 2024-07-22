/*
 * common.h
 */

#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>

#define stderrchr(c) fputc(c, stderr)
#define stderrmsg(msg) fputs(msg, stderr)
#define stderrmsgf(...) fprintf(stderr, __VA_ARGS__)

#define infochr stderrchr
#define infomsg stderrmsg
#define infomsgf stderrmsgf

#define errmsg stderrmsg
#define errmsgf stderrmsgf

#endif

/* vi: set expandtab sw=4 ts=4: */
