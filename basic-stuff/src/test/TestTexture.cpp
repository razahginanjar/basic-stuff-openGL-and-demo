#include "TestTexture.hpp"
#include "ImGui/imgui.h"

Test::TestTexture::TestTexture()
    : m_proj{ glm::ortho(0.f, 640.f, 0.f, 480.f, -1.0f, 1.0f) },
    m_view{ glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)) },
    m_TranslationA{glm::vec3(0,0,0)},
    m_TranslationB{ glm::vec3(200,0,0) }

{
    Vertex vertecies[]
    {
        //position							//color							//coor image
        glm::vec3(-50.f, -50.f, 0.0f),		glm::vec3(0.4f, 0.0f, 0.0f),    glm::vec2(0.0f, 0.0f), //bottom left
        glm::vec3(-50.f, 50.f, 0.0f),		glm::vec3(0.0f, 0.4f, 0.0f),	glm::vec2(0.0f, 1.0f), //top left
        glm::vec3(50.f, 50.f, 0.0f),		glm::vec3(0.0f, 0.0f, 0.4f),	glm::vec2(1.0f, 1.0f), //top right
        glm::vec3(50.f, -50.f, 0.0f),		glm::vec3(0.4f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f), //bottom right
    };
    unsigned int indices[]
    {
        0, 1, 2,
        2, 3, 0
    };
    //CREATE VAO
    m_VAO = std::make_unique<VertexArray>();
    m_VAO->bind();

    //create VBO
    m_buffer = std::make_unique<VertexBuffer>(vertecies, 8 * 4 * sizeof(float));
    m_buffer->bind();

    //buffer for the index
    m_ibo = std::make_unique<IndexBuffer>(indices, 6);
    m_ibo->bind();

    glm::vec4 vp(192.f, 144.f, 0.f, 1.0f);
    glm::vec4 hasil = m_proj * vp;

    //for actually to draw triangle with hal modern and old openGL we need arrpointer to tell
    //openGl that it's for pos., color, or a textcoor

    m_layout = std::make_unique<VertexLayout>();
    m_layout->Push<float>(3);
    m_layout->Push<float>(3);
    m_layout->Push<float>(2);

    m_VAO->addBufffer(*m_layout, *m_buffer);

    //create shader
    m_shader = std::make_unique<Shader>("res/shader/Shader.shader");
    m_shader->bind();

    //create texture
    m_texture = std::make_unique<Texture>("res/pics/R.png", 4);
    m_texture->bind(0);
    m_texture->enableTemporaryBlen();

    m_shader->setUniform1i("u_TextCoor", 0);
}

Test::TestTexture::~TestTexture()
{
}

void Test::TestTexture::onRender()
{
    Renderer render;
    {
        m_texture->bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->bind();
        m_shader->setUniformMat4f("u_MVP", mvp);

        //draw element
        render.drawElement(*m_VAO, *m_shader, *m_ibo);

    }

    {
        m_texture->bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->bind();
        m_shader->setUniformMat4f("u_MVP", mvp);

        //draw element
        render.drawElement(*m_VAO, *m_shader, *m_ibo);

    }
}

void Test::TestTexture::onUpdate(float deltaTime)
{
}

void Test::TestTexture::onImGui()
{
    //IMGUI
    {
        ImGui::SliderFloat3("translationA", &m_TranslationA.x, 0.0f, 640.f); // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat3("translationB", &m_TranslationB.x, 0.0f, 640.f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}
