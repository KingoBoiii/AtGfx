#pragma once
#include "Test/Abstractions/GraphicsShaderTest.h"

#include <AtGfx/Buffer.h>
#include <AtGfx/Texture.h>

namespace LearnOpenGL
{

	class CoordinateSystemsP3_MoreCubes : public GraphicsShaderTest
	{
	public:
		CoordinateSystemsP3_MoreCubes(AtGfx::GraphicsDevice* graphicsDevice);
		virtual ~CoordinateSystemsP3_MoreCubes() = default;
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
		AtGfx::Texture* m_Texture1 = nullptr;
		AtGfx::Texture* m_Texture2 = nullptr;
	};

}
