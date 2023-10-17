#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Application.h"
#include "Globals.h"

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

			LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
		break;

		case MAIN_FINISH:

			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	delete App;
	LOG("Exiting game '%s'...\n", TITLE);
	return main_return;
}

// Hablar con el profe sobre rehacer el repositorio con este proyecto en lugar de intentar subirlo para evitar conflictos

//int main(int argc, char* argv[])
//{
//    try {
//        /auto window = initSDLWindowWithOpenGL();
//        /auto gl_context = createSdlGlContext(window);
//        /initOpenGL();
//
//        {
//            MyGameEngine engine;
//            engine.camera.fov = 60;
//            engine.camera.aspect = static_cast<double>(WINDOW_WIDTH) / WINDOW_HEIGHT;
//            engine.camera.zNear = 0.1;
//            engine.camera.zFar = 100;
//            engine.camera.eye = vec3(5, 1.75, 5);
//            engine.camera.center = vec3(0, 1, 0);
//            engine.camera.up = vec3(0, 1, 0);
//
//			// Engine manager maybe? Ask teacher
//            while (processSDLEvents()) {
//                const auto frame_start = steady_clock::now();
//                engine.step(FDT);
//                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//                engine.render();
//                SDL_GL_SwapWindow(window);
//                const auto frame_end = steady_clock::now();
//                const auto frame_duration = frame_end - frame_start;
//                if (frame_duration < FDT) this_thread::sleep_for(FDT - frame_duration);
//            }
//        }
//
//        SDL_GL_DeleteContext(gl_context);
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//
//        return EXIT_SUCCESS;
//    }
//    catch (const exception& ex) {
//       cerr << ex.what() << endl;
//        return EXIT_FAILURE;
//    }
//}