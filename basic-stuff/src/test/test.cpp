#include "test.hpp"
#include "ImGui/imgui.h"

namespace Test
{
	TestMenu::TestMenu(Test*& currentTest)
		:m_currentTest{currentTest}
	{
	}
	TestMenu::~TestMenu()
	{
	}
	void TestMenu::onImGui()
	{

		for (auto& test : m_testmenu)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_currentTest = test.second();
			}
		}

	}
}