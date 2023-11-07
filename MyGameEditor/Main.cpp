#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <sstream>

#include "Application.h"
#include "Globals.h"

using namespace std;

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char** argv)
{
	//LOG("Starting game '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;

	//Test de parsing
	//Parse();

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			App = new Application();
			App->Gengine->addLOG("Application Creation --------------");
			state = MAIN_START;
			break;

		case MAIN_START:

			App->Gengine->addLOG("Application Init--------------");
			if (App->Init() == false)
			{
				App->Gengine->addLOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				App->Gengine->addLOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
		break;

		case MAIN_FINISH:

			App->Gengine->addLOG("Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				App->Gengine->addLOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;
		}
	}

	stringstream ss;
	ss << "Exiting app " << TITLE;
	App->Gengine->addLOG(ss.str());
	delete App;
	return main_return;
}