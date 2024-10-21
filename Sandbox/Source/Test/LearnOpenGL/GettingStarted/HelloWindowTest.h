#pragma once
#include "../../Tests/ClearColorTest.h"

namespace LearnOpenGL
{

	class HelloWindowTest : public Tests::ClearColorTest
	{
	public:
		HelloWindowTest(AtGfx::GraphicsDevice* graphicsDevice);
		virtual ~HelloWindowTest() = default;
	};

}