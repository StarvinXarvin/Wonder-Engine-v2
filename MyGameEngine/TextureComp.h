#pragma once
#include "Component.h"
#include "Globals.h"
#include "Texture.h"

#include <memory>
#include <string>
#include <vector>

using namespace std;

class TextureComp : public Component
{
public:
	TextureComp(GameObject* owner);
	virtual ~TextureComp() {}

	void Enable()
	{
		active = true;
	}
	update_statusE Update()
	{
		return UPDATE_CONTINUEE;
	}
	void Disable()
	{
		active = false;
	}

	void extractName(string path);

	void setTexture(Texture::Ptr texture)
	{
		_texture = texture;
	}

private:
	Texture::Ptr _texture;

	component_type type = TEXTURE;

	string extension = "\.png";
	string name = "";

	bool active = true;

	GameObject* _owner;
};