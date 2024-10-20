#pragma once
#include <AtGfx/GraphicsDevice.h>

class Test
{
public:
	Test(AtGfx::GraphicsDevice* graphicsDevice);
	virtual ~Test() = default;
public:
	virtual void Initialize() = 0;
	virtual void Deinitialize() = 0;
	virtual void Perform() = 0;
	virtual void ImGuiRender()
	{
	}
protected:
	AtGfx::GraphicsDevice* m_GraphicsDevice;
};