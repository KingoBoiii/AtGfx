#include "ShadersP1_Uniforms.h"

namespace LearnOpenGL
{

	ShadersP1_Uniforms::ShadersP1_Uniforms(AtGfx::GraphicsDevice* graphicsDevice)
		: GraphicsShaderTest(graphicsDevice, "Shaders-P1")
	{
	}

	void ShadersP1_Uniforms::Initialize()
	{
		GraphicsShaderTest::Initialize();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer = AtGfx::Buffer::Create(m_GraphicsDevice, AtGfx::BufferSpecification::CreateVertexBufferSpecification(sizeof(vertices), AtGfx::BufferUsage::StaticDraw, vertices));
	}

	void ShadersP1_Uniforms::Deinitialize()
	{
		GraphicsShaderTest::Deinitialize();

		delete m_VertexBuffer;
	}

	void ShadersP1_Uniforms::Perform(float glfwTime)
	{
		Clear();


		m_Shader->Bind(); 
		float greenValue = sin(glfwTime) / 2.0f + 0.5f;
		m_Shader->SetVec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
		m_GraphicsDevice->Draw(m_Pipeline, m_VertexBuffer);
	}

}