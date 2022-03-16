#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
namespace miosGE {

	class MIOS_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Runing;
	};

	Application* CreateApplication();

}