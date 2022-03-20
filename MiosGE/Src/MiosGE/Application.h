#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
namespace miosGE {

	class MIOS_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Runing = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;

	};

	Application* CreateApplication();

}