#include "Scene.h"


Scene::Scene(WonderEngine* engine, bool start_enabled) : EngineModule(engine, start_enabled)
{
}

Scene::~Scene()
{
}

bool Scene::Init()
{
	//define assimp scene to add meshes and materials there

	return true;
}

bool Scene::Start()
{
	GameObject* defaultHouse = new GameObject("BakerHouse.fbx", "Baker_house.png");

	addGameObj(defaultHouse);

	return true;
}

update_statusE Scene::PostUpdate()
{
	// Draw all gameObjects in the vector
	for (GameObject* gObjs : gameObj_vector)
	{
		gObjs->drawObj();
	}
	return UPDATE_CONTINUEE;
}

bool Scene::CleanUp()
{
	gameObj_vector.clear();

	return true;
}

void Scene::addGameObj(GameObject* newGameObj)
{
	gameObj_vector.push_back(newGameObj);
}