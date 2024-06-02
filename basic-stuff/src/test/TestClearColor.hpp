#pragma once
#include "test.hpp"

namespace Test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();
		void onRender() override;
		void onUpdate(float deltaTime) override;
		void onImGui() override;
	private:
		float m_color[4];
	};
}