#pragma once
#include "renderer.hpp"

class IndexBuffer
{
private:
	unsigned int m_indexBufferID{};
	unsigned int m_count{};
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void bind();
	void unbind();

	unsigned int getCount() const { return m_count; }
};