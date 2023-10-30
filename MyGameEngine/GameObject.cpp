#include "GameObject.h"
#include "Mesh.h"
#include "Transform.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

Component* GameObject::createComponent(component_type type)
{
	Component* newComponent = nullptr;

	switch (type)
	{
	case TRANSFORM:
		newComponent = new Transform();
		break;

	case MESH:
		newComponent = new Mesh();
		break;

	case TEXTURE:
		
		break;
	}

	return newComponent;
}