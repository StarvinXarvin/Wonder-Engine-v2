#include "GameObject.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

using namespace std;
namespace fs = filesystem;

GameObject::GameObject(string meshPath = "", string texturePath = "")
{
	createComponent(this, TRANSFORM);
	if (meshPath != "") createComponent(this, MESH, meshPath);
	if (texturePath != "") createComponent(this, TEXTURE, texturePath);

	this->name = "defaultName";
}

GameObject::~GameObject()
{
}

void GameObject::createComponent(GameObject* owner, component_type type, string meshPath, string textPath)
{
	Component* newComponent = nullptr;
	vector<Mesh::Ptr> mesh_shrdptrs;

	stringstream ssfilePath;
	ssfilePath << "..\\MyGameEditor\\Assets\\" << meshPath;

	ifstream file(ssfilePath.str());

	smatch match;
	regex filenamerg(".*(.+)\.fbx");

	if (type == TRANSFORM || file.good()) {
		switch (type)
		{
		case TRANSFORM:
			newComponent = new TransformComp(owner);
			component_vector.push_back(newComponent);
			break;

		case MESH:
			// Check if files exist before loading
			if (textPath != "") mesh_shrdptrs = Mesh::loadFromFile(meshPath, textPath);
			else mesh_shrdptrs = Mesh::loadFromFile(ssfilePath.str());

			for (auto item : mesh_shrdptrs) {
				newComponent = new MeshComp(owner, item, ssfilePath.str());
				component_vector.push_back(newComponent);
			}
			break;

		case TEXTURE:
			//newComponent = new TextureComp(owner);
			//component_vector.push_back(newComponent);
			break;
		}
	}
	else {
		// LOG wrong file path
	}

	mesh_shrdptrs.clear();
}

void GameObject::drawObj()
{
	// Draws all the components in the vector of an object
	for (auto item : component_vector)
	{
		if (item->getType() == MESH)	item->drawComponent();
	}
}