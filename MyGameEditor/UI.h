#pragma once
#include "Module.h"

class Application;

class UI : public Module
{
public:
	UI(Application* app, bool start_enabled = true);
	virtual ~UI();

	bool Init();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:
	bool createImGuiContext();
	void setUpUI();
};