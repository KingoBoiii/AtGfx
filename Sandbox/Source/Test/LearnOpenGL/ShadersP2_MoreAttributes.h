#pragma once
#include "LearnOpenGLTest.h"

#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

namespace LearnOpenGL
{

	class ShadersP2_MoreAttributes : public LearnOpenGLTest
	{
	public:
		ShadersP2_MoreAttributes(AtGfx::GraphicsDevice* graphicsDevice);
		virtual ~ShadersP2_MoreAttributes() = default;
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