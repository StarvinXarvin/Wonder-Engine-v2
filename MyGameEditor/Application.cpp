#include "Application.h"
#include <parson.h>
#include "Globals.h"

Application::Application() {
	window = new Window(this);
	Gengine = new GameEngine(this);
	ui = new UI(this);

	config = json_parse_file("config.json");

	AddModule(window);
	AddModule(Gengine);
	AddModule(ui);
}

Application::~Application()
{
	std::list<Module*>::iterator item = list_modules.end();

	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	LoadConfig();

	// Call Init() in all modules
	for (const auto& item : list_modules)
	{
		item->Init();
	}

	// After all Init calls we call Start() in all modules
	//
	LOG("Application Start --------------");
	for (const auto& item : list_modules)
	{
		item->Start();
	}

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();

	for (const auto& item : list_modules)
	{
		item->PreUpdate();
	}

	for (const auto& item : list_modules)
	{
		item->Update();
	}

	for (const auto& item : list_modules)
	{
		item->PostUpdate();
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	delete config;
	for (const auto& item : list_modules)
	{
		item->CleanUp();
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

void Application::SaveConfig() {

	json_object_dotset_number(json_object(config), "config.window.width", window->width);
	json_object_dotset_number(json_object(config), "config.window.height", window->height);
	json_serialize_to_file(config, "config.json");

}

void Application::LoadConfig() {

	window->height = json_object_dotget_number(json_object(config), "config.window.height");
	window->width = json_object_dotget_number(json_object(config), "config.window.width");

}