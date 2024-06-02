#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak(); 
#define GLCall(x) GLClearError();\
       x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class VertexArray;
class IndexBuffer;
class Shader;
class VertexLayout;

class Renderer
{
public:
    void drawElement(const VertexArray& VAO, const Shader& shad, const IndexBuffer& ibo) const;
    void clear();
};