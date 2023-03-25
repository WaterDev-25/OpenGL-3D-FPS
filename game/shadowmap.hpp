#ifndef SHADOWMAP_HPP
#define SHADOWMAP_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glshader.hpp"

class CShadowMap
{
public:
	// Constructor
	CShadowMap(GLfloat shadowWidth, GLfloat shadowHeight, glm::vec3 lightPos);

	// Destructor
	~CShadowMap();

	// Shadow map painting
	void ShadowMapPainting(CGLShader* shader);
	
	// Scene rendering using shadow map
	void SceneRendering(CGLShader* shader);

	// Back to default viewport
	void Reset(SDL_Window* window);

private:
	// Shadow map data
	GLfloat m_shadowWidth;
	GLfloat m_shadowHeight;

	glm::vec3 m_lightPos;

	GLuint m_depthMapFbo;
	GLuint m_depthMap;

	glm::mat4 m_lightSpaceMatrix;
};

#endif // SHADOWMAP_HPP
