#pragma once
#include "glm/glm.hpp"

#include "types.h"
#include "Component.h"
#include "TransformComp.h"
#include "MeshComp.h"
#include "TextureComp.h"

#include <string>
#include <sstream>
#include <vector>

using namespace std;

// GameObjects are imported, primitives are loaded independently
class GameObject
{
public:
	GameObject(string meshPath, string texturePath);
	~GameObject();

	void createComponent(component_type type, string meshPath = "", string textPath = "");

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
	string adaptPath(string ogPath);

private:
	string name = "";

	string meshName = "";
};