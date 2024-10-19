#pragma once
#include "Bindable.h"
#include "AtomGfx/GraphicsDevice.h"
#include "AtomGfx/VertexAttributeLayout.h"

namespace AtomGfx
{

	struct PipelineSpecification
	{
		VertexAttributeLayout VertexAttributeLayout;
	};

	class Pipeline : public Internal::Bindable
	{
	public:
		static Pipeline* Create(GraphicsDevice* graphicsDevice, const PipelineSpecification& specification);
	public:
		virtual ~Pipeline() = default;
	protected:
		Pipeline(GraphicsDevice* graphicsDevice, const PipelineSpecification& specification);
	protected:
		GraphicsDevice* m_GraphicsDevice = nullptr;
		PipelineSpecification m_Specification;
	};

	using VertexArray = Pipeline;

}
