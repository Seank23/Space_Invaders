#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace SpaceInvaders
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

// Client log macros
#define INFO(...)	::SpaceInvaders::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TRACE(...)	::SpaceInvaders::Log::GetClientLogger()->info(__VA_ARGS__)
#define WARN(...)	::SpaceInvaders::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ERROR(...)	::SpaceInvaders::Log::GetClientLogger()->error(__VA_ARGS__)
#define FATAL(...)	::SpaceInvaders::Log::GetClientLogger()->fatal(__VA_ARGS__)

