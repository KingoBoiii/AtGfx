#pragma once
#include "../Test.h"

namespace Tests
{

	class ClearColorTest : public Test
	{
	public:
		ClearColorTest(AtGfx::GraphicsDevice* graphicsDevice);
	public:
		virtual void Initialize() override;
		virtual void Deinitialize() override;
		virtual void Perform() override;
		virtual void ImGuiRender() override;
	private:
		float m_ClearColor[3] = { 1.0f, 1.0f, 1.0f };
	};

}