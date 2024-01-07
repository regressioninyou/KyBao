#pragma once 
#include "KyBao/Render/Framebuffer.h"
namespace KyBao {
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		~OpenGLFramebuffer();

		void Invalidate();

		// 通过 Framebuffer 继承
		void Bind() override;

		void Unbind() override;

		void Resize(uint32_t width, uint32_t height) override;

		int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		void ClearAttachment(uint32_t attachmentIndex, int value) override;

		uint32_t GetColorAttachmentRendererID(uint32_t index) const override { return m_ColorAttachment; };

		const FramebufferSpecification& GetSpecification() const override { return m_Specificaation; };
	private:
		void BindBufferFramer();
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FramebufferSpecification m_Specificaation;
	};
}