#include "Application.h"
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

bool UI::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->window->GLContext);
	ImGui_ImplOpenGL3_Init();

	return true;
}

update_status UI::Update()
{
	ImGui_ImplSDL2_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
	
	ImGui::DockSpaceOverViewport();
	
	ImGui::ShowDemoWindow();

	ImGui::End();

	ImGui::Render();

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