#pragma once
#include "GameObject.h"
#include "Globals.h"

class GameObject;

enum component_type
{
	TRANSFORM = 0,
	MESH,
	TEXTURE,
	UNKNOWN
};

class Component
{
public:
	GameObject* gameObj;

	Component(component_type type, GameObject* owner) : type(type), active(true)
	{}
	virtual ~Component()
	{}

	virtual void Enable()
	{
		active = true;
	}
	virtual update_statusE Update()
	{
		return UPDATE_CONTINUEE;
	}
	virtual void Disable()
	{
		active = false;
	}

	virtual void drawComponent()
	{}

	component_type getType()
	{
		return type;
	}
	GameObject* getOwner()
	{
		return owner;
	}
	bool getActive()
	{
		return active;
	}

private:
	component_type type = component_type::UNKNOWN;
	
	GameObject* owner = nullptr;
	
	std::string extension = "";
	std::string name = "";
	
	bool active = true;
};