#include "vertexBuffer.hpp"



VertexBuffer::VertexBuffer(const void* data, unsigned int sizeOfData)
{
	GLCall(glGenBuffers(1, &m_bufferID));
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_bufferID));
}

void VertexBuffer::bind() const 
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferID));
}

void VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
