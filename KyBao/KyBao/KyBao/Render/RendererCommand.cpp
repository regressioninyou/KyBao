#include "kbpch.h"
#include "RendererCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace KyBao {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}