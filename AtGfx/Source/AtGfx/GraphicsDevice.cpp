#include "AtGfx/GraphicsDevice.h"

#include "OpenGL/OpenGLGraphicsDevice.h"

namespace AtGfx
{

	GraphicsDevice* GraphicsDevice::Create(GraphicsAPI graphicsAPI, GraphicsDeviceSpecification specification)
	{
		switch (graphicsAPI)
		{
			case AtGfx::GraphicsAPI::OpenGL:		return new OpenGLGraphicsDevice(specification);
			case AtGfx::GraphicsAPI::Vulkan:
			case AtGfx::GraphicsAPI::DirectX11:
			case AtGfx::GraphicsAPI::DirectX12:
			case AtGfx::GraphicsAPI::None:
			default: break;
		}

		return nullptr;
	}

	GraphicsDevice::GraphicsDevice(GraphicsAPI graphicsAPI, GraphicsDeviceSpecification specification)
		: m_GraphicsAPI(graphicsAPI), m_Specification(specification)
	{
	}

}