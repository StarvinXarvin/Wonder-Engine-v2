#pragma once

#include "Module.h"
#include "../MyGameEngine/MyGameEngine.h"

class Application;

class GameEngine : public Module
{
public:
	GameEngine(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~GameEngine();

	bool Init();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	MyGameEngine engine;

	float camSensitivity = 1.0f;

public:
	float frame_ratef;
};