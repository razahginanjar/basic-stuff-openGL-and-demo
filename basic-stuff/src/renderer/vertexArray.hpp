#pragma once

#include "renderer.hpp"
#include "vertexLayout.hpp"
#include "vertexBuffer.hpp"

class VertexArray
{
private:
	unsigned int m_vertexArrayID{};
public:
	VertexArray();
	~VertexArray();

	void addBufffer(const VertexLayout& vl, const  VertexBuffer& vb);
	void bind()const;
	void unbind() const;
	unsigned int getID() { return m_vertexArrayID; }
};