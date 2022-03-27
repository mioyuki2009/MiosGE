#include "MiosPch.h"
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace miosGE {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
