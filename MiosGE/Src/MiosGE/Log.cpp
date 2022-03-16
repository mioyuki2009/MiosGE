#include "MiosPch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
namespace miosGE {
	std::shared_ptr<spdlog::logger> Log::m_spCoreLogger;
	std::shared_ptr<spdlog::logger> Log::m_spClientLogger;

	Log::Log() {}
	Log::~Log() {}
	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		m_spCoreLogger = spdlog::stdout_color_mt("miosGE");
		m_spCoreLogger->set_level(spdlog::level::trace);
		m_spClientLogger = spdlog::stdout_color_mt("app");
		m_spClientLogger->set_level(spdlog::level::trace);

	}

}