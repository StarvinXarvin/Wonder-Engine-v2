#pragma once

#include "EngineModule.h"
#include "GameObject.h"

#include <list>

class GameObject;

class Scene : public EngineModule
{
public:
	Scene(WonderEngine* engine, bool start_enabled = true);
	virtual ~Scene();

	bool Start();

	update_statusE PostUpdate();

	bool CleanUp();

	void addGameObj(GameObject* newGameObject);
private:
	std::list<GameObject*> gameObj_list;
};