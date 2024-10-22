#include "HelloTriangleP1_VBO.h"

namespace LearnOpenGL
{

	HelloTriangleP1_VBO::HelloTriangleP1_VBO(AtGfx::GraphicsDevice* graphicsDevice)
		: GraphicsShaderTest(graphicsDevice, "HelloTriangle-P1")
	{
	}

	void HelloTriangleP1_VBO::Initialize()
	{
		GraphicsShaderTest::Initialize();

		float vertices[] = {
		    -0.5f, -0.5f, 0.0f,
		     0.5f, -0.5f, 0.0f,
		     0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer = AtGfx::Buffer::Create(m_GraphicsDevice, AtGfx::BufferSpecification::CreateVertexBufferSpecification(sizeof(vertices), AtGfx::BufferUsage::StaticDraw, vertices));
	}

	void HelloTriangleP1_VBO::Deinitialize()
	{
		GraphicsShaderTest::Deinitialize();

		delete m_VertexBuffer;
	}

	void HelloTriangleP1_VBO::Perform(float glfwTime)
	{
		Clear();

		m_Shader->Bind();
		m_GraphicsDevice->Draw(m_Pipeline, m_VertexBuffer);
	}

}