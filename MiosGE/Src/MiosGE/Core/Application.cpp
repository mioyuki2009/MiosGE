#include "MiosPch.h"
#include "Application.h"

#include "Log.h"
#include "glad/glad.h"
#include "Renderer/Renderer.h"
#include "Input.h"

#include "GLFW/glfw3.h"
#include "Debug/Instrumentor.h"

namespace miosGE {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		MIOS_PROFILE_FUNCTION();

		MIOS_CORE_ASSERT(!s_Instance, "Application aleady exists!");

		s_Instance = this;

		m_Runing = true;

		m_Window = Scope<Window>(Window::Create(WindowsProps(name)));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
		MIOS_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer) {
		MIOS_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer* layer) {
		MIOS_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close(){
		m_Runing = false;
	}

	void Application::OnEvent(Event& e) {
		MIOS_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	
	void Application::Run() {
		MIOS_PROFILE_FUNCTION();

		while (m_Runing) {
			MIOS_PROFILE_SCOPE("RunLoop");
			
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				
				{
					MIOS_PROFILE_SCOPE("LayerStack OnUpdate");

					for (const auto& layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();

				{
					MIOS_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (const auto& layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Runing = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		MIOS_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

}

