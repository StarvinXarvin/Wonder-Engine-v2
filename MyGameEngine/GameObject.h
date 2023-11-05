#pragma once
#include "glm/glm.hpp"

#include "types.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"


#include <string>
#include <vector>

using namespace std;

// GameObjects are imported, primitives are loaded independently
class GameObject
{
public:
	GameObject(string meshPath, string texturePath);
	~GameObject();

	Component* createComponent(component_type type, string path = "");
	void addComponent(Component* component);
	
	vector<Component*> component_vector;

	void drawObj();

	string getName()
	{
		return name;
	}
	void setName(string name)
	{
		this->name = name;
	}

private:
	string name = "";
};