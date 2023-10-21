#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "Application.h"
#include "Globals.h"
#include "UI.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

UI::UI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

UI::~UI()
{
}

bool UI::createImGuiContext()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->window->GLContext);

	if (ImGui_ImplOpenGL3_Init())   return true;
	else    return false;
}

void UI::setUpUI()
{
#pragma region
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::BeginMenu("Window Toggle"))
			{
				if (ImGui::MenuItem("Hierarchy", NULL, false, false))
				{
					// Toggle Hierarchy window
				}
				if (ImGui::MenuItem("Inspector", NULL, false, false))
				{
					// Toggle Inspector window
				}
				if (ImGui::MenuItem("Configuration", NULL, false, false))
				{
					// Toggle Configuration window
				}
				if (ImGui::MenuItem("Console", NULL, false, false))
				{
					// Toggle Console window
				}
				EndMenu();
			}

			if (ImGui::MenuItem("GitHub", NULL, false, false))
			{
				// Open default explorer with our GitHub link
			}
			if (ImGui::MenuItem("About", NULL, false, false))
			{
				// Open a window with description of the editor
			}
			if (ImGui::MenuItem("Quit", "Esc", false, true))
			{
				// Quit app
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
#pragma endregion
#pragma region
	
	if (ImGui::Begin("Hierarchy"))
	{
		//for (all items in GameObject list)
		//{
		//	ImGui::MenuItem("Objectname", NULL, false, false);
		//}
		ImGui::End();
	}

	// Console
	if (ImGui::Begin("Console"))
	{
		//for (all items in log list)
		//{
		//	// Find a better way to print a prettier and less heavy log
		//	ImGui::MenuItem("HH:MM:SS  Log description", NULL, false, false);
		//}
		ImGui::End();
	}

	// Inspector
	if (ImGui::Begin("Inspector"))
	{

		if (ImGui::CollapsingHeader("Transform"))
		{
			//ImGui::SeparatorText("Position");
			//ImGui::DragFloat("x axis", NULL, ranges);
			//ImGui::DragFloat("y axis", NULL, ranges);
			//ImGui::DragFloat("z axis", NULL, ranges);
			//
			//ImGui::SeparatorText("Rotation");
			//ImGui::DragFloat("x axis", NULL, ranges);
			//ImGui::DragFloat("y axis", NULL, ranges);
			//ImGui::DragFloat("z axis", NULL, ranges);
		}
		if (ImGui::CollapsingHeader("Mesh"))
		{
			ImGui::MenuItem("Mesh Name", NULL, false, false);
		}
		if (ImGui::CollapsingHeader("Texture"))
		{
			ImGui::MenuItem("Texture Name", NULL, false, false);
		}
		ImGui::End();
	}
}

bool UI::Init()
{
	if (createImGuiContext())   return true;
	else    return false;
}

update_status UI::PreUpdate()
{
	//setUpUI();
	ImGui_ImplSDL2_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGuiDockNodeFlags dock_flags = 0;
	dock_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpaceOverViewport(0, dock_flags);

	ImGui::DockSpaceOverViewport();

	setUpUI();

	return UPDATE_CONTINUE;
}

update_status UI::PostUpdate()
{
	// Render UI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool UI::CleanUp()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}