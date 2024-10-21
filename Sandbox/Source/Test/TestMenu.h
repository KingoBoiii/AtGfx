#pragma once
#include "Test.h"

#include <string>
#include <functional>
#include <vector>
#include <map>

namespace AtGfx
{
	class GraphicsDevice;
}

struct TestRegistration
{
	std::string Label;
	std::function<Test* ()> InstantiateTest;

	TestRegistration(const std::string& label, std::function<Test* ()> instantiateFunc)
		: Label(label), InstantiateTest(instantiateFunc)
	{
	}
};

class TestMenu
{
public:
	TestMenu(AtGfx::GraphicsDevice* graphicsDevice, Test*& currentTest);
public:
	void ImGuiRender();

	const std::string& RegisterCategory(const std::string& category)
	{
		m_Tests[category] = std::vector<TestRegistration>();
		return category;
	}

	template<typename T>
	void RegisterTest(const std::string& category, const std::string& name)
	{
		auto it = m_Tests.find(category);
		if (it == m_Tests.end())
		{
			return;
		}

		it->second.push_back({ name,[&]() { return new T(m_GraphicsDevice); }});
	}
private:
	AtGfx::GraphicsDevice* m_GraphicsDevice = nullptr;
	Test*& m_CurrentTest;
	std::map<std::string, std::vector<TestRegistration>> m_Tests;
};