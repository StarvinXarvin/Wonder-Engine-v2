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
	update_status setUpUI();

	update_status setupMAINMENU();
	void setupINSPECTOR();
	void setupCONSOLE();
	void setupHIERARCHY();
	void setupABOUT();

private:
	bool showDemo;
	bool showHier;
	bool showCons;
	bool showInsp;
	bool showConf;

	bool showAbout;

	glm::vec3 fobjPos;
	glm::vec3 fobjRot;

	const char posxlabel[11] = "Pos x axis";
	const char posylabel[11] = "Pos y axis";
	const char poszlabel[11] = "Pos z axis";
	const char anglexlabel[13] = "Angle x axis";
	const char angleylabel[13] = "Angle y axis";
	const char anglezlabel[13] = "Angle z axis";
};