#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <iostream>

#include "game.hpp"

int main(int argc, char** argv)
{
	// Initialize SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Failed to initialize SDL2: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Set relative mouse to true
	if (SDL_SetRelativeMouseMode(SDL_TRUE) != 0)
	{
		std::cerr << "Failed to set relative mouse to true: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Set profile to core profile and use OpenGL 4.6
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	// Create a window
	SDL_Window* pWindow = SDL_CreateWindow(
		"Game",						// Title
		SDL_WINDOWPOS_CENTERED,		// X
		SDL_WINDOWPOS_CENTERED,		// Y
		1280,						// Height
		720,						// Width
		SDL_WINDOW_OPENGL |			// Flags
		SDL_WINDOW_RESIZABLE
	);

	if (!pWindow)
	{
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Create an OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(pWindow);

	if (!context)
	{
		std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW: " << glGetError() << std::endl;
		return 1;
	}

	// Create game object
	CGame game(pWindow);

	bool bIsRunning = true;

	// Main loop
	while (bIsRunning)
	{
		// Call game update function
		game.Update(&bIsRunning);

		// Update window
		SDL_GL_SwapWindow(pWindow);
	}

	// Delete OpenGL context
	SDL_GL_DeleteContext(context);

	// Destroy window
	SDL_DestroyWindow(pWindow);

	// Quit SDL
	SDL_Quit();

	return 0;
}
