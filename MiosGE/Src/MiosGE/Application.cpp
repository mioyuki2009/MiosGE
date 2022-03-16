#include "MiosPch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"

#include "GLFW/glfw3.h"

namespace miosGE {
	Application::Application() {
		m_Runing = true;

		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}


	void Application::Run() {

		while (m_Runing) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}

