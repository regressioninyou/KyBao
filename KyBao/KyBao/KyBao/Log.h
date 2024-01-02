#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
namespace KyBao {
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
// Core log macros
#define KyBao_CORE_TRACE(...)    ::KyBao::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KyBao_CORE_INFO(...)     ::KyBao::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KyBao_CORE_WARN(...)     ::KyBao::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KyBao_CORE_ERROR(...)    ::KyBao::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KyBao_CORE_CRITICAL(...) ::KyBao::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define KyBao_TRACE(...)         ::KyBao::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KyBao_INFO(...)          ::KyBao::Log::GetClientLogger()->info(__VA_ARGS__)
#define KyBao_WARN(...)          ::KyBao::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KyBao_ERROR(...)         ::KyBao::Log::GetClientLogger()->error(__VA_ARGS__)
#define KyBao_CRITICAL(...)      ::KyBao::Log::GetClientLogger()->critical(__VA_ARGS__)
