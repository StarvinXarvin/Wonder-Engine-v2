#pragma once
#include "glm/glm.hpp"

#include "types.h"
#include "Component.h"

#include <string>
#include <vector>

// GameObjects are imported, primitives are loaded independently
class GameObject
{
public:
	GameObject(std::string meshPath, std::string texturePath = "");
	~GameObject();

	Component* createComponent(GameObject* owner, component_type type, std::string path = "");
	void addComponent(Component* component);
	
	std::vector<Component*> component_vector;

	void draw();
};