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

enum class LogConfig
{
	NOTHING				= 1 << 0,
	EXTRA_INFO			= 1 << 1,
};

#define MAX_LOG_TYPE ((int)LogType::FATAL + 1)

#define DEBUG_INFO(...)          DebugLog::LogMessage(LogType::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG_WARN(...)          DebugLog::LogMessage(LogType::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG_ERROR(...)         DebugLog::LogMessage(LogType::ERR, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG_CRITICAL(...)      DebugLog::LogMessage(LogType::FATAL, __FILE__, __LINE__, __VA_ARGS__)

class DebugLog
{
public:
	static void Init(LogConfig config);
	static void LogMessage(LogType type, const char* fileName, int line, const char* fmt, ...);
private:
	static bool s_bExtraInfo;
};


#endif // _LOG_H_