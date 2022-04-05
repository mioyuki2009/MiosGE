#include "MiosPch.h"

#include "OpenGLContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <gl/GL.h>
#include "Debug/Instrumentor.h"
namespace miosGE {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
		m_WindowHandle(windowHandle)
	{
		MIOS_CORE_ASSERT(m_WindowHandle, "Window Handle is null");
	}
	OpenGLContext::~OpenGLContext() {

	}
	
	void OpenGLContext::Init() {
		MIOS_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MIOS_CORE_ASSERT(status, "Failed to initialize Glad");

		MIOS_CORE_INFO("OpenGL info:");
		MIOS_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		MIOS_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		MIOS_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers() {
		MIOS_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
