#pragma once
#include "Component.h"
#include <string>

using namespace std;

class GameObject;

class TextureComp : public Component
{
public:
	TextureComp(string path);
	virtual ~TextureComp();

	void Enable();
	update_statusE Update();
	void Disable();

private:
	component_type type = TEXTURE;
};