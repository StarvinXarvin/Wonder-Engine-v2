#pragma once

#include "Globals.h"
#include "Module.h"
#include "Window.h"
#include "Engine.h"
#include "UI.h"

#include "parson.h"
#include <list>

class Application {
public:
	Window* window;
	GameEngine* Gengine;
	UI* ui;

private:
	std::list<Module*> list_modules;

public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	JSON_Value* config;

private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	void SaveConfig();
	void LoadConfig();
};