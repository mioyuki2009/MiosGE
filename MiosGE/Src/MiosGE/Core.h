#pragma once

#ifdef MIOS_WIN64
#if MIOS_DYNAMIC_LINK
	#ifdef MIOS_BUILDDLL
		#define MIOS_API __declspec(dllexport)
	#else
		#define MIOS_API __declspec(dllimport)
	#endif
#else
#define MIOS_API
#endif
#else
	#error only support windows
#endif

#ifdef MIOS_ENABLE_ASSERTS
#define MIOS_ASSERT(x, ...) {if (!(x)){ MIOS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#define MIOS_CORE_ASSERT(x, ...) {if (!(x)){ MIOS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define MIOS_ASSERT(x, ...)
#define MIOS_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define MIOS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
