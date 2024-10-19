#include "AtomGfx/Pipeline.h"

#include "OpenGL/OpenGLPipeline.h"

namespace AtomGfx
{

	Pipeline* Pipeline::Create(GraphicsDevice* graphicsDevice, const PipelineSpecification& specification)
	{
		switch (graphicsDevice->GetGraphicsAPI())
		{
			case AtomGfx::GraphicsAPI::OpenGL:		return new OpenGLPipeline(graphicsDevice, specification);
			case AtomGfx::GraphicsAPI::Vulkan:
			case AtomGfx::GraphicsAPI::DirectX11:
			case AtomGfx::GraphicsAPI::DirectX12:
			case AtomGfx::GraphicsAPI::None:
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