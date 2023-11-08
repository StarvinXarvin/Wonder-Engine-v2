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
				if (MenuItem("Hierarchy")) showHier = !showHier;
				if (MenuItem("Inspector")) showInsp = !showInsp;
				if (MenuItem("Configuration")) showConf = !showConf;
				if (MenuItem("Console")) showCons = !showCons;
				ImGui::EndMenu();
			}
			
			if (MenuItem("Show Demo Window")) showDemo = !showDemo;

			if (MenuItem("GitHub", NULL, false, true)) OsOpenInShell("https://github.com/CITM-UPC/Wonder-Engine");

			if (MenuItem("About")) showAbout = !showAbout;

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
				int temp = 0;
				for (auto child : gObj->getChildren())
				{
					stringstream ss;
					ss << child->getName() << "_" << temp;
					if (MenuItem(ss.str().c_str()))
					{
						selectedObj = child;
					}
					temp++;
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
			ImGui::Text(log.c_str());
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
			if (selectedObj != nullptr) {
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
			else
				ImGui::Text("No Object selected");
		}
		if (CollapsingHeader("Mesh"))
		{
			if (selectedObj != nullptr) {
				stringstream meshnamess;
				string meshname = selectedObj->getComponent(MESH)->getName();
				meshnamess << "Mesh file name: " << meshname;
				ImGui::Text(meshnamess.str().c_str());
				if (IsItemHovered())
				{
					stringstream meshfiless;
					string meshpath = selectedObj->getComponent(MESH)->getFilePath();
					meshfiless << "Mesh file path: " << meshpath;
					SetTooltip(meshfiless.str().c_str());
				}
			}
			else
				ImGui::Text("No Object selected");
		}
		if (CollapsingHeader("Texture"))
		{
			if (selectedObj != nullptr) {
				stringstream texturenamess;
				string texturename = selectedObj->getComponent(TEXTURE)->getName();
				texturenamess << "Texture file name: " << texturename;
				ImGui::Text(texturenamess.str().c_str());
				if (IsItemHovered())
				{
					stringstream texturefiless;
					string texturepath = selectedObj->getComponent(TEXTURE)->getFilePath();
					texturefiless << "Texture file path: " << texturepath;
					SetTooltip(texturefiless.str().c_str());
				}
			}
			else
				ImGui::Text("No Object selected");
		}
		End();
	}
}
void UI::setupCONFIG()
{
	if (Begin("Configuration"))
	{
		if (TreeNode("Application"))
		{
			PlotHistogram("FPS", &frame_list[0], frame_list.size(), 0, 0, 0.0f, 100.0f, ImVec2(310, 100));

			PlotHistogram("ms", &ms_list[0], ms_list.size(), 0, 0, 0.0f, 100.0f, ImVec2(310, 100));
			TreePop();
		}
		if (TreeNode("Modules"))
		{
			if (TreeNode("Window"))
			{
				SeparatorText("Size");
				if (DragFloat("Width", &windowwidth, 1.0f, 1.0f, 4096.0f)) App->window->resizeWindow(windowwidth, windowheight);
				if (DragFloat("Height", &windowheight, 1.0f, 1.0f, 4096.0f)) App->window->resizeWindow(windowwidth, windowheight);
				if (TreeNode("Presets"))
				{
					if (MenuItem("1366 x 768"))
					{
						windowwidth = 1366;
						windowheight = 768;
						App->window->resizeWindow(windowwidth, windowheight);
					}
					if (MenuItem("1920 x 1080"))
					{
						windowwidth = 1920;
						windowheight = 1080;
						App->window->resizeWindow(windowwidth, windowheight);
					}
					if (MenuItem("2048 x 1080"))
					{
						windowwidth = 2048;
						windowheight = 1080;
						App->window->resizeWindow(windowwidth, windowheight);
					}
				}

				SeparatorText("Markers");
				Checkbox("Fullscreen", &App->window->fullscreen);
				App->window->handleFullscreen();
				Checkbox("Resizable", &App->window->resizable);
				App->window->handleResizable();
				// VSYNC
				// Predefined window sizes
				//    (HD, FHD, 4K)
				TreePop();
			}
			if (TreeNode("Renderer"))
			{
				TreePop();
			}
			TreePop();
		}
	}
}
void UI::setupABOUT()
{
	if (Begin("About"))
	{
		ImGui::Text("WONDER ENGINE");
		Separator();
		ImGui::Text("Developed by");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.6f, 0.8f, 1.0f, 1.0f), "Pau Fusco");
		if (IsItemClicked()) OsOpenInShell("https://github.com/PauFusco");
		ImGui::SameLine();
		ImGui::Text("&");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.6f, 0.8f, 1.0f, 1.0f), "Xavi Alcaniz");
		if (IsItemClicked()) OsOpenInShell("https://github.com/StarvinXarvin");
		
		Separator();
		ImVec4 colorGray(0.5f, 0.5f, 0.5f, 1.0f);
		Text("LIBRARIES USED: ");
		Bullet(); if (ImGui::Button("Assimp 5.2.5")) OsOpenInShell("https://assimp-docs.readthedocs.io/");
		Bullet(); if (ImGui::Button("DevIL 1.8.0#11")) OsOpenInShell("https://openil.sourceforge.net/");
		Bullet(); if (ImGui::Button("GLEW 2.2.0#3")) OsOpenInShell("https://glew.sourceforge.net/");
		Bullet(); if (ImGui::Button("GLM 2023-06-08")) OsOpenInShell("https://glm.g-truc.net/0.9.5/index.html");
		Bullet(); if (ImGui::Button("ImGUI 1.89.9")) OsOpenInShell("https://imgui-test.readthedocs.io/");
		Bullet(); if (ImGui::Button("jsoncpp 1.9.5")) OsOpenInShell("https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html");
		Bullet(); if (ImGui::Button("OpenGL 2022-12-04#3")) OsOpenInShell("https://www.opengl.org/");
		Bullet(); if (ImGui::Button("SDL2 2.28.3")) OsOpenInShell("https://wiki.libsdl.org/");
		ImGui::End();
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

	windowwidth = App->window->window_width;
	windowheight = App->window->window_height;

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
	TransformComp* transcomp = nullptr;
	if (selectedObj != nullptr) {
		for (auto& comp : selectedObj->component_vector)
		{
			if (comp->getType() == TRANSFORM)
			{
				transcomp = (TransformComp*)comp;
			}
		}

		fobjPos = transcomp->getTransformData()[0];
		fobjRot = transcomp->getTransformData()[1];
		fobjSca = transcomp->getTransformData()[2];
	}
}

void UI::OsOpenInShell(const char* path)
{
#ifdef _WIN32
	// Note: executable path must use backslashes!
	::ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWDEFAULT);
#else
#if __APPLE__
	const char* open_executable = "open";
#else
	const char* open_executable = "xdg-open";
#endif
	char command[256];
	snprintf(command, 256, "%s \"%s\"", open_executable, path);
	system(command);
#endif
}