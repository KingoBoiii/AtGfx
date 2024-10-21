#include "ShaderTest.h"

ShaderTest::ShaderTest(AtGfx::GraphicsDevice* graphicsDevice, const std::string& shaderName)
	: Test(graphicsDevice),  m_ShaderName(shaderName)
{
}

void ShaderTest::Initialize()
{
	const char* vertexShaderSource = GetVertexSource();
	const char* fragmentShaderSource = GetFragmentSource();

	m_Shader = AtGfx::Shader::Create(m_GraphicsDevice, vertexShaderSource, fragmentShaderSource, m_ShaderName);

	AfterShaderInitialization();
}

void ShaderTest::Deinitialize()
{
	delete m_Shader;

	AfterShaderDeinitialization();
}
