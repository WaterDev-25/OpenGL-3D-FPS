#include "debug.hpp"

// ------------------------------------------------------
// Purpose: Constructor
// ------------------------------------------------------
CDebug::CDebug(CGLShader* shader, CTextRendering* textRendering, SDL_Window* window) :
	m_pShader(shader),
	m_pTextRendering(textRendering),
	m_pWindow(window)
{
	// --
}

// ------------------------------------------------------
// Purpose: Destructor
// ------------------------------------------------------
CDebug::~CDebug()
{
	// RAII
	// --
}

// ------------------------------------------------------
// Purpose: Render debug message
// ------------------------------------------------------
void CDebug::Render()
{
	float i = 50.0f;

	// Get current window width and height
	int w = 0;
	int h = 0;

	SDL_GetWindowSize(this->m_pWindow, &w, &h);

	for (auto& text : this->m_infoText)
	{
		this->m_pTextRendering->RenderText(this->m_pShader, text, 50.0f, (float)h - i, 0.3f, glm::vec3(1.0f), w, h);

		i += 20.0f;
	}
}

// ------------------------------------------------------
// Purpose: Add info message
// ------------------------------------------------------
void CDebug::AddInfo(std::string text)
{
	this->m_infoText.push_back(text);
}

// ------------------------------------------------------
// Purpose: Edit info message
// ------------------------------------------------------
void CDebug::EditInfo(int index, std::string text)
{
	this->m_infoText.at(index) = text;
}
