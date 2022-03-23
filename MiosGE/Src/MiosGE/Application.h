#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Runing = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

	private:
		static Application* s_Instance;

	};

	Application* CreateApplication();

}