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
	TextureComp(GameObject* owner, Texture::Ptr texture, string path);
	virtual ~TextureComp();

	void Enable();
	update_statusE Update();
	void Disable();

	void extractName(string path);

	void setTexture(Texture::Ptr texture)
	{
		_texture = texture;
	}

	string getName()
	{
		return this->name;
	}

	Texture::Ptr getTextureData()
	{
		return _texture;
	}

private:
	Texture::Ptr _texture;
	
	component_type type = TEXTURE;

	string extension = "\.png";
	string name = "";

	bool active = true;

	GameObject* _owner;

};