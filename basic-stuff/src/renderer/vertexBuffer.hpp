#pragma once
#include "renderer.hpp"

class VertexBuffer
{
private:
	unsigned int m_bufferID{};
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void bind() const ;
	void unbind() const;

};