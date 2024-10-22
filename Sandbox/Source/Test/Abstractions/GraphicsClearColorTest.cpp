#include "GraphicsClearColorTest.h"

GraphicsClearColorTest::GraphicsClearColorTest(AtGfx::GraphicsDevice* graphicsDevice, float clearColor[4])
	: Test(graphicsDevice), m_ClearColor(clearColor)
{
}

void GraphicsClearColorTest::Perform(float glfwTime)
{
	Clear();
}

void GraphicsClearColorTest::Clear() const
{
	m_GraphicsDevice->Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
}
