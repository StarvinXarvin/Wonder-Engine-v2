#include "Scene.h"

#include "Mesh.h"
#include "Texture.h"

#include <iostream>
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
	createGameObject("Assets/BakerHouse.fbx", "Assets/Baker_house.png");

	return true;
}

update_statusE Scene::PostUpdate()
{
	// Draw all gameObjects in the vector
	for (auto gObjs : gameObj_vector)
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

void Scene::createGameObject(string meshPath, string texturePath)
{
	GameObject* newgObj = new GameObject();

	MeshComp* meshcomp = nullptr;
	TextureComp* textcomp = nullptr;
	if (meshPath != "")
	{
#pragma region Mesh names
		string meshname;
		string meshcompname;

		// Correct \ in the path when using drag and drop
		size_t found = meshPath.find("\\");
		while (found != string::npos)
		{
			meshPath.replace(found, 1, "/");
			found = meshPath.find("\\", found + 1);
		}

		size_t slashplace = meshPath.find_last_of("/");
		meshname = meshPath.substr(slashplace + 1, meshPath.size() - slashplace - 5);
		meshcompname = meshPath.substr(slashplace + 1, meshPath.size());
#pragma endregion
#pragma region Texture names
		string texturename = "";
		string texturecompname = "";

		if (texturePath != "") {
			size_t found = texturePath.find("\\");
			while (found != string::npos)
			{
				texturePath.replace(found, 1, "/");
				found = texturePath.find("\\", found + 1);
			}

			size_t slashplace = texturePath.find_last_of("/");
			texturename = texturePath.substr(slashplace + 1, texturePath.size() - slashplace - 5);
			texturecompname = texturePath.substr(slashplace + 1, texturePath.size());
		}
#pragma endregion

		// Load meshs to a vector
		vector<Mesh::Ptr> mesh_ptrs;
		if (texturePath != "")
		{
			mesh_ptrs = Mesh::loadFromFile(meshPath, texturePath);
		}
		else
		{
			mesh_ptrs = Mesh::loadFromFile(meshPath);
		}

		// Create components for the new gameobject
		// Create all meshes as new gameobjects, childs of the newgObj
		for (auto mesh : mesh_ptrs)
		{
			GameObject* newGOchild = new GameObject();
			newgObj->addChild(newGOchild);

			for (auto comp : newGOchild->component_vector)
			{
				if (comp->getType() == MESH)
				{
					meshcomp = (MeshComp*)comp;
					meshcomp->setMesh(mesh);
				}
				if (comp->getType() == TEXTURE)
				{
					textcomp = (TextureComp*)comp;
					textcomp->setTexture(mesh->texture);
				}
			}

			newGOchild->setName(meshname);
			newGOchild->getComponent(MESH)->setName(meshcompname);
			newGOchild->getComponent(MESH)->setFilePath(meshPath);

			if (texturename != "") {
				newGOchild->setName(texturename);
				newGOchild->getComponent(TEXTURE)->setName(texturecompname);
				newGOchild->getComponent(TEXTURE)->setFilePath(texturePath);
			}
		}
	}

	int temp = 0;
	for (auto gObj : gameObj_vector)
	{
		temp++;
	}
	stringstream gObjName;
	gObjName << "GameObject_" << temp;

	newgObj->setName(gObjName.str());

	addGameObj(newgObj);
}

void Scene::changeTextureofObj(GameObject* gObj, string path)
{
	MeshComp* meshcomp = nullptr;
	TextureComp* textcomp = nullptr;

	for (auto comp : gObj->component_vector)
	{
		if (comp->getType() == TEXTURE)
		{
			textcomp = (TextureComp*)comp;
			break;
		}
	}
	for (auto comp : gObj->component_vector)
	{
		if (comp->getType() == MESH && textcomp != nullptr)
		{
			meshcomp = (MeshComp*)comp;
			meshcomp->getMeshData()->loadTextureToMesh(path);
			textcomp->setTexture(meshcomp->getMeshData()->texture);
		}
	}
}