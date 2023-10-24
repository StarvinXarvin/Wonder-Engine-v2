#pragma once

#include "EngineModule.h"
#include "Camera.h"
#include "Mesh.h"

#include <list>
#include <vector>

class Renderer : public EngineModule
{
public:
	Renderer(WonderEngine* engine, bool start_enabled = true);
	virtual ~Renderer();

	bool Init();
	bool Start();
	update_statusE PreUpdate();
	update_statusE Update();
	update_statusE PostUpdate();
	bool CleanUp();

public:
	static void drawAxis();
	static void drawGrid(int grid_size, int grid_step);
	Camera camera;
private:


	std::list<std::vector<Mesh::Ptr>> mesh_list;
};