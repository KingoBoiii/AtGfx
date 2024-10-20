#pragma once
#include "../ClearColorTest.h"

namespace LearnOpenGL
{

	class HelloWindowTest : public ClearColorTest
	{
	public:
		HelloWindowTest(AtGfx::GraphicsDevice* graphicsDevice);
		virtual ~HelloWindowTest() = default;
	};

}