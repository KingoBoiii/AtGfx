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
		virtual const char* GetVertexSource() const override;
		virtual const char* GetFragmentSource() const override;
	private:
		AtGfx::Buffer* m_VertexBuffer = nullptr;
	};

}