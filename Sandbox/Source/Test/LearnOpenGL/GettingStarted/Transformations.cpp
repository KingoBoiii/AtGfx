#include "Transformations.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LearnOpenGL
{

	Transformations::Transformations(AtGfx::GraphicsDevice* graphicsDevice)
		: GraphicsShaderTest(graphicsDevice, "Transformations")
	{
	}

	void Transformations::Initialize()
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

		m_Texture1 = AtGfx::Texture::Create(m_GraphicsDevice, "Resources/Test/LearnOpenGL/GettingStarted/Textures/container.jpg");
		m_Texture2 = AtGfx::Texture::Create(m_GraphicsDevice, "Resources/Test/LearnOpenGL/GettingStarted/Textures/awesomeface.png");

		m_Shader->Bind();
		m_Shader->SetInt("texture1", 0);
		m_Shader->SetInt("texture2", 1);
	}

	void Transformations::Deinitialize()
	{
		GraphicsShaderTest::Deinitialize();

		delete m_Texture1;
		delete m_Texture2;
		delete m_VertexBuffer;
		delete m_IndexBuffer;
	}

	void Transformations::Perform(float glfwTime)
	{
		Clear();

		m_Texture1->Bind();
		m_Texture2->Bind(1);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, glfwTime, glm::vec3(0.0f, 0.0f, 1.0f));

		m_Shader->Bind();
		m_Shader->SetMat4("transform", glm::value_ptr(trans));
		m_GraphicsDevice->DrawIndexed(m_Pipeline, m_VertexBuffer, m_IndexBuffer);
	}

	const char* Transformations::GetVertexSource() const
	{
		return R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
  
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
})";
	}

	const char* Transformations::GetFragmentSource() const
	{
		return R"(#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
})";
	}

	AtGfx::VertexAttributeLayout Transformations::GetVertexAttributeLayout() const
	{
		return {
			{ AtGfx::ShaderDataType::Float3, "aPos" },
			{ AtGfx::ShaderDataType::Float3, "aColor" },
			{ AtGfx::ShaderDataType::Float2, "aTexCoord" }
		};
	}

}
