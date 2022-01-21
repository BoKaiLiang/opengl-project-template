#include "DebugLog.h"

#include <cstdarg>
#include <cstdio>

static const char* LOG_LABELS[MAX_LOG_TYPE] = {
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

void LogMessage(LogType type, const char* fileName, int line, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    fprintf(stdout, "[%s] %s:%d ", LOG_LABELS[(int)type], fileName, line);
    vfprintf(stdout, fmt, args);
    fprintf(stdout, "\n");

    va_end(args);
}