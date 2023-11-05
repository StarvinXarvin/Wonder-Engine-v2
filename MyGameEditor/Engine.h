#pragma once

#include "Module.h"
#include <vector>
#include <string>

#include "../MyGameEngine/WonderEngine.h"

using namespace std;

class Application;

enum admittedFileTypes
{
	_FBX = 0,
	_PNG,
	NOTADMITTED,
};

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

	static void createDroppedFile(string path);

private:
	WonderEngine engine;

	float camSensitivity = 1.0f;

public:
	float frame_ratef;
	std::vector<GameObject*> gObjVec;
};