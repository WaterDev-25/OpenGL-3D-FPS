#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "glshader.hpp"
#include "textrendering.hpp"

#include <iostream>
#include <vector>

class CDebug
{
public:
	// Constructor
	CDebug(CGLShader* shader, CTextRendering* textRendering, SDL_Window* window);

	// Destructor
	~CDebug();

	// Render debug message
	void Render();

	// Add debug message
	// Add info message
	void AddInfo(std::string text);

	// Edit debug message
	// Edit info message
	void EditInfo(int index, std::string text);

private:
	CGLShader* m_pShader;
	CTextRendering* m_pTextRendering;
	SDL_Window* m_pWindow;

	std::vector<std::string> m_infoText;
	std::vector<std::string> m_warningText;
	std::vector<std::string> m_errorText;
};

#endif // DEBUG_HPP
