#pragma once

#include "Module.h"
#include "Globals.h"
#include "SDL2/SDL.h"

class Input : public Module
{
public:
	Input(Application* app, bool start_enabled = true);
	
	// Destructor
	virtual ~Input();

	bool Start();
	bool Init();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	bool CleanUp();
};
