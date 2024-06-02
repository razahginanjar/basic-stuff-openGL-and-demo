#include "vertexArray.hpp"

VertexArray::VertexArray()
{
	GLCall(glCreateVertexArrays(1, &m_vertexArrayID));
	GLCall(glBindVertexArray(m_vertexArrayID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_vertexArrayID));
}

void VertexArray::addBufffer(const VertexLayout& vl, const VertexBuffer& vb)
{
	vb.bind();
	const auto& layouts = vl.getElement();
	unsigned int offset{ 0 };
	for (unsigned int i {0}; i < layouts.size(); i++)
	{
		const auto& layout = layouts[i];
		GLCall(glVertexAttribPointer(i, layout.count, layout.type, layout.normalize,
			vl.getStride(), (const void*) (offset)));
		GLCall(glEnableVertexAttribArray(i));
		offset += layout.count * LayoutElement::getSizeOfType(layout.type);
	}
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_vertexArrayID));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
