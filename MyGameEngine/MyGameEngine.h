#pragma once

#include <chrono>

#include "types.h"
#include "Camera.h"

class MyGameEngine
{
public:
	Camera camera;

	MyGameEngine();
	void step(std::chrono::duration<double> dt);
	void render();
	void LoadConfig();
	void SaveConfig();

	JSON_Value* config;
};

