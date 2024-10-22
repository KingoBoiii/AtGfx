#pragma once
#include "Test/Test.h"
#include "GraphicsClearColorTest.h"

#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>

class GraphicsShaderTest : public GraphicsClearColorTest
{
public:
	GraphicsShaderTest(AtGfx::GraphicsDevice* graphicsDevice, const std::string& shaderName);
	virtual ~GraphicsShaderTest() = default;
public:
	virtual void Initialize() override;
	virtual void Deinitialize() override;
	virtual void Perform(float glfwTime) override;
protected:
	virtual const char* GetVertexSource() const
	{
		return R"(#version 330 core
layout (location=0) in vec3 aPos;

void main() {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})";
	}
	virtual const char* GetFragmentSource() const
	{
		return R"(#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
})";
	}

	virtual AtGfx::VertexAttributeLayout GetVertexAttributeLayout() const
	{
		return {
			{ AtGfx::ShaderDataType::Float3, "aPos" }
		};
	}
protected:
	AtGfx::Shader* m_Shader = nullptr;
	AtGfx::Pipeline* m_Pipeline = nullptr;
private:
	std::string m_ShaderName = "Unnamed";
};