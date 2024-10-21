#include "HelloTriangleP1_VBO.h"

namespace LearnOpenGL
{

	HelloTriangleP1_VBO::HelloTriangleP1_VBO(AtGfx::GraphicsDevice* graphicsDevice)
		: LearnOpenGLTest(graphicsDevice)
	{
	}

	void HelloTriangleP1_VBO::Initialize()
	{
		const char* vertexShaderSource = R"(#version 330 core
layout (location=0) in vec3 aPos;

void main() {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})";

		const char* fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} )";
		m_Shader = AtGfx::Shader::Create(m_GraphicsDevice, vertexShaderSource, fragmentShaderSource, "HelloTriangle");

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

	void HelloTriangleP1_VBO::Deinitialize()
	{
		delete m_VertexBuffer;
		delete m_Pipeline;
	}

	void HelloTriangleP1_VBO::Perform(float glfwTime)
	{
		Clear();

		m_Shader->Bind();
		m_GraphicsDevice->Draw(m_Pipeline, m_VertexBuffer);
	}

}