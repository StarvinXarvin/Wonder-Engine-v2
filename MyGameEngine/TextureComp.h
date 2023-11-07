#pragma once
#include "Component.h"
#include <string>

using namespace std;

class TextureComp : public Component
{
public:
	TextureComp(GameObject* owner, string path);
	virtual ~TextureComp();

	void Enable();
	update_statusE Update();
	void Disable();

private:
	component_type type = TEXTURE;

	GameObject* _owner;
};