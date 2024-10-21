#include "HelloTriangleP2.h"

namespace LearnOpenGL
{

	HelloTriangleP2::HelloTriangleP2(AtGfx::GraphicsDevice* graphicsDevice)
		: LearnOpenGLTest(graphicsDevice)
	{
	}

	void HelloTriangleP2::Initialize()
	{
		m_Pipeline = AtGfx::Pipeline::Create(m_GraphicsDevice, {
			.VertexAttributeLayout = {
				{ AtGfx::ShaderDataType::Float3, "POSITION" }
			}
		});

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

	void HelloTriangleP2::Deinitialize()
	{
		delete m_IndexBuffer;
		delete m_VertexBuffer;
		delete m_Pipeline;
	}

	void HelloTriangleP2::Perform()
	{
		Clear();

		m_GraphicsDevice->DrawIndexed(m_Pipeline, m_VertexBuffer, m_IndexBuffer);
	}

}