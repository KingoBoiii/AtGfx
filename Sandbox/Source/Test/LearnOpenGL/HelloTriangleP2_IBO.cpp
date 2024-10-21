#include "HelloTriangleP2_IBO.h"

namespace LearnOpenGL
{

	HelloTriangleP2_IBO::HelloTriangleP2_IBO(AtGfx::GraphicsDevice* graphicsDevice)
		: LearnOpenGLTest(graphicsDevice)
	{
	}

	void HelloTriangleP2_IBO::Initialize()
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
		delete m_IndexBuffer;
		delete m_VertexBuffer;
		delete m_Pipeline;
	}

	void HelloTriangleP2_IBO::Perform()
	{
		Clear();

		m_Shader->Bind();
		m_GraphicsDevice->DrawIndexed(m_Pipeline, m_VertexBuffer, m_IndexBuffer);
	}

}