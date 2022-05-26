#include "MiosPch.h"
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace miosGE {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
