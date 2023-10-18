#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "Application.h"
#include "Globals.h"
#include "Engine.h"
#include "Window.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

using namespace std;
using namespace chrono;

static const unsigned int FPS = 60;
static const auto FDT = 1.0s / FPS;

GameEngine::GameEngine(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

GameEngine::~GameEngine()
{
}

bool GameEngine::Init()
{
	engine.camera.fov = 60;
	engine.camera.aspect = static_cast<double>(WINDOW_WIDTH) / WINDOW_HEIGHT;
	engine.camera.zNear = 0.1;
	engine.camera.zFar = 100;
	engine.camera.eye = vec3(5, 1.75, 5);
	engine.camera.center = vec3(0, 1, 0);
	engine.camera.up = vec3(0, 1, 0);

	return true;
}

update_status GameEngine::PostUpdate()
{
	const auto frame_start = steady_clock::now();
	engine.step(FDT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	engine.render();
	const auto frame_end = steady_clock::now();
	const auto frame_duration = frame_end - frame_start;
	if (frame_duration < FDT) this_thread::sleep_for(FDT - frame_duration);

	return UPDATE_CONTINUE;
}

bool GameEngine::CleanUp()
{
	return true;
}