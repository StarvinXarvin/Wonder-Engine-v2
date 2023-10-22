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

void UI::calculateFramerate()
{
	frame_rate = 1.0f / App->Gengine->frame_ratef * 1000000000;

	milliseconds = App->Gengine->frame_ratef * 0.000001f;

	frame_list.push_back(frame_rate);
	if (frame_list.size() > 100)
	{
		frame_list.erase(frame_list.begin());
	}

	ms_list.push_back(milliseconds);
	if (ms_list.size() > 100)
	{
		ms_list.erase(ms_list.begin());
	}
}

update_status UI::setupMAINMENU()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::BeginMenu("Window Toggle"))
			{
				ImGui::Checkbox("Hierarchy", &showHier);
				ImGui::Checkbox("Inspector", &showInsp);
				ImGui::Checkbox("Configuration", &showConf);
				ImGui::Checkbox("Console", &showCons);
				ImGui::EndMenu();
			}

			ImGui::Checkbox("Show Demo Window", &showDemo);

			if (ImGui::MenuItem("GitHub", NULL, false, true))
			{

			}

			ImGui::Checkbox("About", &showAbout);

			if (ImGui::MenuItem("Quit", "Esc", false, true))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	return UPDATE_CONTINUE;
}
void UI::setupHIERARCHY()
{
	if (ImGui::Begin("Hierarchy"))
	{
		//for (all items in GameObject list)
		//{
		//	ImGui::MenuItem("Objectname", NULL, false, false);
		//}
		ImGui::End();
	}
}
void UI::setupCONSOLE()
{
	if (ImGui::Begin("Console"))
	{
		//for (all items in log list)
		//{
		//	// Find a better way to print a prettier and less heavy log
		//	ImGui::MenuItem("HH:MM:SS  Log description", NULL, false, false);
		//}
		ImGui::End();
	}
}
void UI::setupINSPECTOR()
{
	if (ImGui::Begin("Inspector"))
	{
		if (ImGui::CollapsingHeader("Transform"))
		{
			ImGui::SeparatorText("Position");
			ImGui::DragFloat(posxlabel, &fobjPos.x);
			ImGui::DragFloat(posylabel, &fobjPos.y);
			ImGui::DragFloat(poszlabel, &fobjPos.z);

			ImGui::SeparatorText("Rotation");
			ImGui::DragFloat(anglexlabel, &fobjRot.x);
			ImGui::DragFloat(angleylabel, &fobjRot.y);
			ImGui::DragFloat(anglezlabel, &fobjRot.z);
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
void UI::setupCONFIG()
{
	if (ImGui::Begin("Configuration"))
	{
		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::PlotHistogram("FPS", &frame_list[0], frame_list.size(), 0, 0, 0.0f, 100.0f, ImVec2(310, 100));

			ImGui::PlotHistogram("Milliseconds", &ms_list[0], ms_list.size(), 0, 0, 0.0f, 100.0f, ImVec2(310, 100));
		}
	}
}
void UI::setupABOUT()
{
	if (ImGui::Begin("About"))
	{
		ImGui::Text("Hello test text");
	}
}

update_status UI::setUpUI()
{
	update_status ret = UPDATE_CONTINUE;

	ret = setupMAINMENU();
	if (showHier) setupHIERARCHY();
	if (showCons) setupCONSOLE();
	if (showInsp) setupINSPECTOR();

	calculateFramerate();
	if (showConf) setupCONFIG();

	if (showAbout) setupABOUT();
	if (showDemo) ImGui::ShowDemoWindow();

	return ret;
}

bool UI::Init()
{
	fobjPos.x = 3; fobjPos.y = 3; fobjPos.z = 3;
	fobjRot.x = 10; fobjRot.y = 10; fobjRot.z = 10;

	showDemo = false;
	showHier = true;
	showCons = true;
	showInsp = true;
	showConf = true;

	showAbout = false;

	frame_list.push_back(0);
	ms_list.push_back(0);

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

	return setUpUI();
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