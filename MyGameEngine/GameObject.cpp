#include "GameObject.h"

GameObject::GameObject(Mesh mesh) : position(0, 0, 0), rotation(0, 0, 0), scale(0, 0, 0)
{
	this->mesh = mesh;
}

GameObject::~GameObject()
{
}


vec3f GameObject::getPos()
{
	return position;
}

vec3f GameObject::getRot()
{
	return rotation;
}

vec3f GameObject::getScale()
{
	return scale;
}

void GameObject::setPos(vec3f newPos)
{
	position = newPos;
}

void GameObject::setRot(vec3f newRot)
{
	rotation = newRot;
}

void GameObject::setScale(vec3f newScale)
{
	scale = newScale;
}