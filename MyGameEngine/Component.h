#pragma once
#include "GameObject.h"
#include "Globals.h"

enum component_type
{
	TRANSFORM = 0,
	MESH,
	TRANSFORM,
};

class Component
{
public:
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

private:
	component_type type;
	GameObject* owner;
	bool active;
};