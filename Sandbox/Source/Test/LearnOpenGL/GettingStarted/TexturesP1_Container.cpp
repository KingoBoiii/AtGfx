#include "TexturesP1_Container.h"

namespace LearnOpenGL
{

	TexturesP1_Container::TexturesP1_Container(AtGfx::GraphicsDevice* graphicsDevice)
		: GraphicsShaderTest(graphicsDevice, "Textures-P1")
	{
	}

	void TexturesP1_Container::Initialize()
	{
		GraphicsShaderTest::Initialize();

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

		m_Texture = AtGfx::Texture::Create(m_GraphicsDevice, "Resources/Test/LearnOpenGL/GettingStarted/Textures/container.jpg");
	}

	void TexturesP1_Container::Deinitialize()
	{
		GraphicsShaderTest::Deinitialize();

		delete m_Texture;
		delete m_VertexBuffer;
	}

	void TexturesP1_Container::Perform(float glfwTime)
	{
		Clear();

		m_Texture->Bind();
		m_Shader->Bind();
		m_GraphicsDevice->DrawIndexed(m_Pipeline, m_VertexBuffer, m_IndexBuffer);
	}

	const char* TexturesP1_Container::GetVertexSource() const
	{
		return R"(#version 330 core
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
	}
	const char* TexturesP1_Container::GetFragmentSource() const
	{
		return R"(#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);  
})";
	}

	AtGfx::VertexAttributeLayout TexturesP1_Container::GetVertexAttributeLayout() const
	{
		return {
			{ AtGfx::ShaderDataType::Float3, "aPos" },
			{ AtGfx::ShaderDataType::Float3, "aColor" },
			{ AtGfx::ShaderDataType::Float2, "aTexCoord" }
		};
	}

}