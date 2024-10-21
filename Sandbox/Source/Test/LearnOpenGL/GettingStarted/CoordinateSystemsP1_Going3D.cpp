#include "CoordinateSystemsP1_Going3D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LearnOpenGL
{

	CoordinateSystemsP1_Going3D::CoordinateSystemsP1_Going3D(AtGfx::GraphicsDevice* graphicsDevice)
		: LearnOpenGLTest(graphicsDevice)
	{
	}

	void CoordinateSystemsP1_Going3D::Initialize()
	{
		const char* vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
  
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
})";

		const char* fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
  
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

	void CoordinateSystemsP1_Going3D::Deinitialize()
	{
		delete m_Texture1;
		delete m_Texture2;
		delete m_VertexBuffer;
		delete m_Pipeline;
		delete m_Shader;
	}

	void CoordinateSystemsP1_Going3D::Perform(float glfwTime)
	{
		Clear();

		m_Texture1->Bind();
		m_Texture2->Bind(1);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		m_Shader->Bind();
		m_Shader->SetMat4("model", glm::value_ptr(model));
		m_Shader->SetMat4("view", glm::value_ptr(view));
		m_Shader->SetMat4("projection", glm::value_ptr(projection));
		m_GraphicsDevice->DrawIndexed(m_Pipeline, m_VertexBuffer, m_IndexBuffer);
	}

}