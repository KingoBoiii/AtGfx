#include "LearnOpenGLTest.h"

#include <iostream>

namespace LearnOpenGL
{

	void LearnOpenGLTest::Clear() const
	{
		m_GraphicsDevice->Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	}

	void LearnOpenGLTest::Initialize()
	{
		std::cout << "Hello from base class\n";
	}

}