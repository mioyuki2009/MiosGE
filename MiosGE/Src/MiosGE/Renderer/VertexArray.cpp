#include "MiosPch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace miosGE{
	Ref<VertexArray> VertexArray::Create() {
		MIOS_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:			MIOS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:			return std::make_shared<OpenGLVertexArray>();
		}

		MIOS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}