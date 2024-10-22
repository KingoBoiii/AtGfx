#include "ClearColorTest.h"

#include <imgui.h>

namespace Tests
{

	ClearColorTest::ClearColorTest(AtGfx::GraphicsDevice* graphicsDevice)
		: GraphicsClearColorTest(graphicsDevice, new float[4] { 1.0f, 1.0f, 1.0f, 1.0f })
	{
	}

	void ClearColorTest::Perform(float glfwTime)
	{
		m_GraphicsDevice->Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2]);
	}

	void ClearColorTest::ImGuiRender()
	{
		ImGui::Text("Clear Color:");
		ImGui::ColorPicker3("##Clear color##", m_ClearColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview);
	}

}