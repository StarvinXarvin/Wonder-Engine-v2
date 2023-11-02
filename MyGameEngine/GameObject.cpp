#include "GameObject.h"

#include "Transform.h"
#include "Mesh.h"


GameObject::GameObject(std::string meshPath, std::string texturePath)
{
	Component* transform = createComponent(this, TRANSFORM);
	Component* mesh = createComponent(this, MESH, meshPath);
	//Component* texture = createComponent(TEXTURE, texturePath);

	addComponent(transform);
	addComponent(mesh);
	//addComponent(texture);
}

GameObject::~GameObject()
{
}

Component* GameObject::createComponent(GameObject* owner, component_type type, std::string path)
{
	Component* newComponent = nullptr;

	switch (type)
	{
	case TRANSFORM:
		newComponent = new Transform(owner);
		break;

	case MESH:
		newComponent = new Mesh(path, owner);
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

void GameObject::draw()
{
	// Draws all the components in the vector of an object
	for (Component* item : component_vector)
	{
		if (item->getActive()) item->drawComponent();
	}

}