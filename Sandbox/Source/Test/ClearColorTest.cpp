#include "ClearColorTest.h"

#include <imgui.h>

ClearColorTest::ClearColorTest(AtGfx::GraphicsDevice* graphicsDevice)
	: Test(graphicsDevice)
{
}

void ClearColorTest::Initialize()
{
}

void ClearColorTest::Deinitialize()
{
}

void ClearColorTest::Perform()
{
	m_GraphicsDevice->Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2]);
}

void ClearColorTest::ImGuiRender()
{
	ImGui::Text("Clear Color:");
	ImGui::ColorPicker3("##Clear color##", m_ClearColor, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview);
}
