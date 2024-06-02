#pragma once


#include "renderer.hpp"

class Texture
{
private:
	int m_height{};
	int m_width{};
	int m_Channel{};
	unsigned char* m_buffer{};
	unsigned int m_TextureID{};

public:
	Texture(const std::string& filepath, const int desiredChannel);
	~Texture();
	void bind(unsigned int active = 0);
	void unbind();
	void enableTemporaryBlen();
};