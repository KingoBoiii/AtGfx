#include "AtGfx/Texture.h"

#include "OpenGL/OpenGLTexture.h"

namespace AtGfx
{

	Texture* Texture::Create(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const TextureSpecification& specification)
	{
		switch (graphicsDevice->GetGraphicsAPI())
		{
			case AtGfx::GraphicsAPI::OpenGL:		return new OpenGLTexture(graphicsDevice, filepath, specification);
			case AtGfx::GraphicsAPI::Vulkan:
			case AtGfx::GraphicsAPI::DirectX11:
			case AtGfx::GraphicsAPI::DirectX12:
			case AtGfx::GraphicsAPI::None:
			default: break;
		}

		return nullptr;
	}

	Texture::Texture(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const TextureSpecification& specification)
		: m_GraphicsDevice(graphicsDevice), m_FilePath(filepath), m_Specification(specification), m_Width(0), m_Height(0)
	{
	}

}