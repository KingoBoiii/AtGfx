#pragma once

#include "Test/Test.h"

class GraphicsClearColorTest : public Test
{
public:
	GraphicsClearColorTest(AtGfx::GraphicsDevice* graphicsDevice, float clearColor[4]);
	virtual ~GraphicsClearColorTest() = default;
public:
	virtual void Initialize() override { }
	virtual void Deinitialize() override { }
	virtual void Perform(float glfwTime) override;
protected:
	void Clear() const;
protected:
	float* m_ClearColor;
};

