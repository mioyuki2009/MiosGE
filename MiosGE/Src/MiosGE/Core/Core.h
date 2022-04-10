#pragma once

#include <memory>

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

namespace miosGE {

	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
