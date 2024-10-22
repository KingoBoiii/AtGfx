#pragma once
#include "Test/Abstractions/GraphicsShaderTest.h"

#include <AtGfx/Buffer.h>
#include <AtGfx/Texture.h>

namespace LearnOpenGL
{

	class TexturesP1_Container : public GraphicsShaderTest
	{
	public:
		TexturesP1_Container(AtGfx::GraphicsDevice* graphicsDevice);
		virtual ~TexturesP1_Container() = default;
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
		AtGfx::Buffer* m_IndexBuffer = nullptr;
		AtGfx::Texture* m_Texture = nullptr;
	};

}