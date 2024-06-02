#pragma once
#include "renderer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <sstream>
#include <unordered_map>

struct ShaderSourceType
{
    const std::string vertex{};
    const std::string fragment{};
};


class Shader
{
private:
	unsigned int m_programID{};
	std::unordered_map<std::string, GLint> m_uniformLocationCache;
public:
	Shader(const char* filepath);
	~Shader();

	unsigned int compileShader(unsigned int typeShader, const std::string& shaderSrc);
    ShaderSourceType programSourceCode(const std::string filepath);
	void setUniform4f(const char* name, float v0, float v1, float v2, float v3);
	void setUniform1i(const char* name, int value);
	void setUniformMat4f(const char* name, glm::mat4 value);
	void bind() const ;
	void unbind() const ;
private:
	unsigned int getUniformLocation(const std::string& name_function);
};