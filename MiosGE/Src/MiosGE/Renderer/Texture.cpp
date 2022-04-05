#include "MiosPch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace miosGE {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			MIOS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:			return CreateRef<OpenGLTexture2D>(width, height);
		}

		MIOS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			MIOS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:			return CreateRef<OpenGLTexture2D>(path);
		}

		MIOS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}