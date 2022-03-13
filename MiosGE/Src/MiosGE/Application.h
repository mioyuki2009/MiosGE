#pragma once

#include "Core.h"

namespace miosGE {

	class MIOS_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
	};

	Application* CreateApplication();

}