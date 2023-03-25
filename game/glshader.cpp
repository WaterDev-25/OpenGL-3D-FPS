#include "glshader.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CGLShader::CGLShader(const char* vertexSource, const char* fragmentSource)
{
	// Create the shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	// Create the program shader
	this->m_id = glCreateProgram();

	GLint result = GL_FALSE;
	GLint infoLogLength = 0;

	// Compile vertex shader
	glShaderSource(vertexShader, 1, &vertexSource, 0);
	glCompileShader(vertexShader);

	// Check vertex shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<GLchar> vertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(vertexShader, infoLogLength, 0, &vertexShaderErrorMessage[0]);
		std::cerr << "Vertex shader compilation failed: " << &vertexShaderErrorMessage[0] << std::endl;
	}

	// Compile fragment shader
	glShaderSource(fragmentShader, 1, &fragmentSource, 0);
	glCompileShader(fragmentShader);

	// Check fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<GLchar> fragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShader, infoLogLength, 0, &fragmentShaderErrorMessage[0]);
		std::cerr << "Fragment shader compilation failed: " << &fragmentShaderErrorMessage[0] << std::endl;
	}

	// Link the program
	glAttachShader(this->m_id, vertexShader);
	glAttachShader(this->m_id, fragmentShader);
	glLinkProgram(this->m_id);

	// Check the program
	glGetProgramiv(this->m_id, GL_LINK_STATUS, &result);
	glGetProgramiv(this->m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<GLchar> fragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(this->m_id, infoLogLength, 0, &fragmentShaderErrorMessage[0]);
		std::cerr << "Program shader linking failed: " << &fragmentShaderErrorMessage[0] << std::endl;
	}

	// Detach shaders
	glDetachShader(this->m_id, vertexShader);
	glDetachShader(this->m_id, fragmentShader);

	// Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CGLShader::~CGLShader()
{
}

// ------------------------------------------------------
// Purpose: Bind program shader
// ------------------------------------------------------
void CGLShader::Use()
{
	glUseProgram(this->m_id);
}

// ------------------------------------------------------
// Purpose: Uniform functions
// ------------------------------------------------------
void CGLShader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->m_id, name.c_str()), (int)value);
}

void CGLShader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->m_id, name.c_str()), value);
}

void CGLShader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->m_id, name.c_str()), value);
}

void CGLShader::SetVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(this->m_id, name.c_str()), 1, glm::value_ptr(value));
}

void CGLShader::SetVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(this->m_id, name.c_str()), x, y);
}

void CGLShader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(this->m_id, name.c_str()), 1, glm::value_ptr(value));
}

void CGLShader::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(this->m_id, name.c_str()), x, y, z);
}

void CGLShader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, glm::value_ptr(value));
}

void CGLShader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(this->m_id, name.c_str()), x, y, z, w);
}

void CGLShader::SetMat2(const std::string& name, const glm::mat2& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void CGLShader::SetMat3(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void CGLShader::SetMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
