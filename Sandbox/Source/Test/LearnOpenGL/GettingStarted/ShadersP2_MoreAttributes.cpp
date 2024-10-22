#include "ShadersP2_MoreAttributes.h"

namespace LearnOpenGL
{

	ShadersP2_MoreAttributes::ShadersP2_MoreAttributes(AtGfx::GraphicsDevice* graphicsDevice)
		: GraphicsShaderTest(graphicsDevice, "Shaders-P2")
	{
	}

	void ShadersP2_MoreAttributes::Initialize()
	{
		GraphicsShaderTest::Initialize();

		float vertices[] = {
			// positions         // colors
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
		};

		m_VertexBuffer = AtGfx::Buffer::Create(m_GraphicsDevice, AtGfx::BufferSpecification::CreateVertexBufferSpecification(sizeof(vertices), AtGfx::BufferUsage::StaticDraw, vertices));
	}

	void ShadersP2_MoreAttributes::Deinitialize()
	{
		GraphicsShaderTest::Deinitialize();

		delete m_VertexBuffer;
	}

	void ShadersP2_MoreAttributes::Perform(float glfwTime)
	{
		Clear();

		m_Shader->Bind();
		m_GraphicsDevice->Draw(m_Pipeline, m_VertexBuffer);
	}

}