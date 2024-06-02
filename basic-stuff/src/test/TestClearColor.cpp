#include "TestClearColor.hpp"
#include "renderer.hpp"
#include "ImGui/imgui.h"

Test::TestClearColor::TestClearColor()
	: m_color{0.f, 0.f, 0.f, 1.0f}
{
}

Test::TestClearColor::~TestClearColor()
{
}

void Test::TestClearColor::onRender()
{
	GLCall(glClearColor(m_color[0], m_color[1], m_color[2], m_color[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Test::TestClearColor::onUpdate(float deltaTime)
{
}

void Test::TestClearColor::onImGui()
{
	ImGui::ColorEdit4("Edit Color", m_color);
}
