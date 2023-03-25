#ifndef TEXTRENDERING_HPP
#define TEXTRENDERING_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <map>

#include "glshader.hpp"

struct SCharacter
{
	GLuint id;

	glm::ivec2 size;
	glm::ivec2 bearing;

	GLuint advance;
};

class CTextRendering
{
public:
	// Constructor
	CTextRendering(std::string filePath);

	// Destructor
	~CTextRendering();

	// Render text
	void RenderText(CGLShader* shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, GLuint width, GLuint height);

private:
	std::map<GLchar, SCharacter> m_characters;

	GLuint m_vao;
	GLuint m_vbo;
};

#endif // TEXTRENDERING_HPP
