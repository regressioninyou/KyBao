#include "kbpch.h"
#include "KyBao/Render/VertexArray.h"

#include "KyBao/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace KyBao {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    KyBao_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		KyBao_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}