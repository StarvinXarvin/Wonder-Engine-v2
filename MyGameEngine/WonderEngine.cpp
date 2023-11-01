#include "WonderEngine.h"
#include <list>
#include <IL/il.h>

WonderEngine::WonderEngine()
{
	renderer = new Renderer(this);
	scene = new Scene(this);

	AddModule(renderer);
	AddModule(scene);

	ilInit();
}

WonderEngine::~WonderEngine()
{
	std::list<EngineModule*>::iterator item = list_modulesE.end();

	list_modulesE.clear();
}

bool WonderEngine::Init()
{
	bool ret = true;

	// Call Init() in all modules
	for (const auto& item : list_modulesE)
	{
		ret = item->Init();
		if (ret == false) return ret;
	}

	// After all Init calls we call Start() in all modules
	//
	LOG("Engine Start --------------");
	for (const auto& item : list_modulesE)
	{
		ret = item->Start();
		if (ret == false) return ret;
	}

	return ret;
}

void WonderEngine::PrepareUpdate()
{
}

// ---------------------------------------------
void WonderEngine::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_statusE WonderEngine::Update()
{
	update_statusE ret = UPDATE_CONTINUEE;
	PrepareUpdate();

	for (const auto& item : list_modulesE)
	{
		ret = item->PreUpdate();
		if (ret == UPDATE_STOPE) return ret;
	}

	for (const auto& item : list_modulesE)
	{
		ret = item->Update();
		if (ret == UPDATE_STOPE) return ret;
	}

	for (const auto& item : list_modulesE)
	{
		ret = item->PostUpdate();
		if (ret == UPDATE_STOPE) return ret;
	}

	FinishUpdate();

	return ret;
}

bool WonderEngine::CleanUp()
{
	bool ret = true;
	for (const auto& item : list_modulesE)
	{
		ret = item->CleanUp();
	}
	return ret;
}

void WonderEngine::AddModule(EngineModule* mod)
{
	list_modulesE.push_back(mod);
}

/*
static void drawAxis() {
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

static void drawGrid(int grid_size, int grid_step) {
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

void MyGameEngine::render() {

	//PostUpdate of render

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);            //Para hacer que se ponga en wireframe

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


	if (mesh_list.empty())
	{
		//static auto mesh_ptrs = Mesh::loadFromFile("Assets/BakerHouse.fbx");
		mesh_list.push_back(Mesh::loadFromFile("Assets/BakerHouse.fbx"));
	}
	if (!mesh_list.empty()) {
		for (const auto& mesh_list_item : mesh_list)
		{
			for (const auto& mesh_ptr_vector : mesh_list_item)
			{
				mesh_ptr_vector->draw();

			}
		}
	}

#pragma endregion
	assert(glGetError() == GL_NONE);
}
*/