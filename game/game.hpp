#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "glshader.hpp"
#include "player.hpp"
#include "model.hpp"
#include "cubemap.hpp"
#include "map.hpp"
#include "shadowmap.hpp"
#include "physics.hpp"
#include "textrendering.hpp"
#include "debug.hpp"

#include <string>

class CGame
{
public:
	CGame(SDL_Window* window);
	~CGame();

	// Render, game logic...
	void Update(bool* isRunning);

private:
	SDL_Window* m_pWindow;
	SDL_Event m_event;

	CGLShader* m_pShader;
	CGLShader* m_pSkyboxShader;
	CGLShader* m_pShadowMapShader;
	CGLShader* m_pTextRenderingShader;

	CTextRendering* m_pTextRendering;
	CDebug* m_pDebug;

	// Time logic
	GLfloat m_deltaTime;
	GLfloat m_lastFrame;

	CPhysics* m_pPhysics;

	CMap* m_pMap;

	glm::vec3 m_gravity;

	CPlayer* m_pPlayer;

	CCubeMap* m_pCubeMap;

	CShadowMap* m_pShadowMap;

	glm::vec3 m_lightPos;
};

#endif // GAME_HPP
