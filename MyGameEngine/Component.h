#pragma once

#include "Globals.h"
#include <string>
#include <regex>
using namespace std;

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

	virtual void drawComponent()
	{}

	virtual void extractName(std::string path)
	{}

	virtual component_type getType()
	{
		return type;
	}
	virtual bool getActive()
	{
		return active;
	}

private:
	component_type type = component_type::UNKNOWN;

	std::string extension = "";
	std::string name = "";
	
	bool active = true;
};