#include "AtomGfx/GraphicsDevice.h"

#include "OpenGL/OpenGLGraphicsDevice.h"

namespace AtomGfx
{

	GraphicsDevice* GraphicsDevice::Create(GraphicsAPI graphicsAPI, GraphicsDeviceSpecification specification)
	{
		switch (graphicsAPI)
		{
			case AtomGfx::GraphicsAPI::OpenGL:		return new OpenGLGraphicsDevice(specification);
			case AtomGfx::GraphicsAPI::Vulkan:
			case AtomGfx::GraphicsAPI::DirectX11:
			case AtomGfx::GraphicsAPI::DirectX12:
			case AtomGfx::GraphicsAPI::None:
			default: break;
		}

		return nullptr;
	}

	GraphicsDevice::GraphicsDevice(GraphicsAPI graphicsAPI, GraphicsDeviceSpecification specification)
		: m_GraphicsAPI(graphicsAPI), m_Specification(specification)
	{
	}

}