#include "MiosPch.h"
#include "WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Debug/Instrumentor.h"
namespace miosGE {
   
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error_code, const char* description) {
        MIOS_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
    
    }

	Window* Window::Create(const WindowsProps& props) {
		return new WindowsWindow(props);
	}

    WindowsWindow::WindowsWindow(const WindowsProps& props) {
        MIOS_PROFILE_FUNCTION();
        
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        MIOS_PROFILE_FUNCTION();
        
        Shutdown();
    }

    void WindowsWindow::Init(const WindowsProps& props) {
        MIOS_PROFILE_FUNCTION();

        m_Data.Title = props.Title;
        m_Data.Height = props.Height;
        m_Data.Width = props.Width;

        
        MIOS_CORE_INFO("Create window {0},{1},{2}", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0) {
            MIOS_PROFILE_SCOPE("glfwInit");
            int success = glfwInit();
            MIOS_CORE_ASSERT(success, "Cound not intialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback); 
        }

        {
            MIOS_PROFILE_SCOPE("glfwCreateWindow");
            m_Windows = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
            ++s_GLFWWindowCount;
        }

        m_Context = new OpenGLContext(m_Windows);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Windows, &m_Data);

        SetVSync(true);

        glfwSetWindowSizeCallback(m_Windows, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);

            });

        glfwSetWindowCloseCallback(m_Windows, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
            });

        glfwSetKeyCallback(m_Windows, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, mods, 0);
                data.EventCallback(event);
            }
                break;
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key, mods);
                data.EventCallback(event);
            }
                break;
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, mods, 1);
                data.EventCallback(event);
            }
                break;
            default:
                break;
            }
            });

        glfwSetCharCallback(m_Windows, [](GLFWwindow* window, unsigned int codepoint) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(codepoint, 0);
            data.EventCallback(event);
            });


        glfwSetMouseButtonCallback(m_Windows, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
            }
            break;
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
            }
            break;
            default:
                break;
            }

            });

        glfwSetScrollCallback(m_Windows, [](GLFWwindow* window, double xoffset, double yoffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);
            });

        glfwSetCursorPosCallback(m_Windows, [](GLFWwindow* window, double xpos, double ypos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
            });
    }

    void WindowsWindow::Shutdown() {
        MIOS_PROFILE_FUNCTION();

        glfwDestroyWindow(m_Windows);
        --s_GLFWWindowCount;

        if (s_GLFWWindowCount == 0)
        {
            glfwTerminate();
        }
    }

    void WindowsWindow::OnUpdate() {
        MIOS_PROFILE_FUNCTION();
        
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled) {
        MIOS_PROFILE_FUNCTION();

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
