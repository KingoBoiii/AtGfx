#include "LearnOpenGLTest.h"

namespace LearnOpenGL
{

	void LearnOpenGLTest::Clear() const
	{
		m_GraphicsDevice->Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	}

}