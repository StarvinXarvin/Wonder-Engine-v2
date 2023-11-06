#include "GameObject.h"
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = filesystem;

GameObject::GameObject(string meshPath = "", string texturePath = "")
{
	createComponent(TRANSFORM);
	if (meshPath != "") createComponent(MESH, meshPath);
	if (texturePath != "") createComponent(TEXTURE, texturePath);

	this->name = "defaultName";
}

GameObject::~GameObject()
{
}

void GameObject::createComponent(component_type type, string meshPath, string textPath)
{
	Component* newComponent = nullptr;
	vector<Mesh::Ptr> mesh_shrdptrs;

	stringstream ssmesh;
	ssmesh << "..\\MyGameEditor\\Assets\\" << meshPath;

	ifstream file(ssmesh.str());
	if (file.good())
	{
		cout << "ur mom" << endl;
	}

	switch (type)
	{
	case TRANSFORM:
		newComponent = new TransformComp();
		component_vector.push_back(newComponent);
		break;

	case MESH:
		// Check if files exist before loading
		if (textPath != "") mesh_shrdptrs = Mesh::loadFromFile(meshPath, textPath);
		else mesh_shrdptrs = Mesh::loadFromFile(ssmesh.str());

		for (auto item : mesh_shrdptrs) {
			newComponent = new MeshComp(item, ssmesh.str());
			component_vector.push_back(newComponent);
		}
		break;

	case TEXTURE:
		//newComponent = new TextureComp();
		//component_vector.push_back(newComponent);
		break;
	}
	mesh_shrdptrs.clear();
}

void GameObject::drawObj()
{
	// Draws all the components in the vector of an object
	for (auto item : component_vector)
	{
		if(item->getType() == MESH)	item->drawComponent();
	}
}