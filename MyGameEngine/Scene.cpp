#include "Scene.h"

#include "Mesh.h"
#include "Texture.h"
//#include "Importer.h"

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
	createGameObject("Assets/Default_House/BakerHouse.fbx");

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

		// Load meshs to a vector
		vector<Mesh::Ptr> mesh_ptrs;
		if (texturePath != "")
		{
			mesh_ptrs = Mesh::loadFromFile(meshPath, texturePath);
		}
		else
		{
			MeshDto* dto = new MeshDto;
			MeshImporter::MeshImport(*dto, meshPath);
			MeshImporter::MeshSave("Library/saveDto.wdr", *dto);
			MeshImporter::MeshLoad("Library/saveDto.wdr", *dto);
			auto mesh_sptr = make_shared<Mesh>(DTOToMesh(*dto)->F_V3T2, DTOToMesh(*dto)->meshVertsV3T2.data(), DTOToMesh(*dto)->getVerts(), DTOToMesh(*dto)->getFaces(), DTOToMesh(*dto)->meshIndices.data(), DTOToMesh(*dto)->getIndexs());
			mesh_sptr.get()->loadTextureToMesh("Assets/Baker_house.png");
			mesh_ptrs.push_back(mesh_sptr); //Parece que el problema est� aqui porque el resto lo compila bien 
			delete dto;
			//mesh_ptrs = Mesh::loadFromFile(meshPath);
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
					textcomp->setTexture(mesh->texture); //Falta la textura (Me cago en mi putisima estampa)
														 //Tiene que sacar la textura del Devil probablemente
				}
			}

			newGOchild->setName(meshname);
			newGOchild->getComponent(MESH)->setName(meshcompname);
			newGOchild->getComponent(MESH)->setFilePath(meshPath);

			
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