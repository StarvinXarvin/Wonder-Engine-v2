#pragma once
#include "Component.h"

class GameObject;

class Texture : Component
{
	Texture(GameObject* parent, bool start_enabled = true);
	virtual ~Texture();

	void Enable();
	update_statusE Update();
	void Disable();

private:
	component_type type = TEXTURE;
	GameObject* owner;
};