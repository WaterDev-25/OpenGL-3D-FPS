#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include <GL/glew.h>
#include <stb/stb_image.h>

#include "glshader.hpp"

#include <string>
#include <vector>

GLuint LoadCubemap(std::vector<std::string> faces);

class CCubeMap
{
public:
	// Constructor
	CCubeMap(std::vector<std::string> faces);

	// Destructor
	~CCubeMap();

	// Render the cubemap
	void Draw();

private:
	// Cubemap data
	GLuint m_vao;
	GLuint m_id;
};

#endif // CUBEMAP_HPP
