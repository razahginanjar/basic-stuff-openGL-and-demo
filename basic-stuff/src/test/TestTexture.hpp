#pragma once
#include "test.hpp"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "renderer/renderer.hpp"
#include "renderer/vertexBuffer.hpp"
#include "renderer/indexBuffer.hpp"
#include "renderer/vertexArray.hpp"
#include "renderer/shader.hpp"
#include "renderer/texture.hpp"

#include <memory>

namespace Test
{
	struct Vertex
	{
		glm::vec3 v_position{};
		glm::vec3 v_color{};
		glm::vec2 v_textCoor{};
	};

	class TestTexture : public Test
	{
	public:
		TestTexture();
		~TestTexture();
		void onRender() override;
		void onUpdate(float deltaTime) override;
		void onImGui() override;
	private:
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_buffer;
		std::unique_ptr<IndexBuffer> m_ibo;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;
		std::unique_ptr<VertexLayout> m_layout;
	};
}