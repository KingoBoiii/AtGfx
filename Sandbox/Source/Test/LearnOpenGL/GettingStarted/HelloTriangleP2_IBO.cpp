#include "HelloTriangleP2_IBO.h"

namespace LearnOpenGL
{

	HelloTriangleP2_IBO::HelloTriangleP2_IBO(AtGfx::GraphicsDevice* graphicsDevice)
		: GraphicsShaderTest(graphicsDevice, "HelloTriangle-P2")
	{
	}

	void HelloTriangleP2_IBO::Initialize()
	{
		GraphicsShaderTest::Initialize();

		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		m_VertexBuffer = AtGfx::Buffer::Create(m_GraphicsDevice, AtGfx::BufferSpecification::CreateVertexBufferSpecification(sizeof(vertices), AtGfx::BufferUsage::StaticDraw, vertices));
		m_IndexBuffer = AtGfx::Buffer::Create(m_GraphicsDevice, AtGfx::BufferSpecification::CreateIndexBufferSpecification(sizeof(indices), AtGfx::BufferUsage::StaticDraw, indices));
	}

	void HelloTriangleP2_IBO::Deinitialize()
	{
		GraphicsShaderTest::Deinitialize();

		delete m_IndexBuffer;
		delete m_VertexBuffer;
	}

	void HelloTriangleP2_IBO::Perform(float glfwTime)
	{
		Clear();

		m_Shader->Bind();
		m_GraphicsDevice->DrawIndexed(m_Pipeline, m_VertexBuffer, m_IndexBuffer);
	}

}