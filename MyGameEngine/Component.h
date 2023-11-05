#pragma once

#include "Globals.h"
#include "types.h"
#include <vector>
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
	virtual string getName()
	{
		return name;
	}

	virtual vector<vec3> getData()
	{
		vector<vec3> empty;
		return empty;
	}

private:
	component_type type = component_type::UNKNOWN;

	string extension = "";
	string name = "";
	
	bool active = true;
};