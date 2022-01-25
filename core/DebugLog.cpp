#include "DebugLog.h"

#include <cstdarg>
#include <cstdio>

static const char* LOG_LABELS[MAX_LOG_TYPE] = {
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

bool DebugLog::s_bExtraInfo = false;

void DebugLog::Init(LogConfig config)
{
    if ((int)config & (int)LogConfig::EXTRA_INFO)
    {
        s_bExtraInfo = true;
    }
}

void DebugLog::LogMessage(LogType type, const char* fileName, int line, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (s_bExtraInfo)
    {
        fprintf(stdout, "[%s] %s:%d ", LOG_LABELS[(int)type], fileName, line);
    }
    else
    {
        fprintf(stdout, "[%s] ", LOG_LABELS[(int)type]);
    }

    vfprintf(stdout, fmt, args);

    va_end(args);
}