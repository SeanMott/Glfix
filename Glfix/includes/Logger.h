//defines a logger for glfix

#ifndef Logger_h
#define Logger_h

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define LogMessage(message) printf("%s\n", message);

#ifdef GLFIX_RELEASE

#define LogWarning(code, message)
#define LogError(code, message)
#define LogFatalError(code, message) printf("Glfix Fatal Error: %s || %s\n", code, message); getchar(); exit(1);

#define LogData(formate, ...)
#define LogFatalData(formate, ...) printf(formate, __VA_ARGS__); getchar(); exit(1);

#endif

#ifdef GLFIX_DIST

#define LogWarning(code, message)
#define LogError(code, message)
#define LogFatalError(code, message) exit(1);

#define LogData(formate, ...)
#define LogFatalData(formate, ...) printf(formate, __VA_ARGS__); exit(1);

#endif

#ifdef GLFIX_DEBUG

#define LogWarning(code, message) printf("Glfix Warning : %s || %s\n", code, message);
#define LogError(code, message) printf("Glfix Error : %s || %s\n", code, message);
#define LogFatalError(code, message) printf("Glfix Fatal Error: %s || %s\n", code, message); getchar(); exit(1);

#define LogData(formate, ...) printf(formate, __VA_ARGS__);
#define LogFatalData(formate, ...) printf(formate, __VA_ARGS__); getchar(); exit(1);

#endif

#ifndef LogWarning(code, message)
#define LogWarning(code, message)
#endif
#ifndef LogError(code, message)
#define LogError(code, message)
#endif
#ifndef LogFatalError(code, message)
#define LogFatalError(code, message)
#endif
#ifndef LogData(formate, ...)
#define LogData(formate, ...)
#endif
#ifndef LogFatalData(formate, ...)
#define LogFatalData(formate, ...)
#endif

#endif