#ifndef BITCOIN_LOGGING_H
#define BITCOIN_LOGGING_H
#include <cstdio>
#include <cstdarg>
#include <string>
inline void LogPrintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}
#define LogPrint(category, ...) LogPrintf(__VA_ARGS__)
#endif // BITCOIN_LOGGING_H
