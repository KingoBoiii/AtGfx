#include "ShadersP2_MoreAttributes.h"

namespace LearnOpenGL
{

	ShadersP2_MoreAttributes::ShadersP2_MoreAttributes(AtGfx::GraphicsDevice* graphicsDevice)
		: LearnOpenGLTest(graphicsDevice)
	{
	}

	void ShadersP2_MoreAttributes::Initialize()
	{
		const char* vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
})";

		const char* fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
})";

		m_Shader = AtGfx::Shader::Create(m_GraphicsDevice, vertexShaderSource, fragmentShaderSource, "Shaders");

		m_Pipeline = AtGfx::Pipeline::Create(m_GraphicsDevice, {
			.VertexAttributeLayout = {
				{ AtGfx::ShaderDataType::Float3, "aPos" },
				{ AtGfx::ShaderDataType::Float3, "aColor" }
			}
			});

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
		delete m_VertexBuffer;
		delete m_Pipeline;
		delete m_Shader;
	}

	void ShadersP2_MoreAttributes::Perform(float glfwTime)
	{
		Clear();

		m_Shader->Bind();
		m_GraphicsDevice->Draw(m_Pipeline, m_VertexBuffer);
	}

}