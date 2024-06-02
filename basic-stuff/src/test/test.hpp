#pragma once
#include <functional>
#include <vector>
#include <string>

namespace Test
{
	class Test
	{
	public:
		Test(){}
		virtual ~Test(){}
		virtual void onRender(){}
		virtual void onUpdate(float deltaTime){}
		virtual void onImGui(){}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTest);
		~TestMenu();
		
		void onImGui() override;
		template <typename T>
		void registerTest(const char* name)
		{
			m_testmenu.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_testmenu;
		Test*& m_currentTest;
	};
}