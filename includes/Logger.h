//defines a Logger for Glfix

#ifndef Logger_h
#define Logger_h

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define LogWarning(code, message) printf("Glfix Warning : %s || %s\n", code, message);
#define LogError(code, message) printf("Glfix Error : %s || %s\n", code, message);
#define LogFatalError(code, message) printf("Glfix Fatal Error: %s || %s\n", code, message); getchar(); exit(1);

#define LogData(formate, ...) printf(formate, __VA_ARGS__);
#define LogFatalData(formate, ...) printf(formate, __VA_ARGS__); getchar(); exit(1);

#endif