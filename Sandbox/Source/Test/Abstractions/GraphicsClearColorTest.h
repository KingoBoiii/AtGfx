#pragma once

#include "Test/Test.h"

class GraphicsClearColorTest : public Test
{
public:
	GraphicsClearColorTest(AtGfx::GraphicsDevice* graphicsDevice, float clearColor[4]);
	virtual ~GraphicsClearColorTest() = default;
public:
	virtual void Perform(float glfwTime) override;
protected:
	void Clear() const;
private:
	float* m_ClearColor;
};

