#include "MiosPch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace miosGE {
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			MIOS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:			return std::make_shared<OpenGLTexture2D>(path);
		}

		MIOS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}