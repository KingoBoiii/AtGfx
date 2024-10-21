#pragma once
#include "LearnOpenGLTest.h"

#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

namespace LearnOpenGL
{

	class HelloTriangleP2 : public LearnOpenGLTest
	{
	public:
		HelloTriangleP2(AtGfx::GraphicsDevice* graphicsDevice);
		virtual ~HelloTriangleP2() = default;
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;
		virtual void Perform() override;
	private:
		AtGfx::Pipeline* m_Pipeline = nullptr;
		AtGfx::Buffer* m_VertexBuffer = nullptr;
		AtGfx::Buffer* m_IndexBuffer = nullptr;
	};

}
