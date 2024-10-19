#pragma once
#include "AtomGfx/Texture.h"

namespace AtomGfx
{

	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const TextureSpecification& specification);
		virtual ~OpenGLTexture();
	public:
		virtual void Bind(uint32_t slot = 0) const override;
		virtual void Unbind() const override;
	private:
		void SetTextureParameters();
	private:
		uint32_t m_RendererId;
	};

}
