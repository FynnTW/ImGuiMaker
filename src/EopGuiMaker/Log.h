#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace EopGuiMaker
{
	class GUIMAKER_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }


		Log();
		
		~Log();

	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;


	};
}

#define GUIMAKER_CORE_ERROR(...)::EopGuiMaker::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GUIMAKER_CORE_WARN(...) ::EopGuiMaker::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GUIMAKER_CORE_INFO(...) ::EopGuiMaker::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GUIMAKER_CORE_TRACE(...)::EopGuiMaker::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define GUIMAKER_APP_ERROR(...) ::EopGuiMaker::Log::GetClientLogger()->error(__VA_ARGS__)
#define GUIMAKER_APP_WARN(...)  ::EopGuiMaker::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GUIMAKER_APP_INFO(...)  ::EopGuiMaker::Log::GetClientLogger()->info(__VA_ARGS__)
#define GUIMAKER_APP_TRACE(...) ::EopGuiMaker::Log::GetClientLogger()->trace(__VA_ARGS__)

