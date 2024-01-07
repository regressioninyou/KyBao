#include "kbpch.h"
#include "OpenGLFramebuffer.h"
#include <glad/glad.h>
namespace KyBao {
	static const uint32_t MaxFramerBufferSize = 8192;
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		:m_Specificaation(spec), m_RendererID(0) {
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		glCreateFramebuffers(1, &m_RendererID);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		BindBufferFramer();
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specificaation.Width, m_Specificaation.Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width < 360)
			width = 360;
		else if (width > MaxFramerBufferSize)
			width = MaxFramerBufferSize;
		if (height < 360)
			height = 360;
		else if (height > MaxFramerBufferSize)
			height = MaxFramerBufferSize;
		m_Specificaation.Width = width;
		m_Specificaation.Height = height;
		BindBufferFramer();
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		return 0;
	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
	}

	void OpenGLFramebuffer::BindBufferFramer()
	{
		Bind();
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specificaation.Width, m_Specificaation.Height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		//glTexStorage2D(GL_TEXTURE_2D,0,GL_DEPTH8,m_spa);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specificaation.Width, m_Specificaation.Height,
			0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
		KyBao_CORE_ASSERT(glCheckNamedFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framerbuffer is not complete");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


}