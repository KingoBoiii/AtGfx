#pragma once
#include "LearnOpenGLTest.h"

#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

namespace LearnOpenGL
{

	class HelloTriangleP1 : public LearnOpenGLTest
	{
	public:
		HelloTriangleP1(AtGfx::GraphicsDevice* graphicsDevice);
		virtual ~HelloTriangleP1() = default;
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;
		virtual void Perform() override;
	private:
		AtGfx::Pipeline* m_Pipeline = nullptr;
		AtGfx::Buffer* m_VertexBuffer = nullptr;
	};

}