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

using namespace ImGui;

UI::UI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

UI::~UI()
{
}

bool UI::createImGuiContext()
{
	IMGUI_CHECKVERSION();
	CreateContext();
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
	if (frame_list.size() > 80)
	{
		frame_list.erase(frame_list.begin());
	}

	ms_list.push_back(milliseconds);
	if (ms_list.size() > 80)
	{
		ms_list.erase(ms_list.begin());
	}
}

update_status UI::setupMAINMENU()
{
	if (BeginMainMenuBar()) {
		if (BeginMenu("Menu"))
		{
			if (BeginMenu("Window Toggle"))
			{
				Checkbox("Hierarchy", &showHier);
				Checkbox("Inspector", &showInsp);
				Checkbox("Configuration", &showConf);
				Checkbox("Console", &showCons);
				ImGui::EndMenu();
			}

			Checkbox("Show Demo Window", &showDemo);

			if (MenuItem("GitHub", NULL, false, true))
			{

			}

			Checkbox("About", &showAbout);

			if (MenuItem("Quit", "Esc", false, true))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		EndMainMenuBar();
	}
	return UPDATE_CONTINUE;
}
void UI::setupHIERARCHY()
{
	if (Begin("Hierarchy"))
	{
		for (auto& gObj : App->Gengine->gObjVec)
		{
			if (TreeNode(gObj->getName().c_str()))
			{
				selectedObj = gObj;
				for (auto comp : gObj->component_vector)
				{
					int temp = 0;
					if (comp->getType() != TRANSFORM)
					{
						MenuItem(comp->getName().c_str());
					}
				}
				TreePop();
			}
		}
		End();
	}
}
void UI::setupCONSOLE()
{
	if (Begin("Console"))
	{
		for (auto log : App->Gengine->LOGS)
		{
			Text(log.c_str());
		}
		End();
	}
}
void UI::setupINSPECTOR()
{
	if (Begin("Inspector"))
	{
		if (CollapsingHeader("Transform"))
		{
			SeparatorText("Position");
			DragFloat(posxlabel, &fobjPos.x);
			DragFloat(posylabel, &fobjPos.y);
			DragFloat(poszlabel, &fobjPos.z);

			SeparatorText("Rotation");
			DragFloat(anglexlabel, &fobjRot.x);
			DragFloat(angleylabel, &fobjRot.y);
			DragFloat(anglezlabel, &fobjRot.z);

			SeparatorText("Scale");
			DragFloat(scalexlabel, &fobjSca.x);
			DragFloat(scaleylabel, &fobjSca.y);
			DragFloat(scalezlabel, &fobjSca.z);
		}
		if (CollapsingHeader("Mesh"))
		{
			MenuItem("Mesh Name", NULL, false, false);
		}
		if (CollapsingHeader("Texture"))
		{
			MenuItem("Texture Name", NULL, false, false);
		}
		End();
	}
}
void UI::setupCONFIG()
{
	if (Begin("Configuration"))
	{
		if (CollapsingHeader("Application"))
		{
			PlotHistogram("FPS", &frame_list[0], frame_list.size(), 0, 0, 0.0f, 100.0f, ImVec2(310, 100));

			PlotHistogram("ms", &ms_list[0], ms_list.size(), 0, 0, 0.0f, 100.0f, ImVec2(310, 100));
		}
		if (CollapsingHeader("Modules"))
		{
			if (BeginMenu("Window", NULL)){}
			if (BeginMenu("Renderer", NULL)){}
		}
	}
}
void UI::setupABOUT()
{
	if (Begin("About"))
	{
		Text("Hello test text");
	}
}

update_status UI::setUpUI()
{
	update_status ret = UPDATE_CONTINUE;

	ret = setupMAINMENU();
	if (showHier) setupHIERARCHY();
	if (showCons) setupCONSOLE();
	
	updateObjInspector();
	if (showInsp) setupINSPECTOR();

	calculateFramerate();
	if (showConf) setupCONFIG();

	if (showAbout) setupABOUT();
	if (showDemo) ShowDemoWindow();

	return ret;
}

bool UI::Init()
{
	App->Gengine->addLOG("UI Initialization");

	fobjPos.x = 0; fobjPos.y = 0; fobjPos.z = 0;
	fobjRot.x = 0; fobjRot.y = 0; fobjRot.z = 0;
	fobjSca.x = 1; fobjSca.y = 1; fobjSca.z = 1;

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
	NewFrame();

	ImGuiDockNodeFlags dock_flags = 0;
	dock_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
	DockSpaceOverViewport(0, dock_flags);

	DockSpaceOverViewport();

	return setUpUI();
}

update_status UI::PostUpdate()
{
	// Render UI
	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

	return UPDATE_CONTINUE;
}

bool UI::CleanUp()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	DestroyContext();

	return true;
}

void UI::updateObjInspector()
{
	if (selectedObj != nullptr) {
		for (auto& comp : selectedObj->component_vector)
		{
			if (comp->getType() == TRANSFORM) {
				fobjPos = comp->getTransformData()[0];
				fobjRot = comp->getTransformData()[1];
				fobjSca = comp->getTransformData()[2];
			}
		}
	}
}