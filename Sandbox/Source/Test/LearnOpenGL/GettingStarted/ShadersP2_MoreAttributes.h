#pragma once
#include "Test/Abstractions/GraphicsShaderTest.h"
#include "LearnOpenGLTest.h"

#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

namespace LearnOpenGL
{

	class ShadersP2_MoreAttributes : public GraphicsShaderTest
	{
	public:
		ShadersP2_MoreAttributes(AtGfx::GraphicsDevice* graphicsDevice);
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;
		virtual void Perform(float glfwTime) override;
	protected:
		virtual const char* GetVertexSource() const override
		{
			return R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
})";
		}
		virtual const char* GetFragmentSource() const override
		{
			return R"(#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
})";
		}
		virtual AtGfx::VertexAttributeLayout GetVertexAttributeLayout() const override
		{
			return {
				{ AtGfx::ShaderDataType::Float3, "aPos" },
				{ AtGfx::ShaderDataType::Float3, "aColor" }
			};
		}
	private:
		AtGfx::Buffer* m_VertexBuffer = nullptr;
	};

}