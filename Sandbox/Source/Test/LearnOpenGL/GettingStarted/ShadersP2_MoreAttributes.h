#pragma once
#include "Test/Abstractions/GraphicsShaderTest.h"
#include "LearnOpenGLTest.h"

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
		virtual const char* GetVertexSource() const override;
		virtual const char* GetFragmentSource() const override;
		virtual AtGfx::VertexAttributeLayout GetVertexAttributeLayout() const override;
	private:
		AtGfx::Buffer* m_VertexBuffer = nullptr;
	};

}