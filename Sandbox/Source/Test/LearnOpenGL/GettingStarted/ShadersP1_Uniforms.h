#pragma once
#include "Test/Abstractions/GraphicsShaderTest.h"
#include "LearnOpenGLTest.h"

#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

namespace LearnOpenGL
{

	class ShadersP1_Uniforms : public GraphicsShaderTest
	{
	public:
		ShadersP1_Uniforms(AtGfx::GraphicsDevice* graphicsDevice);
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;
		virtual void Perform(float glfwTime) override;
	protected:
		virtual const char* GetVertexSource() const override
		{
			return R"(#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
})";
		}
		virtual const char* GetFragmentSource() const override
		{
			return R"(#version 330 core
out vec4 FragColor;
  
uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main()
{
    FragColor = ourColor;
})";
		}
	private:
		AtGfx::Buffer* m_VertexBuffer = nullptr;
	};

}