#include "indexBuffer.hpp"


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_count{count}
{
	GLCall(glGenBuffers(1, &m_indexBufferID)); 
	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_indexBufferID));
}

void IndexBuffer::bind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID));
}

void IndexBuffer::unbind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
