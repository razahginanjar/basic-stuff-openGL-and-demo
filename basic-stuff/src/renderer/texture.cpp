#include "texture.hpp"
#include "stb_image/stbimage.hpp"

Texture::Texture(const std::string& filepath, const int desiredChannel)
	: m_buffer{nullptr}
{
	stbi_set_flip_vertically_on_load(true);

	m_buffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_Channel, desiredChannel);

	if (!m_buffer)
		ASSERT(false);

	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	//set the parameter texture
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // GL_TEXTURE_WRAP_S -> sumbu x
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); //GL_TEXTURE_WRAP_T -> sumbu Y

	//image filtering
	// teknik untuk openGL interpolasi gambar yang sudah ada supaya bisa ditampilkan
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));



	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));
	//call mipMap
	//teknik interpolasi yang membantu ketika display menjauhi si gambar
	//agar gambar bisa dinamis dalam menampilkan si resolusinya
	//internal format, format yang akan disimpan di openGL
	//format, format yang kamu kasih ke openGL
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	stbi_image_free(m_buffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_TextureID));
}

void Texture::unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::enableTemporaryBlen()
{
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // ngatur cara openGl draw perpixel untuk nilai alpha
															   // terutama untuk bagian yang transparant
	GLCall(glEnable(GL_BLEND));
}

void Texture::bind(unsigned int active)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + active));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

