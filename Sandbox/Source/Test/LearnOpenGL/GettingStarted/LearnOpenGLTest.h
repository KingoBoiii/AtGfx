#pragma once
#include "../../Test.h"

namespace LearnOpenGL
{

	class LearnOpenGLTest : public Test
	{
	public:
		LearnOpenGLTest(AtGfx::GraphicsDevice* graphicsDevice) 
			: Test(graphicsDevice)
		{
		}
		virtual ~LearnOpenGLTest() = default;
	public:
		virtual void Initialize() override;
	protected:
		void Clear() const;
	protected:
		float m_ClearColor[4] = { 0.2f, 0.3f, 0.3f, 1.0f };
	};

}