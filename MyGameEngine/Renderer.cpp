#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "Renderer.h"
//#include "GraphicObject.h"
#include "Mesh.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>
#include <vector>

Renderer::Renderer(WonderEngine* engine, bool start_enabled) : EngineModule(engine, start_enabled)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Init()
{
	return true;
}

bool Renderer::Start()
{
	mesh_list.push_back(Mesh::loadFromFile("Assets/BakerHouse.fbx"));

	return true;
}

update_statusE Renderer::PreUpdate()
{
	return UPDATE_CONTINUEE;
}

update_statusE Renderer::Update()
{
	return UPDATE_CONTINUEE;
}

update_statusE Renderer::PostUpdate()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera.fov, camera.aspect, camera.zNear, camera.zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
		camera.center.x, camera.center.y, camera.center.z,
		camera.up.x, camera.up.y, camera.up.z);

	drawGrid(100, 1);
	drawAxis();

#pragma region Draw Sandbox
	//auto cubeDraw = make_shared<CubeImmediateMode>();
	//GraphicObject cubeA(cubeDraw);
	//GraphicObject cubeB(cubeDraw);
	//GraphicObject cubeC(cubeDraw);

	//cubeA.addChild(&cubeB);
	//cubeB.addChild(&cubeC);
	//cubeB.pos().y = 2.5;
	//cubeC.pos().x = 2.5;
	//
	//cubeA.rotate(glm::radians(angle), vec3(0, 1, 0));
	//cubeB.rotate(glm::radians(angle), vec3(1, 0, 0));
	//cubeC.rotate(glm::radians(angle), vec3(0, 0, 1));

	//cubeA.paint();


	for (const auto& mesh_list_item : mesh_list)
	{
		for (const auto& mesh_ptr_vector : mesh_list_item)
		{
			mesh_ptr_vector->draw();
		}
	}

#pragma endregion
	assert(glGetError() == GL_NONE);

	return UPDATE_CONTINUEE;
}

bool Renderer::CleanUp()
{
	return true;
}

void Renderer::drawAxis()
{
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0.8, 0, 0);
	glColor3ub(0, 255, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0.8, 0);
	glColor3ub(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 0.8);
	glEnd();
}
void Renderer::drawGrid(int grid_size, int grid_step)
{
	glLineWidth(1.0);
	glColor3ub(128, 128, 128);

	glBegin(GL_LINES);
	for (int i = -grid_size; i <= grid_size; i += grid_step) {
		//XY plane
		glVertex2i(i, -grid_size);
		glVertex2i(i, grid_size);
		glVertex2i(-grid_size, i);
		glVertex2i(grid_size, i);

		//XZ plane
		glVertex3i(i, 0, -grid_size);
		glVertex3i(i, 0, grid_size);
		glVertex3i(-grid_size, 0, i);
		glVertex3i(grid_size, 0, i);
	}
	glEnd();
}