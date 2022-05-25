#include "MiosPch.h"
#include "GraphicsContext.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace miosGE
{
    Scope<GraphicsContext> miosGE::GraphicsContext::Create(void* window)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MIOS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		MIOS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}