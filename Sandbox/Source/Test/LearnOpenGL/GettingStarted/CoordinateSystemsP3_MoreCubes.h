#pragma once
#include "LearnOpenGLTest.h"

#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>
#include <AtGfx/Texture.h>

namespace LearnOpenGL
{

	class CoordinateSystemsP3_MoreCubes : public LearnOpenGLTest
	{
	public:
		CoordinateSystemsP3_MoreCubes(AtGfx::GraphicsDevice* graphicsDevice);
		virtual ~CoordinateSystemsP3_MoreCubes() = default;
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;
		virtual void Perform(float glfwTime) override;
	private:
		AtGfx::Shader* m_Shader = nullptr;
		AtGfx::Pipeline* m_Pipeline = nullptr;
		AtGfx::Buffer* m_VertexBuffer = nullptr;
		AtGfx::Texture* m_Texture1 = nullptr;
		AtGfx::Texture* m_Texture2 = nullptr;
	};

}
