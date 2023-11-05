#include "Scene.h"

#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

Scene::Scene(WonderEngine* engine, bool start_enabled) : EngineModule(engine, start_enabled)
{
}

Scene::~Scene()
{
}

bool Scene::Start()
{
	GameObject* defaultHouse = new GameObject("BakerHouse.fbx", "Baker_house.png");

	addGameObj(defaultHouse);

	defaultHouse = new GameObject("BakerHouse.fbx", "Baker_house.png");

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

void Scene::createGameObject(string meshPath = "", string texturePath = "")
{
	GameObject* newgObj = new GameObject(meshPath, texturePath);

	int temp = 0;
	for (GameObject* gObj : gameObj_vector)
	{
		temp++;
	}
	stringstream gObjName;
	gObjName << "GameObject_" << temp;

	newgObj->setName(gObjName.str());
}