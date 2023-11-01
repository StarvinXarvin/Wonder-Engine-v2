#include "Scene.h"

Scene::Scene(WonderEngine* engine, bool start_enabled) : EngineModule(engine, start_enabled)
{
}

Scene::~Scene()
{
}

bool Scene::Start()
{
	GameObject* defaultHouse = new GameObject("BakerHouse", "Baker_house");

	addGameObj(defaultHouse);

	return true;
}

update_statusE Scene::PostUpdate()
{
	for (GameObject* gObjs : gameObj_list)
	{
		gObjs->draw();
	}

	return UPDATE_CONTINUEE;
}

bool Scene::CleanUp()
{
	gameObj_list.clear();

	return true;
}

void Scene::addGameObj(GameObject* newGameObj)
{
	gameObj_list.push_back(newGameObj);
}