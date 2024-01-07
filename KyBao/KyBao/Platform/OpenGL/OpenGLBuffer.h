#pragma once
#include "KyBao/Render/Buffer.h"
namespace KyBao {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		virtual void Bind()const ;
		virtual void UnBind()const;
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		virtual BufferLayout& GetLayout()override { return m_Layout; };
	private:
		uint32_t m_RenderID;
		BufferLayout m_Layout;
	};
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		virtual void Bind()const  ;
		virtual void UnBind()const ;

		virtual uint32_t GetCount() const { return m_count; };
	private:
		uint32_t m_RenderID;
		uint32_t m_count;
	};
}