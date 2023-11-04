#pragma once

#include "Module.h"
#include <vector>
#include "../MyGameEngine/WonderEngine.h"

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

	void detectCameraInput();

private:
	WonderEngine engine;

	float camSensitivity = 1.0f;


public:
	float frame_ratef;
	std::vector<GameObject*> gObjVec;
};