#include "GameObject.h"
#include "Mesh.h"
#include "Transform.h"

GameObject::GameObject(std::string meshPath, std::string texturePath)
{
	Component* transform = createComponent(TRANSFORM);
	Component* mesh = createComponent(MESH, meshPath);
	Component* texture = createComponent(TEXTURE, texturePath);

	addComponent(transform);
	addComponent(mesh);
	addComponent(texture);

}

GameObject::~GameObject()
{
}

Component* GameObject::createComponent(component_type type, std::string path)
{
	Component* newComponent = nullptr;

	switch (type)
	{
	case TRANSFORM:
		newComponent = new Transform();
		break;

	case MESH:
		newComponent = new Mesh(path, );
		break;

	case TEXTURE:
		
		break;
	}

	return newComponent;
}
void GameObject::addComponent(Component* component)
{
	component_list.push_back(component);
}
