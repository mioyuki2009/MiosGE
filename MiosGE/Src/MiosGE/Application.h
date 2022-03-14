#pragma once

#include "Core.h"
#include "Events/Event.h"
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