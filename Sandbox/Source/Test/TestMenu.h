#pragma once
#include "Test.h"

#include <string>
#include <functional>

class TestMenu 
{
public:
	TestMenu(Test*& test);
	~TestMenu();
public:
	void ImGuiRender();
private:
	Test*& m_CurrentTest;
	std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
};


