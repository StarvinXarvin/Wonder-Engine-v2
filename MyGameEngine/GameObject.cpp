#include "GameObject.h"

using namespace std;

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
	ssmesh << "..\\\\MyGameEditor\\\\Assets\\\\" << meshPath;
	switch (type)
	{
	case TRANSFORM:
		newComponent = new TransformComp();
		break;

	case MESH:
		// Check if files exist before loading
		if (textPath != "") mesh_shrdptrs = Mesh::loadFromFile(meshPath, textPath);
		else mesh_shrdptrs = Mesh::loadFromFile(ssmesh.str());

		for (auto item : mesh_shrdptrs) {
			newComponent = new MeshComp(item, ssmesh.str());
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

}