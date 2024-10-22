#include "TestMenu.h"

#include <imgui.h>

TestMenu::TestMenu(AtGfx::GraphicsDevice* graphicsDevice, Test*& currentTest)
	: m_GraphicsDevice(graphicsDevice), m_CurrentTest(currentTest)
{
}

void TestMenu::ImGuiRender()
{
	const ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	if (ImGui::Begin("Tests", nullptr, windowFlags))
	{
		for (const auto& [category, testRegistrations] : m_Tests)
		{
			if (ImGui::TreeNodeEx(category.c_str(), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen))
			{
				for (auto& testRegistration : testRegistrations)
				{
					ImGui::TreeNodeEx(testRegistration.Label.c_str(), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf);
					if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
					{
						if (m_CurrentTest != nullptr)
						{
							m_CurrentTest->Deinitialize();
							delete m_CurrentTest;
							m_CurrentTest = nullptr;
						}

						m_CurrentTest = testRegistration.InstantiateTest();
						m_CurrentTest->Initialize();
					}
					ImGui::TreePop();

#if 0
					if (ImGui::Button(testRegistration.Label.c_str()))
					{
						if (m_CurrentTest != nullptr)
						{
							m_CurrentTest->Deinitialize();
							delete m_CurrentTest;
							m_CurrentTest = nullptr;
						}

						m_CurrentTest = testRegistration.InstantiateTest();
						m_CurrentTest->Initialize();
					}
#endif
				}
				ImGui::TreePop();
			}
		}

		//for (auto& testRegistration : m_Tests)
		//{
		//	if (ImGui::Button(testRegistration.Label.c_str()))
		//	{
		//		if (m_CurrentTest != nullptr)
		//		{
		//			m_CurrentTest->Deinitialize();
		//			delete m_CurrentTest;
		//			m_CurrentTest = nullptr;
		//		}

		//		m_CurrentTest = testRegistration.InstantiateTest();
		//		m_CurrentTest->Initialize();
		//	}
		//}
	}
	ImGui::End();

	if (m_CurrentTest != nullptr)
	{
		if (ImGui::Begin("Test...", nullptr, windowFlags))
		{
			m_CurrentTest->ImGuiRender();
		}
		ImGui::End();
	}
}
