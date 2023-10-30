#pragma once
#include "GameObject.h"
#include "Globals.h"

class GameObject;

enum component_type
{
	TRANSFORM = 0,
	MESH,
	TEXTURE,
};

class Component
{
public:
	GameObject* gameObj;

	Component(component_type type) : type(type), active(true)
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

	component_type getType()
	{
		return type;
	}
	GameObject* getOwner()
	{
		return owner;
	}

private:
	component_type type;
	GameObject* owner;
	bool active;
};