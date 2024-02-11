#include "gmpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace EopGuiMaker
{

	std::shared_ptr<spdlog::logger> Log::m_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::m_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		m_CoreLogger = spdlog::stdout_color_mt("EOP");
		m_CoreLogger->set_level(spdlog::level::trace);

		m_ClientLogger = spdlog::stdout_color_mt("APP");
		m_ClientLogger->set_level(spdlog::level::trace);
	}


	Log::Log()
	= default;

	Log::~Log()
	= default;


	
}
