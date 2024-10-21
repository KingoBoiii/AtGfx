#include "TexturesP2_TextureUnits.h"

namespace LearnOpenGL
{

	TexturesP2_TextureUnits::TexturesP2_TextureUnits(AtGfx::GraphicsDevice* graphicsDevice)
		: LearnOpenGLTest(graphicsDevice)
	{
	}

	void TexturesP2_TextureUnits::Initialize()
	{
		const char* vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
})";

		const char* fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
})";

		m_Shader = AtGfx::Shader::Create(m_GraphicsDevice, vertexShaderSource, fragmentShaderSource, "Textures");

		m_Pipeline = AtGfx::Pipeline::Create(m_GraphicsDevice, {
			.VertexAttributeLayout = {
				{ AtGfx::ShaderDataType::Float3, "aPos" },
				{ AtGfx::ShaderDataType::Float3, "aColor" },
				{ AtGfx::ShaderDataType::Float2, "aTexCoord" }
			}
			});

		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
		};

		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		m_VertexBuffer = AtGfx::Buffer::Create(m_GraphicsDevice, AtGfx::BufferSpecification::CreateVertexBufferSpecification(sizeof(vertices), AtGfx::BufferUsage::StaticDraw, vertices));
		m_IndexBuffer = AtGfx::Buffer::Create(m_GraphicsDevice, AtGfx::BufferSpecification::CreateIndexBufferSpecification(sizeof(indices), AtGfx::BufferUsage::StaticDraw, indices));

		m_Texture1 = AtGfx::Texture::Create(m_GraphicsDevice, "Resources/Test/LearnOpenGL/GettingStarted/Textures/container.jpg");
		m_Texture2 = AtGfx::Texture::Create(m_GraphicsDevice, "Resources/Test/LearnOpenGL/GettingStarted/Textures/awesomeface.png");

		m_Shader->Bind();
		m_Shader->SetInt("texture1", 0);
		m_Shader->SetInt("texture2", 1);
	}

	void TexturesP2_TextureUnits::Deinitialize()
	{
		delete m_Texture1;
		delete m_Texture2;
		delete m_VertexBuffer;
		delete m_Pipeline;
		delete m_Shader;
	}

	void TexturesP2_TextureUnits::Perform(float glfwTime)
	{
		Clear();

		m_Texture1->Bind();
		m_Texture2->Bind(1);
		m_Shader->Bind();
		m_GraphicsDevice->DrawIndexed(m_Pipeline, m_VertexBuffer, m_IndexBuffer);
	}

}