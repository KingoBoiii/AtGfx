#pragma once
#include "Test/Abstractions/GraphicsClearColorTest.h"

namespace LearnOpenGL
{

	class HelloWindowTest : public GraphicsClearColorTest
	{
	public:
		HelloWindowTest(AtGfx::GraphicsDevice* graphicsDevice);
	};

}