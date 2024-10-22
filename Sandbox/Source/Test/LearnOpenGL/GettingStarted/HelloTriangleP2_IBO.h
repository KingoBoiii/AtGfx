#pragma once
#include "Test/Abstractions/GraphicsShaderTest.h"

#include <AtGfx/Buffer.h>

namespace LearnOpenGL
{

	class HelloTriangleP2_IBO : public GraphicsShaderTest
	{
	public:
		HelloTriangleP2_IBO(AtGfx::GraphicsDevice* graphicsDevice);
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;
		virtual void Perform(float glfwTime) override;
	private:
		AtGfx::Buffer* m_VertexBuffer = nullptr;
		AtGfx::Buffer* m_IndexBuffer = nullptr;
	};

}
