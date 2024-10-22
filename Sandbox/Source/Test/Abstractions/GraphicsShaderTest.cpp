#include "GraphicsShaderTest.h"

GraphicsShaderTest::GraphicsShaderTest(AtGfx::GraphicsDevice* graphicsDevice, const std::string& shaderName)
	: GraphicsClearColorTest(graphicsDevice, new float[4] { 0.2f, 0.3f, 0.3f, 1.0f }),  m_ShaderName(shaderName)
{
}

void GraphicsShaderTest::Initialize()
{
	const char* vertexShaderSource = GetVertexSource();
	const char* fragmentShaderSource = GetFragmentSource();

	m_Shader = AtGfx::Shader::Create(m_GraphicsDevice, vertexShaderSource, fragmentShaderSource, m_ShaderName);

	m_Pipeline = AtGfx::Pipeline::Create(m_GraphicsDevice, {
		.VertexAttributeLayout = GetVertexAttributeLayout()
	});
}

void GraphicsShaderTest::Deinitialize()
{
	delete m_Pipeline;
	delete m_Shader;
}

void GraphicsShaderTest::Perform(float glfwTime)
{
	Clear();
}

