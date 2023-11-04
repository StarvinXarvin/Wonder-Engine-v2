#pragma once

#include "EngineModule.h"
#include "Renderer.h"
#include "Scene.h"

class WonderEngine
{
public:
	Renderer* renderer;
	Scene* scene;
private:
	std::list<EngineModule*> list_modulesE;

public:
	WonderEngine();
	virtual ~WonderEngine();

	bool Init();
	update_statusE Update();
	bool CleanUp();

private:
	void AddModule(EngineModule* mod);
	void PrepareUpdate();
	void FinishUpdate();
};