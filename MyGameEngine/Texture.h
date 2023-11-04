#pragma once
#include "Component.h"
#include <string>

using namespace std;

class GameObject;

class Texture : Component
{
	Texture(string path);
	virtual ~Texture();

	void Enable();
	update_statusE Update();
	void Disable();

private:
	component_type type = TEXTURE;
};