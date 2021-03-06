#pragma once
#include "Renderer/Texture.h"
#include "glad/glad.h"
namespace miosGE{
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
	
		virtual bool IsLoaded() const override { return m_IsLoaded; }

		virtual bool operator==(const Texture& other) const override {
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		};

	private:
		std::string m_Path;
		bool m_IsLoaded = false;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
		uint32_t m_RendererID = 0;
		GLenum m_InternalFormat = 0;
		GLenum m_DataFormat = 0;
	};
}