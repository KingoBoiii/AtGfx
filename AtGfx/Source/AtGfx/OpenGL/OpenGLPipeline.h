#pragma once
#include "AtGfx/Pipeline.h"

namespace AtGfx
{

	class OpenGLPipeline : public Pipeline
	{
	public:
		OpenGLPipeline(GraphicsDevice* graphicsDevice, const PipelineSpecification& specification);
		virtual ~OpenGLPipeline();
	public:
		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererId;
	};

}

