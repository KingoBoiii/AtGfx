#pragma once
#include "Test/Abstractions/GraphicsShaderTest.h"

#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

namespace LearnOpenGL
{

	class HelloTriangleP1_VBO : public GraphicsShaderTest
	{
	public:
		HelloTriangleP1_VBO(AtGfx::GraphicsDevice* graphicsDevice);
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;
		virtual void Perform(float glfwTime) override;
	private:
		AtGfx::Buffer* m_VertexBuffer = nullptr;
	};

}