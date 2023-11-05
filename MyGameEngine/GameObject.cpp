#include "GameObject.h"

using namespace std;

GameObject::GameObject(string meshPath = "", string texturePath = "")
{
	Component* transform = createComponent(TRANSFORM);
	Component* mesh = createComponent(MESH, meshPath);
	//Component* texture = createComponent(TEXTURE, texturePath);

	addComponent(transform);
	addComponent(mesh);
	//addComponent(texture);

	this->name = "defaultName";
}

GameObject::~GameObject()
{
}

Component* GameObject::createComponent(component_type type, string path)
{
	Component* newComponent = nullptr;

	switch (type)
	{
	case TRANSFORM:
		newComponent = new Transform();
		break;

	case MESH:
		newComponent = new Mesh(path);
		break;

	case TEXTURE:

		break;
	}

	return newComponent;
}
void GameObject::addComponent(Component* component)
{
	component_vector.push_back(component);
}

void GameObject::drawObj()
{
	// Draws all the components in the vector of an object
	for (Component* item : component_vector)
	{
		if (item->getActive()) item->drawComponent();
	}
}