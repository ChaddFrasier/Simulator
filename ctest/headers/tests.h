#ifndef TEST_H
#define TEST_H

#ifdef _WIN32
#define TEST int WinMain(void)
#define TEST_ARGS int WinMain
#endif

#ifdef _WIN64
#define TEST int WinMain(void)
#define TEST_ARGS int WinMain
#endif

#ifdef __CYGWIN__
#define TEST int WinMain(void)
#define TEST_ARGS int WinMain
#endif

#include <stdio.h>

typedef enum {PASS, FAIL} TEST_STATUS;

#endif