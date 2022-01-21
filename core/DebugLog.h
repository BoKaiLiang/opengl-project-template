#ifndef _LOG_H_
#define _LOG_H_

#include <cstdarg>

enum class LogType
{
	INFO,
	WARN,
	ERR,
	FATAL,
};

#define MAX_LOG_TYPE ((int)LogType::FATAL + 1)

#define DEBUG_INFO(...)          LogMessage(LogType::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG_WARN(...)          LogMessage(LogType::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG_ERROR(...)         LogMessage(LogType::ERR, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG_CRITICAL(...)      LogMessage(LogType::FATAL, __FILE__, __LINE__, __VA_ARGS__)

void LogMessage(LogType type, const char* fileName, int line, const char* fmt, ...);

#endif // _LOG_H_