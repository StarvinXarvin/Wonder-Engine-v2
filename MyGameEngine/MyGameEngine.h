#pragma once

#include <chrono>

#include "types.h"
#include "Camera.h"
#include "Mesh.h"
#include <list>
#include <vector>

class MyGameEngine
{
public:
	Camera camera;

	MyGameEngine();
	void step(std::chrono::duration<double> dt);
	void render();

public:
	std::list<std::vector<Mesh::Ptr>> mesh_list;
};

