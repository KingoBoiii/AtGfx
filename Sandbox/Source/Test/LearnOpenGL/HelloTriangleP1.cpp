#include "HelloTriangleP1.h"

namespace LearnOpenGL
{

	HelloTriangleP1::HelloTriangleP1(AtGfx::GraphicsDevice* graphicsDevice)
		: LearnOpenGLTest(graphicsDevice)
	{
	}

	void HelloTriangleP1::Initialize()
	{
		m_Pipeline = AtGfx::Pipeline::Create(m_GraphicsDevice, {
		    .VertexAttributeLayout = {
		        { AtGfx::ShaderDataType::Float3, "POSITION" }
		    }
		});

		float vertices[] = {
		    -0.5f, -0.5f, 0.0f,
		     0.5f, -0.5f, 0.0f,
		     0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer = AtGfx::Buffer::Create(m_GraphicsDevice, AtGfx::BufferSpecification::CreateVertexBufferSpecification(sizeof(vertices), AtGfx::BufferUsage::StaticDraw, vertices));
	}

	void HelloTriangleP1::Deinitialize()
	{
		delete m_VertexBuffer;
		delete m_Pipeline;
	}

	void HelloTriangleP1::Perform()
	{
		Clear();

		m_GraphicsDevice->Draw(m_Pipeline, m_VertexBuffer);
	}

}