#include "AtomGfx/Texture.h"

#include "OpenGL/OpenGLTexture.h"

namespace AtomGfx
{

	Texture* Texture::Create(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const TextureSpecification& specification)
	{
		switch (graphicsDevice->GetGraphicsAPI())
		{
			case AtomGfx::GraphicsAPI::OpenGL:		return new OpenGLTexture(graphicsDevice, filepath, specification);
			case AtomGfx::GraphicsAPI::Vulkan:
			case AtomGfx::GraphicsAPI::DirectX11:
			case AtomGfx::GraphicsAPI::DirectX12:
			case AtomGfx::GraphicsAPI::None:
			default: break;
		}

		return nullptr;
	}

	Texture::Texture(GraphicsDevice* graphicsDevice, const std::filesystem::path& filepath, const TextureSpecification& specification)
		: m_GraphicsDevice(graphicsDevice), m_FilePath(filepath), m_Specification(specification), m_Width(0), m_Height(0)
	{
	}

}