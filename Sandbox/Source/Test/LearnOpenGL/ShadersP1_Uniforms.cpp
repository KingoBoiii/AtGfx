#include "ShadersP1_Uniforms.h"

namespace LearnOpenGL
{

	ShadersP1_Uniforms::ShadersP1_Uniforms(AtGfx::GraphicsDevice* graphicsDevice)
		: LearnOpenGLTest(graphicsDevice)
	{
	}

	void ShadersP1_Uniforms::Initialize()
	{
		const char* vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
})";

		const char* fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
  
uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main()
{
    FragColor = ourColor;
})";
	}

	void ShadersP1_Uniforms::Deinitialize()
	{
	}

	void ShadersP1_Uniforms::Perform(float glfwTime)
	{
		Clear();


	}

}