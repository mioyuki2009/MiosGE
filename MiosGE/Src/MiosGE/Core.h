#pragma once

#ifdef MIOS_WIN64
	#ifdef MIOS_BUILDDLL
		#define MIOS_API __declspec(dllexport)
	#else
		#define MIOS_API __declspec(dllimport)
	#endif
#else
	#error only support windows
#endif

#define BIT(x) (1 << x)
