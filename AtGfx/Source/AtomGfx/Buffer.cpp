#include "AtomGfx/Buffer.h"

#include "OpenGL/OpenGLBuffer.h"

namespace AtomGfx
{

	Buffer* Buffer::Create(GraphicsDevice* graphicsDevice, const BufferSpecification& specification)
	{
		switch (graphicsDevice->GetGraphicsAPI())
		{
			case AtomGfx::GraphicsAPI::OpenGL:		return new OpenGLBuffer(graphicsDevice, specification);
			case AtomGfx::GraphicsAPI::Vulkan:
			case AtomGfx::GraphicsAPI::DirectX11:
			case AtomGfx::GraphicsAPI::DirectX12:
			case AtomGfx::GraphicsAPI::None:
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