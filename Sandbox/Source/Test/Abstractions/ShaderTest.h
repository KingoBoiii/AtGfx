#pragma once
#include "Test/Test.h"

#include <AtGfx/Shader.h>

class ShaderTest : public Test
{
public:
	ShaderTest(AtGfx::GraphicsDevice* graphicsDevice, const std::string& shaderName);
	virtual ~ShaderTest() = default;
public:
	virtual void Initialize() override;
	virtual void Deinitialize() override;
protected:
	virtual void AfterShaderInitialization() = 0;
	virtual void AfterShaderDeinitialization() = 0;

	virtual const char* GetVertexSource() const = 0;
	virtual const char* GetFragmentSource() const = 0;
protected:
	std::string m_ShaderName = "Unnamed";
	AtGfx::Shader* m_Shader = nullptr;
};