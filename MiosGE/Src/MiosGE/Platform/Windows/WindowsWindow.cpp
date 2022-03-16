#include "MiosPch.h"
#include "WindowsWindow.h"

namespace miosGE {
   
	static bool s_GLFWInitalized = false;

	Window* Window::Create(const WindowsProps& props) {
		return new WindowsWindow(props);
	}

    WindowsWindow::WindowsWindow(const WindowsProps& props) {
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {}

    void WindowsWindow::Init(const WindowsProps& props) {
        m_Data.Title = props.Title;
        m_Data.Height = props.Height;
        m_Data.Width = props.Width;

        MIOS_CORE_INFO("Create window {0},{1},{2}", props.Title, props.Width, props.Height);

        if (!s_GLFWInitalized) {
            int success = glfwInit();
            MIOS_CORE_ASSERT(success, "Cound not intialize GLFW!");

            s_GLFWInitalized = true;
        }
        m_Windows = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Windows);
        glfwSetWindowUserPointer(m_Windows, &m_Data);

        SetVSync(true);
    }

    void WindowsWindow::ShutDown() {
        glfwDestroyWindow(m_Windows);
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Windows);
    }

    void WindowsWindow::SetVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }
    
    bool WindowsWindow::IsVSync() const {
        return m_Data.VSync;
    }

}
