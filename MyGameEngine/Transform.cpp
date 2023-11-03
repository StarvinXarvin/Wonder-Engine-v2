#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "Transform.h"

Transform::Transform() : Component(TRANSFORM)
{	
	active = true;

	Position = (vec3)(0, 0, 0);
	Rotation = (vec3)(0, 0, 0);
	Scale = (vec3)(1, 1, 1);
}

Transform::~Transform()
{
}

void Transform::Enable()
{
	active = true;
}
void Transform::Disable()
{
	active = false;
}