#include "AtGfx/Buffer.h"

#include "OpenGL/OpenGLBuffer.h"

namespace AtGfx
{

	Buffer* Buffer::Create(GraphicsDevice* graphicsDevice, const BufferSpecification& specification)
	{
		switch (graphicsDevice->GetGraphicsAPI())
		{
			case AtGfx::GraphicsAPI::OpenGL:		return new OpenGLBuffer(graphicsDevice, specification);
			case AtGfx::GraphicsAPI::Vulkan:
			case AtGfx::GraphicsAPI::DirectX11:
			case AtGfx::GraphicsAPI::DirectX12:
			case AtGfx::GraphicsAPI::None:
			default:
				break;
		}

		return nullptr;
	}

	Buffer::Buffer(GraphicsDevice* graphicsDevice, const BufferSpecification& specification)
		: m_GraphicsDevice(graphicsDevice), m_Specification(specification), m_Type(specification.Type)
	{
	}

}