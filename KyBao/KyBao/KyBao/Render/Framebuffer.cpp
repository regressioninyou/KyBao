#include "kbpch.h"
#include "Framebuffer.h"
#include "KyBao/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace KyBao {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    KyBao_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		KyBao_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}