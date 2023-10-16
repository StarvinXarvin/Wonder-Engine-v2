#include "Module.h"
#include <SDL2/SDL.h>

class Application;

class Window : public Module
{
public:

	Window(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~Window();

	bool Init();
	update_status PostUpdate();
	bool CleanUp();

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;

	// OpenGL Context creation
	SDL_GLContext GLContext;
};