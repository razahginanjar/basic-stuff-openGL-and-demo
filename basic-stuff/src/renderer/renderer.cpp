#include "renderer.hpp"
#include "vertexArray.hpp"
#include "shader.hpp"
#include "indexBuffer.hpp"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGl Error] (" << error << ") : " <<
            function << " " << file << " " << line << " " << std::endl;
        return false;
    }
    return true;
}

void Renderer::drawElement(const VertexArray& VAO, const Shader& shad, const IndexBuffer& ibo) const
{
    VAO.bind();
    shad.bind();

    //draw element
    GLCall(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
