#ifndef _LOG_H_
#define _LOG_H_

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

#define DEBUG_TRACE(...)         Log::GetLogger()->trace(__VA_ARGS__)
#define DEBUG_INFO(...)          Log::GetLogger()->info(__VA_ARGS__)
#define DEBUG_WARN(...)          Log::GetLogger()->warn(__VA_ARGS__)
#define DEBUG_ERROR(...)         Log::GetLogger()->error(__VA_ARGS__)
#define DEBUG_CRITICAL(...)      Log::GetLogger()->critical(__VA_ARGS__)

#endif // _LOG_H_