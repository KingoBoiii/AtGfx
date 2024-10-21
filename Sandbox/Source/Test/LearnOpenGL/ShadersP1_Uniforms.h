#pragma once
#include "LearnOpenGLTest.h"

#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

namespace LearnOpenGL
{

	class ShadersP1_Uniforms : public LearnOpenGLTest
	{
	public:
		ShadersP1_Uniforms(AtGfx::GraphicsDevice* graphicsDevice);
		virtual ~ShadersP1_Uniforms() = default;
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;
		virtual void Perform(float glfwTime) override;
	private:
		AtGfx::Shader* m_Shader = nullptr;
		AtGfx::Pipeline* m_Pipeline = nullptr;
		AtGfx::Buffer* m_VertexBuffer = nullptr;
	};

}