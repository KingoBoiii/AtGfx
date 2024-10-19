#include "AtGfx/Pipeline.h"

#include "OpenGL/OpenGLPipeline.h"

namespace AtGfx
{

	Pipeline* Pipeline::Create(GraphicsDevice* graphicsDevice, const PipelineSpecification& specification)
	{
		switch (graphicsDevice->GetGraphicsAPI())
		{
			case AtGfx::GraphicsAPI::OpenGL:		return new OpenGLPipeline(graphicsDevice, specification);
			case AtGfx::GraphicsAPI::Vulkan:
			case AtGfx::GraphicsAPI::DirectX11:
			case AtGfx::GraphicsAPI::DirectX12:
			case AtGfx::GraphicsAPI::None:
			default:
				break;
		}

		return nullptr;
	}

	Pipeline::Pipeline(GraphicsDevice* graphicsDevice, const PipelineSpecification& specification)
		: m_GraphicsDevice(graphicsDevice), m_Specification(specification)
	{
	}

}