#include "shader.hpp"

Shader::Shader(const char* filepath)
{
    m_programID = glCreateProgram();
    ShaderSourceType src = programSourceCode(filepath);

    unsigned int vs{ compileShader(GL_VERTEX_SHADER, src.vertex) };
    unsigned int fs{ compileShader(GL_FRAGMENT_SHADER, src.fragment) };

    //attach the shader to the program
    glAttachShader(m_programID, vs);
    glAttachShader(m_programID, fs);
    //link it
    glLinkProgram(m_programID);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_programID));
}

unsigned int Shader::compileShader(unsigned int typeShader, const std::string& shaderSrc)
{
    unsigned int shader{ glCreateShader(typeShader) };
    std::string shadSrc = shaderSrc;
    const char* shadersource = shadSrc.c_str();
    glShaderSource(shader, 1, &shadersource, NULL);
    glCompileShader(shader);

    int succcess{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &succcess);
    if (succcess == GL_FALSE)
    {
        int length{};
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        //becs the length of an array must now at compile time so 
        //the slah satu solusinya bisa pake dengan nge alokasi memori di stack dengan:

        char* infoLog = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, infoLog);
        std::cout << "error compiling" <<
            (typeShader == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << "shader\n" << infoLog;

        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

ShaderSourceType Shader::programSourceCode(const std::string filepath)
{
    enum class ShaderType
    {
        NONE = -1,
        VERTEX,
        FRAGMENT
    };

    std::fstream stream;
    stream.open(filepath);
    std::string line{};
    ShaderType shaderType = ShaderType::NONE;
    std::stringstream ss[2];

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                shaderType = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                shaderType = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[int(shaderType)] << line << "\n";
        }
    }

    return { ss[int(ShaderType::VERTEX)].str(), ss[int(ShaderType::FRAGMENT)].str() };
}

void Shader::setUniform4f(const char* name, float v0, float v1, float v2, float v3)
{
    unsigned int location = getUniformLocation(name);
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::setUniform1i(const char* name, int value)
{
    unsigned int location = getUniformLocation(name);
    glUniform1i(location, value);
}

void Shader::setUniformMat4f(const char* name, glm::mat4 value)
{
    unsigned int location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

void Shader::bind() const 
{
    GLCall(glUseProgram(m_programID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

unsigned int Shader::getUniformLocation(const std::string& name_function)
{
    if (m_uniformLocationCache.find(name_function) != m_uniformLocationCache.end())
    {
        return m_uniformLocationCache[name_function];
    }
    GLint location = glGetUniformLocation(m_programID, name_function.c_str());
    ASSERT(location != -1); //artinya tidak ketemu
    m_uniformLocationCache[name_function] = location;
    return location;
}
