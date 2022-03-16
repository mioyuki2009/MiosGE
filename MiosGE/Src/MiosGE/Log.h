#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace miosGE{

class MIOS_API Log
{
public:
	Log();
	virtual ~Log();

public:
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_spClientLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_spCoreLogger; }
private:

	static std::shared_ptr<spdlog::logger> m_spCoreLogger;
	static std::shared_ptr<spdlog::logger> m_spClientLogger;

};

}

#define MIOS_CORE_TRACE(...)	::miosGE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MIOS_CORE_INFO(...)		::miosGE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MIOS_CORE_WARN(...)		::miosGE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MIOS_CORE_ERROR(...)	::miosGE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MIOS_CORE_Fatal(...)	::miosGE::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define MIOS_CORE_A(...)	::miosGE::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define MIOS_TRACE(...)			::miosGE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MIOS_INFO(...)			::miosGE::Log::GetClientLogger()->info(__VA_ARGS__)
#define MIOS_WARN(...)			::miosGE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MIOS_ERROR(...)			::miosGE::Log::GetClientLogger()->error(__VA_ARGS__)
#define MIOS_Fatal(...)			::miosGE::Log::GetClientLogger()->fatal(__VA_ARGS__)