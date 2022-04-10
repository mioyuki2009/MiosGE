
#include "MiosPch.h"
#include "Framebuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace miosGE {
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:			MIOS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:			return CreateRef<OpenGLFramebuffer>(spec);
		}

		MIOS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
