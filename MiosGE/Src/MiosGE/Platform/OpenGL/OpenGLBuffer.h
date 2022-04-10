#pragma once

#include <stdint.h>
#include "Renderer/Buffer.h"

namespace miosGE {
	class OpenGLVertexBuffer :public VertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		
		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override { return m_Layerout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layerout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layerout;
	};

	class OpenGLIndexBuffer :public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; } 

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}
