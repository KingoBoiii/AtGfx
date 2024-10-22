#include "HelloWindowTest.h"

namespace LearnOpenGL
{

	HelloWindowTest::HelloWindowTest(AtGfx::GraphicsDevice* graphicsDevice)
		: GraphicsClearColorTest(graphicsDevice, new float[4] { 0.2f, 0.3f, 0.3f, 1.0f })
	{
	}

}