#pragma once
#include "renderer.hpp"
#include <stdexcept>
#include <vector>

struct LayoutElement
{
	unsigned int type{};
	unsigned int count{};
	unsigned char normalize{};

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type) 
		{
		case GL_FLOAT:
			return sizeof(float);
		case GL_UNSIGNED_INT:
			return sizeof(unsigned int);
		case GL_UNSIGNED_BYTE:
			return sizeof(unsigned char);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexLayout
{
private:
	std::vector<LayoutElement> m_element{};
	unsigned int m_stride{};
public:
	VertexLayout();
	template <typename T>
	void Push(unsigned int count)
	{
		std::runtime_error(false);
		/*static_assert(false);*/
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_element.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * sizeof(float);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_element.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * sizeof(unsigned int);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_element.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * sizeof(unsigned char);
	}

	inline unsigned int getStride() const { return m_stride; }
	inline const std::vector<LayoutElement> getElement() const { return m_element; }
	~VertexLayout();

};