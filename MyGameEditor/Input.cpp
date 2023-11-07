#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "Application.h"
#include "Globals.h"
#include "Input.h"
#include "Engine.h"

#include <SDL2/SDL.h>
#include <imgui_impl_sdl2.h>

#define MAX_KEYS 300

Input::Input(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Input::~Input()
{
}

bool Input::Init()
{
	App->Gengine->addLOG("Input Initialization");

	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);

	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		stringstream ss;
		ss << "SDL_EVENTS could not initialize! SDL_Error: " << SDL_GetError();
		App->Gengine->addLOG(ss.str());
		ret = false;
	}

	return ret;
}

update_status Input::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= WINDOW_SIZE;
	mouse_y /= WINDOW_SIZE;
	mouse_z = 0;

	for (int i = 0; i < 5; ++i)
	{
		if (buttons & SDL_BUTTON(i))
		{
			if (mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if (mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

		case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / WINDOW_SIZE;
			mouse_y = e.motion.y / WINDOW_SIZE;

			mouse_x_motion = e.motion.xrel / WINDOW_SIZE;
			mouse_y_motion = e.motion.yrel / WINDOW_SIZE;
			break;

		case SDL_QUIT:
			quit = true;
			break;

		case SDL_DROPFILE:
			string path = e.drop.file;
			size_t lastslash = path.find_last_of("\\");
			string filename = path.substr(lastslash + 1, path.size());
			stringstream pathfromengine;
			pathfromengine << "..\\MyGameEditor\\Assets\\" << filename;
			stringstream ss;
			ss << "File with path: " << path << " dropped";
			App->Gengine->addLOG(ss.str());
			App->Gengine->createDroppedFile(pathfromengine.str());
			break;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	if (quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

bool Input::CleanUp()
{
	delete[] keyboard;
	App->Gengine->addLOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}